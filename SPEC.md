# The Formal Specification

> **Status: CURRENT**
**Oracle:** `lean/src/Accounting.lean`

This document states the accounting algebra as definitions and theorems,
with the mapping to the Rust implementation. The theorems are proven
mechanically in [`lean/src/Accounting.lean`](lean/src/Accounting.lean);
this document is the human-readable companion.

**Status (Iteration 2)**: every theorem in the Lean file is machine-proved
with Lean 4 core alone - zero `sorry`s, zero dependencies, and `lake build`
type-checks all of them (the library target is declared; previously CI
verified nothing). See ITERATIONS.md for the research loop.

## 1. Money amounts are integers

Every amount is an element of ℤ; integer minor units. There are no floats
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
defensive; it enforces the conservation law that makes the reports work.

## 3. The trial balance

The **balance** of an account `a` in a ledger `L`:

    balance(L, a) := Σ { p.amount | p ∈ L, p.account = a }

**Formal status (Iteration 3)**: the account dimension is now modelled -
`Posting` carries `account : Nat`, `balanceOf` is the per-account fold,
and the append law (`balanceOf (x ++ y) a = balanceOf x a + balanceOf y a`)
plus the per-account reversal law (`balanceOf (reverseEntries ps) a =
−balanceOf ps a`) are machine-proved. The coverage form (Σ over a
covering, duplicate-free account list = 0) is the next open theorem;
its `NoDup` side-condition is load-bearing - a duplicated account
double-counts, and the Rust `TrialBalance` must iterate distinct
accounts.

**Theorem 3.1** (Trial balance). If every entry in `L` is balanced, then:

    Σ { balance(L, a) | a ∈ accounts(L) } = 0

This is the runtime check `report-kit`'s `TrialBalance::is_balanced()`
performs, restated: the report is not discovering something about the
ledger; it is confirming a property the ledger's post-time check already
guaranteed. The theorem says the check must always pass; if it doesn't, the
ledger is not a ledger.

## 4. Reversal is an involution

A **reversal** of entry `e` is an entry `e'` whose postings are `e`'s
postings with every amount negated.

    reversed(e) := { p | amount := −p.amount, account := p.account, p ∈ e }

**Theorem 4.1** (Reversal conservation). If `e` is balanced and `e'` is its
reversal, then `e + e'` is balanced: the pair nets to zero on every account.

    ∀a. balance({e, e'}, a) = balance({e}, a) + balance({e'}, a) = 0

**Theorem 4.2** (Reversal involution, added Iteration 2). Reversing twice
is the identity:

    reversed(reversed(e)) = e

**Rust mapping**: `double_entry`'s `reverse()` and `ledger-pg`'s
`reverse()`. The original stays posted and the counter cancels it; the
theorem says the cancellation is exact, to the minor unit, on every
account, which is why the reversal cannot produce a spurious residual.
The involution theorem pins the round-trip: a reversed reversal must
reproduce the original entry bit-for-bit.

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
as `gross − vat`, never independently; the theorem says this is not an
optimisation but the definition of correctness.

**Theorem 5.1b** (Rounding error bound). For any `n` and any `d > 0`,
half-up rounding lands within half a minor unit of the exact quotient:

    −d/2 ≤ d · round(n, d) − n ≤ d/2

Two-sided - the form the drift bound (Theorem 5.3) composes. The bound
is mode-robust: every nearest-rounding mode satisfies it, so switching
`TieMode` cannot leak more than half a minor unit per rounding.

**Corollary** (VAT error bound). The VAT leg of a split is within
`(1000 + rate)/2` minor units of the exact product, and the net absorbs
the difference exactly (by 5.1).

**Rust mapping**: `invoice_kit::split_vat_inclusive` (in i128, via the
shared `TieMode` from `vat-rules`).

**Theorem 5.2** (Sign symmetry). For any amount `a` and rate `r`:

    restate(−a, r) = −restate(a, r)

The proof is definitional, and that is the finding: `restate` is
specified as magnitude-then-sign,

    restate(a, d) := sign(a) · (⌊|a| + d/2⌋ / d in half-up form)

Applying the raw half-up formula to signed input breaks symmetry at ties
(`(−1 + 1)/2 = 0 ≠ −1` at `d = 2`). The definition is the guarantee.

**Rust mapping**: `fx_kit::Rate::restate` rounds the magnitude and restores
the sign; the theorem pins that this construction, not extra code, is
what makes credit notes restate symmetrically.

**Theorem 5.3** (Scope drift bound, corrected in Iteration 6). For `n`
lines over one rate, the per-line and per-document allocations differ by
at most `⌊n/2⌋` minor units:

    2 · |per_line_total − per_document_total| ≤ n

Across `k` rates the total drift is at most `k·⌊n/2⌋`. The earlier
claim `⌈n·k/2⌉` was valid but loose by up to `(k−1)/2` - the tight form
follows from the *strict* bottom end of the sharp error bound (5.1b):
half-up's error is strictly greater than `−d/2` because the Euclidean
remainder is at most `d − 1`. Attained: two lines each with an exact
`.5` fraction give per-line `2` vs per-document `1`.

**Rust mapping**: `sales_tax`'s `RoundingScope.PerLine` vs
`PerDocument`. The property test bounded the drift; the theorem pins the
tight constant.

## 6. The hash chain - symbolic model (Iteration 7)

A chain entry is a pair `(payload, prevHash)`; the chained hash is

    stepHash(e) := SHA256(canonical(e.payload) ∥ e.prevHash)

modelled symbolically as an injective function on the canonical pair
(the Toychain axiom shape - Pîrlea & Sergey, CPP 2018). Injectivity
idealizes collision resistance; no preimage axiom is needed, because
detection never inverts a hash.

**Theorem 6.2** (Valid append). An entry claiming the chain's end hash
extends the chain validly:

    validChain(h, es) ∧ e'.prevHash = chainEnd(h, es)
      → validChain(h, es ++ [e'])

**Theorem 6.3** (Tamper localization). Replacing the head entry of a
valid chain continuation with a different entry - whatever previous
hash the attacker claims - invalidates it:

    validChain(stepHash(e), r :: rs) ∧ stepHash(e') ≠ stepHash(e)
      → ¬validChain(stepHash(e'), r :: rs)

This is the first-divergence localization a linear chain gives for
free: the mismatch pinpoint's the tampered position (a Merkle root
mismatch only says "something", not "where"). Scope: tampering with
the *last* entry changes only the end hash, whose detection requires
the anchored head - stated with the head as hypothesis, since whoever
can rewrite the whole chain *and* the head passes any internal check.

**Rust mapping**: `ledger-pg`'s `verify_chain` (`ChainVerification`/
`ChainBreak` at the first mismatch - the localization, implemented)
and `ledger-kit`'s `verify_chain` (via `tamper-audit`, SHA-256).
Note for integrators: `ledger-pg` currently logs a `CHAIN DEBUG`
eprintln in the hash-mismatch path - remove before the next release.

## 7. What is deliberately not specified

- **Currency conversion rates**: rates are exact rationals supplied by
  the caller; the theorem set covers conversion *mechanics* (§8), not
  rate discovery.
- **Tax law**: the taxability decision is an input (`ap-kit`'s
  `Recoverability`, `sales-tax`'s `SaleLine.taxable`). The arithmetic is
  specified; the law is not.
- **Float behavior**: there is none. The specification has no float type.

## 8. The currency view - per-currency conservation

Currencies are dimensions exactly as accounts are (§2b, one level up): a
posting carries `(account, currency, amount)`, and the conservation law
holds **per currency**. A cross-currency sum is not a term of the
algebra.

    CPosting := (account : Nat, currency : CurrencyId, amount : ℤ)
    amountsIn(c, ps)  := the amounts of ps whose currency is c
    isBalancedIn(c, ps) :↔ Σ amountsIn(c, ps) = 0
    balanceOfIn(led, c, a) := Σ { p.amount | p ∈ led, p.currency = c,
                                           p.account = a }

**Theorem 8.1** (Per-currency trial balance). If every entry of a
journal is balanced in currency `c`, the currency-restricted view of the
whole journal is balanced in `c`.

**Theorem 8.2** (Reversal cancels, currency-refined). An entry plus its
reversal is balanced in every currency.

**Theorem 8.3** (Coverage). Let `chart` be a list of accounts with no
duplicates that covers every posting's account. If the ledger is
balanced in currency `c`, then the sum of per-account balances over the
chart is zero:

    Σ { balanceOfIn(led, c, a) | a ∈ chart } = 0

This is §3's trial balance stated the way the report actually computes
it: per account, over the chart of accounts. `NoDup` is load-bearing -
a duplicated chart entry would double-count. The theorem is what makes
the runtime check *a check with content*: it recomputes the invariant
by a different route (per-account, not per-entry) and must land on the
same zero.

**Theorem 8.4** (Conversion preserves conservation). A well-formed
conversion between currencies `c` and `d` is two internally balanced
entries: `v` moves from the source account to the FX account within `c`;
the converted amount moves from the FX account to the target account
within `d`. Appending any sequence of such entries to a
per-currency-balanced journal keeps it balanced in every currency. The
FX account carries the cross-currency exposure - measurable, auditable,
never a silent leak.

**Rust mapping**: `double_entry`'s `PostError::MixedCurrencies` and
per-currency `Amount`; `report-kit`'s `TrialBalance::currencies()` and
`accounting_equation_holds`; `fx-kit`'s `revalue` (IAS 21) posting
residuals to a named account. Structural precedent: TigerBeetle makes
cross-ledger transfers illegal (`accounts_must_have_the_same_ledger`);
ERP practice (Odoo's exchange-difference journal, ERPNext's
`difference_amount == 0` gate) requires every residual to land on a
named account. Per-currency conservation is *enforced at runtime*
everywhere we checked and *proved* nowhere - this section is the
proof.
