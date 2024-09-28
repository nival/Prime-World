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

#ifndef __TBB_tbb_stddef_H
#define __TBB_tbb_stddef_H

// Marketing-driven product version
#define TBB_VERSION_MAJOR 2
#define TBB_VERSION_MINOR 1

// Engineering-focused interface version
#define TBB_INTERFACE_VERSION 3015
#define TBB_INTERFACE_VERSION_MAJOR TBB_INTERFACE_VERSION/1000

// The oldest major interface version still supported
// To be used in SONAME, manifests, etc.
#define TBB_COMPATIBLE_INTERFACE_VERSION 2

#define __TBB_STRING_AUX(x) #x
#define __TBB_STRING(x) __TBB_STRING_AUX(x)

// We do not need defines below for resource processing on windows
#if !defined RC_INVOKED

// Define groups for Doxygen documentation
/**
 * @defgroup algorithms         Algorithms
 * @defgroup containers         Containers
 * @defgroup memory_allocation  Memory Allocation
 * @defgroup synchronization    Synchronization
 * @defgroup timing             Timing
 * @defgroup task_scheduling    Task Scheduling
 */

// Simple text that is displayed on the main page of Doxygen documentation.
/**
 * \mainpage Main Page
 *
 * Click the tabs above for information about the
 * - <a href="./modules.html">Modules</a> (groups of functionality) implemented by the library 
 * - <a href="./annotated.html">Classes</a> provided by the library
 * - <a href="./files.html">Files</a> constituting the library.
 * .
 * Please note that significant part of TBB functionality is implemented in the form of
 * template functions, descriptions of which are not accessible on the <a href="./annotated.html">Classes</a>
 * tab. Use <a href="./modules.html">Modules</a> or <a href="./namespacemembers.html">Namespace/Namespace Members</a>
 * tabs to find them.
 *
 * Additional pieces of information can be found here
 * - \subpage concepts
 * .
 */

/** \page concepts TBB concepts
    
    A concept is a set of requirements to a type, which are necessary and sufficient
    for the type to model a particular behavior or a set of behaviors. Some concepts 
    are specific to a particular algorithm (e.g. algorithm body), while other ones 
    are common to several algorithms (e.g. range concept). 

    All TBB algorithms make use of different classes implementing various concepts.
    Implementation classes are supplied by the user as type arguments of template 
    parameters and/or as objects passed as function call arguments. The library 
    provides predefined  implementations of some concepts (e.g. several kinds of 
    \ref range_req "ranges"), while other ones must always be implemented by the user. 
    
    TBB defines a set of minimal requirements each concept must conform to. Here is 
    the list of different concepts hyperlinked to the corresponding requirements specifications:
    - \subpage range_req
    - \subpage parallel_do_body_req
    - \subpage parallel_for_body_req
    - \subpage parallel_reduce_body_req
    - \subpage parallel_scan_body_req
    - \subpage parallel_sort_iter_req
**/

// Define preprocessor symbols used to determine architecture
#if _WIN32||_WIN64
#   if defined(_M_AMD64)
#       define __TBB_x86_64 1
#   elif defined(_M_IA64)
#       define __TBB_ipf 1
#   elif defined(_M_IX86)
#       define __TBB_x86_32 1
#   endif
#else /* Assume generic Unix */
#   if !__linux__ && !__APPLE__
#       define __TBB_generic_os 1
#   endif
#   if __x86_64__
#       define __TBB_x86_64 1
#   elif __ia64__
#       define __TBB_ipf 1
#   elif __i386__||__i386  // __i386 is for Sun OS
#       define __TBB_x86_32 1
#   else
#       define __TBB_generic_arch 1
#   endif
#endif

#if _WIN32||_WIN64
// define the parts of stdint.h that are needed, but put them inside tbb::internal
namespace tbb {
namespace internal {
    typedef __int8 int8_t;
    typedef __int16 int16_t;
    typedef __int32 int32_t;
    typedef __int64 int64_t;
    typedef unsigned __int8 uint8_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int64 uint64_t;
} // namespace internal
} // namespace tbb
#else
#include <stdint.h>
#endif

#if _MSC_VER >=1400
#define __TBB_EXPORTED_FUNC   __cdecl
#define __TBB_EXPORTED_METHOD __thiscall
#else
#define __TBB_EXPORTED_FUNC
#define __TBB_EXPORTED_METHOD
#endif

#include <cstddef>      /* Need size_t and ptrdiff_t (the latter on Windows only) from here. */

#if _WIN32||_WIN64
#define __TBB_tbb_windef_H
#include "_tbb_windef.h"
#undef __TBB_tbb_windef_H
#endif /* _WIN32||_WIN64 */

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

namespace tbb {
    //! Type for an assertion handler
    typedef void(*assertion_handler_type)( const char* filename, int line, const char* expression, const char * comment );
}

#if TBB_USE_ASSERT

//! Assert that x is true.
/** If x is false, print assertion failure message.  
    If the comment argument is not NULL, it is printed as part of the failure message.  
    The comment argument has no other effect. */
#define __TBB_ASSERT(predicate,message) ((predicate)?((void)0):tbb::assertion_failure(__FILE__,__LINE__,#predicate,message))
#define __TBB_ASSERT_EX __TBB_ASSERT

namespace tbb {
    //! Set assertion handler and return previous value of it.
    assertion_handler_type __TBB_EXPORTED_FUNC set_assertion_handler( assertion_handler_type new_handler );

    //! Process an assertion failure.
    /** Normally called from __TBB_ASSERT macro.
        If assertion handler is null, print message for assertion failure and abort.
        Otherwise call the assertion handler. */
    void __TBB_EXPORTED_FUNC assertion_failure( const char* filename, int line, const char* expression, const char* comment );
} // namespace tbb

#else

//! No-op version of __TBB_ASSERT.
#define __TBB_ASSERT(predicate,comment) ((void)0)
//! "Extended" version is useful to suppress warnings if a variable is only used with an assert
#define __TBB_ASSERT_EX(predicate,comment) ((void)(1 && (predicate)))

#endif /* TBB_USE_ASSERT */

//! The namespace tbb contains all components of the library.
namespace tbb {

//! The function returns the interface version of the TBB shared library being used.
/**
 * The version it returns is determined at runtime, not at compile/link time.
 * So it can be different than the value of TBB_INTERFACE_VERSION obtained at compile time.
 */
extern "C" int __TBB_EXPORTED_FUNC TBB_runtime_interface_version();

//! Dummy type that distinguishes splitting constructor from copy constructor.
/**
 * See description of parallel_for and parallel_reduce for example usages.
 * @ingroup algorithms
 */
class split {
};

/**
 * @cond INTERNAL
 * @brief Identifiers declared inside namespace internal should never be used directly by client code.
 */
namespace internal {

using std::size_t;

//! An unsigned integral type big enough to hold a pointer.
/** There's no guarantee by the C++ standard that a size_t is really big enough,
    but it happens to be for all platforms of interest. */
typedef size_t uintptr;

//! A signed integral type big enough to hold a pointer.
/** There's no guarantee by the C++ standard that a ptrdiff_t is really big enough,
    but it happens to be for all platforms of interest. */
typedef std::ptrdiff_t intptr;

//! Report a runtime warning.
void __TBB_EXPORTED_FUNC runtime_warning( const char* format, ... );

#if TBB_USE_ASSERT
//! Set p to invalid pointer value.
template<typename T>
inline void poison_pointer( T* & p ) {
    p = reinterpret_cast<T*>(-1);
}
#else
template<typename T>
inline void poison_pointer( T* ) {/*do nothing*/}
#endif /* TBB_USE_ASSERT */

//! Base class for types that should not be assigned.
class no_assign {
    // Deny assignment
    void operator=( const no_assign& );
public:
#if __GNUC__
    //! Explicitly define default construction, because otherwise gcc issues gratuitous warning.
    no_assign() {}
#endif /* __GNUC__ */
};

//! Base class for types that should not be copied or assigned.
class no_copy: no_assign {
    //! Deny copy construction
    no_copy( const no_copy& );
public:
    //! Allow default construction
    no_copy() {}
};

// Struct to be used as a version tag for inline functions.
/** Version tag can be necessary to prevent loader on Linux from using the wrong 
    symbol in debug builds (when inline functions are compiled as out-of-line). **/
struct version_tag_v3 {};

typedef version_tag_v3 version_tag;

} // internal
//! @endcond

} // tbb

#if defined(__EXCEPTIONS) || defined(_CPPUNWIND) || defined(__SUNPRO_CC)
#ifndef __TBB_EXCEPTIONS
#define __TBB_EXCEPTIONS 1
#endif /* __TBB_EXCEPTIONS */
#endif

#ifndef __TBB_SCHEDULER_OBSERVER
#define __TBB_SCHEDULER_OBSERVER 1
#endif /* __TBB_SCHEDULER_OBSERVER */

#ifndef __TBB_NAMING_API_SUPPORT
#define __TBB_NAMING_API_SUPPORT 1
#endif /* __TBB_NAMING_API_SUPPORT */


#endif /* RC_INVOKED */
#endif /* __TBB_tbb_stddef_H */
