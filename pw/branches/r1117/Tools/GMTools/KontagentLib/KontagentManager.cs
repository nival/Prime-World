using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using log4net;

namespace KontagentLib
{
  public interface IKontagentManager
  {
    void Run();
    void Stop();
    bool IsRunning { get; }

    void LauncherStart(long auid, string hostid, string version);
    void LauncherDStart(long auid, string hostid, string package, string version);
    void LauncherDEnd(long auid, string hostid, string package, string version, int status);
    void LauncherEvents(long auid, string muid, long events);
    void FirstLogin(long auid, string muid);
    void FactionSelected(long auid, int faction);
    void CastleLogin(long auid, int faction);
    void SessionStart(long auid, int faction, int sessiontype, int heroid);
    void ResourceChange(long auid, string source, bool gain,
                        int goldchange, int silverchange, int perlchange, int redperlchange, int resource1change, int resource2change, int resource3change, int shardchange, Dictionary<string, int> currencyChange);
    void QuestChange(long auid, int status, int quid, int tm);
  }

  public class KontagentManager : IKontagentManager, IDisposable
  {
    private static ILog _log = LogManager.GetLogger(typeof (KontagentManager));

    private int selfMonitoringPeriod = 60000;
    private KontagentContext context;

    /// <summary>
    /// Индикатор того, что сервис запущен
    /// </summary>
    public bool IsRunning { get; private set; }

    private Queue<IKontagentTask> taskQueue = new Queue<IKontagentTask>();
    private readonly object qlocker = new object();
    private readonly ITaskDumper tdumper;
    private readonly IKontagentTaskCreator tcreator;

    public KontagentManager(KontagentContext context, ITaskDumper td)
      : this(context, td, new KontagentTaskCreator())
    {
    }

    public KontagentManager(KontagentContext kc, ITaskDumper td, IKontagentTaskCreator tc)
    {
      if (kc == null) throw new ArgumentNullException("kc");
      if (td == null) throw new ArgumentNullException("td");
      KontagentTask.ServiceUrl = kc.MarketingServiceUrl;
      KontagentTask.RequestTimeout = kc.RequestTimeout;
      context = kc;
      tdumper = td;
      tcreator = tc;
#if DEBUG
      selfMonitoringPeriod = 10000;
#endif
    }

    private void EnqueueTask(IKontagentTask task)
    {
      lock (qlocker)
      {
        taskQueue.Enqueue(task);
      }
    }

    private Thread processingThread;
    private Thread selfmonitoringThread;
    private volatile bool stopflag;

    public void Run()
    {
      _log.Info("Run kontagent manager");
      processingThread = new Thread(Process);
      processingThread.IsBackground = true;
      processingThread.Start();
      selfmonitoringThread = new Thread(SelfMonitoring);
      selfmonitoringThread.IsBackground = true;
      selfmonitoringThread.Start();
      stopflag = false;
      IsRunning = true;
    }

    public void Stop()
    {
      if (stopflag || !IsRunning)
        return;
      stopflag = true;
      processingThread.Join();
      selfmonitoringThread.Join();
      _log.Info("Kontagent manager stopped");
      IsRunning = false;
    }

    private int sentRate = 30; // ожидаемое количество сообщений в секунду
    private List<IKontagentTask> executing = new List<IKontagentTask>();
    private readonly object exlocker = new object();
    private volatile int failcount;

    private void Process()
    {
      try
      {
        int executingcount = 0;
        while (!stopflag)
        {
          int sentcount = executingcount;
          failcount = 0;
          for (int i = 0; i < sentRate; i++)
          {
            IKontagentTask t;

            if (taskQueue.Count == 0)
              break;
            lock (qlocker)
              t = taskQueue.Dequeue();
            if (t == null) continue;

            t.Finished += TaskFinishedCallback;
            lock (exlocker)
              executing.Add(t);
            if (t.SendRequest())
            {
              sentcount++;
            }
            else
            {
              t.Finished -= TaskFinishedCallback;
              lock (exlocker)
                executing.Remove(t);
              _log.ErrorFormat("Task {0} has failed to send request", t);
            }
          }
          if (sentcount != 0)
            _log.DebugFormat("{0} tasks sent to execution", sentcount);

          Thread.Sleep(1000); // процесс отправки происходит с интервалом в 1 секунду
          if (sentcount == 0)
          {
            _log.Debug("Nothing happened");
            continue;
          }

          executingcount = executing.Count;
          var failpercent = (float)(failcount + executingcount) / sentcount;
          _log.DebugFormat("Fails percent: {0:p0} (sent={1}, failed={2}, executing={3})", failpercent, sentcount, failcount, executingcount);
          // Если события начинают сильно проваливаться - sent rate уменьшается
          if (failpercent > context.MaxFailPercent)
          {
            if (sentRate == 1 || failpercent >= 1.0)
            {
              sentRate = 1;
              var sw = Stopwatch.StartNew();
              while (!stopflag && sw.ElapsedMilliseconds < context.TimeoutAfterError)
                Thread.Sleep(100);
              continue;
            }
            sentRate -= context.SentRateChange;
            if (sentRate < context.SentRateMin) sentRate = 1;
            _log.Debug("Decrease sent rate to " + sentRate);
          }
          // sent rate увеличивается только при незначительном проценте фейлов
          // и если количество отосланных событий близко к максимальному
          else if (failpercent < 0.01f && sentcount >= sentRate - context.SentRateChange) 
          {
            sentRate += context.SentRateChange;
            if (sentRate < context.SentRateMin) sentRate = context.SentRateMin;
            _log.Debug("Increase sent rate to " + sentRate);
          }
        }
      }
      catch(Exception ex)
      {
        _log.Fatal("Kontagent manager has crashed", ex);
        stopflag = true;
        IsRunning = false;
      }
    }

    void TaskFinishedCallback(IKontagentTask t, bool success)
    {
      t.Finished -= TaskFinishedCallback;
      lock (exlocker)
        executing.Remove(t);
      if (!success)
      {
        lock (qlocker)
          taskQueue.Enqueue(t);
        failcount++;
      }
    }

    private void SelfMonitoring()
    {
      var sw = Stopwatch.StartNew();
      try
      {
        while (!stopflag)
        {
          if (taskQueue.Count > context.QueueLength)
          {
            _log.WarnFormat("Too many tasks in kontagent manager! Queue length = " + taskQueue.Count);
            var oldtasks = new List<IKontagentTask>();

            lock (qlocker)
              for (int i = 0; i < context.QueueLength*context.QueueDumpingPart; i++)
                oldtasks.Add(taskQueue.Dequeue());

            tdumper.Dump(oldtasks);
          }
          else if (taskQueue.Count < context.QueueLength * context.QueueRestoringPoint && tdumper.HasDumpedTasks)
          {
            var oldtasks = tdumper.Restore((int) (context.QueueLength * context.QueueDumpingPart));
            foreach (var t in oldtasks)
              EnqueueTask(t);
          }

          if (sw.ElapsedMilliseconds >= selfMonitoringPeriod)
          {
            _log.DebugFormat("Kontagent tasks in queue = {0}, executing tasks = {1}, sent rate = {2}", taskQueue.Count, executing.Count, sentRate);
            sw.Reset();
            sw.Start();
          }
          Thread.Sleep(100);
        }
      }
      catch (Exception ex)
      {
        _log.Fatal("Self monioring crashed", ex);
        stopflag = true;
      }

      if (taskQueue.Count > 0)
      {
        var alltasks = new List<IKontagentTask>();
        try
        {
          lock (qlocker)
            while (taskQueue.Count > 0)
              alltasks.Add(taskQueue.Dequeue());
          tdumper.Dump(alltasks);
        }
        catch (Exception ex)
        {
          _log.Fatal("TaskDumper has crashed", ex);
        }
      }
      IsRunning = false;
    }

    public void LauncherStart(long auid, string hostid, string version)
    {
      EnqueueTask(tcreator.CreateLauncherStart(auid, hostid, version));
    }

    public void LauncherDStart(long auid, string hostid, string package, string version)
    {
      EnqueueTask(tcreator.CreateLauncherDStart(auid, hostid, package, version));
    }

    public void LauncherDEnd(long auid, string hostid, string package, string version, int status)
    {
      EnqueueTask(tcreator.CreateLauncherDEnd(auid, hostid, package, version, status));
    }

    public void LauncherEvents(long auid, string muid, long events)
    {
      EnqueueTask(tcreator.CreateLauncherEvents(auid, muid, events));
    }

    public void FirstLogin(long auid, string muid)
    {
      EnqueueTask(tcreator.CreateFirstLogin(auid, muid));
    }

    public void FactionSelected(long auid, int faction)
    {
      EnqueueTask(tcreator.CreateFactionSelected(auid, faction));
    }

    public void CastleLogin(long auid, int faction)
    {
      EnqueueTask(tcreator.CreateCastleLogin(auid, faction));
    }

    public void SessionStart(long auid, int faction, int sessiontype, int heroid)
    {
      EnqueueTask(tcreator.CreateSessionStart(auid, faction, sessiontype, heroid));
    }

    public void ResourceChange(long auid, string source, bool gain, int goldchange, int silverchange, int perlchange, int redperlchange, int resource1change, int resource2change, int resource3change, int shardchange, Dictionary<string, int> currencyChange)
    {
      EnqueueTask(tcreator.CreateResourceChange(auid, source, gain, goldchange, silverchange, perlchange, redperlchange, resource1change, resource2change, resource3change, shardchange, currencyChange));
    }

    public void QuestChange(long auid, int status, int quid, int tm)
    {
      EnqueueTask(tcreator.CreateQuestChange(auid, status, quid, tm));
    }

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~KontagentManager()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          Stop();
        }
        disposed = true;
      }
    }
  }
}
