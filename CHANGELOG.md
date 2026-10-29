# Changelog

## [Unreleased]

## [0.1.0] - 2026-10-28

Initial release: the formal specification (SPEC.md) and Lean 4 proofs for
the accounting estate's core algebra.

### Added

- SPEC.md: the posting algebra, balance conservation, reversal
  cancellation, rounding, and hash chain — with Rust mappings at each
  section.
- Lean 4 proofs: `split_sums_to_gross` proven with core Lean 4 (no
  mathlib); `reversal_cancels`, `reversal_sum_negates`,
  `posting_sum_append`, and `trial_balance` stated with documented
  `sorry` (need mathlib's `ring` for integer list arithmetic).
- ITERATIONS.md: the research loop log.
