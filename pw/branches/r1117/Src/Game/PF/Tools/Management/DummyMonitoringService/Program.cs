using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using DummyMonitoringService.Thrift;
using log4net;
using log4net.Config;
using MonitoringService;
using Thrift;

namespace DummyMonitoringService
{
  class Program
  {
    private static ILog _log = LogManager.GetLogger(typeof (Program));

    private static THttpHandler httpHandler;
    private static HttpListener httpListener;

    private const string ThriftUrlPrefix = "http://+:35501/";

    static void Main()
    {
      BasicConfigurator.Configure();
      _log.Info("Starting dummy monitoring service");

      TProcessor processor = new MonitoringSummary.Processor(new DummyMonitoringStorage());
      httpHandler = new THttpHandler(processor);

      _log.DebugFormat("Created http listener on address {0}", ThriftUrlPrefix);
      httpListener = new HttpListener();
      httpListener.Prefixes.Add(ThriftUrlPrefix);

      _log.Info("Start monitoring");

      _log.Info("Start http listener");
      httpListener.Start();
      while (true)
      {
        try
        {
          var context = httpListener.GetContext();
          // Show request info
          _log.DebugFormat("Thrift http {0} request: RemoteEndPoint = {1}", context.Request.HttpMethod, context.Request.RemoteEndPoint.ToString());

          httpHandler.ProcessRequest(context);
        }
        catch (HttpListenerException ex)
        {
          if (ex.ErrorCode == 995) // ERROR_OPERATION_ABORTED
            _log.Info("HttpListener aborted");
          else
            _log.Warn("Error in HttpListener", ex);
          return;
        }
      }

    }
  }

  class DummyMonitoringStorage : MonitoringSummary.Iface
  {
    public int GetGameClusterCCU()
    {
      return 1;
    }

    public int GetSocialClusterCCU()
    {
      return 2;
    }

    public int GetNumberOfMatchmakingUsers()
    {
      return -1;
    }

    public MonitoringInfo GetFullMonitoringInfo()
    {
      return new MonitoringInfo
               {
                 Gameccu = 1,
                 Socialccu = 2,
                 Mmakingusers = -1
               };
    }
  }
}
