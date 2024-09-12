#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBStats.h"

struct IXmlSaver;

namespace NDb
{
struct AdvMapDescription;
struct GuildBuff;
struct GuildShopItemBonus;
struct Hero;

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

struct HeroExperienceBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( HeroExperienceBonus );
public:

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

struct GuildWarEventPass : public SessionBonus
{
	DBRESOURCE_METHODS( GuildWarEventPass );
public:

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

struct SiegePointsBonus : public SessionValueBonus
{
	DBRESOURCE_METHODS( SiegePointsBonus );
public:

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

}; // namespace NDb
