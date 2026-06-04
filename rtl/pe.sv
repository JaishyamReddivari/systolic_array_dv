// ============================================================================
// pe.sv  --  Processing Element for the 8x8 INT8 weight-stationary systolic
//            array (systolic_array_dv).
//
// One PE = one signed INT8 x INT8 multiply-accumulate, plus the pipeline
// registers that make the array "systolic" (one register per hop).
//
// This module is the hardware counterpart of PE.tick() in
// ref/python/systolic_sim.py. The mapping is:
//
//     Python                              SystemVerilog
//     ------------------------------      ------------------------------
//     self.weight                         weight_reg
//     self.activation_reg                 a_reg      (flows DOWN)
//     self.psum_reg                       psum_reg   (flows RIGHT)
//     activation_in (from PE above)       a_in
//     psum_in       (from PE at left)     psum_in
//     new_psum = psum_in + weight*act_in  psum_reg <= psum_in + weight_reg*a_in
//     a_reg = activation_in               a_reg    <= a_in
//     returns OLD reg values to neighbors registered outputs (a_out/psum_out)
//
// The Python "snapshot then commit" pattern (all PEs read start-of-cycle
// neighbor values, then update together) is exactly what a clock edge does
// in hardware: every flop samples the wire values present just before the
// edge and updates simultaneously. So the hardware naturally matches the
// model's timing -- no special handling needed.
//
// DATAFLOW (spec section 3):
//   - Weights are STATIONARY: loaded once into weight_reg, then held.
//   - Activations flow DOWN columns: a_in (top) -> a_reg -> a_out (bottom).
//   - Partial sums flow RIGHT along rows: psum_in (left) -> psum_reg ->
//     psum_out (right).
//
// WEIGHT LOADING:
//   Weights shift DOWN a dedicated vertical chain during the LOAD phase.
//   The controller feeds each column's weights last-row-first at the top,
//   so after 8 shift cycles PE(i,j) holds A[i][j]. (See controller.sv.)
//   A separate weight path -- distinct from the activation path -- is used
//   for clarity; a production design might mux them onto shared wires to
//   save routing.
//
// Widths are hardcoded INT8 / INT32 per the spec (no parameters).
// ============================================================================

module pe (
    input  logic                clk,
    input  logic                rst,         // synchronous, active-high

    // ---- control ----
    input  logic                load_en,     // LOAD phase: shift weight down
    input  logic                compute_en,  // COMPUTE/DRAIN: MAC + pass data

    // ---- weight shift path (vertical, top -> bottom) ----
    input  logic signed [7:0]   weight_in,   // from PE above (or top feed)
    output logic signed [7:0]   weight_out,  // to PE below  (= weight_reg)

    // ---- activation path (vertical, top -> bottom) ----
    input  logic signed [7:0]   a_in,        // from PE above
    output logic signed [7:0]   a_out,       // to PE below

    // ---- partial-sum path (horizontal, left -> right) ----
    input  logic signed [31:0]  psum_in,     // from PE at left
    output logic signed [31:0]  psum_out     // to PE at right
);

    // ---- state registers ----
    logic signed [7:0]   weight_reg;  // stationary weight  = A[i][j]
    logic signed [7:0]   a_reg;       // activation pipeline (flows down)
    logic signed [31:0]  psum_reg;    // partial-sum pipeline (flows right)

    // Registered outputs: neighbors see what THIS PE latched last edge.
    assign weight_out = weight_reg;
    assign a_out      = a_reg;
    assign psum_out   = psum_reg;

    // Combinational signed 8x8 -> 16-bit product. Declaring the operands and
    // this result as `signed` makes the multiply a signed multiply and lets
    // the later addition sign-extend it correctly into the 32-bit psum.
    logic signed [15:0] product;
    always_comb begin
        product = weight_reg * a_in;
    end

    // ---- sequential behavior ----
    always_ff @(posedge clk) begin
        if (rst) begin
            weight_reg <= 8'sd0;
            a_reg      <= 8'sd0;
            psum_reg   <= 32'sd0;
        end else begin
            // LOAD: shift the weight chain down one PE per cycle.
            if (load_en) begin
                weight_reg <= weight_in;
            end

            // COMPUTE / DRAIN: pass activation down, accumulate psum rightward.
            // During DRAIN the controller drives a_in = 0 at the top, so the
            // array keeps clocking while in-flight psums finish and exit.
            if (compute_en) begin
                a_reg    <= a_in;
                // All operands signed => signed add with sign-extension of
                // the 16-bit product into the 32-bit accumulator.
                psum_reg <= psum_in + 32'(product);
            end
        end
    end

endmodule
