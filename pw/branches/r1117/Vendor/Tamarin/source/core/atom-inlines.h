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

// inline functions that manipulate Atom go here.

#ifndef __avmplus_atom_inlines__
#define __avmplus_atom_inlines__

namespace avmplus
{
    // macros for these are defined in atom.h

    //inline AtomConstants::AtomKind atomKind(Atom a) { return AtomConstants::AtomKind(uintptr_t(a) & 7); }
    //inline void* atomPtr(Atom a) { return (void*)(uintptr_t(a) & ~7); }

    REALLY_INLINE bool atomIsIntptr(Atom atom)
    {
        return atomKind(atom) == kIntptrType;
    }

    REALLY_INLINE bool atomIsBothIntptr(Atom a, Atom b)
    {
        return ((((uintptr_t(a) ^ kIntptrType) | (uintptr_t(b) ^ kIntptrType)) & 7) == 0);
    }


    REALLY_INLINE bool atomCanBeInt32(Atom atom)
    {
        AvmAssert(atomIsIntptr(atom));
#ifdef AVMPLUS_64BIT
        intptr_t const i = atomGetIntptr(atom);
        int32_t const i32 = int32_t(i);
        return i == i32;
#else
        // int atoms always fit in int32 on 32-bit
        (void)atom;
        return true;
#endif
    }

    REALLY_INLINE bool atomCanBeUint32(Atom atom)
    {
        AvmAssert(atomIsIntptr(atom));
#ifdef AVMPLUS_64BIT
        intptr_t const i = atomGetIntptr(atom);
        uint32_t const u32 = uint32_t(i);
        return i == intptr_t(u32);
#else
        // int atoms always fit in uint32 on 32-bit, if they are >= 0
        return atom >= 0;
#endif
    }

    REALLY_INLINE intptr_t atomGetIntptr(Atom a)
    {
        AvmAssert(atomIsIntptr(a));
        AvmAssert(atomIsValidIntptrValue(intptr_t(a) >> 3));
        return intptr_t(a) >> 3;
    }

    REALLY_INLINE bool atomIsValidIntptrValue(const intptr_t i)
    {
#ifdef AVMPLUS_64BIT
        // we want 53 bits of precision, plus 3 bits for the tag bits,
        // so that's 64-53-3 = 8
        return (((i << 8) >> 8) == i);
#else
        return (((i << 3) >> 3) == i);
#endif
    }

    REALLY_INLINE bool atomIsValidIntptrValue_u(const uintptr_t u)
    {
        const uintptr_t MASK = ~(uintptr_t(atomMaxIntValue)>>1);
        return (u & MASK) == 0;
    }

    // unwrap an atom and return a ScriptObject*.  Doesn't use atomPtr(), because
    // using subtract allows the expression to be folded with other pointer math,
    // unlike the & ~7 in atomPtr().
    REALLY_INLINE ScriptObject* atomObj(Atom a)
    {
        AvmAssert(AvmCore::isObject(a)); // proper type and not null or undefined
        return (ScriptObject*) (uintptr_t(a) - kObjectType);
    }

    REALLY_INLINE bool atomGetBoolean(Atom a)
    {
        AvmAssert(a == trueAtom || a == falseAtom);
        return (a >> 3) != 0;
    }

} // namespace

#endif // __avmplus_atom_inlines__
