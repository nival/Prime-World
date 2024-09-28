#pragma once
#include "transport/TLChannelOp.h"
#include <Network/TransportTypes.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    class RemoveRecipient : public ChannelOp
    {
    public:
      RemoveRecipient(naio::ConnectionContextStrongPtr const & _spctx, TL::IChannelInternalSP const & _spchnl, 
        Transport::TClientId const & _recipient);
      ~RemoveRecipient();

    public:
      naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      unsigned int getFinalOutputDataSize(TL::DataHandler* dh);

    private:
      Transport::TClientId recipient_;
    };
  }
}
