using System;
using log4net;
using log4net.Config;
using StatisticService.LoadTests.BusinessLogic;

namespace StatisticService.LoadTests
{
  class Program
  {
    private static ILog _log = LogManager.GetLogger(typeof (Program));

    static void Main(string[] args)
    {
      XmlConfigurator.Configure();
      _log.Info("Run statistic load test");

      try
      {
        //var test = new DBLogsStorageTest();
        var test = new FullTest();
        test.Run();
      }
      catch (Exception ex)
      {
        _log.Fatal("AAARRRRGH!!!", ex);
      }
    }
  }
}
