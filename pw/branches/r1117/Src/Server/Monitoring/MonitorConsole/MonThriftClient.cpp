#include "stdafx.h"
#include <sys/time.h>
#include <sys/socket.h>

#include "MonThriftClient.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace Monitoring;

namespace Monitoring
{
  MonThriftClient::MonThriftClient()
    :lastSamplesRequestTime(0),
    period(-1)
  {

  }

  MonThriftClient::~MonThriftClient()
  {

  }

  int MonThriftClient::open(MonThriftClientCfg const & cfg)
  {
    int rc = 0;
    if (cfg.period <= 0)
    {
      LOG_E(0).Trace("%s: incorrect 'period' parameter: %d", __FUNCTION__, cfg.period);
      return -1;
    }

    period = cfg.period;

    nsocket::Initialize();
    boost::shared_ptr<TTransport> socket(new TSocket(cfg.addr.GetIp(), cfg.addr.GetPort()));
    boost::shared_ptr<TTransport> bufferedTransport(new TBufferedTransport(socket)); 
    transport.reset(new THttpClient(bufferedTransport, "localhost", "/")); 
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    mclient.reset(new Thrift::MonitoringClient(protocol));

    try
    {
      transport->open();
    }
    catch (TException &tx)
    {
      LOG_E(0).Trace("Can't open connection: %s", tx.what());
      rc = -1;
    }

    if (rc >= 0)
    {
      Thread::Resume();
    }

    return rc;
  }

  int MonThriftClient::close()
  {
    transport->close();

    Thread::Stop(true, 10*1000);

    return 0;
  }

  unsigned MonThriftClient::Work()
  {
    while(Thread::isRunning)
    {
      int rc = step();
      if (rc < 0)
      {
        //  log

        isRunning = false;
        break;
      }
      sleep(50);
    }

    return 0;
  }

  int MonThriftClient::step()
  {
    try
    {
      if (!declaredPerfCounters.size())
      {
        mclient->GetPerfCounters(declaredPerfCounters);

        LOG_M(0) << "Supported performance counters:";
        for(std::vector<Thrift::PerfCounterInfo>::iterator it = declaredPerfCounters.begin();
          it != declaredPerfCounters.end(); ++it)
        {
          LOG_M(0) << it->name.c_str() << ":" << it->period;
        }
        LOG_M(0) << "===============================";
      }
      else
      {
        if (!registeredPerfCounters.size())
        {
          mclient->RegisterPerfCounters(declaredPerfCounters);
          registeredPerfCounters = declaredPerfCounters;
          LOG_M(0) << "Register supported performance counters for gathering";
        }
        else
        {
          time_t curr = time(0);
          if (curr >= lastSamplesRequestTime + period)
          {
            LOG_M(0) << "Samples requested ...";
            std::vector<Thrift::PerfCounterSample> samples;
            mclient->GetPerfCounterSamples(samples);
            lastSamplesRequestTime = time(0);
            LOG_M(0).Trace("Samples received: %d samples", samples.size());

            for(std::vector<Thrift::PerfCounterSample>::iterator it = samples.begin();
              it != samples.end(); ++it)
            {
              time_t t = it->timestamp;
              LOG_M(0) << it->name.c_str() << " : " << it->value.c_str() << " : " << ctime(&t);
            }
          }
        }
      }

      return 0;
    }
    catch (TException &tx)
    {
      LOG_E(0).Trace("Can't open connection: %s", tx.what());
      return -1;
    }
  }
}
