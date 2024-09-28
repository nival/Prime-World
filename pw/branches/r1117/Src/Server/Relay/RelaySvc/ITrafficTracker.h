#pragma once
#include "System/Pointers/BaseInterface.h"
#include "Network/TransportUtils.h"

namespace Relay
{

class ITrafficTracker : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITrafficTracker, IBaseInterfaceMT );

public:
  virtual void HandlePacket(Transport::ChannelAddr const & caddr, char const * data, size_t len) = 0;
};

}
