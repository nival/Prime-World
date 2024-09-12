#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;
// forward declarations for factories
namespace PF_Minigames
{
	class IMinigamesMain;
}; //namespace PF_Minigames

namespace NDb
{
struct Ability;
struct BehaviourTrackerParams;
struct BotsSettings;
struct ConditionFormula;
struct Consumable;
struct ConsumableGroupList;
struct DBGameMenu;
struct DBLevelToExperience;
struct DerivativeStatsContainer;
struct EffectBase;
struct ForceParameters;
struct GameObject;
struct Hero;
struct HeroRanks;
struct HeroRespawnParams;
struct SingleStateObject;
struct StatsBudgetContainer;
struct StatsContainer;
struct StatsEnhancersContainer;
struct Talent;
struct TalentGroupList;
struct TalentKit;
struct TalentKitList;
struct TalentPack;
struct TalentPackList;
struct TalentsSet;
struct UnitConstantsContainer;
struct UnitLogicParameters;
struct UnitTargetingParameters;

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

enum EGlyphSpawnMode
{
	GLYPHSPAWNMODE_RANDOMWEIGHT = 0,
	GLYPHSPAWNMODE_ORDERED = 1,
};

const char *EnumToString( const EGlyphSpawnMode value );
const EGlyphSpawnMode StringToEnum_EGlyphSpawnMode( const char* value );

template <>
struct KnownEnum< EGlyphSpawnMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EGlyphSpawnMode value ) { return EnumToString( value ); }
	static const EGlyphSpawnMode ToEnum( const char* value ) { return StringToEnum_EGlyphSpawnMode( value ); }
	static const EGlyphSpawnMode ToEnum( const string& value ) { return StringToEnum_EGlyphSpawnMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EMenuItemAction
{
	MENUITEMACTION_GOBACK = 0,
	MENUITEMACTION_CONTACTWITHGAMEMASTER = 1,
	MENUITEMACTION_OPENSUBMENU = 2,
	MENUITEMACTION_GAMESETTINGS = 3,
	MENUITEMACTION_GRAPHICSETTINGS = 4,
	MENUITEMACTION_SOUNDSETTINGS = 5,
	MENUITEMACTION_CONTROLSETTINGS = 6,
	MENUITEMACTION_GOTOTOWN = 7,
	MENUITEMACTION_LEAVETHEGAME = 8,
	MENUITEMACTION_LEAVEMINIGAME = 9,
	MENUITEMACTION_ABORTMINIGAMELEVEL = 10,
};

const char *EnumToString( const EMenuItemAction value );
const EMenuItemAction StringToEnum_EMenuItemAction( const char* value );

template <>
struct KnownEnum< EMenuItemAction >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EMenuItemAction value ) { return EnumToString( value ); }
	static const EMenuItemAction ToEnum( const char* value ) { return StringToEnum_EMenuItemAction( value ); }
	static const EMenuItemAction ToEnum( const string& value ) { return StringToEnum_EMenuItemAction( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum EMenuItemType
{
	MENUITEMTYPE_BUTTONTYPE = 0,
	MENUITEMTYPE_TEXTTYPE = 1,
	MENUITEMTYPE_ICONTYPE = 2,
};

const char *EnumToString( const EMenuItemType value );
const EMenuItemType StringToEnum_EMenuItemType( const char* value );

template <>
struct KnownEnum< EMenuItemType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EMenuItemType value ) { return EnumToString( value ); }
	static const EMenuItemType ToEnum( const char* value ) { return StringToEnum_EMenuItemType( value ); }
	static const EMenuItemType ToEnum( const string& value ) { return StringToEnum_EMenuItemType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETeamColorID
{
	TEAMCOLORID_TEAM = 0,
	TEAMCOLORID_HERO1 = 1,
	TEAMCOLORID_HERO2 = 2,
	TEAMCOLORID_HERO3 = 3,
	TEAMCOLORID_HERO4 = 4,
	TEAMCOLORID_HERO5 = 5,
};

const char *EnumToString( const ETeamColorID value );
const ETeamColorID StringToEnum_ETeamColorID( const char* value );

template <>
struct KnownEnum< ETeamColorID >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const ETeamColorID value ) { return EnumToString( value ); }
	static const ETeamColorID ToEnum( const char* value ) { return StringToEnum_ETeamColorID( value ); }
	static const ETeamColorID ToEnum( const string& value ) { return StringToEnum_ETeamColorID( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum GeneralServices
{
	GENERALSERVICES_ZZBOOST = 0,
};

const char *EnumToString( const GeneralServices value );
const GeneralServices StringToEnum_GeneralServices( const char* value );

template <>
struct KnownEnum< GeneralServices >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const GeneralServices value ) { return EnumToString( value ); }
	static const GeneralServices ToEnum( const char* value ) { return StringToEnum_GeneralServices( value ); }
	static const GeneralServices ToEnum( const string& value ) { return StringToEnum_GeneralServices( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

enum ImpulseBuffs
{
	IMPULSEBUFFS_BUFF_HEALING = 0,
	IMPULSEBUFFS_BUFF_GETMANA = 1,
	IMPULSEBUFFS_BUFF_CLEANISING = 2,
	IMPULSEBUFFS_BUFF_RISING = 3,
	IMPULSEBUFFS_BUFF_INVULNERABILITY = 4,
	IMPULSEBUFFS_BUFF_BLAST = 5,
	IMPULSEBUFFS_BUFF_SPEED = 6,
	IMPULSEBUFFS_BUFF_HELP = 7,
	IMPULSEBUFFS_BUFF_GRATITUDE1 = 8,
	IMPULSEBUFFS_BUFF_GRATITUDE2 = 9,
	IMPULSEBUFFS_BUFF_RESURRECTION = 10,
};

const char *EnumToString( const ImpulseBuffs value );
const ImpulseBuffs StringToEnum_ImpulseBuffs( const char* value );

template <>
struct KnownEnum< ImpulseBuffs >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const ImpulseBuffs value ) { return EnumToString( value ); }
	static const ImpulseBuffs ToEnum( const char* value ) { return StringToEnum_ImpulseBuffs( value ); }
	static const ImpulseBuffs ToEnum( const string& value ) { return StringToEnum_ImpulseBuffs( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum TeamForceCalcMethod
{
	TEAMFORCECALCMETHOD_MINIMUM = 0,
	TEAMFORCECALCMETHOD_AVERAGE = 1,
};

const char *EnumToString( const TeamForceCalcMethod value );
const TeamForceCalcMethod StringToEnum_TeamForceCalcMethod( const char* value );

template <>
struct KnownEnum< TeamForceCalcMethod >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const TeamForceCalcMethod value ) { return EnumToString( value ); }
	static const TeamForceCalcMethod ToEnum( const char* value ) { return StringToEnum_TeamForceCalcMethod( value ); }
	static const TeamForceCalcMethod ToEnum( const string& value ) { return StringToEnum_TeamForceCalcMethod( value.c_str() ); }
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

struct AbilityAndDamageScalingParams
{
public:
	float abilityScaleStatLeft;
	float abilityScaleStatRight;
	float abilityScaleLifeLeft;
	float abilityScaleLifeRight;
	float abilityScaleEnergyLeft;
	float abilityScaleEnergyRight;
	float damageScaleStatLeft;
	float damageScaleStatRight;
	float damageScaleLifeLeft;
	float damageScaleLifeRight;
	float damageScaleEnergyLeft;
	float damageScaleEnergyRight;

	AbilityAndDamageScalingParams();

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

struct CommonSummonParameters
{
public:
	float primarySummonEscortDistance;
	float secondarySummonEscortDistance;
	float petEscortDistance;

	CommonSummonParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ConsumableGroup
{
public:
	CTextRef name;
	CTextRef description;
	float cooldown;
	vector< Ptr< Consumable > > consumables;

	ConsumableGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreatureHappyStateParams
{
public:
	float happyCreaturesPercent;
	float minRestTime;
	float happyCheckTick;

	CreatureHappyStateParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreepsLevelUpInfo
{
public:
	float interval;
	int increment;

	CreepsLevelUpInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBFameRatingPair
{
public:
	int fameLevel;
	int rating;

	DBFameRatingPair();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ExpoModeParams
{
public:
	Ptr< StatsEnhancersContainer > statsEnhancers;
	float minHeroLife;
	ExecutableFloatString damageModifier;

	ExpoModeParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GameMenuItem
{
public:
	CTextRef itemText;
	EMenuItemType itemType;
	EMenuItemAction itemAction;
	bool minigamesOnly;
	Ptr< DBGameMenu > subMenu;

	GameMenuItem();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GlyphSettings
{
public:
	float minNormalSpawnDelay;
	float maxNormalSpawnDelay;
	float minAfterPickupSpawnDelay;
	float maxAfterPickupSpawnDelay;
	float spawnAttemptDelayDecrease;
	int maxInstances;
	EGlyphSpawnMode spawnMode;

	GlyphSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct HeroStatisticsParams
{
public:
	float timeSlicePeriod;

	HeroStatisticsParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct KillTimeIntervals
{
public:
	float creepKillInterval;
	float buildingKillInterval;
	float heroKillerDeadInterval;
	float heroKillDamageInterval;

	KillTimeIntervals();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct OvertimeRespawnParams
{
public:
	float overtime;
	float respawnDelayForOvertime;

	OvertimeRespawnParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TalentGroup
{
public:
	CTextRef name;
	CTextRef description;
	float cooldown;
	vector< Ptr< Talent > > talents;

	TalentGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TeamColors
{
public:
	vector< Render::HDRColor > teamColors;

	TeamColors();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TurretParams
{
public:
	float turretAngleSpeed;
	float turretAngleAcceleration;
	float turretRotaionTolerance;
	float turretLastAngleResetDelay;

	TurretParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AILogicParameters : public DbResource
{
	DBRESOURCE_METHODS( AILogicParameters );
public:
	vector< CTextRef > teamsNames;
	Ptr< SingleStateObject > chestGameObject;
	vector< Ptr< ConditionFormula > > conditionFormulas;
	Ptr< UnitConstantsContainer > globalConstants;
	Ptr< HeroRespawnParams > heroRespawnParams;
	float heroAdvanceRespawnTime;
	float baseRedeemCost;
	float redeemCostPerLevel;
	float redeemCostrecalculateTime;
	float followRange;
	float pickupItemRange;
	float killAwardPartyMultiplier;
	float maxTrueSightRange;
	float channelingAbilityRangeMultiplier;
	float heroScreamDelay;
	float globalCooldownTime;
	float skeletonLifeTime;
	GlyphSettings glyphSettings;
	float assistAccountTime;
	KillTimeIntervals killTimeIntervals;
	int creepsWavesDelay;
	int creepLevelCap;
	CreepsLevelUpInfo creepsLevelUpInfo;
	vector< float > quarterDestroyStatsMultipliers;
	float movingTimerBlock;
	CreatureHappyStateParams creatureHappyStateParams;
	CommonSummonParameters commonSummonParameters;
	float rotationSpeed;
	float rotationSpeedZ;
	TurretParams towerTurretParams;
	vector< TurretParams > mainBuildingTurretParams;
	int expandNatureSegmentRation;
	float expandNatureGlyphsLifeTime;
	float expandNatureGlyphsVisibilityRadius;
	Ptr< GameObject > expandNatureGlyphGameObject;
	Ptr< Ability > buildingsDenyAbility;
	float buildingsDenyMinHealth;
	float buildingsDenyExperiencePenalty;
	float buildingsDenyNaftaPenalty;
	float buildingsDenyNaftaSpecPenalty;
	float buildingsDenyTeamNaftaPenalty;
	Ptr< Ability > buildingsAbilityA;
	Ptr< Ability > buildingsAbilityB;
	float buildingsMinHealthExplosionPercent;
	float buildingsFragEffectProbability;
	Ptr< Ability > raiseFlagAbility;
	float talentsBuyRange;
	Ptr< TalentsSet > defaultTalentsSet;
	float talentBaseStatBudget;
	vector< int > talentNaftaCostByLevel;
	vector< int > talentVendorCostByRarity;
	float pauseSeconds;
	Ptr< DerivativeStatsContainer > derivativeStats;
	Ptr< StatsBudgetContainer > statsBudget;
	Ptr< ForceParameters > forceParameters;
	Ptr< TalentGroupList > talentGroups;
	Ptr< ConsumableGroupList > consumableGroups;
	Ptr< TalentKitList > talentKits;
	Ptr< TalentPackList > talentPacks;
	ExecutableFloatString energyDamageReduction;
	ExecutableFloatString physicalDamageReduction;
	HeroStatisticsParams heroStatisticsParams;
	ExpoModeParams expoModeParams;
	AbilityAndDamageScalingParams abilityAndDamageScalingParams;
	Ptr< DBLevelToExperience > levelToExperienceTable;
	Ptr< BotsSettings > botsSettings;
	float warFogRemoveTime;
	float warFogRemoveRadius;
	int maxCreepsCount;
	Ptr< Talent > portal;
	Ptr< HeroRanks > heroRanks;
	int baseEmblemHeroNeeds;
	Ptr< BehaviourTrackerParams > behaviourTrackerParams;

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

struct BehaviourTrackerParams : public DbResource
{
	DBRESOURCE_METHODS( BehaviourTrackerParams );
public:
	int idleTime;
	int goodActionTimeout;
	int goodZumaActionTimeout;
	int feederDeathCount;
	int feederDeathTime;
	int badBehaviourComplaintsThreshold;
	int insultComplaintsThreshold;
	int autoMuteMinMessage;
	int autoMuteMessagePerTime;
	int autoMuteTimeLimit;
	int autoMuteMessageLength;

	BehaviourTrackerParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BehaviourTrackerParams& operator = ( const BehaviourTrackerParams &_behaviourTrackerParams ) { Assign( _behaviourTrackerParams ); return *this; }
	BehaviourTrackerParams( const BehaviourTrackerParams &_behaviourTrackerParams ) { Assign( _behaviourTrackerParams ); }
	virtual void Assign( const BehaviourTrackerParams &_behaviourTrackerParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BehaviourTrackerParams * pOther = dynamic_cast< const BehaviourTrackerParams * > ( _pResource );
		if ( pOther ) BehaviourTrackerParams::Assign( *pOther );
	}
};

struct BotsSettings : public DbResource
{
	DBRESOURCE_METHODS( BotsSettings );
public:
	float manaUsePotionThreshold;
	float healthUsePotionThreshold;
	int minShoppingMoney;
	int maxHealthPotion;
	int maxManaPotion;
	vector< Ptr< Hero > > doNotBuyMana;
	int timeToGo;
	bool midOnly;
	bool enableBotsAI;
	int timeToTeleport;
	float healthFractionToRetreatToBase;
	float healthToRetreatToBase;
	float escapeTowerDistance;
	float healthFractionToMoveToFront;
	float forcedFollowRange;

	BotsSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BotsSettings& operator = ( const BotsSettings &_botsSettings ) { Assign( _botsSettings ); return *this; }
	BotsSettings( const BotsSettings &_botsSettings ) { Assign( _botsSettings ); }
	virtual void Assign( const BotsSettings &_botsSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BotsSettings * pOther = dynamic_cast< const BotsSettings * > ( _pResource );
		if ( pOther ) BotsSettings::Assign( *pOther );
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

struct ChatLogicParameters : public DbResource
{
	DBRESOURCE_METHODS( ChatLogicParameters );
public:
	int timeBeforeDisappearing;
	int disappearingTime;
	float backgroundOpacityPermanent;
	float backgroundOpacityMotion;
	string channelStyle;
	string nicknameStyle;
	string messageStyle;

	ChatLogicParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChatLogicParameters& operator = ( const ChatLogicParameters &_chatLogicParameters ) { Assign( _chatLogicParameters ); return *this; }
	ChatLogicParameters( const ChatLogicParameters &_chatLogicParameters ) { Assign( _chatLogicParameters ); }
	virtual void Assign( const ChatLogicParameters &_chatLogicParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChatLogicParameters * pOther = dynamic_cast< const ChatLogicParameters * > ( _pResource );
		if ( pOther ) ChatLogicParameters::Assign( *pOther );
	}
};

struct ConsumableGroupList : public DbResource
{
	DBRESOURCE_METHODS( ConsumableGroupList );
public:
	vector< ConsumableGroup > groups;

	ConsumableGroupList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConsumableGroupList& operator = ( const ConsumableGroupList &_consumableGroupList ) { Assign( _consumableGroupList ); return *this; }
	ConsumableGroupList( const ConsumableGroupList &_consumableGroupList ) { Assign( _consumableGroupList ); }
	virtual void Assign( const ConsumableGroupList &_consumableGroupList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConsumableGroupList * pOther = dynamic_cast< const ConsumableGroupList * > ( _pResource );
		if ( pOther ) ConsumableGroupList::Assign( *pOther );
	}
};

struct DBGameMenu : public DbResource
{
	DBRESOURCE_METHODS( DBGameMenu );
public:
	vector< GameMenuItem > menuItems;

	DBGameMenu();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBGameMenu& operator = ( const DBGameMenu &_dBGameMenu ) { Assign( _dBGameMenu ); return *this; }
	DBGameMenu( const DBGameMenu &_dBGameMenu ) { Assign( _dBGameMenu ); }
	virtual void Assign( const DBGameMenu &_dBGameMenu );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBGameMenu * pOther = dynamic_cast< const DBGameMenu * > ( _pResource );
		if ( pOther ) DBGameMenu::Assign( *pOther );
	}
};

struct DBLevelToExperience : public DbResource
{
	DBRESOURCE_METHODS( DBLevelToExperience );
public:
	vector< int > Levels;

	DBLevelToExperience();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBLevelToExperience& operator = ( const DBLevelToExperience &_dBLevelToExperience ) { Assign( _dBLevelToExperience ); return *this; }
	DBLevelToExperience( const DBLevelToExperience &_dBLevelToExperience ) { Assign( _dBLevelToExperience ); }
	virtual void Assign( const DBLevelToExperience &_dBLevelToExperience );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBLevelToExperience * pOther = dynamic_cast< const DBLevelToExperience * > ( _pResource );
		if ( pOther ) DBLevelToExperience::Assign( *pOther );
	}
};

struct DBRatingToFame : public DbResource
{
	DBRESOURCE_METHODS( DBRatingToFame );
public:
	vector< DBFameRatingPair > Ratings;

	DBRatingToFame();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBRatingToFame& operator = ( const DBRatingToFame &_dBRatingToFame ) { Assign( _dBRatingToFame ); return *this; }
	DBRatingToFame( const DBRatingToFame &_dBRatingToFame ) { Assign( _dBRatingToFame ); }
	virtual void Assign( const DBRatingToFame &_dBRatingToFame );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBRatingToFame * pOther = dynamic_cast< const DBRatingToFame * > ( _pResource );
		if ( pOther ) DBRatingToFame::Assign( *pOther );
	}
};

struct ForceParameters : public DbResource
{
	DBRESOURCE_METHODS( ForceParameters );
public:
	vector< float > talentLevelForceModifiers;
	vector< float > talentRarityForceModifiers;
	vector< float > talentRarityForceSummand;
	vector< float > classTalentLevelForceModifiers;
	float talentForceBonusPerStar;
	float classTalentForceBonusPerStar;
	vector< float > talentLevelBonusPercent;
	float baseHeroForce;
	float defaultBaseForce;
	float masteryPointForce;
	float statBonusByForce;
	float defaultStatBonus;
	TeamForceCalcMethod teamForceCalcMethod;
	float mapHabitantsStatsMultiplier;
	float trainingBotsStatsMultiplier;
	float talentForceModifier;
	float seriesMapHabitantsStatsMultiplier;
	float maxHeroForce;

	ForceParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ForceParameters& operator = ( const ForceParameters &_forceParameters ) { Assign( _forceParameters ); return *this; }
	ForceParameters( const ForceParameters &_forceParameters ) { Assign( _forceParameters ); }
	virtual void Assign( const ForceParameters &_forceParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ForceParameters * pOther = dynamic_cast< const ForceParameters * > ( _pResource );
		if ( pOther ) ForceParameters::Assign( *pOther );
	}
};

struct HeroRespawnParams : public DbResource
{
	DBRESOURCE_METHODS( HeroRespawnParams );
public:
	float heroRespawnDelayMultiplier;
	float heroMinRespawnTime;
	float heroBaseRespawnTime;
	OvertimeRespawnParams overtimeRespawnParams;

	HeroRespawnParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroRespawnParams& operator = ( const HeroRespawnParams &_heroRespawnParams ) { Assign( _heroRespawnParams ); return *this; }
	HeroRespawnParams( const HeroRespawnParams &_heroRespawnParams ) { Assign( _heroRespawnParams ); }
	virtual void Assign( const HeroRespawnParams &_heroRespawnParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroRespawnParams * pOther = dynamic_cast< const HeroRespawnParams * > ( _pResource );
		if ( pOther ) HeroRespawnParams::Assign( *pOther );
	}
};

struct MinigamesBasic : public DbResource
{
	DBRESOURCE_METHODS( MinigamesBasic );
public:

	MinigamesBasic();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinigamesBasic& operator = ( const MinigamesBasic &_minigamesBasic ) { Assign( _minigamesBasic ); return *this; }
	MinigamesBasic( const MinigamesBasic &_minigamesBasic ) { Assign( _minigamesBasic ); }
	virtual void Assign( const MinigamesBasic &_minigamesBasic );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinigamesBasic * pOther = dynamic_cast< const MinigamesBasic * > ( _pResource );
		if ( pOther ) MinigamesBasic::Assign( *pOther );
	}

	virtual PF_Minigames::IMinigamesMain* Construct() const;
};

struct TalentGroupList : public DbResource
{
	DBRESOURCE_METHODS( TalentGroupList );
public:
	vector< TalentGroup > groups;

	TalentGroupList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentGroupList& operator = ( const TalentGroupList &_talentGroupList ) { Assign( _talentGroupList ); return *this; }
	TalentGroupList( const TalentGroupList &_talentGroupList ) { Assign( _talentGroupList ); }
	virtual void Assign( const TalentGroupList &_talentGroupList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentGroupList * pOther = dynamic_cast< const TalentGroupList * > ( _pResource );
		if ( pOther ) TalentGroupList::Assign( *pOther );
	}
};

struct TalentKitList : public DbResource
{
	DBRESOURCE_METHODS( TalentKitList );
public:
	vector< Ptr< TalentKit > > kits;

	TalentKitList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentKitList& operator = ( const TalentKitList &_talentKitList ) { Assign( _talentKitList ); return *this; }
	TalentKitList( const TalentKitList &_talentKitList ) { Assign( _talentKitList ); }
	virtual void Assign( const TalentKitList &_talentKitList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentKitList * pOther = dynamic_cast< const TalentKitList * > ( _pResource );
		if ( pOther ) TalentKitList::Assign( *pOther );
	}
};

struct TalentPackList : public DbResource
{
	DBRESOURCE_METHODS( TalentPackList );
public:
	vector< Ptr< TalentPack > > packs;

	TalentPackList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentPackList& operator = ( const TalentPackList &_talentPackList ) { Assign( _talentPackList ); return *this; }
	TalentPackList( const TalentPackList &_talentPackList ) { Assign( _talentPackList ); }
	virtual void Assign( const TalentPackList &_talentPackList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentPackList * pOther = dynamic_cast< const TalentPackList * > ( _pResource );
		if ( pOther ) TalentPackList::Assign( *pOther );
	}
};

struct TeamsColoringScheme : public DbResource
{
	DBRESOURCE_METHODS( TeamsColoringScheme );
public:
	TeamColors teamA;
	TeamColors teamB;

	TeamsColoringScheme();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TeamsColoringScheme& operator = ( const TeamsColoringScheme &_teamsColoringScheme ) { Assign( _teamsColoringScheme ); return *this; }
	TeamsColoringScheme( const TeamsColoringScheme &_teamsColoringScheme ) { Assign( _teamsColoringScheme ); }
	virtual void Assign( const TeamsColoringScheme &_teamsColoringScheme );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TeamsColoringScheme * pOther = dynamic_cast< const TeamsColoringScheme * > ( _pResource );
		if ( pOther ) TeamsColoringScheme::Assign( *pOther );
	}
};

struct UnitDeathParameters : public DbResource
{
	DBRESOURCE_METHODS( UnitDeathParameters );
public:
	float fallOffset;
	float fallSpeed;
	float deathTime;
	float unsummonTime;
	float observeOffset;
	float effectOffset;
	Ptr< EffectBase > effect;

	UnitDeathParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitDeathParameters& operator = ( const UnitDeathParameters &_unitDeathParameters ) { Assign( _unitDeathParameters ); return *this; }
	UnitDeathParameters( const UnitDeathParameters &_unitDeathParameters ) { Assign( _unitDeathParameters ); }
	virtual void Assign( const UnitDeathParameters &_unitDeathParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitDeathParameters * pOther = dynamic_cast< const UnitDeathParameters * > ( _pResource );
		if ( pOther ) UnitDeathParameters::Assign( *pOther );
	}
};

struct UnitLogicParameters : public DbResource
{
	DBRESOURCE_METHODS( UnitLogicParameters );
public:
	Ptr< StatsContainer > defaultStats;
	Ptr< UnitTargetingParameters > targetingPars;
	float screamRange;

	UnitLogicParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitLogicParameters& operator = ( const UnitLogicParameters &_unitLogicParameters ) { Assign( _unitLogicParameters ); return *this; }
	UnitLogicParameters( const UnitLogicParameters &_unitLogicParameters ) { Assign( _unitLogicParameters ); }
	virtual void Assign( const UnitLogicParameters &_unitLogicParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitLogicParameters * pOther = dynamic_cast< const UnitLogicParameters * > ( _pResource );
		if ( pOther ) UnitLogicParameters::Assign( *pOther );
	}
};

struct UnitsLogicParameters : public DbResource
{
	DBRESOURCE_METHODS( UnitsLogicParameters );
public:
	vector< Ptr< UnitLogicParameters > > unitParameters;

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

struct UnitTargetingParameters : public DbResource
{
	DBRESOURCE_METHODS( UnitTargetingParameters );
public:
	vector< float > unitTargetWeight;
	float unitTypeTableWeight;
	float weightMaximumRangePersent;
	float rangeWeight;
	float attackerMeWeight;
	vector< float > attackerHeroWeight;
	float attackerHeroTableWeight;
	float attackerHeroSummonWeight;
	float attackerTowerWeight;
	float attackerMasterWeight;
	float attackerAllyWeight;
	vector< float > currentTargetWeight;
	float currentTargetTableWeight;
	float targetRevisionTime;
	float healthWeight;
	float masterTargetWeight;
	float talentAttackWeight;
	float autoAttackWeight;
	float OutOfAggroWeight;
	float allyTargetWeight;
	float aggressiveNeutralWeight;
	float aggressiveNeutralAttackingHeroWeight;
	ExecutableFloatString customWeight;
	float maxTimeFromAttack;
	float targetingRange;
	float chaseRange;
	float aggroRange;
	bool ignoreSiblingTarget;
	bool isStationarySummon;
	bool onlyAutoTargeting;
	float attackerNearbyHeroWeight;
	float nearbyRange;
	float longSuspendTimeout;
	float sortSuspendTimeout;

	UnitTargetingParameters();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitTargetingParameters& operator = ( const UnitTargetingParameters &_unitTargetingParameters ) { Assign( _unitTargetingParameters ); return *this; }
	UnitTargetingParameters( const UnitTargetingParameters &_unitTargetingParameters ) { Assign( _unitTargetingParameters ); }
	virtual void Assign( const UnitTargetingParameters &_unitTargetingParameters );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitTargetingParameters * pOther = dynamic_cast< const UnitTargetingParameters * > ( _pResource );
		if ( pOther ) UnitTargetingParameters::Assign( *pOther );
	}
};

}; // namespace NDb
