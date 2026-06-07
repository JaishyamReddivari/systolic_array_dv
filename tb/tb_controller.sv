// ============================================================================
// tb_controller.sv  --  full-DUT AXI4-Stream testbench for controller.sv
//
// Drives the controller through its real AXI-Stream interfaces:
//   - pulse start
//   - push 8 beats of A on s_axis_a (TLAST on beat 8)
//   - push 8 beats of B on s_axis_b (TLAST on beat 8)
//   - wait for done
//   - read 8 beats of C off m_axis_c, compare to expected
//
// Expected vectors come from gen_controller_vectors.py (proven golden model),
// so a mismatch isolates to the RTL. Tile 0's output backpressure is exercised
// (consumer holds tready low) to check the controller stalls correctly.
//
// File: controller_vectors.txt (must be in working dir).
//   line 1:        N_TILES
//   per tile: 8 rows A, then 8 rows B, then 8 rows C  (8 ints each)
//
// Run with Verilator:
//   (from tb/) verilator --binary -j 0 ../rtl/pe.sv ../rtl/systolic_array.sv \
//              ../rtl/controller.sv tb_controller.sv --top-module tb_controller
//   ./obj_dir/Vtb_controller
// Run with Icarus:
//   iverilog -g2012 -o tb ../rtl/pe.sv ../rtl/systolic_array.sv \
//            ../rtl/controller.sv tb_controller.sv && vvp tb
// ============================================================================

module tb_controller;

    localparam int N = 8;

    logic         clk, rst;
    logic         start, busy, done;

    logic [63:0]  a_tdata;  logic a_tvalid, a_tready, a_tlast;
    logic [63:0]  b_tdata;  logic b_tvalid, b_tready, b_tlast;
    logic [255:0] c_tdata;  logic c_tvalid, c_tready, c_tlast;

    controller dut (
        .clk(clk), .rst(rst),
        .start(start), .busy(busy), .done(done),
        .s_axis_a_tdata(a_tdata), .s_axis_a_tvalid(a_tvalid),
        .s_axis_a_tready(a_tready), .s_axis_a_tlast(a_tlast),
        .s_axis_b_tdata(b_tdata), .s_axis_b_tvalid(b_tvalid),
        .s_axis_b_tready(b_tready), .s_axis_b_tlast(b_tlast),
        .m_axis_c_tdata(c_tdata), .m_axis_c_tvalid(c_tvalid),
        .m_axis_c_tready(c_tready), .m_axis_c_tlast(c_tlast)
    );

    // clock
    initial clk = 0;
    always #5 clk = ~clk;

    // storage for one tile's data
    int  Amat [N][N];
    int  Bmat [N][N];
    int  Cexp [N][N];
    int  Cgot [N][N];

    integer fd, code, n_tiles, errors, checks;
    int     tmp;

    // ---- drive A as 8 AXI-Stream beats (correct handshake idiom) ----
    task automatic send_A();
        int r;
        r = 0;
        a_tvalid = 0; a_tlast = 0;
        while (r < N) begin
            @(negedge clk);
            a_tvalid = 1;
            a_tlast  = (r == N-1);
            for (int j = 0; j < N; j++)
                a_tdata[j*8 +: 8] = Amat[r][j][7:0];
            @(posedge clk);
            // beat transfers iff both valid and ready at this edge
            if (a_tvalid && a_tready)
                r++;
        end
        @(negedge clk);
        a_tvalid = 0; a_tlast = 0;
    endtask

    // ---- drive B as 8 AXI-Stream beats (correct handshake idiom) ----
    task automatic send_B();
        int k;
        k = 0;
        b_tvalid = 0; b_tlast = 0;
        while (k < N) begin
            @(negedge clk);
            b_tvalid = 1;
            b_tlast  = (k == N-1);
            for (int j = 0; j < N; j++)
                b_tdata[j*8 +: 8] = Bmat[k][j][7:0];
            @(posedge clk);
            if (b_tvalid && b_tready)
                k++;
        end
        @(negedge clk);
        b_tvalid = 0; b_tlast = 0;
    endtask

    // ---- read C as 8 AXI-Stream beats; with_bp = exercise backpressure ----
    task automatic recv_C(input bit with_bp);
        int beat;
        beat = 0;
        while (beat < N) begin
            @(negedge clk);
            // optionally stall the consumer for a couple cycles on tile 0
            if (with_bp && (beat == 2)) begin
                c_tready = 0;
                repeat (3) @(posedge clk);
                @(negedge clk);
            end
            c_tready = 1;
            @(posedge clk);
            if (c_tvalid && c_tready) begin
                for (int j = 0; j < N; j++)
                    Cgot[beat][j] = $signed(c_tdata[j*32 +: 32]);
                beat++;
            end
        end
        @(negedge clk);
        c_tready = 0;
    endtask

    initial begin
        errors = 0; checks = 0;
        start = 0;
        a_tvalid = 0; a_tlast = 0; a_tdata = '0;
        b_tvalid = 0; b_tlast = 0; b_tdata = '0;
        c_tready = 0;

        fd = $fopen("controller_vectors.txt", "r");
        if (fd == 0) begin $display("FATAL: cannot open controller_vectors.txt"); $finish; end
        code = $fscanf(fd, "%d", n_tiles);
        $display("Tiles: %0d", n_tiles);

        // global reset
        rst = 1;
        repeat (3) @(posedge clk);
        @(negedge clk); rst = 0;

        for (int t = 0; t < n_tiles; t++) begin
            // read A, B, C(expected) for this tile
            for (int r = 0; r < N; r++) for (int j = 0; j < N; j++) begin
                code = $fscanf(fd, "%d", tmp); Amat[r][j] = tmp; end
            for (int k = 0; k < N; k++) for (int j = 0; j < N; j++) begin
                code = $fscanf(fd, "%d", tmp); Bmat[k][j] = tmp; end
            for (int r = 0; r < N; r++) for (int j = 0; j < N; j++) begin
                code = $fscanf(fd, "%d", tmp); Cexp[r][j] = tmp; end

            // kick off a tile
            @(negedge clk); start = 1;
            @(negedge clk); start = 0;

            // feed A and B (B can stream right after / overlapping)
            fork
                send_A();
                send_B();
            join

            // Read results AS the DUT offers them (state OUTPUT). The DUT holds
            // c_tvalid until we assert c_tready; draining OUTPUT is what lets it
            // advance to DONE. (Waiting for `done` BEFORE reading would deadlock:
            // done can't assert until C is drained.)
            recv_C(t == 0);

            // now the tile has drained; done pulses as the FSM passes S_DONE
            // (already happened or happens within a cycle). Settle.
            repeat (2) @(posedge clk);

            // compare
            for (int r = 0; r < N; r++)
                for (int j = 0; j < N; j++) begin
                    checks++;
                    if (Cgot[r][j] !== Cexp[r][j]) begin
                        errors++;
                        $display("MISMATCH tile %0d C[%0d][%0d]: got %0d exp %0d",
                                 t, r, j, Cgot[r][j], Cexp[r][j]);
                    end
                end

            // settle before next tile
            repeat (2) @(posedge clk);
        end

        $fclose(fd);
        $display("----------------------------------------");
        $display("Checks: %0d   Errors: %0d", checks, errors);
        $display(errors == 0 ? "RESULT: PASS" : "RESULT: FAIL");
        $finish;
    end

    // timeout
    initial begin #2_000_000; $display("FATAL: timeout (DUT likely hung)"); $finish; end

    // ---- DEBUG state trace (first 120 cycles). Comment out once passing. ----
    int dbg_cyc;
    initial dbg_cyc = 0;
    always @(posedge clk) begin
        if (dbg_cyc < 120) begin
            $display("t=%0t cyc=%0d state=%0d busy=%b a_rdy=%b a_vld=%b b_rdy=%b b_vld=%b c_vld=%b c_rdy=%b done=%b a_cnt=%0d b_cnt=%0d comp=%0d",
                     $time, dbg_cyc, dut.state, busy,
                     a_tready, a_tvalid, b_tready, b_tvalid,
                     c_tvalid, c_tready, done,
                     dut.a_cnt, dut.b_cnt, dut.comp_cnt);
        end
        dbg_cyc <= dbg_cyc + 1;
    end

endmodule