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

#ifndef __TBB_pipeline_H 
#define __TBB_pipeline_H 

#include "atomic.h"
#include "task.h"
#include <cstddef>

namespace tbb {

class pipeline;
class filter;

//! @cond INTERNAL
namespace internal {

// The argument for PIPELINE_VERSION should be an integer between 2 and 9
#define __TBB_PIPELINE_VERSION(x) (unsigned char)(x-2)<<1

typedef unsigned long Token;
typedef long tokendiff_t;
class stage_task;
class ordered_buffer;

} // namespace internal
//! @endcond

//! A stage in a pipeline.
/** @ingroup algorithms */
class filter: internal::no_copy {
private:
    //! Value used to mark "not in pipeline"
    static filter* not_in_pipeline() {return reinterpret_cast<filter*>(internal::intptr(-1));}
    
    //! The lowest bit 0 is for parallel vs. serial
    static const unsigned char filter_is_serial = 0x1; 

    //! 4th bit distinguish ordered vs unordered
    // The bit was not set for parallel filters in TBB 2.1 and earlier,
    // but is_ordered() function always treats parallel filters as out of order
    static const unsigned char filter_is_out_of_order = 0x1<<4;  

    static const unsigned char current_version = __TBB_PIPELINE_VERSION(4);
    static const unsigned char version_mask = 0x7<<1; // bits 1-3 are for version
public:
    enum mode {
        //! processes multiple items in parallel and in no particular order
        parallel = current_version | filter_is_out_of_order, 
        //! processes items one at a time; all such filters process items in the same order
        serial_in_order = current_version | filter_is_serial,
        //! processes items one at a time and in no particular order
        serial_out_of_order = current_version | filter_is_serial | filter_is_out_of_order,
        //! @deprecated use serial_in_order instead
        serial = serial_in_order
    };
protected:
    filter( bool is_serial_ ) : 
        next_filter_in_pipeline(not_in_pipeline()),
        input_buffer(NULL),
        my_filter_mode(static_cast<unsigned char>(is_serial_ ? serial : parallel)),
        prev_filter_in_pipeline(not_in_pipeline()),
        my_pipeline(NULL)
    {}
    
    filter( mode filter_mode ) :
        next_filter_in_pipeline(not_in_pipeline()),
        input_buffer(NULL),
        my_filter_mode(static_cast<unsigned char>(filter_mode)),
        prev_filter_in_pipeline(not_in_pipeline()),
        my_pipeline(NULL)
    {}

public:
    //! True if filter is serial.
    bool is_serial() const {
        return bool( my_filter_mode & filter_is_serial );
    }  
    
    // ! True if filter must receive stream in order.
    bool is_ordered() const {
        return (my_filter_mode & (filter_is_out_of_order|filter_is_serial))==filter_is_serial;
    }

    //! Operate on an item from the input stream, and return item for output stream.
    /** Returns NULL if filter is a sink. */
    virtual void* operator()( void* item ) = 0;

    //! Destroy filter.  
    /** If the filter was added to a pipeline, the pipeline must be destroyed first. */
    virtual __TBB_EXPORTED_METHOD ~filter();

#if __TBB_EXCEPTIONS
    //! Destroys item if pipeline is cancelled
    /** Required to prevent memory leaks 
        Note it can be called concurrently even for serial filters.*/
    virtual void finalize( void* /*item*/ ) {};
#endif

private:
    //! Pointer to next filter in the pipeline.
    filter* next_filter_in_pipeline;

    //! Input buffer for filter that requires serial input; NULL otherwise. */
    internal::ordered_buffer* input_buffer;

    friend class internal::stage_task;
    friend class pipeline;

    //! Internal storage for is_serial()
    const unsigned char my_filter_mode;

    //! Pointer to previous filter in the pipeline.
    filter* prev_filter_in_pipeline;

    //! Pointer to the pipeline
    pipeline* my_pipeline;
};

//! A processing pipeling that applies filters to items.
/** @ingroup algorithms */
class pipeline {
public:
    //! Construct empty pipeline.
    __TBB_EXPORTED_METHOD pipeline();

    /** Though the current implementation declares the destructor virtual, do not rely on this 
        detail.  The virtualness is deprecated and may disappear in future versions of TBB. */
    virtual __TBB_EXPORTED_METHOD ~pipeline();

    //! Add filter to end of pipeline.
    void __TBB_EXPORTED_METHOD add_filter( filter& filter_ );

    //! Run the pipeline to completion.
    void __TBB_EXPORTED_METHOD run( size_t max_number_of_live_tokens );

#if __TBB_EXCEPTIONS
    //! Run the pipeline to completion with user-supplied context
    void __TBB_EXPORTED_METHOD run( size_t max_number_of_live_tokens, tbb::task_group_context& context );
#endif

    //! Remove all filters from the pipeline
    void __TBB_EXPORTED_METHOD clear();

private:
    friend class internal::stage_task;
    friend class filter;

    //! Pointer to first filter in the pipeline.
    filter* filter_list;

    //! Pointer to location where address of next filter to be added should be stored.
    filter* filter_end;

    //! task who's reference count is used to determine when all stages are done.
    empty_task* end_counter;

    //! Number of idle tokens waiting for input stage.
    atomic<internal::Token> input_tokens;

    //! Number of tokens created so far.
    internal::Token token_counter;

    //! False until fetch_input returns NULL.
    bool end_of_input;

    //! Remove filter from pipeline.
    void remove_filter( filter& filter_ );

    //! Not used, but retained to satisfy old export files.
    void __TBB_EXPORTED_METHOD inject_token( task& self );

#if __TBB_EXCEPTIONS
    //! Does clean up if pipeline is cancelled or exception occured
    void clear_filters();
#endif
};

} // tbb

#endif /* __TBB_pipeline_H */
