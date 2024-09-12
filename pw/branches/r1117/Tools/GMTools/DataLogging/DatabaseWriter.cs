using System;
using System.Data;
using System.Globalization;
using System.Linq;
using log4net;
using Npgsql;

namespace DataLogging
{
  public interface IDatabaseWriter
  {
    bool FastWriteTable(DataTable table);
    bool WriteTable(DataTable table);

    int GetVersion();
  }

  public class DatabaseWriter : IDatabaseWriter
  {
    private static ILog _log = LogManager.GetLogger(typeof(DatabaseWriter));
    
    private readonly DataLoggingContext context;

    public DatabaseWriter(DataLoggingContext context)
    {
      if (context == null) throw new ArgumentNullException("context");
      this.context = context;
    }


    /// <summary>
    /// Fast but yet unstable writing approach
    /// </summary>
    public bool FastWriteTable(DataTable table)
    {
      if (table == null) throw new ArgumentNullException("table");
      if (table.Rows.Count == 0)
        return true;

      string[] fields = new string[table.Columns.Count];
      for (int i = 0; i < table.Columns.Count; i++)
      {
        fields[i] = table.Columns[i].ColumnName;
      }

      var connection = new NpgsqlConnection(context.ConnectionString);
      try
      {
        connection.Open();
        var serializer = new NpgsqlCopySerializer(connection);

        var cmd = connection.CreateCommand();
        cmd.CommandText = String.Format("copy {0} ({1}) from STDIN", table.TableName, String.Join(",", fields));

        var copyIn = new NpgsqlCopyIn(cmd, connection);
        serializer.ToStream = copyIn.CopyStream;
        copyIn.Start();

        foreach (DataRow row in table.Rows)
        {
          foreach (object item in row.ItemArray)
          {
            if (item is DBNull)
              serializer.AddNull();
            else if (item is DateTime)
              serializer.AddDateTime((DateTime)item);
            else if (item is bool)
              serializer.AddBool((bool)item);
            else if (item is float)
              serializer.AddString(((float)item).ToString(CultureInfo.InvariantCulture));
            else if (item is double)
              serializer.AddString(((double)item).ToString(CultureInfo.InvariantCulture));
            else
              serializer.AddString(item.ToString());
          }
          serializer.EndRow();
        }
        serializer.Flush();
        serializer.Close();
        copyIn.End();
      }
      catch (NpgsqlException ex)
      {
        _log.Error(String.Format("Failed to write {0} rows in table {1}",table.Rows.Count, table.TableName), ex);
        return false;
      }
      finally
      {
        connection.Close();
      }
      return true;
    }

    /// <summary>
    /// Simple ADO.NET writing in one transaction
    /// </summary>
    public bool WriteTable(DataTable table)
    {
      if (table == null) throw new ArgumentNullException("table");
      if (table.Rows.Count == 0)
        return true;

      string[] fields = new string[table.Columns.Count];
      for (int i = 0; i < table.Columns.Count; i++)
      {
        fields[i] = table.Columns[i].ColumnName;
      }

      var connection = new NpgsqlConnection(context.ConnectionString);
      try
      {
        connection.Open();

        var cmd = connection.CreateCommand();
        cmd.CommandText = String.Format("insert into {0} ({1}) values ({2})",
                                        table.TableName, String.Join(",", fields), String.Join(",", fields.Select(f => "@" + f).ToArray()));

        using (var tran = connection.BeginTransaction())
        {
          cmd.Transaction = tran;

          foreach (DataRow row in table.Rows)
          {
            cmd.Parameters.Clear();
            foreach (string field in fields)
            {
              cmd.Parameters.AddWithValue("@" + field, row[field]);
            }
            cmd.ExecuteNonQuery();
          }

          tran.Commit();
        }
      }
      catch (NpgsqlException ex)
      {
        _log.Error(String.Format("Failed to write {0} rows in table {1}", table.Rows.Count, table.TableName), ex);
        return false;
      }
      finally
      {
        connection.Close();
      }
      return true;
    }

    public int GetVersion()
    {
      var connection = new NpgsqlConnection(context.ConnectionString);
      try
      {
        connection.Open();
        var cmd = new NpgsqlCommand("select dbversion()", connection);
        return (int)cmd.ExecuteScalar();
      }
      catch (Exception ex)
      {
        _log.Error("Error while requesting dbversion", ex);
        return -1;
      }
      finally
      {
        connection.Close();
      }
    }
  }
}