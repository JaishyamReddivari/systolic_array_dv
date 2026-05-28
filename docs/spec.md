# Systolic Array Specification — `systolic_array_dv`

**Version:** 0.1 (Draft)
**Author:** Jaishyam Reddy Reddivari
**Status:** Architecture frozen pending Phase 1 HLS implementation

---

## 1. Overview

An 8×8 INT8 matrix-multiply accelerator implemented as a **weight-stationary systolic array** of 64 processing elements (PEs). The block computes `C = A × B` where A and B are INT8 matrices and C is an INT32 matrix. Designed as the canonical compute primitive of an ML inference accelerator (TPU-style microarchitecture).

This document is the contract between the design and the verification environment. Any change to interface, timing, or numerical behavior requires a spec revision.

## 2. Top-Level Parameters

| Parameter      | Value         | Notes                                            |
|----------------|---------------|--------------------------------------------------|
| Array size     | 8 × 8 PEs     | 64 MAC units total                               |
| Operand width  | 8 bits (INT8) | Signed two's complement                          |
| Product width  | 16 bits       | INT8 × INT8 → INT16 (internal to PE)             |
| Accumulator    | 32 bits       | INT32 signed, see 6 for justification            |
| Dataflow       | Weight-stationary | See 3                                        |
| Tile size      | Fixed 8×8     | Larger matmuls handled by software tiling        |
| Clock          | Single, synchronous, positive-edge triggered | Target frequency TBD post-synthesis |
| Reset          | Synchronous, active-high                       | Resets all PE accumulators and FSM state         |

## 3. Dataflow: Weight-Stationary

Operand A (the "weights" by CNN convention) is preloaded into the PE grid. Each PE(i, j) holds `A[i][j]` in a local register for the duration of one compute pass. Operand B (the "activations") streams in from the top edge of the grid, flowing downward through the columns with a staircase skew. Partial sums accumulate within each PE and the final C values are read out at the bottom edge after the compute and drain phases complete.

**Justification:** Weights have the highest reuse factor in typical CNN workloads (each weight is multiplied by activations across many output positions and batch elements), so keeping them stationary in PE registers amortizes the load cost over the maximum number of MAC operations. Weight-stationary also has the simplest control FSM of the major dataflows, which reduces design risk for a first portfolio implementation. This is the TPU v1 pattern.

## 4. Operating Phases

The control FSM cycles through three phases per matmul tile:

| Phase   | Duration  | Description                                                                 |
|---------|-----------|-----------------------------------------------------------------------------|
| LOAD    | 8 cycles  | Operand A shifted into the PE grid one row per cycle from the top edge.     |
| COMPUTE | 8 cycles  | Operand B streamed in with skew; PEs perform MAC; psums propagate downward. |
| DRAIN   | 8 cycles  | Final psums flushed out the bottom edge as C values.                        |

Total cycles per tile: **24** (back-to-back tiles can pipeline LOAD of tile N+1 with DRAIN of tile N — stretch goal for Rev B).

## 5. Interfaces

### 5.1 Interface Summary

| Interface     | Protocol      | Direction | Purpose                          |
|---------------|---------------|-----------|----------------------------------|
| `s_axis_a`    | AXI4-Stream   | Slave     | Operand A (weights) input        |
| `s_axis_b`    | AXI4-Stream   | Slave     | Operand B (activations) input    |
| `m_axis_c`    | AXI4-Stream   | Master    | Operand C (results) output       |
| `s_axi_lite`  | AXI4-Lite     | Slave     | Control / status registers       |
| `clk`         | Clock         | Input     | Single clock domain              |
| `rst`         | Synchronous   | Input     | Active-high reset                |

### 5.2 `s_axis_a` — Weight Input Stream

| Signal     | Width  | Description                                              |
|------------|--------|----------------------------------------------------------|
| `tdata`    | 64     | Eight INT8 values packed (one row of A per beat)         |
| `tvalid`   | 1      | Master asserts when data valid                           |
| `tready`   | 1      | Slave asserts when ready to accept                       |
| `tlast`    | 1      | Asserted on the 8th (final) beat of an A tile            |

**Transaction:** Exactly 8 beats per tile. Beat `i` carries row `i` of A, with `A[i][0]` in `tdata[7:0]`, `A[i][1]` in `tdata[15:8]`, ..., `A[i][7]` in `tdata[63:56]`. `tlast` asserted on beat 7 (zero-indexed).

### 5.3 `s_axis_b` — Activation Input Stream

| Signal     | Width  | Description                                              |
|------------|--------|----------------------------------------------------------|
| `tdata`    | 64     | Eight INT8 values packed (one row of B per beat)         |
| `tvalid`   | 1      | Master asserts when data valid                           |
| `tready`   | 1      | Slave asserts when ready to accept                       |
| `tlast`    | 1      | Asserted on the 8th (final) beat of a B tile             |

**Transaction:** Exactly 8 beats per tile. Beat `k` carries row `k` of B, with `B[k][0]` in `tdata[7:0]` through `B[k][7]` in `tdata[63:56]`. Internal skew logic in the controller staggers the column inputs into the PE grid; the producer does not need to skew externally.

### 5.4 `m_axis_c` — Result Output Stream

| Signal     | Width  | Description                                              |
|------------|--------|----------------------------------------------------------|
| `tdata`    | 256    | Eight INT32 values packed (one row of C per beat)        |
| `tvalid`   | 1      | Master asserts when result valid                         |
| `tready`   | 1      | Slave asserts when ready to accept                       |
| `tlast`    | 1      | Asserted on the 8th (final) beat of a C tile             |

**Transaction:** Exactly 8 beats per tile. Beat `i` carries row `i` of C, with `C[i][0]` in `tdata[31:0]` through `C[i][7]` in `tdata[255:224]`.

### 5.5 `s_axi_lite` — Control / Status Registers

| Offset | Name        | Access | Width | Description                                  |
|--------|-------------|--------|-------|----------------------------------------------|
| 0x00   | `CTRL`      | R/W    | 32    | bit[0] = `start`, bit[1] = `soft_reset`      |
| 0x04   | `STATUS`    | RO     | 32    | bit[0] = `busy`, bit[1] = `done`, bit[2] = `overflow_sticky` |
| 0x08   | `TILE_CNT`  | RO     | 32    | Monotonic count of completed tiles           |
| 0x0C   | `IRQ_EN`    | R/W    | 32    | bit[0] = enable `done` interrupt             |
| 0x10   | `VERSION`   | RO     | 32    | bit[31:16] = major, bit[15:0] = minor        |

Writing `1` to `CTRL.start` initiates a tile. Hardware self-clears `start` after one cycle. `STATUS.done` is sticky and cleared by writing `1` to it (W1C).

## 6. Numerical Behavior

### 6.1 Accumulator Width Justification

Each output `C[i][j]` is the sum of 8 INT8×INT8 products. Worst-case bounds:

- INT8 range: `[-128, +127]`. Worst-case product magnitude: `128 × 128 = 16384` (fits INT16 with one bit of headroom; the product is technically in `[-16384, +16384]`).
- Sum of 8 such products: worst case `8 × 16384 = 131072`, fits comfortably in INT18.

**Decision: 32-bit accumulator.** Reasons:
- Headroom for K > 8 in future revisions where a single PE accumulates across multiple K-tiles.
- Matches industry convention (TPU, NVDLA both use 32-bit accumulators with INT8 operands).
- Negligible area cost at this PE count.
- Simplifies the output stream packing (clean 32-bit alignment in `m_axis_c.tdata`).

### 6.2 Overflow Behavior

For the 8×8 tile case, overflow is mathematically impossible (max value 131072 fits in 18 bits). However, the design includes a sticky `overflow_sticky` status bit that asserts if any psum ever exceeds INT32 range. For Rev A this bit is wired but should remain zero across all valid stimulus; it provides hooks for future K-tiling support and serves as a sanity check on the verification environment (if it ever fires, something is wrong).

### 6.3 Signedness

All operands are **signed two's complement**. INT8 × INT8 signed multiplication is performed; sign extension is propagated through the adder tree into the 32-bit accumulator.

## 7. PE Microarchitecture

Each of the 64 PEs contains:

| Element             | Width  | Description                                              |
|---------------------|--------|----------------------------------------------------------|
| Weight register     | 8 bits | Holds `A[i][j]`, loaded during LOAD phase                |
| Activation pipe reg | 8 bits | Pipeline reg for B value flowing down through column     |
| Multiplier          | 8×8→16 | Signed × signed                                          |
| Adder               | 32-bit | Adds (sign-extended product) + incoming psum             |
| Psum pipe reg       | 32 bits| Holds accumulator state / outgoing psum                  |

**Per-cycle behavior during COMPUTE:**
```
psum_out <= psum_in + (weight_reg * activation_in)
activation_out <= activation_in   // pass downward to next PE
```

**Connectivity:** Each PE has only nearest-neighbor connections (one above, one below — no diagonal or skip connections). This is the canonical "systolic" structure that keeps wiring local and timing closure achievable at high clock rates.

## 8. Verification Implications

Cross-referenced with `docs/vplan.md` (TBD). Quick highlights to keep in mind during RTL development:

- The skew pattern is internal to the controller — the testbench feeds raw row-major data and the DUT handles staggering. Drivers should not assume the testbench needs to model skew.
- Result latency is deterministic: tile complete at exactly `clock_of(CTRL.start)` + 24 cycles, assuming both `s_axis_a` and `s_axis_b` are ready when needed. Backpressure from `m_axis_c.tready = 0` is supported; result is held in output staging registers until accepted.
- The accumulator's 32-bit width relative to the 18-bit mathematical maximum gives the verification environment a clean assertion: `overflow_sticky` must be 0 for all legal stimulus.

## 9. Out of Scope (Rev A)

The following are explicitly *not* in this design and may appear in Rev B:

- K-tiling (K > 8 matmul accumulation across multiple tiles)
- Bias addition or activation functions (ReLU, etc.)
- Sparse weight or activation support
- Variable tile sizes
- Multiple precision modes (e.g., INT4, FP16)
- Power gating or clock gating of idle PEs
- Quantization scale/zero-point parameters (assumes pre-scaled INT8 operands)

## 10. References

- Jouppi et al., "In-Datacenter Performance Analysis of a Tensor Processing Unit," ISCA 2017.
- Chen, Emer, Sze, "Eyeriss: A Spatial Architecture for Energy-Efficient Dataflow for CNNs," ISCA 2016.
- NVDLA Hardware Architectural Specification, https://nvdla.org/hw/v1/hwarch.html.
- AMBA AXI and ACE Protocol Specification (ARM IHI 0022).

## 11. Revision History

| Version | Date       | Author    | Change                            |
|---------|------------|-----------|-----------------------------------|
| 0.1     | 2026-05-28 | Jaishyam  | Initial draft.                    |
