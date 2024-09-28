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

#include "TProactor/POSIX_AIO_SUN_Port_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
#if defined (ACE_HAS_SUN_COMPLETION_PORTS) && defined (sun)

#include "ace/Log_Msg.h"
//#include "ace/Addr.h"
//#include "ace/ACE.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX SUN_Port -based Wait Strategy
 *
 *****************************************************************
 */
TRB_POSIX_AIO_SUN_Port_Provider::~TRB_POSIX_AIO_SUN_Port_Provider()
{
    fini ();
}

TRB_POSIX_AIO_SUN_Port_Provider::TRB_POSIX_AIO_SUN_Port_Provider
  (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Emulation_Provider (config)
, fd_poller_      (ACE_INVALID_HANDLE)
, events_         ()
, max_num_events_ (sizeof(events_)/sizeof(events_[0]))
, num_remain_     (0)
, cur_index_      (0)
{
    init ();
}

int
TRB_POSIX_AIO_SUN_Port_Provider::init ()
{
    if (this->fd_poller_ == ACE_INVALID_HANDLE)
    {
        this->fd_poller_ = ::port_create ();
    }
    return (this->fd_poller_ != ACE_INVALID_HANDLE)? 0 : -1;
}

int
TRB_POSIX_AIO_SUN_Port_Provider::fini ()
{
    if (this->fd_poller_ != ACE_INVALID_HANDLE)
    {
        ACE_OS::close (this->fd_poller_);
    }

    this->fd_poller_ = ACE_INVALID_HANDLE;
    return 0;
}


int
TRB_POSIX_AIO_SUN_Port_Provider::interrupt()
{
    int events = 0;
    void * user_data = 0;
    int rc = ::port_send (this->fd_poller_, events, user_data);
    return rc;
}
// *****************************************************************
//  Declare interest
//  Return code :
//    1 - leader was interrupted
//    0 - OK, we do not have to interrupt leader
//   -1 - errors
// *****************************************************************
int
TRB_POSIX_AIO_SUN_Port_Provider::declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                                   int interest,
                                                   int remain_mask)
{
    ACE_UNUSED_ARG (remain_mask);

    int fd = info->get_handle ();

    int events = 0;

    if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::READ))
    {
        events |= POLLIN;
    }

    if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::WRITE))
    {
        events |= POLLOUT;
    }

    int rc = ::port_associate (this->fd_poller_, PORT_SOURCE_FD, fd, events, 0);

    if (rc != 0)
    {
        ACE_ERROR ((LM_ERROR,
            ACE_LIB_TEXT("TRB_POSIX_AIO_SUN_Port_Provider::declare_interest: ")
            ACE_LIB_TEXT("fd=%d mask=%x %p\n"),
            fd,
            remain_mask,
            ACE_LIB_TEXT("port_associate failed")));
    }

    return rc;
}

int
TRB_POSIX_AIO_SUN_Port_Provider::clear_interest  (TRB_POSIX_AIO_FD_Info * info)
{
    int fd = info->get_handle ();

    int rc = ::port_dissociate (this->fd_poller_, PORT_SOURCE_FD, fd);

//  Errors are OK here
//    if (rc != 0)
//    {
//        ACE_ERROR ((LM_ERROR,
//            ACE_LIB_TEXT("TRB_POSIX_AIO_SUN_Port_Provider::clear_interest: ")
//            ACE_LIB_TEXT("fd=%d %p\n"),
//            fd,
//            ACE_LIB_TEXT("port_dissociate failed")));
//    }
    return rc;
}


int
TRB_POSIX_AIO_SUN_Port_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    //
    ACE_UNUSED_ARG (leader_guard);
    ACE_UNUSED_ARG (ready_mask);
    ACE_UNUSED_ARG (remain_mask);
    return ACE_INVALID_HANDLE;
}

int
TRB_POSIX_AIO_SUN_Port_Provider::get_ready_fd (ACE_Time_Value * wait_time,
                                           Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    ACE_UNUSED_ARG (leader_guard);

    // SunOS completion ports don't requires leadership
    // if this is not , fix later
    //Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    timespec_t   timeout;
    timespec_t * ptimeout = 0;

    if (wait_time != 0 )
    {
        timeout =  wait_time->operator timespec_t ();
        ptimeout = &timeout;
    }


    port_event_t  event;

    int rc = ::port_get (this->fd_poller_,
                         &event,
                         ptimeout);

    if (rc < 0)
    {
        return ACE_INVALID_HANDLE;
    }

    if (event.portev_source != PORT_SOURCE_FD)
    {
        ACE_ASSERT ( event.portev_source == PORT_SOURCE_USER);
        return ACE_INVALID_HANDLE;
    }

    int fd = event.portev_object;

    ready_mask = 0;
    remain_mask = 0;

    // do not report invalid fd, 
    if (ACE_BIT_ENABLED(event.portev_events, POLLNVAL))
    {
        return ACE_INVALID_HANDLE;
    }

    if (ACE_BIT_ENABLED(event.portev_events,
                            (POLLIN|POLLHUP|POLLERR|POLLNVAL)))
    {
        ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
    }

    if (ACE_BIT_ENABLED(event.portev_events,
                        (POLLOUT|POLLHUP|POLLERR|POLLNVAL)))
    {
        ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
    }

    //TRB_POSIX_AIO_FD_Info * fd_info =
    //    this->update_fd_info(fd, ready_mask, 0);
    //
    //if (fd_info == 0)
    //{
    //    return ACE_INVALID_HANDLE;
    //}

    return fd;
}

//--------------------------------------------------------------------------
// version with port_getn
//-------------------------------------------------------------------------
//int
//TRB_POSIX_AIO_SUN_Port_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
//                                           int & ready_mask,
//                                           int & remain_mask)
//{
//    //
//    // only one thread can take leadership
//    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);
//
//    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
//    return fd;
//
//}
//
//ACE_HANDLE
//TRB_POSIX_AIO_SUN_Port_Provider::find_next_ready_fd (
//                                           int & ready_mask,
//                                           int & remain_mask)
//{
//    ready_mask = 0;
//    remain_mask = 0;
//
//    while (this->cur_index_ < this->num_remain_)
//    {
//
//        port_event_t & event = this->events_ [this->cur_index_];
//        ++this->cur_index_;
//
//        if (event.portev_source != PORT_SOURCE_FD)
//        {
//            ACE_ASSERT ( event.portev_source == PORT_SOURCE_USER);
//            continue;
//        }
//
//        if (ACE_BIT_ENABLED(event.portev_events, POLLNVAL))
//        {
//            continue;
//        }
//
//
//        if (ACE_BIT_ENABLED(event.portev_events,
//                            (POLLIN|POLLHUP|POLLERR|POLLNVAL)))
//        {
//            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
//        }
//
//        if (ACE_BIT_ENABLED(event.portev_events,
//                        (POLLOUT|POLLHUP|POLLERR|POLLNVAL)))
//        {
//            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
//        }
//
//        if (ready_mask == 0)
//        {
//            continue;
//        }
//
//        int fd = event.portev_object;
//        return fd;
//        //TRB_POSIX_AIO_FD_Info * fd_info =
//        //    this->update_fd_info(fd, ready_mask, 0);
//        //
//        //if (fd_info == 0)
//        //{
//        //    return ACE_INVALID_HANDLE;
//        //}
//
//    }
//    return ACE_INVALID_HANDLE;
//}
//
//int
//TRB_POSIX_AIO_SUN_Port_Provider::wait_for_ready_fd (ACE_Time_Value * wait_time)
//{
//    timespec_t   timeout;
//    timespec_t * ptimeout = 0;
//
//    if (wait_time != 0 )
//    {
//        timeout =  wait_time->operator timespec_t ();
//        ptimeout = &timeout;
//    }
//
//    this->cur_index_  = 0;
//    this->num_remain_ = 1;
//
//    // Poll for events  port_getn had problems
//    int rc = ::port_getn (this->fd_poller_,
//                          this->events_,
//                          this->max_num_events_,
//                          &this->num_remain_,
//                          ptimeout);
//
//
//    if (rc < 0)
//        this->num_remain_ = 0;
//
//    return this->num_remain_;
//}
//
//
//int
//TRB_POSIX_AIO_SUN_Port_Provider::get_ready_fd (ACE_Time_Value * wait_time,
//                                           Guard_Monitor &  leader_guard,
//                                           int & ready_mask,
//                                           int & remain_mask)
//{
//    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);
//
//    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
//    if (fd != ACE_INVALID_HANDLE)
//    {
//        return fd;
//    }
//
//    this->wait_for_ready_fd (wait_time);
//    
//    fd = find_next_ready_fd (ready_mask, remain_mask);
//    return fd;
//}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_SUN_COMPLETION_PORTS */
#endif /* ACE_HAS_AIO_CALLS */
