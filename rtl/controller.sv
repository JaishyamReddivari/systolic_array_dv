// ============================================================================
// controller.sv  --  AXI4-Stream front-end + sequencer for systolic_array_dv.
//
// Wraps the raw systolic_array fabric and owns ALL the timing logic the fabric
// deliberately lacks: input buffering, weight-load ordering, activation skew,
// output de-skew, and the AXI4-Stream handshakes.
//
// DATA PACKING (spec section 5):
//   s_axis_a_tdata [63:0]  = one row of A  (8 x INT8), A[r][0] in [7:0] ...
//   s_axis_b_tdata [63:0]  = one row of B  (8 x INT8)
//   m_axis_c_tdata [255:0] = one row of C  (8 x INT32), C[r][0] in [31:0] ...
//
// PHASE FLOW (single integrated FSM):
//   IDLE -> RECV_A -> LOAD -> [WAIT_B] -> COMPUTE -> OUTPUT -> DONE -> IDLE
//   B is received CONCURRENTLY into a buffer during RECV_A / LOAD / WAIT_B;
//   COMPUTE is gated on the full B tile being present. This decouples B's
//   arrival timing from its consumption (producer/consumer decoupling).
//
// BACKPRESSURE (Rev A): tile-granularity. Mid-stream input stalling is
// tolerated (tready drops), but COMPUTE never starts on a partial tile.
//
// Widths hardcoded INT8 / INT32 per spec.
// ============================================================================

module controller (
    input  logic         clk,
    input  logic         rst,           // synchronous, active-high

    // ---- control / status (to/from CSR block) ----
    input  logic         start,         // pulse: begin a tile
    output logic         busy,          // high while a tile is in progress
    output logic         done,          // 1-cycle pulse when a tile completes

    // ---- AXI4-Stream slave: matrix A (weights) ----
    input  logic [63:0]  s_axis_a_tdata,
    input  logic         s_axis_a_tvalid,
    output logic         s_axis_a_tready,
    input  logic         s_axis_a_tlast,

    // ---- AXI4-Stream slave: matrix B (activations) ----
    input  logic [63:0]  s_axis_b_tdata,
    input  logic         s_axis_b_tvalid,
    output logic         s_axis_b_tready,
    input  logic         s_axis_b_tlast,

    // ---- AXI4-Stream master: matrix C (results) ----
    output logic [255:0] m_axis_c_tdata,
    output logic         m_axis_c_tvalid,
    input  logic         m_axis_c_tready,
    output logic         m_axis_c_tlast
);

    localparam int N = 8;

    // Sized constants for counter comparisons (avoids width-mismatch lint
    // between the small counters and the 32-bit int localparam N).
    localparam logic [3:0] CNT_N   = 4'd8;   // == N
    localparam logic [3:0] CNT_NM1 = 4'd7;   // == N-1

    // ---- FSM ----
    typedef enum logic [2:0] {
        S_IDLE, S_RECV_A, S_LOAD, S_WAIT_B, S_COMPUTE, S_OUTPUT, S_DONE
    } state_t;
    state_t state;

    // ---- counters ----
    logic [3:0] a_cnt;     // A beats received   0..8
    logic [3:0] b_cnt;     // B beats received   0..8
    logic [3:0] load_cnt;  // LOAD cycles        0..7
    logic [4:0] comp_cnt;  // COMPUTE cycles     0..22
    logic [3:0] out_cnt;   // OUTPUT beats       0..7

    // ---- buffers ----
    logic signed [7:0]   a_buf [N][N];   // a_buf[r][k] = A[r][k]
    logic signed [7:0]   b_buf [N][N];   // b_buf[k][c] = B[k][c]
    logic signed [31:0]  c_buf [N][N];   // c_buf[r][c] = C[r][c]

    // ---- array fabric interface ----
    logic                load_en;
    logic                compute_en;
    logic signed [7:0]   weight_top [N];
    logic signed [7:0]   a_top      [N];
    logic signed [31:0]  c_out      [N];

    systolic_array u_array (
        .clk        (clk),
        .rst        (rst),
        .load_en    (load_en),
        .compute_en (compute_en),
        .weight_top (weight_top),
        .a_top      (a_top),
        .c_out      (c_out)
    );

    // ------------------------------------------------------------------
    // Combinational: array control + top-edge feeds
    // ------------------------------------------------------------------
    assign load_en    = (state == S_LOAD);
    assign compute_en = (state == S_COMPUTE);

    always_comb begin
        for (int j = 0; j < N; j++) begin
            weight_top[j] = 8'sd0;
            a_top[j]      = 8'sd0;
        end

        // LOAD: feed column j last-row-first so PE(i,j) ends with A[i][j].
        // Row index = 7 - load_cnt, computed in 3 bits (0..7).
        if (state == S_LOAD) begin
            for (int j = 0; j < N; j++)
                weight_top[j] = a_buf[3'd7 - load_cnt[2:0]][j];
        end

        // COMPUTE: feed skewed B. skewed[t][k] = B[k][t-k], t = comp_cnt.
        // Arithmetic done in int (cast comp_cnt) to match the int loop vars.
        if (state == S_COMPUTE) begin
            for (int k = 0; k < N; k++) begin
                automatic int idx = int'(comp_cnt) - k;
                if (idx >= 0 && idx < N)
                    a_top[k] = b_buf[k][idx[2:0]];
                else
                    a_top[k] = 8'sd0;
            end
        end
    end

    // ------------------------------------------------------------------
    // Combinational: AXI-Stream handshakes + status
    // ------------------------------------------------------------------
    assign s_axis_a_tready = (state == S_RECV_A) && (a_cnt < CNT_N);

    logic b_active;
    assign b_active = (state == S_RECV_A) || (state == S_LOAD) ||
                      (state == S_WAIT_B);
    assign s_axis_b_tready = b_active && (b_cnt < CNT_N);

    always_comb begin
        for (int j = 0; j < N; j++)
            m_axis_c_tdata[j*32 +: 32] = c_buf[out_cnt[2:0]][j];
    end
    assign m_axis_c_tvalid = (state == S_OUTPUT);
    assign m_axis_c_tlast  = (state == S_OUTPUT) && (out_cnt == CNT_NM1);

    assign busy = (state != S_IDLE);
    assign done = (state == S_DONE);

    // ------------------------------------------------------------------
    // Sequential: FSM + datapath
    // ------------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            state    <= S_IDLE;
            a_cnt    <= '0;
            b_cnt    <= '0;
            load_cnt <= '0;
            comp_cnt <= '0;
            out_cnt  <= '0;
        end else begin

            // ---- concurrent B reception (independent of main phase) ----
            if (s_axis_b_tready && s_axis_b_tvalid) begin
                for (int j = 0; j < N; j++)
                    b_buf[b_cnt[2:0]][j] <= s_axis_b_tdata[j*8 +: 8];
                b_cnt <= b_cnt + 4'd1;
`ifndef SYNTHESIS
                if (s_axis_b_tlast != (b_cnt == CNT_NM1))
                    $warning("s_axis_b TLAST on beat %0d (expected %0d)",
                             b_cnt, N-1);
`endif
            end

            // ---- main FSM ----
            case (state)

                S_IDLE: begin
                    if (start) begin
                        a_cnt    <= '0;
                        b_cnt    <= '0;
                        load_cnt <= '0;
                        comp_cnt <= '0;
                        out_cnt  <= '0;
                        state    <= S_RECV_A;
                    end
                end

                S_RECV_A: begin
                    if (s_axis_a_tready && s_axis_a_tvalid) begin
                        for (int j = 0; j < N; j++)
                            a_buf[a_cnt[2:0]][j] <= s_axis_a_tdata[j*8 +: 8];
                        a_cnt <= a_cnt + 4'd1;
`ifndef SYNTHESIS
                        if (s_axis_a_tlast != (a_cnt == CNT_NM1))
                            $warning("s_axis_a TLAST on beat %0d (expected %0d)",
                                     a_cnt, N-1);
`endif
                    end
                    if (a_cnt == CNT_N) begin       // A fully buffered
                        state    <= S_LOAD;
                        load_cnt <= '0;
                    end
                end

                S_LOAD: begin
                    if (load_cnt == CNT_NM1) begin  // 8th (final) shift this edge
                        if (b_cnt == CNT_N) begin
                            state    <= S_COMPUTE;
                            comp_cnt <= '0;
                        end else begin
                            state <= S_WAIT_B;
                        end
                    end else begin
                        load_cnt <= load_cnt + 4'd1;
                    end
                end

                S_WAIT_B: begin
                    if (b_cnt == CNT_N) begin
                        state    <= S_COMPUTE;
                        comp_cnt <= '0;
                    end
                end

                S_COMPUTE: begin
                    // ----------------------------------------------------------
                    // OUTPUT DE-SKEW  (HIGHEST-RISK TIMING -- verify carefully)
                    //
                    // c_out is registered: during the cycle comp_cnt == v it
                    // holds right_log[v-1] (one-cycle pipeline delay). The model
                    // gives C[r][c] = right_log[r+c+N-1][r]. With t = comp_cnt-1:
                    //   c = (comp_cnt-1) - r - (N-1) = comp_cnt - r - N.
                    // Last capture C[7][7] at comp_cnt = 22, so run 0..22.
                    // ----------------------------------------------------------
                    for (int r = 0; r < N; r++) begin
                        automatic int cidx = int'(comp_cnt) - r - N;
                        if (cidx >= 0 && cidx < N)
                            c_buf[r][cidx[2:0]] <= c_out[r];
                    end

                    if (comp_cnt == 5'd22) begin
                        state   <= S_OUTPUT;
                        out_cnt <= '0;
                    end else begin
                        comp_cnt <= comp_cnt + 5'd1;
                    end
                end

                S_OUTPUT: begin
                    if (m_axis_c_tvalid && m_axis_c_tready) begin
                        if (out_cnt == CNT_NM1)
                            state <= S_DONE;
                        else
                            out_cnt <= out_cnt + 4'd1;
                    end
                end

                S_DONE: begin
                    state <= S_IDLE;
                end

                default: state <= S_IDLE;

            endcase
        end
    end

`ifdef FORMAL
    // ================= formal: control-plane proof + reachability =============
    // Targets the FSM/handshake logic; the array is blackboxed in the .sby
    // (its math is covered by simulation, not formal).
    logic f_past_valid;
    initial f_past_valid = 1'b0;
    always_ff @(posedge clk) f_past_valid <= 1'b1;

    initial assume (rst);                       // design starts in reset

    always_ff @(posedge clk) if (f_past_valid) begin
        // FSM never reaches the undefined 8th encoding
        assert (state <= S_DONE);

        // counters never run past their declared ranges
        assert (a_cnt    <= CNT_N);
        assert (b_cnt    <= CNT_N);
        assert (load_cnt <= CNT_NM1);
        assert (comp_cnt <= 5'd22);
        assert (out_cnt  <= CNT_NM1);

        if ($past(rst))
            assert (state == S_IDLE);           // reset -> IDLE

        if (!$past(rst)) begin
            // done is a one-cycle pulse: S_DONE always returns to IDLE
            if ($past(state) == S_DONE)
                assert (state == S_IDLE);

            // start in IDLE launches a tile
            if (($past(state) == S_IDLE) && $past(start))
                assert (state == S_RECV_A);

            // KEY GUARANTEE: COMPUTE never begins on a partial B tile
            // (the producer/consumer decoupling the header advertises)
            if (($past(state) != S_COMPUTE) && (state == S_COMPUTE))
                assert ($past(b_cnt) == CNT_N);
        end

        // reachability of every phase, incl. S_WAIT_B
        cover (state == S_RECV_A);
        cover (state == S_LOAD);
        cover (state == S_WAIT_B);
        cover (state == S_COMPUTE);
        cover (state == S_OUTPUT);
        cover (state == S_DONE);
    end
`endif

endmodule
