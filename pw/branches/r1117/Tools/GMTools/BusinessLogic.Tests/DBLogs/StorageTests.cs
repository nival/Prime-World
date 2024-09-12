using System;
using System.Collections.Generic;
using System.Reflection;
using BusinessLogic.DBLogs;
using BusinessLogic.DBLogs.Mapping;
using BusinessLogic.Queuing;
using DataLogging;
using Moq;
using NUnit.Framework;

namespace BusinessLogic.Tests.DBLogs
{
  [TestFixture]
  public class OperationalStorageTests
  {
    [Test]
    public void CreateStorage()
    {
      var mockTaskExecutor = new Mock<ITaskExecutor>();
      var mockDatabaseWriter = new Mock<IDatabaseWriter>();

      var tables = new[]
                     {
                       new TableFormat
                         {
                           Name = "firsttable",
                           Fields = new[]
                                      {
                                        new StorageField {Name = "id", Type = typeof (Int32).FullName},
                                        new StorageField {Name = "name", Type = typeof (String).FullName}
                                      }
                         },
                       new TableFormat
                         {
                           Name = "secondtable",
                           Fields = new[]
                                      {
                                        new StorageField {Name = "longid", Type = typeof (Int64).FullName},
                                        new StorageField {Name = "timestamp", Type = typeof (DateTime).FullName}
                                      }
                         }
                     };
      var storage = new DBLogsStorage(mockTaskExecutor.Object, mockDatabaseWriter.Object, tables);

      FieldInfo fi = typeof (DBLogsStorage).GetField("eventStorage", BindingFlags.Instance | BindingFlags.NonPublic);
      var private_eventStorage = (Dictionary<string, StorageTable>)fi.GetValue(storage);
      
      Assert.AreEqual(2, private_eventStorage.Count);
      Assert.That(private_eventStorage.ContainsKey("firsttable"));
      Assert.That(private_eventStorage.ContainsKey("secondtable"));
    }

    [Test]
    public void RegisterTableTest()
    {
      /*var storage = new OperationalStorage();
      var tableformat = new TableFormat
                          {
                            Name = "firsttable",
                            Fields = new[]
                                       {
                                         new StorageField {Name = "id", Type = typeof (Int32).FullName},
                                         new StorageField {Name = "name", Type = typeof (String).FullName}
                                       }
                          };
      bool added = storage.RegisterTable(tableformat);
      Assert.That(added);

      added = storage.RegisterTable(tableformat);
      Assert.That(!added);

      tableformat.Name = "secondtable";
      tableformat.Fields = new[] { new StorageField {Name = "id", Type = typeof (Int32).FullName} };
      added = storage.RegisterTable(tableformat);
      Assert.That(added);

      FieldInfo fi = typeof (OperationalStorage).GetField("eventStorage", BindingFlags.Instance | BindingFlags.NonPublic);
      var private_eventStorage = (Dictionary<string, StorageTable>)fi.GetValue(storage);
      
      Assert.AreEqual(2, private_eventStorage.Count);
      Assert.That(private_eventStorage.ContainsKey("firsttable"));
      Assert.That(private_eventStorage.ContainsKey("secondtable"));*/
    }

    [Test]
    public void WriteInTest()
    {
      /*var storage = new OperationalStorage();
      var tableformat = new TableFormat
                          {
                            Name = "testtable",
                            Fields = new[]
                                       {
                                         new StorageField {Name = "id", Type = typeof (Int32).FullName},
                                         new StorageField {Name = "name", Type = typeof (String).FullName},
                                         new StorageField {Name = "date", Type = typeof (DateTime).FullName}
                                       }
                          };
      storage.RegisterTable(tableformat);

      object[] values;

      values = new object[] {100, "name00", DateTime.Now};
      Assert.That(storage.WriteIn("testtable", values));

      values = new object[] { 105, DateTime.Now, "name05" };
      Assert.IsFalse(storage.WriteIn("testtable", values));

      values = new object[] { 100, "name00", DateTime.Now };
      Assert.IsFalse(storage.WriteIn("anothertesttable", values));

      values = new object[] { "name00", DateTime.Now };
      Assert.IsFalse(storage.WriteIn("testtable", values));

      FieldInfo fi = typeof(OperationalStorage).GetField("eventStorage", BindingFlags.Instance | BindingFlags.NonPublic);
      var private_eventStorage = (Dictionary<string, StorageTable>)fi.GetValue(storage);

      Assert.AreEqual(1, private_eventStorage.Count);
      Assert.That(private_eventStorage.ContainsKey("testtable"));

      StorageTable st = private_eventStorage["testtable"];
      Assert.AreEqual(1, st.Table.Rows.Count);*/
    }
  }
}