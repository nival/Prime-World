#include "stdafx.h"
#include "Coordinator/CoordinatorSvcContext.h"

namespace Coordinator
{
  SvcContext::SvcContext(Transport::TServiceId const & _svcpath, Transport::TServiceId const & _svcid, TServiceRole const & _svcrole,
                         ServerIdT const & _srvid, int _pid, string const & _machineName)
    :status_(ServiceStatus::S_INIT),
    svcpath_(_svcpath),
    svcid_(_svcid),
    srvid_(_srvid),
    pid_(_pid),
    machineName_(_machineName),
    svcrole_(_svcrole)
  {
    Transport::MakeFullServiceId(_svcpath, _svcid, fullsvcid_);
    Transport::GetServiceClass(_svcid, svcls_);
  }

  SvcContext::~SvcContext()
  {
  }
}
