#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/AsynchChannel.h>
#include "TransportMessagesHeaders.h"
#include "BaseProtocol.h"
#include "BaseChannel.h"
#include "ace/OS_NS_sys_socket.h"

using namespace Terabit;

namespace Relay
{

// ***************************************************
// BaseChannel
// ***************************************************
BaseChannel::BaseChannel (int id)
: TcpChannel (id, 0),
  protocol_(0)
{
}

BaseChannel::~BaseChannel (void)
{
}

int BaseChannel::activate_protocol (Protocol     *protocol,
    const char   *data,
    size_t        datalen)
{
  protocol_ = static_cast<BaseProtocol*>(protocol);

  return TcpChannel::activate_protocol(protocol, data, datalen);
}

void BaseChannel::handle_user_operation(const TRB_Asynch_User_Result& result)
{
  ACE_ASSERT(result.act());

  Operation* op = const_cast<Operation*>(reinterpret_cast<Operation const *>(result.act()));
  if (protocol_)
  {
    int rc = protocol_->on_user_operation(this, op);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. on_user_operation() is FAILED(ch=%d)"), __FUNCTION__, this->get_id()));
      this->close();
    }
  }
  else
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Protocol is NULL(ch=%d)"), 
      __FUNCTION__, this->get_id()));
  }
}

}
