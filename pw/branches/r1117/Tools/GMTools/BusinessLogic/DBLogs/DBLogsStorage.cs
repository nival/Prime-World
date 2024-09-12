using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Threading;
using BusinessLogic.DBLogs.Mapping;
using BusinessLogic.Queuing;
using DataLogging;
using log4net;

namespace BusinessLogic.DBLogs
{
  public interface IDBLogsStorage : IDisposable
  {
    bool IsRunning { get; }
    void WriteIn(string table, params object[] values);
  }

  /// <summary>
  /// Stores game session events into internal storage and can generate tasks for external processor
  /// </summary>
  public class DBLogsStorage : IDBLogsStorage
  {
    private static ILog _log = LogManager.GetLogger(typeof (DBLogsStorage));

    Dictionary<string, StorageTable> eventStorage = new Dictionary<string, StorageTable>();
    private readonly object storageSyncRoot = new object();

    private BackgroundWorker processing;
    private Timer selfmonitoringTimer;

    private readonly ITaskExecutor executor;
    private readonly IDatabaseWriter writer;

    #region Settings

    /// <summary>
    /// Interval (ms) between tables fetching
    /// </summary>
    public int TableFetchingInterval
    {
      get { return _tableFetchingInterval; }
      set { _tableFetchingInterval = value; }
    }
    private int _tableFetchingInterval = 300;

    /// <summary>
    /// Self monitoring interval (ms)
    /// </summary>
    public int SelfMonitoringInterval
    {
      get { return _selfMonitoringInterval; }
      set
      {
        _selfMonitoringInterval = value;
        selfmonitoringTimer.Change(_selfMonitoringInterval, _selfMonitoringInterval);
      }
    }
    private int _selfMonitoringInterval = 60000;

    #endregion

    /// <summary>
    /// Ctor
    /// </summary>
    public DBLogsStorage(ITaskExecutor executor, IDatabaseWriter writer, IEnumerable<TableFormat> tables)
    {
      if (executor == null) throw new ArgumentNullException("executor");
      if (writer == null) throw new ArgumentNullException("writer");
      this.executor = executor;
      this.writer = writer;

      var reg_tabs = new List<string>();
      foreach (TableFormat tableFormat in tables)
      {
        if (!RegisterTable(tableFormat))
          _log.Error("Failed to register table " + tableFormat.Name);
        else
          reg_tabs.Add(tableFormat.Name);
      }
      if (reg_tabs.Count > 0)
        _log.DebugFormat("Added tables: {0}", String.Join(", ", reg_tabs.ToArray()));

      processing = new BackgroundWorker();
      processing.DoWork += ProcessingStorage;
      processing.WorkerSupportsCancellation = true;
      processing.RunWorkerAsync();

      executor.Run();

      _isRunning = true;
#if DEBUG
      _selfMonitoringInterval = 10000;
#endif
      selfmonitoringTimer = new Timer(SelfMonitoring, null, SelfMonitoringInterval, SelfMonitoringInterval);
    }

    /// <summary>
    /// Registering new table in the eventStorage
    /// </summary>
    private bool RegisterTable(TableFormat tableFormat)
    {
      if (tableFormat == null) throw new ArgumentNullException("tableFormat");
      if (String.IsNullOrEmpty(tableFormat.Name))
      {
        _log.Error("Cannot register table without name");
        return false;
      }
      if (tableFormat.Fields.Length == 0)
      {
        _log.ErrorFormat("Cannot register table {0} with empty fields list", tableFormat.Name);
        return false;
      }

      var dt = new DataTable();
      dt.TableName = tableFormat.Name;
      foreach (StorageField field in tableFormat.Fields)
      {
        try
        {
          dt.Columns.Add(field.Name, Type.GetType(field.Type));
        }
        catch (Exception ex)
        {
          _log.Error("Cannot create DataTable object for table " + tableFormat.Name, ex);
          return false;
        }
      }
      var table = new StorageTable(tableFormat.Name, dt);

      lock (storageSyncRoot)
      {
        if (eventStorage.ContainsKey(tableFormat.Name))
        {
          _log.ErrorFormat("Storage table with name {0} is already defined in OperationalStorage", tableFormat.Name);
          return false;
        }

        eventStorage.Add(tableFormat.Name, table);
      }
      return true;
    }

    /// <summary>
    /// Main loop for storage data processing
    /// </summary>
    private void ProcessingStorage(object sender, DoWorkEventArgs e)
    {
      _log.Info("Run processing DBLogs storage");
      try
      {
        while (!processing.CancellationPending)
        {
          // “асков должно быть не больше чем таблиц
          if (executor.QueueLength < eventStorage.Count)
          {
            foreach (StorageTable table in eventStorage.Values)
            {
              if ((DateTime.UtcNow - table.LastFetchingTime).TotalMilliseconds > TableFetchingInterval)
              {
                var dt = table.FetchTable();
                if (dt == null) continue;

                var task = new WriteTableTask(writer, dt);
                executor.EnqueueTask(task);
              }
            }
          }
          Thread.Sleep(5); // todo: rewrite it as the timer with a syncobject
        }
        _log.Info("Processing storage has finished");
      }
      catch (Exception ex)
      {
        _log.Fatal("Unexpected exception in storage processing", ex);
      }
      _isRunning = false;
    }

    /// <summary>
    /// Shows debug information about current state of the event storage
    /// </summary>
    private void SelfMonitoring(object obj)
    {
      string tablesinfo = String.Empty;
      foreach (KeyValuePair<string, StorageTable> pair in eventStorage)
      {
        lock (pair.Value.syncRoot)
        {
          int cnt = pair.Value.Table.Rows.Count;
          if (cnt > 0)
            tablesinfo += String.Format(" {0,-25}{1}\n", pair.Key, pair.Value.Table.Rows.Count);
        }
      }
      _log.InfoFormat("Storage current state: {0} tables, {1}", eventStorage.Count,
                      tablesinfo != String.Empty ? "rows information:\n" + tablesinfo : "all tables are empty");
    }

    private bool _isRunning;
    public bool IsRunning
    {
      get { return _isRunning && executor.IsRunning; }
    }

    /// <summary>
    /// Writes data into the storage
    /// </summary>
    public void WriteIn(string table, params object[] values)
    {
      if (table == null) throw new ArgumentNullException("table");
      if (values == null) throw new ArgumentNullException("values");

      if (!eventStorage.ContainsKey(table))
      {
        _log.ErrorFormat("Table {0} was not registered", table);
        return;
      }

      lock (eventStorage[table].syncRoot)
      {
        eventStorage[table].AddRow(values);
      }
    }

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~DBLogsStorage()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          processing.CancelAsync();
          selfmonitoringTimer.Dispose();
          executor.Stop();
        }
        disposed = true;
      }
    }
  }
}