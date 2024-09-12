using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;
using System.Threading;
using KontagentLib;
using StatisticService.RPC;
using log4net;
using MonitoringService;
using StatisticService;
using ToolsServer.Properties;

namespace ToolsServer
{
  public class ToolsServer
  {
    private static ILog _log = LogManager.GetLogger(typeof(ToolsServer));

    private GameStatService gameStat;
    private SocialStatService socialStat;
    private MonitoringService.MonitoringService gameMonitoring;
    private MonitoringService.MonitoringService socialMonitoring;
    private MonitoringStorage monitoringStorage;
    private MonitoringSummaryHost monitoringSummary;

    private bool AllServicesAreRunning
    {
      get
      {
        if (gameStat != null && gameStat.CurrentStatus != GameStatService.Status.Starting && gameStat.CurrentStatus != GameStatService.Status.Running) return false;
        if (socialStat != null && socialStat.CurrentStatus != SocialStatService.Status.Running) return false;
        if (gameMonitoring != null && gameMonitoring.CurrentStatus != MonitoringService.MonitoringService.Status.Running) return false;
        if (socialMonitoring != null && socialMonitoring.CurrentStatus != MonitoringService.MonitoringService.Status.Running) return false;
        return true;
      }
    }

    private bool initialized;

    private EventWaitHandle runningHandle = new AutoResetEvent(false);
    private volatile bool stopFlag;

    private GameStatContext CreateGameStatContext()
    {
      // Считывание из конфига информации о портах
      var networking = ConfigurationManager.GetSection("networking") as NameValueCollection;
      if (networking == null)
        throw new ConfigurationErrorsException("Configuration block <networking> was not found.");

      // Считывание из конфига информации о версиях
      var dbversions = ConfigurationManager.GetSection("dbversions") as NameValueCollection;
      if (dbversions == null)
        throw new ConfigurationErrorsException("Configuration block <dbversions> was not found.");

      // Считывание из конфига информации о записываемых событиях
      var events = ConfigurationManager.GetSection("events") as StatisticEventsSection;
      if (events == null)
        throw new ConfigurationErrorsException("Configuration block <events> was not found.");

      var swcontext = new GameStatContext.StatisticWriterContext
                        {
                          LogSessionDamage = events.StatisticWriter.LogSessionDamage.ElementInformation.IsPresent,
                          LogSessionEvent = new List<int>()
                        };
      if (events.StatisticWriter.LogSessionEvent != null)
        foreach (SessionEventTypeElement eventType in events.StatisticWriter.LogSessionEvent)
        {
          if (Enum.IsDefined(typeof(SessionEventType), eventType.Name))
          {
            swcontext.LogSessionEvent.Add((int)Enum.Parse(typeof(SessionEventType), eventType.Name));
          }
          else
            _log.ErrorFormat("Invalid SessionEventTypeElement value '{0}'", eventType.Name);
        }

      var sdwcontext = new GameStatContext.StatisticDebugWriterContext
                         {
                           LogExceedingStepTime = events.StatisticDebugWriter.LogExceedingStepTime.ElementInformation.IsPresent,
                           LogExceedingPingTime = events.StatisticDebugWriter.LogExceedingPingTime.ElementInformation.IsPresent,
                           LogOfflineEvent = events.StatisticDebugWriter.LogOfflineEvent.ElementInformation.IsPresent,
                           LogDebugVar = events.StatisticDebugWriter.LogDebugVar.ElementInformation.IsPresent,
                           LogPvxLogin = events.StatisticDebugWriter.LogPvxLogin.ElementInformation.IsPresent,
                           LogPvxScreenResolution = events.StatisticDebugWriter.LogPvxScreenResolution.ElementInformation.IsPresent
                         };
      
      return new GameStatContext
               {
                 DBVersionManagement = Int32.Parse(dbversions["DBVersion_management"]),
                 DBVersionLogs = Int32.Parse(dbversions["DBVersion_logs"]),
                 ConnectionManagement = ConfigurationManager.AppSettings["managementConnectionString_gstat"] ??
                                        ConfigurationManager.AppSettings["managementConnectionString"],
                 ConnectionLogs = ConfigurationManager.AppSettings["logsConnectionString_gstat"] ??
                                  ConfigurationManager.AppSettings["logsConnectionString"],
                 PollFrequency = Int32.Parse(Settings.Default.PollFrequency),
                 ListenUrl = networking["GameStatUrl"],
                 StatisticWriter = swcontext,
                 StatisticDebugWriter = sdwcontext
               };
    }

    private SocialStatContext CreateSocialStatContext()
    {
      // Считывание из конфига информации о портах
      var networking = ConfigurationManager.GetSection("networking") as NameValueCollection;
      if (networking == null)
        throw new ConfigurationErrorsException("Configuration block <networking> was not found.");

      // Считывание из конфига информации о версиях
      var dbversions = ConfigurationManager.GetSection("dbversions") as NameValueCollection;
      if (dbversions == null)
        throw new ConfigurationErrorsException("Configuration block <dbversions> was not found.");

      return new SocialStatContext
               {
                 DBVersionManagement = Int32.Parse(dbversions["DBVersion_management"]),
                 DBVersionLogs = Int32.Parse(dbversions["DBVersion_logs"]),
                 ConnectionManagement = ConfigurationManager.AppSettings["managementConnectionString_sstat"] ??
                                        ConfigurationManager.AppSettings["managementConnectionString"],
                 ConnectionLogs = ConfigurationManager.AppSettings["logsConnectionString_sstat"] ??
                                  ConfigurationManager.AppSettings["logsConnectionString"],
                 ThriftUrlPrefix = networking["Thrift_url_prefix"]
               };
    }

    private KontagentContext CreateKontagentContext(string tdfile)
    {
      var networking = ConfigurationManager.GetSection("networking") as NameValueCollection;
      if (networking == null)
        throw new ConfigurationErrorsException("Configuration block <networking> was not found.");

      if (String.IsNullOrEmpty(networking["MarketingService_url"]))
        return null;

      return new KontagentContext
               {
                 MarketingServiceUrl = networking["MarketingService_url"],
                 RequestTimeout = Settings.Default.MSRequestTimeout,
                 TimeoutAfterError = Settings.Default.MSTimeoutAfterError,
                 QueueLength = Settings.Default.MSQueueLength,
                 QueueDumpingPart = Settings.Default.MSQueueDumpingPart,
                 QueueRestoringPoint = Settings.Default.MSQueueRestoringPoint,
                 SentRateMin = Settings.Default.MSSentRateMin,
                 SentRateMax = Settings.Default.MSSentRateMax,
                 SentRateChange = Settings.Default.MSSentRateChange,
                 MaxFailPercent = Settings.Default.MSMaxFailPercent,
                 TaskDumperFilename = tdfile
               };
    }

    private MonitoringContext CreateMonitoringContext(string type)
    {
      var networking = ConfigurationManager.GetSection("monitoring.networking") as NameValueCollection;
      if (networking == null)
        throw new ConfigurationErrorsException("Configuration block <monitoring.networking> was not found.");

      var context = new MonitoringContext();

      Uri url;

      if (Uri.TryCreate(networking["StatisticService_url"], UriKind.Absolute, out url))
        context.StatisticServiceUrl = url;
      else
        throw new ConfigurationErrorsException("Invalid url \"StatisticService_url\" = " +
                                               networking["StatisticService_url"]);

      if (!String.IsNullOrEmpty(networking["MonitoringSummary_url_prefix"]))
        context.MonitoringSummaryUrlPrefix = networking["MonitoringSummary_url_prefix"];
      else
        throw new ConfigurationErrorsException("Empty value of MonitoringSummary_url_prefix");

      // Deserialize counters requests config
      var counters = ConfigurationManager.GetSection("monitoring.counters") as PerfCounterRequestSection;
      if (counters == null)
        throw new ConfigurationErrorsException("Configuration block <monitoring.counters> is not found");

      context.StatPeriod = counters.StatPeriod.Value;

      // В зависимости от типа создаваемого контекста, из конфига читаются те или иные параметры
      string monitoringUrlParam;
      CounterCollection countersCollection;
      if (type == "game")
      {
        monitoringUrlParam = "GameCluster_monitoring_url";
        countersCollection = counters.PvxCounters;
      }
      else if (type == "social")
      {
        monitoringUrlParam = "SocialCluster_monitoring_url";
        countersCollection = counters.SocialCounters;
      }
      else
        return context;

      // Адрес кластера для мониторинга
      if (Uri.TryCreate(networking[monitoringUrlParam], UriKind.Absolute, out url))
        context.MonitoringUrl = url;
      else
        throw new ConfigurationErrorsException("Invalid url \"SocialCluster_monitoring_url\" = " + networking["SocialCluster_monitoring_url"]);

      // Заполнение каунтеров в контекст
      foreach (CounterElement cnt in countersCollection)
      {
        if (!String.IsNullOrEmpty(cnt.Field) && !String.IsNullOrEmpty(cnt.Counter))
        {
          if (context.Requests.ContainsKey(cnt.Field))
          {
            _log.WarnFormat("Counter for the field {0} is already exists", cnt.Field);
            continue;
          }
          var counterRequest = PerfCounterRequest.FromString(cnt.Counter);
          if (counterRequest == null)
          {
            _log.ErrorFormat("Cannot create counter request for string \"{0}\"", cnt.Counter);
            continue;
          }
          context.Requests.Add(cnt.Field, counterRequest);
        }
      }

      return context;
    }

    public bool Init(bool gstat, bool sstat, bool gmon, bool smon)
    {
      if (initialized)
        return true;

      // Игровая статистика
      if (gstat)
      {
        _log.Info("Init game statistic");
        var context = CreateGameStatContext();
        var kcontext = CreateKontagentContext("marketing-tasks-gstat.dump");
        gameStat = new GameStatService(context, kcontext);
        if (!gameStat.Init())
        {
          _log.Info("Failed to initialize game statistic service");
          return false;
        }
      }

      // Социальная статистика
      if (sstat)
      {
        _log.Info("Init social statistic");
        var context = CreateSocialStatContext();
        var kcontext = CreateKontagentContext("marketing-tasks-sstat.dump");
        socialStat = new SocialStatService(context, kcontext);
        if (!socialStat.Init())
        {
          _log.Info("Failed to initialize social statistic service");
          return false;
        }
      }

      if (gmon || smon)
      {
        var nullcontext = CreateMonitoringContext(null);
        monitoringStorage = new MonitoringStorage(nullcontext.StatisticServiceUrl, nullcontext.StatPeriod);
        monitoringSummary = new MonitoringSummaryHost(nullcontext.MonitoringSummaryUrlPrefix, monitoringStorage);

        if (gmon)
        {
          var context = CreateMonitoringContext("game");
          gameMonitoring = new MonitoringService.MonitoringService(context, monitoringStorage);
          if (!gameMonitoring.Init())
          {
            _log.Info("Failed to initialize game monitoring service");
            return false;
          }
        }

        if (smon)
        {
          var context = CreateMonitoringContext("social");
          socialMonitoring = new MonitoringService.MonitoringService(context, monitoringStorage);
          if (!socialMonitoring.Init())
          {
            _log.Info("Failed to initialize social monitoring service");
            return false;
          }
        }
      }

      initialized = true;
      return true;
    }

    public void Run()
    {
      if (!initialized)
      {
        _log.Error("ToolsServer can't run until it will be initialized");
        return;
      }

      // Запуск всех инициализированных компонентов статистики
      if (gameStat != null && !gameStat.RunAsync())
      {
        _log.Error("Failed to run game statistic service");
        stopFlag = true;
      }
      if (!stopFlag && socialStat != null && !socialStat.RunAsync())
      {
        _log.Error("Failed to run social statistic service");
        stopFlag = true;
      }
      // Запуск всех инициализированных компонентов мониторинга
      if (!stopFlag && monitoringStorage != null && !monitoringStorage.RunStatisticSenderAsync())
      {
        _log.Error("Failed to run monitoring summary host");
        stopFlag = true;
      }
      if (!stopFlag && monitoringSummary != null && !monitoringSummary.RunAsync())
      {
        _log.Error("Failed to run monitoring summary host");
        stopFlag = true;
      }
      if (!stopFlag && gameMonitoring != null && !gameMonitoring.RunAsync())
      {
        _log.Error("Failed to run game monitoring service");
        stopFlag = true;
      }
      if (!stopFlag && socialMonitoring != null && !socialMonitoring.RunAsync())
      {
        _log.Error("Failed to run social monitoring service");
        stopFlag = true;
      }

      while (!stopFlag && AllServicesAreRunning)
      {
        Thread.Sleep(10);
      }

      _log.Info("Stopping all services");
      if (gameStat != null && gameStat.CurrentStatus != BaseStatService.Status.Stopping && gameStat.CurrentStatus != BaseStatService.Status.Stopped) gameStat.Stop();
      if (socialStat != null && socialStat.CurrentStatus != BaseStatService.Status.Stopping && socialStat.CurrentStatus != BaseStatService.Status.Stopped) socialStat.Stop();
      if (monitoringStorage != null) monitoringStorage.StopStatisticSender();
      if (monitoringSummary != null) monitoringSummary.Stop();
      if (gameMonitoring != null) gameMonitoring.Stop();
      if (socialMonitoring != null) socialMonitoring.Stop();

      _log.Info("Tools server is stopped.");
      runningHandle.Set();
    }

    public void Stop()
    {
      stopFlag = true;
      runningHandle.WaitOne();
    }
  }
}