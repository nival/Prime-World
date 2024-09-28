using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.DBLogs;
using BusinessLogic.DBLogs.Mapping;
using BusinessLogic.DBManagement;
using BusinessLogic.Queuing;
using DataLogging;

namespace BusinessLogic.Social
{
  public class SocialSessionManager : ISocialSessionManager
  {
    private readonly IDBManagementStorage storage;
    private readonly IDBLogsStorage logstorage;
    private readonly IDBLogsStorage logstoragePwLogs;

    public SocialSessionManager(string mgmtconnectionstring, string logsconnectionstring)
    {
      var mgmtdlcontext = new DataLoggingContext(mgmtconnectionstring);
      var logsdlcontext = new DataLoggingContext(logsconnectionstring);

      storage = new DBManagementStorage(new TaskExecutor { Name = "SocialSessionManager" });
      logstorage = new DBLogsStorage(new TaskExecutor {Name = "SocialSessionManager_Logs"},
                                     new DatabaseWriter(mgmtdlcontext), TablesMapping.GetManagementTables());
      logstoragePwLogs = new DBLogsStorage(new TaskExecutor {Name = "SocialSessionManager_MLogs"},
                                           new DatabaseWriter(logsdlcontext), TablesMapping.GetLogsTables());
    }

    public SocialSessionManager(IDBManagementStorage dbManagementStorage, IDBLogsStorage dbManagementEventStorage,
      IDBLogsStorage dbLogsEventStorage)
    {
      if (dbManagementStorage == null) throw new ArgumentNullException("dbManagementStorage");
      if (dbManagementEventStorage == null) throw new ArgumentNullException("dbManagementEventStorage");
      if (dbLogsEventStorage == null) throw new ArgumentNullException("dbLogsEventStorage");

      storage = dbManagementStorage;
      logstorage = dbManagementEventStorage;
      logstoragePwLogs = dbLogsEventStorage;
    }

    public bool IsRunning
    {
      get { return storage.IsRunning && logstorage.IsRunning && logstoragePwLogs.IsRunning; }
    }

    public void LogIn(IEnumerable<LoginInfoBL> logins)
    {
      storage.WriteSocialLogin(logins);
    }

    public void LogOut(IEnumerable<LoginInfoBL> logins)
    {
      storage.WriteSocialLogout(logins);
    }

    public void FactionSelect(IEnumerable<FactionSelectInfoBL> infos)
    {
      storage.WriteFactionChange(infos);
    }

    public void JoinSession(IEnumerable<JoinSessionInfoBL> infos)
    {
      foreach (var info in infos)
      {
        foreach (int talentid in info.TalentSet)
          logstoragePwLogs.WriteIn("talentjoinsession", info.Auid, info.HeroId, info.SessionPersistentId, talentid);

        if (info.GuildBuffs != null && info.GuildBuffs.Count > 0)
          foreach (int buff in info.GuildBuffs)
            logstoragePwLogs.WriteIn("guildbuffsession", "join", info.Auid, info.SessionPersistentId, buff, info.GuildwarEventPass);
      }
    }

    public void SessionAwards(IEnumerable<SessionAwardsInfoBL> awards)
    {
      var awardsList = awards.ToList();

      storage.WriteSessionAwards(awardsList);

      foreach (var aw in awardsList)
        if (aw.GuildBuffs != null && aw.GuildBuffs.Count > 0)
          foreach (int buff in aw.GuildBuffs)
            logstoragePwLogs.WriteIn("guildbuffsession", "roll", aw.Auid, aw.SessionPersistentId, buff);
    }

    public void TalentChange(IEnumerable<TalentChangeInfoBL> infos)
    {
      storage.WriteTalentLog(infos);
    }

    public void UnlockHero(IEnumerable<UnlockHeroInfoBL> unlocks)
    {
      storage.WriteCharacterUnlock(unlocks);
    }

    public void MoveToBath(IEnumerable<MoveToBathInfoBL> infos)
    {
      storage.WriteMovingToBath(infos);
    }

    public void AddIgnore(IEnumerable<AddIgnoreInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
      {
        logstoragePwLogs.WriteIn("ignoreadd", i.Auid, i.Ignoreauid, i.Reason, i.Timestamp);
      }
    }

    public void RemoveIgnore(IEnumerable<RemoveIgnoreInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
      {
        logstoragePwLogs.WriteIn("ignoreremove", i.Auid, i.Ignoreauid, i.Timestamp);
      }
    }

    public void ResourcesChange(IEnumerable<ResourcesChangeInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteResourceLog(infos);
    }

    public void QuestChange(IEnumerable<QuestChangeInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteQuestChange(infos);
    }

    public void DynamicQuestChange(IEnumerable<DynamicQuestChangeInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteDynamicQuestChange(infos);
    }

    public void TournamentQuestChange( IEnumerable<TournamentQuestChangeInfoBL> infos )
    {
      if ( infos == null ) throw new ArgumentNullException( "infos" );
      storage.WriteTournamentQuestChange( infos );
    }

    public void RatingChange(IEnumerable<RatingChangeInfoBL> infos)
    {
      foreach (var info in infos)
        logstoragePwLogs.WriteIn("ratingchange", info.Type, info.Auid, info.SessionPersistentId, info.HeroId, 
          info.RatingInc, info.RatingNew, info.Timestamp);
    }

    public void GuildCreated(IEnumerable<GuildInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildCreate(infos);
    }

    public void GuildRenamed(IEnumerable<GuildInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildRename(infos);
    }

    public void GuildJoined(IEnumerable<GuildCoreInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildJoin(infos);
    }

    public void GuildLeaved(IEnumerable<GuildLeaveInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildLeave(infos);
    }

    public void GuildDisbanded(IEnumerable<GuildCoreInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildDisband(infos);
    }

    public void GuildShopBuy(IEnumerable<GuildShopBuyInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildShopBuy(infos);
    }

    public void GuildSiege(IEnumerable<GuildSiegeInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildSiege(infos);
    }

    public void GuildDailyStats(IEnumerable<GuildDailyStatsInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildDailyStats(infos);
    }

    public void GuildInteraction(IEnumerable<GuildInteractionInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      storage.WriteGuildInteraction(infos);
    }

    public void GuildPointsChange(IEnumerable<GuildPointsChangeInfoBL> infos)
    {
      storage.WriteGuildPointsChange(infos);
    }

    public void RuneExpire(IEnumerable<RuneExpireInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstorage.WriteIn("runeexpire", i.Auid, i.RuneId, i.TransactionsLeft, i.BonusLeft, i.Timestamp);
    }

    public void RuneUnsoulbound(IEnumerable<RuneSoulboundInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstorage.WriteIn("runeunsoulbound", i.Auid, i.RuneId, i.TalentId, i.Timestamp);
    }

      public void RuneHeroApply(IEnumerable<RuneHeroApplyInfoBL> infos)
      {
          if (infos == null) throw new ArgumentNullException("infos");
          foreach (var i in infos)
              logstorage.WriteIn("runeheroapply", i.Auid, i.RuneId, i.Hero, i.Timestamp);
      }

      public void GWEventAdd(IEnumerable<GWEventInfoBL> infos)
      {
          if (infos == null) throw new ArgumentNullException("infos");
          foreach (var i in infos)
              logstorage.WriteIn("gwevents", i.mongoId, i.eventidx, i.enabled, i.points, i.endTime, i.limit);
        }

    public void GWScoreChange(IEnumerable<GWScoreChangeInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstorage.WriteIn("gweventslog", i.gweventmid, i.guildid, i.lastpoints, i.currentpoints, i.timestamp, i.auid);
    }

    public void RuneReplenish(IEnumerable<RuneReplenishInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstorage.WriteIn("runereplenish", i.Auid, i.RuneId, i.Timestamp);
    }

    public void RuneRoll(IEnumerable<RuneRollInfoBL> infos)
    {
      foreach (var i in infos)
        logstorage.WriteIn("runeroll", i.Auid, i.Source, i.SessionPersistentId, i.RuneId, i.Timestamp, i.RunesCountOld, i.RunesCountNew);
    }

    public void Claim(IEnumerable<ClaimInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstorage.WriteIn("claim", i.FromAuid, i.ToAuid, i.Source, i.Category, i.Locale, i.Comment, i.Log, i.Timestamp, i.PersistentId, i.Kills, i.Deaths, i.Assists, i.Points, i.Prime, i.Distance, i.Afks, i.ConnStatus, i.Muid);
    }

    public void AfterParty(IEnumerable<AfterPartyInfoBL> infos)
    {
      storage.WriteAfterParty(infos);
    }

    public void LeaverPointsChange(IEnumerable<LeaverPointsChangeInfoBL> infos)
    {
      storage.WriteLeaverPointsLog(infos);
    }

    public void ReRollShop(IEnumerable<ReRollShopInfoBL> infos)
    {
        storage.WriteReRollShopLog(infos);
    }

    public void QuestEventStageChange(IEnumerable<QuestEventStagesInfoBL> infos)
    {
      foreach (var i in infos)
        logstorage.WriteIn("questeventsstageslog", i.ToStageChange, i.Auid, i.Timestamp);
    }

    public void QuestEventStepChange(IEnumerable<QuestEventStepsInfoBl> infos)
    {
      foreach (var i in infos)
        logstorage.WriteIn("questeventsstepslog", i.ToStepChange, i.Stage, i.Auid, i.TimeStamp);
    }

    public void GMOperation(IEnumerable<GMOperationInfoBL> infos)
    {
      storage.WriteGMOperation(infos);
    }

    public void GMUserOperation(IEnumerable<GMUserOperationInfoBL> infos)
    {
      storage.WriteGMUserOperation(infos);
    }

    public void LauncherStart(string hostid, string version, long playerid, string clientip, string geolocation, string locale, DateTime timestamp)
    {
      logstoragePwLogs.WriteIn("launcherstart", hostid, version, playerid, clientip, geolocation, locale, timestamp);
    }

    public void LauncherDAction(string action, string hostid, string version, string muid, long playerid, float speed, float avgspeed, float minspeed, int totalpatches, int appliedpatches, float totaldownload, float downloaded, string error, int needclose, string geolocation, string locale, DateTime clienttimestamp, DateTime servertimestamp)
    {
      logstoragePwLogs.WriteIn("launcherdaction", action, hostid, version, muid, playerid, speed, avgspeed, minspeed, totalpatches, appliedpatches, totaldownload, downloaded, error, needclose, geolocation, locale, clienttimestamp, servertimestamp);
    }

    public void LauncherEvents(long playerid, string muid, long eventflags, string locale, DateTime clienttimestamp, DateTime servertimestamp)
    {
      logstoragePwLogs.WriteIn("launcherevents", playerid, muid, eventflags, locale, clienttimestamp, servertimestamp);
    }

    public void SocialRegister(string hostid, long playerid, string snid, string snuid, string muid, DateTime timestamp)
    {
      logstoragePwLogs.WriteIn("socialregister", hostid, playerid, snid, snuid, muid, timestamp);
    }

    public void SocialJoin(long playerid, string snid, string snuid, DateTime timestamp)
    {
      logstoragePwLogs.WriteIn("socialjoin", playerid, snid, snuid, timestamp);
    }

    public void SocialMerge(long playerid1, long playerid2, DateTime timestamp)
    {
      logstoragePwLogs.WriteIn("socialmerge", playerid1, playerid2, timestamp);
    }

    public void MonitoringResults(IEnumerable<MonitoringResultInfoBL> results)
    {
      if (results == null) throw new ArgumentNullException("results");
      foreach (var info in results)
      {
        logstorage.WriteIn("monitoring_results", info.Property, info.Counter, info.Value, info.Timestamp);
      }
    }

    public void ClientPings(IEnumerable<ClientPingInfoBL> infos)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      foreach (var i in infos)
        logstoragePwLogs.WriteIn("clientping", i.Auid, i.SrvLocation, i.Ping, i.Timestamp);
    }

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~SocialSessionManager()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          storage.Dispose();
          logstorage.Dispose();
          logstoragePwLogs.Dispose();
        }
        disposed = true;
      }
    }

  }
}