using System;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Xml.Serialization;
using log4net;

namespace BusinessLogic.DBLogs.Mapping
{
  public static class TablesMapping
  {
    private static ILog _log = LogManager.GetLogger(typeof(TablesMapping));

    /// <summary>
    /// Get deserialized TableFormat objects from DBLogsTablesMapping.xml
    /// </summary>
    public static TableFormat[] GetLogsTables()
    {
      return Get("DBLogsTablesMapping.xml");
    }

    /// <summary>
    /// Get deserialized TableFormat objects from DBManagementMapping.xml
    /// </summary>
    public static TableFormat[] GetManagementTables()
    {
      return Get("DBManagementMapping.xml");
    }

    private static TableFormat[] Get(string resourceName)
    {
      var assembly = Assembly.GetExecutingAssembly();
      string resource = assembly.GetManifestResourceNames().Single(r => r.Contains(resourceName));
      if (resource == null)
      {
        _log.FatalFormat("Resource {0} was not found", resource);
        return null;
      }

      try
      {
        using (var stream = assembly.GetManifestResourceStream(resource))
        {
          var s = new XmlSerializer(typeof(TableFormat[]));

          using (var reader = new StreamReader(stream))
          {
            var result = (TableFormat[])s.Deserialize(reader);
            return result;
          }
        }
      }
      catch (Exception ex)
      {
        _log.Fatal("Cannot deserialize resource " + resource, ex);
        throw;
      }
    }
  }
}