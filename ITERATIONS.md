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
