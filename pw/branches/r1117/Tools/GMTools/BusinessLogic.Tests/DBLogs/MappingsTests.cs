using System;
using System.Xml;
using System.Xml.Serialization;
using BusinessLogic.DBLogs.Mapping;
using NUnit.Framework;

namespace BusinessLogic.Tests.DBLogs
{
  [TestFixture]
  public class MappingsTests
  {
    [Test]
    public void FileSerializationTest()
    {
      var stf = new[]
                  { new TableFormat 
                      { Name = "firsttable",
                        Fields = new[]
                                   { new StorageField {Name = "id", Type = typeof (Int32).FullName},
                                     new StorageField {Name = "name", Type = typeof (String).FullName} } },
                    new TableFormat
                      { Name = "secondtable",
                        Fields = new[]
                                   { new StorageField {Name = "xy", Type = typeof (Single).FullName},
                                     new StorageField {Name = "dt", Type = typeof (DateTime).FullName} } } };
      var w = XmlWriter.Create("DeserializeFromFileTest.xml");
      var s = new XmlSerializer(typeof(TableFormat[]));

      Assert.IsNotNull(w);
      s.Serialize(w, stf);

      w.Close();

      var r = XmlReader.Create("DeserializeFromFileTest.xml");
      var stf2 = (TableFormat[]) s.Deserialize(r);

      Assert.IsNotNull(stf2);
      Assert.AreNotSame(stf, stf2);
      Assert.AreEqual(2, stf2.Length);
      
      Assert.AreEqual("firsttable", stf2[0].Name);
      Assert.AreEqual(2, stf2[0].Fields.Length);
      Assert.AreEqual("id", stf2[0].Fields[0].Name);
      Assert.AreEqual("name", stf2[0].Fields[1].Name);
      Assert.AreEqual(typeof(Int32).FullName, stf2[0].Fields[0].Type);
      Assert.AreEqual(typeof(String).FullName, stf2[0].Fields[1].Type);

      Assert.AreEqual("secondtable", stf2[1].Name);
      Assert.AreEqual(2, stf2[1].Fields.Length);
      Assert.AreEqual("xy", stf2[1].Fields[0].Name);
      Assert.AreEqual("dt", stf2[1].Fields[1].Name);
      Assert.AreEqual(typeof(Single).FullName, stf2[1].Fields[0].Type);
      Assert.AreEqual(typeof(DateTime).FullName, stf2[1].Fields[1].Type);
    }

    [Test]
    public void ResourceDBLogsDeserializationTest()
    {
      TableFormat[] table = TablesMapping.GetLogsTables();
      Assert.IsNotNull(table);

      foreach (TableFormat t in table)
      {
        Assert.IsFalse(String.IsNullOrEmpty(t.Name));
        Assert.AreNotEqual(0, t.Fields.Length);

        foreach (StorageField f in t.Fields)
        {
          Assert.IsFalse(String.IsNullOrEmpty(f.Name));
          Assert.IsNotNull(Type.GetType(f.Type), String.Format("{0} {1}", t.Name, f.Type));
        }
      }
    }

    [Test]
    public void ResourceDBManagementDeserializationTest()
    {
      TableFormat[] table = TablesMapping.GetManagementTables();
      Assert.IsNotNull(table);

      foreach (TableFormat t in table)
      {
        Assert.IsFalse(String.IsNullOrEmpty(t.Name));
        Assert.AreNotEqual(0, t.Fields.Length);

        foreach (StorageField f in t.Fields)
        {
          Assert.IsFalse(String.IsNullOrEmpty(f.Name));
          Assert.IsNotNull(Type.GetType(f.Type), String.Format("{0} {1}", t.Name, f.Type));
        }
      }
    }
  }
}