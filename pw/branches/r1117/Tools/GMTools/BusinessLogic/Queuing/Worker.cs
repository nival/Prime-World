using System;
using System.Diagnostics;
using System.Threading;
using log4net;

namespace BusinessLogic.Queuing
{
  public class Worker
  {
    private static ILog _log = LogManager.GetLogger(typeof(Worker));

    private Thread workingThread;
    public bool Idle { get; private set; }

    public Worker()
    {
      this.Idle = true;
    }

    public bool Execute(ITask task)
    {
      if (task == null) throw new ArgumentNullException("task");
      if (!Idle)
      {
        _log.WarnFormat("Attempt to run busy worker");
        return false;
      }
      Idle = false;

      workingThread = new Thread(Work);
      workingThread.Start(task);
      return true;
    }

    public delegate void TaskCallback(ITask task, bool success, long elapsed);
    public event TaskCallback Finished;

    private void Work(object obj)
    {
      var task = (ITask)obj;
      var sw = Stopwatch.StartNew();
      bool success;
      try
      {
        success = task.Execute();
      }
      catch (Exception ex)
      {
        _log.Error("Execution error in " + task, ex);
        success = false;
        task.ErrorCount++;
      }
      sw.Stop();
      task.LastExecutionTime = DateTime.UtcNow;

      // Результат возвращается в executor
      Finished(task, success, sw.ElapsedMilliseconds);
      Idle = true;
    }
  }
}