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

#include "avmplus.h"

namespace avmplus
{
#if defined FEATURE_TEEWRITER
    TeeWriter::TeeWriter(CodeWriter* coder1, CodeWriter* coder2)
        : coder1(coder1)
        , coder2(coder2)
    {
        AvmAssert(coder1 != NULL);
        AvmAssert(coder2 != NULL);
    }

    TeeWriter::~TeeWriter()
    {
    }

    void TeeWriter::write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type) {
        coder1->write(state, pc, opcode, type);
        coder2->write(state, pc, opcode, type);
    }

    void TeeWriter::writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits* type)
    {
        coder1->writeOp1(state, pc, opcode, opd1, type);
        coder2->writeOp1(state, pc, opcode, opd1, type);
    }

    void TeeWriter::writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type)
    {
        coder1->writeOp2(state, pc, opcode, opd1, opd2, type);
        coder2->writeOp2(state, pc, opcode, opd1, opd2, type);
    }

    void TeeWriter::writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr opd1, uint32_t opd2, Traits* type)
    {
        coder1->writeInterfaceCall(state, pc, opcode, opd1, opd2, type);
        coder2->writeInterfaceCall(state, pc, opcode, opd1, opd2, type);
    }

    void TeeWriter::writeNip(FrameState* state, const byte *pc)
    {
        coder1->writeNip(state, pc);
        coder2->writeNip(state, pc);
    }

    void TeeWriter::writeCheckNull(FrameState* state, uint32_t index)
    {
        coder1->writeCheckNull(state, index);
        coder2->writeCheckNull(state, index);
    }

    void TeeWriter::writeCoerce(FrameState* state, uint32_t index, Traits *type)
    {
        coder1->writeCoerce(state, index, type);
        coder2->writeCoerce(state, index, type);
    }

    void TeeWriter::writePrologue(FrameState* state, const byte *pc)
    {
        coder1->writePrologue(state, pc);
        coder2->writePrologue(state, pc);
    }

    void TeeWriter::writeEpilogue(FrameState* state)
    {
        coder1->writeEpilogue(state);
        coder2->writeEpilogue(state);
    }

    void TeeWriter::writeBlockStart(FrameState* state)
    {
        coder1->writeBlockStart(state);
        coder2->writeBlockStart(state);
    }

    void TeeWriter::writeOpcodeVerified(FrameState* state, const byte* pc, AbcOpcode opcode) {
        coder1->writeOpcodeVerified(state, pc, opcode);
        coder2->writeOpcodeVerified(state, pc, opcode);
    }

    void TeeWriter::writeFixExceptionsAndLabels(FrameState* state, const byte* pc) {
        coder1->writeFixExceptionsAndLabels(state, pc);
        coder2->writeFixExceptionsAndLabels(state, pc);
    }

    void TeeWriter::formatOperand(PrintWriter& buffer, Value& v) {
        coder1->formatOperand(buffer, v);
        coder2->formatOperand(buffer, v);
    }

    void TeeWriter::cleanup() {
        coder1->cleanup();
        coder2->cleanup();
    }

#endif // FEATURE_TEEWRITER

    NullWriter::NullWriter(CodeWriter* coder)
        : coder(coder) {
        AvmAssert(coder != NULL);
    }

    NullWriter::~NullWriter()
    {}

    void NullWriter::write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type)
    {
        coder->write(state, pc, opcode, type);
    }

    void NullWriter::writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd, Traits *type)
    {
        coder->writeOp1(state, pc, opcode, opd, type);
    }

    void NullWriter::writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type)
    {
        coder->writeOp2(state, pc, opcode, opd1, opd2, type);
    }

    void NullWriter::writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr opd1, uint32_t opd2, Traits* type)
    {
        coder->writeInterfaceCall(state, pc, opcode, opd1, opd2, type);
    }

    void NullWriter::writeNip(FrameState* state, const byte *pc)
    {
        coder->writeNip(state, pc);
    }

    void NullWriter::writeCheckNull(FrameState* state, uint32_t index)
    {
        coder->writeCheckNull(state, index);
    }

    void NullWriter::writeCoerce(FrameState* state, uint32_t index, Traits *type)
    {
        coder->writeCoerce(state, index, type);
    }

    void NullWriter::writePrologue(FrameState* state, const byte *pc)
    {
        coder->writePrologue(state, pc);
    }

    void NullWriter::writeEpilogue(FrameState* state)
    {
        coder->writeEpilogue(state);
    }

    void NullWriter::writeBlockStart(FrameState* state)
    {
        coder->writeBlockStart(state);
    }

    void NullWriter::writeOpcodeVerified(FrameState* state, const byte* pc, AbcOpcode opcode)
    {
        coder->writeOpcodeVerified(state, pc, opcode);
    }

    void NullWriter::writeFixExceptionsAndLabels(FrameState* state, const byte* pc)
    {
        coder->writeFixExceptionsAndLabels(state, pc);
    }

    void NullWriter::formatOperand(PrintWriter& buffer, Value& v)
    {
        coder->formatOperand(buffer, v);
    }

    void NullWriter::cleanup()
    {
        coder->cleanup();
    }

#ifdef VMCFG_LOOKUP_CACHE
    LookupCacheBuilder::LookupCacheBuilder()
    {
        this->next_cache = 0;
        this->caches = NULL;
        this->num_caches = 0;
    }

    void LookupCacheBuilder::cleanup()
    {
        if (caches) {
            mmfx_delete_array(caches);
            caches = NULL;
        }
    }

    // The cache structure is expected to be small in the normal case, so use a
    // linear list.  For some programs, notably classical JS programs, it may however
    // be larger, and we may need a more sophisticated structure.
    uint32_t LookupCacheBuilder::allocateCacheSlot(uint32_t imm30)
    {
        for ( int i=0 ; i < next_cache ; i++ )
            if (caches[i] == imm30)
                return i;
        if (next_cache == num_caches) {
            uint32_t newcap = num_caches + num_caches/2 + 5; // 0 5 12 23 39 66 ...
            uint32_t* new_cache = mmfx_new_array(uint32_t, newcap);
            if (num_caches > 0) {
                VMPI_memcpy(new_cache, caches, sizeof(uint32_t)*num_caches);
                mmfx_delete_array(caches);
            }
            caches = new_cache;
            num_caches = newcap;
        }
        caches[next_cache] = imm30;
        return next_cache++;
    }
#endif // VMCFG_LOOKUP_CACHE

    CodeWriter::~CodeWriter()
    { }

    void CodeWriter::write(FrameState*, const byte *, AbcOpcode, Traits*)
    { }

    void CodeWriter::writeOp1(FrameState*, const byte *, AbcOpcode, uint32_t, Traits*)
    { }

    void CodeWriter::writeOp2(FrameState*, const byte *, AbcOpcode, uint32_t, uint32_t, Traits*)
    { }

    void CodeWriter::writeInterfaceCall(FrameState*, const byte *, AbcOpcode, uintptr_t, uint32_t, Traits*)
    { }

    void CodeWriter::writeNip(FrameState*, const byte *)
    { }

    void CodeWriter::writeCheckNull(FrameState*, uint32_t)
    { }

    void CodeWriter::writeCoerce(FrameState*, uint32_t, Traits*)
    { }

    void CodeWriter::writePrologue(FrameState*, const byte *)
    { }

    void CodeWriter::writeEpilogue(FrameState*)
    { }

    void CodeWriter::writeBlockStart(FrameState*)
    { }

    void CodeWriter::writeOpcodeVerified(FrameState*, const byte *, AbcOpcode)
    { }

    void CodeWriter::writeFixExceptionsAndLabels(FrameState*, const byte *)
    { }

    void CodeWriter::formatOperand(PrintWriter&, Value&)
    { }

    void CodeWriter::cleanup()
    { }
}
