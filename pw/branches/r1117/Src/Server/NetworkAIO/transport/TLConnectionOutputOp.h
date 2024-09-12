#pragma once
#include "transport/TLChannelOp.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  Output operation
    //
    class ConnectionOutput : public naio::Operation
    {
    public:
      ConnectionOutput(TL::ConnectionSP const & spconn, TL::MessageBlockFactorySP const & mbf, ChannelOpPtr const & op);
      ~ConnectionOutput();

    public:
      naio::StatusT execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
      naio::StatusT complete();

      ChannelOpPtr const & op() const;

    private:
      void CloseOps();

    private:
      TL::ConnectionSP spconn_;
      TL::MessageBlockFactorySP mbf_;
      ChannelOpPtr op_;
    };

    inline
    ChannelOpPtr const & ConnectionOutput::op() const
    {
      return op_;
    }
  }
}
