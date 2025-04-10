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
// Inline implementations of functions defined in instr.h
//

#define AssertNotNull(a) AvmAssert(!AvmCore::isNullOrUndefined(a))

REALLY_INLINE
bool isObjectPtr(Atom a)
{
    // copy of AvmCore::isObject, but without the null check since we know we have nonnull
    AssertNotNull(a);
    return atomKind(a) == kObjectType;
}

REALLY_INLINE
bool isStringPtr(Atom a)
{
    // copy of AvmCore::isString, but without the null check since we know we have nonnull
    AssertNotNull(a);
    return atomKind(a) == kStringType;
}

REALLY_INLINE
Atom call_method_binding(Atom base, VTable* vtable, Binding b, int argc, Atom* atomv)
{
    // force receiver == base.  if caller used OP_callproplex then receiver was null.
    // todo: split out case for callproplex.
    atomv[0] = base;
    MethodEnv* method = vtable->methods[AvmCore::bindingToMethodId(b)];
    return method->coerceEnter(argc, atomv);
}

template <class E> REALLY_INLINE
Atom call_slot_binding(E env, Atom base, Binding b, int argc, Atom* atomv)
{
    ScriptObject* method = AvmCore::atomToScriptObject(base)->getSlotObject(AvmCore::bindingToSlotId(b));
    return op_call(env, method, argc, atomv);
}

REALLY_INLINE
Atom call_get_binding(Atom base, VTable* vtable, Binding b)
{
    int m = AvmCore::bindingToGetterId(b);
    MethodEnv *f = vtable->methods[m];
    return f->coerceEnter(base);
}

REALLY_INLINE
Atom call_obj_dynamic(Atom base, const Multiname* name, int argc, Atom* atomv)
{
    return AvmCore::atomToScriptObject(base)->callProperty(name, argc, atomv);
}

template <class E> REALLY_INLINE
Atom call_prim_dynamic(E env, Atom val, const Multiname* name, int argc, Atom* args)
{
    // primitive types are not dynamic, so we can go directly
    // to their __proto__ object
    ScriptObject* proto = env->toplevel()->toPrototype(val);
    Atom func = proto->getMultinameProperty(name);
    return op_call(env, func, argc, args);
}

/**
 * OP_call.
 *
 * arg0 = argv[0]
 * arg1 = argv[1]
 * argN = argv[argc]
 */
template <class E> REALLY_INLINE
Atom op_call(E env, Atom func, int argc, Atom* atomv)
{
    if (AvmCore::isObject(func))
        return AvmCore::atomToScriptObject(func)->call(argc, atomv);

    // The construction of the multiname and the resulting error string is
    // delegated because in-lining it here prevents the call to call() from
    // being a tail call - the address of a local multiname is taken, this
    // makes GCC (arguably incorrectly, given the scope of the variable)
    // turn off tail calling.

    env->toplevel()->throwTypeErrorWithName(kCallOfNonFunctionError, "value");
    return unreachableAtom;
}

/** specialized op_call when you have a ScriptObject* already for the function */
template <class E> REALLY_INLINE
Atom op_call(E env, ScriptObject* func, int argc, Atom* atomv)
{
    if (func)
        return func->call(argc, atomv);
    env->toplevel()->throwTypeErrorWithName(kCallOfNonFunctionError, "value");
    return unreachableAtom;
}

/**
 * OP_construct.  Note that arguments are in the opposite order from AVM.
 *
 * this = argv[0] // ignored
 * arg1 = argv[1]
 * argN = argv[argc]
 */
template <class E> REALLY_INLINE
Atom op_construct(E env, Atom ctor, int argc, Atom* atomv)
{
    if (AvmCore::isObject(ctor))
        return AvmCore::atomToScriptObject(ctor)->construct(argc, atomv);

    env->toplevel()->throwTypeError(kConstructOfNonFunctionError);
    return unreachableAtom;
}

template <class E> REALLY_INLINE
Binding getBinding(E env, VTable* vtable, const Multiname* ref)
{
    return getBinding(env, vtable->traits, ref);
}

template <class E> REALLY_INLINE
ArrayObject* newarray(E caller_env, int argc, Atom* ap) {
    Toplevel* toplevel = caller_env->toplevel();
    ArrayClass* arrayClass = toplevel->arrayClass;
    return arrayClass->newarray(ap, argc);
}

template <class E> REALLY_INLINE
Atom constructprop(E env, const Multiname* multiname, int argc, Atom* atomv)
{
    Toplevel* toplevel = env->toplevel();
    return constructprop(toplevel, multiname, argc, atomv, toVTable(toplevel, atomv[0]));
}

template <class E> REALLY_INLINE
Atom coerce(E env, Atom atom, Traits* expected)
{
    // do a couple of quick checks to see if we can bail early, since it's often the case
    // that the type is already what we expect (and we can determine that quickly
    // by checks against the Traits BuiltinType)
    if (!expected)
        return atom;

    if (AvmCore::atomDoesNotNeedCoerce(atom, BuiltinType(expected->builtinType)))
        return atom;

    return coerceImpl(env->toplevel(), atom, expected);
}

} // namespace avmplus
