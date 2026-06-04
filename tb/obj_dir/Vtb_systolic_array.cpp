// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_systolic_array__pch.h"

//============================================================
// Constructors

Vtb_systolic_array::Vtb_systolic_array(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_systolic_array__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_systolic_array::Vtb_systolic_array(const char* _vcname__)
    : Vtb_systolic_array(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_systolic_array::~Vtb_systolic_array() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_systolic_array___024root___eval_debug_assertions(Vtb_systolic_array___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_systolic_array___024root___eval_static(Vtb_systolic_array___024root* vlSelf);
void Vtb_systolic_array___024root___eval_initial(Vtb_systolic_array___024root* vlSelf);
void Vtb_systolic_array___024root___eval_settle(Vtb_systolic_array___024root* vlSelf);
void Vtb_systolic_array___024root___eval(Vtb_systolic_array___024root* vlSelf);

void Vtb_systolic_array::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_systolic_array::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_systolic_array___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_systolic_array___024root___eval_static(&(vlSymsp->TOP));
        Vtb_systolic_array___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_systolic_array___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_systolic_array___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_systolic_array::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_systolic_array::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_systolic_array::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_systolic_array___024root___eval_final(Vtb_systolic_array___024root* vlSelf);

VL_ATTR_COLD void Vtb_systolic_array::final() {
    contextp()->executingFinal(true);
    Vtb_systolic_array___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_systolic_array::hierName() const { return vlSymsp->name(); }
const char* Vtb_systolic_array::modelName() const { return "Vtb_systolic_array"; }
unsigned Vtb_systolic_array::threads() const { return 1; }
void Vtb_systolic_array::prepareClone() const { contextp()->prepareClone(); }
void Vtb_systolic_array::atClone() const {
    contextp()->threadPoolpOnClone();
}
