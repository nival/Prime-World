#include "stdafx.h"
#include "MonitoringSvc/PerfCounterCtx.h"

namespace Monitoring
{
  nstl::wstring const & PerfCounterCtx::val() const
  {
    return val_;
  }
}
