// Asynch_IO.cpp

#include "TProactor/Asynch_IO.h"

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))
// This only works on platforms with Asynchronous IO

#include "TProactor/Proactor.h"
#include "ace/Message_Block.h"
#include "ace/OS_NS_sys_socket.h"

#if !defined (__ACE_INLINE__)
#include "TProactor/Asynch_IO.inl"
#endif /* __ACE_INLINE__ */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


// ***********************************************************************
// Asynch_Result
// ***********************************************************************
TRB_Asynch_Result::TRB_Asynch_Result (int                op_code,
                                      int                op_flags,
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info&  buf_info,
                                      size_t             bytes_requested,
                                      u_long             offset,
                                      u_long             offset_high,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number)
: op_code_            (op_code)
, op_flags_           (op_flags)
, handler_            (handler)
, handle_             (handle)
, buf_info_           (buf_info)
, bytes_requested_    (bytes_requested)
, offset_             (offset)
, offset_high_        (offset_high)
, act_                (act)
, completion_key_     (completion_key)
, priority_           (priority)
, signal_number_      (signal_number)
, error_              (0)
, bytes_transferred_  (0)
{
    switch (buf_info_.get_iov_count ())
    {
    case -1:  // message block
        ACE_CLR_BITS (op_flags, FLG_DIRECT_BUFFERS);
        break;
    case  0:  // simple buffer
        ACE_SET_BITS (op_flags_, FLG_DIRECT_BUFFERS);
        break;
    default:  // iovect
        ACE_SET_BITS (op_flags_, FLG_DIRECT_BUFFERS | FLG_IOVECT);
        break;
    }
}

TRB_Asynch_Result::~TRB_Asynch_Result (void)
{
}

int
TRB_Asynch_Result::dispatch ()
{
  return 0;
}


void
TRB_Asynch_Result::move_wr_ptrs ()
{
  ACE_Message_Block* mb = this->get_message_block_ptr();
  if (mb == 0)
      return;  //  Direct Buffers 

  size_t num_bytes = this->bytes_transferred();
 

  // Appropriately move the pointers in the message block.
  if (!this->is_iov_operation ())
    {
      mb->wr_ptr (num_bytes);
    }
  else
    {
      for (;(mb != 0) && (num_bytes > 0);   mb = mb->cont ())
        {
          size_t len_part = mb->space ();

          if (len_part == 0)
            continue; 

          if (len_part > num_bytes)
            len_part = num_bytes;

          mb->wr_ptr (len_part);

          num_bytes -= len_part;
        }
    }
}

void
TRB_Asynch_Result::move_rd_ptrs ()
{
  ACE_Message_Block* mb = this->get_message_block_ptr();
  if (mb == 0)
      return;  //  Direct Buffers 

  size_t num_bytes = this->bytes_transferred();

  // Appropriately move the pointers in the message block.
  if (!this->is_iov_operation ())
    {
      mb->rd_ptr (num_bytes);
    }
  else
    {
      for (;(mb != 0) && (num_bytes > 0);   mb = mb->cont ())
        {
          size_t len_part = mb->length ();

          if (len_part == 0)
            continue; 

          if (len_part > num_bytes)
            len_part = num_bytes;

          mb->rd_ptr (len_part);

          num_bytes -= len_part;
        }
    }
}

// ***********************************************************************
// Asynch_Read_Stream_Result
// ***********************************************************************

TRB_Asynch_Read_Stream_Result::TRB_Asynch_Read_Stream_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info&  buf_info,
                                      size_t             bytes_requested,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                op_flags)
  : TRB_Asynch_Result (OP_READ_STREAM ,
                       op_flags & (FLG_IOVECT | FLG_EXACTLY_BYTES),
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       0,  // offset,
                       0,  // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
{
}


TRB_Asynch_Read_Stream_Result::TRB_Asynch_Read_Stream_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info&  buf_info,
                                      size_t             bytes_requested,
                                      u_long             offset,
                                      u_long             offset_high,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                op_flags)
  : TRB_Asynch_Result (OP_READ_FILE,
                       op_flags & (FLG_IOVECT | FLG_EXACTLY_BYTES),
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       offset,
                       offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
{
}

TRB_Asynch_Read_Stream_Result::~TRB_Asynch_Read_Stream_Result ()
{
}

int
TRB_Asynch_Read_Stream_Result::dispatch (void)
{
  // Appropriately move the pointers in the message block.
  // wr_ptr after read !
  this->move_wr_ptrs ();

  // Call the application handler.
  if (this->op_code() == OP_READ_STREAM)
    this->get_handler()->handle_read_stream (*this);
  else
    this->get_handler()->handle_read_file (*this);

  return 0;
}


// ***********************************************************************
// Asynch_Write_Stream_Result
// ***********************************************************************
TRB_Asynch_Write_Stream_Result::TRB_Asynch_Write_Stream_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info& buf_info,
                                      size_t             bytes_requested,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                op_flags)
  : TRB_Asynch_Result (OP_WRITE_STREAM,
                       op_flags & (FLG_IOVECT | FLG_EXACTLY_BYTES),
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       0, // offset,
                       0, // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
{
}

TRB_Asynch_Write_Stream_Result::TRB_Asynch_Write_Stream_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info& buf_info,
                                      size_t             bytes_requested,
                                      u_long             offset,
                                      u_long             offset_high,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                op_flags)
  : TRB_Asynch_Result (OP_WRITE_FILE,
                       op_flags & (FLG_IOVECT | FLG_EXACTLY_BYTES),
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       offset,
                       offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
{
}

TRB_Asynch_Write_Stream_Result::~TRB_Asynch_Write_Stream_Result ()
{
}

int
TRB_Asynch_Write_Stream_Result::dispatch (void)
{
  // Appropriately move the pointers in the message block.
  // rd_ptr after write !
  this->move_rd_ptrs ();

  // Call the application handler.
  if (this->op_code() == OP_WRITE_STREAM)
    this->get_handler()->handle_write_stream (*this);
  else
    this->get_handler()->handle_write_file (*this);

  return 0;
}

// ***********************************************************************
// Asynch_Accept_Result
// ***********************************************************************

TRB_Asynch_Accept_Result::TRB_Asynch_Accept_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         listen_handle,
                                      const Buffer_Info& buf_info,
                                      size_t             bytes_requested,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number)
  : TRB_Asynch_Result (OP_ACCEPT,
                       0,
                       handler,
                       listen_handle,
                       buf_info,
                       bytes_requested,
                       0,            // offset,
                       0,            // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
  , accept_handle_    (ACE_INVALID_HANDLE)
  , remote_address_   ()
  , local_address_    ()
{
}

TRB_Asynch_Accept_Result::~TRB_Asynch_Accept_Result ()
{
}

void
TRB_Asynch_Accept_Result::set_accept_handle (ACE_HANDLE  accept_handle)
{
  this->accept_handle_ = accept_handle;
}

void
TRB_Asynch_Accept_Result::update_addresses (sockaddr   *local_addr,
                                            int         local_size,
                                            sockaddr   *remote_addr,
                                            int         remote_size)
{
  // this method is called on Windows when AcceptEx
  // completed and contains addresses in the buffer

  this->local_address_.set (local_addr, local_size);
  this->remote_address_.set (remote_addr, remote_size);
}

void
TRB_Asynch_Accept_Result::update_addresses (ACE_HANDLE handle)
{
  // this method is called on POSIX

  this->local_address_.getsockname (handle);        
  this->remote_address_.getpeername (handle);
}

int
TRB_Asynch_Accept_Result::dispatch (void)
{
    // Appropriately move the pointers in the message block.
    // wr_ptr after read !
    this->move_wr_ptrs ();

    if (!this->success())
    {
        ACE_OS::closesocket (this->accept_handle_);
        this->accept_handle_ = ACE_INVALID_HANDLE;

    }

    int addr_type = this->remote_address_.get_type ();
    if (addr_type == AF_ANY)
    {
        addr_type = this->local_address_.get_type ();
        this->remote_address_.set_type (addr_type);
    }

    this->get_handler()->handle_accept (*this);
    return 0;
}

// ***********************************************************************
// Asynch_Connect_Result
// ***********************************************************************

TRB_Asynch_Connect_Result::TRB_Asynch_Connect_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const ACE_Addr&    remote_sap,
                                      const ACE_Addr&    local_sap,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                op_flags)
                                      
  : TRB_Asynch_Result (OP_CONNECT,
                       op_flags,
                       handler,
                       handle,
                       Buffer_Info (0),
                       0,            // bytes_requested,
                       0,            // offset,
                       0,            // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
  , remote_address_   (remote_sap)
  , local_address_    (local_sap)
{
}

TRB_Asynch_Connect_Result::~TRB_Asynch_Connect_Result ()
{
}

int
TRB_Asynch_Connect_Result::dispatch (void)
{
    // Appropriately move the pointers in the message block.
    // rd_ptr after write !
    this->move_rd_ptrs ();

    if (this->success ()) 
    {
        ACE_HANDLE h = this->handle ();
        this->local_address_.getsockname (h);
    }
    else
    {
        // failure
        if (ACE_BIT_ENABLED(this->op_flags(), FLG_NEW_HANDLE))
        {
            ACE_OS::closesocket (this->handle());
            this->set_handle (ACE_INVALID_HANDLE);
        }
    }

    int addr_type = this->local_address_.get_type ();
    if (addr_type == AF_ANY)
    {
        addr_type = this->remote_address_.get_type ();
        this->local_address_.set_type (addr_type);
    }

    this->get_handler()->handle_connect (*this);
    return 0;
}


// ***********************************************************************
// Asynch_Read_Dgram_Result
// ***********************************************************************

TRB_Asynch_Read_Dgram_Result::TRB_Asynch_Read_Dgram_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const Buffer_Info& buf_info,
                                      size_t             bytes_requested,
                                      int                recv_flags,
                                      int                protocol_family,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                scatter_flags)
  : TRB_Asynch_Result (OP_READ_DGRAM,
                       scatter_flags ? FLG_IOVECT : 0,
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       0,  // offset,
                       0,  // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
  , recv_flags_       (recv_flags)
  , remote_address_   (protocol_family)
{
}

TRB_Asynch_Read_Dgram_Result::~TRB_Asynch_Read_Dgram_Result ()
{
}

int
TRB_Asynch_Read_Dgram_Result::dispatch (void)
{
  // Appropriately move the pointers in the message block.
  // wr_ptr after read !
  this->move_wr_ptrs ();

  // Call the application handler.
  this->get_handler()->handle_read_dgram (*this);
  return 0;
}


// ***********************************************************************
// Asynch_Write_Dgram_Result
// ***********************************************************************

TRB_Asynch_Write_Dgram_Result::TRB_Asynch_Write_Dgram_Result (
                                      TRB_Handler       *handler,
                                      ACE_HANDLE         handle,
                                      const ACE_Addr &   remote_sap,
                                      const Buffer_Info&  buf_info,
                                      size_t             bytes_requested,
                                      int                send_flags,
                                      const void        *act,
                                      const void        *completion_key,
                                      int                priority,
                                      int                signal_number,
                                      int                gather_flags)
  : TRB_Asynch_Result (OP_WRITE_DGRAM,
                       gather_flags ? FLG_IOVECT : 0,
                       handler,
                       handle,
                       buf_info,
                       bytes_requested,
                       0, // offset,
                       0, // offset_high,
                       act,
                       completion_key,
                       priority,
                       signal_number)
  , send_flags_       (send_flags)
  , remote_address_   (remote_sap)
{
}

TRB_Asynch_Write_Dgram_Result::~TRB_Asynch_Write_Dgram_Result ()
{
}

int
TRB_Asynch_Write_Dgram_Result::dispatch (void)
{
  // Appropriately move the pointers in the message block.
  // rd_ptr after write !
  this->move_rd_ptrs ();

  // Call the application handler.
  this->get_handler()->handle_write_dgram (*this);

  return 0;
}

// ***********************************************************************
// Asynch_Transmit_File_Result
// ***********************************************************************
TRB_Asynch_Transmit_File_Result::TRB_Asynch_Transmit_File_Result (
                                   TRB_Handler        *handler,
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
                                   int                 signal_number)
  : TRB_Asynch_Result  (OP_TRANSMIT_FILE,
                        0,
                        handler,
                        socket,
                        Buffer_Info (0),
                        bytes_to_write, // bytes_requested,
                        offset,
                        offset_high,
                        act,
                        completion_key,
                        priority,
                        signal_number)
   , file_              (file)
   , header_and_trailer_(header_and_trailer)
   , bytes_per_send_    (bytes_per_send)
   , flags_             (transmit_flags)
{
}
 
TRB_Asynch_Transmit_File_Result::~TRB_Asynch_Transmit_File_Result ()
{
}

int
TRB_Asynch_Transmit_File_Result::dispatch()
{
  // Call the application handler.
  this->get_handler()->handle_transmit_file (*this);

  return 0;
}

// ***********************************************************************
// Asynch_Transmit_File :: Header_And_Trailer
// ***********************************************************************
TRB_Asynch_Transmit_File_Result::
Header_And_Trailer::Header_And_Trailer (ACE_Message_Block *header,
                                        size_t             header_bytes,
                                        ACE_Message_Block *trailer,
                                        size_t             trailer_bytes)
  : header_ (header),
    header_bytes_ (header_bytes),
    trailer_ (trailer),
    trailer_bytes_ (trailer_bytes)
{
}

TRB_Asynch_Transmit_File_Result::Header_And_Trailer::~Header_And_Trailer (void)
{
}

void
TRB_Asynch_Transmit_File_Result::
Header_And_Trailer::header_and_trailer (ACE_Message_Block *header,
                                        size_t             header_bytes,
                                        ACE_Message_Block *trailer,
                                        size_t             trailer_bytes)
{
  this->header (header);
  this->header_bytes (header_bytes);
  this->trailer (trailer);
  this->trailer_bytes (trailer_bytes);
}

ACE_Message_Block *
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::header (void) const
{
  return this->header_;
}

void
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::header (ACE_Message_Block *message_block)
{
  this->header_ = message_block;
}

size_t
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::header_bytes (void) const
{
  return this->header_bytes_;
}

void
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::header_bytes (size_t bytes)
{
  this->header_bytes_ = bytes;
}

ACE_Message_Block *
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::trailer (void) const
{
  return this->trailer_;
}

void
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::trailer (ACE_Message_Block *message_block)
{
  this->trailer_ = message_block;
}

size_t
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::trailer_bytes (void) const
{
  return this->trailer_bytes_;
}

void
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::trailer_bytes (size_t bytes)
{
  this->trailer_bytes_ = bytes;
}

ACE_LPTRANSMIT_FILE_BUFFERS
TRB_Asynch_Transmit_File_Result::Header_And_Trailer::transmit_buffers (void)
{
  // If both are zero, return zero
  if (this->header_ == 0 && this->trailer_ == 0)
    return 0;
  else
    {
      // Something is valid

      // If header is valid, set the fields
      if (this->header_ != 0)
        {
          this->transmit_buffers_.Head = this->header_->rd_ptr ();
#if defined(ACE_WIN64)
          this->transmit_buffers_.HeadLength =
            ACE_static_cast (DWORD, this->header_bytes_);
#else
          this->transmit_buffers_.HeadLength = this->header_bytes_;
#endif /* ACE_WIN64 */
        }
      else
        {
          this->transmit_buffers_.Head = 0;
          this->transmit_buffers_.HeadLength = 0;
        }

      // If trailer is valid, set the fields
      if (this->trailer_ != 0)
        {
          this->transmit_buffers_.Tail = this->trailer_->rd_ptr ();
#if defined(ACE_WIN64)
          this->transmit_buffers_.TailLength =
            ACE_static_cast (DWORD, this->trailer_bytes_);
#else
          this->transmit_buffers_.TailLength = this->trailer_bytes_;
#endif /* ACE_WIN64 */
        }
      else
        {
          this->transmit_buffers_.Tail = 0;
          this->transmit_buffers_.TailLength = 0;
        }

      // Return the transmit buffers
      return &this->transmit_buffers_;
    }
}

// ******************************************************************
// Asynch Timer
// ******************************************************************
TRB_Asynch_Timer::TRB_Asynch_Timer (TRB_Handler          *handler,
                                    const ACE_Time_Value &tv,
                                    const void           *act,
                                    const void           *completion_key,
                                    int                   priority,
                                    int                   signal_number)
  : TRB_Asynch_Result  (OP_TIMER,
                        FLG_FAKE_RESULT,
                        handler,
                        ACE_INVALID_HANDLE, // handle
                        Buffer_Info(0),      // message_block_ptr,
                        0,                  // bytes_requested,
                        0,                  // offset,
                        0,                  // offset_high,
                        act,
                        completion_key,
                        priority,
                        signal_number)
  , time_              (tv)
{
}

TRB_Asynch_Timer::~TRB_Asynch_Timer ()
{
}

int
TRB_Asynch_Timer::dispatch()
{
  // Call the application handler.
  this->get_handler()->handle_time_out (this->time(), this->act ());

  return 0;
}

// ***************************************************************
// Wakeup Completion
// ******************************************************************
TRB_Wakeup_Completion::TRB_Wakeup_Completion (
                                    TRB_Handler          *handler,
                                    const void           *act,
                                    const void           *completion_key,
                                    int                   priority,
                                    int                   signal_number)
  : TRB_Asynch_Result  (OP_WAKEUP,
                        FLG_FAKE_RESULT,
                        handler,
                        ACE_INVALID_HANDLE, // handle
                        Buffer_Info (0),     // message_block_ptr,
                        0,                  // bytes_requested,
                        0,                  // offset,
                        0,                  // offset_high,
                        act,
                        completion_key,
                        priority,
                        signal_number)
{
}

TRB_Wakeup_Completion::~TRB_Wakeup_Completion ()
{
}

int
TRB_Wakeup_Completion::dispatch()
{
  // Call the application handler.
  this->get_handler()->handle_wakeup ();

  return 0;
}

// ***************************************************************
//  User Result
// ******************************************************************
TRB_Asynch_User_Result::TRB_Asynch_User_Result (
                          TRB_Handler        *handler,
                          ACE_HANDLE          handle,
                          const Buffer_Info&   buf_info,
                          size_t              bytes_requested,
                          u_long              offset,
                          u_long              offset_high,
                          const void         *act,
                          const void         *completion_key,
                          int                 priority,
                          int                 signal_number)
                          
  : TRB_Asynch_Result  (OP_USER,
                        FLG_FAKE_RESULT,
                        handler,
                        handle,
                        buf_info,           //message_block_ptr,
                        bytes_requested,
                        offset,
                        offset_high,
                        act,
                        completion_key,
                        priority,
                        signal_number)
{
}

TRB_Asynch_User_Result::~TRB_Asynch_User_Result ()
{
}

int
TRB_Asynch_User_Result::dispatch()
{
  // Call the application handler.
  this->get_handler()->handle_user_operation (*this);

  return 0;
}
// ***********************************************************************
// Asynch_Operation
// ***********************************************************************
TRB_Asynch_Operation::TRB_Asynch_Operation()
  : handle_        (ACE_INVALID_HANDLE)
  , handler_       (0)
  , proactor_      (0)
  , completion_key_(0)
{
}

TRB_Asynch_Operation::~TRB_Asynch_Operation()
{
}

int
TRB_Asynch_Operation::open (TRB_Handler & handler,
                            ACE_HANDLE    handle,
                            const void   *completion_key,
                            TRB_Proactor *proactor)
{
  if (this->handle_   != ACE_INVALID_HANDLE  ||
      this->handler_  != 0 ||
      this->proactor_ != 0)
    {
      return -1;  // already open
    }

  if (proactor == 0)
    {
      proactor = handler.proactor ();

      if (proactor == 0)
        return -1;
    }

  // Grab the handle from the <handler> if <handle> is invalid
  if (handle == ACE_INVALID_HANDLE)
    handle = handler.handle ();

  if (handle == ACE_INVALID_HANDLE)
    return -1;

  this->handle_         = handle;
  this->handler_        = &handler;
  this->proactor_       = proactor;
  this->completion_key_ = completion_key;

  return this->proactor_->register_handle (this->handle_, 
                                           this->completion_key_,
                                           this->supported_operations ());
}

int
TRB_Asynch_Operation::cancel (void)
{
  if (this->proactor_ == 0) 
    return  -1;

  if (this->handle_ != ACE_INVALID_HANDLE)
    return this->proactor_->cancel_aio(this->handle_);

  return this->proactor_->cancel_aio(this->handler_);
}

int
TRB_Asynch_Operation::close (void)
{
  //if (this->handle_ != ACE_INVALID_HANDLE && this->proactor_ != 0)
  //  {
  //    TRB_Proactor_Impl * impl = this->proactor_->implementation ();
  //    if (impl != 0)
  //      impl->unregister_handle (this->handle_);
  //  }
  
  this->handle_         = ACE_INVALID_HANDLE;
  this->handler_        = 0;
  this->proactor_       = 0;
  this->completion_key_ = 0;
  return 0;
}

// ***********************************************************************
// Asynch_Read_Stream
// ***********************************************************************
TRB_Asynch_Read_Stream::TRB_Asynch_Read_Stream (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Read_Stream::~TRB_Asynch_Read_Stream (void)
{
}

int
TRB_Asynch_Read_Stream::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_READ_STREAM;
}

int
TRB_Asynch_Read_Stream::read (const Buffer_Info& buf_info,
                              size_t             bytes_to_read,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       buf_info,
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       0);

  return this->proactor_->start (result);
}
  
int
TRB_Asynch_Read_Stream::read (ACE_Message_Block& message_block,
                              size_t             bytes_to_read,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       0);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Read_Stream::readv (ACE_Message_Block& message_block,
                               size_t             bytes_to_read,
                               const void        *act,
                               int                priority,
                               int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_IOVECT);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Read_Stream::read_n (const Buffer_Info& buf_info,
                              size_t             bytes_to_read,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       buf_info,
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}
  
int
TRB_Asynch_Read_Stream::read_n (ACE_Message_Block& message_block,
                              size_t             bytes_to_read,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Read_Stream::readv_n (ACE_Message_Block& message_block,
                               size_t             bytes_to_read,
                               const void        *act,
                               int                priority,
                               int                signal_number)
{
  TRB_Asynch_Read_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_read,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_IOVECT |
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Write_Stream
// ***********************************************************************
TRB_Asynch_Write_Stream::TRB_Asynch_Write_Stream (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Write_Stream::~TRB_Asynch_Write_Stream (void)
{
}

int
TRB_Asynch_Write_Stream::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_WRITE_STREAM;
}
  
int
TRB_Asynch_Write_Stream::write (ACE_Message_Block& message_block,
                                size_t             bytes_to_write,
                                const void        *act,
                                int                priority,
                                int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_Stream::write (const Buffer_Info& buf_info,
                                size_t             bytes_to_write,
                                const void        *act,
                                int                priority,
                                int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       buf_info,
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}


int
TRB_Asynch_Write_Stream::writev (ACE_Message_Block& message_block,
                              size_t             bytes_to_write,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_IOVECT |
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_Stream::write_n (ACE_Message_Block& message_block,
                                size_t             bytes_to_write,
                                const void        *act,
                                int                priority,
                                int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_Stream::write_n (const Buffer_Info& buf_info,
                                size_t             bytes_to_write,
                                const void        *act,
                                int                priority,
                                int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       buf_info,
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}


int
TRB_Asynch_Write_Stream::writev_n (ACE_Message_Block& message_block,
                              size_t             bytes_to_write,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Write_Stream_Result result(this->handler_,
                                       this->handle_,
                                       Buffer_Info (message_block),
                                       bytes_to_write,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       TRB_Asynch_Result::FLG_IOVECT |
                                       TRB_Asynch_Result::FLG_EXACTLY_BYTES);

  return this->proactor_->start (result);
}
// ***********************************************************************
// Asynch_Read_File
// ***********************************************************************
TRB_Asynch_Read_File::TRB_Asynch_Read_File (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Read_File::~TRB_Asynch_Read_File (void)
{
}

int
TRB_Asynch_Read_File::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_READ_FILE;
}

int
TRB_Asynch_Read_File::read (ACE_Message_Block& message_block,
                            size_t             bytes_to_read,
                            u_long             offset,
                            u_long             offset_high,
                            const void        *act,
                            int                priority,
                            int                signal_number)
{
  TRB_Asynch_Read_File_Result result(this->handler_,
                                     this->handle_,
                                     Buffer_Info (message_block),
                                     bytes_to_read,
                                     offset,
                                     offset_high,
                                     act,
                                     this->completion_key_,
                                     priority,
                                     signal_number,
                                     0);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Read_File::read (const Buffer_Info& buf_info,
                            size_t             bytes_to_read,
                            u_long             offset,
                            u_long             offset_high,
                            const void        *act,
                            int                priority,
                            int                signal_number)
{
  TRB_Asynch_Read_File_Result result(this->handler_,
                                     this->handle_,
                                     buf_info,
                                     bytes_to_read,
                                     offset,
                                     offset_high,
                                     act,
                                     this->completion_key_,
                                     priority,
                                     signal_number,
                                     0);

  return this->proactor_->start (result);
}


int
TRB_Asynch_Read_File::readv (ACE_Message_Block& message_block,
                              size_t             bytes_to_read,
                              u_long             offset,
                              u_long             offset_high,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Read_File_Result result(this->handler_,
                                     this->handle_,
                                     Buffer_Info (message_block),
                                     bytes_to_read,
                                     offset,
                                     offset_high,
                                     act,
                                     this->completion_key_,
                                     priority,
                                     signal_number,
                                     TRB_Asynch_Result::FLG_IOVECT);

  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Write_File
// ***********************************************************************
TRB_Asynch_Write_File::TRB_Asynch_Write_File (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Write_File::~TRB_Asynch_Write_File (void)
{
}

int
TRB_Asynch_Write_File::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_WRITE_FILE;
}

int
TRB_Asynch_Write_File::write (ACE_Message_Block& message_block,
                              size_t             bytes_to_write,
                              u_long             offset,
                              u_long             offset_high,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Write_File_Result result(this->handler_,
                                     this->handle_,
                                     Buffer_Info (message_block),
                                     bytes_to_write,
                                     offset,
                                     offset_high,
                                     act,
                                     this->completion_key_,
                                     priority,
                                     signal_number,
                                     0);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_File::write (const Buffer_Info& buf_info,
                              size_t             bytes_to_write,
                              u_long             offset,
                              u_long             offset_high,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Write_File_Result result(this->handler_,
                                      this->handle_,
                                      buf_info,
                                      bytes_to_write,
                                      offset,
                                      offset_high,
                                      act,
                                      this->completion_key_,
                                      priority,
                                      signal_number,
                                      0);

  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_File::writev (ACE_Message_Block& message_block,
                              size_t             bytes_to_write,
                              u_long             offset,
                              u_long             offset_high,
                              const void        *act,
                              int                priority,
                              int                signal_number)
{
  TRB_Asynch_Write_File_Result result(this->handler_,
                                     this->handle_,
                                     Buffer_Info (message_block),
                                     bytes_to_write,
                                     offset,
                                     offset_high,
                                     act,
                                     this->completion_key_,
                                     priority,
                                     signal_number,
                                     TRB_Asynch_Result::FLG_IOVECT);

  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Accept
// ***********************************************************************
TRB_Asynch_Accept::TRB_Asynch_Accept (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Accept::~TRB_Asynch_Accept (void)
{
}

int
TRB_Asynch_Accept::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_ACCEPT;
}


int
TRB_Asynch_Accept::accept(ACE_Message_Block &message_block,
                          size_t             bytes_to_read,
                          const void        *act,
                          int                priority,
                          int                signal_number)
{
  TRB_Asynch_Accept_Result result (this->handler_,
                                   this->handle_,
                                   Buffer_Info (message_block),
                                   bytes_to_read,
                                   act,
                                   this->completion_key_,
                                   priority,
                                   signal_number);
  return this->proactor_->start (result);
}

int
TRB_Asynch_Accept::accept(const Buffer_Info& buf_info,
                          size_t             bytes_to_read,
                          const void        *act,
                          int                priority,
                          int                signal_number)
{
  TRB_Asynch_Accept_Result result (this->handler_,
                                   this->handle_,
                                   buf_info,
                                   bytes_to_read,
                                   act,
                                   this->completion_key_,
                                   priority,
                                   signal_number);
  return this->proactor_->start (result);
}

int
TRB_Asynch_Accept::accept(const void        *act,
                          int                priority,
                          int                signal_number)
{
  TRB_Asynch_Accept_Result result (this->handler_,
                                   this->handle_,
                                   Buffer_Info (0),
                                   0,
                                   act,
                                   this->completion_key_,
                                   priority,
                                   signal_number);
  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Connect
// ***********************************************************************
TRB_Asynch_Connect::TRB_Asynch_Connect (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Connect::~TRB_Asynch_Connect (void)
{
}

int
TRB_Asynch_Connect::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_CONNECT;
}

int
TRB_Asynch_Connect::open (TRB_Handler & handler,
                          ACE_HANDLE    handle,
                          const void   *completion_key,
                          TRB_Proactor *proactor)
{
  if (this->handle_   != ACE_INVALID_HANDLE  ||
      this->handler_  != 0 ||
      this->proactor_ != 0)
    {
      return -1;  // already open
    }

  if (proactor == 0)
    return -1;


  this->handle_         = handle;
  this->handler_        = &handler;
  this->proactor_       = proactor;
  this->completion_key_ = completion_key;
  
  return 0;
}
  
int
TRB_Asynch_Connect::prepare_connect (
                           ACE_HANDLE & connect_handle,
                           const ACE_Addr & remote_sap,
                           const ACE_Addr & local_sap,
                           int  reuse_addr)
{
    int protocol_family = remote_sap.get_type ();
    if (connect_handle == ACE_INVALID_HANDLE)
    {
        connect_handle = ACE_OS::socket (protocol_family,
                                         SOCK_STREAM,
                                         0);
      
        if (connect_handle == ACE_INVALID_HANDLE)
        {
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("%N:%l:TRB_POSIX_Asynch_Connect::prepare_connect:")
                ACE_LIB_TEXT(" ACE_OS::socket failed\n")),
                -1);
        }

        // Reuse the address
        int one = 1;
        if (reuse_addr != 0 &&
            ACE_OS::setsockopt (connect_handle,
                                SOL_SOCKET,
                                SO_REUSEADDR,
                                (const char*) &one,
                                sizeof one) == -1 )
        {
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("%N:%l:TRB_Asynch_Connect::prepare_connect:")
                ACE_LIB_TEXT(" ACE_OS::setsockopt failed\n")),
                -1);
        }
    }

    if (local_sap != ACE_Addr::sap_any)
    {
        sockaddr *laddr = reinterpret_cast<sockaddr *>
                               (local_sap.get_addr ());
        size_t size = local_sap.get_size ();

        if (ACE_OS::bind (connect_handle, laddr, size) == -1)
        {
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("%N:%l:TRB_Asynch_Connect::prepare_connect:")
                ACE_LIB_TEXT(" ACE_OS::bind failed\n")),
                -1);
        }
    }
    else if (protocol_family == AF_INET ||
             protocol_family == AF_INET6 )
    {
        if (ACE::bind_port (connect_handle, 
                            INADDR_ANY,
                            protocol_family) == -1)
        {
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("%N:%l:TRB_Asynch_Connect::prepare_connect:")
                ACE_LIB_TEXT(" ACE_OS::bind_port failed\n")),
                -1);
        }
  
    }
 

    return this->proactor_->register_handle (connect_handle,
                                             this->completion_key_,
                                             this->supported_operations ());
}

int
TRB_Asynch_Connect::connect(ACE_HANDLE       connect_handle,
                            const ACE_Addr & remote_sap,
                            const ACE_Addr & local_sap,
                            int              reuse_addr,
                            const void *     act,
                            int              priority,
                            int              signal_number)
{
  int flags = 0;   // TRB_Asynch_Result::FLG_REGISTER_HANDLE;
  
  if (connect_handle == ACE_INVALID_HANDLE)
    flags |= TRB_Asynch_Result::FLG_NEW_HANDLE;

  int rc = this->prepare_connect(connect_handle,
                                 remote_sap,
                                 local_sap,
                                 reuse_addr);

  if (rc < 0 )
    {
      if (ACE_BIT_ENABLED(flags, TRB_Asynch_Result::FLG_NEW_HANDLE))
        {
          ACE_OS::closesocket (connect_handle);
        }
      return -1;
    }

  TRB_Asynch_Connect_Result result (this->handler_,
                                    connect_handle,
                                    remote_sap,
                                    local_sap,
                                    act,
                                    this->completion_key_,
                                    priority,
                                    signal_number,
                                    flags);

  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Read_Dgram
// ***********************************************************************
TRB_Asynch_Read_Dgram::TRB_Asynch_Read_Dgram (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Read_Dgram::~TRB_Asynch_Read_Dgram (void)
{
}

int
TRB_Asynch_Read_Dgram::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_READ_DGRAM;
}

int
TRB_Asynch_Read_Dgram::recv (ACE_Message_Block *message_block,
                             size_t             bytes_to_read,
                             int                recv_flags,
                             int                protocol_family,
                             const void        *act,
                             int                priority,
                             int                signal_number,
                             int                scatter_flags)
{
  TRB_Asynch_Read_Dgram_Result result (this->handler_,
                                       this->handle_,
                                       Buffer_Info (*message_block),
                                       bytes_to_read,
                                       recv_flags,
                                       protocol_family,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       scatter_flags);
  return this->proactor_->start (result);
}

int
TRB_Asynch_Read_Dgram::recv (const Buffer_Info& buf_info,
                             size_t             bytes_to_read,
                             int                recv_flags,
                             int                protocol_family,
                             const void        *act,
                             int                priority,
                             int                signal_number,
                             int                scatter_flags)
{
  TRB_Asynch_Read_Dgram_Result result (this->handler_,
                                       this->handle_,
                                       buf_info,
                                       bytes_to_read,
                                       recv_flags,
                                       protocol_family,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       scatter_flags);
  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Write_Dgram
// ***********************************************************************
TRB_Asynch_Write_Dgram::TRB_Asynch_Write_Dgram (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Write_Dgram::~TRB_Asynch_Write_Dgram (void)
{
}

int
TRB_Asynch_Write_Dgram::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_WRITE_DGRAM;
}

int
TRB_Asynch_Write_Dgram::send (ACE_Message_Block *message_block,
                              size_t             bytes_to_write,
                              int                send_flags,
                              const ACE_Addr &   addr,
                              const void        *act,
                              int                priority,
                              int                signal_number,
                              int                gather_flags)
{
  TRB_Asynch_Write_Dgram_Result result (this->handler_,
                                       this->handle_,
                                       addr,
                                       Buffer_Info (*message_block),
                                       bytes_to_write,
                                       send_flags,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       gather_flags);
  return this->proactor_->start (result);
}

int
TRB_Asynch_Write_Dgram::send (const Buffer_Info& buf_info,
                              size_t             bytes_to_write,
                              int                send_flags,
                              const ACE_Addr &   addr,
                              const void        *act,
                              int                priority,
                              int                signal_number,
                              int                gather_flags)
{
  TRB_Asynch_Write_Dgram_Result result (this->handler_,
                                       this->handle_,
                                       addr,
                                       buf_info,
                                       bytes_to_write,
                                       send_flags,
                                       act,
                                       this->completion_key_,
                                       priority,
                                       signal_number,
                                       gather_flags);
  return this->proactor_->start (result);
}

// ***********************************************************************
// Asynch_Transmit_File
// ***********************************************************************

TRB_Asynch_Transmit_File::TRB_Asynch_Transmit_File (void)
  : TRB_Asynch_Operation ()
{
}

TRB_Asynch_Transmit_File::~TRB_Asynch_Transmit_File (void)
{
}

int
TRB_Asynch_Transmit_File::supported_operations (void) const
{
  return TRB_Asynch_Result::OP_TRANSMIT_FILE;
}

int
TRB_Asynch_Transmit_File::transmit_file (ACE_HANDLE file,
                                         Header_And_Trailer *header_and_trailer,
                                         size_t bytes_to_write,
                                         u_long offset,
                                         u_long offset_high,
                                         size_t bytes_per_send,
                                         u_long flags,
                                         const void *act,
                                         int priority,
                                         int signal_number)
                                         
                                         
{
  TRB_Asynch_Transmit_File_Result result (this->handler_,
                                          this->handle_, // socket to write
                                          file,
                                          header_and_trailer,
                                          offset,
                                          offset_high,
                                          bytes_to_write,
                                          bytes_per_send,
                                          flags,
                                          act,
                                          this->completion_key_,
                                          priority,
                                          signal_number);
  return this->proactor_->start (result);
}

// *********************************************************************
// TRB_Handler
// *********************************************************************

TRB_Handler::TRB_Handler (void)
  : proactor_ (0)
  , handle_ (ACE_INVALID_HANDLE)
{
}

TRB_Handler::TRB_Handler (TRB_Proactor *d)
  : proactor_ (d)
  , handle_ (ACE_INVALID_HANDLE)
{
}

TRB_Handler::~TRB_Handler (void)
{
}

void
TRB_Handler::handle_read_stream (const TRB_Asynch_Read_Stream::Result & /* result */)
{
}

void
TRB_Handler::handle_write_stream (const TRB_Asynch_Write_Stream::Result & /* result */)
{
}

void
TRB_Handler::handle_write_dgram (const TRB_Asynch_Write_Dgram::Result & /* result */)
{
}

void
TRB_Handler::handle_read_dgram (const TRB_Asynch_Read_Dgram::Result & /* result */)
{
}

void
TRB_Handler::handle_accept (const TRB_Asynch_Accept::Result & /* result */)
{
}

void
TRB_Handler::handle_connect (const TRB_Asynch_Connect::Result & /* result */)
{
}

void
TRB_Handler::handle_transmit_file (const TRB_Asynch_Transmit_File::Result & /* result */)
{
}

void
TRB_Handler::handle_read_file (const TRB_Asynch_Read_File::Result & /* result */)
{
}

void
TRB_Handler::handle_write_file (const TRB_Asynch_Write_File::Result & /* result */)
{
}

void
TRB_Handler::handle_time_out (const ACE_Time_Value & /* tv */,
                              const void *           /* act */)
{
}
void
TRB_Handler::handle_user_operation(const TRB_Asynch_User_Result & /* result */)
{
}

void
TRB_Handler::handle_wakeup (void)
{
}

TRB_Proactor *
TRB_Handler::proactor (void)
{
  return this->proactor_;
}

void
TRB_Handler::proactor (TRB_Proactor *p)
{
  this->proactor_ = p;
}

ACE_HANDLE
TRB_Handler::handle (void) const
{
  return this->handle_;
}

void
TRB_Handler::handle (ACE_HANDLE h)
{
  this->handle_ = h;
}

ACE_Allocator*
TRB_Handler::allocator ()
{
  return 0;
}

// ************************************************************


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS */
