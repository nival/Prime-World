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

#ifndef __avmplus_Interpreter__
#define __avmplus_Interpreter__

namespace avmplus
{
	/**
	 * interpFPR/GPR() are stubs wrapping the main loop of the AVM+
	 * interpreter: interpBoxed().
	 *
	 * The native code compiler is used by default
	 * for executing AVM+ bytecode, since it is faster by
	 * nature, but the AVM+ interpreter is used in some cases:
	 *
	 * - It is used to execute AVM+ code when the jit flag is
	 *   set to false (-Dinterp in command-line shell)
	 * - It is used when the target platform does not support
	 *   the native code compiler.
	 * - Used by default when the method is not likely to run
	 *   more than once. e.g. script and static-init methods.
	 *
	 * @param methodEnv   The method to execute.
	 * @param argc number of args
	 * @param ap arg list
	 * @return The return value of the method that was executed.
	 * @throws Exception if the method throws an exception.
	 */
	uintptr_t interpGPR(MethodEnv* method, int argc, uint32 *ap); // returns Atom, int/uint, or a pointer
	double interpFPR(MethodEnv* method, int argc, uint32 *ap); // really returns double

	// main interpreter method.  Signature should correspond to AtomMethodProc to allow tail calls to here
	Atom interpBoxed(MethodEnv* method, int argc, Atom* ap);

#ifdef AVMPLUS_DIRECT_THREADED
	void** interpGetOpcodeLabels();
#endif
}

//#  define LAST_SUPERWORD_OPCODE    ((50<<8) | OP_ext)

#endif // __avmplus_Interpreter__
