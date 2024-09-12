using System;
using System.Data;
using System.Diagnostics;
using Npgsql;
using NUnit.Framework;

namespace DataLogging.Tests
{
  [TestFixture]
  public class DatabaseWriterTests
  {
    private DataLoggingContext context = 
      new DataLoggingContext("Server=localhost;Port=5432;Database=test_logs;User Id=postgres;Password=password;");

    private NpgsqlConnection connection;

    [TestFixtureSetUp]
    public void OpenConnection()
    {
      connection = new NpgsqlConnection(context.ConnectionString);
      connection.Open();
    }

    [TestFixtureTearDown]
    public void CloseConnection()
    {
      connection.Close();
    }

    [Test]
    public void GetVersionTest()
    {
      var writer = new DatabaseWriter(context);
      Assert.Greater(writer.GetVersion(), 0);

      var writer2 = new DatabaseWriter(new DataLoggingContext("Server=l;Port=5;Database=t;User Id=p;Password=q;"));
      Assert.AreEqual(-1, writer2.GetVersion());
    }

    [Test]
    public void FastWriteTest()
    {
      TruncateKill();

      var writer = new DatabaseWriter(context);

      var tb = GenerateKillDataTable(5);
      Assert.That(writer.FastWriteTable(tb));

      AssertThatRowsCountIs(5);
    }

    [Test]
    public void WriteTest()
    {
      TruncateKill();

      var writer = new DatabaseWriter(context);

      var tb = GenerateKillDataTable(5);
      Assert.That(writer.WriteTable(tb));

      AssertThatRowsCountIs(5);
    }

    [Test]
    public void CompareWritesTest()
    {
      var sw_fast = new Stopwatch();
      var sw_slow = new Stopwatch();

      var writer = new DatabaseWriter(context);

      TruncateKill();

      writer.FastWriteTable(GenerateKillDataTable(1));
      writer.WriteTable(GenerateKillDataTable(1));
      
      foreach (int count in new[] {10, 100, 1000})
      {
        var tb = GenerateKillDataTable(count);

        sw_fast.Reset();
        sw_slow.Reset();

        sw_fast.Start();
        Assert.That(writer.FastWriteTable(tb));
        sw_fast.Stop();

        sw_slow.Start();
        Assert.That(writer.WriteTable(tb));
        sw_slow.Stop();

        Debug.WriteLine(String.Format("{0, 4} rows: FastWrite = {1,-4} ms, Write = {2,-4} ms",
                                      count, sw_fast.ElapsedMilliseconds, sw_slow.ElapsedMilliseconds));
        Assert.LessOrEqual(sw_fast.ElapsedMilliseconds, sw_slow.ElapsedMilliseconds);
      }
    }

    private void TruncateKill()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table kill";
      cmd.ExecuteNonQuery();
    }

    private void AssertThatRowsCountIs(int cnt)
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "select count(*) from kill";
      object count = cmd.ExecuteScalar();
      Assert.AreEqual(cnt, count);
    }

    private static DataTable GenerateKillDataTable(int rowscount)
    {
      var datatable = new DataTable("kill");
      datatable.Columns.Add("sessionid", typeof(Int32));
      datatable.Columns.Add("step", typeof(Int32));
      datatable.Columns.Add("x", typeof(Single));
      datatable.Columns.Add("y", typeof(Single));
      datatable.Columns.Add("login", typeof(String));
      datatable.Columns.Add("victimlogin", typeof(String));
      datatable.Columns.Add("victimcreatureid", typeof(Int32));

      for (int i = 0; i < rowscount; i++)
      {
        var row = datatable.NewRow();
        row["sessionid"] = 100;
        row["step"] = 1023;
        row["x"] = 4.5f;
        row["y"] = 6.7f;
        row["login"] = "Varg Vikernes";
        row["victimlogin"] = "Euronymous";
        row["victimcreatureid"] = DBNull.Value;
        datatable.Rows.Add(row);
      }

      return datatable;
    }
  }
}