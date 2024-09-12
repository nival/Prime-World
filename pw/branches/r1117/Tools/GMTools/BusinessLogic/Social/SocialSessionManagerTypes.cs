using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;

namespace BusinessLogic.Social
{
  public class LoginInfoBL
  {
    public long UserId { get; set; }
    public string Login { get; set; }
    public int Faction { get; set; }
    public string Ip { get; set; }
    public string Server { get; set; }
    public string Cluster { get; set; }
    public bool IsDeveloper { get; set; }
    public string Locale { get; set; }
    public DateTime Timestamp { get; set; }
    public long GuildId { get; set; }
    public string GuildShortName { get; set; }
    public string GuildFullName { get; set; }
    public int LeaverPoints { get; set; }
    public bool IsLeaver { get; set; }

    public override string ToString()
    {
      return String.Format("LoginInfoBL(UserId={0},Login={1},Faction={2},Ip={3},Server={4},Cluster={5},IsDeveloper={6},Locale={7},Timestamp={8},GuildId={9},GuildShortName={10},GuildFullName={11},LeaverPoints={12},IsLeaver={13})",
                           UserId, Login, Faction, Ip, Server, Cluster, IsDeveloper, Locale, Timestamp, GuildId, GuildShortName, GuildFullName, LeaverPoints, IsLeaver);
    }
  }

  public class ResourceTableBL
  {
    public int Gold;
    public int Silver;
    public int Perl;
    public int RedPerl;
    public int Population;
    public int Resource1;
    public int Resource2;
    public int Resource3;
    public int Shard;
    public string CurrencyName;
    public int CurrencyValue;

    public bool IsEmpty
    {
      get { return Gold == 0 && Silver == 0 && Perl == 0 && RedPerl == 0 && Population == 0 && Resource1 == 0 && Resource2 == 0 && Resource3 == 0 && Shard == 0 && CurrencyValue == 0; }
    }

    public override string ToString()
    {
      return String.Format("ResourceTableBL(Gold={0},Silver={1},Perl={2},RedPerl={3},Population={4},Resource1={5},Resource2={6},Resource3={7},Shard={8}, Currency={9}:{10})",
                           Gold, Silver, Perl, RedPerl, Population, Resource1, Resource2, Resource3, Shard, CurrencyName, CurrencyValue);
    }
  }

  public class FactionSelectInfoBL
  {
    public long UserId;
    public int OldFaction;
    public int NewFaction;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public DateTime Timestamp;
    public ResourceLog ResourceLog; // вспомогательное поле, используется в FactionSelectTask

    public override string ToString()
    {
      return String.Format("FactionSelectInfoBL(UserId={0},OldFaction={1},NewFaction={2},RChange={3},RTotal:{4},Timestamp={5})",
                           UserId, OldFaction, NewFaction, RChange, RTotal, Timestamp);
    }
  }

  public class UnlockHeroInfoBL
  {
    public long UserId;
    public int HeroId;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public DateTime Timestamp;
    public ResourceLog ResourceLog; // вспомогательное поле, используется в CharacterUnlockTask

    public override string ToString()
    {
      return String.Format("UnlockHeroInfoBL(UserId={0},HeroId={1},RChange={2},RTotal={3},Timestamp={4})",
                           UserId, HeroId, RChange, RTotal, Timestamp);
    }
  }

  public class MoveToBathInfoBL
  {
    public long UserId;
    public int HeroId;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public int Minutes;
    public DateTime Timestamp;
    public ResourceLog ResourceLog; // вспомогательное поле, используется в MoveToBathTask

    public override string ToString()
    {
      return String.Format("MoveToBathInfoBL(UserId={0},HeroId={1},RChange={2},RTotal={3},Minutes={4},Timestamp={5})",
                           UserId, HeroId, RChange, RTotal, Minutes, Timestamp);
    }
  }

  public class SessionAwardsInfoBL
  {
    public long Auid;
    public long SessionPersistentId;
    public string Nick;
    public int HeroId;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public DateTime Timestamp;
    public List<int> GuildBuffs;
    public int GuildPointsChange;
    public int PlayerPointsChange;
    public int GuildPointsTotal;
    public int PlayerPointsTotal;
    public LeaverPointsChangeInfoBL LeaverPointsChange;
    public ResourceLog ResourceLog;         // вспомогательное поле, используется в SessionAwardsTask

    public class TalentInfoBL
    {
      public int Id;
      public long InstanceId;
      public override string ToString()
      {
        return String.Format("TalentInfoBL(Id={0},InstanceId={1})", Id, InstanceId);
      }
    }
    public List<TalentInfoBL> Talents;

    public override string ToString()
    {
      return
        String.Format(
          "SessionAwardsInfoBL(Auid: {0}, SessionPersistentId: {1}, Nick: {2}, HeroId: {3}, RChange: {4}, RTotal: {5}, Timestamp: {6}, " + 
          "GuildBuffs: {7}, GuildPointsChange: {8}, PlayerPointsChange: {9}, GuildPointsTotal: {10}, PlayerPointsTotal: {11}, ResourceLog: {12}, Talents: {13}, " +
          "LeaverPointsChange: {14})",
          Auid, SessionPersistentId, Nick, HeroId, RChange, RTotal, Timestamp,
          GuildBuffs != null ? String.Join(",", GuildBuffs.Select(t => t.ToString()).ToArray()) : "null",
          GuildPointsChange, PlayerPointsChange, GuildPointsTotal, PlayerPointsTotal, ResourceLog,
          Talents != null ? String.Join(",", Talents.Select(t => t.ToString()).ToArray()) : "null",
          LeaverPointsChange);
    }
  }

  public class TalentChangeInfoBL
  {
    public long Auid;
    public string Operation;
    public string Data;
    public int TalentId;
    public long TalentInstanceId;
    public int BoundHero;
    public DateTime Timestamp;
  }

  public class ResourcesChangeInfoBL
  {
    public long Auid;
    public bool Gain;
    public string Source;
    public string BuildingName;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("ResourcesChangeInfoBL(Auid={0},Gain={1},Source={2},BuildingName={3},RChange={4},BuildingName={5},RTotal={6},Timestamp={7})",
                           Auid, Gain, Source, BuildingName, RChange, BuildingName, RTotal, Timestamp);
    }
  }

  public class MonitoringResultInfoBL
  {
    public string Property { get; set; }
    public string Counter { get; set; }
    public int Value { get; set; }
    public DateTime Timestamp { get; set; }

    public override string ToString()
    {
      return String.Format("MonitoringResultInfoBL(Property={0},Counter={1},Value={2},Timestamp={3})",
                           Property, Counter, Value, Timestamp);
    }
  }

  public class AddIgnoreInfoBL
  {
    public long Auid { get; set; }
    public long Ignoreauid { get; set; }
    public string Reason { get; set; }
    public DateTime Timestamp { get; set; }

    public override string ToString()
    {
      return String.Format("AddIgnoreInfoBL(Auid={0},Ignoreauid={1},Reason={2},Timestamp={3})",
                           Auid, Ignoreauid, Reason, Timestamp);
    }
  }

  public class RemoveIgnoreInfoBL
  {
    public long Auid { get; set; }
    public long Ignoreauid { get; set; }
    public DateTime Timestamp { get; set; }

    public override string ToString()
    {
      return String.Format("RemoveIgnoreInfoBL(Auid={0},Ignoreauid={1},Timestamp={2})",
                           Auid, Ignoreauid, Timestamp);
    }
  }

  public class QuestChangeInfoBL
  {
    public long Auid { get; set; }
    public int QuestId { get; set; }
    public int Reason { get; set; }
    public DateTime Timestamp { get; set; }

    public override string ToString()
    {
      return String.Format("QuestChangeInfoBL(Auid={0},QuestId={1},Reason={2},Timestamp={3})",
                           Auid, QuestId, Reason, Timestamp);
    }
  }

  public class DynamicQuestChangeInfoBL
  {
    public long Auid { get; set; }
    public int QuestIndex { get; set; }
    public string QuestName { get; set; }
    public int Reason { get; set; }
    public DateTime Timestamp { get; set; }
    public bool Alternativeline { get; set;}

      public override string ToString()
    {
      return String.Format("DynamicQuestChangeInfoBL(Auid={0},QuestIndex={1},QuestName={2},Reason={3},Timestamp={4}, Alternativeline={5})",
                           Auid, QuestIndex, QuestName, Reason, Timestamp, Alternativeline);
    }
  }

  public class TournamentQuestChangeInfoBL
  {
    public long Auid { get; set; }
    public int QuestIndex { get; set; }
    public string QuestName { get; set; }
    public int Reason { get; set; }
    public DateTime Timestamp { get; set; }
    public bool Alternativeline { get; set; }

    public override string ToString()
    {
      return String.Format( "TournamentQuestChangeInfoBL(Auid={0},QuestIndex={1},QuestName={2},Reason={3},Timestamp={4}, Alternativeline={5})",
                           Auid, QuestIndex, QuestName, Reason, Timestamp, Alternativeline );
    }
  }

  public class RatingChangeInfoBL
  {
    public long Auid { get; set; }
    public RatingType Type { get; set; }
    public long SessionPersistentId { get; set; }
    public int HeroId { get; set; }
    public int RatingInc { get; set; }
    public int RatingNew { get; set; }
    public DateTime Timestamp { get; set; }
  }

  public class JoinSessionInfoBL
  {
    public long Auid { get; set; }
    public long SessionPersistentId { get; set; }
    public int HeroId { get; set; }
    public List<int> TalentSet { get; set; }
    public List<int> GuildBuffs { get; set; }
    public DateTime Timestamp { get; set; }
    public int GuildwarEventPass { get; set; }
    public override string ToString()
    {
      return string.Format("JoinSessionInfoBL(Auid={0},SessionPersistentId={1},HeroId={2},TalentSet={3},GuildBuffs={4},Timestamp={5},GuildwarEventPass={6})",
                           Auid, SessionPersistentId, HeroId, TalentSet, GuildBuffs, Timestamp, GuildwarEventPass);
    }
  }

  public class GuildInfoBL
  {
    public long GuildId;
    public long Auid;
    public string ShortName;
    public string FullName;
    public ResourceTableBL RChange;
    public ResourceTableBL RTotal;
    public DateTime Timestamp;
    public ResourceLog ResourceLog;         // вспомогательное поле, используется в GuildCreateTask

    public override string ToString()
    {
      return String.Format("GuildInfoBL(GuildId={0},Auid={1},ShortName={2},FullName={3},RChange={4},RTotal={5},Timestamp={6})",
                           GuildId,Auid,ShortName,FullName,RChange,RTotal,Timestamp);
    }
  }

  public class GuildCoreInfoBL
  {
    public long GuildId;
    public long Auid;
    public int Members;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("GuildCoreInfoBL(GuildId={0},Auid={1},Members={2},Timestamp={3})",
                           GuildId, Auid, Members, Timestamp);
    }
  }

  public class GuildLeaveInfoBL
  {
    public long GuildId;
    public long Auid;
    public int Members;
    public bool Kicked;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("GuildLeaveInfoBL(GuildId={0},Auid={1},Members={2},Kicked={3},Timestamp={4})",
                           GuildId, Auid, Members, Kicked, Timestamp);
    }
  }

  public class ClientPingInfoBL
  {
    public long Auid;
    public string SrvLocation;
    public int Ping;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("ClientPingInfoBL(Auid={0},SrvLocation={1},Ping={2},Timestamp={3})",
                           Auid, SrvLocation, Ping, Timestamp);
    }
  }

  public class RuneReplenishInfoBL
  {
    public long Auid;
    public int RuneId;
    public DateTime Timestamp;
  }

  public class RuneSoulboundInfoBL
  {
    public long Auid;
    public int RuneId;
    public int TalentId;
    public DateTime Timestamp;
  }

    public class RuneHeroApplyInfoBL
    {
        public long Auid;
        public int RuneId;
        public string Hero;
        public DateTime Timestamp;
    }

    public class GWEventInfoBL
    {
        public string mongoId;
        public int eventidx;
        public bool enabled;
        public int points;
        public DateTime endTime;
        public int limit;
    }

  public class GWScoreChangeInfoBL
  {
    public int auid;
    public string gweventmid;
    public long guildid;
    public int lastpoints;
    public int currentpoints;
    public DateTime timestamp;
  }

    public class RuneExpireInfoBL
  {
    public long Auid;
    public int RuneId;
    public int TransactionsLeft;
    public int BonusLeft;
    public DateTime Timestamp;
  }

  public class RuneRollInfoBL
  {
    public long Auid;
    public int RuneId;
    public string Source;
    public long SessionPersistentId;
    public DateTime Timestamp;
    public int? RunesCountOld;
    public int? RunesCountNew;
  }

  public class ClaimInfoBL
  {
    public long FromAuid;
    public long ToAuid;
    public int Source;
    public int Category;
    public string Locale;
    public string Muid;
    public string Comment;
    public string Log;
    public DateTime Timestamp;
    public long PersistentId;
    public int Kills;
    public int Deaths;
    public int Assists;
    public int Points;
    public int Prime;
    public int Distance;
    public int Afks;
    public int ConnStatus;
  }

  public class GMUserOperationInfoBL
  {
    public long UserId;
    public int Type;
    public int Minutes;
    public int Points;
    public string Reason;
    public string GMLogin;
    public DateTime Timestamp;
    public List<int> ClaimIds;
  }

  public class GMOperationInfoBL
  {
    public long UserId;
    public string Type;
    public string Data;
    public string GMLogin;
    public DateTime Timestamp;
  }

  public class GuildShopBuyInfoBL
  {
    public long Auid;
    public long GuildId;
    public bool HasSuzerain;
    public int ShopLevel;
    public int ShopItemId;
    public int GuildPointsChange;
    public int PlayerPointsChange;
    public int GuildPointsTotal;
    public int PlayerPointsTotal;

    public ResourceTableBL ResourceTableChange;
    public ResourceTableBL ResourceTableTotal;

    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("GuildShopBuyInfoBL(Auid: {0}, GuildId: {1}, HasSuzerain: {2}, ShopLevel: {3}, ShopItemId: {4}, GuildPointsChange: {5}, PlayerPointsChange: {6}, GuildPointsTotal: {7}, PlayerPointsTotal: {8}, Timestamp: {9}",
                           Auid, GuildId, HasSuzerain, ShopLevel, ShopItemId, GuildPointsChange, PlayerPointsChange, GuildPointsTotal, PlayerPointsTotal, Timestamp);
    }
  }

  public class GuildSiegeParticipantInfoBL
  {
    public long GuildId;
    public int GuildRating;
    public DateTime StartTimestamp;
    public DateTime EndTimestamp;
    public int SiegePoints;
    public int GuildPointsChange;
    public int GuildPointsTotal;

    public override string ToString()
    {
      return String.Format("GuildSiegeParticipantInfoBL(GuildId: {0}, GuildRating: {1}, StartTimestamp: {2}, EndTimestamp: {3}, SiegePoints: {4}, GuildPointsChange {5}, GuildPointsTotal: {6})",
                           GuildId, GuildRating, StartTimestamp, EndTimestamp, SiegePoints, GuildPointsChange, GuildPointsTotal);
    }
  }

  public class GuildSiegeInfoBL
  {
    public long SiegeId;
    public long GuildId;
    public int GuildRating;
    public long TargetGuildId;
    public int TargetGuildRating;
    public long TargetSuzerainId;
    public int TargetSuzerainRating;
    public int GuildPointsChange;
    public int GuildPointsTotal;
    public DateTime StartTimestamp;
    public DateTime EndTimestamp;
    public List<GuildSiegeParticipantInfoBL> Participants;
    public long WinnerGuildId;


    public override string ToString()
    {
      return
        String.Format(
          "GuildSiegeInfoBL(SiegeId: {0}, GuildId: {1}, GuildRating: {2}, TargetGuildId: {3}, TargetGuildRating: {4}, TargetSuzerainId: {5}, TargetSuzerainRating: {6}, GuildPointsChange: {7}, GuildPointsTotal: {8}, StartTimestamp: {9}, EndTimestamp: {10}, Participants: {11}, WinnerGuildId: {12})",
          SiegeId, GuildId, GuildRating, TargetGuildId, TargetGuildRating, TargetSuzerainId, TargetSuzerainRating,
          GuildPointsChange, GuildPointsTotal, StartTimestamp, EndTimestamp, Participants, WinnerGuildId);
    }

  }

  public class GuildDailyStatsInfoBL
  {
    public long GuildId;
    public int GuildRating;
    public int GuildRatingToday;
    public int GuildPoints;
    public int GuildRank;
    public DateTime Timestamp;
    public Dictionary<long, long> Vassals;
    public Dictionary<long, long> Suggested;

    public override string ToString()
    {
      return String.Format("GuildDailyStatsInfo(GuildId: {0}, GuildRating: {1}, GuildRatingToday: {2}, GuildPoints: {3}, GuildRank: {4}, Timestamp: {5}, Vassals: {6}, Suggested: {7})",
                           GuildId, GuildRating, GuildRatingToday, GuildPoints, GuildRank, Timestamp, Vassals, Suggested);
    }
  }

  public class GuildInteractionInfoBL
  {
    public long GuildId;
    public long TargetGuildId;
    public string Type;
    public long SiegeId;
    public int WaitingTime;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("GuildInteractionInfoBL(GuildId: {0}, TargetGuildId: {1}, Type: {2}, SiegeId: {3}, WaitingTime: {4}, Timestamp: {5})",
                           GuildId, TargetGuildId, Type, SiegeId, WaitingTime, Timestamp);
    }
  }

  public class GuildPointsChangeInfoBL
  {
    public long GuildId;
    public long Auid;
    public string Source;
    public int GuildPointsChange;
    public int GuildPointsTotal;
    public int PlayerPointsChange;
    public int PlayerPointsTotal;
    public DateTime Timestamp;

    public override string ToString()
    {
      return
        String.Format(
          "GuildPointsChangeInfoBL(GuildId: {0}, Auid: {1}, Source: {2}, GuildPointsChange: {3}, GuildPointsTotal: {4}, PlayerPointsChange: {5}, PlayerPointsTotal: {6}, Timestamp: {7})",
          GuildId, Auid, Source, GuildPointsChange, GuildPointsTotal, PlayerPointsChange, PlayerPointsTotal, Timestamp);
    }
  }

  public class AfterPartyInfoBL
  {
    public bool MMStarted;
    public List<AfterPartyMemberInfoBL> Members;
    public DateTime Timestamp;

    public override string ToString()
    {
      return String.Format("AfterPartyInfoBL(MMStarted: {0}, Members: [{1}], Timestamp: {2})", MMStarted, String.Join(",", Members.Select(m => m.ToString()).ToArray()), Timestamp);
    }
  }

  public class AfterPartyMemberInfoBL
  {
    public long Auid;
    public long SessionPersistentId;
    public bool Kicked;
    public bool Leaved;

    public override string ToString()
    {
      return string.Format("AfterPartyMemberInfoBL(Auid: {0}, SessionPersistentId: {1}, Kicked: {2}, Leaved: {3})", Auid, SessionPersistentId, Kicked, Leaved);
    }
  }

  public class LeaverPointsChangeInfoBL
  {
    public long Auid;
    public long? PersistentId;
    public string Type;
    public int LeaverPointsChange;
    public int LeaverPointsTotal;
    public bool IsLeaverChanged;
    public bool IsLeaver;
    public bool IsBadBehaviour;
    public DateTime Timestamp;

    public override string ToString()
    {
      return string.Format("LeaverPointsChangeInfoBL(Auid: {0}, PersistentId: {1}, Type: {2}, LeaverPointsChange: {3}, LeaverPointsTotal: {4}, IsLeaverChanged: {5}, IsLeaver: {6}, IsBadBehaviour: {7}, Timestamp: {8})", Auid, PersistentId, Type, LeaverPointsChange, LeaverPointsTotal, IsLeaverChanged, IsLeaver, IsBadBehaviour, Timestamp);
    }
  }

  public class ReRollShopInfoBL
  {
      public long Auid;
      public int ItemId ;
      public int ItemGroup ;
      public long ItemPrice;
      public string ItemPriceType;
      public int RerollCount;
      public string SlotType;
      public DateTime Timestamp;
      public override string ToString()
      {
          return string.Format("ReRollShopInfoBL(Auid:{0}, ItemId: {1}, ItemGroup: {2}, ItemPrice: {3}, ItemPriceType: {4}, RerollCount: {5}, SlotType: {6},  Timestamp: {7})", 
              Auid, ItemId, ItemGroup, ItemPrice, ItemPriceType, RerollCount, SlotType, Timestamp);
      }
  }

  public class QuestEventStagesInfoBL
  {
    public int Auid;
    public int ToStageChange;
    public DateTime Timestamp;
  }

  public class QuestEventStepsInfoBl
  {
    public int Auid;
    public int ToStepChange;
    public int Stage;
    public DateTime TimeStamp;
  }


}