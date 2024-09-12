#pragma once

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/THttpClient.h>

#include "gen-cpp/Monitoring.h"
#include "Network/Address.h"

namespace Monitoring
{
  struct MonThriftClientCfg
  {
    Network::Address addr;
    time_t period;

    MonThriftClientCfg()
      :addr("localhost:8707"),
      period(10)
    {
    }
  };

  class MonThriftClient : public threading::Thread, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( MonThriftClient, BaseObjectMT );

  public:
    MonThriftClient();
    ~MonThriftClient();

  public:
    int open(MonThriftClientCfg const & cfg);
    int close();

  private:
    //  Thread  iface
    virtual unsigned Work();

    //  
    int step();

  private:
    boost::shared_ptr<apache::thrift::transport::THttpClient> transport;
    boost::shared_ptr<Thrift::MonitoringClient> mclient;

    std::vector<Thrift::PerfCounterInfo> declaredPerfCounters;
    std::vector<Thrift::PerfCounterInfo> registeredPerfCounters;
    time_t lastSamplesRequestTime;
    time_t period;
  };
}
