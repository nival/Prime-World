/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Asynch_IO.h
 *
 *  Asynch_IO.h,v 4.66 2003/07/19 19:04:10 dhinton Exp
 *
 *  This works on Win32 (#if defined (ACE_WIN32) && !defined
 *  (ACE_HAS_WINCE)) platforms and on POSIX4 platforms with <aio_*>
 *  routines (#if defined (ACE_HAS_AIO_CALLS))
 *
 *  On Win32 platforms, the implementation of
 *  <TRB_Asynch_Transmit_File> and <TRB_Asynch_Accept> are only
 *  supported if ACE_HAS_WINSOCK2 is defined or you are on WinNT 4.0
 *  or higher.
 *
 *  @author Irfan Pyarali <irfan@cs.wustl.edu>
 *  @author Tim Harrison <harrison@cs.wustl.edu>
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Roger Tragin <r.tragin@computer.org>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_ASYNCH_IO_H 
#define TPROACTOR_ASYNCH_IO_H 
#include /**/ "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))

# include "ace/os_include/os_signal.h"
# include "ace/os_include/sys/os_socket.h"
# include "ace/os_include/sys/os_types.h"
# include "ace/Time_Value.h"
# include "ace/Malloc_Base.h"

// for new ACE
//# include "ace/Assert.h"          // For ACE_ASSERT

// for old ACE
# include "ace/Log_Msg.h"           // For ACE_ASSERT

# include "TProactor/Sock_Addr.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

# if defined (ACE_WIN32) && ! defined (ACE_HAS_WINCE) && ! defined (ACE_HAS_PHARLAP)

    typedef TRANSMIT_FILE_BUFFERS ACE_TRANSMIT_FILE_BUFFERS;
    typedef LPTRANSMIT_FILE_BUFFERS ACE_LPTRANSMIT_FILE_BUFFERS;
    typedef PTRANSMIT_FILE_BUFFERS ACE_PTRANSMIT_FILE_BUFFERS;

#   define ACE_INFINITE INFINITE
#   define ACE_STATUS_TIMEOUT STATUS_TIMEOUT
#   define ACE_WAIT_FAILED WAIT_FAILED
#   define ACE_WAIT_TIMEOUT WAIT_TIMEOUT

# else /* ACE_WIN32 */

    struct ACE_TRANSMIT_FILE_BUFFERS
    {
      void *Head;
      size_t HeadLength;
      void *Tail;
      size_t TailLength;
    };
    typedef ACE_TRANSMIT_FILE_BUFFERS* ACE_PTRANSMIT_FILE_BUFFERS;
    typedef ACE_TRANSMIT_FILE_BUFFERS* ACE_LPTRANSMIT_FILE_BUFFERS;

#   if !defined (ACE_INFINITE)
#     define ACE_INFINITE LONG_MAX
#   endif /* ACE_INFINITE */
#   define ACE_STATUS_TIMEOUT LONG_MAX
#   define ACE_WAIT_FAILED LONG_MAX
#   define ACE_WAIT_TIMEOUT LONG_MAX

# endif /* ACE_WIN32 */



// Forward declarations
class TRB_Proactor;
class TRB_Asynch_Result_Impl;
class TRB_Handler;
class ACE_Message_Block;



// ******************************************************************
//   Let define all user-visible Asynchronous Results
// ******************************************************************

/**
 * @class TRB_Asynch_Result
 *
 * @brief An interface base class which allows users access to common
 * information related to an asynchronous operation.
 *
 * An interface base class from which you can obtain some basic
 * information like the number of bytes transferred, the ACT
 * associated with the asynchronous operation, indication of
 * success or failure, etc. Subclasses may want to store more
 * information that is particular to the asynchronous operation
 * it represents.
 */
class TPROACTOR_Export TRB_Asynch_Result
{
public:
  friend class TRB_Asynch_Result_Impl;

  /// Operation code
  enum OpCode
    {
      NO_OP            = 0x0000,
      OP_READ_MASK     = 0x000F,
      OP_READ_STREAM   = 0x0001,
      OP_READ_FILE     = 0x0002,   
      OP_READ_DGRAM    = 0x0004,  
      OP_ACCEPT        = 0x0008,
      OP_WRITE_MASK    = 0x00F0, 
      OP_WRITE_STREAM  = 0x0010,
      OP_WRITE_FILE    = 0x0020,  
      OP_WRITE_DGRAM   = 0x0040, 
      OP_CONNECT       = 0x0080,
      OP_TRANSMIT_FILE = 0x0100,
      OP_TIMER         = 0x1000,
      OP_WAKEUP        = 0x2000,
      OP_USER          = 0x4000
    };     

  enum OpFlags 
    {
      FLG_IOVECT          = 0x0001,   // iov operation readv/writev
      FLG_EXACTLY_BYTES   = 0x0002,   // operation read_n/write_n
      FLG_NEW_HANDLE      = 0x0004,   // in case of failure close file handle
      FLG_FAKE_RESULT     = 0x0008,   // fake result (for post_completion)

      FLG_DIRECT_BUFFERS  = 0x0080    // user raw buffers instead of 
                                      // ACE_Message_Block
      //FLG_REGISTER_HANDLE = 0x0010, // register_handle should be called 
      //FLG_ALTERNATIVE_CB  = 0x0020  // use alternative call back
                                      // (file operations with stream callback)
    };

  class TPROACTOR_Export Buffer_Info
  {
  private:
    union 
    {
        ACE_Message_Block  *message_block_ptr_;
        char               *buffer_;
        iovec              *iov_;
    };

    // switch
    // > 0  : select iov_
    //   0  : select buffer_
    // < 0  : select message_block_ptr_
    int    iov_count_;

  public:

    Buffer_Info (char *buffer = 0);
    Buffer_Info (iovec *iov, int iovcnt);
    Buffer_Info (ACE_Message_Block &mb);
    
    int     get_iov_count () const;
    char   *get_buffer (void) const;
    iovec  *get_iov (void) const;
    ACE_Message_Block * get_message_block_ptr() const;
  };



  
  /// Get the operation code
  int op_code (void) const;

  /// Get the operation additional flags
  int op_flags (void) const;

  int is_read_family (void) const;
  int is_write_family (void) const;
  int is_iov_operation (void) const;
  int is_direct_buffers (void) const;

  /// Accessor for the gather write OpCode modifier
  int gather_enabled (void) const
    {
      return is_iov_operation ();
    }

  /// Accessor for the scatter read OpCode modifier
  int scatter_enabled (void) const
    {
      return is_iov_operation ();
    }

  /// Did the operation succeed?
  int success (void) const;

  /// Error value if the operation fails.
  u_long error (void) const;

  /// Number of bytes transferred by the operation.
  size_t bytes_transferred (void) const;

  /// Number of bytes requested
  size_t bytes_requested (void) const;


  const Buffer_Info& get_buffer_info () const;
  /// Message block which contains the read/write data.
  /// Can be zero if asynch operation does not require
  /// to read/write
  ACE_Message_Block *get_message_block_ptr (void) const;

  char   *get_buffer (void) const;
  iovec  *get_iov (void) const;
  int     get_iov_count (void) const;


  /// I/O handle used for operation
  ACE_HANDLE handle (void) const;

  TRB_Handler *get_handler(void) const;

  /// This really make sense only when doing file I/O.
  u_long offset (void) const;

  /// Offset_high associated with the OVERLAPPED structure.
  u_long offset_high (void) const;

  /// ACT associated with the operation.
  const void *act (void) const;

  /**
   * This is the ACT associated with the handle on which the
   * Asynch_Operation takes place.
   *
   * On WIN32, this returns the ACT associated with the handle when it
   * was registered with the I/O completion port.
   *
   * @@ This is not implemented for POSIX4 platforms. Returns 0.
   */
  const void *completion_key (void) const;
  
  /**
   * Priority of the operation.
   *
   * On POSIX4-Unix, this is supported. Priority works like <nice> in
   * Unix. Negative values are not allowed. 0 means priority of the
   * operation same as the process priority. 1 means priority of the
   * operation is one less than process. And so forth.
   *
   * On Win32, this is a no-op.
   */
  int priority (void) const;

  /**
   * POSIX4 real-time signal number to be used for the
   * operation. <signal_number> ranges from ACE_SIGRTMIN to ACE_SIGRTMAX. By
   * default, ACE_SIGRTMIN is used to issue <aio_> calls. This is a no-op
   * on non-POSIX4 systems and returns 0.
   */
  int signal_number (void) const;



  /// Destructor.
  virtual ~TRB_Asynch_Result (void);

  
  void  set_handle   (ACE_HANDLE handle);
  void  set_op_flags (int mask);
  void  clr_op_flags (int mask);
  void  set_completion (ssize_t nbytes, u_long errcode);
  

protected:

  void  move_rd_ptrs (void);
  void  move_wr_ptrs (void);

  /// Constructor. 
  TRB_Asynch_Result (int                op_code,
                     int                op_flags,
                     TRB_Handler       *handler,
                     ACE_HANDLE         handle,
                     const Buffer_Info& buf_info,
                     size_t             bytes_requested,
                     u_long             offset,
                     u_long             offset_high,
                     const void        *act,
                     const void        *completion_key,
                     int                priority,
                     int                signal_number);
  /// Default copy constructor and assignment are OK

private:
  /// called by Proactor framework when operation is completed
  /// return codes:
  ///   1 - operation should be restored
  ///   0 - operation was successfuly dispatched
  ///  -1 - errors 
  virtual int dispatch (void);

private:

  // const data
  int                op_code_;
  int                op_flags_;

  TRB_Handler       *handler_;
  ACE_HANDLE         handle_;

  Buffer_Info        buf_info_;
  size_t             bytes_requested_;

  const u_long       offset_;
  const u_long       offset_high_;
  const void * const act_;
  const void * const completion_key_;
  const int          priority_;
  const int          signal_number_;

  // variable data
  u_long             error_;
  size_t             bytes_transferred_;
};

/**
 * @class TRB_Asynch_Read_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Stream::Result class.
 *
 */
class TPROACTOR_Export TRB_Asynch_Read_Stream_Result 
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// The number of bytes which were requested at the start of the
  /// asynchronous read.
  size_t bytes_to_read (void) const
    {
      return this->bytes_requested();
    }

  /// Message block which contains the read data.
  ACE_Message_Block &message_block (void) const
    {
      ACE_ASSERT (this->get_message_block_ptr() != 0);
      return *this->get_message_block_ptr();
    }

  virtual ~TRB_Asynch_Read_Stream_Result (void);

  TRB_Asynch_Read_Stream_Result (TRB_Handler       *handler,
                                 ACE_HANDLE         handle,
                                 const Buffer_Info& buf_info,
                                 size_t             bytes_requested,
                                 const void        *act,
                                 const void        *completion_key,
                                 int                priority,
                                 int                signal_number,
                                 int                op_flags); // was scatter_flags

  TRB_Asynch_Read_Stream_Result (TRB_Handler       *handler,
                                 ACE_HANDLE         handle,
                                 const Buffer_Info& buf_info,
                                 size_t             bytes_requested,
                                 u_long             offset,
                                 u_long             offset_high,
                                 const void        *act,
                                 const void        *completion_key,
                                 int                priority,
                                 int                signal_number,
                                 int                op_flags); // was scatter_flags
};

typedef TRB_Asynch_Read_Stream_Result TRB_Asynch_Read_File_Result;

/**
 * @class TRB_Asynch_Write_Stream_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Stream::Result.
 *
 */
class TPROACTOR_Export TRB_Asynch_Write_Stream_Result 
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// The number of bytes which were requested at the start of the
  /// asynchronous write.
  size_t bytes_to_write (void) const
    {
      return this->bytes_requested();
    }

  /// Message block which contains the write data.
  ACE_Message_Block &message_block (void) const
    {
      ACE_ASSERT (this->get_message_block_ptr() != 0);
      return *this->get_message_block_ptr();
    }

  virtual ~TRB_Asynch_Write_Stream_Result (void);

  TRB_Asynch_Write_Stream_Result (TRB_Handler       *handler,
                                  ACE_HANDLE         handle,
                                  const Buffer_Info& buf_info,
                                  size_t             bytes_requested,
                                  const void        *act,
                                  const void        *completion_key,
                                  int                priority,
                                  int                signal_number,
                                  int                op_flags); // was gather_flags

  TRB_Asynch_Write_Stream_Result (TRB_Handler       *handler,
                                  ACE_HANDLE         handle,
                                  const Buffer_Info& buf_info,
                                  size_t             bytes_requested,
                                  u_long             offset,
                                  u_long             offset_high,
                                  const void        *act,
                                  const void        *completion_key,
                                  int                priority,
                                  int                signal_number,
                                  int                op_flags); // was gather_flags
};

typedef TRB_Asynch_Write_Stream_Result TRB_Asynch_Write_File_Result;

/**
 * @class TRB_Asynch_Accept_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Accept.
 *
 */
class TPROACTOR_Export TRB_Asynch_Accept_Result 
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// I/O handle used for accepting new connections.
  ACE_HANDLE listen_handle (void) const 
    {
      return this->handle();
    }

  /// I/O handle for the new connection.
  ACE_HANDLE accept_handle (void) const 
    {
      return this->accept_handle_;
    }

  const ACE_Addr& remote_address () const
    {
      return this->remote_address_.get_ace_addr ();
    }

  const ACE_Addr& local_address () const
    {
      return this->local_address_.get_ace_addr ();
    }

  void set_accept_handle (ACE_HANDLE  accept_handle);

  // this method is called on Windows when AcceptEx
  // completed and contains addresses in the buffer
  void update_addresses (sockaddr   *local_addr,
                         int         local_size,
                         sockaddr   *remote_addr,
                         int         remote_size);

  // this method is called on POSIX 
  void update_addresses (ACE_HANDLE h);

  virtual ~TRB_Asynch_Accept_Result (void);

  TRB_Asynch_Accept_Result (TRB_Handler       *handler,
                            ACE_HANDLE         listen_handle,
                            const Buffer_Info& buf_info,
                            size_t             bytes_requested,
                            const void        *act,
                            const void        *completion_key,
                            int                priority,
                            int                signal_number);
private:
  /// I/O handle for the new connection.
  ACE_HANDLE     accept_handle_;
  TRB_Sock_Addr  remote_address_;
  TRB_Sock_Addr  local_address_;
};

/**
 * @class TRB_Asynch_Connect_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Connect.
 *
 */
class TPROACTOR_Export TRB_Asynch_Connect_Result
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// I/O handle for the connection.
  ACE_HANDLE connect_handle (void) const 
    {
      return this->handle();
    }

  /// The address to connect
  const ACE_Addr& remote_address () const
    {
      return this->remote_address_.get_ace_addr ();
    }

  /// The local address
  const ACE_Addr& local_address () const
    {
      return this->local_address_.get_ace_addr ();
    }
   
  virtual ~TRB_Asynch_Connect_Result ();

  TRB_Asynch_Connect_Result(TRB_Handler       *handler,
                            ACE_HANDLE         handle,
                            const ACE_Addr&    remote_sap,
                            const ACE_Addr&    local_sap,
                            const void        *act,
                            const void        *completion_key,
                            int                priority,
                            int                signal_number,
                            int                flags);
private:
  
  /// replace later with union to support diffrent address types 
  TRB_Sock_Addr  remote_address_;
  TRB_Sock_Addr  local_address_;
};

/**
 * @class TRB_Asynch_Read_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Read_Dgram::Result class.
 *
 */
class TPROACTOR_Export TRB_Asynch_Read_Dgram_Result 
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:
  /// The number of bytes which were requested at the start of the
  /// asynchronous read.
  size_t bytes_to_read (void) const
    {
      return this->bytes_requested();
    }

  /// Message block which contains the read data.
  ACE_Message_Block *message_block (void) const
    {
      return this->get_message_block_ptr();
    }

  /// The address of where the packet came from
  const ACE_Addr &  remote_address () const 
    {
      return this->remote_address_.get_ace_addr ();
    }

  /// The address of where the packet came from
  int remote_address (ACE_Addr& addr) const
    {
        return TRB_Sock_Addr::copy_addr (addr,
                                         this->remote_address ());
    }

  /// The flags using in the read
  int flags(void) const
    {
      return this->recv_flags_;
    }

  int set_flags(int recv_flags)
    {
      return this->recv_flags_ = recv_flags;
    }



  virtual ~TRB_Asynch_Read_Dgram_Result (void);
  TRB_Asynch_Read_Dgram_Result (TRB_Handler       *handler,
                                ACE_HANDLE         handle,
                                const Buffer_Info& buf_info,
                                size_t             bytes_requested,
                                int                recv_flags,
                                int                protocol_family,
                                const void        *act,
                                const void        *completion_key,
                                int                priority,
                                int                signal_number,
                                int                scatter_flags);

private:
  int            recv_flags_;             // additional flags 
  TRB_Sock_Addr  remote_address_;
};

/**
 * @class TRB_Asynch_Write_Dgram_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Write_Dgram::Result class.
 *
 */
class TPROACTOR_Export TRB_Asynch_Write_Dgram_Result
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// The number of bytes which were requested at the start of the
  /// asynchronous write.
  size_t bytes_to_write (void) const
    {
      return this->bytes_requested();
    }

  /// Message block which contains the write data.
  ACE_Message_Block *message_block (void) const
    {
      return this->get_message_block_ptr();
    }

  /// The flags using in the write
  int flags(void) const
    {
      return this->send_flags_;
    }

  /// The address to send
  const ACE_Addr &  remote_address () const
    {
      return this->remote_address_.get_ace_addr ();
    }

  /// The address to send
  int remote_address (ACE_Addr& addr) const
    {
        return TRB_Sock_Addr::copy_addr (addr,
                                         this->remote_address ());
    }


  virtual ~TRB_Asynch_Write_Dgram_Result (void);

  TRB_Asynch_Write_Dgram_Result (TRB_Handler       *handler,
                                 ACE_HANDLE         handle,
                                 const ACE_Addr &   remote_sap,
                                 const Buffer_Info& buf_info,
                                 size_t             bytes_requested,
                                 int                send_flags,
                                 const void        *act,
                                 const void        *completion_key,
                                 int                priority,
                                 int                signal_number,
                                 int                gather_flags);
private:
  int            send_flags_;             // additional flags 
  TRB_Sock_Addr  remote_address_;
};

/**
 * @class TRB_Asynch_Transmit_File_Result
 *
 * @brief Abstract base class for all the concrete implementation
 * classes that provide different implementations for the
 * TRB_Asynch_Transmit_File::Result.
 *
 */
class TPROACTOR_Export TRB_Asynch_Transmit_File_Result 
    : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

/**
 * @class Header_And_Trailer
 *
 * @brief The class defines a data structure that contains pointers
 * to data to send before and after the file data is sent.
 *
 * This class provides a wrapper over TRANSMIT_FILE_BUFFERS
 * and provided a consistent use of ACE_Message_Blocks.
 */
  class TPROACTOR_Export Header_And_Trailer
  {

  public:
    /// Constructor.
    Header_And_Trailer (ACE_Message_Block *header = 0,
                        size_t header_bytes = 0,
                        ACE_Message_Block *trailer = 0,
                        size_t trailer_bytes = 0);

    /// Destructor
    virtual ~Header_And_Trailer (void);

    /// This method allows all the member to be set in one fell swoop.
    void header_and_trailer (ACE_Message_Block *header = 0,
                             size_t header_bytes = 0,
                             ACE_Message_Block *trailer = 0,
                             size_t trailer_bytes = 0);

    /// Get header which goes before the file data.
    ACE_Message_Block *header (void) const;

    /// Set header which goes before the file data.
    void header (ACE_Message_Block *message_block);

    /// Get size of the header data.
    size_t header_bytes (void) const;

    /// Set size of the header data.
    void header_bytes (size_t bytes);

    /// Get trailer which goes after the file data.
    ACE_Message_Block *trailer (void) const;

    /// Set trailer which goes after the file data.
    void trailer (ACE_Message_Block *message_block);

    /// Get size of the trailer data.
    size_t trailer_bytes (void) const;

    /// Set size of the trailer data.
    void trailer_bytes (size_t bytes);

    /// Conversion routine.
    ACE_LPTRANSMIT_FILE_BUFFERS transmit_buffers (void);

  protected:
    /// Header data.
    ACE_Message_Block *header_;

    /// Size of header data.
    size_t header_bytes_;

    /// Trailer data.
    ACE_Message_Block *trailer_;

    /// Size of trailer data.
    size_t trailer_bytes_;

    /// Target data structure.
    ACE_TRANSMIT_FILE_BUFFERS transmit_buffers_;
  };

  /// Socket used for transmitting the file.
  ACE_HANDLE socket (void) const
    {
      return this->handle();
    }
  
  /// File from which the data is read.
  ACE_HANDLE file (void) const
    {
      return this->file_;
    }
  
  /// Header and trailer data associated with this transmit file.
  Header_And_Trailer *header_and_trailer (void) const
    {
      return this->header_and_trailer_;
    }
     
  
  /// The number of bytes which were requested at the start of the
  /// asynchronous transmit file.
  size_t bytes_to_write (void) const
    {
      return this->bytes_requested();
    }


  /// Number of bytes per send requested at the start of the transmit
  /// file.
  size_t bytes_per_send (void) const
    {
      return this->bytes_per_send_;
    }

  /// Flags which were passed into transmit file.
  u_long flags (void) const
    {
      return this->flags_;
    }


  virtual ~TRB_Asynch_Transmit_File_Result (void);

  TRB_Asynch_Transmit_File_Result (TRB_Handler        *handler,
                                   ACE_HANDLE          socket,
                                   ACE_HANDLE          file,
                                   Header_And_Trailer *header_and_trailer,
                                   u_long              offset,
                                   u_long              offset_high,
                                   size_t              bytes_to_write,
                                   size_t              bytes_per_send,
                                   u_long              transmit_flags,
                                   const void         *act,
                                   const void         *completion_key,
                                   int                 priority,
                                   int                 signal_number);
private:

  /// File I/O handle.
  ACE_HANDLE file_;

  /// Header and trailer data associated with this transmit file.
  Header_And_Trailer *header_and_trailer_;


  /// Number of bytes per send requested at the start of the transmit
  /// file.
  size_t bytes_per_send_;

  /// Flags which were passed into transmit file.
  u_long flags_;
};

/**
 * @class TRB_Asynch_Timer
 *
 * @brief This class is posted to the completion port when a timer
 * expires. When the complete method of this object is
 * called, the <handler>'s handle_timeout method will be
 * called.
 */
class TPROACTOR_Export TRB_Asynch_Timer 
  : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:

  /// The time value which were requested at the start of the
  /// asynchronous timer
  const ACE_Time_Value&  time(void) const
    {
      return this->time_;
    }

  virtual ~TRB_Asynch_Timer (void);

  TRB_Asynch_Timer (TRB_Handler          *handler,
                    const ACE_Time_Value &tv,
                    const void           *act,
                    const void           *completion_key,
                    int                   priority,
                    int                   signal_number);

private:
  /// Time value requested by caller
  ACE_Time_Value time_;
};

/**
 * @class TRB_Wakeup_Completion
 *
 * @brief This class is posted to the completion port when a timer
 * expires. When the complete method of this object is
 * called, the <handler>'s handle_timeout method will be
 * called.
 */
class TPROACTOR_Export TRB_Wakeup_Completion 
  : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:


  virtual ~TRB_Wakeup_Completion (void);

  TRB_Wakeup_Completion (TRB_Handler          *handler,
                         const void           *act,
                         const void           *completion_key,
                         int                   priority,
                         int                   signal_number);

};

/**
 * @class TRB_Asynch_User_Result
 *
 * @brief This class is posted to the completion port when a timer
 * expires. When the complete method of this object is
 * called, the <handler>'s handle_timeout method will be
 * called.
 */
class TPROACTOR_Export TRB_Asynch_User_Result 
  : public TRB_Asynch_Result
{
private:
  virtual int dispatch (void);

public:


  virtual ~TRB_Asynch_User_Result (void);

  TRB_Asynch_User_Result (TRB_Handler        *handler,
                          ACE_HANDLE          handle,
                          const Buffer_Info&  buf_info,
                          size_t              bytes_requested,
                          u_long              offset,
                          u_long              offset_high,
                          const void         *act,
                          const void         *completion_key,
                          int                 priority,
                          int                 signal_number);

};

// ****************************************************************
//   Asynchronous operations
// ****************************************************************
/**
 * @class TRB_Asynch_Operation
 *
 * @brief This is an interface base class for all asynch
 * operations. The resposiblility of this class is to forward
 * all methods to its delegation/implementation class, e.g.,
 * TRB_WIN32_Asynch_Operation or TRB_POSIX_Asynch_Operation.
 *
 * There are some attributes and functionality which is common
 * to all asychronous operations. The delegation classes of this
 * class will factor out this code.
 */
class TPROACTOR_Export TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;
  /**
   * Initializes the factory with information which will be used with
   * each asynchronous call.  If (<handle> == ACE_INVALID_HANDLE),
   * <TRB_Handler::handle> will be called on the <handler> to get the
   * correct handle.
   */
  virtual int open (TRB_Handler&  handler,
                    ACE_HANDLE    handle,
                    const void   *completion_key,
                    TRB_Proactor *proactor);

  /**
   * (Attempts to) cancel the asynchronous operation pending against
   * the <handle> registered with this Operation.
   *
   * All completion notifications for the I/O operations will occur
   * normally.
   *
   * = Return Values:
   *
   * -1 : Operation failed. (can get only in POSIX).
   *  0 : All the operations were cancelled.
   *  1 : All the operations were already finished in this
   *      handle. Unable to cancel them.
   *  2 : Atleast one of the requested operations cannot be
   *      cancelled.
   *
   * There is slight difference in the semantics between NT and POSIX
   * platforms which is given below.
   *
   * = Win32 :
   *
   *   cancels all pending accepts operations that were issued by the
   *   calling thread.  The function does not cancel asynchronous
   *   operations issued by other threads.
   *   All I/O operations that are canceled will complete with the
   *   error ERROR_OPERATION_ABORTED.
   *
   * = POSIX:
   *
   *   Attempts to cancel one or more asynchronous I/O requests
   *   currently outstanding against the <handle> registered in this
   *   operation.
   *   For requested operations that are successfully canceled, the
   *   associated  error  status is set to ECANCELED.
   */
  virtual int cancel (void);

  /**
   * unregister the factory 
   */
  virtual int close (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const = 0;

  // = Access methods.

  /// Return the underlying proactor.
  TRB_Proactor *proactor (void) const;

  /// Return the underlying handler.
  TRB_Handler  *handler (void) const;

  /// Return the underlying handle.
  ACE_HANDLE    handle (void) const; 

  /// Return the completion key associated with this oparations
  const void   *completion_key (void) const; 

  /// Destructor.
  virtual ~TRB_Asynch_Operation (void);

protected:
  /// Constructor.
  TRB_Asynch_Operation (void);

  ACE_HANDLE     handle_;
  TRB_Handler   *handler_;
  TRB_Proactor  *proactor_;
  const void    *completion_key_;
};


/**
 * @class TRB_Asynch_Read_Stream
 *
 * @brief This class is a factory for starting off asynchronous reads
 * on a stream. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <read>s can
 * started using this class.  An TRB_Asynch_Read_Stream::Result
 * will be passed back to the <handler> when the asynchronous
 * reads completes through the <TRB_Handler::handle_read_stream>
 * callback.
 */
class TPROACTOR_Export TRB_Asynch_Read_Stream
    : public TRB_Asynch_Operation
{
public:

  typedef TRB_Asynch_Read_Stream_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Read_Stream (void);

  /// Destructor
  virtual ~TRB_Asynch_Read_Stream (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous read.  Upto <bytes_to_read> will
   * be read and stored in the <message_block>. <message_block>'s
   * <wr_ptr> will be updated to reflect the added bytes if the read
   * operation is successful completed. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, <priority> is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int read (ACE_Message_Block &message_block,
            size_t num_bytes_to_read,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int read  (const Buffer_Info& buf_info,
             size_t num_bytes_to_read,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  /**
  * Same as above but with scatter support, through chaining of composite
  * message blocks using the continuation field.
  */
  int readv (ACE_Message_Block &message_block,
             size_t num_bytes_to_read,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);


  /**
  * Same as above but operations require to read exactly
  * spesified number of bytes
  */
  int read_n (ACE_Message_Block& message_block,
            size_t bytes_to_read,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int read_n (const Buffer_Info& buf_info,
            size_t bytes_to_read,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int readv_n (ACE_Message_Block &message_block,
             size_t bytes_to_read,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

};

/**
 * @class TRB_Asynch_Write_Stream
 *
 * @brief This class is a factory for starting off asynchronous writes
 * on a stream. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <writes>s can
 * started using this class.  An TRB_Asynch_Write_Stream::Result
 * will be passed back to the <handler> when the asynchronous
 * write completes through the
 * <TRB_Handler::handle_write_stream> callback.
 */
class TPROACTOR_Export TRB_Asynch_Write_Stream 
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Write_Stream_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Write_Stream (void);

  /// Destructor.
  virtual ~TRB_Asynch_Write_Stream (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous write.  Upto <bytes_to_write>
   * will be written from the <message_block>. Upon successful completion
   * of the write operation, <message_block>'s <rd_ptr> is updated to
   * reflect the data that was written. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this argument is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int write (ACE_Message_Block &message_block,
             size_t bytes_to_write,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  int write (const Buffer_Info& buf_info,
             size_t bytes_to_write,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  /**
  * Same as above but with gather support, through chaining of composite
  * message blocks using the continuation field.
  */
  int writev (ACE_Message_Block &message_block,
              size_t bytes_to_write,
              const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);

  /**
  * Same as above but operations require to read exactly
  * spesified number of bytes
  */
  int write_n (ACE_Message_Block &message_block,
             size_t bytes_to_write,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  int write_n (const Buffer_Info& buf_info,
             size_t bytes_to_write,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  int writev_n (ACE_Message_Block &message_block,
              size_t bytes_to_write,
              const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);
};

/**
 * @class TRB_Asynch_Read_File
 *
 * @brief This class is a factory for starting off asynchronous reads
 * on a file. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <read>s can
 * started using this class. An TRB_Asynch_Read_File::Result
 * will be passed back to the <handler> when the asynchronous
 * reads completes through the <TRB_Handler::handle_read_file>
 * callback.
 * This class differs slightly from TRB_Asynch_Read_Stream as it
 * allows the user to specify an offset for the read.
 */
class TPROACTOR_Export TRB_Asynch_Read_File 
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Read_File_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Read_File (void);

  /// Destructor.
  virtual ~TRB_Asynch_Read_File (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous read.  Upto <bytes_to_read> will
   * be read and stored in the <message_block>.  The read will start
   * at <offset> from the beginning of the file. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this argument is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int read (ACE_Message_Block& message_block,
            size_t bytes_to_read,
            u_long offset = 0,
            u_long offset_high = 0,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int read (const Buffer_Info& buf_info,
            size_t bytes_to_read,
            u_long offset = 0,
            u_long offset_high = 0,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  /**
  * Same as above but with scatter support, through chaining of composite
  * message blocks using the continuation field.
  * NOTE: In win32 Each data block payload must be at least the size of a system
  * memory page and must be aligned on a system memory page size boundary
  */
  int readv (ACE_Message_Block &message_block,
             size_t bytes_to_read,
             u_long offset = 0,
             u_long offset_high = 0,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);
};

/**
 * @class TRB_Asynch_Write_File
 *
 * @brief This class is a factory for starting off asynchronous writes
 * on a file. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <write>s can be
 * started using this class.  A TRB_Asynch_Write_File::Result
 * will be passed back to the <handler> when the asynchronous
 * writes completes through the <TRB_Handler::handle_write_file>
 * callback.
 * This class differs slightly from TRB_Asynch_Write_Stream as
 * it allows the user to specify an offset for the write.
 */
class TPROACTOR_Export TRB_Asynch_Write_File 
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Write_File_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Write_File (void);

  /// Destructor.
  virtual ~TRB_Asynch_Write_File (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous write.  Upto <bytes_to_write>
   * will be written from the <message_block>, starting at the
   * block's <rd_ptr>.  The write will go to the file, starting
   * <offset> bytes from the beginning of the file. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int write (ACE_Message_Block &message_block,
             size_t bytes_to_write,
             u_long offset = 0,
             u_long offset_high = 0,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  int write (const Buffer_Info& buf_info,
             size_t bytes_to_write,
             u_long offset = 0,
             u_long offset_high = 0,
             const void *act = 0,
             int priority = 0,
             int signal_number = ACE_SIGRTMIN);

  /**
  * Same as above but with gather support, through chaining of composite
  * message blocks using the continuation field.
  * NOTE: In win32 Each data block payload must be at least the size of a system
  * memory page and must be aligned on a system memory page size boundary
  */
  int writev (ACE_Message_Block &message_block,
              size_t bytes_to_write,
              u_long offset = 0,
              u_long offset_high = 0,
              const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);
};

/**
 * @class TRB_Asynch_Accept
 *
 * @brief This class is a factory for starting off asynchronous accepts
 * on a listen handle. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <accept>s can
 * started using this class.  A TRB_Asynch_Accept::Result will
 * be passed back to the <handler> when the asynchronous accept
 * completes through the <TRB_Handler::handle_accept>
 * callback.
 */
class TPROACTOR_Export TRB_Asynch_Accept
    : public TRB_Asynch_Operation
{
public:

  typedef TRB_Asynch_Accept_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Accept (void);

  /// Destructor.
  virtual ~TRB_Asynch_Accept (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous accept.  The asynchronous accept
   * call also allows any initial data to be returned to the
   * <handler>.  Upto <bytes_to_read> will be read and stored in the
   * <message_block>.  The <accept_handle> will be used for the
   * <accept> call.  If (<accept_handle> == INVALID_HANDLE), a new
   * handle will be created. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this is a no-op.
   *
   * <message_block> must be specified. This is because the address of
   * the new connection is placed at the end of this buffer.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int accept (ACE_Message_Block &message_block,
              size_t bytes_to_read,
              const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);
              
  int accept (const Buffer_Info & buf_info,
              size_t bytes_to_read,
              const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);

  int accept (const void *act = 0,
              int priority = 0,
              int signal_number = ACE_SIGRTMIN);


};

/**
 * @class TRB_Asynch_Connect
 *
 * @brief This class is a factory for starting off asynchronous connects
 * This class forwards all methods to its implementation class.
 *
 * Once @c open is called, multiple asynchronous connect operationss can
 * started using this class.  A TRB_Asynch_Connect::Result will
 * be passed back to the associated TRB_Handler when the asynchronous connect
 * completes through the TRB_Handler::handle_connect() callback.
 */
class TPROACTOR_Export TRB_Asynch_Connect 
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Connect_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Connect (void);

  /// Destructor.
  virtual ~TRB_Asynch_Connect (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * Initializes the factory with information which will be used with
   * each asynchronous call.
   *
   * @note @arg handle is ignored and should be @c ACE_INVALID_HANDLE.
   */
  virtual int open (TRB_Handler &handler,
                    ACE_HANDLE handle = ACE_INVALID_HANDLE,
                    const void *completion_key = 0,
                    TRB_Proactor *proactor = 0);

  /**
   * This starts off an asynchronous Connect.
   */
  int connect (ACE_HANDLE connect_handle,
               const ACE_Addr & remote_sap,
               const ACE_Addr & local_sap,
               int  reuse_addr,
               const void *act=0,
               int priority = 0,
               int signal_number = ACE_SIGRTMIN);

private:
  int  prepare_connect(ACE_HANDLE & handle,
                  const ACE_Addr & remote_sap,
                  const ACE_Addr & local_sap,
                  int  reuse_addr);


};


/**
 * @class TRB_Asynch_Read_Dgram
 *
 * @brief This class is a factory for starting off asynchronous reads
 * on a UDP socket. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <read>s can be
 * started using this class.  An TRB_Asynch_Read_Dgram::Result
 * will be passed back to the <handler> when the asynchronous
 * reads completes through the <TRB_Handler::handle_read_dgram>
 * callback.
 */
class TPROACTOR_Export TRB_Asynch_Read_Dgram 
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Read_Dgram_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Read_Dgram (void);

  /// Destructor
  virtual ~TRB_Asynch_Read_Dgram (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /** This starts off an asynchronous read.  Upto
   * <message_block->total_size()> will be read and stored in the
   * <message_block>.  <message_block>'s <wr_ptr> will be updated to reflect
   * the added bytes if the read operation is successfully completed.
   * Return code of 1 means immediate success and <number_of_bytes_recvd>
   * will contain number of bytes read.  The <TRB_Handler::handle_read_dgram>
   * method will still be called.  Return code of 0 means the IO will
   * complete proactively.  Return code of -1 means there was an error, use
   * errno to get the error code.
   *
   * Scatter/gather is supported on WIN32 by using the <message_block->cont()>
   * method.  Up to ACE_IOV_MAX <message_block>'s are supported.  Upto
   * <message_block->size()> bytes will be read into each <message block> for
   * a total of <message_block->total_size()> bytes.  All <message_block>'s
   * <wr_ptr>'s will be updated to reflect the added bytes for each
   * <message_block>
   *
   * Priority of the operation is specified by <priority>. On POSIX4-Unix,
   * this is supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, <priority> is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int  recv (ACE_Message_Block *message_block,
             size_t             bytes_to_read,
             int                recv_flags,
             int                protocol_family = PF_INET,
             const void        *act = 0,
             int                priority = 0,
             int                signal_number = ACE_SIGRTMIN,
             int                scatter_flags = 1);

  int  recv (const Buffer_Info& buf_info,
             size_t             bytes_to_read,
             int                recv_flags,
             int                protocol_family = PF_INET,
             const void        *act = 0,
             int                priority = 0,
             int                signal_number = ACE_SIGRTMIN,
             int                scatter_flags = 1);
};

/**
 * @class TRB_Asynch_Write_Dgram
 *
 * @brief This class is a factory for starting off asynchronous writes
 * on a UDP socket. This class forwards all methods to its
 * implementation class.
 *
 * Once <open> is called, multiple asynchronous <writes>s can
 * started using this class.  An TRB_Asynch_Write_Dgram::Result
 * will be passed back to the <handler> when the asynchronous
 * write completes through the
 * <TRB_Handler::handle_write_dgram> callback.
 */
class TPROACTOR_Export TRB_Asynch_Write_Dgram 
  : public TRB_Asynch_Operation
{
public:

  typedef TRB_Asynch_Write_Dgram_Result Result;

  /// A do nothing constructor.
  TRB_Asynch_Write_Dgram (void);

  /// Destructor.
  virtual ~TRB_Asynch_Write_Dgram (void);

  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /** This starts off an asynchronous send.  Upto
   * <message_block->total_length()> will be sent.  <message_block>'s
   * <rd_ptr> will be updated to reflect the sent bytes if the send operation
   * is successfully completed.
   * Return code of 1 means immediate success and <number_of_bytes_sent>
   * is updated to number of bytes sent.  The <TRB_Handler::handle_write_dgram>
   * method will still be called.  Return code of 0 means the IO will
   * complete proactively.  Return code of -1 means there was an error, use
   * errno to get the error code.
   *
   * Scatter/gather is supported on WIN32 by using the <message_block->cont()>
   * method.  Up to ACE_IOV_MAX <message_block>'s are supported.  Upto
   * <message_block->length()> bytes will be sent from each <message block>
   * for a total of <message_block->total_length()> bytes.  All
   * <message_block>'s <rd_ptr>'s will be updated to reflect the bytes sent
   * from each <message_block>.
   *
   * Priority of the operation is specified by <priority>. On POSIX4-Unix,
   * this is supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this argument is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int send (ACE_Message_Block  * message_block,
            size_t               bytes_to_write,
            int                  flags,
            const ACE_Addr&      remote_addr,
            const void *         act = 0,
            int                  priority = 0,
            int                  signal_number = ACE_SIGRTMIN,
            int                  gather_flags = 1);

  int send (const Buffer_Info&   buf_info,
            size_t               bytes_to_write,
            int                  flags,
            const ACE_Addr&      remote_addr,
            const void *         act = 0,
            int                  priority = 0,
            int                  signal_number = ACE_SIGRTMIN,
            int                  gather_flags = 1);
};

/**
 * @class TRB_Asynch_Transmit_File
 *
 * @brief This class is a factory for starting off asynchronous
 * transmit files on a stream.
 *
 * Once <open> is called, multiple asynchronous <transmit_file>s
 * can started using this class.  A
 * TRB_Asynch_Transmit_File::Result will be passed back to the
 * <handler> when the asynchronous transmit file completes
 * through the <TRB_Handler::handle_transmit_file> callback.
 * The transmit_file function transmits file data over a
 * connected network connection. The function uses the operating
 * system's cache manager to retrieve the file data. This
 * function provides high-performance file data transfer over
 * network connections.  This function would be of great use in
 * a Web Server, Image Server, etc.
 */
class TPROACTOR_Export TRB_Asynch_Transmit_File
    : public TRB_Asynch_Operation
{
public:
  typedef TRB_Asynch_Transmit_File_Result Result;

  typedef 
    TRB_Asynch_Transmit_File_Result::Header_And_Trailer 
    Header_And_Trailer;


  /// A do nothing constructor.
  TRB_Asynch_Transmit_File (void);

  /// Destructor.
  virtual ~TRB_Asynch_Transmit_File (void);


  /**
   *  get supported operations mask 
   *  see TRB_Asynch_Result::OpCode
   */
  virtual int supported_operations (void) const;

  /**
   * This starts off an asynchronous transmit file.  The <file> is a
   * handle to an open file.  <header_and_trailer> is a pointer to a
   * data structure that contains pointers to data to send before and
   * after the file data is sent.  Set this parameter to 0 if you only
   * want to transmit the file data.  Upto <bytes_to_write> will be
   * written to the <socket>.  If you want to send the entire file,
   * let <bytes_to_write> = 0.  <bytes_per_send> is the size of each
   * block of data sent per send operation.  Please read the Win32
   * documentation on what the flags should be. Priority of the
   * operation is specified by <priority>. On POSIX4-Unix, this is
   * supported. Works like <nice> in Unix. Negative values are not
   * allowed. 0 means priority of the operation same as the process
   * priority. 1 means priority of the operation is one less than
   * process. And so forth. On Win32, this is a no-op.
   * <signal_number> is the POSIX4 real-time signal number to be used
   * for the operation. <signal_number> ranges from ACE_SIGRTMIN to
   * ACE_SIGRTMAX. This argument is a no-op on non-POSIX4 systems.
   */
  int transmit_file (ACE_HANDLE file,
                     Header_And_Trailer *header_and_trailer = 0,
                     size_t bytes_to_write = 0,
                     u_long offset = 0,
                     u_long offset_high = 0,
                     size_t bytes_per_send = 0,
                     u_long flags = 0,
                     const void *act = 0,
                     int priority = 0,
                     int signal_number = ACE_SIGRTMIN);
};

// ****************************************************************
//   Asynchronous handlers
// ****************************************************************

/**
 * @class TRB_Handler
 *
 * @brief This base class defines the interface for receiving the
 * results of asynchronous operations.
 *
 * Subclasses of this class will fill in appropriate methods.
 */
class TPROACTOR_Export TRB_Handler
{
public:
  /// A do nothing constructor.
  TRB_Handler (void);

  /// A do nothing constructor which allows proactor to be set to \<p\>.
  TRB_Handler (TRB_Proactor *p);

  /// Virtual destruction.
  virtual ~TRB_Handler (void);

  /// This method will be called when an asynchronous read completes on
  /// a stream.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This method will be called when an asynchronous write completes
  /// on a UDP socket.
  virtual void handle_write_dgram (const TRB_Asynch_Write_Dgram::Result &result);

  /// This method will be called when an asynchronous read completes on
  /// a UDP socket.
  virtual void handle_read_dgram (const TRB_Asynch_Read_Dgram::Result &result);

  /// This method will be called when an asynchronous write completes
  /// on a stream.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

  /// This method will be called when an asynchronous read completes on
  /// a file.
  virtual void handle_read_file (const TRB_Asynch_Read_File::Result &result);

  /// This method will be called when an asynchronous write completes
  /// on a file.
  virtual void handle_write_file (const TRB_Asynch_Write_File::Result &result);

  /// This method will be called when an asynchronous accept completes.
  virtual void handle_accept (const TRB_Asynch_Accept::Result &result);

  /// This method will be called when an asynchronous connect completes.
  virtual void handle_connect (const TRB_Asynch_Connect::Result &result);

  /// This method will be called when an asynchronous transmit file
  /// completes.
  virtual void handle_transmit_file (const TRB_Asynch_Transmit_File::Result &result);

  /// Called when timer expires.  <tv> was the requested time value and
  /// <act> is the ACT passed when scheduling the timer.
  virtual void handle_time_out (const ACE_Time_Value &tv,
                                const void *act = 0);

  virtual void handle_user_operation(const TRB_Asynch_User_Result& result);
  
  /**
   * This is method works with the <run_event_loop> of the
   * TRB_Proactor. A special <Wake_Up_Completion> is used to wake up
   * all the threads that are blocking for completions.
   */
  virtual void handle_wakeup (void);

  /// Get the proactor associated with this handler.
  TRB_Proactor *proactor (void);

  /// Set the proactor.
  void proactor (TRB_Proactor *p);

  /**
   * Get the I/O handle used by this <handler>. This method will be
   * called by the TRB_Asynch_* classes when an ACE_INVALID_HANDLE is
   * passed to <open>.
   */
  virtual ACE_HANDLE handle (void) const;

  /// Set the ACE_HANDLE value for this Handler.
  virtual void handle (ACE_HANDLE);
  
  virtual ACE_Allocator *allocator (void);
 
protected:
  /// The proactor associated with this handler.
  TRB_Proactor *proactor_;

  /// The ACE_HANDLE in use with this handler.
  ACE_HANDLE    handle_;
};


// Forward declarations
//template <class HANDLER>
//class TRB_Asynch_Acceptor;

/**
 * @class TRB_Service_Handler
 *
 * @brief This base class defines the interface for the
 * TRB_Asynch_Acceptor to call into when new connection are
 * accepted.
 *
 * Subclasses of this class will fill in appropriate methods to
 * define application specific behavior.
 */
template <typename ADDR>
class TRB_Service_Handler_T : public TRB_Handler
{
public:
  typedef ADDR  ADDRESS;

  /// A do nothing constructor.
  TRB_Service_Handler_T (void)  
  {}

  /// Virtual destruction.
  virtual ~TRB_Service_Handler_T (void) 
  {}

  /**
   * <open> is called by TRB_Asynch_Acceptor to initialize a new
   * instance of TRB_Service_Handler that has been created after the
   * new connection is accepted. The handle for the new connection is
   * passed along with the initial data that may have shown up.
   */
  virtual void open (ACE_HANDLE          /*new_handle*/,
                     ACE_Message_Block & /*message_block*/)
  {}

  // protected:
  // This should be corrected after the correct semantics of the
  // friend has been figured out.

  /// Called by TRB_Asynch_Acceptor to pass the addresses of the new
  /// connections. 
  virtual void addresses (const ADDRESS& remote_address,
                          const ADDRESS& local_address) = 0;

  //{}


  /// Called by TRB_Asynch_Acceptor to pass the act.
  virtual void act (const void *)
  {}

};

typedef 
    TRB_Service_Handler_T<ACE_INET_Addr> 
    TRB_Service_Handler;

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (__ACE_INLINE__)
#include "TProactor/Asynch_IO.inl"
#endif /* __ACE_INLINE__ */

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS*/
#include "ace/post.h"
#endif //TPROACTOR_ASYNCH_IO_H 
