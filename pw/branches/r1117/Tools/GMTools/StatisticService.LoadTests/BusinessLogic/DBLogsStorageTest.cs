using System;
using System.Data;
using System.Threading;
using BusinessLogic.DBLogs;
using BusinessLogic.DBLogs.Mapping;
using BusinessLogic.Queuing;
using DataLogging;
using log4net;

namespace StatisticService.LoadTests.BusinessLogic
{
  public class DBLogsStorageTest
  {
    private static ILog _log = LogManager.GetLogger(typeof (DBLogsStorageTest));

    private int users;
    private DBLogsStorage storage;

    public DBLogsStorageTest()
    {
      var executor = new TaskExecutor(5);
      var writer = new TestDatabaseWriter();

      storage = new DBLogsStorage(executor, writer, TablesMapping.GetLogsTables());
    }

    public void Run()
    {
      int maxWorkerThreads, maxCompletionPortThreads;
      ThreadPool.GetMaxThreads(out maxWorkerThreads, out maxCompletionPortThreads);
      int workerThreads, completionPortThreads;
      ThreadPool.GetAvailableThreads(out workerThreads, out completionPortThreads);
      _log.Info("runningThreads=" + (maxWorkerThreads - workerThreads));

      for (int i = 0; i < 10000; i++)
      {
        storage.WriteIn("debugvar", 1, 2, DateTime.UtcNow, 4, "5", "6");
        Thread.Sleep(1);
        storage.WriteIn("damage", 1, 2f, 3, true, 5, 6, 7, 8, 9, 10);
        Thread.Sleep(0);
        storage.WriteIn("talentused", 1, 2, 3f, 4f, 5, 6);
        Thread.Sleep(1);
        storage.WriteIn("debugvar", 1, 2, DateTime.UtcNow, 4, "5", "6");
        Thread.Sleep(0);
        storage.WriteIn("damage", 1, 2f, 3, true, 5, 6, 7, 8, 9, 10);
        Thread.Sleep(1);
        storage.WriteIn("kill", 1, 2, 3f, 4f, 5, 6, 7);
      }
      Thread.Sleep(5000);

      ThreadPool.GetMaxThreads(out maxWorkerThreads, out maxCompletionPortThreads);
      ThreadPool.GetAvailableThreads(out workerThreads, out completionPortThreads);
      _log.Info("runningThreads=" + (maxWorkerThreads - workerThreads));
    }
  }

  public class TestDatabaseWriter : IDatabaseWriter
  {
    private static ILog _log = LogManager.GetLogger(typeof (TestDatabaseWriter));
    
    public bool FastWriteTable(DataTable table)
    {
      throw new NotImplementedException("Y U NEED TO FAST WRITE?!");
    }

    public bool WriteTable(DataTable table)
    {
      //_log.DebugFormat("Write table {0} rows in table {1}", table.Rows.Count, table.TableName);
      try
      {
        foreach (var row in table.Rows) 
          Thread.Sleep(0);
        
        Thread.Sleep(2);
      }
      catch (Exception ex)
      {
        _log.Fatal(ex);
        return false;
      }

      if (new Random().Next(10) == 6)
        throw new InvalidOperationException("RANDOM EXCEPTION");

      return true;
    }

    public int GetVersion()
    {
      return 0;
    }
  }
}