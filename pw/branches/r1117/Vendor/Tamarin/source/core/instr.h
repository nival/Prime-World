/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

namespace avmplus {

//
// ABC Instruction implementations and helper functions.
//
// Many are parameterized on E (environment) where E can be Toplevel*
// or MethodEnv*, because often it pays to defer loading those pointers
// until it's needed, which often is only in the error case.
//
// the JIT uses MethodEnv instantiations.  The interpreter and Toplevel
// classes currently use Toplevel* instantiations.
//

/**
 * find the binding for a property given a full multiname reference.  The lookup
 * must produce a single binding, or it's an error.  Note that the name could be
 * bound to the same binding in multiple namespaces.
 */
template <class E>
Binding getBinding(E env, Traits* traits, const Multiname* ref);

/**
 * specialized getBinding() when you only have vtable.  hides the
 * traits lookup from vtable
 */
template <class E>
Binding getBinding(E env, VTable* vtable, const Multiname* ref);

/**
 * implements OP_call, including error handling for non-callable values
 */
template <class E>
Atom op_call(E env, Atom func, int argc, Atom* atomv);

/**
 * specialized OP_call implementation when you have a ScriptObject*
 * already.  Includes null pointer handling
 */
template <class E>
Atom op_call(E env, ScriptObject* func, int argc, Atom* atomv);

/**
 * implements OP_construct, including error handling for non-constructor
 * values of "ctor"
 */
template <class E>
Atom op_construct(E env, Atom ctor, int argc, Atom* atomv);

/**
 * implements OP_callproperty.  Caller is responsible for obtaining vtable
 * and binding, usually by calling toVTable() and getBinding().  Null
 * pointer checking must be done by caller.
 */
template <class E>
Atom callprop_b(E env, Atom base, const Multiname* name, int argc, Atom* atomv, VTable* vtable, Binding b);

/**
 * get the __proto__ object for this value.  When the value is an object,
 * we look it up directly.  For primitives (String, Namespace, int,
 * Boolean, uint, and Number, we get the prototype from the primitive's
 * class object.  Includes null/undefined error handling.
 */
template <class E>
ScriptObject* toPrototype(Atom obj);

/**
 * get the vtable for the given value, or throw null/undefined exception.
 * when the value is a primitive we get the vtable from the environment.
 */
template <class E>
VTable* toVTable(E env, Atom atom);

/**
 * OP_applytype implementation.
 * used to create concrete class objects for parameterizations of Vector.
 */
template <class E>
Atom op_applytype(E env, Atom factory, int argc, Atom* args);

/**
 * implementaion of OP_newarray for creating array literals
 */
template <class E>
ArrayObject* newarray(E caller_env, int argc, Atom* ap);

/**
 * implementation of OP_astype when RHS type is not
 * known at JIT time
 */
template <class E>
Atom astype_late(E caller_env, Atom value, Atom type);

/**
 * implementation of OP_instanceof
 */
template <class E>
Atom instanceof(E caller_env, Atom val, Atom ctor);

/**
 * implementation of OP_in
 */
template <class E>
Atom op_in(E caller_env, Atom name, Atom obj);

/**
 * inline-cache enabled finddef.  if the cache for this slot is valid, return
 * the result from calling finddef on this (env,multiname) pair previously.
 */
ScriptObject* finddef_cache(MethodEnv* env, const Multiname* name, uint32_t slot);

/**
 * Implementation of OP_constructprop
 */
template <class E>
Atom constructprop(E env, const Multiname* multiname, int argc, Atom* atomv);
Atom constructprop(Toplevel* toplevel, const Multiname* multiname, int argc, Atom* atomv, VTable* vtable);

/**
 * This is the implicit coercion operator.  It is kind of like a
 * Java downcast, but because of how E4 works, there are some cases
 * when it returns a different value than what you pass in.
 *
 * It will happily return null if you pass in null for
 * any reference type.  And, it will throw an exception if the
 * value is not in the type's value set.  It does not do type
 * conversion.
 *
 * @param  atom      The atom containing the value to coerce.
 * @param  itraits   The itraits of the type to coerce to.
 * @return The coerced atom.
 * @throws Exception if the value is not in the type's value
 *                   set.
 */
Atom coerceImpl(const Toplevel*, Atom atom, Traits* expected);
template <class E>
Atom coerce(E env, Atom atom, Traits* expected);

/**
 * coerce specialized for objects; coerceobj() either throws an error
 * or returns with no side effects
 */
template <class E>
void coerceobj(E env, ScriptObject* obj, Traits*);

/**
 * generic implementation of OP_add
 */
Atom op_add(AvmCore*, Atom lhs, Atom rhs);

void FASTCALL mop_rangeCheckFailed(MethodEnv* env);
// load-and-sign-extend
int32_t FASTCALL mop_lix8(const void* addr); 
int32_t FASTCALL mop_lix16(const void* addr);
// load-and-zero-extend
int32_t FASTCALL mop_liz8(const void* addr);
int32_t FASTCALL mop_liz16(const void* addr); 
int32_t FASTCALL mop_li32(const void* addr);
double FASTCALL mop_lf32(const void* addr);
double FASTCALL mop_lf64(const void* addr);
void FASTCALL mop_si8(void* addr, int32_t value);
void FASTCALL mop_si16(void* addr, int32_t value);
void FASTCALL mop_si32(void* addr, int32_t value);
void mop_sf32(void* addr, double value);
void mop_sf64(void* addr, double value);

} // namespace avmplus
