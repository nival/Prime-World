#pragma once

#include "PerfCounterProviderIface.h"
#include <Monitoring/MonitoringSvc/RMonitoringIface.auto.h>
#include <RPC/IfaceRequester.h>

namespace Monitoring
{
  class PerfCounter;

  class PerfCounterProvider : public IPerfCounterProvider, 
                              public rpc::IfaceRequesterCallback<Monitoring::RIMonitor>, 
                              public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3( PerfCounterProvider, IPerfCounterProvider, rpc::IfaceRequesterCallback<Monitoring::RIMonitor>, BaseObjectMT );

    typedef nstl::map<nstl::string, StrongMT<PerfCounter> > PerfCountersMapT;

  public:
    PerfCounterProvider(StrongMT<rpc::GateKeeper> const & _gk, Transport::TServiceId const & _svcid);
    ~PerfCounterProvider();

    //IPerfCounterProvider
    virtual nstl::vector<nstl::string> GetPerfCountersList();
    virtual PerfCounterSample GetPerfCounterSample(char const * name);

    //  local interface
    int RegisterPerfCounter(nstl::string const & name, NDebug::IDebugVar* dv, bool _toCumulate, int _samplingPeriod);
    int UnregisterPerfCounter(nstl::string const & name);
    void UnregisterAllCounters();

    void step();

  protected:
    //  rpc::IfaceRequesterCallback<Monitoring::RIMonitor>
    void onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<Monitoring::RIMonitor> > const & _ifacereq);

    void onReturn_RegisterPerfCounter(int result, int context, rpc::CallStatus status);

  private:
    PerfCountersMapT  perfCounters_;
    StrongMT<rpc::IfaceRequester<Monitoring::RIMonitor> > monitorIfaceReq_;
    Transport::TServiceId svcid_;
    int pcids_;
  };
}
