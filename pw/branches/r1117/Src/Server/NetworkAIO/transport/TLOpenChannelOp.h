#pragma once
#include "transport/TLChannelOp.h"
#include <Network/TransportAddress.h>
#include <Network/TransportLoginData.h>

namespace Transport
{
  struct OpenChannelResponse;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    //////////////////////////////////////////////////////////////////////////
    //  OpenChannel
    //
    class OpenChannel : public ChannelOp
    {
    public:
      OpenChannel(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl, void* tag);
      ~OpenChannel();

    public:
      naio::StatusT execute(TL::DataHandler* dh, 
        Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      unsigned int getFinalOutputDataSize(TL::DataHandler* dh);

      naio::StatusT complete(Transport::OpenChannelResponse const * msg);

    public:
      //  getters
      Transport::TLoginData const & GetLoginData() const;
      Transport::Address const & GetAddress() const;
      void* tag() const;

    private:
      void* tag_;
    };

    inline
    void* OpenChannel::tag() const
    {
      return tag_;
    }
  }
}
