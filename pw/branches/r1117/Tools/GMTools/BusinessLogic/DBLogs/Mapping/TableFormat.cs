using System.Xml.Serialization;

namespace BusinessLogic.DBLogs.Mapping
{
  public class TableFormat
  {
    [XmlAttribute]
    public string Name;
    [XmlArray]
    public StorageField[] Fields;
  }

  public class StorageField
  {
    [XmlAttribute]
    public string Name;
    [XmlAttribute]
    public string Type;
  }
}