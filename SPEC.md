# The Formal Specification

This document states the accounting algebra as definitions and theorems,
with the mapping to the Rust implementation. The theorems are proven
mechanically in [`lean/src/Accounting.lean`](lean/src/Accounting.lean);
this document is the human-readable companion.

## 1. Money amounts are integers

Every amount is an element of ℤ — integer minor units. There are no floats
anywhere in the arithmetic path. This is the axiom the entire estate is
built on, and it eliminates the class of defects that Odoo's
`float_utils.py` documents as requiring minimization.

    Amount : ℤ

**Rust mapping**: `double_entry::Amount.units : i64`, with `scale` and
`currency` carried alongside but not affecting the algebra (a per-currency
scale is metadata; the arithmetic is integer addition regardless).

## 2. The posting monoid

A **posting** maps an account to a signed amount: debit is positive, credit
is negative.

    Posting := (account : AccountId, amount : ℤ)

A **transaction** is a finite list of postings. A transaction is
**balanced** when the signed amounts sum to zero:

    balanced(tx) :↔ Σ tx.amounts = 0

**Theorem 2.1** (Posting commutativity). The order of postings within a
transaction does not affect whether the transaction is balanced, nor the
balance it produces on any account.

**Theorem 2.2** (Balance conservation). If every transaction in a ledger is
balanced, then the sum of all account balances is zero.

**Rust mapping**: `double_entry::post()` refuses unbalanced entries
(`PostError::Unbalanced`). The theorem says this check is not just
defensive — it enforces the conservation law that makes the reports work.

## 3. The trial balance

The **balance** of an account `a` in a ledger `L`:

    balance(L, a) := Σ { p.amount | p ∈ L, p.account = a }

**Theorem 3.1** (Trial balance). If every entry in `L` is balanced, then:

    Σ { balance(L, a) | a ∈ accounts(L) } = 0

This is the runtime check `report-kit`'s `TrialBalance::is_balanced()`
performs, restated: the report is not discovering something about the
ledger — it is confirming a property the ledger's post-time check already
guaranteed. The theorem says the check must always pass; if it doesn't, the
ledger is not a ledger.

## 4. Reversal is an involution

A **reversal** of entry `e` is an entry `e'` whose postings are `e`'s
postings with every amount negated.

    reversed(e) := { p | amount := −p.amount, account := p.account, p ∈ e }

**Theorem 4.1** (Reversal conservation). If `e` is balanced and `e'` is its
reversal, then `e + e'` is balanced: the pair nets to zero on every account.

    ∀a. balance({e, e'}, a) = balance({e}, a) + balance({e'}, a) = 0

**Rust mapping**: `double_entry`'s `reverse()` and `ledger-pg`'s
`reverse()`. The original stays posted and the counter cancels it — the
theorem says the cancellation is exact, to the minor unit, on every
account, which is why the reversal cannot produce a spurious residual.

## 5. Rounding

The rounding function maps an exact rational `q = n/d` to an integer,
breaking ties by `mode`:

    round(n, d, HalfUp)   = ⌈n/d⌉ if the fractional part ≥ ½, else ⌊n/d⌋
    round(n, d, HalfEven) = the even neighbour on ties
    round(n, d, TowardZero) = truncate(n/d)

**Theorem 5.1** (Sum-to-gross). For any VAT-inclusive gross `g` and any
rate `r < 1000`:

    split(g, r).net + split(g, r).vat = g

**Rust mapping**: `invoice_kit::split_vat_inclusive`. The net is computed
as `gross − vat`, never independently — the theorem says this is not an
optimisation but the definition of correctness.

**Theorem 5.2** (Sign symmetry). For any amount `a` and rate `r`:

    restate(−a, r) = −restate(a, r)

**Rust mapping**: `fx_kit::Rate::restate` rounds the magnitude and restores
the sign. A signed-toward-zero rounding would break this at ties; the
theorem pins the guarantee.

**Theorem 5.3** (Scope drift bound). For `n` lines and `k` jurisdictions:

    | per_line_total − per_document_total | ≤ ⌈n·k/2⌉

**Rust mapping**: `sales_tax`'s `PerLine` vs `PerDocument`. The property
test bounds the drift; the theorem says the bound is tight.

## 6. The hash chain

A **hash chain** over entries `e₁, e₂, …` with previous hash `h₀`:

    hᵢ := SHA256(canonical(eᵢ) ∥ hᵢ₋₁)

**Theorem 6.1** (Tamper detection). If `hⱼ` is the first hash that does not
match its recomputation, then entry `eⱼ` (or any earlier entry) has been
altered since its hash was committed.

**Rust mapping**: `ledger_pg::verify_chain`. The theorem is conditional on
SHA-256's collision resistance — stated in Lean as a trusted assumption,
not proven from first principles (which would be a paper, not a proof).

## 7. What is deliberately not specified

- **Currency conversion**: rates are exact rationals supplied by the
  caller; the theorem set covers restatement arithmetic, not rate discovery.
- **Tax law**: the taxability decision is an input (`ap-kit`'s
  `Recoverability`, `sales-tax`'s `SaleLine.taxable`). The arithmetic is
  specified; the law is not.
- **Float behavior**: there is none. The specification has no float type.
