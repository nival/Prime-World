ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// ****************************************************************
//   Asynchronous Result
// ****************************************************************
ACE_INLINE
TRB_Asynch_Result::Buffer_Info::Buffer_Info (ACE_Message_Block &mb)
: message_block_ptr_ (&mb)
, iov_count_         (-1)
{
}

ACE_INLINE
TRB_Asynch_Result::Buffer_Info::Buffer_Info (char *buffer)
: buffer_           (buffer)
, iov_count_        (0)
{
}

ACE_INLINE
TRB_Asynch_Result::Buffer_Info::Buffer_Info (iovec *iov, int iovcnt)
: iov_              (iov)
, iov_count_        (iovcnt)
{
  ACE_ASSERT (iovcnt > 0);
}

ACE_INLINE int
TRB_Asynch_Result::Buffer_Info::get_iov_count () const
{
   return iov_count_;
}

ACE_INLINE char *
TRB_Asynch_Result::Buffer_Info::get_buffer (void) const
{
    return (iov_count_ == 0) ? buffer_ : 0;
}

ACE_INLINE iovec *
TRB_Asynch_Result::Buffer_Info::get_iov (void) const
{
    return (iov_count_ > 0) ? iov_ : 0;
}

ACE_INLINE ACE_Message_Block *
TRB_Asynch_Result::Buffer_Info::get_message_block_ptr (void) const
{
    return (iov_count_ < 0) ? message_block_ptr_ : 0;
}

ACE_INLINE int
TRB_Asynch_Result::op_code (void) const
{
  return this->op_code_;
}

ACE_INLINE int
TRB_Asynch_Result::op_flags (void) const
{
  return this->op_flags_;
}

ACE_INLINE int
TRB_Asynch_Result::is_read_family (void) const
{
  return ACE_BIT_ENABLED(this->op_code_, OP_READ_MASK);
}

ACE_INLINE int
TRB_Asynch_Result::is_write_family (void) const
{
  return ACE_BIT_ENABLED(this->op_code_, OP_WRITE_MASK);
}

ACE_INLINE int
TRB_Asynch_Result::is_iov_operation (void) const
{
  return ACE_BIT_ENABLED(this->op_flags_, FLG_IOVECT);
}

ACE_INLINE int
TRB_Asynch_Result::is_direct_buffers (void) const
{
  return ACE_BIT_ENABLED(this->op_flags_, FLG_DIRECT_BUFFERS);
}

ACE_INLINE u_long
TRB_Asynch_Result::offset (void) const
{
  return this->offset_;
}

ACE_INLINE u_long
TRB_Asynch_Result::offset_high (void) const
{
  return this->offset_high_;
}

ACE_INLINE int
TRB_Asynch_Result::priority (void) const
{
  return this->priority_;
}

ACE_INLINE int
TRB_Asynch_Result::signal_number (void) const
{
  return this->signal_number_;
}

ACE_INLINE const void *
TRB_Asynch_Result::act (void) const
{
  return this->act_;
}

ACE_INLINE const void *
TRB_Asynch_Result::completion_key (void) const
{
  return this->completion_key_;
}

ACE_INLINE int
TRB_Asynch_Result::success (void) const
{
  return this->error_ == 0;
}

ACE_INLINE u_long
TRB_Asynch_Result::error (void) const
{
  return this->error_;
}

ACE_INLINE size_t
TRB_Asynch_Result::bytes_transferred (void) const
{
  return this->bytes_transferred_;
}

ACE_INLINE size_t
TRB_Asynch_Result::bytes_requested (void) const
{
  return this->bytes_requested_;
}

ACE_INLINE  
const TRB_Asynch_Result::Buffer_Info& 
TRB_Asynch_Result::get_buffer_info () const
{
  return buf_info_;
}

ACE_INLINE ACE_Message_Block *
TRB_Asynch_Result::get_message_block_ptr (void) const
{
  return buf_info_.get_message_block_ptr ();
}

ACE_INLINE char *
TRB_Asynch_Result::get_buffer (void) const
{
  return buf_info_.get_buffer ();
}

ACE_INLINE iovec *
TRB_Asynch_Result::get_iov (void) const
{
  return buf_info_.get_iov ();
}

ACE_INLINE int
TRB_Asynch_Result::get_iov_count (void) const
{
  return buf_info_.get_iov_count ();
}


ACE_INLINE ACE_HANDLE
TRB_Asynch_Result::handle (void) const
{
  return this->handle_;
}

ACE_INLINE TRB_Handler * 
TRB_Asynch_Result::get_handler(void) const
{
  return this->handler_;
}

ACE_INLINE void  
TRB_Asynch_Result::set_op_flags (int mask)
{
  ACE_SET_BITS (this->op_flags_ , mask);
}

ACE_INLINE void  
TRB_Asynch_Result::clr_op_flags (int mask)
{
  ACE_CLR_BITS (this->op_flags_ , mask);
}

ACE_INLINE void  
TRB_Asynch_Result::set_handle (ACE_HANDLE handle)
{
  this->handle_ = handle;
}

ACE_INLINE void  
TRB_Asynch_Result::set_completion (ssize_t nbytes, u_long errcode)
{
  // do not pass -1 as transfer count
  if (nbytes  > 0 )
    this->bytes_transferred_+= ACE_static_cast (u_long, nbytes);

  this->error_ = errcode;
}

// ****************************************************************
//   Asynchronous Operation
// ****************************************************************

ACE_INLINE TRB_Proactor *
TRB_Asynch_Operation::proactor (void) const
{
  return this->proactor_;
}

ACE_INLINE TRB_Handler *
TRB_Asynch_Operation::handler (void) const
{
  return this->handler_;
}

ACE_INLINE ACE_HANDLE
TRB_Asynch_Operation::handle (void) const
{
  return this->handle_;
}

ACE_INLINE const void *
TRB_Asynch_Operation::completion_key (void) const
{
  return this->completion_key_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
