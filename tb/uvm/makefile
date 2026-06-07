UVM_SRC ?= /Users/jaishyamreddivari/tools/uvm-core/src

COMMON = --binary -j 0 --timing \
  +define+UVM_NO_DPI \
  -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-WIDTH -Wno-TIMESCALEMOD \
  +incdir+$(UVM_SRC) +incdir+.

RTL = ../../rtl/pe.sv ../../rtl/systolic_array.sv ../../rtl/controller.sv \
      ../../rtl/csr.sv ../../rtl/systolic_top.sv
UVMPKG = ctrl_if.sv axis_if.sv axil_if.sv systolic_uvm_pkg.sv tb_top.sv

BIN = ./obj_dir/Vtb_top

# clean filter (drops UVM name-warning spam + release notes)
FILTER = grep -vE "UVM/COMP/NAME|UVM/RELNOTES|RELEASE NOTES|deviates|Accellera|copyright|Rights Reserved|^[[:space:]]*$$|^-+$$|\*+"
# verbose filter (keeps meaningful traces only)
DBGFILTER = grep -E "TEST|RUN1|DRV|CMON|SB|COV|tile|ERROR|FATAL"

UVM_QUIET = +uvm_set_action=*,UVM/COMP/NAME,UVM_WARNING,UVM_NO_ACTION

# DBG=1 -> verbose; else clean
ifeq ($(DBG),1)
  VERB = +UVM_VERBOSITY=UVM_HIGH
  SHOW = $(DBGFILTER)
else
  VERB = +UVM_NO_RELNOTES
  SHOW = $(FILTER)
endif

build: $(BIN)

$(BIN): $(RTL) $(UVMPKG)
	verilator $(COMMON) $(UVM_SRC)/uvm_pkg.sv $(RTL) $(UVMPKG) \
	  --top-module tb_top -o Vtb_top

# generic test runner: `make run TEST=<name>`
run: build
	$(BIN) +UVM_TESTNAME=$(TEST) $(VERB) $(UVM_QUIET) 2>&1 | $(SHOW)

# convenience targets (each just sets TEST)
top_tile_test:   build ; $(BIN) +UVM_TESTNAME=top_tile_test   $(VERB) 2>&1 | $(SHOW)
multi_tile_test: build ; $(BIN) +UVM_TESTNAME=multi_tile_test $(VERB) 2>&1 | $(SHOW)

# ---- controller-level bring-up (separate binary; uses ctrl_if shim) ----
RTL_CTRL = ../../rtl/pe.sv ../../rtl/systolic_array.sv ../../rtl/controller.sv
BIN_CTRL = ./obj_dir/Vtb_ctrl

$(BIN_CTRL): $(RTL_CTRL) ctrl_if.sv axis_if.sv axil_if.sv systolic_uvm_pkg.sv tb_ctrl.sv
	verilator $(COMMON) $(UVM_SRC)/uvm_pkg.sv $(RTL_CTRL) \
	  ctrl_if.sv axis_if.sv axil_if.sv systolic_uvm_pkg.sv tb_ctrl.sv \
	  --top-module tb_ctrl -o Vtb_ctrl

single_tile_test: $(BIN_CTRL)
	$(BIN_CTRL) +UVM_TESTNAME=single_tile_test $(VERB) 2>&1 | $(SHOW)

# ---- code coverage (line + toggle + user); separate binary/obj_dir ----
COV_DIR  = ./obj_dir_cov
BIN_COV  = $(COV_DIR)/Vtb_top_cov
COV_DAT  = ./coverage.dat
COV_ANN  = ./cov_annotated
COV_TEST ?= multi_tile_test

$(BIN_COV): $(RTL) $(UVMPKG) coverage.vlt
	verilator $(COMMON) --coverage --Mdir $(COV_DIR) coverage.vlt \
	  $(UVM_SRC)/uvm_pkg.sv $(RTL) $(UVMPKG) \
	  --top-module tb_top -o Vtb_top_cov

coverage: $(BIN_COV)
	rm -f $(COV_DAT)
	rm -rf $(COV_ANN)
	$(BIN_COV) +UVM_TESTNAME=$(COV_TEST) +UVM_NO_RELNOTES 2>&1 | $(FILTER)
	@test -f $(COV_DAT) || { echo "no $(COV_DAT) written"; exit 1; }
	@echo "==== coverage summary ===="
	verilator_coverage $(COV_DAT)
	verilator_coverage --annotate $(COV_ANN) --annotate-min 1 $(COV_DAT)
	@echo "annotated RTL in $(COV_ANN)/  (uncovered lines marked with '%')"

build_top:  $(BIN)
build_ctrl: $(BIN_CTRL)
build_cov:  $(BIN_COV)

clean:
	rm -rf obj_dir obj_dir_cov coverage.dat cov_annotated