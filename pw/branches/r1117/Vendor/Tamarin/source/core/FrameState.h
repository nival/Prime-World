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

#ifndef __avmplus_FrameState__
#define __avmplus_FrameState__

#if defined FEATURE_NANOJIT
#  include "CodegenLIR.h"
#endif

namespace avmplus
{
    /**
     * represents a value in the verifier
     */
    class Value
    {
    public:
        Traits* traits;
    #if defined FEATURE_NANOJIT
        LIns* ins;
    #endif
        bool notNull;
        bool isWith;
        bool killed;
    };

    /**
     * this object holds the stack frame state at any given block entry.
     * the frame state consists of the types of each local, each entry on the
     * scope chain, and each operand stack slot.
     */
    class FrameState
    {
        // info about each local var in this frame.
        // length is verifier->frameSize, one entry per local, scope, and stack operand
        Value *locals;
    public:
        Verifier *verifier;
    #if defined FEATURE_NANOJIT
        CodegenLabel label;
    #endif
        int32_t pc; // offset from code_start
        int32_t scopeDepth;
        int32_t stackDepth;
        int32_t withBase;
        bool initialized;
        bool targetOfBackwardsBranch;
        bool insideTryBlock;

    public:
        FrameState(Verifier*);
        ~FrameState();

        void init(FrameState* other);
        Value& value(int32_t i);
        const Value& value(int32_t i) const;
        Value& scopeValue(int32_t i);
        const Value& scopeValue(int32_t i) const;
        Value& stackValue(int32_t i);
        Value& stackTop();
        int32_t sp() const;
        void setType(int32_t i, Traits* t, bool notNull=false, bool isWith=false);
        void pop(int32_t n=1);
        Value& peek(int32_t n=1);
        void pop_push(int32_t n, Traits* type, bool notNull=false);
        void push(Value& _value);
        void push(Traits* traits, bool notNull=false);
    };
}

// inline method definitions
#include "FrameState-inlines.h"

#endif /* __avmplus_FrameState__ */
