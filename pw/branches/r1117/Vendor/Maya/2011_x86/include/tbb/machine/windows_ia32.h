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

#if defined(__INTEL_COMPILER)
#define __TBB_release_consistency_helper() __asm { __asm nop }
#elif _MSC_VER >= 1300
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define __TBB_release_consistency_helper() _ReadWriteBarrier()
#else
#error Unsupported compiler - need to define __TBB_release_consistency_helper to support it
#endif

inline void __TBB_rel_acq_fence() { __asm { __asm mfence } }

#define __TBB_WORDSIZE 4
#define __TBB_BIG_ENDIAN 0

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    // Workaround for overzealous compiler warnings in /Wp64 mode
    #pragma warning (push)
    #pragma warning (disable: 4244 4267)
#endif

extern "C" {
    __int64 __TBB_EXPORTED_FUNC __TBB_machine_cmpswp8 (volatile void *ptr, __int64 value, __int64 comparand );
    __int64 __TBB_EXPORTED_FUNC __TBB_machine_fetchadd8 (volatile void *ptr, __int64 addend );
    __int64 __TBB_EXPORTED_FUNC __TBB_machine_fetchstore8 (volatile void *ptr, __int64 value );
    void __TBB_EXPORTED_FUNC __TBB_machine_store8 (volatile void *ptr, __int64 value );
    __int64 __TBB_EXPORTED_FUNC __TBB_machine_load8 (const volatile void *ptr);
}

template <typename T, size_t S>
struct __TBB_machine_load_store {
    static inline T load_with_acquire(const volatile T& location) {
        T to_return = location;
        __TBB_release_consistency_helper();
        return to_return;
    }

    static inline void store_with_release(volatile T &location, T value) {
        __TBB_release_consistency_helper();
        location = value;
    }
};

template <typename T>
struct __TBB_machine_load_store<T,8> {
    static inline T load_with_acquire(const volatile T& location) {
        return __TBB_machine_load8((volatile void *)&location);
    }

    static inline void store_with_release(T &location, T value) {
        __TBB_machine_store8((volatile void *)&location,(__int64)value);
    }
};

template<typename T>
inline T __TBB_machine_load_with_acquire(const volatile T &location) {
    return __TBB_machine_load_store<T,sizeof(T)>::load_with_acquire(location);
}

template<typename T, typename V>
inline void __TBB_machine_store_with_release(T& location, V value) {
    __TBB_machine_load_store<T,sizeof(T)>::store_with_release(location,value);
}

//! Overload that exists solely to avoid /Wp64 warnings.
inline void __TBB_machine_store_with_release(size_t& location, size_t value) {
    __TBB_machine_load_store<size_t,sizeof(size_t)>::store_with_release(location,value);
} 

#define __TBB_load_with_acquire(L) __TBB_machine_load_with_acquire((L))
#define __TBB_store_with_release(L,V) __TBB_machine_store_with_release((L),(V))

#define __TBB_DEFINE_ATOMICS(S,T,U,A,C) \
static inline T __TBB_machine_cmpswp##S ( volatile void * ptr, U value, U comparand ) { \
    T result; \
    volatile T *p = (T *)ptr; \
    __TBB_release_consistency_helper(); \
    __asm \
    { \
       __asm mov edx, p \
       __asm mov C , value \
       __asm mov A , comparand \
       __asm lock cmpxchg [edx], C \
       __asm mov result, A \
    } \
    __TBB_release_consistency_helper(); \
    return result; \
} \
\
static inline T __TBB_machine_fetchadd##S ( volatile void * ptr, U addend ) { \
    T result; \
    volatile T *p = (T *)ptr; \
    __TBB_release_consistency_helper(); \
    __asm \
    { \
        __asm mov edx, p \
        __asm mov A, addend \
        __asm lock xadd [edx], A \
        __asm mov result, A \
    } \
    __TBB_release_consistency_helper(); \
    return result; \
}\
\
static inline T __TBB_machine_fetchstore##S ( volatile void * ptr, U value ) { \
    T result; \
    volatile T *p = (T *)ptr; \
    __TBB_release_consistency_helper(); \
    __asm \
    { \
        __asm mov edx, p \
        __asm mov A, value \
        __asm lock xchg [edx], A \
        __asm mov result, A \
    } \
    __TBB_release_consistency_helper(); \
    return result; \
}

__TBB_DEFINE_ATOMICS(1, __int8, __int8, al, cl)
__TBB_DEFINE_ATOMICS(2, __int16, __int16, ax, cx)
__TBB_DEFINE_ATOMICS(4, __int32, ptrdiff_t, eax, ecx)

static inline __int32 __TBB_machine_lg( unsigned __int64 i ) {
    unsigned __int32 j;
    __asm
    {
        bsr eax, i
        mov j, eax
    }
    return j;
}

static inline void __TBB_machine_OR( volatile void *operand, __int32 addend ) {
   __asm 
   {
       mov eax, addend
       mov edx, [operand]
       lock or [edx], eax
   }
}

static inline void __TBB_machine_AND( volatile void *operand, __int32 addend ) {
   __asm 
   {
       mov eax, addend
       mov edx, [operand]
       lock and [edx], eax
   }
}

static inline void __TBB_machine_pause (__int32 delay ) {
    _asm 
    {
        mov eax, delay
      L1: 
        pause
        add eax, -1
        jne L1  
    }
    return;
}

#define __TBB_CompareAndSwap1(P,V,C) __TBB_machine_cmpswp1(P,V,C)
#define __TBB_CompareAndSwap2(P,V,C) __TBB_machine_cmpswp2(P,V,C)
#define __TBB_CompareAndSwap4(P,V,C) __TBB_machine_cmpswp4(P,V,C)
#define __TBB_CompareAndSwap8(P,V,C) __TBB_machine_cmpswp8(P,V,C)
#define __TBB_CompareAndSwapW(P,V,C) __TBB_machine_cmpswp4(P,V,C)

#define __TBB_FetchAndAdd1(P,V) __TBB_machine_fetchadd1(P,V)
#define __TBB_FetchAndAdd2(P,V) __TBB_machine_fetchadd2(P,V)
#define __TBB_FetchAndAdd4(P,V) __TBB_machine_fetchadd4(P,V)
#define __TBB_FetchAndAdd8(P,V) __TBB_machine_fetchadd8(P,V)
#define __TBB_FetchAndAddW(P,V) __TBB_machine_fetchadd4(P,V)

#define __TBB_FetchAndStore1(P,V) __TBB_machine_fetchstore1(P,V)
#define __TBB_FetchAndStore2(P,V) __TBB_machine_fetchstore2(P,V)
#define __TBB_FetchAndStore4(P,V) __TBB_machine_fetchstore4(P,V)
#define __TBB_FetchAndStore8(P,V) __TBB_machine_fetchstore8(P,V)
#define __TBB_FetchAndStoreW(P,V) __TBB_machine_fetchstore4(P,V)

// Should define this: 
#define __TBB_Store8(P,V) __TBB_machine_store8(P,V)
#define __TBB_Load8(P) __TBB_machine_load8(P)
#define __TBB_AtomicOR(P,V) __TBB_machine_OR(P,V)
#define __TBB_AtomicAND(P,V) __TBB_machine_AND(P,V)

// Definition of other functions
extern "C" __declspec(dllimport) int __stdcall SwitchToThread( void );
#define __TBB_Yield()  SwitchToThread()
#define __TBB_Pause(V) __TBB_machine_pause(V)
#define __TBB_Log2(V)    __TBB_machine_lg(V)

// Use generic definitions from tbb_machine.h
#undef __TBB_TryLockByte
#undef __TBB_LockByte

#if defined(_MSC_VER)&&_MSC_VER<1400
    static inline void* __TBB_machine_get_current_teb () {
        void* pteb;
        __asm mov eax, fs:[0x18]
        __asm mov pteb, eax
        return pteb;
    }
#endif

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    #pragma warning (pop)
#endif // warnings 4244, 4267 are back

