// tb_top.sv -- UVM top for controller bring-up.
// Generates clk/rst, instantiates interfaces + the controller DUT, publishes
// virtual interfaces to the config_db, and runs the test.
`timescale 1ns/1ps
module tb_ctrl;
    import uvm_pkg::*;
    import systolic_uvm_pkg::*;
    `include "uvm_macros.svh"

    logic clk = 0;
    logic rst = 1;
    always #5 clk = ~clk;

    // interfaces
    axis_if #(64)  a_if (clk, rst);
    axis_if #(64)  b_if (clk, rst);
    axis_if #(256) c_if (clk, rst);
    ctrl_if        ctl   (clk, rst);

    // output consumer: no backpressure in bring-up
    assign c_if.tready = 1'b1;

    // DUT = controller (raw start)
    controller dut (
        .clk(clk), .rst(rst),
        .start(ctl.start), .busy(ctl.busy), .done(ctl.done),
        .s_axis_a_tdata(a_if.tdata), .s_axis_a_tvalid(a_if.tvalid),
        .s_axis_a_tready(a_if.tready), .s_axis_a_tlast(a_if.tlast),
        .s_axis_b_tdata(b_if.tdata), .s_axis_b_tvalid(b_if.tvalid),
        .s_axis_b_tready(b_if.tready), .s_axis_b_tlast(b_if.tlast),
        .m_axis_c_tdata(c_if.tdata), .m_axis_c_tvalid(c_if.tvalid),
        .m_axis_c_tready(c_if.tready), .m_axis_c_tlast(c_if.tlast)
    );

    initial begin
        // publish vifs
        uvm_config_db#(virtual axis_if #(64))::set (null, "*", "a_vif", a_if);
        uvm_config_db#(virtual axis_if #(64))::set (null, "*", "b_vif", b_if);
        uvm_config_db#(virtual axis_if #(256))::set(null, "*", "c_vif", c_if);
        uvm_config_db#(virtual ctrl_if)::set       (null, "*", "ctrl_vif", ctl);

        // run_test must be called at time 0 (no delays before it)
        run_test();
    end

    // reset runs concurrently; the test waits for rst==0 before driving
    initial begin
        rst = 1;
        repeat (4) @(posedge clk);
        rst = 0;
    end

    initial begin #200000; `uvm_fatal("TIMEOUT", "sim hung") end
endmodule
