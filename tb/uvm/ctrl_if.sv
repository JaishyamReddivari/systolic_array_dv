// ctrl_if.sv -- minimal control interface for controller bring-up:
// start (driven by test), busy/done (observed). Replaced by the AXIL agent
// when the env retargets to systolic_top.
interface ctrl_if (input logic clk, input logic rst);
    logic start, busy, done;
    clocking cb @(posedge clk);
        default input #1step output #1;
        output start;
        input  busy, done;
    endclocking
endinterface
