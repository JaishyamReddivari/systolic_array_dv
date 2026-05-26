# systolic_array_dv

**INT8 systolic-array matrix-multiply accelerator — HLS-generated RTL, verified with UVM, formal, and back-annotated gate-level simulation.**

> Status: 🚧 Work in progress. See [Roadmap](#roadmap) for current phase.

---

## 1. Project Intent

This repository is a complete verification environment for a small INT8 systolic-array MAC engine — the kind of compute primitive that sits at the heart of NPUs and ML accelerators (TPU, NVDLA, Apple ANE).

The design itself is intentionally small. The point of the project is the **verification flow**, not the accelerator. Specifically, it demonstrates:

- A modern UVM testbench with constrained-random stimulus, functional coverage, and SVA assertions.
- A **C++ reference model imported via DPI-C** and an independent **NumPy golden model** for cross-checking.
- **Formal property verification** with SymbiYosys on the control logic.
- **Gate-level simulation with SDF back-annotation** to catch timing-sensitive bugs that RTL sim misses.
- An **HLS-to-RTL** path (Vitis HLS C++ → Verilog) so the same algorithmic source is the spec, the reference, and the DUT origin.


## 2. Architecture

### 2.1 DUT — Systolic Array MAC Engine

| Parameter         | Value                                |
|-------------------|--------------------------------------|
| Array dimensions  | `N × N` PEs (default `N = 8`) *TBD*  |
| Datatype          | INT8 × INT8 → INT32 accumulate       |
| Dataflow          | Weight-stationary *(TBD: vs output-stationary)* |
| Interface         | AXI4-Stream in / AXI4-Stream out     |
| Control           | AXI4-Lite CSR block (start, status, dims) |
| Pipeline depth    | `N + N - 1` cycles per tile          |

```
              ┌─────────────────────────────────────────┐
              │            AXI4-Lite CSR                │
              │  (start, status, M/N/K, base addrs)     │
              └────────────┬────────────────────────────┘
                           │
  AXI4-Stream A  ────►  ┌──┴────────────────────────┐  ────► AXI4-Stream C
  (activations)         │                           │       (results)
                        │   N × N PE grid           │
  AXI4-Stream B  ────►  │   (INT8 MAC, skew regs)   │
  (weights)             │                           │
                        └───────────────────────────┘
```

### 2.2 Design Source Flow

```
  Vitis HLS C++  ──►  Synthesized Verilog (DUT)
       │
       └────────────►  C++ behavioral reference (compiled into DPI-C lib)
```

Both the synthesizable RTL and the untimed C++ reference are generated from the same algorithmic description. A second independent reference is written in NumPy to catch errors that might be common to the HLS C++ source.

### 2.3 Verification Environment

```
            ┌──────────────────────────────────────────────┐
            │                UVM Testbench                 │
            │                                              │
            │   ┌──────────┐   ┌──────────┐   ┌─────────┐  │
            │   │  Driver  │   │ Monitor  │   │Sequencer│  │
            │   │  (AXIS)  │   │  (AXIS)  │   │         │  │
            │   └────┬─────┘   └────┬─────┘   └─────────┘  │
            │        │              │                      │
            │        ▼              ▼                      │
            │     ┌──────────────────────┐   ┌──────────┐  │
            │     │      DUT (RTL)       │──►│Scoreboard│  │
            │     └──────────────────────┘   │          │  │
            │                                │ ◄── DPI-C│  │
            │                                │   C++ ref│  │
            │                                └──────────┘  │
            └──────────────────────────────────────────────┘
                              │
                              ▼
                  ┌────────────────────────┐
                  │ NumPy golden model     │
                  │ (offline cross-check)  │
                  └────────────────────────┘
```

Independent verification axes:

| Axis                 | Tool / Technique                              | What it catches                          |
|----------------------|-----------------------------------------------|------------------------------------------|
| Dynamic, RTL         | UVM + constrained-random + functional coverage| Functional bugs across the input space   |
| Reference comparison | DPI-C C++ + NumPy                             | Spec-vs-RTL divergence                   |
| Assertions           | SVA (concurrent + immediate)                  | Protocol violations, internal invariants |
| Formal               | SymbiYosys + SBY scripts                      | Control FSM correctness, deadlock freedom|
| Gate-level           | Post-synth netlist + SDF back-annotation      | X-propagation, hold/setup-sensitive bugs |

## 3. Target Deliverables

By the time this repo is complete, it will contain:

- [ ] Synthesizable RTL for the `N × N` INT8 systolic array, generated from Vitis HLS.
- [ ] AXI4-Stream and AXI4-Lite UVM agents (reusable, parameterized).
- [ ] UVM environment with virtual sequencer, scoreboard, and config DB plumbing.
- [ ] DPI-C C++ reference model linked into the testbench.
- [ ] Standalone NumPy golden model with a published reference vector set.
- [ ] Functional coverage model with target ≥ 95% closure.
- [ ] ≥ 20 SVA assertions covering AXI handshake and internal invariants.
- [ ] SymbiYosys formal flow targeting the CSR + control FSM, with `prove` and `cover` modes.
- [ ] Gate-level simulation script with SDF back-annotation against a synthesized netlist.
- [ ] GitHub Actions CI: lint → smoke test → regression → coverage report.
- [ ] Verification plan (`docs/vplan.md`) and bug log (`docs/bugs.md`).

## 4. Repository Layout *(planned)*

```
systolic_array_dv/
├── README.md
├── docs/
│   ├── vplan.md              # Verification plan
│   ├── arch.md               # Microarchitecture notes
│   └── bugs.md               # Running bug log (real engineers keep these)
├── hls/
│   ├── src/                  # Vitis HLS C++ source
│   └── tcl/                  # HLS synthesis scripts
├── rtl/                      # Generated + hand-written Verilog
├── tb/
│   ├── agents/               # AXIS, AXI-Lite UVM agents
│   ├── env/                  # UVM env, scoreboard, coverage
│   ├── tests/                # UVM tests
│   └── seq/                  # Sequence library
├── ref/
│   ├── cpp/                  # DPI-C reference
│   └── python/               # NumPy golden model
├── formal/                   # SymbiYosys properties and .sby files
├── gls/                      # Gate-level sim scripts + SDF flow
├── sim/                      # Makefile / run scripts (Verilator + commercial)
└── .github/workflows/        # CI
```

## 5. Roadmap

| Phase | Scope                                                       | Status   |
|-------|-------------------------------------------------------------|----------|
| 0     | Repo skeleton, README, architecture decisions               | 🟡 In progress |
| 1     | HLS C++ source + initial RTL generation                     | ⚪ Not started |
| 2     | AXI4-Stream + AXI4-Lite UVM agents                          | ⚪ Not started |
| 3     | NumPy golden model + DPI-C reference                        | ⚪ Not started |
| 4     | UVM env, base test, scoreboard, smoke regression            | ⚪ Not started |
| 5     | Functional coverage model + coverage closure                | ⚪ Not started |
| 6     | SVA assertion suite                                         | ⚪ Not started |
| 7     | SymbiYosys formal flow on control logic                     | ⚪ Not started |
| 8     | Synthesis + SDF back-annotated GLS                          | ⚪ Not started |
| 9     | GitHub Actions CI + final documentation                     | ⚪ Not started |

## 6. Tooling *(planned)*

- **HLS:** Vitis HLS *(version TBD)*
- **Simulation:** Verilator (open-source CI) + a commercial simulator for UVM *(TBD: Questa / Xcelium / VCS)*
- **Formal:** SymbiYosys (Yosys + Z3 / Boolector)
- **Synthesis:** Yosys (open) and/or Vivado for GLS netlist
- **CI:** GitHub Actions

## 7. How to Build & Run

*Instructions will be added as each phase lands.* For now:

```bash
git clone https://github.com/<user>/systolic_array_dv.git
cd systolic_array_dv
# Build/run instructions TBD
```

## 8. References

*To be filled in:*
- TPU paper (Jouppi et al., 2017)
- Vitis HLS user guide
- SymbiYosys docs
- AXI4-Stream / AXI4-Lite specs

## 9. Author

**Jaishyam Reddy Reddivari** — MS Computer Engineering, Syracuse University. Boston, MA.
Open to entry-level DV / ASIC verification roles in the US.

## 10. License

*TBD — MIT or Apache 2.0.*
