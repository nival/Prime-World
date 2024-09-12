#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct AdvMapDescription;
struct AdvMapSettings;
struct AILogicParameters;
struct ClanWarsSettings;
struct ContainersBySpecialPoints;
struct CustomFlag;
struct DefaultFormulas;
struct GameSvcSettings;
struct GlyphsDB;
struct GuildBonus;
struct GuildBuff;
struct GuildBuffsCollection;
struct GuildLevels;
struct GuildShopItemBonus;
struct Hero;
struct HeroesDB;
struct HeroesLevelUps;
struct HeroRanks;
struct HeroSkin;
struct ImpulsiveBuffsContainer;
struct MapList;
struct MapMMakingSettings;
struct ModeRollSettings;
struct RollContainer;
struct RollContainerCostByRank;
struct RollContainerCountByRank;
struct RollItem;
struct RollSettings;
struct ScoringTable;
struct SessionAudioRoot;
struct SessionLogicRoot;
struct SessionMessages;
struct SessionUIRoot;
struct SessionVisualRoot;
struct Talent;
struct TalentUpgradeEntity;
struct TalentUpgradeProbabilityTable;
struct UnitsLogicParameters;

enum BillingServicesStart
{
	BILLINGSERVICESSTART_IMPULSES = 100,
	BILLINGSERVICESSTART_GENERIC = 1000,
	BILLINGSERVICESSTART_REWARDS = 2000,
};

const char *EnumToString( const BillingServicesStart value );
const BillingServicesStart StringToEnum_BillingServicesStart( const char* value );

template <>
struct KnownEnum< BillingServicesStart >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const BillingServicesStart value ) { return EnumToString( value ); }
	static const BillingServicesStart ToEnum( const char* value ) { return StringToEnum_BillingServicesStart( value ); }
	static const BillingServicesStart ToEnum( const string& value ) { return StringToEnum_BillingServicesStart( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ClanWarsRollItemType
{
	CLANWARSROLLITEMTYPE_CLANRATING = 0,
	CLANWARSROLLITEMTYPE_PLAYERRATING = 1,
};

const char *EnumToString( const ClanWarsRollItemType value );
const ClanWarsRollItemType StringToEnum_ClanWarsRollItemType( const char* value );

template <>
struct KnownEnum< ClanWarsRollItemType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ClanWarsRollItemType value ) { return EnumToString( value ); }
	static const ClanWarsRollItemType ToEnum( const char* value ) { return StringToEnum_ClanWarsRollItemType( value ); }
	static const ClanWarsRollItemType ToEnum( const string& value ) { return StringToEnum_ClanWarsRollItemType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EBotRollMode
{
	BOTROLLMODE_ENABLED = 0,
	BOTROLLMODE_DISABLED = 1,
	BOTROLLMODE_DISABLEDASENEMY = 2,
};

const char *EnumToString( const EBotRollMode value );
const EBotRollMode StringToEnum_EBotRollMode( const char* value );

template <>
struct KnownEnum< EBotRollMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EBotRollMode value ) { return EnumToString( value ); }
	static const EBotRollMode ToEnum( const char* value ) { return StringToEnum_EBotRollMode( value ); }
	static const EBotRollMode ToEnum( const string& value ) { return StringToEnum_EBotRollMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EBuildingProductionCycle
{
	BUILDINGPRODUCTIONCYCLE_FIRST = 1,
	BUILDINGPRODUCTIONCYCLE_SECOND = 2,
	BUILDINGPRODUCTIONCYCLE_THIRD = 4,
	BUILDINGPRODUCTIONCYCLE_FOURTH = 8,
	BUILDINGPRODUCTIONCYCLE_ALL = 15,
};

const char *EnumToString( const EBuildingProductionCycle value );
const EBuildingProductionCycle StringToEnum_EBuildingProductionCycle( const char* value );

template <>
struct KnownEnum< EBuildingProductionCycle >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EBuildingProductionCycle value ) { return EnumToString( value ); }
	static const EBuildingProductionCycle ToEnum( const char* value ) { return StringToEnum_EBuildingProductionCycle( value ); }
	static const EBuildingProductionCycle ToEnum( const string& value ) { return StringToEnum_EBuildingProductionCycle( value.c_str() ); }
	static const int SizeOf() { return 5; }
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

enum EGameType
{
	GAMETYPE_PVP = 1,
	GAMETYPE_CTE = 2,
	GAMETYPE_PVE = 4,
	GAMETYPE_MIDONLY = 8,
	GAMETYPE_ALL = 15,
};

const char *EnumToString( const EGameType value );
const EGameType StringToEnum_EGameType( const char* value );

template <>
struct KnownEnum< EGameType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EGameType value ) { return EnumToString( value ); }
	static const EGameType ToEnum( const char* value ) { return StringToEnum_EGameType( value ); }
	static const EGameType ToEnum( const string& value ) { return StringToEnum_EGameType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EGender
{
	GENDER_MALE = 0,
	GENDER_FEMALE = 1,
};

const char *EnumToString( const EGender value );
const EGender StringToEnum_EGender( const char* value );

template <>
struct KnownEnum< EGender >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EGender value ) { return EnumToString( value ); }
	static const EGender ToEnum( const char* value ) { return StringToEnum_EGender( value ); }
	static const EGender ToEnum( const string& value ) { return StringToEnum_EGender( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EHeroRaces
{
	HERORACES_ZERO = 0,
	HERORACES_A = 1,
	HERORACES_B = 2,
};

const char *EnumToString( const EHeroRaces value );
const EHeroRaces StringToEnum_EHeroRaces( const char* value );

template <>
struct KnownEnum< EHeroRaces >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EHeroRaces value ) { return EnumToString( value ); }
	static const EHeroRaces ToEnum( const char* value ) { return StringToEnum_EHeroRaces( value ); }
	static const EHeroRaces ToEnum( const string& value ) { return StringToEnum_EHeroRaces( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EMapType
{
	MAPTYPE_NONE = 0,
	MAPTYPE_PVP = 1,
	MAPTYPE_CTE = 2,
	MAPTYPE_TRAINING = 3,
	MAPTYPE_TUTORIAL = 4,
	MAPTYPE_SERIES = 5,
	MAPTYPE_COOPERATIVE = 6,
};

const char *EnumToString( const EMapType value );
const EMapType StringToEnum_EMapType( const char* value );

template <>
struct KnownEnum< EMapType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EMapType value ) { return EnumToString( value ); }
	static const EMapType ToEnum( const char* value ) { return StringToEnum_EMapType( value ); }
	static const EMapType ToEnum( const string& value ) { return StringToEnum_EMapType( value.c_str() ); }
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

enum ESessionType
{
	SESSIONTYPE_USUALBATTLE = 1,
	SESSIONTYPE_GUILDBATTLE = 2,
	SESSIONTYPE_ALL = 3,
};

const char *EnumToString( const ESessionType value );
const ESessionType StringToEnum_ESessionType( const char* value );

template <>
struct KnownEnum< ESessionType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ESessionType value ) { return EnumToString( value ); }
	static const ESessionType ToEnum( const char* value ) { return StringToEnum_ESessionType( value ); }
	static const ESessionType ToEnum( const string& value ) { return StringToEnum_ESessionType( value.c_str() ); }
	static const int SizeOf() { return 3; }
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

enum EStatBufToggle
{
	STATBUFTOGGLE_ATGAMESTART = 1,
	STATBUFTOGGLE_BY36LEVEL = 2,
};

const char *EnumToString( const EStatBufToggle value );
const EStatBufToggle StringToEnum_EStatBufToggle( const char* value );

template <>
struct KnownEnum< EStatBufToggle >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EStatBufToggle value ) { return EnumToString( value ); }
	static const EStatBufToggle ToEnum( const char* value ) { return StringToEnum_EStatBufToggle( value ); }
	static const EStatBufToggle ToEnum( const string& value ) { return StringToEnum_EStatBufToggle( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ESweepStage
{
	SWEEPSTAGE_LOWERLIMIT = 0,
	SWEEPSTAGE_UPPERLIMIT = 1,
	SWEEPSTAGE_WIDENEDLIMITS = 2,
};

const char *EnumToString( const ESweepStage value );
const ESweepStage StringToEnum_ESweepStage( const char* value );

template <>
struct KnownEnum< ESweepStage >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ESweepStage value ) { return EnumToString( value ); }
	static const ESweepStage ToEnum( const char* value ) { return StringToEnum_ESweepStage( value ); }
	static const ESweepStage ToEnum( const string& value ) { return StringToEnum_ESweepStage( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETalentRarity
{
	TALENTRARITY_CLASS = 0,
	TALENTRARITY_ORDINARY = 1,
	TALENTRARITY_GOOD = 2,
	TALENTRARITY_EXCELLENT = 3,
	TALENTRARITY_MAGNIFICENT = 4,
	TALENTRARITY_EXCLUSIVE = 5,
	TALENTRARITY_OUTSTANDING = 6,
};

const char *EnumToString( const ETalentRarity value );
const ETalentRarity StringToEnum_ETalentRarity( const char* value );

template <>
struct KnownEnum< ETalentRarity >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ETalentRarity value ) { return EnumToString( value ); }
	static const ETalentRarity ToEnum( const char* value ) { return StringToEnum_ETalentRarity( value ); }
	static const ETalentRarity ToEnum( const string& value ) { return StringToEnum_ETalentRarity( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum ETalentRollGroup
{
	TALENTROLLGROUP_PVP = 1,
	TALENTROLLGROUP_TRAINING = 2,
	TALENTROLLGROUP_CTE = 4,
	TALENTROLLGROUP_PVE = 8,
	TALENTROLLGROUP_CASTLE = 16,
	TALENTROLLGROUP_MIDONLY = 32,
	TALENTROLLGROUP_ALL = 63,
};

const char *EnumToString( const ETalentRollGroup value );
const ETalentRollGroup StringToEnum_ETalentRollGroup( const char* value );

template <>
struct KnownEnum< ETalentRollGroup >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ETalentRollGroup value ) { return EnumToString( value ); }
	static const ETalentRollGroup ToEnum( const char* value ) { return StringToEnum_ETalentRollGroup( value ); }
	static const ETalentRollGroup ToEnum( const string& value ) { return StringToEnum_ETalentRollGroup( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum HeroClassEnum
{
	HEROCLASSENUM_NONE = 0,
	HEROCLASSENUM_PROTECTOR = 1,
	HEROCLASSENUM_VANGUARD = 2,
	HEROCLASSENUM_EXECUTIONER = 4,
	HEROCLASSENUM_FIGHTER = 8,
	HEROCLASSENUM_SUPPORT = 16,
};

const char *EnumToString( const HeroClassEnum value );
const HeroClassEnum StringToEnum_HeroClassEnum( const char* value );

template <>
struct KnownEnum< HeroClassEnum >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const HeroClassEnum value ) { return EnumToString( value ); }
	static const HeroClassEnum ToEnum( const char* value ) { return StringToEnum_HeroClassEnum( value ); }
	static const HeroClassEnum ToEnum( const string& value ) { return StringToEnum_HeroClassEnum( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum MMakingHeroClassEnum
{
	MMAKINGHEROCLASSENUM_NONE = 0,
	MMAKINGHEROCLASSENUM_PROTECTOR = 1,
	MMAKINGHEROCLASSENUM_VANGUARD = 2,
	MMAKINGHEROCLASSENUM_EXECUTIONER = 3,
	MMAKINGHEROCLASSENUM_FIGHTER = 4,
	MMAKINGHEROCLASSENUM_SUPPORT = 5,
	MMAKINGHEROCLASSENUM_JUNGLER = 6,
};

const char *EnumToString( const MMakingHeroClassEnum value );
const MMakingHeroClassEnum StringToEnum_MMakingHeroClassEnum( const char* value );

template <>
struct KnownEnum< MMakingHeroClassEnum >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const MMakingHeroClassEnum value ) { return EnumToString( value ); }
	static const MMakingHeroClassEnum ToEnum( const char* value ) { return StringToEnum_MMakingHeroClassEnum( value ); }
	static const MMakingHeroClassEnum ToEnum( const string& value ) { return StringToEnum_MMakingHeroClassEnum( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum ResourceRollConstraint
{
	RESOURCEROLLCONSTRAINT_SILVER = 0,
	RESOURCEROLLCONSTRAINT_RESOURCE1 = 1,
	RESOURCEROLLCONSTRAINT_RESOURCE2 = 2,
	RESOURCEROLLCONSTRAINT_RESOURCE3 = 3,
	RESOURCEROLLCONSTRAINT_PEARL = 4,
	RESOURCEROLLCONSTRAINT_REDPEARL = 5,
	RESOURCEROLLCONSTRAINT_SHARD = 6,
	RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY = 7,
};

const char *EnumToString( const ResourceRollConstraint value );
const ResourceRollConstraint StringToEnum_ResourceRollConstraint( const char* value );

template <>
struct KnownEnum< ResourceRollConstraint >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const ResourceRollConstraint value ) { return EnumToString( value ); }
	static const ResourceRollConstraint ToEnum( const char* value ) { return StringToEnum_ResourceRollConstraint( value ); }
	static const ResourceRollConstraint ToEnum( const string& value ) { return StringToEnum_ResourceRollConstraint( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum TalentUpgradeEntityType
{
	TALENTUPGRADEENTITYTYPE_RUNE = 0,
	TALENTUPGRADEENTITYTYPE_CATALYST = 1,
};

const char *EnumToString( const TalentUpgradeEntityType value );
const TalentUpgradeEntityType StringToEnum_TalentUpgradeEntityType( const char* value );

template <>
struct KnownEnum< TalentUpgradeEntityType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const TalentUpgradeEntityType value ) { return EnumToString( value ); }
	static const TalentUpgradeEntityType ToEnum( const char* value ) { return StringToEnum_TalentUpgradeEntityType( value ); }
	static const TalentUpgradeEntityType ToEnum( const string& value ) { return StringToEnum_TalentUpgradeEntityType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ZZRewards
{
	ZZREWARDS_VICTORY = 0,
};

const char *EnumToString( const ZZRewards value );
const ZZRewards StringToEnum_ZZRewards( const char* value );

template <>
struct KnownEnum< ZZRewards >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const ZZRewards value ) { return EnumToString( value ); }
	static const ZZRewards ToEnum( const char* value ) { return StringToEnum_ZZRewards( value ); }
	static const ZZRewards ToEnum( const string& value ) { return StringToEnum_ZZRewards( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

struct BaseModifierFromQuantity
{
public:
	float quantity;
	float percent;

	BaseModifierFromQuantity();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct BuyServiceCost
{
public:
	int goldCost;

	BuyServiceCost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CountryFlag
{
public:
	string countryCode;

	CountryFlag();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EstimFunctionWeights
{
public:
	float ladiesNumber;
	float genderPairs;
	float heroes;
	float ratingSpan;
	float ratingPatternDelta;
	float ratingTeamAvgDelta;
	float forceSpan;
	float heroClassesDifference;
	float heroClassesOptimum;

	EstimFunctionWeights();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FullPartyRatingModifier
{
public:
	int minRating;
	float ratingBonus;

	FullPartyRatingModifier();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GameProps
{
public:
	vector< Ptr< AdvMapDescription > > maps;
	ESessionType sessionType;

	GameProps();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GuildLevel
{
public:
	long requiredExp;
	CTextRef title;
	CTextRef tooltip;
	vector< Ptr< GuildBonus > > Bonuses;

	GuildLevel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LerpDataItem
{
public:
	float x;
	float y;

	LerpDataItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingHeroClass
{
public:
	float minEfficiency;
	float maxEfficiency;

	MMakingHeroClass();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingLocationPingSettings
{
public:
	int nicePingThreshold;
	float pingScaleMinFactor;
	int worstPingWaitTimePenalty;
	float goodEnoughPingFactor;
	int ratingThreshold;

	MMakingLocationPingSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingLoseStreakCorrection
{
public:
	int minStreak;
	float forcePenalty;
	float ratingPenalty;
	int firstCaseThreshold;
	float firstCasePenalty;
	int secondCaseThreshold;
	float secondCasePenalty;
	int thirdCaseThreshold;
	float thirdCasePenalty;

	MMakingLoseStreakCorrection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingRank
{
public:
	float lowRating;
	bool mergeWithNextRank;
	int mergeRanksCount;
	string debugName;
	bool useForceMM;
	bool usePlayerRatingMM;

	MMakingRank();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingScale
{
public:
	int low;
	int high;
	int step;
	vector< LerpDataItem > diffLow;
	vector< LerpDataItem > diffHigh;

	MMakingScale();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MMakingWaitVsProbability
{
public:
	float startingWaitTime;
	float endingWaitTime;
	int startingProbabilityWeight;
	int endingProbabilityWeight;

	MMakingWaitVsProbability();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PointsToContainers
{
public:
	int specialPoints;
	int containers;

	PointsToContainers();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Rank
{
public:
	int rating;

	Rank();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RatingModifier
{
public:
	int minValue;
	int maxValue;
	float winModifier;
	float looseModifier;

	RatingModifier();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RecessionData
{
public:
	vector< float > recessionTable;
	bool isWaitingTimePremium;

	RecessionData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RecessionFullPartyTableForForceMM
{
public:
	vector< float > recessionTable;
	vector< float > recessionPremium;

	RecessionFullPartyTableForForceMM();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RecessionTableForPlayerRatingMM
{
public:
	vector< RecessionData > recessionTable;
	float recessionSideDiff;
	vector< float > recessionPremiumTable;
	float recessionPremiumTimeThreshold;
	int recessionMaxPlayerRating;
	int recessionMinPlayerRating;

	RecessionTableForPlayerRatingMM();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RollItemProbability
{
public:
	float probability;
	Ptr< RollItem > item;

	RollItemProbability();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RollLevelInfo
{
public:
	int level;
	int count;
	int deviation;

	RollLevelInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SingleRollSettings
{
public:
	Ptr< RollContainer > rollContainer;
	ETalentRollGroup allowedRollGroups;
	int version;

	SingleRollSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ValueProps
{
public:
	float additiveValue;
	float multiplicativeValue;

	ValueProps();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TalentUpgradeProbability
{
public:
	float probability;
	int points;

	TalentUpgradeProbability();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatBonus
{
public:
	EStat statType;
	ValueProps modifiers;

	StatBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Spell : public DbResource
{
	DBRESOURCE_METHODS( Spell );
public:
	enum { typeId = 0x2C5C0B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Spell::typeId; }

	Spell();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Spell& operator = ( const Spell &_spell ) { Assign( _spell ); return *this; }
	Spell( const Spell &_spell ) { Assign( _spell ); }
	virtual void Assign( const Spell &_spell );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Spell * pOther = dynamic_cast< const Spell * > ( _pResource );
		if ( pOther ) Spell::Assign( *pOther );
	}
};

struct GuildBonus : public DbResource
{
public:
	CTextRef tooltip;

	GuildBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildBonus& operator = ( const GuildBonus &_guildBonus ) { Assign( _guildBonus ); return *this; }
	GuildBonus( const GuildBonus &_guildBonus ) { Assign( _guildBonus ); }
	virtual void Assign( const GuildBonus &_guildBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildBonus * pOther = dynamic_cast< const GuildBonus * > ( _pResource );
		if ( pOther ) GuildBonus::Assign( *pOther );
	}
};

struct AdvMapDescription : public DbResource
{
	DBRESOURCE_METHODS( AdvMapDescription );
public:
	EMapType mapType;
	Ptr< MapMMakingSettings > matchmakingSettings;
	int teamSize;
	int minTeamSize;
	int maxUncompleteTeamSize;
	bool productionMode;
	Ptr< AdvMapSettings > mapSettings;
	Ptr< ModeRollSettings > rollSettings;
	Ptr< ModeRollSettings > guardRollSettings;
	int minimalGuildFightTeam;
	Ptr< GameSvcSettings > gameSvcSettings;
	int playSameTeamTimeOut;

	AdvMapDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapDescription& operator = ( const AdvMapDescription &_advMapDescription ) { Assign( _advMapDescription ); return *this; }
	AdvMapDescription( const AdvMapDescription &_advMapDescription ) { Assign( _advMapDescription ); }
	virtual void Assign( const AdvMapDescription &_advMapDescription );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapDescription * pOther = dynamic_cast< const AdvMapDescription * > ( _pResource );
		if ( pOther ) AdvMapDescription::Assign( *pOther );
	}
};

struct AdvMapSettings : public DbResource
{
	DBRESOURCE_METHODS( AdvMapSettings );
public:
	bool fullPartyOnly;

	AdvMapSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapSettings& operator = ( const AdvMapSettings &_advMapSettings ) { Assign( _advMapSettings ); return *this; }
	AdvMapSettings( const AdvMapSettings &_advMapSettings ) { Assign( _advMapSettings ); }
	virtual void Assign( const AdvMapSettings &_advMapSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapSettings * pOther = dynamic_cast< const AdvMapSettings * > ( _pResource );
		if ( pOther ) AdvMapSettings::Assign( *pOther );
	}
};

struct AILogicParameters : public DbResource
{
	DBRESOURCE_METHODS( AILogicParameters );
public:
	vector< int > talentVendorCostByRarity;
	Ptr< HeroRanks > heroRanks;

	AILogicParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AILogicParameters& operator = ( const AILogicParameters &_aILogicParameters ) { Assign( _aILogicParameters ); return *this; }
	AILogicParameters( const AILogicParameters &_aILogicParameters ) { Assign( _aILogicParameters ); }
	virtual void Assign( const AILogicParameters &_aILogicParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AILogicParameters * pOther = dynamic_cast< const AILogicParameters * > ( _pResource );
		if ( pOther ) AILogicParameters::Assign( *pOther );
	}
};

struct GameObject : public DbResource
{
	DBRESOURCE_METHODS( GameObject );
public:
	enum { typeId = 0x9E5573C6 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GameObject::typeId; }

	GameObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GameObject& operator = ( const GameObject &_gameObject ) { Assign( _gameObject ); return *this; }
	GameObject( const GameObject &_gameObject ) { Assign( _gameObject ); }
	virtual void Assign( const GameObject &_gameObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GameObject * pOther = dynamic_cast< const GameObject * > ( _pResource );
		if ( pOther ) GameObject::Assign( *pOther );
	}
};

struct BuyServicesContainer : public DbResource
{
	DBRESOURCE_METHODS( BuyServicesContainer );
public:
	enum { typeId = 0x0F994BC9 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BuyServicesContainer::typeId; }
	vector< BuyServiceCost > services;
	vector< BuyServiceCost > buffs;
	vector< BuyServiceCost > rewards;

	BuyServicesContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BuyServicesContainer& operator = ( const BuyServicesContainer &_buyServicesContainer ) { Assign( _buyServicesContainer ); return *this; }
	BuyServicesContainer( const BuyServicesContainer &_buyServicesContainer ) { Assign( _buyServicesContainer ); }
	virtual void Assign( const BuyServicesContainer &_buyServicesContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BuyServicesContainer * pOther = dynamic_cast< const BuyServicesContainer * > ( _pResource );
		if ( pOther ) BuyServicesContainer::Assign( *pOther );
	}
};

struct GuildShopItemBonus : public DbResource
{
public:
	CTextRef propertyTooltip;

	GuildShopItemBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildShopItemBonus& operator = ( const GuildShopItemBonus &_guildShopItemBonus ) { Assign( _guildShopItemBonus ); return *this; }
	GuildShopItemBonus( const GuildShopItemBonus &_guildShopItemBonus ) { Assign( _guildShopItemBonus ); }
	virtual void Assign( const GuildShopItemBonus &_guildShopItemBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildShopItemBonus * pOther = dynamic_cast< const GuildShopItemBonus * > ( _pResource );
		if ( pOther ) GuildShopItemBonus::Assign( *pOther );
	}
};

struct RollItem : public DbResource
{
public:

	RollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RollItem& operator = ( const RollItem &_rollItem ) { Assign( _rollItem ); return *this; }
	RollItem( const RollItem &_rollItem ) { Assign( _rollItem ); }
	virtual void Assign( const RollItem &_rollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RollItem * pOther = dynamic_cast< const RollItem * > ( _pResource );
		if ( pOther ) RollItem::Assign( *pOther );
	}
};

struct ClanWarsSettings : public DbResource
{
	DBRESOURCE_METHODS( ClanWarsSettings );
public:
	float basePoints;
	vector< BaseModifierFromQuantity > partyClanMembersModifier;
	vector< BaseModifierFromQuantity > foeCountsModifier;
	vector< float > defeatedFoeRankModifier;
	float clanPoints;
	bool normalizeBySessionScores;
	float premiumAccountModifier;

	ClanWarsSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ClanWarsSettings& operator = ( const ClanWarsSettings &_clanWarsSettings ) { Assign( _clanWarsSettings ); return *this; }
	ClanWarsSettings( const ClanWarsSettings &_clanWarsSettings ) { Assign( _clanWarsSettings ); }
	virtual void Assign( const ClanWarsSettings &_clanWarsSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ClanWarsSettings * pOther = dynamic_cast< const ClanWarsSettings * > ( _pResource );
		if ( pOther ) ClanWarsSettings::Assign( *pOther );
	}
};

struct ContainersBySpecialPoints : public DbResource
{
	DBRESOURCE_METHODS( ContainersBySpecialPoints );
public:
	vector< PointsToContainers > items;

	ContainersBySpecialPoints();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ContainersBySpecialPoints& operator = ( const ContainersBySpecialPoints &_containersBySpecialPoints ) { Assign( _containersBySpecialPoints ); return *this; }
	ContainersBySpecialPoints( const ContainersBySpecialPoints &_containersBySpecialPoints ) { Assign( _containersBySpecialPoints ); }
	virtual void Assign( const ContainersBySpecialPoints &_containersBySpecialPoints );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ContainersBySpecialPoints * pOther = dynamic_cast< const ContainersBySpecialPoints * > ( _pResource );
		if ( pOther ) ContainersBySpecialPoints::Assign( *pOther );
	}
};

struct SingleStateObject : public GameObject
{
	DBRESOURCE_METHODS( SingleStateObject );
public:
	enum { typeId = 0x0F641B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SingleStateObject::typeId; }

	SingleStateObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SingleStateObject& operator = ( const SingleStateObject &_singleStateObject ) { Assign( _singleStateObject ); return *this; }
	SingleStateObject( const SingleStateObject &_singleStateObject ) { Assign( _singleStateObject ); }
	virtual void Assign( const SingleStateObject &_singleStateObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SingleStateObject * pOther = dynamic_cast< const SingleStateObject * > ( _pResource );
		if ( pOther ) SingleStateObject::Assign( *pOther );
	}
};

struct CustomFlag : public DbResource
{
	DBRESOURCE_METHODS( CustomFlag );
public:

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

struct DefaultFormulas : public DbResource
{
	DBRESOURCE_METHODS( DefaultFormulas );
public:
	enum { typeId = 0x0F664BC9 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DefaultFormulas::typeId; }

	DefaultFormulas();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DefaultFormulas& operator = ( const DefaultFormulas &_defaultFormulas ) { Assign( _defaultFormulas ); return *this; }
	DefaultFormulas( const DefaultFormulas &_defaultFormulas ) { Assign( _defaultFormulas ); }
	virtual void Assign( const DefaultFormulas &_defaultFormulas );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DefaultFormulas * pOther = dynamic_cast< const DefaultFormulas * > ( _pResource );
		if ( pOther ) DefaultFormulas::Assign( *pOther );
	}
};

struct FlagRollItem : public RollItem
{
	DBRESOURCE_METHODS( FlagRollItem );
public:
	Ptr< CustomFlag > flag;

	FlagRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FlagRollItem& operator = ( const FlagRollItem &_flagRollItem ) { Assign( _flagRollItem ); return *this; }
	FlagRollItem( const FlagRollItem &_flagRollItem ) { Assign( _flagRollItem ); }
	virtual void Assign( const FlagRollItem &_flagRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FlagRollItem * pOther = dynamic_cast< const FlagRollItem * > ( _pResource );
		if ( pOther ) FlagRollItem::Assign( *pOther );
	}
};

struct Unit : public SingleStateObject
{
	DBRESOURCE_METHODS( Unit );
public:
	enum { typeId = 0x9E678C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Unit::typeId; }

	Unit();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Unit& operator = ( const Unit &_unit ) { Assign( _unit ); return *this; }
	Unit( const Unit &_unit ) { Assign( _unit ); }
	virtual void Assign( const Unit &_unit );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Unit * pOther = dynamic_cast< const Unit * > ( _pResource );
		if ( pOther ) Unit::Assign( *pOther );
	}
};

struct GameSvcSettings : public DbResource
{
	DBRESOURCE_METHODS( GameSvcSettings );
public:
	int afkMessageTimer;
	int afkDisconnectTimer;
	float timeScale;

	GameSvcSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GameSvcSettings& operator = ( const GameSvcSettings &_gameSvcSettings ) { Assign( _gameSvcSettings ); return *this; }
	GameSvcSettings( const GameSvcSettings &_gameSvcSettings ) { Assign( _gameSvcSettings ); }
	virtual void Assign( const GameSvcSettings &_gameSvcSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GameSvcSettings * pOther = dynamic_cast< const GameSvcSettings * > ( _pResource );
		if ( pOther ) GameSvcSettings::Assign( *pOther );
	}
};

struct GlyphsDB : public DbResource
{
	DBRESOURCE_METHODS( GlyphsDB );
public:

	GlyphsDB();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GlyphsDB& operator = ( const GlyphsDB &_glyphsDB ) { Assign( _glyphsDB ); return *this; }
	GlyphsDB( const GlyphsDB &_glyphsDB ) { Assign( _glyphsDB ); }
	virtual void Assign( const GlyphsDB &_glyphsDB );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GlyphsDB * pOther = dynamic_cast< const GlyphsDB * > ( _pResource );
		if ( pOther ) GlyphsDB::Assign( *pOther );
	}
};

struct GoldRollItem : public RollItem
{
	DBRESOURCE_METHODS( GoldRollItem );
public:
	int count;

	GoldRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GoldRollItem& operator = ( const GoldRollItem &_goldRollItem ) { Assign( _goldRollItem ); return *this; }
	GoldRollItem( const GoldRollItem &_goldRollItem ) { Assign( _goldRollItem ); }
	virtual void Assign( const GoldRollItem &_goldRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GoldRollItem * pOther = dynamic_cast< const GoldRollItem * > ( _pResource );
		if ( pOther ) GoldRollItem::Assign( *pOther );
	}
};

struct AdditionHeroExpBonus : public GuildBonus
{
	DBRESOURCE_METHODS( AdditionHeroExpBonus );
public:
	int percent;

	AdditionHeroExpBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdditionHeroExpBonus& operator = ( const AdditionHeroExpBonus &_additionHeroExpBonus ) { Assign( _additionHeroExpBonus ); return *this; }
	AdditionHeroExpBonus( const AdditionHeroExpBonus &_additionHeroExpBonus ) { Assign( _additionHeroExpBonus ); }
	virtual void Assign( const AdditionHeroExpBonus &_additionHeroExpBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdditionHeroExpBonus * pOther = dynamic_cast< const AdditionHeroExpBonus * > ( _pResource );
		if ( pOther ) AdditionHeroExpBonus::Assign( *pOther );
	}
};

struct GuildBuff : public DbResource
{
	DBRESOURCE_METHODS( GuildBuff );
public:
	string persistentId;
	vector< Ptr< GuildBuff > > doNotWorkWith;
	bool isGuildBonus;
	int priority;
	int duration;
	int numGames;
	CTextRef propertyTooltip;
	vector< Ptr< GuildShopItemBonus > > bonuses;

	GuildBuff();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildBuff& operator = ( const GuildBuff &_guildBuff ) { Assign( _guildBuff ); return *this; }
	GuildBuff( const GuildBuff &_guildBuff ) { Assign( _guildBuff ); }
	virtual void Assign( const GuildBuff &_guildBuff );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildBuff * pOther = dynamic_cast< const GuildBuff * > ( _pResource );
		if ( pOther ) GuildBuff::Assign( *pOther );
	}
};

struct GuildBuffsCollection : public DbResource
{
	DBRESOURCE_METHODS( GuildBuffsCollection );
public:
	vector< Ptr< GuildBuff > > buffs;

	GuildBuffsCollection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildBuffsCollection& operator = ( const GuildBuffsCollection &_guildBuffsCollection ) { Assign( _guildBuffsCollection ); return *this; }
	GuildBuffsCollection( const GuildBuffsCollection &_guildBuffsCollection ) { Assign( _guildBuffsCollection ); }
	virtual void Assign( const GuildBuffsCollection &_guildBuffsCollection );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildBuffsCollection * pOther = dynamic_cast< const GuildBuffsCollection * > ( _pResource );
		if ( pOther ) GuildBuffsCollection::Assign( *pOther );
	}
};

struct GuildLevels : public DbResource
{
	DBRESOURCE_METHODS( GuildLevels );
public:
	int requiredExpMultiplier;
	vector< GuildLevel > levels;

	GuildLevels();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildLevels& operator = ( const GuildLevels &_guildLevels ) { Assign( _guildLevels ); return *this; }
	GuildLevels( const GuildLevels &_guildLevels ) { Assign( _guildLevels ); }
	virtual void Assign( const GuildLevels &_guildLevels );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildLevels * pOther = dynamic_cast< const GuildLevels * > ( _pResource );
		if ( pOther ) GuildLevels::Assign( *pOther );
	}
};

struct GuildResourceBonus : public GuildBonus
{
	DBRESOURCE_METHODS( GuildResourceBonus );
public:
	int resource;

	GuildResourceBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildResourceBonus& operator = ( const GuildResourceBonus &_guildResourceBonus ) { Assign( _guildResourceBonus ); return *this; }
	GuildResourceBonus( const GuildResourceBonus &_guildResourceBonus ) { Assign( _guildResourceBonus ); }
	virtual void Assign( const GuildResourceBonus &_guildResourceBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildResourceBonus * pOther = dynamic_cast< const GuildResourceBonus * > ( _pResource );
		if ( pOther ) GuildResourceBonus::Assign( *pOther );
	}
};

struct HeroBonusBase : public GuildShopItemBonus
{
	DBRESOURCE_METHODS( HeroBonusBase );
public:
	vector< Ptr< Hero > > heroes;

	HeroBonusBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroBonusBase& operator = ( const HeroBonusBase &_heroBonusBase ) { Assign( _heroBonusBase ); return *this; }
	HeroBonusBase( const HeroBonusBase &_heroBonusBase ) { Assign( _heroBonusBase ); }
	virtual void Assign( const HeroBonusBase &_heroBonusBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroBonusBase * pOther = dynamic_cast< const HeroBonusBase * > ( _pResource );
		if ( pOther ) HeroBonusBase::Assign( *pOther );
	}
};

struct SessionBonus : public HeroBonusBase
{
	DBRESOURCE_METHODS( SessionBonus );
public:
	GameProps gameSettings;

	SessionBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionBonus& operator = ( const SessionBonus &_sessionBonus ) { Assign( _sessionBonus ); return *this; }
	SessionBonus( const SessionBonus &_sessionBonus ) { Assign( _sessionBonus ); }
	virtual void Assign( const SessionBonus &_sessionBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionBonus * pOther = dynamic_cast< const SessionBonus * > ( _pResource );
		if ( pOther ) SessionBonus::Assign( *pOther );
	}
};

struct Creature : public Unit
{
	DBRESOURCE_METHODS( Creature );
public:
	enum { typeId = 0x9E722340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Creature::typeId; }

	Creature();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Creature& operator = ( const Creature &_creature ) { Assign( _creature ); return *this; }
	Creature( const Creature &_creature ) { Assign( _creature ); }
	virtual void Assign( const Creature &_creature );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Creature * pOther = dynamic_cast< const Creature * > ( _pResource );
		if ( pOther ) Creature::Assign( *pOther );
	}
};

struct SessionValueBonus : public SessionBonus
{
	DBRESOURCE_METHODS( SessionValueBonus );
public:
	ValueProps modifiers;

	SessionValueBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionValueBonus& operator = ( const SessionValueBonus &_sessionValueBonus ) { Assign( _sessionValueBonus ); return *this; }
	SessionValueBonus( const SessionValueBonus &_sessionValueBonus ) { Assign( _sessionValueBonus ); }
	virtual void Assign( const SessionValueBonus &_sessionValueBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionValueBonus * pOther = dynamic_cast< const SessionValueBonus * > ( _pResource );
		if ( pOther ) SessionValueBonus::Assign( *pOther );
	}
};

struct HeroEnergyBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( HeroEnergyBonus );
public:
	int fakeFieldForCastle;

	HeroEnergyBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroEnergyBonus& operator = ( const HeroEnergyBonus &_heroEnergyBonus ) { Assign( _heroEnergyBonus ); return *this; }
	HeroEnergyBonus( const HeroEnergyBonus &_heroEnergyBonus ) { Assign( _heroEnergyBonus ); }
	virtual void Assign( const HeroEnergyBonus &_heroEnergyBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroEnergyBonus * pOther = dynamic_cast< const HeroEnergyBonus * > ( _pResource );
		if ( pOther ) HeroEnergyBonus::Assign( *pOther );
	}
};

struct HeroesDB : public DbResource
{
	DBRESOURCE_METHODS( HeroesDB );
public:
	vector< Ptr< Hero > > heroes;

	HeroesDB();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroesDB& operator = ( const HeroesDB &_heroesDB ) { Assign( _heroesDB ); return *this; }
	HeroesDB( const HeroesDB &_heroesDB ) { Assign( _heroesDB ); }
	virtual void Assign( const HeroesDB &_heroesDB );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroesDB * pOther = dynamic_cast< const HeroesDB * > ( _pResource );
		if ( pOther ) HeroesDB::Assign( *pOther );
	}
};

struct HeroesLevelUps : public DbResource
{
	DBRESOURCE_METHODS( HeroesLevelUps );
public:

	HeroesLevelUps();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroesLevelUps& operator = ( const HeroesLevelUps &_heroesLevelUps ) { Assign( _heroesLevelUps ); return *this; }
	HeroesLevelUps( const HeroesLevelUps &_heroesLevelUps ) { Assign( _heroesLevelUps ); }
	virtual void Assign( const HeroesLevelUps &_heroesLevelUps );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroesLevelUps * pOther = dynamic_cast< const HeroesLevelUps * > ( _pResource );
		if ( pOther ) HeroesLevelUps::Assign( *pOther );
	}
};

struct HeroExperienceBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( HeroExperienceBonus );
public:
	int fakeFieldForCastle;

	HeroExperienceBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroExperienceBonus& operator = ( const HeroExperienceBonus &_heroExperienceBonus ) { Assign( _heroExperienceBonus ); return *this; }
	HeroExperienceBonus( const HeroExperienceBonus &_heroExperienceBonus ) { Assign( _heroExperienceBonus ); }
	virtual void Assign( const HeroExperienceBonus &_heroExperienceBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroExperienceBonus * pOther = dynamic_cast< const HeroExperienceBonus * > ( _pResource );
		if ( pOther ) HeroExperienceBonus::Assign( *pOther );
	}
};

struct HeroRanks : public DbResource
{
	DBRESOURCE_METHODS( HeroRanks );
public:
	int highLevelsMMRating;
	vector< Rank > ranks;

	HeroRanks();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroRanks& operator = ( const HeroRanks &_heroRanks ) { Assign( _heroRanks ); return *this; }
	HeroRanks( const HeroRanks &_heroRanks ) { Assign( _heroRanks ); }
	virtual void Assign( const HeroRanks &_heroRanks );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroRanks * pOther = dynamic_cast< const HeroRanks * > ( _pResource );
		if ( pOther ) HeroRanks::Assign( *pOther );
	}
};

struct HeroRollItem : public RollItem
{
	DBRESOURCE_METHODS( HeroRollItem );
public:
	Ptr< Hero > hero;

	HeroRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroRollItem& operator = ( const HeroRollItem &_heroRollItem ) { Assign( _heroRollItem ); return *this; }
	HeroRollItem( const HeroRollItem &_heroRollItem ) { Assign( _heroRollItem ); }
	virtual void Assign( const HeroRollItem &_heroRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroRollItem * pOther = dynamic_cast< const HeroRollItem * > ( _pResource );
		if ( pOther ) HeroRollItem::Assign( *pOther );
	}
};

struct HeroSkin : public DbResource
{
	DBRESOURCE_METHODS( HeroSkin );
public:
	enum { typeId = 0xB1988440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HeroSkin::typeId; }
	bool legal;
	string persistentId;
	EGender gender;
	EHeroRaces heroRace;
	bool botRoll;

	HeroSkin();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroSkin& operator = ( const HeroSkin &_heroSkin ) { Assign( _heroSkin ); return *this; }
	HeroSkin( const HeroSkin &_heroSkin ) { Assign( _heroSkin ); }
	virtual void Assign( const HeroSkin &_heroSkin );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroSkin * pOther = dynamic_cast< const HeroSkin * > ( _pResource );
		if ( pOther ) HeroSkin::Assign( *pOther );
	}
};

struct ImpulsiveBuffsContainer : public DbResource
{
	DBRESOURCE_METHODS( ImpulsiveBuffsContainer );
public:
	enum { typeId = 0x0F664BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ImpulsiveBuffsContainer::typeId; }

	ImpulsiveBuffsContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ImpulsiveBuffsContainer& operator = ( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer ) { Assign( _impulsiveBuffsContainer ); return *this; }
	ImpulsiveBuffsContainer( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer ) { Assign( _impulsiveBuffsContainer ); }
	virtual void Assign( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ImpulsiveBuffsContainer * pOther = dynamic_cast< const ImpulsiveBuffsContainer * > ( _pResource );
		if ( pOther ) ImpulsiveBuffsContainer::Assign( *pOther );
	}
};

struct MapList : public DbResource
{
	DBRESOURCE_METHODS( MapList );
public:
	vector< Ptr< AdvMapDescription > > maps;

	MapList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MapList& operator = ( const MapList &_mapList ) { Assign( _mapList ); return *this; }
	MapList( const MapList &_mapList ) { Assign( _mapList ); }
	virtual void Assign( const MapList &_mapList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MapList * pOther = dynamic_cast< const MapList * > ( _pResource );
		if ( pOther ) MapList::Assign( *pOther );
	}
};

struct MapMMakingSettings : public DbResource
{
	DBRESOURCE_METHODS( MapMMakingSettings );
public:
	bool mock;
	bool isTournamentMap;
	EstimFunctionWeights estimFunctionWeights;
	int normalBasePointsRepeatFactor;
	int noobBasePointsRepeatFactor;
	float ratingDiffGrowTime;
	int fullSweepSubsetLimit;
	int fullSweepSubsetLimitPve;
	int estimFunDecreaseTimeBegin;
	int estimFunDecreaseTimeEnd;
	float estimFunDecreaseFactor;
	float estimFunManoeuvresDecreaseFactor;
	int identicalHeroesSampleLimit;
	int identicalGuardHeroesSampleLimit;
	int identicalNoobHeroesSampleLimit;
	int lowWaitTimeThreshold;
	float lowWaitTimeFactor;
	int manoeuvresMinPopulation;
	int manoeuvresMaxPopulation;
	int guardManoeuvresMinPopulation;
	int guardManoeuvresMaxPopulation;
	float manoeuvresWaitThreshold;
	int manoeuvresFullSweepSubset;
	int trainingFemaleBotsCount;
	int necessaryLadiesCount;
	vector< float > partySkillCompensation;
	MMakingLoseStreakCorrection loseStreakCorrection;
	int highRatingThreshold;
	int proRatingThreshold;
	int noobGamesMaxNormalRating;
	int highRatingCooldown;
	float noobsTimeout;
	int minimalNoobsPercentage;
	int fullPartyGameRatingDiffMin;
	int fullPartyGameRatingDiffMax;
	int waitTimeSoftLimit;
	int waitTimeHardLimit;
	int teamLeaversTimeTrashold;
	int gameLeaversTimeTrashold;
	MMakingLocationPingSettings locationPingSettings;
	MMakingWaitVsProbability waitVsProbability;
	vector< MMakingRank > ranks;
	vector< RecessionData > recessionTableForForceMM;
	vector< float > recessionPremiumTable;
	RecessionFullPartyTableForForceMM recessionFullPartyTableForForceMM;
	float recessionPremiumTimeThreshold;
	RecessionTableForPlayerRatingMM recessionTableForPlayerRatingMM;
	int playerDiff;
	float rankDifferenceTimePenalty;
	float heroClassLimitsAttenuationTime;
	bool useRanking;
	vector< MMakingHeroClass > optimalClasses;
	vector< float > delayPerDonorLocalePlayer;
	int fullPartySize;
	float fullPartyVsRandomTimeThreshold;
	int localeWaitTimeThreshold;
	MMakingScale ratingScale;
	MMakingScale forceScale;
	float TeamSideTimeTreshold;

	MapMMakingSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MapMMakingSettings& operator = ( const MapMMakingSettings &_mapMMakingSettings ) { Assign( _mapMMakingSettings ); return *this; }
	MapMMakingSettings( const MapMMakingSettings &_mapMMakingSettings ) { Assign( _mapMMakingSettings ); }
	virtual void Assign( const MapMMakingSettings &_mapMMakingSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MapMMakingSettings * pOther = dynamic_cast< const MapMMakingSettings * > ( _pResource );
		if ( pOther ) MapMMakingSettings::Assign( *pOther );
	}
};

struct MarketingEventRollItem : public RollItem
{
	DBRESOURCE_METHODS( MarketingEventRollItem );
public:
	string persistentId;

	MarketingEventRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MarketingEventRollItem& operator = ( const MarketingEventRollItem &_marketingEventRollItem ) { Assign( _marketingEventRollItem ); return *this; }
	MarketingEventRollItem( const MarketingEventRollItem &_marketingEventRollItem ) { Assign( _marketingEventRollItem ); }
	virtual void Assign( const MarketingEventRollItem &_marketingEventRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MarketingEventRollItem * pOther = dynamic_cast< const MarketingEventRollItem * > ( _pResource );
		if ( pOther ) MarketingEventRollItem::Assign( *pOther );
	}
};

struct ModeRollSettings : public DbResource
{
	DBRESOURCE_METHODS( ModeRollSettings );
public:
	int scoresCap;
	int containersOnWin;
	Ptr< RollContainerCountByRank > containersOnFWOD;
	Ptr< ContainersBySpecialPoints > containersBySpecialPoints;
	ETalentRollGroup allowedRollGroups;
	vector< Ptr< RollContainer > > containers;
	vector< Ptr< RollContainer > > premiumContainers;
	vector< Ptr< RollContainer > > additionalPremiumContainers;
	Ptr< RollContainer > defaultContainer;
	vector< Ptr< RollContainer > > eventContainers;
	vector< Ptr< RollContainer > > premiumEventContainers;
	int enduranceGain;
	float enduranceCoeff;
	float enduranceFameCoeff;
	float enduranceExperienceCoeff;
	float enduranceResourcesCoeff;
	float leaversAwardsCoeff;
	int reliabilityOnFinishWin;
	int reliabilityOnFinishLose;
	int reliabilityOnFinishPeriod;
	int reliabilityOnFinishPerPeriod;
	int reliabilityOnLeave;
	int reliabilityOnLeavePeriod;
	int reliabilityOnLeavePerPeriod;
	int talentsMultiplicator;
	bool enduranceDisableRollBoost;
	vector< RollLevelInfo > famePerSession;
	float fameLoseCoeff;
	float experienceLoseCoeff;
	float resourcesLoseCoeff;
	vector< RollLevelInfo > experiencePerSession;
	int dodgePointsOnLeave;
	float ratingChangeMultiplier;
	int minSessionDuration;
	int applyPremiumTalent;
	Ptr< RollContainer > FWODRewardContainer;
	string modeName;
	int version;
	bool teamWinDisconnectedWin;
	Ptr< ClanWarsSettings > clanWarsSettings;
	int fullPartySize;

	ModeRollSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ModeRollSettings& operator = ( const ModeRollSettings &_modeRollSettings ) { Assign( _modeRollSettings ); return *this; }
	ModeRollSettings( const ModeRollSettings &_modeRollSettings ) { Assign( _modeRollSettings ); }
	virtual void Assign( const ModeRollSettings &_modeRollSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ModeRollSettings * pOther = dynamic_cast< const ModeRollSettings * > ( _pResource );
		if ( pOther ) ModeRollSettings::Assign( *pOther );
	}
};

struct NothingRollItem : public RollItem
{
	DBRESOURCE_METHODS( NothingRollItem );
public:
	int dummy;

	NothingRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NothingRollItem& operator = ( const NothingRollItem &_nothingRollItem ) { Assign( _nothingRollItem ); return *this; }
	NothingRollItem( const NothingRollItem &_nothingRollItem ) { Assign( _nothingRollItem ); }
	virtual void Assign( const NothingRollItem &_nothingRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NothingRollItem * pOther = dynamic_cast< const NothingRollItem * > ( _pResource );
		if ( pOther ) NothingRollItem::Assign( *pOther );
	}
};

struct PlayerPointsBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( PlayerPointsBonus );
public:
	int fakeFieldForCastle;

	PlayerPointsBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PlayerPointsBonus& operator = ( const PlayerPointsBonus &_playerPointsBonus ) { Assign( _playerPointsBonus ); return *this; }
	PlayerPointsBonus( const PlayerPointsBonus &_playerPointsBonus ) { Assign( _playerPointsBonus ); }
	virtual void Assign( const PlayerPointsBonus &_playerPointsBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PlayerPointsBonus * pOther = dynamic_cast< const PlayerPointsBonus * > ( _pResource );
		if ( pOther ) PlayerPointsBonus::Assign( *pOther );
	}
};

struct PremiumAccRollItem : public RollItem
{
	DBRESOURCE_METHODS( PremiumAccRollItem );
public:
	int days;

	PremiumAccRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PremiumAccRollItem& operator = ( const PremiumAccRollItem &_premiumAccRollItem ) { Assign( _premiumAccRollItem ); return *this; }
	PremiumAccRollItem( const PremiumAccRollItem &_premiumAccRollItem ) { Assign( _premiumAccRollItem ); }
	virtual void Assign( const PremiumAccRollItem &_premiumAccRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PremiumAccRollItem * pOther = dynamic_cast< const PremiumAccRollItem * > ( _pResource );
		if ( pOther ) PremiumAccRollItem::Assign( *pOther );
	}
};

struct RandomTalentBonus : public GuildBonus
{
	DBRESOURCE_METHODS( RandomTalentBonus );
public:
	SingleRollSettings singleRollSettings;

	RandomTalentBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RandomTalentBonus& operator = ( const RandomTalentBonus &_randomTalentBonus ) { Assign( _randomTalentBonus ); return *this; }
	RandomTalentBonus( const RandomTalentBonus &_randomTalentBonus ) { Assign( _randomTalentBonus ); }
	virtual void Assign( const RandomTalentBonus &_randomTalentBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RandomTalentBonus * pOther = dynamic_cast< const RandomTalentBonus * > ( _pResource );
		if ( pOther ) RandomTalentBonus::Assign( *pOther );
	}
};

struct RarityTalentListRollItem : public RollItem
{
	DBRESOURCE_METHODS( RarityTalentListRollItem );
public:
	ETalentRarity rarity;

	RarityTalentListRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RarityTalentListRollItem& operator = ( const RarityTalentListRollItem &_rarityTalentListRollItem ) { Assign( _rarityTalentListRollItem ); return *this; }
	RarityTalentListRollItem( const RarityTalentListRollItem &_rarityTalentListRollItem ) { Assign( _rarityTalentListRollItem ); }
	virtual void Assign( const RarityTalentListRollItem &_rarityTalentListRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RarityTalentListRollItem * pOther = dynamic_cast< const RarityTalentListRollItem * > ( _pResource );
		if ( pOther ) RarityTalentListRollItem::Assign( *pOther );
	}
};

struct ResourceRollItem : public RollItem
{
	DBRESOURCE_METHODS( ResourceRollItem );
public:
	ResourceRollConstraint type;
	string customCurrencyId;
	vector< RollLevelInfo > itemsFromLord;
	vector< RollLevelInfo > itemsFromHero;
	vector< RollLevelInfo > itemsFromRank;

	ResourceRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ResourceRollItem& operator = ( const ResourceRollItem &_resourceRollItem ) { Assign( _resourceRollItem ); return *this; }
	ResourceRollItem( const ResourceRollItem &_resourceRollItem ) { Assign( _resourceRollItem ); }
	virtual void Assign( const ResourceRollItem &_resourceRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ResourceRollItem * pOther = dynamic_cast< const ResourceRollItem * > ( _pResource );
		if ( pOther ) ResourceRollItem::Assign( *pOther );
	}
};

struct RollContainer : public RollItem
{
	DBRESOURCE_METHODS( RollContainer );
public:
	Ptr< RollContainerCostByRank > costByRank;
	string name;
	vector< RollItemProbability > items;
	int multiplicator;

	RollContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RollContainer& operator = ( const RollContainer &_rollContainer ) { Assign( _rollContainer ); return *this; }
	RollContainer( const RollContainer &_rollContainer ) { Assign( _rollContainer ); }
	virtual void Assign( const RollContainer &_rollContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RollContainer * pOther = dynamic_cast< const RollContainer * > ( _pResource );
		if ( pOther ) RollContainer::Assign( *pOther );
	}
};

struct RollContainerCostByRank : public DbResource
{
	DBRESOURCE_METHODS( RollContainerCostByRank );
public:
	vector< float > costs;

	RollContainerCostByRank();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RollContainerCostByRank& operator = ( const RollContainerCostByRank &_rollContainerCostByRank ) { Assign( _rollContainerCostByRank ); return *this; }
	RollContainerCostByRank( const RollContainerCostByRank &_rollContainerCostByRank ) { Assign( _rollContainerCostByRank ); }
	virtual void Assign( const RollContainerCostByRank &_rollContainerCostByRank );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RollContainerCostByRank * pOther = dynamic_cast< const RollContainerCostByRank * > ( _pResource );
		if ( pOther ) RollContainerCostByRank::Assign( *pOther );
	}
};

struct RollContainerCountByRank : public DbResource
{
	DBRESOURCE_METHODS( RollContainerCountByRank );
public:
	vector< int > counts;

	RollContainerCountByRank();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RollContainerCountByRank& operator = ( const RollContainerCountByRank &_rollContainerCountByRank ) { Assign( _rollContainerCountByRank ); return *this; }
	RollContainerCountByRank( const RollContainerCountByRank &_rollContainerCountByRank ) { Assign( _rollContainerCountByRank ); }
	virtual void Assign( const RollContainerCountByRank &_rollContainerCountByRank );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RollContainerCountByRank * pOther = dynamic_cast< const RollContainerCountByRank * > ( _pResource );
		if ( pOther ) RollContainerCountByRank::Assign( *pOther );
	}
};

struct ClanWarsRollItem : public RollItem
{
	DBRESOURCE_METHODS( ClanWarsRollItem );
public:
	ClanWarsRollItemType type;
	float count;

	ClanWarsRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ClanWarsRollItem& operator = ( const ClanWarsRollItem &_clanWarsRollItem ) { Assign( _clanWarsRollItem ); return *this; }
	ClanWarsRollItem( const ClanWarsRollItem &_clanWarsRollItem ) { Assign( _clanWarsRollItem ); }
	virtual void Assign( const ClanWarsRollItem &_clanWarsRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ClanWarsRollItem * pOther = dynamic_cast< const ClanWarsRollItem * > ( _pResource );
		if ( pOther ) ClanWarsRollItem::Assign( *pOther );
	}
};

struct RollSettings : public DbResource
{
	DBRESOURCE_METHODS( RollSettings );
public:
	Ptr< ModeRollSettings > pvp;
	Ptr< RollContainerCostByRank > defaultRollContainerCostByRank;
	Ptr< ModeRollSettings > trainingFWODSettings;
	vector< RatingModifier > ratingModifiers;
	vector< FullPartyRatingModifier > fullPartyRatingModifiers;
	SingleRollSettings forgeRollSettings;
	Ptr< GuildLevels > guildLevels;
	int requiredLevelForExclusiveTalents;
	int requiredRatingForExclusiveTalents;
	Ptr< ClanWarsSettings > clanWarsSettings;

	RollSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RollSettings& operator = ( const RollSettings &_rollSettings ) { Assign( _rollSettings ); return *this; }
	RollSettings( const RollSettings &_rollSettings ) { Assign( _rollSettings ); }
	virtual void Assign( const RollSettings &_rollSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RollSettings * pOther = dynamic_cast< const RollSettings * > ( _pResource );
		if ( pOther ) RollSettings::Assign( *pOther );
	}
};

struct ScoringTable : public DbResource
{
	DBRESOURCE_METHODS( ScoringTable );
public:
	enum { typeId = 0xA06693C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScoringTable::typeId; }

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

struct SessionAudioRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionAudioRoot );
public:

	SessionAudioRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionAudioRoot& operator = ( const SessionAudioRoot &_sessionAudioRoot ) { Assign( _sessionAudioRoot ); return *this; }
	SessionAudioRoot( const SessionAudioRoot &_sessionAudioRoot ) { Assign( _sessionAudioRoot ); }
	virtual void Assign( const SessionAudioRoot &_sessionAudioRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionAudioRoot * pOther = dynamic_cast< const SessionAudioRoot * > ( _pResource );
		if ( pOther ) SessionAudioRoot::Assign( *pOther );
	}
};

struct GuildWarEventPass : public SessionBonus
{
	DBRESOURCE_METHODS( GuildWarEventPass );
public:
	int fakeFieldForCastle;

	GuildWarEventPass();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GuildWarEventPass& operator = ( const GuildWarEventPass &_guildWarEventPass ) { Assign( _guildWarEventPass ); return *this; }
	GuildWarEventPass( const GuildWarEventPass &_guildWarEventPass ) { Assign( _guildWarEventPass ); }
	virtual void Assign( const GuildWarEventPass &_guildWarEventPass );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GuildWarEventPass * pOther = dynamic_cast< const GuildWarEventPass * > ( _pResource );
		if ( pOther ) GuildWarEventPass::Assign( *pOther );
	}
};

struct SessionLogicRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionLogicRoot );
public:
	Ptr< AILogicParameters > aiLogic;
	Ptr< ScoringTable > scoringTable;
	Ptr< UnitsLogicParameters > unitLogicParameters;
	Ptr< GlyphsDB > glyphsDB;
	Ptr< HeroesDB > heroes;
	Ptr< HeroesLevelUps > heroesLevelups;
	Ptr< ImpulsiveBuffsContainer > impulsiveBuffs;
	Ptr< DefaultFormulas > defaultFormulas;
	Ptr< MapList > mapList;
	Ptr< GuildBuffsCollection > guildBuffsCollection;

	SessionLogicRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionLogicRoot& operator = ( const SessionLogicRoot &_sessionLogicRoot ) { Assign( _sessionLogicRoot ); return *this; }
	SessionLogicRoot( const SessionLogicRoot &_sessionLogicRoot ) { Assign( _sessionLogicRoot ); }
	virtual void Assign( const SessionLogicRoot &_sessionLogicRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionLogicRoot * pOther = dynamic_cast< const SessionLogicRoot * > ( _pResource );
		if ( pOther ) SessionLogicRoot::Assign( *pOther );
	}
};

struct SessionMessages : public DbResource
{
	DBRESOURCE_METHODS( SessionMessages );
public:

	SessionMessages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionMessages& operator = ( const SessionMessages &_sessionMessages ) { Assign( _sessionMessages ); return *this; }
	SessionMessages( const SessionMessages &_sessionMessages ) { Assign( _sessionMessages ); }
	virtual void Assign( const SessionMessages &_sessionMessages );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionMessages * pOther = dynamic_cast< const SessionMessages * > ( _pResource );
		if ( pOther ) SessionMessages::Assign( *pOther );
	}
};

struct SessionResourceBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( SessionResourceBonus );
public:
	EResourceType resource;

	SessionResourceBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionResourceBonus& operator = ( const SessionResourceBonus &_sessionResourceBonus ) { Assign( _sessionResourceBonus ); return *this; }
	SessionResourceBonus( const SessionResourceBonus &_sessionResourceBonus ) { Assign( _sessionResourceBonus ); }
	virtual void Assign( const SessionResourceBonus &_sessionResourceBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionResourceBonus * pOther = dynamic_cast< const SessionResourceBonus * > ( _pResource );
		if ( pOther ) SessionResourceBonus::Assign( *pOther );
	}
};

struct SessionRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionRoot );
private:
	static Ptr< SessionRoot > instance;
	static bool instanceInitialized;
public:
	Ptr< SessionUIRoot > uiRoot;
	Ptr< SessionLogicRoot > logicRoot;
	Ptr< SessionVisualRoot > visualRoot;
	Ptr< SessionAudioRoot > audioRoot;
	Ptr< RollSettings > rollSettings;
	Ptr< SessionMessages > sessionMessages;

	SessionRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionRoot& operator = ( const SessionRoot &_sessionRoot ) { Assign( _sessionRoot ); return *this; }
	SessionRoot( const SessionRoot &_sessionRoot ) { Assign( _sessionRoot ); }
	virtual void Assign( const SessionRoot &_sessionRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionRoot * pOther = dynamic_cast< const SessionRoot * > ( _pResource );
		if ( pOther ) SessionRoot::Assign( *pOther );
	}
	static void InitRoot( const DBID& dbid );
	static void InitRoot( const SessionRoot* instance );
	static const Ptr< SessionRoot >& GetRoot();
};

struct SessionTalentsBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( SessionTalentsBonus );
public:
	int fakeFieldForCastle;

	SessionTalentsBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionTalentsBonus& operator = ( const SessionTalentsBonus &_sessionTalentsBonus ) { Assign( _sessionTalentsBonus ); return *this; }
	SessionTalentsBonus( const SessionTalentsBonus &_sessionTalentsBonus ) { Assign( _sessionTalentsBonus ); }
	virtual void Assign( const SessionTalentsBonus &_sessionTalentsBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionTalentsBonus * pOther = dynamic_cast< const SessionTalentsBonus * > ( _pResource );
		if ( pOther ) SessionTalentsBonus::Assign( *pOther );
	}
};

struct SessionUIRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionUIRoot );
public:

	SessionUIRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionUIRoot& operator = ( const SessionUIRoot &_sessionUIRoot ) { Assign( _sessionUIRoot ); return *this; }
	SessionUIRoot( const SessionUIRoot &_sessionUIRoot ) { Assign( _sessionUIRoot ); }
	virtual void Assign( const SessionUIRoot &_sessionUIRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionUIRoot * pOther = dynamic_cast< const SessionUIRoot * > ( _pResource );
		if ( pOther ) SessionUIRoot::Assign( *pOther );
	}
};

struct ClanPointsBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( ClanPointsBonus );
public:
	int fakeFieldForCastle;

	ClanPointsBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ClanPointsBonus& operator = ( const ClanPointsBonus &_clanPointsBonus ) { Assign( _clanPointsBonus ); return *this; }
	ClanPointsBonus( const ClanPointsBonus &_clanPointsBonus ) { Assign( _clanPointsBonus ); }
	virtual void Assign( const ClanPointsBonus &_clanPointsBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ClanPointsBonus * pOther = dynamic_cast< const ClanPointsBonus * > ( _pResource );
		if ( pOther ) ClanPointsBonus::Assign( *pOther );
	}
};

struct SessionVisualRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionVisualRoot );
public:

	SessionVisualRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionVisualRoot& operator = ( const SessionVisualRoot &_sessionVisualRoot ) { Assign( _sessionVisualRoot ); return *this; }
	SessionVisualRoot( const SessionVisualRoot &_sessionVisualRoot ) { Assign( _sessionVisualRoot ); }
	virtual void Assign( const SessionVisualRoot &_sessionVisualRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionVisualRoot * pOther = dynamic_cast< const SessionVisualRoot * > ( _pResource );
		if ( pOther ) SessionVisualRoot::Assign( *pOther );
	}
};

struct SiegePointsBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( SiegePointsBonus );
public:
	int fakeFieldForCastle;

	SiegePointsBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SiegePointsBonus& operator = ( const SiegePointsBonus &_siegePointsBonus ) { Assign( _siegePointsBonus ); return *this; }
	SiegePointsBonus( const SiegePointsBonus &_siegePointsBonus ) { Assign( _siegePointsBonus ); }
	virtual void Assign( const SiegePointsBonus &_siegePointsBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SiegePointsBonus * pOther = dynamic_cast< const SiegePointsBonus * > ( _pResource );
		if ( pOther ) SiegePointsBonus::Assign( *pOther );
	}
};

struct BaseHero : public Creature
{
	DBRESOURCE_METHODS( BaseHero );
public:
	EGender gender;
	vector< string > mmakingAntagonists;
	EHeroRaces heroRace;
	vector< Ptr< HeroSkin > > heroSkins;

	BaseHero();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BaseHero& operator = ( const BaseHero &_baseHero ) { Assign( _baseHero ); return *this; }
	BaseHero( const BaseHero &_baseHero ) { Assign( _baseHero ); }
	virtual void Assign( const BaseHero &_baseHero );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BaseHero * pOther = dynamic_cast< const BaseHero * > ( _pResource );
		if ( pOther ) BaseHero::Assign( *pOther );
	}
};

struct SkinRollItem : public RollItem
{
	DBRESOURCE_METHODS( SkinRollItem );
public:
	Ptr< HeroSkin > skin;

	SkinRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SkinRollItem& operator = ( const SkinRollItem &_skinRollItem ) { Assign( _skinRollItem ); return *this; }
	SkinRollItem( const SkinRollItem &_skinRollItem ) { Assign( _skinRollItem ); }
	virtual void Assign( const SkinRollItem &_skinRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SkinRollItem * pOther = dynamic_cast< const SkinRollItem * > ( _pResource );
		if ( pOther ) SkinRollItem::Assign( *pOther );
	}
};

struct Ability : public Spell
{
	DBRESOURCE_METHODS( Ability );
public:
	enum { typeId = 0x2C5C0B01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Ability::typeId; }

	Ability();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Ability& operator = ( const Ability &_ability ) { Assign( _ability ); return *this; }
	Ability( const Ability &_ability ) { Assign( _ability ); }
	virtual void Assign( const Ability &_ability );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Ability * pOther = dynamic_cast< const Ability * > ( _pResource );
		if ( pOther ) Ability::Assign( *pOther );
	}
};

struct StatChangeBonus : public SessionBonus
{
	DBRESOURCE_METHODS( StatChangeBonus );
public:
	vector< StatBonus > statBonuses;
	vector< EStat > excludedBufs;
	EStatBufToggle toggle;

	StatChangeBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatChangeBonus& operator = ( const StatChangeBonus &_statChangeBonus ) { Assign( _statChangeBonus ); return *this; }
	StatChangeBonus( const StatChangeBonus &_statChangeBonus ) { Assign( _statChangeBonus ); }
	virtual void Assign( const StatChangeBonus &_statChangeBonus );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatChangeBonus * pOther = dynamic_cast< const StatChangeBonus * > ( _pResource );
		if ( pOther ) StatChangeBonus::Assign( *pOther );
	}
};

struct Talent : public Ability
{
	DBRESOURCE_METHODS( Talent );
public:
	enum { typeId = 0x0F690AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Talent::typeId; }
	ETalentRarity rarity;
	string persistentId;
	int vendorCost;
	ETalentRollGroup talentRollGroups;

	Talent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Talent& operator = ( const Talent &_talent ) { Assign( _talent ); return *this; }
	Talent( const Talent &_talent ) { Assign( _talent ); }
	virtual void Assign( const Talent &_talent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Talent * pOther = dynamic_cast< const Talent * > ( _pResource );
		if ( pOther ) Talent::Assign( *pOther );
	}
};

struct TalentRollItem : public RollItem
{
	DBRESOURCE_METHODS( TalentRollItem );
public:
	Ptr< Talent > talent;

	TalentRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentRollItem& operator = ( const TalentRollItem &_talentRollItem ) { Assign( _talentRollItem ); return *this; }
	TalentRollItem( const TalentRollItem &_talentRollItem ) { Assign( _talentRollItem ); }
	virtual void Assign( const TalentRollItem &_talentRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentRollItem * pOther = dynamic_cast< const TalentRollItem * > ( _pResource );
		if ( pOther ) TalentRollItem::Assign( *pOther );
	}
};

struct TalentUpgradeEntity : public DbResource
{
	DBRESOURCE_METHODS( TalentUpgradeEntity );
public:
	string persistentId;
	TalentUpgradeEntityType type;
	int talentLevelLimit;
	int probability;

	TalentUpgradeEntity();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentUpgradeEntity& operator = ( const TalentUpgradeEntity &_talentUpgradeEntity ) { Assign( _talentUpgradeEntity ); return *this; }
	TalentUpgradeEntity( const TalentUpgradeEntity &_talentUpgradeEntity ) { Assign( _talentUpgradeEntity ); }
	virtual void Assign( const TalentUpgradeEntity &_talentUpgradeEntity );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentUpgradeEntity * pOther = dynamic_cast< const TalentUpgradeEntity * > ( _pResource );
		if ( pOther ) TalentUpgradeEntity::Assign( *pOther );
	}
};

struct TalentUpgradeEntityRollItem : public RollItem
{
	DBRESOURCE_METHODS( TalentUpgradeEntityRollItem );
public:
	Ptr< TalentUpgradeEntity > entity;

	TalentUpgradeEntityRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentUpgradeEntityRollItem& operator = ( const TalentUpgradeEntityRollItem &_talentUpgradeEntityRollItem ) { Assign( _talentUpgradeEntityRollItem ); return *this; }
	TalentUpgradeEntityRollItem( const TalentUpgradeEntityRollItem &_talentUpgradeEntityRollItem ) { Assign( _talentUpgradeEntityRollItem ); }
	virtual void Assign( const TalentUpgradeEntityRollItem &_talentUpgradeEntityRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentUpgradeEntityRollItem * pOther = dynamic_cast< const TalentUpgradeEntityRollItem * > ( _pResource );
		if ( pOther ) TalentUpgradeEntityRollItem::Assign( *pOther );
	}
};

struct TalentUpgradeProbabilityTable : public DbResource
{
	DBRESOURCE_METHODS( TalentUpgradeProbabilityTable );
public:
	vector< TalentUpgradeProbability > upgrades;

	TalentUpgradeProbabilityTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentUpgradeProbabilityTable& operator = ( const TalentUpgradeProbabilityTable &_talentUpgradeProbabilityTable ) { Assign( _talentUpgradeProbabilityTable ); return *this; }
	TalentUpgradeProbabilityTable( const TalentUpgradeProbabilityTable &_talentUpgradeProbabilityTable ) { Assign( _talentUpgradeProbabilityTable ); }
	virtual void Assign( const TalentUpgradeProbabilityTable &_talentUpgradeProbabilityTable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentUpgradeProbabilityTable * pOther = dynamic_cast< const TalentUpgradeProbabilityTable * > ( _pResource );
		if ( pOther ) TalentUpgradeProbabilityTable::Assign( *pOther );
	}
};

struct TalentUpgradeRollItem : public RollItem
{
	DBRESOURCE_METHODS( TalentUpgradeRollItem );
public:
	Ptr< TalentUpgradeProbabilityTable > upgradeTable;
	Ptr< RollItem > talentItem;

	TalentUpgradeRollItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentUpgradeRollItem& operator = ( const TalentUpgradeRollItem &_talentUpgradeRollItem ) { Assign( _talentUpgradeRollItem ); return *this; }
	TalentUpgradeRollItem( const TalentUpgradeRollItem &_talentUpgradeRollItem ) { Assign( _talentUpgradeRollItem ); }
	virtual void Assign( const TalentUpgradeRollItem &_talentUpgradeRollItem );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentUpgradeRollItem * pOther = dynamic_cast< const TalentUpgradeRollItem * > ( _pResource );
		if ( pOther ) TalentUpgradeRollItem::Assign( *pOther );
	}
};

struct TargetHeroes : public DbResource
{
	DBRESOURCE_METHODS( TargetHeroes );
public:
	vector< Ptr< Hero > > heroes;

	TargetHeroes();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TargetHeroes& operator = ( const TargetHeroes &_targetHeroes ) { Assign( _targetHeroes ); return *this; }
	TargetHeroes( const TargetHeroes &_targetHeroes ) { Assign( _targetHeroes ); }
	virtual void Assign( const TargetHeroes &_targetHeroes );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TargetHeroes * pOther = dynamic_cast< const TargetHeroes * > ( _pResource );
		if ( pOther ) TargetHeroes::Assign( *pOther );
	}
};

struct Hero : public BaseHero
{
	DBRESOURCE_METHODS( Hero );
public:
	enum { typeId = 0x2C5B3C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Hero::typeId; }
	string id;
	bool legal;
	EBotRollMode botRollMode;
	vector< float > classEfficiency;

	Hero();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Hero& operator = ( const Hero &_hero ) { Assign( _hero ); return *this; }
	Hero( const Hero &_hero ) { Assign( _hero ); }
	virtual void Assign( const Hero &_hero );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Hero * pOther = dynamic_cast< const Hero * > ( _pResource );
		if ( pOther ) Hero::Assign( *pOther );
	}
};

struct UnitsLogicParameters : public DbResource
{
	DBRESOURCE_METHODS( UnitsLogicParameters );
public:

	UnitsLogicParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitsLogicParameters& operator = ( const UnitsLogicParameters &_unitsLogicParameters ) { Assign( _unitsLogicParameters ); return *this; }
	UnitsLogicParameters( const UnitsLogicParameters &_unitsLogicParameters ) { Assign( _unitsLogicParameters ); }
	virtual void Assign( const UnitsLogicParameters &_unitsLogicParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitsLogicParameters * pOther = dynamic_cast< const UnitsLogicParameters * > ( _pResource );
		if ( pOther ) UnitsLogicParameters::Assign( *pOther );
	}
};

}; // namespace NDb
