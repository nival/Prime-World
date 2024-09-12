#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBTalent.h"

struct IXmlSaver;

namespace NDb
{
struct ClanWarsSettings;
struct ContainersBySpecialPoints;
struct CustomFlag;
struct GuildBonus;
struct GuildLevels;
struct Hero;
struct HeroSkin;
struct ModeRollSettings;
struct RollContainer;
struct RollContainerCostByRank;
struct RollContainerCountByRank;
struct RollItem;
struct Talent;
struct TalentUpgradeEntity;
struct TalentUpgradeProbabilityTable;
struct Texture;

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
	Ptr< Texture > image;
	CTextRef tooltip;

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

}; // namespace NDb
