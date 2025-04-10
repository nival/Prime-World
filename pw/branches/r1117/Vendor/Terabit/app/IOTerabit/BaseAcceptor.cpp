/* -*- C++ -*- */

#include "IOTerabit/BaseAcceptor.h"
#include "ace/OS_Errno.h"
#include "ace/OS_Memory.h"
#include "ace/OS_NS_sys_socket.h"


#include "ace/Log_Msg.h"
#include "ace/SOCK_Stream.h"
#include "ace/Sock_Connect.h"
#include "ace/Trace.h"

namespace Terabit {

BaseAcceptor::BaseAcceptor (void)
: monitor_        ()
, state_          (ST_INIT)
, pending_count_  (0)
, listen_handle_  (ACE_INVALID_HANDLE)
, asynch_accept_  ()
, reissue_accept_ (1)
, bytes_to_read_  (0)
, seq_num_        (0)
, mb_factory_     (8)
{
}


BaseAcceptor::~BaseAcceptor (void)
{
    this->cancel ();
    this->wait ();
}

int
BaseAcceptor::open (const ACE_Addr& address,
                    size_t bytes_to_read,
                    int backlog,
                    int reuse_addr,
                    TRB_Proactor *proactor,
                    int reissue_accept,
                    int number_of_initial_accepts)
{
    ACE_TRACE ("BaseAcceptor<>::open");

    Guard_Monitor guard (monitor_);

    switch (this->state_)
    {
    case ST_CANCEL:     return -1;
    case ST_ACTIVE:
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) BaseAcceptor:  already open\n")),
            -1);
    default:
        break;
    }

    this->proactor (proactor);
    this->bytes_to_read_ = bytes_to_read;
    this->reissue_accept_ = reissue_accept;

    // Create the listener socket
    this->listen_handle_ = ACE_OS::socket (address.get_type (), SOCK_STREAM, 0);
    if (this->listen_handle_ == ACE_INVALID_HANDLE)
    {
        ACE_Errno_Guard g (errno);
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) BaseAcceptor:  %p\n"),
            ACE_LIB_TEXT ("ACE_OS::socket")),
            -1);
    }

    this->state_ = ST_ACTIVE;

    if (reuse_addr)
    {
        // Reuse the address
        int one = 1;
        if (ACE_OS::setsockopt (this->listen_handle_,
                                SOL_SOCKET,
                                SO_REUSEADDR,
                                (const char*) &one,
                                sizeof one) == -1)
        {
            ACE_Errno_Guard g (errno);
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT ("(%t) BaseAcceptor:  %p\n"),
                ACE_LIB_TEXT ("ACE_OS::setsockopt")),
                -1);
        }
    }

    // Bind to the specified port.
    if (ACE_OS::bind (this->listen_handle_,
                      reinterpret_cast<sockaddr *>
                             (address.get_addr ()),
                      address.get_size ()) == -1)
    {
        ACE_Errno_Guard g (errno);
        ACE_ERROR_RETURN ((LM_ERROR,
            "(%t) BaseAcceptor:  %p\n",
            "ACE_OS::bind"),
            -1);
    }

    // Start listening.
    if (ACE_OS::listen (this->listen_handle_, backlog) == -1)
    {
        ACE_Errno_Guard g (errno);
        ACE_ERROR_RETURN ((LM_ERROR,
            "(%t) BaseAcceptor:  %p\n",
            "ACE_OS::listen"),
            -1);
    }

    // Initialize the TRB_Asynch_Accept
    if (this->asynch_accept_.open (*this,
                                   this->listen_handle_,
                                   0,
                                   this->proactor ()) == -1)
    {
        ACE_Errno_Guard g (errno);
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) BaseAcceptor:  %p\n"),
            ACE_LIB_TEXT ("open")),
            -1);
    }


    // For the number of <initial_accepts>.
    if (number_of_initial_accepts == -1)
    {
        number_of_initial_accepts = backlog;
    }

    for (int i = 0; i < number_of_initial_accepts; i++)
    {
        // Initiate accepts.
        if (this->accept_i (bytes_to_read, guard) != 0)
        {
            ACE_Errno_Guard g (errno);
            ACE_ERROR_RETURN ((LM_ERROR,
                "(%t) BaseAcceptor:  %p\n",
                "accept_i failed"),
                -1);
        }
    }
    return 0;
}


int
BaseAcceptor::get_pending_count (void) const
{
    Guard_Monitor guard (monitor_);
    return this->pending_count_;
}


int
BaseAcceptor::accept (size_t bytes_to_read)
{
    Guard_Monitor guard (monitor_);
    return accept_i (bytes_to_read, guard);
}
  
int
BaseAcceptor::accept_i (size_t bytes_to_read, 
                        Guard_Monitor& guard)
{
    ACE_TRACE ("BaseAcceptor<>::accept_i");

    Save_Guard saver(guard, Save_Guard::ACQUIRE);

    if (this->state_ != ST_ACTIVE || 
        this->listen_handle_ == ACE_INVALID_HANDLE)
    {
        return -1;
    }

    int rc = 0;

    ACE_Message_Block *message_block = 0;

    if (bytes_to_read == 0)
    {
        rc = this->asynch_accept_.accept ((const void *) ++this->seq_num_);
    }
    else
    {
        enum 
        {
            ACCEPT_EXTRA_BUF_BYTES = sizeof(ACE_INET_Addr)+16
        };

        size_t space_needed = bytes_to_read + 2 * ACCEPT_EXTRA_BUF_BYTES;
        
        // Create a new message block big enough for the addresses and data
        message_block = mb_factory_.alloc_msg (space_needed);
        if (message_block == 0)
        {
            return -1;
        }

        // Initiate asynchronous accepts
        rc = this->asynch_accept_.accept (*message_block,
                                          bytes_to_read,
                                          (const void *) ++this->seq_num_);
    }

    if (rc == 0)
    {
        ++this->pending_count_;
    }
    else
    {
        // Cleanup on error, it is OK if message_block is null
        mb_factory_.free_msg (message_block);
    }
    return rc;
}

void
BaseAcceptor::handle_accept (const TRB_Asynch_Accept::Result &result)
{
    ACE_TRACE ("BaseAcceptor<>::handle_accept");

    // Variable for error tracking
    int error = result.error ();
    ACE_HANDLE handle = result.accept_handle ();

    if (error != 0 || handle == ACE_INVALID_HANDLE)
    {
        // asynchronous accept fails.
        this->reissue_accept (0);
        

        ACE_Errno_Guard g (errno);

        ACE_Log_Msg::instance ()->errnum (error);
        ACE_OS::last_error (error);

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) BaseAcceptor: act=%u error=%d %p\n"),
                    (intptr_t) result.act(),
                    error,
                    ACE_TEXT ("accept failed")));
    }
    else if (this->reissue_accept ())
    {
        // accept was successfull
        // Start off another asynchronous accept to keep the backlog going
        this->accept (this->bytes_to_read_);
    }

    if (this->on_accept_completed (result) != 0 && // handle was not taken
        handle != ACE_INVALID_HANDLE)
    {
        ACE_OS::closesocket (handle);
    }

    {
        Guard_Monitor guard (monitor_);
        mb_factory_.free_msg (result.get_message_block_ptr ());
   
        --this->pending_count_;
        if (this->pending_count_ == 0 && this->state_ == ST_CANCEL)
        {
            guard.broadcast (); // notify all waiters
        }
    }
}


void
BaseAcceptor::wait (void)
{
    Guard_Monitor guard (monitor_);
    while (this->pending_count_ != 0)
    {
        guard.wait ();
    }
    if (this->state_ == ST_CANCEL)
    {
        this->state_ = ST_CLOSED;
    }
}

int
BaseAcceptor::cancel (void)
{
    ACE_TRACE ("BaseAcceptor<>::cancel");

    Guard_Monitor guard (monitor_);

    if (this->state_ != ST_ACTIVE)
        return 0;


    this->state_ = ST_CANCEL;
    
    // prevent reissue new accepts
    this->reissue_accept (0);

    // All I/O operations that are canceled will complete with the error
    // ERROR_OPERATION_ABORTED. All completion notifications for the I/O
    // operations will occur normally.

    int rc = 0;
    // This only one way to stop all pending accepts
    // after cancel on Windows
    if (this->listen_handle_ != ACE_INVALID_HANDLE)
    {
        rc = this->asynch_accept_.cancel();

        ACE_OS::closesocket (this->listen_handle_);
        this->listen_handle_ = ACE_INVALID_HANDLE;
    }

    return rc;
}

}  //namespace Terabit 
