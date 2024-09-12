using DAL;
using DataLogging;
using log4net;

namespace StatisticService
{
  public class BaseStatService
  {
    private static ILog _log = LogManager.GetLogger(typeof (BaseStatService));
    private readonly StatisticContext context;

    public enum Status
    {
      NotInitialized,
      Starting,
      Running,
      Invalid,
      Stopping,
      Stopped
    }
    public Status CurrentStatus { get; protected set; }

    public BaseStatService(StatisticContext context)
    {
      this.context = context;
      CurrentStatus = Status.NotInitialized;
    }

    /// <summary>
    ///  оличество воркеров с которым запускаютс€ TaskExecutor'ы
    /// </summary>
    public static int ExecutorWorkers
    {
      get { return executorWorkers; }
      set { executorWorkers = value; }
    }
    private static int executorWorkers = 10;


    public virtual bool Init()
    {
      if (CurrentStatus != Status.NotInitialized)
      {
        _log.Warn("Service is already initialized, status = " + CurrentStatus);
        return false;
      }

      // database connections
      var dlcontext = new DataLoggingContext(context.ConnectionLogs);
      var databaseWriter = new DatabaseWriter(dlcontext);

      int dblogsVersion = databaseWriter.GetVersion();
      if (dblogsVersion != context.DBVersionLogs)
        _log.ErrorFormat("Wrong version of database pw_logs: expected = {0}, found = {1}", context.DBVersionLogs, dblogsVersion);

      var dalcontext = new DALContext(context.ConnectionManagement);
      if (!NHibernateHelper.Init(dalcontext))
        return false;

      int dbmanagementVersion = NHibernateHelper.DBVersion;
      if (dbmanagementVersion != context.DBVersionManagement)
        _log.ErrorFormat("Wrong version of database pw_management: expected = {0}, found = {1}", context.DBVersionManagement, dbmanagementVersion);

      if (dblogsVersion == context.DBVersionLogs && dbmanagementVersion == context.DBVersionManagement)
      {
        _log.Info("Version of database pw_management = " + dbmanagementVersion);
        _log.Info("Version of database pw_logs = " + dblogsVersion);
      }
      else
        return false;

      return true;
    }
  }
}