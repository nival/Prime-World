#pragma once
#include <rpc/GateKeeper.h>
#include "PerfCounterProvider/RPerfCounterProviderIface.auto.h"
#include "MonitoringSvc/MonitoringSet.h"
#include "MonitoringSvc/ProviderCtx.h"
#include "MonitoringSvc/gen-cpp/Monitoring_types.h"

namespace Monitoring
{
  class MonitorCore : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( MonitorCore, BaseObjectMT );

    typedef nstl::map<ProviderCtxId, StrongMT<ProviderContext>> ProviderContextsT;

  public:
    MonitorCore();
    ~MonitorCore();

    int Open(StrongMT<rpc::GateKeeper> const & gk);
    int Close();

    void GetPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return);
    int RegisterPerfCounters(const std::vector<Thrift::PerfCounterInfo> & counters);
    int UnregisterPerfCounters(const std::vector<std::string> & counters);
    int UnregisterAllPerfCounters();
    void GetRegisteredPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return);
    void GetPerfCounterSamples(std::vector<Thrift::PerfCounterSample> & _return);

    int CreatePerfCounter(Transport::TServiceId const & _svcid, string const & _name, 
      NDebug::DebugVarType::Enum _type, int _samplingPeriod, unsigned int _repairTimeout, StrongMT<PerfCounterCtx> & _pc);
    int CreatePerfCounter(string const & _path, Transport::TServiceId const & _svcid, string const & _name, 
      NDebug::DebugVarType::Enum _type, int _samplingPeriod, unsigned int _repairTimeout, StrongMT<PerfCounterCtx> & _pc);

    int RegisterPerfCounter(StrongMT<PerfCounterCtx> const & pc);
    StrongMT<PerfCounterCtx> FindPerfCounter(string const & _path);

    int Step();

    string createPerfCounterPath(Transport::TServiceId const & _svcid, string const & _name);

  private:
    int CreateProviderContext(Transport::TServiceId const & svcid, StrongMT<rpc::GateKeeper> const & _gk, 
      unsigned int _repairTimeout, StrongMT<ProviderContext>& ctx);

    StrongMT<ProviderContext> findProviderCtx(Transport::TServiceId const & svcid);
    StrongMT<ProviderContext> findProviderCtx(ProviderCtxId const & ctxid);
    void OnPerfCounterSample(PerfCounterSample result, ProviderCtxId ctxid, rpc::CallStatus status);

  private:
    StrongMT<rpc::GateKeeper> gk_;
    ProviderContextsT contexts;
    PerfCountersSet activeMonitoringSet;
    PerfCountersSet availableCounters;
    unsigned int lastctxid_;
  };
}
