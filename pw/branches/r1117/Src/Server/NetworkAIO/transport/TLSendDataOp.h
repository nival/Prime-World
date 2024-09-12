#pragma once
#include "transport/TLChannelOp.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    //////////////////////////////////////////////////////////////////////////
    //  SendData
    //
    class SendData : public ChannelOp
    {
    public:
      SendData(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl,
        ACE_Message_Block* mb, unsigned long seqNum);
      ~SendData();

    public:
      naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      unsigned int getFinalOutputDataSize(TL::DataHandler* dh);
      ACE_Message_Block* mb() const;

    private:
      ACE_Message_Block* mb_;
    };

    inline
    ACE_Message_Block* SendData::mb() const
    {
      return mb_;
    }
  }
}
