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

#include "linux_common.h"
#include <ia64intrin.h>

#define __TBB_WORDSIZE 8
#define __TBB_BIG_ENDIAN 0
#define __TBB_DECL_FENCED_ATOMICS 1

// Most of the functions will be in a .s file

extern "C" {
    int8_t __TBB_machine_cmpswp1__TBB_full_fence (volatile void *ptr, int8_t value, int8_t comparand); 
    int8_t __TBB_machine_fetchadd1__TBB_full_fence (volatile void *ptr, int8_t addend);
    int8_t __TBB_machine_fetchadd1acquire(volatile void *ptr, int8_t addend);
    int8_t __TBB_machine_fetchadd1release(volatile void *ptr, int8_t addend);
    int8_t __TBB_machine_fetchstore1acquire(volatile void *ptr, int8_t value);
    int8_t __TBB_machine_fetchstore1release(volatile void *ptr, int8_t value);

    int16_t __TBB_machine_cmpswp2__TBB_full_fence (volatile void *ptr, int16_t value, int16_t comparand);
    int16_t __TBB_machine_fetchadd2__TBB_full_fence (volatile void *ptr, int16_t addend);
    int16_t __TBB_machine_fetchadd2acquire(volatile void *ptr, int16_t addend);
    int16_t __TBB_machine_fetchadd2release(volatile void *ptr, int16_t addend);
    int16_t __TBB_machine_fetchstore2acquire(volatile void *ptr, int16_t value);
    int16_t __TBB_machine_fetchstore2release(volatile void *ptr, int16_t value);

    int32_t __TBB_machine_fetchstore4__TBB_full_fence (volatile void *ptr, int32_t value);
    int32_t __TBB_machine_fetchstore4acquire(volatile void *ptr, int32_t value);
    int32_t __TBB_machine_fetchstore4release(volatile void *ptr, int32_t value);
    int32_t __TBB_machine_fetchadd4acquire(volatile void *ptr, int32_t addend);
    int32_t __TBB_machine_fetchadd4release(volatile void *ptr, int32_t addend);

    int64_t __TBB_machine_cmpswp8__TBB_full_fence (volatile void *ptr, int64_t value, int64_t comparand);
    int64_t __TBB_machine_fetchstore8__TBB_full_fence (volatile void *ptr, int64_t value);
    int64_t __TBB_machine_fetchstore8acquire(volatile void *ptr, int64_t value);
    int64_t __TBB_machine_fetchstore8release(volatile void *ptr, int64_t value);
    int64_t __TBB_machine_fetchadd8acquire(volatile void *ptr, int64_t addend);
    int64_t __TBB_machine_fetchadd8release(volatile void *ptr, int64_t addend);

    int8_t __TBB_machine_cmpswp1acquire(volatile void *ptr, int8_t value, int8_t comparand); 
    int8_t __TBB_machine_cmpswp1release(volatile void *ptr, int8_t value, int8_t comparand); 
    int8_t __TBB_machine_fetchstore1__TBB_full_fence (volatile void *ptr, int8_t value);

    int16_t __TBB_machine_cmpswp2acquire(volatile void *ptr, int16_t value, int16_t comparand); 
    int16_t __TBB_machine_cmpswp2release(volatile void *ptr, int16_t value, int16_t comparand); 
    int16_t __TBB_machine_fetchstore2__TBB_full_fence (volatile void *ptr, int16_t value);

    int32_t __TBB_machine_cmpswp4__TBB_full_fence (volatile void *ptr, int32_t value, int32_t comparand);
    int32_t __TBB_machine_cmpswp4acquire(volatile void *ptr, int32_t value, int32_t comparand); 
    int32_t __TBB_machine_cmpswp4release(volatile void *ptr, int32_t value, int32_t comparand); 
    int32_t __TBB_machine_fetchadd4__TBB_full_fence (volatile void *ptr, int32_t value);

    int64_t __TBB_machine_cmpswp8acquire(volatile void *ptr, int64_t value, int64_t comparand); 
    int64_t __TBB_machine_cmpswp8release(volatile void *ptr, int64_t value, int64_t comparand); 
    int64_t __TBB_machine_fetchadd8__TBB_full_fence (volatile void *ptr, int64_t value);

    int64_t __TBB_machine_lg(uint64_t value);
    void __TBB_machine_pause(int32_t delay);
    bool __TBB_machine_trylockbyte( volatile unsigned char &ptr );
    int64_t __TBB_machine_lockbyte( volatile unsigned char &ptr );

    //! Retrieves the current RSE backing store pointer. IA64 specific.
    void* __TBB_get_bsp();
}

#define __TBB_CompareAndSwap1(P,V,C) __TBB_machine_cmpswp1__TBB_full_fence(P,V,C)
#define __TBB_CompareAndSwap2(P,V,C) __TBB_machine_cmpswp2__TBB_full_fence(P,V,C) 

#define __TBB_FetchAndAdd1(P,V)        __TBB_machine_fetchadd1__TBB_full_fence(P,V)
#define __TBB_FetchAndAdd1acquire(P,V) __TBB_machine_fetchadd1acquire(P,V)
#define __TBB_FetchAndAdd1release(P,V) __TBB_machine_fetchadd1release(P,V)
#define __TBB_FetchAndAdd2(P,V)        __TBB_machine_fetchadd2__TBB_full_fence(P,V)
#define __TBB_FetchAndAdd2acquire(P,V) __TBB_machine_fetchadd2acquire(P,V)
#define __TBB_FetchAndAdd2release(P,V) __TBB_machine_fetchadd2release(P,V)
#define __TBB_FetchAndAdd4acquire(P,V) __TBB_machine_fetchadd4acquire(P,V)
#define __TBB_FetchAndAdd4release(P,V) __TBB_machine_fetchadd4release(P,V)
#define __TBB_FetchAndAdd8acquire(P,V) __TBB_machine_fetchadd8acquire(P,V)
#define __TBB_FetchAndAdd8release(P,V) __TBB_machine_fetchadd8release(P,V)

#define __TBB_FetchAndStore1acquire(P,V) __TBB_machine_fetchstore1acquire(P,V)
#define __TBB_FetchAndStore1release(P,V) __TBB_machine_fetchstore1release(P,V)
#define __TBB_FetchAndStore2acquire(P,V) __TBB_machine_fetchstore2acquire(P,V)
#define __TBB_FetchAndStore2release(P,V) __TBB_machine_fetchstore2release(P,V)
#define __TBB_FetchAndStore4acquire(P,V) __TBB_machine_fetchstore4acquire(P,V)
#define __TBB_FetchAndStore4release(P,V) __TBB_machine_fetchstore4release(P,V)
#define __TBB_FetchAndStore8acquire(P,V) __TBB_machine_fetchstore8acquire(P,V)
#define __TBB_FetchAndStore8release(P,V) __TBB_machine_fetchstore8release(P,V)

#define __TBB_CompareAndSwap1acquire(P,V,C) __TBB_machine_cmpswp1acquire(P,V,C)
#define __TBB_CompareAndSwap1release(P,V,C) __TBB_machine_cmpswp1release(P,V,C)
#define __TBB_CompareAndSwap2acquire(P,V,C) __TBB_machine_cmpswp2acquire(P,V,C)
#define __TBB_CompareAndSwap2release(P,V,C) __TBB_machine_cmpswp2release(P,V,C)
#define __TBB_CompareAndSwap4(P,V,C)        __TBB_machine_cmpswp4__TBB_full_fence(P,V,C)
#define __TBB_CompareAndSwap4acquire(P,V,C) __TBB_machine_cmpswp4acquire(P,V,C)
#define __TBB_CompareAndSwap4release(P,V,C) __TBB_machine_cmpswp4release(P,V,C)
#define __TBB_CompareAndSwap8(P,V,C)        __TBB_machine_cmpswp8__TBB_full_fence(P,V,C)
#define __TBB_CompareAndSwap8acquire(P,V,C) __TBB_machine_cmpswp8acquire(P,V,C)
#define __TBB_CompareAndSwap8release(P,V,C) __TBB_machine_cmpswp8release(P,V,C)

#define __TBB_FetchAndAdd4(P,V) __TBB_machine_fetchadd4__TBB_full_fence(P,V)
#define __TBB_FetchAndAdd8(P,V) __TBB_machine_fetchadd8__TBB_full_fence(P,V)

#define __TBB_FetchAndStore1(P,V) __TBB_machine_fetchstore1__TBB_full_fence(P,V)
#define __TBB_FetchAndStore2(P,V) __TBB_machine_fetchstore2__TBB_full_fence(P,V)
#define __TBB_FetchAndStore4(P,V) __TBB_machine_fetchstore4__TBB_full_fence(P,V)
#define __TBB_FetchAndStore8(P,V) __TBB_machine_fetchstore8__TBB_full_fence(P,V)

#define __TBB_FetchAndIncrementWacquire(P) __TBB_FetchAndAdd8acquire(P,1)
#define __TBB_FetchAndDecrementWrelease(P) __TBB_FetchAndAdd8release(P,-1)

#ifndef __INTEL_COMPILER
/* Even though GCC imbues volatile loads with acquire semantics, 
   it sometimes moves loads over the acquire fence.  The
   fences defined here stop such incorrect code motion. */
#define __TBB_release_consistency_helper() __asm__ __volatile__("": : :"memory")
#define __TBB_rel_acq_fence() __asm__ __volatile__("mf": : :"memory")
#else
#define __TBB_release_consistency_helper()
#define __TBB_rel_acq_fence() __mf()
#endif /* __INTEL_COMPILER */

// Special atomic functions
#define __TBB_CompareAndSwapW(P,V,C)   __TBB_CompareAndSwap8(P,V,C)
#define __TBB_FetchAndStoreW(P,V)      __TBB_FetchAndStore8(P,V)
#define __TBB_FetchAndAddW(P,V)        __TBB_FetchAndAdd8(P,V)
#define __TBB_FetchAndAddWrelease(P,V) __TBB_FetchAndAdd8release(P,V)

// Not needed
#undef __TBB_Store8
#undef __TBB_Load8

// Definition of Lock functions
#define __TBB_TryLockByte(P) __TBB_machine_trylockbyte(P)
#define __TBB_LockByte(P)    __TBB_machine_lockbyte(P)

// Definition of other utility functions
#define __TBB_Pause(V) __TBB_machine_pause(V)
#define __TBB_Log2(V)  __TBB_machine_lg(V)

