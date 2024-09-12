using System;
using System.Data;
using BusinessLogic.DBManagement;
using DataLogging;
using log4net;

namespace BusinessLogic.DBLogs
{
  public class WriteTableTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (WriteTableTask));

    private readonly IDatabaseWriter dbwriter;
    private readonly DataTable table;

    public WriteTableTask(IDatabaseWriter dbwriter, DataTable table)
    {
      if (dbwriter == null) throw new ArgumentNullException("dbwriter");
      if (table == null) throw new ArgumentNullException("table");

      this.dbwriter = dbwriter;
      this.table = table;
    }

    public override bool Execute()
    {
      try
      {
        _log.DebugFormat("Writing {0} rows into table {1}", table.Rows.Count, table.TableName);
        bool success = dbwriter.WriteTable(table);
        if (!success)
          ErrorCount++;
        return success;
      }
      catch (Exception ex)
      {
        _log.Error("Failed task " + this, ex);
        ErrorCount++;
        LastErrorMessage = ex.Message;
        return false;
      }
    }

    public override string ToString()
    {
      return String.Format("WriteTableTask(dbwriter={0}, DataTable(Name={1}, RowCount={2}))",
                           dbwriter, table.TableName, table.Rows.Count);
    }
  }
}