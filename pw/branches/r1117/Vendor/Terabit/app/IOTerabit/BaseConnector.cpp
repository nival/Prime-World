/* -*- C++ -*- */
#include "IOTerabit/BaseConnector.h"


#include "ace/OS_NS_sys_socket.h"
#include "ace/OS_Memory.h"
#include "ace/ACE.h"

#include "ace/Flag_Manip.h"
#include "ace/Log_Msg.h"
#include "ace/Message_Block.h"

namespace Terabit {


BaseConnector::BaseConnector (void)
: monitor_        ()
, state_          (ST_INIT)
, pending_count_  (0)
, asynch_connect_ ()
{
}


BaseConnector::~BaseConnector (void)
{
    this->cancel ();
    this->wait ();
}


 int
BaseConnector::get_pending_count (void) const
{
    Guard_Monitor guard (monitor_);
    return this->pending_count_;
}

 int
BaseConnector::open (TRB_Proactor *proactor)
{
    ACE_TRACE ("BaseConnector<>::open");

    Guard_Monitor guard (monitor_);

    switch (this->state_)
    {
    case ST_ACTIVE:   return 0;    // ignore
    case ST_CANCEL:   return -1;   // can be re-reopened after ST_CLOSED
    default:          break;
    }

    this->proactor (proactor);


    // Initialize the TRB_Asynch_Connect
    if (this->asynch_connect_.open (*this,
                                    ACE_INVALID_HANDLE,
                                    0,
                                    this->proactor ()) == -1)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) BaseConnector: TRB_Asynch_Connect::open failed")),
            -1);
    }
    this->state_ = ST_ACTIVE;

    return 0;
}


 int
BaseConnector::connect (const ACE_Addr & remote_sap,
                        const ACE_Addr & local_sap,
                        int reuse_addr,
                        const void *act)
{
    Guard_Monitor guard (monitor_);

    if (this->state_ != ST_ACTIVE)
    {
        return -1;
    }


    // Initiate asynchronous connect
    if (this->asynch_connect_.connect (ACE_INVALID_HANDLE,
                                       remote_sap,
                                       local_sap,
                                       reuse_addr,
                                       act) == -1)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_LIB_TEXT ("%N:%l %p\n"),
                       ACE_LIB_TEXT ("BaseConnector::connect")),
                      -1);
    }

    ++this->pending_count_;
    return 0;
}

 void
BaseConnector::handle_connect (const TRB_Asynch_Connect::Result &result)
{
    // Variable for error tracking
    int error = result.error ();
    ACE_HANDLE handle = result.connect_handle ();

    // If the asynchronous connect fails.
    if (error != 0 || handle == ACE_INVALID_HANDLE)
    {
        ACE_TCHAR buf [512];
        const ACE_Addr& addr = result.remote_address ();

        TRB_Sock_Addr::to_string (addr, buf, sizeof(buf));

        ACE_Errno_Guard g (errno);

        ACE_Log_Msg::instance ()->errnum (error);
        ACE_OS::last_error (error);

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) BaseConnector: %s act=%u error=%d %p\n"),
                    buf,
                    (intptr_t) result.act (),
                    error,
                    ACE_TEXT ("connect failed")));
    }
    else 
    {
        // set blocking mode 
        if (ACE::clr_flags (handle, ACE_NONBLOCK) != 0)
        {
            ACE_ERROR ((LM_ERROR,
                ACE_LIB_TEXT ("(%t) BaseConnector: %p\n"),
                ACE_LIB_TEXT ("Set blocking mode failed")));
        }
    }

    if (this->on_connect_completed (result) != 0 && // handle was not taken
        handle != ACE_INVALID_HANDLE)
    {
        ACE_OS::closesocket (handle);
    }

    Guard_Monitor guard (monitor_);

    --this->pending_count_;
    if (this->pending_count_ == 0 && this->state_ == ST_CANCEL)
    {
        guard.broadcast (); // notify all waiters
    }
}


void
BaseConnector::wait (void)
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
BaseConnector::cancel (void)
{
    ACE_TRACE ("BaseConnector<>::cancel");

    Guard_Monitor guard (monitor_);
  
    if (this->state_ != ST_ACTIVE)
        return 0;

    this->state_ = ST_CANCEL;

    //TODO: Windows cancel does not help
    // Compare: in Asynch_Acceptor we can close listen_handle
    // that makes real cancellation
    // POSIX: TProactor can handle cancel 
    return this->asynch_connect_.cancel ();
}

}  //namespace Terabit 

