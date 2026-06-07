# Verification Plan — systolic_array_dv

**DUT:** `systolic_top` — 8×8 INT8 weight-stationary matmul accelerator.
**Interfaces:** AXI4-Stream (A, B in; C out), AXI4-Lite (control/status).
**Method:** UVM environment, self-checking against an SV behavioral golden
reference in the scoreboard, cross-validated against three independent offline
models.

---

## 1. Objective

Prove that `systolic_top` computes `C = A × B` correctly for all valid INT8
inputs, obeys the AXI4-Stream and AXI4-Lite protocols, and handles control,
backpressure, and abort correctly — to a curated functional-coverage bar of
95% (achieved 100%), backed by code coverage.

The scoreboard reference is an SV behavioral golden that re-implements the
INT8 matmul and predicts C from the *monitored* A and B tiles. The same matmul
algorithm is independently proven offline by three references that agree —
the NumPy behavioral golden, the cycle-accurate simulator, and the C++
`matmul_int8`. Because those references agree, a scoreboard mismatch isolates
to the RTL rather than to an ambiguous reference. Importing the C++ model
directly into the scoreboard via DPI-C is planned future work (see §7); the SV
golden is the live reference today.

## 2. Feature / Risk / Coverage Matrix

| # | Feature | Risk | Check | Coverage — closed when |
|---|---------|------|-------|------------------------|
| 1 | Functional correctness | C ≠ A×B | Scoreboard vs SV golden, random | CP1, CP2, Cross1 hit; 0 mismatches across regression |
| 2 | INT8 signed arithmetic | Sign error at extremes | Directed corners (±128, 0) + random | CP1 `max_pos`/`max_neg`/`negative`; Cross1 corner cells (neg×neg, max×max) |
| 3 | AXI4-Stream A/B input | Dropped/duplicated beats, protocol violation | Input monitors + scoreboard | Protocol-clean across all tiles; CP1 sampled on every element |
| 4 | AXI4-Stream C output | Wrong beat order, bad TLAST | Output monitor + scoreboard | Protocol/TLAST-clean; CP2 hit; CP3 `stall_at_last_beat` |
| 5 | Output backpressure | Data lost when consumer stalls | Randomized TREADY delays (C responder) | CP3 all bins hit |
| 6 | AXI4-Lite CSR | Wrong read/write, W1C, start semantics | Directed register tests | CP5 read/write/`W1C_clear` bins hit |
| 7 | start/busy/done handshake | Re-trigger, missed done, race | Directed + random tile spacing | CP4 hit; formal FSM-phase `cover`s reachable |
| 8 | start-while-busy (defensive) | Spurious start corrupts running tile | Directed: write start while busy; confirm tile undisturbed + `tile_cnt` unchanged | CP5 `start_while_busy` (ignored path) bin |
| 9 | soft_reset / abort | Doesn't flush, leaves stale state | Abort under continuous feed | CP4 `abort_mid_tile` + CP5 `soft_reset_issued` |
| 10 | Back-to-back tiles | Tile N corrupts tile N+1 | Random multi-tile sequences | CP4 `back_to_back` + Cross2 |
| 11 | tile_cnt | Miscount | Multi-tile, read & check via CSR | CP5 `TILE_CNT` read; value matches tiles issued |

## 3. Checking Strategy

Three independent checks across the scoreboard and monitors:

1. **End-of-tile data compare** — collect full A and B tiles from the input
   monitors, predict C via the SV golden matmul, compare against the C tile
   from the output monitor.
2. **Latency window** — assert each tile completes within the expected cycle
   budget (load + compute + drain + handshake overhead).
3. **AXI4-Stream protocol checks** — monitors flag valid/ready rule violations
   and TLAST placement independently of data correctness.

## 4. Coverage Model

### 4.1 Functional coverage (primary metric — target ≥ 95%, achieved 100%)

The model is specified as curated covergroup-style bins: unreachable / illegal
combinations are excluded (the `ignore_bins` / `illegal_bins` intent) so the
percentage reflects meaningful coverage, not padding. Because Verilator has no
covergroup support, the bins are implemented as manual hit-counters that
preserve the same semantics — including the excluded combinations. (This is
called out as a tooling limitation in §4.2 and the README.)

**CP1 — operand value range** (sampled per A and per B element):
`negative` (−128..−1), `zero`, `positive` (1..127), `max_pos` (127),
`max_neg` (−128).

**CP2 — result magnitude (C):**
`zero`, `small`, `large`, `near_max` (close to the worst-case bound).

**CP3 — output backpressure:**
`no_stall`, `stall_1cyc`, `stall_multi`, `stall_at_first_beat`,
`stall_at_last_beat`.

**CP4 — tile spacing / sequencing:**
`back_to_back`, `gap`, `abort_mid_tile`.

**CP5 — CSR access:**
each register read, each writable register written, `W1C_clear`,
`start_while_busy` (ignored path), `soft_reset_issued`.

**Crosses:**
- `CP1.A_range × CP1.B_range` — the high-value cross: confirms arithmetic
  corners compound correctly (negative×negative, max×max, zero×anything).
- `CP3.backpressure × CP4.tile_spacing` — backpressure during back-to-back vs
  isolated tiles. (Secondary; stretch bins.)

### 4.2 Code coverage (secondary metric — via Verilator `--coverage`)

Instrumentation is restricted to the DUT RTL (UVM, the UVM package, the
testbenches, and the interfaces are excluded via `coverage.vlt`).

- **Line** — every RTL line executed.
- **Branch / expression** — every case arm and decision exercised.
- **Toggle** — every signal bit toggles 0→1 and 1→0.
- **FSM** — Verilator does not auto-extract FSM state/transition coverage on
  this design, so **case-arm branch coverage on the state machine** stands in
  for it; every legal state arm is shown taken. (No covergroup is used —
  Verilator lacks the feature.)

Functional coverage answers "did I test what matters"; code coverage answers
"did I leave any RTL untouched." Both are required for closure. Legitimately
rare lines (default case arms, reset values, the `ifndef SYNTHESIS` block,
constant `bresp`/`rresp`, the tied-off overflow path) are investigated and
**waived with rationale** rather than forced to a hard percentage.

## 5. Stimulus Scenarios (sequence library)

1. **Random tiles** — randomized INT8 A, B; the workhorse correctness test.
2. **INT8 corners** — directed ±128, zero, mixed-sign tiles.
3. **Back-to-back tiles** — no idle between tiles; checks no cross-tile
   contamination.
4. **Output backpressure** — randomized TREADY stalls, including first/last beat.
5. **CSR register tests** — read/write all registers, W1C, start-while-busy,
   soft_reset.
6. **Abort under load** — continuous tile feeding interrupted by an abrupt
   soft_reset; checks clean flush and recovery. Inputs are fully driven before
   the abort so the monitors and scoreboard stay synchronized.

## 6. Assertions (formal track)

SVA-style assertions targeting the **control plane** (controller FSM, counter
bounds, handshake legality) are authored in `controller.sv` under
`` `ifdef FORMAL ``:

- `assert` properties — invariants intended to be proven to hold exhaustively
  (e.g. legal state at all times, counter bounds, entering COMPUTE implies B
  fully received).
- `cover` properties — every FSM phase proven reachable, guarding against
  vacuous / dead assertions.

**Status:** properties are authored; exhaustive proof is **deferred** because
the local open-source flow lacks a SystemVerilog-capable yosys frontend (the
native frontend can't parse the SV; sv2v converts the RTL but strips the
assertions). The proper path is a yosys with `read_systemverilog`
(OSS CAD Suite); this is recorded as the formal track's open item.

The datapath (64 MACs) is deliberately out of scope for formal — intractable
for a solver and already covered dynamically. Formal proof of assertions is
stronger than simulation-based assertion stimulus, which is also why no
error-injection sequence is used (and there is no error-detection feature to
inject against — see §7).

## 7. Out of Scope (future work)

Explicitly not verified, because the corresponding features are not in the
current design scope:

- **Autonomous error detection** — the DUT uses software-commanded abort
  (`soft_reset`), not hardware error detection. With no error-detection feature
  to test, an error-injection sequence would have nothing meaningful to verify;
  adding such a feature was deliberately declined to keep scope tight and every
  claimed feature fully verified.
- **K-tiling, bias/activation, multiple precisions, sparsity** — not in the
  datapath.
- **Mid-stream input backpressure recovery** — backpressure is handled at tile
  granularity; a producer stalling mid-tile and resuming is not exercised.
- **Overflow detection** — mathematically impossible for the 8×8 INT8 case;
  the status bit is tied off.
- **DPI-C scoreboard reference** — the SV golden is the live reference;
  importing the proven C++ `matmul_int8` directly as a parallel DPI-C reference
  is planned future work.

## 8. Environment Architecture

```
uvm_test
└── env
    ├── axis_agent (A)      driver + sequencer + monitor
    ├── axis_agent (B)      driver + sequencer + monitor
    ├── axis_agent (C)      monitor + TREADY responder (backpressure)
    ├── axil_agent (CSR)    driver + sequencer + monitor
    ├── scoreboard          A,B in → SV golden matmul_int8 → compare to C
    └── coverage collector  samples transactions into the model above
virtual sequence orchestrates: CSR start → drive A,B → read C → poll status
```

Reuses the agent/driver/monitor/scoreboard structure from the prior
`AXI_RAM_Verification` UVM environment; the AXI4-Lite agent adapts that
full-AXI4 environment to Lite-style single transfers. The AXIS driver settled
on direct-signal driving (rather than a clocking block) after debugging a
clocking-skew/double-latch issue — see `bugs.md`.

## 9. Closure Criteria

| Criterion | Target | Status |
|-----------|--------|--------|
| All 11 features checked, passing | 11/11 | ✓ |
| Functional coverage on the curated bin set | ≥ 95% | ✓ 100% (CP1–CP5, Cross1, Cross2) |
| Code coverage gaps investigated and explained | all waived w/ rationale | ✓ line 97.1%, branch 93.8%, expr 94.3%, toggle 92.1% |
| All 6 scenarios passing across multi-seed regression | clean | ✓ 15/15 (3 tests × 5 seeds), vacuous = 0; multi-tile 36/36 checked, 0 mismatches |
| Control-plane assertions | proven in formal | ◐ authored; proof deferred (SV-frontend toolchain — §6) |