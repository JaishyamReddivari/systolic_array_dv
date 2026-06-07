// axis_if.sv -- AXI4-Stream interface (parameterized width).
// Used for A/B inputs (DATA_W=64) and C output (DATA_W=256).
// Three clocking blocks: master-drive (A/B), slave-drive (C consumer), monitor.

interface axis_if #(parameter int DATA_W = 64) (input logic clk, input logic rst);
    logic [DATA_W-1:0] tdata;
    logic              tvalid;
    logic              tready;
    logic              tlast;

    // master drives data/valid/last, samples ready  (used for A, B)
    clocking drv_cb @(posedge clk);
        default input #1step output #1;
        output tdata, tvalid, tlast;
        input  tready;
    endclocking

    // slave drives ready, samples data/valid/last    (used for C consumer)
    clocking slv_cb @(posedge clk);
        default input #1step output #1;
        input  tdata, tvalid, tlast;
        output tready;
    endclocking

    // passive monitor
    clocking mon_cb @(posedge clk);
        default input #1step;
        input tdata, tvalid, tready, tlast;
    endclocking

    modport drv (clocking drv_cb, input clk, input rst);
    modport slv (clocking slv_cb, input clk, input rst);
    modport mon (clocking mon_cb, input clk, input rst);
endinterface
