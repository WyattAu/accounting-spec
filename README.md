# accounting-spec

The formal specification and machine-checked proofs for the WyattAu
accounting estate.

## Why

The correctness brand has been enforced by property tests (round 39) and
spec-cited worked examples. A machine-checked proof is stronger: the
properties hold **for all inputs by construction**, not for the ones the
tests sampled. No accounting-software vendor does this. TigerBeetle
advocates assertion density; Cardano formalized its ledger in Agda. This is
the estate's answer: the same rigour in Lean 4, because the core algebra is
linear integer arithmetic; exactly what Lean 4's `omega` tactic proves
automatically, so the proofs cost nothing to maintain and cannot rot.

## The iteration loop

Each round: **research → analyze → find the cutting edge → check whether
other languages solved it or couldn't → implement in spec → adjust the Lean
proof → repeat.** The loop log is in `ITERATIONS.md`.

## Structure

- [`SPEC.md`](SPEC.md); the formal specification: the algebra, the
  invariants, and the mapping to the Rust implementation
- [`lean/`](lean/); Lean 4 proofs (no mathlib; core Lean 4 + `omega`)
- `ITERATIONS.md`; the loop log

## Verifying

```sh
cd lean
lean src/Accounting.lean
```

No output means every proof checked. Any `error:` means a theorem is false ;
which means a crate is wrong.

## Licence

MIT OR Apache-2.0.

## Where the truth lives

| Concern | File |
|---|---|
| Formal spec (normative) | `SPEC.md` |
| Lean proofs (executable oracle) | `lean/src/Accounting.lean` |
| Research loop log | `ITERATIONS.md` |
| Release notes | `CHANGELOG.md` |
