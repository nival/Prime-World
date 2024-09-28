using System.Collections.Generic;

namespace KontagentLib
{
  public interface IKontagentTaskCreator
  {
    IKontagentTask CreateLauncherStart(long auid, string hostid, string version);
    IKontagentTask CreateLauncherDStart(long auid, string hostid, string package, string version);
    IKontagentTask CreateLauncherDEnd(long auid, string hostid, string package, string version, int status);
    IKontagentTask CreateLauncherEvents(long auid, string muid, long events);
    IKontagentTask CreateFirstLogin(long auid, string muid);
    IKontagentTask CreateCastleLogin(long auid, int faction);
    IKontagentTask CreateFactionSelected(long auid, int faction);
    IKontagentTask CreateSessionStart(long auid, int faction, int sessiontype, int heroid);
    IKontagentTask CreateResourceChange(long auid, string source, bool gain, int goldchange, int silverchange, int perlchange,
                                        int redperlchange, int resource1change, int resource2change, int resource3change, int shardchange, Dictionary<string, int> currencyChange);
    IKontagentTask CreateQuestChange(long auid, int status, int quid, int tm);
  }

  public class KontagentTaskCreator : IKontagentTaskCreator
  {
    public IKontagentTask CreateLauncherStart(long auid, string hostid, string version)
    {
      return new LauncherStartTask { Auid = auid, HostId = hostid, Version = version };
    }

    public IKontagentTask CreateLauncherDStart(long auid, string hostid, string package, string version)
    {
      return new LauncherDStartTask { Auid = auid, HostId = hostid, Package = package, Version = version };
    }

    public IKontagentTask CreateLauncherDEnd(long auid, string hostid, string package, string version, int status)
    {
      return new LauncherDEndTask { Auid = auid, HostId = hostid, Package = package, Version = version, Status = status };
    }

    public IKontagentTask CreateLauncherEvents(long auid, string muid, long events)
    {
      return new LauncherEventsTask { Auid = auid, Muid = muid, Events = events };
    }

    public IKontagentTask CreateFirstLogin(long auid, string muid)
    {
      return new FirstLoginTask { Auid = auid, Muid = muid };
    }

    public IKontagentTask CreateCastleLogin(long auid, int faction)
    {
      return new CastleLoginTask { Auid = auid, Faction = faction };
    }

    public IKontagentTask CreateFactionSelected(long auid, int faction)
    {
      return new FactionSelectedTask { Auid = auid, Faction = faction };
    }

    public IKontagentTask CreateSessionStart(long auid, int faction, int sessiontype, int heroid)
    {
      return new SessionStartTask { Auid = auid, Faction = faction, SessionType = sessiontype, HeroId = heroid };
    }

    public IKontagentTask CreateResourceChange(long auid, string source, bool gain, int goldchange, int silverchange, int perlchange, int redperlchange, int resource1change, int resource2change, int resource3change, int shardchange, Dictionary<string, int> currencyChange)
    {
      return new ResourceChangeTask
               {
                 Auid = auid,
                 Source = source,
                 Gain = gain,
                 GoldChange = goldchange,
                 SilverChange = silverchange,
                 PerlChange = perlchange,
                 RedPerlChange = redperlchange,
                 Resource1Change = resource1change,
                 Resource2Change = resource2change,
                 Resource3Change = resource3change,
                 ShardChange = shardchange,
                 CurrencyChange = currencyChange
               };
    }

    public IKontagentTask CreateQuestChange(long auid, int status, int quid, int tm)
    {
      return new QuestChangeTask {Auid = auid, Status = status, Quid = quid, Tm = tm};
    }
  }
}