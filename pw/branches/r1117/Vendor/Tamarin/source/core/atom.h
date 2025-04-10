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

#ifndef __avmplus_atom__
#define __avmplus_atom__


namespace avmplus
{
    // Atom should really be an intptr_t, but doing so can cause problematic compiles
    // because some platforms define intptr_t as an int64, and some as a long, which
    // create different overload possibilities in a few cases. Ideally, Atom should
    // be a unique pointer type (as it is in TT) but for now, avoid the code churn
    // by defining it the "old" way
    //
    // math friendly pointer (64 bits in LP 64 systems)
    #if defined (_MSC_VER) && (_MSC_VER >= 1300)
        #define AVMPLUS_TYPE_IS_POINTER_SIZED __w64
    #else
        #define AVMPLUS_TYPE_IS_POINTER_SIZED
    #endif
    #ifdef AVMPLUS_64BIT
    typedef AVMPLUS_TYPE_IS_POINTER_SIZED int64_t Atom;
    #else
    typedef AVMPLUS_TYPE_IS_POINTER_SIZED int32_t Atom;
    #endif

    /**
     * The AtomConstants namespace defines constants for
     * manipulating atoms.
     *
     * The atom is a primitive value in ActionScript.  Since
     * ActionScript is a dynamically typed language, an atom can
     * belong to one of several types: null, undefined, number,
     * integer, string, boolean, object reference.
     *
     * Atoms are encoded with care to take up the minimum
     * possible space.  An atom is represented by a 32-bit
     * integer, with the bottom 3 bits indicating the type.
     *
     *      32 bit atom
     *
     *  31             16 15     8 7   3 210
     *  dddddddd dddddddd dddddddd ddddd TTT
     *
     *  TTT
     *  000  - untagged
     *  001  object
     *  010  string
     *  011  namespace
     *  100  undefined
     *  101  boolean
     *  110  integer
     *  111  double
     *
     *  - using last 3 bits means allocations must be 8-byte aligned.
     *  - related types are 1 bit apart, e.g. int/double
     *
     *  kInteger atoms are used to represent integer values from -2^28..2^28-1,
     *  regardless of whether the context implies int, uint, or Number.
     *  If a number doesn't fit into that range it is stored as a kDoubleType
     *
     */
    namespace AtomConstants
    {
        /**
         * @name Atom types
         * These are the type values that appear in the bottom
         * 3 bits of an atom.
         */
        /*@{*/
        // cannot use 0 as tag, breaks atomWriteBarrier
        const Atom kUnusedAtomTag = 0;
        const Atom kObjectType    = 1;  // null=1
        const Atom kStringType    = 2;  // null=2
        const Atom kNamespaceType = 3;  // null=3
        const Atom kSpecialType   = 4;  // undefined=4
        const Atom kBooleanType   = 5;  // false=5 true=13
        const Atom kIntptrType    = 6;
        const Atom kDoubleType    = 7;
        /*@}*/

        /*
        other things you can do with math on atoms

        isNull          (unsigned)a < 4
        isUndefined     a == undefinedAtom
        isSpecial       (unsigned)a <= 4
        isNumber        a & 6 == 6

                            ^8  jlt(a<8)    ^2      jle(a<=4)
        true        1110  0110  t           1100    f
        false       0110  1110  f           0100    t
        undefined   0100  1100  f           0110    f
        */

        /**
         * @name Special atom values
         * These are the atoms for undefined, null, true
         * and false.
         */
        /*@{*/
        // there is no single null atom.  use isNull() to test, or
        // one of the following typed null atoms.  if you must, use NULL (0).
        const Atom nullObjectAtom = kObjectType|0;
        const Atom nullStringAtom = kStringType|0;
        const Atom nullNsAtom     = kNamespaceType|0;
        const Atom undefinedAtom  = kSpecialType|0; // 0x03
        const Atom trueAtom       = kBooleanType|0x08; // 0x0D
        const Atom falseAtom      = kBooleanType|0x00; // 0x05
        const Atom zeroIntAtom    = Atom(kIntptrType|0);

        // used in unreachable "return" clauses as a self-documenting invalid value.
        const Atom unreachableAtom = kUnusedAtomTag;
        /*@}*/

    }

#ifdef AVMPLUS_64BIT
    // in 64-bit builds, integer atoms can hold a 53-bit signed value.
    // (this is so that integer values can be interchanged with doubles with no loss of precision)
    const intptr_t atomMinIntValue = -(1LL<<53);
    const intptr_t atomMaxIntValue = (1LL<<53)-1;
#else
    // in 32-bit builds, integer atoms can hold a 29-bit signed value.
    const intptr_t atomMinIntValue = -(1L<<29);
    const intptr_t atomMaxIntValue = (1L<<29)-1;
#endif

    // sadly, these generate better code than the inlines in atom-inlines.h
    #define atomKind(a)     ((Atom)((uintptr_t(a) & 7)))
    #define atomPtr(a)      ((void*)(uintptr_t(a) & ~7))

    #define ISNULL(a) (((uintptr)a) < (uintptr)kSpecialType)

    // returns true if atom type is int.
    // Note that this DOES NOT imply that the Atom's value will
    // fit into an int32 (or a uint32); an integer atom's value
    // will always fit into an intptr_t, which may be more than
    // an int32 (or uint32) will hold on 64-bit architectures.
    bool            atomIsIntptr(Atom atom);

    // return true iff both atoms are of the given type. sometimes this is slightly
    // faster than calling atomIs(b1)&&atomIs(b2). (And yes, "atomIsBoth" is poor
    // grammar in English, but follows the "atomIsXXX -> bool" pattern)
    bool            atomIsBothIntptr(Atom atom1, Atom atom2);

    // if the atom is kIntptrType and will fit into an int32_t, return true
    // if the atom is kIntptrType and will NOT fit into an int32_t, return false
    // if the atom is not kIntptrType, assert
    bool            atomCanBeInt32(Atom atom);
    // if the atom is kIntptrType and will fit into an uint32_t, return true
    // if the atom is kIntptrType and will NOT fit into an uint32_t, return false
    // if the atom is not kIntptrType, assert
    bool            atomCanBeUint32(Atom atom);

    // getters to obtain the value.
    // these getters require that the type of the Atom be *exactly* what is requested;
    // no coercion is done (e.g., calling getDouble() on a Atom containing TypeInt will assert).
    intptr_t        atomGetIntptr(Atom atom);

    // if the given intptr can fit into an kIntptrType atom, return true.
    // if not (the magnitude is too large/small), return false.
    // WARNING: do not pass an (unsigned) uintptr_t value; you may get incorrect results.
    bool            atomIsValidIntptrValue(const intptr_t i);

    // if the given uintptr can fit into an kIntptrType atom, return true.
    // if not (the magnitude is too large/small), return false.
    // WARNING: do not pass a (signed) intptr_t value; you may get incorrect results.
    bool            atomIsValidIntptrValue_u(const uintptr_t u);

    // macro for profiling the frequencies of different Atom tags.
    // Must include vprof.h.  usage:   tagprof("histogram for my_atom", my_atom);
    #ifdef DOPROF
    #  define tagprof(n,v) _nhprof(n, uintptr_t(v)&7, 8, 0, 1, 2, 3, 4, 5, 6, 7)
    #else
    #  define tagprof(n,v)
    #endif

}

#endif // __avmplus_atom__
