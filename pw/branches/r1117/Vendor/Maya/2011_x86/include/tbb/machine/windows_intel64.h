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

#include <intrin.h>
#if !defined(__INTEL_COMPILER)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedCompareExchange64)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchange64)
#endif /* !defined(__INTEL_COMPILER) */

#if defined(__INTEL_COMPILER)
#define __TBB_release_consistency_helper() __asm { __asm nop }
inline void __TBB_rel_acq_fence() { __asm { __asm mfence } }
#elif _MSC_VER >= 1300
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define __TBB_release_consistency_helper() _ReadWriteBarrier()
#pragma intrinsic(_mm_mfence)
inline void __TBB_rel_acq_fence() { _mm_mfence(); }
#endif

#define __TBB_WORDSIZE 8
#define __TBB_BIG_ENDIAN 0

// ATTENTION: if you ever change argument types in machine-specific primitives,
// please take care of atomic_word<> specializations in tbb/atomic.h
extern "C" {
    __int8 __TBB_EXPORTED_FUNC __TBB_machine_cmpswp1 (volatile void *ptr, __int8 value, __int8 comparand );
    __int8 __TBB_EXPORTED_FUNC __TBB_machine_fetchadd1 (volatile void *ptr, __int8 addend );
    __int8 __TBB_EXPORTED_FUNC __TBB_machine_fetchstore1 (volatile void *ptr, __int8 value );
    __int16 __TBB_EXPORTED_FUNC __TBB_machine_cmpswp2 (volatile void *ptr, __int16 value, __int16 comparand );
    __int16 __TBB_EXPORTED_FUNC __TBB_machine_fetchadd2 (volatile void *ptr, __int16 addend );
    __int16 __TBB_EXPORTED_FUNC __TBB_machine_fetchstore2 (volatile void *ptr, __int16 value );
    void __TBB_EXPORTED_FUNC __TBB_machine_pause (__int32 delay );
}


#if !__INTEL_COMPILER
extern "C" unsigned char _BitScanReverse64( unsigned long* i, unsigned __int64 w );
#pragma intrinsic(_BitScanReverse64)
#endif

inline __int64 __TBB_machine_lg( unsigned __int64 i ) {
#if __INTEL_COMPILER
    unsigned __int64 j;
    __asm
    {
        bsr rax, i
        mov j, rax
    }
#else
    unsigned long j;
    _BitScanReverse64( &j, i );
#endif
    return j;
}

inline void __TBB_machine_OR( volatile void *operand, intptr_t addend ) {
    _InterlockedOr64((__int64*)operand, addend); 
}

inline void __TBB_machine_AND( volatile void *operand, intptr_t addend ) {
    _InterlockedAnd64((__int64*)operand, addend); 
}

#define __TBB_CompareAndSwap1(P,V,C) __TBB_machine_cmpswp1(P,V,C)
#define __TBB_CompareAndSwap2(P,V,C) __TBB_machine_cmpswp2(P,V,C)
#define __TBB_CompareAndSwap4(P,V,C) _InterlockedCompareExchange( (long*) P , V , C ) 
#define __TBB_CompareAndSwap8(P,V,C) _InterlockedCompareExchange64( (__int64*) P , V , C )
#define __TBB_CompareAndSwapW(P,V,C) _InterlockedCompareExchange64( (__int64*) P , V , C )

#define __TBB_FetchAndAdd1(P,V) __TBB_machine_fetchadd1(P,V)
#define __TBB_FetchAndAdd2(P,V) __TBB_machine_fetchadd2(P,V)
#define __TBB_FetchAndAdd4(P,V) _InterlockedExchangeAdd((long*) P , V )
#define __TBB_FetchAndAdd8(P,V) _InterlockedExchangeAdd64((__int64*) P , V )
#define __TBB_FetchAndAddW(P,V) _InterlockedExchangeAdd64((__int64*) P , V )

#define __TBB_FetchAndStore1(P,V) __TBB_machine_fetchstore1(P,V)
#define __TBB_FetchAndStore2(P,V) __TBB_machine_fetchstore2(P,V)
#define __TBB_FetchAndStore4(P,V) _InterlockedExchange((long*) P , V )
#define __TBB_FetchAndStore8(P,V) _InterlockedExchange64((__int64*) P , V )
#define __TBB_FetchAndStoreW(P,V) _InterlockedExchange64((__int64*) P , V ) 

// Not used if wordsize == 8
#undef __TBB_Store8
#undef __TBB_Load8

#define __TBB_AtomicOR(P,V) __TBB_machine_OR(P,V)
#define __TBB_AtomicAND(P,V) __TBB_machine_AND(P,V)

extern "C" __declspec(dllimport) int __stdcall SwitchToThread( void );
#define __TBB_Yield()  SwitchToThread()
#define __TBB_Pause(V) __TBB_machine_pause(V)
#define __TBB_Log2(V)    __TBB_machine_lg(V)

// Use generic definitions from tbb_machine.h
#undef __TBB_TryLockByte
#undef __TBB_LockByte
