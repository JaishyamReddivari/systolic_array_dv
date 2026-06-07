// systolic_uvm_pkg.sv -- UVM environment package for systolic_array_dv.
// Grows incrementally: step 1 = transaction items.

package systolic_uvm_pkg;
    import uvm_pkg::*;
    `include "uvm_macros.svh"

    localparam int N = 8;

    // ====================================================================
    // axis_tile_item -- one full 8x8 tile (A, B, or C).
    // A/B carry INT8 values (constrained to [-128,127]); C carries the INT32
    // result (filled by the monitor, not randomized). Stored uniformly as
    // 32-bit signed so one class serves all three streams.
    // ====================================================================
    class axis_tile_item extends uvm_sequence_item;
        typedef enum {KIND_A, KIND_B, KIND_C} kind_e;
        kind_e                  kind;          // set before randomize()
        rand bit signed [31:0]  matrix [N][N];

        // C-tile backpressure annotations, filled by the C monitor (CP3).
        // Default 0; meaningless for A/B tiles.
        int bp_stalls  = 0;     // stall cycles (tvalid && !tready) during the tile
        bit bp_on_last = 0;     // a stall coincided with tlast

        // INT8 range applies to driven (A/B) tiles; C is assigned, not solved.
        constraint c_int8 {
            if (kind != KIND_C)
                foreach (matrix[i,j]) matrix[i][j] inside {[-128:127]};
        }

        `uvm_object_utils(axis_tile_item)

        function new(string name = "axis_tile_item");
            super.new(name);
        endfunction

        virtual function void do_copy(uvm_object rhs);
            axis_tile_item r;
            if (!$cast(r, rhs)) `uvm_fatal("CAST", "do_copy failed")
            super.do_copy(rhs);
            kind = r.kind;
            foreach (matrix[i,j]) matrix[i][j] = r.matrix[i][j];
        endfunction

        virtual function bit do_compare(uvm_object rhs, uvm_comparer comparer);
            axis_tile_item r;
            bit eq = 1;
            if (!$cast(r, rhs)) return 0;
            eq &= super.do_compare(rhs, comparer);
            foreach (matrix[i,j])
                eq &= (matrix[i][j] === r.matrix[i][j]);
            return eq;
        endfunction

        virtual function string convert2string();
            string s = $sformatf("tile kind=%s\n", kind.name());
            foreach (matrix[i]) begin
                foreach (matrix[i][j]) s = {s, $sformatf("%0d ", matrix[i][j])};
                s = {s, "\n"};
            end
            return s;
        endfunction
    endclass

    // ====================================================================
    // axil_reg_item -- one AXI4-Lite register access (read or write).
    // ====================================================================
    class axil_reg_item extends uvm_sequence_item;
        typedef enum {OP_READ, OP_WRITE} op_e;
        rand op_e        op;
        rand bit [7:0]   addr;
        rand bit [31:0]  wdata;
        bit  [31:0]      rdata;     // filled on read

        // valid register offsets from spec 5.5
        constraint c_addr { addr inside {8'h00, 8'h04, 8'h08, 8'h0C, 8'h10}; }

        `uvm_object_utils(axil_reg_item)

        function new(string name = "axil_reg_item");
            super.new(name);
        endfunction

        virtual function string convert2string();
            return $sformatf("axil %s addr=0x%02h wdata=0x%08h rdata=0x%08h",
                             op.name(), addr, wdata, rdata);
        endfunction
    endclass

    // ====================================================================
    // axis_driver -- drives a tile item as 8 AXI4-Stream beats (master).
    // Used for A and B (parameterized only by which virtual interface it
    // gets via config_db). Packs row r of the tile into beat r: 8 x INT8
    // on a 64-bit bus, TLAST on the final beat. Uses drv_cb so all
    // drive/sample timing is race-free.
    // ====================================================================
    class axis_driver extends uvm_driver #(axis_tile_item);
        `uvm_component_utils(axis_driver)

        virtual axis_if #(64) vif;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(64))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axis_driver: no virtual interface set")
        endfunction

        task run_phase(uvm_phase phase);
            // idle until reset deasserts
            vif.tvalid = 0;
            vif.tlast  = 0;
            vif.tdata  = '0;
            wait (vif.rst == 0);

            forever begin
                axis_tile_item tr;
                seq_item_port.get_next_item(tr);
                drive_tile(tr);
                seq_item_port.item_done();
            end
        endtask

        task drive_tile(axis_tile_item tr);
            int r;
            r = 0;
            @(posedge vif.clk);                 // line up once, BEFORE the loop
            while (r < N) begin
                #1;
                vif.tvalid = 1'b1;
                vif.tlast  = (r == N-1);
                for (int j = 0; j < N; j++)
                    vif.tdata[j*8 +: 8] = tr.matrix[r][j][7:0];
                @(posedge vif.clk);             // beat shown for ONE cycle; sample here
                if (vif.tready === 1'b1) begin
                    `uvm_info("DRV", $sformatf("beat %0d accepted", r), UVM_HIGH)
                    r++;
                end
            end
            #1;
            vif.tvalid = 1'b0;
            vif.tlast  = 1'b0;
            `uvm_info("DRV", $sformatf("tile fully driven: %0d beats", r), UVM_LOW)
        endtask
    endclass

    // ====================================================================
    // axis_in_monitor -- observes a 64-bit input stream (A or B), rebuilds
    // an INT8 tile from 8 beats, publishes via analysis port.
    // ====================================================================
    class axis_in_monitor extends uvm_monitor;
        `uvm_component_utils(axis_in_monitor)
        virtual axis_if #(64) vif;
        int kind_id;                                  // 0=A, 1=B
        uvm_analysis_port #(axis_tile_item) ap;

        function new(string name, uvm_component parent);
            super.new(name, parent);
            ap = new("ap", this);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(64))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axis_in_monitor: no vif")
            void'(uvm_config_db#(int)::get(this, "", "kind_id", kind_id));
        endfunction

        task run_phase(uvm_phase phase);
            forever begin
                axis_tile_item tr = axis_tile_item::type_id::create("tr");
                int r = 0;
                tr.kind = (kind_id == 0) ? axis_tile_item::KIND_A
                                         : axis_tile_item::KIND_B;
                while (r < N) begin
                    @(vif.mon_cb);
                    if (vif.mon_cb.tvalid && vif.mon_cb.tready) begin
                        for (int j = 0; j < N; j++)
                            tr.matrix[r][j] = $signed(vif.mon_cb.tdata[j*8 +: 8]);
                        r++;
                    end
                end
                ap.write(tr);
            end
        endtask
    endclass

    // ====================================================================
    // axis_out_monitor -- observes the 256-bit output stream (C), rebuilds
    // an INT32 tile from 8 beats.
    // ====================================================================
    class axis_out_monitor extends uvm_monitor;
        `uvm_component_utils(axis_out_monitor)
        virtual axis_if #(256) vif;
        uvm_analysis_port #(axis_tile_item) ap;

        function new(string name, uvm_component parent);
            super.new(name, parent);
            ap = new("ap", this);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(256))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axis_out_monitor: no vif")
        endfunction

        task run_phase(uvm_phase phase);
            forever begin
                axis_tile_item tr = axis_tile_item::type_id::create("tr");
                int r = 0;
                int stalls = 0;
                bit on_last = 0;
                tr.kind = axis_tile_item::KIND_C;
                while (r < N) begin
                    @(vif.mon_cb);
                    // stall = valid presented but not accepted (CP3)
                    if (vif.mon_cb.tvalid && !vif.mon_cb.tready) begin
                        stalls++;
                        if (vif.mon_cb.tlast) on_last = 1;
                    end
                    if (vif.mon_cb.tvalid && vif.mon_cb.tready) begin
                        for (int j = 0; j < N; j++)
                            tr.matrix[r][j] = $signed(vif.mon_cb.tdata[j*32 +: 32]);
                        `uvm_info("CMON", $sformatf("C beat %0d captured", r), UVM_HIGH)
                        r++;
                    end
                end
                tr.bp_stalls  = stalls;
                tr.bp_on_last = on_last;
                ap.write(tr);
            end
        endtask
    endclass

    // ====================================================================
    // axis_slave_responder -- drives m_axis_c_tready to generate output
    // backpressure on the C channel (CP3). Mode is switchable at runtime by
    // the test via the public `mode` field:
    //   BP_NONE   : tready always 1 (no backpressure; default)
    //   BP_RANDOM : tready high ~60% of cycles (mid-tile stalls)
    //   BP_LAST   : hold the final (tlast) beat low for 3 cycles (directed)
    // Drives the raw signal with #1 post-edge skew, matching the input
    // drivers' house style.
    // ====================================================================
    class axis_slave_responder extends uvm_component;
        `uvm_component_utils(axis_slave_responder)
        typedef enum {BP_NONE, BP_RANDOM, BP_LAST} bp_mode_e;
        bp_mode_e mode = BP_NONE;          // test flips this between tiles
        virtual axis_if #(256) vif;
        int last_cnt;                       // BP_LAST stall counter

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(256))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axis_slave_responder: no vif")
        endfunction

        task run_phase(uvm_phase phase);
            vif.tready = 1'b1;              // idle = ready to accept
            last_cnt   = 0;
            wait (vif.rst == 0);
            forever begin
                @(posedge vif.clk);
                #1;
                case (mode)
                    BP_RANDOM: vif.tready = ($urandom_range(0, 9) < 6);  // ~60%
                    BP_LAST: begin
                        if (vif.tvalid && vif.tlast && last_cnt < 3) begin
                            vif.tready = 1'b0;                  // hold the last beat
                            last_cnt++;
                        end else begin
                            vif.tready = 1'b1;                  // accept
                            if (!(vif.tvalid && vif.tlast))     // rearm between tiles
                                last_cnt = 0;
                        end
                    end
                    default: vif.tready = 1'b1;                 // BP_NONE
                endcase
            end
        endtask
    endclass

    // ====================================================================
    // axis_in_agent -- sequencer + driver + monitor for one input stream.
    // kind_id (0=A,1=B) selects which stream; vif comes from config_db.
    // ====================================================================
    class axis_in_agent extends uvm_agent;
        `uvm_component_utils(axis_in_agent)
        int kind_id;
        virtual axis_if #(64) vif;
        uvm_sequencer #(axis_tile_item) seqr;
        axis_driver                     drv;
        axis_in_monitor                 mon;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(64))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axis_in_agent: no vif")
            // hand vif/kind down to children
            uvm_config_db#(virtual axis_if #(64))::set(this, "drv", "vif", vif);
            uvm_config_db#(virtual axis_if #(64))::set(this, "mon", "vif", vif);
            uvm_config_db#(int)::set(this, "mon", "kind_id", kind_id);

            seqr = uvm_sequencer#(axis_tile_item)::type_id::create("seqr", this);
            drv  = axis_driver::type_id::create("drv", this);
            mon  = axis_in_monitor::type_id::create("mon", this);
        endfunction

        function void connect_phase(uvm_phase phase);
            drv.seq_item_port.connect(seqr.seq_item_export);
        endfunction
    endclass

    // ====================================================================
    // scoreboard -- buffers A and B (from input monitors), predicts C with
    // a SystemVerilog behavioral matmul, compares to observed C.
    // (C++ DPI reference added later as a parallel cross-check.)
    // ====================================================================
    `uvm_analysis_imp_decl(_a)
    `uvm_analysis_imp_decl(_b)
    `uvm_analysis_imp_decl(_c)

    class axis_scoreboard extends uvm_scoreboard;
        `uvm_component_utils(axis_scoreboard)
        uvm_analysis_imp_a #(axis_tile_item, axis_scoreboard) a_imp;
        uvm_analysis_imp_b #(axis_tile_item, axis_scoreboard) b_imp;
        uvm_analysis_imp_c #(axis_tile_item, axis_scoreboard) c_imp;

        axis_tile_item a_tile, b_tile;
        bit have_a, have_b;
        int tiles_checked, mismatches;
        uvm_phase end_phase;        // objection dropped here when a tile checks
        int tiles_target = 1;       // drop after this many tiles checked
        bit own_objection = 0;      // if set, scoreboard raises/drops its own
        uvm_event tile_done_ev = new("tile_done_ev");  // triggered each check

        function new(string name, uvm_component parent);
            super.new(name, parent);
            a_imp = new("a_imp", this);
            b_imp = new("b_imp", this);
            c_imp = new("c_imp", this);
        endfunction

        function void write_a(axis_tile_item t); a_tile = t; have_a = 1; endfunction
        function void write_b(axis_tile_item t); b_tile = t; have_b = 1; endfunction

        task run_phase(uvm_phase phase);
            end_phase = phase;
            if (own_objection) phase.raise_objection(this);
        endtask

        function void write_c(axis_tile_item t);
            int exp;
            bit ok = 1;
            if (!have_a || !have_b) begin
                `uvm_error("SB", "C arrived before A/B")
                return;
            end
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) begin
                    exp = 0;
                    for (int k = 0; k < N; k++)
                        exp += a_tile.matrix[i][k] * b_tile.matrix[k][j];
                    if (t.matrix[i][j] !== exp) begin
                        ok = 0; mismatches++;
                        `uvm_error("SB", $sformatf("C[%0d][%0d] got %0d exp %0d",
                                   i, j, t.matrix[i][j], exp))
                    end
                end
            tiles_checked++;
            if (ok) `uvm_info("SB", $sformatf("tile %0d OK", tiles_checked), UVM_LOW)
            have_a = 0; have_b = 0;
            tile_done_ev.trigger();     // cross-process signal to the test

            // signal completion: drop the run-phase objection when done
            if (own_objection && end_phase != null && tiles_checked >= tiles_target)
                end_phase.drop_objection(this);
        endfunction

        function void report_phase(uvm_phase phase);
            `uvm_info("SB", $sformatf("checked=%0d mismatches=%0d",
                      tiles_checked, mismatches), UVM_NONE)
        endfunction
    endclass

    // ====================================================================
    // single_tile_seq -- generates one randomized tile of a given kind.
    // ====================================================================
    class single_tile_seq extends uvm_sequence #(axis_tile_item);
        `uvm_object_utils(single_tile_seq)
        axis_tile_item::kind_e kind = axis_tile_item::KIND_A;

        function new(string name = "single_tile_seq");
            super.new(name);
        endfunction

        task body();
            axis_tile_item tr = axis_tile_item::type_id::create("tr");
            tr.kind = kind;                       // set BEFORE randomize
            start_item(tr);
            if (!tr.randomize())
                `uvm_error("SEQ", "tile randomize failed")
            finish_item(tr);
        endtask
    endclass

    // ====================================================================
    // env -- two input agents (A,B), one output monitor (C), scoreboard.
    // ====================================================================
    // ====================================================================
    // axil_driver -- drives AXI4-Lite read/write transactions (master).
    // Single-beat Lite transfers, signals driven directly with edge timing.
    // On a read, captures rdata back into the item.
    // ====================================================================
    class axil_driver extends uvm_driver #(axil_reg_item);
        `uvm_component_utils(axil_driver)
        virtual axil_if #(8,32) vif;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axil_if #(8,32))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axil_driver: no vif")
        endfunction

        task run_phase(uvm_phase phase);
            // idle
            vif.awvalid = 0; vif.wvalid = 0; vif.bready = 0;
            vif.arvalid = 0; vif.rready = 0;
            vif.awaddr = 0; vif.wdata = 0; vif.wstrb = 4'hF; vif.araddr = 0;
            wait (vif.rst == 0);

            forever begin
                axil_reg_item tr;
                seq_item_port.get_next_item(tr);
                if (tr.op == axil_reg_item::OP_WRITE) do_write(tr);
                else                                  do_read(tr);
                seq_item_port.item_done();
            end
        endtask

        task do_write(axil_reg_item tr);
            @(posedge vif.clk); #1;
            vif.awaddr = tr.addr; vif.awvalid = 1;
            vif.wdata  = tr.wdata; vif.wstrb = 4'hF; vif.wvalid = 1;
            // wait until both address and data accepted
            forever begin
                @(posedge vif.clk);
                if (vif.awready && vif.wready) break;
            end
            #1; vif.awvalid = 0; vif.wvalid = 0;
            vif.bready = 1;
            forever begin
                @(posedge vif.clk);
                if (vif.bvalid) break;
            end
            #1; vif.bready = 0;
        endtask

        task do_read(axil_reg_item tr);
            @(posedge vif.clk); #1;
            vif.araddr = tr.addr; vif.arvalid = 1; vif.rready = 1;
            forever begin
                @(posedge vif.clk);
                if (vif.arready) break;
            end
            #1; vif.arvalid = 0;
            forever begin
                @(posedge vif.clk);
                if (vif.rvalid) begin tr.rdata = vif.rdata; break; end
            end
            #1; vif.rready = 0;
        endtask
    endclass

    // ====================================================================
    // axil_monitor -- passive: reconstructs completed Lite transactions and
    // publishes them as axil_reg_item (op/addr/data) for CSR coverage (CP5).
    // ====================================================================
    class axil_monitor extends uvm_component;
        `uvm_component_utils(axil_monitor)
        virtual axil_if #(8,32) vif;
        uvm_analysis_port #(axil_reg_item) ap;

        function new(string name, uvm_component parent);
            super.new(name, parent);
            ap = new("ap", this);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axil_if #(8,32))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axil_monitor: no vif")
        endfunction

        task run_phase(uvm_phase phase);
            bit [7:0]  waddr = 0, raddr = 0;
            bit [31:0] wdat  = 0;
            bit aw_seen = 0, w_seen = 0;
            forever begin
                @(vif.mon_cb);
                if (vif.mon_cb.awvalid && vif.mon_cb.awready) begin
                    waddr = vif.mon_cb.awaddr; aw_seen = 1;
                end
                if (vif.mon_cb.wvalid && vif.mon_cb.wready) begin
                    wdat = vif.mon_cb.wdata; w_seen = 1;
                end
                if (vif.mon_cb.bvalid && vif.mon_cb.bready && aw_seen && w_seen) begin
                    axil_reg_item tr = axil_reg_item::type_id::create("tr");
                    tr.op = axil_reg_item::OP_WRITE; tr.addr = waddr; tr.wdata = wdat;
                    ap.write(tr);
                    aw_seen = 0; w_seen = 0;
                end
                if (vif.mon_cb.arvalid && vif.mon_cb.arready)
                    raddr = vif.mon_cb.araddr;
                if (vif.mon_cb.rvalid && vif.mon_cb.rready) begin
                    axil_reg_item tr = axil_reg_item::type_id::create("tr");
                    tr.op = axil_reg_item::OP_READ; tr.addr = raddr;
                    tr.rdata = vif.mon_cb.rdata;
                    ap.write(tr);
                end
            end
        endtask
    endclass

    // ====================================================================
    // axil_agent -- sequencer + driver (+ optional monitor) for the CSR.
    // ====================================================================
    class axil_agent extends uvm_agent;
        `uvm_component_utils(axil_agent)
        virtual axil_if #(8,32) vif;
        uvm_sequencer #(axil_reg_item) seqr;
        axil_driver                    drv;
        axil_monitor                   mon;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axil_if #(8,32))::get(this, "", "vif", vif))
                `uvm_fatal("NOVIF", "axil_agent: no vif")
            uvm_config_db#(virtual axil_if #(8,32))::set(this, "drv", "vif", vif);
            uvm_config_db#(virtual axil_if #(8,32))::set(this, "mon", "vif", vif);
            seqr = uvm_sequencer#(axil_reg_item)::type_id::create("seqr", this);
            drv  = axil_driver::type_id::create("drv", this);
            mon  = axil_monitor::type_id::create("mon", this);
        endfunction

        function void connect_phase(uvm_phase phase);
            drv.seq_item_port.connect(seqr.seq_item_export);
        endfunction
    endclass

    // ====================================================================
    // CSR sequences: write a register, read a register.
    // ====================================================================
    class axil_write_seq extends uvm_sequence #(axil_reg_item);
        `uvm_object_utils(axil_write_seq)
        rand bit [7:0]  addr;
        rand bit [31:0] data;
        function new(string name = "axil_write_seq"); super.new(name); endfunction
        task body();
            axil_reg_item tr = axil_reg_item::type_id::create("tr");
            start_item(tr);
            tr.op = axil_reg_item::OP_WRITE; tr.addr = addr; tr.wdata = data;
            finish_item(tr);
        endtask
    endclass

    class axil_read_seq extends uvm_sequence #(axil_reg_item);
        `uvm_object_utils(axil_read_seq)
        rand bit [7:0] addr;
        bit [31:0]     result;          // captured after finish_item
        function new(string name = "axil_read_seq"); super.new(name); endfunction
        task body();
            axil_reg_item tr = axil_reg_item::type_id::create("tr");
            start_item(tr);
            tr.op = axil_reg_item::OP_READ; tr.addr = addr;
            finish_item(tr);
            result = tr.rdata;
        endtask
    endclass


    // ====================================================================
    // coverage collector -- functional coverage per the vplan.
    // Subscribes to A/B input monitors and the C output monitor.
    //   CP1 operand range (per A, per B element, sampled on a few cells)
    //   CP2 result magnitude (C)
    //   CP5 not here (CSR access covered in the CSR collector later)
    //   cross A_range x B_range
    // (CP3 backpressure / CP4 tile spacing are sampled by the sequences in
    //  later steps; this collector covers the data-value model.)
    // ====================================================================
    `uvm_analysis_imp_decl(_cva)
    `uvm_analysis_imp_decl(_cvb)
    `uvm_analysis_imp_decl(_cvc)

    // ====================================================================
    // axis_coverage -- MANUAL functional coverage (Verilator has no
    // covergroup support). Same bin model as the vplan; bins tracked with
    // hit counters and percentages computed by hand.
    //   CP1 operand range (A, B): neg/zero/pos/max_pos/max_neg   (5 bins each)
    //   CP2 result magnitude (C): zero/small/large/near_max      (4 bins)
    //   cross A_range x B_range (neg/zero/pos each):             (9 bins)
    // ====================================================================
    class axis_coverage extends uvm_component;
        `uvm_component_utils(axis_coverage)
        `uvm_analysis_imp_decl(_csr)
        uvm_analysis_imp_cva #(axis_tile_item, axis_coverage) a_imp;
        uvm_analysis_imp_cvb #(axis_tile_item, axis_coverage) b_imp;
        uvm_analysis_imp_cvc #(axis_tile_item, axis_coverage) c_imp;
        uvm_analysis_imp_csr #(axil_reg_item, axis_coverage)  csr_imp;

        // hit counts (index = bin id). [0]neg [1]zero [2]pos [3]max_pos [4]max_neg
        int a_bins[5], b_bins[5], c_bins[4];
        // cross: 3x3 (a:neg/zero/pos) x (b:neg/zero/pos)
        int x_bins[3][3];
        // remember last A tile's per-cell sign class for the cross
        int a_sign[8][8];
        bit have_a_tile;
        int bp_bins[3];          // CP3: [0]none [1]stall [2]stall_on_last
        // CP4 spacing + Cross2 (backpressure x spacing)
        int sp_bins[3];          // [0]b2b [1]gapped [2]abort
        int x2_bins[2][2];       // [bp:0 none,1 stall][sp:0 b2b,1 gapped]
        int last_bp;             // bp class of the most recent C tile, for cross2
        typedef enum {SP_B2B, SP_GAPPED, SP_ABORT} spacing_e;
        int cp5_bins[9];         // CSR access: see write_csr for index map

        function new(string name, uvm_component parent);
            super.new(name, parent);
            a_imp = new("a_imp", this);
            b_imp = new("b_imp", this);
            c_imp = new("c_imp", this);
            csr_imp = new("csr_imp", this);
        endfunction

        // operand bin id: 0 neg, 1 zero, 2 pos, 3 max_pos(127), 4 max_neg(-128)
        function int op_bin(int v);
            if      (v == 0)    op_bin = 1;
            else if (v == 127)  op_bin = 3;
            else if (v == -128) op_bin = 4;
            else if (v < 0)     op_bin = 0;
            else                op_bin = 2;
        endfunction

        // sign class for cross: 0 neg, 1 zero, 2 pos
        function int sign_bin(int v);
            if      (v < 0) sign_bin = 0;
            else if (v == 0) sign_bin = 1;
            else            sign_bin = 2;
        endfunction

        // result magnitude: 0 zero, 1 small, 2 large, 3 near_max
        function int res_bin(int v);
            int a = (v < 0) ? -v : v;
            if      (a == 0)        res_bin = 0;
            else if (a <= 1000)     res_bin = 1;
            else if (a <= 100000)   res_bin = 2;
            else                    res_bin = 3;
        endfunction

        function void write_cva(axis_tile_item t);
            foreach (t.matrix[i,j]) begin
                a_bins[op_bin(t.matrix[i][j])]++;
                a_sign[i][j] = sign_bin(t.matrix[i][j]);
            end
            have_a_tile = 1;
        endfunction

        function void write_cvb(axis_tile_item t);
            foreach (t.matrix[i,j]) begin
                b_bins[op_bin(t.matrix[i][j])]++;
                if (have_a_tile)
                    x_bins[a_sign[i][j]][sign_bin(t.matrix[i][j])]++;
            end
        endfunction

        function void write_cvc(axis_tile_item t);
            foreach (t.matrix[i,j])
                c_bins[res_bin(t.matrix[i][j])]++;
            // CP3: output backpressure pattern for this tile
            if (t.bp_stalls == 0) bp_bins[0]++;             // none
            else begin
                bp_bins[1]++;                               // stalled
                if (t.bp_on_last) bp_bins[2]++;             // stalled on last beat
            end
            last_bp = (t.bp_stalls == 0) ? 0 : 1;           // for cross2
        endfunction

        // CP4: spacing class for the tile just completed (or aborted), called
        // by the test. For completing tiles it also bins the backpressure cross.
        function void sample_spacing(spacing_e s);
            sp_bins[s]++;
            if (s == SP_B2B || s == SP_GAPPED)
                x2_bins[last_bp][s]++;       // s is 0/1 -> column index
        endfunction

        // CP5 index map: 0 CTRL.start 1 CTRL.soft_reset 2 CTRL.read
        //   3 STATUS.read 4 STATUS.w1c 5 TILE_CNT.read
        //   6 IRQ_EN.write 7 IRQ_EN.read 8 VERSION.read
        function void write_csr(axil_reg_item t);
            bit wr = (t.op == axil_reg_item::OP_WRITE);
            case (t.addr)
                8'h00: if (wr) begin
                           if (t.wdata[1])      cp5_bins[1]++;   // soft_reset
                           else if (t.wdata[0]) cp5_bins[0]++;   // start
                       end else cp5_bins[2]++;                   // CTRL read
                8'h04: if (wr) cp5_bins[4]++; else cp5_bins[3]++;
                8'h08: if (!wr) cp5_bins[5]++;
                8'h0C: if (wr) cp5_bins[6]++; else cp5_bins[7]++;
                8'h10: if (!wr) cp5_bins[8]++;
                default: ;
            endcase
        endfunction

        // percentage of bins in an array that were hit at least once
        function real pct(int arr[], int n);
            int hit = 0;
            for (int k = 0; k < n; k++) if (arr[k] > 0) hit++;
            return (100.0 * hit) / n;
        endfunction

        function void report_phase(uvm_phase phase);
            int xhit = 0, x2hit = 0;
            real xpct, x2pct;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (x_bins[i][j] > 0) xhit++;
            xpct = (100.0 * xhit) / 9.0;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    if (x2_bins[i][j] > 0) x2hit++;
            x2pct = (100.0 * x2hit) / 4.0;

            `uvm_info("COV", $sformatf(
                "CP1_A=%.1f%% CP1_B=%.1f%% CP2_C=%.1f%% cross=%.1f%% CP3_BP=%.1f%% CP4_SP=%.1f%% cross2=%.1f%% CP5_CSR=%.1f%%",
                pct(a_bins,5), pct(b_bins,5), pct(c_bins,4), xpct,
                pct(bp_bins,3), pct(sp_bins,3), x2pct, pct(cp5_bins,9)), UVM_NONE)
            `uvm_info("COV", $sformatf("A bins neg=%0d zero=%0d pos=%0d max+=%0d max-=%0d",
                a_bins[0],a_bins[1],a_bins[2],a_bins[3],a_bins[4]), UVM_NONE)
            `uvm_info("COV", $sformatf("B bins neg=%0d zero=%0d pos=%0d max+=%0d max-=%0d",
                b_bins[0],b_bins[1],b_bins[2],b_bins[3],b_bins[4]), UVM_NONE)
            `uvm_info("COV", $sformatf("C bins zero=%0d small=%0d large=%0d near_max=%0d",
                c_bins[0],c_bins[1],c_bins[2],c_bins[3]), UVM_NONE)
            `uvm_info("COV", $sformatf("BP bins none=%0d stall=%0d on_last=%0d",
                bp_bins[0], bp_bins[1], bp_bins[2]), UVM_NONE)
            `uvm_info("COV", $sformatf("SP bins b2b=%0d gapped=%0d abort=%0d",
                sp_bins[0], sp_bins[1], sp_bins[2]), UVM_NONE)
            `uvm_info("COV", $sformatf(
                "CP5 start=%0d srst=%0d ctrl_rd=%0d stat_rd=%0d w1c=%0d tcnt_rd=%0d irq_wr=%0d irq_rd=%0d ver_rd=%0d",
                cp5_bins[0],cp5_bins[1],cp5_bins[2],cp5_bins[3],cp5_bins[4],
                cp5_bins[5],cp5_bins[6],cp5_bins[7],cp5_bins[8]), UVM_NONE)
            `uvm_info("COV", $sformatf(
                "cross2 none/b2b=%0d none/gap=%0d stall/b2b=%0d stall/gap=%0d",
                x2_bins[0][0], x2_bins[0][1], x2_bins[1][0], x2_bins[1][1]), UVM_NONE)
            `uvm_info("COV", $sformatf("cross A=neg  : B neg=%0d zero=%0d pos=%0d",
                x_bins[0][0], x_bins[0][1], x_bins[0][2]), UVM_NONE)
            `uvm_info("COV", $sformatf("cross A=zero : B neg=%0d zero=%0d pos=%0d",
                x_bins[1][0], x_bins[1][1], x_bins[1][2]), UVM_NONE)
            `uvm_info("COV", $sformatf("cross A=pos  : B neg=%0d zero=%0d pos=%0d",
                x_bins[2][0], x_bins[2][1], x_bins[2][2]), UVM_NONE)
        endfunction
    endclass

    class systolic_env extends uvm_env;
        `uvm_component_utils(systolic_env)
        axis_in_agent   a_agent, b_agent;
        axis_out_monitor c_mon;
        axis_scoreboard  sb;
        axis_coverage    cov;
        axil_agent       csr_agent;          // present only at top level
        axis_slave_responder c_resp;
        virtual axis_if #(64)  a_vif, b_vif;
        virtual axis_if #(256) c_vif;
        virtual axil_if #(8,32) csr_vif;
        bit have_csr;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            if (!uvm_config_db#(virtual axis_if #(64))::get(this, "", "a_vif", a_vif))
                `uvm_fatal("NOVIF", "env: no a_vif")
            if (!uvm_config_db#(virtual axis_if #(64))::get(this, "", "b_vif", b_vif))
                `uvm_fatal("NOVIF", "env: no b_vif")
            if (!uvm_config_db#(virtual axis_if #(256))::get(this, "", "c_vif", c_vif))
                `uvm_fatal("NOVIF", "env: no c_vif")

            // push vifs to children before they build
            uvm_config_db#(virtual axis_if #(64))::set(this, "a_agent", "vif", a_vif);
            uvm_config_db#(virtual axis_if #(64))::set(this, "b_agent", "vif", b_vif);
            uvm_config_db#(virtual axis_if #(256))::set(this, "c_mon", "vif", c_vif);
            uvm_config_db#(virtual axis_if #(256))::set(this, "c_resp", "vif", c_vif);


            a_agent = axis_in_agent::type_id::create("a_agent", this);
            b_agent = axis_in_agent::type_id::create("b_agent", this);
            a_agent.kind_id = 0;
            b_agent.kind_id = 1;

            c_mon = axis_out_monitor::type_id::create("c_mon", this);
            c_resp = axis_slave_responder::type_id::create("c_resp", this);
            sb    = axis_scoreboard::type_id::create("sb", this);
            cov   = axis_coverage::type_id::create("cov", this);

            // build the CSR agent only if a Lite interface was provided
            have_csr = uvm_config_db#(virtual axil_if #(8,32))::get(
                          this, "", "csr_vif", csr_vif);
            if (have_csr) begin
                uvm_config_db#(virtual axil_if #(8,32))::set(
                    this, "csr_agent", "vif", csr_vif);
                csr_agent = axil_agent::type_id::create("csr_agent", this);
            end
        endfunction

        function void connect_phase(uvm_phase phase);
            a_agent.mon.ap.connect(sb.a_imp);
            b_agent.mon.ap.connect(sb.b_imp);
            c_mon.ap.connect(sb.c_imp);
            // analysis ports fan out to coverage as well
            a_agent.mon.ap.connect(cov.a_imp);
            b_agent.mon.ap.connect(cov.b_imp);
            c_mon.ap.connect(cov.c_imp);
            if (have_csr) csr_agent.mon.ap.connect(cov.csr_imp);
        endfunction
    endclass

    // ====================================================================
    // ctrl_vif typedef + base test -- pulses start, runs A/B seqs, waits done.
    // ====================================================================
    typedef virtual ctrl_if ctrl_vif_t;

    class single_tile_test extends uvm_test;
        `uvm_component_utils(single_tile_test)
        systolic_env env;
        ctrl_vif_t   ctrl_vif;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            env = systolic_env::type_id::create("env", this);
            if (!uvm_config_db#(ctrl_vif_t)::get(this, "", "ctrl_vif", ctrl_vif))
                `uvm_fatal("NOVIF", "test: no ctrl_vif")
        endfunction

        task run_phase(uvm_phase phase);
            single_tile_seq a_seq, b_seq;

            phase.raise_objection(this);        // own the objection up front

            wait (ctrl_vif.rst == 0);
            @(posedge ctrl_vif.clk);
            `uvm_info("TEST", "reset done, pulsing start", UVM_LOW)

            ctrl_vif.start = 1'b1;
            @(posedge ctrl_vif.clk);
            #1 ctrl_vif.start = 1'b0;
            `uvm_info("TEST", "start pulsed, launching A/B sequences", UVM_LOW)

            a_seq = single_tile_seq::type_id::create("a_seq");
            b_seq = single_tile_seq::type_id::create("b_seq");
            a_seq.kind = axis_tile_item::KIND_A;
            b_seq.kind = axis_tile_item::KIND_B;
            fork
                a_seq.start(env.a_agent.seqr);
                b_seq.start(env.b_agent.seqr);
            join
            `uvm_info("TEST", "A/B driven; waiting for scoreboard check", UVM_LOW)

            env.sb.tile_done_ev.wait_trigger();   // SB fires this when C is checked
            repeat (2) @(posedge ctrl_vif.clk);
            phase.drop_objection(this);
        endtask
    endclass


    // ====================================================================
    // top_tile_test -- full-DUT test against systolic_top: start via CSR
    // write (CTRL=0x1), drive A/B, scoreboard checks C. No ctrl_if shim.
    // ====================================================================
    class top_tile_test extends uvm_test;
        `uvm_component_utils(top_tile_test)
        systolic_env env;

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            env = systolic_env::type_id::create("env", this);
        endfunction

        task run_phase(uvm_phase phase);
            single_tile_seq a_seq, b_seq;
            axil_write_seq  start_seq;

            phase.raise_objection(this);          // own the objection up front

            wait (env.csr_vif.rst == 0);
            repeat (2) @(posedge env.csr_vif.clk);

            start_seq = axil_write_seq::type_id::create("start_seq");
            start_seq.addr = 8'h00; start_seq.data = 32'h1;
            start_seq.start(env.csr_agent.seqr);
            `uvm_info("TEST", "CTRL.start written via AXI4-Lite", UVM_LOW)

            a_seq = single_tile_seq::type_id::create("a_seq");
            b_seq = single_tile_seq::type_id::create("b_seq");
            a_seq.kind = axis_tile_item::KIND_A;
            b_seq.kind = axis_tile_item::KIND_B;
            fork
                a_seq.start(env.a_agent.seqr);
                b_seq.start(env.b_agent.seqr);
            join
            `uvm_info("TEST", "A/B driven; waiting for scoreboard check", UVM_LOW)

            env.sb.tile_done_ev.wait_trigger();   // SB triggers this on each C check
            repeat (2) @(posedge env.csr_vif.clk);
            phase.drop_objection(this);
        endtask
    endclass

    // ====================================================================
    // corner_tile_seq -- directed INT8 corner tile (all max_pos, all max_neg,
    // all zero, or a checkerboard of +127/-128) to hit the corner bins that
    // random draws rarely produce. `mode` selects which.
    // ====================================================================
    class corner_tile_seq extends uvm_sequence #(axis_tile_item);
        `uvm_object_utils(corner_tile_seq)
        axis_tile_item::kind_e kind = axis_tile_item::KIND_A;
        int mode = 0;   // 0=all +127, 1=all -128, 2=all 0, 3=checker +127/-128

        function new(string name = "corner_tile_seq"); super.new(name); endfunction

        task body();
            axis_tile_item tr = axis_tile_item::type_id::create("tr");
            tr.kind = kind;
            start_item(tr);
            foreach (tr.matrix[i,j]) begin
                case (mode)
                    0: tr.matrix[i][j] = 127;
                    1: tr.matrix[i][j] = -128;
                    2: tr.matrix[i][j] = 0;
                    default: tr.matrix[i][j] = ((i+j) % 2) ? 127 : -128;
                endcase
            end
            // no randomize: values are set directly
            finish_item(tr);
        endtask
    endclass

    // ====================================================================
    // multi_tile_test -- runs N random tiles plus directed INT8 corner tiles,
    // each launched via a CSR start. Drives coverage toward closure.
    // ====================================================================
    // ====================================================================
    // multi_tile_test -- N random tiles plus directed INT8 corner tiles,
    // each launched via a CSR start. Drives coverage toward closure.
    //   matched corners : A,B same mode  -> extreme bins + (zero,zero) cross
    //   mixed   corners : A,B differ     -> the (zero x non-zero) cross bins
    // ====================================================================
    class multi_tile_test extends uvm_test;
        `uvm_component_utils(multi_tile_test)
        systolic_env env;
        int n_random = 24;     // random tiles
        int n_corner = 4;      // matched corner modes (per A and B)

        function new(string name, uvm_component parent);
            super.new(name, parent);
        endfunction

        function void build_phase(uvm_phase phase);
            super.build_phase(phase);
            env = systolic_env::type_id::create("env", this);
        endfunction

        task run_one(uvm_sequence #(axis_tile_item) a_seq,
                     uvm_sequence #(axis_tile_item) b_seq,
                     axis_slave_responder::bp_mode_e bp = axis_slave_responder::BP_NONE,
                     axis_coverage::spacing_e sp = axis_coverage::SP_GAPPED,
                     int gap = 4);
            axil_write_seq start_seq, clr;
            axil_read_seq  poll;

            env.c_resp.mode = bp;                          // CP3 backpressure
            if (sp == axis_coverage::SP_GAPPED)            // CP4 spacing: idle gap
                repeat (gap) @(posedge env.csr_vif.clk);
            // SP_B2B: no inserted idle -> start immediately

            `uvm_info("RUN1", $sformatf("tile start (checked=%0d)",
                      env.sb.tiles_checked), UVM_LOW)
            start_seq = axil_write_seq::type_id::create("start_seq");
            start_seq.addr = 8'h00; start_seq.data = 32'h1;
            start_seq.start(env.csr_agent.seqr);
            `uvm_info("RUN1", "CTRL.start written", UVM_LOW)

            fork
                a_seq.start(env.a_agent.seqr);
                b_seq.start(env.b_agent.seqr);
            join
            `uvm_info("RUN1", "A/B driven, polling STATUS.done", UVM_LOW)

            poll = axil_read_seq::type_id::create("poll");
            poll.addr = 8'h04;
            forever begin
                poll.start(env.csr_agent.seqr);
                if (poll.result[1]) break;
            end
            `uvm_info("RUN1", "done seen, clearing STATUS", UVM_LOW)

            clr = axil_write_seq::type_id::create("clr");
            clr.addr = 8'h04; clr.data = 32'h2;
            clr.start(env.csr_agent.seqr);
            `uvm_info("RUN1", "tile complete", UVM_LOW)

            env.cov.sample_spacing(sp);                    // CP4 + cross2
        endtask

        // Abort-mid-tile: drive a full tile's inputs, then pulse soft_reset
        // during COMPUTE (before any C output). Verifies the controller returns
        // to idle with no done/C and that CSR tile_cnt survives the abort.
        task run_abort();
            axil_write_seq start_seq, abort_seq;
            axil_read_seq  rd;
            single_tile_seq a_seq, b_seq;
            int cnt_before;

            rd = axil_read_seq::type_id::create("rd");
            rd.addr = 8'h08; rd.start(env.csr_agent.seqr);   // TILE_CNT before
            cnt_before = rd.result;

            env.c_resp.mode = axis_slave_responder::BP_NONE;
            `uvm_info("ABORT", "starting tile to abort", UVM_LOW)
            start_seq = axil_write_seq::type_id::create("start_seq");
            start_seq.addr = 8'h00; start_seq.data = 32'h1;
            start_seq.start(env.csr_agent.seqr);

            a_seq = single_tile_seq::type_id::create("a_seq");
            b_seq = single_tile_seq::type_id::create("b_seq");
            a_seq.kind = axis_tile_item::KIND_A;
            b_seq.kind = axis_tile_item::KIND_B;
            fork                                   // full input drive -> monitors close
                a_seq.start(env.a_agent.seqr);
                b_seq.start(env.b_agent.seqr);
            join

            rd.addr = 8'h04; rd.start(env.csr_agent.seqr);   // STATUS: expect busy
            if (!rd.result[0]) `uvm_error("ABORT", "not busy before abort")
            abort_seq = axil_write_seq::type_id::create("abort_seq");
            abort_seq.addr = 8'h00; abort_seq.data = 32'h2;  // CTRL.soft_reset
            abort_seq.start(env.csr_agent.seqr);
            `uvm_info("ABORT", "soft_reset pulsed mid-tile", UVM_LOW)

            repeat (10) @(posedge env.csr_vif.clk);
            rd.addr = 8'h04; rd.start(env.csr_agent.seqr);
            if (rd.result[0]) `uvm_error("ABORT", "busy still set after soft_reset")
            if (rd.result[1]) `uvm_error("ABORT", "spurious done after abort")
            rd.addr = 8'h08; rd.start(env.csr_agent.seqr);
            if (rd.result != cnt_before)
                `uvm_error("ABORT", $sformatf("tile_cnt moved on abort: %0d -> %0d",
                           cnt_before, rd.result))
            else
                `uvm_info("ABORT", $sformatf(
                    "clean: idle, no done, tile_cnt preserved (%0d)", cnt_before), UVM_LOW)

            env.cov.sample_spacing(axis_coverage::SP_ABORT);
        endtask

        // Touches the CSR regs the tile loop never exercises -- closes CP5 and
        // checks VERSION (RO constant), IRQ_EN (RW), and a CTRL readback.
        task csr_sanity();
            axil_write_seq wr;
            axil_read_seq  rd;

            rd = axil_read_seq::type_id::create("rd_ver");
            rd.addr = 8'h10; rd.start(env.csr_agent.seqr);           // VERSION
            if (rd.result !== 32'h0001_0000)
                `uvm_error("CSR", $sformatf("VERSION %08h exp 00010000", rd.result))

            wr = axil_write_seq::type_id::create("wr_irq");
            wr.addr = 8'h0C; wr.data = 32'h1; wr.start(env.csr_agent.seqr); // IRQ_EN=1
            rd = axil_read_seq::type_id::create("rd_irq");
            rd.addr = 8'h0C; rd.start(env.csr_agent.seqr);
            if (rd.result[0] !== 1'b1)
                `uvm_error("CSR", $sformatf("IRQ_EN readback %08h exp bit0=1", rd.result))
            wr = axil_write_seq::type_id::create("wr_irq0");
            wr.addr = 8'h0C; wr.data = 32'h0; wr.start(env.csr_agent.seqr); // restore

            wr = axil_write_seq::type_id::create("wr_unmap");
            wr.addr = 8'hFC; wr.data = 32'hDEAD_BEEF; wr.start(env.csr_agent.seqr);
            rd = axil_read_seq::type_id::create("rd_unmap");
            rd.addr = 8'hFC; rd.start(env.csr_agent.seqr);
            if (rd.result !== 32'd0)
                `uvm_error("CSR", $sformatf("unmapped read %08h exp 0", rd.result))

            rd = axil_read_seq::type_id::create("rd_ctrl");
            rd.addr = 8'h00; rd.start(env.csr_agent.seqr);           // CTRL readback

            `uvm_info("CSR", "CSR sanity done (VERSION, IRQ_EN RW, CTRL readback)", UVM_LOW)
        endtask

        // Start B ~20 cycles late so b_cnt < 8 when S_LOAD ends and the FSM
        // passes through S_WAIT_B (the producer/consumer decoupling path).
        task run_one_slowb();
            axil_write_seq start_seq, clr;
            axil_read_seq  poll;
            single_tile_seq a_seq, b_seq;

            env.c_resp.mode = axis_slave_responder::BP_NONE;
            `uvm_info("RUN1", "slow-B tile (exercise S_WAIT_B)", UVM_LOW)
            start_seq = axil_write_seq::type_id::create("start_seq");
            start_seq.addr = 8'h00; start_seq.data = 32'h1;
            start_seq.start(env.csr_agent.seqr);

            a_seq = single_tile_seq::type_id::create("a_seq");
            b_seq = single_tile_seq::type_id::create("b_seq");
            a_seq.kind = axis_tile_item::KIND_A;
            b_seq.kind = axis_tile_item::KIND_B;
            fork
                a_seq.start(env.a_agent.seqr);
                begin
                    repeat (20) @(posedge env.csr_vif.clk);  // hold B off past LOAD
                    b_seq.start(env.b_agent.seqr);
                end
            join

            poll = axil_read_seq::type_id::create("poll");
            poll.addr = 8'h04;
            forever begin
                poll.start(env.csr_agent.seqr);
                if (poll.result[1]) break;
            end
            clr = axil_write_seq::type_id::create("clr");
            clr.addr = 8'h04; clr.data = 32'h2;
            clr.start(env.csr_agent.seqr);
            env.cov.sample_spacing(axis_coverage::SP_GAPPED);
            `uvm_info("RUN1", "slow-B tile complete", UVM_LOW)
        endtask

        task run_phase(uvm_phase phase);
            single_tile_seq ra, rb;
            corner_tile_seq ca, cb;

            phase.raise_objection(this);
            env.sb.tiles_target = 1_000_000;   // test manages completion

            wait (env.csr_vif.rst == 0);
            repeat (2) @(posedge env.csr_vif.clk);

            // ---- random tiles: sweep backpressure (CP3), all gapped ----
            for (int n = 0; n < n_random; n++) begin
                ra = single_tile_seq::type_id::create("ra");
                rb = single_tile_seq::type_id::create("rb");
                ra.kind = axis_tile_item::KIND_A;
                rb.kind = axis_tile_item::KIND_B;
                if      (n < 8)  run_one(ra, rb, axis_slave_responder::BP_NONE,   axis_coverage::SP_GAPPED);
                else if (n < 22) run_one(ra, rb, axis_slave_responder::BP_RANDOM, axis_coverage::SP_GAPPED);
                else             run_one(ra, rb, axis_slave_responder::BP_LAST,   axis_coverage::SP_GAPPED);
            end

            // ---- matched-mode corners ----
            for (int m = 0; m < n_corner; m++) begin
                ca = corner_tile_seq::type_id::create("ca");
                cb = corner_tile_seq::type_id::create("cb");
                ca.kind = axis_tile_item::KIND_A; ca.mode = m;
                cb.kind = axis_tile_item::KIND_B; cb.mode = m;
                run_one(ca, cb, axis_slave_responder::BP_NONE, axis_coverage::SP_GAPPED);
            end

            // ---- mixed-mode corners (close the operand cross) ----
            begin
                int am[4] = '{2, 0, 2, 1};
                int bm[4] = '{0, 2, 1, 2};
                for (int p = 0; p < 4; p++) begin
                    ca = corner_tile_seq::type_id::create("ca");
                    cb = corner_tile_seq::type_id::create("cb");
                    ca.kind = axis_tile_item::KIND_A; ca.mode = am[p];
                    cb.kind = axis_tile_item::KIND_B; cb.mode = bm[p];
                    run_one(ca, cb, axis_slave_responder::BP_NONE, axis_coverage::SP_GAPPED);
                end
            end

            // ---- CP4 spacing + Cross2: back-to-back column + abort ----
            // (gapped x none/stall already covered by the sweep above)
            ra = single_tile_seq::type_id::create("ra");
            rb = single_tile_seq::type_id::create("rb");
            ra.kind = axis_tile_item::KIND_A; rb.kind = axis_tile_item::KIND_B;
            run_one(ra, rb, axis_slave_responder::BP_NONE, axis_coverage::SP_B2B);   // (none,b2b)

            ra = single_tile_seq::type_id::create("ra");
            rb = single_tile_seq::type_id::create("rb");
            ra.kind = axis_tile_item::KIND_A; rb.kind = axis_tile_item::KIND_B;
            run_one(ra, rb, axis_slave_responder::BP_LAST, axis_coverage::SP_B2B);   // (stall,b2b)

            run_abort();                                                            // SP_ABORT
            csr_sanity();
            run_one_slowb();

            // recovery tile: proves the controller resumed and CSR state survived
            ra = single_tile_seq::type_id::create("ra");
            rb = single_tile_seq::type_id::create("rb");
            ra.kind = axis_tile_item::KIND_A; rb.kind = axis_tile_item::KIND_B;
            run_one(ra, rb, axis_slave_responder::BP_NONE, axis_coverage::SP_GAPPED);

            `uvm_info("TEST", $sformatf("ran %0d tiles total",
                      env.sb.tiles_checked), UVM_LOW)
            repeat (4) @(posedge env.csr_vif.clk);
            phase.drop_objection(this);
        endtask
    endclass

endpackage
