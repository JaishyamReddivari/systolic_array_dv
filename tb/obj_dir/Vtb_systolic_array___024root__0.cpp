// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_systolic_array.h for the primary calling header

#include "Vtb_systolic_array__pch.h"

VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__0(Vtb_systolic_array___024root* vlSelf);
VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__1(Vtb_systolic_array___024root* vlSelf);
VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__2(Vtb_systolic_array___024root* vlSelf);

void Vtb_systolic_array___024root___eval_initial(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_initial\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__clk = 0U;
    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

void Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(Vtb_systolic_array___024root* vlSelf, const char* __VeventDescription);
void Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0(Vtb_systolic_array___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__0(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_systolic_array__DOT__fd;
    tb_systolic_array__DOT__fd = 0;
    IData/*31:0*/ tb_systolic_array__DOT__code;
    tb_systolic_array__DOT__code = 0;
    IData/*31:0*/ tb_systolic_array__DOT__errors;
    tb_systolic_array__DOT__errors = 0;
    IData/*31:0*/ tb_systolic_array__DOT__checks;
    tb_systolic_array__DOT__checks = 0;
    IData/*31:0*/ tb_systolic_array__DOT__unnamedblk2__DOT__t;
    tb_systolic_array__DOT__unnamedblk2__DOT__t = 0;
    // Body
    tb_systolic_array__DOT__errors = 0U;
    tb_systolic_array__DOT__checks = 0U;
    tb_systolic_array__DOT__fd = VL_FOPEN_NN("stimulus.txt"s
                                             , "r"s);
    ;
    if (VL_UNLIKELY(((0U == tb_systolic_array__DOT__fd)))) {
        VL_WRITEF_NX("FATAL: cannot open stimulus.txt\n",0);
        VL_FINISH_MT("tb_systolic_array.sv", 76, "");
    }
    tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d %d %d %d",4
                                                 , '#',32,&(vlSelfRef.tb_systolic_array__DOT__file_N)
                                                 , '#',32,&(vlSelfRef.tb_systolic_array__DOT__file_NLOAD)
                                                 , '#',32,&(vlSelfRef.tb_systolic_array__DOT__file_NCOMPUTE)
                                                 , '#',32,&(vlSelfRef.tb_systolic_array__DOT__file_NTILES)) ;
    if (VL_UNLIKELY(((8U != vlSelfRef.tb_systolic_array__DOT__file_N)))) {
        VL_WRITEF_NX("FATAL: stimulus N=%0d but TB built for N=8\n",1
                     , '~',32,vlSelfRef.tb_systolic_array__DOT__file_N);
        VL_FINISH_MT("tb_systolic_array.sv", 83, "");
    }
    VL_WRITEF_NX("Stimulus: N=%0d LOAD=%0d COMPUTE=%0d TILES=%0d\n",4
                 , '~',32,vlSelfRef.tb_systolic_array__DOT__file_N
                 , '~',32,vlSelfRef.tb_systolic_array__DOT__file_NLOAD
                 , '~',32,vlSelfRef.tb_systolic_array__DOT__file_NCOMPUTE
                 , '~',32,vlSelfRef.tb_systolic_array__DOT__file_NTILES);
    vlSelfRef.tb_systolic_array__DOT__rst = 1U;
    vlSelfRef.tb_systolic_array__DOT__load_en = 0U;
    vlSelfRef.tb_systolic_array__DOT__compute_en = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[0U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[1U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[1U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[2U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[2U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[3U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[3U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[4U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[4U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[5U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[5U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[6U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[6U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__weight_top[7U] = 0U;
    vlSelfRef.tb_systolic_array__DOT__a_top[7U] = 0U;
    tb_systolic_array__DOT__unnamedblk2__DOT__t = 0U;
    while (VL_LTS_III(32, tb_systolic_array__DOT__unnamedblk2__DOT__t, vlSelfRef.tb_systolic_array__DOT__file_NTILES)) {
        Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(vlSelf, 
                                                                 "@(negedge tb_systolic_array.clk)");
        co_await vlSelfRef.__VtrigSched_h4bda924e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge tb_systolic_array.clk)", 
                                                             "tb_systolic_array.sv", 
                                                             96);
        vlSelfRef.tb_systolic_array__DOT__rst = 1U;
        vlSelfRef.tb_systolic_array__DOT__load_en = 0U;
        vlSelfRef.tb_systolic_array__DOT__compute_en = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[0U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[0U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[1U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[1U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[2U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[2U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[3U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[3U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[4U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[4U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[5U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[5U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[6U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[6U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__weight_top[7U] = 0U;
        vlSelfRef.tb_systolic_array__DOT__a_top[7U] = 0U;
        Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0(vlSelf, 
                                                                 "@(posedge tb_systolic_array.clk)");
        co_await vlSelfRef.__VtrigSched_h4bda957c__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_systolic_array.clk)", 
                                                             "tb_systolic_array.sv", 
                                                             99);
        Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(vlSelf, 
                                                                 "@(negedge tb_systolic_array.clk)");
        co_await vlSelfRef.__VtrigSched_h4bda924e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge tb_systolic_array.clk)", 
                                                             "tb_systolic_array.sv", 
                                                             100);
        vlSelfRef.tb_systolic_array__DOT__rst = 0U;
        vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk4__DOT__c = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk4__DOT__c, vlSelfRef.tb_systolic_array__DOT__file_NLOAD)) {
            Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(vlSelf, 
                                                                     "@(negedge tb_systolic_array.clk)");
            co_await vlSelfRef.__VtrigSched_h4bda924e__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(negedge tb_systolic_array.clk)", 
                                                                 "tb_systolic_array.sv", 
                                                                 105);
            vlSelfRef.tb_systolic_array__DOT__load_en = 1U;
            vlSelfRef.tb_systolic_array__DOT__compute_en = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[0U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[0U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[1U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[1U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[2U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[2U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[3U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[3U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[4U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[4U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[5U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[5U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[6U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[6U] = 0U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__weight_top[7U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            vlSelfRef.tb_systolic_array__DOT__a_top[7U] = 0U;
            Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0(vlSelf, 
                                                                     "@(posedge tb_systolic_array.clk)");
            co_await vlSelfRef.__VtrigSched_h4bda957c__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_systolic_array.clk)", 
                                                                 "tb_systolic_array.sv", 
                                                                 112);
            vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk4__DOT__c 
                = ((IData)(1U) + vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk4__DOT__c);
        }
        vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c, vlSelfRef.tb_systolic_array__DOT__file_NCOMPUTE)) {
            Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(vlSelf, 
                                                                     "@(negedge tb_systolic_array.clk)");
            co_await vlSelfRef.__VtrigSched_h4bda924e__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(negedge tb_systolic_array.clk)", 
                                                                 "tb_systolic_array.sv", 
                                                                 117);
            vlSelfRef.tb_systolic_array__DOT__load_en = 0U;
            vlSelfRef.tb_systolic_array__DOT__compute_en = 1U;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[0U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[1U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[2U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[3U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[4U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[5U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[6U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__a_top[7U] 
                = (0x000000ffU & vlSelfRef.tb_systolic_array__DOT__tmp);
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[0U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[1U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[2U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[3U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[4U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[5U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[6U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            tb_systolic_array__DOT__code = VL_FSCANF_INX(tb_systolic_array__DOT__fd,"%d",1
                                                         , '#',32,&(vlSelfRef.tb_systolic_array__DOT__tmp)) ;
            vlSelfRef.tb_systolic_array__DOT__exp_cout[7U] 
                = vlSelfRef.tb_systolic_array__DOT__tmp;
            Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0(vlSelf, 
                                                                     "@(posedge tb_systolic_array.clk)");
            co_await vlSelfRef.__VtrigSched_h4bda957c__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_systolic_array.clk)", 
                                                                 "tb_systolic_array.sv", 
                                                                 128);
            co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                                 nullptr, 
                                                 "tb_systolic_array.sv", 
                                                 129);
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[0U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[0U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 0: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[0U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[0U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[1U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[1U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 1: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[1U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[1U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[2U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[2U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 2: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[2U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[2U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[3U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[3U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 3: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[3U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[3U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[4U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[4U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 4: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[4U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[4U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[5U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[5U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 5: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[5U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[5U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[6U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[6U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 6: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[6U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[6U]);
            }
            tb_systolic_array__DOT__checks = ((IData)(1U) 
                                              + tb_systolic_array__DOT__checks);
            if (VL_UNLIKELY(((vlSelfRef.tb_systolic_array__DOT__c_out[7U] 
                              != vlSelfRef.tb_systolic_array__DOT__exp_cout[7U])))) {
                tb_systolic_array__DOT__errors = ((IData)(1U) 
                                                  + tb_systolic_array__DOT__errors);
                VL_WRITEF_NX("MISMATCH tile %0d cycle %0d row 7: got %0d exp %0d\n",4
                             , '~',32,tb_systolic_array__DOT__unnamedblk2__DOT__t
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__c_out[7U]
                             , '~',32,vlSelfRef.tb_systolic_array__DOT__exp_cout[7U]);
            }
            vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c 
                = ((IData)(1U) + vlSelfRef.tb_systolic_array__DOT__unnamedblk2__DOT__unnamedblk6__DOT__c);
        }
        tb_systolic_array__DOT__unnamedblk2__DOT__t 
            = ((IData)(1U) + tb_systolic_array__DOT__unnamedblk2__DOT__t);
    }
    VL_FCLOSE_I(tb_systolic_array__DOT__fd); VL_WRITEF_NX("----------------------------------------\nChecks: %0d   Errors: %0d\n",2
                                                          , '~',32,tb_systolic_array__DOT__checks
                                                          , '~',32,tb_systolic_array__DOT__errors);
    if ((0U == tb_systolic_array__DOT__errors)) {
        VL_WRITEF_NX("RESULT: PASS\n",0);
    } else {
        VL_WRITEF_NX("RESULT: FAIL\n",0);
    }
    VL_FINISH_MT("tb_systolic_array.sv", 147, "");
    co_return;
}

VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__1(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x00000000000f4240ULL, 
                                         nullptr, "tb_systolic_array.sv", 
                                         152);
    VL_WRITEF_NX("FATAL: timeout\n",0);
    VL_FINISH_MT("tb_systolic_array.sv", 154, "");
    co_return;
}

VlCoroutine Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__2(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(5ULL, 
                                             nullptr, 
                                             "tb_systolic_array.sv", 
                                             56);
        vlSelfRef.tb_systolic_array__DOT__clk = (1U 
                                                 & (~ (IData)(vlSelfRef.tb_systolic_array__DOT__clk)));
    }
    co_return;
}

void Vtb_systolic_array___024root___eval_triggers_vec__act(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_triggers_vec__act\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.tb_systolic_array__DOT__clk)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_systolic_array__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0 
        = vlSelfRef.tb_systolic_array__DOT__clk;
}

bool Vtb_systolic_array___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtb_systolic_array___024root___act_comb__TOP__0(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___act_comb__TOP__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[0U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[1U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[2U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[3U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[4U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[5U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[6U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[0U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[1U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[2U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[3U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[4U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[5U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[6U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U];
}

void Vtb_systolic_array___024root___eval_act(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_act\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((7ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_systolic_array___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_systolic_array___024root___nba_comb__TOP__0(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___nba_comb__TOP__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[0U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[1U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[2U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[3U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[4U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[5U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[6U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U] 
        = vlSelfRef.tb_systolic_array__DOT__a_top[7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[0U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[1U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[2U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[3U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[4U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[5U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[6U];
    vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U] 
        = vlSelfRef.tb_systolic_array__DOT__weight_top[7U];
}

void Vtb_systolic_array___024root___nba_sequent__TOP__0(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___nba_sequent__TOP__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.tb_systolic_array__DOT__rst) {
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg = 0U;
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg = 0U;
    } else {
        if (vlSelfRef.tb_systolic_array__DOT__compute_en) {
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][7U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][0U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][0U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][1U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][1U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][2U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][2U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][3U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][3U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][4U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][4U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][5U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][5U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][6U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][6U]))))));
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg 
                = (vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][7U] 
                   + VL_EXTENDS_II(32,16, (0x0000ffffU 
                                           & VL_MULS_III(16, 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, (IData)(vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg))), 
                                                         (0x0000ffffU 
                                                          & VL_EXTENDS_II(16,8, vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][7U]))))));
        }
        if (vlSelfRef.tb_systolic_array__DOT__load_en) {
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][7U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][0U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][1U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][2U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][3U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][4U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][5U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][6U];
            vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg 
                = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][7U];
        }
    }
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__a_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__psum_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[0U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[1U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[2U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[3U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[4U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[5U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_out_w[6U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][7U];
    vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[0U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[1U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[2U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[3U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[4U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[5U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[6U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_in_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__psum_out_w[7U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__0__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__1__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__2__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__3__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__4__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__5__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__6__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__0__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__1__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__2__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__3__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__4__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__5__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__6__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__c_out[0U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[0U];
    vlSelfRef.tb_systolic_array__DOT__c_out[1U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[1U];
    vlSelfRef.tb_systolic_array__DOT__c_out[2U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[2U];
    vlSelfRef.tb_systolic_array__DOT__c_out[3U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[3U];
    vlSelfRef.tb_systolic_array__DOT__c_out[4U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[4U];
    vlSelfRef.tb_systolic_array__DOT__c_out[5U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[5U];
    vlSelfRef.tb_systolic_array__DOT__c_out[6U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[6U];
    vlSelfRef.tb_systolic_array__DOT__c_out[7U] = vlSelfRef.tb_systolic_array__DOT____Vcellout__dut__c_out[7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__g_row__BRA__7__KET____DOT__g_col__BRA__7__KET____DOT__u_pe__DOT__weight_reg;
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[1U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[0U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[2U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[1U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[3U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[2U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[4U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[3U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[5U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[4U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[6U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[5U][7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][0U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][1U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][2U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][3U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][4U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][5U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][6U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[7U][7U] 
        = vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_out_w[6U][7U];
}

void Vtb_systolic_array___024root___nba_comb__TOP__1(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___nba_comb__TOP__1\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][0U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][1U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][2U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][3U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][4U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][5U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][6U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U];
    vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][7U] 
        = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U];
}

void Vtb_systolic_array___024root___eval_nba(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_nba\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[0U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[1U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[2U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[3U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[4U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[5U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[6U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U] 
            = vlSelfRef.tb_systolic_array__DOT__a_top[7U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[0U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[1U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[2U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[3U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[4U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[5U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[6U];
        vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U] 
            = vlSelfRef.tb_systolic_array__DOT__weight_top[7U];
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_systolic_array___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][0U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[0U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][1U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[1U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][2U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[2U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][3U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[3U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][4U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[4U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][5U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[5U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][6U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[6U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__a_in_w[0U][7U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__a_top[7U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][0U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[0U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][1U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[1U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][2U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[2U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][3U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[3U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][4U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[4U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][5U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[5U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][6U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[6U];
        vlSelfRef.tb_systolic_array__DOT__dut__DOT__weight_in_w[0U][7U] 
            = vlSelfRef.tb_systolic_array__DOT____Vcellinp__dut__weight_top[7U];
    }
}

void Vtb_systolic_array___024root___timing_ready(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___timing_ready\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h4bda924e__0.ready("@(negedge tb_systolic_array.clk)");
    }
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h4bda957c__0.ready("@(posedge tb_systolic_array.clk)");
    }
}

void Vtb_systolic_array___024root___timing_resume(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___timing_resume\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h4bda924e__0.moveToResumeQueue(
                                                          "@(negedge tb_systolic_array.clk)");
    vlSelfRef.__VtrigSched_h4bda957c__0.moveToResumeQueue(
                                                          "@(posedge tb_systolic_array.clk)");
    vlSelfRef.__VtrigSched_h4bda924e__0.resume("@(negedge tb_systolic_array.clk)");
    vlSelfRef.__VtrigSched_h4bda957c__0.resume("@(posedge tb_systolic_array.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_systolic_array___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_systolic_array___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_systolic_array___024root___eval_phase__act(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_phase__act\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_systolic_array___024root___eval_triggers_vec__act(vlSelf);
    Vtb_systolic_array___024root___timing_ready(vlSelf);
    Vtb_systolic_array___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_systolic_array___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_systolic_array___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_systolic_array___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_systolic_array___024root___timing_resume(vlSelf);
        Vtb_systolic_array___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_systolic_array___024root___eval_phase__inact(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_phase__inact\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_systolic_array.sv", 30, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_systolic_array___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_systolic_array___024root___eval_phase__nba(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_phase__nba\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_systolic_array___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_systolic_array___024root___eval_nba(vlSelf);
        Vtb_systolic_array___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_systolic_array___024root___eval(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_systolic_array___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_systolic_array.sv", 30, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb_systolic_array.sv", 30, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_systolic_array___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb_systolic_array.sv", 30, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_systolic_array___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_systolic_array___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_systolic_array___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0(Vtb_systolic_array___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root____VbeforeTrig_h4bda924e__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.tb_systolic_array__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0)) 
                                   << 1U) | ((IData)(vlSelfRef.tb_systolic_array__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0 
        = vlSelfRef.tb_systolic_array__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
    }
    if ((2ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0(Vtb_systolic_array___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root____VbeforeTrig_h4bda957c__0\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.tb_systolic_array__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0)) 
                                   << 1U) | ((IData)(vlSelfRef.tb_systolic_array__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_systolic_array__DOT__clk__0 
        = vlSelfRef.tb_systolic_array__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda957c__0.ready(__VeventDescription);
    }
    if ((2ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h4bda924e__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_systolic_array___024root___eval_debug_assertions(Vtb_systolic_array___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_systolic_array___024root___eval_debug_assertions\n"); );
    Vtb_systolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
