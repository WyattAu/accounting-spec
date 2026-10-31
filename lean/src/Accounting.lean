/-
The formal proofs for the WyattAu accounting estate.

Every definition here corresponds to a section of SPEC.md. The theorems
are stated with their Rust implementation mappings.

Iteration 2 status: ZERO `sorry`s. Every stated theorem is machine-proved
with Lean 4 core alone — no mathlib dependency.

Iteration 2 findings, for the record:
- Iteration 1 believed the conservation theorems needed mathlib's `ring`.
  Wrong twice over. First, `postingSum` unfolds to `List.sum` (a `foldr`
  over `+`), and the list lemmas live in core (`List.sum_append`,
  `List.map_map`); the residual arithmetic is linear — `omega`'s domain in
  principle. Second, in practice `omega` REJECTS these goals outright:
  its frontend type-sniffs operands and refuses terms whose type is an
  `abbrev` (`Posting`/`Amount`), not syntactically `Int` — "no usable
  constraints", on 4.29 as well as 4.35. The tactic that actually closes
  them is 4.35's `grind` (with its integrated `lia` decision procedure),
  which does not have the abbrev strictness. Lesson recorded: the claim
  "needs mathlib" was never tested against the real goal shapes.
- `lake build` previously declared no library target, so CI verified
  nothing. The lakefile now declares the `Accounting` lib; every push
  type-checks every proof.

Axioms of trust:
- `Int` arithmetic is correct (Lean 4 core, which is self-hosted).
- SHA-256's collision resistance is a trusted assumption (Section 6).
- The mapping to the Rust implementation is by review, not by extraction
  (see ITERATIONS.md for the extraction roadmap).
-/

/-! ## Section 1: Money amounts are integers -/

/-- An amount is an integer in minor units. -/
abbrev Amount := Int

/-! ## Section 2: The posting algebra -/

/-- For the conservation proofs, a posting is a signed amount: debit
positive, credit negative. The account assignment is a labelling that
does not affect whether debits equal credits.

Iteration 2 note: this erasure is *deliberate* for the conservation
theorems — but it means SPEC §3's per-account trial balance cannot be
stated at this layer. The account-carrying model arrives in Iteration 3
(see ITERATIONS.md). -/
abbrev Posting := Amount

/-- The signed sum of a list of postings. -/
def postingSum (ps : List Posting) : Amount := ps.sum

/-- A list of postings is balanced when its signed amounts sum to zero. -/
def isBalanced (ps : List Posting) : Prop := postingSum ps = 0

/-- The reversal of a posting negates its amount. -/
def reversePosting (p : Posting) : Posting := -p

/-- The reversal of a list of postings negates every posting. -/
def reverseAll (ps : List Posting) : List Posting := ps.map reversePosting

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

/-! ## Section 4: The conservation theorems (all machine-proved) -/

/-- **Helper** (`sum_map_neg`): the sum of negated postings is the negated
sum. Stated over raw list operations so induction + `grind` close it; the
`reverseAll` theorem is a one-line corollary. -/
theorem sum_map_neg (ps : List Posting) :
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
theorem posting_sum_append (a b : List Posting) :
    postingSum (a ++ b) = postingSum a + postingSum b := by
  simp [postingSum, List.sum_append]

/-- **reversal_sum_negates**: The sum of the reversal is the negation of
the sum of the original.

    ∀ ps, postingSum (reverseAll ps) = -(postingSum ps)

**Rust**: `double_entry`'s and `ledger-pg`'s reversal. -/
theorem reversal_sum_negates (ps : List Posting) :
    postingSum (reverseAll ps) = -(postingSum ps) := by
  simp only [reverseAll, postingSum]
  exact sum_map_neg ps

/-- **reversal_cancels**: An entry plus its reversal is balanced: the
cancellation is exact, to the minor unit, with no residual.

    ∀ ps, isBalanced ps → isBalanced (ps ++ reverseAll ps)

**Rust**: `double_entry`'s `reverse()` and `ledger-pg`'s `reverse()`.
0.2.0's double-flip (counter with the original's sides) violated this
theorem and was caught by the chain tests plus the balance assertion. -/
theorem reversal_cancels (ps : List Posting) (_h : isBalanced ps) :
    isBalanced (ps ++ reverseAll ps) := by
  -- Stronger than stated: the cancellation holds for EVERY ps — the
  -- balancedness hypothesis is not needed. Kept in the signature for
  -- SPEC §4 fidelity.
  rw [isBalanced, posting_sum_append, reversal_sum_negates]
  grind

/-- **trial_balance**: The trial balance's check must always pass on a
ledger whose every entry was posted through the balanced gate.

    ∀ pss, (∀ ps ∈ pss, isBalanced ps) →
             isBalanced (pss.foldr (fun a b => a ++ b) [])

**Rust**: `report-kit`'s `TrialBalance::is_balanced()`. The theorem says
the check is not discovering something about the ledger — it is confirming
a property the post-time gate already guaranteed. -/
theorem trial_balance (pss : List (List Posting))
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

    ∀ ps, reverseAll (reverseAll ps) = ps

**Rust**: reversing a reversal must reproduce the original entry
(`double_entry`'s round-trip test). -/
theorem reversePosting_idempotent (p : Posting) :
    reversePosting (reversePosting p) = p := Int.neg_neg p

theorem reversal_involution (ps : List Posting) :
    reverseAll (reverseAll ps) = ps := by
  induction ps with
  | nil => rfl
  | cons x xs ih =>
    have h : reverseAll (reverseAll (x :: xs)) =
        reversePosting (reversePosting x) :: reverseAll (reverseAll xs) := rfl
    rw [h, ih, reversePosting_idempotent]

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

/-- **Theorem (nil_balanced)**: The empty posting list is balanced.
Definitional. -/
theorem nil_balanced : isBalanced [] := rfl

/-! ## Section 6: The hash chain (symbolic model — Iteration 7) -/

/-- **Theorem (tamper detection)**: If any entry in a committed hash chain
is altered, the recomputed hash at that position differs from the stored
hash. Conditional on SHA-256's collision resistance. The symbolic-hash
axiomatisation that turns this from `True := trivial` into a real proof is
Iteration 7's deliverable (see ITERATIONS.md). -/
theorem tamper_detection_conditional : True := trivial
