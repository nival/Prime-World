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

#ifndef __TBB_scalable_allocator_H
#define __TBB_scalable_allocator_H
/** @file */

#include <stddef.h> /* Need ptrdiff_t and size_t from here. */

#if !defined(__cplusplus) && __ICC==1100
    #pragma warning (push)
    #pragma warning (disable: 991)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if _MSC_VER >= 1400
#define __TBB_EXPORTED_FUNC   __cdecl
#else
#define __TBB_EXPORTED_FUNC
#endif

/** The "malloc" analogue to allocate block of memory of size bytes.
  * @ingroup memory_allocation */
void * __TBB_EXPORTED_FUNC scalable_malloc (size_t size);

/** The "free" analogue to discard a previously allocated piece of memory.
    @ingroup memory_allocation */
void   __TBB_EXPORTED_FUNC scalable_free (void* ptr);

/** The "realloc" analogue complementing scalable_malloc.
    @ingroup memory_allocation */
void * __TBB_EXPORTED_FUNC scalable_realloc (void* ptr, size_t size);

/** The "calloc" analogue complementing scalable_malloc.
    @ingroup memory_allocation */
void * __TBB_EXPORTED_FUNC scalable_calloc (size_t nobj, size_t size);

/** The "posix_memalign" analogue.
    @ingroup memory_allocation */
int __TBB_EXPORTED_FUNC scalable_posix_memalign (void** memptr, size_t alignment, size_t size);

/** The "_aligned_malloc" analogue.
    @ingroup memory_allocation */
void * __TBB_EXPORTED_FUNC scalable_aligned_malloc (size_t size, size_t alignment);

/** The "_aligned_realloc" analogue.
    @ingroup memory_allocation */
void * __TBB_EXPORTED_FUNC scalable_aligned_realloc (void* ptr, size_t size, size_t alignment);

/** The "_aligned_free" analogue.
    @ingroup memory_allocation */
void __TBB_EXPORTED_FUNC scalable_aligned_free (void* ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#ifdef __cplusplus

#include <new>      /* To use new with the placement argument */

namespace tbb {

#if _MSC_VER && !defined(__INTEL_COMPILER)
    // Workaround for erroneous "unreferenced parameter" warning in method destroy.
    #pragma warning (push)
    #pragma warning (disable: 4100)
#endif

//! Meets "allocator" requirements of ISO C++ Standard, Section 20.1.5
/** The members are ordered the same way they are in section 20.4.1
    of the ISO C++ standard.
    @ingroup memory_allocation */
template<typename T>
class scalable_allocator {
public:
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<class U> struct rebind {
        typedef scalable_allocator<U> other;
    };

    scalable_allocator() throw() {}
    scalable_allocator( const scalable_allocator& ) throw() {}
    template<typename U> scalable_allocator(const scalable_allocator<U>&) throw() {}

    pointer address(reference x) const {return &x;}
    const_pointer address(const_reference x) const {return &x;}

    //! Allocate space for n objects.
    pointer allocate( size_type n, const void* /*hint*/ =0 ) {
        return static_cast<pointer>( scalable_malloc( n * sizeof(value_type) ) );
    }

    //! Free previously allocated block of memory
    void deallocate( pointer p, size_type ) {
        scalable_free( p );
    }

    //! Largest value for which method allocate might succeed.
    size_type max_size() const throw() {
        size_type absolutemax = static_cast<size_type>(-1) / sizeof (T);
        return (absolutemax > 0 ? absolutemax : 1);
    }
    void construct( pointer p, const T& val ) { new(static_cast<void*>(p)) T(val); }
    void destroy( pointer p ) {p->~T();}
};

#if _MSC_VER && !defined(__INTEL_COMPILER)
    #pragma warning (pop)
#endif // warning 4100 is back

//! Analogous to std::allocator<void>, as defined in ISO C++ Standard, Section 20.4.1
/** @ingroup memory_allocation */
template<>
class scalable_allocator<void> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;
    template<class U> struct rebind {
        typedef scalable_allocator<U> other;
    };
};

template<typename T, typename U>
inline bool operator==( const scalable_allocator<T>&, const scalable_allocator<U>& ) {return true;}

template<typename T, typename U>
inline bool operator!=( const scalable_allocator<T>&, const scalable_allocator<U>& ) {return false;}

} // namespace tbb

#if _MSC_VER
    #if __TBB_BUILD && !defined(__TBBMALLOC_NO_IMPLICIT_LINKAGE)
        #define __TBBMALLOC_NO_IMPLICIT_LINKAGE 1
    #endif

    #if !__TBBMALLOC_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "tbbmalloc_debug.lib")
        #else
            #pragma comment(lib, "tbbmalloc.lib")
        #endif
    #endif
#endif

#endif /* __cplusplus */

#if !defined(__cplusplus) && __ICC==1100
    #pragma warning (pop)
#endif // ICC 11.0 warning 991 is back

#endif /* __TBB_scalable_allocator_H */
