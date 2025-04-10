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

//=============================================================================
/**
 *  @file    TRB_POSIX_AIO_Dev_Poll_Strategy.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_DEV_POLL_PROVIDER_H 
#define TRB_POSIX_AIO_DEV_POLL_PROVIDER_H 

#include "TProactor/POSIX_AIO_Emulation_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
#if defined (ACE_HAS_DEV_POLL)

#include "ace/os_include/os_poll.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class TRB_POSIX_AIO_Dev_Poll_Provider
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_Dev_Poll_Provider : 
  public TRB_POSIX_AIO_Emulation_Provider
{
    enum { POLL_MAX_EVENTS = 256 };

public:

    TRB_POSIX_AIO_Dev_Poll_Provider (const TRB_POSIX_AIO_Config & config);
    virtual ~TRB_POSIX_AIO_Dev_Poll_Provider();

    virtual int init ();
    virtual int fini ();
    virtual int declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                  int interest,
                                  int remain_mask);

    virtual int clear_interest (TRB_POSIX_AIO_FD_Info * info);

    virtual int get_ready_fd (ACE_Time_Value * wait_time,
                              Guard_Monitor &  leader_guard,
                              int & ready_mask,
                              int & remain_mask);

    virtual int poll_ready_fd (Guard_Monitor &  leader_guard,
                              int & ready_mask,
                              int & remain_mask);
    virtual int interrupt ();
  

private:

    int        modify_poll(int begin, int end);
    int        wait_for_ready_fd (ACE_Time_Value * wait_time);
    ACE_HANDLE find_next_ready_fd (int & ready_mask, int & remain_mask);


   
    /// mutex to protect access to interest list
    Monitor    mon_interest_;
    FD_Info_Interest_List list_interest_;


    int        max_num_events_;
    int        num_remain_;
    int        cur_index_;

    struct pollfd  poll_fds_ [POLL_MAX_EVENTS];

    /**
    * All interactions with the `/dev/poll' device are
    * done through this file descriptor.
    */
    ACE_HANDLE        fd_poller_;

    bool              need_interrupt_;
    Notification_Pipe interrupter_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_DEV_POLL */
#endif /* ACE_HAS_AIO_CALLS */
#endif //TRB_POSIX_AIO_DEV_POLL_PROVIDER_H 
