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

#ifndef __avmplus_Coder__
#define __avmplus_Coder__

namespace avmplus
{
    class CodeWriter {
    public:

        CodeWriter();
        virtual ~CodeWriter();

        virtual void write(FrameState* state, const byte *pc, AbcOpcode opcode, Traits *type);
        virtual void writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits *type);
        virtual void writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type);
        virtual void writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr_t opd1, uint32_t opd2, Traits* type);
        virtual void writeNip(FrameState* state, const byte *pc);
        virtual void writeCheckNull(FrameState* state, uint32_t index);
        virtual void writeCoerce(FrameState* state, uint32_t index, Traits* type);
        virtual void writePrologue(FrameState* state, const byte *pc);
        virtual void writeEpilogue(FrameState* state);
        virtual void writeBlockStart(FrameState* state);
        virtual void writeOpcodeVerified(FrameState* state, const byte *pc, AbcOpcode opcode);
        virtual void writeFixExceptionsAndLabels(FrameState* state, const byte *pc);
        virtual void formatOperand(PrintWriter& buffer, Value& v);
        virtual void cleanup();

        // convenience functions
        void write(FrameState* state, const byte *pc, AbcOpcode opcode);
        void writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1);
        void writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2);
    };

#if defined FEATURE_TEEWRITER
    class TeeWriter : public CodeWriter {
    public:
        CodeWriter* coder1;  // deleted elsewhere
        CodeWriter* coder2;

        TeeWriter(CodeWriter* coder1, CodeWriter* coder2);
        ~TeeWriter();
        void write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type);
        void writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits* type);
        void writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type);
        void writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr_t opd1, uint32_t opd2, Traits* type);
        void writeNip(FrameState* state, const byte *pc);
        void writeCheckNull(FrameState* state, uint32_t index);
        void writeCoerce(FrameState* state, uint32_t index, Traits *type);
        void writePrologue(FrameState* state, const byte *pc);
        void writeEpilogue(FrameState* state);
        void writeBlockStart(FrameState* state);
        void writeOpcodeVerified(FrameState* state, const byte *pc, AbcOpcode opcode);
        void writeFixExceptionsAndLabels(FrameState* state, const byte *pc);
        void formatOperand(PrintWriter& buffer, Value& v);
        void cleanup();
    };
#endif // FEATURE_TEEWRITER

    class NullWriter : public CodeWriter {
    public:
        CodeWriter* coder;       // the next leg of the pipeline

        NullWriter(CodeWriter* coder);
        ~NullWriter();
        void write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type);
        void writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits *type);
        void writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type);
        void writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr_t opd1, uint32_t opd2, Traits* type);
        void writeNip(FrameState* state, const byte *pc);
        void writeCheckNull(FrameState* state, uint32_t index);
        void writeCoerce(FrameState* state, uint32_t index, Traits *type);
        void writePrologue(FrameState* state, const byte *pc);
        void writeEpilogue(FrameState* state);
        void writeBlockStart(FrameState* state);
        void writeOpcodeVerified(FrameState* state, const byte *pc, AbcOpcode opcode);
        void writeFixExceptionsAndLabels(FrameState* state, const byte *pc);
        void formatOperand(PrintWriter& buffer, Value& v);
        void cleanup();
    };

#ifdef VMCFG_LOOKUP_CACHE
    /**
     * helper class for building the layout of a lookup cache, used during
     * jit compilation or wordcode translation.
     */
    class LookupCacheBuilder
    {
        // entry i has an imm30 value that represents the multiname whose entry in the MethodEnv's lookup cache is 'i'
        uint32_t* caches;

        // number of entries in 'caches'
        int num_caches;

    public:
        // next free entry in 'caches'
        int next_cache;
        uint32_t get_entry(int i);

    public:
        LookupCacheBuilder();

        /** allocate a new cache slot or reuse an existing one with the same imm30 */
        uint32_t allocateCacheSlot(uint32_t imm30);

        void cleanup();
    };
#endif
}
#endif  /* __avmplus_Coder__ */
