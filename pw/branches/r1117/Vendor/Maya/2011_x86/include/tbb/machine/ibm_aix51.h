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

#ifndef __TBB_machine_H
#error Do not include this file directly; include tbb_machine.h instead
#endif

#define __TBB_WORDSIZE 8
#define __TBB_BIG_ENDIAN 1

#include <stdint.h>
#include <unistd.h>
#include <sched.h>

extern "C" {

int32_t __TBB_machine_cas_32 (volatile void* ptr, int32_t value, int32_t comparand);
int64_t __TBB_machine_cas_64 (volatile void* ptr, int64_t value, int64_t comparand);
#define __TBB_fence_for_acquire() __TBB_machine_flush ()
#define __TBB_fence_for_release() __TBB_machine_flush ()

}

#define __TBB_CompareAndSwap4(P,V,C) __TBB_machine_cas_32(P,V,C)
#define __TBB_CompareAndSwap8(P,V,C) __TBB_machine_cas_64(P,V,C)
#define __TBB_CompareAndSwapW(P,V,C) __TBB_machine_cas_64(P,V,C)
#define __TBB_Yield() sched_yield()
