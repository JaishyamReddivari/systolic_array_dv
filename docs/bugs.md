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