#include "TProactor/WIN32_Asynch_IO.h"

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE))

#include "TProactor/WIN32_Proactor.h"
#include "ace/ACE.h"

#include "ace/Log_Msg.h"
#include "ace/Message_Block.h"
#include "ace/OS_NS_errno.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_socket.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


TRB_WIN32_Asynch_Result::~TRB_WIN32_Asynch_Result (void)
{
}

TRB_WIN32_Asynch_Result::TRB_WIN32_Asynch_Result (
                             ACE_Allocator      *allocator,
                             void               *area,
                             TRB_WIN32_Proactor *win32_proactor,
                             DWORD               offset_low,
                             DWORD               offset_high)
: OVERLAPPED  ()
, TRB_Asynch_Result_Impl (allocator , area)
, win32_proactor_ (win32_proactor)
{
    this->Internal = 0;
    this->InternalHigh = 0;
    this->Offset = offset_low;
    this->OffsetHigh = offset_high;
    this->hEvent = this->win32_proactor_->get_handle (); // event;
}


int
TRB_WIN32_Asynch_Result::check_start_error (bool  rc_start,
                                            const ACE_TCHAR *op_name)
{
    if (rc_start)
    {    
        // Immediate success: the OVERLAPPED will still get queued.
        return 0;
    }

    // If initiate failed, check for a bad error.
    ACE_OS::set_errno_to_last_error ();
    switch (errno)
    {
    case ERROR_IO_PENDING:
    case ERROR_MORE_DATA:

        // The IO will complete proactively: the OVERLAPPED will still
        // get queued.
        return 0;

    default:
        break;
    }

    TRB_Asynch_Result & user_result = this->get_original_result ();
    user_result.set_completion (0, ::GetLastError ());

    if (ACE_BIT_ENABLED(user_result.op_flags (), TRB_Asynch_Result::FLG_NEW_HANDLE))
    {
        ACE_OS::closesocket (user_result.handle());
        user_result.set_handle (ACE_INVALID_HANDLE);
    }

    // make EOF condition processing simple
    // i.e. deliver as completion
    if (user_result.error () ==  ERROR_HANDLE_EOF)
    {
        // set FLG_FAKE_RESULT flags
        user_result.set_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

        return this->post_impl ();
    }


    // Something else went wrong: the OVERLAPPED will not get
    // queued.

    //if (ACE::debug ())
    {
        ACE_DEBUG ((LM_ERROR,
            ACE_LIB_TEXT ("(%t)%T LastError=%d %p\n"),
            (int) user_result.error(),
            op_name));
    }

    return -1;
}

int
TRB_WIN32_Asynch_Result::complete (size_t              bytes_transferred,
                                   const void         *completion_key,
                                   u_long              error)
{
    TRB_Asynch_Result & user_result = this->get_original_result();

    ACE_ASSERT(user_result.completion_key() == completion_key);

    if (ACE_BIT_ENABLED (user_result.op_flags(), 
                         TRB_Asynch_Result::FLG_FAKE_RESULT))
    {
        return 0;
    }

    // This is AIO completion, not fake post completion

    user_result.set_completion (bytes_transferred, error);

    return this->on_complete();
}

int
TRB_WIN32_Asynch_Result::on_complete ()
{
    return 0;
}

int
TRB_WIN32_Asynch_Result::post_impl ()
{
    return this->win32_proactor ()->post (this);
}

// *****************************************************************************
// AIO read results and initiators for streams and files 
// *****************************************************************************
TRB_WIN32_Asynch_Read_Stream_Result::TRB_WIN32_Asynch_Read_Stream_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Read_Stream_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
  , io_flags_               (0)
{
}

TRB_WIN32_Asynch_Read_Stream_Result::~TRB_WIN32_Asynch_Read_Stream_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Read_Stream_Result::get_original_result () 
{
   return this->original_;
}

int
TRB_WIN32_Asynch_Read_Stream_Result::start_impl ()
{
    if (!this->original_.is_iov_operation ())
        return this->start_read_generic ();

    // iovec operation
    if (this->original_.op_code() == TRB_Asynch_Result::OP_READ_FILE)
        return this->start_readv_file ();

    return this->start_readv_stream ();
}

int
TRB_WIN32_Asynch_Read_Stream_Result::start_read_generic ()
{
    DWORD     bytes_read    = original_.bytes_transferred ();
    size_t    bytes_to_read = original_.bytes_requested ();
    char     *buffer        = original_.get_buffer ();

    if (buffer == 0)
    {
        const ACE_Message_Block * msg = original_.get_message_block_ptr ();

        if (msg == 0)
        {
            errno = EINVAL;
            return -1;
        }

        size_t space = msg->space ();
        if (bytes_to_read > space)
        {
            bytes_to_read = space;
        }

        buffer = msg->wr_ptr ();  
    }

    ACE_ASSERT (bytes_to_read >= bytes_read);

    bytes_to_read -= bytes_read;
    buffer        += bytes_read;

    if (bytes_to_read == 0)
    {
        errno = ENOSPC;
        return -1;
    }

    if (bytes_to_read > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    // Initiate the read
    BOOL rc = ::ReadFile (original_.handle (),
                          buffer,
                          bytes_to_read,
                          &bytes_read,
                          this);

    return this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("ReadFile"));
}

int
TRB_WIN32_Asynch_Read_Stream_Result::start_readv_stream ()
{
    size_t    bytes_to_read = original_.bytes_requested ();
    DWORD        bytes_read = original_.bytes_transferred ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;

    int ok = -1;
    if (this->original_.is_direct_buffers ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_read,
                         bytes_read);
    }
    else
    {
        ok = build_read_iovec (original_.get_message_block_ptr (),
                               true,  // process msg->cont()
                               iov,
                               iovcnt,
                               bytes_to_read,
                               bytes_read);
    }

    if (ok != 0)
    {
        return -1;
    }

    this->io_flags_ = 0;

    // Initiate the readv
    BOOL rc = ::WSARecv (reinterpret_cast<SOCKET> (original_.handle ()),
                         reinterpret_cast<WSABUF *> (iov),
                         iovcnt,
                         &bytes_read,
                         &this->io_flags_, // IO flags
                         this,
                         0);

    return this->check_start_error ((rc==0), ACE_LIB_TEXT("WSARecv"));
}

int
TRB_WIN32_Asynch_Read_Stream_Result::start_readv_file ()
{
    size_t    bytes_to_read  = original_.bytes_requested ();
    DWORD        bytes_read  = 0;
    size_t       total_space = 0;


    // TODO: fix this - it is not MT safe
    static const size_t page_size = ACE_OS::getpagesize();

    FILE_SEGMENT_ELEMENT buffer_pointers[ACE_IOV_MAX + 1];
    int buffer_pointers_count = 0;

    // Each buffer must be at least the size of a system memory page
    // and must be aligned on a system memory page size boundary

    // We should not read more than user requested,
    // but it is allowed to read less

    if (this->original_.is_direct_buffers ())
    {
        int iovcnt = this->original_.get_iov_count ();
        iovec *iov = this->original_.get_iov ();

        for (int i=0;
              i < iovcnt && 
              buffer_pointers_count < ACE_IOV_MAX  && 
              total_space < bytes_to_read ;
             ++i, ++buffer_pointers_count )
        {
            if (iov[i].iov_len != page_size)
            {
                ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_LIB_TEXT ("TRB_WIN32_Asynch_Read_Stream_Result::start_readv_file:")
                    ACE_LIB_TEXT ("Invalid iov_len size\n")),
                    -1);
            }

            buffer_pointers[buffer_pointers_count].Buffer = iov[i].iov_base;
            total_space += page_size;
        }
    }
    else
    {
        for (const ACE_Message_Block * msg = original_.get_message_block_ptr ();
              msg != 0 &&
              buffer_pointers_count < ACE_IOV_MAX  && 
              total_space < bytes_to_read ;
             msg = msg->cont(), ++buffer_pointers_count )
        {
            size_t msg_space = msg->space ();

            if (msg_space != page_size)   // was msg < page_size
            {
                ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_LIB_TEXT ("TRB_WIN32_Asynch_Read_Stream_Result::start_readv_file:")
                    ACE_LIB_TEXT ("Invalid message block size\n")),
                -1);
            }

            buffer_pointers[buffer_pointers_count].Buffer = msg->wr_ptr ();
            total_space += page_size;
        }
    }

    // not read more than buffers space
    if (bytes_to_read > total_space)
        bytes_to_read = total_space;

    // ReadFileScatter API limits us to DWORD range.
    if (bytes_to_read > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    // last one should be completely 0
    buffer_pointers[buffer_pointers_count].Buffer = 0;

    // Initiate the readv
    BOOL rc = ::ReadFileScatter (original_.handle (),
                                 buffer_pointers,
                                 bytes_to_read,
                                 0, // reserved, must be NULL
                                 this);

    return this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("ReadFileScatter"));
}

// *****************************************************************************
// AIO write results and initiators for streams and files 
// *****************************************************************************
TRB_WIN32_Asynch_Write_Stream_Result::TRB_WIN32_Asynch_Write_Stream_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Write_Stream_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
{
}

TRB_WIN32_Asynch_Write_Stream_Result::~TRB_WIN32_Asynch_Write_Stream_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Write_Stream_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_WIN32_Asynch_Write_Stream_Result::start_impl ()
{ 
    if (!this->original_.is_iov_operation ())
        return this->start_write_generic ();

    // iovec operation
    if (this->original_.op_code() == TRB_Asynch_Result::OP_WRITE_FILE)
        return this->start_writev_file ();

    return this->start_writev_stream ();
}

int
TRB_WIN32_Asynch_Write_Stream_Result::start_write_generic ()
{
    DWORD     bytes_written  = original_.bytes_transferred ();
    size_t    bytes_to_write = original_.bytes_requested ();
    char     *buffer         = original_.get_buffer ();

    if (buffer == 0)
    {
        const ACE_Message_Block * msg = original_.get_message_block_ptr ();

        size_t len = msg->length ();
        if (bytes_to_write > len)
        {
            bytes_to_write = len;
        }

        buffer = msg->rd_ptr ();
    }

    ACE_ASSERT (bytes_to_write >= bytes_written);

    bytes_to_write -= bytes_written;
    buffer         += bytes_written;

    if (bytes_to_write == 0)
    {
        errno = ENOSPC;
        return -1;
    }

    if (bytes_to_write > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    // Initiate the write
    BOOL rc = ::WriteFile (original_.handle (),
                           buffer,
                           bytes_to_write,
                           &bytes_written,
                           this);

    return this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("WriteFile"));
}

int
TRB_WIN32_Asynch_Write_Stream_Result::start_writev_stream ()
{
    size_t    bytes_to_write = original_.bytes_requested ();
    DWORD     bytes_written  = original_.bytes_transferred ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;

    int ok = -1;
    if (this->original_.is_direct_buffers ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_write,
                         bytes_written);
    }
    else
    {
        ok = build_write_iovec (original_.get_message_block_ptr (),
                                true,  // process msg->cont()
                                iov,
                                iovcnt,
                                bytes_to_write,
                                bytes_written);
    }

    if (ok != 0)
    {
        return -1;
    }

    // Initiate the writev
    BOOL rc = ::WSASend (reinterpret_cast<SOCKET> (original_.handle ()),
                         reinterpret_cast<WSABUF *> (iov),
                         iovcnt,
                         &bytes_written,
                         0,  // send flags, default is 0
                         this,
                         0);

    return this->check_start_error ((rc==0), ACE_LIB_TEXT("WSASend"));
}

int
TRB_WIN32_Asynch_Write_Stream_Result::start_writev_file ()
{
    size_t    bytes_to_write  = original_.bytes_requested ();
    DWORD     bytes_written  = 0;
    size_t    total_len = 0;


    // TODO: fix this - it is MT safe
    static const size_t page_size = ACE_OS::getpagesize();

    FILE_SEGMENT_ELEMENT buffer_pointers[ACE_IOV_MAX + 1];
    int buffer_pointers_count = 0;

    // Each buffer must be at least the size of a system memory page
    // and must be aligned on a system memory page size boundary

    // We should not read more than user requested,
    // but it is allowed to read less

    if (this->original_.is_direct_buffers ())
    {
        int iovcnt = this->original_.get_iov_count ();
        iovec *iov = this->original_.get_iov ();

        for (int i=0;
              i < iovcnt && 
              buffer_pointers_count < ACE_IOV_MAX  && 
              total_len < bytes_to_write ;
             ++i, ++buffer_pointers_count )
        {
            if (iov[i].iov_len != page_size)
            {
                ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_LIB_TEXT ("TRB_WIN32_Asynch_Read_Stream_Result::start_writev_file:")
                    ACE_LIB_TEXT ("Invalid iov_len size\n")),
                    -1);
            }

            buffer_pointers[buffer_pointers_count].Buffer = iov[i].iov_base;
            total_len += page_size;
        }
    }
    else
    {
        for (const ACE_Message_Block *msg = original_.get_message_block_ptr ();
              msg != 0 && 
              buffer_pointers_count < ACE_IOV_MAX && 
              total_len < bytes_to_write;
             msg = msg->cont (), ++buffer_pointers_count )
        {
            size_t msg_len = msg->length ();

            // Don't allow writing less than page_size, unless
            // the size of the message block is big enough (so we don't write from
            // memory which does not belong to the message block), and the message
            // block is the last in the chain.
            if (msg_len != page_size &&
                (msg_len + msg->space () < page_size ||  // message block too small
                bytes_to_write - total_len > page_size ))// NOT last chunk
            {
                ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_LIB_TEXT ("TRB_WIN32_Asynch_Write_Stream_Result::start_writev_file")
                    ACE_LIB_TEXT ("Invalid message block length\n")),
                    -1);
            }

            buffer_pointers[buffer_pointers_count].Buffer = msg->rd_ptr ();
            total_len += page_size;
        }
    }
    // not write more than we have in buffers
    if (bytes_to_write > total_len)
        bytes_to_write = total_len;

    // WriteFileGather API limits us to DWORD range.
    if (bytes_to_write > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    // last one should be completely 0
    buffer_pointers[buffer_pointers_count].Buffer = 0;


    // Initiate the writev
    BOOL rc = ::WriteFileGather (original_.handle (),
                                 buffer_pointers,
                                 bytes_to_write,
                                 0, // reserved, must be NULL
                                 this);

    return this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("WriteFileGather"));
}

// *****************************************************************************
// AIO read results and initiators for datagrams
// *****************************************************************************
TRB_WIN32_Asynch_Read_Dgram_Result::TRB_WIN32_Asynch_Read_Dgram_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Read_Dgram_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
  , io_flags_               (0)
  , addr_len_               (0)
{
}

TRB_WIN32_Asynch_Read_Dgram_Result::~TRB_WIN32_Asynch_Read_Dgram_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Read_Dgram_Result::get_original_result () 
{
    return this->original_;
}

int
TRB_WIN32_Asynch_Read_Dgram_Result::start_impl ()
{ 
    // to be compatible with original ACE version
    size_t bytes_to_read = MAXDWORD;
    //size_t bytes_to_read = original_.bytes_requested (); 

    DWORD  bytes_read = original_.bytes_transferred ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;

    int ok = -1;
    if (!this->original_.is_direct_buffers ())
    {
        ok = build_read_iovec (original_.get_message_block_ptr (),
                               original_.is_iov_operation ()? true : false,
                               iov,
                               iovcnt,
                               bytes_to_read,
                               bytes_read);
    }
    else if (this->original_.is_iov_operation ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_read,
                         bytes_read);
    }
    else
    {
        iov[0].iov_base = original_.get_buffer ();
        iov[0].iov_len  = bytes_to_read;
        iovcnt = 1;
        ok = 0;
    }

    if (ok != 0)
    {
        return -1;
    }

    if (bytes_to_read > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }


    sockaddr *saddr = (sockaddr *) original_.remote_address().get_addr ();

    this->addr_len_ = original_.remote_address().get_size();
    this->io_flags_ = original_.flags ();   // Input-Output recv flags


    // Initiate the recvfrom
    BOOL rc =  ::WSARecvFrom (reinterpret_cast<SOCKET> (original_.handle ()),
                              reinterpret_cast<WSABUF *> (iov),
                              iovcnt,
                              &bytes_read,
                              &this->io_flags_,
                              saddr,
                              &this->addr_len_,
                              this,
                              0);

    return this->check_start_error ((rc==0), ACE_LIB_TEXT("WSARecvFrom"));
}

int
TRB_WIN32_Asynch_Read_Dgram_Result::on_complete ()
{
    if (original_.error () == 0) 
    {
        // Adjust the address length
        ACE_Addr& remote_addr = 
            const_cast<ACE_Addr&> (original_.remote_address());

        remote_addr.set_size (this->addr_len_);
    }

    return 0;
}


// *****************************************************************************
// AIO write results and initiators for datagrams
// *****************************************************************************
TRB_WIN32_Asynch_Write_Dgram_Result::TRB_WIN32_Asynch_Write_Dgram_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Write_Dgram_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
{
}

TRB_WIN32_Asynch_Write_Dgram_Result::~TRB_WIN32_Asynch_Write_Dgram_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Write_Dgram_Result::get_original_result () 
{
    return this->original_;
}

int
TRB_WIN32_Asynch_Write_Dgram_Result::start_impl ()
{ 
    // to be compatible with original ACE version
    size_t bytes_to_write = MAXDWORD;
    //size_t bytes_to_write = original_.bytes_requested (); 

    DWORD  bytes_written = original_.bytes_transferred ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;
  
    int ok = -1;
    if (!this->original_.is_direct_buffers ())
    {
        ok = build_write_iovec (original_.get_message_block_ptr (),
                                original_.is_iov_operation ()? true : false,
                                iov,
                                iovcnt,
                                bytes_to_write,
                                bytes_written);
    }
    else if (this->original_.is_iov_operation ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_write,
                         bytes_written);
    }
    else
    {
        iov[0].iov_base = original_.get_buffer ();
        iov[0].iov_len  = bytes_to_write;
        iovcnt = 1;
        ok = 0;
    }

    if (ok != 0)
    {
        return -1;
    }

    if (bytes_to_write > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    sockaddr * saddr = (sockaddr *) original_.remote_address().get_addr ();
    INT     addr_len = original_.remote_address().get_size();
    DWORD   io_flags = original_.flags ();   // Input-Output send flags

    // Initiate the sendto
    BOOL rc =  ::WSASendTo (reinterpret_cast<SOCKET> (original_.handle ()),
                           reinterpret_cast<WSABUF *> (iov),
                           iovcnt,
                           &bytes_written,
                           io_flags,
                           saddr,
                           addr_len,
                           this,
                           0);

    return this->check_start_error ((rc==0), ACE_LIB_TEXT("WSASendTo"));
}


// *****************************************************************************
// AIO Connect results and initiators 
// *****************************************************************************
TRB_WIN32_Asynch_Connect_Result::TRB_WIN32_Asynch_Connect_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Connect_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
{
}

TRB_WIN32_Asynch_Connect_Result::~TRB_WIN32_Asynch_Connect_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Connect_Result::get_original_result () 
{
    return this->original_;
}

int
TRB_WIN32_Asynch_Connect_Result::start_impl ()
{ 
    DWORD       bytes_written = 0;
    DWORD       bytes_to_write = original_.bytes_requested ();
    const char *buf = 0;

    if (bytes_to_write != 0)
    {
        if (bytes_to_write > MAXDWORD)
        {
            errno = ERANGE;
            return -1;
        }

        buf = original_.get_buffer ();
        if (buf == 0)
        {
            const ACE_Message_Block * msg = 
                original_.get_message_block_ptr ();

            if (msg == 0) 
            {
                errno = EINVAL;
                return -1;
            }
            buf = msg->rd_ptr();

            if (bytes_to_write > msg->length ())
                bytes_to_write = msg->length ();
        }
    }


    sockaddr *saddr     = (sockaddr *) original_.remote_address().get_addr ();
    int       saddr_len = original_.remote_address().get_size();

    LPFN_CONNECTEX lpfnConnectEx = NULL; // a pointer to the 'ConnectEx()' function
    GUID GuidConnectEx = WSAID_CONNECTEX; // The Guid


    if (0 != ::WSAIoctl (reinterpret_cast<SOCKET> (original_.handle ()),
                         SIO_GET_EXTENSION_FUNCTION_POINTER,
                         &GuidConnectEx,
                         sizeof(GuidConnectEx),
                         &lpfnConnectEx,
                         sizeof(lpfnConnectEx),
                         &bytes_written,
                         0,
                         0))
    {
        ACE_OS::set_errno_to_last_error ();
        ACE_ASSERT (errno != ERROR_IO_PENDING);
        return this->check_start_error (false, ACE_LIB_TEXT("WSAIoctl for ConnectEx"));
    }


    this->win32_proactor ()->add_connect (this);

    // Initiate the connect
    BOOL rc = lpfnConnectEx (reinterpret_cast<SOCKET> (original_.handle ()),
                             saddr,
                             saddr_len,
                             (PVOID)buf,
                             bytes_to_write,
                             &bytes_written,
                             this);

    int ret = this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("ConnectEx"));

    if (ret < 0)
    {
        this->win32_proactor ()->remove_connect (this);
    }

    return ret;
}

int
TRB_WIN32_Asynch_Connect_Result::on_complete ()
{
    this->win32_proactor ()->remove_connect (this);

    ACE_HANDLE handle = original_.handle ();

    if (original_.error() == 0)
    {
        if (handle == ACE_INVALID_HANDLE)
        {
            original_.set_completion (0, ERROR_OPERATION_ABORTED);
        }
        else
        {
            ACE_OS::setsockopt (handle,
                                SOL_SOCKET,
                                SO_UPDATE_CONNECT_CONTEXT,
                                0,
                                0);
        }
    }

  return 0;
}

// *****************************************************************************
// AIO Accept results and initiators 
// *****************************************************************************
TRB_WIN32_Asynch_Accept_Result::TRB_WIN32_Asynch_Accept_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Accept_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
{
}

TRB_WIN32_Asynch_Accept_Result::~TRB_WIN32_Asynch_Accept_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Accept_Result::get_original_result () 
{
   return this->original_;
}

int
TRB_WIN32_Asynch_Accept_Result::start_impl ()
{ 
    DWORD    bytes_to_read = original_.bytes_requested();
    DWORD    bytes_read = 0;
    size_t   address_size = ACCEPT_EXTRA_BUF_BYTES;
    char    *buf = 0;

    if (bytes_to_read == 0)
    {
        buf = this->addr_buf_;
    }
    else if (bytes_to_read > MAXDWORD)
    {
        // AcceptEx API limits us to DWORD range.
        errno = ERANGE;
        return -1;
    }
    else
    {
        buf = original_.get_buffer ();
        size_t space = bytes_to_read;
        if (buf == 0)
        {
            const ACE_Message_Block * msg = 
                original_.get_message_block_ptr ();

            if (msg == 0) 
            {
                errno = EINVAL;
                return -1;
            }
            buf = msg->wr_ptr();
            space = msg->space ();
        }

        if (space <  2*address_size)
        {
            errno = ENOSPC;
            ACE_ERROR_RETURN ((LM_ERROR, 
                ACE_LIB_TEXT ("TRB_WIN32_Asynch_Accept_Result::start:")
                ACE_LIB_TEXT ("Buffer too small\n")), 
                -1);
        }

        space -= 2*address_size;
        if (bytes_to_read > space)
            bytes_to_read = space;
    }

    ACE_HANDLE accept_handle = ACE_INVALID_HANDLE;

    // If the <accept_handle> is invalid, we will create a new socket.
    if (original_.accept_handle () == ACE_INVALID_HANDLE)
    {
        TRB_Sock_Addr tmp_addr;
        tmp_addr.getsockname (original_.listen_handle ());

        accept_handle = ACE_OS::socket (tmp_addr.get_type (),
                                        SOCK_STREAM,
                                        0);

        if (accept_handle == ACE_INVALID_HANDLE)
        {
            if (ACE::debug ())
            {
                ACE_DEBUG ((LM_ERROR,
                    ACE_LIB_TEXT ("TRB_WIN32_Asynch_Accept_Result::start:%p\n"),
                    ACE_LIB_TEXT ("ACE_OS::socket")));
            }
            return -1;
        }

        // store as accepted handle
        original_.set_accept_handle (accept_handle);
    }


    // Initiate the accept
    BOOL rc = ::AcceptEx (reinterpret_cast<SOCKET> (original_.listen_handle ()),
                          reinterpret_cast<SOCKET> (original_.accept_handle ()),
                          buf,
                          bytes_to_read,
                          address_size,
                          address_size,
                          &bytes_read,
                          this);

    int ret = this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("AcceptEx"));
    if (ret < 0 && accept_handle != ACE_INVALID_HANDLE)
    {
        // Remember to close the socket down if failures occur.
        ACE_OS::closesocket (accept_handle);
        original_.set_accept_handle (ACE_INVALID_HANDLE);
    }
    return ret;
}

int
TRB_WIN32_Asynch_Accept_Result::on_complete ()
{
    if (original_.error () == 0) 
    {
        DWORD    bytes_to_read = original_.bytes_requested ();
        size_t   address_size = ACCEPT_EXTRA_BUF_BYTES;
        char    *buf = 0;

        if (bytes_to_read == 0)
        {
            buf = this->addr_buf_;
        }
        else
        {
            buf = original_.get_buffer ();
            size_t space = bytes_to_read;
            if (buf == 0)
            {
                const ACE_Message_Block * msg = 
                    original_.get_message_block_ptr ();

                buf = msg->wr_ptr();
                space = msg->space ();
            }

            space -= 2*address_size;
            if (bytes_to_read > space)
                bytes_to_read = space;
        }

        sockaddr *local_addr = 0;
        sockaddr *remote_addr = 0;
        int local_size = 0;
        int remote_size = 0;

        ::GetAcceptExSockaddrs (buf,
                                bytes_to_read,
                                address_size,
                                address_size,
                                &local_addr,
                                &local_size,
                                &remote_addr,
                                &remote_size);

        this->original_.update_addresses (local_addr,
                                          local_size,
                                          remote_addr,
                                          remote_size);


        ACE_HANDLE listen_handle = original_.listen_handle();

        if (ACE_OS::setsockopt (original_.accept_handle (),
                                SOL_SOCKET,
                                SO_UPDATE_ACCEPT_CONTEXT,
                                (char *) &listen_handle,
                                sizeof (ACE_HANDLE)) == -1)
        {
            ACE_OS::set_errno_to_last_error ();
            original_.set_completion (0, errno);
        }
    }

    if (original_.error () != 0)
    {
        // Remember to close the socket down if failures occur.
        ACE_OS::closesocket (original_.accept_handle ());
        original_.set_accept_handle (ACE_INVALID_HANDLE);
    }

    return 0;
}

// *****************************************************************************
// AIO Transmit_File results and initiators 
// *****************************************************************************
TRB_WIN32_Asynch_Transmit_File_Result::TRB_WIN32_Asynch_Transmit_File_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Transmit_File_Result&  original,
     TRB_WIN32_Proactor *win32_proactor)
  : TRB_WIN32_Asynch_Result (allocator, 
                             area,
                             win32_proactor,
                             original.offset (),
                             original.offset_high ())
  , original_               (original)
{
}

TRB_WIN32_Asynch_Transmit_File_Result::~TRB_WIN32_Asynch_Transmit_File_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_WIN32_Asynch_Transmit_File_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_WIN32_Asynch_Transmit_File_Result::start_impl ()
{ 
    size_t    bytes_to_write = original_.bytes_requested ();
    size_t    bytes_per_send = original_.bytes_per_send ();
    DWORD     bytes_written  = 0;


    // TransmitFile API limits us to DWORD range.
    if (bytes_to_write > MAXDWORD || bytes_per_send > MAXDWORD)
    {
        errno = ERANGE;
        return -1;
    }

    ACE_LPTRANSMIT_FILE_BUFFERS transmit_buffers = 0;
    if (original_.header_and_trailer () != 0)
    {
        transmit_buffers = original_.header_and_trailer ()->transmit_buffers ();
    }

    // Initiate the transmit file
    BOOL rc = ::TransmitFile ((SOCKET) original_.socket (),
                              original_.file (),
                              bytes_to_write,
                              bytes_per_send,
                              this,
                              transmit_buffers,
                              original_.flags());

    return this->check_start_error ((rc==TRUE), ACE_LIB_TEXT("TransmitFile"));
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 || ACE_HAS_WINCE */
