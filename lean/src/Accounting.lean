/-
The formal proofs for the WyattAu accounting estate.

Every definition here corresponds to a section of SPEC.md. The theorems
are stated with their Rust implementation mappings.

Status (Iteration 4): ZERO `sorry`s. Zero dependencies beyond Lean 4 core.
`lake build` type-checks every proof.

Three layers, per Ellerman's mathematical treatment of double-entry
bookkeeping (arXiv:1407.1898): a ledger entry is an element of the group
of differences, and with multiple accounts it is a *vector* — accounts are
dimensions, not erased labels.

- **Amount view** (§2): lists of signed amounts. The conservation
  theorems live here; they are pure `List Int` algebra.
- **Account view** (§2b): postings carry an account id; the amount view
  is the *projection* `amounts`. Per-account balances, their append and
  reversal laws, and entry-level cancellation are proved here.
- **Currency view** (§7): postings carry a currency; conservation holds
  *per currency*, the coverage trial balance sums per-account balances
  over a NoDup chart, and well-formed conversions post every residual
  to an account.

Axioms of trust:
- `Int` arithmetic is correct (Lean 4 core, which is self-hosted).
- SHA-256's collision resistance is a trusted assumption (Section 6).
- The mapping to the Rust implementation is by review, not by extraction
  (see ITERATIONS.md for the extraction roadmap).

Proof-engineering notes (Iteration 2, kept for posterity):
- `omega`'s frontend type-sniffs operands and rejects terms typed through
  the `Amount`/`Posting` abbrevs ("no usable constraints", 4.29 and 4.35
  alike). `grind` — 4.35's Cooper-style LIA — has no such strictness and
  closes the residual arithmetic.
- Iteration 1's "needs mathlib" claim was never tested; it was wrong.
- Deterministic `rfl`-have + `rw` chains beat fragile `simp` composition.
- The lakefile previously declared no library target, so CI verified
  nothing. It now declares `Accounting` as the default target.
-/

/-! ## Section 1: Money amounts are integers -/

/-- An amount is an integer in minor units. -/
abbrev Amount := Int

/-! ## Section 2: The amount view — the conservation algebra

A posting's *amount* is signed: debit positive, credit negative. At this
layer the account assignment is erased — these are the theorems about
debits-equal-credits alone. -/

/-- The signed sum of a list of amounts. -/
def postingSum (ps : List Amount) : Amount := ps.sum

/-- A list of amounts is balanced when its signed sum is zero. -/
def isBalanced (ps : List Amount) : Prop := postingSum ps = 0

/-- The reversal of an amount negates it. -/
def reversePosting (a : Amount) : Amount := -a

/-- The reversal of a list of amounts negates every amount. -/
def reverseAll (ps : List Amount) : List Amount := ps.map reversePosting

/-- **Helper** (`sum_map_neg`): the sum of negated amounts is the negated
sum. Stated over raw list operations so induction + `grind` close it; the
`reverseAll` theorem is a one-line corollary. -/
theorem sum_map_neg (ps : List Amount) :
    (ps.map reversePosting).sum = -ps.sum := by
  induction ps with
  | nil => rfl
  | cons x xs ih =>
    simp only [reversePosting, List.map_cons, List.sum_cons, ih]
    grind

/-- **posting_sum_append**: The sum of a concatenation is the sum of the
sums.

    ∀ a b, postingSum (a ++ b) = postingSum a + postingSum b

**Rust**: `double_entry`'s posting append. -/
theorem posting_sum_append (a b : List Amount) :
    postingSum (a ++ b) = postingSum a + postingSum b := by
  simp [postingSum, List.sum_append]

/-- **reversal_sum_negates**: The sum of the reversal is the negation of
the sum of the original.

**Rust**: `double_entry`'s and `ledger-pg`'s reversal. -/
theorem reversal_sum_negates (ps : List Amount) :
    postingSum (reverseAll ps) = -(postingSum ps) := by
  simp only [reverseAll, postingSum]
  exact sum_map_neg ps

/-- **reversal_cancels**: An entry plus its reversal is balanced: the
cancellation is exact, to the minor unit, with no residual. The proof
shows this is *unconditional* — it holds for every amount list, balanced
or not; the balancedness hypothesis in SPEC is kept for fidelity.

**Rust**: `double_entry`'s `reverse()` and `ledger-pg`'s `reverse()`.
0.2.0's double-flip (counter with the original's sides) violated this
theorem and was caught by the chain tests plus the balance assertion. -/
theorem reversal_cancels (ps : List Amount) :
    isBalanced (ps ++ reverseAll ps) := by
  rw [isBalanced, posting_sum_append, reversal_sum_negates]
  grind

/-- **trial_balance**: The trial balance's check must always pass on a
ledger whose every entry was posted through the balanced gate.

    ∀ pss, (∀ ps ∈ pss, isBalanced ps) →
             isBalanced (pss.foldr (fun a b => a ++ b) [])

**Rust**: `report-kit`'s `TrialBalance::is_balanced()`. The theorem says
the check is not discovering something about the ledger — it is confirming
a property the post-time gate already guaranteed. -/
theorem trial_balance (pss : List (List Amount))
    (h : ∀ ps ∈ pss, isBalanced ps) :
    isBalanced (pss.foldr (fun a b => a ++ b) []) := by
  induction pss with
  | nil => simp [isBalanced, postingSum]
  | cons ps rest ih =>
    have hps : isBalanced ps := h ps (List.mem_cons_self ..)
    have hrest : ∀ q ∈ rest, isBalanced q :=
      fun q hq => h q (List.mem_cons_of_mem _ hq)
    have hrest' : isBalanced (rest.foldr (fun a b => a ++ b) []) := ih hrest
    simp only [List.foldr_cons]
    rw [isBalanced, posting_sum_append]
    rw [isBalanced] at hps hrest'
    grind

/-- **reversal_involution**: SPEC §4's title names reversal an involution;
here is the theorem the title promised. Reversing twice is the identity.

**Rust**: reversing a reversal must reproduce the original entry
(`double_entry`'s round-trip test). -/
theorem reversePosting_idempotent (a : Amount) :
    reversePosting (reversePosting a) = a := Int.neg_neg a

theorem reversal_involution (ps : List Amount) :
    reverseAll (reverseAll ps) = ps := by
  induction ps with
  | nil => rfl
  | cons x xs ih =>
    have h : reverseAll (reverseAll (x :: xs)) =
        reversePosting (reversePosting x) :: reverseAll (reverseAll xs) := rfl
    rw [h, ih, reversePosting_idempotent]

/-- **nil_balanced**: The empty amount list is balanced. Definitional. -/
theorem nil_balanced : isBalanced [] := rfl

/-! ## Section 2b: The account view — postings carry their dimension -/

/-- A posting assigns a signed amount to an account. The account is the
*dimension* (Ellerman's vector view); the conservation algebra of §2
operates on the `amounts` projection. -/
structure Posting where
  account : Nat
  amount : Amount

/-- The amount projection — the input to the §2 algebra. -/
def amounts (ps : List Posting) : List Amount := ps.map (·.amount)

/-- An entry is balanced when its amount projection is balanced. -/
def isBalancedEntry (ps : List Posting) : Prop := isBalanced (amounts ps)

/-- The reversal of a posting negates the amount, preserves the account. -/
def reverseEntry (p : Posting) : Posting := { p with amount := -p.amount }

/-- The reversal of a posting list. -/
def reverseEntries (ps : List Posting) : List Posting := ps.map reverseEntry

/-- **amounts_append**: the projection is a list homomorphism. -/
theorem amounts_append (x y : List Posting) :
    amounts (x ++ y) = amounts x ++ amounts y := by
  simp [amounts, List.map_append]

/-- **amounts_reverseEntries**: reversal at the posting level projects to
reversal at the amount level. -/
theorem amounts_reverseEntries (ps : List Posting) :
    amounts (reverseEntries ps) = reverseAll (amounts ps) := by
  induction ps with
  | nil => rfl
  | cons p rest ih =>
    have h1 : amounts (reverseEntries (p :: rest)) =
        -(p.amount) :: amounts (reverseEntries rest) := rfl
    have h2 : amounts (p :: rest) = p.amount :: amounts rest := rfl
    rw [h1, h2, ih]
    rfl

/-- The balance of account `a` under posting list `led`: the signed sum of
exactly those postings assigned to `a`.

**Rust**: `report-kit`'s per-account balance in the trial balance. -/
def balanceOf (led : List Posting) (a : Nat) : Amount :=
  led.foldr (fun p acc => if p.account = a then p.amount + acc else acc) 0

/-- **balanceOf_nil**: the empty ledger gives every account a zero balance.
Definitional. -/
theorem balanceOf_nil (a : Nat) : balanceOf [] a = 0 := rfl

/-- **balanceOf_cons**: one posting adds its amount to exactly one
account's balance. -/
theorem balanceOf_cons (p : Posting) (led : List Posting) (a : Nat) :
    balanceOf (p :: led) a =
      if p.account = a then p.amount + balanceOf led a else balanceOf led a :=
  rfl

/-- **balanceOf_append**: balances compose over ledger concatenation —
running the ledger in two halves then adding equals running it whole.

    ∀ x y a, balanceOf (x ++ y) a = balanceOf x a + balanceOf y a -/
theorem balanceOf_append (x y : List Posting) (a : Nat) :
    balanceOf (x ++ y) a = balanceOf x a + balanceOf y a := by
  induction x with
  | nil => simp [balanceOf]
  | cons p rest ih =>
    rw [List.cons_append, balanceOf_cons]
    split
    · next h => rw [balanceOf_cons, if_pos h, ih, Int.add_assoc]
    · next h => rw [balanceOf_cons, if_neg h]; exact ih

/-- **balanceOf_reverseEntries**: the reversal negates every account's
balance — exactly, to the minor unit, per account.

    ∀ ps a, balanceOf (reverseEntries ps) a = -(balanceOf ps a) -/
theorem balanceOf_reverseEntries (ps : List Posting) (a : Nat) :
    balanceOf (reverseEntries ps) a = -(balanceOf ps a) := by
  induction ps with
  | nil => rfl
  | cons p rest ih =>
    have hc : balanceOf (reverseEntries (p :: rest)) a =
        if p.account = a then -p.amount + balanceOf (reverseEntries rest) a
        else balanceOf (reverseEntries rest) a := by
      simp only [reverseEntries, List.map_cons, balanceOf, List.foldr_cons,
        reverseEntry]
    have h1 : balanceOf (p :: rest) a =
        if p.account = a then p.amount + balanceOf rest a
        else balanceOf rest a := rfl
    rw [hc, h1]
    split
    · rw [ih, Int.neg_add]
    · exact ih


theorem entry_reversal_cancels (ps : List Posting) :
    isBalancedEntry (ps ++ reverseEntries ps) := by
  rw [isBalancedEntry, amounts_append, amounts_reverseEntries]
  exact reversal_cancels _

/-! ## Section 3: Rounding -/

/-- Rounding a rational `n/d` with half-up tie-breaking on the magnitude.
Stated for non-negative `n` and positive `d` (the magnitude path in
`fx_kit::Rate::restate`); the sign is restored externally. -/
def roundHalfUp (n d : Int) : Int := (n + d / 2) / d

/-- A VAT-inclusive gross split into net and tax. -/
structure GrossSplit where
  gross : Int
  rate : Int
  vat : Int
  net : Int

/-- Split a VAT-inclusive gross: tax = gross × rate / (1000 + rate),
net = gross − tax. The net is computed as gross − tax, never
independently, so the pieces always sum to the gross. -/
def splitVatInclusive (gross rate : Int) : GrossSplit where
  gross := gross
  rate := rate
  vat := (gross * rate + (1000 + rate) / 2) / (1000 + rate)
  net := gross - ((gross * rate + (1000 + rate) / 2) / (1000 + rate))

/-! ## Section 5: Rounding theorems -/

/-- **Theorem 5.1 (Sum-to-gross)**: The pieces always sum to the gross,
because the net is computed as the gross minus the tax — not
independently. This is a definitional tautology — which is the point: the
*definition* of the net is what guarantees the invariant, not a separate
computation that might disagree. -/
theorem split_sums_to_gross (gross rate : Int) :
    let s := splitVatInclusive gross rate
    s.net + s.vat = s.gross := by
  simp [splitVatInclusive]

/-! ## Section 6: The hash chain (symbolic model — Iteration 7) -/

/-- **Theorem (tamper detection)**: If any entry in a committed hash chain
is altered, the recomputed hash at that position differs from the stored
hash. Conditional on SHA-256's collision resistance. The symbolic-hash
axiomatisation that turns this from `True := trivial` into a real proof is
Iteration 7's deliverable (see ITERATIONS.md). -/
theorem tamper_detection_conditional : True := trivial

/-! ## Section 7: The currency view — per-currency conservation (Iteration 4)

Currencies are dimensions exactly as accounts are (Ellerman's vector
view, one level up): a posting carries `(account, currency, amount)`, and
the conservation law holds *per currency*. A cross-currency sum is not a
term of the algebra. The Rust side mirrors the structure: `double_entry`
refuses `MixedCurrencies` at post time, TigerBeetle makes cross-ledger
transfers structurally illegal, and ERP practice (Odoo's
exchange-difference journal, ERPNext's `difference_amount == 0` gate)
requires every FX residual to land on a named account. No published
ledger *proves* this; everywhere it is a runtime check. -/

/-- A currency is an opaque identifier; the algebra never converts
silently. -/
abbrev CurrencyId := Nat

/-- A currency-tagged posting. -/
structure CPosting where
  account : Nat
  currency : CurrencyId
  amount : Amount

/-- The amounts of a posting list restricted to currency `c`. -/
def amountsIn (c : CurrencyId) (ps : List CPosting) : List Amount :=
  ps.foldr (fun p acc => if p.currency = c then p.amount :: acc else acc) []

/-- Cons equation for `amountsIn` — the rfl lemma that keeps rewrites
folded (rw-unfolding the def breaks later pattern matches). -/
theorem amountsIn_cons (c : CurrencyId) (p : CPosting) (ps : List CPosting) :
    amountsIn c (p :: ps) =
      if p.currency = c then p.amount :: amountsIn c ps else amountsIn c ps :=
  rfl

/-- Balanced *in currency `c`*: the currency-restricted signed sum is
zero. -/
def isBalancedIn (c : CurrencyId) (ps : List CPosting) : Prop :=
  (amountsIn c ps).sum = 0

/-- The balance of account `a` in currency `c`.

**Rust**: `report-kit`'s `TrialBalance::currencies()` + per-account rows. -/
def balanceOfIn (led : List CPosting) (c : CurrencyId) (a : Nat) : Amount :=
  led.foldr (fun p acc => if p.currency = c ∧ p.account = a then p.amount + acc else acc) 0

/-- Cons equation for `balanceOfIn`. -/
theorem balanceOfIn_cons (p : CPosting) (led : List CPosting) (c : CurrencyId) (a : Nat) :
    balanceOfIn (p :: led) c a =
      if p.currency = c ∧ p.account = a then p.amount + balanceOfIn led c a
      else balanceOfIn led c a :=
  rfl

/-- **amountsIn_append**: the currency projection is a homomorphism —
slicing by currency distributes over ledger concatenation. -/
theorem amountsIn_append (c : CurrencyId) (x y : List CPosting) :
    amountsIn c (x ++ y) = amountsIn c x ++ amountsIn c y := by
  induction x with
  | nil => rfl
  | cons p rest ih =>
    rw [List.cons_append, amountsIn_cons, amountsIn_cons, ih]
    by_cases h : p.currency = c
    · rw [if_pos h, if_pos h]; rfl
    · rw [if_neg h, if_neg h]

/-- **trial_balance_currency**: if every entry of the ledger is balanced
in currency `c`, the currency-restricted view of the whole ledger is
balanced in `c`. The per-currency form of §3's trial balance. -/
theorem trial_balance_currency (c : CurrencyId)
    (entries : List (List CPosting))
    (h : ∀ e ∈ entries, isBalancedIn c e) :
    isBalancedIn c (entries.foldr (fun a b => a ++ b) []) := by
  induction entries with
  | nil => rfl
  | cons e rest ih =>
    have he : isBalancedIn c e := h e (List.mem_cons_self ..)
    have hrest : ∀ q ∈ rest, isBalancedIn c q :=
      fun q hq => h q (List.mem_cons_of_mem _ hq)
    have hrest' : isBalancedIn c (rest.foldr (fun a b => a ++ b) []) := ih hrest
    simp only [List.foldr_cons, amountsIn_append, isBalancedIn] at *
    rw [List.sum_append, he, hrest']
    simp

/-- The reversal of a currency-tagged posting negates the amount and
preserves the account and currency. -/
def reverseCPosting (p : CPosting) : CPosting := { p with amount := -p.amount }

/-- The reversal of a currency-tagged posting list. -/
def reverseCEntries (ps : List CPosting) : List CPosting := ps.map reverseCPosting

/-- A chart has no duplicated accounts. (Core Lean 4 has no `List.NoDup`;
this is the minimal local version — a duplicated chart entry would
double-count, which the theorem forbids.) -/
inductive NoDup : List Nat → Prop
  | nil : NoDup []
  | cons : ∀ {a l}, a ∉ l → NoDup l → NoDup (a :: l)

/-- **amountsIn_reverseCEntries**: reversal projects to reversal in every
currency slice. -/
theorem amountsIn_reverseCEntries (c : CurrencyId) (ps : List CPosting) :
    amountsIn c (reverseCEntries ps) = reverseAll (amountsIn c ps) := by
  induction ps with
  | nil => rfl
  | cons p rest ih =>
    show amountsIn c (reverseCPosting p :: reverseCEntries rest) = _
    rw [amountsIn_cons, amountsIn_cons, ih]
    simp only [reverseCPosting]
    by_cases h : p.currency = c
    · simp [h, reverseAll, reversePosting, List.map_cons]
    · simp [h, reverseAll, reversePosting, List.map_cons]

/-- **reversal_cancels_in**: an entry plus its reversal is balanced in
every currency — the §4 cancellation, currency-refined. -/
theorem reversal_cancels_in (c : CurrencyId) (ps : List CPosting) :
    isBalancedIn c (ps ++ reverseCEntries ps) := by
  show (amountsIn c (ps ++ reverseCEntries ps)).sum = 0
  rw [amountsIn_append, amountsIn_reverseCEntries]
  exact reversal_cancels _

/-! ### The coverage theorem — §3 as stated

§3's trial balance sums over the *accounts*. That needs a finite chart
(a covering account list); a duplicated chart entry would double-count,
so `NoDup` is load-bearing. -/

/-- Helper: summing a constant-zero mapping over a chart is zero. -/
theorem sum_const_zero (l : List Nat) :
    (l.map (fun _ => (0 : Amount))).sum = 0 := by
  induction l with
  | nil => rfl
  | cons _ rest ih => rw [List.map_cons, List.sum_cons, ih]; simp

/-- Helper: a pointwise sum of functions sums to the sum of sums. -/
theorem sum_map_add (f g : Nat → Amount) (l : List Nat) :
    (l.map (fun a => f a + g a)).sum = (l.map f).sum + (l.map g).sum := by
  induction l with
  | nil => rfl
  | cons x rest ih => simp only [List.map_cons, List.sum_cons, ih]; grind

/-- Helper: a chart on which account `a` never appears contributes zero
to the single-hit sum. -/
theorem sum_zero_of_ne : ∀ (chart : List Nat) (a : Nat) (v : Amount),
    (∀ x ∈ chart, x ≠ a) →
    (chart.map (fun x => if x = a then v else 0)).sum = 0 := by
  intro chart
  induction chart with
  | nil => intro a v _; rfl
  | cons hd rest ih =>
    intro a v hne
    have hz := ih a v (fun x hx => hne x (List.mem_cons_of_mem _ hx))
    rw [List.map_cons, List.sum_cons, if_neg (hne hd (List.mem_cons_self ..)), hz]
    simp

/-- Helper: exactly-one-hit sum. If account `a` appears in `chart`, the
sum of `if x = a then v else 0` over the chart is `v` — `NoDup` ensures
the hit is single. -/
theorem sum_single_hit : ∀ (chart : List Nat) (a : Nat) (v : Amount),
    NoDup chart → a ∈ chart →
    (chart.map (fun x => if x = a then v else 0)).sum = v := by
  intro chart
  induction chart with
  | nil => intro a v _ hmem; exact absurd hmem (by simp)
  | cons hd rest ih =>
    intro a v hnd hmem
    cases hnd with
    | @cons _ _ hnot hndrest =>
      rw [List.map_cons, List.sum_cons]
      by_cases h : hd = a
      · rw [if_pos h]
        have hz : (rest.map (fun x => if x = a then v else 0)).sum = 0 :=
          sum_zero_of_ne rest a v (by
            intro x hx hxa
            rw [hxa.trans h.symm] at hx
            exact hnot hx)
        rw [hz]; simp
      · rw [if_neg h]
        have hmem' : a ∈ rest := by
          rcases List.mem_cons.1 hmem with he | he
          · exact absurd he.symm h
          · exact he
        rw [ih a v hndrest hmem']
        simp

/-- **coverage_exchange**: the exchange lemma. With a `NoDup` chart that
covers every posting's account, the sum of per-account balances in `c`
equals the currency-restricted total — this is what makes the trial
balance a *check with content*: it recomputes the invariant by a
different route (per-account instead of per-entry). -/
theorem coverage_exchange (led : List CPosting) (c : CurrencyId) :
    ∀ (chart : List Nat), NoDup chart →
    (∀ p ∈ led, p.account ∈ chart) →
    (chart.map (fun a => balanceOfIn led c a)).sum = (amountsIn c led).sum := by
  induction led with
  | nil =>
    intro chart _ _
    exact sum_const_zero chart
  | cons p rest ih =>
    intro chart hnd hcov
    cases hnd with
    | nil => exact absurd (hcov p (List.mem_cons_self ..)) (by simp)
    | @cons a l hnot hndrest =>
      -- `chart` has been substituted to `a :: l`
      have hcov' : ∀ q ∈ rest, q.account ∈ a :: l :=
        fun q hq => hcov q (List.mem_cons_of_mem _ hq)
      by_cases hpc : p.currency = c
      · have hpa : p.account ∈ a :: l := hcov p (List.mem_cons_self ..)
        have step : ∀ x : Nat, balanceOfIn (p :: rest) c x =
            (if x = p.account then p.amount else 0) + balanceOfIn rest c x := by
          intro x
          rw [balanceOfIn_cons]
          by_cases h : p.account = x
          · rw [if_pos ⟨hpc, h⟩, if_pos h.symm]
          · rw [if_neg (fun hcon => h hcon.2), if_neg (fun hcon => h hcon.symm)]
            simp
        simp only [step, sum_map_add,
          sum_single_hit (a :: l) p.account p.amount (NoDup.cons hnot hndrest) hpa,
          amountsIn_cons, if_pos hpc, List.sum_cons]
        rw [ih (a :: l) (NoDup.cons hnot hndrest) hcov']
      · have step : ∀ x : Nat, balanceOfIn (p :: rest) c x =
            balanceOfIn rest c x := by
          intro x
          rw [balanceOfIn_cons, if_neg (fun hcon => hpc hcon.1)]
        simp only [step, amountsIn_cons, if_neg hpc, List.sum_cons]
        rw [ih (a :: l) (NoDup.cons hnot hndrest) hcov']

/-- **trial_balance_coverage**: §3's theorem, now stated and proved. If
the chart covers every posting's account (NoDup), a ledger balanced in
currency `c` sums to zero over the chart. The runtime check
`report-kit`'s `TrialBalance::is_balanced()` performs is exactly this
sum; the theorem says on a gated ledger it cannot fail. -/
theorem trial_balance_coverage (led : List CPosting) (c : CurrencyId)
    (chart : List Nat) (hnd : NoDup chart)
    (hcov : ∀ p ∈ led, p.account ∈ chart)
    (hb : isBalancedIn c led) :
    (chart.map (fun a => balanceOfIn led c a)).sum = 0 := by
  have hex := coverage_exchange led c chart hnd hcov
  rw [hex]
  exact hb

/-! ### The conversion entries — every residual has an account

A well-formed conversion between currency `c` (source) and `d` (target)
is *two* internally balanced entries: `v` moves from the source account
to the FX account within `c`; the converted amount moves from the FX
account to the target account within `d`. The FX account carries the
cross-currency exposure — measurable, auditable, never a silent leak.

**Rust**: `fx-kit`'s `revalue` (IAS 21) posting residuals to a named
account; Odoo's exchange-difference journal; TigerBeetle's linked
two-transfer exchange recipe. -/

def conversionEntrySource (fx src : Nat) (c : CurrencyId) (v : Amount) :
    List CPosting :=
  [{ account := src, currency := c, amount := -v },
   { account := fx, currency := c, amount := v }]

def conversionEntryTarget (fx tgt : Nat) (d : CurrencyId) (v' : Amount) :
    List CPosting :=
  [{ account := fx, currency := d, amount := -v' },
   { account := tgt, currency := d, amount := v' }]

/-- Each half of a conversion is balanced in its own currency: the
conversion cannot disturb conservation, whatever the rate or rounding. -/
theorem conversion_source_balanced (fx src : Nat) (c : CurrencyId) (v : Amount) :
    isBalancedIn c (conversionEntrySource fx src c v) := by
  simp [isBalancedIn, amountsIn, conversionEntrySource]
  grind

theorem conversion_target_balanced (fx tgt : Nat) (d : CurrencyId) (v' : Amount) :
    isBalancedIn d (conversionEntryTarget fx tgt d v') := by
  simp [isBalancedIn, amountsIn, conversionEntryTarget]
  grind

/-- **conversion_preserves**: appending any sequence of well-formed
conversion halves to a per-currency-balanced journal keeps it balanced in
every currency of interest. The composite law: per-currency conservation
is inductive under posting *and* conversion. -/
theorem conversion_preserves (cs : List CurrencyId)
    (led convs : List (List CPosting))
    (hb : ∀ c ∈ cs, isBalancedIn c (led.foldr (fun a b => a ++ b) []))
    (hc : ∀ e ∈ convs, ∀ c ∈ cs, isBalancedIn c e) :
    ∀ c ∈ cs, isBalancedIn c
        ((led.foldr (fun a b => a ++ b) []) ++
         (convs.foldr (fun a b => a ++ b) [])) := by
  intro c hc'
  have h1 : ∀ e ∈ convs, isBalancedIn c e := fun e he => hc e he c hc'
  have h2 := trial_balance_currency c convs h1
  have h3 := hb c hc'
  rw [isBalancedIn] at h2 h3 ⊢
  rw [amountsIn_append, List.sum_append, h3, h2]
  simp

/-! ## Section 8: Rounding bounds and sign symmetry (Iteration 5)

Half-up on magnitude is the de-facto VAT norm (Stripe "rounds half up",
DIN 1333 commercial rounding, SAP per-line condition rounding); ISO 4217
fixes only the minor-unit scale, so the mode is policy — but the *error
bound* is mode-robust: every nearest-rounding mode satisfies it. The
theorem below is the one the drift bound (Iteration 6) composes. -/

/-- **Theorem 5.1b (rounding error bound)**: half-up rounding of `n/d`
lands within `d/2` minor units of the exact quotient — two-sided, which
is the form the drift bound composes. Holds for every `n` with `d > 0`
(Euclidean division keeps the remainder in `[0, d)`); the `n ≥ 0`
contract lives in the Rust side, which rounds the magnitude and restores
the sign. -/
theorem roundHalfUp_error (n d : Int) (hd : 0 < d) :
    -(d / 2) ≤ d * roundHalfUp n d - n ∧ d * roundHalfUp n d - n ≤ d / 2 := by
  have hd0 : d ≠ 0 := by omega
  have h2 := Int.emod_nonneg (n + d / 2) hd0
  have h3 := Int.emod_lt_of_pos (n + d / 2) hd
  have h1 := Int.emod_add_mul_ediv (n + d / 2) d
  have hdq : d * ((n + d / 2) / d) = n + d / 2 - (n + d / 2) % d := by
    generalize hm : d * ((n + d / 2) / d) = m at h1 ⊢
    omega
  simp only [roundHalfUp]
  constructor <;> rw [hdq] <;> omega

/-- **Corollary (VAT error bound)**: the VAT leg of a split is the
half-up rounding of `gross · rate / (1000 + rate)` — so it is within
`(1000 + rate) / 2` minor units of the exact product, and `net = gross −
vat` absorbs the difference exactly (Theorem 5.1). -/
theorem vat_error_bound (gross rate : Int) (hr : 0 < 1000 + rate) :
    -((1000 + rate) / 2)
      ≤ (1000 + rate) * (splitVatInclusive gross rate).vat - gross * rate
    ∧ (1000 + rate) * (splitVatInclusive gross rate).vat - gross * rate
      ≤ (1000 + rate) / 2 :=
  roundHalfUp_error (gross * rate) (1000 + rate) hr

/-- `fx_kit::Rate::restate` — round the magnitude half-up, restore the
sign. The definition is the point: magnitude-then-sign is *what makes*
the sign-symmetry theorem true. Applying the raw formula to signed
input breaks it at ties (`(-1 + 1) / 2 = 0 ≠ -1 = -((1 + 1) / 2)` at
`d = 2`). -/
def restate (n d : Int) : Int :=
  Int.sign n * (((n.natAbs : Int) + d / 2) / d)

/-- **Theorem 5.2 (sign symmetry)**: restating a negated amount is the
negation of the restated amount. A signed-toward-zero rounding would
break this at ties; the magnitude-then-sign definition cannot. -/
theorem restate_sign_symmetry (n d : Int) : restate (-n) d = -restate n d := by
  simp only [restate, Int.sign_neg, Int.natAbs_neg]
  rw [Int.neg_mul]

/-! ## Section 9: The drift bound (Iteration 6)

Per-line vs per-document tax allocation (SPEC §5.3). The Euclidean
remainder makes every error *linear*: `d·round(x, d) = x + d/2 − rem`
with `rem = (x + d/2) % d ∈ [0, d)` — so the drift theorem needs no
nonlinear arithmetic at all. -/

theorem sum_map_sub (f g : Int → Int) (l : List Int) :
    (l.map (fun x => f x - g x)).sum = (l.map f).sum - (l.map g).sum := by
  induction l with
  | nil => rfl
  | cons x rest ih => simp only [List.map_cons, List.sum_cons, ih]; grind

/-- The sharp two-sided bound: the scaled error · the value
`2 · (d·round − n)` lies in `[1 − d, d]`. The bottom end is *strictly*
above `−d` in every case (the Euclidean remainder is at most `d − 1`) —
this strictness is what makes the drift bound ⌊n/2⌋ and not ⌈n/2⌉. -/
theorem roundHalfUp_error_sharp (n d : Int) (hd : 0 < d) :
    1 - d ≤ 2 * (d * roundHalfUp n d - n)
    ∧ 2 * (d * roundHalfUp n d - n) ≤ d := by
  have hd0 : d ≠ 0 := by omega
  have h2 := Int.emod_nonneg (n + d / 2) hd0
  have h3 := Int.emod_lt_of_pos (n + d / 2) hd
  have h1 := Int.emod_add_mul_ediv (n + d / 2) d
  have hdq : d * ((n + d / 2) / d) = n + d / 2 - (n + d / 2) % d := by
    generalize hm : d * ((n + d / 2) / d) = m at h1 ⊢
    omega
  simp only [roundHalfUp]
  constructor <;> rw [hdq] <;> omega

/-- The per-line total (round each line, then sum). -/
def perLine (xs : List Int) (d : Int) : Int := (xs.map (fun x => roundHalfUp x d)).sum

/-- The per-document total (sum the lines, then round once). -/
def perDoc (xs : List Int) (d : Int) : Int := roundHalfUp xs.sum d

/-- Rounding zero is zero. -/
theorem roundHalfUp_zero (d : Int) (hd : 0 < d) : roundHalfUp 0 d = 0 := by
  have hd0 : d ≠ 0 := by omega
  have h2 : 0 ≤ d / 2 := by omega
  have h3 : d / 2 < d := by omega
  have h1 : (0 + d / 2) % d + d * ((0 + d / 2) / d) = 0 + d / 2 :=
    Int.emod_add_mul_ediv _ _
  have h5 : d * ((0 + d / 2) / d) = 0 := by
    generalize hm : d * ((0 + d / 2) / d) = m at h1 ⊢
    have h4 : d / 2 % d = d / 2 := Int.emod_eq_of_lt h2 h3
    rw [Int.zero_add, h4] at h1
    omega
  exact (Int.mul_eq_zero.mp h5).resolve_left hd0

/-- Pointwise-bounded lists have bounded sums — the multiplicative step
(`n` terms each `≤ hi` sum to `≤ n·hi`) done **once, generically, at
term level**: omega rejects every fact containing a nonlinear monomial,
so `n·hi` may never appear inside a hypothesis handed to it. -/
theorem sum_bounded (l : List Int) (f : Int → Int) (lo hi : Int)
    (hbound : ∀ x ∈ l, lo ≤ f x ∧ f x ≤ hi) :
    l.length * lo ≤ (l.map f).sum ∧ (l.map f).sum ≤ l.length * hi := by
  induction l with
  | nil => simpa using by constructor <;> omega
  | cons x rest ih =>
    obtain ⟨ih1, ih2⟩ := ih (fun y hy => hbound y (List.mem_cons_of_mem _ hy))
    obtain ⟨hx1, hx2⟩ := hbound x (List.mem_cons_self ..)
    constructor
    · rw [List.length_cons, Int.natCast_add, Int.add_mul, Int.natCast_one, Int.one_mul,
        List.map_cons, List.sum_cons, Int.add_comm (f x) (rest.map f).sum]
      exact Int.add_le_add ih1 hx1
    · rw [List.length_cons, Int.natCast_add, Int.add_mul, Int.natCast_one, Int.one_mul,
        List.map_cons, List.sum_cons, Int.add_comm (f x) (rest.map f).sum]
      exact Int.add_le_add ih2 hx2

theorem sum_bounded_hi (l : List Int) (f : Int → Int) (hi : Int)
    (hbound : ∀ x ∈ l, f x ≤ hi) : (l.map f).sum ≤ l.length * hi := by
  induction l with
  | nil => simp
  | cons x rest ih =>
    have ih1 := ih (fun y hy => hbound y (List.mem_cons_of_mem _ hy))
    have hx2 := hbound x (List.mem_cons_self ..)
    rw [List.length_cons, Int.natCast_add, Int.add_mul, Int.natCast_one, Int.one_mul,
      List.map_cons, List.sum_cons, Int.add_comm (f x) (rest.map f).sum]
    exact Int.add_le_add ih1 hx2

theorem sum_bounded_lo (l : List Int) (f : Int → Int) (lo : Int)
    (hbound : ∀ x ∈ l, lo ≤ f x) : l.length * lo ≤ (l.map f).sum := by
  induction l with
  | nil => simp
  | cons x rest ih =>
    have ih1 := ih (fun y hy => hbound y (List.mem_cons_of_mem _ hy))
    have hx1 := hbound x (List.mem_cons_self ..)
    rw [List.length_cons, Int.natCast_add, Int.add_mul, Int.natCast_one, Int.one_mul,
      List.map_cons, List.sum_cons, Int.add_comm (f x) (rest.map f).sum]
    exact Int.add_le_add ih1 hx1

/-- Scaling a sum: `Σ (c · f x) = c · Σ (f x)`. -/
theorem sum_const_mul (c : Int) (f : Int → Int) (l : List Int) :
    (l.map (fun x => c * f x)).sum = c * (l.map f).sum := by
  induction l with
  | nil => simp
  | cons x rest ih =>
    simp only [List.map_cons, List.sum_cons, ih]
    rw [Int.mul_add]

/-- The scaled per-element rounding error `2·(d·round(x,d) − x)`,
which the sharp bound confines to `[1 − d, d]`. -/
def scaledErr (d : Int) (x : Int) : Int := 2 * (d * roundHalfUp x d - x)

/-- **Theorem 5.3 (drift bound, corrected and tight)**: for `n` lines
over one rate, the per-line and per-document allocations differ by at
most `⌊n/2⌋` minor units:

    2 · |per_line − per_document| ≤ n

Across `k` rates the total drift is at most `k·⌊n/2⌋` — the earlier
`⌈n·k/2⌉` claim overstated by up to `(k−1)/2`. Tightness: two lines each
with an exact `.5` fraction give per-line `2` vs per-document `1`. -/
theorem drift_bound (xs : List Int) (d : Int) (hd : 0 < d) :
    2 * (perLine xs d - perDoc xs d) ≤ xs.length
    ∧ 2 * (perDoc xs d - perLine xs d) ≤ xs.length := by
  have hd0 : d ≠ 0 := by omega
  have hb : ∀ x ∈ xs, scaledErr d x ≤ d := by
    intro x _
    exact (roundHalfUp_error_sharp x d hd).2
  -- per-line side: Σ scaledErr d = 2·(d·perLine − Σx)
  have hlink : (xs.map (scaledErr d)).sum = 2 * (d * perLine xs d - xs.sum) := by
    have h1 : (xs.map (scaledErr d)).sum
        = 2 * ((xs.map (fun x => d * roundHalfUp x d - x)).sum) :=
      sum_const_mul 2 (fun x => d * roundHalfUp x d - x) xs
    have h2 : (xs.map (fun x => d * roundHalfUp x d - x)).sum
        = (xs.map (fun x => d * roundHalfUp x d)).sum - xs.sum := by
      have h := sum_map_sub (fun x => d * roundHalfUp x d) (fun x => x) xs
      simpa using h
    rw [h1, h2, sum_const_mul]
    simp only [perLine]
  -- per-element bound transfers: Σ scaledErr d ≤ n·d
  have hE : (xs.map (scaledErr d)).sum ≤ xs.length * d :=
    sum_bounded_hi xs (scaledErr d) d hb
  -- document side
  have hdoc : 1 - d ≤ 2 * (d * perDoc xs d - xs.sum)
      ∧ 2 * (d * perDoc xs d - xs.sum) ≤ d :=
    roundHalfUp_error_sharp xs.sum d hd
  -- decomposition: d·(2K) = Σerr − 2·docerr
  have hlink' : 2 * (d * perLine xs d)
      = (xs.map (scaledErr d)).sum + 2 * xs.sum := by
    rw [hlink, Int.mul_sub 2 (d * perLine xs d) xs.sum, Int.sub_add_cancel]
  have hsplit : d * (2 * (perLine xs d - perDoc xs d))
      = (xs.map (scaledErr d)).sum - 2 * (d * perDoc xs d - xs.sum) := by
    rw [Int.mul_sub 2 (perLine xs d) (perDoc xs d),
      Int.mul_sub d (2 * perLine xs d) (2 * perDoc xs d),
      Int.mul_left_comm d 2 (perLine xs d),
      Int.mul_left_comm d 2 (perDoc xs d),
      hlink', Int.mul_sub 2 (d * perDoc xs d) xs.sum]
    omega
  -- decomposition for the flipped direction
  have hsplit2 : d * (2 * (perDoc xs d - perLine xs d))
      = 2 * (d * perDoc xs d - xs.sum) - (xs.map (scaledErr d)).sum := by
    have h2 : 2 * (perDoc xs d - perLine xs d)
        = -(2 * (perLine xs d - perDoc xs d)) := by
      rw [Int.mul_sub, Int.mul_sub, Int.neg_sub]
    rw [h2, Int.mul_neg, hsplit, Int.neg_sub]
  constructor
  · refine Classical.byContradiction fun hc => ?_
    have hj : xs.length + 1 ≤ 2 * (perLine xs d - perDoc xs d) := by omega
    have hmul : d * (2 * (perLine xs d - perDoc xs d) - (xs.length + 1))
        = (xs.map (scaledErr d)).sum - 2 * (d * perDoc xs d - xs.sum)
          - d * (xs.length + 1) := by
      rw [Int.mul_sub, hsplit]
    -- term-level combination of the bounds (omega drops monomial facts)
    have hchain : (xs.map (scaledErr d)).sum - 2 * (d * perDoc xs d - xs.sum)
        ≤ xs.length * d - (1 - d) := by
      have h1 := Int.sub_le_sub_right (a := (xs.map (scaledErr d)).sum)
        (b := xs.length * d) (c := 2 * (d * perDoc xs d - xs.sum)) hE
      exact Int.le_trans h1 (Int.sub_le_sub_left hdoc.1 _)
    have hle := Int.sub_le_sub_right hchain (d * (xs.length + 1))
    rw [← hmul, Int.mul_add, Int.mul_comm d xs.length] at hle
    -- hle : d·(2K − (n+1)) ≤ n·d − (1 − d) − (n·d + d) = −1
    have hge : 0 ≤ d * (2 * (perLine xs d - perDoc xs d) - (xs.length + 1)) := by
      rw [Int.mul_sub, Int.sub_nonneg]
      exact (Int.mul_le_mul_left hd).mpr hj
    have hfinal : xs.length * d - (1 - d) - (xs.length * d + d * 1) ≤ -1 := by omega
    exact absurd (Int.le_trans hge (Int.le_trans hle hfinal)) (by omega)
  · refine Classical.byContradiction fun hc => ?_
    have hn1 : 1 ≤ xs.length := by
      cases xs with
      | nil =>
        have h02 : perDoc ([] : List Int) d - perLine ([] : List Int) d = 0 := by
          simp [perLine, perDoc, roundHalfUp_zero d hd]
        have h03 : (2 : Int) * (perDoc ([] : List Int) d - perLine ([] : List Int) d)
            ≤ (([] : List Int).length : Int) :=
          by
          rw [h02, Int.mul_zero]
          omega
        exact absurd h03 hc
      | cons _ _ => simp
    have hj : xs.length + 1 ≤ 2 * (perDoc xs d - perLine xs d) := by omega
    have hmul2 : d * (2 * (perDoc xs d - perLine xs d) - (xs.length + 1))
        = 2 * (d * perDoc xs d - xs.sum) - (xs.map (scaledErr d)).sum
          - d * (xs.length + 1) := by
      rw [Int.mul_sub, hsplit2]
    have hchain2 : 2 * (d * perDoc xs d - xs.sum) - (xs.map (scaledErr d)).sum
        ≤ d - (xs.length - xs.length * d) := by
      have hE1 : xs.length - xs.length * d ≤ (xs.map (scaledErr d)).sum := by
        have h := sum_bounded_lo xs (scaledErr d) (1 - d)
          (fun x _ => (roundHalfUp_error_sharp x d hd).1)
        have h2 : xs.length * (1 - d) = xs.length - xs.length * d := by
          rw [Int.mul_sub, Int.mul_one]
        omega
      have h2 := Int.sub_le_sub_right (a := 2 * (d * perDoc xs d - xs.sum))
        (b := d) (c := (xs.map (scaledErr d)).sum) hdoc.2
      -- h2 : 2·doc − Σerr ≤ d − Σerr;  hE1 : n − n·d ≤ Σerr  (term-level chain)
      have h3 := Int.sub_le_sub_left hE1 d
      -- h3 : d − Σerr ≤ d − (n − n·d)
      exact Int.le_trans h2 h3
    have hle2 := Int.sub_le_sub_right hchain2 (d * (xs.length + 1))
    rw [← hmul2, Int.mul_add, Int.mul_comm d xs.length] at hle2
    -- hle2 : d·(2K' − (n+1)) ≤ d − (n − n·d) − (n·d + d) = −n
    have hge2 : 0 ≤ d * (2 * (perDoc xs d - perLine xs d) - (xs.length + 1)) := by
      rw [Int.mul_sub, Int.sub_nonneg]
      exact (Int.mul_le_mul_left hd).mpr hj
    have hfinal2 : d - (xs.length - xs.length * d) - (xs.length * d + d * 1)
        ≤ -(xs.length : Int) := by omega
    exact absurd (Int.le_trans hge2 (Int.le_trans hle2 hfinal2))
      (by omega)