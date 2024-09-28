#include "stdafx.h"
#include "MonitoringSvc/CumulativePerfCounter.h"

namespace Monitoring
{
  int CumulativePerfCounter::AddCounter(StrongMT<PerfCounterCtx> const & _ctx)
  {
    LOG_M(MONLOG).Trace("%s(path=%s svcid=%s name=%s)", __FUNCTION__, 
      _ctx->path().c_str(), _ctx->svcid().c_str(), _ctx->name().c_str());

    if (_ctx->type() != type())
    {
      LOG_W(MONLOG).Trace("%s. Type doesn't match(path=%s type=%d cumulativeType=%d)", __FUNCTION__, 
        _ctx->path().c_str(), (int)_ctx->type(), (int)type());
      return -1;
    }

    return counters_.registerPerfCounter(_ctx);
  }

  int CumulativePerfCounter::RemoveCounter(StrongMT<PerfCounterCtx> const & _ctx)
  {
    LOG_M(MONLOG).Trace("%s(path=%s svcid=%s name=%s)", __FUNCTION__, 
      _ctx->path().c_str(), _ctx->svcid().c_str(), _ctx->name().c_str());

    if (_ctx->type() != type())
    {
      LOG_W(MONLOG).Trace("%s. Type doesn't match(path=%s type=%d cumulativeType=%d)", __FUNCTION__, 
        _ctx->path().c_str(), (int)_ctx->type(), (int)type());
      return -1;
    }

    return counters_.unregisterPerfCounter(_ctx->path());
  }

  nstl::wstring const & CumulativePerfCounter::val() const
  {
    time_t t(0);
    if (NDebug::DebugVarType::Byte == type() ||
        NDebug::DebugVarType::Int16 == type() ||
        NDebug::DebugVarType::Int32 == type())
    {
      int result = 0;
      PerfCountersSet::PerfCounterListT const & lst = counters_.getPerfCounterList();
      for(PerfCountersSet::PerfCounterListT::const_iterator cit = lst.begin();
        cit != lst.end(); ++cit)
      {
        StrongMT<PerfCounterCtx> const & pc = *cit;
        if (!pc->val().empty())
        {
          int v = ::_wtoi(pc->val().c_str());
          if (errno != ERANGE)
            result += v;
        }

        if (pc->time() > t)
          t = pc->time();
      }

      if (!t)
        t = ::time(0);

      time_ = t;
      val_.assign(NStr::StrFmtW(L"%d", result));
    }

    return val_;
  }
}
