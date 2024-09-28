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

#ifndef __TBB_task_scheduler_init_H
#define __TBB_task_scheduler_init_H

#include "tbb_stddef.h"

namespace tbb {

typedef std::size_t stack_size_type;

//! @cond INTERNAL
namespace internal {
    //! Internal to library. Should not be used by clients.
    /** @ingroup task_scheduling */
    class scheduler;
} // namespace internal
//! @endcond

//! Class representing reference to tbb scheduler.
/** A thread must construct a task_scheduler_init, and keep it alive,
    during the time that it uses the services of class task.
    @ingroup task_scheduling */
class task_scheduler_init: internal::no_copy {
    /** NULL if not currently initialized. */
    internal::scheduler* my_scheduler;
public:

    //! Typedef for number of threads that is automatic.
    static const int automatic = -1;

    //! Argument to initialize() or constructor that causes initialization to be deferred.
    static const int deferred = -2;

    //! Ensure that scheduler exists for this thread
    /** A value of -1 lets tbb decide on the number of threads, which is typically 
        the number of hardware threads. For production code, the default value of -1 
        should be used, particularly if the client code is mixed with third party clients 
        that might also use tbb.

        The number_of_threads is ignored if any other task_scheduler_inits 
        currently exist.  A thread may construct multiple task_scheduler_inits.  
        Doing so does no harm because the underlying scheduler is reference counted. */
    void __TBB_EXPORTED_METHOD initialize( int number_of_threads=automatic );

    //! The overloaded method with stack size parameter
    /** Overloading is necessary to preserve ABI compatibility */
    void __TBB_EXPORTED_METHOD initialize( int number_of_threads, stack_size_type thread_stack_size );

    //! Inverse of method initialize.
    void __TBB_EXPORTED_METHOD terminate();

    //! Shorthand for default constructor followed by call to intialize(number_of_threads).
    task_scheduler_init( int number_of_threads=automatic, stack_size_type thread_stack_size=0 ) : my_scheduler(NULL)  {
        initialize( number_of_threads, thread_stack_size );
    }

    //! Destroy scheduler for this thread if thread has no other live task_scheduler_inits.
    ~task_scheduler_init() {
        if( my_scheduler ) 
            terminate();
        internal::poison_pointer( my_scheduler );
    }
    //! Returns the number of threads tbb scheduler would create if initialized by default.
    /** Result returned by this method does not depend on whether the scheduler 
        has already been initialized.
        
        Because tbb 2.0 does not support blocking tasks yet, you may use this method
        to boost the number of threads in the tbb's internal pool, if your tasks are 
        doing I/O operations. The optimal number of additional threads depends on how
        much time your tasks spend in the blocked state. */
    static int __TBB_EXPORTED_FUNC default_num_threads ();

    //! Returns true if scheduler is active (initialized); false otherwise
    bool is_active() const { return my_scheduler != NULL; }
};

} // namespace tbb

#endif /* __TBB_task_scheduler_init_H */
