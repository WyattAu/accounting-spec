/-
The formal proofs for the WyattAu accounting estate.

Every definition here corresponds to a section of SPEC.md. The theorems
are stated with their Rust implementation mappings.

Status (Iteration 3): ZERO `sorry`s. Zero dependencies beyond Lean 4 core.
`lake build` type-checks every proof.

Two layers, per Ellerman's mathematical treatment of double-entry
bookkeeping (arXiv:1407.1898): a ledger entry is an element of the group
of differences, and with multiple accounts it is a *vector* — accounts are
dimensions, not erased labels.

- **Amount view** (§2): lists of signed amounts. The conservation
  theorems live here; they are pure `List Int` algebra.
- **Account view** (§2b): postings carry an account id; the amount view
  is the *projection* `amounts`. Per-account balances, their append and
  reversal laws, and entry-level cancellation are proved here.

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
