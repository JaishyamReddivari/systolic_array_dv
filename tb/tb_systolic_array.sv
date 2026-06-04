// ============================================================================
// tb_systolic_array.sv  --  golden-vector testbench for systolic_array.sv
//
// This testbench contains NO skew / de-skew / timing logic of its own. It
// reads pre-computed stimulus and expected outputs from stimulus.txt (produced
// by generate_stimulus.py from the proven cycle-accurate model) and replays
// them against the DUT, checking c_out every compute cycle.
//
// Because the expected values come from an independently-proven model and the
// TB just plays them back, this test cannot share a bug with the controller
// logic it will later verify -- it checks the array FABRIC in isolation.
//
// Stimulus file format (whitespace-separated ints):
//   line 1:        N  N_LOAD  N_COMPUTE  N_TILES
//   per tile:
//      N_LOAD lines    of 8 ints  -> weight_top[0..7]
//      N_COMPUTE lines of 16 ints -> a_top[0..7] then expected c_out[0..7]
//
// Run with Verilator:
//   (from tb/)  verilator --binary -j 0 ../rtl/pe.sv ../rtl/systolic_array.sv \
//               tb_systolic_array.sv --top-module tb_systolic_array
//   ./obj_dir/Vtb_systolic_array
// Run with Icarus:
//   iverilog -g2012 -o tb ../rtl/pe.sv ../rtl/systolic_array.sv \
//            tb_systolic_array.sv && vvp tb
//
// (stimulus.txt must be in the working directory.)
// ============================================================================

module tb_systolic_array;

    localparam int N = 8;

    // ---- DUT I/O ----
    logic                clk;
    logic                rst;
    logic                load_en;
    logic                compute_en;
    logic signed [7:0]   weight_top [N];
    logic signed [7:0]   a_top      [N];
    logic signed [31:0]  c_out      [N];

    // ---- DUT ----
    systolic_array dut (
        .clk        (clk),
        .rst        (rst),
        .load_en    (load_en),
        .compute_en (compute_en),
        .weight_top (weight_top),
        .a_top      (a_top),
        .c_out      (c_out)
    );

    // ---- clock: 10ns period ----
    initial clk = 0;
    always #5 clk = ~clk;

    // ---- file + bookkeeping ----
    integer fd;
    integer code;
    int     file_N, file_NLOAD, file_NCOMPUTE, file_NTILES;
    int     errors;
    int     checks;

    // temporaries for reading
    int tmp;
    logic signed [31:0] exp_cout [N];

    initial begin
        errors = 0;
        checks = 0;

        fd = $fopen("stimulus.txt", "r");
        if (fd == 0) begin
            $display("FATAL: cannot open stimulus.txt");
            $finish;
        end

        code = $fscanf(fd, "%d %d %d %d",
                       file_N, file_NLOAD, file_NCOMPUTE, file_NTILES);
        if (file_N != N) begin
            $display("FATAL: stimulus N=%0d but TB built for N=%0d", file_N, N);
            $finish;
        end
        $display("Stimulus: N=%0d LOAD=%0d COMPUTE=%0d TILES=%0d",
                 file_N, file_NLOAD, file_NCOMPUTE, file_NTILES);

        // init inputs
        rst = 1; load_en = 0; compute_en = 0;
        for (int j = 0; j < N; j++) begin weight_top[j] = 0; a_top[j] = 0; end

        // ---- per-tile loop ----
        for (int t = 0; t < file_NTILES; t++) begin

            // --- reset pulse (synchronous) ---
            @(negedge clk);
            rst = 1; load_en = 0; compute_en = 0;
            for (int j = 0; j < N; j++) begin weight_top[j] = 0; a_top[j] = 0; end
            @(posedge clk);          // regs zeroed on this edge
            @(negedge clk);
            rst = 0;

            // --- LOAD phase: shift weights in ---
            for (int c = 0; c < file_NLOAD; c++) begin
                @(negedge clk);
                load_en = 1; compute_en = 0;
                for (int j = 0; j < N; j++) begin
                    code = $fscanf(fd, "%d", tmp);
                    weight_top[j] = tmp[7:0];
                    a_top[j] = 0;            // drive don't-care to 0 (clean waves)
                end
                @(posedge clk);              // shift on this edge
            end

            // --- COMPUTE + DRAIN phase ---
            for (int c = 0; c < file_NCOMPUTE; c++) begin
                @(negedge clk);
                load_en = 0; compute_en = 1;
                for (int j = 0; j < N; j++) begin
                    code = $fscanf(fd, "%d", tmp);
                    a_top[j] = tmp[7:0];
                end
                for (int r = 0; r < N; r++) begin
                    code = $fscanf(fd, "%d", tmp);
                    exp_cout[r] = tmp;       // 32-bit expected
                end

                @(posedge clk);              // DUT clocks compute cycle c
                #1;                          // let registered c_out settle

                for (int r = 0; r < N; r++) begin
                    checks++;
                    if (c_out[r] !== exp_cout[r]) begin
                        errors++;
                        $display("MISMATCH tile %0d cycle %0d row %0d: got %0d exp %0d",
                                 t, c, r, c_out[r], exp_cout[r]);
                    end
                end
            end
        end

        $fclose(fd);
        $display("----------------------------------------");
        $display("Checks: %0d   Errors: %0d", checks, errors);
        if (errors == 0) $display("RESULT: PASS");
        else             $display("RESULT: FAIL");
        $finish;
    end

    // safety timeout
    initial begin
        #1_000_000;
        $display("FATAL: timeout");
        $finish;
    end

endmodule
