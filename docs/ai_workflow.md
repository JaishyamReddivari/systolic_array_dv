# AI-Assisted Development Workflow

This document records how AI tooling was used in building `systolic_array_dv`,
and — more importantly — where human engineering judgment drove, corrected, or
overrode that tooling. It is written for anyone evaluating how I integrate AI
into real engineering work.

The short version: AI shortened time-to-first-draft on scaffolding and
documentation. The architecture, the verification strategy, and every
correctness decision are mine, and every committed line is one I can defend.

---

## Division of labor

I keep a deliberate split between work I own outright and work where AI
accelerates a draft that I then verify and adapt.

**Owned outright (no AI authorship):**
- Architectural decisions: weight-stationary dataflow, 32-bit accumulator,
  24-cycle tile schedule, AXI interface partitioning.
- Verification strategy: what to check, what the independent references are,
  what the interesting corner cases are.
- All bug investigation and root-cause analysis (see `docs/bugs.md`).
- Final judgment on whether any generated artifact is correct.

**AI-accelerated, human-verified:**
- First drafts of documentation (this spec, README sections).
- Skeleton code for the reference models, which I then read line-by-line,
  adapted, and validated against hand-computed results.
- Boilerplate: build files, test harness structure, cross-check plumbing.

**The rule I hold:** I do not commit code I could not reproduce and explain
from a blank page. AI changes how fast I get to a draft; it does not change
my responsibility for the result.

---

## Concrete examples

### Example 1 — Human override caught a specification error

While developing the cycle-accurate Python model, the generated implementation
followed the dataflow as I had originally documented it (partial sums
accumulating down columns, output read from the bottom edge). When I ran it
against a hand-computed 2x2 example, the outputs did not match.

Tracing the mismatch by hand, I found the error was in my *specification*, not
the code: the documented dataflow does not compute a matrix product. A correct
weight-stationary systolic array must route partial sums perpendicular to the
activation stream — activations down, partial sums right, output from the right
edge. I corrected the spec, the diagram, and the model, and logged it as Bug #1.

This is the central value of building a reference model before RTL: it caught
a spec inconsistency that would otherwise have cost significant RTL and
verification effort. AI produced a faithful implementation of a flawed spec;
the human verification step is what caught the flaw.

### Example 2 — Scope discipline over AI suggestions

When scaffolding the C++ reference, the natural pull was to mirror the full
cycle-accurate simulator structure in C++. I decided against it: the reference
model's job in the testbench is to answer "what is the correct result," which
is a behavioral question. Cycle-level timing is checked separately via
assertions and the Python model. Mirroring the cycle-accurate model in C++
would have been ~150 lines re-proving something already proven, so the C++
reference is a deliberately small behavioral model instead.

### Example 3 — Language-specific correctness checks

The C++ reference required attention to details that do not exist in the NumPy
version: integer promotion in `int8_t` multiplication, and stream parsing
treating `int8_t` as a character rather than a number. I verified the C++
matched the NumPy semantics bit-for-bit by running both on identical random
inputs (200 trials, full agreement across the C++ reference, the NumPy
behavioral golden, and the cycle-accurate simulator).

---

## Result

The project has three independent models of the same function — a C++
behavioral reference, a NumPy behavioral golden, and a NumPy cycle-accurate
simulator — that agree on all tested inputs. When RTL comes online, any
disagreement isolates to the RTL rather than to an ambiguous reference. That
triangulation was a deliberate verification-strategy choice.

---

## Tools used

- Conversational AI assistant: documentation drafts, code scaffolding,
  explanation of unfamiliar concepts, and as a reviewer I argue with.
- Standard toolchain (compilers, simulators, version control) used normally.

*This document is updated as the project progresses.*