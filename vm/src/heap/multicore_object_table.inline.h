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


# if Use_Object_Table

inline Oop Multicore_Object_Table::allocate_oop_and_set_backpointer(Object_p obj, int rank  COMMA_DCL_ESB) {
  Oop r = allocate_oop(rank COMMA_USE_ESB);
  obj->set_backpointer(r); // should never be a read-mostly obj anyway
  set_object_for(r, obj  COMMA_USE_ESB);
  ++allocatedEntryCount[rank];
  ++allocationsSinceLastQuery[rank];
  return r;
}

inline Oop Multicore_Object_Table::allocate_oop_and_set_preheader(Object_p obj, int r  COMMA_DCL_ESB) { 
  obj->initialize_preheader();
  return allocate_oop_and_set_backpointer(obj, r  COMMA_USE_ESB); 
}

# endif // if Use_Object_Table

