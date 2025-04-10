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

#ifndef __avmplus_MethodEnv__
#define __avmplus_MethodEnv__


namespace avmplus
{
	class MethodEnvProcHolder : public MMgc::GCObject
	{
		friend class CodegenLIR;

#if VMCFG_METHODENV_IMPL32
	protected:
		MethodEnvProcHolder(GprMethodProc p);
		union {
			GprMethodProc _implGPR;
			FprMethodProc _implFPR;
		};
#else
	protected:
		MethodEnvProcHolder(MethodInfo* m);
	public:
		MethodInfo* const method;
#endif
	public:
		GprMethodProc implGPR() const;
		FprMethodProc implFPR() const;
	};
	
	class MethodEnv : public MethodEnvProcHolder
	{
		friend class CodegenLIR;
		friend class MethodInfo;
		friend class MethodInfoProcHolder;
	#if VMCFG_METHODENV_IMPL32
		static uintptr_t delegateInvoke(MethodEnv* env, int32_t argc, uint32_t *ap);
	#endif
	public:
		/** vtable for the activation scope inside this method */
        ScriptObject* newActivation();

		/** getter lazily creates table which maps SO->MC */
		WeakKeyHashtable *getMethodClosureTable();

		MethodEnv(MethodInfo* method, ScopeChain* scope);

		AbcEnv* abcEnv() const;
		AvmCore* core() const;
		CodeContext* codeContext() const;
		DomainEnv* domainEnv() const;
		ScopeChain* scope() const;
		MethodEnv* super_init() const;
		Toplevel* toplevel() const;
		Stringp traitsName() const;
		Namespacep traitsNs() const;

		ScriptEnv* getScriptEnv(const Multiname *m) const;

		/**
		 * Coerces an array of actual parameters to the types
		 * required by a function's formal parameters, then invokes
		 * the method.  Args are provided as an array of atoms, not
		 * an array of native types.
		 *
		 * It is not well documented throughout, but it is generally
		 * assumed that argument arrays may /always/ be modified in
		 * place by the callee, thus coerceEnter may modify 'argv'
		 * (though not the ArrayObject 'a', of course).
		 *
		 * @param instance The "this" that the function
		 *                 is being invoked with; may be
		 *                 coerced by this method.
		 * @param argv The array of arguments to coerce
		 * @param argc The number of arguments
		 * @throws Exception May throw an ArgumentError or
		 *         TypeError if an argument cannot be coerced
		 *         to the required type
		 */
		Atom coerceEnter(Atom thisArg);
		Atom coerceEnter(Atom thisArg, ArrayObject* a);
		Atom coerceEnter(Atom thisArg, int32_t argc, Atom* argv);
		Atom coerceEnter(int32_t argc, Atom* argv);

	private:
		static Atom coerceEnter_interp(MethodEnv* env, int32_t argc, Atom* argv);
		static Atom coerceEnter_interp_nocoerce(MethodEnv* env, int32_t argc, Atom* argv);
		static Atom coerceEnter_generic(MethodEnv* env, int32_t argc, Atom* argv);

		MethodSignaturep get_ms();
		bool isInterpreted();
		Atom endCoerce(int32_t argc, uint32_t *ap, MethodSignaturep ms);
		int32_t  startCoerce(int32_t argc, MethodSignaturep ms);
		Atom coerceUnboxEnter(int32_t argc, Atom* atomv);
		void unboxCoerceArgs(Atom thisArg, ArrayObject *a, uint32_t *argv, MethodSignaturep ms);
		void unboxCoerceArgs(int32_t argc, Atom* in, uint32_t *ap, MethodSignaturep ms);
		void unboxCoerceArgs(Atom thisArg, int32_t argc, Atom* in, uint32_t *argv, MethodSignaturep ms);
		void FASTCALL nullcheckfail(Atom atom);
		Atom* FASTCALL coerceUnbox1(Atom atom, Traits* t, Atom* args);
		Atom* FASTCALL unbox1(Atom atom, Traits* t, Atom* args);

		VTable* getActivationVTable();
		VTable* buildActivationVTable();

	// helper functions used from compiled code
	public:
		void argcError(int32_t argc); // never returns; throws argument count error
	    void nullcheck(Atom atom);	  // null pointer check
	    void npe();					  // never returns; throws null pointer error

		ArrayObject* createRest(Atom* argv, int32_t argc);
		Atom getpropertylate_i(Atom obj, int32_t index) const;
		Atom getpropertylate_u(Atom obj, uint32_t index) const;

#if defined FEATURE_NANOJIT || defined VMCFG_AOT
		void setpropertyHelper(Atom obj, /* not const */ Multiname *multi, Atom value, VTable *vtable, Atom index);
		void initpropertyHelper(Atom obj, /* not const */ Multiname *multi, Atom value, VTable *vtable, Atom index);
		Atom getpropertyHelper(Atom obj, /* not const */ Multiname *multi, VTable *vtable, Atom index);
		Atom delpropertyHelper(Atom obj, /* not const */ Multiname *multi, Atom index);

		void initMultinameLateForDelete(Multiname& name, Atom index);
		ArrayObject* createArgumentsHelper(int32_t argc, uint32_t *ap);
		ArrayObject* createRestHelper(int32_t argc, uint32_t *ap);
#endif

		ScriptObject* newcatch(Traits *traits);
		/**
		 * used for defining and resolving imported definitions.
		 */
		ScriptObject* finddef(const Multiname* name) const;

		/**
		 * implementation of object initializers
		 */
		ScriptObject* op_newobject(Atom* sp, int32_t argc) const;

		/** Implementation of OP_nextname */		
		Atom nextname(Atom objAtom, int32_t index) const;

		/** Implementation of OP_nextvalue */
		Atom nextvalue(Atom objAtom, int32_t index) const;

		/** Implementation of OP_hasnext */		
		int32_t hasnext(Atom objAtom, int32_t index) const;

		/** Implementation of OP_hasnext2 */		
		int32_t hasnextproto(Atom& objAtom, int& index) const;
		
		/**
		 * OP_newfunction
		 * see 13.2 creating function objects
		 */
		ClassClosure* newfunction(MethodInfo *function, 
						 ScopeChain* outer,
						 Atom* scopes) const;

		/**
		 * OP_newclass
		 */

		ClassClosure* newclass(Traits* ctraits,
			          ClassClosure* base,
					  ScopeChain* outer,
					  Atom* scopes) const;

		void initproperty(Atom obj, const Multiname* multiname, Atom value, VTable* vtable) const;
		void setpropertylate_i(Atom obj, int32_t index, Atom value) const;
		void setpropertylate_u(Atom obj, uint32_t index, Atom value) const;

		/** same as callproperty but only considers the bindings in given vtable */
		Atom callsuper(const Multiname* name, int32_t argc, Atom* atomv) const;

		Atom delproperty(Atom obj, const Multiname* multiname) const;

		/**
		 * Reads a property from an object, with the property
		 * to retrieve specified by its binding.
		 * The binding was likely retrieved using getBinding.
		 * @param obj Object to retrieve property from
		 * @param b The binding of the property
		 * @param traits The traits of the object
		 */
		Atom getsuper(Atom obj, const Multiname* name) const;

		/**
		 * Write to a property of an object, with the property
		 * to modify specified by its binding.
		 * The binding was likely retrieved using getBinding.
		 * @param obj Object to modify property of
		 * @param b The binding of the property
		 * @param value The new value of the property
		 */
		void setsuper(Atom obj, const Multiname* name, Atom value) const;

		/** Implementation of OP_findproperty */		
		Atom findproperty(ScopeChain* outer, 
						  Atom* scopes,
						  int32_t extraScopes,
						  const Multiname* multiname,
						  bool strict,
						  Atom* withBase);
		
		/** Like findproperty, but ignoring all lexical and 'this' scopes.  Returns NULL if
		 *  property could not be found; caller should signal strict error or return the
		 *  target_global as appropriate.
		 */
		Atom findglobalproperty(Atom target_global, const Multiname* multiname);

		Namespace* internRtns(Atom ns);

		/** Creates the arguments array */
		ArrayObject* createArguments(Atom *atomv, int32_t argc);

		/**
		 * E4X descendants operator (..)
		 */
		Atom getdescendants(Atom obj, const Multiname* multiname);

		/**
		 * E4X filter operator
		 */
		void checkfilter(Atom obj);

		ScriptObject* coerceAtom2SO(Atom atom, Traits *expected) const;

#ifdef DEBUGGER
		void debugEnter(Traits** frameTraits, 
						CallStackNode* callstack,
						FramePtr framep, 
						volatile intptr_t *eip);

		void debugEnterInner();

		void debugExit(CallStackNode* callstack);
#endif

	private:
		Atom findWithProperty(Atom obj, const Multiname* multiname);
		
		class ActivationMethodTablePair
		{
		public:
			ActivationMethodTablePair(VTable *a, WeakKeyHashtable*wkh);
		// ------------------------ DATA SECTION BEGIN
		public:
			VTable* const activation;
			WeakKeyHashtable* const methodTable;
		// ------------------------ DATA SECTION END
		};

		// low 2 bits of activationOrMCTable 
		enum { kActivation=0, kMethodTable, kActivationMethodTablePair };
		// and the 3rd bit is a flag for "am I a ScriptEnv"
		enum { kIsScriptEnv = 4 };

		ActivationMethodTablePair* getPair() const;
		int32_t getType() const;
		void setActivationOrMCTable(void *ptr, int32_t type);

	protected:
		void setIsScriptEnv();

	public:
		bool isScriptEnv() const;

#ifdef DEBUGGER
		uint64_t invocationCount() const;
#endif

	protected:
		VTable* vtable() const;

	// ------------------------ DATA SECTION BEGIN
#if VMCFG_METHODENV_IMPL32
	public:
		MethodInfo* const method;
#else
	// inherit "method" from MethodEnvProcHolder. yeah, this is ugly,
	// but allows us to eliminate an otherwise-useless field from ImtThunkEnv.
#endif
	protected:
		// pointers are write-once so we don't need WB's
		ScopeChain* const			_scope;			
	private:
		uintptr_t					activationOrMCTable;
	public:
#ifdef VMCFG_LOOKUP_CACHE
		class LookupCache : public MMgc::GCObject
		{
		public:
			uint32_t timestamp;
			DRCWB(ScriptObject*) object;
		};
		DWB(LookupCache*) lookup_cache;
#endif
	// ------------------------ DATA SECTION END
	};

	class ScriptEnv : public MethodEnv
	{
	public:
		ScriptEnv(MethodInfo* _method, VTable* _vtable, AbcEnv* _abcEnv);
		ScriptObject* initGlobal();
	
	private:
		static ScopeChain* createScriptScope(const ScopeTypeChain* stc, VTable* _vtable, AbcEnv* _abcEnv);
		
	// ------------------------ DATA SECTION BEGIN
	public:
		DRCWB(ScriptObject*) global; // initially null, set after initialization
	// ------------------------ DATA SECTION END
	};

	class FunctionEnv : public MethodEnv
	{
	  public:
		FunctionEnv(MethodInfo* _method, ScopeChain* _scope);
	// ------------------------ DATA SECTION BEGIN
	  public:
		DRCWB(ClassClosure*) closure;
	// ------------------------ DATA SECTION END
	};

#if defined FEATURE_NANOJIT
	struct ImtThunkEntry
	{
		uintptr_t iid;
		uintptr_t disp_id; // only needs to be uint32_t, is this size for alignment purposes
	};

	class ImtThunkEnv;

	class ImtThunkEnv : public MethodEnvProcHolder
	{
	public:
		ImtThunkEnv(GprImtThunkProc p, VTable* v);
		ImtThunkEnv(GprImtThunkProc p, uint32_t c);
		GprImtThunkProc implImtGPR() const;
		ImtThunkEntry* entries() const;

	// ------------------------ DATA SECTION BEGIN
	public:
		union 
		{
			VTable* vtable;
			uint32_t imtMapCount;
		};
#if !VMCFG_METHODENV_IMPL32
		MethodInfoProcHolder methodProcHolder;
#endif
	// ------------------------ DATA SECTION END
	};
#endif // FEATURE_NANOJIT
}

#endif // __avmplus_MethodEnv__
