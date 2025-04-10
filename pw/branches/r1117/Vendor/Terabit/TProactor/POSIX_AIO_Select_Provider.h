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
 *  @file    POSIX_AIO_Emulation_Provider.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_SELECT_PROVIDER_H 
#define TRB_POSIX_AIO_SELECT_PROVIDER_H 

#include "TProactor/POSIX_AIO_Emulation_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "ace/Select_Reactor_Base.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


/**
 * @class TRB_POSIX_AIO_Select_Provider
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_Select_Provider : 
  public TRB_POSIX_AIO_Emulation_Provider
{

public:

    TRB_POSIX_AIO_Select_Provider (const TRB_POSIX_AIO_Config & config);
    virtual ~TRB_POSIX_AIO_Select_Provider();

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

    bool       declare_interest_i (ACE_HANDLE handle, int interest);
    int        clear_interest_i   (ACE_HANDLE handle, int interest);
    int        wait_for_ready_fd  (ACE_Time_Value * wait_time);
    ACE_HANDLE find_next_ready_fd (int & ready_mask, int & remain_mask);
 
    /// monitor to protect access to request set
    Monitor     mon_interest_;


    ACE_HANDLE hcur_;
    ACE_HANDLE hmax_;
    int        num_bits_ready_;

    /// Masks for keeping  pending AIO
    ACE_Select_Reactor_Handle_Set  request_set_;

    /// Masks returned by select() call 
    ACE_Select_Reactor_Handle_Set  ready_set_;

    bool              need_interrupt_;
    Notification_Pipe interrupter_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#endif //TRB_POSIX_AIO_SELECT_PROVIDER_H 
