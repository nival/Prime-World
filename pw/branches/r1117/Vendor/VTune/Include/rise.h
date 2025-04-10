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

#if !defined(__RISE_H__)
#define __RISE_H__

#include "vtune_types.h"
#include "rise_errors.h"

#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus


/* --------------------------------------------------------- */
/*!
 *
 *  General purpose routines
 *
 */

    
//
// Called once per process. For every open (or fork or dup),
// must call close. The driver_ptr is an opaque type used by the
// library. Allows for multiple opens in the future...
//

SAMPUTIL_API
RISE_ERROR SAMPUTIL_APICALL RISE_open(OUT RISE_PTR *rise_ptr);

SAMPUTIL_API
RISE_ERROR SAMPUTIL_APICALL RISE_close(IN RISE_PTR rise_ptr);

// This function takes an error code and returns a pointer to
// a constant string which is a textual translation of that
// error code.
//
// Since the string pointer returned is a constant, if the caller
// wants to manipulate the string, it is the responsibility of the
// caller to allocate space and copy the error string into that
// allocated buffer.
// The rise_ptr is the pointer passed back by RISE_open()
// It returns VT_SUCCESS if successful, VT_INVALID_ERR_CODE 
// if it cannot find the error code, or VT_SAM_ERROR for other error
// 
SAMPUTIL_API
RISE_ERROR SAMPUTIL_APICALL RISE_translate_err_code(IN RISE_PTR rise_ptr, IN RISE_ERROR err_code, OUT const VTSA_CHAR ** text);

SAMPUTIL_API
RISE_ERROR SAMPUTIL_APICALL RISE_get_error_string(IN RISE_ERROR error_code, OUT const VTSA_CHAR **error_string);


#ifdef __cplusplus
}
#endif   // __cplusplus
                          
#endif //__RISE_PUBLIC_H__
