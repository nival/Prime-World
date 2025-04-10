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
 * Portions created by the Initial Developer are Copyright (C) 2004-2008
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

#ifndef __avmplus_CdeclThunk__
#define __avmplus_CdeclThunk__

namespace avmplus
{
	// used to call a MethodEnv with a C cdecl implementation
	
	// TODO for x86-64, we probably want to split this into real 32-bit integer returning variant
	Atom coerce32CdeclArgDescEnter(Traits* retTraits, uintptr_t argDesc, MethodEnv* env, va_list ap);
	Atom coerce32CdeclArgDescEnter(Traits* retTraits, char* argDesc, MethodEnv* env, va_list ap);
	Atom coerce32CdeclArgDescEnter(Traits* retTraits, MethodEnv* env, int argc, Atom* argv);
	Atom coerce32CdeclArgDescEnter(Traits* retTraits, MethodEnv* env, int argc, uint32_t* ap);
	double coerceNCdeclArgDescEnter(uintptr_t argDesc, MethodEnv* env, va_list ap);
	double coerceNCdeclArgDescEnter(char* argDesc, MethodEnv* env, va_list ap);
	double coerceNCdeclArgDescEnter(MethodEnv* env, int argc, Atom* argv);
	double coerceNCdeclArgDescEnter(MethodEnv* env, int argc, uint32_t* ap);

	// used to convert C parameters to impl32 style (argc, ap)
	
	// calculate size needed for ap style argument block
	int32 argDescApSize(uintptr_t argDesc, MethodEnv* env);
	int32 argDescApSize(char* argDesc, MethodEnv* env);
	// convert arguments to ap style argument block, returning "argc"
	int32 argDescArgsToAp(void* args, uintptr_t argDesc, MethodEnv* env, va_list ap);
	int32 argDescArgsToAp(void* args, char* argDesc, MethodEnv* env, va_list ap);

	// used to convert C parameters to Atom* style (argc, atomv)
	
	// return number of arguments in description
	int32 argDescArgCount(uintptr_t argDesc);
	int32 argDescArgCount(char* argDesc);
	// convert arguments to Atoms
	void argDescArgsToAtomv(Atom* args, uintptr_t argDesc, MethodEnv* env, va_list ap);
	void argDescArgsToAtomv(Atom* args, char* argDesc, MethodEnv* env, va_list ap);
	
#ifdef VMCFG_AOT
	Atom aotThunker(MethodEnv* env, uint32_t argc, Atom* argv);
	double aotThunkerN(MethodEnv* env, uint32_t argc, Atom* argv);
#endif
}

#endif

