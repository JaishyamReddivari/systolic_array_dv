## Bug #1: Spec dataflow inconsistency — "output from bottom edge" computes wrong function

**Phase found:** Model development (Phase 3, NumPy golden)

**Symptom:** Cycle-accurate simulator implementing the spec's documented
dataflow produced outputs that did not match `A @ B` for any matrix.

**Investigation:** Traced bottom-of-column output for a 2x2 example.
Found that with psums flowing down columns alongside B values, the
bottom psum equals (sum of column weights) × (one B value), not
the dot-product needed for matmul.

**Root cause:** Spec section 3 conflated weight-stationary and
output-stationary dataflow language. In a true weight-stationary
systolic matmul, partial sums must flow PERPENDICULAR to the activation
stream — if B flows down columns, psums must flow right along rows,
and C exits the right edge, not the bottom.

**Fix:** Updated spec section 3 to specify: psums flow rightward,
C exits the right edge of the array.

**Lesson:** Building the cycle-accurate model before RTL caught a
spec inconsistency that would have wasted significant RTL+verification
effort. This validates the "model first, RTL second" methodology.

# Bugs

Defects found during verification of `systolic_array_dv`, with root cause and
fix for each. Both bugs below are in the **testbench / verification
methodology**, not the RTL: no functional RTL bug surfaced under the closed
functional coverage (5 coverpoints + 2 crosses), 97% line coverage, and the
seeded regression. The one spec-level dataflow bug was caught **pre-RTL** by the
reference-model cross-check (see the README "Development Process" section), so
it never reached the DUT and is documented there rather than here.

These are logged because each one passed silently for a while, and the *way*
each was caught is the lesson.

---

## BUG-001 — AXIS driver double-latched every beat

**Severity:** High &nbsp;|&nbsp; **Component:** `axis_driver.drive_tile` &nbsp;|&nbsp; **Status:** Fixed

**Symptom.** `multi_tile_test` hung after tile 1 and timed out. The driver
logged only beats 0–3 accepted on both A and B, then made no further progress.
`top_tile_test` (single tile) appeared to pass.

**Root cause.** `drive_tile` held `tvalid` high while presenting each beat
across *two* clock edges — an extra `@(posedge clk)` at the top of the loop,
with `tvalid` never deasserted between iterations. The controller asserts
`s_axis_*_tready` every cycle in `S_RECV_A` and latches one beat per clock, so
it consumed each row **twice** and filled its 8-deep A/B buffers after only 4
driver beats. At `a_cnt == 8` the FSM left `S_RECV_A` and dropped `tready`; the
driver, still presenting beat 4 with `tvalid` high, spun forever waiting for a
`tready` that never returned. `drive_tile` never returned, so the `fork...join`
in `run_one` never completed — hence the hang.

**Why it hid.** The input monitors sampled the same bus and captured the same
doubled rows, so the scoreboard's golden was computed from the doubled tile
`[r0,r0,r1,r1,...]` and matched the DUT exactly. The single-tile test had been
"passing" on degenerate data, not the random tile it intended to drive.

**Fix.** Present each beat for exactly one cycle: moved the leading
`@(posedge clk)` out of the loop so `tvalid` stays continuously high with one
transfer per clock, matching the DUT's one-beat-per-clock consumption. The same
structure is backpressure-safe — if `tready` is low at the sample edge the beat
is re-presented without a duplicate latch.

**Lesson.** A scoreboard that predicts from *monitored* inputs verifies the
DUT, not the driver — a self-consistent driver bug passes silently. Catching it
requires a separate driver-vs-intended consistency check, or noticing the
second-order symptom (here, the multi-tile hang).

---

## BUG-002 — Phase-objection race produced vacuous passes

**Severity:** High &nbsp;|&nbsp; **Component:** `single_tile_test` / `top_tile_test` `run_phase` &nbsp;|&nbsp; **Status:** Fixed

**Symptom.** Under the seeded regression, `single_tile_test` and
`top_tile_test` reported `checked=0`, finished at time 0 with no drive activity,
yet reported PASS (0 errors, 0 fatals). They were green while verifying nothing.

**Root cause.** Both tests set `env.sb.own_objection = 1` inside their own
`run_phase` and relied on the **scoreboard** to raise the run-phase objection.
But the scoreboard reads `own_objection` at the top of *its* `run_phase`, and
UVM does not order `run_phase` execution across components. The scoreboard ran
first, saw the default `0`, and raised nothing; with no objection held anywhere,
UVM ended the run phase immediately — killing the test while it was still
blocked on `wait(rst == 0)`. The tile was never driven.

**Why it hid.** Classic Heisenbug: phase-execution order happened to favor the
test in the build the original status was written against. A different build and
invocation (the regression runner) flipped the ordering and exposed it.

**Detection.** The regression runner's vacuous-pass guard — a run that passes
but reports `checked == 0` is flagged `PASS*` and counted separately from real
passes. This was the framework's first catch.

**Fix.** The test owns its objection: `phase.raise_objection(this)` as the first
statement of `run_phase` (before any yield), then drive, `wait_trigger` on the
scoreboard's `tile_done_ev`, then `drop_objection`. Removed all reliance on
`own_objection`. `multi_tile_test` was already immune because it owned its
objection and polled STATUS.

**Lesson.** Never configure one component's objection behavior from another
component's `run_phase` — phase order across components is unspecified. A test
should own the objection it depends on. And a green test that checked nothing is
worse than a red one: a regression must distinguish "passed" from "verified."