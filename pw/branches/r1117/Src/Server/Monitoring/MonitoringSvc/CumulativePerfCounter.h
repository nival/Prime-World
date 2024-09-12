#pragma once

#include "MonitoringSvc/MonitoringSet.h"

namespace Monitoring
{
  class CumulativePerfCounter : public PerfCounterCtx
  {
    NI_DECLARE_REFCOUNT_CLASS_1(CumulativePerfCounter, PerfCounterCtx);

    CumulativePerfCounter()
    {}

    CumulativePerfCounter(nstl::string const & _path, nstl::string const & _name, NDebug::DebugVarType::Enum _type, unsigned int _period = 10)
      :PerfCounterCtx(_path, "", _name, _type, _period)
    {}

  public:
    int AddCounter(StrongMT<PerfCounterCtx> const & _ctx);
    int RemoveCounter(StrongMT<PerfCounterCtx> const & _ctx);

    //  PerfCounterCtx
    nstl::wstring const & val() const;

  public:
    PerfCountersSet counters_;
  };
}
