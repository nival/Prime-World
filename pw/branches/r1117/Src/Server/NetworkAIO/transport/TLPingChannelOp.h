#pragma once
#include "transport/TLChannelOp.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  PingChannel
    //
    class PingChannel : public ChannelOp
    {
    public:
      PingChannel(naio::ConnectionContextStrongPtr const & spctx, TL::IChannelInternalSP const & spchnl, 
                  unsigned long pingSeqNum);
      ~PingChannel();

    public:
      naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      unsigned int getFinalOutputDataSize(TL::DataHandler* dh);

    private:
      unsigned long pingSeqNum_;
    };
  }
}
