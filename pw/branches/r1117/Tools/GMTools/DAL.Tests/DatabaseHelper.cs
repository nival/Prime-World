using System;
using System.Linq;
using System.Xml.Linq;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests
{
  static class DatabaseHelper
  {
    public static string ConnectionString { get; private set; }
    private static bool initialized;

    public static void Init()
    {
      if (initialized)
        return;

      // read connection string directly from config file
      var xD = XDocument.Load("Statistic.datasources.config");
      string connstr = xD.Root.Descendants("add")
        .First(e => e.Attribute("key").Value == "managementConnectionString")
        .Attribute("value").Value;
      var builder = new NpgsqlConnectionStringBuilder(connstr) { Database = "test_management" };
      ConnectionString = builder.ToString();

      // read version information from config file
      xD = XDocument.Load("Statistic.dbversions.config");
      string verstr = xD.Root.Descendants("add")
        .First(e => e.Attribute("key").Value == "DBVersion_management")
        .Attribute("value").Value;
      int ver = Int32.Parse(verstr);

      var context = new DALContext(ConnectionString);
      NHibernateHelper.Init(context);
      Assert.AreEqual(ver, NHibernateHelper.DBVersion);
      initialized = true;
    }
  }
}
