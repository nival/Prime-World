#pragma once
#include "MonitoringSvc/PerfCounterCtx.h"

namespace Monitoring
{
  class PerfCountersSet
  {
  public:
    typedef nstl::list<StrongMT<PerfCounterCtx>> PerfCounterListT;

  public:
    PerfCountersSet();
    ~PerfCountersSet();

    int registerPerfCounter(StrongMT<PerfCounterCtx> const & pcc);
    int unregisterPerfCounter(nstl::string const & path);

    StrongMT<PerfCounterCtx> findByName(Transport::TServiceId const & svcid, nstl::string const & name);
    StrongMT<PerfCounterCtx> findByPath(nstl::string const & path);

    PerfCounterListT const & getPerfCounterList() const;

    void clear();

  private:
    PerfCounterListT::iterator findByName_(Transport::TServiceId const & svcid, nstl::string const & name);
    PerfCounterListT::iterator findByPath_(nstl::string const & path);

  private:
    PerfCounterListT perfCounterList;
  };

  inline
  PerfCountersSet::PerfCounterListT const & PerfCountersSet::getPerfCounterList() const
  {
    return perfCounterList;
  }

  inline
  StrongMT<PerfCounterCtx> PerfCountersSet::findByName(Transport::TServiceId const & svcid, 
                                                       nstl::string const & name)
  {
    PerfCounterListT::iterator it = findByName_(svcid, name);
    if (it == perfCounterList.end())
      return 0;
    
    return *it;
  }

  inline
  StrongMT<PerfCounterCtx> PerfCountersSet::findByPath(nstl::string const & path)
  {
    PerfCounterListT::iterator it = findByPath_(path);
    if (it == perfCounterList.end())
      return 0;

    return *it;
  }
}
