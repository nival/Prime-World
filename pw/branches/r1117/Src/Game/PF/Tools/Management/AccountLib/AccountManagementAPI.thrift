namespace csharp AccountLib

enum RequestResult {
    Success = 0,
    BadResult,
    LoginNotExist,
    SnUidNotExist,
    HeroInstIdNotExist,
    HeroClassNotExist,
    CantRemoveClassHero,
    TalentInstIdNotExist,
    TalentClassNotExist,
    ServerReturnedNull,
    TransportException,
    AuidNotExist,
    NoUsersWithThatNickname,
    BadServiceType,
    GuildLevelIsTooLow,
    IconFileUploadingError,
    UnknownOperationType,
    UnknownBroadcastLocale,
    CantDisjointFsn,
    BadResponseFromDatabase,
    FlagInstNotExist,
    FlagNotExist,
    GuildLockRequired
    SiegeInProgress,
    SiegeNotExists,
    IncorrectSuzerain,
    MaxVassalsReached,
    DynamicQuestHasIllegalSynthaxis,
    AuidsListInUsedInQuest,
    CantRemoveGuildMemberFromFriends,
    CantRemoveFavouriteFriend,
	EmailNotExist,
	EmailAlreadyActivated,
  NicknameNotExist,
}

enum Gender {
  Unknown = 0,
  Male = 1,
  Female = 2,
  Other = 3,
}

enum PayServiceType {
  NoService = 0,
  PremiumAccount = 1,
  Unban = 2,
}

enum PayTicketType {
  Silver = 0,
  Gold = 1,
  Free = 2,
}

struct SeasonAwards {
	1: i32 seasonId,	
	2: string seasonName,	
	3: i64 startDate,
	4: i64 endDate,
	5: i32 perls,
	6: string skin,
	7: string flag,
	8: string talents,
  9: string lootboxes,
}

struct AccountInfo {
  1:  string snid,
  2:  string snuid,	
  3:  string login,
  4:  string email,
  5:  string nickname,
  6:  bool online,
  7:  i32 gold,
  8:  i32 silver,
  9:  i32 resource1,
  10: i32 resource2,
  11: i32 resource3,
  12: i32 perl,
  13: i32 redPerl,
  14: i64 currentsession,
  15: i64 registerdate,
  16: i32 fame,
  17: i32 reliability,
  18: i32 fraction,
  19: string location,
  20: i32 banFlag,
  21: i64 banned,
  22: i32 muteFlag,
  23: i64 muted,
  24: bool isDeveloper,
  25: i64 auid,
  26: Gender gender,
  27: i32 nickChanges,
  28: i32 nickChangesFree,
  29: i32 fractionChanges,
  30: i32 fractionChangesFree,
  31: i64 premiumAccountDate,
  32: double lordRating,
  33: double numberOfWins,
  34: i32 dodges,
  35: i64 retiredTime,
  36: double guardRating,
  37: double dailyRating,
  38: i64 guildid,
  39: i32 guildBuildingLevel,
  40: bool isSpectator,
  41: bool hasLamp,
  42: list<string> joinedSnids,
  43: i64 lastPaymentTime,
  44: i64 lastLampDropTime,
  45: bool isRegularMMAllowed,
  46: string locale,
  47: string muid,
  48: string country,
  49: string region,
  50: string city,
  51: string gmcountry,
  52: string gmregion,
  53: string gmcity,
  54: i32 cwplayerpoints,
  55: i32 leaverPoints,
  56: bool isLeaver,
  57: bool isBadBehaviour,
  58: bool canMute,
  59: i32 PlayerRating,
  60: i64 PlayerRatingHero,
  61: i64 PlayerRatingHeroLastPlayed,
  62: i64 numberOfWinsForPR,
  63: i32 extraComplaints,
  64: i64 bruteForceDefenderBan,
  65: i32 extraSessionComplaints,
  66: list<SeasonAwards> listSeasonsAwards,
  67: i32 Shard,
  68: map<string,i32> currencies,
}

struct AccountEdit{
  1: string snid,
  2: string snuid,
  3: string login,
  4: string email,
  5: string nickname,
  6: i32 gold,
  7: i32 silver,
  8: i32 resource1,
  9: i32 resource2,
  10: i32 resource3,
  11: i32 perl,
  12: i32 redPerl,
  13: i32 fame,
  14: i32 reliability,
  15: i32 fraction,
  16: string location,
  17: bool isDeveloper,
  18: i64 auid,
  19: Gender gender,
  20: i32 switchQuant,
  21: double lordRating,
  22: double numberOfWins,
  23: i32 dodges,
  24: i64 retiredTime,
  25: double guardRating,
  26: double dailyRating,
  27: i32 guildBuildingLevel,
  28: bool isSpectator,
  29: i64 lastPaymentTime,
  30: i64 lastLampDropTime,
  31: bool isRegularMMAllowed,
  32: i32 cwplayerpoints,
  33: bool canMute,
  34: i32 PlayerRating,
  35: i64 numberOfWinsForPR,
  36: i32 extraComplaints,
  37: i64 bruteForceDefenderBan,
  38: i32 extraSessionComplaints,
  39: i32 Shard,
  40: map<string,i32> currencies,
}

struct AccountShortInfo {
  1: string snid,
  2: string snuid,
  3: string login,
  5: string email,
  6: string nickname,
}

struct SeasonInfo {
	1: i32 seasonId,	
	2: string seasonName,	
	3: i64 startDate,
	4: i64 endDate,
	5: i32 seasonRating,
	6: i32 leagueIndex,
	7: i32 curLeaguePlace,
	8: i32 bestLeaguePlace,
}

struct HeroInfo {
  1: i32 heroClassId,
  2: i64 heroInstanceId,
  3: i32 experience,
  4: double rating,
  5: i32 epicWins
}

struct TalentInfo {
  1: i32 talentClassId,
  2: i64 talentInstanceId,
  3: i32 refineRate,
  4: i32 boundHeroClassId,
  5: i64 boundHeroInstanceId,
}

struct TalentSetInfo {
  1: i32 talentSetId,
  2: list<TalentInfo> talents,
}

//QuestForTalent region

struct QuestForTalentInfo {
  1: i32 questId,
  2: i32 startTime,
  3: i32 endTime,
  4: i32 talentAwardPersistentId,
  5: string talentAwardName,
  6: i32 shardsSpent,
  7: string fullDynamicQuestInfo,
  8: i32 currentObjectiveValue,
  9: string currentObjectiveData,
  10: i32 currentObjectiveId,
  11: i32 currentAwardId,
  12: string totalObjectiveData,
  13: i32 reason,
}

struct QuestForTalentEdit {
   1: i32 questId,
   2: i32 startTime,
   3: i32 endTime,
   4: string talentAwardName,
   5: i32 currentObjectiveValue,
   6: string currentObjectiveData,
   7: i32 editObjectiveId,
   8: i32 editAwardId,
}

//---------------------

struct GameSessionShortInfo {
  1: i64 sessionid,
  2: list<AccountShortInfo> teamdocts,
  3: list<AccountShortInfo> teamadorni,
  4: RequestResult result,
}

struct BruteForceAccountShortInfo {
  1: i64 banTime,
  2: string email,
  3: i32 count,
  4: string ip,
  5: RequestResult result,
}

struct BannedIpShortInfo {
  1: i64 BanTime,
  2: i32 Accounts,
  3: i32 Tryes,
  4: string Ip,
}

struct BannedIpFullListInfo{
  1: list<BannedIpShortInfo> IpList,
  2: RequestResult result,
  3: i32 Count,
}



struct BroadcastMessage {
  1: string Locale
  2: string Text,
}

struct BroadcastInfo {
  1: i32 Id,
  2: string Title,
  3: list<BroadcastMessage> Messages,
  4: i64 TimeStart,
  5: i64 TimeFinish,
  6: i32 Interval,
  7: bool EnabledNow,
}

struct BroadcastListResponse{
  1: RequestResult result,
  2: list<BroadcastInfo> broadcastList,
}

struct BroadcastLocalesResponse{
  1: RequestResult result,
  2: list<string> locales,
}

struct BroadcastCreateResponse{
  1: RequestResult result,
  2: i32 id,
}

struct UpgradeHeroTalentsInfo {
  1: i32 UsesLeft,
}

struct UpgradeHeroTalentsInfoResponse {
  1: RequestResult result,
  2: UpgradeHeroTalentsInfo upgradeHeroTalentsInfo,
}

struct LampInfo {
  1: i32 Bonus,
  2: i32 GoldBonus,
  3: i32 Transaction,
  4: i64 Duration,
}
struct LampInfoResponse {
  1: RequestResult result,
  2: LampInfo lampInfo,
}

struct AccountInfoResponse{
  1: RequestResult result,
  2: AccountInfo accountInfo,
}

//QuestForTalent region

struct QuestsForTalentsInfoResponse{
  1: RequestResult result,
  2: list<QuestForTalentInfo> questsForTalentsInfo,
}

//----------

struct NickSnidResponse{
  1: RequestResult result,
  2: AccountShortInfo foundAccount,
}
struct NickSnidListResponse{
  1: RequestResult result,
  2: i32 totalFound,
  3: list<AccountShortInfo> foundAccounts,
}
struct LibraryResponse{
  1: RequestResult result,
  2: list<TalentInfo> libraryList,
}
struct HeroesResponse{
  1: RequestResult result,
  2: list<HeroInfo> heroesList,
}
struct TalentSetResponse{
  1: RequestResult result,
  2: list<TalentSetInfo> talentSetList,
}

struct SeasonInfoResponse{
  1: RequestResult result,
  2: list<SeasonInfo> seasonInfoList,
}

struct GuildMemberInfo{
  1: i64 auid,
  2: string nickname,
  3: bool isofficer,
  4: i32 addedTalentsDailyCount,
  5: i32 takenTalentsDailyCount,
}

struct GuildShortInfo {
  1: i64 guildid,
  2: string shortname,
  3: string fullname,
}

struct GuildInfo{
  1: i64 guildid,
  2: string shortname,
  3: string fullname,
  4: string messageoftheday,
  5: i64 leaderauid,
  6: string leadernickname,
  7: list<GuildMemberInfo> members,
  8: i64 guildExperience,
  9: i32 iconChangesCount,
  10: i32 guildLevel,
  11: i32 guildBankAddLimit,
  12: i32 guildBankTakeLimit,
  13: i32 cwguildpoints,
  14: i32 cwrating,
  15: GuildShortInfo suzerain,
  16: list<GuildShortInfo> vassals,
  17: i64 siegeendtime,
  18: i64 releaselocktime,
}

struct GuildInfoResponse{
  1: RequestResult result,
  2: GuildInfo guild,
}

struct GuildEditInfo {
  1: i64 guildid,
  2: string shortname,
  3: string fullname,
  4: string messageoftheday,
  5: i64 guildExperience,
  6: i32 cwguildpoints,
  7: i32 guildrating,
}

struct GuildMemberInfoResponse{
  1: RequestResult result,
  2: GuildMemberInfo guildMember,
}

struct SocServerVersionResponse{
  1: RequestResult result,
  2: string version,
}
struct StringDataResponse{
 1: RequestResult result,
 2: string data,
}
struct ServerActionResponse{
 1: RequestResult result,
 2: string error,
 3: i32 ec,
 4: string error_args,
}
struct PriceServiceInfo{
 1: i32 priceInGold,
 2: i32 paramValue,
}
struct PriceServiceDataResponse{
 1: ServerActionResponse result,
 2: list<PriceServiceInfo> prInfoList,
}
struct RegisterPaymentResponse{
 1: RequestResult result,
 2: i32 bonus_amount,
}
struct GetPaymentBonusActionsResponse{
 1: RequestResult result,
 2: list<string> actions,
}

enum QuestStatus {
  NotIssued,   // квест не выдан
  New,         // выданный, но еще не принятый квест
  Accepted,    // квест в процессе выполнения
  Complete     // завершенный квест
}

enum QuestChangeAction {
  Add,
  Accept,
  Complete,
  Delete
}

struct QuestInfo {
  1: i64 auid,
  2: i32 questid,        // CRC32
  3: string name,        // строковый идентификатор (в виде "h14_qB")
  4: QuestStatus status
}

struct QuestsInfoResponse{
  1: RequestResult result,
  2: list<QuestInfo> quests
}

struct BuildingInfo {
  1: i32 classid,
  2: i64 instanceid,
  3: i32 level,
  4: bool instorage
}

struct BuildingsInfoResponse{
  1: RequestResult result,
  2: i64 auid,
  3: list<BuildingInfo> buildings
}

struct SkinInfo {
  1: string persistentId
  2: i32 heroClassId
  3: bool owned          // Куплен игроком
  4: bool available      // Доступен для покупки
  5: i32 cost
}

struct SkinsResponse {
  1: RequestResult result
  2: i64 auid
  3: list<SkinInfo> skins
}

enum TalentUpgradeEntityType
{
  Rune = 0,
  Catalist = 1
}

struct TalentUpgradeEntityInfo {
  1: i64 instanceId
  2: string persistentId
  3: i32 chance
  4: TalentUpgradeEntityType type
  5: i32 talentLevelLimit
}

struct TalentUpgradeEntitiesResponse {
  1: RequestResult result
  2: i64 auid
  3: list<TalentUpgradeEntityInfo> entities
}

enum TicketState {
  NotActivated = 0,
  InTournament = 1,
  TournamentLost = 2,
}

enum TicketPriseState {
  HasNoPrise = 0,
  PriseInProgress = 1,
  HasPrise = 2,
}

enum TicketBoughtType
{
  BoughtForGold = 0,
  BoughtForSilver = 1,
  GiftedWithPayment = 2,
  GivenByGM = 3,
}

struct TournamentInfo {
  1: i32 Wins,
  2: i32 Losses,
  3: i64 LastGameTime,
  4: TicketPriseState TicketPriseState,
  5: TicketState State,
  6: TicketBoughtType TicketBoughtType,
  7: i32 MissedGames,
  8: bool IsSynchronized,
}

struct TournamentInfoResponse {
  1: RequestResult Result,
  2: TournamentInfo TournamentInfo
}

struct TournamentGamesInfo {
  1: i64 GameStartTime
  2: i32 GameDuration
  3: string SessionId
}

struct TournamentGamesInfoResponse{
  1: RequestResult Result,
  2: list<TournamentGamesInfo> TournamentGames
}

struct GiveTournamentTicketResponse {
  1: RequestResult Result,
}

struct GuildTalentInfo {
  1: i64 Owner,
  2: i64 Holder,
  3: i32 HeroClassId,
  4: i32 Points,
  5: i32 PersistentId,
  6: i64 InstanceId,
}

struct GuildBankTalentsResponse {
  1: RequestResult result,
  2: list<GuildTalentInfo> guildBankTalents,
}

enum UserOperationType {
  Ban,
  Mute,
  Unban,
  Unmute,
  Forgive,
  SetLeave,
}

struct SocialNetworksResponse{
  1: RequestResult result,
  2: list<string> socialnetworks,
}

struct LocaleInfo {
  1: string locale,
  2: string muid,
}

struct LocaleInfoResponse {
  1: RequestResult result,
  2: LocaleInfo info,
}

struct DynamicQuestInfo {
  1: string QuestText,
  2: string Locale,
  3: i32 Index,
  4: i32 PullId,
}

struct DynamicQuestInfoResponse {
  1: RequestResult result,
  2: list<DynamicQuestInfo> quests,
}

struct DynamicQuestByIdResponse {
  1: RequestResult result,
  2: DynamicQuestInfo quest,
}

struct AddDynamicQuestResponse {
  1: RequestResult result,
  2: i32 questId,
  3: string details
}

struct AuidsList {
  1: i32 index,
  2: string description,
  3: list<i64> auids,
}

struct AuidsListResponse
{
  1: RequestResult result,
  2: list<AuidsList> auidsLists,
}

struct AuidsListByIdResponse
{
  1: RequestResult result,
  2: AuidsList auidsLists,
}


struct DynamicQuestPull {
  1: string locale,
  2: i64 startTime,
  3: i64 endTime,
  4: i32 persistentId,
  5: list<i32> quests,
  6: bool hasRotation,
  7: bool isActive,
}

struct DynamicQuestPullsInfoResponse {
  1: RequestResult result,
  2: list<DynamicQuestPull> questPulls,
}

struct DynamicQuestPullByIdResponse {
  1: RequestResult result,
  2: DynamicQuestPull questPull,
}

struct Flag {
  1: string flagPersistentId,
  2: i32 flagPrice,
}

struct FlagResponse {
  1: RequestResult result,
  2: list<Flag> ownedFlags,
  3: list<Flag> adminFlags,
  4: list<Flag> notOwnedFlags,
}

struct AdminMessage {
  1: string messageTitle,
  2: string messageText,
  3: string gmLogin,
  4: i64 timestamp,
}

struct AdminMessagesResponse {
  1: RequestResult result,
  2: list<AdminMessage> adminMessages,
}

struct TalentsEventsResponse {
  1: RequestResult result,
  2: list<string> talentsEvents,
}

struct ResourceEventsResponse {
  1: RequestResult result,
  2: list<string> resourceEvents,
}

// EVENTS
// ======

enum ConfigEventType {
  Techs = 0,
  CustomEvent,
  EventMap,
  TalentDropRarity,
  NewsBanner,
  SkinGoldPrice,
  HeroPrice,
  TransmutationTalentsPerPerl,
  ReforgeTalentPrice,
  RerollShopSlots,
  RerollShopPrice,
  RerollShopGroupPrice,
  RerollShopGroupCurrencies,
  RerollShopGroupProbability,
  RerollShopSlotPrice,
  FirstBuyPrice,
  PremiumNotInactive,
  RerollShopSlotAmount,
  RerollShopGroupSlots,
  RerollShopBanner,
  RerollShopTooltip,
  RollEvent,
  QuestEvent,
  TradeEvent,
  SeasonEvent,
  DonateEvent
}

struct CommonEventInfo {
  1: i32 persistentId,
  2: ConfigEventType type,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
}

struct CommonEventsListResponse {
  1: RequestResult result,
  2: list<CommonEventInfo> availableEvents,
}

// Tech info event
// ---------------

struct TechsInfo {
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string type,
  5: i32 time,
  6: string description,
}

struct TechsInfoByIdResponse {
  1: RequestResult result,
  2: TechsInfo techInfo,
}

struct TechsInfosResponse {
  1: RequestResult result,
  2: list<TechsInfo> techInfos,
}

// Custom event
// ------------

struct CustomEvent {
  1: i32 persistentId,
  2: string type,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
}

struct CustomEventByIdResponse {
  1: RequestResult result,
  2: CustomEvent customEvent,
}

struct CustomEventsResponse {
  1: RequestResult result,
  2: list<CustomEvent> customEvents,
}

// Custom map event
// ----------------

struct CustomMap {
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string day,
  5: string startHour,
  6: string endHour,
  7: string mapDbid,
  8: string mapType,
  9: bool mapEnabled,
  10: bool enabled,
  11: string description,
}

struct CustomMapsResponse {
  1: RequestResult result,
  2: list<CustomMap> customMaps,
}

struct CustomMapByIdResponse {
  1: RequestResult result,
  2: CustomMap customMap,
}

// Talent drop rarity event
// ------------------------

struct TalentDropRarity {
  1: i32 classRar,
  2: i32 ordinary,
  3: i32 good,
  4: i32 excellent,
  5: i32 magnificent,
  6: i32 exclusive,
}

struct TalentDropRarityEvent {
  1: i32 persistentId,
  2: TalentDropRarity dropRarity,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
  7: bool premium,
}

struct TalentDropRarityByIdResponse {
  1: RequestResult result,
  2: TalentDropRarityEvent talentDropEvent,
  3: TalentDropRarity ordinaryDefault,
  4: TalentDropRarity premiumDefault,
}

struct TalentDropRaritiesResponse {
  1: RequestResult result,
  2: list<TalentDropRarityEvent> talentDropEvents,
  3: TalentDropRarity ordinaryDefault,
  4: TalentDropRarity premiumDefault,
}

// News banner
// -----------

struct NewsBanner {
  1: i32 persistentId,
  2: string buttonText,
  3: string windowCaption,
  4: string buttonUrl,
  5: string mainUrl,
  6: string tooltip,
  7: string mainUrlB,
  8: string LoginNetworks,
  9: i32 minLordLevel,
  10: bool hideIfViewed,
  11: i32 startTime,
  12: i32 endTime,
  13: string locale,
  14: bool enabled,
  15: string description,
  16: string extensionJson,
}

struct NewsBannerByIdResponse {
  1: RequestResult result,
  2: NewsBanner newsBanner,
}

struct NewsBannersResponse {
  1: RequestResult result,
  2: list<NewsBanner> newsBanners,
}

// Skin gold price event
// ---------------------

struct SkinGoldPrice {
  1: string persistentId,
  2: i32 heroClassId,
  3: i32 price,
}

struct SkinGoldPriceEvent {
  1: i32 persistentId,
  2: list<SkinGoldPrice> skins,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

 struct SkinGoldPriceByIdResponse {
  1: RequestResult result,
  2: SkinGoldPriceEvent skinEvent,
  3: list<SkinGoldPrice> defaultPrices,
}

struct SkinGoldPricesResponse {
  1: RequestResult result,
  2: list<SkinGoldPriceEvent> skinEvents,
  3: list<SkinGoldPrice> defaultPrices,
}

// Hero price event
// ----------------

struct HeroPrice {
  1: string persistentId,
  2: i32 silverPrice,
  3: i32 goldPrice,
}

struct HeroPriceEvent {
  1: i32 persistentId,
  2: list<HeroPrice> heroes,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct HeroPriceByIdResponse {
  1: RequestResult result,
  2: HeroPriceEvent heroEvent,
  3: list<HeroPrice> defaultPrices,
}

struct HeroPricesResponse {
  1: RequestResult result,
  2: list<HeroPriceEvent> heroEvents,
  3: list<HeroPrice> defaultPrices,
}

// Transmutation events
// --------------------

struct TransmutationTalentsPerPerl {
  1: i32 persistentId,
  2: i32 talents,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
}

struct TransmutationTalentsPerPerlByIdResponse {
  1: RequestResult result,
  2: TransmutationTalentsPerPerl talentsPerPerl,
  3: i32 talentsDefault,
}

struct TransmutationTalentsPerPerlResponse {
  1: RequestResult result,
  2: list<TransmutationTalentsPerPerl> talentsPerPerlEvents,
  3: i32 talentsDefault,
}

// Friend info
// ===========

struct FriendInfo {
  1: i64 auid,
  2: string nickname,
  3: string guildShortName,
}

struct FriendInfoResponse {
  1: RequestResult result,
  2: list<FriendInfo> friends,
}

// Reforge talent price event
// --------------------------

enum ETalentRarity
  {
    Class = 0,
    ordinary,
    good,
    excellent,
    magnificent,
    exclusive,
    outstanding,
  }

struct ReforgeTalentPrice
{
    1: ETalentRarity rarity,
    2: i32 rerollPrice,
    3: i32 upgradePrice,
    4: i32 talentsToUpgrade,

}
struct ReforgeTalentPrices
{
    1: i32 persistentId,
    2: i32 startTime,
    3: i32 endTime,
    4: bool enabled,
    5: string description,
    6: list<ReforgeTalentPrice> listReforgeTalentPrices
}

struct ReforgeTalentPriceResponse {
  1: RequestResult result,
  2: list<ReforgeTalentPrices> reforgeTalentPricesEvents,
  3: ReforgeTalentPrices defaultReforgeTalentPrices

}

struct ReforgeTalentPriceByIdResponse {
  1: RequestResult result,
  2: ReforgeTalentPrices defaultReforgeTalentPrices
  3: ReforgeTalentPrices reforgeTalentPrices
}

// Reroll shop plots event
// -----------------------

struct RerollShopSlots {
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: bool enabled,
  5: string description,
  6: i32 usualSlots,
  7: i32 premiumSlots,
  8: i32 maxActiveUsualSlots,
  9: i32 maxActivePremiumSlots,
}

struct RerollShopSlotsByIdResponse {
  1: RequestResult result,
  2: RerollShopSlots rerollShopSlots,
  3: i32 defaultUsualSlots,
  4: i32 defaultPremiumSlots,
  5: i32 defaultMaxActiveUsualSlots,
  6: i32 defaultMaxActivePremiumSlots,
}

struct RerollShopSlotsResponse {
  1: RequestResult result,
  2: list<RerollShopSlots> rerollShopSlotsEvents,
  3: i32 defaultUsualSlots,
  4: i32 defaultPremiumSlots,
  5: i32 defaultMaxActiveUsualSlots,
  6: i32 defaultMaxActivePremiumSlots,
}

// Reroll shop price event
// -----------------------

struct ResourceTableSmall {
  1: i32 resource1,
  2: i32 resource2,
  3: i32 resource3,
  4: i32 silver,
  5: i32 gold,
  6: i32 perl,
  7: i32 redPerl,
  8: string currencyId,
  9: i32 currency,
}

struct RerollShopPrice {
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: bool enabled,
  5: string description,
  6: ResourceTableSmall price
}

struct RerollShopPriceByIdResponse {
  1: RequestResult result,
  2: RerollShopPrice rerollShopPrice,
  3: ResourceTableSmall defaultRerollShopPrice,
}

struct RerollShopPricesResponse {
  1: RequestResult result,
  2: list<RerollShopPrice> rerollShopPriceEvents,
  3: ResourceTableSmall defaultRerollShopPrice,
}

// Reroll shop group price
// -----------------------

struct RerollShopGroupPrice {
  1: string persistentId,
  2: i32 minPrice,
  3: i32 maxPrice,
}

struct RerollShopGroupPriceEvent {
  1: i32 persistentId,
  2: list<RerollShopGroupPrice> groups,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopGroupPriceByIdResponse {
  1: RequestResult result,
  2: RerollShopGroupPriceEvent groupEvent,
  3: list<RerollShopGroupPrice> defaultPrices,
}

struct RerollShopGroupPricesResponse {
  1: RequestResult result,
  2: list<RerollShopGroupPriceEvent> groupEvents,
  3: list<RerollShopGroupPrice> defaultPrices,
}

// Reroll shop group currencies
// ----------------------------

struct RerollShopGroupCurrencies {
  1: string persistentId,
  2: i32 currencies
}

struct RerollShopGroupCurrenciesEvent {
  1: i32 persistentId,
  2: list<RerollShopGroupCurrencies> groups,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopGroupCurrenciesByIdResponse {
  1: RequestResult result,
  2: RerollShopGroupCurrenciesEvent groupEvent,
  3: list<RerollShopGroupCurrencies> defaultCurrencies,
}

struct RerollShopGroupCurrenciesResponse {
  1: RequestResult result,
  2: list<RerollShopGroupCurrenciesEvent> groupEvents,
  3: list<RerollShopGroupCurrencies> defaultCurrencies,
}

// Reroll shop slot price event
// ----------------------------

struct RerollShopSlotPrice {
  1: string persistentId,
  2: string groupId,
  3: i32 minPrice,
  4: i32 maxPrice,
}

struct RerollShopSlotPriceEvent {
  1: i32 persistentId,
  2: list<RerollShopSlotPrice> slots,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopSlotPriceByIdResponse {
  1: RequestResult result,
  2: RerollShopSlotPriceEvent slotEvent,
  3: list<RerollShopSlotPrice> defaultPrices,
}

struct RerollShopSlotPricesResponse {
  1: RequestResult result,
  2: list<RerollShopSlotPriceEvent> slotEvents,
  3: list<RerollShopSlotPrice> defaultPrices,
}

// Reroll shop group probability event
// im: добавил для поля для заточки выпадаемых в этой группе талантов (имхо костыль)
// -----------------------------------

struct RerollShopGroupProbability {
  1: string persistentId,
  2: i32 rerollTime,
  3: i32 probability,
  4: i32 minUpgradeLevel,
  5: i32 maxUpgradeLevel
}

struct RerollShopGroupProbabilityEvent {
  1: i32 persistentId,
  2: list<RerollShopGroupProbability> groups,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopGroupProbabilityByIdResponse {
  1: RequestResult result,
  2: RerollShopGroupProbabilityEvent groupEvent,
  3: list<RerollShopGroupProbability> defaultProbability,
}

struct RerollShopGroupProbabilitiesResponse {
  1: RequestResult result,
  2: list<RerollShopGroupProbabilityEvent> groupEvents,
  3: list<RerollShopGroupProbability> defaultProbability,
}

// First buy gold price event
// --------------------------

struct FirstBuyGoldPrice {
  1: string persistentId,
  2: i32 price,
}

struct FirstBuyGoldPriceEvent {
  1: i32 persistentId,
  2: list<FirstBuyGoldPrice> firstBuys,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

 struct FirstBuyGoldPriceByIdResponse {
  1: RequestResult result,
  2: FirstBuyGoldPriceEvent firstBuyEvent,
  3: list<FirstBuyGoldPrice> defaultPrices,
}

struct FirstBuyGoldPricesResponse {
  1: RequestResult result,
  2: list<FirstBuyGoldPriceEvent> firstBuyEvents,
  3: list<FirstBuyGoldPrice> defaultPrices,
}

// Reroll shop premium not inactive event
// --------------------------------------

struct RerollShopPremiumNotInactiveEvent {
  1: i32 persistentId,
  2: bool isInactive,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
}

struct RerollShopPremiumNotInactiveByIdResponse {
  1: RequestResult result,
  2: RerollShopPremiumNotInactiveEvent rerollShopPremiumNotInactive,
  3: bool rerollShopPremiumNotInactiveDefault,
}

struct RerollShopPremiumNotInactiveResponse {
  1: RequestResult result,
  2: list<RerollShopPremiumNotInactiveEvent> rerollShopPremiumNotInactiveEvents,
  3: bool rerollShopPremiumNotInactiveDefault,
}

// Reroll shop slot amout event
// ----------------------------

struct RerollShopSlotAmount {
  1: string persistentId,
  2: string groupId,
  3: i32 amount,
}

struct RerollShopSlotAmountEvent {
  1: i32 persistentId,
  2: list<RerollShopSlotAmount> slots,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopSlotAmountByIdResponse {
  1: RequestResult result,
  2: RerollShopSlotAmountEvent slotEvent,
  3: list<RerollShopSlotAmount> defaultAmounts,
}

struct RerollShopSlotAmountsResponse {
  1: RequestResult result,
  2: list<RerollShopSlotAmountEvent> slotEvents,
  3: list<RerollShopSlotAmount> defaultAmounts,
}

// Reroll shop group slots events
// ------------------------------

struct RerollShopGroupSlots {
  1: list<string> persistentIds,
  2: string groupId,
}

struct RerollShopGroupSlotsEvent {
  1: i32 persistentId,
  2: list<RerollShopGroupSlots> groups,
  3: i32 startTime,
  4: i32 endTime,
  5: bool enabled,
  6: string description,
 }

struct RerollShopGroupSlotsByIdResponse {
  1: RequestResult result,
  2: RerollShopGroupSlotsEvent slotEvent,
  3: list<RerollShopGroupSlots> defaultSlots,
}

struct RerollShopGroupSlotsResponse {
  1: RequestResult result,
  2: list<RerollShopGroupSlotsEvent> slotEvents,
  3: list<RerollShopGroupSlots> defaultSlots,
}

// User dumps
// ==========

struct UserDumpsDataResponse {
   1: list<string> avaialbleBackups,
   2: RequestResult result
 }

// Mass operations
// ---------------

enum MassOperationType
  {
    UnlockFlag = 0,
    LockFlag,
    AddTalent,
    AddTalents,
    PremiumAccount,
    SendMessageToUser,
    GiveLamp,
    AddSkin,
    DeleteSkin,
    UnlockHero,
    AddBuilding,
    EditAccount,
    FlushServerId,
  }

struct MassOperationInfo {
  1: MassOperationType type,
  2: list<i64> auids,
  3: string flagId,
  4: i32 talentId,
  5: list<i32> talentIds,
  6: i32 days,
  7: string message,
  8: LampInfo lampInfo,
  9: string skinId,
  10: i32 heroId,
  11: i32 buildingId,
  12: AccountEdit accountEdit
}

struct MassOperationResult {
  1: i32 operationId,
  2: MassOperationType type,
  3: i32 startTime,
  4: i32 endTime,
  5: string failedAuids,
  6: bool finished,
}

struct MassOperationsResultResponse
{
  1: RequestResult result,
  2: list<MassOperationResult> massOperations
}

// Reroll shop banner events
// -------------------------

struct RerollShopBanner {
  1: i32 persistentId,
  2: string mainUrl,
  3: i32 startTime,
  4: i32 endTime,
  5: string locale,
  6: bool enabled,
  7: string description,
}

struct RerollShopBannerByIdResponse {
  1: RequestResult result,
  2: RerollShopBanner rerollShopBanner,
}

struct RerollShopBannersResponse {
  1: RequestResult result,
  2: list<RerollShopBanner> rerollShopBanners,
}

// Reroll shop tooltip events
// --------------------------

struct RerollShopTooltip {
  1: i32 persistentId,
  2: string tooltip,
  3: i32 startTime,
  4: i32 endTime,
  5: string locale,
  6: bool enabled,
  7: string description,
}

struct RerollShopTooltipByIdResponse {
  1: RequestResult result,
  2: RerollShopTooltip rerollShopTooltip,
}

struct RerollShopTooltipsResponse {
  1: RequestResult result,
  2: list<RerollShopTooltip> rerollShopTooltips,
}

// GW events
// -----------

struct GWEventModel {
  1: string persistentId,
  2: bool enabled,
  3: i32 pointsToAddLimit,
  4: i32 endTime,
  5: string locale,
  6: i64 points,
  7: i64 limit,
  8: i32 event_index,
}

struct GWEventsModelByIdResponse {
  1: RequestResult result,
  2: GWEventModel gwEvent,
}

struct GWEventsModelResponse {
  1: RequestResult result,
  2: list<GWEventModel> gwEvents,
}

// -----------

// Roll events
// -----------

enum RollEventItemType { // Identical to lobby's ConfigData.cs > RollEventItemType
  Resource,
  Talent,
  Skin,
  Hero,
  Lootbox,
}

struct RollEventItem {
  1: RollEventItemType itemType,
  2: string persistentId,
  3: ResourceTableSmall resource,
  4: double ratio,
}

enum RollEventRuleType { // Identical to lobby's ConfigData.cs > RollEventRuleType
  Simple,
  Reforge,
}

struct RollEventRule {
  1: RollEventRuleType ruleType,
  2: string description,
  3: string titleLocalized,
  4: string textLocalized,
  5: ResourceTableSmall price,
  6: list<RollEventItem> rewards,
  7: list<RollEventItem> reforgeSource,
}

struct RollEvent {
  // Common
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string locale,
  5: bool enabled,
  6: string description,
  // Specific
  7: string title,
  8: string image,
  9: string text,
  10: list<string> currencyIds,
  11: list<RollEventRule> rolls,
  12: string completionTalentId,
  13: i32 completionTalentRatio,
  14: i32 guid,
}

struct RollEventByIdResponse {
  1: RequestResult result,
  2: RollEvent rollEvent,
}

struct RollEventsResponse {
  1: RequestResult result,
  2: list<RollEvent> rollEvents,
}

// Quest events
// ------------

struct QuestEventStageStepVariant {
  1: string message,
  2: string winMessage,
  3: string loseMessage,
  4: double winRatioBase,
  5: double winRatioGold,
  6: ResourceTableSmall price,
}

struct QuestEventStageStep {
  1: string title,
  2: list<QuestEventStageStepVariant> variants,
}

struct QuestEventStage {
  1: string title,
  2: string text,
  3: string image;
  4: RollEventItem reward,
  5: list<QuestEventStageStep> steps,
  6: RollEventItem loseReward,
}

struct QuestEvent {
  // Common
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string locale,
  5: bool enabled,
  6: string description,
  // Specific
  7: string title,
  8: string text,
  9: list<string> currencyIds,
  10: list<QuestEventStage> stages,
  11: string completionTalentId,
  12: i32 completionTalentRatio,
  13: i32 guid,
}

struct QuestEventByIdResponse {
  1: RequestResult result,
  2: QuestEvent questEvent,
}

struct QuestEventsResponse {
  1: RequestResult result,
  2: list<QuestEvent> questEvents,
}


// Trade events
// ------------

struct TradeGroupMemberModel {
  1: string name,
  2: string image,
  3: string currencyName,
  4: double currencyCostPerExp
  5: RollEventItem rewardA,
  6: i32 rewardACost,
  7: RollEventItem rewardB,
  8: i32 rewardBCost,
}

struct TradeEventGroupModel {
  1: string name,
  2: list<TradeGroupMemberModel> tradeGroupMembers,
}

struct ExperienceRewardRelation {
  1: RollEventItem reward,
  2: i32 rewardCount,
  3: i32 experience,
  4: bool isMinor
}

struct WorldRatingRewardRelation {
  1: RollEventItem reward,
  2: i32 rewardCount,
  3: i32 worldPosition,
}

struct TradeEventModel {
  // Common
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string locale,
  5: bool enabled,
  6: string description,
  // Specific
  7: string title,
  8: string text,
  9: string completionTalentId,
  10: i32 completionTalentRatio,
  11: string experienceCurrencyName,
  12: string bannerUrl,
  13: list<TradeEventGroupModel> tradeEventGroups,
  14: list<WorldRatingRewardRelation> worldRatingRewardRelations,
  15: list<ExperienceRewardRelation> experienceRewardRelations,
  16: string rewardsBlockTitle,
  17: i32 guid,
}

struct TradeEventByIdResponse {
  1: RequestResult result,
  2: TradeEventModel tradeEvent,
}

struct TradeEventsResponse {
  1: RequestResult result,
  2: list<TradeEventModel> tradeEvents,
}

// Season events
// ------------

struct SeasonEventShopItem {
  1: string name,
  2: string image,
  3: string lootboxId,
  4: i32 cost,
  5: i32 limit
}

struct SeasonEventShopGroup {
  1: string name,
  2: list<SeasonEventShopItem> items,
}

struct SeasonProgressRewardRelation {
  1: RollEventItem reward,
  2: i32 rewardCount,
  3: i32 requiredProgress
}

struct SeasonEvent {
  // Common
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: string locale,
  5: bool enabled,
  6: string description,
  // Specific
  7: string title,
  8: string text,
  9: string completionTalentId,
  10: i32 completionTalentRatio,
  11: string shopCurrencyId,
  12: string rewardsCurrencyId,
  13: string bannerUrl,
  14: list<SeasonEventShopGroup> shopGroups,
  15: list<WorldRatingRewardRelation> worldRatingRewardRelations,
  16: list<SeasonProgressRewardRelation> progressRewardRelations,
  17: string rewardsBlockTitle,
  18: i32 guid,
}

struct SeasonEventByIdResponse {
  1: RequestResult result,
  2: SeasonEvent seasonEvent,
}

struct SeasonEventsResponse {
  1: RequestResult result,
  2: list<SeasonEvent> seasonEvents,
}

// Donate Event
// ---------------------

struct DonateReward {
  1: list<string> lootboxes,
}

struct DonateRange {
  1: i32 amountFrom,
  2: i32 amountTo,
  3: list<DonateReward> rewards,
}

struct DonateEvent {
  1: i32 persistentId,
  2: i32 startTime,
  3: i32 endTime,
  4: bool enabled,
  5: string description,
  6: list<DonateRange> ranges,
 }

 struct DonateEventByIdResponse {
  1: RequestResult result,
  2: DonateEvent donateEvent,
}

struct DonateEventsResponse {
  1: RequestResult result,
  2: list<DonateEvent> donateEvents,
}

// MAIN SERVICE DEFINITION
//========================

service AccountManagement {
  
  //Localized strings
  

  //view account info methods
  AccountInfoResponse GetAccountBySNUid(1: string snid, 2: string snuid),
  AccountInfoResponse GetAccountByAuid(1: i64 auid),
  NickSnidResponse FindNicknameExact(1: string nickName),
  NickSnidListResponse FindNicknamesLike(1: string nickName, 2: i32 page_offset, 3: i32 page_size),
  SocialNetworksResponse GetSocialNetworks(),
  LocaleInfoResponse GetLocaleInfoBySNUid(1: string snid, 2: string snuid),
  LocaleInfoResponse GetLocaleInfoByAuid(1: i64 auid),
  
  // Player Data Control
  NickSnidResponse FindPlayerByNickname(1: string nickname),
  NickSnidResponse FindPlayerByEmail(1: string email),
  NickSnidResponse PlayerChangeEmail(1: string email, 2: string newEmail, 3: string newPass),
  NickSnidResponse PlayerRemoveNickname(1: string email, 2: string nickname),

  QuestsForTalentsInfoResponse GetAccountQuestsForTalentsByAuid(1: string login),
  RequestResult EditQuestForTalent(1: string login, 2: QuestForTalentEdit questForTalentEdit, 3: string gmLogin, 4:  string extra_comment=''),

  RequestResult EditAccount(1: string login, 2: AccountEdit accountEdit, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult EditAccountResources(1: string login, 2: AccountEdit accountEdit, 3: string gmLogin, 4:  string extra_comment=''),
  LibraryResponse GetAccountLibrary(1: string login),
  GameSessionShortInfo GetGameSession(1: i32 sessionid),

  BruteForceAccountShortInfo GetBruteForceAccount(1: string email),
  RequestResult UnBanBruteForceAccount(1: string email),

  BannedIpFullListInfo GetBannedIp(1: i32 limit, 2: i32 skip),
  RequestResult UnBanIp(1: string ip),


  RequestResult EditFreeChanges(1: string login, 2: string gmLogin, 3: i32 nickChanges, 4: i32 fractionChanges ),

  //WebIMMethods
  RequestResult AddResources(1: i64 auid, 2: string ResourceType, 3: i32 amount),

  HeroesResponse GetAccountHeroes(1: string login),
  RequestResult UnlockHero(1: string login, 2: i32 heroClassId, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult EditHero(1: string login, 2: HeroInfo heroEdit, 3: string gmLogin),
  RequestResult LockHero(1: string login, 2: i64 heroInstanceId, 3: string gmLogin),

  RequestResult EditSeasonAwards(1:string login, 2: SeasonAwards awardEdit, 3: string gmLogin),
  RequestResult EditSeasonInfo(1:string login, 2: i64 heroInstanceId, 3: SeasonInfo seasonEdit, 4: string gmLogin),

  TalentSetResponse GetHeroTalentSet(1: string login, 2: i64 heroInstanceId),
  SeasonInfoResponse GetHeroSeasonsInfo(1: string login, 2: i64 heroInstanceId),
  RequestResult AddTalent(1: string login, 2: i32 talentClassId, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult AddTalents(1: string login, 2: list<i32> talentIds, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult EditTalent(1: string login, 2: TalentInfo talentEdit, 3: string gmLogin),
  RequestResult DeleteTalent(1: string login, 2: i64 talentInstanceId, 3: string gmLogin),

  RequestResult MoveTalentFromTalentSetToLibrary(1: string login, 2: i64 heroInstanceId, 3: i64 talentInstanceId, 4: string gmLogin),
  RequestResult MoveTalentFromLibraryToTalentSet(1: string login, 2: i64 heroInstanceId, 3: i64 talentInstanceId, 4: i32 slot, 5: string gmLogin),
  RequestResult RemoveTalentFromTalentSet(1: string login, 2: i64 heroInstanceId, 3: i64 talentInstanceId, 4: i32 talentSetId, 5: string gmLogin),

  SkinsResponse GetAccountSkins(1: i64 auid),
  RequestResult AddSkin(1: i64 auid, 2: string skinPersistentId, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult DeleteSkin(1: i64 auid, 2: string skinPersistentId, 3: string gmLogin, 4:  string extra_comment=''),

  TalentUpgradeEntitiesResponse GetAccountTalentUpgradeEntities(1: i64 auid),
  RequestResult DeleteTalentUpgradeEntity(1: i64 auid, 2: i64 instanceId, 3: string gmLogin, 4:  string extra_comment=''),
  //RequestResult DeleteSkin(1: i64 auid, 2: string skinPersistentId, 3: string gmLogin, 4:  string extra_comment=''),

  BuildingsInfoResponse GetAccountBuildings(1: i64 auid),
  RequestResult MoveBuildingToStorage(1: i64 auid, 2: i64 buildingInstanceId, 3: string gmLogin),
  RequestResult AddBuilding(1: i64 auid, 2: i32 buildingClassId, 3: i32 level, 4: string gmLogin, 5:  string extra_comment=''),
  RequestResult DeleteBuilding(1: i64 auid, 2: i64 buildingInstanceId, 3: string gmLogin),

  RequestResult GiveLamp( 1: string login, 2: LampInfo lampInfo, 3: string gmLogin, 4:  string extra_comment=''),
  LampInfoResponse GetLampInfo( 1: string login ),
  
  RequestResult GiveUpgradeHeroTalents( 1: string login, 2: UpgradeHeroTalentsInfo lampInfo, 3: string gmLogin, 4:  string extra_comment=''),
  UpgradeHeroTalentsInfoResponse GetUpgradeHeroTalentsInfo( 1: string login ),

  RequestResult DisjointSN(1: i64 auid, 2: string snid),
  RequestResult ChangeFSN(1: i64 auid, 2: string snid),
  RequestResult DeleteSAAccount(1: i64 auid);

  //Tournament info
  TournamentInfoResponse GetAccountTournamentInfo(1: string login),
  RequestResult EditTournamentInfo(1: string login, 2: TournamentInfo tournamentInfo, 3: string gmLogin),
  GiveTournamentTicketResponse GiveTournamentTicket(1: string login),
  TournamentGamesInfoResponse GetAccountTournamentGames(1: string login),

  //guild methods
  GuildInfoResponse GetGuildById(1: i64 guildid),
  GuildInfoResponse GetGuildByName(1: string shortname, 2: string fullname),
  GuildMemberInfoResponse GetGuildMemberById(1: i64 guildid, 2: i64 auid),
  RequestResult EditGuild(1: GuildEditInfo info, 2: string gmlogin),
  RequestResult ChangeGuildLeader(1: i64 guildid, 2: i64 auid, 3: string gmLogin),
  RequestResult RemoveGuildMembers(1: i64 guildid, 2: list<i64> auids, 3: string gmLogin),
  RequestResult ViewGuildMembers(1: i64 guildid),
  RequestResult EditGuildMember(1: i64 guildid, 2: GuildMemberInfo member, 3: string gmLogin),
  RequestResult SetGuildIcon(1: i64 guildid, 2: binary image),
  RequestResult SwitchToNewGuildIcon(1: i64 guildid, 2: string gmLogin),
  ServerActionResponse TryToPayForGuildIconChange(1: i64 leaderauid, 2: i32 changeiter),
  RequestResult AcquireGuildLock(1: i64 guildid, 2: string gmlogin),
  RequestResult ReleaseGuildLock(1: i64 guildid, 2: string gmlogin),
  RequestResult StopGuildSiege(1: i64 targetguildid, 2: string gmlogin),
  RequestResult AddGuildSuzerain(1: i64 guildid, 2: i64 suzerainguildid, 3: string gmlogin),
  RequestResult RemoveGuildSuzerain(1: i64 guildid, 2: string gmlogin),
  StringDataResponse GetFullGuildDump(1: i64 guildid, 2: bool zip),

  // guild bank methods
  GuildBankTalentsResponse GetFreeGuildBankTalents(1: i64 guildid),
  GuildBankTalentsResponse GetTakenGuildBankTalents(1: i64 guildid),
  RequestResult ReturnTalentToOwner(1: i64 guildid, 2: i64 talentId, 3: string gmLogin),
  RequestResult ReturnTalentToGuildBank(1: i64 guildid, 2: i64 talentId, 3: string gmLogin),

  //game master actions over user methods
  RequestResult SendMessageToUser(1: string login, 2: i64 auid, 3: string messageTitle, 4: string messageText, 5: string gmLogin, 6:  string extra_comment='' ),
  AdminMessagesResponse GetAccountAdminMessages(1: string login),
  RequestResult UserOperation(1: i64 auid, 2: UserOperationType type, 3: i32 minutes, 4: string reason, 5: list<i32> claims, 6: string gmLogin, 7: list<i64> claimAuids, 8: i32 points),
  RequestResult ResetUserAccount(1: string login, 2: string gmLogin),
  RequestResult DeleteUserAccount(1: string login, 2: string gmLogin),
  RequestResult KickUser(1: string login, 2: string gmLogin),
  StringDataResponse EditNickname( 1: string login, 2: string gmLogin, 3: string nickname ),

  ServerActionResponse PayEditNickname( 1: string login, 2: string nickname ),
  ServerActionResponse PayChangeFraction( 1: string login, 2: i32 fraction ),
  PriceServiceDataResponse GetPrices( 1: string login, 2: PayServiceType servicetype, 5:  string extra_comment='' ),
  ServerActionResponse BuyService( 1: string login, 2: PayServiceType servicetype, 3: i32 paramValue ),

  RequestResult PayService( 1: string login, 2: PayServiceType servicetype, 3: i32 paramValue, 4: string gmLogin ),

  RequestResult BuyTournamentTicket( 1: string login, 2: PayTicketType pttype ),

  //broadcast
  BroadcastCreateResponse CreateBroadcast(1: BroadcastInfo createInfo, 2: string gmLogin),
  BroadcastLocalesResponse GetBroadcastLocales(),
  RequestResult EditBroadcast(1: BroadcastInfo editInfo, 2: string gmLogin),
  RequestResult DeleteBroadcast(1: i32 id, 2: string gmLogin),
  BroadcastListResponse GetBroadcastList(1: i32 skipLines, 2: i32 takeLines),

  RequestResult StartMessageRotation(1: i32 id, 2: string gmLogin),
  RequestResult StopMessageRotation(1: i32 id, 2: string gmLogin),

  SocServerVersionResponse GetSocServerVersion(),

  // user data dumps
  StringDataResponse GetFullUserDump(1: string login, 2: bool zip),
  RequestResult ApplyFullUserDump(1: string login, 2: string dumpdata),
  RequestResult RemoveFakeAuid(1: string login),
  UserDumpsDataResponse GetBackups(),
  StringDataResponse GetBrokenUserDump(1: string login, 2: string date, 3: bool zip),
  StringDataResponse GetBrokenUserDumpByNickname(1: string nickname, 2: string date, 3: bool zip),

  StringDataResponse CheckAccountValidity(1: string login),
  RequestResult FixAccount(1: string login, 2: string gmLogin),
  RequestResult ActivateEmail(1: string email, 2: string gmLogin),
  RequestResult FlushServerId(1: string login, 2: string gmLogin),

  // CBT user restrictions
  RequestResult AddUserRestriction(1: string snid, 2: string snuid, 3: string cbtAccessKey),

  // acc.db hack, set some acc.db.<key> = <value> (use value="" to clear)
  RequestResult EditAccountDbValue(1: string login, 2: string gmLogin, 3: string key, 4: string value),

  RegisterPaymentResponse RegisterPayment( 1: i64 auid, 2: i32 amount, 3: string source, 4: string txnid ),
  GetPaymentBonusActionsResponse GetPaymentBonusActions( 1: i64 auid ),
  RequestResult ReplenishUserGold( 1: i64 auid, 2: i32 amount, 3: string payment_system ),
  RequestResult UpdateUserGold( 1: i64 auid ),

  // quests
  QuestsInfoResponse GetQuests(1: i64 auid),
  ServerActionResponse ChangeQuest(1: i64 auid, 2: i32 questid, 3: QuestChangeAction action, 4: string gmLogin),

  // show geolocated rates
  RequestResult UpdateGeoshowFlag(1: i64 auid, 2: bool isAllowed),

  RequestResult ApplyDLC( 1: i64 auid, 2: string dlcid ),

  DynamicQuestInfoResponse GetDynamicQuestInfo(),
  DynamicQuestByIdResponse GetDynamicQuestById(1: i32 index),
  AddDynamicQuestResponse AddDynamicQuest( 1: string questData, 2: string locale, 3: string gmLogin ),
  RequestResult RemoveDynamicQuest( 1: i32 index, 2: string locale ),
  RequestResult EditDynamicQuest( 1: i32 index, 2: string locale, 3: string questData ),
  DynamicQuestPullsInfoResponse GetDynamicQuestPullsInfo(),
  DynamicQuestPullByIdResponse GetDynamicQuestPullById(1: i32 pullId),

  AuidsListResponse GetAuidsLists(),
  AuidsListByIdResponse GetAuidsListById(1: i32 index),
  RequestResult AddAuidsList( 1: AuidsList auidsList, 2: string gmLogin ),
  RequestResult EditAuidsList( 1: AuidsList auidsList, 2: string gmLogin ),
  RequestResult RemoveAuidsList( 1: i32 index ),

  RequestResult AddDynamicQuestPull( 1: DynamicQuestPull questPull, 2: string gmLogin ),
  RequestResult EditDynamicQuestPull( 1: DynamicQuestPull questPull, 2: string gmLogin ),
  RequestResult RemoveDynamicQuestPull( 1: i32 index, 2: string locale, 3: string gmLogin ),
  RequestResult AddDynamicQuestsToPull( 1: i32 pullId, 2: list<i32> questIds, 3: string locale, 4: string gmLogin ),
  RequestResult RemoveDynamicQuestsFromPull( 1: i32 pullId, 2: list<i32> questIds, 3: string locale, 4: string gmLogin ),

  // paid flags
  FlagResponse GetAccountFlags(1: string login),
  RequestResult UnlockFlag(1: string login, 2: string flagPersistentId, 3: string gmLogin, 4:  string extra_comment=''),
  RequestResult LockFlag(1: string login, 2: string flagPersistentId, 3: string gmLogin, 4:  string extra_comment=''),

  // bind auid to the particular geolocation
  RequestResult BindToGeolocation(1: i64 auid, 2: string country, 3: string region, 4: string city, 5: string gmLogin),

  TalentsEventsResponse GetTalentsEvents(),
  ResourceEventsResponse GetResourceEvents(),

  RequestResult AddMassOperation(1: MassOperationInfo massOperation, 2: string gmLogin),
  MassOperationsResultResponse GetMassOperationsInfo(),
  RequestResult DeleteMassOperationInfo(1: i32 operaionId),

  // EVENTS API
  CommonEventsListResponse GetAvailableEvents(),
  RequestResult ChangeEventStateById(1: i32 persistentId, 2: bool state),
  RequestResult DeleteEventById(1: i32 persistentId),
  // Tech info events
  TechsInfosResponse GetTechsInfos(),
  TechsInfoByIdResponse GetTechsInfoById(1: i32 persistentId),
  RequestResult AddTechs(1: TechsInfo techInfo),
  RequestResult EditTechs(1: TechsInfo techInfo),
  // Custom event
  CustomEventsResponse GetCustomEvents(),
  CustomEventByIdResponse GetCustomEventById(1: i32 persistentId),
  RequestResult AddCustomEvent(1: CustomEvent customEvent),
  RequestResult EditCustomEvent(1: CustomEvent customEvent),
  // Custom map event
  CustomMapsResponse GetCustomMaps(),
  CustomMapByIdResponse GetCustomMapById(1: i32 persistentId),
  RequestResult AddCustomMap(1: CustomMap customMap),
  RequestResult EditCustomMap(1: CustomMap customMap),
  // Talent drop rarity event
  TalentDropRaritiesResponse GetTalentDropRarities(),
  TalentDropRarityByIdResponse GetTalentDropRarityById(1: i32 persistentId),
  RequestResult AddTalentDropRarities(1: TalentDropRarityEvent dropRarity),
  RequestResult EditTalentDropRarities(1: TalentDropRarityEvent dropRarity),
  // News banner evens
  NewsBannersResponse GetNewsBanners(),
  NewsBannerByIdResponse GetNewsBannerById(1: i32 persistentId),
  RequestResult AddNewsBanner(1: NewsBanner banner),
  RequestResult EditNewsBanner(1: NewsBanner banner),
  // Skin price events
  SkinGoldPricesResponse GetSkinPrices(),
  SkinGoldPriceByIdResponse GetSkinPriceById(1: i32 persistentId),
  RequestResult AddSkinPricesEvent(1: SkinGoldPriceEvent skinEvent),
  RequestResult EditSkinPricesEvent(1: SkinGoldPriceEvent skinEvent),
  // Hero price events
  HeroPricesResponse GetHeroPrices(),
  HeroPriceByIdResponse GetHeroPriceById(1: i32 persistentId),
  RequestResult AddHeroPricesEvent(1: HeroPriceEvent skinEvent),
  RequestResult EditHeroPricesEvent(1: HeroPriceEvent skinEvent),
  // Transmutation events
  TransmutationTalentsPerPerlResponse GetTransmutationTalentsPerPerl(),
  TransmutationTalentsPerPerlByIdResponse GetTransmutationTalentsPerPerlById(1: i32 persistentId),
  RequestResult AddTalentPerPerlEvent(1: TransmutationTalentsPerPerl talentsPerPerlEvent),
  RequestResult EditTalentPerPerlEvent(1: TransmutationTalentsPerPerl talentsPerPerlEvent),
  // Reroll shop slot events
  RerollShopSlotsResponse GetRerollShopSlots(),
  RerollShopSlotsByIdResponse GetRerollShopSlotsById(1: i32 persistentId),
  RequestResult AddRerollShopSlotsEvent(1: RerollShopSlots rerollShopSlotsEvent),
  RequestResult EditRerollShopSlotsEvent(1: RerollShopSlots rerollShopSlotsEvent),
  // Reroll shop price events
  RerollShopPricesResponse GetRerollShopPrices(),
  RerollShopPriceByIdResponse GetRerollShopPriceById(1: i32 persistentId),
  RequestResult AddRerollShopPriceEvent(1: RerollShopPrice rerollShopPriceEvent),
  RequestResult EditRerollShopPriceEvent(1: RerollShopPrice rerollShopPriceEvent),
  // Reforge talent price events
  ReforgeTalentPriceResponse GetReforgeTalentPrice(),
  ReforgeTalentPriceByIdResponse GetReforgeTalentPriceById(1: i32 persistentId),
  RequestResult AddReforgeTalentPriceEvent(1: ReforgeTalentPrices reforgeTalentPriceEvent),
  RequestResult EditReforgeTalentPriceEvent(1: ReforgeTalentPrices reforgeTalentPriceEvent),
  // Reroll shop group price events
  RerollShopGroupPricesResponse GetRerollShopGroupPrices(),
  RerollShopGroupPriceByIdResponse GetRerollShopGroupPriceById(1: i32 persistentId),
  RequestResult AddRerollShopGroupPricesEvent(1: RerollShopGroupPriceEvent groupEvent),
  RequestResult EditRerollShopGroupPricesEvent(1: RerollShopGroupPriceEvent groupEvent),
  // Reroll shop group currency events
  RerollShopGroupCurrenciesResponse GetRerollShopGroupCurrencies(),
  RerollShopGroupCurrenciesByIdResponse GetRerollShopGroupCurrenciesById(1: i32 persistentId),
  RequestResult AddRerollShopGroupCurrenciesEvent(1: RerollShopGroupCurrenciesEvent groupEvent),
  RequestResult EditRerollShopGroupCurrenciesEvent(1: RerollShopGroupCurrenciesEvent groupEvent),
  // Reroll shop slot price events
  RerollShopSlotPricesResponse GetRerollShopSlotPrices(),
  RerollShopSlotPriceByIdResponse GetRerollShopSlotPriceById(1: i32 persistentId),
  RequestResult AddRerollShopSlotPricesEvent(1: RerollShopSlotPriceEvent groupEvent),
  RequestResult EditRerollShopSlotPricesEvent(1: RerollShopSlotPriceEvent groupEvent),
  // Reroll shop group probability events
  RerollShopGroupProbabilitiesResponse GetRerollShopGroupProbabilities(),
  RerollShopGroupProbabilityByIdResponse GetRerollShopGroupProbabilityById(1: i32 persistentId),
  RequestResult AddRerollShopGroupProbabilityEvent(1: RerollShopGroupProbabilityEvent groupEvent),
  RequestResult EditRerollShopGroupProbabilityEvent(1: RerollShopGroupProbabilityEvent groupEvent),
  // Reroll shop slot amount events
  RerollShopSlotAmountsResponse GetRerollShopSlotAmount(),
  RerollShopSlotAmountByIdResponse GetRerollShopSlotAmountById(1: i32 persistentId),
  RequestResult AddRerollShopSlotAmountsEvent(1: RerollShopSlotAmountEvent groupEvent),
  RequestResult EditRerollShopSlotAmountsEvent(1: RerollShopSlotAmountEvent groupEvent),
  // First buy price events
  FirstBuyGoldPricesResponse GetFirstBuyPrices(),
  FirstBuyGoldPriceByIdResponse GetFirstBuyPriceById(1: i32 persistentId),
  RequestResult AddFirstBuyPricesEvent(1: FirstBuyGoldPriceEvent firstBuyEvent),
  RequestResult EditFirstBuyPricesEvent(1: FirstBuyGoldPriceEvent firstBuyEvent),
  // Reroll shop premium not in active events
  RerollShopPremiumNotInactiveResponse GetRerollShopPremiumNotInactive(),
  RerollShopPremiumNotInactiveByIdResponse GetRerollShopPremiumNotInactiveById(1: i32 persistentId),
  RequestResult AddRerollShopPremiumNotInactiveEvent(1: RerollShopPremiumNotInactiveEvent rerollShopPremiumNotInactiveEvent),
  RequestResult EditRerollShopPremiumNotInactiveEvent(1: RerollShopPremiumNotInactiveEvent rerollShopPremiumNotInactiveEvent),
  // Reroll shop group slots events
  RerollShopGroupSlotsResponse GetRerollShopGroupSlots(),
  RerollShopGroupSlotsByIdResponse GetRerollShopGroupSlotsById(1: i32 persistentId),
  RequestResult AddRerollShopGroupSlotsEvent(1: RerollShopGroupSlotsEvent groupEvent),
  RequestResult EditRerollShopGroupSlotsEvent(1: RerollShopGroupSlotsEvent groupEvent),
  // Reroll shop banner events
  RerollShopBannersResponse GetRerollShopBanners(),
  RerollShopBannerByIdResponse GetRerollShopBannerById(1: i32 persistentId),
  RequestResult AddRerollShopBanner(1: RerollShopBanner banner),
  RequestResult EditRerollShopBanner(1: RerollShopBanner banner),
  // Reroll shop tooltip events
  RerollShopTooltipsResponse GetRerollShopTooltips(),
  RerollShopTooltipByIdResponse GetRerollShopTooltipById(1: i32 persistentId),
  RequestResult AddRerollShopTooltip(1: RerollShopTooltip tooltip),
  RequestResult EditRerollShopTooltip(1: RerollShopTooltip tooltip),
  // Roll events
  RollEventsResponse GetRollEvents(),
  RollEventByIdResponse GetRollEventById(1: i32 persistentId),
  RequestResult AddRollEvent(1: RollEvent rollEvent),
  RequestResult EditRollEvent(1: RollEvent rollEvent),
  // Quest events
  QuestEventsResponse GetQuestEvents(),
  QuestEventByIdResponse GetQuestEventById(1: i32 persistentId),
  RequestResult AddQuestEvent(1: QuestEvent questEvent),
  RequestResult EditQuestEvent(1: QuestEvent questEvent),
  // Trade events
  TradeEventsResponse GetTradeEvents(),
  TradeEventByIdResponse GetTradeEventById(1: i32 persistentId),
  RequestResult AddTradeEvent(1: TradeEventModel tradeEvent),
  RequestResult EditTradeEvent(1: TradeEventModel tradeEvent),

  // Trade events
  SeasonEventsResponse GetSeasonEvents(),
  SeasonEventByIdResponse GetSeasonEventById(1: i32 persistentId),
  RequestResult AddSeasonEvent(1: SeasonEvent seasonEvent),
  RequestResult EditSeasonEvent(1: SeasonEvent seasonEvent),

  // Donate events
  DonateEventsResponse GetDonateEvents(),
  DonateEventByIdResponse GetDonateEventById(1: i32 persistentId),
  RequestResult AddDonateEvent(1: DonateEvent donateEvent),
  RequestResult EditDonateEvent(1: DonateEvent donateEvent),

  // GW events
  GWEventsModelResponse GetGWEvents(),
  GWEventsModelByIdResponse GetGWEventsModelById(1: i32 persistentId),
  RequestResult EditGWEvent(1: GWEventModel gwEventModel, 2: string gmLogin),

  // Actions with friends
  FriendInfoResponse GetAccountFriends(1: i64 auid),
  RequestResult RemoveFriend(1: i64 auid, 2: i64 friendAuid),
}