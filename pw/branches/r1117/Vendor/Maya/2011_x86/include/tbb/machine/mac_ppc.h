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

#include <stdint.h>
#include <unistd.h>

#include <sched.h> // sched_yield

inline int32_t __TBB_machine_cmpswp4 (volatile void *ptr, int32_t value, int32_t comparand )
{
    int32_t result;

    __asm__ __volatile__("sync\n"
                         "0: lwarx %0,0,%2\n\t"  /* load w/ reservation */
                         "cmpw %0,%4\n\t"        /* compare against comparand */
                         "bne- 1f\n\t"           /* exit if not same */
                         "stwcx. %3,0,%2\n\t"    /* store new_value */
                         "bne- 0b\n"             /* retry if reservation lost */
                         "1: sync"               /* the exit */
                          : "=&r"(result), "=m"(* (int32_t*) ptr)
                          : "r"(ptr), "r"(value), "r"(comparand), "m"(* (int32_t*) ptr)
                          : "cr0");
    return result;
}

inline int64_t __TBB_machine_cmpswp8 (volatile void *ptr, int64_t value, int64_t comparand )
{
    int64_t result;
    __asm__ __volatile__("sync\n"
                         "0: ldarx %0,0,%2\n\t"  /* load w/ reservation */
                         "cmpd %0,%4\n\t"        /* compare against comparand */
                         "bne- 1f\n\t"           /* exit if not same */
                         "stdcx. %3,0,%2\n\t"    /* store new_value */
                         "bne- 0b\n"             /* retry if reservation lost */
                         "1: sync"               /* the exit */
                          : "=&b"(result), "=m"(* (int64_t*) ptr)
                          : "r"(ptr), "r"(value), "r"(comparand), "m"(* (int64_t*) ptr)
                          : "cr0");
    return result;
}

#define __TBB_BIG_ENDIAN 1

#if defined(powerpc64) || defined(__powerpc64__) || defined(__ppc64__)
#define __TBB_WORDSIZE 8
#define __TBB_CompareAndSwapW(P,V,C) __TBB_machine_cmpswp8(P,V,C)
#else
#define __TBB_WORDSIZE 4
#define __TBB_CompareAndSwapW(P,V,C) __TBB_machine_cmpswp4(P,V,C)
#endif

#define __TBB_CompareAndSwap4(P,V,C) __TBB_machine_cmpswp4(P,V,C)
#define __TBB_CompareAndSwap8(P,V,C) __TBB_machine_cmpswp8(P,V,C)
#define __TBB_Yield() sched_yield()
#define __TBB_rel_acq_fence() __asm__ __volatile__("lwsync": : :"memory")
#define __TBB_release_consistency_helper() __TBB_rel_acq_fence()
