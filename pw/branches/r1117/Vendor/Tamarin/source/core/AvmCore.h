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

#ifndef __avmplus_AvmCore__
#define __avmplus_AvmCore__

namespace avmplus
{

#define OBJECT_TYPE		(core->traits.object_itraits)
#define CLASS_TYPE		(core->traits.class_itraits)
#define FUNCTION_TYPE	(core->traits.function_itraits)
#define ARRAY_TYPE		(core->traits.array_itraits)
#define STRING_TYPE		(core->traits.string_itraits)
#define NUMBER_TYPE		(core->traits.number_itraits)
#define INT_TYPE		(core->traits.int_itraits)
#define UINT_TYPE		(core->traits.uint_itraits)
#define BOOLEAN_TYPE	(core->traits.boolean_itraits)
#define VOID_TYPE		(core->traits.void_itraits)
#define NULL_TYPE		(core->traits.null_itraits)
#define NAMESPACE_TYPE	(core->traits.namespace_itraits)
#define VECTORINT_TYPE	(core->traits.vectorint_itraits)
#define VECTORUINT_TYPE	(core->traits.vectoruint_itraits)
#define VECTORDOUBLE_TYPE		(core->traits.vectordouble_itraits)
#define VECTOROBJ_TYPE	(core->traits.vectorobj_itraits)

const int kBufferPadding = 16;

	enum Runmode { RM_mixed, RM_jit_all, RM_interp_all };

    enum VB_Bits {
        // Output control bits for verbose mode
        VB_builtins     = 1<<0, // display output for builtins (default is to ignore any builtins)
        VB_parse        = 1<<1, // abc parsing information
        VB_verify       = 1<<2, // verification information
        VB_interp       = 1<<3, // interpreter information
        VB_jit          = 1<<4, // jit information
        VB_traits       = 1<<5, // traits creation information
    };

	struct Config
	{
		/**
		 * The verbose flag may be set to display each bytecode
		 * instruction as it is executed, along with a snapshot of
		 * the state of the stack and scope chain.
		 * @see VB_Bits for individual settings of these flags
		 */
		uint32_t verbose_vb;

		// if true, record original names of methods at runtime.
		// if false, don't (Function.toString will return things like "Function-21")
		bool methodNames;
		
		// give "Vector.<*>" instead of "Vector$object", etc
		bool oldVectorMethodNames;	

		enum Runmode runmode;

		/**
		 * To speed up initialization, we don't use jit on
		 * $init methods; we use interp instead.  For testing
		 * purposes, one may want to force the jit to be used
		 * for all code including $init methods.  The
		 * jit switch forces all code to run through the jit
		 * instead of interpreter.
		 */
		bool cseopt;

		bool sse2;
        bool fixed_esp;
		bool use_cmov;

        /**
		 * If this switch is set, executing code will check the
		 * "interrupted" flag to see whether an interrupt needs
		 * to be handled.
		 */
		bool interrupts;

		bool verifyall;

        bool show_stats;
        bool tree_opt;
		
		bool jitordie;		// Always JIT, and if the JIT fails then abort
	};

	class MethodFrame;
	
	/**
	 * The main class of the AVM+ virtual machine.  This is the
	 * main entry point to the VM for running ActionScript code.
	 */
	class AvmCore : public MMgc::GCRoot
	{
		friend class MethodFrame;
		friend class CodegenLIR;
		friend class EnterCodeContext;
		friend class EnterMethodEnv;
		friend class ExceptionFrame;

	public:
		/**
		 * Default values for the config parameters.  These need to be visible, because
		 * the shell's command line parsing needs to know what they are.  Presumably
		 * other host environments might find them useful too.
		 *
		 * These are not conditionally included because the resulting code is a mess
		 * at no benefit.
		 */
		static const uint32_t verbose_default;
		static const bool methodNames_default;
		static const bool oldVectorMethodNames_default;
		static const bool verifyall_default;
		static const bool show_stats_default;
		static const bool tree_opt_default;
		static const Runmode runmode_default;
		static const bool cseopt_default;
		static const bool sse2_default;
        static const bool fixed_esp_default;
		static const bool interrupts_default;
		static const bool jitordie_default;
		
#ifdef AVMPLUS_VERBOSE
		// default set of flags to enable for "verbose" with no specific qualifiers
		static const uint32_t DEFAULT_VERBOSE_ON;
#endif

	public:
		/**
		 * The console object.  Text to be displayed to the developer
		 * or end-user can be directed to console, much like the cout
		 * object in C++ iostreams.
		 *
		 * The console object is a wrapper around the console output
		 * stream specified by the setConsoleStream method.
		 * Programs embedding AVM+ will typically implement
		 * the OutputStream interface and pass it in via
		 * setConsoleStream.
		 */
		PrintWriter console;

#ifdef VTUNE
		iJIT_IsProfilingActiveFlags VTuneStatus;

		iJIT_IsProfilingActiveFlags CheckVTuneStatus();
#endif // VTUNE

		/**
		 * The GC used by this AVM instance
		 */
		MMgc::GC * const gc;
		
		private:
	#ifdef _DEBUG
			// Only the thread used to create the AvmCore is allowed to modify currentMethodFrame (and thus, use EnterCodeContext).
			// We don't enforce this in Release builds, but check for it and assert in Debug builds.
			vmpi_thread_t		codeContextThread;
	#endif
	

		#ifdef DEBUGGER
		private:
			Debugger*		_debugger;
			Profiler*		_profiler;
			Sampler*		_sampler;
		public:
			Debugger* debugger() const;
			Profiler* profiler() const;
			Sampler* get_sampler() const;
			void sampleCheck();
		protected:
			virtual Debugger* createDebugger(int tracelevel);
			virtual Profiler* createProfiler();
			virtual Sampler* createSampler();
		public:
			int					langID;
			bool				passAllExceptionsToDebugger;
		#endif
		
#ifdef AVMPLUS_VERIFYALL
	public:
        List<MethodInfo*, LIST_GCObjects> verifyQueue;
		void enqFunction(MethodInfo* f);
		void enqTraits(Traits* t);
		void verifyEarly(Toplevel* toplevel, AbcEnv* abc_env);
#endif

	private:
		class LivePoolNode : public MMgc::GCRoot
		{
		public:
			LivePoolNode* next;
			MMgc::GCWeakRef* pool;
			LivePoolNode(MMgc::GC* gc) : GCRoot(gc) {}
		};
		
		// note, allocated using mmfx_new, *not* gc memory 
        LivePoolNode* livePools;
	
	public:
		void addLivePool(PoolObject* pool);
	
	public:
		/**
		 * inlineable interrupt check; used by interpreter in situations
		 * where we must do more work before calling handleInterrupt, like
		 * in the body of OP_absjump.
		 */
		bool interruptCheck(bool interruptable);

		/**
		 * on a backwards branch, check if the interrupt flag is enabled.
		 * used by interpreter only.  A copy of this is inline-generated
		 * by CodegenLIR at loop headers.
		 */
		void branchCheck(MethodEnv *env, bool interruptable, int go);

	private:
		QCache*			m_tbCache;
		QCache*			m_tmCache;
		QCache*			m_msCache;
	public:
		QCache* tbCache();
		QCache* tmCache();
		QCache* msCache();
		struct CacheSizes
		{
			enum { DEFAULT_BINDINGS = 32, DEFAULT_METADATA = 1, DEFAULT_METHODS = 32 };
			
			uint16_t bindings;
			uint16_t metadata;
			uint16_t methods;
			
			inline CacheSizes() : bindings(DEFAULT_BINDINGS), metadata(DEFAULT_METADATA), methods(DEFAULT_METHODS) {}
		};
		// safe to call at any time, but calling tosses existing caches, thus has a perf hit --
		// don't call cavalierly
		void setCacheSizes(const CacheSizes& cs);

	public:
		/**
		 * Redirects the standard output of the VM to the specified
		 * output stream.  Output from print() statements and
		 * error messages will be sent here.
		 * @param stream output stream to use for console output
		 */
		void setConsoleStream(OutputStream *stream);

		/**
		 * GCCallback functions 
		 */
		virtual void presweep();
		virtual void postsweep();
		virtual void oom(MMgc::MemoryStatus status);
		
		Config config;
        
        #ifdef FEATURE_NANOJIT // accessors
            bool quiet_opt() const;
            #if defined AVMPLUS_IA32 || defined AVMPLUS_AMD64
            bool use_sse2() const;
			#endif
        #endif
		#ifdef AVMPLUS_VERBOSE
		bool isVerbose(uint32_t b) const;
        static bool isBitSet(uint32_t v, uint32_t bit);
        static uint32_t parseVerboseFlags(const char* arg);
		#endif

	    void SetJITEnabled(bool isEnabled);
        bool IsJITEnabled() const;
		bool JITMustSucceed() const;

		enum InterruptReason {
			// normal state.  must be 0 to allow efficient code for interrupt checks
			NotInterrupted = 0,

			// script is running too long
			ScriptTimeout = 1,

			// host-defined external interrupt, other than a script timeout.
			ExternalInterrupt = 2
		};

		/**
		 * Check for stack overflow and call handler if it happens.
		 * This is the canonical stack overflow check called from Interpreter. 
		 * An inlined version of this code is also generated by CodegenLIR::prologue().
		 */
		void stackCheck(MethodEnv* env);
		
		/**
		 * Like the previous method but for a Toplevel* argument.
		 */
		void stackCheck(Toplevel* env);
		
		/** set the stack limit that will be checked by executing AS3 code. */
		void setStackLimit(uintptr_t p);

		/** called by executing code when stack overflow is detected (sp < minstack) */
		static void FASTCALL handleStackOverflowMethodEnv(MethodEnv* env);

		/** called by executing code when stack overflow is detected (sp < minstack) */
		static void FASTCALL handleStackOverflowToplevel(Toplevel* env);
		
		/**
		 * Called by certain functions in PCRE to check for overflow.  The state is
		 * kept in thread-local storage and is set up by call-ins to PCRE.
		 */
		static void FASTCALL checkPCREStackOverflow();
 
		/**
		 * Set the state for call-ins to PCRE.
		 */
		static void setPCREContext(Toplevel* env);
		
	private:
		/**
		 * Stack limit set by host and checked by executing AS3 code.
		 * If the stack pointer goes below this value, handleStackOverflow is invoked,
		 * which in turn calls the host-provided virtual stackOverflow() handler.
		 */
		uintptr_t minstack;

		/**
		 * the host-provided stack limit.  we never change this, but
		 * it's used to save/restore minstack when minstack is moved
		 * to trigger interrupt handling.
		 */
		uintptr_t stack_limit;

		/**
		 * If this field is not NotInterrupted, the host has requested that the currently
		 * executing AS3 code stop and invoke handleInterrupt.  The field
		 * is checked directly by executing code.
		 * 
		 * Set to ScriptTimeout for a timeout interrupt,
		 * ExternalInterrupt for an external (i.e., signal handler) interrupt.
		 */
		InterruptReason interrupted;

		/**
		 * points to the topmost AS3 frame that's executing and provides
		 * the full AS3 callstack.  Every AS3 method prolog/epilog updates
		 * this pointer.  Exception catch handlers update this as well.
		 */
		MethodFrame*		currentMethodFrame;

		public:
		/**
		 * This method will be invoked when the first exception
		 * frame is set up.  This will be a good point to set
		 * minstack by calling setStackLimit().
		 */
		virtual void setStackBase();
		
		/** Internal table of strings for boolean type ("true", "false") */
		DRC(Stringp) booleanStrings[2];

		/** Container object for traits of built-in classes */
		BuiltinTraits traits;

		/** PoolObject for built-in classes */
		PoolObject* builtinPool;

		/** Domain for built-in classes */
		Domain* builtinDomain;
		
	private:
		/**
		 * The default namespace, "public"
		 */
		DRC(Namespacep) publicNamespace;

	public:
		/**
		 * The unnamed public namespaces
		 */
		NamespaceSet* publicNamespaces;

		#ifdef AVMPLUS_WITH_JNI
		Java* java;     /* java vm control */
		#endif

		/**
		 * Execute an ABC file that has been parsed into a
		 * PoolObject.
		 * @param pool PoolObject containing the ABC file to
		 *             execute
		 * @param domainEnv The DomainEnv object to execute
		 *                  against, or NULL if a new DomainEnv
		 *                  should be created
		 * @param toplevel the Toplevel object to execute against,
		 *                 or NULL if a Toplevel should be
		 *                 created.
		 * @param codeContext FIXME
		 * @throws Exception If an error occurs, an Exception object will
		 *         be thrown using the AVM+ exceptions mechanism.
		 *         Calls to handleActionBlock should be bracketed
		 *         in TRY/CATCH.
		 */
		Atom handleActionPool(PoolObject* pool,
								   DomainEnv* domainEnv,
								   Toplevel* &toplevel,
								   CodeContext *codeContext);

		ScriptEnv* prepareActionPool(PoolObject* pool,
									 DomainEnv* domainEnv,
									 Toplevel*& toplevel,
									 CodeContext *codeContext);
		
		void exportDefs(Traits* traits, ScriptEnv* scriptEnv);

		/**
		 * Parse the ABC block starting at offset start in code.
		 * @param code buffer holding the ABC block to parse
		 * @param start zero-indexed offset, in bytes, into the
		 *              buffer where the code begins
		 * @param toplevel the Toplevel object to execute against,
		 *                 or NULL if a Toplevel should be
		 *                 created.
		 * @param domain FIXME
		 * @param ninit FIXME
		 * @param api The api version of the code being parsed. It must
		 *            coorespond to one of the versions in api-versions.h
		 * @throws Exception If an error occurs, an Exception object will
		 *         be thrown using the AVM+ exceptions mechanism.
		 *         Calls to handleActionBlock should be bracketed
		 *         in TRY/CATCH.
		 */
		PoolObject* parseActionBlock(ScriptBuffer code,
									 int start,
									 Toplevel* toplevel,
									 Domain* domain,
									 const NativeInitializer* ninit,
									 uint32_t api);
		
		/**
		 * Execute the ABC block starting at offset start in code.
		 * @param code buffer holding the ABC block to execute
		 * @param start zero-indexed offset, in bytes, into the
		 *              buffer where the code begins
		 * @param domainEnv FIXME
		 * @param toplevel the Toplevel object to execute against,
		 *                 or NULL if a Toplevel should be
		 *                 created.
		 * @param ninit FIXME
		 * @param codeContext FIXME
		 * @param api The api version of the code being parsed. It must
		 *            coorespond to one of the versions in api-versions.h
		 * @throws Exception If an error occurs, an Exception object will
		 *         be thrown using the AVM+ exceptions mechanism.
		 *         Calls to handleActionBlock should be bracketed
		 *         in TRY/CATCH.
		 */
		Atom handleActionBlock(ScriptBuffer code,
									int start,
									DomainEnv* domainEnv,
									Toplevel* &toplevel,
									const NativeInitializer* ninit,
									CodeContext *codeContext,
									uint32_t api);

#ifdef VMCFG_EVAL
		/**
		 * Compile the source code held in 'code' and then execute it
		 * as for handleActionBlock() above.
		 *
		 * @param code The code to be compiled and executed.  The string must be
		 *             NUL-terminated and the NUL is not considered part of the
		 *             input.  If 'code' is not in UTF-16 format it will be converted
		 *             to UTF-16 format, so it is highly advisable that the caller
		 *             has created an UTF-16 string.
		 * @param filename The name of the file originating the code, or
		 *                 NULL if the source code does not originate from a file.
		 *                 If not NULL then ActionScript's 'include' directive will
		 *                 be allowed in the program and files will be loaded
		 *                 relative to 'filename'.
		 * @param domainEnv FIXME
		 * @param toplevel the Toplevel object to execute against,
		 *                 or NULL if a Toplevel should be
		 *                 created.
		 * @param ninit FIXME
		 * @param codeContext FIXME
		 * @param api The api version of the code being parsed. It must
		 *            coorespond to one of the versions in api-versions.h
		 * @throws Exception If an error occurs, an Exception object will
		 *         be thrown using the AVM+ exceptions mechanism.
		 *         Calls to handleActionBlock should be bracketed
		 *         in TRY/CATCH.
		 */
		Atom handleActionSource(String* code,
								String* filename,
								DomainEnv* domainEnv,
								Toplevel* &toplevel,
								const NativeInitializer* ninit,
								CodeContext *codeContext,
								uint32_t api);
		
		/**
		 * Obtain input from a file to handle ActionScript's 'include' directive.
		 *
		 * This method invoked by the run-time compiler if the script uses 'include'
		 * and the use of 'include' is allowed because the script originated from
		 * a file; see 'handleActionSource()' above.
		 *
		 * 'referencingFilename' should be taken into
		 * account by this method if 'filename' is not an absolute file name.
		 *
		 * @param referencingFilename The name of the file from which the script 
		 *                            containing the 'include' directive was loaded
		 * @param filename  The filename in the 'include' directive.
		 * @return  A string representing the contents of the file named by 'filename'.
		 *          The string must NUL-terminated and the NUL is not considered part
		 *          of the input.  If the returned string is not in UTF-16 format then
		 *          it will be converted to UTF-16 format, so it is highly advisable
		 *          that the method has created an UTF-16 string.  If the file cannot
		 *          be opened or read then the return value should be NULL, an
		 *          exception should not be thrown.
		 */
		virtual String* readFileForEval(String* referencingFilename, String* filename) = 0;
#endif // VMCFG_EVAL

		/** Implementation of OP_equals */
		Atom equals(Atom lhs, Atom rhs);
		
		/**
		 * this is the abstract relational comparison algorithm according to ECMA 262 11.8.5
		 * @param lhs
		 * @param rhs
		 * @return trueAtom, falseAtom, or undefinedAtom
		 */
		Atom compare(Atom lhs, Atom rhs);

		/** Implementation of OP_strictequals */
		Atom stricteq(Atom lhs, Atom rhs);

		/**
		 * Helper method; returns true if the atom is a tagged ScriptObject
		 * pointer.  The actual type of the object is indicated by
		 * ScriptObject->vtable->traits.
		 */
		static bool isObject(Atom atom);

		static bool isPointer(Atom atom);

		static bool isNamespace(Atom atom);

		static BindingKind bindingKind(Binding b);

		static bool isMethodBinding(Binding b);
		
		static bool isAccessorBinding(Binding b);

		static bool hasSetterBinding(Binding b);

		static bool hasGetterBinding(Binding b);

		static int bindingToGetterId(Binding b);

		static int bindingToSetterId(Binding b);

		static int bindingToMethodId(Binding b);

		static int bindingToSlotId(Binding b);

		/** true if b is a var or a const */
		static int isSlotBinding(Binding b);

		static Binding makeSlotBinding(uintptr_t id, BindingKind kind);

		static Binding makeMGSBinding(uintptr_t id, BindingKind kind);

		static Binding makeGetSetBinding(Binding b);

		/** true only if b is a var */
		static int isVarBinding(Binding b);

		/** true only if b is a const */
		static int isConstBinding(Binding b);

		/** Helper method; returns true if atom is an Function */
		bool isFunction(Atom atom);

		/** Helper method; returns true if atom's type is double */
		static bool isDouble(Atom atom);

		// removed, because it was being (erroneously) used to ask
        // "will you fit in int32?", which was never right for 64-bit.
        // instead, use atomIsIntptr(), which asks "will you fit in intptr?"
		// static bool isInteger(Atom atom);

		/** Helper method; returns true if atom's type is Number */
		static bool isNumber(Atom atom);

		/** Helper method; returns true if atom's type is boolean */
		static bool isBoolean(Atom atom);

		/** Helper method; returns true if atom's type is null */
		static bool isNull(Atom atom);

		/** Helper method; returns true if atom's type is undefined */
		static bool isUndefined(Atom atom);

		static bool isNullOrUndefined(Atom atom);

#ifdef AVMPLUS_VERBOSE
		/** Disassembles an opcode and places the text in str. */
		void formatOpcode(PrintWriter& out, const byte *pc, AbcOpcode opcode, ptrdiff_t off, PoolObject* pool);
# ifdef AVMPLUS_WORD_CODE
		void formatOpcode(PrintWriter& out, const uintptr_t *pc, WordOpcode opcode, ptrdiff_t off, PoolObject* pool);
		void formatBits(PrintWriter& buffer, uint32 bits);
# endif
		static void formatMultiname(PrintWriter& out, uint32 index, PoolObject* pool);
#endif

		/**
		 * @name interned constants
		 * Constants used frequently in the VM; these are typically
		 * identifiers that are part of the core language semantics
		 * like "prototype" and "constructor".  These are interned
		 * up front and held in AvmCore for easy reference.
		 */
		/*@{*/

		DRC(Stringp) kconstructor;
		DRC(Stringp) kEmptyString;
		DRC(Stringp) ktrue;
		DRC(Stringp) kfalse;
		DRC(Stringp) kundefined;
		DRC(Stringp) knull;
		DRC(Stringp) ktoString;
		DRC(Stringp) ktoLocaleString;
		DRC(Stringp) kvalueOf;
		DRC(Stringp) klength;
		DRC(Stringp) kobject;
		DRC(Stringp) kfunction;
		DRC(Stringp) kxml;
		DRC(Stringp) kboolean;
		DRC(Stringp) knumber;
		DRC(Stringp) kstring;
		DRC(Stringp) kuri;
		DRC(Stringp) kprefix;
		DRC(Stringp) kglobal;
		DRC(Stringp) kcallee;
		DRC(Stringp) kNeedsDxns;
		DRC(Stringp) kAsterisk;
		DRC(Stringp) kVersion;
#if VMCFG_METHOD_NAMES
		DRC(Stringp) kanonymousFunc;
#endif

		Atom kNaN;

		DRC(Stringp) cachedChars[128];
		/*@}*/

		/** Constructor */
		AvmCore(MMgc::GC *gc);

		/** Destructor */
		~AvmCore();

		/**
		 * Parses builtin.abc into a PoolObject, to be executed
		 * later for each new Toplevel
		 */
#ifdef DEBUGGER
		void initBuiltinPool(int tracelevel);
#else
		void initBuiltinPool();
#endif

		/**
		 * Initializes the specified Toplevel object by running
		 * builtin.abc
		 */
		Toplevel* initTopLevel();		

		virtual Toplevel* createToplevel(AbcEnv* abcEnv);
		
		/**
		 * Support for API versioning
		 */

		/**
		 * Set the AVM wide version information on startup.
		 *
		 * @param apis_start First first API version number
		 * @param apis_sizes Array of sizes of arrays of compatible APIs
		 * @param apis_count Count of API versions
		 * @param apis       Array of arrays of compatible APIs
		 * @param uris_count Count of URIs
		 * @param uris       Array of versioned URIs
		 */
		void setAPIInfo(uint32_t apis_start,
						uint32_t apis_count,  
						uint32_t uris_count, const char** uris,
						const int32_t* api_compat);


		bool isVersionedURI(Stringp uri);

		/**
		 * Get the AVM wide default API version.
		 */
		virtual int32_t getDefaultAPI() = 0;

		/**
		 * Get the current API version. Uses the given PoolObject, or otherwise
		 * walks the scope chain for the first non-builtin method info and uses
		 * it's PoolObject.
		 *
		 * @param pool The caller's pool object.
		 */
		int32_t getAPI(PoolObject* pool);

		/**
		 * Find the current public by walking the call stack
		 */
		Namespacep findPublicNamespace();

		/**
		 * Get the public namespace associated with the given pool's version.
		 *
		 * @param pool The caller's pool object.
		 */
		Namespacep getPublicNamespace(PoolObject* pool);

		/**
		 * Get any public namespace
		 */
		Namespacep getAnyPublicNamespace();

		/**
		 * Get the public namespace associated with the given pool's version.
		 *
		 * @param version The version of public being requested.
		 */
		Namespacep getPublicNamespace(int32_t api);

		/**
		 * Set the active api bit for the given api
		 */
		void setActiveAPI(int32_t api);

		/**
		 * Get the bits for the currently active apis
		 */
		int32_t getActiveAPIs();

		friend class ApiUtils;

		/**
		 * toUInt32 is the ToUInt32 algorithm from
		 * ECMA-262 section 9.6, used in many of the
		 * native core objects
		 */
		static uint32_t toUInt32(Atom atom);

		/**
		 * toInteger is the ToInteger algorithm from
		 * ECMA-262 section 9.4, used in many of the
		 * native core objects
		 */
		static double toInteger(Atom atom);

		/**
		 * Converts the passed atom to a 32-bit signed integer.
		 * If the atom is already an integer, it is simply
		 * decoded.  Otherwise, it is coerced to the int type
		 * and returned.  This is ToInt32() from E3 section 9.5
		 */
#ifdef AVMPLUS_64BIT
		static	int64_t integer64(Atom atom);
		static	int64_t integer64_i(Atom atom);
		static	int64_t integer64_d(double d);
	#ifdef AVMPLUS_AMD64
		static	int64_t integer64_d_sse2(double d);
	#endif
#endif
		static int32_t integer(Atom atom);

		// convert atom to integer when we know it is already a legal signed-32 bit int value
		static int32_t integer_i(Atom a);
		
		// convert atom to integer when we know it is already a legal unsigned-32 bit int value
		static uint32_t integer_u(Atom a);

        static int integer_d(double d);
        Atom doubleToAtom(double n);

#if defined (AVMPLUS_IA32) || defined(AVMPLUS_AMD64)
		static int integer_d_sse2(double d);
		Atom doubleToAtom_sse2(double n);
#endif

	private:
		static int doubleToInt32(double d);

	public:
		static double number_d(Atom a);

		/**
		 * intAtom is similar to the integer method, but returns
		 * an atom instead of a C++ int.
		 */
		Atom intAtom(Atom atom);

		Atom uintAtom(Atom atom);

		/**
		 * Converts the passed atom to a C++ bool.
		 * If the atom is already an E4 boolean, it is simply
		 * decoded.  Otherwise, it is coerced to the boolean type
		 * and returned.
		 * [ed] 12/28/04 use int because bool is sometimes byte-wide.
		 */
		static int boolean(Atom atom);

		/**
		 * Returns the passed atom's string representation.
		 * If the passed atom is not a string, it is coerced
		 * to type string using the ECMAScript coercion rules.
		 */
		Stringp string(Atom atom);

		Stringp coerce_s(Atom atom);

		/**
		 * Returns true if the passed atom is of string type.
		 */
		static bool isString(Atom atom);

		static bool isName(Atom atom);

		/**
		 * an interned atom is canonicalized in this way:
		 * boolean -> "true" or "false"
		 * number -> intern'ed string value
		 * string -> intern'ed string value
		 * object -> intern'ed result of toString()
		 *
		 * this way, interned atoms are suitable to be used as map keys and can
		 * be compared using ==.
		 * @param atom
		 * @return
		 */
		Stringp intern(Atom atom);

		Namespacep internNamespace(Namespacep ns);

		/** Helper function; reads a signed 24-bit integer from pc */
		static int readS24(const byte *pc);

        /**
         * Returns the size of the instruction + all it's operands.  For OP_lookupswitch the size will not include
         * the size for the case targets.
         */
		static int calculateInstructionWidth(const byte* p);

        /**
         * Read in some operands for the instruction located at *pc.  
         * Returns the size of the instruction, but will not read in all the case targets for 
         * an OP_lookupswitch, since there will be a variable number of them. 
         */
        static void readOperands(const byte* &pc, unsigned int& imm32, int& imm24, unsigned int& imm32b, int& imm8 );

		/** 
         * Helper function; reads an unsigned 32-bit integer from pc 
         * See AbcParser::readS32 for more explanation of the variable length
         * encoding scheme.  
         * 
         * 2nd argument is set to the actual size, in bytes, of the number read in,
         * and third argument is the version of the ABC 
         */
		static uint32 readU30(const byte *&p)
		{
			// @todo -- needs to be moved into AvmCore-inlines.h, 
			// but first we must determine whether it should be inline, REALLY_INLINE, etc...
			
			unsigned int result = p[0];
			if (!(result & 0x00000080))
			{
				p++;
				return result;
			}
			result = (result & 0x0000007f) | p[1]<<7;
			if (!(result & 0x00004000))
			{
				p += 2;
				return result;
			}
			result = (result & 0x00003fff) | p[2]<<14;
			if (!(result & 0x00200000))
			{
				p += 3;
				return result;
			}
			result = (result & 0x001fffff) | p[3]<<21;
			if (!(result & 0x10000000))
			{
				p += 4;
				return result;
			}
			result = (result & 0x0fffffff) | p[4]<<28;
			p += 5;
			return result;
		}

		// when you need to skip over a u30 and don't care about the result,
		// this is slightly faster.
		static void skipU30(const uint8_t*& p, int count = 1)
		{
			// @todo -- needs to be moved into AvmCore-inlines.h, 
			// but first we must determine whether it should be inline, REALLY_INLINE, etc...
			
			while (count-- > 0)
			{
				if (!(p[0] & 0x80)) { p += 1; continue; }
				if (!(p[1] & 0x80)) { p += 2; continue; }
				if (!(p[2] & 0x80)) { p += 3; continue; }
				if (!(p[3] & 0x80)) { p += 4; continue; }
				//if (!(*p[4] & 0x80)) { p += 5; continue; }	// test should be unnecessary
				AvmAssert(!(p[4] & 0x80));
				p += 5;
			}
		}

		/** Helper function; reads an unsigned 16-bit integer from pc */
		static int32_t readU16(const byte *pc);

	private:
		static const int k_atomDoesNotNeedCoerce_Masks[8];
	
	public:
		// note, return of true means we definitely DO NOT need a coerce, 
		// but return of false still means we *might* need to (ie, negating the result of this function 
		// isn't "needscoerce")
		static bool atomDoesNotNeedCoerce(Atom a, BuiltinType bt);
		

		/**
		 * this is the implementation of the actionscript "is" operator.  similar to java's
		 * instanceof.  returns true/false according to AS rules.  in particular, it will return
		 * false if value==null.
		 */
		static bool istype(Atom atom, Traits* itraits);

		/**
		 * this is the implementation of the actionscript "is" operator.  similar to java's
		 * instanceof.  returns true/false according to AS rules.  in particular, it will return
		 * false if value==null.
		 */
		static Atom istypeAtom(Atom atom, Traits* itraits);

		/**
		 * implements ECMA as operator.  Returns the same value, or null.
		 */
		static Atom astype(Atom atom, Traits* expected);

		/**
		 * implementation of OP_increg, decreg, increment, decrement which correspond to
		 * ++ and -- operators in AS.
		 */
		void increment_d(Atom *atom, int delta);

		/**
		 * implementation of OP_increg, decreg, increment, decrement which correspond to
		 * ++ and -- operators in AS.
		 */
		void increment_i(Atom *atom, int delta);
		
		/**
		 * ES3's internal ToPrimitive() function
		 */
		static Atom primitive(Atom atom);

		/** OP_toboolean; ES3 ToBoolean() */
		static Atom booleanAtom(Atom atom);

		/** OP_tonumber; ES3 ToNumber */
		Atom numberAtom(Atom atom);
		
		/**
		 * ES3's internal ToNumber() function for internal use
		 */
		static double number(Atom atom);

		/**
		 * The interrupt method is called from executing code
		 * when the interrupted flag is set.  interrupt()
		 * MUST NOT RETURN; the caller expects a thrown exception.
		 */
		virtual void interrupt(Toplevel *env, InterruptReason) = 0;
		
		/**
		 * called by the host to raise the AS3 interrupt exception.
		 * if AS3 code is executing, then soon after this call, 
		 * interrupt() will be invoked by the currently executing function.
		 */
		void raiseInterrupt(InterruptReason reason);

		// return true if there is a pending interrupt of the specific InterruptReason.
		bool interruptCheckReason(InterruptReason r) const;

		/**
		 * called by AS3 code when the interrupt is detected.  Must
		 * not return!
		 */
		static void handleInterruptMethodEnv(MethodEnv*);

		/**
		 * called by AS3 code when the interrupt is detected.  Must
		 * not return!
		 */
		static void handleInterruptToplevel(Toplevel*);
		
		/**
		 * This is called when the stack overflows
		 * (when the machine stack pointer is about to go below
		 *  minstack)
		 */
		virtual void stackOverflow(Toplevel *env) = 0;
		
		/**
		 * Throws an exception.  Constructs an Exception object
		 * and calls throwException.
		 */
		void throwAtom(Atom atom);

		/**
		 * The AVM+ equivalent of the C++ "throw" statement.
		 * Throws an exception, transferring control to the
		 * nearest CATCH block.
		 */
		void throwException(Exception *exception);

		/**
		 * throwErrorV is a convenience function for throwing
		 * an exception with a formatted error message,
		 */
		void throwErrorV(ClassClosure *type, int errorID, Stringp arg1=0, Stringp arg2=0, Stringp arg3=0);

		/**
		 * formatErrorMessageV is a convenience function for
		 * assembling an error message with varags.
		 */
		String* formatErrorMessageV( int errorID, Stringp arg1=0, Stringp arg2=0, Stringp arg3=0);

		/**
		 * Convenience methods for converting various objects into value 
		 * strings used for error message output.
		 */
		String* toErrorString(int d);
		String* toErrorString(MethodInfo* m);
		String* toErrorString(const Multiname& n);
		String* toErrorString(const Multiname* n);
		String* toErrorString(Namespacep ns);
		String* toErrorString(const Traits* t);
		String* toErrorString(const char* s);
		String* toErrorString(const wchar* s);
		String* atomToErrorString(Atom a);

		/**
		 * getErrorMessage returns the format string for an
		 * errorID.  Override to provide format strings for
		 * additional implementation-dependent error strings.
		 */
		virtual String* getErrorMessage(int errorID);

		#ifdef DEBUGGER
		/**
		 * willExceptionBeCaught walks all the way up the
		 * ActionScript stack to see if there is any "catch"
		 * statement which is going to catch the specified
		 * exception.
		 */
		bool willExceptionBeCaught(Exception* exception);

		/**
		 * findErrorMessage searches an error messages table.
		 * Only available in debugger builds.
		 */
		String* findErrorMessage(int errorID,
								 int* mapTable,
								 const char** errorTable,
								 int numErrors);

		/**
		 * Determines the language id of the given platform
		 */
		virtual int determineLanguage();
		

		/**
		 * Creates a StackTrace from the current executing call stack
		 */
		StackTrace* newStackTrace();

		#ifdef _DEBUG
		void dumpStackTrace();
		#endif

		/** The call stack of currently executing code. */
		CallStackNode *callStack;

#endif /* DEBUGGER */

		CodeContext* codeContext() const;
		Namespace* dxns() const;

		/**
		 * implements OP_dxns.  internedUri is expected to be from a constant
		 * pool and therefore already interned.  Creates a namespace and
		 * saves it as the given method frame's default xml namespace.
		 */
		void setDxns(MethodFrame*, String* internedUri);

		/**
		 * implements OP_dxnslate.  uri is any value, which we must convert
		 * to an interned-string, then create an namespace from it,
		 * then save the value in the current method frame as the current
		 * default xml namespace.
		 */
		void setDxnsLate(MethodFrame*, Atom uri);

		/** env of the highest catch handler on the call stack, or NULL */
		ExceptionFrame *exceptionFrame;
		
		Exception *exceptionAddr;

		/**
		 * Searches the exception handler table of info for
		 * a try/catch block that contains the instruction at pc
		 * and matches the type of exception.
		 * @param info      the method to search the exception handler
		 *                  table of
		 * @param pc        the program counter at the point where
		 *                  the exception occurred; either a pointer into
		 *                  bytecode or into native compiled code
		 * @param exception the exception object that was thrown;
		 *                  used to match the type.
		 * @return ExceptionHandler object for the exception
		 *         handler that matches, or re-throws the passed-in
		 *         exception if no handler is found.
		 */
		ExceptionHandler* findExceptionHandler(MethodInfo *info,
											   sintptr pc,
											   Exception *exception);
		
		ExceptionHandler* beginCatch(ExceptionFrame *ef,
				MethodInfo *info, sintptr pc, Exception *exception);

		/**
		 * Just like findExceptionHandler(), except that this function
		 * returns NULL if it can't find an exception handler, whereas
		 * findExceptionHandler() re-throws the passed-in exception if
		 * it can't find a handler.
		 */
		ExceptionHandler* findExceptionHandlerNoRethrow(MethodInfo *info,
														sintptr pc,
														Exception *exception);

		/**
		 * Returns true if the passed atom is an XML object,
		 * as defined in the E4X Specification.
		 */				
		static bool isXML(Atom atm);

		/**
		 * Returns true if the passed atom is a XMLList object,
		 * as defined in the E4X Specification.
		 */		
		static bool isXMLList(Atom atm);

		static bool isXMLorXMLList(Atom atm);

		/* Returns tru if the atom is a Date object */
		static bool isDate(Atom atm);

		// From http://www.w3.org/TR/2004/REC-xml-20040204/#NT-Name
		static bool isLetter(wchar c);
		static bool isDigit(wchar c);
		static bool isCombiningChar(wchar c);
		static bool isExtender(wchar c);

		Stringp ToXMLString (Atom a);
		Stringp EscapeElementValue (const Stringp s, bool removeLeadingTrailingWhitespace);
		Stringp EscapeAttributeValue (Atom v);

		/**
		 * Converts an Atom to a E4XNode if its traits match.
		 * Otherwise, null is returned. (An exception is NOT thrown)
		 */
		static E4XNode* atomToXML(Atom atm);

		/**
		 * Converts an Atom to a XMLObject if its traits match.
		 * Otherwise, null is returned. (An exception is NOT thrown)
		 */
		static XMLObject* atomToXMLObject(Atom atm);

		/**
		 * Converts an Atom to a XMLListObject if its traits match.
		 * Otherwise, null is returned. (An exception is NOT thrown)
		 */
		static XMLListObject* atomToXMLList(Atom atm);

		/**
		 * Returns true if the passed atom is a QName object,
		 * as defined in the E4X Specification.
		 */		
		static bool isQName(Atom atm);

		/**
		 * Returns true if the passed atom is a Dictionary object,
		 * as defined in the E4X Specification.
		 */		
		static bool isDictionary(Atom atm);

		static bool isDictionaryLookup(Atom key, Atom obj);

		/**
		 * Returns true if the passed atom is a valid XML name,
		 * as defined in the E4X Specification.
		 */		
		bool isXMLName(Atom arg);

		/**
		 * Converts an Atom to a QNameObject if its traits match.
		 * Otherwise, null is returned. (An exception is NOT thrown)
		 */
		static QNameObject* atomToQName(Atom atm);

		/** Implementation of OP_typeof */		
		Stringp _typeof (Atom arg);

		/** The XML entities table, used by E4X */
		HeapHashtable* xmlEntities;
		
	private:
		static bool isBuiltinType(Atom atm, BuiltinType bt);
		static bool isBuiltinTypeMask(Atom atm, int btmask);

	private:
		//
		// this used to be Heap
		//

		/** size of interned String table */
		int stringCount;

		/** number of deleted entries in our String table */
		int deletedCount;
		#define AVMPLUS_STRING_DELETED ((Stringp)(1))

		/** size of interned Namespace table */
		int nsCount;

		int numStrings;
		int numNamespaces;
		
	public:

		static Namespacep atomToNamespace(Atom atom);
		
		static double atomToDouble(Atom atom);

		/**
		 * Convert an Atom of kStringType to a Stringp
		 * @param atom atom to convert.  Note that the Atom
		 *             must be of kStringType
		 */
		static Stringp atomToString(Atom atom);

		// Avoid adding validation checks here and returning NULL.  If this
		// is returning a bad value, the higher level function should be fixed
		// or AbcParser/Verifier should be enhanced to catch this case.
		static ScriptObject* atomToScriptObject(const Atom atom);
	
		// Helper function, allows generic objects to work with InlineHashtable
		// and AtomArray, uses double type which is the only non-RC pointer tag.
		// The key here is that these methods round-trip any pointer value to the
		// same pointer value, there is no casting that might adjust the pointer.
		static Atom genericObjectToAtom(const void* obj);
		static const void* atomToGenericObject(Atom a);
		static bool isGenericObject(Atom a);

	private:
		/** search the string intern table */
		int findStringLatin1(const char* s, int len);
		int findStringUTF16(const wchar* s, int len);
		int findString(Stringp s);

		/** search the namespace intern table */
		int findNamespace(Namespacep ns, bool canRehash = true);
		Namespacep gotNamespace(Stringp uri, int32_t api);

	public:

		// String creation. If len is omitted, zero-termination is assumed.
		Stringp newStringLatin1(const char* str, int len = -1);
		Stringp newStringUTF8(const char* str, int len = -1, bool strict = false);
		Stringp newStringUTF16(const wchar* str, int len = -1);

		// decodes UTF16LE or UTF16BE.
		Stringp newStringEndianUTF16(bool littleEndian, const wchar* str, int len = -1);
		
		// like newStringLatin1, but the string constant is assumed to remain valid
		// for the life of the AvmCore. Generally, should only be used for literal
		// strings, eg newConstantStringLatin1("foo")
		Stringp newConstantStringLatin1(const char* str);


		// variants on the newStringXXX() calls that also intern the string.
		Stringp internStringLatin1(const char* s, int len = -1);
		Stringp internStringUTF8(const char* s, int len = -1, bool constant = false);
		Stringp internStringUTF16(const wchar* s, int len = -1);

		// like internStringLatin1, but the string constant is assumed to remain valid
		// for the life of the AvmCore. Generally, should only be used for literal
		// strings, eg internStringLatin1("foo")
		Stringp internConstantStringLatin1(const char* s);

		/**
		 * intern the given string atom which has already been allocated
		 * @param atom
		 * @return
		 */
		Stringp internString(Stringp s);
		Stringp internString(Atom atom);
		Stringp internInt(int n);
		Stringp internDouble(double d);
		Stringp internUint32(uint32 ui);


#ifdef DEBUGGER
		/**
		 * intern without allocating memory, returns NULL if its not already interned
		 */
		Stringp findInternedString(const char *s, int len);
#endif

		static bool getIndexFromAtom(Atom a, uint32 *result);
		static bool getIndexFromString(Stringp s, uint32 *result);
			
		ScriptBufferImpl* newScriptBuffer(size_t size);
		VTable* newVTable(Traits* traits, VTable* base, Toplevel* toplevel);

		RegExpObject* newRegExp(RegExpClass* regExpClass,
								Stringp pattern,
								Stringp options);

		ScriptObject* newObject(VTable* ivtable, ScriptObject *delegate);

		FrameState* newFrameState(int frameSize, int scopeBase, int stackBase);
		Namespacep newNamespace(Atom prefix, Atom uri, Namespace::NamespaceType type = Namespace::NS_Public);
		Namespacep newNamespace(Atom uri, Namespace::NamespaceType type = Namespace::NS_Public);
		Namespacep newNamespace(Stringp uri, Namespace::NamespaceType type = Namespace::NS_Public, int32_t api = 0);
		Namespacep newPublicNamespace(Stringp uri);

		Stringp uintToString(uint32 i);
		Stringp intToString(int i);
		Stringp doubleToString(double d);
		Stringp concatStrings(Stringp s1, Stringp s2);
		
		Atom uintToAtom(uint32_t n);
		Atom intToAtom(int32_t n);

		Atom allocDouble(double n);
		
		void rehashStrings(int newlen);
		void rehashNamespaces(int newlen);

		// static version for smart pointers
		static void atomWriteBarrier(MMgc::GC *gc, const void *container, Atom *address, Atom atomNew);
		static void atomWriteBarrier_ctor(MMgc::GC *gc, const void *container, Atom *address, Atom atomNew);
		static void atomWriteBarrier_dtor(Atom *address);

		static void decrementAtomRegion(Atom *ar, int length);

	public:
#ifdef AVMPLUS_VERBOSE
		Stringp format(Atom atom);
#endif
#if VMCFG_METHOD_NAMES
		Stringp formatAtomPtr(Atom atom);
#endif

	private:
		// hash set containing intern'ed strings
		DRC(Stringp) * strings;
		// hash set containing namespaces
		DRC(Namespacep) * namespaces;

		// API versioning state
		uint32_t		  apis_start;  // first api number
		uint32_t		  apis_count;  // count of apis
		uint32_t		  uris_count;  // count of uris
		const char**	  uris;		   // array of uris
		const int32_t*	  api_compat;  // array of compatible api bit masks
		int32_t			  largest_api;
		int32_t			  active_api_flags;

#ifdef VMCFG_LOOKUP_CACHE
	private:
		// Saturating counter.  
		uint32_t lookup_cache_timestamp;
	public:
		uint32_t lookupCacheTimestamp() const;
		bool lookupCacheIsValid(uint32_t t) const;
		void invalidateLookupCache();
#endif

#ifdef VMCFG_NANOJIT
    private:
        // when set, we flush all binding caches at the end of the next gc sweep.
        bool m_flushBindingCachesNextSweep;
    public:
        void flushBindingCachesNextSweep();
#endif

	private:
		friend class Traits;
		Traits** _emptySupertypeList; // empty supertype list shared by many Traits
		
	public:
		// avoid multiple inheritance issues
		class GCInterface : MMgc::GCCallback
		{
		public:
			GCInterface(MMgc::GC * _gc) : MMgc::GCCallback(_gc), core(NULL) {}
			void SetCore(AvmCore* _core) { this->core = _core; }
			void presweep() { if(core) core->presweep(); }
			void postsweep() { if(core) core->postsweep(); }
			void log(const char *str) { if(core) core->console << str; }
			void oom(MMgc::MemoryStatus status) { if(core) core->oom(status); }
		private:
			AvmCore *core;
		};
		GCInterface gcInterface;
	};

	/*
		MethodFrame is a way of maintaining CodeContext and DXNS in a uniform way
		in both Interpreter and JIT modes. CodeContext is a poorly-documented
		structure that is exercised very little in current acceptance tests, but is
		used extensively for Flash and AIR. The theory of operation:
		-- Normally, the "active" CodeContext is that of the most-recently-called
			non-builtin MethodEnv on the call stack.
		-- native C++ code can override the current CodeContext by using EnterCodeContext(),
			which just pushes another MethodFrame onto the stack...
			it overrides the current CodeContext, but subsequent nested calls to non-builtin
			methods will in turn override this.
		-- The implementation is a bit convoluted, in the name of saving stack space.
			A single field can contain either a MethodEnv* (for a normal MethodFrame)
			or a CodeContext* (for one pushed by EnterCodeContext). This means that the top-of-stack
			may not have the current MethodEnv* handy, so walking down the stack is necessary
			to find it.
		-- Note that MethodFrame doesn't contain a pointer to AvmCore*; this is by design 
			(as a stack-saving measure), as CodegenLIR doesn't need to save it (it can emit the proper constant value), 
			and	all other callers have ready access to one.
	*/
	class MethodFrame
	{
	public:
		// deliberately no ctor or dtor here.
		
		// NOTE, the code in enter/exit is replicated in CodegenLIR.cpp;
		// if you make changes here, you may need to make changes there as well.
		void enter(AvmCore* core, MethodEnv* e);
		void enter(AvmCore* core, CodeContext* cc);
		void exit(AvmCore* core);
		CodeContext* cc() const;
		MethodEnv* env() const;

		// Search for a frame that has a default namespace, starting on the given frame.
		static Namespace* findDxns(const MethodFrame* start);

		void setDxns(Namespace* ns);

	public:
		MethodFrame*	next;

	private:
		friend class CodegenLIR;
		enum {
			IS_EXPLICIT_CODECONTEXT = 0x1,
			DXNS_NOT_NULL = 0x2,
			FLAGS_MASK = 0x3
		};
		uintptr_t		envOrCodeContext;
		Namespace*		dxns; // NOTE: this struct is always stack-allocated (or via VMPI_alloca, which is just as good), so no DRC needed
	};


	/**
	 * ApiUtils provides some helper methods to friends of
	 * api versioning
	 */
	  
	class ApiUtils 
	{
		friend class AvmCore;
		friend class AbcParser;
		friend class Namespace;
		friend class NativeInitializer;
		friend class Traits;
		friend class QNameObject;
		friend class TypeDescriber;
		friend class BuiltinTraits;

		/**
		 * Return true if type is Namespace::NS_Pubilc and uri is one of the versioned
		 * namespaces in the list provided by the host
		 */
		static bool isVersionedNS(AvmCore* core, Namespace::NamespaceType type, Stringp uri);

		/**
		 * Return an interned namespace that corresponds to the given a namespace 
		 * and api bitmask
		 */
		static Namespacep getVersionedNamespace(AvmCore* core, Namespacep ns, API api);

		/**
		 * Map an api bitmask to its cooresponding version number
		 */
		static uint32_t toVersion(AvmCore* core, API api);

		/**
		 * Strip the given uri of its version marker, if it has one
		 */
		static Stringp getBaseURI(AvmCore* core, Stringp uri);

		/**
		 * Return the API bitmask for the given uri, or zero if there is none
		 */
		static API getURIAPI(AvmCore* core, Stringp uri);

		/**
		 * Return true if the given uri has a version marker
		 */
		static bool hasVersionMark(Stringp uri);

		/**
		 * Return the API bitmask of all APIs compatible with the given API
		 */
		static API getCompatibleAPIs(AvmCore* core, API api);

		/**
		 * Return the API bitmask for the smallest api
		 */
		static API getSmallestAPI();

		/**
		 * Return the API bitmask for the largest api
		 */
		static API getLargestAPI(AvmCore* core);

		enum { 
			MIN_API_MARK = 0xE000,
			MAX_API_MARK = 0xF8FF
		};

	public:

		/**
		 * Convert a version number to an api bitmask
		 */
		static API toAPI(AvmCore* core, uint32_t v);
	};
}

#endif /* __avmplus_AvmCore__ */
