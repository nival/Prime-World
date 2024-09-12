using System;
using System.Collections.Generic;
using BusinessLogic.Queuing;
using log4net;

namespace BusinessLogic.DBManagement
{
  public abstract class BaseMultipleTask<T> : BaseTask 
    where T : class
  {
    private static ILog _log = LogManager.GetLogger(typeof(BaseMultipleTask<T>).Assembly, "BaseMultipleTask<T>");

    protected IEnumerable<T> infos;
    /// <summary>
    /// Repositories to dispose after execution
    /// </summary>
    protected IEnumerable<IDisposable> repos;

    protected BaseMultipleTask(IEnumerable<T> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      this.infos = infos;
    }

    public override bool Execute()
    {
      var failedinfos = new List<T>();
      foreach (T info in infos)
      {
        try
        {
          Execute(info);
        }
        catch (Exception ex)
        {
          _log.ErrorFormat("Failed task {0}, info = {1}\n{2}", this.GetType(), info, ex);
          LastErrorMessage = ex.Message;
          failedinfos.Add(info);
        }
      }
      if (failedinfos.Count > 0)
      {
        ErrorCount++;
        infos = failedinfos;
        return false;
      }
      if (repos != null)
        foreach (var repo in repos)
          repo.Dispose();
      return true;
    }

    protected abstract void Execute(T info);
  }
}