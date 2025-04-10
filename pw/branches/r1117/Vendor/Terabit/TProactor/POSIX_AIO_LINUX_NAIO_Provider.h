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
 *  @file    POSIX_AIO_LINUX_NAIO_Provider.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_LINUX_NAIO_PROVIDER_H 
#define TRB_POSIX_AIO_LINUX_NAIO_PROVIDER_H 

#include "TProactor/POSIX_AIO_Provider.h"

#if defined(ACE_HAS_AIO_CALLS) && defined (ACE_HAS_LINUX_LIBAIO) && defined(linux)


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *
 * @class TRB_POSIX_AIO_LINUX_NAIO_Provider
 * currently supports OP_READ_FILE and OP_WRITE_FILE
 * asynch operations. They correspond to Linux NAIO
 * operations: IO_CMD_PREAD and IO_CMD_PWRITE.
 * Read/Write operations are real and native AIO
 * supported by Linux Kernel. As soon as Linux 
 * will provide IO_CMD_POLL and IO_CMD_EPOLL_POLL_WAIT
 * this provider will be extented for other asynchronous
 * operations: OR_READ_STREAM, OP_WRITE_STREAM, 
 * OP_WRITE_DGRAM, OP_READ_DGRAM, OP_ACCEPT, OP_CONNECT.
 * Moreover, it will be the first hybrid AIO Provider:
 * part of operations will be native AIO (ReadFile 
 * and WriteFile), while other will be emulated.
 *
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_LINUX_NAIO_Provider 
    : public TRB_POSIX_AIO_Provider 
{
    enum { IO_GETEVENTS_MAX_EVENTS = 256 };

   /**
     *
     * @class Notification_File
     *
     */
    class TPROACTOR_Export Notification_File
    {
    public:
        Notification_File ();
        virtual ~Notification_File ();

        int   open  ();
        int   close ();

        int   notify (io_context_t  context);
        bool  check (struct io_event& event);

        ACE_HANDLE  handle() { return handle_; }


    private:
        /// Notification handle 
        ACE_HANDLE        handle_;
        char              buffer_[512];
        struct iocb       iocb_;
    };

public:

    TRB_POSIX_AIO_LINUX_NAIO_Provider (const TRB_POSIX_AIO_Config & config);
    virtual ~TRB_POSIX_AIO_LINUX_NAIO_Provider();

    virtual int  init ();
    virtual int  fini ();
    virtual int  interrupt ();

    virtual int  get_supported_operations_mask () const;

    virtual int register_handle (ACE_HANDLE  handle,
                               const void *completion_key,
                               int         operations);

    virtual int  unregister_handle (ACE_HANDLE handle);

    
    virtual int  get_completed_aio (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual bool begin_aio_wait (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  finish_aio_completions (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  start_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (ACE_HANDLE handle,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (TRB_Handler * handler,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_all (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);


    int  max_files ()  const;

private:

    int cancel_queue (TRB_Handler * handler,
                      TRB_POSIX_Asynch_Result_List & pending_list,
                      TRB_POSIX_Asynch_Result_Queue & completed_queue);

  int    wait_for_events (ACE_Time_Value * wait_time);
  int    find_next_event (struct io_event& event);
  void   process_event   (struct io_event& event,
                          TRB_POSIX_Asynch_Result_Queue & completed_queue);


  io_context_t      context_;

  io_event          events_ [IO_GETEVENTS_MAX_EVENTS];

  int               max_num_events_;
  int               num_remain_;
  int               cur_index_;
  Notification_File interrupter_;


  TRB_POSIX_AIO_FD_Repository repository_;
};

inline int
TRB_POSIX_AIO_LINUX_NAIO_Provider::max_files () const
{
    return this->repository_.max_files ();
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* defined(ACE_HAS_AIO_CALLS) && defined (ACE_HAS_LINUX_LIBAIO) && defined(linux) */

#endif //TRB_POSIX_AIO_LINUX_NAIO_PROVIDER_H 
