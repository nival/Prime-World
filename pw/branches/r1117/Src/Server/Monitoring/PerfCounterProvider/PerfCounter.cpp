#include "stdafx.h"
#include "PerfCounterProvider/PerfCounter.h"

namespace Monitoring
{
  nstl::wstring const & PerfCounter::val() const
  {
    wchar_t buffer[128];
    debugVar_->FormatValue( buffer, sizeof(buffer) / sizeof(wchar_t) );
    val_.assign(buffer);
    return val_;
  }
}
