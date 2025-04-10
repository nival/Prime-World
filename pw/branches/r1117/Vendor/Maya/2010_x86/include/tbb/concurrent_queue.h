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

#ifndef __TBB_concurrent_queue_H
#define __TBB_concurrent_queue_H

#include "tbb_stddef.h"
#include "cache_aligned_allocator.h"
#include <iterator>
#include <new>

namespace tbb {

template<typename T, class A = cache_aligned_allocator<T> > 
class concurrent_queue;

//! @cond INTERNAL
namespace internal {

class concurrent_queue_rep;
class concurrent_queue_iterator_rep;
class concurrent_queue_iterator_base_v3;
template<typename Container, typename Value> class concurrent_queue_iterator;

//! For internal use only.
/** Type-independent portion of concurrent_queue.
    @ingroup containers */
class concurrent_queue_base_v3: no_copy {
    //! Internal representation
    concurrent_queue_rep* my_rep;

    friend class concurrent_queue_rep;
    friend struct micro_queue;
    friend class micro_queue_pop_finalizer;
    friend class concurrent_queue_iterator_rep;
    friend class concurrent_queue_iterator_base_v3;
protected:
    //! Prefix on a page
    struct page {
        page* next;
        uintptr mask; 
    };

    //! Capacity of the queue
    ptrdiff_t my_capacity;
   
    //! Always a power of 2
    size_t items_per_page;

    //! Size of an item
    size_t item_size;

private:
    virtual void copy_item( page& dst, size_t index, const void* src ) = 0;
    virtual void assign_and_destroy_item( void* dst, page& src, size_t index ) = 0;
protected:
    __TBB_EXPORTED_METHOD concurrent_queue_base_v3( size_t item_size );
    virtual __TBB_EXPORTED_METHOD ~concurrent_queue_base_v3();

    //! Enqueue item at tail of queue
    void __TBB_EXPORTED_METHOD internal_push( const void* src );

    //! Dequeue item from head of queue
    void __TBB_EXPORTED_METHOD internal_pop( void* dst );

    //! Attempt to enqueue item onto queue.
    bool __TBB_EXPORTED_METHOD internal_push_if_not_full( const void* src );

    //! Attempt to dequeue item from queue.
    /** NULL if there was no item to dequeue. */
    bool __TBB_EXPORTED_METHOD internal_pop_if_present( void* dst );

    //! Get size of queue
    ptrdiff_t __TBB_EXPORTED_METHOD internal_size() const;

    //! set the queue capacity
    void __TBB_EXPORTED_METHOD internal_set_capacity( ptrdiff_t capacity, size_t element_size );

    //! custom allocator
    virtual page *allocate_page() = 0;

    //! custom de-allocator
    virtual void deallocate_page( page *p ) = 0;

    //! free any remaining pages
    /* note that the name may be misleading, but it remains so due to a historical accident. */
    void __TBB_EXPORTED_METHOD internal_finish_clear() ;

    //! throw an exception
    void __TBB_EXPORTED_METHOD internal_throw_exception() const;

    //! copy internal representation
    void __TBB_EXPORTED_METHOD assign( const concurrent_queue_base_v3& src ) ;

private:
    virtual void copy_item( page& dst, size_t dindex, const page& src, size_t sindex ) = 0;
};

typedef concurrent_queue_base_v3 concurrent_queue_base ;

//! Type-independent portion of concurrent_queue_iterator.
/** @ingroup containers */
class concurrent_queue_iterator_base_v3 {
    //! Concurrentconcurrent_queue over which we are iterating.
    /** NULL if one past last element in queue. */
    concurrent_queue_iterator_rep* my_rep;

    template<typename C, typename T, typename U>
    friend bool operator==( const concurrent_queue_iterator<C,T>& i, const concurrent_queue_iterator<C,U>& j );

    template<typename C, typename T, typename U>
    friend bool operator!=( const concurrent_queue_iterator<C,T>& i, const concurrent_queue_iterator<C,U>& j );
protected:
    //! Pointer to current item
    mutable void* my_item;

    //! Default constructor
    concurrent_queue_iterator_base_v3() : my_rep(NULL), my_item(NULL) {}

    //! Copy constructor
    concurrent_queue_iterator_base_v3( const concurrent_queue_iterator_base_v3& i ) : my_rep(NULL), my_item(NULL) {
        assign(i);
    }

    //! Construct iterator pointing to head of queue.
    __TBB_EXPORTED_METHOD concurrent_queue_iterator_base_v3( const concurrent_queue_base& queue );

    //! Assignment
    void __TBB_EXPORTED_METHOD assign( const concurrent_queue_iterator_base_v3& i );

    //! Advance iterator one step towards tail of queue.
    void __TBB_EXPORTED_METHOD advance();

    //! Destructor
    __TBB_EXPORTED_METHOD ~concurrent_queue_iterator_base_v3();
};

typedef concurrent_queue_iterator_base_v3 concurrent_queue_iterator_base;

//! Meets requirements of a forward iterator for STL.
/** Value is either the T or const T type of the container.
    @ingroup containers */
template<typename Container, typename Value>
class concurrent_queue_iterator: public concurrent_queue_iterator_base,
        public std::iterator<std::forward_iterator_tag,Value> {
#if !defined(_MSC_VER) || defined(__INTEL_COMPILER)
    template<typename T, class A>
    friend class ::tbb::concurrent_queue;
#else
public: // workaround for MSVC
#endif 
    //! Construct iterator pointing to head of queue.
    concurrent_queue_iterator( const concurrent_queue_base& queue ) :
        concurrent_queue_iterator_base_v3(queue)
    {
    }
public:
    concurrent_queue_iterator() {}

    /** If Value==Container::value_type, then this routine is the copy constructor. 
        If Value==const Container::value_type, then this routine is a conversion constructor. */
    concurrent_queue_iterator( const concurrent_queue_iterator<Container,typename Container::value_type>& other ) :
        concurrent_queue_iterator_base_v3(other)
    {}

    //! Iterator assignment
    concurrent_queue_iterator& operator=( const concurrent_queue_iterator& other ) {
        assign(other);
        return *this;
    }

    //! Reference to current item 
    Value& operator*() const {
        return *static_cast<Value*>(my_item);
    }

    Value* operator->() const {return &operator*();}

    //! Advance to next item in queue
    concurrent_queue_iterator& operator++() {
        advance();
        return *this;
    }

    //! Post increment
    Value* operator++(int) {
        Value* result = &operator*();
        operator++();
        return result;
    }
}; // concurrent_queue_iterator


template<typename C, typename T, typename U>
bool operator==( const concurrent_queue_iterator<C,T>& i, const concurrent_queue_iterator<C,U>& j ) {
    return i.my_item==j.my_item;
}

template<typename C, typename T, typename U>
bool operator!=( const concurrent_queue_iterator<C,T>& i, const concurrent_queue_iterator<C,U>& j ) {
    return i.my_item!=j.my_item;
}

} // namespace internal;

//! @endcond

//! A high-performance thread-safe queue.
/** Multiple threads may each push and pop concurrently.
    Assignment and copy construction are not allowed.
    @ingroup containers */
template<typename T, class A>
class concurrent_queue: public internal::concurrent_queue_base_v3 {
    template<typename Container, typename Value> friend class internal::concurrent_queue_iterator;

    //! allocator type
    typedef typename A::template rebind<char>::other page_allocator_type;
    page_allocator_type my_allocator;

    //! Class used to ensure exception-safety of method "pop" 
    class destroyer: internal::no_copy {
        T& my_value;
    public:
        destroyer( T& value ) : my_value(value) {}
        ~destroyer() {my_value.~T();}          
    };

    T& get_ref( page& page, size_t index ) {
        __TBB_ASSERT( index<items_per_page, NULL );
        return static_cast<T*>(static_cast<void*>(&page+1))[index];
    }

    /*override*/ virtual void copy_item( page& dst, size_t index, const void* src ) {
        new( &get_ref(dst,index) ) T(*static_cast<const T*>(src)); 
    }

    /*override*/ virtual void copy_item( page& dst, size_t dindex, const page& src, size_t sindex ) {
        new( &get_ref(dst,dindex) ) T( static_cast<const T*>(static_cast<const void*>(&src+1))[sindex] );
    }

    /*override*/ virtual void assign_and_destroy_item( void* dst, page& src, size_t index ) {
        T& from = get_ref(src,index);
        destroyer d(from);
        *static_cast<T*>(dst) = from;
    }

    /*overide*/ virtual page *allocate_page() {
        size_t n = sizeof(page) + items_per_page*item_size;
        page *p = reinterpret_cast<page*>(my_allocator.allocate( n ));
        if( !p ) internal_throw_exception(); 
        return p;
    }

    /*override*/ virtual void deallocate_page( page *p ) {
        size_t n = sizeof(page) + items_per_page*item_size;
        my_allocator.deallocate( reinterpret_cast<char*>(p), n );
    }

public:
    //! Element type in the queue.
    typedef T value_type;

    //! Allocator type
    typedef A allocator_type;

    //! Reference type
    typedef T& reference;

    //! Const reference type
    typedef const T& const_reference;

    //! Integral type for representing size of the queue.
    /** Notice that the size_type is a signed integral type.
        This is because the size can be negative if there are pending pops without corresponding pushes. */
    typedef std::ptrdiff_t size_type;

    //! Difference type for iterator
    typedef std::ptrdiff_t difference_type;

    //! Construct empty queue
    explicit concurrent_queue(const allocator_type  &a = allocator_type()) : 
        concurrent_queue_base_v3( sizeof(T) ), my_allocator( a )
    {
    }

    //! Destroy queue
    ~concurrent_queue();

    //! Enqueue an item at tail of queue.
    void push( const T& source ) {
        internal_push( &source );
    }

    //! Dequeue item from head of queue.
    /** Block until an item becomes available, and then dequeue it. */
    void pop( T& destination ) {
        internal_pop( &destination );
    }

    //! Enqueue an item at tail of queue if queue is not already full.
    /** Does not wait for queue to become not full.
        Returns true if item is pushed; false if queue was already full. */
    bool push_if_not_full( const T& source ) {
        return internal_push_if_not_full( &source );
    }

    //! Attempt to dequeue an item from head of queue.
    /** Does not wait for item to become available.
        Returns true if successful; false otherwise. */
    bool pop_if_present( T& destination ) {
        return internal_pop_if_present( &destination );
    }

    //! Return number of pushes minus number of pops.
    /** Note that the result can be negative if there are pops waiting for the 
        corresponding pushes.  The result can also exceed capacity() if there 
        are push operations in flight. */
    size_type size() const {return internal_size();}

    //! Equivalent to size()<=0.
    bool empty() const {return size()<=0;}

    //! Maximum number of allowed elements
    size_type capacity() const {
        return my_capacity;
    }

    //! Set the capacity
    /** Setting the capacity to 0 causes subsequent push_if_not_full operations to always fail,
        and subsequent push operations to block forever. */
    void set_capacity( size_type capacity ) {
        internal_set_capacity( capacity, sizeof(T) );
    }

    //! return allocator object
    allocator_type get_allocator() const { return this->my_allocator; }

    //! clear the queue. not thread-safe.
    void clear() ;

    typedef internal::concurrent_queue_iterator<concurrent_queue,T> iterator;
    typedef internal::concurrent_queue_iterator<concurrent_queue,const T> const_iterator;

    //------------------------------------------------------------------------
    // The iterators are intended only for debugging.  They are slow and not thread safe.
    //------------------------------------------------------------------------
    iterator begin() {return iterator(*this);}
    iterator end() {return iterator();}
    const_iterator begin() const {return const_iterator(*this);}
    const_iterator end() const {return const_iterator();}
    
    //! Copy constructor
    concurrent_queue( const concurrent_queue& src, const allocator_type &a = allocator_type()) : 
        concurrent_queue_base_v3( sizeof(T) ), my_allocator( a )
    {
        assign( src );
    }

    //! [begin,end) constructor
    template<typename InputIterator>
    concurrent_queue( InputIterator begin, InputIterator end, const allocator_type &a = allocator_type()) :
        concurrent_queue_base_v3( sizeof(T) ), my_allocator( a )
    {
        for( ; begin != end; ++begin )
            internal_push_if_not_full(&*begin);
    }
}; 

template<typename T, class A>
concurrent_queue<T,A>::~concurrent_queue() {
    clear();
    internal_finish_clear();
}

template<typename T, class A>
void concurrent_queue<T,A>::clear() {
    while( !empty() ) {
        T value;
        internal_pop_if_present(&value);
    }
}

} // namespace tbb

#endif /* __TBB_concurrent_queue_H */
