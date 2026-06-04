// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_systolic_array.h for the primary calling header

#ifndef VERILATED_VTB_SYSTOLIC_ARRAY___024ROOT_H_
#define VERILATED_VTB_SYSTOLIC_ARRAY___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_systolic_array__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_systolic_array___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ tb_systolic_array__DOT__clk;
        CData/*0:0*/ tb_systolic_array__DOT__rst;
        CData/*0:0*/ tb_systolic_array__DOT__load_en;
        CData/*0:0*/ tb_systolic_array__DOT__compute_en;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    };
    struct {
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    };
    struct {
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
        CData/*7:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        IData/*31:0*/ tb_systolic_array__DOT__file_N;
        IData/*31:0*/ tb_systolic_array__DOT__file_NLOAD;
        IData/*31:0*/ tb_systolic_array__DOT__file_NCOMPUTE;
        IData/*31:0*/ tb_systolic_array__DOT__file_NTILES;
        IData/*31:0*/ tb_systolic_array__DOT__tmp;
        IData/*31:0*/ tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk4__DOT__c;
        IData/*31:0*/ tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    };
    struct {
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        VlUnpacked<CData/*7:0*/, 8> tb_systolic_array__DOT__weight_top;
        VlUnpacked<CData/*7:0*/, 8> tb_systolic_array__DOT__a_top;
        VlUnpacked<IData/*31:0*/, 8> tb_systolic_array__DOT__c_out;
        VlUnpacked<IData/*31:0*/, 8> tb_systolic_array__DOT____Vcellout__dut__c_out;
        VlUnpacked<CData/*7:0*/, 8> tb_systolic_array__DOT____Vcellinp__dut__a_top;
        VlUnpacked<CData/*7:0*/, 8> tb_systolic_array__DOT____Vcellinp__dut__weight_top;
        VlUnpacked<IData/*31:0*/, 8> tb_systolic_array__DOT__exp_cout;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__weight_out_w;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__a_out_w;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__psum_out_w;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__weight_in_w;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__a_in_w;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 8>, 8> tb_systolic_array__DOT__dut__DOT__psum_in_w;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h4bda924e__0;
    VlTriggerScheduler __VtrigSched_h4bda957c__0;

    // INTERNAL VARIABLES
    Vtb_systolic_array__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_systolic_array___024root(Vtb_systolic_array__Syms* symsp, const char* namep);
    ~Vtb_systolic_array___024root();
    VL_UNCOPYABLE(Vtb_systolic_array___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
