// systolic_top.sv -- top level: CSR + controller + array.
// External interfaces: AXI4-Stream A/B (in), C (out); AXI4-Lite (control); irq.
// Software writes CTRL.start to launch a tile; polls STATUS or waits on irq.
// soft_reset (CTRL[1]) forces the controller back to idle (OR'd into its reset).

module systolic_top (
    input  logic         clk,
    input  logic         rst,            // synchronous, active-high

    // ---- AXI4-Stream slave: A (weights) ----
    input  logic [63:0]  s_axis_a_tdata,
    input  logic         s_axis_a_tvalid,
    output logic         s_axis_a_tready,
    input  logic         s_axis_a_tlast,

    // ---- AXI4-Stream slave: B (activations) ----
    input  logic [63:0]  s_axis_b_tdata,
    input  logic         s_axis_b_tvalid,
    output logic         s_axis_b_tready,
    input  logic         s_axis_b_tlast,

    // ---- AXI4-Stream master: C (results) ----
    output logic [255:0] m_axis_c_tdata,
    output logic         m_axis_c_tvalid,
    input  logic         m_axis_c_tready,
    output logic         m_axis_c_tlast,

    // ---- AXI4-Lite slave: control/status ----
    input  logic [7:0]   s_axil_awaddr,
    input  logic         s_axil_awvalid,
    output logic         s_axil_awready,
    input  logic [31:0]  s_axil_wdata,
    input  logic [3:0]   s_axil_wstrb,
    input  logic         s_axil_wvalid,
    output logic         s_axil_wready,
    output logic [1:0]   s_axil_bresp,
    output logic         s_axil_bvalid,
    input  logic         s_axil_bready,
    input  logic [7:0]   s_axil_araddr,
    input  logic         s_axil_arvalid,
    output logic         s_axil_arready,
    output logic [31:0]  s_axil_rdata,
    output logic [1:0]   s_axil_rresp,
    output logic         s_axil_rvalid,
    input  logic         s_axil_rready,

    output logic         irq
);

    // ---- CSR <-> controller links ----
    logic start, soft_reset, core_busy, core_done;
    logic core_overflow = 1'b0;   // Rev A: overflow detection not implemented

    // soft_reset forces the controller (only) back to idle.
    logic ctrl_rst;
    assign ctrl_rst = rst | soft_reset;

    // ================= CSR =================
    csr u_csr (
        .clk(clk), .rst(rst),
        .s_axil_awaddr(s_axil_awaddr),  .s_axil_awvalid(s_axil_awvalid),
        .s_axil_awready(s_axil_awready),
        .s_axil_wdata(s_axil_wdata),    .s_axil_wstrb(s_axil_wstrb),
        .s_axil_wvalid(s_axil_wvalid),  .s_axil_wready(s_axil_wready),
        .s_axil_bresp(s_axil_bresp),    .s_axil_bvalid(s_axil_bvalid),
        .s_axil_bready(s_axil_bready),
        .s_axil_araddr(s_axil_araddr),  .s_axil_arvalid(s_axil_arvalid),
        .s_axil_arready(s_axil_arready),
        .s_axil_rdata(s_axil_rdata),    .s_axil_rresp(s_axil_rresp),
        .s_axil_rvalid(s_axil_rvalid),  .s_axil_rready(s_axil_rready),
        .start(start), .soft_reset(soft_reset),
        .core_busy(core_busy), .core_done(core_done), .core_overflow(core_overflow),
        .irq(irq)
    );

    // ================= controller (+ array inside) =================
    controller u_controller (
        .clk(clk), .rst(ctrl_rst),
        .start(start), .busy(core_busy), .done(core_done),
        .s_axis_a_tdata(s_axis_a_tdata),   .s_axis_a_tvalid(s_axis_a_tvalid),
        .s_axis_a_tready(s_axis_a_tready), .s_axis_a_tlast(s_axis_a_tlast),
        .s_axis_b_tdata(s_axis_b_tdata),   .s_axis_b_tvalid(s_axis_b_tvalid),
        .s_axis_b_tready(s_axis_b_tready), .s_axis_b_tlast(s_axis_b_tlast),
        .m_axis_c_tdata(m_axis_c_tdata),   .m_axis_c_tvalid(m_axis_c_tvalid),
        .m_axis_c_tready(m_axis_c_tready), .m_axis_c_tlast(m_axis_c_tlast)
    );

endmodule
