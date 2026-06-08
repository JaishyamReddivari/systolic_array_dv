# Regression Report — `systolic_array_dv`

**Simulator:** Verilator 5.048  ·  **Methodology:** UVM 1.2  ·  **Runner:** pure-stdlib Python (`tb/uvm/regression/regress.py`)

Multi-seed regression of the 8×8 INT8 weight-stationary systolic-array accelerator across the three UVM tests, with functional + code coverage and a self-checking scoreboard. Raw per-seed data: [`regression_report.json`](regression_report.json).

## Headline

| Metric | Result |
| --- | --- |
| Total runs | **1,500** (3 tests × 500 seeds) |
| Pass / fail | **1,500 / 0** |
| UVM errors / fatals | **0 / 0** |
| Scoreboard comparisons | **19,000**, **0 mismatches** |
| Merged functional coverage | **100%** |
| Line coverage | **97.1%** (33/34) |
| Vacuous passes | **0** (guarded) |

## Per-test

| Test | Seeds | Pass | Fail | Scoreboard checks | Mismatches |
| --- | --- | --- | --- | --- | --- |
| `single_tile_test` | 500 | 500 | 0 | 500 | 0 |
| `top_tile_test` | 500 | 500 | 0 | 500 | 0 |
| `multi_tile_test` | 500 | 500 | 0 | 18,000 | 0 |
| **Total** | **1,500** | **1,500** | **0** | **19,000** | **0** |

## Functional coverage (merged across the regression)

| Coverpoint | % | Coverpoint | % |
| --- | --- | --- | --- |
| CP1_A — A operand range | 100 | CP4_SP — tile spacing | 100 |
| CP1_B — B operand range | 100 | CP5_CSR — CSR access | 100 |
| CP2_C — result magnitude | 100 | cross — A range × B range | 100 |
| CP3_BP — output backpressure | 100 | cross2 — backpressure × spacing | 100 |

Functional coverage is **merged** across seeds: a single seed exercises only part of the bin space, and closure is cumulative over the regression — which is the reason for running 500 seeds per test.

## Code coverage (DUT RTL)

| Metric | % | Hit / Total |
| --- | --- | --- |
| Line | 97.1 | 33 / 34 |
| Branch | 93.8 | 60 / 64 |
| Expression | 94.3 | 33 / 35 |
| Toggle | 92.1 | 3849 / 4178 |

FSM state/transition coverage is not auto-extracted by Verilator on this design; case-arm branch coverage stands in for it. Remaining line/branch/expr/toggle gaps are waived with rationale (see `README.md` and `verification_plan.md`).

## Reproduce

```bash
cd tb/uvm
python3 regression/regress.py        # 3 tests × 500 seeds
```

## Notes

Per-run warning counts of 54 (controller binaries) and 74 (top) are the benign `UVM/COMP/NAME` notices emitted under the required `+define+UVM_NO_DPI`. They are elaboration-only and filtered from normal output — documented, not suppressed.
