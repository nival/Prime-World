/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

/* -*- C++ -*- */
// $Id: $

#include "TProactor/POSIX_AIO_Dispatcher.h"

#if defined (ACE_HAS_AIO_CALLS)  || defined(ACE_HAS_AIO_EMULATION)

#include "ace/Log_Msg.h"
#include "ace/Auto_IncDec_T.h"

#include "TProactor/POSIX_AIO_Processor.h"
#include "TProactor/POSIX_AIO_Config.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace  {

class Thread_Info_List;

class Thread_Info
{
private:

  Thread_Info_List              *list_;
  mutable LinkS_T<Thread_Info>   link_;
  TRB_POSIX_AIO_Dispatcher      *dispatcher_;
  TRB_POSIX_Asynch_Result_Queue *completion_queue_;
  // prohibit copy and assignment
  Thread_Info (const Thread_Info& other);
  Thread_Info& operator=(const Thread_Info& other);

public:
  Thread_Info (Thread_Info_List              *list,
               TRB_POSIX_AIO_Dispatcher      *dispatcher,
               TRB_POSIX_Asynch_Result_Queue *completion_queue);

  ~Thread_Info ();

  // get methods
  LinkS_T<Thread_Info>          *link () const { return &this->link_; }
  TRB_POSIX_AIO_Dispatcher      *dispatcher () const { return this->dispatcher_; }
  TRB_POSIX_Asynch_Result_Queue *completion_queue () { return this->completion_queue_; }
  
  // set methods
  void completion_queue (TRB_POSIX_Asynch_Result_Queue *queue) 
    {
      this->completion_queue_ = queue;
    }

  // Adapter-convertor object to link for intrusive list
  class To_Link 
  {
  public :
    LinkS_T <Thread_Info> * 
    operator () (const  Thread_Info *x)  const 
    {
      return x->link();
    }
  };
};

class Thread_Info_List :
  public Single_List_T<Thread_Info, Thread_Info::To_Link> 
{
public:
  ~Thread_Info_List ()
    {
      ACE_ASSERT (this->empty ());
    }
  
  Thread_Info *find_info(TRB_POSIX_AIO_Dispatcher *disp)
    {
      iterator it1 = this->begin();
      iterator it2 = this->end();

      for (; it1 != it2 ; ++it1)
      {
        if ((*it1)->dispatcher() == disp)
          return *it1;
      }
      return 0;
    }

  TRB_POSIX_Asynch_Result_Queue  *find_queue(TRB_POSIX_AIO_Dispatcher *disp)
    {
       Thread_Info *info = find_info(disp);
       if (info == 0)
         return 0;

       return info->completion_queue();
    }
      

};

Thread_Info::Thread_Info (Thread_Info_List              *list,
                          TRB_POSIX_AIO_Dispatcher      *dispatcher,
                          TRB_POSIX_Asynch_Result_Queue *completion_queue)
: list_             (list)
, link_             ()
, dispatcher_       (dispatcher)
, completion_queue_ (completion_queue)
{
  this->list_->push_front (this);
}

Thread_Info::~Thread_Info()
{
  Thread_Info *info = list_->pop_front ();
  ACE_ASSERT (info == this);
}

} // close namespace

ACE_TSS<Thread_Info_List>  tss_info_list;

// ********************************************************************
//
// ********************************************************************

TRB_POSIX_AIO_Dispatcher::TRB_POSIX_AIO_Dispatcher 
    (const TRB_POSIX_AIO_Config & config1,
     const TRB_POSIX_AIO_Config & config2)
: config1_               (config1)
, config2_               (config2)
, thr_manager_           ()
, completion_monitor_    ()
, main_completion_queue_ ()
, shared_processor_      (0)
, dedicated_processors_  ()
, num_waiting_threads_   (0)
{
    ;
}

TRB_POSIX_AIO_Dispatcher::~TRB_POSIX_AIO_Dispatcher (void)
{
    this->close ();
}


int
TRB_POSIX_AIO_Dispatcher::add_processor(TRB_POSIX_AIO_Processor * processor)
{
    Guard_Monitor guard (this->completion_monitor_, true);

    if (processor == 0)
    {
        return 0;
    }

    if (!processor->is_dedicated ())
    {
        if (this->shared_processor_ != 0 )
        {
            // it is enabled only one shared processor
            return -1;
        }
        this->shared_processor_ = processor;
    }
    else 
    {
        // dedicated processor
        this->dedicated_processors_.push_back (processor);
    }
    return 0;
}

int 
TRB_POSIX_AIO_Dispatcher::close ()
{
    Guard_Monitor guard (this->completion_monitor_, true);

    ACE_ASSERT (this->num_waiting_threads_ == 0);

    this->shared_processor_ = 0;
    this->dedicated_processors_.clear ();
    this->clear_main_queue (guard);
    return 0;
}

void
TRB_POSIX_AIO_Dispatcher::add_completion (TRB_POSIX_Asynch_Result *result)
{
    TRB_POSIX_Asynch_Result_Queue *local_queue = 
        tss_info_list->find_queue (this);

    if (local_queue != 0)
    {
        local_queue->push_back (result);
        return;
    }

    this->add_main_completion (result);
}

void
TRB_POSIX_AIO_Dispatcher::add_completions 
            (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_Queue *local_queue = 
        tss_info_list->find_queue (this);

    if (local_queue != 0)
    {
        local_queue->splice (completed_queue);
        return;
    }

    this->add_main_completions (completed_queue);
}

void
TRB_POSIX_AIO_Dispatcher::add_main_completion (TRB_POSIX_Asynch_Result *result)
{
    {
        Guard_Monitor guard (this->completion_monitor_, true);
        this->main_completion_queue_.push_back (result);

        if (num_waiting_threads_ == 0)
        {
            return;   // no waiting threads in completion dispatcher
        }

        if (this->shared_processor_ == 0)
        {
            // there are only dedicated processors, 
            // completion dispatcher waits on the queue
            this->completion_monitor_.signal ();
            return;
        }
    }   // release completion_monitor_

    this->shared_processor_->interrupt ();
}

void
TRB_POSIX_AIO_Dispatcher::add_main_completions 
            (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    {
        Guard_Monitor guard (this->completion_monitor_, true);
        this->main_completion_queue_.splice (completed_queue);

        if (num_waiting_threads_ == 0)
        {
            return;   // no waiting threads in completion dispatcher
        }

        if (this->shared_processor_ == 0)
        {
            // there are only dedicated processors, 
            // completion dispatcher waits on the queue
            this->completion_monitor_.signal ();
            return;
        }
    }   // release completion_monitor_

    this->shared_processor_->interrupt ();
}

void
TRB_POSIX_AIO_Dispatcher::wakeup ()
{
    {
        Guard_Monitor guard (this->completion_monitor_, true);

        if (num_waiting_threads_ == 0)
        {
            return;   // no waiting threads in completion dispatcher
        }

        if (this->shared_processor_ == 0)
        {
            // there are only dedicated processors, 
            // completion dispatcher waits on the queue
            this->completion_monitor_.signal ();
            return;
        }
    }   // release completion_monitor_

    this->shared_processor_->interrupt ();
}


int 
TRB_POSIX_AIO_Dispatcher::handle_events (ACE_Time_Value *wait_time)
{
    //Auto decrement wait time
    ACE_Countdown_Time countdown (wait_time);

    if (this->shared_processor_ != 0)
    {
        return this->handle_events_s(wait_time);
    }
   
    return handle_events_d(wait_time);
}

int 
TRB_POSIX_AIO_Dispatcher::handle_events_d (ACE_Time_Value *wait_time)
{
    TRB_POSIX_Asynch_Result_Queue tmp_queue;

    Thread_Info_List *info_list = tss_info_list;

    Thread_Info info (info_list, this, &tmp_queue);

    int num_processed = 0;

    for (int i = 0; ; ++i)
    {
        poll_dedicated_processors (tmp_queue);
        num_processed += process_completion_queue(tmp_queue);
    
        {
            Guard_Monitor guard (this->completion_monitor_, true);

            if (this->main_completion_queue_.size () != 0)
            {
                num_processed += this->process_main_queue (guard);
            }

            if (i == 0 && num_processed == 0)
            {
                ACE_Auto_IncDec<int> inc_dec_wait_threads (this->num_waiting_threads_);
                guard.wait(wait_time, false);
            }
 
            if (main_completion_queue_.size() != 0)
            {
                continue;
            }
        }

        if (tmp_queue.size () == 0)
        {
            break;
        }
    }
    
    return num_processed;
}


int 
TRB_POSIX_AIO_Dispatcher::handle_events_s (ACE_Time_Value *wait_time)
{
    // avoid access to TSS object through thread local storage 
    TRB_POSIX_Asynch_Result_Queue tmp_queue;

    Thread_Info_List *info_list = tss_info_list;

    Thread_Info info (info_list, this, &tmp_queue);

    int     num_processed = 0;
    size_t  num_dedicated = this->dedicated_processors_.size();

    bool  flgContinue = true;
 
    for (int i = 0; flgContinue && i < 3; ++i)
    {
        {
            Guard_Monitor guard (this->completion_monitor_, true);
        
            if (this->main_completion_queue_.size() != 0)
            {
                num_processed += this->process_main_queue (guard);
            }
            
            if (i == 0 && num_processed == 0)
            {
                ACE_Auto_IncDec<int> inc_dec_wait_threads 
                                      (this->num_waiting_threads_);
                Save_Guard save_guard (guard, Save_Guard::RELEASE);

                this->shared_processor_->get_completed_aio (wait_time, 
                                                            tmp_queue);
            }
            
            flgContinue = (this->main_completion_queue_.size() != 0);
        }
                
        if (num_dedicated != 0)
        {
            poll_dedicated_processors (tmp_queue);
        }
        num_processed += process_completion_queue(tmp_queue);
        
        flgContinue |= (tmp_queue.size() != 0);
    }

    if (!flgContinue)
    { 
        return num_processed;
    }
    
    {
        Guard_Monitor guard (this->completion_monitor_, true);
        this->main_completion_queue_.splice (tmp_queue);

        if (this->num_waiting_threads_ == 0)
        {
            return num_processed;   // no waiting threads in dispatcher
        }
    }
    
    this->shared_processor_->interrupt ();
    
    return num_processed;
}

void 
TRB_POSIX_AIO_Dispatcher::poll_dedicated_processors (
                          TRB_POSIX_Asynch_Result_Queue& tmp_queue)
{
    ProcessorVector::iterator it1 = this->dedicated_processors_.begin();
    ProcessorVector::iterator it2 = this->dedicated_processors_.end ();

    for (;it1 != it2 ; ++it1)
    {
        ACE_Time_Value tv(ACE_Time_Value::zero);

        (*it1)->get_completed_aio (&tv, tmp_queue);

    }
}

int 
TRB_POSIX_AIO_Dispatcher::clear_main_queue (Guard_Monitor & guard)
{
    int num_processed = 0;

    Save_Guard save_guard1 (guard, Save_Guard::ACQUIRE);

    for (; ;++num_processed)
    {
        TRB_POSIX_Asynch_Result* result = 
            this->main_completion_queue_.pop_front();

        if (result == 0)
        {
            break;
        }

        Save_Guard save_guard2 (guard, Save_Guard::RELEASE);
        TRB_POSIX_Asynch_Result::release (result);
    }
        
    return num_processed;
}

int 
TRB_POSIX_AIO_Dispatcher::process_main_queue (Guard_Monitor & guard)
{
    int num_processed = 0;

    Save_Guard save_guard1 (guard, Save_Guard::ACQUIRE);

    size_t  max_num = main_completion_queue_.size();

    for (; max_num > 0 ; --max_num, ++num_processed)
    {
        TRB_POSIX_Asynch_Result* result = 
            this->main_completion_queue_.pop_front();

        if (result == 0)
        {
            break;
        }

        Save_Guard save_guard2 (guard, Save_Guard::RELEASE);
        result->dispatch ();
    }
        
    return num_processed;
}

int 
TRB_POSIX_AIO_Dispatcher::process_completion_queue 
    (TRB_POSIX_Asynch_Result_Queue  & tmp_queue)
{
    int num_processed = 0;

    size_t  max_num = tmp_queue.size();

    for (; max_num > 0 ; --max_num, ++num_processed)
    {
        TRB_POSIX_Asynch_Result* result = tmp_queue.pop_front();

        if (result == 0)
        {
            break;
        }
        result->dispatch ();
    }
        
    return num_processed;
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
