using System;
using System.Collections.Generic;
using log4net;
using Thrift.Protocol;
using Thrift.Transport;

namespace MonitoringLib
{
  public interface IMonitoringProvider
  {
    IEnumerable<PerfCounterInfo> GetCounters();
    bool RegisterPerfCounters(List<PerfCounterInfo> counters);
    IEnumerable<PerfCounterSample> GetPerfCounterSamples();
    bool UnregisterAllPerfCounters();
  }

  public class MonitoringProvider : IMonitoringProvider
  {
    private static ILog _log = LogManager.GetLogger(typeof(MonitoringProvider));

    private readonly Uri monitoringAddress;

    public MonitoringProvider(Uri address)
    {
      if (address == null) throw new ArgumentNullException("address");
      monitoringAddress = address;
    }

    private delegate T CallMonitoring<T>(Monitoring.Client client);

    private T ExecuteThriftMethod<T>(CallMonitoring<T> callmonitoring)
    {
      TTransport transport = null;
      try
      {
        transport = new THttpClient(monitoringAddress);
        TProtocol proto = new TBinaryProtocol(transport);
        var client = new Monitoring.Client(proto);
        return callmonitoring(client);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return default(T);
      }
      finally
      {
        if (transport != null && transport.IsOpen)
          transport.Close();
      }
    }

    /// <summary>
    /// Специальная перегрузка для преобразования ерроркода в bool
    /// </summary>
    private bool ExecuteThriftMethod(CallMonitoring<int> callmonitoring)
    {
      TTransport transport = null;
      try
      {
        transport = new THttpClient(monitoringAddress);
        TProtocol proto = new TBinaryProtocol(transport);
        var client = new Monitoring.Client(proto);
        return callmonitoring(client) >= 0;
      }
      catch (Exception ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return false;
      }
      finally
      {
        if (transport != null && transport.IsOpen)
          transport.Close();
      }
    }

    public IEnumerable<PerfCounterInfo> GetCounters()
    {
      return ExecuteThriftMethod(c => c.GetPerfCounters());
    }

    public bool RegisterPerfCounters(List<PerfCounterInfo> counters)
    {
      return ExecuteThriftMethod(c => c.RegisterPerfCounters(counters));
    }

    public IEnumerable<PerfCounterSample> GetPerfCounterSamples()
    {
      return ExecuteThriftMethod(c => c.GetPerfCounterSamples());
    }

    public bool UnregisterAllPerfCounters()
    {
      return ExecuteThriftMethod(c => c.UnregisterAllPerfCounters());
    }

  }
}