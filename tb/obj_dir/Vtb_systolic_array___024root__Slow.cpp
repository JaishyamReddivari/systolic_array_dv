// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_systolic_array.h for the primary calling header

#include "Vtb_systolic_array__pch.h"

void Vtb_systolic_array___024root___ctor_var_reset(Vtb_systolic_array___024root* vlSelf);

Vtb_systolic_array___024root::Vtb_systolic_array___024root(Vtb_systolic_array__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_systolic_array___024root___ctor_var_reset(this);
}

void Vtb_systolic_array___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_systolic_array___024root::~Vtb_systolic_array___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
