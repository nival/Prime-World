/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Proactor_Impl.h
 *
 *  Proactor_Impl.h,v 4.18 2002/08/27 20:33:26 shuston Exp
 *
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================


#ifndef TPROACTOR_PROACTOR_IMPL_H 
#define TPROACTOR_PROACTOR_IMPL_H 

#include /**/ "ace/pre.h"
#include "TProactor/TPROACTOR_Export.h"

#if ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)))
// This only works on Win32 platforms and on Unix platforms supporting
// aio calls.

#include "TProactor/Asynch_IO_Impl.h"
#include "ace/Global_Macros.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class TRB_Proactor_Impl
 *
 * @brief A manager for asynchronous event demultiplexing. This class
 * is the base class for all the concrete implementation
 * classes.
 *
 * See the Proactor pattern description at
 * http://www.cs.wustl.edu/~schmidt/proactor.ps.gz for more
 * details.
 */
class TPROACTOR_Export TRB_Proactor_Impl
{
public:
  /// Virtual destruction.
  virtual ~TRB_Proactor_Impl (void);

  /// Close the IO completion port.
  virtual int close (void) = 0;

  virtual ACE_HANDLE get_handle (void) const = 0;

  /// This method adds the <handle> to the I/O completion port. This
  /// function is a no-op function for Unix systems.
  virtual int register_handle (ACE_HANDLE  handle,
                               const void *completion_key,
                               int         operations) = 0;

  virtual int unregister_handle (ACE_HANDLE handle) = 0;

  /**
   * Dispatch a single set of events.  If <wait_time> elapses before
   * any events occur, return 0.  Return 1 on success i.e., when a
   * completion is dispatched, non-zero (-1) on errors and errno is
   * set accordingly.
   */
  virtual int handle_events (ACE_Time_Value &wait_time) = 0;

  /**
   * Block indefinitely until at least one event is dispatched.
   * Dispatch a single set of events.  If <wait_time> elapses before
   * any events occur, return 0.  Return 1 on success i.e., when a
   * completion is dispatched, non-zero (-1) on errors and errno is
   * set accordingly.
   */
  virtual int handle_events (void) = 0;



  //
  // = Factory methods for the results
  //
  // Note that the user does not have to use or know about these
  // methods unless they want to "fake" results.
  virtual int get_max_result_size (void) const = 0;
  
  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Read_Stream_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Write_Stream_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Read_Dgram_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Write_Dgram_Result & result) = 0;
    
  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Accept_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Connect_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Transmit_File_Result & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_Timer & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Wakeup_Completion & result) = 0;

  virtual TRB_Asynch_Result_Impl *
    create_result_impl (const TRB_Asynch_User_Result & result) = 0;

  virtual int cancel_aio (ACE_HANDLE h) = 0;
  virtual int cancel_aio (TRB_Handler * handler) = 0;
  virtual int cancel_all_aio (void) = 0;


  /**
   * Post <how_many> completions to the completion port so that all
   * threads can wake up. This is used in conjunction with the
   * <run_event_loop>. Default implementation is provided.
   */
  int post_wakeup_completions (int how_many);

protected:
  /// Handler to handle the wakeups. This works in conjunction with the
  /// <TRB_Proactor::run_event_loop>.
  TRB_Handler wakeup_handler_;
};


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* (ACE_WIN32 && ACE_HAS_WINCE) || ACE_HAS_AIO_CALLS */
#include "ace/post.h"
#endif //TPROACTOR_PROACTOR_IMPL_H 
