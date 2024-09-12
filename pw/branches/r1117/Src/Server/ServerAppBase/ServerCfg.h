#pragma once
#include <Network/TransportTypes.h>

namespace HostServer
{
  namespace Cfg
  {
    nstl::string const & GetSvcPath();
    void SetSvcPath(Transport::TServiceId const & svcid);

    const string & ClusterName();
  };
}
