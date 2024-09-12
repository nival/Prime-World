#include "stdafx.h"
#include "MonitoringSvc/ProviderCtx.h"

NI_DEFINE_REFCOUNT( Monitoring::ProviderContext );

namespace Monitoring
{
  ProviderContext::ProviderContext()
    :ifacereq_(new rpc::IfaceRequester<RIPerfCounterProvider>),
    st_(State::INIT),
    repairEndtime_(0.0),
    repairTimeout_(0)
  {
  }

  ProviderContext::~ProviderContext()
  {
  }

  int ProviderContext::open(ProviderCtxId const & _id, Transport::TServiceId const & _svcid, StrongMT<rpc::GateKeeper> const & gk, unsigned int _repairTimeout)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());

    if (isopen())
    {
      LOG_W(MONLOG).Trace("%s. Context already OPENED(svcid=%s)", __FUNCTION__, ifacereq_->svcid().c_str());
      return 1;
    }

    id_ = _id;
    svcid_ = _svcid;
    repairTimeout_ = _repairTimeout;

    Transport::TServiceId localSvcid;
    Transport::GetLocalServiceId(_svcid, localSvcid);

    nstl::string ifacename = localSvcid.c_str();
    ifacename.append(Monitoring::intfSuffix);
    int rc = ifacereq_->init(gk, localSvcid, ifacename.c_str(), &GetSystemLog(), MONLOG, this);
    if (rc >= 0)
      state(State::OPENING);

    return rc;
  }

  int ProviderContext::close()
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s)", __FUNCTION__, ifacereq_->svcid().c_str());

    if (isclose())
    {
      LOG_W(MONLOG).Trace("%s. Context already CLOSED(svcid=%s)", __FUNCTION__, ifacereq_->svcid().c_str());
      return 1;
    }

    state(State::CLOSE);
    ifacereq_->close();

    PerfCountersSet::PerfCounterListT const & counters = counters_.getPerfCounterList();
    for(PerfCountersSet::PerfCounterListT::const_iterator it = counters.begin();
      it != counters.end(); ++it)
    {
      StrongMT<PerfCounterCtx> const & pc = *it;
      pc->val(wstring());
    }
    counters_.clear();

    return 0;
  }

  void ProviderContext::step()
  {
    ifacereq_->step();

    if (State::REPAIR == state() && repairTimeout_ && NHPTimer::GetScalarTime() > repairEndtime_)
    {
      LOG_W(MONLOG).Trace("%s. Repair timeout expired(svcid=%s to=%d)", __FUNCTION__, ifacereq_->svcid().c_str(), repairTimeout_);
      close();
    }
  }

  int ProviderContext::RegisterPerfCounter(StrongMT<PerfCounterCtx> const & _pc)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s counter=%s)", __FUNCTION__, ifacereq_->svcid().c_str(), _pc->path().c_str());

    if (isclose())
    {
      LOG_W(MONLOG).Trace("%s. Context already CLOSED(svcid=%s counter=%s)", __FUNCTION__, ifacereq_->svcid().c_str(), _pc->path().c_str());
      return -1;
    }

    return counters_.registerPerfCounter(_pc);
  }

  int ProviderContext::UnregisterPerfCounter(StrongMT<PerfCounterCtx> const & _pc)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s counter=%s)", __FUNCTION__, ifacereq_->svcid().c_str(), _pc->path().c_str());

    if (isclose())
    {
      LOG_W(MONLOG).Trace("%s. Context already CLOSED(svcid=%s counter=%s)", __FUNCTION__, ifacereq_->svcid().c_str(), _pc->path().c_str());
      return -1;
    }

    return counters_.unregisterPerfCounter(_pc->path());
  }

  void ProviderContext::onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<RIPerfCounterProvider>> const & _ifacereq)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s state=%d)", __FUNCTION__, ifacereq_->svcid().c_str(), (int)_st);

    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      state(State::REPAIR);
      repairEndtime_ = NHPTimer::GetScalarTime() + repairTimeout_;

      //  refresh inprogress flag
      PerfCountersSet::PerfCounterListT const & counters = counters_.getPerfCounterList();
      for(PerfCountersSet::PerfCounterListT::const_iterator it = counters.begin();
        it != counters.end(); ++it)
      {
        StrongMT<PerfCounterCtx> const & pc = *it;
        pc->inprogress(false);
      }
    }
    else
    if (rpc::IfaceRequesterState::OPENED == _st)
    {
      state(State::OPEN);
      repairEndtime_ = 0;
    }
  }
}
