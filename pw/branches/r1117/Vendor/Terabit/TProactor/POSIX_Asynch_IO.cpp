/* -*- C++ -*- */
// POSIX_Asynch_IO.cpp,v 4.46 2002/11/09 23:51:29 shuston Exp

#include "TProactor/POSIX_Asynch_IO.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "TProactor/POSIX_Proactor.h"


#include "ace/Log_Msg.h"
#include "ace/Message_Block.h"
#include "ace/SOCK_Stream.h"
#include "ace/OS_NS_errno.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_socket.h"
#include "ace/OS_NS_sys_stat.h"
#include "ace/OS_NS_poll.h"
#include "ace/OS_NS_sys_uio.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// **************************************************************
//  TRB_POSIX_Asynch_Result
// **************************************************************
LinkS_T <TRB_POSIX_Asynch_Result> *
TRB_POSIX_Asynch_Result::get_link () const
{
    return & this->link_;
}

 
TRB_POSIX_Asynch_Result::TRB_POSIX_Asynch_Result (
        ACE_Allocator            *allocator,
        void                     *area,
        const TRB_Asynch_Result&  original,
        TRB_POSIX_Proactor       *posix_proactor)
: TRB_Asynch_Result_Impl (allocator , area)
, link_ ()
, posix_proactor_ (posix_proactor)
{
  ACE_UNUSED_ARG (original);
  memset(&aio_, 0, sizeof(aio_)); 
}

TRB_POSIX_Asynch_Result::~TRB_POSIX_Asynch_Result (void)
{
}

void 
TRB_POSIX_Asynch_Result::build_aiocb()
{
  TRB_Asynch_Result& original = this->get_original_result();

  this->aio_.aiocb_.aio_fildes  = original.handle ();
  this->aio_.aiocb_.aio_offset  = original.offset ();
  this->aio_.aiocb_.aio_reqprio = original.priority ();
  
  //default notification method
  this->aio_.aiocb_.aio_sigevent.sigev_notify = SIGEV_NONE;
  this->aio_.aiocb_.aio_sigevent.sigev_signo = original.signal_number ();
  this->aio_.aiocb_.aio_sigevent.sigev_value.sival_ptr = this ;

  this->aio_.aiocb_.aio_buf = 0;
  this->aio_.aiocb_.aio_nbytes = original.bytes_requested ();
  
  int   iovcnt = original.get_iov_count ();
  if (iovcnt < 0)   // ACE_Message_Block
  {
    ACE_Message_Block *msg = original.get_message_block_ptr ();
    if (msg != 0)
    {
      if (original.is_read_family ())
          this->aio_.aiocb_.aio_buf = msg->wr_ptr();
      else if (original.is_write_family ())
        this->aio_.aiocb_.aio_buf = msg->rd_ptr();
    }
  }
  else if (iovcnt == 0)  // simple buffer
  {
    this->aio_.aiocb_.aio_buf = original.get_buffer ();
  }
  else  // iovec
  {
    iovec *iov = original.get_iov ();
    this->aio_.aiocb_.aio_buf = iov[0].iov_base;

    if (this->aio_.aiocb_.aio_nbytes > iov[0].iov_len)
      this->aio_.aiocb_.aio_nbytes = iov[0].iov_len;
  }
}

int
TRB_POSIX_Asynch_Result::post_impl ()
{
  return this->posix_proactor ()->post (this);
}

int
TRB_POSIX_Asynch_Result::start_impl ()
{
  return this->posix_proactor ()->start (this);
}

// *****************************************************************************
// AIO read results and initiators for streams and files 
// *****************************************************************************
TRB_POSIX_Asynch_Read_Stream_Result::TRB_POSIX_Asynch_Read_Stream_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Read_Stream_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Read_Stream_Result::~TRB_POSIX_Asynch_Read_Stream_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Read_Stream_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Read_Stream_Result::execute  ()
{ 
    int     rc = 2;         // finished and next op possible
    int     aio_error = 0;
    ssize_t aio_return = 0;

    size_t  bytes_to_read = original_.bytes_requested ();
    size_t  bytes_read    = original_.bytes_transferred ();

    if (original_.op_code () == TRB_Asynch_Result::OP_READ_FILE)
    {
        off_t pos = ACE_OS::lseek (original_.handle (),
                                   original_.offset () + bytes_read,
                                   SEEK_SET);


        if (pos == ACE_static_cast (off_t, -1))
        {
            aio_error = ACE_OS::last_error ();
            original_.set_completion (0, aio_error);
            return rc;
        }
    }

    if (original_.is_iov_operation ())
    {
        iovec  iov[ACE_IOV_MAX];
        int    iovcnt = ACE_IOV_MAX;
        int    ok = -1;

        if (original_.is_direct_buffers ())
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
            original_.set_completion (0, EINVAL);
            return rc;
        }

        aio_return = ACE_OS::readv (original_.handle(),
                                    iov,
                                    iovcnt);
    }
    else  // read, but not readv
    {
        char *buf = original_.get_buffer ();
        if (buf == 0)
        {
            ACE_Message_Block *msg = original_.get_message_block_ptr ();
            if (msg == 0)
            {
                original_.set_completion (0, EINVAL);
                return rc;
            }

            buf = msg->wr_ptr ();
        }

        ACE_ASSERT (bytes_to_read >= bytes_read);

        buf           += bytes_read;
        bytes_to_read -= bytes_read;

        aio_return = ACE_OS::read (original_.handle(),
                                   buf,
                                   bytes_to_read);
    }

    if (aio_return < 0)
    {
        aio_error = ACE_OS::last_error ();

        if (aio_error == EWOULDBLOCK)
        {
            return 0; // not finished
        }

        original_.set_completion (0, aio_error);
        return rc;   // finished and next op possible
    }

    if (aio_return != 0)
    {
        if ((size_t) aio_return != bytes_to_read)
        {
            rc = 1;  //  finished and next op may be possible

            if (ACE_BIT_ENABLED (original_.op_flags(), 
                                 TRB_Asynch_Result::FLG_EXACTLY_BYTES))
            {
                rc = 0;  // not finished
            }
        }
    }

    original_.set_completion (aio_return, 0);
    return rc;  // finished
}

// *****************************************************************************
// AIO write results and initiators for streams and files 
// *****************************************************************************
TRB_POSIX_Asynch_Write_Stream_Result::TRB_POSIX_Asynch_Write_Stream_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Write_Stream_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Write_Stream_Result::~TRB_POSIX_Asynch_Write_Stream_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Write_Stream_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Write_Stream_Result::execute  ()
{ 
    int     rc = 2;  //    finished and next op possible
    int     aio_error = 0;
    ssize_t aio_return = 0;
    size_t  bytes_to_write = original_.bytes_requested ();
    size_t  bytes_written  = original_.bytes_transferred ();


    if (original_.op_code () == TRB_Asynch_Result::OP_WRITE_FILE)
    {
        off_t pos = ACE_OS::lseek (original_.handle (),
            original_.offset () + bytes_written,
            SEEK_SET);


        if (pos == ACE_static_cast (off_t, -1))
        {
            aio_error = ACE_OS::last_error ();
            original_.set_completion (0, aio_error);
            return rc;
        }
    }

    if (original_.is_iov_operation ())
    {
        iovec  iov[ACE_IOV_MAX];
        int    iovcnt = ACE_IOV_MAX;
        int ok = -1;

        if (original_.is_direct_buffers ())
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
            original_.set_completion (0, EINVAL);
            return rc;
        }

        aio_return = ACE_OS::writev (original_.handle(),
                                     iov,
                                     iovcnt);

    }
    else  // write, but not writev
    {
        char *buf = original_.get_buffer ();
        if (buf == 0)
        {
            ACE_Message_Block *msg = original_.get_message_block_ptr ();
            if (msg == 0)
            {
                original_.set_completion (0, EINVAL);
                return rc;
            }

            buf = msg->rd_ptr ();
        }

        ACE_ASSERT (bytes_to_write >= bytes_written);

        buf            += bytes_written;
        bytes_to_write -= bytes_written;

        aio_return = ACE_OS::write (original_.handle(),
                                    buf,
                                    bytes_to_write);
    }


    if (aio_return < 0)
    {
        aio_error = ACE_OS::last_error ();

        if (aio_error == EWOULDBLOCK)
            return 0; // not finished

        original_.set_completion (0, aio_error);
        return rc;
    }

    if ((size_t) aio_return != bytes_to_write)
    {
         rc = 1;  //  finished and next op may be possible
         if (ACE_BIT_ENABLED (original_.op_flags(), 
                              TRB_Asynch_Result::FLG_EXACTLY_BYTES))
          {
                rc = 0;  // not finished
          }
    }


    original_.set_completion (aio_return, 0);
    return rc;  // finished
}


// *****************************************************************************
// AIO read results and initiators for datagrams
// *****************************************************************************
TRB_POSIX_Asynch_Read_Dgram_Result::TRB_POSIX_Asynch_Read_Dgram_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Read_Dgram_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Read_Dgram_Result::~TRB_POSIX_Asynch_Read_Dgram_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Read_Dgram_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Read_Dgram_Result::execute ()
{ 
    // to be compatible with original ACE version
    size_t  bytes_to_read = (size_t) -1; //  read as many as can
    //size_t  bytes_to_read = original_.bytes_requested ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;

    int ok = -1;
    if (!original_.is_direct_buffers ())
    {
        ok = build_read_iovec (original_.get_message_block_ptr (),
                               original_.is_iov_operation ()? true : false,
                               iov,
                               iovcnt,
                               bytes_to_read,
                               0);
    }
    else if (original_.is_iov_operation ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_read,
                         0);

    }
    else
    {
        iov[0].iov_base = original_.get_buffer ();
        iov[0].iov_len = bytes_to_read;
        iovcnt = 1;
        ok = 0;
    }

    if (ok != 0)
    {
        original_.set_completion (0, EINVAL);
        return 2;
    }

    /// msghdr structure
    struct msghdr  msg_hdr;

    msg_hdr.msg_iov = iov;
    msg_hdr.msg_iovlen = iovcnt;

#if defined (ACE_HAS_4_4BSD_SENDMSG_RECVMSG)
    msg_hdr.msg_control = 0;
    msg_hdr.msg_controllen = 0;
    msg_hdr.msg_flags = 0;
#else
    msg_hdr.msg_accrights = 0;
    msg_hdr.msg_accrightslen = 0;
#endif

    msg_hdr.msg_namelen = original_.remote_address().get_size();
    msg_hdr.msg_name = 
#if defined (ACE_HAS_SOCKADDR_MSG_NAME)
        (struct sockaddr *)
#else
        (char *)
#endif /* ACE_HAS_SOCKADDR_MSG_NAME */
        original_.remote_address().get_addr ();


    int     aio_error  = 0;
    ssize_t aio_return = ACE_OS::recvmsg (original_.handle (),
                                          &msg_hdr,
                                          original_.flags ());

    if (aio_return < 0)
    {
        aio_error = ACE_OS::last_error ();

        if (aio_error == EWOULDBLOCK)
            return 0; // not finished

        original_.set_completion (0, aio_error);
        return 2;
    }


#if defined (ACE_HAS_4_4BSD_SENDMSG_RECVMSG)
    original_.set_flags (msg_hdr.msg_flags);
#endif

    original_.set_completion (aio_return, 0);
    return 2;  // finished
}

// *****************************************************************************
// AIO write read results and initiators for datagrams
// *****************************************************************************
TRB_POSIX_Asynch_Write_Dgram_Result::TRB_POSIX_Asynch_Write_Dgram_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Write_Dgram_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Write_Dgram_Result::~TRB_POSIX_Asynch_Write_Dgram_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Write_Dgram_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Write_Dgram_Result::execute ()
{
    // to be compatible with original ACE version
    size_t  bytes_to_write = (size_t) -1; //  write as many as can
    //size_t  bytes_to_write = original_.bytes_requested ();

    iovec  iov[ACE_IOV_MAX];
    int    iovcnt = ACE_IOV_MAX;

    int ok = -1;
    if (!original_.is_direct_buffers ())
    {
        ok = build_write_iovec (original_.get_message_block_ptr (),
                                original_.is_iov_operation ()? true : false,
                                iov,
                                iovcnt,
                                bytes_to_write,
                                0);
    }                       
    else if (original_.is_iov_operation ())
    {
        ok = copy_iovec (original_.get_iov (),
                         original_.get_iov_count (),
                         iov,
                         iovcnt,
                         bytes_to_write,
                         0);
    }                
    else
    {
        iov[0].iov_base = original_.get_buffer ();
        iov[0].iov_len = bytes_to_write;
        iovcnt = 1;
        ok = 0;
    }

    if (ok != 0)
    {
        original_.set_completion (0, EINVAL);
        return 2;
    }

    /// msghdr structure
    struct msghdr  msg_hdr;

    msg_hdr.msg_iov = iov;
    msg_hdr.msg_iovlen = iovcnt;

    //#if (defined(sun) && defined(_XOPEN_SOURCE) && (_XOPEN_VERSION - 0 == 4)) /* XPG4 or XPG4v2 */
#if defined (ACE_HAS_4_4BSD_SENDMSG_RECVMSG)
    msg_hdr.msg_control = 0;
    msg_hdr.msg_controllen = 0;
    msg_hdr.msg_flags = 0;   // recv flags   original_.flags ();
#else
    msg_hdr.msg_accrights = 0;
    msg_hdr.msg_accrightslen = 0;
#endif

    msg_hdr.msg_namelen = original_.remote_address().get_size();
    msg_hdr.msg_name = 
#if defined (ACE_HAS_SOCKADDR_MSG_NAME)
        (struct sockaddr *)
#else
        (char *)
#endif /* ACE_HAS_SOCKADDR_MSG_NAME */
        original_.remote_address().get_addr ();


    int     aio_error  = 0;
    ssize_t aio_return = ACE_OS::sendmsg (original_.handle (),
                                          &msg_hdr,
                                          original_.flags ());

    if (aio_return < 0)
    {
        aio_error = ACE_OS::last_error ();

        if (aio_error == EWOULDBLOCK)
            return 0; // not finished

        original_.set_completion (0, aio_error);
        return 2;
    }


    original_.set_completion (aio_return, 0);
    return 2;  // finished
}

// *****************************************************************************
// AIO Accept results and initiators 
// *****************************************************************************
TRB_POSIX_Asynch_Accept_Result::TRB_POSIX_Asynch_Accept_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Accept_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Accept_Result::~TRB_POSIX_Asynch_Accept_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Accept_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Accept_Result::execute ()
{ 
    ACE_HANDLE listen_handle = original_.listen_handle();

    while (true)
    {
        ACE_HANDLE new_handle = ACE_OS::accept (listen_handle, 0, 0);

        if (new_handle != ACE_INVALID_HANDLE)
        {
           // Store the new handle.
           ACE::clr_flags (new_handle, ACE_NONBLOCK);
           original_.set_accept_handle(new_handle);
           original_.update_addresses (new_handle);

           original_.set_completion(0, 0);
           return 1;  // next accept  may be possible
        }

        int aio_error = ACE_OS::last_error ();
        switch (aio_error)
        { 
        case EWOULDBLOCK:
            return 0;

        case EINTR:
           continue;

        default:
           // Put any valid address
           original_.update_addresses (listen_handle);
           original_.set_completion(0, aio_error);
           return 1;  // next accept  may be possible
        }
    }
    
    return 1;  // never reached 
}

// *****************************************************************************
// AIO Connect results and initiators 
// *****************************************************************************
TRB_POSIX_Asynch_Connect_Result::TRB_POSIX_Asynch_Connect_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Connect_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, original_               (original)
{
}

TRB_POSIX_Asynch_Connect_Result::~TRB_POSIX_Asynch_Connect_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Connect_Result::get_original_result () 
{
  return this->original_;
}

int
TRB_POSIX_Asynch_Connect_Result::execute ()
{ 
    ACE_HANDLE handle = original_.handle ();
    int aio_error = 0;

    struct pollfd pfd;

    pfd.fd      = handle;
    pfd.events  = (POLLIN|POLLOUT);
    pfd.revents = 0;

    int rc = ::poll (&pfd, 1, 0);

    if (rc == 0)  // not ready
        return 0;

    if (rc < 0)  // errors
    {
        aio_error = ACE_OS::last_error ();
        original_.set_completion(0, aio_error);
        return 2;
    }


    int sockerror  = 0 ;
    int lsockerror = sizeof sockerror;

    ACE_OS::getsockopt (handle,
                        SOL_SOCKET,
                        SO_ERROR,
                        (char*) &sockerror,
                        &lsockerror);

    ACE::clr_flags (handle, ACE_NONBLOCK);

    original_.set_completion (0, sockerror);
    return 2;   // next op with new handle is possible
}

int
TRB_POSIX_Asynch_Connect_Result::start_impl ()
{ 
    const ACE_Addr & addr = this->original_.remote_address ();

    // register_handle() sets NONBLOCK
    //ACE::set_flags (handle, ACE_NONBLOCK);

    for (;;)
    {
        int rc = ACE_OS::connect (this->original_.handle (),
                                  reinterpret_cast<sockaddr *>
                                            (addr.get_addr ()),
                                  addr.get_size ());

        if (rc == 0)
        {
            this->set_completion (0, 0);
            return this->posix_proactor ()->post (this);
        }

        if (errno == EWOULDBLOCK || errno == EINPROGRESS )
        {
            return this->posix_proactor ()->start (this);
        }

        if (errno != EINTR)
        {
            break;
        }
    }

    // not started
    this->set_completion (0, errno);
    
    return this->posix_proactor ()->post (this);
    //return -1;
}

// *****************************************************************************
// AIO Transmit_File results and initiators 
// *****************************************************************************
TRB_POSIX_Asynch_Transmit_File_Result::TRB_POSIX_Asynch_Transmit_File_Result 
    (ACE_Allocator *allocator,
     void *area,
     const TRB_Asynch_Transmit_File_Result&  original,
     TRB_POSIX_Proactor *posix_proactor)
: TRB_POSIX_Asynch_Result (allocator, area,  original, posix_proactor)
, transmitter_            (*this, original)
{
}

TRB_POSIX_Asynch_Transmit_File_Result::~TRB_POSIX_Asynch_Transmit_File_Result (void)
{
}
 
TRB_Asynch_Result &
TRB_POSIX_Asynch_Transmit_File_Result::get_original_result () 
{
  return this->transmitter_.get_original_result ();
}

int
TRB_POSIX_Asynch_Transmit_File_Result::execute ()
{ 
  return -1;
}

int
TRB_POSIX_Asynch_Transmit_File_Result::start_impl ()
{
  int rc = transmitter_.transmit ();
  if (rc < 0)    // not started
    return -1;   
  
  if (rc > 0)    // immediately finished
    {
      return this->posix_proactor ()->post (this);
    }

  return 0;
}

void
TRB_POSIX_Asynch_Transmit_File_Result::on_complete (
               TRB_Asynch_File_Transmitter& transmitter)
{
  ACE_UNUSED_ARG (transmitter);
  this->dispatch ();
}

ACE_END_VERSIONED_NAMESPACE_DECL


#endif /* ACE_HAS_AIO_CALLS */
