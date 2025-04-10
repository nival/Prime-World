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

#ifndef __avmbuild__
#define __avmbuild__

// Note, the goal is to keep this file small and for it to concern itself mostly
// with debugging settings useful for VM development and other ad-hocery.  In
// general all externally visible configuration should be handled by the configuration
// system in core/avmfeatures.as.
//
// For sanity's sake, please note the reason for the presence of each clause in the
// following.

// This is here as a sanity check, nuke after a few more release cycles (now == Apr-2009).
#ifdef AVMPLUS_DISABLE_NJ
    #error "AVMPLUS_DISABLE_NJ is no longer supported"
#endif

// This is here because the configuration system does not deal with DEBUG
#if defined DEBUG && !defined AVMPLUS_VERBOSE && !defined VMCFG_SYMBIAN
    #define AVMPLUS_VERBOSE
#endif

// This is here because the conditional for MacTel can't be expressed by the
// feature system (yet).
// FIXME: extend the feature system to handle this.
//
// all x64, and all MacTel machines, always have sse2
#if defined(AVMPLUS_AMD64) || (defined(AVMPLUS_MAC) && defined(AVMPLUS_IA32))
    #ifndef AVMPLUS_SSE2_ALWAYS
	    #define AVMPLUS_SSE2_ALWAYS
    #endif
#endif

// This is here because it's for VM debugging.
#ifdef FEATURE_NANOJIT
// Enable the jitmax global variables and -jitmax switch to the shell, for bisecting nanojit bugs
//#define AVMPLUS_JITMAX
#endif

// This is here because it's not yet been refactored.
// FIXME: refactor this.
#ifndef VMCFG_METHOD_NAMES
	#if defined AVMPLUS_VERBOSE || defined DEBUGGER
		#define VMCFG_METHOD_NAMES 1
	#else
		#define VMCFG_METHOD_NAMES 0
	#endif
#endif

// This is here because the conditional can't be expressed by the feature system (yet),
// and because support for this case (word code + jit) is likely to be removed anyway.
//
// For word code + jit, define a verifier output module that can drive two code generators.
#if defined AVMPLUS_WORD_CODE && defined FEATURE_NANOJIT
    #define FEATURE_TEEWRITER
#endif

// This is here because it's an always-enabled switch to externally sourced code:
// PCRE should always be compiled as a statically linked library, never as a shared
// library.  See pcre/pcre_internal.h, pcre/pcre.h, and pcre/config.h.
#define PCRE_STATIC

// The PERFM macros are here because they are for VM debugging.
//
// Enable performance metrics for NJ
//
// *** NOTE ON THREAD SAFETY ***
// PERFM is not supported in configurations where more than one AvmCore is
// instantiated in the same process, as the monitoring code is not thread
// safe and the results will be unpredictable.

//#define PERFM

#ifdef PERFM
# define PERFM_NVPROF(n,v) _nvprof(n,v)
# define PERFM_NTPROF(n) _ntprof(n)
# define PERFM_TPROF_END() _tprof_end()
#else
# define PERFM_NVPROF(n,v)
# define PERFM_NTPROF(n)
# define PERFM_TPROF_END() 
#endif

// This is here for VM performance profiling.
//
// The use of the SUPERWORD_PROFILING switch is described in comments at the head of
// utils/superwordprof.c
//
// The limit is optional and describes a cutoff for sampling; the program continues to
// run after sampling ends but data are no longer gathered or stored.  A limit of 250e6
// produces 1GB of sample data.  There is one sample per VM instruction executed.
//
// *** NOTE ON THREAD SAFETY ***
// SUPERWORD_PROFILING is not supported in configurations where more than one
// AvmCore is instantiated in the same process, as the monitoring code is not
// thread safe and the results will be unpredictable.

//#define SUPERWORD_PROFILING
//#define SUPERWORD_LIMIT 250000000

#ifdef SUPERWORD_PROFILING
#  ifndef VMCFG_WORDCODE
#    error "You must have word code enabled to perform superword profiling"
#  endif
#  ifdef VMCFG_WORDCODE_THREADED
#    error "You must disable direct threading to perform superword profiling"
#  endif
#endif

// This is here for VM development.
//
// define this to 1 to keep a shadow copy of implGPR in MethodEnv (vs MethodInfo only).
// more speed, but more memory used... not clear if the tradeoff is worthwhile yet.
#ifndef VMCFG_METHODENV_IMPL32
#  define VMCFG_METHODENV_IMPL32 1
#endif

// This is here for VM development.
//
// Enable support for printing the control flow graph in the JIT.
//#define FEATURE_CFGWRITER

// This is here for documentation purposes.
//
// This must be enabled (probably not in this file) if nanojit is being used outside AVM,
// eg, in TraceMonkey.
//#define VMCFG_NANOJIT_STANDALONE

// This is here because it's slated to be deleted, but can't be deleted yet (now == Apr-2009).
//
// AVMPLUS_PORTING_API is completely unsupported and it /will/ be removed here and elsewhere
// in the code.  Embedding software /must/ instead use the common configuration system, see
// core/avmfeatures.as and core/avmfeatures.h.
#if defined(AVMPLUS_PORTING_API)
	// The portapi_avmbuild.h file is used to override
	// definitions in this file. E.g. turning off
	// features, etc.
	//#include "portapi_avmbuild.h"
    #error "Obsolete define"
#endif

#endif /* __avmbuild__ */
