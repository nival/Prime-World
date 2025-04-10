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
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
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

namespace avmplus
{

REALLY_INLINE Atom Toplevel::callproperty(Atom base, const Multiname* name, int argc, Atom* atomv, VTable* vtable)
{
    AssertNotNull(base);
    Binding b = avmplus::getBinding(this, vtable, name);
    return avmplus::callprop_b(this, base, name, argc, atomv, vtable, b);
}

REALLY_INLINE VTable* Toplevel::toVTable(Atom atom)
{
    return avmplus::toVTable(this, atom);
}

REALLY_INLINE Atom Toplevel::op_call(Atom method, int argc, Atom* atomv)
{
    return avmplus::op_call(this, method, argc, atomv);
}

REALLY_INLINE Atom Toplevel::op_construct(Atom ctor, int argc, Atom* atomv)
{
    return avmplus::op_construct(this, ctor, argc, atomv);
}

REALLY_INLINE Binding Toplevel::getBinding(Traits* traits, const Multiname* ref) const
{
    return avmplus::getBinding(this, traits, ref);
}

REALLY_INLINE Atom Toplevel::constructprop(const Multiname *name, int argc, Atom* atomv, VTable* vtable)
{
    return avmplus::constructprop(this, name, argc, atomv, vtable);
}

REALLY_INLINE Atom Toplevel::op_applytype(Atom obj, int argc, Atom* atomv)
{
    return avmplus::op_applytype(this, obj, argc, atomv);
}

REALLY_INLINE QNameObject* Toplevel::ToAttributeName(const Stringp arg)
{
    return ToAttributeName(arg->atom());
}

REALLY_INLINE Atom Toplevel::coerce(Atom atom, Traits* expected) const
{
    return avmplus::coerce(this, atom, expected);
}

REALLY_INLINE ClassClosure* Toplevel::getBuiltinClass(int class_id) const
{
    return _builtinClasses[class_id]
        ? _builtinClasses[class_id]
        : const_cast<Toplevel*>(this)->resolveBuiltinClass(class_id);
}

// static
REALLY_INLINE bool Toplevel::contains(const uint32 *uriSet, uint32 ch)
{
    return (ch<0x80) && (uriSet[ch>>5]&(1<<(ch&0x1f))) != 0;
}

REALLY_INLINE void Toplevel::throwReferenceError(int id, const Multiname& multiname, const Traits* traits) const
{
    throwReferenceError(id, &multiname, traits);
}

REALLY_INLINE void Toplevel::throwReferenceError(int id, const Multiname& multiname) const
{
    throwReferenceError(id, &multiname);
}

#ifndef DEBUGGER
REALLY_INLINE void Toplevel::throwVerifyError(int id, Stringp) const
{
    throwVerifyError(id);
}

REALLY_INLINE void Toplevel::throwVerifyError(int id, Stringp, Stringp) const
{
    throwVerifyError(id);
}
#endif // !DEBUGGER

REALLY_INLINE AbcEnv* Toplevel::abcEnv() const
{
    return _abcEnv;
}

REALLY_INLINE DomainEnv* Toplevel::domainEnv() const
{
    return _abcEnv->domainEnv();
}

REALLY_INLINE AvmCore* Toplevel::core() const
{
    return _abcEnv->pool()->core;
}

REALLY_INLINE MMgc::GC* Toplevel::gc() const
{
    return core()->GetGC();
}

REALLY_INLINE ScriptObject* Toplevel::global() const
{
    return _global;
}

REALLY_INLINE Atom Toplevel::atom() const
{
    return _global->atom();
}

REALLY_INLINE Atom Toplevel::add2(Atom val1, Atom val2)
{
    return avmplus::op_add(this->core(), val1, val2);
}

} // namespace avmplus
