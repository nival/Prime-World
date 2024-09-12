#include <naio/stdafx.h>
#include <naio/BaseProtocol.h>
#include <naio/Channel.h>

namespace naio
{
  // ***************************************************
  // Channel
  // ***************************************************
  Channel::Channel (int id)
    : Terabit::TcpChannel (id, 0),
    protocol_(0)
  {
  }

  Channel::~Channel ()
  {
  }

  int Channel::activate_protocol (Terabit::Protocol     *protocol,
      const char   *data,
      size_t        datalen)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    protocol_ = static_cast<naio::BaseProtocol*>(protocol);

    return TcpChannel::activate_protocol(protocol, data, datalen);
  }

  void Channel::handle_user_operation(const TRB_Asynch_User_Result& result)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_ASSERT(result.act());

    Ptr<Operation> op(const_cast<Operation*>(reinterpret_cast<Operation const *>(result.act())), false);
    if (protocol_)
    {
      int rc = protocol_->on_user_operation(this, op);
      rc;
    }
    else
    {
      ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Protocol is NULL(ch=%d)"), 
        __FUNCTION__, this->get_id()));
    }
  }
}
