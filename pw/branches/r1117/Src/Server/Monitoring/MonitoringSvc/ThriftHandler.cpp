#include "MonitoringSvc/ThriftHandler.h"

namespace Monitoring
{
  ThriftHandler::ThriftHandler(StrongMT<MonitorCore> const & mc)
    :moncore(mc)
  {
  }

  ThriftHandler::~ThriftHandler()
  {
  }

  void ThriftHandler::GetPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return)
  {
    moncore->GetPerfCounters(_return);
  }

  int32_t ThriftHandler::RegisterPerfCounters(const std::vector<Thrift::PerfCounterInfo> & counters)
  {
    return moncore->RegisterPerfCounters(counters);
  }

  int32_t ThriftHandler::UnregisterPerfCounters(const std::vector<std::string> & counters)
  {
    return moncore->UnregisterPerfCounters(counters);
  }

  int32_t ThriftHandler::UnregisterAllPerfCounters()
  {
    return moncore->UnregisterAllPerfCounters();
  }

  void ThriftHandler::GetRegisteredPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return)
  {
    moncore->GetRegisteredPerfCounters(_return);
  }

  void ThriftHandler::GetPerfCounterSamples(std::vector<Thrift::PerfCounterSample> & _return)
  {
    moncore->GetPerfCounterSamples(_return);
  }
}
