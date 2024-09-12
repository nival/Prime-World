using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.Social;
using DAL.Entities;
using KontagentLib;
using log4net;
using StatisticCore.Thrift;

namespace StatisticService.ThriftImpls
{
  public class StatisticServiceImplementation : StatisticCore.Thrift.StatisticService.Iface
  {
    private static ILog _log = LogManager.GetLogger(typeof(StatisticServiceImplementation));

    private ISocialSessionManager _socialSessionManager;
    private IKontagentManager kontagentManager;

    enum Source
    {
      Session,
      UnlockHero,
      MoveToBath,
      FactionChange
    }


    public StatisticServiceImplementation(ISocialSessionManager manager, IKontagentManager km)
    {
      _socialSessionManager = manager;
      kontagentManager = km;
    }

    /// <summary>
    /// ¬озвращает значение DateTime.UtcNow, округленное до секунд (т.е. без миллисекунд)
    /// </summary>
    private DateTime CurrentDateTime
    {
      get
      {
        var now = DateTime.UtcNow;
        return new DateTime(now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);
      }
    }

    #region Iface

    public void LoginUsers(List<LoginInfo> logins)
    {
      try
      {
        _log.DebugFormat("{0} players are logged in: ({1})",
                         logins.Count, String.Join(",", logins.Select(l => l.ToString()).ToArray()));

        _socialSessionManager.LogIn(logins.Select(l => l.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var login in logins)
          {
            int faction = login.Faction.ToIntFaction();
            kontagentManager.CastleLogin(login.Auid, faction);
          }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LoginUsers", ex);
      }
    }

    public void LogoutUsers(List<LoginInfo> logins)
    {
      try
      {
        _log.DebugFormat("{0} players are logged out: ({1})",
                         logins.Count, String.Join(",", logins.Select(l => l.ToString()).ToArray()));

        _socialSessionManager.LogOut(logins.Select(l => l.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LoginUsers", ex);
      }
    }

    public void FactionSelect(List<FactionSelectInfo> infos)
    {
      try
      {
        _log.DebugFormat("Social event FactionSelect, infos = List[{0}]({1})",
                        infos.Count, String.Join(", ", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.FactionSelect(infos.Select(l => l.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos)
          {
            //kontagentManager.FactionSelected(info.Auid, info.Newfaction.ToIntFaction());
            // если смена платна€, то отправка в контагент еще и информации о ресурсах
            if (info.Rchange.Gold != 0)
              kontagentManager.ResourceChange(info.Auid, Source.FactionChange.ToString().ToLower(), false,
                                              -info.Rchange.Gold, -info.Rchange.Silver, -info.Rchange.Perl, -info.Rchange.RedPerl,
                                              -info.Rchange.Resource1, -info.Rchange.Resource2, -info.Rchange.Resource3, -info.Rchange.Shard, info.Rchange.Currencies);
          }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in FactionSelect", ex);
      }
    }

    public void MoveTalentToSet(List<MoveTalentInfo> infos)
    {
      _log.WarnFormat("NOT IMPLEMENTED: social event MoveTalentToSet, infos = List({0})",
                      String.Join(", ", infos.Select(i => i.ToString()).ToArray()));
    }

    public void MoveTalentFromSet(List<MoveTalentInfo> infos)
    {
      _log.WarnFormat("NOT IMPLEMENTED: social event MoveTalentFromSet, infos = List({0})",
                      String.Join(", ", infos.Select(i => i.ToString()).ToArray()));
    }

    public void UnlockHero(List<UnlockHeroInfo> infos)
    {
      try
      {
        _log.DebugFormat("{0} heroes was unlocked: ({1})",
                         infos.Count, String.Join(",", infos.Select(i => String.Format("UnlockHeroInfo(userid={0},heroid={1})", i.Auid,i.Heroid)).ToArray()));

        _socialSessionManager.UnlockHero(infos.Select(i => i.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos.Where(i => i.Rchange.Gold != 0))
            kontagentManager.ResourceChange(info.Auid, Source.UnlockHero.ToString().ToLower(), false,
                                            -info.Rchange.Gold, -info.Rchange.Silver, -info.Rchange.Perl, -info.Rchange.RedPerl,
                                            -info.Rchange.Resource1, -info.Rchange.Resource2, -info.Rchange.Resource3, -info.Rchange.Shard, info.Rchange.Currencies);
        
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LoginUsers", ex);
      }
    }

    public void MoveHeroToBath(List<MoveToBathInfo> infos)
    {
      try
      {
        _log.DebugFormat("{0} heroes has moved to bath: ({1})",
                         infos.Count, String.Join(",", infos.Select(i => String.Format("MoveToBathInfo(userid={0},heroid={1})", i.Auid, i.Heroid)).ToArray()));

        _socialSessionManager.MoveToBath(infos.Select(i => i.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos.Where(i => i.Rchange.Gold != 0))
            kontagentManager.ResourceChange(info.Auid, Source.MoveToBath.ToString().ToLower(), false,
                                            -info.Rchange.Gold, -info.Rchange.Silver, -info.Rchange.Perl, -info.Rchange.RedPerl,
                                            -info.Rchange.Resource1, -info.Rchange.Resource2, -info.Rchange.Resource3, -info.Rchange.Shard, info.Rchange.Currencies);
        
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LoginUsers", ex);
      }
    }

    public void ResourcesChange(List<ResourcesChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event ResourcesChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.ResourcesChange(infos.Select(i => i.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos.Where(i => i.Rchange.Gold != 0))
            kontagentManager.ResourceChange(info.Auid, info.Source.ToString().ToLower() + (String.IsNullOrEmpty(info.Buildingname) ? String.Empty : "_" + info.Buildingname.ToLower()), info.Gain,
                                            ( info.Gain ? 1 : -1 ) * info.Rchange.Gold, ( info.Gain ? 1 : -1 ) * info.Rchange.Silver, ( info.Gain ? 1 : -1 ) * info.Rchange.Perl, ( info.Gain ? 1 : -1 ) * info.Rchange.RedPerl,
                                            (info.Gain ? 1 : -1) * info.Rchange.Resource1, (info.Gain ? 1 : -1) * info.Rchange.Resource2, (info.Gain ? 1 : -1) * info.Rchange.Resource3, (info.Gain ? 1 : -1) * info.Rchange.Shard, info.Rchange.Currencies);
      }
      catch (Exception ex)
      {
        _log.Error("Exception in ResourcesChange", ex);
      }
    }

    public void QuestChange(List<QuestChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event QuestChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.QuestChange(infos.Select(i => i.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos)
            kontagentManager.QuestChange(info.Auid, (int) info.Reason, info.Questid, info.Timestamp);
      }
      catch (Exception ex)
      {
        _log.Error("Exception in QuestChange", ex);
      }
    }

    public void DynamicQuestChange(List<DynamicQuestChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event DynamicQuestChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.DynamicQuestChange(infos.Select(i => i.ToBLEntity()));

      }
      catch (Exception ex)
      {
        _log.Error("Exception in DynamicQuestChange", ex);
      }
    }

    public void TournamentQuestChange( List<TournamentQuestChangeInfo> infos )
    {
      try
      {
        _log.DebugFormat( "social event TournamentQuestChange: infos = List[{0}]({1})",
                         infos.Count, String.Join( ",", infos.Select( i => i.ToString() ).ToArray() ) );

        _socialSessionManager.TournamentQuestChange( infos.Select( i => i.ToBLEntity() ) );

      }
      catch ( Exception ex )
      {
        _log.Error( "Exception in TournamentQuestChange", ex );
      }
    }

    public void TutorialStateChange(List<TutorialStateChangeInfo> infos)
    {
      _log.WarnFormat("NOT IMPLEMENTED: social event TutorialStateChange, infos = List({0})",
                      String.Join(", ", infos.Select(i => i.ToString()).ToArray()));
    }

    public void TalentChange(List<TalentChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event TalentChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.TalentChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in TalentChange", ex);
      }
    }

    public void JoinPvpSession(List<JoinSessionInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event JoinPvpSession, infos = List[{0}]({1})",
                         infos.Count, String.Join(", ", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.JoinSession(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in JoinPvpSession", ex);
      }
    }

    public void GiveSessionAwards(List<SessionAwardsInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event GiveSessionAwards: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.SessionAwards(infos.Select(i => i.ToBLEntity()));

        if (kontagentManager != null)
          foreach (var info in infos.Where(i => i.Rchange.Gold != 0))
            kontagentManager.ResourceChange(info.Auid, Source.Session.ToString().ToLower(), true,
                                            info.Rchange.Gold, info.Rchange.Silver, info.Rchange.Perl, info.Rchange.RedPerl,
                                            info.Rchange.Resource1, info.Rchange.Resource2, info.Rchange.Resource3, info.Rchange.Shard, info.Rchange.Currencies);
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GiveSessionAwards", ex);
      }
    }

    public void RatingChange(List<RatingChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social event RatingChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));

        _socialSessionManager.RatingChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in RatingChange", ex);
      }
    }

    public void HeroLevelChange(List<HeroLevelChangeInfo> infos)
    {
      try
      {
        _log.WarnFormat("NOT IMPLEMENTED: event HeroLevelChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in HeroLevelChange", ex);
      }
    }

    public void HeroRankChange(List<HeroRankChangeInfo> infos)
    {
      try
      {
        _log.WarnFormat("NOT IMPLEMENTED: event HeroRankChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in HeroRankChange", ex);
      }
    }

    public void CastleLevelChange(List<CastleLevelChangeInfo> infos)
    {
      try
      {
        _log.WarnFormat("NOT IMPLEMENTED: event CastleLevelChange: infos = List[{0}]({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in CastleLevelChange", ex);
      }
    }

    public void AfterParty(List<AfterPartyInfo> infos)
    {
      try
      {
        _log.DebugFormat("event AfterParty: infos = List[{0}]({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.AfterParty(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in AfterParty", ex);
      }
    }

    public void LeaverPointsChange(List<LeaverPointsChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("event LeaverPointsChange: infos = List[{0}]({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.LeaverPointsChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LeaverPointsChange", ex);
      }
    }
    
      public void ReRollShop(List<ReRollShopInfo> infos)
    {
        try
        {
            _log.DebugFormat("event ReRollShop: infos = List[{0}]({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
            _socialSessionManager.ReRollShop(infos.Select(i => i.ToBLEntity()));
        }
        catch (Exception ex)
        {
            _log.Error("Exception in ReRollShop", ex);
        }
    }


    public void ChatMessages(List<ChatMessageInfo> infos)
    {
      try
      {
        _log.WarnFormat("NOT SUPPORTED: Received {0} chat messages", infos.Count);
      }
      catch (Exception ex)
      {
        _log.Error("Exception in ChatMessages", ex);
      }
    }

    public void UserClaims(List<ClaimInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events ClaimInfo[{0}]: List({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.Claim(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void GMEditUser(List<GMEditFieldInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GMEditUser[{0}]: List({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GMOperation(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GMEditUser", ex);
      }
    }

    public void GMUnlockHero(List<GMHeroActionInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GMUnlockHero[{0}]: List({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GMOperation(infos.Select(i => i.ToBLEntity("HeroUnlock")));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GMUnlockHero", ex);
      }
    }

    public void GMLockHero(List<GMHeroActionInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GMLockHero[{0}]: List({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GMOperation(infos.Select(i => i.ToBLEntity("HeroLock")));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GMLockHero", ex);
      }
    }

    public void GMOperation(List<GMOperationInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GMOperation[{0}]: List({1})", infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GMOperation(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GMOperation", ex);
      }
    }

    public void GMUserOperation(List<GMUserOperationInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GMUserOperation[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GMUserOperation(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void MonitoringResults(List<MonitoringResultInfo> results)
    {
      if (results == null)
      {
        _log.Error("Monitoring results list is null");
        return;
      }

      try
      {
        _log.DebugFormat("received a list of {0} monitoring results", results.Count);
        _socialSessionManager.MonitoringResults(results.Select(r => r.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GMDeleteTalent", ex);
      }
    }

    public void ClientPings(List<ClientPingInfo> infos)
    {
      try
      {
        _log.DebugFormat("client pings [{0}]", infos.Count);
        _socialSessionManager.ClientPings(infos.Select(m => m.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in ClientPings", ex);
      }
    }

    public void AddIgnore(List<AddIgnoreInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events AddIgnore[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.AddIgnore(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in AddIgnore", ex);
      }
    }

    public void RemoveIgnore(List<RemoveIgnoreInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events RemoveIgnore[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.RemoveIgnore(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in RemoveIgnore", ex);
      }
    }

    public void LauncherStart(List<LauncherInfo> infos)
    {
      try
      {
        _log.DebugFormat("launcher events LauncherStart[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          _socialSessionManager.LauncherStart(i.Hostid, i.Version, i.Auid, i.Ip, i.Location, i.Locale, CurrentDateTime);
          if (kontagentManager != null)
            kontagentManager.LauncherStart(i.Auid, i.Hostid, i.Version);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LauncherStart", ex);
      }
    }

    public void LauncherEvents(List<LauncherEventsInfo> infos)
    {
      try
      {
        _log.DebugFormat("launcher events LauncherEvents[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          _socialSessionManager.LauncherEvents(i.Auid, i.Muid, i.Bitmask, i.Locale, EntitiesConvertor.FromUnixTimestamp(i.Timestamp), CurrentDateTime);
          if (kontagentManager != null)
            kontagentManager.LauncherEvents(i.Auid, i.Muid, i.Bitmask);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in LauncherEvents", ex);
      }
    }

    public void LauncherDActions(List<LauncherDActionsInfo> infos)
    {
      try
      {
        _log.DebugFormat("launcher actions LauncherDActions[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          long playerid;
          if (!Int64.TryParse(i.Auid, out playerid))
          {
            _log.Warn("invalid auid = " + i.Auid);
            continue;
          }
          _socialSessionManager.LauncherDAction(i.Action, i.Hostid, i.Version, i.Muid, playerid, (float) i.Speed,(float) i.Avg_speed, (float) i.Min_speed,
                                                i.Total_patches, i.Applied_patches, (float) i.Total_download,(float) i.Downloaded, i.Error, i.Need_close, i.Geolocation, i.Locale,
                                                EntitiesConvertor.FromUnixTimestamp(i.Timestamp), EntitiesConvertor.FromUnixTimestamp(i.Server_timestamp));
        }
      }
      catch (Exception ex)
      {
        _log.Error("UNEXPECTED EXCEPTION", ex);
      }
    }

    public void SocialRegister(List<SocialRegisterInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events SocialRegister[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          long playerid;
          if (!Int64.TryParse(i.Auid, out playerid))
          {
            _log.Warn("invalid auid = " + i.Auid);
            continue;
          }
          _socialSessionManager.SocialRegister(i.Hostid, playerid, i.Snid, i.Snuid, i.Muid, CurrentDateTime);
          if (kontagentManager != null)
            kontagentManager.FirstLogin(playerid, i.Muid);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in SocialRegister", ex);
      }
    }

    public void SocialJoin(List<SocialJoinInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events SocialJoin[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          long playerid;
          if (!Int64.TryParse(i.Auid, out playerid))
          {
            _log.Warn("invalid auid = " + i.Auid);
            continue;
          }
          _socialSessionManager.SocialJoin(playerid, i.Snid, i.Snuid, CurrentDateTime);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in SocialJoin", ex);
      }
    }

    public void SocialMerge(List<SocialMergeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events SocialMerge[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        foreach (var i in infos)
        {
          long playerid1, playerid2;
          if (!Int64.TryParse(i.Auid1, out playerid1) || !Int64.TryParse(i.Auid2, out playerid2))
          {
            _log.WarnFormat("invalid auids {0}, {1}", i.Auid1, i.Auid2);
            continue;
          }
          _socialSessionManager.SocialMerge(playerid1, playerid2, CurrentDateTime);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Exception in SocialMerge", ex);
      }
    }

    public void GuildCreated(List<GuildInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildCreated[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildCreated(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GuildCreated", ex);
      }
    }

    public void GuildRenamed(List<GuildInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildRenamed[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildRenamed(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GuildRenamed", ex);
      }
    }

    public void GuildJoined(List<GuildCoreInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildJoined[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildJoined(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GuildJoined", ex);
      }
    }

    public void GuildLeaved(List<GuildLeaveInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildLeaved[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildLeaved(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GuildLeaved", ex);
      }
    }

    public void GuildDisbanded(List<GuildCoreInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildDisbanded[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildDisbanded(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error("Exception in GuildDisbanded", ex);
      }
    }

    public void GuildShopBuy(List<GuildShopBuyInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildShopBuy[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildShopBuy(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void GuildSiege(List<GuildSiegeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildSiege[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildSiege(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void GuildDailyStats(List<GuildDailyStatsInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildDailyStats[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildDailyStats(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void GuildInteraction(List<GuildInteractionInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildInteraction[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildInteraction(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void GuildPointsChange(List<GuildPointsChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GuildPointsChange[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GuildPointsChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void RuneExpire(List<RuneExpireInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events RuneExpire[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.RuneExpire(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void RuneUnsoulbound(List<RuneSoulboundInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events RuneUnsoulbound[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.RuneUnsoulbound(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void RuneReplenish(List<RuneReplenishInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events RuneReplenish[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.RuneReplenish(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

      public void RuneHeroApply(List<RuneHeroApplyInfo> infos)
      {
          try
          {
              _log.DebugFormat("social events RuneHeroApply[{0}]: List({1})",
               infos.Count, string.Join(",", infos.Select(i => i.ToString()).ToArray()));
              _socialSessionManager.RuneHeroApply(infos.Select(i => i.ToBLEntity()));
          }
          catch (Exception ex)
          {
              _log.Error(ex);
          }
        }

        public void GWEventAdd(List<GWEventInfo> infos)
        {
            try
            {
                _log.DebugFormat("social events GWEventAdd[{0}]: List({1})",
                    infos.Count, string.Join(",", infos.Select(i => i.ToString()).ToArray()));
                _socialSessionManager.GWEventAdd(infos.Select(i => i.ToBLEntity()));
            }
            catch (Exception ex)
            {
                _log.Error(ex);
            }
        }

    public void GWScoreChange(List<GWScoreChangeInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events GWScoreChange[{0}]: List({1})",
          infos.Count, string.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.GWScoreChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void QuestEventStageChange(List<QuestEventsStagesInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events QuestEventStageChange[{0}]: List({1})",
          infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.QuestEventStageChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    public void QuestEventStateChange(List<QuestEventsStatesInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events QuestEventStateChange[{0}]: List({1})",
          infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.QuestEventStepChange(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

      public void RuneRoll(List<RuneRollInfo> infos)
    {
      try
      {
        _log.DebugFormat("social events RuneRoll[{0}]: List({1})",
                         infos.Count, String.Join(",", infos.Select(i => i.ToString()).ToArray()));
        _socialSessionManager.RuneRoll(infos.Select(i => i.ToBLEntity()));
      }
      catch (Exception ex)
      {
        _log.Error(ex);
      }
    }

    #endregion
  }

  /// <summary>
  /// We are replacing excplicit cast by extension methods, because thrift classes are generated
  /// </summary>
  internal static class EntitiesConvertor
  {
    internal static LoginInfoBL ToBLEntity(this LoginInfo info)
    {
      return new LoginInfoBL
               {
                 UserId = info.Auid,
                 Login = info.Nick,
                 Faction = info.Faction.ToIntFaction(),
                 Ip = info.Ip,
                 Cluster = info.Cluster,
                 Server = info.Server,
                 IsDeveloper = info.Isdeveloper,
                 Locale = info.Locale,
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 GuildId = info.Guildid,
                 GuildShortName = info.Guildshortname,
                 GuildFullName = info.Guildfullname,
                 LeaverPoints = info.Leaverpoints,
                 IsLeaver = info.Isleaver
               };
    }

    internal static ResourceTableBL ToBLEntity(this ResourceTable info)
    {
        string keyCurrency = "";
        int valCurrency = 0;

        if (info.Currencies != null)
        {
            var currencies = info.Currencies.ToList();
            if (currencies.Count != 0)
            {
                keyCurrency = currencies.First().Key;
                valCurrency = currencies.First().Value;
            }
        }
        
      
      return new ResourceTableBL
               {
                 Gold = info.Gold,
                 Silver = info.Silver,
                 Perl = info.Perl,
                 RedPerl = info.RedPerl,
                 Population = info.Population,
                 Resource1 = info.Resource1,
                 Resource2 = info.Resource2,
                 Resource3 = info.Resource3,
                 Shard = info.Shard,
                 CurrencyName = keyCurrency,
                 CurrencyValue = valCurrency
      };
    }

    internal static FactionSelectInfoBL ToBLEntity(this FactionSelectInfo info)
    {
      return new FactionSelectInfoBL
               {
                 UserId = info.Auid,
                 OldFaction = info.Oldfaction.ToIntFaction(),
                 NewFaction = info.Newfaction.ToIntFaction(),
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static UnlockHeroInfoBL ToBLEntity(this UnlockHeroInfo info)
    {
      return new UnlockHeroInfoBL
               {
                 UserId = info.Auid,
                 HeroId = info.Heroid,
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static MoveToBathInfoBL ToBLEntity(this MoveToBathInfo info)
    {
      return new MoveToBathInfoBL
               {
                 UserId = info.Auid,
                 HeroId = info.Heroid,
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Minutes = info.Minutes,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static SessionAwardsInfoBL ToBLEntity(this SessionAwardsInfo info)
    {
      var leaverPointsChange = info.Leaverpointschange.ToBLEntity();
      leaverPointsChange.PersistentId = info.Sessionpersistentid;

      return new SessionAwardsInfoBL
               {
                 Auid = info.Auid,
                 SessionPersistentId = info.Sessionpersistentid,
                 Nick = info.Nick,
                 HeroId = info.Heroid,
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 Talents = info.Talents == null || info.Talents.Count == 0
                             ? null
                             : info.Talents.Select(t => new SessionAwardsInfoBL.TalentInfoBL { Id = t.ClassId, InstanceId = t.InstanceId }).ToList(),
                 GuildBuffs = info.Appliedbuffs,
                 GuildPointsChange = info.Guildpointschange,
                 GuildPointsTotal = info.Guildpointstotal,
                 PlayerPointsChange = info.Rchange.CWPoints_Player,
                 PlayerPointsTotal = info.Rtotal.CWPoints_Player,
                 LeaverPointsChange = leaverPointsChange
               };
    }

    internal static LeaverPointsChangeInfoBL ToBLEntity(this LeaverPointsChangeInfo info)
    {
      return new LeaverPointsChangeInfoBL
             {
               Auid = info.Auid,
               PersistentId = null,
               Type = info.Type,
               LeaverPointsChange = info.Leaverpointschange,
               LeaverPointsTotal = info.Leaverpointstotal,
               IsLeaverChanged = info.Isleaverchanged,
               IsLeaver = info.Isleaver,
               IsBadBehaviour = info.Isbadbehaviour,
               Timestamp = FromUnixTimestamp(info.Timestamp)
             };
    }


    internal static ReRollShopInfoBL ToBLEntity(this ReRollShopInfo info)
    {
        return new ReRollShopInfoBL
        {
            ItemId = info.ItemId,
            Auid = info.Auid,
            ItemGroup = info.ItemGroup,
            ItemPrice = info.ItemPrice,
            ItemPriceType = info.ItemPriceType.ToString().ToLower(),
            RerollCount = info.RerollCount,
            SlotType = info.SlotType,
            Timestamp = FromUnixTimestamp(info.Timestamp),
        };
    }


    internal static TalentChangeInfoBL ToBLEntity(this TalentChangeInfo info)
    {
      return new TalentChangeInfoBL
               {
                 Auid = info.Auid,
                 Operation = info.Operation.ToString().ToLower(),
                 Data = info.Data,
                 TalentId = info.Talent.ClassId,
                 TalentInstanceId = info.Talent.InstanceId,
                 BoundHero = info.Talent.BoundHeroClassId,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static ResourcesChangeInfoBL ToBLEntity(this ResourcesChangeInfo info)
    {
      return new ResourcesChangeInfoBL
               {
                 Auid = info.Auid,
                 Gain = info.Gain,
                 Source = info.Source.ToString().ToLower(),
                 BuildingName = string.IsNullOrEmpty(info.Buildingname) ? null : info.Buildingname.ToLower(),
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static MonitoringResultInfoBL ToBLEntity(this MonitoringResultInfo info)
    {
      return new MonitoringResultInfoBL
               {
                 Property = info.Property,
                 Counter = info.Counter,
                 Value = info.Value,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static AddIgnoreInfoBL ToBLEntity(this AddIgnoreInfo info)
    {
      return new AddIgnoreInfoBL
               {
                 Auid = info.Auid,
                 Ignoreauid = info.Ignoreauid,
                 Reason = info.Reason,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static RemoveIgnoreInfoBL ToBLEntity(this RemoveIgnoreInfo info)
    {
      return new RemoveIgnoreInfoBL
               {
                 Auid = info.Auid,
                 Ignoreauid = info.Ignoreauid,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static QuestChangeInfoBL ToBLEntity(this QuestChangeInfo info)
    {
      return new QuestChangeInfoBL
               {
                 Auid = info.Auid,
                 QuestId = info.Questid,
                 Reason = (int)info.Reason,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static DynamicQuestChangeInfoBL ToBLEntity(this DynamicQuestChangeInfo info)
    {
      return new DynamicQuestChangeInfoBL
               {
                 Auid = info.Auid,
                 QuestIndex = info.Questindex,
                 QuestName = info.Questname,
                 Reason = (int)info.Reason,
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 Alternativeline = info.Alternativeline,

               };
    }

    internal static TournamentQuestChangeInfoBL ToBLEntity( this TournamentQuestChangeInfo info )
    {
      return new TournamentQuestChangeInfoBL
      {
        Auid = info.Auid,
        QuestIndex = info.Questindex,
        QuestName = info.Questname,
        Reason = (int)info.Reason,
        Timestamp = FromUnixTimestamp( info.Timestamp ),
        Alternativeline = info.Alternativeline,

      };
    }

    internal static RatingChangeInfoBL ToBLEntity(this RatingChangeInfo info)
    {
      return new RatingChangeInfoBL
               {
                 Type = (DAL.Entities.RatingType) info.Type,
                 Auid = info.Auid,
                 HeroId = info.Heroid,
                 SessionPersistentId = info.Sessionpersistentid,
                 RatingInc = (int) info.Rating_inc,
                 RatingNew = (int) info.Rating_new,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static JoinSessionInfoBL ToBLEntity(this JoinSessionInfo info)
    {
      return new JoinSessionInfoBL
               {
                 Auid = info.Auid,
                 HeroId = info.Heroid,
                 SessionPersistentId = info.Sessionpersistentid,
                 TalentSet = info.Talentset,
                 GuildBuffs = info.Guildbuffs,
                 GuildwarEventPass = info.Guildwareventpass,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GuildInfoBL ToBLEntity(this GuildInfo info)
    {
      return new GuildInfoBL
               {
                 GuildId = info.CoreInfo.Guildid,
                 Auid = info.CoreInfo.Auid,
                 ShortName = info.Shortname,
                 FullName = info.Fullname,
                 RChange = info.Rchange.ToBLEntity(),
                 RTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.CoreInfo.Timestamp)
               };
    }

    internal static GuildCoreInfoBL ToBLEntity(this GuildCoreInfo info)
    {
      return new GuildCoreInfoBL
               {
                 GuildId = info.Guildid,
                 Auid = info.Auid,
                 Members = info.Guildmembers,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GuildLeaveInfoBL ToBLEntity(this GuildLeaveInfo info)
    {
      return new GuildLeaveInfoBL
               {
                 GuildId = info.CoreInfo.Guildid,
                 Auid = info.CoreInfo.Auid,
                 Members = info.CoreInfo.Guildmembers,
                 Kicked = info.Kicked,
                 Timestamp = FromUnixTimestamp(info.CoreInfo.Timestamp)
               };
    }

    internal static ClientPingInfoBL ToBLEntity(this ClientPingInfo info)
    {
      return new ClientPingInfoBL
               {
                 Auid = info.Auid,
                 SrvLocation = info.Location,
                 Ping = info.MsecPing,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static RuneReplenishInfoBL ToBLEntity(this RuneReplenishInfo info)
    {
      return new RuneReplenishInfoBL
               {
                 Auid = info.Auid,
                 RuneId = info.Rune,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static RuneRollInfoBL ToBLEntity(this RuneRollInfo info)
    {
      return new RuneRollInfoBL
               {
                 Auid = info.Auid,
                 Source = info.Source.ToString(),
                 SessionPersistentId = info.Sessionpersistentid,
                 RuneId = info.Rune,
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 RunesCountOld = info.Runescountold,
                 RunesCountNew = info.Runescountnew,
               };
    }

    internal static RuneSoulboundInfoBL ToBLEntity(this RuneSoulboundInfo info)
    {
      return new RuneSoulboundInfoBL
               {
                 Auid = info.Auid,
                 RuneId = info.Rune,
                 TalentId = info.Talent,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static RuneHeroApplyInfoBL ToBLEntity(this RuneHeroApplyInfo info)
    {
      return new RuneHeroApplyInfoBL
      {
                 Auid = info.Auid,
                 RuneId = info.Rune,
                 Hero = info.Hero,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

      internal static GWEventInfoBL ToBLEntity(this GWEventInfo info)
      {
          return new GWEventInfoBL
          {
              enabled = info.Enabled,
              eventidx = info.Eventidx,
              endTime = FromUnixTimestamp(info.Endtime),
              limit = info.Limit,
              mongoId = info.Mongoid,
              points = info.Points
          };
      }

    internal static GWScoreChangeInfoBL ToBLEntity(this GWScoreChangeInfo info)
    {
      return new GWScoreChangeInfoBL
      {
        auid = info.Auid,
        gweventmid = info.Gweventmid,
        guildid = info.Guildid,
        lastpoints = info.Lastpoints,
        currentpoints = info.Currentpoints,
        timestamp = FromUnixTimestamp(info.Timestamp)
      };
    }

    internal static QuestEventStagesInfoBL ToBLEntity(this QuestEventsStagesInfo info)
    {
      return new QuestEventStagesInfoBL
      {
        Auid = info.Auid,
        ToStageChange = info.Tostagechange,
        Timestamp = FromUnixTimestamp(info.Timestamp)
      };
    }

    internal static QuestEventStepsInfoBl ToBLEntity(this QuestEventsStatesInfo info)
    {
      return new QuestEventStepsInfoBl
      {
        Auid = info.Auid,
        ToStepChange = info.Tostepschange,
        Stage = info.Stage,
        TimeStamp = FromUnixTimestamp(info.Timestamp)
      };
    }

    internal static RuneExpireInfoBL ToBLEntity(this RuneExpireInfo info)
    {
      return new RuneExpireInfoBL
               {
                 Auid = info.Auid,
                 RuneId = info.Rune,
                 BonusLeft = info.BonusLeft,
                 TransactionsLeft = info.TransactionsLeft,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static ClaimInfoBL ToBLEntity(this ClaimInfo info)
    {
      return new ClaimInfoBL
               {
                 FromAuid = info.FromAuid,
                 ToAuid = info.ToAuid,
                 Source = info.Source,
                 Category = info.Category,
                 Locale = info.Locale,
                 Muid = info.Muid,
                 Comment = info.Comment,
                 Log = info.Log,
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 PersistentId = info.Sessionpersistentid,
                 Kills = info.Kills,
                 Deaths = info.Deaths,
                 Assists = info.Assists,
                 Points = info.Points,
                 Prime = info.Prime,
                 Distance = info.Distance,
                 Afks = info.Afks,
                 ConnStatus = info.Connstatus
               };
    }

    internal static GMUserOperationInfoBL ToBLEntity(this GMUserOperationInfo info)
    {
      return new GMUserOperationInfoBL
               {
                 UserId = info.Auid,
                 Type = (int) info.Type,
                 Minutes = info.Minutes,
                 Reason = info.Reason,
                 Points = info.Points,
                 GMLogin = info.Gmlogin,
                 Timestamp = FromUnixTimestamp(info.Timestamp),
                 ClaimIds = info.ClaimIds
               };
    }

    internal static GMOperationInfoBL ToBLEntity(this GMOperationInfo info)
    {
      return new GMOperationInfoBL
               {
                 UserId = info.Auid,
                 Type = info.Operation.ToString(),
                 Data = info.Data,
                 GMLogin = info.Gmlogin,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GMOperationInfoBL ToBLEntity(this GMEditFieldInfo info)
    {
      return new GMOperationInfoBL
               {
                 UserId = info.Auid,
                 Type = "PlayerEdit",
                 Data = String.Format("{0}: old='{1}', new='{2}'", info.Field, info.Oldvalue, info.Newvalue),
                 GMLogin = info.Gmlogin,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GMOperationInfoBL ToBLEntity(this GMHeroActionInfo info, string type)
    {
      return new GMOperationInfoBL
      {
        UserId = info.Auid,
        Type = type,
        Data = info.Heroid.ToString(),
        GMLogin = info.Gmlogin,
        Timestamp = FromUnixTimestamp(info.Timestamp)
      };
    }

    internal static GuildShopBuyInfoBL ToBLEntity(this GuildShopBuyInfo info)
    {
      return new GuildShopBuyInfoBL
               {
                 Auid = info.Auid,
                 GuildId = info.Guildid,
                 HasSuzerain = info.Hassuzerain,
                 ShopLevel = info.Shoplevel,
                 ShopItemId = info.Shopitemid,
                 GuildPointsChange = info.Guildpointschange,
                 PlayerPointsChange = info.Rchange.CWPoints_Player,
                 GuildPointsTotal = info.Guildpointstotal,
                 PlayerPointsTotal = info.Rtotal.CWPoints_Player,
                 ResourceTableChange = info.Rchange.ToBLEntity(),
                 ResourceTableTotal = info.Rtotal.ToBLEntity(),
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GuildSiegeInfoBL ToBLEntity(this GuildSiegeInfo info)
    {
      var result = new GuildSiegeInfoBL
                     {
                       SiegeId = info.Siegeid,
                       GuildId = info.Guildid,
                       GuildRating = info.Guildrating,
                       TargetGuildId = info.Targetguildid,
                       TargetGuildRating = info.Targetguildrating,
                       TargetSuzerainId = info.Targetsuzerainid,
                       GuildPointsChange = info.Guildpointsprice,
                       GuildPointsTotal = 0,
                       StartTimestamp = FromUnixTimestamp(info.Starttimestamp),
                       EndTimestamp = FromUnixTimestamp(info.Endtimestamp),
                       Participants = new List<GuildSiegeParticipantInfoBL>(),
                       WinnerGuildId = info.Winnerguildid
                     };
      if (info.Participants != null && info.Participants.Count > 0)
        result.Participants.AddRange(info.Participants.Select(p => p.ToBLEntity()));
      return result;
    }

    internal static GuildSiegeParticipantInfoBL ToBLEntity(this GuildSiegeParticipantInfo info)
    {
      return new GuildSiegeParticipantInfoBL
               {
                 GuildId = info.Guildid,
                 GuildRating = info.Guildrating,
                 StartTimestamp = FromUnixTimestamp(info.Starttimestamp),
                 EndTimestamp = FromUnixTimestamp(info.Endtimestamp),
                 SiegePoints = info.Siegepoints,
                 GuildPointsChange = info.Guildpointsprice,
                 GuildPointsTotal = 0,
               };
    }

    internal static GuildDailyStatsInfoBL ToBLEntity(this GuildDailyStatsInfo info)
    {
      var result = new GuildDailyStatsInfoBL
                     {
                       GuildId = info.Guildid,
                       GuildRating = info.Guildrating,
                       GuildRatingToday = info.Guildratingtoday,
                       GuildPoints = info.Guildpoints,
                       GuildRank = info.Guildrank,
                       Timestamp = FromUnixTimestamp(info.Timestamp),
                       Vassals = new Dictionary<long, long>(),
                       Suggested = new Dictionary<long, long>()
                     };

      if (info.Vassals != null && info.Vassals.Count > 0)
        info.Vassals.ForEach(i => result.Vassals.Add(i.Guildid, i.Guildpoints));

      if (info.Suggested != null && info.Suggested.Count > 0)
        info.Suggested.ForEach(i => result.Suggested.Add(i.Guildid, i.Guildrating));

      return result;
    }

    internal static GuildInteractionInfoBL ToBLEntity(this GuildInteractionInfo info)
    {
      return new GuildInteractionInfoBL
               {
                 GuildId = info.Guildid,
                 TargetGuildId = info.Targetguildid,
                 Type = info.Type.ToString(),
                 SiegeId = info.Siegeid,
                 WaitingTime = info.Waitingtime,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static GuildPointsChangeInfoBL ToBLEntity(this GuildPointsChangeInfo info)
    {
      return new GuildPointsChangeInfoBL
               {
                 GuildId = info.Guildid,
                 Auid = info.Auid,
                 Source = info.Source.ToString(),
                 PlayerPointsChange = info.Playerpointschange,
                 PlayerPointsTotal = info.Playerpointstotal,
                 GuildPointsChange = info.Guildpointschange,
                 GuildPointsTotal = info.Guildpointstotal,
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }

    internal static AfterPartyInfoBL ToBLEntity(this AfterPartyInfo info)
    {
      var members = info.Members
        .Select(m => new AfterPartyMemberInfoBL
                     {
                       Auid = m.Auid,
                       SessionPersistentId = m.Auid,
                       Kicked = m.Kicked,
                       Leaved = m.Leaved
                     });
      
      return new AfterPartyInfoBL
               {
                 MMStarted = info.Mmstarted,
                 Members = members.ToList(),
                 Timestamp = FromUnixTimestamp(info.Timestamp)
               };
    }


    internal static DateTime FromUnixTimestamp(long timestamp)
    {
      return new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc).AddSeconds(timestamp);
    }


    internal static DateTime FromUnixTimestamp(long timestamp, long synctimestamp)
    {
      var now = DateTime.UtcNow;
      now = new DateTime(now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);
      return now.AddSeconds(timestamp - synctimestamp);
    }


    internal static int ToIntFaction(this string faction)
    {
      return faction == "A" ? 0 : faction == "B" ? 1 : -1;
    }


    internal static DateTime ToDate(this ICallContext callCtx)
    {
      return FromUnixTimestamp(callCtx.eventTimestamp, callCtx.transmissionTimestamp);
    }
  }
}