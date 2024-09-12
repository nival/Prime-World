using System;
using System.Data;
using System.Linq;
using log4net;

namespace BusinessLogic.DBLogs
{
  /// <summary>
  /// Object that wraps datatable
  /// </summary>
  public class StorageTable
  {
    private static ILog _log = LogManager.GetLogger(typeof(StorageTable));

    internal readonly object syncRoot = new object();

    private DataTable _table;
    internal DataTable Table
    {
      get { return _table; }
    }

    public DateTime LastFetchingTime { get; private set; }

    public StorageTable(string tablename, DataTable table)
    {
      if (tablename == null) throw new ArgumentNullException("tablename");
      if (table == null) throw new ArgumentNullException("table");
      if (table.Columns.Count == 0)
        throw new ArgumentException("Attempt to create storage table with no rows", "table");

      _table = table;
      _table.TableName = tablename;
      LastFetchingTime = DateTime.UtcNow;
    }

    /// <summary>
    /// Collects all records from Table and returns them, Table is clearing after that
    /// </summary>
    public DataTable FetchTable()
    {
      lock (syncRoot)
      {
        LastFetchingTime = DateTime.UtcNow;

        if (_table.Rows.Count == 0)
          return null;

        var detached_table = _table;
        _table = _table.Clone();

        _log.DebugFormat("Fetched {0} rows from storage table {1}", detached_table.Rows.Count, detached_table.TableName);
        return detached_table;
      }
    }

    /// <summary>
    /// Add row to the Table
    /// </summary>
    public bool AddRow(object[] values)
    {
      if (values == null) throw new ArgumentNullException("values");

      if (values.Length != _table.Columns.Count)
      {
        _log.ErrorFormat("Cannot add row in table {0}, received {1} fields but {2} fields expected",
                         _table.TableName, values.Length, _table.Columns.Count);
        return false;
      }

      DataRow newrow;
      lock(syncRoot)
      {
        newrow = _table.NewRow();
      }

      try
      {
        newrow.ItemArray = values;
      }
      catch (Exception ex)
      {
        _log.ErrorFormat("Cannot add row ({0}) in table {1}. Exception message : {2}",
                         String.Join(", ", values.Select(o => o.ToString()).ToArray()), _table.TableName, ex.Message);
        return false;
      }

      lock (syncRoot)
      {
        _table.Rows.Add(newrow);
      }
      return true;
    }
  }
}