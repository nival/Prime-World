#include "transport/stdafx.h"
#include "transport/TLCloseChannelOp.h"
#include <Network/TransportMessages.h>
#include "transport/TLChannelInt.h"
#include "transport/TLDataHandler.h"
#include "transport/TLConnection.h"

namespace TransportLayer
{
  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  CloseChannel
    //
    CloseChannel::CloseChannel(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl)
      :ChannelOp(op::CLOSE_CHANNEL, spconnctx, spchnl)
    {
    }

    CloseChannel::~CloseChannel()
    {
    }

    naio::StatusT CloseChannel::execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      naio::StatusT sts = naio::status::SUCCESS;

      Transport::CloseChannelMessage msg;
      msg.clientAddress = channel()->chaddr();
      ACE_Message_Block* mb = channel()->packMessage(&msg);
      if (mb)
      {
        sts = dh->HandleOutput(Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, channel()->chaddr().client),
          mb->length(), mb->base(), this->spctx_, outmbf, poutmb);
        channel()->freeMsgBlock_(mb);

        TL::ConnectionSP spconn = channel()->getConnection();
        if (TL::IsValid(spconn))
          spconn->onChannelClosed(channel());
      }

      return sts;
    }

    unsigned int CloseChannel::getFinalOutputDataSize(TL::DataHandler* dh)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      Transport::CloseChannelMessage msg;
      msg.clientAddress = channel()->chaddr();

      Transport::ChannelAddr caddr(Transport::EKnownPipeId::NetLogic, msg.clientAddress.client);
      return dh->GetFinalOutputDataSize(caddr, &msg);
    }
  }
}
