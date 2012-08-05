/******************************************************************************
 *  Copyright (c) 2008 - 2010 IBM Corporation and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *    David Ungar, IBM Research - Initial Implementation
 *    Sam Adams, IBM Research - Initial Implementation
 *    Stefan Marr, Vrije Universiteit Brussel - Port to x86 Multi-Core Systems
 ******************************************************************************/


#include "headers.h"

/**
 * This file defines helper functions to facilitate debugging.
 * Helper like pst() can be used from GDB with 'call pst()' easily.
 */

// OOP

void dp(Oop x) { x.dp(); }
void Oop::dp() { print(stderr_printer);
  
  if (is_mem()) {
  
    // OMNI
    stderr_printer->printf(" ((");
    
    Oop domain = as_object()->domain_oop();
    if (domain.is_illegal()) {
      stderr_printer->printf("illegal");
    }
    else {
      domain.as_object()->print(stderr_printer);
    }
    
    stderr_printer->printf("))");
  }
  
  stderr_printer->nl(); }  // debugging print routines
void dp(Object* x) {x->dp(); } // print Object

void dpf(Oop x)     { x.as_object()->print_with_fields(); }
void dpf(Object* x) { x->print_with_fields(); } 

Oop at(Oop x, oop_int_t i) {
  return x.as_object()->fetchPointer(i);
}

void dpf_top() {
  dpf_n(0);
}
void dpf_n(int offset) {
  Squeak_Interpreter* const interp = The_Squeak_Interpreter();
  if (interp->is_internal_valid()) {
    dpf(interp->internalStackValue(offset));
  }
  else if (interp->is_external_valid()) {
    dpf(interp->stackValue(offset));
  }
}



// Interpreter

void pet() {
  if (Trace_Execution && The_Squeak_Interpreter()->execution_tracer() != NULL)
    The_Squeak_Interpreter()->execution_tracer()->print();
}

void pst() {
  The_Squeak_Interpreter()->print_stack_trace(dittoing_stdout_printer);
}

int printCallStack() { pst(); return 0; }

void pat() {
  The_Squeak_Interpreter()->print_all_stack_traces(dittoing_stdout_printer);
}
int printAllStacks() { pat(); return 0; }

void print_current_method() {
  The_Squeak_Interpreter()->print_method_info("debug helper");
}

void print_stack_frame() {
  The_Squeak_Interpreter()->print_stack_frame();
}


void enableTracing() {
  Triggerable_Execution_Tracer* tracer = 
      (Triggerable_Execution_Tracer*)The_Squeak_Interpreter()->execution_tracer();
  if (tracer) {
    tracer->enable_recording_and_printing();
  }
}

void disableTracing() {
  Triggerable_Execution_Tracer* tracer = 
  (Triggerable_Execution_Tracer*)The_Squeak_Interpreter()->execution_tracer();
  if (tracer) {
    tracer->disable_recording_and_printing();
  }
}

void disable_context_switches() {
  The_Squeak_Interpreter()->suppress_context_switch_for_debugging = true;
}
void reenable_context_switches() {
  The_Squeak_Interpreter()->suppress_context_switch_for_debugging = false;
}


