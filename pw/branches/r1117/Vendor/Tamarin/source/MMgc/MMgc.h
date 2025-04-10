/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: t; tab-width: 4 -*- */
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
 *   leon.sha@sun.com
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

#ifndef __MMgc__
#define __MMgc__

// VMPI.h includes avmfeatures.h, which detects platforms and sets up most MMGC_ names.
#include "VMPI.h"

#if defined MMGC_MEMORY_INFO && defined MMGC_64BIT
    #error "MMGC_MEMORY_INFO not supported on 64-bit (see bugzilla 468501)"
#endif

#ifdef DEBUG
    #define MMGC_DELETE_DEBUGGING
    #ifndef MMGC_64BIT				// see bugzilla 468501
        #define MMGC_MEMORY_INFO
    #endif
#endif

#if defined MMGC_MEMORY_INFO && defined MMGC_MEMORY_PROFILER
    #define MMGC_RC_HISTORY
#endif

#if defined DEBUGGER || defined MMGC_MEMORY_PROFILER || defined MMGC_MEMORY_INFO
    #ifndef MMGC_HOOKS
        #define MMGC_HOOKS
    #endif
#endif

// Policy profiler settings (for MMgc development mostly).
//
// On MacOS X desktop MMGC_POLICY_PROFILING incurs a 5% execution overhead on the
// benchmark test/performance/mmgc/gcbench.as.
//
// Enabling this and MMGC_MEMORY_INFO at the same time is probably not a good idea.
//
// If AVMSHELL_BUILD is enabled then the output can be enabled/disabled with the -gcbehavior
// switch in the shell; the output is directed to whatever channel is used by GCLog.
//
// If AVMSHELL_BUILD is disabled then the output of policy info is unconditional and is
// directed to a file gcbehavior.txt in the working directory.

#ifdef AVMSHELL_BUILD
    #define MMGC_POLICY_PROFILING
#endif

#ifdef MMGC_POLICY_PROFILING
	// Really for the specially interested!  These switches incur measurable overhead,
	// so be careful when benchmarking.

	// Profile the pointer density of scanned memory
    //#define MMGC_POINTINESS_PROFILING

	// Profile reference count traffic.  This feature adds about 8% execution time overhead
	// to the overhead already added by MMGC_POLICY_PROFILING, on the gcbench benchmark,
	// measured on MacOS X desktop.
	//#define MMGC_REFCOUNT_PROFILING

	// Profile mark stack depth
	//#define MMGC_MARKSTACK_DEPTH
#endif

#ifdef MMGC_REFCOUNT_PROFILING
	#define REFCOUNT_PROFILING_ONLY(x) x
	#define REFCOUNT_PROFILING_ARG(x) , x
#else
	#define REFCOUNT_PROFILING_ONLY(x)
	#define REFCOUNT_PROFILING_ARG(x)
#endif

#include "GCDebug.h"
#include "GCLog.h"

/*
 * If _GCHeapLock is defined, a spin lock is used for thread safety
 * on all public API's (Alloc, Free)
 *
 * Warning:
 * We may use GCHeap for allocation on other threads, hence the
 * spinlock, but the MMgc garbage collector in general is not
 * thread-safe.
 */

#ifdef MMGC_LOCKING
#define MMGC_LOCK(_x) MMgc::GCAcquireSpinlock _lock(&_x)
#include "GCSpinLock.h"
#else
#define MMGC_LOCK(_x) 
#endif

// This keeps a graph of the edges the marker finds which are printed out in Sweep
// for all objects added with GC::AddToBlacklist
//#define MMGC_HEAP_GRAPH

namespace MMgc
{
	class GC;
	class RCObject;
	class GCWeakRef;
	class GCFinalizedObject;
	class GCObject;
	class Cleaner;
	class GCAlloc;
	class GCHeap;
}

#define CAPACITY(T)  (uint32_t(GCHeap::kBlockSize) / uint32_t(sizeof(T)))

#include "GCTypes.h"
#include "AllocationMacros.h"
#include "OOM.h"
#include "GCStack.h"
#include "GCThreads.h"
#include "GCAllocObject.h"
#include "GCHashtable.h"
#include "GCMemoryProfiler.h"
#include "GCThreadLocal.h"
#include "FixedAlloc.h"
#include "FixedMalloc.h"
#include "GCGlobalNew.h"
#include "BasicList.h"
#include "GCHeap.h"
#include "GCAlloc.h"
#include "GCLargeAlloc.h"
#include "ZCT.h"
#include "HeapGraph.h"
#include "GC.h"
#include "GCObject.h"
#include "GCWeakRef.h"
#include "WriteBarrier.h"

#include "FixedAlloc-inlines.h"
#include "FixedMalloc-inlines.h"
#include "GCAlloc-inlines.h"
#include "GCLargeAlloc-inlines.h"
#include "ZCT-inlines.h"
#include "GC-inlines.h"

// remove these when the player stops using it
#define MMGC_DRC
#define WRITE_BARRIERS

#endif /* __MMgc__ */

