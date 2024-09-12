#include "stdafx.h"
#include "PerfCounterProvider.h"
#include <Monitoring/MonitoringSvc/MonitoringNaming.h>
#include "PerfCounter.h"

NI_DEFINE_REFCOUNT(Monitoring::PerfCounterProvider);

namespace Monitoring
{
  SERIALIZE_FACTORY(PerfCounterSample);

  PerfCounterProvider::PerfCounterProvider(StrongMT<rpc::GateKeeper> const & _gk, Transport::TServiceId const & _svcid)
    :svcid_(_svcid),
    pcids_(0)
  {
    monitorIfaceReq_ = new rpc::IfaceRequester<Monitoring::RIMonitor>;
    int rc = monitorIfaceReq_->init(_gk, Monitoring::ServiceId, Monitoring::ServiceRpcIface, &GetSystemLog(), 0, this, 30);
    if (rc < 0)
    {

    }
  }

  PerfCounterProvider::~PerfCounterProvider()
  {
  }

  //IPerfCounterProvider
  nstl::vector<nstl::string> PerfCounterProvider::GetPerfCountersList()
  {
    nstl::vector<nstl::string> vec;
    for(PerfCountersMapT::iterator it = perfCounters_.begin();
      it != perfCounters_.end(); ++it)
    {
      vec.push_back(it->first);
    }

    return vec;
  }

  PerfCounterSample PerfCounterProvider::GetPerfCounterSample(char const * name)
  {
    PerfCounterSample pcs;
    pcs.name = name;
    pcs.time = time(0);
    PerfCountersMapT::iterator it = perfCounters_.find(name);
    if (it != perfCounters_.end())
    {
      StrongMT<PerfCounter> const & pc = it->second;
      pcs.rc = 0;
      pcs.val = pc->val();
      pcs.type = pc->type();
    }

    return pcs;
  }

  int PerfCounterProvider::RegisterPerfCounter(nstl::string const & name, NDebug::IDebugVar* dv, bool _toCumulate, int _samplingPeriod)
  {
    PerfCountersMapT::iterator it = perfCounters_.find(name);
    if (it != perfCounters_.end())
      return -1;

    StrongMT<PerfCounter> pc = new PerfCounter(++pcids_, name, dv, _toCumulate, _samplingPeriod);
    perfCounters_.insert(nstl::make_pair(name, pc));

    if (monitorIfaceReq_->isopen())
    {
      monitorIfaceReq_->iface()->RegisterPerfCounter(svcid_, pc->name(), pc->type(), pc->samplingPeriod(), pc->toCumulate(), this, &PerfCounterProvider::onReturn_RegisterPerfCounter, pc->id(), 10);
    }
    return 0;
  }

  int PerfCounterProvider::UnregisterPerfCounter(nstl::string const & name)
  {
    PerfCountersMapT::iterator it = perfCounters_.find(name);
    if (it == perfCounters_.end())
      return -1;

    perfCounters_.erase(it);
    return 0;
  }

  void PerfCounterProvider::UnregisterAllCounters()
  {
    perfCounters_.clear();
  }

  void PerfCounterProvider::step()
  {
    if (monitorIfaceReq_)
      monitorIfaceReq_->step();
  }

  //  rpc::IfaceRequesterCallback<Monitoring::RIMonitor>
  void PerfCounterProvider::onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<Monitoring::RIMonitor> > const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == _st)
    {
      for(PerfCountersMapT::iterator it = perfCounters_.begin();
        it != perfCounters_.end(); ++it)
      {
        StrongMT<PerfCounter> const & pc = it->second;
        _ifacereq->iface()->RegisterPerfCounter(svcid_, pc->name(), pc->type(), pc->samplingPeriod(), pc->toCumulate(), this, &PerfCounterProvider::onReturn_RegisterPerfCounter, pc->id(), 10);
      }
    }
  }

  void PerfCounterProvider::onReturn_RegisterPerfCounter(int result, int context, rpc::CallStatus status)
  {
    
  }
}
