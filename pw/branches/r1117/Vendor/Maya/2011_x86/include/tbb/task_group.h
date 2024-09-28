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

#ifndef __TBB_task_group_H
#define __TBB_task_group_H

#include "task.h"
#include <exception>

namespace tbb {

template<typename F>
class task_handle {
    F my_func;

public:
    task_handle( const F& f ) : my_func(f) {}

    void operator()() { my_func(); }
};

enum task_group_status {
    not_complete,
    complete,
    canceled
};

namespace internal {

// Suppress gratuitous warnings from icc 11.0 when lambda expressions are used in instances of function_task.
//#pragma warning(disable: 588)

template<typename F>
class function_task : public task {
    F my_func;
    /*override*/ task* execute() {
        my_func();
        return NULL;
    }
public:
    function_task( const F& f ) : my_func(f) {}
};

template<typename F>
class task_handle_task : public task {
    task_handle<F>& my_handle;
    /*override*/ task* execute() {
        my_handle();
        return NULL;
    }
public:
    task_handle_task( task_handle<F>& h ) : my_handle(h) {}
};

class task_group_base : internal::no_copy {
protected:
    empty_task* my_root;
    task_group_context my_context;

    task& owner () { return *my_root; }

    template<typename F>
    task_group_status internal_run_and_wait( F& f ) {
        try {
            if ( !my_context.is_group_execution_cancelled() )
                f();
        } catch ( ... ) {
            my_context.register_pending_exception();
        }
        return wait();
    }

    template<typename F, typename Task>
    void internal_run( F& f ) {
        owner().spawn( *new( owner().allocate_additional_child_of(*my_root) ) Task(f) );
    }

public:
    task_group_base( uintptr_t traits = 0 )
        : my_context(task_group_context::bound, task_group_context::default_traits | traits)
    {
        my_root = new( task::allocate_root(my_context) ) empty_task;
        my_root->set_ref_count(1);
    }

    template<typename F>
    void run( task_handle<F>& h ) {
        internal_run< task_handle<F>, internal::task_handle_task<F> >( h );
    }

    task_group_status wait() {
        try {
            owner().prefix().owner->wait_for_all( *my_root, NULL );
        } catch ( ... ) {
            my_context.reset();
            throw;
        }
        if ( my_context.is_group_execution_cancelled() ) {
            my_context.reset();
            return canceled;
        }
        return complete;
    }

    bool is_canceling() {
        return my_context.is_group_execution_cancelled();
    }

    void cancel() {
        my_context.cancel_group_execution();
    }
}; // class task_group_base

} // namespace internal

class task_group : public internal::task_group_base {
public:
    task_group () : task_group_base( task_group_context::concurrent_wait ) {}

    ~task_group() try {
        __TBB_ASSERT( my_root->ref_count() != 0, NULL );
        if( my_root->ref_count() > 1 )
            my_root->wait_for_all();
        owner().destroy(*my_root);
    }
    catch (...) {
        owner().destroy(*my_root);
        throw;
    }

#if __SUNPRO_CC
    template<typename F>
    void run( task_handle<F>& h ) {
        internal_run< task_handle<F>, internal::task_handle_task<F> >( h );
    }
#else
    using task_group_base::run;
#endif

    template<typename F>
    void run( const F& f ) {
        internal_run< const F, internal::function_task<F> >( f );
    }

    template<typename F>
    task_group_status run_and_wait( const F& f ) {
        return internal_run_and_wait<const F>( f );
    }

    template<typename F>
    task_group_status run_and_wait( task_handle<F>& h ) {
      return internal_run_and_wait< task_handle<F> >( h );
    }
}; // class task_group

class missing_wait : public std::exception {
public:
    /*override*/ 
    const char* what() const throw() { return "wait() was not called on the structured_task_group"; }
};

class structured_task_group : public internal::task_group_base {
public:
    ~structured_task_group() {
        if( my_root->ref_count() > 1 ) {
            bool stack_unwinding_in_progress = std::uncaught_exception();
            // Always attempt to do proper cleanup to avoid inevitable memory corruption 
            // in case of missing wait (for the sake of better testability & debuggability)
            if ( !is_canceling() )
                cancel();
            my_root->wait_for_all();
            owner().destroy(*my_root);
            if ( !stack_unwinding_in_progress )
                throw missing_wait();
        }
        else
            owner().destroy(*my_root);
    }

    template<typename F>
    task_group_status run_and_wait ( task_handle<F>& h ) {
        return internal_run_and_wait< task_handle<F> >( h );
    }

    task_group_status wait() {
        __TBB_ASSERT ( my_root->ref_count() != 0, "wait() can be called only once during the structured_task_group lifetime" );
        return task_group_base::wait();
    }
}; // class structured_task_group

inline 
bool is_current_task_group_canceling() {
    return task::self().is_cancelled();
}

template<class F>
task_handle<F> make_task( const F& f ) {
    return task_handle<F>( f );
}

} // namespace tbb

#endif /* __TBB_task_group_H */
