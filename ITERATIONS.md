# Iteration Log

The loop: research → analyze → find the cutting edge → check whether
other languages solved it or couldn't → implement in spec → adjust the
Lean proof → repeat.

## Iteration 1 (2026-10-28)

**Research**: TigerBeetle's TIGER_STYLE (assertion density, invariant
checking, compile-time assertions), Cardano's formal ledger specification
(Agda), Lean 4 core vs mathlib capabilities, Verdi's symbolic SHA model,
Aeneas's Rust-to-Lean extraction.

**Analysis**: The core algebra is linear integer arithmetic; exactly
what Lean 4's `omega` tactic proves automatically, so no mathlib is
needed for the subset that matters most. The theorems that need more
(per-line rounding accumulation, sign symmetry under `Int.ediv`) are
stated with `sorry` and documented as requiring mathlib in a future
iteration.

**Finding**: The estate's money representation (integer minor units)
gives the formalization a structural advantage over Odoo's float-based
model: the canonical serialization is deterministic without Odoo's
`float_repr` stabilization, and the proofs are about `Int` (which Lean
proves natively) rather than about `Float` (which requires IEEE 754
formalization).

**Spec**: Created SPEC.md with the posting algebra (Section 2), the
balance conservation theorem (Section 3), reversal cancellation
(Section 4), rounding (Section 5), and the hash chain (Section 6).
Mapping to Rust crates documented at each section.

**Lean proof**: `split_sums_to_gross` proven (the definition makes it a
tautology; the point). `reversal_cancels`, `posting_sum_append`,
`reversal_sum_negates`, and `trial_balance` stated with `sorry` (they
need mathlib's `ring` for integer list arithmetic). Three `sorry`s,
each documented with what it needs and why.

**Next**: Add mathlib (or `ric`/`Linarith` subset) to close the `sorry`
gap; model the hash chain symbolically; extract from Rust with Aeneas.

## Iteration 2 (2026-10-31)

**Research**: Lean 4's `omega` tactic (Pugh's omega test, in core since
4.x — linear integer arithmetic incl. division by constants), the new
`grind`/`lia` decision procedure in 4.35 (Cooper-style LIA with
divisibility), core list lemmas (`List.sum_append`, `List.map_map`,
`Function.comp_apply`), and the repo's own build system.

**Analysis — two process defects found, not proof defects**:
1. **`lake build` verified nothing.** The lakefile declared no library
   target, so CI's build step was a no-op ("no targets specified"). The
   four `sorry`s were visible only because someone ran `lake env lean`
   by hand. Fixed: `lean_lib` target + `defaultTargets` declared; a push
   now type-checks every proof.
2. **Iteration 1's "needs mathlib" claim was never tested.** Ran the
   goal shapes empirically: `omega` refuses them — not because they are
   hard, but because its frontend type-sniffs operands and rejects
   terms typed through the `Amount`/`Posting` abbrevs ("no usable
   constraints", identical on 4.29 and 4.35). The tactic that closes
   them is 4.35's `grind` (integrated `lia`), which lacks the abbrev
   strictness. Mathlib remains unnecessary. Language check: Coq/Agda
   need stdlib imports for the same results; Lean 4.35 core is
   self-sufficient here — keep the zero-dependency posture.

**Spec**: Added `reversal_involution` — SPEC §4's title claimed reversal
is an involution but no theorem stated it. Also strengthened the
`reversal_cancels` note: the proof shows cancellation is unconditional
(balancedness hypothesis unused) — kept in the signature for fidelity.

**Lean proof**: All four `sorry`s closed: `posting_sum_append` (core
`List.sum_append`), `reversal_sum_negates` (new helper `sum_map_neg` +
induction + `grind`), `reversal_cancels` (rewrite chain + `grind`),
`trial_balance` (induction + rewrite chain + `grind`). Plus
`reversal_involution` (`Int.neg_neg`). Zero `sorry`s, zero warnings,
`lake build` green. Proof-engineering notes recorded in the file header
(`simp`/`rw` ordering vs definition unfolding; `omega`'s abbrev
strictness; deterministic `rfl`+`rw` beats fragile `simp` composition
for the involution).

**Next**: the account dimension (SPEC §3 cannot be *stated* —
`Posting := Amount` erases it), multi-currency conservation, rounding
error bounds, symbolic hash chain.
