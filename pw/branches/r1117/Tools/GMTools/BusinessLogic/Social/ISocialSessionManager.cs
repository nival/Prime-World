using System;
using System.Collections.Generic;

namespace BusinessLogic.Social
{
  public interface ISocialSessionManager : IDisposable
  {
    bool IsRunning { get; }

    void LogIn (IEnumerable<LoginInfoBL> logins);
    void LogOut(IEnumerable<LoginInfoBL> logins);
    void FactionSelect(IEnumerable<FactionSelectInfoBL> infos);
    void JoinSession(IEnumerable<JoinSessionInfoBL> infos);
    void SessionAwards(IEnumerable<SessionAwardsInfoBL> awards);
    void TalentChange(IEnumerable<TalentChangeInfoBL> infos);
    void UnlockHero(IEnumerable<UnlockHeroInfoBL> unlocks);
    void MoveToBath(IEnumerable<MoveToBathInfoBL> infos);
    void AddIgnore(IEnumerable<AddIgnoreInfoBL> infos);
    void RemoveIgnore(IEnumerable<RemoveIgnoreInfoBL> infos);
    void ResourcesChange(IEnumerable<ResourcesChangeInfoBL> infos);
    void QuestChange(IEnumerable<QuestChangeInfoBL> infos);
    void DynamicQuestChange( IEnumerable<DynamicQuestChangeInfoBL> infos );
    void TournamentQuestChange( IEnumerable<TournamentQuestChangeInfoBL> infos );
    void RatingChange(IEnumerable<RatingChangeInfoBL> infos);
    void GuildCreated(IEnumerable<GuildInfoBL> infos);
    void GuildRenamed(IEnumerable<GuildInfoBL> infos);
    void GuildJoined(IEnumerable<GuildCoreInfoBL> infos);
    void GuildLeaved(IEnumerable<GuildLeaveInfoBL> infos);
    void GuildDisbanded(IEnumerable<GuildCoreInfoBL> infos);
    void GuildShopBuy(IEnumerable<GuildShopBuyInfoBL> infos);
    void GuildSiege(IEnumerable<GuildSiegeInfoBL> infos);
    void GuildDailyStats(IEnumerable<GuildDailyStatsInfoBL> infos);
    void GuildInteraction(IEnumerable<GuildInteractionInfoBL> infos);
    void GuildPointsChange(IEnumerable<GuildPointsChangeInfoBL> infos);
    void RuneExpire(IEnumerable<RuneExpireInfoBL> infos);
    void RuneUnsoulbound(IEnumerable<RuneSoulboundInfoBL> infos);
    void RuneHeroApply(IEnumerable<RuneHeroApplyInfoBL> infos);
    void GWEventAdd(IEnumerable<GWEventInfoBL> infos);
    void GWScoreChange(IEnumerable<GWScoreChangeInfoBL> infos);
    void RuneReplenish(IEnumerable<RuneReplenishInfoBL> infos);
    void RuneRoll(IEnumerable<RuneRollInfoBL> infos);
    void Claim(IEnumerable<ClaimInfoBL> infos);
    void AfterParty(IEnumerable<AfterPartyInfoBL> infos);
    void LeaverPointsChange(IEnumerable<LeaverPointsChangeInfoBL> infos);
    void ReRollShop(IEnumerable<ReRollShopInfoBL> infos);

    void QuestEventStageChange(IEnumerable<QuestEventStagesInfoBL> infos);
    void QuestEventStepChange(IEnumerable<QuestEventStepsInfoBl> infos);

    void GMOperation(IEnumerable<GMOperationInfoBL> infos);
    void GMUserOperation(IEnumerable<GMUserOperationInfoBL> infos);

    // Методы для pw_logs
    void LauncherStart(string hostid, string version, long playerid, string clientip, string geolocation, string locale, DateTime timestamp);
    void LauncherDAction(string action, string hostid, string version, string muid, long playerid, float speed, float avgspeed, float minspeed, int totalpatches,
                         int appliedpatches, float totaldownload, float downloaded, string error, int needclose, string geolocation, string locale, DateTime clienttimestamp, DateTime servertimestamp);
    void LauncherEvents(long playerid, string muid, long eventflags, string locale, DateTime clienttimestamp, DateTime servertimestamp);
    void SocialRegister(string hostid, long playerid, string snid, string snuid, string muid, DateTime timestamp);
    void SocialJoin(long playerid, string snid, string snuid, DateTime timestamp);
    void SocialMerge(long playerid1, long playerid2, DateTime timestamp);

    void ClientPings(IEnumerable<ClientPingInfoBL> infos);

    // Этот метод вообще-то из мониторинга, но пока пусть тут тихонечко в углу постоит
    void MonitoringResults(IEnumerable<MonitoringResultInfoBL> results);
  }
}