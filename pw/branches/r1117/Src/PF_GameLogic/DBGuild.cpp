// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBAdvMap.h"
#include "../PF_GameLogic/DBUnit.h"
#include "DBGuild.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_DBRESOURCE( GuildShopItemBonus );
REGISTER_DBRESOURCE( GuildBuff );
REGISTER_DBRESOURCE( GuildBuffsCollection );
REGISTER_DBRESOURCE( HeroBonusBase );
REGISTER_DBRESOURCE( SessionBonus );
REGISTER_DBRESOURCE( SessionValueBonus );
REGISTER_DBRESOURCE( HeroEnergyBonus );
REGISTER_DBRESOURCE( HeroExperienceBonus );
REGISTER_DBRESOURCE( GuildWarEventPass );
REGISTER_DBRESOURCE( SessionResourceBonus );
REGISTER_DBRESOURCE( SiegePointsBonus );
REGISTER_DBRESOURCE( StatChangeBonus );
REGISTER_DBRESOURCE( TargetHeroes );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBuildingProductionCycle value )
{
	switch( value )
	{
		case BUILDINGPRODUCTIONCYCLE_FIRST:
			return "First";
		case BUILDINGPRODUCTIONCYCLE_SECOND:
			return "Second";
		case BUILDINGPRODUCTIONCYCLE_THIRD:
			return "Third";
		case BUILDINGPRODUCTIONCYCLE_FOURTH:
			return "Fourth";
		case BUILDINGPRODUCTIONCYCLE_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBuildingProductionCycle StringToEnum_EBuildingProductionCycle( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBuildingProductionCycle)(NStr::ToInt( value ));
	if ( strcmp( value, "First" ) == 0 || strcmp( value, "BUILDINGPRODUCTIONCYCLE_FIRST" ) == 0 )
		return BUILDINGPRODUCTIONCYCLE_FIRST;
	if ( strcmp( value, "Second" ) == 0 || strcmp( value, "BUILDINGPRODUCTIONCYCLE_SECOND" ) == 0 )
		return BUILDINGPRODUCTIONCYCLE_SECOND;
	if ( strcmp( value, "Third" ) == 0 || strcmp( value, "BUILDINGPRODUCTIONCYCLE_THIRD" ) == 0 )
		return BUILDINGPRODUCTIONCYCLE_THIRD;
	if ( strcmp( value, "Fourth" ) == 0 || strcmp( value, "BUILDINGPRODUCTIONCYCLE_FOURTH" ) == 0 )
		return BUILDINGPRODUCTIONCYCLE_FOURTH;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "BUILDINGPRODUCTIONCYCLE_ALL" ) == 0 )
		return BUILDINGPRODUCTIONCYCLE_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBuildingProductionCycle", value ) );
	return BUILDINGPRODUCTIONCYCLE_FIRST;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGameType value )
{
	switch( value )
	{
		case GAMETYPE_PVP:
			return "PvP";
		case GAMETYPE_CTE:
			return "CTE";
		case GAMETYPE_PVE:
			return "PvE";
		case GAMETYPE_MIDONLY:
			return "MidOnly";
		case GAMETYPE_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGameType StringToEnum_EGameType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGameType)(NStr::ToInt( value ));
	if ( strcmp( value, "PvP" ) == 0 || strcmp( value, "GAMETYPE_PVP" ) == 0 )
		return GAMETYPE_PVP;
	if ( strcmp( value, "CTE" ) == 0 || strcmp( value, "GAMETYPE_CTE" ) == 0 )
		return GAMETYPE_CTE;
	if ( strcmp( value, "PvE" ) == 0 || strcmp( value, "GAMETYPE_PVE" ) == 0 )
		return GAMETYPE_PVE;
	if ( strcmp( value, "MidOnly" ) == 0 || strcmp( value, "GAMETYPE_MIDONLY" ) == 0 )
		return GAMETYPE_MIDONLY;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "GAMETYPE_ALL" ) == 0 )
		return GAMETYPE_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGameType", value ) );
	return GAMETYPE_PVP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESessionType value )
{
	switch( value )
	{
		case SESSIONTYPE_USUALBATTLE:
			return "UsualBattle";
		case SESSIONTYPE_GUILDBATTLE:
			return "GuildBattle";
		case SESSIONTYPE_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESessionType StringToEnum_ESessionType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESessionType)(NStr::ToInt( value ));
	if ( strcmp( value, "UsualBattle" ) == 0 || strcmp( value, "SESSIONTYPE_USUALBATTLE" ) == 0 )
		return SESSIONTYPE_USUALBATTLE;
	if ( strcmp( value, "GuildBattle" ) == 0 || strcmp( value, "SESSIONTYPE_GUILDBATTLE" ) == 0 )
		return SESSIONTYPE_GUILDBATTLE;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "SESSIONTYPE_ALL" ) == 0 )
		return SESSIONTYPE_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESessionType", value ) );
	return SESSIONTYPE_USUALBATTLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStatBufToggle value )
{
	switch( value )
	{
		case STATBUFTOGGLE_ATGAMESTART:
			return "AtGameStart";
		case STATBUFTOGGLE_BY36LEVEL:
			return "By36Level";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStatBufToggle", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStatBufToggle StringToEnum_EStatBufToggle( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStatBufToggle)(NStr::ToInt( value ));
	if ( strcmp( value, "AtGameStart" ) == 0 || strcmp( value, "STATBUFTOGGLE_ATGAMESTART" ) == 0 )
		return STATBUFTOGGLE_ATGAMESTART;
	if ( strcmp( value, "By36Level" ) == 0 || strcmp( value, "STATBUFTOGGLE_BY36LEVEL" ) == 0 )
		return STATBUFTOGGLE_BY36LEVEL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStatBufToggle", value ) );
	return STATBUFTOGGLE_ATGAMESTART;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameProps::GameProps() :
		sessionType( SESSIONTYPE_ALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameProps::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maps );
	saver.Add( 3, &sessionType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameProps::operator&( IXmlSaver &saver )
{
	saver.Add( "maps", &maps );
	saver.Add( "sessionType", &sessionType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ValueProps::ValueProps() :
		additiveValue( 0.0f )
	, multiplicativeValue( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValueProps::operator&( IBinSaver &saver )
{
	saver.Add( 2, &additiveValue );
	saver.Add( 3, &multiplicativeValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValueProps::operator&( IXmlSaver &saver )
{
	saver.Add( "additiveValue", &additiveValue );
	saver.Add( "multiplicativeValue", &multiplicativeValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatBonus::StatBonus() :
		statType( STAT_LIFE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatBonus::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statType );
	saver.Add( 3, &modifiers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatBonus::operator&( IXmlSaver &saver )
{
	saver.Add( "statType", &statType );
	saver.Add( "modifiers", &modifiers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildShopItemBonus::GuildShopItemBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildShopItemBonus::operator&( IBinSaver &saver )
{
	saver.Add( 2, &propertyTooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildShopItemBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildShopItemBonus* parentPtr = (GuildShopItemBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildShopItemBonus::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "propertyTooltip", &propertyTooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildShopItemBonus::Assign( const GuildShopItemBonus& _guildShopItemBonus )
{
	propertyTooltip = _guildShopItemBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildBuff::GuildBuff() :
		isGuildBonus( false )
	, priority( 0 )
	, duration( 0 )
	, numGames( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBuff::operator&( IBinSaver &saver )
{
	saver.Add( 2, &persistentId );
	saver.Add( 3, &doNotWorkWith );
	saver.Add( 4, &isGuildBonus );
	saver.Add( 5, &priority );
	saver.Add( 6, &duration );
	saver.Add( 7, &numGames );
	saver.Add( 8, &propertyTooltip );
	saver.Add( 9, &bonuses );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBuff::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildBuff* parentPtr = (GuildBuff*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBuff::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "persistentId", &persistentId );
	saver.Add( "doNotWorkWith", &doNotWorkWith );
	saver.Add( "isGuildBonus", &isGuildBonus );
	saver.Add( "priority", &priority );
	saver.Add( "duration", &duration );
	saver.Add( "numGames", &numGames );
	saver.Add( "propertyTooltip", &propertyTooltip );
	saver.Add( "bonuses", &bonuses );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBuff::Assign( const GuildBuff& _guildBuff )
{
	persistentId = _guildBuff.persistentId;
	doNotWorkWith = _guildBuff.doNotWorkWith;
	isGuildBonus = _guildBuff.isGuildBonus;
	priority = _guildBuff.priority;
	duration = _guildBuff.duration;
	numGames = _guildBuff.numGames;
	propertyTooltip = _guildBuff.propertyTooltip;
	bonuses = _guildBuff.bonuses;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildBuffsCollection::GuildBuffsCollection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBuffsCollection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &buffs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBuffsCollection::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildBuffsCollection* parentPtr = (GuildBuffsCollection*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBuffsCollection::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "buffs", &buffs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBuffsCollection::Assign( const GuildBuffsCollection& _guildBuffsCollection )
{
	buffs = _guildBuffsCollection.buffs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroBonusBase::HeroBonusBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroBonusBase::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GuildShopItemBonus*)this );
	saver.Add( 2, &heroes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroBonusBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroBonusBase* parentPtr = (HeroBonusBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroBonusBase::SerializeSelf( IXmlSaver &saver )
{
	GuildShopItemBonus::SerializeSelf( saver );
	saver.Add( "heroes", &heroes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroBonusBase::Assign( const HeroBonusBase& _heroBonusBase )
{
	heroes = _heroBonusBase.heroes;
	propertyTooltip = _heroBonusBase.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionBonus::SessionBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (HeroBonusBase*)this );
	saver.Add( 2, &gameSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionBonus* parentPtr = (SessionBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionBonus::SerializeSelf( IXmlSaver &saver )
{
	HeroBonusBase::SerializeSelf( saver );
	saver.Add( "gameSettings", &gameSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionBonus::Assign( const SessionBonus& _sessionBonus )
{
	gameSettings.maps = _sessionBonus.gameSettings.maps;
	gameSettings.sessionType = _sessionBonus.gameSettings.sessionType;
	heroes = _sessionBonus.heroes;
	propertyTooltip = _sessionBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionValueBonus::SessionValueBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionValueBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionBonus*)this );
	saver.Add( 2, &modifiers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionValueBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionValueBonus* parentPtr = (SessionValueBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionValueBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionBonus::SerializeSelf( saver );
	saver.Add( "modifiers", &modifiers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionValueBonus::Assign( const SessionValueBonus& _sessionValueBonus )
{
	modifiers.additiveValue = _sessionValueBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _sessionValueBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _sessionValueBonus.gameSettings.maps;
	gameSettings.sessionType = _sessionValueBonus.gameSettings.sessionType;
	heroes = _sessionValueBonus.heroes;
	propertyTooltip = _sessionValueBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroEnergyBonus::HeroEnergyBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroEnergyBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroEnergyBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroEnergyBonus* parentPtr = (HeroEnergyBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroEnergyBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroEnergyBonus::Assign( const HeroEnergyBonus& _heroEnergyBonus )
{
	modifiers.additiveValue = _heroEnergyBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _heroEnergyBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _heroEnergyBonus.gameSettings.maps;
	gameSettings.sessionType = _heroEnergyBonus.gameSettings.sessionType;
	heroes = _heroEnergyBonus.heroes;
	propertyTooltip = _heroEnergyBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroExperienceBonus::HeroExperienceBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroExperienceBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroExperienceBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroExperienceBonus* parentPtr = (HeroExperienceBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroExperienceBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroExperienceBonus::Assign( const HeroExperienceBonus& _heroExperienceBonus )
{
	modifiers.additiveValue = _heroExperienceBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _heroExperienceBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _heroExperienceBonus.gameSettings.maps;
	gameSettings.sessionType = _heroExperienceBonus.gameSettings.sessionType;
	heroes = _heroExperienceBonus.heroes;
	propertyTooltip = _heroExperienceBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildWarEventPass::GuildWarEventPass()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildWarEventPass::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionBonus*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildWarEventPass::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildWarEventPass* parentPtr = (GuildWarEventPass*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildWarEventPass::SerializeSelf( IXmlSaver &saver )
{
	SessionBonus::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildWarEventPass::Assign( const GuildWarEventPass& _guildWarEventPass )
{
	gameSettings.maps = _guildWarEventPass.gameSettings.maps;
	gameSettings.sessionType = _guildWarEventPass.gameSettings.sessionType;
	heroes = _guildWarEventPass.heroes;
	propertyTooltip = _guildWarEventPass.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionResourceBonus::SessionResourceBonus() :
		resource( RESOURCETYPE_SILVER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionResourceBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &resource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionResourceBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionResourceBonus* parentPtr = (SessionResourceBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionResourceBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
	saver.Add( "resource", &resource );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionResourceBonus::Assign( const SessionResourceBonus& _sessionResourceBonus )
{
	resource = _sessionResourceBonus.resource;
	modifiers.additiveValue = _sessionResourceBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _sessionResourceBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _sessionResourceBonus.gameSettings.maps;
	gameSettings.sessionType = _sessionResourceBonus.gameSettings.sessionType;
	heroes = _sessionResourceBonus.heroes;
	propertyTooltip = _sessionResourceBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SiegePointsBonus::SiegePointsBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SiegePointsBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SiegePointsBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SiegePointsBonus* parentPtr = (SiegePointsBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SiegePointsBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SiegePointsBonus::Assign( const SiegePointsBonus& _siegePointsBonus )
{
	modifiers.additiveValue = _siegePointsBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _siegePointsBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _siegePointsBonus.gameSettings.maps;
	gameSettings.sessionType = _siegePointsBonus.gameSettings.sessionType;
	heroes = _siegePointsBonus.heroes;
	propertyTooltip = _siegePointsBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatChangeBonus::StatChangeBonus() :
		toggle( EStatBufToggle( 0 ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatChangeBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionBonus*)this );
	saver.Add( 2, &statBonuses );
	saver.Add( 3, &excludedBufs );
	saver.Add( 4, &toggle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatChangeBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatChangeBonus* parentPtr = (StatChangeBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatChangeBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionBonus::SerializeSelf( saver );
	saver.Add( "statBonuses", &statBonuses );
	saver.Add( "excludedBufs", &excludedBufs );
	saver.Add( "toggle", &toggle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatChangeBonus::Assign( const StatChangeBonus& _statChangeBonus )
{
	statBonuses = _statChangeBonus.statBonuses;
	excludedBufs = _statChangeBonus.excludedBufs;
	toggle = _statChangeBonus.toggle;
	gameSettings.maps = _statChangeBonus.gameSettings.maps;
	gameSettings.sessionType = _statChangeBonus.gameSettings.sessionType;
	heroes = _statChangeBonus.heroes;
	propertyTooltip = _statChangeBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TargetHeroes::TargetHeroes()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetHeroes::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetHeroes::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TargetHeroes* parentPtr = (TargetHeroes*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetHeroes::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "heroes", &heroes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetHeroes::Assign( const TargetHeroes& _targetHeroes )
{
	heroes = _targetHeroes.heroes;
}
}; // namespace NDb
