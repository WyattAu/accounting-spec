# Changelog

## [Unreleased]

### Iteration 4

- SPEC §8: the currency view — per-currency conservation, the coverage
  trial balance over a `NoDup` chart, and well-formed conversion
  entries (every residual has an account).
- Lean: `trial_balance_currency`, `trial_balance_coverage`,
  `reversal_cancels_in`, `conversion_source_balanced`,
  `conversion_target_balanced`, `conversion_preserves`; zero sorries,
  zero dependencies.

### Iteration 6

- SPEC §5.3 corrected: the drift bound is `2·|per_line − per_doc| ≤ n`
  per rate (`k·⌊n/2⌋` across `k` rates), replacing the loose
  `⌈n·k/2⌉`.
- Lean: `roundHalfUp_error_sharp`, `sum_bounded`(+hi/lo),
  `sum_const_mul`, `sum_map_sub`, `perLine`/`perDoc`, `drift_bound`;
  zero sorries.

### Iteration 5

- SPEC §5: Theorem 5.1b (two-sided rounding error bound, mode-robust),
  the VAT-error corollary, and the restatement definition behind 5.2.
- Lean: `roundHalfUp_error`, `vat_error_bound`, `restate`,
  `restate_sign_symmetry`; zero sorries, zero dependencies.

## [0.1.0] - 2026-10-28

Initial release: the formal specification (SPEC.md) and Lean 4 proofs for
the accounting estate's core algebra.

### Added

- SPEC.md: the posting algebra, balance conservation, reversal
  cancellation, rounding, and hash chain; with Rust mappings at each
  section.
- Lean 4 proofs: `split_sums_to_gross` proven with core Lean 4 (no
  mathlib); `reversal_cancels`, `reversal_sum_negates`,
  `posting_sum_append`, and `trial_balance` stated with documented
  `sorry` (need mathlib's `ring` for integer list arithmetic).
- ITERATIONS.md: the research loop log.
