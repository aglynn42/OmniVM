/******************************************************************************
 *  Copyright (c) 2008 - 2010 IBM Corporation and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *    Stefan Marr, Vrije Universiteit Brussel - Initial Implementation
 ******************************************************************************/


# if Track_OnStackPointer

#include <assert.h>

/**
 * This class is used to track pointers on the stack.
 * The idea is that a global event can occur that invalidates the pointers
 * and this class is meant to signal all cases in which an invalid pointer
 * is used.
 */
template<typename T>
class tracked_ptr {
private:
  typedef tracked_ptr_registry< tracked_ptr<T> > registry_t;
  typedef typename tracked_ptr_registry< tracked_ptr<T> >::iterator iterator;
  
  friend class tracked_ptr_registry< tracked_ptr<T> >;
  
  static registry_t registry;
  
  T*       ptr;
  bool     valid;
  iterator it;
  
  iterator register_this() {
    return registry.register_tracked_ptr(this);
  }
    
  void unregister_and_invalidate() {
    registry.unregister_tracked_ptr(this, it);
    valid = false;
  }

public:
  
  /**
   * This operation will invalidate all pointers that are tracked
   * and on subsequent use, an assertion will fail.
   */
  static void invalidate_all_pointer() {
    registry.invalidate_all_pointer();
  }

  
  
  /**
   * The simple constructor will initialize the tracker to be invalid.
   * It will also register it, then we don't need to care about to many
   * different cases, I think.
   * The only thing we have to keep track is the pointer passed trough
   * in copy operations, and its validity.
   */
  explicit tracked_ptr() :
    ptr(NULL), valid(false), it(register_this()) {}
  
  /**
   * Constructor initialized with the pointer to be tracked.
   */
  explicit tracked_ptr(T* const ptr) :
    ptr(ptr), valid(true), it(register_this()) {}
  
  /**
   * Copy constructor
   */
  tracked_ptr(const tracked_ptr & t_ptr) :
    ptr(t_ptr.ptr), valid(t_ptr.valid), it(register_this()) {}
  
  ~tracked_ptr() {
    unregister_and_invalidate();
  }  
  
  tracked_ptr& operator=(tracked_ptr const & t_ptr) {
    ptr   = t_ptr.ptr;
    valid = t_ptr.valid;
    return *this;
  }

  tracked_ptr& operator=(T* const p) {
    ptr   = p;
    valid = true;
    return *this;
  }  
  
  /**
   * Cast operator to bool
   */
  operator bool() const {
    return valid && ptr;
  }
  
  /**
   * Cast operator to void*
   */
  operator void*() const {
    assert(is_valid());  // not sure why that was not here before, Stefan 2011-01-06
    return ptr;
  }
  
  operator T*() const {
    assert(is_valid());
    return ptr;
  }
  
  inline T& operator* () const {
    assert(is_valid());
    assert(ptr != NULL);
    return *ptr;
  }
  
  inline T* operator-> () const {
    assert(is_valid());
    assert(ptr != NULL);
    return ptr;
  }
  
  /**
   * Make sure there is nobody doing something stupid with the address.
   * Lets have it fail for now. In case there is a real need for it to work,
   * it can be changed by removing the assert.
   */
  inline T* const * operator& () const {
    assert(false); // This assert is added to avoid surprises. Remove with caution!
    return &ptr;
  }
  
  inline bool operator==(tracked_ptr const & t_ptr) const {
    return ptr == t_ptr.ptr;
  }

  inline bool operator!=(tracked_ptr const & t_ptr) const {
    return ptr != t_ptr.ptr;
  }

  /*inline bool operator==(const T* const p) const {
    return ptr == p;
  }
  
  inline bool operator!=(const T* const p) const {
    return ptr != p;
  }*/

  inline bool operator==(int const p) const {
    return ptr == (void*)p;
  }
  
  inline bool operator!=(int const p) const {
    return ptr != (void*)p;
  }
  
  inline T* get() const {
    return ptr;
  }
  
  static size_t pointers_on_stack() {
    return registry.size();
  }  
  
  bool is_valid() const {
    return valid;
  }
    
}; // tracked_ptr

/* STEFAN: this is not necessary for the moment, the bool() conversion operator
           is sufficient. And, overloading && breaks short circuiting, so stay
           away here! -- 2010-12-09
template<typename T>
inline bool operator&&(const bool a, tracked_ptr<T> const & t_ptr) {
  return a && t_ptr.is_valid() && t_ptr.get();
} */

template<typename T>
inline bool operator==(const bool a, tracked_ptr<T> const & t_ptr) {
  return a && t_ptr.is_valid() && t_ptr.get();
} 


template<typename T>
typename tracked_ptr<T>::registry_t tracked_ptr<T>::registry;

# endif // Track_OnStackPointer
