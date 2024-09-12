using System;
using log4net;
using MonitoringService;
using Thrift;
using Thrift.Protocol;
using Thrift.Transport;

namespace MonitoringSummaryLib
{
  public interface IMonitoringSummaryService
  {
    int GetGameClusterCCU();
    int GetSocialClusterCCU();
    int GetNumberOfMatchmakingUsers();
    MonitoringInfo GetFullMonitoringInfo();
  }

  public class MonitoringSummaryService : IMonitoringSummaryService
  {
    private static ILog _log = LogManager.GetLogger(typeof (MonitoringSummaryService));

    private MonitoringSummary.Client client;

    public MonitoringSummaryService(Uri address)
    {
      if (address == null) throw new ArgumentNullException("address");

      // init thrift client
      TTransport transport = new THttpClient(address);
      TProtocol proto = new TBinaryProtocol(transport);
      this.client = new MonitoringSummary.Client(proto);
    }

    public int GetGameClusterCCU()
    {
      try
      {
        return client.GetGameClusterCCU();
      }
      catch (TTransportException ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return -1;
      }
      catch (TApplicationException ex)
      {
        _log.Error("Failed to get Game Cluster CCU", ex);
        return -1;
      }
    }

    public int GetSocialClusterCCU()
    {
      try
      {
        return client.GetSocialClusterCCU();
      }
      catch (TTransportException ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return -1;
      }
      catch (TApplicationException ex)
      {
        _log.Error("Failed to get Social Cluster CCU", ex);
        return -1;
      }
    }

    public int GetNumberOfMatchmakingUsers()
    {
      try
      {
        return client.GetNumberOfMatchmakingUsers();
      }
      catch (TTransportException ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return -1;
      }
      catch (TApplicationException ex)
      {
        _log.Error("Failed to get Number of matchmaking users", ex);
        return -1;
      }
    }

    private static object _locker = new object();

    public MonitoringInfo GetFullMonitoringInfo()
    {
      try
      {
        // подпорка пока не придумаю как победить зависание HttpWebRequest.GetRequestStream() в трифтовом THttpClient
        lock (_locker)
        {
          return client.GetFullMonitoringInfo();
        }
      }
      catch (TTransportException ex)
      {
        _log.Error("Failed to execute method on remote host.", ex);
        return null;
      }
      catch (TApplicationException ex)
      {
        _log.Error("Failed to get Number of matchmaking users", ex);
        return null;
      }
    }
  }
}