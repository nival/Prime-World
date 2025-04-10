#include "IOTerabit/ChannelConnector.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/IOThreadPool.h"
#include "IOTerabit/Protocol.h"

namespace Terabit {

// *************************************************************
//  ChannelConnector
// *************************************************************
ChannelConnector::ChannelConnector (IOThreadPool &     task,
                                    ProtocolFactory &  protocol_factory, 
                                    ChannelManager &   manager)
: task_             (task)
, protocol_factory_ (protocol_factory)
, manager_          (manager)
, log_level_        (0)
{
}

ChannelConnector::~ChannelConnector ()
{
}


int
ChannelConnector::start (const ACE_Addr& addr, const void *act)
{
    switch (this->get_state ())
    {
    case ST_CANCEL:   return -1;
    case ST_ACTIVE:   break;
    default:
        {
            TRB_Proactor * proactor = this->task().get_proactor(0);
            if (!proactor || this->open (proactor) != 0)
            {
                return -1;
            }
        }
        break;
    }

    int rc = this->connect(addr,
                           ACE_Addr::sap_any,
                           1,
                           act);
    return rc;
}


int
ChannelConnector::on_connect_completed (const TRB_Asynch_Connect::Result&  result)
{
    bool  success = result.success ();
    const void * act = result.act ();
    
    const ACE_Addr& local_addr  = result.local_address ();
    const ACE_Addr& remote_addr = result.remote_address ();

    int rc = this->protocol_factory_.validate_connection (success,
                                                          remote_addr,
                                                          local_addr,
                                                          act);
    if (!success || rc != 0)  // accept/connect failure
    {                         // or factory rejected to process
        return -1;            // new connection
    }


    AsynchChannelPtr  channel = this->manager_.allocate_channel ();
    if (!channel)
    {
        return -1;
    }

    channel->addresses (remote_addr, local_addr);
    if (this->get_log_level () < 2)
    {
        ACE_TCHAR str_peer [256];
        ACE_TCHAR str_local[256];

        TRB_Sock_Addr::to_string (remote_addr, str_peer, sizeof (str_peer)/sizeof (ACE_TCHAR));
        TRB_Sock_Addr::to_string (local_addr, str_local, sizeof (str_local)/sizeof (ACE_TCHAR));

        ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) CONNECTED channel id=(C)%d remote=%s local=%s\n"),
              channel->get_id (),
              str_peer,
              str_local));
    }


    ACE_HANDLE handle = result.connect_handle ();
    rc = channel->open (handle, false);
    if (rc < 0)
    {
        return 0;  // open failed, but handle ownership must be taken
    }

    // ownership of handle is taken
    Protocol *protocol = protocol_factory_.create_protocol (act);
    
    if (!protocol)
    {
        channel->close ();
        return 0;
    }

    const ACE_Message_Block *mb   = result.get_message_block_ptr ();
    int                      len  = result.bytes_transferred ();
    const char              *data = mb ? mb->base () : 0;

    channel->activate_protocol (protocol, data, len);
    return 0;
}

}  //namespace Terabit 


