// tb_systolic_top.sv -- integrated smoke test for the full DUT.
// Drives the real software flow through BOTH interfaces:
//   AXI4-Lite write CTRL.start -> stream A,B in -> stream C out
//   -> poll STATUS.done -> read TILE_CNT.
// Expected C computed by an independent behavioral matmul in the TB.
// Run: verilator --binary -j 0 ../rtl/pe.sv ../rtl/systolic_array.sv \
//      ../rtl/controller.sv ../rtl/csr.sv ../rtl/systolic_top.sv \
//      tb_systolic_top.sv --top-module tb_systolic_top
//      ./obj_dir/Vtb_systolic_top

module tb_systolic_top;
    localparam int N = 8;

    logic clk, rst;
    logic [63:0]  a_tdata; logic a_tvalid, a_tready, a_tlast;
    logic [63:0]  b_tdata; logic b_tvalid, b_tready, b_tlast;
    logic [255:0] c_tdata; logic c_tvalid, c_tready, c_tlast;
    logic [7:0]   awaddr; logic awvalid, awready;
    logic [31:0]  wdata;  logic [3:0] wstrb; logic wvalid, wready;
    logic [1:0]   bresp;  logic bvalid, bready;
    logic [7:0]   araddr; logic arvalid, arready;
    logic [31:0]  rdata;  logic [1:0] rresp; logic rvalid, rready;
    logic irq;

    int Amat[N][N], Bmat[N][N], Cexp[N][N], Cgot[N][N];
    int errors = 0;

    systolic_top dut (
        .clk(clk), .rst(rst),
        .s_axis_a_tdata(a_tdata), .s_axis_a_tvalid(a_tvalid),
        .s_axis_a_tready(a_tready), .s_axis_a_tlast(a_tlast),
        .s_axis_b_tdata(b_tdata), .s_axis_b_tvalid(b_tvalid),
        .s_axis_b_tready(b_tready), .s_axis_b_tlast(b_tlast),
        .m_axis_c_tdata(c_tdata), .m_axis_c_tvalid(c_tvalid),
        .m_axis_c_tready(c_tready), .m_axis_c_tlast(c_tlast),
        .s_axil_awaddr(awaddr), .s_axil_awvalid(awvalid), .s_axil_awready(awready),
        .s_axil_wdata(wdata), .s_axil_wstrb(wstrb), .s_axil_wvalid(wvalid),
        .s_axil_wready(wready),
        .s_axil_bresp(bresp), .s_axil_bvalid(bvalid), .s_axil_bready(bready),
        .s_axil_araddr(araddr), .s_axil_arvalid(arvalid), .s_axil_arready(arready),
        .s_axil_rdata(rdata), .s_axil_rresp(rresp), .s_axil_rvalid(rvalid),
        .s_axil_rready(rready),
        .irq(irq)
    );

    initial clk = 0; always #5 clk = ~clk;

    // ---- AXI4-Lite write ----
    task automatic axil_write(input [7:0] addr, input [31:0] data);
        @(negedge clk);
        awaddr=addr; awvalid=1; wdata=data; wstrb=4'hF; wvalid=1;
        do @(posedge clk); while (!(awready && wready));
        @(negedge clk); awvalid=0; wvalid=0; bready=1;
        do @(posedge clk); while (!bvalid);
        @(negedge clk); bready=0;
    endtask

    // ---- AXI4-Lite read ----
    task automatic axil_read(input [7:0] addr, output [31:0] data);
        @(negedge clk);
        araddr=addr; arvalid=1; rready=1;
        do @(posedge clk); while (!arready);
        @(negedge clk); arvalid=0;
        do @(posedge clk); while (!rvalid);
        data = rdata;
        @(negedge clk); rready=0;
    endtask

    // ---- AXI-Stream drive A ----
    task automatic send_A();
        int r; r = 0; a_tvalid=0; a_tlast=0;
        while (r < N) begin
            @(negedge clk); a_tvalid=1; a_tlast=(r==N-1);
            for (int j=0;j<N;j++) a_tdata[j*8 +: 8] = Amat[r][j][7:0];
            @(posedge clk);
            if (a_tvalid && a_tready) r++;
        end
        @(negedge clk); a_tvalid=0; a_tlast=0;
    endtask

    // ---- AXI-Stream drive B ----
    task automatic send_B();
        int k; k = 0; b_tvalid=0; b_tlast=0;
        while (k < N) begin
            @(negedge clk); b_tvalid=1; b_tlast=(k==N-1);
            for (int j=0;j<N;j++) b_tdata[j*8 +: 8] = Bmat[k][j][7:0];
            @(posedge clk);
            if (b_tvalid && b_tready) k++;
        end
        @(negedge clk); b_tvalid=0; b_tlast=0;
    endtask

    // ---- AXI-Stream read C ----
    task automatic recv_C();
        int beat; beat = 0;
        while (beat < N) begin
            @(negedge clk); c_tready=1;
            @(posedge clk);
            if (c_tvalid && c_tready) begin
                for (int j=0;j<N;j++) Cgot[beat][j] = $signed(c_tdata[j*32 +: 32]);
                beat++;
            end
        end
        @(negedge clk); c_tready=0;
    endtask

    // ---- behavioral reference matmul ----
    task automatic compute_expected();
        for (int r=0;r<N;r++)
            for (int c=0;c<N;c++) begin
                int acc; acc=0;
                for (int k=0;k<N;k++) acc += Amat[r][k]*Bmat[k][c];
                Cexp[r][c]=acc;
            end
    endtask

    // ---- run one tile through the full software flow ----
    task automatic run_tile(input int tnum);
        logic [31:0] st; int polls;
        compute_expected();

        // launch via CSR
        axil_write(8'h00, 32'h1);          // CTRL.start = 1

        // stream A and B
        fork send_A(); send_B(); join

        // drain results (during OUTPUT)
        recv_C();

        // poll STATUS.done
        polls = 0; st = 0;
        while (!st[1] && polls < 50) begin
            axil_read(8'h04, st); polls++;
        end
        if (!st[1]) begin errors++; $display("tile %0d: done never set", tnum); end

        // clear done (W1C) for next tile
        axil_write(8'h04, 32'h2);

        // check C
        for (int r=0;r<N;r++)
            for (int c=0;c<N;c++)
                if (Cgot[r][c] !== Cexp[r][c]) begin
                    errors++;
                    $display("tile %0d MISMATCH C[%0d][%0d]: got %0d exp %0d",
                             tnum, r, c, Cgot[r][c], Cexp[r][c]);
                end
        $display("tile %0d done (errors so far %0d)", tnum, errors);
    endtask

    logic [31:0] tc;
    initial begin
        awvalid=0; wvalid=0; bready=0; arvalid=0; rready=0; wstrb=4'hF;
        a_tvalid=0; a_tlast=0; b_tvalid=0; b_tlast=0; c_tready=0;
        awaddr=0; wdata=0; araddr=0; a_tdata=0; b_tdata=0;
        rst=1; repeat(3) @(posedge clk); @(negedge clk); rst=0;

        // Tile 0: hand example padded
        for (int i=0;i<N;i++) for (int j=0;j<N;j++) begin Amat[i][j]=0; Bmat[i][j]=0; end
        Amat[0][0]=1; Amat[0][1]=2; Amat[1][0]=3; Amat[1][1]=4;
        Bmat[0][0]=5; Bmat[0][1]=6; Bmat[1][0]=7; Bmat[1][1]=8;
        run_tile(0);

        // Tile 1: small full matrices
        for (int i=0;i<N;i++) for (int j=0;j<N;j++) begin
            Amat[i][j] = (i+j) % 5 - 2;     // -2..2
            Bmat[i][j] = (i*2+j) % 7 - 3;   // -3..3
        end
        run_tile(1);

        // tile count should be 2
        axil_read(8'h08, tc);
        if (tc !== 32'h2) begin errors++; $display("TILE_CNT got %0d exp 2", tc); end
        else $display("ok TILE_CNT = 2");

        $display("----------------------------------------");
        if (errors==0) $display("RESULT: PASS");
        else           $display("RESULT: FAIL (%0d errors)", errors);
        $finish;
    end

    initial begin #2_000_000; $display("FATAL: timeout"); $finish; end
endmodule
