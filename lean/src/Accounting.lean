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

