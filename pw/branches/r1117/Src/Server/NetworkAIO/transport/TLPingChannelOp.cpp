#include "transport/stdafx.h"
#include "transport/TLPingChannelOp.h"
#include <Network/TransportMessages.h>
#include "transport/TLChannel.h"
#include <ace/OS_NS_sys_time.h>
#include "transport/TLDataHandler.h"
#include <ace/Message_Block.h>

namespace TransportLayer
{
  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  PingChannel
    //
    PingChannel::PingChannel(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl,
                             unsigned long pingSeqNum)
      :ChannelOp(op::PING_CHANNEL, spconnctx, spchnl),
      pingSeqNum_(pingSeqNum)
    {
    }

    PingChannel::~PingChannel()
    {
    }

    naio::StatusT 
    PingChannel::execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_FUNCTION;

      naio::StatusT sts = naio::status::SUCCESS;

      Transport::PingMessage msg;
      msg.requestingChannel = channel()->chaddr();
      msg.seqNum = pingSeqNum_;
      msg.reply = false;
      ACE_OS::gettimeofday().msec( static_cast< long int >( msg.sendTime ) );

      ACE_Message_Block* mb = channel()->packMessage(&msg);
      if (mb)
      {
        sts = dh->HandleOutput(Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, channel()->chaddr().client),
          mb->length(), mb->base(), this->spctx_, outmbf, poutmb);
        channel()->freeMsgBlock_(mb);
      }

      return sts;
    }

    unsigned int PingChannel::getFinalOutputDataSize(TL::DataHandler* dh)
    {
      NI_PROFILE_FUNCTION;

      Transport::PingMessage msg;
      msg.requestingChannel = channel()->chaddr();

      Transport::ChannelAddr caddr(Transport::EKnownPipeId::NetLogic, msg.requestingChannel.client);
      return dh->GetFinalOutputDataSize(caddr, &msg);
    }
  }
}
