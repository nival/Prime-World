/**********************************************************************************************
 * INTEL CONFIDENTIAL
 * Copyright 2004-2008 Intel Corporation All Rights Reserved.
 * 
 * The source code contained or described herein and all documents related to the source code
 * ("Material") are owned by Intel Corporation or its suppliers or licensors. Title to the
 * Material remains with Intel Corporation or its suppliers and licensors. The Material
 * contains trade secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright and trade secret
 * laws and treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or disclosed in any way
 * without Intel's prior express written permission.
 *   
 * No license under any patent, copyright, trade secret or other intellectual property right
 * is granted to or conferred upon you by disclosure or delivery of the Materials, either
 * expressly, by implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in writing.
 */

#ifndef __VTSA_STATIC_TYPES_H__
#define __VTSA_STATIC_TYPES_H__

#if 0

To allow for a more easily portable environment, certain #define constants
will be guaranteed to exist (or conversely, guaranteed NOT to exist) for
certain compilation environments.

Specifically, we need to handle portability between:

    OSes (such as Linux* vs. Windows*)
    Architectures (such as Intel(R) Itanium(R) architecture and "IA32 architecture")
    Native pointer sizes (such as 32-bit for "IA32 architecture" and 64 bit for Intel(R) Itanium(R) architecture)

To avoid having different developers define these values in different ways,
this header file will take care of determining the compilation environment
and then setting specific #defines which can be used as flags
during later compilation as necessary.


General guidelines we are trying to follow:

1) The namespace prefix for "global" related macros and "#define"
    constants will be VTSA_xxx.

2) Standardize on the way to handle different environmental aspects
    for static "#if defined()" compilation

3) Make sure any "#else" clause always has a "#error" indication.

Specifically, for any given OS, one (and only one) of the following will
be defined:

VTSA_OS_WINDOWS		-- The OS is a Windows OS (any bit size, any architecture)
VTSA_OS_LINUX		-- The OS is a Linux OS (any bit size, any architecture)
VTSA_OS_DARWIN		-- The OS is a Darwin / Mac OSX (any bit size, any architecture)

For any given architecture, one (and only one) of the following will
be defined:

VTSA_ARCH_PENTIUM		-- The current architecture is "IA32 architecture"/Intel(R) Extended memory 64 Technology (Intel(R) EM64T)  (any OS, any bit size)
VTSA_ARCH_IA64		-- The current architecture is Intel(R) Itanium(R) architecture (any OS, any bit size but implies 64-bits)
VTSA_ARCH_XSCALE		-- The current architecture is Intel XScale(R) (any OS, any bit size)

And for any given native pointer size, one (and only one) of the following
will be defined:
VTSA_32BIT			-- The current "native" bit size is 32 bits (any OS, any architecture)
VTSA_64BIT			-- The current "native" bit size is 64 bits (any OS, any architecture)

For any given compiler, one (and only one) of the following will be defined:
VTSA_COMPILER_ICC   -- The current compiler is the Intel(R) C Compiler
VTSA_COMPILER_GCC   -- The current compiler is the GNU project C and C++ compiler
VTSA_COMPILER_MSC   -- The current compiler is the Microsoft(R) C/C++ Optimizing Compiler


When you need a specific combination of these elements, you need to
explicitly check for that combination. For example:

#if defined(VTSA_OS_WINDOWS) && defined(VTSA_64BIT)
	// code here is only compiled on a 64-bit window
    // platform (either Intel(R) EM64T or Intel(R) Itanium(R) architecture)
#endif

#if defined(VTSA_OS_LINUX) && defined(VTSA_ARCH_PENTIUM)
	// code here is only compiled on a Linux machine
    // that is running either "IA32 architecture" or Intel(R) EM64T
#endif

#if (defined(VTSA_OS_DARWIN) || defined(VTSA_OS_LINUX)) && defined(VTSA_32BIT)
	// code here is for either Darwin or Linux,
    // any architecture, but only for "native" 32-bit products
#endif

If you have two static code paths, one for Darwin and Linux and
the other for Windows, then the correct way to show that is:

#if defined(VTSA_OS_DARWIN) || defined(VTSA_OS_LINUX)
	// this is Darwin or Linux code
#elif defined(VTSA_OS_WINDOWS)
	// this is Windows specific code
#else
	// this makes life easier when we go to a different OS...
#error "Unexpected OS seen"
#endif

#endif  // #if 0 comment section


//
// Start off with none of the OS'es are defined
//
#undef VTSA_OS_WINDOWS
#undef VTSA_OS_LINUX
#undef VTSA_OS_DARWIN

//
// Make sure none of the architectures is defined here
//
#undef VTSA_ARCH_PENTIUM
#undef VTSA_ARCH_IA64
#undef VTSA_ARCH_XSCALE

//
// Make sure none of the native pointer sizes is defined here
//
#undef VTSA_32BIT
#undef VTSA_64BIT

//
// Make sure none of the compilers is defined here
//
#undef VTSA_COMPILER_ICC
#undef VTSA_COMPILER_GCC
#undef VTSA_COMPILER_MSC

//
// Make sure none of the build types is defined here
//
#undef VTSA_BUILD_RELEASE
#undef VTSA_BUILD_DEBUG


//
// Make sure one (and only one) of the OS'es gets defined here
//
// Unfortunately entirex defines _WIN32 so we need to check for linux
// first. We don't want VTSA_OS_LINUX and VTSA_OS_WINDOWS defined for
// entirex. The definition of these flags is one and only one
// VTSA_OS_xxx is allowed to be defined.
//
#if defined(linux)
#define VTSA_OS_LINUX       1
#elif defined(_WIN32)
#define VTSA_OS_WINDOWS       1
#elif defined(__APPLE__)
#define VTSA_OS_DARWIN       1
#else
#error "Compiling for an unknown OS"
#endif

//
// Make sure one (and only one) architecture is defined here
// as well as one (and only one) pointer size
//
#if defined(_M_IX86) || defined(__i386__)
#define VTSA_32BIT          1
#define VTSA_ARCH_PENTIUM   1
#elif defined(_M_IA64) || defined(__ia64__)
#define VTSA_ARCH_IA64      1
#define VTSA_64BIT          1
#elif defined(_M_AMD64) || defined(__x86_64__)
#define VTSA_ARCH_PENTIUM   1
#define VTSA_64BIT          1
#else
#error "Unknown architecture for compilation"
#endif


//
// Make sure one (and only one) compiler is defined here
//
// We have to check for ICC first, because it will emulate the version
// variables used by GCC and MSC.
//
#if defined(__INTEL_COMPILER)
#define VTSA_COMPILER_ICC   1
#elif defined(__GNUC__)
#define VTSA_COMPILER_GCC   1
#elif defined(_MSC_VER)
#define VTSA_COMPILER_MSC   1
#else
#error "Unknown compiler"
#endif


//
// Add a well defined definition of compiling for release (free) vs.
// debug (checked). Once again, don't assume these are the only two values,
// always have an else clause in case we want to expand this.
//
// The DBG variable is used by the win ddk to define free vs. checked builds.
// The defined(_DEBUG) is a visual studio thing. Of course, we all know we
// aren't supposed to be compiling using visual studio, don't we?
//
#if defined(VTSA_OS_WINDOWS)

#if DBG || defined(_DEBUG)
#define VTSA_BUILD_DEBUG    1
#else
#define VTSA_BUILD_RELEASE  1
#endif

#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
//
// How do we mark Linux for release vs. debug builds?
//
#define VTSA_BUILD_RELEASE  1

#else
#error "Compiling for an unknown OS"
#endif

#endif  // __VTSA_STATIC_ENV_H__
