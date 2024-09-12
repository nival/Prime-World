using System;
using System.Collections.Generic;
using log4net;
using StatisticCore.Thrift;
using Thrift;
using Thrift.Protocol;
using Thrift.Transport;

namespace MonitoringLib
{
  public interface IStatisticProvider
  {
    void MonitoringResults(List<MonitoringResultInfo> results);
  }

  public class StatisticProvider : IStatisticProvider
  {
    private static ILog _log = LogManager.GetLogger(typeof (StatisticProvider));

    private Uri statisticAddress;

    public StatisticProvider(Uri address)
    {
      if (address == null) throw new ArgumentNullException("address");
      statisticAddress = address;
    }

    public void MonitoringResults(List<MonitoringResultInfo> results)
    {
      TTransport transport = null;
      try
      {
        transport = new THttpClient(statisticAddress);
        TProtocol proto = new TBinaryProtocol(transport);
        var client = new StatisticService.Client(proto);
        client.MonitoringResults(results);
      }
      catch (TTransportException ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
      }
      catch (TApplicationException ex)
      {
        _log.Error("Failed to write monitoring results", ex);
      }
      finally
      {
        if (transport != null && transport.IsOpen)
          transport.Close();
      }
    }
  }
}