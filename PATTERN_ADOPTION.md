# PATTERN_ADOPTION

Relationship of accounting-spec to the pattern canon
(WyattAu/pattern-standards). Evidence paths are repo-relative. The
executable oracle (SPEC-CORE SC-6) is `lean/src/Accounting.lean`:
Lean 4 core alone, zero `sorry`, `lake build` type-checks every
theorem; SPEC.md is the human-readable companion.

T26 (bitemporal facts) and P13 (causal horizons) appear in no
definition, theorem, or roadmap entry in this repo, so they are
omitted per adoption-format rule 6.

| Pattern | Status | Evidence |
|---|---|---|
| T27 | adopted | lean/src/Accounting.lean:195 (balanceOf, the per-account fold; append and reversal laws proved; SPEC.md section 2 states the posting monoid) |
| T21 | partial | lean/src/Accounting.lean:213 (balances derive by folding the entry list; reversals append counter-entries and rewrite nothing, SPEC.md:95; append-only/permutation invariance itself is scheduled for It 9) |
| T33 | planned | ITERATIONS.md:362 (It 9: idempotent posting; It 8 landed 2026-11-09, It 9 targets week of 2026-11-23) |
| P11 | adopted | lean/src/Accounting.lean:281 (split_sums_to_gross: allocation conserves the gross and the net absorbs the remainder; SPEC.md:152 bounds per-line vs per-document drift) |
| P12 | adopted | lean/src/Accounting.lean:402 (currencies are dimensions of the algebra; conservation holds per currency and a cross-currency sum is not a term) |
| P83 | adopted | lean/src/Accounting.lean:343 (validChain over the symbolic hash; valid append and tamper localization proved) |
| X4 | adopted | SPEC.md:4 (the Lean oracle is the truth source; every Rust mapping is stated as a theorem correspondence, all machine-proved) |
