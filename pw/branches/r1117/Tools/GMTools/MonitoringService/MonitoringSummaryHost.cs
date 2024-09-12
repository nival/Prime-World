using System;
using System.Net;
using System.Threading;
using log4net;
using MonitoringService.Thrift;
using Thrift;

namespace MonitoringService
{
  public interface IMonitoringSummaryHost
  {
    bool RunAsync();
    void Stop();
  }

  public class MonitoringSummaryHost : IMonitoringSummaryHost
  {
    private static ILog _log = LogManager.GetLogger(typeof(MonitoringSummaryHost));

    private readonly string thriftUrlPrefix;
    private readonly MonitoringSummary.Iface monitoringSummary;

    private bool monitoringStopworker;
    private THttpHandler httpHandler;
    private HttpListener httpListener;
    private Thread workingThread;

    public MonitoringSummaryHost(string urlPrefix, MonitoringSummary.Iface monitoringSummaryIface)
    {
      if (urlPrefix == null) throw new ArgumentNullException("urlPrefix");
      if (monitoringSummaryIface == null) throw new ArgumentNullException("monitoringSummaryIface");
      
      this.thriftUrlPrefix = urlPrefix;
      this.monitoringSummary = monitoringSummaryIface;
    }

    public bool RunAsync()
    {
      if (workingThread != null)
      {
        _log.Warn("Cannot run monitoring summary module, working thread already exists");
        return false;
      }

      try
      {
        TProcessor processor = new MonitoringSummary.Processor(monitoringSummary);
        httpHandler = new THttpHandler(processor);

        _log.DebugFormat("Created http listener on address {0}", thriftUrlPrefix);
        httpListener = new HttpListener();
        httpListener.Prefixes.Add(thriftUrlPrefix);

        _log.Info("Start http listener");
        httpListener.Start();

        // run monitoring in the new thread
        workingThread = new Thread(RunMonitoringSummary);
        workingThread.Start();
      }
      catch (Exception ex)
      {
        _log.Error("Cannot run monitoring summary host", ex);
        return false;
      }

      return true;
    }

    private void RunMonitoringSummary()
    {
      //_log.Info("Run monitoring summary provider module");
      monitoringStopworker = false;

      while (!monitoringStopworker)
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

      _log.Info("Stop http listener");
      httpListener.Stop();
    }

    public void Stop()
    {
      if (workingThread.ThreadState != ThreadState.Running)
      {
        _log.WarnFormat("Cannot stop social statistic, thread is in {0} state", workingThread.ThreadState);
        return;
      }

      monitoringStopworker = true;
      workingThread.Join(100);
      // Если не выключился по хорошему - выключим по плохому
      if (httpListener.IsListening)
      {
        httpListener.Stop();
        workingThread.Join();
      }
    }
  }
}