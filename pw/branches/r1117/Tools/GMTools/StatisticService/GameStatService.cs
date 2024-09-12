using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Threading;
using BusinessLogic.DBManagement;
using BusinessLogic.Game;
using KontagentLib;
using log4net;
using StatisticService.RPC;
using ThreadState=System.Threading.ThreadState;

namespace StatisticService
{
  public class GameStatService : BaseStatService
  {
    private static ILog _log = LogManager.GetLogger(typeof (GameStatService));

    private readonly GameStatContext context;
    private readonly KontagentContext kcontext;
    private UnmanagedRPC unmanagedRpc;

    private StatisticWriter clientWriter;
    private StatisticDebugWriter debugWriter;
    private StatisticClusterWriter clusterWriter;
    private IKontagentManager kontagentManager;
    private ISessionWriter sessionWriter;
    private ISessionEventWriter sessionEventWriter;

    private Thread workingThread;
    private Thread selfmonitoringThread;
    private volatile bool stopFlag;

    public GameStatService(GameStatContext context, KontagentContext kcontext)
      : base(context)
    {
      this.context = context;
      this.kcontext = kcontext;
    }


    public override bool Init()
    {
      _log.Info("Game statistic initialization...");

      if (!base.Init())
        return false;

      if (kcontext != null)
      {
        ITaskDumper tdumper = new TaskFileDumper(kcontext.TaskDumperFilename);
        kontagentManager = new KontagentManager(kcontext, tdumper);
      }

      sessionWriter = new SessionWriter();
      sessionEventWriter = new SessionEventWriter(context.ConnectionLogs, SessionEventWriter.Tables.Logs);

      unmanagedRpc = new UnmanagedRPC();

      this.clusterWriter = new StatisticClusterWriter(unmanagedRpc, sessionWriter, sessionEventWriter, kontagentManager);
      this.debugWriter = new StatisticDebugWriter(unmanagedRpc, sessionEventWriter, sessionWriter, context.StatisticDebugWriter);
      this.clientWriter = new StatisticWriter(unmanagedRpc, sessionEventWriter, context.StatisticWriter);

      CurrentStatus = Status.Stopped;
      return true;
    }



    public List<string> GetPermittedMethodsList()
    {
      var result = new List<string>();

      if (context.StatisticWriter.LogSessionEvent.Count > 0)
        result.Add(typeof(StatisticWriter).GetMethod("LogSessionEvent").GetParameters()[0].ParameterType.Name);

      // Получаем все bool поля из StatisticWriterContext и находим соответствующие методы в самом StatisticWriter
      foreach (var fieldInfo in typeof(GameStatContext.StatisticWriterContext)
        .GetFields().Where(f => f.FieldType == typeof(bool)))
      {
        if ((bool)fieldInfo.GetValue(context.StatisticWriter))
          result.Add(typeof(StatisticWriter).GetMethod(fieldInfo.Name).GetParameters()[0].ParameterType.Name);
      }

      // Получаем все bool поля из StatisticDebugWriterContext и находим соответствующие методы в самом StatisticDebugWriter
      foreach (var fieldInfo in typeof(GameStatContext.StatisticDebugWriterContext)
        .GetFields().Where(f => f.FieldType == typeof(bool)))
      {
        if ((bool)fieldInfo.GetValue(context.StatisticDebugWriter))
          result.Add(typeof(StatisticDebugWriter).GetMethod(fieldInfo.Name).GetParameters()[0].ParameterType.Name);
      }

      return result;
    }



    protected bool TryCompleteGameStatisticsInitialization()
    {
      if (CurrentStatus != Status.Starting)
        return false;

      _log.Info("Completing game statistics initialization");

      unmanagedRpc.Start(context.ListenUrl, GetPermittedMethodsList(), context.StatisticWriter.LogSessionEvent);

      CurrentStatus = Status.Running;
      return true;
    }

    public bool RunAsync()
    {
      if (CurrentStatus != Status.Stopped)
        return false;
      CurrentStatus = Status.Starting;

      try
      {
        _log.Debug("Run game statistic module");
        // standalone == true    запускаемся как standalone-сервер, без коннекта к кластеру.
        // standalone == false   запускаемся как кластерный сервис.

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
      var watch = new Stopwatch();

      try
      {
        while (!stopFlag)
        {
          watch.Start();
          try
          {
            TryCompleteGameStatisticsInitialization();
            unmanagedRpc.Poll();
          }
          catch (Exception ex)
          {
            _log.FatalFormat("Weird thing happened!\n {0}", ex);
            stopFlag = true; // shut down statistic module
            CurrentStatus = Status.Invalid;
          }
          watch.Stop();
          int remain_time = context.PollFrequency - (int)watch.ElapsedMilliseconds;
          if (remain_time > 0)
            Thread.Sleep(remain_time);
          watch.Reset();
        }
      }
      catch (Exception ex)
      {
        stopFlag = true;
        _log.Fatal("Game statistic service has crashed", ex);
        CurrentStatus = Status.Invalid;
      }

      _log.InfoFormat("Game statistic is stopped");
    }

    private void SelfMonitoring()
    {
      bool makeitstop = false;

      while (!stopFlag)
      {
        // Проверка на то, что остальные компоненты живы
        if (kontagentManager != null && !kontagentManager.IsRunning)
          makeitstop = true;

        if (!sessionWriter.IsRunning)
          makeitstop = true;

        if (!sessionEventWriter.IsRunning)
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
      if (CurrentStatus != Status.Running && CurrentStatus != Status.Starting && CurrentStatus != Status.Invalid)
      {
        _log.Warn("Cannot stop game statistic, because service in status " + CurrentStatus);
        return;
      }
      CurrentStatus = Status.Stopping;

      stopFlag = true;

      if (kontagentManager != null)
        kontagentManager.Stop();

      sessionWriter.Dispose();
      sessionEventWriter.Dispose();

      // Ожидание завершения основного треда
      if (workingThread != null)
      {
        var threadState = workingThread.ThreadState;
        if ((threadState != ThreadState.Running) && (threadState != ThreadState.WaitSleepJoin))
          _log.WarnFormat("Cannot stop game statistic, thread is in {0} state", threadState);
        else
          workingThread.Join();
      }

      unmanagedRpc.Shutdown();

      CurrentStatus = Status.Stopped;
    }
  }
}
