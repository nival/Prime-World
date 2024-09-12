using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Threading;
using log4net;

namespace BusinessLogic.Queuing
{
  public interface ITaskExecutor
  {
    bool IsRunning { get; }
    void Run();
    void Stop();
    void EnqueueTask(ITask task);
    int QueueLength { get; }
  }

  public class TaskExecutor : ITaskExecutor
  {
    private static ILog _log = LogManager.GetLogger(typeof (TaskExecutor));

    private const int DEFAULT_WORKERS_COUNT = 10;
    private const int DEFAULT_MAX_TASK_ATTEMPTS = 5;
    private const int DELAY_BEFORE_RETRY = 200;

    private Queue<ITask> tasks;
    private List<Worker> workers;
    private readonly object qlocker = new object();
//    private readonly object wlocker = new object();

    /// <summary>
    /// ћаксимальное количество попыток выполнить определенный таск
    /// </summary>
    public int MaxTaskAttempts { get; set; }
    /// <summary>
    /// ѕериод вывода диагностической информации
    /// </summary>
    public int SelfMonitoringInterval { get; set; }

    /// <summary>
    /// »м€ объекта, нужно чтобы отличать их друг от друга в логах
    /// </summary>
    public string Name { get; set; }

    public TaskExecutor()
      : this(DEFAULT_WORKERS_COUNT)
    {
    }

    public TaskExecutor(int workersCount)
    {
      if (workersCount <= 0) throw new ArgumentException("Invalid value " + workersCount, "workersCount");
      tasks = new Queue<ITask>();
      workers = new List<Worker>(workersCount);
      for (int i = 0; i < workersCount; i++)
      {
        var w = new Worker();
        w.Finished += TaskFinished;
        workers.Add(w);
      }

      MaxTaskAttempts = DEFAULT_MAX_TASK_ATTEMPTS;
      SelfMonitoringInterval = 60000;
#if DEBUG
      SelfMonitoringInterval = 10000;
#endif
    }

    private Thread processingThread;
    private volatile bool stopflag;

    public bool IsRunning { get; private set; }

    public void Run()
    {
      if (processingThread != null)
      {
        _log.Error("Task executor already running");
        return;
      }
      _log.Info("Run task executor");
      processingThread = new Thread(Processing);
      processingThread.IsBackground = true;
      processingThread.Start();
      stopflag = false;
      IsRunning = true;
    }

    private void Processing()
    {
      var sw = Stopwatch.StartNew();
      try
      {
        while (!stopflag)
        {
          if (sw.ElapsedMilliseconds > SelfMonitoringInterval)
          {
            _log.InfoFormat("Task executor state ({0}): queue length = {1}, workers idle = {2}/{3}",
                            Name, QueueLength, workers.Count(w => w.Idle), workers.Count);
            sw.Reset();
            sw.Start();
          }

          var worker = workers.Find(w => w.Idle);
          
          if (worker != null && tasks.Count > 0)
          {
            ITask task = null;
            do
            {
              lock (qlocker)
              {
                // ≈сли мы перебираем таски в поисках подход€щего, 
                // то не забываем положить потом ненужный таск обратно в очередь
                if (task != null)
                  tasks.Enqueue(task);

                // ¬ыбор следующего из очереди
                task = tasks.Dequeue();
              }
              Thread.Sleep(1);
              // ѕроверка таска на адекватность:
              // если выбрали таск у которого LastExecutionTime было меньше чем N секунд назад (DELAY_BEFORE_RETRY), то пойдем за новым
            } while (task != null && task.LastExecutionTime.HasValue &&
                     (DateTime.UtcNow - task.LastExecutionTime.Value).TotalMilliseconds < DELAY_BEFORE_RETRY);

            if (task != null)
            {
              if (worker.Execute(task))
                continue;
              EnqueueTask(task);
            }
          }
          Thread.Sleep(10);
        }
      }
      catch (Exception ex)
      {
        _log.Fatal("Task executor (" + Name + ") has crashed", ex);
        stopflag = true;
        IsRunning = false;
      }
      if (tasks.Count > 0)
        _log.WarnFormat("{0} tasks will be lost", tasks.Count);
    }

    public void EnqueueTask(ITask task)
    {
      lock (qlocker)
        tasks.Enqueue(task);
    }

    public int QueueLength
    {
      get { return tasks.Count; }
    }

    public void Stop()
    {
      stopflag = true;
      processingThread.Join();
      _log.InfoFormat("Task executor ({0}) stopped", Name);
      IsRunning = false;
    }

    /// <summary>
    /// Callback из воркера
    /// </summary>
    private void TaskFinished(ITask task, bool success, long elapsed)
    {
      if (success)
      {
        _log.DebugFormat("{0} executed in {1} ms", task, elapsed);
      }
      else
      {
        if (task.ErrorCount < MaxTaskAttempts)
        {
          _log.DebugFormat("{0} failed in {1} ms, error count = {2}, last error message = {3}", task, elapsed, task.ErrorCount, task.LastErrorMessage);
          EnqueueTask(task);
        }
        else
        {
          _log.Error("Failed task: " + task.Dump());
        }
      }
    }
  }
}