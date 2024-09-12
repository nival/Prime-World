#pragma once
#include "transport/TLChannelOp.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  CloseChannel
    //
    class CloseChannel : public ChannelOp
    {
    public:
      CloseChannel(naio::ConnectionContextStrongPtr const & spctx, TL::IChannelInternalSP const & spchnl);
      ~CloseChannel();

    public:
      naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      unsigned int getFinalOutputDataSize(TL::DataHandler* dh);
    };
  }
}
