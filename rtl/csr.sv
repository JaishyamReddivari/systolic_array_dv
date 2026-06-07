// csr.sv -- AXI4-Lite control/status registers for systolic_array_dv.
// Own minimal AXI4-Lite slave decode + register file. Drives `start` to the
// controller and exposes busy/done/tile-count. Registers (spec 5.5):
//   0x00 CTRL     [0]=start(RW, set-when-idle, auto-clear on done) [1]=soft_reset
//   0x04 STATUS   [0]=busy(RO) [1]=done(RO,W1C) [2]=overflow(RO)
//   0x08 TILE_CNT (RO, ++ on each done)
//   0x0C IRQ_EN   [0]=done-interrupt enable (RW)
//   0x10 VERSION  (RO)

module csr (
    input  logic        clk,
    input  logic        rst,

    // ---- AXI4-Lite slave ----
    input  logic [7:0]  s_axil_awaddr,
    input  logic        s_axil_awvalid,
    output logic        s_axil_awready,
    input  logic [31:0] s_axil_wdata,
    input  logic [3:0]  s_axil_wstrb,      // accepted; full-word writes only
    input  logic        s_axil_wvalid,
    output logic        s_axil_wready,
    output logic [1:0]  s_axil_bresp,
    output logic        s_axil_bvalid,
    input  logic        s_axil_bready,
    input  logic [7:0]  s_axil_araddr,
    input  logic        s_axil_arvalid,
    output logic        s_axil_arready,
    output logic [31:0] s_axil_rdata,
    output logic [1:0]  s_axil_rresp,
    output logic        s_axil_rvalid,
    input  logic        s_axil_rready,

    // ---- to/from controller ----
    output logic        start,        // pulse-or-level trigger
    output logic        soft_reset,
    input  logic        core_busy,
    input  logic        core_done,
    input  logic        core_overflow,

    // ---- interrupt ----
    output logic        irq
);

    localparam logic [7:0] ADDR_CTRL   = 8'h00;
    localparam logic [7:0] ADDR_STATUS = 8'h04;
    localparam logic [7:0] ADDR_TILE   = 8'h08;
    localparam logic [7:0] ADDR_IRQ    = 8'h0C;
    localparam logic [7:0] ADDR_VER    = 8'h10;
    localparam logic [31:0] VERSION    = 32'h0001_0000;  // major 1, minor 0

    // ---- register state ----
    logic        start_reg, soft_reset_reg, done_sticky, irq_en;
    logic [31:0] tile_cnt;

    assign start      = start_reg;
    assign soft_reset = soft_reset_reg;
    assign irq        = irq_en & done_sticky;

    // ================= AXI4-Lite write channel =================
    logic        aw_seen, w_seen, bvalid_q;
    logic [7:0]  awaddr_q;
    logic [31:0] wdata_q;

    assign s_axil_awready = !aw_seen;
    assign s_axil_wready  = !w_seen;
    assign s_axil_bvalid  = bvalid_q;
    assign s_axil_bresp   = 2'b00;             // OKAY

    wire do_write = aw_seen && w_seen && !bvalid_q;

    // ================= AXI4-Lite read channel ==================
    logic        ar_seen, rvalid_q;
    logic [7:0]  araddr_q;
    logic [31:0] rdata_q;

    assign s_axil_arready = !ar_seen && !rvalid_q;
    assign s_axil_rvalid  = rvalid_q;
    assign s_axil_rresp   = 2'b00;
    assign s_axil_rdata   = rdata_q;

    // read data mux
    function automatic logic [31:0] read_reg(input logic [7:0] a);
        case (a)
            ADDR_CTRL:   read_reg = {30'd0, soft_reset_reg, start_reg};
            ADDR_STATUS: read_reg = {29'd0, core_overflow, done_sticky, core_busy};
            ADDR_TILE:   read_reg = tile_cnt;
            ADDR_IRQ:    read_reg = {31'd0, irq_en};
            ADDR_VER:    read_reg = VERSION;
            default:     read_reg = 32'd0;
        endcase
    endfunction

    // Strobes and upper data bits are intentionally unused: CSR registers are
    // written as full 32-bit words and only low bits are defined.
    logic _unused;
    assign _unused = &{1'b0, s_axil_wstrb, wdata_q[31:2]};

    // ================= sequential =================
    always_ff @(posedge clk) begin
        if (rst) begin
            aw_seen <= 0; w_seen <= 0; bvalid_q <= 0;
            ar_seen <= 0; rvalid_q <= 0;
            awaddr_q <= 0; wdata_q <= 0; araddr_q <= 0; rdata_q <= 0;
            start_reg <= 0; soft_reset_reg <= 0; done_sticky <= 0;
            irq_en <= 0; tile_cnt <= 0;
        end else begin
            soft_reset_reg <= 1'b0;   // default: soft_reset is a 1-cycle pulse

            // ---- write address/data capture ----
            if (s_axil_awvalid && s_axil_awready) begin
                awaddr_q <= s_axil_awaddr; aw_seen <= 1;
            end
            if (s_axil_wvalid && s_axil_wready) begin
                wdata_q <= s_axil_wdata; w_seen <= 1;
            end
            if (do_write) begin aw_seen <= 0; w_seen <= 0; bvalid_q <= 1; end
            if (bvalid_q && s_axil_bready) bvalid_q <= 0;

            // ---- read capture / response ----
            if (s_axil_arvalid && s_axil_arready) begin
                araddr_q <= s_axil_araddr; ar_seen <= 1;
            end
            if (ar_seen && !rvalid_q) begin
                rdata_q <= read_reg(araddr_q); rvalid_q <= 1; ar_seen <= 0;
            end
            if (rvalid_q && s_axil_rready) rvalid_q <= 0;

            // ---- register write effects (bus) ----
            if (do_write) begin
                case (awaddr_q)
                    ADDR_CTRL: begin
                        if (wdata_q[1]) begin
                            soft_reset_reg <= 1'b1;   // abort: pulse reset...
                            start_reg      <= 1'b0;   // ...and clear start
                        end else if (!core_busy) begin
                            start_reg <= wdata_q[0];  // set start only when idle
                        end
                    end
                    ADDR_STATUS: if (wdata_q[1]) done_sticky <= 0; // W1C
                    ADDR_IRQ:    irq_en <= wdata_q[0];
                    default: ;
                endcase
            end

            // ---- core-done effects (override bus same-cycle) ----
            if (core_done) begin
                start_reg   <= 0;             // auto-clear start
                done_sticky <= 1;             // set sticky done
                tile_cnt    <= tile_cnt + 1;
            end
        end
    end

endmodule
