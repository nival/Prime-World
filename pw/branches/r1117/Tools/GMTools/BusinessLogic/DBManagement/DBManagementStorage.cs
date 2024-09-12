using System;
using System.Collections.Generic;
using BusinessLogic.Game;
using BusinessLogic.Queuing;
using BusinessLogic.Social;
using log4net;

namespace BusinessLogic.DBManagement
{
  public interface IDBManagementStorage : IDisposable
  {
    bool IsRunning { get; }

    // Game methods
    void WriteSessionStart(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players);
    void WriteSessionResult(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players);
    
    // Social methods
    void WriteSocialLogin(IEnumerable<LoginInfoBL> logins);
    void WriteSocialLogout(IEnumerable<LoginInfoBL> logins);
    void WriteFactionChange(IEnumerable<FactionSelectInfoBL> infos);
    void WriteSessionAwards(IEnumerable<SessionAwardsInfoBL> awards);
    void WriteTalentLog(IEnumerable<TalentChangeInfoBL> infos);
    void WriteCharacterUnlock(IEnumerable<UnlockHeroInfoBL> logins);
    void WriteMovingToBath(IEnumerable<MoveToBathInfoBL> infos);
    void WriteResourceLog(IEnumerable<ResourcesChangeInfoBL> infos);
    void WriteQuestChange(IEnumerable<QuestChangeInfoBL> infos);
    void WriteDynamicQuestChange( IEnumerable<DynamicQuestChangeInfoBL> infos );
    void WriteTournamentQuestChange( IEnumerable<TournamentQuestChangeInfoBL> infos );
    void WriteGuildCreate(IEnumerable<GuildInfoBL> infos);
    void WriteGuildRename(IEnumerable<GuildInfoBL> infos);
    void WriteGuildJoin(IEnumerable<GuildCoreInfoBL> infos);
    void WriteGuildLeave(IEnumerable<GuildLeaveInfoBL> infos);
    void WriteGuildDisband(IEnumerable<GuildCoreInfoBL> infos);
    void WriteGuildShopBuy(IEnumerable<GuildShopBuyInfoBL> infos);
    void WriteGuildSiege(IEnumerable<GuildSiegeInfoBL> infos);
    void WriteGuildDailyStats(IEnumerable<GuildDailyStatsInfoBL> infos);
    void WriteGuildInteraction(IEnumerable<GuildInteractionInfoBL> infos);
    void WriteGuildPointsChange(IEnumerable<GuildPointsChangeInfoBL> infos);
    void WriteGMOperation(IEnumerable<GMOperationInfoBL> infos);
    void WriteGMUserOperation(IEnumerable<GMUserOperationInfoBL> infos);
    void WriteAfterParty(IEnumerable<AfterPartyInfoBL> infos);
    void WriteLeaverPointsLog(IEnumerable<LeaverPointsChangeInfoBL> infos);
    void WriteReRollShopLog(IEnumerable<ReRollShopInfoBL> infos);

    // Matchmaking methods
    void WriteMMakingCancelled(MMakingPlayerInfo mmplayer, DateTime timestamp);
    void WriteMMakingSession(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers);

    // Client methods
    void WriteSessionRelayInfo(long persistentId, long playerid, string relayAddress);
  }

  public class DBManagementStorage : IDBManagementStorage
  {
    private static ILog _log = LogManager.GetLogger(typeof (DBManagementStorage));

    private readonly ITaskExecutor executor;

    public DBManagementStorage(ITaskExecutor executor)
    {
      this.executor = executor;
      this.executor.Run();
    }

    public bool IsRunning
    {
      get { return executor.IsRunning; }
    }

    public void WriteSessionStart(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players)
    {
      var task = new SessionStartTask(persistentId, map, server, serveraddress, cluster, sessionType, timestamp, players);
      _log.DebugFormat("Enqueuing new SessionStartTask for session(persistentId={0})", persistentId);
      executor.EnqueueTask(task);
    }

    public void WriteSessionResult(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players)
    {
      var task = new SessionResultTask(persistentId, result, sideWon, surrendervote, timestamp, players);
      _log.DebugFormat("Enqueuing new SessionResultTask for session(persistentId={0})", persistentId);
      executor.EnqueueTask(task);
    }

    public void WriteSocialLogin(IEnumerable<LoginInfoBL> logins)
    {
      _log.Debug("Enqueuing new SocialLoginTask");
      var task = new SocialLoginTask(logins);
      executor.EnqueueTask(task);
    }

    public void WriteSocialLogout(IEnumerable<LoginInfoBL> logins)
    {
      _log.Debug("Enqueuing new SocialLogoutTask");
      var task = new SocialLogoutTask(logins);
      executor.EnqueueTask(task);
    }

    public void WriteFactionChange(IEnumerable<FactionSelectInfoBL> infos)
    {
      _log.Debug("Enqueuing new FactionChangeTask");
      var task = new FactionChangeTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteSessionAwards(IEnumerable<SessionAwardsInfoBL> awards)
    {
      _log.Debug("Enqueuing new SessionAwardsTask");
      var task = new SessionAwardsTask(awards);
      executor.EnqueueTask(task);
    }

    public void WriteTalentLog(IEnumerable<TalentChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new TalentLogTask");
      var task = new TalentLogTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteCharacterUnlock(IEnumerable<UnlockHeroInfoBL> logins)
    {
      _log.Debug("Enqueuing new CharacterUnlockTask");
      var task = new CharacterUnlockTask(logins);
      executor.EnqueueTask(task);
    }

    public void WriteMovingToBath(IEnumerable<MoveToBathInfoBL> infos)
    {
      _log.Debug("Enqueuing new MoveToBathTask");
      var task = new MoveToBathTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteResourceLog(IEnumerable<ResourcesChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new ResourcesLogTask");
      var task = new ResourcesLogTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteQuestChange(IEnumerable<QuestChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new QuestChangeTask");
      var task = new QuestChangeTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteDynamicQuestChange(IEnumerable<DynamicQuestChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new DynamicQuestChangeTask");
      var task = new DynamicQuestChangeTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteTournamentQuestChange( IEnumerable<TournamentQuestChangeInfoBL> infos )
    {
      _log.Debug( "Enqueuing new TournamentQuestChangeTask" );
      var task = new TournamentQuestChangeTask( infos );
      executor.EnqueueTask( task );
    }

    public void WriteGuildCreate(IEnumerable<GuildInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildCreateTask");
      var task = new GuildCreateTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildRename(IEnumerable<GuildInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildRenameTask");
      var task = new GuildRenameTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildJoin(IEnumerable<GuildCoreInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildJoinTask");
      var task = new GuildJoinTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildLeave(IEnumerable<GuildLeaveInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildLeaveTask");
      var task = new GuildLeaveTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildDisband(IEnumerable<GuildCoreInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildDisbandTask");
      var task = new GuildDisbandTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildShopBuy(IEnumerable<GuildShopBuyInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildShopBuyTask");
      var task = new GuildShopBuyTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildSiege(IEnumerable<GuildSiegeInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildSiegeTask");
      var task = new GuildSiegeTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildDailyStats(IEnumerable<GuildDailyStatsInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildDailyStatsTask");
      var task = new GuildDailyStatsTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildInteraction(IEnumerable<GuildInteractionInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildInteractionTask");
      var task = new GuildInteractionTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGuildPointsChange(IEnumerable<GuildPointsChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new GuildPointsChangeTask");
      var task = new GuildPointsChangeTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGMOperation(IEnumerable<GMOperationInfoBL> infos)
    {
      _log.Debug("Enqueuing new GMOperationTask");
      var task = new GMOperationTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteGMUserOperation(IEnumerable<GMUserOperationInfoBL> infos)
    {
      _log.Debug("Enqueuing new GMUserOperationTask");
      var task = new GMUserOperationTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteAfterParty(IEnumerable<AfterPartyInfoBL> infos)
    {
      _log.Debug("Enqueuing new AfterPartyTask");
      var task = new AfterPartyTask(infos);
      executor.EnqueueTask(task);
    }

    public void WriteLeaverPointsLog(IEnumerable<LeaverPointsChangeInfoBL> infos)
    {
      _log.Debug("Enqueuing new LeaverPointsChangeTask");
      var task = new LeaverPointsChangeTask(infos);
      executor.EnqueueTask(task);
    }
    
    public void WriteReRollShopLog(IEnumerable<ReRollShopInfoBL> infos)
    {
        _log.Debug("Enqueuing new ReRollShopTask");
        var task = new ReRollShopTask(infos);
        executor.EnqueueTask(task);
    }

    public void WriteMMakingCancelled(MMakingPlayerInfo mmplayer, DateTime timestamp)
    {
      _log.Debug("Enqueuing new MMakingPlayerTask");
      var task = new MMakingPlayerTask(mmplayer, timestamp);
      executor.EnqueueTask(task);
    }

    public void WriteMMakingSession(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers)
    {
      _log.Debug("Enqueuing new MMakingPlayerTask");
      var task = new MMakingSessionTask(persistentId, status, manoeuvresFaction, basket, map, timestamp, mmplayers);
      executor.EnqueueTask(task);
    }

    public void WriteSessionRelayInfo(long persistentId, long playerid, string relayAddress)
    {
      if (String.IsNullOrEmpty(relayAddress))
      {
        _log.WarnFormat("Empty relayAddress for (persistentId={0},playerId={1}), SessionRelayInfoTask will be ignored", persistentId, playerid);
        return;
      }
      _log.Debug("Enqueuing new SessionRelayInfoTask");
      var task = new SessionRelayInfoTask(persistentId, playerid, relayAddress);
      executor.EnqueueTask(task);
    }

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~DBManagementStorage()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          executor.Stop();
        }
        disposed = true;
      }
    }
  }
}