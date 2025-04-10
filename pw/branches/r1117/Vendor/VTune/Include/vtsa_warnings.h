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

#ifndef __VTSA_WARNINGS_H__
#define __VTSA_WARNINGS_H__

#include "vtsa_static_env.h"

#if defined(VTSA_OS_WINDOWS)
#pragma once
#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
// Do they have a "#pragma once" equivalent?
#else
#error "unknown os"
#endif


#if defined(VTSA_PRODUCT_PRIVATE)

//
// The functions wcstombs and mbstowcs should *NOT* be used anywhere in SEP.
// We use UTF-8 for all multibyte strings, and that's unreliable with wcstombs
// and mbstowcs.
//
// Instead, use wcs_to_utf8[_malloced] and utf8_to_wcs[_malloced].
//
#if defined(VTSA_COMPILER_MSC)
#include <stdlib.h>
//Commented out so we don't raise an error for the standard library
//#pragma deprecated( wcstombs, mbstowcs )
//#pragma warning( error : 4995 )

#elif defined(VTSA_COMPILER_GCC)
#include <stdlib.h>
//Commented out so we don't raise an error for the standard library
//#pragma GCC poison wcstombs mbstowcs

#elif defined(VTSA_COMPILER_ICC)
// is there a deprecation macro?

#else
#error "Unknown compiler"
#endif

#else
//
// We only do the deprecation check on private builds, to avoid
// forcing a mantra on external folks...
//
#endif

#endif  // __VTSA_WARNINGS_H__
