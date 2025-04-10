#pragma once
#include "system-selection.h"

#ifndef AVMFEATURE_DEBUGGER
  #ifdef DEBUGGER
    #define AVMFEATURE_DEBUGGER        1
  #else
    #define AVMFEATURE_DEBUGGER        0
  #endif
#endif

#ifndef AVMFEATURE_ALLOCATION_SAMPLER
  // This is compatible with existing behavior: debugging support enables 
  // sampling support.
  #if AVMFEATURE_DEBUGGER
    #define AVMFEATURE_ALLOCATION_SAMPLER 1
  #else
    #define AVMFEATURE_ALLOCATION_SAMPLER 0
  #endif
#endif

#ifndef AVMFEATURE_VTUNE
  #define AVMFEATURE_VTUNE             0
#endif

#ifndef AVMFEATURE_JIT
  #define AVMFEATURE_JIT               1
#endif

#ifndef AVMFEATURE_AOT
  #define AVMFEATURE_AOT               0
#endif

#ifndef AVMFEATURE_ABC_INTERP
  #define AVMFEATURE_ABC_INTERP        1
#endif

#ifndef AVMFEATURE_WORDCODE_INTERP
  #define AVMFEATURE_WORDCODE_INTERP   0
#endif

#if AVMFEATURE_WORDCODE_INTERP
  #ifndef AVMFEATURE_THREADED_INTERP
    #ifdef __GNUC__
      #define AVMFEATURE_THREADED_INTERP 1
    #else
      #define AVMFEATURE_THREADED_INTERP 0
    #endif
  #endif
#else
  #define AVMFEATURE_THREADED_INTERP   0
#endif

#ifndef AVMFEATURE_SELFTEST
  #define AVMFEATURE_SELFTEST          0
#endif

#ifndef AVMFEATURE_EVAL
  #define AVMFEATURE_EVAL              0
#endif

#ifndef AVMFEATURE_PROTECT_JITMEM
  #define AVMFEATURE_PROTECT_JITMEM    1
#endif

#ifndef AVMFEATURE_SHARED_GCHEAP
  #define AVMFEATURE_SHARED_GCHEAP     1
#endif

#ifndef AVMFEATURE_USE_SYSTEM_MALLOC
  #define AVMFEATURE_USE_SYSTEM_MALLOC 0
#endif

#ifndef AVMFEATURE_CPP_EXCEPTIONS
  #define AVMFEATURE_CPP_EXCEPTIONS    0
#endif

#ifndef AVMFEATURE_INTERIOR_POINTERS
  #define AVMFEATURE_INTERIOR_POINTERS 0
#endif

#ifndef AVMFEATURE_JNI
  #define AVMFEATURE_JNI               0
#endif

#ifndef AVMFEATURE_HEAP_ALLOCA
  #define AVMFEATURE_HEAP_ALLOCA       0
#endif

#ifndef AVMFEATURE_STATIC_FUNCTION_PTRS
  #define AVMFEATURE_STATIC_FUNCTION_PTRS 1
#endif

#ifndef AVMFEATURE_INDIRECT_NATIVE_THUNKS
  #define AVMFEATURE_INDIRECT_NATIVE_THUNKS 1
#endif

#if !defined(_DEBUG) && !defined(DEBUG)
	// by default, nanojit enables NJ_VERBOSE mode when AVMPLUS_VERBOSE is on,
	// which is enabled for Debug *and* Debugger builds. 
	#define NJ_VERBOSE_DISABLED 1
	#define NJ_PROFILE_DISABLED 1
#endif

#ifndef AVMFEATURE_OVERRIDE_GLOBAL_NEW
  #define AVMFEATURE_OVERRIDE_GLOBAL_NEW 0
#endif

#ifndef AVMFEATURE_MEMORY_PROFILER
#if AVMFEATURE_DEBUGGER
	#if AVMSYSTEM_MAC && !(AVMSYSTEM_PPC && AVMSYSTEM_64BIT)
		#define AVMFEATURE_MEMORY_PROFILER 1
	#elif AVMSYSTEM_WIN32 && !AVMSYSTEM_ARM // note, does not require DEBUG
		#define AVMFEATURE_MEMORY_PROFILER 1
	#else
		#define AVMFEATURE_MEMORY_PROFILER 0
	#endif
#else
	#define AVMFEATURE_MEMORY_PROFILER 0
#endif
#endif

#ifndef AVMFEATURE_API_VERSIONING
    #define AVMFEATURE_API_VERSIONING 0
#endif

#ifndef AVMFEATURE_CACHE_GQCN
  #define AVMFEATURE_CACHE_GQCN 1
#endif


