#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>

namespace Monitoring
{
  REMOTE class IMonitor : public IBaseInterfaceMT
  {
    RPC_ID();

  public:
    REMOTE virtual int RegisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname, int _type, int _defaultUpdatePeriod, bool _toCumulate) = 0;
    REMOTE virtual int UnregisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname) = 0;
  };
}
