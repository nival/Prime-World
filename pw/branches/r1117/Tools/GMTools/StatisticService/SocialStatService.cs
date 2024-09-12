using System;
using System.Net;
using System.Threading;
using BusinessLogic.Social;
using KontagentLib;
using log4net;
using StatisticService.ThriftImpls;
using Thrift;

namespace StatisticService
{
  public class SocialStatService : BaseStatService
  {
    private static ILog _log = LogManager.GetLogger(typeof (SocialStatService));

    private readonly SocialStatContext context;
    private readonly KontagentContext kcontext;
    private HttpListener httpListener;
    private THttpHandler httpHandler;
    private IKontagentManager kontagentManager;
    private ISocialSessionManager sessionManager;

    private Thread workingThread;
    private Thread selfmonitoringThread;
    private volatile bool stopFlag;

    public SocialStatService(SocialStatContext context, KontagentContext kcontext)
      : base(context)
    {
      this.context = context;
      this.kcontext = kcontext;
    }

    public override bool Init()
    {
      _log.Info("Social statistic initialization...");

      if (!base.Init())
        return false;

      if (kcontext != null)
      {
        ITaskDumper tdumper = new TaskFileDumper(kcontext.TaskDumperFilename);
        kontagentManager = new KontagentManager(kcontext, tdumper);
      }

      sessionManager = new SocialSessionManager(context.ConnectionManagement, context.ConnectionLogs);
      
      var service = new StatisticServiceImplementation(sessionManager, kontagentManager);
      TProcessor processor = new StatisticCore.Thrift.StatisticService.Processor(service);
      httpHandler = new THttpHandler(processor);

      httpListener = new HttpListener();
      httpListener.Prefixes.Add(context.ThriftUrlPrefix);

      CurrentStatus = Status.Stopped;
      return true;
    }

    public bool RunAsync()
    {
      if (CurrentStatus != Status.Stopped)
        return false;
      CurrentStatus = Status.Running;

      try
      {
        _log.Debug("Run social statistic module");
        _log.DebugFormat("start http listener on address {0}", context.ThriftUrlPrefix);
        httpListener.Start();
        stopFlag = false;

        workingThread = new Thread(Run);
        workingThread.Start();

        if (kontagentManager != null)
          kontagentManager.Run();

        selfmonitoringThread = new Thread(SelfMonitoring);
        selfmonitoringThread.Start();
      }
      catch (Exception ex)
      {
        _log.Fatal("RunAsync() failed", ex);
        Stop();
        return false;
      }
      return true;
    }

    private void Run()
    {
      while (!stopFlag)
      {
        try
        {
          var httpcontext = httpListener.GetContext();
          // Show request info
          _log.DebugFormat("Thrift http {0} request: RemoteEndPoint = {1}", httpcontext.Request.HttpMethod, httpcontext.Request.RemoteEndPoint);

          httpHandler.ProcessRequest(httpcontext);
        }
        catch (HttpListenerException ex)
        {
          if (ex.ErrorCode == 1229) // ERROR_CONNECTION_INVALID
          {
            _log.WarnFormat("HttpListener error {0}: {1}", ex.ErrorCode, ex.Message);
            continue;
          }
          if (ex.ErrorCode == 995) // ERROR_OPERATION_ABORTED
            _log.Info("HttpListener aborted");
          else
            _log.ErrorFormat("HttpListener error {0}: {1}", ex.ErrorCode, ex);
          stopFlag = true;
        }
        catch(Exception ex)
        {
          stopFlag = true;
          _log.Fatal("Social statistic service has crashed", ex);
          CurrentStatus = Status.Invalid;
        }
      }

      httpListener.Stop();

      CurrentStatus = Status.Stopped;
      _log.InfoFormat("Stopped social statistic listener on address {0}", context.ThriftUrlPrefix);
    }

    private void SelfMonitoring()
    {
      bool makeitstop = false;

      while (!stopFlag)
      {
        // Проверка на то, что остальные компоненты живы
        if (kontagentManager != null && !kontagentManager.IsRunning)
          makeitstop = true;

        if (!sessionManager.IsRunning)
          makeitstop = true;

        if (makeitstop)
        {
          _log.Debug("Something went wrong");
          Stop();
          return;
        }

        Thread.Sleep(100);
      }
    }

    public void Stop()
    {
      if (CurrentStatus != Status.Running && CurrentStatus != Status.Invalid)
      {
        _log.Warn("Cannot stop stop statistic, because service in status " + CurrentStatus);
        return;
      }

      CurrentStatus = Status.Stopping;

      var threadState = workingThread.ThreadState;
      if (threadState != ThreadState.Running && threadState != ThreadState.WaitSleepJoin)
      {
        _log.WarnFormat("Cannot stop social statistic, thread is in {0} state", threadState);
        return;
      }

      stopFlag = true;

      if (kontagentManager != null)
        kontagentManager.Stop();

      sessionManager.Dispose();

      // Ожидание завершения основного треда
      workingThread.Join(100);
      // Если не выключился по хорошему - выключим по плохому
      if (httpListener.IsListening)
      {
        httpListener.Stop();
        workingThread.Join();
      }

      CurrentStatus = Status.Stopped;
    }
  }
}