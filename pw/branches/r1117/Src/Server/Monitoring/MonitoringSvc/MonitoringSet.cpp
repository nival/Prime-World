#include "stdafx.h"
#include "MonitoringSvc/MonitoringSet.h"

namespace Monitoring
{
  PerfCountersSet::PerfCountersSet()
  {
  }

  PerfCountersSet::~PerfCountersSet()
  {
  }

  int PerfCountersSet::registerPerfCounter(StrongMT<PerfCounterCtx> const & pcd)
  {
    LOG_D(MONLOG).Trace("%s(path=%s svcid=%s)", __FUNCTION__, pcd->path().c_str(), pcd->svcid().c_str());

    PerfCounterListT::iterator itdecl = findByPath_(pcd->path());
    if (itdecl != perfCounterList.end())
    {
      LOG_W(MONLOG).Trace("%s. Counter is ALREADY registered(path=%s)", __FUNCTION__, pcd->path().c_str());
      return 1;
    }

    perfCounterList.push_back(pcd);
    LOG_D(MONLOG).Trace("%s. Counter registered successfully(path=%s)", __FUNCTION__, pcd->path().c_str());
    return 0;
  }

  int PerfCountersSet::unregisterPerfCounter(nstl::string const & path)
  {
    LOG_D(MONLOG).Trace("%s(path=%s)", __FUNCTION__, path.c_str());

    PerfCounterListT::iterator itdecl = findByPath_(path);
    if (itdecl == perfCounterList.end())
    {
      LOG_W(MONLOG).Trace("%s. Counter is NOT FOUND(path=%s)", __FUNCTION__, path.c_str());
      return -1;
    }

    perfCounterList.erase(itdecl);
    LOG_D(MONLOG).Trace("%s. Counter unregistered successfully(path=%s)", __FUNCTION__, path.c_str());
    return 0;
  }

  PerfCountersSet::PerfCounterListT::iterator 
  PerfCountersSet::findByPath_(nstl::string const & path)
  {
    for(PerfCounterListT::iterator it = perfCounterList.begin(); it != perfCounterList.end(); ++it)
    {
      if ((*it)->path() == path)
        return it;
    }

    return perfCounterList.end();
  }

  PerfCountersSet::PerfCounterListT::iterator 
  PerfCountersSet::findByName_(Transport::TServiceId const & svcid, nstl::string const & name)
  {
    for(PerfCounterListT::iterator it = perfCounterList.begin(); it != perfCounterList.end(); ++it)
    {
      if ((*it)->svcid() == svcid && 
          (*it)->name() == name)
        return it;
    }

    return perfCounterList.end();
  }

  void PerfCountersSet::clear()
  {
    perfCounterList.clear();
  }
}
