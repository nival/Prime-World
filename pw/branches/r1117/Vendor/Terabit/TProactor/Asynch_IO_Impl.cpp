// Asynch_IO_Impl.cpp,v 4.7 2002/04/16 22:47:26 shuston Exp

#include "TProactor/Asynch_IO_Impl.h"

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))
// This only works on Win32 platforms and on Unix platforms supporting
// aio calls. 

#include "ace/Log_Msg.h"
#include "ace/Message_Block.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

TRB_Asynch_Result_Impl::TRB_Asynch_Result_Impl (ACE_Allocator *allocator,
                                                void          *area)
  : allocator_ (allocator)
  , area_      (area)
{
}

TRB_Asynch_Result_Impl::~TRB_Asynch_Result_Impl ()
{
}

void
TRB_Asynch_Result_Impl::release (TRB_Asynch_Result_Impl *result)
{
  if (result != 0)
    result->free();
}

void
TRB_Asynch_Result_Impl::free ()
{
  ACE_Allocator *allocator = this->allocator_;
  void          *area = this->area_;

  if (allocator != 0)
    {
      this->~TRB_Asynch_Result_Impl ();
  
      allocator->free (area);
    }
}



int
TRB_Asynch_Result_Impl::dispatch ()
{
  int rc = -1;
  // Call completion hook
  ACE_SEH_TRY
    {
      TRB_Asynch_Result & user_result = this->get_original_result ();
      rc = user_result.dispatch ();
    }
  ACE_SEH_FINALLY
    {
      // This is crucial to prevent memory leaks
      TRB_Asynch_Result_Impl::release (this);
    }
  return rc;
}

int
TRB_Asynch_Result_Impl::start ()
{
  TRB_Asynch_Result & original = this->get_original_result ();

  // clear FLG_FAKE_RESULT flags
  original.clr_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

  if (this->start_impl () == 0)
    return 0;
   
  this->free();
  return -1;
}

int
TRB_Asynch_Result_Impl::post ()
{
  TRB_Asynch_Result & original = this->get_original_result ();

  // set FLG_FAKE_RESULT flags
  original.set_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

  if (this->post_impl () == 0)
    return 0;
   
  this->free();
  return -1;
}

int
TRB_Asynch_Result_Impl::build_read_iovec (
                  const ACE_Message_Block *msg,
                  bool                     flg_chain,
                  iovec                   *iov,
                  int &                    iovmax,
                  size_t &                 max_bytes_to_read,
                  size_t                   bytes_done)
{
    // We should not read more than user requested,
    // but it is allowed to read less
    ACE_ASSERT (max_bytes_to_read > bytes_done);

    size_t remain_bytes = max_bytes_to_read - bytes_done;
    size_t skip_bytes   = bytes_done;

    if (iovmax > ACE_IOV_MAX)
    {
        iovmax = ACE_IOV_MAX;
    }

    int    ocnt = 0;

    for (;msg != 0 && remain_bytes != 0 && ocnt < iovmax;
        msg = msg->cont ()) 
    {
        size_t msg_space = msg->space ();
        if (skip_bytes >= msg_space)
        {
            skip_bytes -= msg_space;
            continue;
        }

        // Make as many iovec as needed to fit all of msg_space.
        size_t wr_ptr_offset = skip_bytes;

        msg_space -= skip_bytes;
        skip_bytes = 0;

        if (msg_space > remain_bytes)
        {
            msg_space = remain_bytes;
        }

        remain_bytes -= msg_space;

        while (msg_space > 0 && ocnt < iovmax)
        {
            u_long this_chunk_length;
            if (msg_space > ULONG_MAX)
            {
                this_chunk_length = ULONG_MAX;
            }
            else
            {
                this_chunk_length = ACE_static_cast (u_long, msg_space);
            }

            // Collect the data in the iovec.
            iov[ocnt].iov_base = msg->wr_ptr () + wr_ptr_offset;
            iov[ocnt].iov_len  = this_chunk_length;

            msg_space     -= this_chunk_length;
            wr_ptr_offset += this_chunk_length;

            // Increment iovec counter if there's more to do.
            ocnt++;
        }

        if (msg_space > 0)       // Ran out of iovecs before msg_space exhausted
        {
            errno = ERANGE;
            return -1;
        }

        if (!flg_chain)   // only first message block
            break;
    }

    // Re-calculate number bytes to read
    iovmax = ocnt;
    max_bytes_to_read = 0;

    for (int i = 0; i < ocnt ; ++i)
    {
        max_bytes_to_read += iov[i].iov_len;
    }

    if (max_bytes_to_read == 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("build_read_iovec:")
            ACE_LIB_TEXT ("attempt to read 0 bytes\n")),
            -1);
    }

    return  0;
}

int
TRB_Asynch_Result_Impl::build_write_iovec (
                   const ACE_Message_Block *msg,
                   bool                     flg_chain,
                   iovec                   *iov,
                   int &                    iovmax,
                   size_t &                 max_bytes_to_write,
                   size_t                   bytes_done)
{
    // We should not write more than user requested,
    // but it is allowed to write less
    ACE_ASSERT (max_bytes_to_write > bytes_done);

    size_t remain_bytes = max_bytes_to_write - bytes_done;
    size_t skip_bytes   = bytes_done;

    if (iovmax > ACE_IOV_MAX)
    {
        iovmax = ACE_IOV_MAX;
    }

    int ocnt = 0;

    for (;msg != 0 && remain_bytes != 0 && ocnt < iovmax;
        msg = msg->cont ()) 
    {
        size_t msg_length = msg->length ();

        if (skip_bytes >= msg_length)
        {
            skip_bytes -= msg_length;
            continue;
        }

        // Make as many iovec as needed to fit all of msg_length.
        size_t rd_ptr_offset = skip_bytes;

        msg_length -= skip_bytes;
        skip_bytes  = 0;
        
        if (msg_length > remain_bytes)
        {
            msg_length = remain_bytes;
        }

        remain_bytes -= msg_length;

        while (msg_length > 0 && ocnt < iovmax)
        {
            u_long this_chunk_length;
            if (msg_length > ULONG_MAX)
            {
                this_chunk_length = ULONG_MAX;
            }
            else
            {
                this_chunk_length = ACE_static_cast (u_long, msg_length);
            }

            // Collect the data in the iovec.
            iov[ocnt].iov_base = msg->rd_ptr () + rd_ptr_offset;
            iov[ocnt].iov_len  = this_chunk_length;
            msg_length    -= this_chunk_length;
            rd_ptr_offset += this_chunk_length;

            // Increment iovec counter if there's more to do.
            ocnt++;
        }

        if (msg_length > 0)       // Ran out of iovecs before msg_length exhausted
        {
            errno = ERANGE;
            return -1;
        }

        if (!flg_chain)   // only first message block
            break;
    }

    // Re-calculate number bytes to write
    iovmax = ocnt;
    max_bytes_to_write = 0;

    for (int i = 0; i < ocnt ; ++i)
    {
        max_bytes_to_write += iov[i].iov_len;
    }

    if (max_bytes_to_write == 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
           ACE_LIB_TEXT ("build_write_iovec:")
            ACE_LIB_TEXT ("attempt to write 0 bytes\n")),
            -1);
    }
    return  0;
} 

int
TRB_Asynch_Result_Impl::copy_iovec (
                  const iovec             *src,
                  int                      src_cnt,
                  iovec                   *iov,
                  int &                    iovmax,
                  size_t &                 max_bytes,
                  size_t                   done_bytes)
{
    // We should not read/write more than user requested,
    // but it is allowed to read/write less

    ACE_ASSERT (max_bytes > done_bytes);

    size_t remain_bytes = max_bytes - done_bytes;
    size_t skip_bytes   = done_bytes;

    if (iovmax > ACE_IOV_MAX)
    {
        iovmax = ACE_IOV_MAX;
    }

    int icnt = 0;
    int ocnt = 0;

    for (; icnt < src_cnt && ocnt < iovmax && remain_bytes != 0; ++icnt)
    {
        if (skip_bytes >= src[icnt].iov_len)
        {
            skip_bytes -= src[icnt].iov_len;
            continue;
        }

        iov[ocnt].iov_base = (char *) (src[icnt].iov_base) + skip_bytes;
        iov[ocnt].iov_len  = src[icnt].iov_len  - skip_bytes;

        skip_bytes = 0;

        if (iov[ocnt].iov_len > remain_bytes)
        {
            iov[ocnt].iov_len = remain_bytes;
        }

        remain_bytes -= iov[ocnt].iov_len;
        ++ocnt;
    }
       
    // Re-calculate number bytes to read/write
    iovmax = ocnt;

    //max_bytes = max_bytes - done_bytes - remain_bytes;
    max_bytes = 0;
    for (int i = 0; i < ocnt ; ++i)
    {
        max_bytes += iov[i].iov_len;
    }

    if (max_bytes == 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
           ACE_LIB_TEXT ("copy_iovec:")
           ACE_LIB_TEXT ("attempt to read/write 0 bytes\n")),
           -1);
    }

    return  0;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 || ACE_HAS_WINCE */
