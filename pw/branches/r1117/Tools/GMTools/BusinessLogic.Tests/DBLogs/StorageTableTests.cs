using System;
using System.Collections.Generic;
using System.Data;
using BusinessLogic.DBLogs;
using NUnit.Framework;

namespace BusinessLogic.Tests.DBLogs
{
  [TestFixture]
  public class StorageTableTests
  {
    [Test]
    public void CreateTable()
    {
      var dt = new DataTable();
      dt.Columns.Add(new DataColumn("id", typeof (Int32)));
      var t = new StorageTable("test table", dt);
      Assert.IsNotNull(t.Table);
      Assert.That(t.Table.Columns.Contains("id"));
      Assert.AreEqual("test table", t.Table.TableName);
    }
    
    [Test]
    public void CreateTableWithNoColums()
    {
      var dt = new DataTable();
      try
      {
        new StorageTable("test table", dt);
        Assert.Fail("Created StorageTable without any columns");
      }
      catch (ArgumentException)
      {
      }
    }

    [Test]
    public void AddRowToTable()
    {
      var dt = new DataTable();
      dt.Columns.Add(new DataColumn("c_int", typeof(Int32)));
      dt.Columns.Add(new DataColumn("c_float", typeof(Single)));
      dt.Columns.Add(new DataColumn("c_string", typeof(String)));
      dt.Columns.Add(new DataColumn("c_datetime", typeof(DateTime)));
      dt.Columns.Add(new DataColumn("c_bool", typeof (bool)));
      
      var t = new StorageTable("test table", dt);

      List<object> values;

      values = new List<object> {1, 4f, "sample string"};
      Assert.IsFalse(t.AddRow(values.ToArray()));

      values.Add(DateTime.Now);
      values.Add(false);
      Assert.IsTrue(t.AddRow(values.ToArray()));

      values[0] = "invalid";
      Assert.IsFalse(t.AddRow(values.ToArray()));

      Assert.AreEqual(1, t.Table.Rows.Count);
    }

    [Test]
    public void FetchTable()
    {
      var dt = new DataTable();
      dt.Columns.Add(new DataColumn("id", typeof (Int32)));
      dt.Columns.Add(new DataColumn("name", typeof (String)));
      var t = new StorageTable("test table", dt);

      var ftime = t.LastFetchingTime;
      Assert.LessOrEqual(ftime, DateTime.Now);

      object[] values;
      values = new object[] {1, "test name 1"};
      t.AddRow(values);
      values = new object[] {2, "test name 2"};
      t.AddRow(values);
      values = new object[] {3, "test name 3"};
      t.AddRow(values);

      Assert.AreEqual(3, t.Table.Rows.Count);

      DataTable ft = t.FetchTable();
      Assert.AreEqual(0, t.Table.Rows.Count);
      Assert.AreEqual(3, ft.Rows.Count);

      Assert.AreEqual(1, (int) ft.Rows[0]["id"]);
      Assert.AreEqual(2, (int) ft.Rows[1]["id"]);
      Assert.AreEqual(3, (int) ft.Rows[2]["id"]);
      Assert.AreEqual("test name 1", ft.Rows[0]["name"]);
      Assert.AreEqual("test name 2", ft.Rows[1]["name"]);
      Assert.AreEqual("test name 3", ft.Rows[2]["name"]);
    }
  }
}