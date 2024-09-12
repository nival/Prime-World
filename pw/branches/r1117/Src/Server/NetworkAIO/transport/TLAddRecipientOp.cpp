#include "transport/stdafx.h"
#include "transport/TLAddRecipientOp.h"
#include <Network/TransportMessages.h>
#include "transport/TLChannel.h"
#include "transport/TLDataHandler.h"
#include <ace/Message_Block.h>

namespace TransportLayer
{
  namespace op
  {
    AddRecipient::AddRecipient(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl,
      Transport::TClientId const & _recipient)
      :ChannelOp(op::ADD_RECIPIENT, spconnctx, spchnl),
      recipient_(_recipient)
    {
    }

    AddRecipient::~AddRecipient()
    {
    }

    naio::StatusT 
    AddRecipient::execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_FUNCTION;

      naio::StatusT sts = naio::status::SUCCESS;

      Transport::AddRecipientRequest msg;
      msg.caddr = channel()->chaddr();
      msg.recipient = recipient_;

      ACE_Message_Block* mb = channel()->packMessage(&msg);
      if (mb)
      {
        sts = dh->HandleOutput(Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, msg.caddr.client),
          mb->length(), mb->base(), this->spctx_, outmbf, poutmb);
        channel()->freeMsgBlock_(mb);
      }

      return sts;
    }

    unsigned int AddRecipient::getFinalOutputDataSize(TL::DataHandler* dh)
    {
      NI_PROFILE_FUNCTION;

      Transport::AddRecipientRequest msg;
      msg.caddr = channel()->chaddr();

      Transport::ChannelAddr caddr(Transport::EKnownPipeId::NetLogic, msg.caddr.client);
      return dh->GetFinalOutputDataSize(caddr, &msg);
    }
  }
}
