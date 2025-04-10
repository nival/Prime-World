/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    WIN32_Proactor.h
 *
 *  WIN32_Proactor.h,v 4.24 2002/10/05 00:25:54 shuston Exp
 *
 *  @author Irfan Pyarali (irfan@cs.wustl.edu)
 *  @author Tim Harrison (harrison@cs.wustl.edu)
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_WIN32_PROACTOR_H 
#define TPROACTOR_WIN32_PROACTOR_H 

#include /**/ "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE))
// WIN32 implementation of the Proactor.

#include "TProactor/Proactor_Impl.h"
#include "TProactor/WIN32_Asynch_IO.h"
#include "TProactor/Asynch_Allocator_T.h"

#include "ace/Event_Handler.h"
#include "ace/Auto_Event.h"

#include <ace/Synch_T.h>
#include <set>

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Forward declarations.
//class TRB_WIN32_Proactor_Timer_Handler;

/**
 * @class TRB_WIN32_Proactor
 *
 * @brief A manager for asynchronous event demultiplexing on Win32.
 *
 * See the Proactor pattern description at
 * http://www.cs.wustl.edu/~schmidt/PDF/proactor.pdf for more
 * details.
 */
class TPROACTOR_Export TRB_WIN32_Proactor : 
  public TRB_Proactor_Impl ,
  public ACE_Event_Handler
{
  friend class TRB_WIN32_Asynch_Connect_Result;
public:
  /// A do nothing constructor.
  TRB_WIN32_Proactor (size_t number_of_threads = 0,
                      int used_with_reactor_event_loop = 0);

  /// Virtual destruction.
  virtual ~TRB_WIN32_Proactor (void);

  // 
  // Win32 Proactor specific methods
  //

  /// Get number of thread used as a parameter to CreatIoCompletionPort.
  size_t number_of_threads (void) const;

  /// Set number of thread used as a parameter to CreatIoCompletionPort.
  void number_of_threads (size_t threads);

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


  virtual int post (TRB_WIN32_Asynch_Result *win32_result);


  /// These methods do nothing and
  /// included for compatibiltity with POSIX
  virtual int cancel_aio (ACE_HANDLE h);
  virtual int cancel_aio (TRB_Handler * handler);
  virtual int cancel_all_aio (void);


protected:

  /// Called when object is signaled by OS (either via UNIX signals or
  /// when a Win32 object becomes signaled).
  virtual int handle_signal (int signum, siginfo_t * = 0, ucontext_t * = 0);

  /// Called when object is removed from the ACE_Reactor.
  virtual int handle_close (ACE_HANDLE handle,
          ACE_Reactor_Mask close_mask);

  /**
   * Dispatch a single set of events.  If <milli_seconds> elapses
   * before any events occur, return 0. Return 1 if a completion is
   * dispatched. Return -1 on errors.
   */
  virtual int handle_events (unsigned long milli_seconds);


private:
  void add_connect(TRB_WIN32_Asynch_Connect_Result *result);
  void remove_connect(TRB_WIN32_Asynch_Connect_Result *result);

  /// Handle for the completion port. Unix doesnt have completion
  /// ports.
  ACE_HANDLE completion_port_;

  /// This number is passed to the <CreatIOCompletionPort> system
  /// call.
  DWORD number_of_threads_;

  /// This event is used in conjunction with Reactor when we try to
  /// integrate the event loops of Reactor and the Proactor.
  ACE_Auto_Event event_;

  /// Flag that indicates whether we are used in conjunction with
  /// Reactor.
  int used_with_reactor_event_loop_;

  union MAX_WIN32_RESULT1
    {
       void * any_ptr_;
       char   data_rs_ [sizeof(TRB_WIN32_Asynch_Read_Stream_Result)];
       char   data_ws_ [sizeof(TRB_WIN32_Asynch_Write_Stream_Result)];
    };
    
  union MAX_WIN32_RESULT2
    {
       void * any_ptr_;
       char   data_rd_ [sizeof(TRB_WIN32_Asynch_Read_Dgram_Result)];
       char   data_wd_ [sizeof(TRB_WIN32_Asynch_Write_Dgram_Result)];
       char   data_a_  [sizeof(TRB_WIN32_Asynch_Accept_Result)];
       char   data_c_  [sizeof(TRB_WIN32_Asynch_Connect_Result)];
    };
    
  union MAX_WIN32_RESULT3
    {
       void * any_ptr_;
       char   data_tf_   [sizeof(TRB_WIN32_Asynch_Transmit_File_Result)];
       char   data_tm_   [sizeof(TRB_WIN32_Asynch_Timer)];
       char   data_wkup_ [sizeof(TRB_WIN32_Wakeup_Completion)];
       char   data_usr_  [sizeof(TRB_WIN32_Asynch_User_Result)];
    };

  union MAX_WIN32_RESULT
    {
       union MAX_WIN32_RESULT1;
       union MAX_WIN32_RESULT2;
       union MAX_WIN32_RESULT3;
    };
       
  enum 
   {
      MAX_WIN32_RESULT1_SIZE = sizeof(MAX_WIN32_RESULT1),
      MAX_WIN32_RESULT2_SIZE = sizeof(MAX_WIN32_RESULT2),
      MAX_WIN32_RESULT3_SIZE = sizeof(MAX_WIN32_RESULT3),
      MAX_WIN32_RESULT_SIZE  = sizeof(MAX_WIN32_RESULT)
   };

  typedef TRB_Asynch_Allocator_T<ACE_SYNCH_MUTEX> Allocator;
  
  Allocator allocator11_;  // read results
  Allocator allocator12_;  // write results
  Allocator allocator2_;   // accept connect dgram
  Allocator allocator3_;   // all others

  ACE_SYNCH_MUTEX  pending_connects_mutex_;
  std::set<TRB_WIN32_Asynch_Connect_Result*> pending_connects_;

};


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 */
#include "ace/post.h"
#endif //TPROACTOR_WIN32_PROACTOR_H 
