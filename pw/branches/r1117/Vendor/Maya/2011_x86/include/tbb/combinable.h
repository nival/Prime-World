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

#ifndef __TBB_combinable_H
#define __TBB_combinable_H

#include "tbb/enumerable_thread_specific.h"
#include "tbb/cache_aligned_allocator.h"

namespace tbb {
/** \name combinable
    **/
//@{
//! Thread-local storage with optional reduction
/** @ingroup containers */
    template <typename T>
        class combinable {
    private:
        typedef typename tbb::cache_aligned_allocator<T> my_alloc;

        typedef typename tbb::enumerable_thread_specific<T, my_alloc, ets_no_key> my_ets_type;
        my_ets_type my_ets; 
 
    public:

        combinable() { }

        template <typename finit>
        combinable( finit _finit) : my_ets(_finit) { }

        //! destructor
        ~combinable() { 
        }

        combinable(const combinable& other) : my_ets(other.my_ets) { }

        combinable & operator=( const combinable & other) { my_ets = other.my_ets; return *this; }

        void clear() { my_ets.clear(); }

        T& local() { return my_ets.local(); }

        T& local(bool & exists) { return my_ets.local(exists); }

        template< typename FCombine>
        T combine(FCombine fcombine) { return my_ets.combine(fcombine); }

        template<typename FCombine>
        void combine_each(FCombine fcombine) { my_ets.combine_each(fcombine); }

    };
} // namespace tbb
#endif /* __TBB_combinable_H */
