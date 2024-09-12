namespace csharp StatisticCore.Thrift

struct LoginInfo {
  1: i64 auid // это везде auid
  2: string nick // nickname
  3: string server // one
  4: string cluster // имя кластера (?)
  5: i32 timestamp // unixtime
  6: string ip // remote_ip юзера (из HTTP-заголовка)
  7: string faction // фракция: A - докты, B - адорнийцы
  8: bool factionselected // False:собственно логин, True:смена фракции
  9: bool isdeveloper // разработчик или нет
  10: string locale // локаль игрока
  11: i64 guildid
  12: string guildshortname
  13: string guildfullname
  14: i32 leaverpoints
  15: bool isleaver
}

struct TalentInfo {
  1: i32 classId
  2: i64 instanceId
  3: i32 boundHeroClassId
}

struct MoveTalentInfo {
  1: i64 auid
  2: string nick
  3: i32 talentid // CRC32 signed
  4: i32 heroid // CRC32 signed
  5: byte slot
  6: i32 timestamp
}

struct ResourceTable {
  1: i32 Gold
  2: i32 Silver
  3: i32 Perl
  4: i32 RedPerl
  5: i32 Population
  6: i32 Resource1
  7: i32 Resource2
  8: i32 Resource3
  9: i32 CWPoints_Player
  10: i32 Shard
  11: map<string,i32> Currencies
}

enum ResourceChangeItem {
  BuildingPlace,
  BuildingUpgrade,
  BuildingBuyCycle,
  ChangeFraction,
  ChangeNickname,
  Unsoulbound,
  Expansion,
  MoveFromPocket,
  MovePerlIntoBuilding,
  StartProduction,
  MoveToPocket,
  RemovePerlFromBuilding,
  TalentSell,
  FinishProduction,
  BuildingSell,
  ResetHeroStats,
  SkipQuestObjective,
  BuyPremiumAccount,
  UpgradeTalent,
  BuySkin,
  Unban,
  BuyGuildIconChange,
  BuyTournamentTicket,
  InvestInGuild,
  BuyFlag,
  Transmutation,
  BuyBeginnersPack,
  ContextBuyResource,
  BoostProduction,
  DynamicQuestReward,
  RerollShopBuy,
  RollEvent,
  AddTalentQuest,
  QuestEvent,
  Session
}

struct ResourcesChangeInfo {
  1: i64 auid
  2: bool gain                 // true - доход, false - расход
  3: ResourceChangeItem source // статья дохода/расхода
  4: string buildingname       // название здания в котором потрачены/заработаны ресурсы (может быть пустым)
  5: ResourceTable rchange     // изменение количество ресурсов (по модулю)
  6: ResourceTable rtotal      // общее количество ресурсов у игрока
  7: i32 timestamp
}

enum QuestChangeItem {
  Add,
  Accept,
  Complete
}

struct QuestChangeInfo {
  1: i64 auid
  2: i32 questid // CRC32 signed
  3: QuestChangeItem reason // причина смены статуса квеста
  4: i32 timestamp
}

struct DynamicQuestChangeInfo {
  1: i64 auid
  2: i32 questindex
  3: string questname
  4: QuestChangeItem reason // причина смены статуса квеста
  5: i32 timestamp
  6: bool alternativeline
}

struct TutorialStateChangeInfo {
  1: i64 auid
  2: string tutorialstate
  3: i32 timestamp
}

struct FactionSelectInfo {
  1: i64 auid
  2: string oldfaction // фракция: A - докты, B - адорнийцы, N - не выбрана
  3: string newfaction
  4: ResourceTable rchange
  5: ResourceTable rtotal
  6: i32 timestamp
}

struct UnlockHeroInfo {
  1: i64 auid
  2: i32 heroid
  3: ResourceTable rchange
  4: ResourceTable rtotal
  5: i32 timestamp
}

struct MoveToBathInfo {
  1: i64 auid
  2: i32 heroid
  3: i32 minutes
  4: ResourceTable rchange
  5: ResourceTable rtotal
  6: i32 timestamp
}

struct JoinSessionInfo {
  1: i64 auid
  2: i64 sessionpersistentid
  3: i32 heroid
  4: list<i32> talentset // список TalentID, по порядку слотов
  5: list<i32> guildbuffs // список клановых бафов, аффектящих сессию
  6: i32 guildwareventpass
  7: i32 timestamp
}

struct ChatMessageInfo {
  1: i64 auid
  2: i32 timestamp
  3: string channel
  4: string message
}

struct FieldEditInfo {
  1: string field
  2: string oldvalue
  3: string newvalue
}

struct MonitoringResultInfo {
  1: string property
  2: string counter
  3: i32 value
  4: i32 timestamp
}

struct GMHeroActionInfo {
  1: i64 auid
  2: string gmlogin
  3: i32 heroid
  4: i32 timestamp
}

struct GMEditFieldInfo {
  1: i64 auid
  2: string gmlogin
  3: i32 timestamp
  4: string field
  5: string oldvalue
  6: string newvalue
}

enum GMOperationType {
  QuestAdd,
  QuestAccept,
  QuestComplete,
  QuestDelete,
  BuildingAdd,
  BuildingDelete,
  BuildingMoveToStorage,
  SkinAdd,
  SkinDelete,
  TalentAdd,
  TalentDelete,
  TalentEdit,
  Kick,
  FlagLock,
  FlagUnlock,
  GuildEdit,
  GuildLock,
  GuildUnlock,
  GuildStopSiege,
  GuildSuzerainChange,
  SeasonAwardsAdd,
  SeasonAwardsChange,
  SeasonInfoAdd,
  SeasonInfoChange,
  TalentUpgradeEntityDelete,
}

struct GMOperationInfo {
  1: i64 auid
  2: GMOperationType operation
  3: string gmlogin
  4: i32 timestamp
  5: string data      // строка с данными о внесенных изменениях
}

enum GMUserOperationType {
  Ban,
  Mute,
  Unban,
  Unmute,
  Forgive,
  SetLeave,
  ModeratorMute,
}

struct GMUserOperationInfo {
  1: i64 auid
  2: GMUserOperationType type
  3: i32 minutes
  4: string reason
  5: string gmlogin
  6: i32 timestamp
  7: list<i32> claimIds
  8: i32 points
}

struct ClaimInfo {
  1: i64 fromAuid
  2: i64 toAuid
  3: i32 source
  4: i32 category
  5: string comment
  6: string log
  7: i32 timestamp
  8: i64 sessionpersistentid
  9: i32 kills
  10: i32 deaths
  11: i32 assists
  12: i32 points
  13: i32 prime
  14: i32 distance
  15: i32 afks
  16: i32 connstatus
  17: string locale
  18: string muid
}

struct AddIgnoreInfo {
  1: i64 auid
  2: i64 ignoreauid
  3: string reason
  4: i32 timestamp
}

struct RemoveIgnoreInfo {
  1: i64 auid
  2: i64 ignoreauid
  3: i32 timestamp
}

struct LeaverPointsChangeInfo {
  1: i64 auid
  2: string type
  3: i32 leaverpointschange
  4: i32 leaverpointstotal
  5: bool isleaverchanged
  6: bool isleaver
  7: bool isbadbehaviour
  8: i32 timestamp
}

struct SessionAwardsInfo {
  1: i64 auid
  2: i64 sessionpersistentid
  3: string nick
  4: i32 heroid // CRC32 signed
  5: ResourceTable rchange
  6: ResourceTable rtotal
  7: i32 inc_reliability
  8: i32 new_reliability
  9: i32 timestamp
  10: list<TalentInfo> talents
  11: double force
  12: i32 guildpointschange
  13: i32 guildpointstotal
  14: list<i32> appliedbuffs
  15: LeaverPointsChangeInfo leaverpointschange
 }

enum RatingType {
  LordRating,
  HeroRating,
  GuardRating
}

struct RatingChangeInfo {
  1: i64 auid
  2: RatingType type
  3: i64 sessionpersistentid
  4: i32 heroid
  5: double rating_inc
  6: double rating_new
  7: i32 timestamp
}

struct HeroLevelChangeInfo {
  1: i64 auid
  2: i32 heroid
  3: i32 level
  4: i32 timestamp
}

struct HeroRankChangeInfo {
  1: i64 auid
  2: i32 heroid
  3: i32 level
  4: i32 rank
  5: bool up
  6: i32 timestamp
}

struct CastleLevelChangeInfo {
  1: i64 auid
  2: i32 level
  3: i32 timestamp
}

enum LauncherStatus {
  Complete,
  Stopped,
  DownloadFailure,
  NotApplied
}

struct LauncherInfo {
  1: string hostid
  2: string package
  3: string version
  4: LauncherStatus status
  5: i64 auid
  6: string ip
  7: string location
  8: string locale
}

struct LauncherEventsInfo {
  1: string muid
  2: i64 auid
  3: i64 bitmask
  4: i32 timestamp
  5: string locale
}

struct LauncherDActionsInfo {
  1: string action
  2: string hostid
  3: string version
  4: string muid
  5: string auid
  6: double speed
  7: double avg_speed
  8: double min_speed
  9: i32 total_patches
  10: i32 applied_patches
  11: double total_download
  12: double downloaded
  13: string error
  14: i32 need_close
  15: i32 timestamp
  16: string geolocation
  17: i32 server_timestamp
  18: string locale
}

struct SocialRegisterInfo {
  1: string hostid
  2: string auid
  3: string snid
  4: string snuid
  5: string muid
}

struct SocialJoinInfo {
  1: string auid
  2: string snid
  3: string snuid
}

struct SocialMergeInfo {
  1: string auid1
  2: string auid2
}

struct GuildCoreInfo {
  1: i64 guildid
  2: i64 auid
  3: i32 timestamp
  4: string faction // фракция: A - докты, B - адорнийцы
  5: i32 guildmembers
}

struct GuildInfo {
  1: GuildCoreInfo coreInfo
  2: string shortname
  3: string fullname
  4: ResourceTable rchange
  5: ResourceTable rtotal
}

struct GuildLeaveInfo {
  1: GuildCoreInfo coreInfo
  2: bool kicked
}

struct ClientPingInfo {
  1: i64 auid // это везде auid
  2: string location // RU0, RU1, TR0 и т.п.
  3: i32 msecPing // при таймаутах тут будет default=9000
  4: i32 timestamp
}

enum RuneRollSource {
  GMTool,
  DumpTool,
  GMToolUpgHeroTal,
  DumpToolUpgHeroTal,
  Quest,
  DynamicQuest,
  DynamicQuestUpgHeroTal,
  CustomEvent,
  SessionDrop,
  NivalGift,
  ReRollShop,
}

struct RuneRollInfo {
  1: i64 auid
  2: i32 rune
  3: RuneRollSource source
  4: i64 sessionpersistentid
  5: i32 timestamp
  6: i32 runescountold
  7: i32 runescountnew
}

struct GWEventInfo {
  1: string mongoid
  2: i32 eventidx
  3: bool enabled
  4: i32 points
  5: i32 endtime
  6: i32 limit
}        

struct GWScoreChangeInfo {
  1: string gweventmid
  2: i64 guildid
  3: i32 lastpoints
  4: i32 currentpoints
  5: i32 timestamp
  6: i32 auid
}

struct QuestEventsStagesInfo {
  1: i32 auid
  2: i32 tostagechange
  3: i32 timestamp
}

struct QuestEventsStatesInfo {
  1: i32 auid
  2: i32 tostepschange
  3: i32 stage
  4: i32 timestamp
}

struct RuneReplenishInfo {
  1: i64 auid
  2: i32 rune
  3: i32 timestamp
}

struct RuneHeroApplyInfo {
  1: i64 auid
  2: i32 rune
  3: string hero
  4: i32 timestamp
}

struct RuneSoulboundInfo {
  1: i64 auid
  2: i32 rune
  3: i32 talent
  4: i32 timestamp
}

struct RuneExpireInfo {
  1: i64 auid
  2: i32 rune
  3: i32 transactionsLeft
  4: i32 bonusLeft
  5: i32 timestamp
}

enum TalentChangeOperation {
  GetFromTransmutation,
  GetFromQuest,
  GetFromTavern,
  GetForLevelUp,
  Soulbound,
  Unsoulbound,
  UseForRefining,
  Sell,
  GetFromSocial,
  GetFromDLC,
  GetFromEvent,
  Refining,
  TakeFromBank,
  PutToBank,
  ReturnToBank,
  TakeBackFromBank,
  ReturnToBankOnLeave,
  ReturnToUserOnLeave,
  RerollShopBuy,
  UpgradeByEntity,
  EntityUsedForUpgrade,
  GetEntityFromLootbox
}

struct TalentChangeInfo {
  1: i64 auid
  2: TalentInfo talent
  3: TalentChangeOperation operation
  4: i32 timestamp
  5: string data
}

struct GuildShopBuyInfo {
  1: i64 auid
  2: i64 guildid
  3: bool hassuzerain
  4: i32 shoplevel
  5: i32 shopitemid
  6: ResourceTable rchange
  7: ResourceTable rtotal
  8: i32 guildpointschange
  9: i32 guildpointstotal
  10: i32 timestamp
}

struct GuildSiegeParticipantInfo {
  1: i64 guildid
  2: i32 guildrating
  3: i32 starttimestamp
  4: i32 endtimestamp
  5: i32 siegepoints
  6: i32 guildpointsprice
}

struct GuildSiegeInfo {
  1: i64 siegeid
  2: i64 guildid
  3: i32 guildrating
  4: i64 targetguildid
  5: i32 targetguildrating
  6: i64 targetsuzerainid
  7: i32 targetsuzerainrating
  8: i32 guildpointsprice
  9: i32 starttimestamp
  10: i32 endtimestamp
  11: list<GuildSiegeParticipantInfo> participants
  12: i64 winnerguildid
}

struct GuildDailyStatsVassalInfo {
  1: i64 guildid
  2: i64 guildpoints
}

struct GuildDailyStatsSuggestedInfo {
  1: i64 guildid
  2: i64 guildrating
}

struct GuildDailyStatsInfo {
  1: i64 guildid
  2: i32 guildrating
  3: i32 guildratingtoday
  4: i32 guildpoints
  5: i32 guildrank
  6: i32 timestamp
  7: list<GuildDailyStatsVassalInfo> vassals
  8: list<GuildDailyStatsSuggestedInfo> suggested
}

enum GuildInteractionType {
  Capture,
  Decline,
  Revolt,
  Apply
}

struct GuildInteractionInfo {
  1: i64 guildid
  2: i64 targetguildid
  3: GuildInteractionType type
  4: i64 siegeid
  5: i32 waitingtime
  6: i32 timestamp
}

struct GuildPointsChangeInfo {
  1: i64 guildid
  2: i64 auid
  3: string source
  4: i32 playerpointschange
  5: i32 playerpointstotal
  6: i32 guildpointschange
  7: i32 guildpointstotal
  8: i32 timestamp
}

struct AfterPartyMemberInfo {
  1: i64 auid
  2: i64 sessionPersistentId
  3: bool kicked
  4: bool leaved
}

struct AfterPartyInfo {
  1: bool mmstarted
  2: list<AfterPartyMemberInfo> members
  3: i32 timestamp
}

enum ERerollShopResources
  {
    Resource1,
    Resource2,
    Resource3,
    Perl,
    RedPerl,
    Silver,
    Gold,
    Shard
}

struct ReRollShopInfo
{
 1: i64 auid            //игрок
 2: i32 itemId          //ID товара в слоте:
                        //   Талант persistentID из *.TALENT
                        //   Герой id из *.HROB
                        //   Скин героя persistentID из *.HEROSKIN
                        //   Ресурс persistentID из ResourceRerollSlot
                        //   Премиум подписка на опр срок persistentID из ResourceRerollSlot
                        //   Руна на опр срок persistentID из ResourceRerollSlot

 3: i32 itemGroup       // ID Группы из которой был получен товар
 4: i64 itemPrice       //Price - уже сформированная на основе очков и типа ресурса цена, за которую игрок купил товар
 5: ERerollShopResources itemPriceType   //TypePrice - тип ресурса, за который продавался товар
 6: i32 rerollCount     // Кол-во рероллов в течении дня, которые сделал игрок прежде чем купить этот товар
 7: string slotType        // Тип слота, в котором был куплен товар - премиум слот или обычный слот
 8: i32 timestamp
}

enum TournamentQuestResult
{
    Loss,
	Win
}

struct TournamentQuestChangeInfo {
  1: i64 auid
  2: i32 questindex
  3: string questname
  4: TournamentQuestResult reason // причина смены статуса квеста
  5: i32 timestamp
  6: bool alternativeline
}


//Service
service StatisticService {
  void LoginUsers(1:list<LoginInfo> logins),
  void LogoutUsers(1:list<LoginInfo> logins),
  void FactionSelect(1:list<FactionSelectInfo> infos),

  void MoveTalentToSet(1:list<MoveTalentInfo> infos),
  void MoveTalentFromSet(1:list<MoveTalentInfo> infos),
  void UnlockHero(1:list<UnlockHeroInfo> infos),
  void MoveHeroToBath(1:list<MoveToBathInfo> infos),
  void ResourcesChange(1:list<ResourcesChangeInfo> infos),
  void QuestChange(1:list<QuestChangeInfo> infos),
  void DynamicQuestChange(1:list<DynamicQuestChangeInfo> infos),
  void TournamentQuestChange(1:list<TournamentQuestChangeInfo> infos),
  void TutorialStateChange(1:list<TutorialStateChangeInfo> infos),
  void TalentChange(1:list<TalentChangeInfo> infos),

  void JoinPvpSession(1:list<JoinSessionInfo> infos),
  void GiveSessionAwards(1:list<SessionAwardsInfo> info),
  void RatingChange(1:list<RatingChangeInfo> infos),
  void HeroLevelChange(1:list<HeroLevelChangeInfo> infos),
  void HeroRankChange(1:list<HeroRankChangeInfo> infos),
  void CastleLevelChange(1:list<CastleLevelChangeInfo> infos),
  void AfterParty(1:list<AfterPartyInfo> infos),
  void LeaverPointsChange(1:list<LeaverPointsChangeInfo> infos),
  void ReRollShop(1:list<ReRollShopInfo> infos),

  void ChatMessages(1:list<ChatMessageInfo> infos),

  void ClientPings(1:list<ClientPingInfo> infos),

  void UserClaims(1: list<ClaimInfo> infos),

  // GM Operations
  void GMEditUser(1:list<GMEditFieldInfo> infos),
  void GMUnlockHero(1:list<GMHeroActionInfo> infos),
  void GMLockHero(1:list<GMHeroActionInfo> infos),
  void GMOperation(1:list<GMOperationInfo> infos),
  void GMUserOperation(1:list<GMUserOperationInfo> infos),

  // Monitoring
  void MonitoringResults(1:list<MonitoringResultInfo> results),

  // Chat Ignores
  void AddIgnore(1:list<AddIgnoreInfo> infos),
  void RemoveIgnore(1:list<RemoveIgnoreInfo> infos),

  // Launcher
  void LauncherStart(1:list<LauncherInfo> infos),
  void LauncherEvents(1:list<LauncherEventsInfo> infos),
  void LauncherDActions(1:list<LauncherDActionsInfo> infos),

  void SocialRegister(1:list<SocialRegisterInfo> infos),
  void SocialJoin(1:list<SocialJoinInfo> infos),
  void SocialMerge(1:list<SocialMergeInfo> infos),

  void GuildCreated(1:list<GuildInfo> infos),
  void GuildRenamed(1:list<GuildInfo> infos),
  void GuildJoined(1:list<GuildCoreInfo> infos),
  void GuildLeaved(1:list<GuildLeaveInfo> infos),
  void GuildDisbanded(1:list<GuildCoreInfo> infos),
  void GuildShopBuy(1:list<GuildShopBuyInfo> infos),
  void GuildSiege(1:list<GuildSiegeInfo> infos),
  void GuildDailyStats(1:list<GuildDailyStatsInfo> infos),
  void GuildInteraction(1:list<GuildInteractionInfo> infos),
  void GuildPointsChange(1:list<GuildPointsChangeInfo> infos),

  void RuneExpire(1:list<RuneExpireInfo> infos),
  void RuneUnsoulbound(1:list<RuneSoulboundInfo> infos),
  void RuneReplenish(1:list<RuneReplenishInfo> infos),
  void RuneHeroApply(1:list<RuneHeroApplyInfo> infos),
  void RuneRoll(1:list<RuneRollInfo> infos),

  void GWEventAdd(1:list<GWEventInfo> infos),
  void GWScoreChange(1:list<GWScoreChangeInfo> infos),
  void QuestEventStageChange(1:list<QuestEventsStagesInfo> infos),
  void QuestEventStateChange(1:list<QuestEventsStatesInfo> infos),
}
