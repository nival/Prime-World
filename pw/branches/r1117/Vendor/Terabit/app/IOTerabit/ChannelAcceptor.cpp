#include "IOTerabit/ChannelAcceptor.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/IOThreadPool.h"
#include "IOTerabit/Protocol.h"

namespace Terabit {

// *************************************************************
//  ChannelAcceptor
// *************************************************************
ChannelAcceptor::ChannelAcceptor (IOThreadPool &     task,
                                  ProtocolFactory &  protocol_factory, 
                                  ChannelManager &   manager)
: task_             (task)
, protocol_factory_ (protocol_factory)
, manager_          (manager)
, log_level_        (0)
{
}

ChannelAcceptor::~ChannelAcceptor ()
{
}


int
ChannelAcceptor::start (const ACE_Addr& addr, 
                        int num_initial_accepts,
                        int bytes_to_read)
{
    int rc = this->open (addr,
                         bytes_to_read,
                         ACE_DEFAULT_BACKLOG,
                         1,  // reuse_addr = 1,
                         task_.get_proactor (0),
                         1,  // reissue_accept = 1,
                         num_initial_accepts);
    return rc;
}


int
ChannelAcceptor::on_accept_completed (const TRB_Asynch_Accept::Result &result)
{
    bool  success = result.success ();
    const void * act = result.act ();
    
    const ACE_Addr & local_addr = result.local_address ();
    const ACE_Addr & remote_addr = result.remote_address ();

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
              ACE_TEXT ("(%t) ACCEPTED  channel id=(S)%d remote=%s local=%s\n"),
              channel->get_id (),
              str_peer,
              str_local));
    }

    ACE_HANDLE handle = result.accept_handle ();
    rc = channel->open (handle, true);
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
    int                      len  = mb ? mb->length () : 0;
    const char              *data = len ? mb->rd_ptr () : 0;

    channel->activate_protocol (protocol, data, len);
    return 0;
}

}  //namespace Terabit 

