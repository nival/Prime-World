using System;
using System.Collections;
using System.Runtime.InteropServices;
using log4net;
using log4net.Config;
using ToolsServer.Utils;

namespace ToolsServer
{
  class Program
  {
    #region Console exit event handler

    [DllImport("Kernel32")]
    private static extern bool SetConsoleCtrlHandler(EventHandler handler, bool add);

    private delegate bool EventHandler(CtrlType sig);
    private static EventHandler _handler;
    private static event Action Closed;

    enum CtrlType
    {
      CTRL_C_EVENT = 0,
      CTRL_BREAK_EVENT = 1,
      CTRL_CLOSE_EVENT = 2,
      CTRL_LOGOFF_EVENT = 5,
      CTRL_SHUTDOWN_EVENT = 6
    }

    private static bool Handler(CtrlType sig)
    {
      switch (sig)
      {
        case CtrlType.CTRL_C_EVENT:
        case CtrlType.CTRL_BREAK_EVENT:
        case CtrlType.CTRL_LOGOFF_EVENT:
        case CtrlType.CTRL_SHUTDOWN_EVENT:
        case CtrlType.CTRL_CLOSE_EVENT:
          _log.InfoFormat("Caught signal {0}", sig);
          Closed();
          Environment.Exit(0);
          _log.Info("Environment.Exit()");
          break;
      }
      return true;
    }

    #endregion

    private static ILog _log = LogManager.GetLogger("ToolsServer");

    #region Command line parameters
    #pragma warning disable 649

    [CommandLineParser.Argument("?", "help", "Show this usage screen")]
    private static bool showHelp;

    [CommandLineParser.Argument("gstat", "game-statistic", "Launch game statistic")]
    private static bool gameStatistic;
    [CommandLineParser.Argument("sstat", "social-statistic", "Launch social statistic")]
    private static bool socialStatistic;

    [CommandLineParser.Argument("gmon", "game-monitoring", "Launch game monitoring")]
    private static bool gameMonitoring;
    [CommandLineParser.Argument("smon", "social-monitoring", "Launch social monitoring")]
    private static bool socialMonitoring;

    #pragma warning restore 649
    #endregion
    
    private static ToolsServer server = new ToolsServer();

    static int Main(string[] args)
    {
      Console.Title = "ToolsServer";

      _handler += Handler;
      SetConsoleCtrlHandler(_handler, true);
      Closed += ProgramClosed;

      // Configure logging
      var argslist = (IList) args;
      if (argslist.Contains("-gstat")) ExtendedNamingFileAppender.ServiceName += "-gamestat";
      if (argslist.Contains("-sstat")) ExtendedNamingFileAppender.ServiceName += "-socialstat";
      if (argslist.Contains("-gmon")) ExtendedNamingFileAppender.ServiceName += "-gamemonitoring";
      if (argslist.Contains("-smon")) ExtendedNamingFileAppender.ServiceName += "-socialmonitoring";
      
      XmlConfigurator.Configure();
      _log.Info("Run tools server");
      var utcoffset = TimeZone.CurrentTimeZone.GetUtcOffset(DateTime.Now);
      _log.InfoFormat("Local time: UTC{0:+#.#;-#.#}", utcoffset.TotalMinutes/60f);

      if (!CommandLineParser.FillObject(typeof(Program), args,
        arg => { _log.ErrorFormat("Invalid argument \"{0}\"", arg); return false; },
        (arg, value) => { _log.ErrorFormat("Invalid value \"{0}\" for argument \"{1}\"", value, arg); return false; }))
      {
        return 1;
      }

      if (showHelp || (!gameStatistic && !socialStatistic && !gameMonitoring && !socialMonitoring))
      {
        Console.WriteLine("\nUsage: ToolsServer.exe [option | option=value]\n");
        CommandLineParser.ShowHelp(typeof(Program), true, null);
        return 0;
      }

      Console.Title += " " + String.Join(" ", args);
      
      // Инициализация и старт приложения
      try
      {
        if (!server.Init(gameStatistic, socialStatistic, gameMonitoring, socialMonitoring))
          return 1;

        server.Run();
      }
      catch (Exception ex)
      {
        _log.Fatal(ex);
        return 1;
      }

      return 0;
    }

    static void ProgramClosed()
    {
      _log.Info("Server.Stop()");
      server.Stop();
    }
  }
}
