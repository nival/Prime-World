/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Asynch_IO_Impl.h
 *
 *  Asynch_IO_Impl.h,v 4.19 2002/08/27 17:35:09 shuston Exp
 *
 *
 *  This class contains asbtract base classes for all the concrete
 *  implementation classes for the various asynchronous operations
 *  that are used with the Praoctor.
 *
 *
 *  @author Irfan Pyarali (irfan@cs.wustl.edu)
 *  @author Tim Harrison (harrison@cs.wustl.edu)
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_ASYNCH_IO_IMPL_H 
#define TPROACTOR_ASYNCH_IO_IMPL_H 

#include /**/ "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))
// This only works on Win32 platforms and on Unix platforms supporting
// aio calls.

#include "TProactor/Asynch_IO.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL


// Forward declaration.
//class TRB_Proactor_Impl;

/**
 * @class TRB_Asynch_Result_Impl
 *
 * @brief Abstract base class for the all the classes that provide
 * concrete implementations for TRB_Asynch_Result.
 *
 */
class TPROACTOR_Export TRB_Asynch_Result_Impl
{
public:
  static void release (TRB_Asynch_Result_Impl *result_impl);

  /// helper method to build iovec for readv
  static int build_read_iovec (
                  const ACE_Message_Block *msg,
                  bool                     flg_chain,
                  iovec                   *iov,
                  int &                    iovmax,
                  size_t &                 max_bytes_to_read,
                  size_t                   bytes_done);

 
  /// helper method to build iovec for writev
  static int build_write_iovec (
                   const ACE_Message_Block *msg,
                   bool                     flg_chain,
                   iovec                   *iov,
                   int &                    iovmax,
                   size_t &                 max_bytes_to_write,
                   size_t                   bytes_done);

  /// helper method to copy iovec for readv/writev
  static int copy_iovec (
                  const iovec             *src,
                  int                      src_cnt,
                  iovec                   *iov,
                  int &                    iovmax,
                  size_t &                 max_bytes,
                  size_t                   done_bytes);

 
  TRB_Asynch_Result_Impl (ACE_Allocator *allocator,
                          void          *area);


  virtual ~TRB_Asynch_Result_Impl (void);

  virtual TRB_Asynch_Result & get_original_result () = 0;


  int  dispatch ();
  int  start ();
  int  post ();
  
  void set_completion (ssize_t nbytes, u_long errcode);


protected:
  /**
   * start AIO implementation
   */
  virtual int start_impl () = 0;

  /**
   * Post a result to the completion queue of the Proactor.
   */
  virtual int post_impl () = 0;

  void free (void);

private:
  // prohibit copy and assignment
  TRB_Asynch_Result_Impl (const TRB_Asynch_Result_Impl& other);
  TRB_Asynch_Result_Impl & operator = (const TRB_Asynch_Result_Impl& other);

  ACE_Allocator *allocator_;  // allocator 
  void          *area_;       // allocated area for the derived object
};


inline void
TRB_Asynch_Result_Impl::set_completion (ssize_t nbytes, u_long errcode)
{
  this->get_original_result ().set_completion (nbytes, errcode);
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS  || !ACE_HAS_WINCE && ACE_WIN32 */
#include "ace/post.h"
#endif // TPROACTOR_ASYNCH_IO_IMPL_H 
