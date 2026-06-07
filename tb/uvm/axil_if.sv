// axil_if.sv -- AXI4-Lite interface (control/status).
// Master clocking drives the five channels; monitor observes all.

interface axil_if #(parameter int ADDR_W = 8, parameter int DATA_W = 32)
                   (input logic clk, input logic rst);
    logic [ADDR_W-1:0]   awaddr;  logic awvalid, awready;
    logic [DATA_W-1:0]   wdata;   logic [DATA_W/8-1:0] wstrb;
    logic                wvalid,  wready;
    logic [1:0]          bresp;   logic bvalid, bready;
    logic [ADDR_W-1:0]   araddr;  logic arvalid, arready;
    logic [DATA_W-1:0]   rdata;   logic [1:0] rresp; logic rvalid, rready;

    clocking drv_cb @(posedge clk);
        default input #1step output #1;
        output awaddr, awvalid, wdata, wstrb, wvalid, bready,
               araddr, arvalid, rready;
        input  awready, wready, bresp, bvalid, arready, rdata, rresp, rvalid;
    endclocking

    clocking mon_cb @(posedge clk);
        default input #1step;
        input awaddr, awvalid, awready, wdata, wstrb, wvalid, wready,
              bresp, bvalid, bready, araddr, arvalid, arready,
              rdata, rresp, rvalid, rready;
    endclocking

    modport drv (clocking drv_cb, input clk, input rst);
    modport mon (clocking mon_cb, input clk, input rst);
endinterface
