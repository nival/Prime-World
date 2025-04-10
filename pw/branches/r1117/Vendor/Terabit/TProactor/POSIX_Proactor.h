/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    POSIX_Proactor.h
 *
 *  POSIX_Proactor.h,v 4.44 2002/12/06 03:20:24 shuston Exp
 *
 *  @author Irfan Pyarali <irfan@cs.wustl.edu>
 *  @author Tim Harrison <harrison@cs.wustl.edu>
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@baltimore.com>
 */
//=============================================================================

#ifndef TRB_POSIX_PROACTOR_H 
#define TRB_POSIX_PROACTOR_H 

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
// POSIX implementation of Proactor depends on the <aio_> family of
// system calls.

#include "TProactor/Proactor_Impl.h"
#include "TProactor/POSIX_Asynch_IO.h"
#include "TProactor/Asynch_Allocator_T.h"


#include "TProactor/POSIX_AIO_Config.h"
#include "TProactor/POSIX_AIO_Processor.h"
#include "TProactor/POSIX_AIO_Dispatcher.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL


// *********************************************************************
/**
 * @class TRB_POSIX_Proactor
 *
 * @brief POSIX implementation of the Proactor.
 *
 */
class TPROACTOR_Export TRB_POSIX_Proactor :
  public TRB_Proactor_Impl
{
public:
  enum Proactor_Type
  {
    /// Base class type
    PROACTOR_POSIX  = TRB_POSIX_AIO_Config::PVC_NONE,

    /// Aio_suspend() based
    PROACTOR_AIOCB  = TRB_POSIX_AIO_Config::PVT_POSIX_AIOCB,

    /// Signals notifications
    PROACTOR_SIG    = TRB_POSIX_AIO_Config::PVT_POSIX_SIG,

    /// Callback notifications
    PROACTOR_CB     = TRB_POSIX_AIO_Config::PVT_POSIX_CB,

    /// SUN specific aiowait()
    PROACTOR_SUN    = TRB_POSIX_AIO_Config::PVT_SUN_AIO,
    
    /// Linux io_submit/io_getevents
    PROACTOR_LINUX  = TRB_POSIX_AIO_Config::PVT_LINUX_NAIO,

    /// POSIX select
    PROACTOR_SELECT = TRB_POSIX_AIO_Config::PVT_SELECT,

    /// POSIX poll
    PROACTOR_POLL   = TRB_POSIX_AIO_Config::PVT_SELECT,

    /// LINUX epoll
    PROACTOR_EPOLL  = TRB_POSIX_AIO_Config::PVT_EPOLL,

    /// SUN /dev/poll
    PROACTOR_DEVPOLL = TRB_POSIX_AIO_Config::PVT_DEVPOLL,

    /// SUN Completion Ports
    PROACTOR_SUNPORT = TRB_POSIX_AIO_Config::PVT_SUNPORT,

    /// BSD kqueue
    PROACTOR_KQUEUE = TRB_POSIX_AIO_Config::PVT_KQUEUE
  };


  enum SystemType  // open for future extention
  {
    OS_UNDEFINED= 0x0000,
    OS_WIN      = 0x0100,          // for future
    OS_WIN_NT   = OS_WIN | 0x0001,
    OS_WIN_2000 = OS_WIN | 0x0002,
    OS_SUN      = 0x0200,          // Sun Solaris family
    OS_SUN_55   = OS_SUN | 0x0001,
    OS_SUN_56   = OS_SUN | 0x0002,
    OS_SUN_57   = OS_SUN | 0x0003,
    OS_SUN_58   = OS_SUN | 0x0004,
    OS_SUN_59   = OS_SUN | 0x0005,
    OS_SUN_510  = OS_SUN | 0x0006,
    OS_SUN_511  = OS_SUN | 0x0007,
    OS_HPUX     = 0x0400,          // HPUX family
    OS_HPUX_11  = OS_HPUX | 0x0001,
    OS_LINUX    = 0x0800,          // Linux family
    OS_FREEBSD  = 0x1000,          // FreeBSD family
    OS_IRIX     = 0x2000,          // SGI IRIX family
    OS_OPENBSD  = 0x4000           // OpenBSD familty
  };


  /// Constructor.
  TRB_POSIX_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                     int sig_num = 0,         // interrupt signal , 0-use pipe 
                     int leader_type = 0);     // 0-shared /1-dedicated

  /// Build Lego-Proactor for your own style;
  TRB_POSIX_Proactor (const TRB_POSIX_AIO_Config & prime_processor_cfg,
                      const TRB_POSIX_AIO_Config & second_processor_cfg);


  /// Virtual destructor.
  virtual ~TRB_POSIX_Proactor (void);

  /// 
  Proactor_Type  get_impl_type (void);
  
  int open (void);

  //
  //  Proactor_Impl interface
  //

  /// Close the IO completion port.
  virtual int close (void);

  /// Get the event handle.
  virtual ACE_HANDLE get_handle (void) const;

  /// This method adds the <handle> to the I/O completion port. This
  /// function is valid for Unix systems now
  virtual int register_handle (ACE_HANDLE  handle,
                               const void *completion_key,
                               int         operations);

  virtual int unregister_handle (ACE_HANDLE handle);
  
  /**
   * Dispatch a single set of events.  If <wait_time> elapses before
   * any events occur, return 0.  Return 1 on success i.e., when a
   * completion is dispatched, non-zero (-1) on errors and errno is
   * set accordingly.
   */
  virtual int handle_events (ACE_Time_Value &wait_time);

  /**
   * Block indefinitely until at least one event is dispatched.
   * Dispatch a single set of events.  If <wait_time> elapses before
   * any events occur, return 0.  Return 1 on success i.e., when a
   * completion is dispatched, non-zero (-1) on errors and errno is
   * set accordingly.
   */
  virtual int handle_events (void);


  //
  // = Factory methods for the results
  //
  // Note that the user does not have to use or know about these
  // methods unless they want to "fake" results.
  virtual int get_max_result_size (void) const;


  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Read_Stream_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Write_Stream_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Read_Dgram_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Write_Dgram_Result & result);
    
  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Accept_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Connect_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Transmit_File_Result & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Timer & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Wakeup_Completion & result);

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_User_Result & result);


  int start (TRB_POSIX_Asynch_Result *posix_result);
  int post  (TRB_POSIX_Asynch_Result *posix_result);


  /// These methods do nothing and
  /// included for compatibiltity with POSIX
  virtual int cancel_aio (ACE_HANDLE h);
  virtual int cancel_aio (TRB_Handler * handler);
  virtual int cancel_all_aio (void);

  TRB_POSIX_AIO_Processor *find_processor (int op_mask);

protected:

  static int get_os_id(void);

private:

  int handle_events_i (ACE_Time_Value * wait_time);
    /// Member variables


  int os_id_;
  int flg_open_ ;
  int flg_disable_start_;

  ACE_SYNCH_MUTEX  mutex_;


  TRB_POSIX_AIO_Config      prime_config_;
  TRB_POSIX_AIO_Config      second_config_;

  TRB_POSIX_AIO_Dispatcher  dispatcher_;
  TRB_POSIX_AIO_Processor * prime_processor_;
  TRB_POSIX_AIO_Processor * second_processor_;

  union MAX_POSIX_RESULT1
    {
       void * any_ptr_;
       char   data_rs_ [sizeof(TRB_POSIX_Asynch_Read_Stream_Result)];
       char   data_ws_ [sizeof(TRB_POSIX_Asynch_Write_Stream_Result)];
    };
    
  union MAX_POSIX_RESULT2
    {
       void * any_ptr_;
       char   data_rd_ [sizeof(TRB_POSIX_Asynch_Read_Dgram_Result)];
       char   data_wd_ [sizeof(TRB_POSIX_Asynch_Write_Dgram_Result)];
       char   data_a_  [sizeof(TRB_POSIX_Asynch_Accept_Result)];
       char   data_c_  [sizeof(TRB_POSIX_Asynch_Connect_Result)];
    };
    
  union MAX_POSIX_RESULT3
    {
       void * any_ptr_;
       char   data_tf_ [sizeof(TRB_POSIX_Asynch_Transmit_File_Result)];
       char   data_tm_ [sizeof(TRB_POSIX_Asynch_Timer)];
       char   data_wc_ [sizeof(TRB_POSIX_Wakeup_Completion)];
       char   data_u_  [sizeof(TRB_POSIX_Asynch_User_Result)];
    };

  union MAX_POSIX_RESULT
    {
       union MAX_POSIX_RESULT1;
       union MAX_POSIX_RESULT2;
       union MAX_POSIX_RESULT3;
    };
       
  enum 
   {
      MAX_POSIX_RESULT1_SIZE = sizeof(MAX_POSIX_RESULT1),
      MAX_POSIX_RESULT2_SIZE = sizeof(MAX_POSIX_RESULT2),
      MAX_POSIX_RESULT3_SIZE = sizeof(MAX_POSIX_RESULT3),
      MAX_POSIX_RESULT_SIZE  = sizeof(MAX_POSIX_RESULT)
   };

  typedef TRB_Asynch_Allocator_T<ACE_SYNCH_MUTEX> Allocator;
  
  Allocator allocator11_;  // read results
  Allocator allocator12_;  // write results
  Allocator allocator2_;   // accept connect dgram
  Allocator allocator3_;   // all others

};



/*
 * For old compatibility
 *
 */
class TPROACTOR_Export TRB_POSIX_AIOCB_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_POSIX_AIOCB_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = 0,        // use pipe, no interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};


class TPROACTOR_Export TRB_POSIX_SIG_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_POSIX_SIG_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = ACE_SIGRTMIN, // interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_POSIX_CB_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_POSIX_CB_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = ACE_SIGRTMIN, // interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_SUN_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_SUN_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                    int sig_num = 0,        // use pipe, no interrupt signal
                    int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_LINUX_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_LINUX_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                    int sig_num = 0,        // use pipe, no interrupt signal
                    int leader_type = 0);   // 0-shared /1-dedicated
};

// **********************************************************************
//
// **********************************************************************

class TPROACTOR_Export TRB_Select_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Select_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = 0,        // use pipe, no interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_Poll_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Poll_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                     int sig_num = 0,        // use pipe, no interrupt signal
                     int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_Dev_Poll_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Dev_Poll_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                         int sig_num = 0,        // use pipe, no interrupt signal
                         int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_Event_Poll_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Event_Poll_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = 0,        // use pipe, no interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};


class TPROACTOR_Export TRB_SUN_Port_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_SUN_Port_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                          int sig_num = 0,        // use pipe, no interrupt signal
                          int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_Kqueue_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Kqueue_Proactor (size_t max_op = ACE_AIO_DEFAULT_SIZE,
                       int sig_num = 0,        // use pipe, no interrupt signal
                       int leader_type = 0);   // 0-shared /1-dedicated
};

class TPROACTOR_Export TRB_Dummy_Proactor: public TRB_POSIX_Proactor 
{
public:
  TRB_Dummy_Proactor(void);
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
#endif //TRB_POSIX_PROACTOR_H 
