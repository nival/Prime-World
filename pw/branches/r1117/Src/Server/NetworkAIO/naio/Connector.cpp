#include "naio/stdafx.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/Protocol.h"
#include "naio/Connector.h"
#include "naio/Channel.h"

using namespace Terabit;

namespace naio
{

Connector::Connector(IOThreadPool &    tp,
                    ProtocolFactory &  protocol_factory,
                    ChannelManager &   manager)
  :ChannelConnector(tp, protocol_factory, manager),
  protocol_factory_(protocol_factory),
  manager_(manager)
{
}

Connector::~Connector()
{
}

int Connector::on_connect_completed(const TRB_Asynch_Connect::Result &result)
{
  //
  //  copy/paste of ChannelConnector::on_connect_completed() because we can't call it
  //
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

      ACE_DEBUG ((LM_INFO,
        ACE_TEXT ("CONNECTED channel id=(C)%d remote=%s local=%s"),
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

    //  <-- changes here : begin -->
    (static_cast<Channel*>(channel.get()))->activate_protocol (protocol, data, len);
    //  <-- changes here : end -->

    return 0;
  }
}

}
