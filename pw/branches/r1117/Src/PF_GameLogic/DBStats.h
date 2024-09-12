#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Sound/DBSound.h"
#include "../Terrain/DBTerrain.h"

struct IXmlSaver;
// forward declarations for factories
namespace NWorld
{
	class PFAchievBase;
	class PFWorld;
}; //namespace NWorld
namespace NGameX
{
	class PFUISign;
}; //namespace NGameX

namespace NDb
{
struct Ability;
struct AchievBase;
struct Actor;
struct AdventureTooltipSettings;
struct AdvMapModeDescription;
struct ApplicatorsList;
struct BindCategory;
struct Creature;
struct CurrencyDescriptionList;
struct CustomFlag;
struct DBMinimap;
struct DBStatisticData;
struct Dialog;
struct FactionScoringTable;
struct HeroScoringTable;
struct SmartChatConfiguration;
struct Texture;
struct TextureBase;
struct UIEvent;
struct UIFontStyle;
struct UISign;

enum BasicResourceType
{
	BASICRESOURCETYPE_NONE = 0,
	BASICRESOURCETYPE_GOLD = 1,
	BASICRESOURCETYPE_SILVER = 2,
	BASICRESOURCETYPE_CRYSTAL = 3,
	BASICRESOURCETYPE_REDCRYSTAL = 4,
	BASICRESOURCETYPE_RESOURCE1 = 5,
	BASICRESOURCETYPE_RESOURCE2 = 6,
	BASICRESOURCETYPE_RESOURCE3 = 7,
	BASICRESOURCETYPE_POPULATION = 8,
	BASICRESOURCETYPE_CLANWARPOINTS = 9,
	BASICRESOURCETYPE_PLAYERWARPOINTS = 10,
	BASICRESOURCETYPE_SHARD = 11,
};

const char *EnumToString( const BasicResourceType value );
const BasicResourceType StringToEnum_BasicResourceType( const char* value );

template <>
struct KnownEnum< BasicResourceType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 12 };
	static const char *ToString( const BasicResourceType value ) { return EnumToString( value ); }
	static const BasicResourceType ToEnum( const char* value ) { return StringToEnum_BasicResourceType( value ); }
	static const BasicResourceType ToEnum( const string& value ) { return StringToEnum_BasicResourceType( value.c_str() ); }
	static const int SizeOf() { return 12; }
};

enum EAchievementType
{
	ACHIEVEMENTTYPE_FIRSTBLOOD = 0,
	ACHIEVEMENTTYPE_DOUBLEKILL = 1,
	ACHIEVEMENTTYPE_MASSKILL = 2,
	ACHIEVEMENTTYPE_DUEL = 3,
	ACHIEVEMENTTYPE_CHASE = 4,
	ACHIEVEMENTTYPE_AVENGE = 5,
	ACHIEVEMENTTYPE_DOMINATE = 6,
	ACHIEVEMENTTYPE_VENDETTA = 7,
	ACHIEVEMENTTYPE_CEREMONIALKILL = 8,
	ACHIEVEMENTTYPE_KILLINGSPREE = 9,
	ACHIEVEMENTTYPE_DOUBLEASSIST = 10,
	ACHIEVEMENTTYPE_MASSASSIST = 11,
	ACHIEVEMENTTYPE_SAVIOUR = 12,
	ACHIEVEMENTTYPE_MASTERCONTROL = 13,
	ACHIEVEMENTTYPE_ASSISTINGSPREE = 14,
	ACHIEVEMENTTYPE_BORDERGUARD = 15,
	ACHIEVEMENTTYPE_FIRSTASSAULT = 16,
	ACHIEVEMENTTYPE_DEMOLISHINGSPREE = 17,
	ACHIEVEMENTTYPE_TOWERDENY = 18,
	ACHIEVEMENTTYPE_CLEARWAY = 19,
	ACHIEVEMENTTYPE_BASESTRIKE = 20,
	ACHIEVEMENTTYPE_VANDALISM = 21,
	ACHIEVEMENTTYPE_WARLORD = 22,
	ACHIEVEMENTTYPE_CLEANUPCREEPS = 23,
	ACHIEVEMENTTYPE_DRAGONSLAYER = 24,
	ACHIEVEMENTTYPE_KITTYSLAYER = 25,
	ACHIEVEMENTTYPE_LEGEND = 26,
	ACHIEVEMENTTYPE_FORESTHUNTER = 27,
	ACHIEVEMENTTYPE_ASCENSION = 28,
	ACHIEVEMENTTYPE_SLIVERRITE = 29,
	ACHIEVEMENTTYPE_GOLDRITE = 30,
	ACHIEVEMENTTYPE_FIRSTMINIGAMECOMPLETE = 31,
	ACHIEVEMENTTYPE_SESSIONDURATION = 32,
	ACHIEVEMENTTYPE_BOSSSLAYER = 33,
	ACHIEVEMENTTYPE_INVALIDACHIVEMENT = 34,
};

const char *EnumToString( const EAchievementType value );
const EAchievementType StringToEnum_EAchievementType( const char* value );

template <>
struct KnownEnum< EAchievementType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 35 };
	static const char *ToString( const EAchievementType value ) { return EnumToString( value ); }
	static const EAchievementType ToEnum( const char* value ) { return StringToEnum_EAchievementType( value ); }
	static const EAchievementType ToEnum( const string& value ) { return StringToEnum_EAchievementType( value.c_str() ); }
	static const int SizeOf() { return 35; }
};

enum EAdventureTooltipStretchMode
{
	ADVENTURETOOLTIPSTRETCHMODE_NONE = 0,
	ADVENTURETOOLTIPSTRETCHMODE_DYNAMIC = 1,
	ADVENTURETOOLTIPSTRETCHMODE_STATIC = 2,
};

const char *EnumToString( const EAdventureTooltipStretchMode value );
const EAdventureTooltipStretchMode StringToEnum_EAdventureTooltipStretchMode( const char* value );

template <>
struct KnownEnum< EAdventureTooltipStretchMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAdventureTooltipStretchMode value ) { return EnumToString( value ); }
	static const EAdventureTooltipStretchMode ToEnum( const char* value ) { return StringToEnum_EAdventureTooltipStretchMode( value ); }
	static const EAdventureTooltipStretchMode ToEnum( const string& value ) { return StringToEnum_EAdventureTooltipStretchMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EAnnouncementType
{
	ANNOUNCEMENTTYPE_PLAYERKILLED = 0,
	ANNOUNCEMENTTYPE_ACHIEVMENT = 1,
	ANNOUNCEMENTTYPE_TOWERDESTROYED = 2,
	ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS = 3,
	ANNOUNCEMENTTYPE_PLAYERLEFT = 4,
	ANNOUNCEMENTTYPE_PLAYERRECONNECTED = 5,
	ANNOUNCEMENTTYPE_QUESTRECIEVED = 6,
	ANNOUNCEMENTTYPE_QUESTCOMPLETE = 7,
	ANNOUNCEMENTTYPE_EGGANNOUNCEMENT = 8,
	ANNOUNCEMENTTYPE_SUPERSIEGESPAWNED = 9,
	ANNOUNCEMENTTYPE_CUSTOMANNOUNCEMENT = 10,
};

const char *EnumToString( const EAnnouncementType value );
const EAnnouncementType StringToEnum_EAnnouncementType( const char* value );

template <>
struct KnownEnum< EAnnouncementType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EAnnouncementType value ) { return EnumToString( value ); }
	static const EAnnouncementType ToEnum( const char* value ) { return StringToEnum_EAnnouncementType( value ); }
	static const EAnnouncementType ToEnum( const string& value ) { return StringToEnum_EAnnouncementType( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum EBossSlayerAchievMode
{
	BOSSSLAYERACHIEVMODE_ONLYFORKILLER = 0,
	BOSSSLAYERACHIEVMODE_FORKILLERANDASSISTER = 1,
	BOSSSLAYERACHIEVMODE_FORALLTEAMMATES = 2,
};

const char *EnumToString( const EBossSlayerAchievMode value );
const EBossSlayerAchievMode StringToEnum_EBossSlayerAchievMode( const char* value );

template <>
struct KnownEnum< EBossSlayerAchievMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EBossSlayerAchievMode value ) { return EnumToString( value ); }
	static const EBossSlayerAchievMode ToEnum( const char* value ) { return StringToEnum_EBossSlayerAchievMode( value ); }
	static const EBossSlayerAchievMode ToEnum( const string& value ) { return StringToEnum_EBossSlayerAchievMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EChatChannel
{
	CHATCHANNEL_GLOBAL = 0,
	CHATCHANNEL_MYTEAM = 1,
	CHATCHANNEL_BOTHTEAMS = 2,
	CHATCHANNEL_SYSTEM = 3,
	CHATCHANNEL_ACHIEVMENTS = 4,
	CHATCHANNEL_PRIVATE = 5,
	CHATCHANNEL_TAMBUR = 6,
	CHATCHANNEL_GUILD = 7,
	CHATCHANNEL_LOOKINGFORGROUPE = 8,
	CHATCHANNEL_ADMINISTRATION = 9,
	CHATCHANNEL_SMARTCHAT = 10,
};

const char *EnumToString( const EChatChannel value );
const EChatChannel StringToEnum_EChatChannel( const char* value );

template <>
struct KnownEnum< EChatChannel >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EChatChannel value ) { return EnumToString( value ); }
	static const EChatChannel ToEnum( const char* value ) { return StringToEnum_EChatChannel( value ); }
	static const EChatChannel ToEnum( const string& value ) { return StringToEnum_EChatChannel( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum EClanWarsResourceType
{
	CLANWARSRESOURCETYPE_CLANRATING = 0,
	CLANWARSRESOURCETYPE_PLAYERRATING = 1,
};

const char *EnumToString( const EClanWarsResourceType value );
const EClanWarsResourceType StringToEnum_EClanWarsResourceType( const char* value );

template <>
struct KnownEnum< EClanWarsResourceType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EClanWarsResourceType value ) { return EnumToString( value ); }
	static const EClanWarsResourceType ToEnum( const char* value ) { return StringToEnum_EClanWarsResourceType( value ); }
	static const EClanWarsResourceType ToEnum( const string& value ) { return StringToEnum_EClanWarsResourceType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EDerivativeStat
{
	DERIVATIVESTAT_LIFEREGENTOTAL = 0,
	DERIVATIVESTAT_ENERGYREGENTOTAL = 1,
	DERIVATIVESTAT_DAMAGEMIN = 2,
	DERIVATIVESTAT_DAMAGEMAX = 3,
	DERIVATIVESTAT_DEXTERITYDAMAGEMULT = 4,
	DERIVATIVESTAT_MOVESPEEDMPS = 5,
	DERIVATIVESTAT_CRITCHANCE = 6,
	DERIVATIVESTAT_ATTACKSPERSECOND = 7,
	DERIVATIVESTAT_BODYDEFENCE = 8,
	DERIVATIVESTAT_SPIRITDEFENCE = 9,
	DERIVATIVESTAT_PENETRATIONFROMATTACKSPEED = 10,
	DERIVATIVESTAT_PENETRATIONFROMDEXTERITY = 11,
	DERIVATIVESTAT_PENETRATIONTOTAL = 12,
};

const char *EnumToString( const EDerivativeStat value );
const EDerivativeStat StringToEnum_EDerivativeStat( const char* value );

template <>
struct KnownEnum< EDerivativeStat >
{
	enum { isKnown = 1 };
	enum { sizeOf = 13 };
	static const char *ToString( const EDerivativeStat value ) { return EnumToString( value ); }
	static const EDerivativeStat ToEnum( const char* value ) { return StringToEnum_EDerivativeStat( value ); }
	static const EDerivativeStat ToEnum( const string& value ) { return StringToEnum_EDerivativeStat( value.c_str() ); }
	static const int SizeOf() { return 13; }
};

enum EErrorMessageType
{
	ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY = 0,
	ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY = 1,
	ERRORMESSAGETYPE_ABILITYONCOOLDOWN = 2,
	ERRORMESSAGETYPE_WRONGTARGET = 3,
	ERRORMESSAGETYPE_INVULNERABLETARGET = 4,
	ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYTOWER = 5,
	ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYNEXT = 6,
	ERRORMESSAGETYPE_FLAGPOLETOOFAR = 7,
	ERRORMESSAGETYPE_FLAGPOLECURRENTLYRISING = 8,
	ERRORMESSAGETYPE_MINIGAMEBUSY = 9,
	ERRORMESSAGETYPE_MINIGAMEPROTECTEDBYTOWERS = 10,
	ERRORMESSAGETYPE_WAITINGFORTARGET = 11,
	ERRORMESSAGETYPE_OUTOFINVENTORY = 12,
	ERRORMESSAGETYPE_MINIGAMENOTREADY = 13,
	ERRORMESSAGETYPE_MINIGAMEDISABLED = 14,
	ERRORMESSAGETYPE_NOTENOUGHLIFEFORABILITY = 15,
	ERRORMESSAGETYPE_PINGRESTRICTED = 16,
	ERRORMESSAGETYPE_SMARTCHATRESTRICTED = 17,
	ERRORMESSAGETYPE_REPLAYENDED = 18,
};

const char *EnumToString( const EErrorMessageType value );
const EErrorMessageType StringToEnum_EErrorMessageType( const char* value );

template <>
struct KnownEnum< EErrorMessageType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 19 };
	static const char *ToString( const EErrorMessageType value ) { return EnumToString( value ); }
	static const EErrorMessageType ToEnum( const char* value ) { return StringToEnum_EErrorMessageType( value ); }
	static const EErrorMessageType ToEnum( const string& value ) { return StringToEnum_EErrorMessageType( value.c_str() ); }
	static const int SizeOf() { return 19; }
};

enum EFaction
{
	FACTION_NEUTRAL = 0,
	FACTION_FREEZE = 1,
	FACTION_BURN = 2,
};

const char *EnumToString( const EFaction value );
const EFaction StringToEnum_EFaction( const char* value );

template <>
struct KnownEnum< EFaction >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EFaction value ) { return EnumToString( value ); }
	static const EFaction ToEnum( const char* value ) { return StringToEnum_EFaction( value ); }
	static const EFaction ToEnum( const string& value ) { return StringToEnum_EFaction( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EFactionFlags
{
	FACTIONFLAGS_FACTIONFREEZE = 1,
	FACTIONFLAGS_FACTIONBURN = 2,
	FACTIONFLAGS_NEUTRAL = 4,
	FACTIONFLAGS_SELF = 8,
	FACTIONFLAGS_OPPOSITE = 16,
};

const char *EnumToString( const EFactionFlags value );
const EFactionFlags StringToEnum_EFactionFlags( const char* value );

template <>
struct KnownEnum< EFactionFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EFactionFlags value ) { return EnumToString( value ); }
	static const EFactionFlags ToEnum( const char* value ) { return StringToEnum_EFactionFlags( value ); }
	static const EFactionFlags ToEnum( const string& value ) { return StringToEnum_EFactionFlags( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EFlyOffAlign
{
	FLYOFFALIGN_LEFT = 0,
	FLYOFFALIGN_CENTER = 1,
	FLYOFFALIGN_RIGHT = 2,
};

const char *EnumToString( const EFlyOffAlign value );
const EFlyOffAlign StringToEnum_EFlyOffAlign( const char* value );

template <>
struct KnownEnum< EFlyOffAlign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EFlyOffAlign value ) { return EnumToString( value ); }
	static const EFlyOffAlign ToEnum( const char* value ) { return StringToEnum_EFlyOffAlign( value ); }
	static const EFlyOffAlign ToEnum( const string& value ) { return StringToEnum_EFlyOffAlign( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EFormatType
{
	FORMATTYPE_INTEGER = 0,
	FORMATTYPE_ONEDIGIT = 1,
	FORMATTYPE_TWODIGITS = 2,
	FORMATTYPE_PERCENT = 3,
	FORMATTYPE_ONEDIGITPERCENT = 4,
};

const char *EnumToString( const EFormatType value );
const EFormatType StringToEnum_EFormatType( const char* value );

template <>
struct KnownEnum< EFormatType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EFormatType value ) { return EnumToString( value ); }
	static const EFormatType ToEnum( const char* value ) { return StringToEnum_EFormatType( value ); }
	static const EFormatType ToEnum( const string& value ) { return StringToEnum_EFormatType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EHeroTitle
{
	HEROTITLE_BESTKILLER = 0,
	HEROTITLE_BESTASSISTER = 1,
	HEROTITLE_TOPCREEPKILLS = 2,
	HEROTITLE_TOPTOWERKILLS = 3,
	HEROTITLE_LEASTDEATHS = 4,
	HEROTITLE_TOPNAFTA = 5,
	HEROTITLE_PAINTER_MG2 = 6,
	HEROTITLE_DEDICATED_MG2 = 7,
	HEROTITLE_MERCILESS = 8,
	HEROTITLE_WANDERER = 9,
	HEROTITLE_TELEPORTER = 10,
	HEROTITLE_STAY_AT_HOME = 11,
	HEROTITLE_TOPCONSUMABLEUSER = 12,
	HEROTITLE_LEASTCONSUMABLEUSER = 13,
	HEROTITLE_ASCETIC = 14,
	HEROTITLE_TOPKILLSTREAKER = 15,
	HEROTITLE_SHINIGAMI = 16,
	HEROTITLE_ADVENTURER = 17,
	HEROTITLE_TOPTOWERDENIER = 18,
	HEROTITLE_TOPNEUTRALKILLER = 19,
	HEROTITLE_TOPCEREMONIALKILLER = 20,
	HEROTITLE_TOPONEHEROKILLER = 21,
	HEROTITLE_AVENGER = 22,
	HEROTITLE_LASTHITTOMAINBUILDING = 23,
	HEROTITLE_TOPIDLETIME = 24,
	HEROTITLE_HUNTSMAN = 25,
	HEROTITLE_DRAGONSLAYER = 26,
	HEROTITLE_LEGEND = 27,
	HEROTITLE_KAMIKAZE = 28,
	HEROTITLE_NOVICE = 29,
	HEROTITLE_BOSSSLAYER = 30,
};

const char *EnumToString( const EHeroTitle value );
const EHeroTitle StringToEnum_EHeroTitle( const char* value );

template <>
struct KnownEnum< EHeroTitle >
{
	enum { isKnown = 1 };
	enum { sizeOf = 31 };
	static const char *ToString( const EHeroTitle value ) { return EnumToString( value ); }
	static const EHeroTitle ToEnum( const char* value ) { return StringToEnum_EHeroTitle( value ); }
	static const EHeroTitle ToEnum( const string& value ) { return StringToEnum_EHeroTitle( value.c_str() ); }
	static const int SizeOf() { return 31; }
};

enum EMessage
{
	MESSAGE_SIMPLE_MESSAGE = 0,
	MESSAGE_LINEAR_FEAT_MESSAGE = 1,
	MESSAGE_ONLY_FOR_PRIESTESS_MESSAGE = 2,
};

const char *EnumToString( const EMessage value );
const EMessage StringToEnum_EMessage( const char* value );

template <>
struct KnownEnum< EMessage >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EMessage value ) { return EnumToString( value ); }
	static const EMessage ToEnum( const char* value ) { return StringToEnum_EMessage( value ); }
	static const EMessage ToEnum( const string& value ) { return StringToEnum_EMessage( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EMinimapIcons
{
	MINIMAPICONS_DEFAULT = 0,
	MINIMAPICONS_MAINBUILDINGA = 1,
	MINIMAPICONS_MAINBUILDINGB = 2,
	MINIMAPICONS_SHOPA = 3,
	MINIMAPICONS_SHOPB = 4,
	MINIMAPICONS_SHOPN = 5,
	MINIMAPICONS_QUARTERA = 6,
	MINIMAPICONS_QUARTERB = 7,
	MINIMAPICONS_TOWERA = 8,
	MINIMAPICONS_TOWERB = 9,
	MINIMAPICONS_NEUTRALSWEAK = 10,
	MINIMAPICONS_NEUTRALSSTRONG = 11,
	MINIMAPICONS_NEUTRALSBOSS = 12,
	MINIMAPICONS_MINIGAME = 13,
	MINIMAPICONS_FOUNTAINA = 14,
	MINIMAPICONS_FOUNTAINB = 15,
	MINIMAPICONS_FLAGPOLE = 16,
	MINIMAPICONS_ALTARA = 17,
	MINIMAPICONS_ALTARB = 18,
	MINIMAPICONS_EGG = 19,
	MINIMAPICONS_ALCHEMISTCIRCLE = 20,
	MINIMAPICONS_GLYPH = 21,
	MINIMAPICONS_BRIDGEPASSABLE = 22,
	MINIMAPICONS_BRIDGEIMPASSABLE = 23,
	MINIMAPICONS_PUSHBUTTON = 24,
	MINIMAPICONS_NONE = 25,
};

const char *EnumToString( const EMinimapIcons value );
const EMinimapIcons StringToEnum_EMinimapIcons( const char* value );

template <>
struct KnownEnum< EMinimapIcons >
{
	enum { isKnown = 1 };
	enum { sizeOf = 26 };
	static const char *ToString( const EMinimapIcons value ) { return EnumToString( value ); }
	static const EMinimapIcons ToEnum( const char* value ) { return StringToEnum_EMinimapIcons( value ); }
	static const EMinimapIcons ToEnum( const string& value ) { return StringToEnum_EMinimapIcons( value.c_str() ); }
	static const int SizeOf() { return 26; }
};

enum EPathMarker
{
	PATHMARKER_GREEN = 0,
	PATHMARKER_RED = 1,
};

const char *EnumToString( const EPathMarker value );
const EPathMarker StringToEnum_EPathMarker( const char* value );

template <>
struct KnownEnum< EPathMarker >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EPathMarker value ) { return EnumToString( value ); }
	static const EPathMarker ToEnum( const char* value ) { return StringToEnum_EPathMarker( value ); }
	static const EPathMarker ToEnum( const string& value ) { return StringToEnum_EPathMarker( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EPlayerID
{
	PLAYERID_NONE = 0,
	PLAYERID_PLAYER_1 = 1,
	PLAYERID_PLAYER_2 = 2,
	PLAYERID_PLAYER_3 = 3,
	PLAYERID_PLAYER_4 = 4,
	PLAYERID_PLAYER_5 = 5,
	PLAYERID_PLAYER_6 = 6,
	PLAYERID_PLAYER_7 = 7,
	PLAYERID_PLAYER_8 = 8,
	PLAYERID_PLAYER_9 = 9,
	PLAYERID_PLAYER_10 = 10,
};

const char *EnumToString( const EPlayerID value );
const EPlayerID StringToEnum_EPlayerID( const char* value );

template <>
struct KnownEnum< EPlayerID >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EPlayerID value ) { return EnumToString( value ); }
	static const EPlayerID ToEnum( const char* value ) { return StringToEnum_EPlayerID( value ); }
	static const EPlayerID ToEnum( const string& value ) { return StringToEnum_EPlayerID( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum ERecipients
{
	RECIPIENTS_EVENT_PARTICIPANTS = 0,
	RECIPIENTS_EVENT_MAKER_TEAM = 1,
	RECIPIENTS_EVENT_MAKER_OPPOSITE_TEAM = 2,
	RECIPIENTS_ALL_PLAYERS = 3,
	RECIPIENTS_ALL_PLAYERS_WITHOUT_PRIESTESS = 4,
	RECIPIENTS_PLAYER_ONLY = 5,
	RECIPIENTS_USE_FROM_PARENT = 6,
};

const char *EnumToString( const ERecipients value );
const ERecipients StringToEnum_ERecipients( const char* value );

template <>
struct KnownEnum< ERecipients >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ERecipients value ) { return EnumToString( value ); }
	static const ERecipients ToEnum( const char* value ) { return StringToEnum_ERecipients( value ); }
	static const ERecipients ToEnum( const string& value ) { return StringToEnum_ERecipients( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EResourceType
{
	RESOURCETYPE_SILVER = 0,
	RESOURCETYPE_CRYSTAL = 1,
	RESOURCETYPE_RESOURCE1 = 2,
	RESOURCETYPE_RESOURCE2 = 3,
	RESOURCETYPE_RESOURCE3 = 4,
	RESOURCETYPE_REDCRYSTAL = 5,
	RESOURCETYPE_SHARD = 6,
};

const char *EnumToString( const EResourceType value );
const EResourceType StringToEnum_EResourceType( const char* value );

template <>
struct KnownEnum< EResourceType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EResourceType value ) { return EnumToString( value ); }
	static const EResourceType ToEnum( const char* value ) { return StringToEnum_EResourceType( value ); }
	static const EResourceType ToEnum( const string& value ) { return StringToEnum_EResourceType( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum ERoute
{
	ROUTE_TOP = 0,
	ROUTE_CENTER = 1,
	ROUTE_BOTTOM = 2,
	ROUTE_TREE = 3,
	ROUTE_UNASSIGNED = 4,
};

const char *EnumToString( const ERoute value );
const ERoute StringToEnum_ERoute( const char* value );

template <>
struct KnownEnum< ERoute >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const ERoute value ) { return EnumToString( value ); }
	static const ERoute ToEnum( const char* value ) { return StringToEnum_ERoute( value ); }
	static const ERoute ToEnum( const string& value ) { return StringToEnum_ERoute( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EScoreType
{
	SCORETYPE_HEROKILLCOUNT = 0,
	SCORETYPE_DEATHCOUNT = 1,
	SCORETYPE_ASSISTCOUNT = 2,
	SCORETYPE_SCORE = 3,
	SCORETYPE_TOTALNAFTA = 4,
	SCORETYPE_ACHIEVMENTCOUNT = 5,
	SCORETYPE_TOWERSDESTROYED = 6,
	SCORETYPE_TOWERSDENIED = 7,
	SCORETYPE_FLAGSRAISED = 8,
	SCORETYPE_FLAGSDESTROYED = 9,
	SCORETYPE_MINIGAMELEVELSWON = 10,
	SCORETYPE_CREEPSKILLED = 11,
	SCORETYPE_NEUTRALCREEPSCOUNT = 12,
	SCORETYPE_TIMEINDEATH = 13,
	SCORETYPE_HELEADAMOUNT = 14,
	SCORETYPE_SEXHELP = 15,
	SCORETYPE_DAMAGEDEALED = 16,
	SCORETYPE_DAMAGERECIEVED = 17,
	SCORETYPE_DANAGEHERODEALED = 18,
	SCORETYPE_DANAGEHERORECIEVED = 19,
	SCORETYPE_METERIALDAMAGEDEALED = 20,
	SCORETYPE_METERIALDAMAGERECIEVED = 21,
	SCORETYPE_ENERGYDAMAGEDEALED = 22,
	SCORETYPE_ENERGYDAMAGERECIEVED = 23,
};

const char *EnumToString( const EScoreType value );
const EScoreType StringToEnum_EScoreType( const char* value );

template <>
struct KnownEnum< EScoreType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 24 };
	static const char *ToString( const EScoreType value ) { return EnumToString( value ); }
	static const EScoreType ToEnum( const char* value ) { return StringToEnum_EScoreType( value ); }
	static const EScoreType ToEnum( const string& value ) { return StringToEnum_EScoreType( value.c_str() ); }
	static const int SizeOf() { return 24; }
};

enum ESign
{
	SIGN_NONE = 0,
	SIGN_SEND_MESSAGE_TO_CHAT = 1,
	SIGN_SEND_MESSAGE_TO_STATUS_LINE = 2,
	SIGN_PLAY_SOUND = 3,
	SIGN_FLYOFF_TEXT = 4,
	SIGN_ANNOUNCEMENT = 5,
};

const char *EnumToString( const ESign value );
const ESign StringToEnum_ESign( const char* value );

template <>
struct KnownEnum< ESign >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const ESign value ) { return EnumToString( value ); }
	static const ESign ToEnum( const char* value ) { return StringToEnum_ESign( value ); }
	static const ESign ToEnum( const string& value ) { return StringToEnum_ESign( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EStat
{
	STAT_LIFE = 0,
	STAT_ENERGY = 1,
	STAT_RANGE = 2,
	STAT_MOVESPEED = 3,
	STAT_ATTACKSPEED = 4,
	STAT_CRITICALCHANCE = 5,
	STAT_CRITICALMULTIPLIER = 6,
	STAT_LIFEDRAIN = 7,
	STAT_ENERGYDRAIN = 8,
	STAT_EVASION = 9,
	STAT_LIFEREGENERATION = 10,
	STAT_LIFEREGENERATIONABSOLUTE = 11,
	STAT_ENERGYREGENERATION = 12,
	STAT_ENERGYREGENERATIONABSOLUTE = 13,
	STAT_VISIBILITYRANGE = 14,
	STAT_STRENGTH = 15,
	STAT_INTELLECT = 16,
	STAT_DEXTERITY = 17,
	STAT_BASEATTACK = 18,
	STAT_STAMINA = 19,
	STAT_WILL = 20,
	STAT_VIRTUALSTAT = 21,
	STAT_CRITCHANCEBONUS = 22,
	STAT_ENERGYDAMAGEDECREASE = 23,
	STAT_MATERIALDAMAGEDECREASE = 24,
	STAT_MISSCHANCE = 25,
	STAT_LEVEL = 26,
	STAT_NAFTAFORKILL = 27,
	STAT_NAFTAFORASSIST = 28,
	STAT_NAFTASPECFORKILL = 29,
	STAT_TEAMNAFTAFORKILL = 30,
	STAT_TEAMNAFTAFORPRESENCE = 31,
};

const char *EnumToString( const EStat value );
const EStat StringToEnum_EStat( const char* value );

template <>
struct KnownEnum< EStat >
{
	enum { isKnown = 1 };
	enum { sizeOf = 32 };
	static const char *ToString( const EStat value ) { return EnumToString( value ); }
	static const EStat ToEnum( const char* value ) { return StringToEnum_EStat( value ); }
	static const EStat ToEnum( const string& value ) { return StringToEnum_EStat( value.c_str() ); }
	static const int SizeOf() { return 32; }
};

enum EStatOwner
{
	STATOWNER_NONE = 0,
	STATOWNER_CREATURE = 1,
	STATOWNER_ENEMYCREATURE = 2,
	STATOWNER_ENEMYHERO = 3,
	STATOWNER_HERO = 4,
	STATOWNER_PLAYER = 5,
};

const char *EnumToString( const EStatOwner value );
const EStatOwner StringToEnum_EStatOwner( const char* value );

template <>
struct KnownEnum< EStatOwner >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EStatOwner value ) { return EnumToString( value ); }
	static const EStatOwner ToEnum( const char* value ) { return StringToEnum_EStatOwner( value ); }
	static const EStatOwner ToEnum( const string& value ) { return StringToEnum_EStatOwner( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum ETerrainType
{
	TERRAINTYPE_PLAINS = 0,
	TERRAINTYPE_SWAMP = 1,
	TERRAINTYPE_DESERT = 2,
	TERRAINTYPE_ROCK = 3,
	TERRAINTYPE_WATER = 4,
	TERRAINTYPE_ROAD = 5,
};

const char *EnumToString( const ETerrainType value );
const ETerrainType StringToEnum_ETerrainType( const char* value );

template <>
struct KnownEnum< ETerrainType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const ETerrainType value ) { return EnumToString( value ); }
	static const ETerrainType ToEnum( const char* value ) { return StringToEnum_ETerrainType( value ); }
	static const ETerrainType ToEnum( const string& value ) { return StringToEnum_ETerrainType( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EVisualStyle
{
	VISUALSTYLE_ALWAYS = 0,
	VISUALSTYLE_CHANGED = 1,
	VISUALSTYLE_DONTSHOW = 2,
};

const char *EnumToString( const EVisualStyle value );
const EVisualStyle StringToEnum_EVisualStyle( const char* value );

template <>
struct KnownEnum< EVisualStyle >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EVisualStyle value ) { return EnumToString( value ); }
	static const EVisualStyle ToEnum( const char* value ) { return StringToEnum_EVisualStyle( value ); }
	static const EVisualStyle ToEnum( const string& value ) { return StringToEnum_EVisualStyle( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum GuildShopCategoryType
{
	GUILDSHOPCATEGORYTYPE_CLANBUFS = 0,
	GUILDSHOPCATEGORYTYPE_PLAYERBUFS = 1,
	GUILDSHOPCATEGORYTYPE_SKINSANDFLAGS = 2,
	GUILDSHOPCATEGORYTYPE_PRODUCTIONBONUS = 3,
	GUILDSHOPCATEGORYTYPE_TALENTS = 4,
};

const char *EnumToString( const GuildShopCategoryType value );
const GuildShopCategoryType StringToEnum_GuildShopCategoryType( const char* value );

template <>
struct KnownEnum< GuildShopCategoryType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const GuildShopCategoryType value ) { return EnumToString( value ); }
	static const GuildShopCategoryType ToEnum( const char* value ) { return StringToEnum_GuildShopCategoryType( value ); }
	static const GuildShopCategoryType ToEnum( const string& value ) { return StringToEnum_GuildShopCategoryType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum PhraseTerminateEvent
{
	PHRASETERMINATEEVENT_PRESSKEY = 0,
	PHRASETERMINATEEVENT_TIME = 1,
	PHRASETERMINATEEVENT_TIMEANDKEY = 2,
};

const char *EnumToString( const PhraseTerminateEvent value );
const PhraseTerminateEvent StringToEnum_PhraseTerminateEvent( const char* value );

template <>
struct KnownEnum< PhraseTerminateEvent >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const PhraseTerminateEvent value ) { return EnumToString( value ); }
	static const PhraseTerminateEvent ToEnum( const char* value ) { return StringToEnum_PhraseTerminateEvent( value ); }
	static const PhraseTerminateEvent ToEnum( const string& value ) { return StringToEnum_PhraseTerminateEvent( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum PortretOrientation
{
	PORTRETORIENTATION_LEFT = 0,
	PORTRETORIENTATION_RIGHT = 1,
};

const char *EnumToString( const PortretOrientation value );
const PortretOrientation StringToEnum_PortretOrientation( const char* value );

template <>
struct KnownEnum< PortretOrientation >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const PortretOrientation value ) { return EnumToString( value ); }
	static const PortretOrientation ToEnum( const char* value ) { return StringToEnum_PortretOrientation( value ); }
	static const PortretOrientation ToEnum( const string& value ) { return StringToEnum_PortretOrientation( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct AbuseSettings
{
public:
	float cooldownTime;
	int maxUsagesPerPeriod;
	float period;
	int maxUsagesPerRestrictedPeriod;
	float restrictedPeriod;
	bool refreshRestrictedPeriod;

	AbuseSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AchievBossSlayerData
{
public:
	Ptr< Creature > boss;
	CTextRef name;
	int perAchievementScore;
	int limit;
	CTextRef tooltip;
	Ptr< Texture > image;
	Ptr< UIEvent > evUI;
	EBossSlayerAchievMode mode;

	AchievBossSlayerData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnnouncementDescription
{
public:
	CTextRef textMessage;
	float lifeTime;

	AnnouncementDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AttackType
{
public:
	CTextRef statName;
	CTextRef phisicalAttackName;
	CTextRef energyAttackName;
	CTextRef pureAttackName;

	AttackType();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct BattleStartAnnouncementParams
{
public:
	Ptr< Texture > imageBurn;
	Ptr< Texture > imageFreeze;
	CTextRef announcementText;
	DBFMODEventDesc battleStartSound;

	BattleStartAnnouncementParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct HotkeyBind
{
public:
	CTextRef name;
	string bindKey;
	string dependentBindKey;
	float bindFactor;
	bool isHelperKey;
	CTextRef tooltip;
	Ptr< BindCategory > category;

	HotkeyBind();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CountryFlag
{
public:
	string id;
	Ptr< Texture > icon;
	CTextRef name;
	string countryCode;
	CTextRef tooltip;

	CountryFlag();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CharStatTooltips
{
public:
	vector< CTextRef > baseStatTooltips;
	vector< CTextRef > derivativeStatTooltips;

	CharStatTooltips();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ChatChannelDescription
{
public:
	CTextRef channelName;
	Render::Color channelColor;
	CTextRef castleChannelName;
	Render::Color castleChannelColor;
	bool showChannelName;
	bool showPlayerName;
	string chatChannelIconA;
	string chatChannelIconB;
	bool showBlinkOnMessage;
	vector< CTextRef > shortcuts;
	bool clearMessagesOnLeave;
	bool spamInGlobalChannel;
	bool cooldownOnSpam;

	ChatChannelDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CombatStatuses
{
public:
	CTextRef replaySpeed;
	CTextRef replayPause;

	CombatStatuses();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct BotDefaultFlags
{
public:
	CountryFlag adornianDefaultFlag;
	CountryFlag doctDefaultFlag;

	BotDefaultFlags();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DamageBloodMaskParams
{
public:
	Animated<float, NDb::AnimatedAlgorithms::Linear> alphaCurve;
	float lowHealthAlpha;
	float nearDeathAlpha;
	float lowHealthLevel;
	float nearDeathLevel;
	float lowHealthSaturation;
	float nearDeathSaturation;
	float afterDeathSaturation;
	float afterLoseSaturation;
	float saturationChangeSpeed;
	float saturationChangeSpeedAfterLose;

	DamageBloodMaskParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DampSmoothing
{
public:
	float dampTimeObserv;
	float dampTimeMove;
	float anchorShiftObserv;
	float projCorretionShiftObservMaxZoom;
	float projCorretionShiftObservMinZoom;
	float firstJumpTime;
	float zoomFactorMove;
	float zoomFactorObserv;
	float maxSpeed;
	float timeToMaxSpeed;

	DampSmoothing();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DialogsSettings
{
public:
	float defaultPhraseDuration;
	float defaultSilenceDuration;
	float FadeInOutPercentage;

	DialogsSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RestrictedScoring
{
public:
	int score;
	int maxScore;

	RestrictedScoring();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ErrorMessageDescription
{
public:
	CTextRef textMessage;
	bool shouldPlaySound;
	float lifeTime;

	ErrorMessageDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FlyOffText
{
public:
	enum { typeId = 0x0B6C5300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FlyOffText::typeId; }
	float lifeTime;
	CVec2 offset;
	CVec2 velocity;
	CVec2 acceleration;
	float startOpacity;
	float endOpacity;
	EFlyOffAlign align;
	string layout;

	FlyOffText();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ForceColor
{
public:
	int force;
	Render::Color color;
	Ptr< UIFontStyle > style;

	ForceColor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ForceToColorTable
{
public:
	vector< ForceColor > forceColors;

	ForceToColorTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GameUIData
{
public:
	CTextRef gamePauseMessage;
	CTextRef gameResumeMessage;

	GameUIData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GuildShopTab
{
public:
	GuildShopCategoryType category;
	CTextRef name;
	CTextRef tooltip;

	GuildShopTab();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct HeroTitle
{
public:
	CTextRef maleName;
	CTextRef femaleName;
	CTextRef tooltip;
	Ptr< Texture > image;
	float score;

	HeroTitle();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Hint
{
public:
	string id;
	CTextRef text;

	Hint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct HintImage : public Hint
{
public:
	Ptr< Texture > image;

	HintImage();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Binds
{
public:
	vector< HotkeyBind > bindList;

	Binds();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct IgnoreListParams
{
public:
	CTextRef outOfIgnorePlace;

	IgnoreListParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ImpulsiveBuffsParams
{
public:
	float minLifeTime;
	float maxLifeTime;
	float normalBlendTime;
	float fastBlendTime;
	float cancelDelay;

	ImpulsiveBuffsParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Locale
{
public:
	string locale;
	CTextRef tooltip;
	Ptr< Texture > localeImage;

	Locale();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MapModeCustomDescriptions
{
public:
	Ptr< AdvMapModeDescription > maneuvers;
	Ptr< AdvMapModeDescription > guardBattle;
	Ptr< AdvMapModeDescription > guildBattle;
	Ptr< AdvMapModeDescription > customBattle;

	MapModeCustomDescriptions();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MarkerSettings
{
public:
	float duration;
	float otherMarkersCheckRange;

	MarkerSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PathMarkerColor
{
public:
	Render::HDRColor mul;
	Render::HDRColor add;

	PathMarkerColor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Phrase
{
public:
	Ptr< Actor > actorMale;
	Ptr< Actor > actorFemale;
	CTextRef textMale;
	CTextRef textFemale;
	Render::Color colorTextMale;
	Render::Color colorTextFemale;
	DBFMODEventDesc soundMale;
	DBFMODEventDesc soundFemale;
	string socialSoundMale;
	string socialSoundFemale;
	float duration;
	string scriptName;
	PhraseTerminateEvent terminate;
	PortretOrientation orientation;
	vector< HintImage > hintImages;

	Phrase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PingAbuseSettings : public AbuseSettings
{
public:

	PingAbuseSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PremiumVisualInfo
{
public:
	CTextRef premiumTooltipAddition;

	PremiumVisualInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PWSoundEvents
{
public:
	DBFMODEventDesc selection;
	DBFMODEventDesc targetCancelled;
	DBFMODEventDesc targetSelected;
	DBFMODEventDesc minimapSignal;
	DBFMODEventDesc chatMarker;

	PWSoundEvents();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ReportType
{
public:
	CTextRef name;
	int id;

	ReportType();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ResourceDescription
{
public:
	CTextRef resourceTooltipFreeze;
	CTextRef resourceTooltipBurn;
	Ptr< Texture > imageFreeze;
	Ptr< Texture > imageBurn;

	ResourceDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DiscreteScoring : public RestrictedScoring
{
public:
	int count;

	DiscreteScoring();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ScoreDescription
{
public:
	CTextRef name;
	Ptr< Texture > icon;
	int outputPriority;

	ScoreDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SessionQuest
{
public:
	string id;
	CTextRef text;
	int counter;
	bool primary;

	SessionQuest();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SmartChatAbuseSettings : public AbuseSettings
{
public:

	SmartChatAbuseSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatBudget
{
public:
	EStat stat;
	float budget;
	bool upgradesWithForce;

	StatBudget();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatEnhancer
{
public:
	EStat statId;
	float statAddModifier;
	float statMullModifier;
	float incrementAddModifier;
	float incrementMullModifier;

	StatEnhancer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatParams
{
public:
	CTextRef name;
	EVisualStyle visualStyle;
	EFormatType format;
	float defValue;

	StatParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatUpgrade
{
public:
	int level;
	float increment;

	StatUpgrade();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StringTextRefPair
{
public:
	string key;
	CTextRef text;

	StringTextRefPair();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TeamInfTooltipSettings
{
public:
	CTextRef heroTooltip;

	TeamInfTooltipSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TipOfTheDay
{
public:
	CTextRef tipText;

	TipOfTheDay();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UnitOvertipSettings
{
public:
	Ptr< AdventureTooltipSettings > ally;
	Ptr< AdventureTooltipSettings > enemy;
	Ptr< AdventureTooltipSettings > neutral;
	Ptr< AdventureTooltipSettings > invulnerableAlly;
	Ptr< AdventureTooltipSettings > invulnerableEnemy;
	Ptr< AdventureTooltipSettings > localHero;
	Ptr< AdventureTooltipSettings > localHeroSlave;
	Ptr< AdventureTooltipSettings > invulnerableLocalHero;
	Ptr< AdventureTooltipSettings > invulnerableLocalHeroSlave;

	UnitOvertipSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UnitStat
{
public:
	ExecutableFloatString value;
	ExecutableFloatString increment;
	EStat statId;
	vector< StatUpgrade > levelUpgrades;

	UnitStat();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct VictoryDefeatImages
{
public:
	Ptr< Texture > DefeatBurn;
	Ptr< Texture > DefeatFreeze;
	Ptr< Texture > VictoryBurn;
	Ptr< Texture > VictoryFreeze;

	VictoryDefeatImages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AchievBase : public DbResource
{
public:
	enum { typeId = 0x4D72CBC2 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievBase::typeId; }
	EAchievementType achievType;
	CTextRef name;
	int perAchievementScore;
	int limit;
	float multiplier;
	CTextRef tooltip;
	int priority;
	Ptr< Texture > image;
	Ptr< UIEvent > evUI;
	float naftaAward;

	AchievBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievBase& operator = ( const AchievBase &_achievBase ) { Assign( _achievBase ); return *this; }
	AchievBase( const AchievBase &_achievBase ) { Assign( _achievBase ); }
	virtual void Assign( const AchievBase &_achievBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievBase * pOther = dynamic_cast< const AchievBase * > ( _pResource );
		if ( pOther ) AchievBase::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievRuler : public AchievBase
{
public:
	enum { typeId = 0x4D732480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievRuler::typeId; }
	int start;
	int step;
	bool breakOnDeath;

	AchievRuler();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievRuler& operator = ( const AchievRuler &_achievRuler ) { Assign( _achievRuler ); return *this; }
	AchievRuler( const AchievRuler &_achievRuler ) { Assign( _achievRuler ); }
	virtual void Assign( const AchievRuler &_achievRuler );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievRuler * pOther = dynamic_cast< const AchievRuler * > ( _pResource );
		if ( pOther ) AchievRuler::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievAvenge : public AchievBase
{
	DBRESOURCE_METHODS( AchievAvenge );
public:
	enum { typeId = 0x4D732B43 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievAvenge::typeId; }
	int timeLimit;
	float distanceLimit;

	AchievAvenge();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievAvenge& operator = ( const AchievAvenge &_achievAvenge ) { Assign( _achievAvenge ); return *this; }
	AchievAvenge( const AchievAvenge &_achievAvenge ) { Assign( _achievAvenge ); }
	virtual void Assign( const AchievAvenge &_achievAvenge );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievAvenge * pOther = dynamic_cast< const AchievAvenge * > ( _pResource );
		if ( pOther ) AchievAvenge::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievStreak : public AchievBase
{
public:
	enum { typeId = 0x4D739B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievStreak::typeId; }
	int start;

	AchievStreak();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievStreak& operator = ( const AchievStreak &_achievStreak ) { Assign( _achievStreak ); return *this; }
	AchievStreak( const AchievStreak &_achievStreak ) { Assign( _achievStreak ); }
	virtual void Assign( const AchievStreak &_achievStreak );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievStreak * pOther = dynamic_cast< const AchievStreak * > ( _pResource );
		if ( pOther ) AchievStreak::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievBaseStrike : public AchievBase
{
	DBRESOURCE_METHODS( AchievBaseStrike );
public:
	enum { typeId = 0x4D732281 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievBaseStrike::typeId; }
	int minBarracks;

	AchievBaseStrike();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievBaseStrike& operator = ( const AchievBaseStrike &_achievBaseStrike ) { Assign( _achievBaseStrike ); return *this; }
	AchievBaseStrike( const AchievBaseStrike &_achievBaseStrike ) { Assign( _achievBaseStrike ); }
	virtual void Assign( const AchievBaseStrike &_achievBaseStrike );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievBaseStrike * pOther = dynamic_cast< const AchievBaseStrike * > ( _pResource );
		if ( pOther ) AchievBaseStrike::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievBorderGuard : public AchievBase
{
	DBRESOURCE_METHODS( AchievBorderGuard );
public:
	enum { typeId = 0x4D732B4B };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievBorderGuard::typeId; }
	int byTowerLifePercent;
	int timePeriod;

	AchievBorderGuard();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievBorderGuard& operator = ( const AchievBorderGuard &_achievBorderGuard ) { Assign( _achievBorderGuard ); return *this; }
	AchievBorderGuard( const AchievBorderGuard &_achievBorderGuard ) { Assign( _achievBorderGuard ); }
	virtual void Assign( const AchievBorderGuard &_achievBorderGuard );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievBorderGuard * pOther = dynamic_cast< const AchievBorderGuard * > ( _pResource );
		if ( pOther ) AchievBorderGuard::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievBossSlayer : public AchievBase
{
	DBRESOURCE_METHODS( AchievBossSlayer );
public:
	enum { typeId = 0xB19BF480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievBossSlayer::typeId; }
	vector< AchievBossSlayerData > creatures;

	AchievBossSlayer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievBossSlayer& operator = ( const AchievBossSlayer &_achievBossSlayer ) { Assign( _achievBossSlayer ); return *this; }
	AchievBossSlayer( const AchievBossSlayer &_achievBossSlayer ) { Assign( _achievBossSlayer ); }
	virtual void Assign( const AchievBossSlayer &_achievBossSlayer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievBossSlayer * pOther = dynamic_cast< const AchievBossSlayer * > ( _pResource );
		if ( pOther ) AchievBossSlayer::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievCeremonialKill : public AchievBase
{
	DBRESOURCE_METHODS( AchievCeremonialKill );
public:
	enum { typeId = 0x4D732280 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievCeremonialKill::typeId; }

	AchievCeremonialKill();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievCeremonialKill& operator = ( const AchievCeremonialKill &_achievCeremonialKill ) { Assign( _achievCeremonialKill ); return *this; }
	AchievCeremonialKill( const AchievCeremonialKill &_achievCeremonialKill ) { Assign( _achievCeremonialKill ); }
	virtual void Assign( const AchievCeremonialKill &_achievCeremonialKill );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievCeremonialKill * pOther = dynamic_cast< const AchievCeremonialKill * > ( _pResource );
		if ( pOther ) AchievCeremonialKill::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievChase : public AchievBase
{
	DBRESOURCE_METHODS( AchievChase );
public:
	enum { typeId = 0x4D732B42 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievChase::typeId; }
	float distanceMult;
	int timeLimit;

	AchievChase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievChase& operator = ( const AchievChase &_achievChase ) { Assign( _achievChase ); return *this; }
	AchievChase( const AchievChase &_achievChase ) { Assign( _achievChase ); }
	virtual void Assign( const AchievChase &_achievChase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievChase * pOther = dynamic_cast< const AchievChase * > ( _pResource );
		if ( pOther ) AchievChase::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievCleanUpCreeps : public AchievBase
{
	DBRESOURCE_METHODS( AchievCleanUpCreeps );
public:
	enum { typeId = 0x4D732B4F };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievCleanUpCreeps::typeId; }
	int minCreepsKilled;
	int timePeriod;

	AchievCleanUpCreeps();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievCleanUpCreeps& operator = ( const AchievCleanUpCreeps &_achievCleanUpCreeps ) { Assign( _achievCleanUpCreeps ); return *this; }
	AchievCleanUpCreeps( const AchievCleanUpCreeps &_achievCleanUpCreeps ) { Assign( _achievCleanUpCreeps ); }
	virtual void Assign( const AchievCleanUpCreeps &_achievCleanUpCreeps );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievCleanUpCreeps * pOther = dynamic_cast< const AchievCleanUpCreeps * > ( _pResource );
		if ( pOther ) AchievCleanUpCreeps::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievClearWay : public AchievBase
{
	DBRESOURCE_METHODS( AchievClearWay );
public:
	enum { typeId = 0x4D72CBC4 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievClearWay::typeId; }
	int minClearWayTowers;

	AchievClearWay();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievClearWay& operator = ( const AchievClearWay &_achievClearWay ) { Assign( _achievClearWay ); return *this; }
	AchievClearWay( const AchievClearWay &_achievClearWay ) { Assign( _achievClearWay ); }
	virtual void Assign( const AchievClearWay &_achievClearWay );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievClearWay * pOther = dynamic_cast< const AchievClearWay * > ( _pResource );
		if ( pOther ) AchievClearWay::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievCraftWoman : public AchievBase
{
	DBRESOURCE_METHODS( AchievCraftWoman );
public:
	enum { typeId = 0x4D738C03 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievCraftWoman::typeId; }
	float heartsCnt;

	AchievCraftWoman();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievCraftWoman& operator = ( const AchievCraftWoman &_achievCraftWoman ) { Assign( _achievCraftWoman ); return *this; }
	AchievCraftWoman( const AchievCraftWoman &_achievCraftWoman ) { Assign( _achievCraftWoman ); }
	virtual void Assign( const AchievCraftWoman &_achievCraftWoman );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievCraftWoman * pOther = dynamic_cast< const AchievCraftWoman * > ( _pResource );
		if ( pOther ) AchievCraftWoman::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDemolishingSpree : public AchievRuler
{
	DBRESOURCE_METHODS( AchievDemolishingSpree );
public:
	enum { typeId = 0x4D732B4D };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDemolishingSpree::typeId; }

	AchievDemolishingSpree();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDemolishingSpree& operator = ( const AchievDemolishingSpree &_achievDemolishingSpree ) { Assign( _achievDemolishingSpree ); return *this; }
	AchievDemolishingSpree( const AchievDemolishingSpree &_achievDemolishingSpree ) { Assign( _achievDemolishingSpree ); }
	virtual void Assign( const AchievDemolishingSpree &_achievDemolishingSpree );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDemolishingSpree * pOther = dynamic_cast< const AchievDemolishingSpree * > ( _pResource );
		if ( pOther ) AchievDemolishingSpree::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDominate : public AchievBase
{
	DBRESOURCE_METHODS( AchievDominate );
public:
	enum { typeId = 0x4D732B45 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDominate::typeId; }
	int minKillsForDominate;

	AchievDominate();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDominate& operator = ( const AchievDominate &_achievDominate ) { Assign( _achievDominate ); return *this; }
	AchievDominate( const AchievDominate &_achievDominate ) { Assign( _achievDominate ); }
	virtual void Assign( const AchievDominate &_achievDominate );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDominate * pOther = dynamic_cast< const AchievDominate * > ( _pResource );
		if ( pOther ) AchievDominate::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDoubleAssist : public AchievBase
{
	DBRESOURCE_METHODS( AchievDoubleAssist );
public:
	enum { typeId = 0x4D732B47 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDoubleAssist::typeId; }
	int timeLimit;

	AchievDoubleAssist();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDoubleAssist& operator = ( const AchievDoubleAssist &_achievDoubleAssist ) { Assign( _achievDoubleAssist ); return *this; }
	AchievDoubleAssist( const AchievDoubleAssist &_achievDoubleAssist ) { Assign( _achievDoubleAssist ); }
	virtual void Assign( const AchievDoubleAssist &_achievDoubleAssist );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDoubleAssist * pOther = dynamic_cast< const AchievDoubleAssist * > ( _pResource );
		if ( pOther ) AchievDoubleAssist::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDoubleKill : public AchievBase
{
	DBRESOURCE_METHODS( AchievDoubleKill );
public:
	enum { typeId = 0x4D732B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDoubleKill::typeId; }
	int timeLimit;

	AchievDoubleKill();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDoubleKill& operator = ( const AchievDoubleKill &_achievDoubleKill ) { Assign( _achievDoubleKill ); return *this; }
	AchievDoubleKill( const AchievDoubleKill &_achievDoubleKill ) { Assign( _achievDoubleKill ); }
	virtual void Assign( const AchievDoubleKill &_achievDoubleKill );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDoubleKill * pOther = dynamic_cast< const AchievDoubleKill * > ( _pResource );
		if ( pOther ) AchievDoubleKill::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDragonSlayer : public AchievBase
{
	DBRESOURCE_METHODS( AchievDragonSlayer );
public:
	enum { typeId = 0x4D732B50 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDragonSlayer::typeId; }
	vector< Ptr< Creature > > dragons;

	AchievDragonSlayer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDragonSlayer& operator = ( const AchievDragonSlayer &_achievDragonSlayer ) { Assign( _achievDragonSlayer ); return *this; }
	AchievDragonSlayer( const AchievDragonSlayer &_achievDragonSlayer ) { Assign( _achievDragonSlayer ); }
	virtual void Assign( const AchievDragonSlayer &_achievDragonSlayer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDragonSlayer * pOther = dynamic_cast< const AchievDragonSlayer * > ( _pResource );
		if ( pOther ) AchievDragonSlayer::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievDuel : public AchievBase
{
	DBRESOURCE_METHODS( AchievDuel );
public:
	enum { typeId = 0x4D732B41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievDuel::typeId; }
	int maxRestLifePercent;
	int minLifePercent;
	int timeLimit;

	AchievDuel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievDuel& operator = ( const AchievDuel &_achievDuel ) { Assign( _achievDuel ); return *this; }
	AchievDuel( const AchievDuel &_achievDuel ) { Assign( _achievDuel ); }
	virtual void Assign( const AchievDuel &_achievDuel );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievDuel * pOther = dynamic_cast< const AchievDuel * > ( _pResource );
		if ( pOther ) AchievDuel::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievFirstAssault : public AchievBase
{
	DBRESOURCE_METHODS( AchievFirstAssault );
public:
	enum { typeId = 0x4D732B4C };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievFirstAssault::typeId; }

	AchievFirstAssault();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievFirstAssault& operator = ( const AchievFirstAssault &_achievFirstAssault ) { Assign( _achievFirstAssault ); return *this; }
	AchievFirstAssault( const AchievFirstAssault &_achievFirstAssault ) { Assign( _achievFirstAssault ); }
	virtual void Assign( const AchievFirstAssault &_achievFirstAssault );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievFirstAssault * pOther = dynamic_cast< const AchievFirstAssault * > ( _pResource );
		if ( pOther ) AchievFirstAssault::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievFirstBlood : public AchievBase
{
	DBRESOURCE_METHODS( AchievFirstBlood );
public:
	enum { typeId = 0x4D72CBC3 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievFirstBlood::typeId; }

	AchievFirstBlood();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievFirstBlood& operator = ( const AchievFirstBlood &_achievFirstBlood ) { Assign( _achievFirstBlood ); return *this; }
	AchievFirstBlood( const AchievFirstBlood &_achievFirstBlood ) { Assign( _achievFirstBlood ); }
	virtual void Assign( const AchievFirstBlood &_achievFirstBlood );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievFirstBlood * pOther = dynamic_cast< const AchievFirstBlood * > ( _pResource );
		if ( pOther ) AchievFirstBlood::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievFirstMinigameComplete : public AchievBase
{
	DBRESOURCE_METHODS( AchievFirstMinigameComplete );
public:
	enum { typeId = 0x4D738C04 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievFirstMinigameComplete::typeId; }

	AchievFirstMinigameComplete();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievFirstMinigameComplete& operator = ( const AchievFirstMinigameComplete &_achievFirstMinigameComplete ) { Assign( _achievFirstMinigameComplete ); return *this; }
	AchievFirstMinigameComplete( const AchievFirstMinigameComplete &_achievFirstMinigameComplete ) { Assign( _achievFirstMinigameComplete ); }
	virtual void Assign( const AchievFirstMinigameComplete &_achievFirstMinigameComplete );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievFirstMinigameComplete * pOther = dynamic_cast< const AchievFirstMinigameComplete * > ( _pResource );
		if ( pOther ) AchievFirstMinigameComplete::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievForestHunter : public AchievRuler
{
	DBRESOURCE_METHODS( AchievForestHunter );
public:
	enum { typeId = 0x4D732B52 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievForestHunter::typeId; }

	AchievForestHunter();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievForestHunter& operator = ( const AchievForestHunter &_achievForestHunter ) { Assign( _achievForestHunter ); return *this; }
	AchievForestHunter( const AchievForestHunter &_achievForestHunter ) { Assign( _achievForestHunter ); }
	virtual void Assign( const AchievForestHunter &_achievForestHunter );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievForestHunter * pOther = dynamic_cast< const AchievForestHunter * > ( _pResource );
		if ( pOther ) AchievForestHunter::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievGoldRite : public AchievStreak
{
	DBRESOURCE_METHODS( AchievGoldRite );
public:
	enum { typeId = 0x4D738C02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievGoldRite::typeId; }

	AchievGoldRite();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievGoldRite& operator = ( const AchievGoldRite &_achievGoldRite ) { Assign( _achievGoldRite ); return *this; }
	AchievGoldRite( const AchievGoldRite &_achievGoldRite ) { Assign( _achievGoldRite ); }
	virtual void Assign( const AchievGoldRite &_achievGoldRite );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievGoldRite * pOther = dynamic_cast< const AchievGoldRite * > ( _pResource );
		if ( pOther ) AchievGoldRite::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievKillingSpree : public AchievRuler
{
	DBRESOURCE_METHODS( AchievKillingSpree );
public:
	enum { typeId = 0x4D732A80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievKillingSpree::typeId; }

	AchievKillingSpree();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievKillingSpree& operator = ( const AchievKillingSpree &_achievKillingSpree ) { Assign( _achievKillingSpree ); return *this; }
	AchievKillingSpree( const AchievKillingSpree &_achievKillingSpree ) { Assign( _achievKillingSpree ); }
	virtual void Assign( const AchievKillingSpree &_achievKillingSpree );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievKillingSpree * pOther = dynamic_cast< const AchievKillingSpree * > ( _pResource );
		if ( pOther ) AchievKillingSpree::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievKittySlayer : public AchievBase
{
	DBRESOURCE_METHODS( AchievKittySlayer );
public:
	enum { typeId = 0x37B1DC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievKittySlayer::typeId; }
	vector< Ptr< Creature > > kitties;

	AchievKittySlayer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievKittySlayer& operator = ( const AchievKittySlayer &_achievKittySlayer ) { Assign( _achievKittySlayer ); return *this; }
	AchievKittySlayer( const AchievKittySlayer &_achievKittySlayer ) { Assign( _achievKittySlayer ); }
	virtual void Assign( const AchievKittySlayer &_achievKittySlayer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievKittySlayer * pOther = dynamic_cast< const AchievKittySlayer * > ( _pResource );
		if ( pOther ) AchievKittySlayer::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievLegend : public AchievBase
{
	DBRESOURCE_METHODS( AchievLegend );
public:
	enum { typeId = 0x4D732B51 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievLegend::typeId; }
	vector< Ptr< Creature > > creatures;

	AchievLegend();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievLegend& operator = ( const AchievLegend &_achievLegend ) { Assign( _achievLegend ); return *this; }
	AchievLegend( const AchievLegend &_achievLegend ) { Assign( _achievLegend ); }
	virtual void Assign( const AchievLegend &_achievLegend );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievLegend * pOther = dynamic_cast< const AchievLegend * > ( _pResource );
		if ( pOther ) AchievLegend::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievMassAssist : public AchievBase
{
	DBRESOURCE_METHODS( AchievMassAssist );
public:
	enum { typeId = 0x4D732B48 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievMassAssist::typeId; }
	int timeLimit;
	int cnt;

	AchievMassAssist();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievMassAssist& operator = ( const AchievMassAssist &_achievMassAssist ) { Assign( _achievMassAssist ); return *this; }
	AchievMassAssist( const AchievMassAssist &_achievMassAssist ) { Assign( _achievMassAssist ); }
	virtual void Assign( const AchievMassAssist &_achievMassAssist );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievMassAssist * pOther = dynamic_cast< const AchievMassAssist * > ( _pResource );
		if ( pOther ) AchievMassAssist::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievMassKill : public AchievBase
{
	DBRESOURCE_METHODS( AchievMassKill );
public:
	enum { typeId = 0x4D732B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievMassKill::typeId; }
	int timeLimit;
	int cnt;

	AchievMassKill();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievMassKill& operator = ( const AchievMassKill &_achievMassKill ) { Assign( _achievMassKill ); return *this; }
	AchievMassKill( const AchievMassKill &_achievMassKill ) { Assign( _achievMassKill ); }
	virtual void Assign( const AchievMassKill &_achievMassKill );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievMassKill * pOther = dynamic_cast< const AchievMassKill * > ( _pResource );
		if ( pOther ) AchievMassKill::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievMasterControl : public AchievRuler
{
	DBRESOURCE_METHODS( AchievMasterControl );
public:
	enum { typeId = 0x4D732B4A };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievMasterControl::typeId; }

	AchievMasterControl();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievMasterControl& operator = ( const AchievMasterControl &_achievMasterControl ) { Assign( _achievMasterControl ); return *this; }
	AchievMasterControl( const AchievMasterControl &_achievMasterControl ) { Assign( _achievMasterControl ); }
	virtual void Assign( const AchievMasterControl &_achievMasterControl );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievMasterControl * pOther = dynamic_cast< const AchievMasterControl * > ( _pResource );
		if ( pOther ) AchievMasterControl::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievNecklaceOfGlory : public AchievStreak
{
	DBRESOURCE_METHODS( AchievNecklaceOfGlory );
public:
	enum { typeId = 0x4D738C01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievNecklaceOfGlory::typeId; }

	AchievNecklaceOfGlory();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievNecklaceOfGlory& operator = ( const AchievNecklaceOfGlory &_achievNecklaceOfGlory ) { Assign( _achievNecklaceOfGlory ); return *this; }
	AchievNecklaceOfGlory( const AchievNecklaceOfGlory &_achievNecklaceOfGlory ) { Assign( _achievNecklaceOfGlory ); }
	virtual void Assign( const AchievNecklaceOfGlory &_achievNecklaceOfGlory );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievNecklaceOfGlory * pOther = dynamic_cast< const AchievNecklaceOfGlory * > ( _pResource );
		if ( pOther ) AchievNecklaceOfGlory::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievAssistingSpree : public AchievRuler
{
	DBRESOURCE_METHODS( AchievAssistingSpree );
public:
	enum { typeId = 0x4D732B4A };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievAssistingSpree::typeId; }

	AchievAssistingSpree();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievAssistingSpree& operator = ( const AchievAssistingSpree &_achievAssistingSpree ) { Assign( _achievAssistingSpree ); return *this; }
	AchievAssistingSpree( const AchievAssistingSpree &_achievAssistingSpree ) { Assign( _achievAssistingSpree ); }
	virtual void Assign( const AchievAssistingSpree &_achievAssistingSpree );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievAssistingSpree * pOther = dynamic_cast< const AchievAssistingSpree * > ( _pResource );
		if ( pOther ) AchievAssistingSpree::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievSaviour : public AchievBase
{
	DBRESOURCE_METHODS( AchievSaviour );
public:
	enum { typeId = 0x4D732B49 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievSaviour::typeId; }
	int minLifePercent;
	int damageDealedPeriod;
	Ptr< ApplicatorsList > applicatorTypes;
	Ptr< ApplicatorsList > exactApplicators;
	int cooldownPeriod;
	float timeToLive;
	float timeToNoDamage;

	AchievSaviour();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievSaviour& operator = ( const AchievSaviour &_achievSaviour ) { Assign( _achievSaviour ); return *this; }
	AchievSaviour( const AchievSaviour &_achievSaviour ) { Assign( _achievSaviour ); }
	virtual void Assign( const AchievSaviour &_achievSaviour );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievSaviour * pOther = dynamic_cast< const AchievSaviour * > ( _pResource );
		if ( pOther ) AchievSaviour::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievSessionDuration : public AchievBase
{
	DBRESOURCE_METHODS( AchievSessionDuration );
public:
	enum { typeId = 0xE79BD3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievSessionDuration::typeId; }
	float minTime;
	float maxTime;
	bool winners;
	bool loosers;

	AchievSessionDuration();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievSessionDuration& operator = ( const AchievSessionDuration &_achievSessionDuration ) { Assign( _achievSessionDuration ); return *this; }
	AchievSessionDuration( const AchievSessionDuration &_achievSessionDuration ) { Assign( _achievSessionDuration ); }
	virtual void Assign( const AchievSessionDuration &_achievSessionDuration );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievSessionDuration * pOther = dynamic_cast< const AchievSessionDuration * > ( _pResource );
		if ( pOther ) AchievSessionDuration::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievAscension : public AchievStreak
{
	DBRESOURCE_METHODS( AchievAscension );
public:
	enum { typeId = 0x4D738C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievAscension::typeId; }

	AchievAscension();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievAscension& operator = ( const AchievAscension &_achievAscension ) { Assign( _achievAscension ); return *this; }
	AchievAscension( const AchievAscension &_achievAscension ) { Assign( _achievAscension ); }
	virtual void Assign( const AchievAscension &_achievAscension );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievAscension * pOther = dynamic_cast< const AchievAscension * > ( _pResource );
		if ( pOther ) AchievAscension::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievTowerDeny : public AchievBase
{
	DBRESOURCE_METHODS( AchievTowerDeny );
public:
	enum { typeId = 0x4D731440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievTowerDeny::typeId; }

	AchievTowerDeny();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievTowerDeny& operator = ( const AchievTowerDeny &_achievTowerDeny ) { Assign( _achievTowerDeny ); return *this; }
	AchievTowerDeny( const AchievTowerDeny &_achievTowerDeny ) { Assign( _achievTowerDeny ); }
	virtual void Assign( const AchievTowerDeny &_achievTowerDeny );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievTowerDeny * pOther = dynamic_cast< const AchievTowerDeny * > ( _pResource );
		if ( pOther ) AchievTowerDeny::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievVandalism : public AchievRuler
{
	DBRESOURCE_METHODS( AchievVandalism );
public:
	enum { typeId = 0x4D732B4E };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievVandalism::typeId; }

	AchievVandalism();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievVandalism& operator = ( const AchievVandalism &_achievVandalism ) { Assign( _achievVandalism ); return *this; }
	AchievVandalism( const AchievVandalism &_achievVandalism ) { Assign( _achievVandalism ); }
	virtual void Assign( const AchievVandalism &_achievVandalism );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievVandalism * pOther = dynamic_cast< const AchievVandalism * > ( _pResource );
		if ( pOther ) AchievVandalism::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievVendetta : public AchievBase
{
	DBRESOURCE_METHODS( AchievVendetta );
public:
	enum { typeId = 0x4D732B46 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievVendetta::typeId; }
	int minKillsForDominate;

	AchievVendetta();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievVendetta& operator = ( const AchievVendetta &_achievVendetta ) { Assign( _achievVendetta ); return *this; }
	AchievVendetta( const AchievVendetta &_achievVendetta ) { Assign( _achievVendetta ); }
	virtual void Assign( const AchievVendetta &_achievVendetta );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievVendetta * pOther = dynamic_cast< const AchievVendetta * > ( _pResource );
		if ( pOther ) AchievVendetta::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct AchievWarLord : public AchievRuler
{
	DBRESOURCE_METHODS( AchievWarLord );
public:
	enum { typeId = 0x4D7324C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AchievWarLord::typeId; }

	AchievWarLord();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AchievWarLord& operator = ( const AchievWarLord &_achievWarLord ) { Assign( _achievWarLord ); return *this; }
	AchievWarLord( const AchievWarLord &_achievWarLord ) { Assign( _achievWarLord ); }
	virtual void Assign( const AchievWarLord &_achievWarLord );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AchievWarLord * pOther = dynamic_cast< const AchievWarLord * > ( _pResource );
		if ( pOther ) AchievWarLord::Assign( *pOther );
	}

	virtual NWorld::PFAchievBase* Create( NWorld::PFWorld* world ) const;
};

struct Actor : public DbResource
{
	DBRESOURCE_METHODS( Actor );
public:
	CTextRef name;
	Ptr< Texture > icon;

	Actor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Actor& operator = ( const Actor &_actor ) { Assign( _actor ); return *this; }
	Actor( const Actor &_actor ) { Assign( _actor ); }
	virtual void Assign( const Actor &_actor );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Actor * pOther = dynamic_cast< const Actor * > ( _pResource );
		if ( pOther ) Actor::Assign( *pOther );
	}
};

struct AdventureCameraSettings : public DbResource
{
	DBRESOURCE_METHODS( AdventureCameraSettings );
public:
	string name;
	float movementSpeed;
	float vertAngleBottom;
	float vertLengthBottom;
	float vertAngleTop;
	float vertLengthTop;
	float vertTime;
	float horCenterAngle;
	float horAngle;
	float horTime;
	float limitRadiusHor;
	float limitRadiusVert;
	float fov;
	float fovCorrectionAngle;
	float smoothRadius;
	int smoothDiscrete;
	float smoothDensity;
	float pitchRMax;
	float pitchRConst;
	int pitchDiscrete;
	float minCameraHeight;
	CVec2 centerOffset;
	float zoomSpeed;
	float maxZoomFactor;
	float lockMultRadiusHor;
	float lockMultRadiusVert;
	CVec2 lockCenterOffset;
	DampSmoothing dampSmoothing;

	AdventureCameraSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdventureCameraSettings& operator = ( const AdventureCameraSettings &_adventureCameraSettings ) { Assign( _adventureCameraSettings ); return *this; }
	AdventureCameraSettings( const AdventureCameraSettings &_adventureCameraSettings ) { Assign( _adventureCameraSettings ); }
	virtual void Assign( const AdventureCameraSettings &_adventureCameraSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdventureCameraSettings * pOther = dynamic_cast< const AdventureCameraSettings * > ( _pResource );
		if ( pOther ) AdventureCameraSettings::Assign( *pOther );
	}
};

struct AdventureTooltipParams : public DbResource
{
	DBRESOURCE_METHODS( AdventureTooltipParams );
public:
	vector< UnitOvertipSettings > units;
	CTextRef locatorName;

	AdventureTooltipParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdventureTooltipParams& operator = ( const AdventureTooltipParams &_adventureTooltipParams ) { Assign( _adventureTooltipParams ); return *this; }
	AdventureTooltipParams( const AdventureTooltipParams &_adventureTooltipParams ) { Assign( _adventureTooltipParams ); }
	virtual void Assign( const AdventureTooltipParams &_adventureTooltipParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdventureTooltipParams * pOther = dynamic_cast< const AdventureTooltipParams * > ( _pResource );
		if ( pOther ) AdventureTooltipParams::Assign( *pOther );
	}
};

struct AdventureTooltipSettings : public DbResource
{
	DBRESOURCE_METHODS( AdventureTooltipSettings );
public:
	bool showDesc;
	EAdventureTooltipStretchMode stretch;
	string uiState;
	string uiStateShort;
	CTextRef text;

	AdventureTooltipSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdventureTooltipSettings& operator = ( const AdventureTooltipSettings &_adventureTooltipSettings ) { Assign( _adventureTooltipSettings ); return *this; }
	AdventureTooltipSettings( const AdventureTooltipSettings &_adventureTooltipSettings ) { Assign( _adventureTooltipSettings ); }
	virtual void Assign( const AdventureTooltipSettings &_adventureTooltipSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdventureTooltipSettings * pOther = dynamic_cast< const AdventureTooltipSettings * > ( _pResource );
		if ( pOther ) AdventureTooltipSettings::Assign( *pOther );
	}
};

struct AdvMapModeDescription : public DbResource
{
	DBRESOURCE_METHODS( AdvMapModeDescription );
public:
	Ptr< Texture > icon;
	CTextRef tooltip;

	AdvMapModeDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapModeDescription& operator = ( const AdvMapModeDescription &_advMapModeDescription ) { Assign( _advMapModeDescription ); return *this; }
	AdvMapModeDescription( const AdvMapModeDescription &_advMapModeDescription ) { Assign( _advMapModeDescription ); }
	virtual void Assign( const AdvMapModeDescription &_advMapModeDescription );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapModeDescription * pOther = dynamic_cast< const AdvMapModeDescription * > ( _pResource );
		if ( pOther ) AdvMapModeDescription::Assign( *pOther );
	}
};

struct BindCategory : public DbResource
{
	DBRESOURCE_METHODS( BindCategory );
public:
	int index;
	CTextRef name;

	BindCategory();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BindCategory& operator = ( const BindCategory &_bindCategory ) { Assign( _bindCategory ); return *this; }
	BindCategory( const BindCategory &_bindCategory ) { Assign( _bindCategory ); }
	virtual void Assign( const BindCategory &_bindCategory );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BindCategory * pOther = dynamic_cast< const BindCategory * > ( _pResource );
		if ( pOther ) BindCategory::Assign( *pOther );
	}
};

struct CustomFlag : public DbResource
{
	DBRESOURCE_METHODS( CustomFlag );
public:
	string id;
	Ptr< Texture > icon;
	Ptr< Texture > bigIcon;
	CTextRef name;
	CTextRef tooltip;
	int Price;

	CustomFlag();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CustomFlag& operator = ( const CustomFlag &_customFlag ) { Assign( _customFlag ); return *this; }
	CustomFlag( const CustomFlag &_customFlag ) { Assign( _customFlag ); }
	virtual void Assign( const CustomFlag &_customFlag );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CustomFlag * pOther = dynamic_cast< const CustomFlag * > ( _pResource );
		if ( pOther ) CustomFlag::Assign( *pOther );
	}
};

struct DBMinimap : public DbResource
{
	DBRESOURCE_METHODS( DBMinimap );
public:
	float normalOpacity;
	float minigameOpacity;
	float transitionVelocity;
	float signalLifeTime;
	Render::Color signalDefaultColor;
	Render::Color enemyColor;
	Render::Color allyColor;
	Render::Color neutralColor;
	Ptr< Texture > enemyHeroFrame;
	Ptr< Texture > allyHeroFrame;
	Ptr< Texture > localHeroFrame;
	vector< Ptr< Texture > > icons;
	Render::Color targetZoneColor;
	int targetZoneLineThickness;

	DBMinimap();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBMinimap& operator = ( const DBMinimap &_dBMinimap ) { Assign( _dBMinimap ); return *this; }
	DBMinimap( const DBMinimap &_dBMinimap ) { Assign( _dBMinimap ); }
	virtual void Assign( const DBMinimap &_dBMinimap );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBMinimap * pOther = dynamic_cast< const DBMinimap * > ( _pResource );
		if ( pOther ) DBMinimap::Assign( *pOther );
	}
};

struct DBStatisticData : public DbResource
{
	DBRESOURCE_METHODS( DBStatisticData );
public:
	CTextRef winnersTeamStr;
	CTextRef losersTeamStr;
	CTextRef levelFormatStr;
	CTextRef favoritesFeatsStr;
	CTextRef timeUnderBlessingStr;
	CTextRef totalHeartsStr;
	CTextRef heartsFromMenAndMinigamesStr;
	CTextRef goldAndSilverFromMinigameStr;
	CTextRef killingAssistantsStr;

	DBStatisticData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBStatisticData& operator = ( const DBStatisticData &_dBStatisticData ) { Assign( _dBStatisticData ); return *this; }
	DBStatisticData( const DBStatisticData &_dBStatisticData ) { Assign( _dBStatisticData ); }
	virtual void Assign( const DBStatisticData &_dBStatisticData );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBStatisticData * pOther = dynamic_cast< const DBStatisticData * > ( _pResource );
		if ( pOther ) DBStatisticData::Assign( *pOther );
	}
};

struct DBTooltip : public DbResource
{
	DBRESOURCE_METHODS( DBTooltip );
public:
	CTextRef friendStyle;
	CTextRef enemyStyle;
	CTextRef heroInfo;
	CTextRef unitInfo;

	DBTooltip();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBTooltip& operator = ( const DBTooltip &_dBTooltip ) { Assign( _dBTooltip ); return *this; }
	DBTooltip( const DBTooltip &_dBTooltip ) { Assign( _dBTooltip ); }
	virtual void Assign( const DBTooltip &_dBTooltip );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBTooltip * pOther = dynamic_cast< const DBTooltip * > ( _pResource );
		if ( pOther ) DBTooltip::Assign( *pOther );
	}
};

struct DBUIData : public DbResource
{
	DBRESOURCE_METHODS( DBUIData );
public:
	vector< StatParams > elements;
	CombatStatuses combatStatuses;
	PWSoundEvents soundEvents;
	AttackType attackType;
	ImpulsiveBuffsParams impulsiveBuffsParams;
	Render::HDRColor colorPreselect;
	Render::HDRColor outlineAllyColor;
	Render::HDRColor outlineHostileColor;
	Render::HDRColor outlineSelfColor;
	float outlineThickness;
	GameUIData gameUIData;
	vector< PathMarkerColor > pathMarkerColor;
	vector< CTextRef > rarityValue;
	DamageBloodMaskParams bloodMaskParams;
	vector< ErrorMessageDescription > errorMessageDescriptions;
	CharStatTooltips charStatTooltips;
	Ptr< DBMinimap > minimap;
	float tooltipDownScaleLimit;
	BattleStartAnnouncementParams battleStartAnnouncementParams;
	float mouseScrollingFieldSize;
	vector< ChatChannelDescription > chatChannelDescriptions;
	Render::HDRColor adminMessageColor;
	vector< ResourceDescription > resourcesDescriptions;
	vector< ResourceDescription > clanWarsResourcesDescriptions;
	VictoryDefeatImages victoryDefeatImages;
	IgnoreListParams ignoreListParams;
	MarkerSettings markerSettings;
	ForceToColorTable forceColors;
	DialogsSettings dialogsSettings;
	PingAbuseSettings pingAbuseSettings;
	Render::HDRColor blockSaturationColor;
	MapModeCustomDescriptions mapModeCustomDescriptions;
	vector< StringTextRefPair > loadingScreenStatuses;
	PremiumVisualInfo premiumVisualInfo;
	vector< Locale > locales;
	vector< TipOfTheDay > tips;
	vector< ReportType > reportTypes;
	Binds binds;
	vector< CountryFlag > countryFlags;
	BotDefaultFlags botFlags;
	vector< Ptr< CustomFlag > > customFlags;
	vector< Ptr< CustomFlag > > adminFlags;
	vector< GuildShopTab > guildShopTabs;
	Ptr< SmartChatConfiguration > smartChat;
	SmartChatAbuseSettings smartChatAbuseSettings;
	int RecentPlayers;
	Ptr< CurrencyDescriptionList > currencies;

	DBUIData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBUIData& operator = ( const DBUIData &_dBUIData ) { Assign( _dBUIData ); return *this; }
	DBUIData( const DBUIData &_dBUIData ) { Assign( _dBUIData ); }
	virtual void Assign( const DBUIData &_dBUIData );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBUIData * pOther = dynamic_cast< const DBUIData * > ( _pResource );
		if ( pOther ) DBUIData::Assign( *pOther );
	}
};

struct DerivativeStatsContainer : public DbResource
{
	DBRESOURCE_METHODS( DerivativeStatsContainer );
public:
	vector< ExecutableFloatString > derivativeStats;

	DerivativeStatsContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DerivativeStatsContainer& operator = ( const DerivativeStatsContainer &_derivativeStatsContainer ) { Assign( _derivativeStatsContainer ); return *this; }
	DerivativeStatsContainer( const DerivativeStatsContainer &_derivativeStatsContainer ) { Assign( _derivativeStatsContainer ); }
	virtual void Assign( const DerivativeStatsContainer &_derivativeStatsContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DerivativeStatsContainer * pOther = dynamic_cast< const DerivativeStatsContainer * > ( _pResource );
		if ( pOther ) DerivativeStatsContainer::Assign( *pOther );
	}
};

struct Dialog : public DbResource
{
	DBRESOURCE_METHODS( Dialog );
public:
	string id;
	CTextRef title;
	vector< Phrase > phrasesA;
	vector< Phrase > phrasesB;

	Dialog();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Dialog& operator = ( const Dialog &_dialog ) { Assign( _dialog ); return *this; }
	Dialog( const Dialog &_dialog ) { Assign( _dialog ); }
	virtual void Assign( const Dialog &_dialog );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Dialog * pOther = dynamic_cast< const Dialog * > ( _pResource );
		if ( pOther ) Dialog::Assign( *pOther );
	}
};

struct DialogsCollection : public DbResource
{
	DBRESOURCE_METHODS( DialogsCollection );
public:
	vector< Ptr< Dialog > > dialogs;

	DialogsCollection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DialogsCollection& operator = ( const DialogsCollection &_dialogsCollection ) { Assign( _dialogsCollection ); return *this; }
	DialogsCollection( const DialogsCollection &_dialogsCollection ) { Assign( _dialogsCollection ); }
	virtual void Assign( const DialogsCollection &_dialogsCollection );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DialogsCollection * pOther = dynamic_cast< const DialogsCollection * > ( _pResource );
		if ( pOther ) DialogsCollection::Assign( *pOther );
	}
};

struct FactionScoringTable : public DbResource
{
	DBRESOURCE_METHODS( FactionScoringTable );
public:
	int loose;
	int win;
	float towerDestroyedBase;
	float towerDestroyedLevelMul;
	int bossKill;
	int topKills;
	int topAssists;
	int maxBossKillScore;

	FactionScoringTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FactionScoringTable& operator = ( const FactionScoringTable &_factionScoringTable ) { Assign( _factionScoringTable ); return *this; }
	FactionScoringTable( const FactionScoringTable &_factionScoringTable ) { Assign( _factionScoringTable ); }
	virtual void Assign( const FactionScoringTable &_factionScoringTable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FactionScoringTable * pOther = dynamic_cast< const FactionScoringTable * > ( _pResource );
		if ( pOther ) FactionScoringTable::Assign( *pOther );
	}
};

struct FakeObj : public DbResource
{
public:
	enum { typeId = 0x8D7C7280 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FakeObj::typeId; }

	FakeObj();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FakeObj& operator = ( const FakeObj &_fakeObj ) { Assign( _fakeObj ); return *this; }
	FakeObj( const FakeObj &_fakeObj ) { Assign( _fakeObj ); }
	virtual void Assign( const FakeObj &_fakeObj );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FakeObj * pOther = dynamic_cast< const FakeObj * > ( _pResource );
		if ( pOther ) FakeObj::Assign( *pOther );
	}

	virtual NWorld::PFWorld* Create() const;
};

struct HeroScoringTable : public DbResource
{
	DBRESOURCE_METHODS( HeroScoringTable );
public:
	int heroOfTheDay;
	int towerKill;
	RestrictedScoring heroKill;
	RestrictedScoring bossKill;
	RestrictedScoring goldMedals;
	RestrictedScoring silverMedals;
	RestrictedScoring buildingDestroy;
	DiscreteScoring flagRaise;
	DiscreteScoring flagDrop;

	HeroScoringTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroScoringTable& operator = ( const HeroScoringTable &_heroScoringTable ) { Assign( _heroScoringTable ); return *this; }
	HeroScoringTable( const HeroScoringTable &_heroScoringTable ) { Assign( _heroScoringTable ); }
	virtual void Assign( const HeroScoringTable &_heroScoringTable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroScoringTable * pOther = dynamic_cast< const HeroScoringTable * > ( _pResource );
		if ( pOther ) HeroScoringTable::Assign( *pOther );
	}
};

struct HintsCollection : public DbResource
{
	DBRESOURCE_METHODS( HintsCollection );
public:
	vector< Hint > hints;

	HintsCollection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HintsCollection& operator = ( const HintsCollection &_hintsCollection ) { Assign( _hintsCollection ); return *this; }
	HintsCollection( const HintsCollection &_hintsCollection ) { Assign( _hintsCollection ); }
	virtual void Assign( const HintsCollection &_hintsCollection );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HintsCollection * pOther = dynamic_cast< const HintsCollection * > ( _pResource );
		if ( pOther ) HintsCollection::Assign( *pOther );
	}
};

struct MinimapImages : public DbResource
{
	DBRESOURCE_METHODS( MinimapImages );
public:
	Ptr< TextureBase > firstMap;
	Ptr< TextureBase > secondMap;
	Ptr< TextureBase > neutralMap;
	CVec2 centerOffset;
	float scaleFactor;

	MinimapImages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinimapImages& operator = ( const MinimapImages &_minimapImages ) { Assign( _minimapImages ); return *this; }
	MinimapImages( const MinimapImages &_minimapImages ) { Assign( _minimapImages ); }
	virtual void Assign( const MinimapImages &_minimapImages );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinimapImages * pOther = dynamic_cast< const MinimapImages * > ( _pResource );
		if ( pOther ) MinimapImages::Assign( *pOther );
	}
};

struct PFTerrainTypeInfo : public TerrainTypeInfo
{
	DBRESOURCE_METHODS( PFTerrainTypeInfo );
public:
	ETerrainType eType;

	PFTerrainTypeInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PFTerrainTypeInfo& operator = ( const PFTerrainTypeInfo &_pFTerrainTypeInfo ) { Assign( _pFTerrainTypeInfo ); return *this; }
	PFTerrainTypeInfo( const PFTerrainTypeInfo &_pFTerrainTypeInfo ) { Assign( _pFTerrainTypeInfo ); }
	virtual void Assign( const PFTerrainTypeInfo &_pFTerrainTypeInfo );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PFTerrainTypeInfo * pOther = dynamic_cast< const PFTerrainTypeInfo * > ( _pResource );
		if ( pOther ) PFTerrainTypeInfo::Assign( *pOther );
	}
};

struct PFUIGameLogicRoot : public DbResource
{
	DBRESOURCE_METHODS( PFUIGameLogicRoot );
public:
	Ptr< DBStatisticData > statisticData;

	PFUIGameLogicRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PFUIGameLogicRoot& operator = ( const PFUIGameLogicRoot &_pFUIGameLogicRoot ) { Assign( _pFUIGameLogicRoot ); return *this; }
	PFUIGameLogicRoot( const PFUIGameLogicRoot &_pFUIGameLogicRoot ) { Assign( _pFUIGameLogicRoot ); }
	virtual void Assign( const PFUIGameLogicRoot &_pFUIGameLogicRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PFUIGameLogicRoot * pOther = dynamic_cast< const PFUIGameLogicRoot * > ( _pResource );
		if ( pOther ) PFUIGameLogicRoot::Assign( *pOther );
	}
};

struct ScoringTable : public DbResource
{
	DBRESOURCE_METHODS( ScoringTable );
public:
	enum { typeId = 0xA06693C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScoringTable::typeId; }
	Ptr< FactionScoringTable > faction;
	Ptr< HeroScoringTable > hero;
	vector< Ptr< AchievBase > > achievementsList;
	vector< HeroTitle > heroTitles;
	vector< ScoreDescription > scoreDescriptions;
	vector< Ptr< Ability > > teleporterAbilities;

	ScoringTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScoringTable& operator = ( const ScoringTable &_scoringTable ) { Assign( _scoringTable ); return *this; }
	ScoringTable( const ScoringTable &_scoringTable ) { Assign( _scoringTable ); }
	virtual void Assign( const ScoringTable &_scoringTable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScoringTable * pOther = dynamic_cast< const ScoringTable * > ( _pResource );
		if ( pOther ) ScoringTable::Assign( *pOther );
	}
};

struct SessionQuestsCollection : public DbResource
{
	DBRESOURCE_METHODS( SessionQuestsCollection );
public:
	vector< SessionQuest > quests;

	SessionQuestsCollection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionQuestsCollection& operator = ( const SessionQuestsCollection &_sessionQuestsCollection ) { Assign( _sessionQuestsCollection ); return *this; }
	SessionQuestsCollection( const SessionQuestsCollection &_sessionQuestsCollection ) { Assign( _sessionQuestsCollection ); }
	virtual void Assign( const SessionQuestsCollection &_sessionQuestsCollection );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionQuestsCollection * pOther = dynamic_cast< const SessionQuestsCollection * > ( _pResource );
		if ( pOther ) SessionQuestsCollection::Assign( *pOther );
	}
};

struct StatsBudgetContainer : public DbResource
{
	DBRESOURCE_METHODS( StatsBudgetContainer );
public:
	vector< StatBudget > stats;

	StatsBudgetContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatsBudgetContainer& operator = ( const StatsBudgetContainer &_statsBudgetContainer ) { Assign( _statsBudgetContainer ); return *this; }
	StatsBudgetContainer( const StatsBudgetContainer &_statsBudgetContainer ) { Assign( _statsBudgetContainer ); }
	virtual void Assign( const StatsBudgetContainer &_statsBudgetContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatsBudgetContainer * pOther = dynamic_cast< const StatsBudgetContainer * > ( _pResource );
		if ( pOther ) StatsBudgetContainer::Assign( *pOther );
	}
};

struct StatsContainer : public DbResource
{
	DBRESOURCE_METHODS( StatsContainer );
public:
	enum { typeId = 0x0F626440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)StatsContainer::typeId; }
	vector< UnitStat > stats;

	StatsContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatsContainer& operator = ( const StatsContainer &_statsContainer ) { Assign( _statsContainer ); return *this; }
	StatsContainer( const StatsContainer &_statsContainer ) { Assign( _statsContainer ); }
	virtual void Assign( const StatsContainer &_statsContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatsContainer * pOther = dynamic_cast< const StatsContainer * > ( _pResource );
		if ( pOther ) StatsContainer::Assign( *pOther );
	}
};

struct StatsEnhancersContainer : public DbResource
{
	DBRESOURCE_METHODS( StatsEnhancersContainer );
public:
	vector< StatEnhancer > statsEnhancers;

	StatsEnhancersContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatsEnhancersContainer& operator = ( const StatsEnhancersContainer &_statsEnhancersContainer ) { Assign( _statsEnhancersContainer ); return *this; }
	StatsEnhancersContainer( const StatsEnhancersContainer &_statsEnhancersContainer ) { Assign( _statsEnhancersContainer ); }
	virtual void Assign( const StatsEnhancersContainer &_statsEnhancersContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatsEnhancersContainer * pOther = dynamic_cast< const StatsEnhancersContainer * > ( _pResource );
		if ( pOther ) StatsEnhancersContainer::Assign( *pOther );
	}
};

struct UIEvent : public DbResource
{
	DBRESOURCE_METHODS( UIEvent );
public:
	enum { typeId = 0x4D7262C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIEvent::typeId; }
	ERecipients signRecipients;
	vector< Ptr< UISign > > UISigns;

	UIEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIEvent& operator = ( const UIEvent &_uIEvent ) { Assign( _uIEvent ); return *this; }
	UIEvent( const UIEvent &_uIEvent ) { Assign( _uIEvent ); }
	virtual void Assign( const UIEvent &_uIEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIEvent * pOther = dynamic_cast< const UIEvent * > ( _pResource );
		if ( pOther ) UIEvent::Assign( *pOther );
	}
};

struct UIEventsCustom : public DbResource
{
	DBRESOURCE_METHODS( UIEventsCustom );
public:
	enum { typeId = 0x4D729C41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIEventsCustom::typeId; }
	Ptr< UIEvent > evMiss;
	Ptr< UIEvent > evGetNafta;
	Ptr< UIEvent > evHeroKill;
	Ptr< UIEvent > evHeroKillByAI;
	Ptr< UIEvent > evHeroKillByNeutralAI;
	Ptr< UIEvent > evTowerDestroy;
	Ptr< UIEvent > evTowerDestroyByAI;
	Ptr< UIEvent > evTowerDestroyByNeutralAI;
	Ptr< UIEvent > evItemTransfer;
	Ptr< UIEvent > evItemGain;
	Ptr< UIEvent > evHeroCheat;
	Ptr< UIEvent > evHeroReconnected;
	Ptr< UIEvent > evHeroDisconnected;
	Ptr< UIEvent > evHeroDisconnectedAFK;
	Ptr< UIEvent > evHeroFriendDisconnected;
	Ptr< UIEvent > evHeroFriendDisconnectedAFK;
	Ptr< UIEvent > evHeroLeft;
	Ptr< UIEvent > evHeroFriendLeft;
	Ptr< UIEvent > evHeroFriendReconnected;
	Ptr< UIEvent > evHeroAFK;
	Ptr< UIEvent > evHeroAFKEnded;
	Ptr< UIEvent > evBarrackDestroyed;
	Ptr< UIEvent > evFriendBarrackDestroyed;
	Ptr< UIEvent > evVictory;
	Ptr< UIEvent > evDefeat;
	Ptr< UIEvent > evSpectatorJoin;
	Ptr< UIEvent > evAdminMuted;
	Ptr< UIEvent > evStartAiForPlayer;
	Ptr< UIEvent > evLeaverMuted;
	Ptr< UIEvent > evLeaverPartyMuted;
	Ptr< UIEvent > evAdminMutedNotify;

	UIEventsCustom();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIEventsCustom& operator = ( const UIEventsCustom &_uIEventsCustom ) { Assign( _uIEventsCustom ); return *this; }
	UIEventsCustom( const UIEventsCustom &_uIEventsCustom ) { Assign( _uIEventsCustom ); }
	virtual void Assign( const UIEventsCustom &_uIEventsCustom );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIEventsCustom * pOther = dynamic_cast< const UIEventsCustom * > ( _pResource );
		if ( pOther ) UIEventsCustom::Assign( *pOther );
	}
};

struct UISign : public DbResource
{
public:
	enum { typeId = 0xF6264430 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UISign::typeId; }
	ERecipients signRecipients;

	UISign();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISign& operator = ( const UISign &_uISign ) { Assign( _uISign ); return *this; }
	UISign( const UISign &_uISign ) { Assign( _uISign ); }
	virtual void Assign( const UISign &_uISign );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISign * pOther = dynamic_cast< const UISign * > ( _pResource );
		if ( pOther ) UISign::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UISignAnnouncement : public UISign
{
	DBRESOURCE_METHODS( UISignAnnouncement );
public:
	EAnnouncementType announcementType;
	CTextRef txt;
	Ptr< Texture > imageBurn;
	Ptr< Texture > imageFreeze;
	int priority;
	float lifeTime;
	DBFMODEventDesc announcementSound;
	float announcementSoundCooldown;
	bool UseInTutorial;

	UISignAnnouncement();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISignAnnouncement& operator = ( const UISignAnnouncement &_uISignAnnouncement ) { Assign( _uISignAnnouncement ); return *this; }
	UISignAnnouncement( const UISignAnnouncement &_uISignAnnouncement ) { Assign( _uISignAnnouncement ); }
	virtual void Assign( const UISignAnnouncement &_uISignAnnouncement );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISignAnnouncement * pOther = dynamic_cast< const UISignAnnouncement * > ( _pResource );
		if ( pOther ) UISignAnnouncement::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UISignFlyOffText : public UISign
{
	DBRESOURCE_METHODS( UISignFlyOffText );
public:
	enum { typeId = 0xF6264434 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UISignFlyOffText::typeId; }
	FlyOffText text;

	UISignFlyOffText();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISignFlyOffText& operator = ( const UISignFlyOffText &_uISignFlyOffText ) { Assign( _uISignFlyOffText ); return *this; }
	UISignFlyOffText( const UISignFlyOffText &_uISignFlyOffText ) { Assign( _uISignFlyOffText ); }
	virtual void Assign( const UISignFlyOffText &_uISignFlyOffText );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISignFlyOffText * pOther = dynamic_cast< const UISignFlyOffText * > ( _pResource );
		if ( pOther ) UISignFlyOffText::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UISignMessageToChat : public UISign
{
	DBRESOURCE_METHODS( UISignMessageToChat );
public:
	enum { typeId = 0xF6264431 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UISignMessageToChat::typeId; }
	vector< CTextRef > messages;
	EChatChannel channel;

	UISignMessageToChat();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISignMessageToChat& operator = ( const UISignMessageToChat &_uISignMessageToChat ) { Assign( _uISignMessageToChat ); return *this; }
	UISignMessageToChat( const UISignMessageToChat &_uISignMessageToChat ) { Assign( _uISignMessageToChat ); }
	virtual void Assign( const UISignMessageToChat &_uISignMessageToChat );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISignMessageToChat * pOther = dynamic_cast< const UISignMessageToChat * > ( _pResource );
		if ( pOther ) UISignMessageToChat::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UISignMessageToStatusLine : public UISign
{
	DBRESOURCE_METHODS( UISignMessageToStatusLine );
public:
	enum { typeId = 0xF6264433 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UISignMessageToStatusLine::typeId; }
	vector< CTextRef > messages;

	UISignMessageToStatusLine();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISignMessageToStatusLine& operator = ( const UISignMessageToStatusLine &_uISignMessageToStatusLine ) { Assign( _uISignMessageToStatusLine ); return *this; }
	UISignMessageToStatusLine( const UISignMessageToStatusLine &_uISignMessageToStatusLine ) { Assign( _uISignMessageToStatusLine ); }
	virtual void Assign( const UISignMessageToStatusLine &_uISignMessageToStatusLine );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISignMessageToStatusLine * pOther = dynamic_cast< const UISignMessageToStatusLine * > ( _pResource );
		if ( pOther ) UISignMessageToStatusLine::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UISignPlaySound : public UISign
{
	DBRESOURCE_METHODS( UISignPlaySound );
public:
	enum { typeId = 0xF6264432 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UISignPlaySound::typeId; }
	DBFMODEventDesc soundDesc;

	UISignPlaySound();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UISignPlaySound& operator = ( const UISignPlaySound &_uISignPlaySound ) { Assign( _uISignPlaySound ); return *this; }
	UISignPlaySound( const UISignPlaySound &_uISignPlaySound ) { Assign( _uISignPlaySound ); }
	virtual void Assign( const UISignPlaySound &_uISignPlaySound );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UISignPlaySound * pOther = dynamic_cast< const UISignPlaySound * > ( _pResource );
		if ( pOther ) UISignPlaySound::Assign( *pOther );
	}

	virtual NGameX::PFUISign* Create() const;
};

struct UITeamInfoParams : public DbResource
{
	DBRESOURCE_METHODS( UITeamInfoParams );
public:
	TeamInfTooltipSettings tooltipSettings;

	UITeamInfoParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UITeamInfoParams& operator = ( const UITeamInfoParams &_uITeamInfoParams ) { Assign( _uITeamInfoParams ); return *this; }
	UITeamInfoParams( const UITeamInfoParams &_uITeamInfoParams ) { Assign( _uITeamInfoParams ); }
	virtual void Assign( const UITeamInfoParams &_uITeamInfoParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UITeamInfoParams * pOther = dynamic_cast< const UITeamInfoParams * > ( _pResource );
		if ( pOther ) UITeamInfoParams::Assign( *pOther );
	}
};

struct WebTowerCameraSettings : public DbResource
{
	DBRESOURCE_METHODS( WebTowerCameraSettings );
public:
	float linearSpeed;
	float initialPitch;
	float yawSpeed;
	float heightOffset;
	float minRod;
	float maxRod;

	WebTowerCameraSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WebTowerCameraSettings& operator = ( const WebTowerCameraSettings &_webTowerCameraSettings ) { Assign( _webTowerCameraSettings ); return *this; }
	WebTowerCameraSettings( const WebTowerCameraSettings &_webTowerCameraSettings ) { Assign( _webTowerCameraSettings ); }
	virtual void Assign( const WebTowerCameraSettings &_webTowerCameraSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WebTowerCameraSettings * pOther = dynamic_cast< const WebTowerCameraSettings * > ( _pResource );
		if ( pOther ) WebTowerCameraSettings::Assign( *pOther );
	}
};

}; // namespace NDb
