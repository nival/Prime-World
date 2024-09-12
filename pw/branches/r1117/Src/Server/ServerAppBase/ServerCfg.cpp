#include "stdafx.h"
#include "ServerCfg.h"

static nstl::string g_uniserverSvcpath = "ru";
REGISTER_VAR("uniserver_svcpath", g_uniserverSvcpath, STORAGE_GLOBAL);

static nstl::string s_clusterName = "C";
REGISTER_VAR( "cluster_name", s_clusterName, STORAGE_GLOBAL );


namespace HostServer
{
  namespace Cfg
  {
    nstl::string const & GetSvcPath()
    {
      return g_uniserverSvcpath;
    }

    void SetSvcPath(Transport::TServiceId const & svcid)
    {
      g_uniserverSvcpath = svcid.c_str();
    }

    const string & ClusterName() { return s_clusterName; }
  }
}
