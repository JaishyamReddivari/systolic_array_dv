// tb_top_full.sv -- UVM top for the FULL DUT (systolic_top).
// start comes from a real AXI4-Lite CTRL write; no ctrl_if shim.
`timescale 1ns/1ps
module tb_top;
    import uvm_pkg::*;
    import systolic_uvm_pkg::*;
    `include "uvm_macros.svh"

    logic clk = 0;
    logic rst = 1;
    always #5 clk = ~clk;

    axis_if #(64)   a_if (clk, rst);
    axis_if #(64)   b_if (clk, rst);
    axis_if #(256)  c_if (clk, rst);
    axil_if #(8,32) l_if (clk, rst);

    // output consumer: m_axis_c_tready driven by the UVM axis_slave_responder
    // (BP_NONE by default == always ready; CP3 tests switch its mode)

    systolic_top dut (
        .clk(clk), .rst(rst),
        .s_axis_a_tdata(a_if.tdata), .s_axis_a_tvalid(a_if.tvalid),
        .s_axis_a_tready(a_if.tready), .s_axis_a_tlast(a_if.tlast),
        .s_axis_b_tdata(b_if.tdata), .s_axis_b_tvalid(b_if.tvalid),
        .s_axis_b_tready(b_if.tready), .s_axis_b_tlast(b_if.tlast),
        .m_axis_c_tdata(c_if.tdata), .m_axis_c_tvalid(c_if.tvalid),
        .m_axis_c_tready(c_if.tready), .m_axis_c_tlast(c_if.tlast),
        .s_axil_awaddr(l_if.awaddr), .s_axil_awvalid(l_if.awvalid),
        .s_axil_awready(l_if.awready),
        .s_axil_wdata(l_if.wdata), .s_axil_wstrb(l_if.wstrb),
        .s_axil_wvalid(l_if.wvalid), .s_axil_wready(l_if.wready),
        .s_axil_bresp(l_if.bresp), .s_axil_bvalid(l_if.bvalid),
        .s_axil_bready(l_if.bready),
        .s_axil_araddr(l_if.araddr), .s_axil_arvalid(l_if.arvalid),
        .s_axil_arready(l_if.arready),
        .s_axil_rdata(l_if.rdata), .s_axil_rresp(l_if.rresp),
        .s_axil_rvalid(l_if.rvalid), .s_axil_rready(l_if.rready),
        .irq()
    );

    initial begin
        uvm_config_db#(virtual axis_if #(64))::set (null, "*", "a_vif", a_if);
        uvm_config_db#(virtual axis_if #(64))::set (null, "*", "b_vif", b_if);
        uvm_config_db#(virtual axis_if #(256))::set(null, "*", "c_vif", c_if);
        uvm_config_db#(virtual axil_if #(8,32))::set(null, "*", "csr_vif", l_if);
        // test selected at runtime via +UVM_TESTNAME=<test>
        run_test();
    end

    initial begin
        rst = 1;
        repeat (4) @(posedge clk);
        rst = 0;
    end

    initial begin #200000; `uvm_fatal("TIMEOUT", "sim hung") end
endmodule
