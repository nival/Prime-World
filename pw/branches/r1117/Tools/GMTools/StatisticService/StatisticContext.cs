using System.Collections.Generic;

namespace StatisticService
{
  public abstract class StatisticContext
  {
    public string ConnectionManagement { get; set; }
    public int DBVersionManagement { get; set; }
    public string ConnectionLogs { get; set; }
    public int DBVersionLogs { get; set; }
  }

  public class GameStatContext : StatisticContext
  {
    public int PollFrequency;
    public string ListenUrl;

    public StatisticWriterContext StatisticWriter;

    public class StatisticWriterContext
    {
      public List<int> LogSessionEvent;
      public bool LogSessionDamage;
    }

    public StatisticDebugWriterContext StatisticDebugWriter;

    public class StatisticDebugWriterContext
    {
      public bool LogExceedingStepTime;
      public bool LogExceedingPingTime;
      public bool LogOfflineEvent;
      public bool LogDebugVar;
      public bool LogPvxLogin;
      public bool LogPvxScreenResolution;
    }
  }

  public class SocialStatContext : StatisticContext
  {
    public string ThriftUrlPrefix;
  }
}