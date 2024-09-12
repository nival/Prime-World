#pragma once
#include <Network/TransportTypes.h>

class ACE_INET_Addr;

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class IAddressResolver
  {
  public:
    virtual bool ResolveAddress(Transport::TServiceId const & serviceid, ACE_INET_Addr & netaddr) = 0;
  };
}
