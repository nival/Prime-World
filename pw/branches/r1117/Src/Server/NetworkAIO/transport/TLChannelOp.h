#pragma once
#include <naio/Operation.h>
#include "transport/TLTypes.h"

class ACE_Message_Block;

namespace Terabit
{
  class MessageBlockFactory;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class DataHandler;

  namespace op
  {
    enum Type
    {
      OPEN_CHANNEL = naio::Operation::OP_USER + 1,
      CLOSE_CHANNEL = naio::Operation::OP_USER + 2,
      SEND_DATA = naio::Operation::OP_USER + 3,
      CONNECTION_OUTPUT = naio::Operation::OP_USER + 4,
      PING_CHANNEL = naio::Operation::OP_USER + 5,
      ADD_RECIPIENT = naio::Operation::OP_USER + 6,
      REMOVE_RECIPIENT = naio::Operation::OP_USER + 7,
    };

    //////////////////////////////////////////////////////////////////////////
    //  ChannelOp
    //
    class ChannelOp : public naio::Operation
    {
    public:
      ChannelOp(unsigned int optypeid, naio::ConnectionContextStrongPtr const & spconnctx, 
        TL::IChannelInternalSP const & spchnl, unsigned int seqNum = 0);
      ~ChannelOp();

    public:
      virtual naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
      virtual unsigned int getFinalOutputDataSize(TL::DataHandler* dh) = 0;
      TL::IChannelInternalSP const & channel() const;

      naio::Ptr<ChannelOp> next() const;
      naio::Ptr<ChannelOp> next(naio::Ptr<ChannelOp> const & op);

      unsigned long seqNum() const;
      void seqNum(unsigned long l);

    private:
      TL::IChannelInternalSP spchnl_;
      unsigned int seqNum_;
    };

    inline
    TL::IChannelInternalSP const & ChannelOp::channel() const
    {
      return spchnl_;
    }

    inline
    naio::Ptr<ChannelOp> ChannelOp::next() const
    {
      return static_cast<ChannelOp*>(naio::Operation::next().get());
    }

    inline
    naio::Ptr<ChannelOp> ChannelOp::next(naio::Ptr<ChannelOp> const & op)
    {
      return static_cast<ChannelOp*>(naio::Operation::next(op).get());
    }

    inline
    void ChannelOp::seqNum(unsigned long l)
    {
      seqNum_ = l;
    }

    inline
    unsigned long ChannelOp::seqNum() const
    {
      return seqNum_;
    }
  }
}
