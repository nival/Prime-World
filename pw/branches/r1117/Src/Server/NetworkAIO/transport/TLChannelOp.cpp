#include "transport/stdafx.h"
#include "transport/TLChannelOp.h"
#include "transport/TLChannelInt.h"

namespace TransportLayer
{
  namespace op
  {
    ChannelOp::ChannelOp(unsigned int optypeid, 
                        naio::ConnectionContextStrongPtr const & spconnctx, 
                        TL::IChannelInternalSP const & spchnl, unsigned int seqNum)
      :Operation(optypeid, spconnctx),
      spchnl_(spchnl),
      seqNum_(seqNum)
    {
    }

    ChannelOp::~ChannelOp()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      ResetPtr(spchnl_);
    }
  }
}
