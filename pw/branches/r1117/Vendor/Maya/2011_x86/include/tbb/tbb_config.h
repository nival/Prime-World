/*
    Copyright 2005-2009 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

#ifndef __TBB_tbb_config_H
#define __TBB_tbb_config_H

/** This header is supposed to contain macro definitions and C style comments only.
    The macros defined here are intended to control such aspects of TBB build as 
    - compilation modes
    - feature sets
    - workarounds presence 
**/

/** Compilation modes **/

#ifndef TBB_USE_DEBUG
#ifdef TBB_DO_ASSERT
#define TBB_USE_DEBUG TBB_DO_ASSERT
#else
#define TBB_USE_DEBUG 0
#endif /* TBB_DO_ASSERT */
#else
#define TBB_DO_ASSERT TBB_USE_DEBUG
#endif /* TBB_USE_DEBUG */

#ifndef TBB_USE_ASSERT
#ifdef TBB_DO_ASSERT
#define TBB_USE_ASSERT TBB_DO_ASSERT
#else 
#define TBB_USE_ASSERT TBB_USE_DEBUG
#endif /* TBB_DO_ASSERT */
#endif /* TBB_USE_ASSERT */

#ifndef TBB_USE_THREADING_TOOLS
#ifdef TBB_DO_THREADING_TOOLS
#define TBB_USE_THREADING_TOOLS TBB_DO_THREADING_TOOLS
#else 
#define TBB_USE_THREADING_TOOLS TBB_USE_DEBUG
#endif /* TBB_DO_THREADING_TOOLS */
#endif /* TBB_USE_THREADING_TOOLS */

#ifndef TBB_USE_PERFORMANCE_WARNINGS
#ifdef TBB_PERFORMANCE_WARNINGS
#define TBB_USE_PERFORMANCE_WARNINGS TBB_PERFORMANCE_WARNINGS
#else 
#define TBB_USE_PERFORMANCE_WARNINGS TBB_USE_DEBUG
#endif /* TBB_PEFORMANCE_WARNINGS */
#endif /* TBB_USE_PERFORMANCE_WARNINGS */


/** Feature sets **/

#ifndef __TBB_EXCEPTIONS
#define __TBB_EXCEPTIONS 1
#endif /* __TBB_EXCEPTIONS */

#ifndef __TBB_SCHEDULER_OBSERVER
#define __TBB_SCHEDULER_OBSERVER 1
#endif /* __TBB_SCHEDULER_OBSERVER */

#ifndef __TBB_NEW_ITT_NOTIFY
#define __TBB_NEW_ITT_NOTIFY 1
#endif /* !__TBB_NEW_ITT_NOTIFY */


/* TODO: The following condition should be extended as soon as new compilers/runtimes 
         with std::exception_ptr support appear. */
#define __TBB_EXCEPTION_PTR_PRESENT  (_MSC_VER >= 1600 || __GXX_EXPERIMENTAL_CXX0X__ && (__GNUC__==4 && __GNUC_MINOR__>=4))


#ifndef TBB_USE_CAPTURED_EXCEPTION
    #if __TBB_EXCEPTION_PTR_PRESENT
        #define TBB_USE_CAPTURED_EXCEPTION 0
    #else
        #define TBB_USE_CAPTURED_EXCEPTION 1
    #endif
#else /* defined TBB_USE_CAPTURED_EXCEPTION */
    #if !TBB_USE_CAPTURED_EXCEPTION && !__TBB_EXCEPTION_PTR_PRESENT
        #error Current runtime does not support std::exception_ptr. Set TBB_USE_CAPTURED_EXCEPTION and make sure that your code is ready to catch tbb::captured_exception.
    #endif
#endif /* defined TBB_USE_CAPTURED_EXCEPTION */


#ifndef __TBB_DEFAULT_PARTITIONER
#if TBB_DEPRECATED
/** Default partitioner for parallel loop templates in TBB 1.0-2.1 */
#define __TBB_DEFAULT_PARTITIONER tbb::simple_partitioner
#else
/** Default partitioner for parallel loop templates in TBB 2.2 */
#define __TBB_DEFAULT_PARTITIONER tbb::auto_partitioner
#endif /* TBB_DEFAULT_PARTITIONER */
#endif /* !defined(__TBB_DEFAULT_PARTITIONER */

/** Workarounds presence **/

#if __GNUC__==4 && __GNUC_MINOR__==4 && !defined(__INTEL_COMPILER)
    #define __TBB_GCC_WARNING_SUPPRESSION_ENABLED 1
#endif

/** Macros of the form __TBB_XXX_BROKEN denote known issues that are caused by
    the bugs in compilers, standard or OS specific libraries. They should be 
    removed as soon as the corresponding bugs are fixed or the buggy OS/compiler
    versions go out of the support list. 
**/

#if defined(_MSC_VER) && _MSC_VER < 0x1500 && !defined(__INTEL_COMPILER)
    /** VS2005 and earlier does not allow to declare a template class as a friend 
        of classes defined in other namespaces. **/
    #define __TBB_TEMPLATE_FRIENDS_BROKEN 1
#endif

#if __GLIBC__==2 && __GLIBC_MINOR__==3 || __MINGW32__
    /** Some older versions of glibc crash when exception handling happens concurrently. **/
    #define __TBB_EXCEPTION_HANDLING_BROKEN 1
#endif

#if (_WIN32||_WIN64) && __INTEL_COMPILER == 1110
    /** That's a bug in Intel compiler 11.1.044/IA-32/Windows, that leads to a worker thread crash on the thread's startup. **/
    #define __TBB_ICL_11_1_CODE_GEN_BROKEN 1
#endif

#if __FreeBSD__
    /** The bug in FreeBSD 8.0 results in kernel panic when there is contention 
        on a mutex created with this attribute. **/
    #define __TBB_PRIO_INHERIT_BROKEN 1

    /** A bug in FreeBSD 8.0 results in test hanging when an exception occurs 
        during (concurrent?) object construction by means of placement new operator. **/
    #define __TBB_PLACEMENT_NEW_EXCEPTION_SAFETY_BROKEN 1
#endif /* __FreeBSD__ */

#if __LRB__
#include "tbb_config_lrb.h"
#endif

#endif /* __TBB_tbb_config_H */
