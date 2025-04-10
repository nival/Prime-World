/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    WIN32_Asynch_IO.h
 *
 *  WIN32_Asynch_IO.h,v 4.26 2002/11/13 22:30:37 shuston Exp
 *
 *
 *  These classes only works on Win32 platforms.
 *
 *  The implementation of TRB_Asynch_Timer,
 *  TRB_Asynch_Accept, and TRB_Asynch_Connect are only supported if
 *  ACE_HAS_WINSOCK2 is defined or you are on WinNT 4.0 or higher.
 *
 *
 *  @author Irfan Pyarali <irfan@cs.wustl.edu>
 *  @author Tim Harrison <harrison@cs.wustl.edu>
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_WIN32_ASYNCH_IO_H 
#define TPROACTOR_WIN32_ASYNCH_IO_H 
#include "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE))

#include "TProactor/Asynch_IO_Impl.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class TRB_WIN32_Proactor;

/**
 * @class TRB_WIN32_Asynch_Result
 *
 * @brief An abstract class which adds information to the OVERLAPPED
 *     structure to make it more useful.
 *
 *     An abstract base class from which you can obtain some basic
 *     information like the number of bytes transferred, the ACT
 *     associated with the asynchronous operation, indication of
 *     success or failure, etc.  Subclasses may want to store more
 *     information that is particular to the asynchronous operation
 *     it represents.
 */
class TPROACTOR_Export TRB_WIN32_Asynch_Result 
    : public OVERLAPPED
    , public TRB_Asynch_Result_Impl
{
public:

  friend class TRB_WIN32_Proactor;
  //  virtual TRB_Asynch_Result & get_original_result () = 0;
 
protected:
  TRB_WIN32_Asynch_Result (ACE_Allocator      *allocator,
                           void               *area,
                           TRB_WIN32_Proactor *win32_proactor,
                           DWORD               offset_low = 0,
                           DWORD               offset_high = 0);
                          
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Result (void);

  int  check_start_error (bool  rc_start,
                          const ACE_TCHAR *op_name);

  TRB_WIN32_Proactor  *win32_proactor () 
    {
      return this->win32_proactor_;
    }

private:
  virtual int on_complete ();

  /// TRB_Asynch_Result_Impl methods

  // start implementation must be overriden for each Result
  // virtual int start_impl () = 0;

  // post implementation is common for all Results
  virtual int post_impl ();

  
  /// Proactor will call this method when the operation on_completes.
  /// Default implementation is provided, derived classes
  /// can override this method and perform additional actions
  /// to extract more information.
  /// This method should return:
  ///  > 0 operation was restarted again (readn/writen case)
  ///    0 result must be dispatched
  ///  < 0 errors 
  int complete (size_t              bytes_transferred,
                const void         *completion_key,
                u_long              error);


  // prohibit copy and assignment
  TRB_WIN32_Asynch_Result (const TRB_WIN32_Asynch_Result& other);
  TRB_WIN32_Asynch_Result & operator = (const TRB_WIN32_Asynch_Result& other);

  TRB_WIN32_Proactor  *win32_proactor_;
};


/**
 * @class TRB_WIN32_Asynch_Read_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Stream::Result class.
 *
 */

class TRB_WIN32_Asynch_Read_Stream_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Read_Stream_Result User_Result;

  TRB_WIN32_Asynch_Read_Stream_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Read_Stream_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           
  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Read_Stream_Result (const TRB_WIN32_Asynch_Read_Stream_Result& other);
  TRB_WIN32_Asynch_Read_Stream_Result & operator = (const TRB_WIN32_Asynch_Read_Stream_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Read_Stream_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

  /// Initiator of simple read operation for streams and files
  int start_read_generic ();
  
  /// Initiator of iovec read operation for streams 
  int start_readv_stream ();
  
  /// Initiator of iovec read operation for files 
  int start_readv_file ();

private:
  TRB_Asynch_Read_Stream_Result  original_;
  DWORD                         io_flags_;
};



/**
 * @class TRB_WIN32_Asynch_Write_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Stream::Result class.
 *
 */

class TRB_WIN32_Asynch_Write_Stream_Result :
  public TRB_WIN32_Asynch_Result
{
public:

  typedef TRB_Asynch_Write_Stream_Result User_Result;

  TRB_WIN32_Asynch_Write_Stream_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Write_Stream_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           

  virtual TRB_Asynch_Result & get_original_result ();
  
private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Write_Stream_Result (const TRB_WIN32_Asynch_Write_Stream_Result& other);
  TRB_WIN32_Asynch_Write_Stream_Result & operator = (const TRB_WIN32_Asynch_Write_Stream_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Write_Stream_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

  /// Initiator of simple write operation for streams and files
  int start_write_generic ();
  
  /// Initiator of iovec write operation for streams 
  int start_writev_stream ();
  
  /// Initiator of iovec write operation for files 
  int start_writev_file ();

private:
  TRB_Asynch_Write_Stream_Result original_;
};

/**
 * @class TRB_WIN32_Asynch_Read_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Dgram::Result class.
 *
 */

class TRB_WIN32_Asynch_Read_Dgram_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Read_Dgram_Result User_Result;

  TRB_WIN32_Asynch_Read_Dgram_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Read_Dgram_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Read_Dgram_Result (const TRB_WIN32_Asynch_Read_Dgram_Result& other);
  TRB_WIN32_Asynch_Read_Dgram_Result & operator = (const TRB_WIN32_Asynch_Read_Dgram_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Read_Dgram_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

  virtual int on_complete ();
  
private:
  TRB_Asynch_Read_Dgram_Result  original_;
  DWORD                         io_flags_;
  INT                           addr_len_;
};

/**
 * @class TRB_WIN32_Asynch_Write_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Dgram::Result class.
 *
 */

class TRB_WIN32_Asynch_Write_Dgram_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Write_Dgram_Result User_Result;

  TRB_WIN32_Asynch_Write_Dgram_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Write_Dgram_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Write_Dgram_Result (const TRB_WIN32_Asynch_Write_Dgram_Result& other);
  TRB_WIN32_Asynch_Write_Dgram_Result & operator = (const TRB_WIN32_Asynch_Write_Dgram_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Write_Dgram_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

private:
  TRB_Asynch_Write_Dgram_Result original_;
};

/**
 * @class TRB_WIN32_Asynch_Connect_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Connect::Result class.
 *
 */

class TRB_WIN32_Asynch_Connect_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Connect_Result User_Result;

  TRB_WIN32_Asynch_Connect_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Connect_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           

  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Connect_Result (const TRB_WIN32_Asynch_Connect_Result& other);
  TRB_WIN32_Asynch_Connect_Result & operator = (const TRB_WIN32_Asynch_Connect_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Connect_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

  virtual int on_complete ();
private:
  TRB_Asynch_Connect_Result original_;
};

/**
 * @class TRB_WIN32_Asynch_Accept_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Accept::Result class.
 *
 */

class TRB_WIN32_Asynch_Accept_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Accept_Result User_Result;

  enum 
    {
      ACCEPT_EXTRA_BUF_BYTES = sizeof(ACE_INET_Addr)+16
    };

  TRB_WIN32_Asynch_Accept_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Accept_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           
  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Accept_Result (const TRB_WIN32_Asynch_Accept_Result& other);
  TRB_WIN32_Asynch_Accept_Result & operator = (const TRB_WIN32_Asynch_Accept_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Accept_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

  virtual int on_complete ();

private:
  TRB_Asynch_Accept_Result original_;
  char                     addr_buf_[2*ACCEPT_EXTRA_BUF_BYTES];
};

/**
 * @class TRB_WIN32_Asynch_Transmit_File_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Transmit_File::Result class.
 *
 */

class TRB_WIN32_Asynch_Transmit_File_Result :
    public TRB_WIN32_Asynch_Result
{
public:
  typedef TRB_Asynch_Transmit_File_Result User_Result;

  TRB_WIN32_Asynch_Transmit_File_Result (
                             ACE_Allocator  *allocator,
                             void * area,
                             const TRB_Asynch_Transmit_File_Result&  original,
                             TRB_WIN32_Proactor *win32_proactor);
                           
  virtual TRB_Asynch_Result & get_original_result ();

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Transmit_File_Result (const TRB_WIN32_Asynch_Transmit_File_Result& other);
  TRB_WIN32_Asynch_Transmit_File_Result & operator = (const TRB_WIN32_Asynch_Transmit_File_Result& other);
  
  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Transmit_File_Result (void);

  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ();

private:
  TRB_Asynch_Transmit_File_Result original_;
};

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
template <class RESULT>
class TRB_WIN32_Asynch_Result_T :
  public TRB_WIN32_Asynch_Result
{
public:
  typedef RESULT User_Result;
  
  TRB_WIN32_Asynch_Result_T (ACE_Allocator  *allocator,
                             void           *area,
                             const RESULT &  original,
                             TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
    {
    }
                             
  virtual TRB_Asynch_Result & get_original_result ()
    {
      return this->original_;
    }

private:
  // prohibit copy and assignment
  TRB_WIN32_Asynch_Result_T (const TRB_WIN32_Asynch_Result_T<RESULT> & other);
  TRB_WIN32_Asynch_Result_T & operator = (const TRB_WIN32_Asynch_Result_T<RESULT> & other);

  /// Destructor.
  virtual ~TRB_WIN32_Asynch_Result_T (void)
    {
    }
  
  
  /// Proactor will call this method to initiate asynch operation
  virtual int start_impl ()
    {
       return -1;
    }


  virtual int on_complete ()
    {
      return 0;
    }
  
  RESULT            original_;
};

typedef 
  TRB_WIN32_Asynch_Result_T<TRB_Asynch_Timer>
  TRB_WIN32_Asynch_Timer;


typedef 
  TRB_WIN32_Asynch_Result_T<TRB_Wakeup_Completion>
  TRB_WIN32_Wakeup_Completion;

typedef 
  TRB_WIN32_Asynch_Result_T<TRB_Asynch_User_Result>
  TRB_WIN32_Asynch_User_Result;

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 && !ACE_HAS_WINCE */
#include "ace/post.h"
#endif //TPROACTOR_WIN32_ASYNCH_IO_H 
