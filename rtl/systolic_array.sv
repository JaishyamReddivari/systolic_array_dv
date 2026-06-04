// ============================================================================
// systolic_array.sv  --  8x8 grid of PEs for systolic_array_dv.
//
// Pure structural module: instantiates 64 `pe` units and wires them with the
// three nearest-neighbor connections from spec section 3:
//
//   - WEIGHTS shift DOWN columns   : PE(i,j).weight_in <= PE(i-1,j).weight_out
//   - ACTIVATIONS flow DOWN columns: PE(i,j).a_in      <= PE(i-1,j).a_out
//   - PARTIAL SUMS flow RIGHT rows : PE(i,j).psum_in   <= PE(i,j-1).psum_out
//
// Edge conditions:
//   - Top row (i==0):    weight_in / a_in come from the external top feeds.
//   - Left col (j==0):   psum_in is tied to 0 (start of each row's accumulation).
//   - Right col (j==N-1):psum_out is the finished C value for that row -> c_out.
//
// This module has NO control logic and NO skew logic. It is the raw compute
// fabric. The controller (controller.sv) is responsible for:
//   - feeding weights last-row-first during LOAD so PE(i,j) ends up with A[i][j]
//   - feeding activations with the staircase skew during COMPUTE
//   - de-skewing the right-edge outputs into row-major C
//
// Functional reference: a full LOAD+COMPUTE+DRAIN sequence driven into this
// fabric must reproduce SystolicArray.run_tile() from systolic_sim.py.
//
// Widths hardcoded INT8 / INT32 per spec.
// ============================================================================

module systolic_array (
    input  logic                clk,
    input  logic                rst,         // synchronous, active-high
    input  logic                load_en,     // LOAD phase enable (to all PEs)
    input  logic                compute_en,  // COMPUTE/DRAIN enable (to all PEs)

    // Top-edge feeds, one lane per column.
    input  logic signed [7:0]   weight_top [8],  // weight feed (LOAD phase)
    input  logic signed [7:0]   a_top      [8],  // activation feed (COMPUTE)

    // Right-edge results, one lane per row.
    output logic signed [31:0]  c_out      [8]
);

    localparam int N = 8;

    // ---- PE output wires (the registered outputs of each PE) ----
    logic signed [7:0]   weight_out_w [N][N];
    logic signed [7:0]   a_out_w      [N][N];
    logic signed [31:0]  psum_out_w   [N][N];

    // ---- PE input wires (driven by edges or by neighbor outputs) ----
    logic signed [7:0]   weight_in_w  [N][N];
    logic signed [7:0]   a_in_w       [N][N];
    logic signed [31:0]  psum_in_w    [N][N];

    genvar i, j;
    generate
        for (i = 0; i < N; i++) begin : g_row
            for (j = 0; j < N; j++) begin : g_col

                // ---- vertical inputs: top feed for row 0, else PE above ----
                if (i == 0) begin : g_top
                    assign weight_in_w[i][j] = weight_top[j];
                    assign a_in_w[i][j]      = a_top[j];
                end else begin : g_above
                    assign weight_in_w[i][j] = weight_out_w[i-1][j];
                    assign a_in_w[i][j]      = a_out_w[i-1][j];
                end

                // ---- horizontal input: 0 at left edge, else PE to the left --
                if (j == 0) begin : g_left
                    assign psum_in_w[i][j] = 32'sd0;
                end else begin : g_lneigh
                    assign psum_in_w[i][j] = psum_out_w[i][j-1];
                end

                // ---- the processing element ----
                pe u_pe (
                    .clk        (clk),
                    .rst        (rst),
                    .load_en    (load_en),
                    .compute_en (compute_en),
                    .weight_in  (weight_in_w[i][j]),
                    .weight_out (weight_out_w[i][j]),
                    .a_in       (a_in_w[i][j]),
                    .a_out      (a_out_w[i][j]),
                    .psum_in    (psum_in_w[i][j]),
                    .psum_out   (psum_out_w[i][j])
                );
            end
        end

        // ---- right-edge outputs: row i's finished accumulation ----
        for (i = 0; i < N; i++) begin : g_out
            assign c_out[i] = psum_out_w[i][N-1];
        end
    endgenerate

endmodule
