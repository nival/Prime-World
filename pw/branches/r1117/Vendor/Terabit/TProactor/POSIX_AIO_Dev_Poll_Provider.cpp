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
// $Id:  $

#include "TProactor/POSIX_AIO_Dev_Poll_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
#if defined (ACE_HAS_DEV_POLL)  

//#if defined (sun)

#include /**/ <sys/devpoll.h>

//#endif /*sun*/

#include "ace/Log_Msg.h"
#include "ace/Addr.h"
#include "ace/ACE.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX Dev_Poll -based Wait Strategy
 *
 *****************************************************************
 */
TRB_POSIX_AIO_Dev_Poll_Provider::~TRB_POSIX_AIO_Dev_Poll_Provider()
{
    fini ();
}

TRB_POSIX_AIO_Dev_Poll_Provider::TRB_POSIX_AIO_Dev_Poll_Provider 
  (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Emulation_Provider (config)
, mon_interest_   ()
, list_interest_  ()
, max_num_events_ (POLL_MAX_EVENTS)
, num_remain_     (0)
, cur_index_      (0)
, poll_fds_       ()
, fd_poller_      (ACE_INVALID_HANDLE)
, need_interrupt_ (false)
, interrupter_    (true)  // non blocking read side
{
    init();
}

int 
TRB_POSIX_AIO_Dev_Poll_Provider::init ()
{
    if (this->fd_poller_ == ACE_INVALID_HANDLE)
    {
        this->fd_poller_ = ACE_OS::open ("/dev/poll", O_RDWR);
    }

   if  (this->fd_poller_ == ACE_INVALID_HANDLE)
   {
       return -1;
   }

   // declare forever interest for notification pipe
   this->poll_fds_[0].fd = interrupter_.read_handle ();
   this->poll_fds_[0].events = POLLIN;
   this->poll_fds_[0].revents = 0;

   return this->modify_poll (0,1);

}

int 
TRB_POSIX_AIO_Dev_Poll_Provider::fini ()
{
    if (this->fd_poller_ != ACE_INVALID_HANDLE)
    {
        ACE_OS::close (this->fd_poller_);
    }

    this->fd_poller_ = ACE_INVALID_HANDLE;
    return 0;
}

int
TRB_POSIX_AIO_Dev_Poll_Provider::interrupt ()
{
    return this->interrupter_.notify();
}

// *****************************************************************
//  Declare interest
//  Return code :
//    1 - leader was interrupted
//    0 - OK, we do not have to interrupt leader
//   -1 - errors
// *****************************************************************
int
TRB_POSIX_AIO_Dev_Poll_Provider::declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                               int interest,
                                               int remain_mask)
{
    ACE_UNUSED_ARG (remain_mask);
    ACE_UNUSED_ARG (interest);
    {
        // lock access to the interest list
        Guard_Monitor guard_interest (this->mon_interest_);
        
        bool flgFree = info->get_link_interest()->is_free ();

        if (flgFree)
        {
            this->list_interest_.push_back (info);
        }
        
        if (!this->need_interrupt_)
        {
            return 0;
        }

        // request set was updated and
        // we have to interrupt, so reset interrupt flag 
        need_interrupt_ = false;
    }

    this->interrupt ();
    return 1;
}

int
TRB_POSIX_AIO_Dev_Poll_Provider::clear_interest (TRB_POSIX_AIO_FD_Info * info)
{
    // we can not call not modify poll,
    // dev/poll will block if ioctl is active
    ACE_UNUSED_ARG (info);
    return 0;
}

int
TRB_POSIX_AIO_Dev_Poll_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}

int
TRB_POSIX_AIO_Dev_Poll_Provider::get_ready_fd (ACE_Time_Value * wait_time,
                                           Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    if (fd != ACE_INVALID_HANDLE)
    {
        return fd;
    }

    fd = this->wait_for_ready_fd (wait_time);
    if (fd <= 0)
    {
        return ACE_INVALID_HANDLE;
    }

    fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}

ACE_HANDLE
TRB_POSIX_AIO_Dev_Poll_Provider::find_next_ready_fd (int & ready_mask,
                                                     int & remain_mask)
{
    while (this->cur_index_ < this->num_remain_)
    {
        int index = cur_index_;

        ++this->cur_index_;

        struct pollfd * pfd = & this->poll_fds_ [index];

        ready_mask = 0;
        remain_mask = 0;

        // do not report invalid fd, 
        // just remove it later
        if (ACE_BIT_ENABLED(pfd->revents, POLLNVAL))
        {
            pfd->events = POLLREMOVE;
            continue;
        }

        if (ACE_BIT_ENABLED(pfd->revents, 
                            (POLLIN|POLLHUP|POLLERR|POLLNVAL)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
        }

        if (ACE_BIT_ENABLED(pfd->revents, 
                            (POLLOUT|POLLHUP|POLLERR|POLLNVAL)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
        }


        ACE_ASSERT (ready_mask != 0);

        // do not report notification pipe 
        if (this->interrupter_.read_handle () == pfd->fd)
        {
            pfd->events = POLLIN;
            this->interrupter_.read ();
            continue;
        }


        pfd->events = POLLREMOVE;
        // better to remove all at once rather than call each time
        // modify_poll (index, index+1);

        return pfd->fd;
        
        //if (ACE_BIT_ENABLED(pfd->events, POLLIN))
        //{
        //    ACE_SET_BITS (remain_mask, TRB_POSIX_AIO_FD_Info::READ);
        //}
        //
        //if (ACE_BIT_ENABLED(pfd->events, POLLOUT))
        //{
        //    ACE_SET_BITS (remain_mask, TRB_POSIX_AIO_FD_Info::WRITE);
        //}
        //remain_mask &= ~ready_mask;
    }

    if (this->num_remain_ > 0)
    {
        modify_poll (0, num_remain_);
        this->num_remain_ = 0;
    }
    return ACE_INVALID_HANDLE;
}


int 
TRB_POSIX_AIO_Dev_Poll_Provider::modify_poll(int begin, int end)
{
    int len = end - begin;
    if (len <= 0)
    {
        return 0;
    }

    len *= sizeof(struct pollfd);

    // Change the events associated with the given file descriptor.
    int rc = ACE_OS::write (this->fd_poller_,
                            &this->poll_fds_[begin],
                            len);
    
    if (rc != len )
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT("TRB_POSIX_AIO_Dev_Poll_Strategy::modify poll ")
            ACE_LIB_TEXT("write to /dev/poll failed")),
            -1);
    }
    return 0;
}


int
TRB_POSIX_AIO_Dev_Poll_Provider::wait_for_ready_fd (ACE_Time_Value * wait_time)
{
    ACE_TRACE ("TRB_POSIX_AIO_Dev_Poll_Provider::wait_for_ready_fd");

    TRB_POSIX_AIO_FD_Info  * fd_info = 0;

    this->cur_index_ = 0;
    {
        // lock access to the interest list
        Guard_Monitor guard_interest (this->mon_interest_);

        int limit = this->max_num_events_; // - 1;

        for (;;)
        {
            if (this->cur_index_ >= limit )
            {
                modify_poll (0, this->cur_index_);
                this->cur_index_ = 0;
            }

            fd_info = this->list_interest_.pop_front();
            if (fd_info == 0)
            {
                break;
            }
         
            ACE_HANDLE fd = fd_info->get_handle();

            // This will lock-unlock fd guard mutex
            int interest = this->get_interest(fd);
            int events = 0;

            if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::READ))
            {
               events |= POLLIN;
            }

            if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::WRITE))
            {
               events |= POLLOUT;
            }
            
            //this->poll_fds_[cur_index_].fd = fd;
            //this->poll_fds_[cur_index_].events = POLLREMOVE;
            //this->poll_fds_[cur_index_].revents = 0;
            //++this->cur_index_ ;

            if (events != 0)
            {
                this->poll_fds_[cur_index_].fd = fd;
                this->poll_fds_[cur_index_].events = events;
                this->poll_fds_[cur_index_].revents = 0;
                ++cur_index_;
            }
        }

        modify_poll (0, this->cur_index_);
        this->cur_index_ = 0;

        this->need_interrupt_ = true;
    }

    long timeout = -1L;
  
    if (wait_time != 0 )
    {
        timeout =  ACE_static_cast (long, wait_time->msec ());
    }


    struct dvpoll dvp;

    dvp.dp_fds = this->poll_fds_;
    dvp.dp_nfds = this->max_num_events_;
    dvp.dp_timeout = timeout;  // Milliseconds

  
    // Poll for events
    this->num_remain_ = ACE_OS::ioctl (this->fd_poller_, DP_POLL, &dvp);
    this->cur_index_ = 0;

    if (this->num_remain_ < 0)
    {
        return this->num_remain_ = 0;
    }

    return this->num_remain_;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_DEV_POLL  */
#endif /* ACE_HAS_AIO_CALLS */
