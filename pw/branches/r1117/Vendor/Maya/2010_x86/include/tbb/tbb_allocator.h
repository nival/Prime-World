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

#ifndef __TBB_tbb_allocator_H
#define __TBB_tbb_allocator_H

#include <new>
#include "tbb_stddef.h"

namespace tbb {

//! @cond INTERNAL
namespace internal {

    //! Deallocates memory using FreeHandler
    /** The function uses scalable_free if scalable allocator is available and free if not*/
    void __TBB_EXPORTED_FUNC deallocate_via_handler_v3( void *p );

    //! Allocates memory using MallocHandler
    /** The function uses scalable_malloc if scalable allocator is available and malloc if not*/
    void* __TBB_EXPORTED_FUNC allocate_via_handler_v3( size_t n );

    //! Returns true if standard malloc/free are used to work with memory.
    bool __TBB_EXPORTED_FUNC is_malloc_used_v3();
}
//! @endcond

#if _MSC_VER && !defined(__INTEL_COMPILER)
    // Workaround for erroneous "unreferenced parameter" warning in method destroy.
    #pragma warning (push)
    #pragma warning (disable: 4100)
#endif

//! Meets "allocator" requirements of ISO C++ Standard, Section 20.1.5
/** The class selects the best memory allocation mechanism available 
    from scalable_malloc and standard malloc.
    The members are ordered the same way they are in section 20.4.1
    of the ISO C++ standard.
    @ingroup memory_allocation */
template<typename T>
class tbb_allocator {
public:
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<typename U> struct rebind {
        typedef tbb_allocator<U> other;
    };

    //! Specifies current allocator
    enum malloc_type {
        scalable, 
        standard
    };

    tbb_allocator() throw() {}
    tbb_allocator( const tbb_allocator& ) throw() {}
    template<typename U> tbb_allocator(const tbb_allocator<U>&) throw() {}

    pointer address(reference x) const {return &x;}
    const_pointer address(const_reference x) const {return &x;}
    
    //! Allocate space for n objects.
    pointer allocate( size_type n, const void* /*hint*/ = 0) {
        return pointer(internal::allocate_via_handler_v3( n * sizeof(T) ));
    }

    //! Free previously allocated block of memory.
    void deallocate( pointer p, size_type ) {
        internal::deallocate_via_handler_v3(p);        
    }

    //! Largest value for which method allocate might succeed.
    size_type max_size() const throw() {
        size_type max = static_cast<size_type>(-1) / sizeof (T);
        return (max > 0 ? max : 1);
    }
    
    //! Copy-construct value at location pointed to by p.
    void construct( pointer p, const T& value ) {new(static_cast<void*>(p)) T(value);}

    //! Destroy value at location pointed to by p.
    void destroy( pointer p ) {p->~T();}

    //! Returns current allocator
    static malloc_type allocator_type() {
        return internal::is_malloc_used_v3() ? standard : scalable;
    }
};

#if _MSC_VER && !defined(__INTEL_COMPILER)
    #pragma warning (pop)
#endif // warning 4100 is back

//! Analogous to std::allocator<void>, as defined in ISO C++ Standard, Section 20.4.1
/** @ingroup memory_allocation */
template<> 
class tbb_allocator<void> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;
    template<typename U> struct rebind {
        typedef tbb_allocator<U> other;
    };
};

template<typename T, typename U>
inline bool operator==( const tbb_allocator<T>&, const tbb_allocator<U>& ) {return true;}

template<typename T, typename U>
inline bool operator!=( const tbb_allocator<T>&, const tbb_allocator<U>& ) {return false;}

} // namespace tbb 

#endif /* __TBB_tbb_allocator_H */
