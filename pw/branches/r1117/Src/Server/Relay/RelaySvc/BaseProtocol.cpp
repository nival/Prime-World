#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/AsynchChannel.h>
#include "TransportMessagesHeaders.h"
#include <ace/OS_NS_sys_socket.h>
#include "BaseProtocol.h"

#if defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

const int SOCKET_ERROR = -1;
#endif

using namespace Terabit;
using namespace Transport;

namespace Relay
{

#pragma warning( push )
#pragma warning( disable : 4355)
BaseProtocol::BaseProtocol(Terabit::ProtocolFactory& factory, bool packaddr, char const * tagname)
: Terabit::RefCntProtocol(factory),
  factory_(factory),
  transport_handler_(this, packaddr, tagname),
  act_(0)
#pragma warning( pop )
{
}

BaseProtocol::~BaseProtocol()
{
}

int BaseProtocol::applyConnectionSettings(Terabit::AsynchChannel *channel, 
                                          ConnectionSettings const & cs)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  int rc = 0;

  mbf_->tag(channel->get_id());

  if (cs.rcvbufSize_)
    channel->set_read_size(cs.rcvbufSize_);

  //  set socket option - read buffer size
  if (cs.soRcvbufSize_ != -1)
  {
    unsigned int recvbufsize = 0;
    int lrecvbufsize = sizeof(recvbufsize);
    int serr = ACE_OS::getsockopt(channel->handle(), SOL_SOCKET, SO_RCVBUF, 
      reinterpret_cast<char*>(&recvbufsize), &lrecvbufsize);
    if (SOCKET_ERROR == serr)
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't get SO_RCVBUF(ch=%d err=%d)"), 
        __FUNCTION__, channel->get_id(), errno));

      recvbufsize = cs.soRcvbufSize_;
    }
    else
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s. Default SO_RCVBUF %d(ch=%d)"), 
        __FUNCTION__, recvbufsize, channel->get_id()));
    }

    if (cs.soRcvbufSize_ > int(recvbufsize))
    {
      recvbufsize = cs.soRcvbufSize_;
      lrecvbufsize = sizeof(recvbufsize);
      serr = ACE_OS::setsockopt(channel->handle(),
        SOL_SOCKET, SO_RCVBUF, 
        reinterpret_cast<char*>(&recvbufsize), lrecvbufsize);
      if (SOCKET_ERROR == serr)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set SO_RCVBUF(ch=%d err=%d)"), 
          __FUNCTION__, channel->get_id(), errno));
        rc = -1;
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. SO_RCVBUF set to %d(ch=%d)"), 
          __FUNCTION__, recvbufsize, channel->get_id()));
      }
    }
  }

  //  Nagle algorithm
  if (cs.disableNagleAlgorithm_)
  {
    int serr = ACE_OS::setsockopt(channel->handle(),  IPPROTO_TCP, TCP_NODELAY, 
      reinterpret_cast<const char*>(&cs.disableNagleAlgorithm_), sizeof(cs.disableNagleAlgorithm_));

    if (SOCKET_ERROR == serr)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't disable Nagle algorithm(ch=%d err=%d)"), 
        __FUNCTION__, channel->get_id(), errno));
      rc = -1;
    }
    else
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s. Nagle algorithm disabled successfully(ch=%d)"), 
        __FUNCTION__, channel->get_id()));
    }
  }

  if (cs.enableWriteNotifications_)
    rc = channel->enable_write_notifications();

  return rc;
}

int BaseProtocol::SendOpenChannelResponse(Terabit::AsynchChannel *channel, bool result, Transport::Address const & caddr, 
                                          TPipeId const & pipeid, Transport::ChannelAddr const & raddr, Transport::EChannelType::Enum chnltype)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d,r=%d)"), __FUNCTION__, channel->get_id(), result));

  OpenChannelResponse msg;
  msg.success = result;
  msg.clientAddress = caddr;
  msg.localPipeId = pipeid;
  msg.remoteAddr = raddr;
  msg.channelType = chnltype;

  return transport_handler_.HandleOutput(&msg, ChannelAddr(EKnownPipeId::NetLogic, msg.clientAddress.client), channel);
}

int BaseProtocol::on_user_operation(Terabit::AsynchChannel *channel, Operation* op)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));
  return 0;
}

int  BaseProtocol::on_channel_up(AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));\
  return -1;  //  have to be overriden
}

void BaseProtocol::on_channel_done(AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));
}

void BaseProtocol::on_reset ()
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s"), __FUNCTION__));
  act_ = 0;
}

void BaseProtocol::set_message_block_factory(TL::MessageBlockFactorySP const & mbf)
{
  mbf_ = mbf;
}

Terabit::MessageBlockFactory* BaseProtocol::get_message_block_factory() const
{
  return mbf_.get();
}

}
