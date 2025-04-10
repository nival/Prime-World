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
#ifdef AVMPLUS_WORD_CODE

#  ifdef AVMPLUS_DIRECT_THREADED
#    define NEW_OPCODE(n)         ((uintptr_t)opcode_labels[n])
#  else
#    ifdef _DEBUG
#      define NEW_OPCODE(opcode)  ((opcode) | ((opcode) << 16))  // aids debugging
#    else
#      define NEW_OPCODE(opcode)  opcode
#    endif
#  endif
	
	// Abstract Base class
    class WordcodeTranslator : public CodeWriter
	{
	public:
		WordcodeTranslator() { };
		virtual ~WordcodeTranslator() { };
		
		// In all cases below, pc points to the opcode.
		
		virtual void computeExceptionFixups() = 0;

		// Call before every instruction to handle exception range translation and
		// fix up branches to this address
		virtual void fixExceptionsAndLabels(const uint8_t *pc) = 0;
		
		// Paste up the translated code and install it in info
		virtual uint32 epilogue(uintptr_t** code_result = NULL) = 0;
		
		// Handle specific instructions or instruction classes
		virtual void emitOp0(const uint8_t *pc, WordOpcode opcode) = 0;
		void emitOp0(WordOpcode opcode) { emitOp0(NULL, opcode); }
		virtual void emitOp1(const uint8_t *pc, WordOpcode opcode) = 0;
		virtual void emitOp1(WordOpcode opcode, uint32 operand) = 0;
		virtual void emitOp2(const uint8_t *pc, WordOpcode opcode) = 0;
		virtual void emitOp2(WordOpcode opcode, uint32 op1, uint32 op2) = 0;
#ifdef DEBUGGER
		virtual void emitDebug(const uint8_t *pc) = 0;
#endif
		virtual void emitRelativeJump(const uint8_t *pc, WordOpcode opcode) = 0;
		virtual void emitLookupswitch(const uint8_t *pc) = 0;
		virtual void emitLabel(const uint8_t *pc) = 0;
		virtual void emitPushbyte(const uint8_t *pc) = 0;
		virtual void emitPushshort(const uint8_t *pc) = 0;
		virtual void emitPushint(const uint8_t *pc) = 0;
		virtual void emitPushuint(const uint8_t *pc) = 0;
		virtual void emitGetscopeobject(const uint8_t *pc) = 0;

		// In this case, new_pc is the pc being jumped to
		virtual void emitAbsJump(const uint8_t *new_pc) = 0;

#ifdef SUPERWORD_PROFILING
		static void swprofStart();
		static void swprofStop();
		static void swprofCode(const uint32_t* start, const uint32_t* limit);
		static void swprofPC(const uint32_t* pc);
#endif
	};

#endif // AVMPUS_WORD_CODE
}
