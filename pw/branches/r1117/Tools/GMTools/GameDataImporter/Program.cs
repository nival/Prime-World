using System;
using System.Collections.Specialized;
using System.Configuration;
using log4net;
using log4net.Config;

namespace GameDataImporter
{
  class Program
  {
    private static ILog _log = LogManager.GetLogger(typeof (Program));

    static int Main(string[] args)
    {
      XmlConfigurator.Configure();
      _log.Info("Run game data importer");

      IDatabaseInteraction dbi = null;
      IGameDataInteraction gdi = null;
      try
      {
        string servicetype = args.Length != 0 ? args[0] : null;
        string connstr = servicetype == null
                           ? ConfigurationManager.AppSettings["managementConnectionString"]
                           : ConfigurationManager.AppSettings["managementConnectionString_" + servicetype] ??
                             ConfigurationManager.AppSettings["managementConnectionString"];
        dbi = new DatabaseInteraction(connstr);
        gdi = new GameDataInteraction();

        var dbversions = ConfigurationManager.GetSection("dbversions") as NameValueCollection;
        if (!dbi.CheckVersion(Int32.Parse(dbversions["DBVersion_management"])))
          return 1;

        var importer = new Importer(dbi, gdi);
        importer.Run();
        _log.Info("Database update completed successfully.");
      }
      catch (Exception ex)
      {
        _log.Fatal("Import Failed!", ex);
        return 1;
      }
      finally
      {
        if (gdi != null)
          gdi.Dispose();
      }
      return 0;
    }
  }
}
