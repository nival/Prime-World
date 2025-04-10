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

#if defined(AVMPLUS_AMD64) && defined(_WIN64)
	extern "C"
	{
		_int64 __cdecl longjmp64(jmp_buf jmpbuf, _int64 arg);
	}
#endif

namespace avmplus
{
	//
	// Exception
	//

	Exception::Exception(AvmCore* core, Atom atom)
	{
		this->atom = atom;
		this->flags = 0;

        #ifdef DEBUGGER
		// If the exception atom is an Error object, copy its stack trace.
		// Otherwise, generate a new stack trace.
		if (AvmCore::istype(atom, core->traits.error_itraits))
		{
			stackTrace = ((ErrorObject*)AvmCore::atomToScriptObject(atom))->getStackTraceObject();
		}
		else
		{
			stackTrace = core->newStackTrace();
		}
		#else
		(void)core;
		#endif
	}
	
	bool Exception::isValid()
	{
		return atomKind(atom) == kObjectType;
	}
	
	//
	// ExceptionHandlerTable
	//
	
	ExceptionHandlerTable::ExceptionHandlerTable(int exception_count)
	{
		this->exception_count = exception_count;
		VMPI_memset(exceptions, 0, sizeof(ExceptionHandler)*exception_count);
	}
	
	//
	// ExceptionFrame
	//

	void ExceptionFrame::beginTry(AvmCore* core)
	{
		this->core = core;

		prevFrame = core->exceptionFrame;

		if (!prevFrame) {
			// Do special setup for first frame
			core->setStackBase();
		}

		core->exceptionFrame = this;

#ifdef DEBUGGER
		callStack = core->callStack;
#endif /* DEBUGGER */

		// beginTry() is called from both the TRY macro and from JIT'd code.  The TRY
		// macro will immediately change the value of catchAction right after the
		// call to beginTry(); but the JIT'd code does not change catchAction.  So,
		// we initialize catchAction to the value that it needs when we're called
		// from JIT'd code, that is, kCatchAction_SearchForActionScriptExceptionHandler.
		catchAction = kCatchAction_SearchForActionScriptExceptionHandler;

		this->stacktop = core->gc->allocaTop();
		
		savedMethodFrame = core->currentMethodFrame;
#ifdef VMCFG_AOT
		this->llvmUnwindStyle = 0;
#endif
	}

#ifdef VMCFG_AOT
	void ExceptionFrame::beginLlvmUnwindTry(AvmCore *core)
	{
		beginTry(core);
		this->llvmUnwindStyle = 1;
	}
#endif

	void ExceptionFrame::endTry()
	{
		if (core) {
			// ISSUE do we need to check core if it is set in constructor?
			core->exceptionFrame = prevFrame;

			core->gc->allocaPopTo(this->stacktop);

			core->currentMethodFrame = savedMethodFrame;
		}
	}
	
	void ExceptionFrame::throwException(Exception *exception)
	{
		core->exceptionAddr = exception;
#ifdef VMCFG_AOT
		if(this->llvmUnwindStyle) {
			llvm_unwind();
			return;
		}
#endif

		VMPI_longjmpNoUnwind(jmpbuf, 1); 
	}

	void ExceptionFrame::beginCatch()
	{
		core->exceptionFrame = prevFrame;

#ifdef DEBUGGER
		//AvmAssert(callStack && callStack->env);
		Profiler* profiler = core->profiler();
		if (profiler && profiler->profilingDataWanted && callStack && callStack->env())
			profiler->sendCatch(callStack->env()->method);

		core->callStack = callStack;
#endif // DEBUGGER

		core->currentMethodFrame = savedMethodFrame;

		core->gc->allocaPopTo(this->stacktop);
	}
}
