#pragma once
#include "transport/TLTypes.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelListenerInternal : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ChannelListenerInternal, IBaseInterfaceMT )

  public:
    virtual void onOpenChannel(TL::IChannelInternalSP const & spchnl) = 0;
  };
}
