#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBStats.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;

namespace NDb
{
struct Ability;
struct AdvMapCreep;
struct AOEMaterial;
struct AoeVisual;
struct AskSoundsRef;
struct BaseAttack;
struct BaseUIMaterial;
struct BasicEffectAttached;
struct BasicEffectStandalone;
struct ConsumablesShop;
struct CreepSkin;
struct CreepSpawnTimer;
struct DBSceneObject;
struct DBSoundSceneComponent;
struct EffectBase;
struct Glyph;
struct GlyphsDB;
struct HeroResource;
struct HeroSkin;
struct Interaction;
struct KillExperienceModifier;
struct MinigamePlaceParams;
struct MSOTransactions;
struct SingleStateObject;
struct StatsContainer;
struct Summoned;
struct TalentsSet;
struct TargetSelector;
struct Texture;
struct UnitDeathParameters;
struct UnitTargetingParameters;

enum BooleanLockMode
{
	BOOLEANLOCKMODE_LOCK = 0,
	BOOLEANLOCKMODE_UNLOCK = 1,
};

const char *EnumToString( const BooleanLockMode value );
const BooleanLockMode StringToEnum_BooleanLockMode( const char* value );

template <>
struct KnownEnum< BooleanLockMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const BooleanLockMode value ) { return EnumToString( value ); }
	static const BooleanLockMode ToEnum( const char* value ) { return StringToEnum_BooleanLockMode( value ); }
	static const BooleanLockMode ToEnum( const string& value ) { return StringToEnum_BooleanLockMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EAskRecipient
{
	ASKRECIPIENT_SELF = 0,
	ASKRECIPIENT_TARGET = 1,
	ASKRECIPIENT_ALLIES = 2,
	ASKRECIPIENT_ENEMIES = 3,
	ASKRECIPIENT_ALL = 4,
};

const char *EnumToString( const EAskRecipient value );
const EAskRecipient StringToEnum_EAskRecipient( const char* value );

template <>
struct KnownEnum< EAskRecipient >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EAskRecipient value ) { return EnumToString( value ); }
	static const EAskRecipient ToEnum( const char* value ) { return StringToEnum_EAskRecipient( value ); }
	static const EAskRecipient ToEnum( const string& value ) { return StringToEnum_EAskRecipient( value.c_str() ); }
	static const int SizeOf() { return 5; }
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

enum ECreepType
{
	CREEPTYPE_FACTIONALNORMAL = 0,
	CREEPTYPE_FACTIONALSIEGE = 1,
	CREEPTYPE_FACTIONALCHAMPION = 2,
	CREEPTYPE_NEUTRALMINION = 3,
	CREEPTYPE_NEUTRALNORMAL = 4,
	CREEPTYPE_NEUTRALCHAMPION = 5,
	CREEPTYPE_NEUTRALBOSS = 6,
};

const char *EnumToString( const ECreepType value );
const ECreepType StringToEnum_ECreepType( const char* value );

template <>
struct KnownEnum< ECreepType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ECreepType value ) { return EnumToString( value ); }
	static const ECreepType ToEnum( const char* value ) { return StringToEnum_ECreepType( value ); }
	static const ECreepType ToEnum( const string& value ) { return StringToEnum_ECreepType( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EDamageType
{
	DAMAGETYPE_MATERIAL = 0,
	DAMAGETYPE_ENERGY = 1,
};

const char *EnumToString( const EDamageType value );
const EDamageType StringToEnum_EDamageType( const char* value );

template <>
struct KnownEnum< EDamageType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EDamageType value ) { return EnumToString( value ); }
	static const EDamageType ToEnum( const char* value ) { return StringToEnum_EDamageType( value ); }
	static const EDamageType ToEnum( const string& value ) { return StringToEnum_EDamageType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EGlyph
{
	GLYPH_DOUBLEDAMAGER = 0,
	GLYPH_LIFERESTORER = 1,
	GLYPH_ENERGYRESTORER = 2,
	GLYPH_REFRESHER = 3,
	GLYPH_BOOSTER = 4,
	GLYPH_INVISIBLER = 5,
};

const char *EnumToString( const EGlyph value );
const EGlyph StringToEnum_EGlyph( const char* value );

template <>
struct KnownEnum< EGlyph >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EGlyph value ) { return EnumToString( value ); }
	static const EGlyph ToEnum( const char* value ) { return StringToEnum_EGlyph( value ); }
	static const EGlyph ToEnum( const string& value ) { return StringToEnum_EGlyph( value.c_str() ); }
	static const int SizeOf() { return 6; }
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

enum ESelectionAoeVisualType
{
	SELECTIONAOEVISUALTYPE_PRIMARY = 0,
	SELECTIONAOEVISUALTYPE_SECONDARY = 1,
};

const char *EnumToString( const ESelectionAoeVisualType value );
const ESelectionAoeVisualType StringToEnum_ESelectionAoeVisualType( const char* value );

template <>
struct KnownEnum< ESelectionAoeVisualType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ESelectionAoeVisualType value ) { return EnumToString( value ); }
	static const ESelectionAoeVisualType ToEnum( const char* value ) { return StringToEnum_ESelectionAoeVisualType( value ); }
	static const ESelectionAoeVisualType ToEnum( const string& value ) { return StringToEnum_ESelectionAoeVisualType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ESpawnType
{
	SPAWNTYPE_BEFORE = 1,
	SPAWNTYPE_AFTER = 2,
};

const char *EnumToString( const ESpawnType value );
const ESpawnType StringToEnum_ESpawnType( const char* value );

template <>
struct KnownEnum< ESpawnType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ESpawnType value ) { return EnumToString( value ); }
	static const ESpawnType ToEnum( const char* value ) { return StringToEnum_ESpawnType( value ); }
	static const ESpawnType ToEnum( const string& value ) { return StringToEnum_ESpawnType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EUnitCategory
{
	UNITCATEGORY_INVALID = 0,
	UNITCATEGORY_HEROES = 1,
	UNITCATEGORY_CREEPS = 2,
	UNITCATEGORY_BUILDINGS = 3,
};

const char *EnumToString( const EUnitCategory value );
const EUnitCategory StringToEnum_EUnitCategory( const char* value );

template <>
struct KnownEnum< EUnitCategory >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EUnitCategory value ) { return EnumToString( value ); }
	static const EUnitCategory ToEnum( const char* value ) { return StringToEnum_EUnitCategory( value ); }
	static const EUnitCategory ToEnum( const string& value ) { return StringToEnum_EUnitCategory( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum MapForceStatModifierApplication
{
	MAPFORCESTATMODIFIERAPPLICATION_NONE = 0,
	MAPFORCESTATMODIFIERAPPLICATION_BASE = 1,
	MAPFORCESTATMODIFIERAPPLICATION_LEVELUP = 2,
	MAPFORCESTATMODIFIERAPPLICATION_ALL = 3,
};

const char *EnumToString( const MapForceStatModifierApplication value );
const MapForceStatModifierApplication StringToEnum_MapForceStatModifierApplication( const char* value );

template <>
struct KnownEnum< MapForceStatModifierApplication >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const MapForceStatModifierApplication value ) { return EnumToString( value ); }
	static const MapForceStatModifierApplication ToEnum( const char* value ) { return StringToEnum_MapForceStatModifierApplication( value ); }
	static const MapForceStatModifierApplication ToEnum( const string& value ) { return StringToEnum_MapForceStatModifierApplication( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

struct NeutralSpawnObject
{
public:
	Ptr< AdvMapCreep > creep;
	CPlacement offset;
	int waveDelayToAppear;
	bool useSpawnerWalkLimit;
	float limitWalkDistance;
	bool specialAwarding;

	NeutralSpawnObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AskSettings
{
public:
	float minInterval;
	EAskRecipient ask3dRecipient;

	AskSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AskSounds
{
public:
	vector< Ptr< DBSoundSceneComponent > > sounds;
	vector< Ptr< DBSoundSceneComponent > > sounds3d;
	vector< AskSettings > settings;

	AskSounds();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EvadeData
{
public:
	float waitForEvadeTime;
	float waitForNextTargetTime;
	float evadeTimeout;
	float restoreHealthPercent;

	EvadeData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GlyphEntry
{
public:
	Ptr< Glyph > glyph;
	int weight;

	GlyphEntry();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LevelDiffModifier
{
public:
	int difference;
	float modifier;

	LevelDiffModifier();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LevelUpInfo
{
public:
	bool lifetimeLevelUp;
	float interval;
	int increment;
	int spawnLevelUpInterval;
	int spawnLevelUpIncrement;

	LevelUpInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AdvMapNeutralCreepsGroup
{
public:
	vector< NeutralSpawnObject > creeps;

	AdvMapNeutralCreepsGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SpawnObject
{
public:
	Ptr< AdvMapCreep > creep;
	CPlacement place;
	Ptr< CreepSpawnTimer > timer;

	SpawnObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SummonedUnits
{
public:
	Ptr< Summoned > unitA;
	Ptr< Summoned > unitB;

	SummonedUnits();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TransactionEffects
{
public:
	Ptr< EffectBase > effectIn;
	Ptr< EffectBase > effectOut;

	TransactionEffects();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UnitCategoryParams
{
public:
	int selectionPriority;

	UnitCategoryParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SingleStateObject : public GameObject
{
	DBRESOURCE_METHODS( SingleStateObject );
public:
	enum { typeId = 0x0F641B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SingleStateObject::typeId; }
	Ptr< DBSceneObject > sceneObject;

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

struct BaseCreepSpawner : public GameObject
{
	DBRESOURCE_METHODS( BaseCreepSpawner );
public:
	LevelUpInfo levelUpInfo;
	float firstSpawnTimeOffset;

	BaseCreepSpawner();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BaseCreepSpawner& operator = ( const BaseCreepSpawner &_baseCreepSpawner ) { Assign( _baseCreepSpawner ); return *this; }
	BaseCreepSpawner( const BaseCreepSpawner &_baseCreepSpawner ) { Assign( _baseCreepSpawner ); }
	virtual void Assign( const BaseCreepSpawner &_baseCreepSpawner );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BaseCreepSpawner * pOther = dynamic_cast< const BaseCreepSpawner * > ( _pResource );
		if ( pOther ) BaseCreepSpawner::Assign( *pOther );
	}
};

struct AdvMapNeutralCreepSpawner : public BaseCreepSpawner
{
	DBRESOURCE_METHODS( AdvMapNeutralCreepSpawner );
public:
	enum { typeId = 0x0F6163C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapNeutralCreepSpawner::typeId; }
	vector< AdvMapNeutralCreepsGroup > groups;
	int spawnDelay;
	int waveCount;
	int baseLevel;
	int naftaForGroupKill;
	EMinimapIcons minimapIcon;
	bool showMinimapIcon;
	vector< CVec2 > path;
	float limitWalkDistance;
	bool useEvade;
	EvadeData evadeParams;
	bool isAggressive;
	MapForceStatModifierApplication mapForceStatModifierApplication;

	AdvMapNeutralCreepSpawner();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapNeutralCreepSpawner& operator = ( const AdvMapNeutralCreepSpawner &_advMapNeutralCreepSpawner ) { Assign( _advMapNeutralCreepSpawner ); return *this; }
	AdvMapNeutralCreepSpawner( const AdvMapNeutralCreepSpawner &_advMapNeutralCreepSpawner ) { Assign( _advMapNeutralCreepSpawner ); }
	virtual void Assign( const AdvMapNeutralCreepSpawner &_advMapNeutralCreepSpawner );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapNeutralCreepSpawner * pOther = dynamic_cast< const AdvMapNeutralCreepSpawner * > ( _pResource );
		if ( pOther ) AdvMapNeutralCreepSpawner::Assign( *pOther );
	}
};

struct AdvMapObstacle : public GameObject
{
	DBRESOURCE_METHODS( AdvMapObstacle );
public:
	enum { typeId = 0xE7879C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapObstacle::typeId; }
	bool opaque;
	BooleanLockMode LockMode;

	AdvMapObstacle();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapObstacle& operator = ( const AdvMapObstacle &_advMapObstacle ) { Assign( _advMapObstacle ); return *this; }
	AdvMapObstacle( const AdvMapObstacle &_advMapObstacle ) { Assign( _advMapObstacle ); }
	virtual void Assign( const AdvMapObstacle &_advMapObstacle );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapObstacle * pOther = dynamic_cast< const AdvMapObstacle * > ( _pResource );
		if ( pOther ) AdvMapObstacle::Assign( *pOther );
	}
};

struct AoeVisual : public DbResource
{
	DBRESOURCE_METHODS( AoeVisual );
public:
	enum { typeId = 0xB1A4F2C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AoeVisual::typeId; }
	ExecutableFloatString size;
	ExecutableBoolString enabled;
	Ptr< AOEMaterial > material;

	AoeVisual();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AoeVisual& operator = ( const AoeVisual &_aoeVisual ) { Assign( _aoeVisual ); return *this; }
	AoeVisual( const AoeVisual &_aoeVisual ) { Assign( _aoeVisual ); }
	virtual void Assign( const AoeVisual &_aoeVisual );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AoeVisual * pOther = dynamic_cast< const AoeVisual * > ( _pResource );
		if ( pOther ) AoeVisual::Assign( *pOther );
	}
};

struct AskSoundsRef : public DbResource
{
	DBRESOURCE_METHODS( AskSoundsRef );
public:
	AskSounds asks;

	AskSoundsRef();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AskSoundsRef& operator = ( const AskSoundsRef &_askSoundsRef ) { Assign( _askSoundsRef ); return *this; }
	AskSoundsRef( const AskSoundsRef &_askSoundsRef ) { Assign( _askSoundsRef ); }
	virtual void Assign( const AskSoundsRef &_askSoundsRef );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AskSoundsRef * pOther = dynamic_cast< const AskSoundsRef * > ( _pResource );
		if ( pOther ) AskSoundsRef::Assign( *pOther );
	}
};

struct AdvMapCreepSpawner : public BaseCreepSpawner
{
	DBRESOURCE_METHODS( AdvMapCreepSpawner );
public:
	enum { typeId = 0x2C5AB3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapCreepSpawner::typeId; }
	vector< SpawnObject > creeps;
	vector< CVec2 > path;
	EFaction faction;
	ERoute routeID;
	bool mustRegisterInAIWorld;
	bool useEvade;
	EvadeData evadeParams;
	float limitWalkDistance;

	AdvMapCreepSpawner();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapCreepSpawner& operator = ( const AdvMapCreepSpawner &_advMapCreepSpawner ) { Assign( _advMapCreepSpawner ); return *this; }
	AdvMapCreepSpawner( const AdvMapCreepSpawner &_advMapCreepSpawner ) { Assign( _advMapCreepSpawner ); }
	virtual void Assign( const AdvMapCreepSpawner &_advMapCreepSpawner );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapCreepSpawner * pOther = dynamic_cast< const AdvMapCreepSpawner * > ( _pResource );
		if ( pOther ) AdvMapCreepSpawner::Assign( *pOther );
	}
};

struct Unit : public SingleStateObject
{
	DBRESOURCE_METHODS( Unit );
public:
	enum { typeId = 0x9E678C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Unit::typeId; }
	Ptr< StatsContainer > stats;
	Ptr< UnitTargetingParameters > targetingParams;
	Ptr< BaseAttack > attackAbility;
	CTextRef description;
	Ptr< Texture > image;
	int overtipBarsWidth;
	float overtipVerticalOffset;
	EDamageType nativeAttack;
	EDamageType nativeDefence;
	Ptr< UnitDeathParameters > deathParameters;
	vector< Ptr< Ability > > abilities;
	float size;
	float sizeDynamic;
	float normalLevelling;
	EMinimapIcons minimapIcon;
	vector< Ptr< AoeVisual > > selectionAoe;
	int pathFindingSteps;
	Ptr< Interaction > interaction;

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

struct Creature : public Unit
{
	DBRESOURCE_METHODS( Creature );
public:
	enum { typeId = 0x9E722340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Creature::typeId; }
	Render::HDRColor recolor;

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

struct Building : public Unit
{
	DBRESOURCE_METHODS( Building );
public:
	enum { typeId = 0x0F67ACC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Building::typeId; }
	EFaction faction;
	ERoute routeID;
	int routeLevel;
	Ptr< DBSceneObject > ruinSceneObject;
	float showRuinDelay;
	string ruinLocator;
	Ptr< EffectBase > onDamageFragEffect;
	Ptr< BasicEffectStandalone > onDestructionEffect;
	bool isDecoration;
	CVec2 minimapIconOffset;
	float levelUpInterval;
	bool updateUnderWarfog;

	Building();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Building& operator = ( const Building &_building ) { Assign( _building ); return *this; }
	Building( const Building &_building ) { Assign( _building ); }
	virtual void Assign( const Building &_building );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Building * pOther = dynamic_cast< const Building * > ( _pResource );
		if ( pOther ) Building::Assign( *pOther );
	}
};

struct BattleBuilding : public Building
{
public:
	float baseRotation;

	BattleBuilding();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BattleBuilding& operator = ( const BattleBuilding &_battleBuilding ) { Assign( _battleBuilding ); return *this; }
	BattleBuilding( const BattleBuilding &_battleBuilding ) { Assign( _battleBuilding ); }
	virtual void Assign( const BattleBuilding &_battleBuilding );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BattleBuilding * pOther = dynamic_cast< const BattleBuilding * > ( _pResource );
		if ( pOther ) BattleBuilding::Assign( *pOther );
	}
};

struct Tower : public BattleBuilding
{
	DBRESOURCE_METHODS( Tower );
public:
	enum { typeId = 0x2C5BE300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Tower::typeId; }

	Tower();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Tower& operator = ( const Tower &_tower ) { Assign( _tower ); return *this; }
	Tower( const Tower &_tower ) { Assign( _tower ); }
	virtual void Assign( const Tower &_tower );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Tower * pOther = dynamic_cast< const Tower * > ( _pResource );
		if ( pOther ) Tower::Assign( *pOther );
	}
};

struct AdvMapCreep : public Creature
{
	DBRESOURCE_METHODS( AdvMapCreep );
public:
	enum { typeId = 0x1E59D400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapCreep::typeId; }
	ECreepType creepType;

	AdvMapCreep();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapCreep& operator = ( const AdvMapCreep &_advMapCreep ) { Assign( _advMapCreep ); return *this; }
	AdvMapCreep( const AdvMapCreep &_advMapCreep ) { Assign( _advMapCreep ); }
	virtual void Assign( const AdvMapCreep &_advMapCreep );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapCreep * pOther = dynamic_cast< const AdvMapCreep * > ( _pResource );
		if ( pOther ) AdvMapCreep::Assign( *pOther );
	}
};

struct CreepSkin : public DbResource
{
	DBRESOURCE_METHODS( CreepSkin );
public:
	enum { typeId = 0xB199C400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CreepSkin::typeId; }
	string heroPersistentId;
	CTextRef description;
	Ptr< Texture > image;
	Ptr< DBSceneObject > sceneObject;
	Ptr< UnitDeathParameters > deathParameters;

	CreepSkin();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CreepSkin& operator = ( const CreepSkin &_creepSkin ) { Assign( _creepSkin ); return *this; }
	CreepSkin( const CreepSkin &_creepSkin ) { Assign( _creepSkin ); }
	virtual void Assign( const CreepSkin &_creepSkin );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CreepSkin * pOther = dynamic_cast< const CreepSkin * > ( _pResource );
		if ( pOther ) CreepSkin::Assign( *pOther );
	}
};

struct CreepSpawnTimer : public DbResource
{
	DBRESOURCE_METHODS( CreepSpawnTimer );
public:
	enum { typeId = 0x0F6693C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CreepSpawnTimer::typeId; }
	int startDelay;
	int spawnDelay;
	ESpawnType spawnType;

	CreepSpawnTimer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CreepSpawnTimer& operator = ( const CreepSpawnTimer &_creepSpawnTimer ) { Assign( _creepSpawnTimer ); return *this; }
	CreepSpawnTimer( const CreepSpawnTimer &_creepSpawnTimer ) { Assign( _creepSpawnTimer ); }
	virtual void Assign( const CreepSpawnTimer &_creepSpawnTimer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CreepSpawnTimer * pOther = dynamic_cast< const CreepSpawnTimer * > ( _pResource );
		if ( pOther ) CreepSpawnTimer::Assign( *pOther );
	}
};

struct Critter : public SingleStateObject
{
	DBRESOURCE_METHODS( Critter );
public:
	enum { typeId = 0x2B832BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Critter::typeId; }
	float moveRadius;
	float alarmRadius;
	float calmDownTime;
	float moveSpeed;
	bool isVisibleUnderWarfog;

	Critter();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Critter& operator = ( const Critter &_critter ) { Assign( _critter ); return *this; }
	Critter( const Critter &_critter ) { Assign( _critter ); }
	virtual void Assign( const Critter &_critter );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Critter * pOther = dynamic_cast< const Critter * > ( _pResource );
		if ( pOther ) Critter::Assign( *pOther );
	}
};

struct Flagpole : public Unit
{
	DBRESOURCE_METHODS( Flagpole );
public:
	enum { typeId = 0x0B768C41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Flagpole::typeId; }
	Ptr< TargetSelector > ownerTowers;
	vector< Ptr< EffectBase > > effect;
	vector< Ptr< Texture > > factionImages;
	vector< CTextRef > factionDescriptions;

	Flagpole();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Flagpole& operator = ( const Flagpole &_flagpole ) { Assign( _flagpole ); return *this; }
	Flagpole( const Flagpole &_flagpole ) { Assign( _flagpole ); }
	virtual void Assign( const Flagpole &_flagpole );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Flagpole * pOther = dynamic_cast< const Flagpole * > ( _pResource );
		if ( pOther ) Flagpole::Assign( *pOther );
	}
};

struct Fountain : public Building
{
	DBRESOURCE_METHODS( Fountain );
public:
	enum { typeId = 0x0F61A400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Fountain::typeId; }

	Fountain();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Fountain& operator = ( const Fountain &_fountain ) { Assign( _fountain ); return *this; }
	Fountain( const Fountain &_fountain ) { Assign( _fountain ); }
	virtual void Assign( const Fountain &_fountain );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Fountain * pOther = dynamic_cast< const Fountain * > ( _pResource );
		if ( pOther ) Fountain::Assign( *pOther );
	}
};

struct Glyph : public Ability
{
	DBRESOURCE_METHODS( Glyph );
public:
	enum { typeId = 0x0F61DC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Glyph::typeId; }
	EGlyph id;
	Ptr< SingleStateObject > gameObject;
	Render::HDRColor color;
	int naftaCost;
	float openWarFogRadius;
	EMinimapIcons minimapIcon;
	Ptr< Ability > pickupAbility;

	Glyph();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Glyph& operator = ( const Glyph &_glyph ) { Assign( _glyph ); return *this; }
	Glyph( const Glyph &_glyph ) { Assign( _glyph ); }
	virtual void Assign( const Glyph &_glyph );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Glyph * pOther = dynamic_cast< const Glyph * > ( _pResource );
		if ( pOther ) Glyph::Assign( *pOther );
	}
};

struct GlyphsDB : public DbResource
{
	DBRESOURCE_METHODS( GlyphsDB );
public:
	vector< GlyphEntry > glyphs;

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

struct GlyphSpawner : public GameObject
{
	DBRESOURCE_METHODS( GlyphSpawner );
public:
	enum { typeId = 0x0F61DC01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GlyphSpawner::typeId; }
	bool useGlyphManager;
	GlyphSettings settings;
	Ptr< GlyphsDB > glyphs;

	GlyphSpawner();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GlyphSpawner& operator = ( const GlyphSpawner &_glyphSpawner ) { Assign( _glyphSpawner ); return *this; }
	GlyphSpawner( const GlyphSpawner &_glyphSpawner ) { Assign( _glyphSpawner ); }
	virtual void Assign( const GlyphSpawner &_glyphSpawner );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GlyphSpawner * pOther = dynamic_cast< const GlyphSpawner * > ( _pResource );
		if ( pOther ) GlyphSpawner::Assign( *pOther );
	}
};

struct BaseHero : public Creature
{
	DBRESOURCE_METHODS( BaseHero );
public:
	vector< Ptr< DBSceneObject > > heroSceneObjects;
	EGender gender;
	vector< AskSounds > askLists;
	vector< AskSounds > askListsSecondState;
	CTextRef heroNameA;
	CTextRef heroNameB;
	Ptr< Texture > heroImageA;
	Ptr< Texture > heroImageB;
	string persistentId;
	string antagonistId;
	vector< string > mmakingAntagonists;
	Ptr< Texture > minimapIconA;
	Ptr< Texture > minimapIconB;
	EHeroRaces heroRace;
	vector< EStat > recommendedStats;
	vector< Ptr< HeroSkin > > heroSkins;
	vector< SummonedUnits > summonedUnits;
	Ptr< HeroResource > uniqueResource;

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

struct HeroesLevelUps : public DbResource
{
	DBRESOURCE_METHODS( HeroesLevelUps );
public:
	vector< int > developmentPoints;
	Ptr< KillExperienceModifier > killExperienceModifiers;

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

struct HeroPlaceHolder : public GameObject
{
	DBRESOURCE_METHODS( HeroPlaceHolder );
public:
	enum { typeId = 0x2C5B3C81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HeroPlaceHolder::typeId; }
	ETeamID teamId;

	HeroPlaceHolder();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroPlaceHolder& operator = ( const HeroPlaceHolder &_heroPlaceHolder ) { Assign( _heroPlaceHolder ); return *this; }
	HeroPlaceHolder( const HeroPlaceHolder &_heroPlaceHolder ) { Assign( _heroPlaceHolder ); }
	virtual void Assign( const HeroPlaceHolder &_heroPlaceHolder );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroPlaceHolder * pOther = dynamic_cast< const HeroPlaceHolder * > ( _pResource );
		if ( pOther ) HeroPlaceHolder::Assign( *pOther );
	}
};

struct HeroResource : public DbResource
{
	DBRESOURCE_METHODS( HeroResource );
public:
	string formulaNameValue;
	string formulaNameMaximum;
	string formulaNameRegeneration;
	Ptr< BaseUIMaterial > overtipManaProgressMaterial;
	Render::Color uiManaBarColor;
	CTextRef name;
	CTextRef tooltip;
	float castleValueMaximum;

	HeroResource();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroResource& operator = ( const HeroResource &_heroResource ) { Assign( _heroResource ); return *this; }
	HeroResource( const HeroResource &_heroResource ) { Assign( _heroResource ); }
	virtual void Assign( const HeroResource &_heroResource );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroResource * pOther = dynamic_cast< const HeroResource * > ( _pResource );
		if ( pOther ) HeroResource::Assign( *pOther );
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
	CTextRef heroName;
	Ptr< Texture > heroImageA;
	Ptr< Texture > heroImageB;
	Ptr< Texture > heroRenderA;
	Ptr< Texture > heroRenderB;
	EHeroRaces heroRace;
	Ptr< DBSceneObject > sceneObject;
	Ptr< AskSoundsRef > askList;
	Ptr< AskSoundsRef > askListSecondState;
	Ptr< UnitDeathParameters > deathParameters;
	int cost;
	bool mute;
	bool botRoll;
	string antagonistSkinId;

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

struct Interaction : public DbResource
{
	DBRESOURCE_METHODS( Interaction );
public:
	enum { typeId = 0xE7A8B300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Interaction::typeId; }
	Ptr< Ability > externalAbility;
	EFactionFlags allowedFactions;

	Interaction();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Interaction& operator = ( const Interaction &_interaction ) { Assign( _interaction ); return *this; }
	Interaction( const Interaction &_interaction ) { Assign( _interaction ); }
	virtual void Assign( const Interaction &_interaction );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Interaction * pOther = dynamic_cast< const Interaction * > ( _pResource );
		if ( pOther ) Interaction::Assign( *pOther );
	}
};

struct KillExperienceModifier : public DbResource
{
	DBRESOURCE_METHODS( KillExperienceModifier );
public:
	float otherDifferenceLessCoeff;
	float otherDifferenceGreaterCoeff;
	vector< LevelDiffModifier > levelModifiers;

	KillExperienceModifier();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	KillExperienceModifier& operator = ( const KillExperienceModifier &_killExperienceModifier ) { Assign( _killExperienceModifier ); return *this; }
	KillExperienceModifier( const KillExperienceModifier &_killExperienceModifier ) { Assign( _killExperienceModifier ); }
	virtual void Assign( const KillExperienceModifier &_killExperienceModifier );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const KillExperienceModifier * pOther = dynamic_cast< const KillExperienceModifier * > ( _pResource );
		if ( pOther ) KillExperienceModifier::Assign( *pOther );
	}
};

struct MainBuilding : public Building
{
	DBRESOURCE_METHODS( MainBuilding );
public:
	enum { typeId = 0x2C5BE302 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MainBuilding::typeId; }
	int aoeUnitsCount;
	ESpellTarget aoeUnitsTypes;
	EFactionFlags aoeUnitsFactions;
	float aoeRadius;
	float minAOEDelay;
	float maxAOEDelay;
	Ptr< Ability > aoeAttack;

	MainBuilding();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MainBuilding& operator = ( const MainBuilding &_mainBuilding ) { Assign( _mainBuilding ); return *this; }
	MainBuilding( const MainBuilding &_mainBuilding ) { Assign( _mainBuilding ); }
	virtual void Assign( const MainBuilding &_mainBuilding );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MainBuilding * pOther = dynamic_cast< const MainBuilding * > ( _pResource );
		if ( pOther ) MainBuilding::Assign( *pOther );
	}
};

struct MinigamePlace : public Building
{
	DBRESOURCE_METHODS( MinigamePlace );
public:
	enum { typeId = 0x9D62D2C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MinigamePlace::typeId; }
	Ptr< MinigamePlaceParams > placeParams;
	string minigameId;
	CVec2 artifactsSpawnPosition;
	Ptr< BasicEffectAttached > onIdleEffect;

	MinigamePlace();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinigamePlace& operator = ( const MinigamePlace &_minigamePlace ) { Assign( _minigamePlace ); return *this; }
	MinigamePlace( const MinigamePlace &_minigamePlace ) { Assign( _minigamePlace ); }
	virtual void Assign( const MinigamePlace &_minigamePlace );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinigamePlace * pOther = dynamic_cast< const MinigamePlace * > ( _pResource );
		if ( pOther ) MinigamePlace::Assign( *pOther );
	}
};

struct MSOTransactions : public DbResource
{
	DBRESOURCE_METHODS( MSOTransactions );
public:
	enum { typeId = 0x8D81AB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MSOTransactions::typeId; }
	TransactionEffects effectN;
	TransactionEffects effectA;
	TransactionEffects effectB;

	MSOTransactions();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MSOTransactions& operator = ( const MSOTransactions &_mSOTransactions ) { Assign( _mSOTransactions ); return *this; }
	MSOTransactions( const MSOTransactions &_mSOTransactions ) { Assign( _mSOTransactions ); }
	virtual void Assign( const MSOTransactions &_mSOTransactions );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MSOTransactions * pOther = dynamic_cast< const MSOTransactions * > ( _pResource );
		if ( pOther ) MSOTransactions::Assign( *pOther );
	}
};

struct MultiStateObject : public GameObject
{
	DBRESOURCE_METHODS( MultiStateObject );
public:
	enum { typeId = 0x0F64B3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MultiStateObject::typeId; }
	vector< Ptr< DBSceneObject > > sceneObjects;
	vector< Ptr< DBSceneObject > > nightSceneObjects;
	Ptr< MSOTransactions > effects;
	Ptr< MSOTransactions > nightEffects;
	bool opaque;
	float fadeInOffset;
	float dropTime;
	bool isVisibleUnderWarfog;
	bool distinct;

	MultiStateObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MultiStateObject& operator = ( const MultiStateObject &_multiStateObject ) { Assign( _multiStateObject ); return *this; }
	MultiStateObject( const MultiStateObject &_multiStateObject ) { Assign( _multiStateObject ); }
	virtual void Assign( const MultiStateObject &_multiStateObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MultiStateObject * pOther = dynamic_cast< const MultiStateObject * > ( _pResource );
		if ( pOther ) MultiStateObject::Assign( *pOther );
	}
};

struct Quarter : public Building
{
	DBRESOURCE_METHODS( Quarter );
public:
	enum { typeId = 0x2C5BE301 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Quarter::typeId; }

	Quarter();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Quarter& operator = ( const Quarter &_quarter ) { Assign( _quarter ); return *this; }
	Quarter( const Quarter &_quarter ) { Assign( _quarter ); }
	virtual void Assign( const Quarter &_quarter );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Quarter * pOther = dynamic_cast< const Quarter * > ( _pResource );
		if ( pOther ) Quarter::Assign( *pOther );
	}
};

struct ScriptedFlagpole : public Flagpole
{
	DBRESOURCE_METHODS( ScriptedFlagpole );
public:
	enum { typeId = 0x9A9BA381 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScriptedFlagpole::typeId; }

	ScriptedFlagpole();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScriptedFlagpole& operator = ( const ScriptedFlagpole &_scriptedFlagpole ) { Assign( _scriptedFlagpole ); return *this; }
	ScriptedFlagpole( const ScriptedFlagpole &_scriptedFlagpole ) { Assign( _scriptedFlagpole ); }
	virtual void Assign( const ScriptedFlagpole &_scriptedFlagpole );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScriptedFlagpole * pOther = dynamic_cast< const ScriptedFlagpole * > ( _pResource );
		if ( pOther ) ScriptedFlagpole::Assign( *pOther );
	}
};

struct Shop : public Building
{
	DBRESOURCE_METHODS( Shop );
public:
	enum { typeId = 0x0F61AC41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Shop::typeId; }
	Ptr< ConsumablesShop > shop;

	Shop();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Shop& operator = ( const Shop &_shop ) { Assign( _shop ); return *this; }
	Shop( const Shop &_shop ) { Assign( _shop ); }
	virtual void Assign( const Shop &_shop );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Shop * pOther = dynamic_cast< const Shop * > ( _pResource );
		if ( pOther ) Shop::Assign( *pOther );
	}
};

struct SimpleObject : public SingleStateObject
{
	DBRESOURCE_METHODS( SimpleObject );
public:
	enum { typeId = 0x8E547B04 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SimpleObject::typeId; }
	int health;
	bool opaque;
	bool isVisibleUnderWarfog;

	SimpleObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SimpleObject& operator = ( const SimpleObject &_simpleObject ) { Assign( _simpleObject ); return *this; }
	SimpleObject( const SimpleObject &_simpleObject ) { Assign( _simpleObject ); }
	virtual void Assign( const SimpleObject &_simpleObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SimpleObject * pOther = dynamic_cast< const SimpleObject * > ( _pResource );
		if ( pOther ) SimpleObject::Assign( *pOther );
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
	bool canMount;
	float askBlessCooldown;
	vector< Ptr< TalentsSet > > defaultTalentsSets;

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

struct Summoned : public Creature
{
	DBRESOURCE_METHODS( Summoned );
public:
	enum { typeId = 0xB199C440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Summoned::typeId; }
	vector< Ptr< CreepSkin > > creepSkins;

	Summoned();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Summoned& operator = ( const Summoned &_summoned ) { Assign( _summoned ); return *this; }
	Summoned( const Summoned &_summoned ) { Assign( _summoned ); }
	virtual void Assign( const Summoned &_summoned );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Summoned * pOther = dynamic_cast< const Summoned * > ( _pResource );
		if ( pOther ) Summoned::Assign( *pOther );
	}
};

struct ControllableTower : public Tower
{
	DBRESOURCE_METHODS( ControllableTower );
public:
	enum { typeId = 0x2C6C1340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ControllableTower::typeId; }

	ControllableTower();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ControllableTower& operator = ( const ControllableTower &_controllableTower ) { Assign( _controllableTower ); return *this; }
	ControllableTower( const ControllableTower &_controllableTower ) { Assign( _controllableTower ); }
	virtual void Assign( const ControllableTower &_controllableTower );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ControllableTower * pOther = dynamic_cast< const ControllableTower * > ( _pResource );
		if ( pOther ) ControllableTower::Assign( *pOther );
	}
};

struct TreeObject : public MultiStateObject
{
	DBRESOURCE_METHODS( TreeObject );
public:
	enum { typeId = 0x2C616C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TreeObject::typeId; }
	vector< Ptr< DBSceneObject > > stubsSceneObjects;
	vector< Ptr< DBSceneObject > > nightStubsSceneObjects;
	bool wonderfulTree;

	TreeObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TreeObject& operator = ( const TreeObject &_treeObject ) { Assign( _treeObject ); return *this; }
	TreeObject( const TreeObject &_treeObject ) { Assign( _treeObject ); }
	virtual void Assign( const TreeObject &_treeObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TreeObject * pOther = dynamic_cast< const TreeObject * > ( _pResource );
		if ( pOther ) TreeObject::Assign( *pOther );
	}
};

struct BasePet : public Creature
{
	DBRESOURCE_METHODS( BasePet );
public:
	enum { typeId = 0x11624C43 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasePet::typeId; }
	float test;

	BasePet();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasePet& operator = ( const BasePet &_basePet ) { Assign( _basePet ); return *this; }
	BasePet( const BasePet &_basePet ) { Assign( _basePet ); }
	virtual void Assign( const BasePet &_basePet );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasePet * pOther = dynamic_cast< const BasePet * > ( _pResource );
		if ( pOther ) BasePet::Assign( *pOther );
	}
};

struct UnitCategories : public DbResource
{
	DBRESOURCE_METHODS( UnitCategories );
public:
	vector< EUnitCategory > elements;

	UnitCategories();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitCategories& operator = ( const UnitCategories &_unitCategories ) { Assign( _unitCategories ); return *this; }
	UnitCategories( const UnitCategories &_unitCategories ) { Assign( _unitCategories ); }
	virtual void Assign( const UnitCategories &_unitCategories );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitCategories * pOther = dynamic_cast< const UnitCategories * > ( _pResource );
		if ( pOther ) UnitCategories::Assign( *pOther );
	}
};

struct UnitCategoriesParams : public DbResource
{
	DBRESOURCE_METHODS( UnitCategoriesParams );
public:
	vector< UnitCategoryParams > elements;

	UnitCategoriesParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitCategoriesParams& operator = ( const UnitCategoriesParams &_unitCategoriesParams ) { Assign( _unitCategoriesParams ); return *this; }
	UnitCategoriesParams( const UnitCategoriesParams &_unitCategoriesParams ) { Assign( _unitCategoriesParams ); }
	virtual void Assign( const UnitCategoriesParams &_unitCategoriesParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitCategoriesParams * pOther = dynamic_cast< const UnitCategoriesParams * > ( _pResource );
		if ( pOther ) UnitCategoriesParams::Assign( *pOther );
	}
};

struct UsableBuilding : public Building
{
	DBRESOURCE_METHODS( UsableBuilding );
public:
	enum { typeId = 0xE78B3C80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UsableBuilding::typeId; }

	UsableBuilding();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UsableBuilding& operator = ( const UsableBuilding &_usableBuilding ) { Assign( _usableBuilding ); return *this; }
	UsableBuilding( const UsableBuilding &_usableBuilding ) { Assign( _usableBuilding ); }
	virtual void Assign( const UsableBuilding &_usableBuilding );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UsableBuilding * pOther = dynamic_cast< const UsableBuilding * > ( _pResource );
		if ( pOther ) UsableBuilding::Assign( *pOther );
	}
};

struct WarFogUnblock : public GameObject
{
	DBRESOURCE_METHODS( WarFogUnblock );
public:
	enum { typeId = 0xEF91A282 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WarFogUnblock::typeId; }
	int radius;
	EFactionFlags faction;

	WarFogUnblock();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WarFogUnblock& operator = ( const WarFogUnblock &_warFogUnblock ) { Assign( _warFogUnblock ); return *this; }
	WarFogUnblock( const WarFogUnblock &_warFogUnblock ) { Assign( _warFogUnblock ); }
	virtual void Assign( const WarFogUnblock &_warFogUnblock );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WarFogUnblock * pOther = dynamic_cast< const WarFogUnblock * > ( _pResource );
		if ( pOther ) WarFogUnblock::Assign( *pOther );
	}
};

}; // namespace NDb
