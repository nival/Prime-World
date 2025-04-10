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

#ifndef __avmplus_VTable__
#define __avmplus_VTable__


namespace avmplus
{
#if defined FEATURE_NANOJIT
	class ImtThunkEnv;

#if NJ_SOFTFLOAT
	// returning uint64_t here rather than uintptr_t is a trick: normally
	// we provide both GPR and FPR versions of calls, on the theory that
	// this is necessary to ensure the return value is always correct. in practice,
	// this seems to be a mostly defunct assumption, as every architecture we're interested
	// in returns values in registers (or register pairs), whether the result is fp or not.
	// still, this dichotomy has been maintained, mostly because it works and
	// hasn't been to painful. with new, table-based thunks this becomes hard to implement,
	// though, as a given IMT thunk can contain both kinds of calls, but C++ can't define
	// a function to return multiple types... however, in practice (as mentioned before) 
	// this seems to mostly be an historical artifact, with a notable exception of 
	// 32-bit NJ_SOFTFLOAT systems (eg ARM without VFP) -- if the compiler decides not
	// to tail-call (MSVC, I'm looking at you), the upper word of the softfloat result
	// can theoretically be clobbered by the compiler. declaring the result as uint64_t 
	// quietly ensures that won't be the case.
	//
	// admittedly, this is a bit fragile, but seems to be the least-objectionable
	// solution to this issue at the present time.
	typedef uint64_t GprImtThunkProcRetType;
#else
	// some big-endian architectures (specifically, PPC and Sparc) return 64-bit values with
	// the hi word in the register used for the lo-word of a 32-bit result, so using
	// uint64_t in all cases breaks things. since the trick above is really only needed for softfloat,
	// let's only use it there...
	typedef uintptr_t GprImtThunkProcRetType;
#endif
	
	typedef GprImtThunkProcRetType (*GprImtThunkProc)(ImtThunkEnv*, int, uint32*, uintptr_t);

#endif

	class VTable : public MMgc::GCObject
	{
#if defined FEATURE_NANOJIT
		friend class CodegenLIR;
		friend class ImtThunkEnv;
#endif
	private:
		MethodEnv* makeMethodEnv(MethodInfo* method, ScopeChain* scope);

#if defined FEATURE_NANOJIT
		void resolveImtSlot(uint32_t slot);

		// Helpers for resolveImtSlot
		void resolveImtSlotFromBase(uint32_t slot);
		bool resolveImtSlotSelf(uint32_t slot);

		// return uint64_t, not uintptr_t: see note for GprImtThunkProc
		static GprImtThunkProcRetType resolveImt(ImtThunkEnv* ite, int argc, uint32* ap, uintptr_t iid);
		static GprImtThunkProcRetType dispatchImt(ImtThunkEnv* ite, int argc, uint32* ap, uintptr_t iid);

	public:
#if defined FEATURE_NANOJIT
		// choose a number that is relatively prime to sizeof(MethodInfo)/8
		// since we use the MethodInfo pointer as the interface method id
		// smaller = dense table, few large conflict stubs
		// larger  = sparse table, many small conflict stubs 

	#ifdef _DEBUG
		enum { IMT_SIZE = 3 };  // good for testing all code paths
	#else
		enum { IMT_SIZE = 7 };  // good for performance
	#endif
#endif // FEATURE_NANOJIT

#endif

	public:
		VTable(Traits* traits, VTable* base, Toplevel* toplevel);
		void resolveSignatures(ScopeChain* scope);

		VTable* newParameterizedVTable(Traits* param_traits, Stringp fullname);

		size_t getExtraSize() const;
		MMgc::GC* gc() const;
		AvmCore* core() const;
		Toplevel* toplevel() const;

#ifdef AVMPLUS_VERBOSE
		Stringp format(AvmCore* core) const;
#endif

#ifdef DEBUGGER
		uint32 size() const;
#endif
	
	// ------------------------ DATA SECTION BEGIN
	private:
		Toplevel* const _toplevel;
	public:
		DWB(MethodEnv*) init;
		DWB(VTable*) base;
		DWB(VTable*) ivtable;
		Traits* const traits;
		bool linked;	// @todo -- surely there's a spare bit we can use for this.
		bool pad[3];

#if defined FEATURE_NANOJIT
		ImtThunkEnv* imt[VTable::IMT_SIZE];
#endif
		MethodEnv* methods[1]; // virtual method table
	// ------------------------ DATA SECTION END
	};
}

#endif // __avmplus_VTable__

