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

#ifndef __TBB_task_scheduler_observer_H
#define __TBB_task_scheduler_observer_H

#include "atomic.h"

#if __TBB_SCHEDULER_OBSERVER

namespace tbb {

namespace internal {

class observer_proxy;

class task_scheduler_observer_v3 {
    friend class observer_proxy;
    observer_proxy* my_proxy;
    atomic<intptr> my_busy_count;
public:
    //! Enable or disable observation
    void __TBB_EXPORTED_METHOD observe( bool state=true );

    //! True if observation is enables; false otherwise.
    bool is_observing() const {return my_proxy!=NULL;}

    //! Construct observer with observation disabled.
    task_scheduler_observer_v3() : my_proxy(NULL) {my_busy_count=0;}

    //! Called by thread before first steal since observation became enabled
    virtual void on_scheduler_entry( bool /*is_worker*/ ) {} 

    //! Called by thread when it no longer takes part in task stealing.
    virtual void on_scheduler_exit( bool /*is_worker*/ ) {}

    //! Destructor
    virtual ~task_scheduler_observer_v3() {observe(false);}
};

} // namespace internal

typedef internal::task_scheduler_observer_v3 task_scheduler_observer;

} // namespace tbb

#endif /* __TBB_SCHEDULER_OBSERVER */

#endif /* __TBB_task_scheduler_observer_H */
