#pragma once

#include "gen-cpp/Monitoring.h"
#include "MonitoringSvc/MonitorCore.h"

namespace Monitoring
{
  class ThriftHandler : public Thrift::MonitoringIf
  {
  public:
    ThriftHandler(StrongMT<MonitorCore> const & mc);
    ~ThriftHandler();

  public:
    //  MonitoringIf
    virtual void GetPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return);
    virtual int32_t RegisterPerfCounters(const std::vector<Thrift::PerfCounterInfo> & counters);
    virtual int32_t UnregisterPerfCounters(const std::vector<std::string> & counters);
    virtual int32_t UnregisterAllPerfCounters();
    virtual void GetRegisteredPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return);
    virtual void GetPerfCounterSamples(std::vector<Thrift::PerfCounterSample> & _return);

  private:
    StrongMT<MonitorCore> moncore;
  };
}
