// tb_csr.sv -- directed test for csr.sv register semantics.
// Stubs the controller by driving core_busy/core_done from the TB.
// Run: verilator --binary -j 0 ../rtl/csr.sv tb_csr.sv --top-module tb_csr
//      ./obj_dir/Vtb_csr

module tb_csr;
    logic clk, rst;
    logic [7:0]  awaddr;  logic awvalid, awready;
    logic [31:0] wdata;   logic [3:0] wstrb; logic wvalid, wready;
    logic [1:0]  bresp;   logic bvalid, bready;
    logic [7:0]  araddr;  logic arvalid, arready;
    logic [31:0] rdata;   logic [1:0] rresp; logic rvalid, rready;
    logic start, soft_reset, core_busy, core_done, core_overflow, irq;

    int errors = 0;

    csr dut (
        .clk(clk), .rst(rst),
        .s_axil_awaddr(awaddr), .s_axil_awvalid(awvalid), .s_axil_awready(awready),
        .s_axil_wdata(wdata), .s_axil_wstrb(wstrb), .s_axil_wvalid(wvalid), .s_axil_wready(wready),
        .s_axil_bresp(bresp), .s_axil_bvalid(bvalid), .s_axil_bready(bready),
        .s_axil_araddr(araddr), .s_axil_arvalid(arvalid), .s_axil_arready(arready),
        .s_axil_rdata(rdata), .s_axil_rresp(rresp), .s_axil_rvalid(rvalid), .s_axil_rready(rready),
        .start(start), .soft_reset(soft_reset),
        .core_busy(core_busy), .core_done(core_done), .core_overflow(core_overflow),
        .irq(irq)
    );

    initial clk = 0; always #5 clk = ~clk;

    // ---- AXI4-Lite write ----
    task automatic axil_write(input [7:0] addr, input [31:0] data);
        @(negedge clk);
        awaddr=addr; awvalid=1; wdata=data; wstrb=4'hF; wvalid=1;
        // wait for both ready
        do @(posedge clk); while (!(awready && wready));
        @(negedge clk); awvalid=0; wvalid=0;
        bready=1;
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

    task automatic check(input [31:0] got, input [31:0] exp, input string name);
        if (got !== exp) begin
            errors++; $display("FAIL %s: got %h exp %h", name, got, exp);
        end else $display("ok   %s = %h", name, got);
    endtask

    logic [31:0] rd;
    initial begin
        awvalid=0; wvalid=0; bready=0; arvalid=0; rready=0;
        wstrb=4'hF; awaddr=0; wdata=0; araddr=0;
        core_busy=0; core_done=0; core_overflow=0;
        rst=1; repeat(3) @(posedge clk); @(negedge clk); rst=0;

        // VERSION constant
        axil_read(8'h10, rd); check(rd, 32'h0001_0000, "VERSION");

        // write start while idle -> start asserts
        axil_write(8'h00, 32'h1);
        @(posedge clk);
        check({31'd0, start}, 32'h1, "start asserted after CTRL write");

        // simulate controller running
        core_busy = 1;
        axil_read(8'h00, rd); check(rd, 32'h1, "CTRL.start reads 1 while busy");
        axil_read(8'h04, rd); check(rd, 32'h1, "STATUS.busy=1");

        // try to write start=0 while busy -> ignored (stays 1)
        axil_write(8'h00, 32'h0);
        @(posedge clk);
        check({31'd0, start}, 32'h1, "start unchanged by write while busy");

        // controller completes
        @(negedge clk); core_done = 1;
        @(posedge clk); @(negedge clk); core_done = 0; core_busy = 0;
        @(posedge clk);
        check({31'd0, start}, 32'h0, "start auto-cleared on done");

        // STATUS.done sticky set, TILE_CNT incremented
        axil_read(8'h04, rd); check({31'd0, rd[1]}, 32'h1, "STATUS.done sticky set");
        axil_read(8'h08, rd); check(rd, 32'h1, "TILE_CNT = 1");

        // W1C clear done
        axil_write(8'h04, 32'h2);   // write 1 to bit[1]
        axil_read(8'h04, rd); check({31'd0, rd[1]}, 32'h0, "STATUS.done cleared by W1C");

        // IRQ_EN + irq line
        axil_write(8'h0C, 32'h1);
        // trigger another done to set sticky again
        @(negedge clk); core_done=1; @(posedge clk); @(negedge clk); core_done=0;
        @(posedge clk);
        check({31'd0, irq}, 32'h1, "irq asserted (irq_en & done)");
        axil_read(8'h08, rd); check(rd, 32'h2, "TILE_CNT = 2");

        $display("----------------------------------------");
        if (errors == 0) $display("RESULT: PASS");
        else             $display("RESULT: FAIL (%0d errors)", errors);
        $finish;
    end

    initial begin #100000; $display("FATAL: timeout"); $finish; end
endmodule
