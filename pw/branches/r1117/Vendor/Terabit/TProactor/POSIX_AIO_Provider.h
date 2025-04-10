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
 *  @file    POSIX_AIO_Provider.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_PROVIDER_H 
#define TRB_POSIX_AIO_PROVIDER_H 

#include "TProactor/POSIX_AIO_FD_Info.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "TProactor/POSIX_AIO_Config.h"
#include "ace/Pipe.h"
#include "ace/Message_Block.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *
 * @class TRB_POSIX_AIO_Provider
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_Provider 
{

public:

    typedef ACE_SYNCH_MUTEX      Mutex;
    typedef ACE_SYNCH_CONDITION  Condition;

    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;

    typedef TRB_POSIX_AIO_FD_Repository::FD_Guard  FD_Guard;

   /**
     *
     * @class Notification_Pipe
     *
     */
    class TPROACTOR_Export Notification_Pipe :
        public TRB_Handler
    {
    public:
        Notification_Pipe (bool flg_nonblock);
        virtual ~Notification_Pipe ();

        int   open  (bool flg_nonblock);
        int   close ();

        int   notify ();
        int   read   ();

        int   read_handle () { return this->pipe_.read_handle();}
        //ACE_Message_Block & message_block () { return message_block_;}

        char   *read_buffer () { return read_buffer_; }
        size_t  read_buffer_size () const { return sizeof (read_buffer_);}

    private:
        /// Notification pipe 
        ACE_Pipe   pipe_;

        /// Message block to read from  the pipe.
        char              read_buffer_ [512];
        //ACE_Message_Block message_block_;
    };

   /**
     *
     * @class Notification_Result
     *
     */
    class TPROACTOR_Export Notification_Result :
        public TRB_POSIX_Asynch_Read_Stream_Result
    {
    public:
        /// Constructor.
        Notification_Result (Notification_Pipe & owner);
    
        /// Destructor.
        virtual ~Notification_Result (void);

    };
 
    
  
    TRB_POSIX_AIO_Provider (const TRB_POSIX_AIO_Config & config); 
    virtual ~TRB_POSIX_AIO_Provider();
    

    const TRB_POSIX_AIO_Config & config() const 
    {
        return config_;
    }


    virtual int  init () = 0;
    virtual int  fini () = 0;
    virtual int  interrupt () = 0;

    virtual int  get_supported_operations_mask () const = 0;

    virtual int register_handle (ACE_HANDLE  handle,
                               const void *completion_key,
                               int         operations) = 0;

    virtual int  unregister_handle (ACE_HANDLE handle)=0;

    
    virtual int  get_completed_aio (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual bool begin_aio_wait (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  finish_aio_completions (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  start_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  cancel_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  cancel_aio (ACE_HANDLE handle,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  cancel_aio (TRB_Handler * handler,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

    virtual int  cancel_all (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue) = 0;

private:
    const TRB_POSIX_AIO_Config & config_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#endif //TRB_POSIX_AIO_PROVIDER_H 
