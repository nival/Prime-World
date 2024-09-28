// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBServer.auto.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Spell );
BASIC_REGISTER_DBRESOURCE( GuildBonus );
REGISTER_DBRESOURCE( AdvMapDescription );
REGISTER_DBRESOURCE( AdvMapSettings );
REGISTER_DBRESOURCE( AILogicParameters );
REGISTER_DBRESOURCE( GameObject );
REGISTER_DBRESOURCE( BuyServicesContainer );
BASIC_REGISTER_DBRESOURCE( GuildShopItemBonus );
BASIC_REGISTER_DBRESOURCE( RollItem );
REGISTER_DBRESOURCE( ClanWarsSettings );
REGISTER_DBRESOURCE( ContainersBySpecialPoints );
REGISTER_DBRESOURCE( SingleStateObject );
REGISTER_DBRESOURCE( CustomFlag );
REGISTER_DBRESOURCE( DefaultFormulas );
REGISTER_DBRESOURCE( FlagRollItem );
REGISTER_DBRESOURCE( Unit );
REGISTER_DBRESOURCE( GameSvcSettings );
REGISTER_DBRESOURCE( GlyphsDB );
REGISTER_DBRESOURCE( GoldRollItem );
REGISTER_DBRESOURCE( AdditionHeroExpBonus );
REGISTER_DBRESOURCE( GuildBuff );
REGISTER_DBRESOURCE( GuildBuffsCollection );
REGISTER_DBRESOURCE( GuildLevels );
REGISTER_DBRESOURCE( GuildResourceBonus );
REGISTER_DBRESOURCE( HeroBonusBase );
REGISTER_DBRESOURCE( SessionBonus );
REGISTER_DBRESOURCE( Creature );
REGISTER_DBRESOURCE( SessionValueBonus );
REGISTER_DBRESOURCE( HeroEnergyBonus );
REGISTER_DBRESOURCE( HeroesDB );
REGISTER_DBRESOURCE( HeroesLevelUps );
REGISTER_DBRESOURCE( HeroExperienceBonus );
REGISTER_DBRESOURCE( HeroRanks );
REGISTER_DBRESOURCE( HeroRollItem );
REGISTER_DBRESOURCE( HeroSkin );
REGISTER_DBRESOURCE( ImpulsiveBuffsContainer );
REGISTER_DBRESOURCE( MapList );
REGISTER_DBRESOURCE( MapMMakingSettings );
REGISTER_DBRESOURCE( MarketingEventRollItem );
REGISTER_DBRESOURCE( ModeRollSettings );
REGISTER_DBRESOURCE( NothingRollItem );
REGISTER_DBRESOURCE( PlayerPointsBonus );
REGISTER_DBRESOURCE( PremiumAccRollItem );
REGISTER_DBRESOURCE( RandomTalentBonus );
REGISTER_DBRESOURCE( RarityTalentListRollItem );
REGISTER_DBRESOURCE( ResourceRollItem );
REGISTER_DBRESOURCE( RollContainer );
REGISTER_DBRESOURCE( RollContainerCostByRank );
REGISTER_DBRESOURCE( RollContainerCountByRank );
REGISTER_DBRESOURCE( ClanWarsRollItem );
REGISTER_DBRESOURCE( RollSettings );
REGISTER_DBRESOURCE( ScoringTable );
REGISTER_DBRESOURCE( SessionAudioRoot );
REGISTER_DBRESOURCE( GuildWarEventPass );
REGISTER_DBRESOURCE( SessionLogicRoot );
REGISTER_DBRESOURCE( SessionMessages );
REGISTER_DBRESOURCE( SessionResourceBonus );
REGISTER_DBRESOURCE( SessionRoot );
REGISTER_DBRESOURCE( SessionTalentsBonus );
REGISTER_DBRESOURCE( SessionUIRoot );
REGISTER_DBRESOURCE( ClanPointsBonus );
REGISTER_DBRESOURCE( SessionVisualRoot );
REGISTER_DBRESOURCE( SiegePointsBonus );
REGISTER_DBRESOURCE( BaseHero );
REGISTER_DBRESOURCE( SkinRollItem );
REGISTER_DBRESOURCE( Ability );
REGISTER_DBRESOURCE( StatChangeBonus );
REGISTER_DBRESOURCE( Talent );
REGISTER_DBRESOURCE( TalentRollItem );
REGISTER_DBRESOURCE( TalentUpgradeEntity );
REGISTER_DBRESOURCE( TalentUpgradeEntityRollItem );
REGISTER_DBRESOURCE( TalentUpgradeProbabilityTable );
REGISTER_DBRESOURCE( TalentUpgradeRollItem );
REGISTER_DBRESOURCE( TargetHeroes );
REGISTER_DBRESOURCE( Hero );
REGISTER_DBRESOURCE( UnitsLogicParameters );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BillingServicesStart value )
{
	switch( value )
	{
		case BILLINGSERVICESSTART_IMPULSES:
			return "Impulses";
		case BILLINGSERVICESSTART_GENERIC:
			return "Generic";
		case BILLINGSERVICESSTART_REWARDS:
			return "Rewards";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BillingServicesStart", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BillingServicesStart StringToEnum_BillingServicesStart( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BillingServicesStart)(NStr::ToInt( value ));
	if ( strcmp( value, "Impulses" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_IMPULSES" ) == 0 )
		return BILLINGSERVICESSTART_IMPULSES;
	if ( strcmp( value, "Generic" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_GENERIC" ) == 0 )
		return BILLINGSERVICESSTART_GENERIC;
	if ( strcmp( value, "Rewards" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_REWARDS" ) == 0 )
		return BILLINGSERVICESSTART_REWARDS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BillingServicesStart", value ) );
	return BILLINGSERVICESSTART_IMPULSES;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ClanWarsRollItemType value )
{
	switch( value )
	{
		case CLANWARSROLLITEMTYPE_CLANRATING:
			return "ClanRating";
		case CLANWARSROLLITEMTYPE_PLAYERRATING:
			return "PlayerRating";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ClanWarsRollItemType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ClanWarsRollItemType StringToEnum_ClanWarsRollItemType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ClanWarsRollItemType)(NStr::ToInt( value ));
	if ( strcmp( value, "ClanRating" ) == 0 || strcmp( value, "CLANWARSROLLITEMTYPE_CLANRATING" ) == 0 )
		return CLANWARSROLLITEMTYPE_CLANRATING;
	if ( strcmp( value, "PlayerRating" ) == 0 || strcmp( value, "CLANWARSROLLITEMTYPE_PLAYERRATING" ) == 0 )
		return CLANWARSROLLITEMTYPE_PLAYERRATING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ClanWarsRollItemType", value ) );
	return CLANWARSROLLITEMTYPE_CLANRATING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBotRollMode value )
{
	switch( value )
	{
		case BOTROLLMODE_ENABLED:
			return "Enabled";
		case BOTROLLMODE_DISABLED:
			return "Disabled";
		case BOTROLLMODE_DISABLEDASENEMY:
			return "DisabledAsEnemy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBotRollMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBotRollMode StringToEnum_EBotRollMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBotRollMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Enabled" ) == 0 || strcmp( value, "BOTROLLMODE_ENABLED" ) == 0 )
		return BOTROLLMODE_ENABLED;
	if ( strcmp( value, "Disabled" ) == 0 || strcmp( value, "BOTROLLMODE_DISABLED" ) == 0 )
		return BOTROLLMODE_DISABLED;
	if ( strcmp( value, "DisabledAsEnemy" ) == 0 || strcmp( value, "BOTROLLMODE_DISABLEDASENEMY" ) == 0 )
		return BOTROLLMODE_DISABLEDASENEMY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBotRollMode", value ) );
	return BOTROLLMODE_ENABLED;
}
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
const char *EnumToString( const EFaction value )
{
	switch( value )
	{
		case FACTION_NEUTRAL:
			return "Neutral";
		case FACTION_FREEZE:
			return "Freeze";
		case FACTION_BURN:
			return "Burn";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFaction", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFaction StringToEnum_EFaction( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFaction)(NStr::ToInt( value ));
	if ( strcmp( value, "Neutral" ) == 0 || strcmp( value, "FACTION_NEUTRAL" ) == 0 )
		return FACTION_NEUTRAL;
	if ( strcmp( value, "Freeze" ) == 0 || strcmp( value, "FACTION_FREEZE" ) == 0 )
		return FACTION_FREEZE;
	if ( strcmp( value, "Burn" ) == 0 || strcmp( value, "FACTION_BURN" ) == 0 )
		return FACTION_BURN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFaction", value ) );
	return FACTION_NEUTRAL;
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
const char *EnumToString( const EGender value )
{
	switch( value )
	{
		case GENDER_MALE:
			return "Male";
		case GENDER_FEMALE:
			return "Female";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EGender", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGender StringToEnum_EGender( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGender)(NStr::ToInt( value ));
	if ( strcmp( value, "Male" ) == 0 || strcmp( value, "GENDER_MALE" ) == 0 )
		return GENDER_MALE;
	if ( strcmp( value, "Female" ) == 0 || strcmp( value, "GENDER_FEMALE" ) == 0 )
		return GENDER_FEMALE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGender", value ) );
	return GENDER_MALE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EHeroRaces value )
{
	switch( value )
	{
		case HERORACES_ZERO:
			return "Zero";
		case HERORACES_A:
			return "A";
		case HERORACES_B:
			return "B";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EHeroRaces StringToEnum_EHeroRaces( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EHeroRaces)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "HERORACES_ZERO" ) == 0 )
		return HERORACES_ZERO;
	if ( strcmp( value, "A" ) == 0 || strcmp( value, "HERORACES_A" ) == 0 )
		return HERORACES_A;
	if ( strcmp( value, "B" ) == 0 || strcmp( value, "HERORACES_B" ) == 0 )
		return HERORACES_B;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EHeroRaces", value ) );
	return HERORACES_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMapType value )
{
	switch( value )
	{
		case MAPTYPE_NONE:
			return "None";
		case MAPTYPE_PVP:
			return "PvP";
		case MAPTYPE_CTE:
			return "CTE";
		case MAPTYPE_TRAINING:
			return "Training";
		case MAPTYPE_TUTORIAL:
			return "Tutorial";
		case MAPTYPE_SERIES:
			return "Series";
		case MAPTYPE_COOPERATIVE:
			return "Cooperative";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMapType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMapType StringToEnum_EMapType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMapType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MAPTYPE_NONE" ) == 0 )
		return MAPTYPE_NONE;
	if ( strcmp( value, "PvP" ) == 0 || strcmp( value, "MAPTYPE_PVP" ) == 0 )
		return MAPTYPE_PVP;
	if ( strcmp( value, "CTE" ) == 0 || strcmp( value, "MAPTYPE_CTE" ) == 0 )
		return MAPTYPE_CTE;
	if ( strcmp( value, "Training" ) == 0 || strcmp( value, "MAPTYPE_TRAINING" ) == 0 )
		return MAPTYPE_TRAINING;
	if ( strcmp( value, "Tutorial" ) == 0 || strcmp( value, "MAPTYPE_TUTORIAL" ) == 0 )
		return MAPTYPE_TUTORIAL;
	if ( strcmp( value, "Series" ) == 0 || strcmp( value, "MAPTYPE_SERIES" ) == 0 )
		return MAPTYPE_SERIES;
	if ( strcmp( value, "Cooperative" ) == 0 || strcmp( value, "MAPTYPE_COOPERATIVE" ) == 0 )
		return MAPTYPE_COOPERATIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMapType", value ) );
	return MAPTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EResourceType value )
{
	switch( value )
	{
		case RESOURCETYPE_SILVER:
			return "Silver";
		case RESOURCETYPE_CRYSTAL:
			return "Crystal";
		case RESOURCETYPE_RESOURCE1:
			return "Resource1";
		case RESOURCETYPE_RESOURCE2:
			return "Resource2";
		case RESOURCETYPE_RESOURCE3:
			return "Resource3";
		case RESOURCETYPE_REDCRYSTAL:
			return "RedCrystal";
		case RESOURCETYPE_SHARD:
			return "Shard";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EResourceType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EResourceType StringToEnum_EResourceType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EResourceType)(NStr::ToInt( value ));
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "RESOURCETYPE_SILVER" ) == 0 )
		return RESOURCETYPE_SILVER;
	if ( strcmp( value, "Crystal" ) == 0 || strcmp( value, "RESOURCETYPE_CRYSTAL" ) == 0 )
		return RESOURCETYPE_CRYSTAL;
	if ( strcmp( value, "Resource1" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE1" ) == 0 )
		return RESOURCETYPE_RESOURCE1;
	if ( strcmp( value, "Resource2" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE2" ) == 0 )
		return RESOURCETYPE_RESOURCE2;
	if ( strcmp( value, "Resource3" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE3" ) == 0 )
		return RESOURCETYPE_RESOURCE3;
	if ( strcmp( value, "RedCrystal" ) == 0 || strcmp( value, "RESOURCETYPE_REDCRYSTAL" ) == 0 )
		return RESOURCETYPE_REDCRYSTAL;
	if ( strcmp( value, "Shard" ) == 0 || strcmp( value, "RESOURCETYPE_SHARD" ) == 0 )
		return RESOURCETYPE_SHARD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EResourceType", value ) );
	return RESOURCETYPE_SILVER;
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
const char *EnumToString( const EStat value )
{
	switch( value )
	{
		case STAT_LIFE:
			return "Life";
		case STAT_ENERGY:
			return "Energy";
		case STAT_RANGE:
			return "Range";
		case STAT_MOVESPEED:
			return "MoveSpeed";
		case STAT_ATTACKSPEED:
			return "AttackSpeed";
		case STAT_CRITICALCHANCE:
			return "CriticalChance";
		case STAT_CRITICALMULTIPLIER:
			return "CriticalMultiplier";
		case STAT_LIFEDRAIN:
			return "LifeDrain";
		case STAT_ENERGYDRAIN:
			return "EnergyDrain";
		case STAT_EVASION:
			return "Evasion";
		case STAT_LIFEREGENERATION:
			return "LifeRegeneration";
		case STAT_LIFEREGENERATIONABSOLUTE:
			return "LifeRegenerationAbsolute";
		case STAT_ENERGYREGENERATION:
			return "EnergyRegeneration";
		case STAT_ENERGYREGENERATIONABSOLUTE:
			return "EnergyRegenerationAbsolute";
		case STAT_VISIBILITYRANGE:
			return "VisibilityRange";
		case STAT_STRENGTH:
			return "Strength";
		case STAT_INTELLECT:
			return "Intellect";
		case STAT_DEXTERITY:
			return "Dexterity";
		case STAT_BASEATTACK:
			return "BaseAttack";
		case STAT_STAMINA:
			return "Stamina";
		case STAT_WILL:
			return "Will";
		case STAT_VIRTUALSTAT:
			return "VirtualStat";
		case STAT_CRITCHANCEBONUS:
			return "CritChanceBonus";
		case STAT_ENERGYDAMAGEDECREASE:
			return "EnergyDamageDecrease";
		case STAT_MATERIALDAMAGEDECREASE:
			return "MaterialDamageDecrease";
		case STAT_MISSCHANCE:
			return "MissChance";
		case STAT_LEVEL:
			return "Level";
		case STAT_NAFTAFORKILL:
			return "NaftaForKill";
		case STAT_NAFTAFORASSIST:
			return "NaftaForAssist";
		case STAT_NAFTASPECFORKILL:
			return "NaftaSpecForKill";
		case STAT_TEAMNAFTAFORKILL:
			return "TeamNaftaForKill";
		case STAT_TEAMNAFTAFORPRESENCE:
			return "TeamNaftaForPresence";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStat", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStat StringToEnum_EStat( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStat)(NStr::ToInt( value ));
	if ( strcmp( value, "Life" ) == 0 || strcmp( value, "STAT_LIFE" ) == 0 )
		return STAT_LIFE;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "STAT_ENERGY" ) == 0 )
		return STAT_ENERGY;
	if ( strcmp( value, "Range" ) == 0 || strcmp( value, "STAT_RANGE" ) == 0 )
		return STAT_RANGE;
	if ( strcmp( value, "MoveSpeed" ) == 0 || strcmp( value, "STAT_MOVESPEED" ) == 0 )
		return STAT_MOVESPEED;
	if ( strcmp( value, "AttackSpeed" ) == 0 || strcmp( value, "STAT_ATTACKSPEED" ) == 0 )
		return STAT_ATTACKSPEED;
	if ( strcmp( value, "CriticalChance" ) == 0 || strcmp( value, "STAT_CRITICALCHANCE" ) == 0 )
		return STAT_CRITICALCHANCE;
	if ( strcmp( value, "CriticalMultiplier" ) == 0 || strcmp( value, "STAT_CRITICALMULTIPLIER" ) == 0 )
		return STAT_CRITICALMULTIPLIER;
	if ( strcmp( value, "LifeDrain" ) == 0 || strcmp( value, "STAT_LIFEDRAIN" ) == 0 )
		return STAT_LIFEDRAIN;
	if ( strcmp( value, "EnergyDrain" ) == 0 || strcmp( value, "STAT_ENERGYDRAIN" ) == 0 )
		return STAT_ENERGYDRAIN;
	if ( strcmp( value, "Evasion" ) == 0 || strcmp( value, "STAT_EVASION" ) == 0 )
		return STAT_EVASION;
	if ( strcmp( value, "LifeRegeneration" ) == 0 || strcmp( value, "STAT_LIFEREGENERATION" ) == 0 )
		return STAT_LIFEREGENERATION;
	if ( strcmp( value, "LifeRegenerationAbsolute" ) == 0 || strcmp( value, "STAT_LIFEREGENERATIONABSOLUTE" ) == 0 )
		return STAT_LIFEREGENERATIONABSOLUTE;
	if ( strcmp( value, "EnergyRegeneration" ) == 0 || strcmp( value, "STAT_ENERGYREGENERATION" ) == 0 )
		return STAT_ENERGYREGENERATION;
	if ( strcmp( value, "EnergyRegenerationAbsolute" ) == 0 || strcmp( value, "STAT_ENERGYREGENERATIONABSOLUTE" ) == 0 )
		return STAT_ENERGYREGENERATIONABSOLUTE;
	if ( strcmp( value, "VisibilityRange" ) == 0 || strcmp( value, "STAT_VISIBILITYRANGE" ) == 0 )
		return STAT_VISIBILITYRANGE;
	if ( strcmp( value, "Strength" ) == 0 || strcmp( value, "STAT_STRENGTH" ) == 0 )
		return STAT_STRENGTH;
	if ( strcmp( value, "Intellect" ) == 0 || strcmp( value, "STAT_INTELLECT" ) == 0 )
		return STAT_INTELLECT;
	if ( strcmp( value, "Dexterity" ) == 0 || strcmp( value, "STAT_DEXTERITY" ) == 0 )
		return STAT_DEXTERITY;
	if ( strcmp( value, "BaseAttack" ) == 0 || strcmp( value, "STAT_BASEATTACK" ) == 0 )
		return STAT_BASEATTACK;
	if ( strcmp( value, "Stamina" ) == 0 || strcmp( value, "STAT_STAMINA" ) == 0 )
		return STAT_STAMINA;
	if ( strcmp( value, "Will" ) == 0 || strcmp( value, "STAT_WILL" ) == 0 )
		return STAT_WILL;
	if ( strcmp( value, "VirtualStat" ) == 0 || strcmp( value, "STAT_VIRTUALSTAT" ) == 0 )
		return STAT_VIRTUALSTAT;
	if ( strcmp( value, "CritChanceBonus" ) == 0 || strcmp( value, "STAT_CRITCHANCEBONUS" ) == 0 )
		return STAT_CRITCHANCEBONUS;
	if ( strcmp( value, "EnergyDamageDecrease" ) == 0 || strcmp( value, "STAT_ENERGYDAMAGEDECREASE" ) == 0 )
		return STAT_ENERGYDAMAGEDECREASE;
	if ( strcmp( value, "MaterialDamageDecrease" ) == 0 || strcmp( value, "STAT_MATERIALDAMAGEDECREASE" ) == 0 )
		return STAT_MATERIALDAMAGEDECREASE;
	if ( strcmp( value, "MissChance" ) == 0 || strcmp( value, "STAT_MISSCHANCE" ) == 0 )
		return STAT_MISSCHANCE;
	if ( strcmp( value, "Level" ) == 0 || strcmp( value, "STAT_LEVEL" ) == 0 )
		return STAT_LEVEL;
	if ( strcmp( value, "NaftaForKill" ) == 0 || strcmp( value, "STAT_NAFTAFORKILL" ) == 0 )
		return STAT_NAFTAFORKILL;
	if ( strcmp( value, "NaftaForAssist" ) == 0 || strcmp( value, "STAT_NAFTAFORASSIST" ) == 0 )
		return STAT_NAFTAFORASSIST;
	if ( strcmp( value, "NaftaSpecForKill" ) == 0 || strcmp( value, "STAT_NAFTASPECFORKILL" ) == 0 )
		return STAT_NAFTASPECFORKILL;
	if ( strcmp( value, "TeamNaftaForKill" ) == 0 || strcmp( value, "STAT_TEAMNAFTAFORKILL" ) == 0 )
		return STAT_TEAMNAFTAFORKILL;
	if ( strcmp( value, "TeamNaftaForPresence" ) == 0 || strcmp( value, "STAT_TEAMNAFTAFORPRESENCE" ) == 0 )
		return STAT_TEAMNAFTAFORPRESENCE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStat", value ) );
	return STAT_LIFE;
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
const char *EnumToString( const ESweepStage value )
{
	switch( value )
	{
		case SWEEPSTAGE_LOWERLIMIT:
			return "LowerLimit";
		case SWEEPSTAGE_UPPERLIMIT:
			return "UpperLimit";
		case SWEEPSTAGE_WIDENEDLIMITS:
			return "WidenedLimits";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESweepStage", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESweepStage StringToEnum_ESweepStage( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESweepStage)(NStr::ToInt( value ));
	if ( strcmp( value, "LowerLimit" ) == 0 || strcmp( value, "SWEEPSTAGE_LOWERLIMIT" ) == 0 )
		return SWEEPSTAGE_LOWERLIMIT;
	if ( strcmp( value, "UpperLimit" ) == 0 || strcmp( value, "SWEEPSTAGE_UPPERLIMIT" ) == 0 )
		return SWEEPSTAGE_UPPERLIMIT;
	if ( strcmp( value, "WidenedLimits" ) == 0 || strcmp( value, "SWEEPSTAGE_WIDENEDLIMITS" ) == 0 )
		return SWEEPSTAGE_WIDENEDLIMITS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESweepStage", value ) );
	return SWEEPSTAGE_LOWERLIMIT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentRarity value )
{
	switch( value )
	{
		case TALENTRARITY_CLASS:
			return "Class";
		case TALENTRARITY_ORDINARY:
			return "ordinary";
		case TALENTRARITY_GOOD:
			return "good";
		case TALENTRARITY_EXCELLENT:
			return "excellent";
		case TALENTRARITY_MAGNIFICENT:
			return "magnificent";
		case TALENTRARITY_EXCLUSIVE:
			return "exclusive";
		case TALENTRARITY_OUTSTANDING:
			return "outstanding";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalentRarity", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentRarity StringToEnum_ETalentRarity( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentRarity)(NStr::ToInt( value ));
	if ( strcmp( value, "Class" ) == 0 || strcmp( value, "TALENTRARITY_CLASS" ) == 0 )
		return TALENTRARITY_CLASS;
	if ( strcmp( value, "ordinary" ) == 0 || strcmp( value, "TALENTRARITY_ORDINARY" ) == 0 )
		return TALENTRARITY_ORDINARY;
	if ( strcmp( value, "good" ) == 0 || strcmp( value, "TALENTRARITY_GOOD" ) == 0 )
		return TALENTRARITY_GOOD;
	if ( strcmp( value, "excellent" ) == 0 || strcmp( value, "TALENTRARITY_EXCELLENT" ) == 0 )
		return TALENTRARITY_EXCELLENT;
	if ( strcmp( value, "magnificent" ) == 0 || strcmp( value, "TALENTRARITY_MAGNIFICENT" ) == 0 )
		return TALENTRARITY_MAGNIFICENT;
	if ( strcmp( value, "exclusive" ) == 0 || strcmp( value, "TALENTRARITY_EXCLUSIVE" ) == 0 )
		return TALENTRARITY_EXCLUSIVE;
	if ( strcmp( value, "outstanding" ) == 0 || strcmp( value, "TALENTRARITY_OUTSTANDING" ) == 0 )
		return TALENTRARITY_OUTSTANDING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentRarity", value ) );
	return TALENTRARITY_CLASS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentRollGroup value )
{
	switch( value )
	{
		case TALENTROLLGROUP_PVP:
			return "PvP";
		case TALENTROLLGROUP_TRAINING:
			return "Training";
		case TALENTROLLGROUP_CTE:
			return "CTE";
		case TALENTROLLGROUP_PVE:
			return "PvE";
		case TALENTROLLGROUP_CASTLE:
			return "Castle";
		case TALENTROLLGROUP_MIDONLY:
			return "MidOnly";
		case TALENTROLLGROUP_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentRollGroup StringToEnum_ETalentRollGroup( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentRollGroup)(NStr::ToInt( value ));
	if ( strcmp( value, "PvP" ) == 0 || strcmp( value, "TALENTROLLGROUP_PVP" ) == 0 )
		return TALENTROLLGROUP_PVP;
	if ( strcmp( value, "Training" ) == 0 || strcmp( value, "TALENTROLLGROUP_TRAINING" ) == 0 )
		return TALENTROLLGROUP_TRAINING;
	if ( strcmp( value, "CTE" ) == 0 || strcmp( value, "TALENTROLLGROUP_CTE" ) == 0 )
		return TALENTROLLGROUP_CTE;
	if ( strcmp( value, "PvE" ) == 0 || strcmp( value, "TALENTROLLGROUP_PVE" ) == 0 )
		return TALENTROLLGROUP_PVE;
	if ( strcmp( value, "Castle" ) == 0 || strcmp( value, "TALENTROLLGROUP_CASTLE" ) == 0 )
		return TALENTROLLGROUP_CASTLE;
	if ( strcmp( value, "MidOnly" ) == 0 || strcmp( value, "TALENTROLLGROUP_MIDONLY" ) == 0 )
		return TALENTROLLGROUP_MIDONLY;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "TALENTROLLGROUP_ALL" ) == 0 )
		return TALENTROLLGROUP_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentRollGroup", value ) );
	return TALENTROLLGROUP_PVP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const HeroClassEnum value )
{
	switch( value )
	{
		case HEROCLASSENUM_NONE:
			return "None";
		case HEROCLASSENUM_PROTECTOR:
			return "Protector";
		case HEROCLASSENUM_VANGUARD:
			return "Vanguard";
		case HEROCLASSENUM_EXECUTIONER:
			return "Executioner";
		case HEROCLASSENUM_FIGHTER:
			return "Fighter";
		case HEROCLASSENUM_SUPPORT:
			return "Support";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const HeroClassEnum StringToEnum_HeroClassEnum( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (HeroClassEnum)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "HEROCLASSENUM_NONE" ) == 0 )
		return HEROCLASSENUM_NONE;
	if ( strcmp( value, "Protector" ) == 0 || strcmp( value, "HEROCLASSENUM_PROTECTOR" ) == 0 )
		return HEROCLASSENUM_PROTECTOR;
	if ( strcmp( value, "Vanguard" ) == 0 || strcmp( value, "HEROCLASSENUM_VANGUARD" ) == 0 )
		return HEROCLASSENUM_VANGUARD;
	if ( strcmp( value, "Executioner" ) == 0 || strcmp( value, "HEROCLASSENUM_EXECUTIONER" ) == 0 )
		return HEROCLASSENUM_EXECUTIONER;
	if ( strcmp( value, "Fighter" ) == 0 || strcmp( value, "HEROCLASSENUM_FIGHTER" ) == 0 )
		return HEROCLASSENUM_FIGHTER;
	if ( strcmp( value, "Support" ) == 0 || strcmp( value, "HEROCLASSENUM_SUPPORT" ) == 0 )
		return HEROCLASSENUM_SUPPORT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum HeroClassEnum", value ) );
	return HEROCLASSENUM_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MMakingHeroClassEnum value )
{
	switch( value )
	{
		case MMAKINGHEROCLASSENUM_NONE:
			return "None";
		case MMAKINGHEROCLASSENUM_PROTECTOR:
			return "Protector";
		case MMAKINGHEROCLASSENUM_VANGUARD:
			return "Vanguard";
		case MMAKINGHEROCLASSENUM_EXECUTIONER:
			return "Executioner";
		case MMAKINGHEROCLASSENUM_FIGHTER:
			return "Fighter";
		case MMAKINGHEROCLASSENUM_SUPPORT:
			return "Support";
		case MMAKINGHEROCLASSENUM_JUNGLER:
			return "Jungler";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MMakingHeroClassEnum", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MMakingHeroClassEnum StringToEnum_MMakingHeroClassEnum( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MMakingHeroClassEnum)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_NONE" ) == 0 )
		return MMAKINGHEROCLASSENUM_NONE;
	if ( strcmp( value, "Protector" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_PROTECTOR" ) == 0 )
		return MMAKINGHEROCLASSENUM_PROTECTOR;
	if ( strcmp( value, "Vanguard" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_VANGUARD" ) == 0 )
		return MMAKINGHEROCLASSENUM_VANGUARD;
	if ( strcmp( value, "Executioner" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_EXECUTIONER" ) == 0 )
		return MMAKINGHEROCLASSENUM_EXECUTIONER;
	if ( strcmp( value, "Fighter" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_FIGHTER" ) == 0 )
		return MMAKINGHEROCLASSENUM_FIGHTER;
	if ( strcmp( value, "Support" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_SUPPORT" ) == 0 )
		return MMAKINGHEROCLASSENUM_SUPPORT;
	if ( strcmp( value, "Jungler" ) == 0 || strcmp( value, "MMAKINGHEROCLASSENUM_JUNGLER" ) == 0 )
		return MMAKINGHEROCLASSENUM_JUNGLER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MMakingHeroClassEnum", value ) );
	return MMAKINGHEROCLASSENUM_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ResourceRollConstraint value )
{
	switch( value )
	{
		case RESOURCEROLLCONSTRAINT_SILVER:
			return "Silver";
		case RESOURCEROLLCONSTRAINT_RESOURCE1:
			return "Resource1";
		case RESOURCEROLLCONSTRAINT_RESOURCE2:
			return "Resource2";
		case RESOURCEROLLCONSTRAINT_RESOURCE3:
			return "Resource3";
		case RESOURCEROLLCONSTRAINT_PEARL:
			return "Pearl";
		case RESOURCEROLLCONSTRAINT_REDPEARL:
			return "RedPearl";
		case RESOURCEROLLCONSTRAINT_SHARD:
			return "Shard";
		case RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY:
			return "CustomCurrency";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ResourceRollConstraint", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ResourceRollConstraint StringToEnum_ResourceRollConstraint( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ResourceRollConstraint)(NStr::ToInt( value ));
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_SILVER" ) == 0 )
		return RESOURCEROLLCONSTRAINT_SILVER;
	if ( strcmp( value, "Resource1" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE1" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE1;
	if ( strcmp( value, "Resource2" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE2" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE2;
	if ( strcmp( value, "Resource3" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE3" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE3;
	if ( strcmp( value, "Pearl" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_PEARL" ) == 0 )
		return RESOURCEROLLCONSTRAINT_PEARL;
	if ( strcmp( value, "RedPearl" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_REDPEARL" ) == 0 )
		return RESOURCEROLLCONSTRAINT_REDPEARL;
	if ( strcmp( value, "Shard" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_SHARD" ) == 0 )
		return RESOURCEROLLCONSTRAINT_SHARD;
	if ( strcmp( value, "CustomCurrency" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY" ) == 0 )
		return RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ResourceRollConstraint", value ) );
	return RESOURCEROLLCONSTRAINT_SILVER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TalentUpgradeEntityType value )
{
	switch( value )
	{
		case TALENTUPGRADEENTITYTYPE_RUNE:
			return "Rune";
		case TALENTUPGRADEENTITYTYPE_CATALYST:
			return "Catalyst";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TalentUpgradeEntityType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TalentUpgradeEntityType StringToEnum_TalentUpgradeEntityType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TalentUpgradeEntityType)(NStr::ToInt( value ));
	if ( strcmp( value, "Rune" ) == 0 || strcmp( value, "TALENTUPGRADEENTITYTYPE_RUNE" ) == 0 )
		return TALENTUPGRADEENTITYTYPE_RUNE;
	if ( strcmp( value, "Catalyst" ) == 0 || strcmp( value, "TALENTUPGRADEENTITYTYPE_CATALYST" ) == 0 )
		return TALENTUPGRADEENTITYTYPE_CATALYST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TalentUpgradeEntityType", value ) );
	return TALENTUPGRADEENTITYTYPE_RUNE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ZZRewards value )
{
	switch( value )
	{
		case ZZREWARDS_VICTORY:
			return "Victory";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ZZRewards", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ZZRewards StringToEnum_ZZRewards( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ZZRewards)(NStr::ToInt( value ));
	if ( strcmp( value, "Victory" ) == 0 || strcmp( value, "ZZREWARDS_VICTORY" ) == 0 )
		return ZZREWARDS_VICTORY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ZZRewards", value ) );
	return ZZREWARDS_VICTORY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseModifierFromQuantity::BaseModifierFromQuantity() :
		quantity( 0.0f )
	, percent( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseModifierFromQuantity::operator&( IBinSaver &saver )
{
	saver.Add( 2, &quantity );
	saver.Add( 3, &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseModifierFromQuantity::operator&( IXmlSaver &saver )
{
	saver.Add( "quantity", &quantity );
	saver.Add( "percent", &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BuyServiceCost::BuyServiceCost() :
		goldCost( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServiceCost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &goldCost );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServiceCost::operator&( IXmlSaver &saver )
{
	saver.Add( "goldCost", &goldCost );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CountryFlag::CountryFlag()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountryFlag::operator&( IBinSaver &saver )
{
	saver.Add( 2, &countryCode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountryFlag::operator&( IXmlSaver &saver )
{
	saver.Add( "countryCode", &countryCode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EstimFunctionWeights::EstimFunctionWeights() :
		ladiesNumber( 1.0f )
	, genderPairs( 1.0f )
	, heroes( 1.0f )
	, ratingSpan( 1.0f )
	, ratingPatternDelta( 1.0f )
	, ratingTeamAvgDelta( 1.0f )
	, forceSpan( 1.0f )
	, heroClassesDifference( 1.0f )
	, heroClassesOptimum( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EstimFunctionWeights::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ladiesNumber );
	saver.Add( 3, &genderPairs );
	saver.Add( 4, &heroes );
	saver.Add( 5, &ratingSpan );
	saver.Add( 6, &ratingPatternDelta );
	saver.Add( 7, &ratingTeamAvgDelta );
	saver.Add( 8, &forceSpan );
	saver.Add( 9, &heroClassesDifference );
	saver.Add( 10, &heroClassesOptimum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EstimFunctionWeights::operator&( IXmlSaver &saver )
{
	saver.Add( "ladiesNumber", &ladiesNumber );
	saver.Add( "genderPairs", &genderPairs );
	saver.Add( "heroes", &heroes );
	saver.Add( "ratingSpan", &ratingSpan );
	saver.Add( "ratingPatternDelta", &ratingPatternDelta );
	saver.Add( "ratingTeamAvgDelta", &ratingTeamAvgDelta );
	saver.Add( "forceSpan", &forceSpan );
	saver.Add( "heroClassesDifference", &heroClassesDifference );
	saver.Add( "heroClassesOptimum", &heroClassesOptimum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FullPartyRatingModifier::FullPartyRatingModifier() :
		minRating( 0 )
	, ratingBonus( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullPartyRatingModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minRating );
	saver.Add( 3, &ratingBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullPartyRatingModifier::operator&( IXmlSaver &saver )
{
	saver.Add( "minRating", &minRating );
	saver.Add( "ratingBonus", &ratingBonus );

	return 0;
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
GuildLevel::GuildLevel() :
		requiredExp( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevel::operator&( IBinSaver &saver )
{
	saver.Add( 2, &requiredExp );
	saver.Add( 3, &title );
	saver.Add( 4, &tooltip );
	saver.Add( 5, &Bonuses );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevel::operator&( IXmlSaver &saver )
{
	saver.Add( "requiredExp", &requiredExp );
	saver.Add( "title", &title );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "Bonuses", &Bonuses );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LerpDataItem::LerpDataItem() :
		x( 0.0f )
	, y( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LerpDataItem::operator&( IBinSaver &saver )
{
	saver.Add( 2, &x );
	saver.Add( 3, &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LerpDataItem::operator&( IXmlSaver &saver )
{
	saver.Add( "x", &x );
	saver.Add( "y", &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingHeroClass::MMakingHeroClass() :
		minEfficiency( 1.0f )
	, maxEfficiency( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingHeroClass::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minEfficiency );
	saver.Add( 3, &maxEfficiency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingHeroClass::operator&( IXmlSaver &saver )
{
	saver.Add( "minEfficiency", &minEfficiency );
	saver.Add( "maxEfficiency", &maxEfficiency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingLocationPingSettings::MMakingLocationPingSettings() :
		nicePingThreshold( 40 )
	, pingScaleMinFactor( 2.0f )
	, worstPingWaitTimePenalty( 180 )
	, goodEnoughPingFactor( 0.2f )
	, ratingThreshold( 1800 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLocationPingSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nicePingThreshold );
	saver.Add( 3, &pingScaleMinFactor );
	saver.Add( 4, &worstPingWaitTimePenalty );
	saver.Add( 5, &goodEnoughPingFactor );
	saver.Add( 6, &ratingThreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLocationPingSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "nicePingThreshold", &nicePingThreshold );
	saver.Add( "pingScaleMinFactor", &pingScaleMinFactor );
	saver.Add( "worstPingWaitTimePenalty", &worstPingWaitTimePenalty );
	saver.Add( "goodEnoughPingFactor", &goodEnoughPingFactor );
	saver.Add( "ratingThreshold", &ratingThreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingLoseStreakCorrection::MMakingLoseStreakCorrection() :
		minStreak( 2 )
	, forcePenalty( 5.0f )
	, ratingPenalty( 100.0f )
	, firstCaseThreshold( 2 )
	, firstCasePenalty( 0.25f )
	, secondCaseThreshold( 3 )
	, secondCasePenalty( 0.5f )
	, thirdCaseThreshold( 5 )
	, thirdCasePenalty( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLoseStreakCorrection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minStreak );
	saver.Add( 3, &forcePenalty );
	saver.Add( 4, &ratingPenalty );
	saver.Add( 5, &firstCaseThreshold );
	saver.Add( 6, &firstCasePenalty );
	saver.Add( 7, &secondCaseThreshold );
	saver.Add( 8, &secondCasePenalty );
	saver.Add( 9, &thirdCaseThreshold );
	saver.Add( 10, &thirdCasePenalty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLoseStreakCorrection::operator&( IXmlSaver &saver )
{
	saver.Add( "minStreak", &minStreak );
	saver.Add( "forcePenalty", &forcePenalty );
	saver.Add( "ratingPenalty", &ratingPenalty );
	saver.Add( "firstCaseThreshold", &firstCaseThreshold );
	saver.Add( "firstCasePenalty", &firstCasePenalty );
	saver.Add( "secondCaseThreshold", &secondCaseThreshold );
	saver.Add( "secondCasePenalty", &secondCasePenalty );
	saver.Add( "thirdCaseThreshold", &thirdCaseThreshold );
	saver.Add( "thirdCasePenalty", &thirdCasePenalty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingRank::MMakingRank() :
		lowRating( 0.0f )
	, mergeWithNextRank( false )
	, mergeRanksCount( 0 )
	, useForceMM( false )
	, usePlayerRatingMM( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lowRating );
	saver.Add( 3, &mergeWithNextRank );
	saver.Add( 4, &mergeRanksCount );
	saver.Add( 5, &debugName );
	saver.Add( 6, &useForceMM );
	saver.Add( 7, &usePlayerRatingMM );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingRank::operator&( IXmlSaver &saver )
{
	saver.Add( "lowRating", &lowRating );
	saver.Add( "mergeWithNextRank", &mergeWithNextRank );
	saver.Add( "mergeRanksCount", &mergeRanksCount );
	saver.Add( "debugName", &debugName );
	saver.Add( "useForceMM", &useForceMM );
	saver.Add( "usePlayerRatingMM", &usePlayerRatingMM );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingScale::MMakingScale() :
		low( 100 )
	, high( 1000 )
	, step( 20 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingScale::operator&( IBinSaver &saver )
{
	saver.Add( 2, &low );
	saver.Add( 3, &high );
	saver.Add( 4, &step );
	saver.Add( 5, &diffLow );
	saver.Add( 6, &diffHigh );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingScale::operator&( IXmlSaver &saver )
{
	saver.Add( "low", &low );
	saver.Add( "high", &high );
	saver.Add( "step", &step );
	saver.Add( "diffLow", &diffLow );
	saver.Add( "diffHigh", &diffHigh );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingWaitVsProbability::MMakingWaitVsProbability() :
		startingWaitTime( 15.0f )
	, endingWaitTime( 180.0f )
	, startingProbabilityWeight( 100 )
	, endingProbabilityWeight( 300 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingWaitVsProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startingWaitTime );
	saver.Add( 3, &endingWaitTime );
	saver.Add( 4, &startingProbabilityWeight );
	saver.Add( 5, &endingProbabilityWeight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingWaitVsProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "startingWaitTime", &startingWaitTime );
	saver.Add( "endingWaitTime", &endingWaitTime );
	saver.Add( "startingProbabilityWeight", &startingProbabilityWeight );
	saver.Add( "endingProbabilityWeight", &endingProbabilityWeight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointsToContainers::PointsToContainers() :
		specialPoints( 0 )
	, containers( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointsToContainers::operator&( IBinSaver &saver )
{
	saver.Add( 2, &specialPoints );
	saver.Add( 3, &containers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointsToContainers::operator&( IXmlSaver &saver )
{
	saver.Add( "specialPoints", &specialPoints );
	saver.Add( "containers", &containers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Rank::Rank() :
		rating( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Rank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Rank::operator&( IXmlSaver &saver )
{
	saver.Add( "rating", &rating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RatingModifier::RatingModifier() :
		minValue( 0 )
	, maxValue( 0 )
	, winModifier( 0.0f )
	, looseModifier( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RatingModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minValue );
	saver.Add( 3, &maxValue );
	saver.Add( 4, &winModifier );
	saver.Add( 5, &looseModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RatingModifier::operator&( IXmlSaver &saver )
{
	saver.Add( "minValue", &minValue );
	saver.Add( "maxValue", &maxValue );
	saver.Add( "winModifier", &winModifier );
	saver.Add( "looseModifier", &looseModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionData::RecessionData() :
		isWaitingTimePremium( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &isWaitingTimePremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionData::operator&( IXmlSaver &saver )
{
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "isWaitingTimePremium", &isWaitingTimePremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionFullPartyTableForForceMM::RecessionFullPartyTableForForceMM()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionFullPartyTableForForceMM::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &recessionPremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionFullPartyTableForForceMM::operator&( IXmlSaver &saver )
{
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "recessionPremium", &recessionPremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionTableForPlayerRatingMM::RecessionTableForPlayerRatingMM() :
		recessionSideDiff( 0.0f )
	, recessionPremiumTimeThreshold( 0.0f )
	, recessionMaxPlayerRating( 2000 )
	, recessionMinPlayerRating( 1200 )
{
	recessionTable.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionTableForPlayerRatingMM::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &recessionSideDiff );
	saver.Add( 4, &recessionPremiumTable );
	saver.Add( 5, &recessionPremiumTimeThreshold );
	saver.Add( 6, &recessionMaxPlayerRating );
	saver.Add( 7, &recessionMinPlayerRating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionTableForPlayerRatingMM::operator&( IXmlSaver &saver )
{
	recessionTable.resize( 3 );
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "recessionSideDiff", &recessionSideDiff );
	saver.Add( "recessionPremiumTable", &recessionPremiumTable );
	saver.Add( "recessionPremiumTimeThreshold", &recessionPremiumTimeThreshold );
	saver.Add( "recessionMaxPlayerRating", &recessionMaxPlayerRating );
	saver.Add( "recessionMinPlayerRating", &recessionMinPlayerRating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollItemProbability::RollItemProbability() :
		probability( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItemProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &probability );
	saver.Add( 3, &item );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItemProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "probability", &probability );
	saver.Add( "item", &item );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollLevelInfo::RollLevelInfo() :
		level( 0 )
	, count( 0 )
	, deviation( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollLevelInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &level );
	saver.Add( 3, &count );
	saver.Add( 4, &deviation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollLevelInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "level", &level );
	saver.Add( "count", &count );
	saver.Add( "deviation", &deviation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleRollSettings::SingleRollSettings() :
		allowedRollGroups( TALENTROLLGROUP_ALL )
	, version( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleRollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rollContainer );
	saver.Add( 3, &allowedRollGroups );
	saver.Add( 4, &version );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleRollSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "rollContainer", &rollContainer );
	saver.Add( "allowedRollGroups", &allowedRollGroups );
	saver.Add( "version", &version );

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
TalentUpgradeProbability::TalentUpgradeProbability() :
		probability( 0.0f )
	, points( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &probability );
	saver.Add( 3, &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "probability", &probability );
	saver.Add( "points", &points );

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
Spell::Spell()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spell::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spell::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Spell* parentPtr = (Spell*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Spell::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Spell::Assign( const Spell& _spell )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildBonus::GuildBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBonus::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildBonus* parentPtr = (GuildBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBonus::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "tooltip", &tooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBonus::Assign( const GuildBonus& _guildBonus )
{
	tooltip = _guildBonus.tooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapDescription::AdvMapDescription() :
		mapType( MAPTYPE_PVP )
	, teamSize( 5 )
	, minTeamSize( -1 )
	, maxUncompleteTeamSize( -1 )
	, productionMode( false )
	, minimalGuildFightTeam( 3 )
	, playSameTeamTimeOut( 30 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &mapType );
	saver.Add( 3, &matchmakingSettings );
	saver.Add( 4, &teamSize );
	saver.Add( 5, &minTeamSize );
	saver.Add( 6, &maxUncompleteTeamSize );
	saver.Add( 7, &productionMode );
	saver.Add( 8, &mapSettings );
	saver.Add( 9, &rollSettings );
	saver.Add( 10, &guardRollSettings );
	saver.Add( 11, &minimalGuildFightTeam );
	saver.Add( 12, &gameSvcSettings );
	saver.Add( 13, &playSameTeamTimeOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapDescription::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapDescription* parentPtr = (AdvMapDescription*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapDescription::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "mapType", &mapType );
	saver.Add( "matchmakingSettings", &matchmakingSettings );
	saver.Add( "teamSize", &teamSize );
	saver.Add( "minTeamSize", &minTeamSize );
	saver.Add( "maxUncompleteTeamSize", &maxUncompleteTeamSize );
	saver.Add( "productionMode", &productionMode );
	saver.Add( "mapSettings", &mapSettings );
	saver.Add( "rollSettings", &rollSettings );
	saver.Add( "guardRollSettings", &guardRollSettings );
	saver.Add( "minimalGuildFightTeam", &minimalGuildFightTeam );
	saver.Add( "gameSvcSettings", &gameSvcSettings );
	saver.Add( "playSameTeamTimeOut", &playSameTeamTimeOut );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapDescription::Assign( const AdvMapDescription& _advMapDescription )
{
	mapType = _advMapDescription.mapType;
	matchmakingSettings = _advMapDescription.matchmakingSettings;
	teamSize = _advMapDescription.teamSize;
	minTeamSize = _advMapDescription.minTeamSize;
	maxUncompleteTeamSize = _advMapDescription.maxUncompleteTeamSize;
	productionMode = _advMapDescription.productionMode;
	mapSettings = _advMapDescription.mapSettings;
	rollSettings = _advMapDescription.rollSettings;
	guardRollSettings = _advMapDescription.guardRollSettings;
	minimalGuildFightTeam = _advMapDescription.minimalGuildFightTeam;
	gameSvcSettings = _advMapDescription.gameSvcSettings;
	playSameTeamTimeOut = _advMapDescription.playSameTeamTimeOut;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapSettings::AdvMapSettings() :
		fullPartyOnly( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fullPartyOnly );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapSettings* parentPtr = (AdvMapSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "fullPartyOnly", &fullPartyOnly );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapSettings::Assign( const AdvMapSettings& _advMapSettings )
{
	fullPartyOnly = _advMapSettings.fullPartyOnly;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AILogicParameters::AILogicParameters()
{
	talentVendorCostByRarity.resize( 7, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AILogicParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &talentVendorCostByRarity );
	saver.Add( 3, &heroRanks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AILogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AILogicParameters* parentPtr = (AILogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AILogicParameters::SerializeSelf( IXmlSaver &saver )
{
	talentVendorCostByRarity.resize( 7 );
	saver.Add( "talentVendorCostByRarity", &talentVendorCostByRarity );
	saver.Add( "heroRanks", &heroRanks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AILogicParameters::Assign( const AILogicParameters& _aILogicParameters )
{
	talentVendorCostByRarity = _aILogicParameters.talentVendorCostByRarity;
	heroRanks = _aILogicParameters.heroRanks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameObject::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GameObject* parentPtr = (GameObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::Assign( const GameObject& _gameObject )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BuyServicesContainer::BuyServicesContainer()
{
	services.resize( 1 );
	buffs.resize( 11 );
	rewards.resize( 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServicesContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &services );
	saver.Add( 3, &buffs );
	saver.Add( 4, &rewards );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServicesContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BuyServicesContainer* parentPtr = (BuyServicesContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuyServicesContainer::SerializeSelf( IXmlSaver &saver )
{
	services.resize( 1 );
	saver.Add( "services", &services );
	buffs.resize( 11 );
	saver.Add( "buffs", &buffs );
	rewards.resize( 1 );
	saver.Add( "rewards", &rewards );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuyServicesContainer::Assign( const BuyServicesContainer& _buyServicesContainer )
{
	services = _buyServicesContainer.services;
	buffs = _buyServicesContainer.buffs;
	rewards = _buyServicesContainer.rewards;
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
RollItem::RollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItem::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollItem* parentPtr = (RollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollItem::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollItem::Assign( const RollItem& _rollItem )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClanWarsSettings::ClanWarsSettings() :
		basePoints( 10.0f )
	, clanPoints( 0.3f )
	, normalizeBySessionScores( true )
	, premiumAccountModifier( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &basePoints );
	saver.Add( 3, &partyClanMembersModifier );
	saver.Add( 4, &foeCountsModifier );
	saver.Add( 5, &defeatedFoeRankModifier );
	saver.Add( 6, &clanPoints );
	saver.Add( 7, &normalizeBySessionScores );
	saver.Add( 8, &premiumAccountModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ClanWarsSettings* parentPtr = (ClanWarsSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "basePoints", &basePoints );
	saver.Add( "partyClanMembersModifier", &partyClanMembersModifier );
	saver.Add( "foeCountsModifier", &foeCountsModifier );
	saver.Add( "defeatedFoeRankModifier", &defeatedFoeRankModifier );
	saver.Add( "clanPoints", &clanPoints );
	saver.Add( "normalizeBySessionScores", &normalizeBySessionScores );
	saver.Add( "premiumAccountModifier", &premiumAccountModifier );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsSettings::Assign( const ClanWarsSettings& _clanWarsSettings )
{
	basePoints = _clanWarsSettings.basePoints;
	partyClanMembersModifier = _clanWarsSettings.partyClanMembersModifier;
	foeCountsModifier = _clanWarsSettings.foeCountsModifier;
	defeatedFoeRankModifier = _clanWarsSettings.defeatedFoeRankModifier;
	clanPoints = _clanWarsSettings.clanPoints;
	normalizeBySessionScores = _clanWarsSettings.normalizeBySessionScores;
	premiumAccountModifier = _clanWarsSettings.premiumAccountModifier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ContainersBySpecialPoints::ContainersBySpecialPoints()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ContainersBySpecialPoints::operator&( IBinSaver &saver )
{
	saver.Add( 2, &items );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ContainersBySpecialPoints::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ContainersBySpecialPoints* parentPtr = (ContainersBySpecialPoints*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ContainersBySpecialPoints::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "items", &items );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ContainersBySpecialPoints::Assign( const ContainersBySpecialPoints& _containersBySpecialPoints )
{
	items = _containersBySpecialPoints.items;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleStateObject::SingleStateObject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleStateObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleStateObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SingleStateObject* parentPtr = (SingleStateObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleStateObject::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleStateObject::Assign( const SingleStateObject& _singleStateObject )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CustomFlag::CustomFlag()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CustomFlag::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CustomFlag::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CustomFlag* parentPtr = (CustomFlag*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CustomFlag::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CustomFlag::Assign( const CustomFlag& _customFlag )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DefaultFormulas::DefaultFormulas()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DefaultFormulas::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DefaultFormulas::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DefaultFormulas* parentPtr = (DefaultFormulas*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultFormulas::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultFormulas::Assign( const DefaultFormulas& _defaultFormulas )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlagRollItem::FlagRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &flag );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FlagRollItem* parentPtr = (FlagRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "flag", &flag );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagRollItem::Assign( const FlagRollItem& _flagRollItem )
{
	flag = _flagRollItem.flag;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Unit::Unit()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Unit::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleStateObject*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Unit::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Unit* parentPtr = (Unit*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Unit::SerializeSelf( IXmlSaver &saver )
{
	SingleStateObject::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Unit::Assign( const Unit& _unit )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameSvcSettings::GameSvcSettings() :
		afkMessageTimer( 0 )
	, afkDisconnectTimer( 0 )
	, timeScale( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameSvcSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &afkMessageTimer );
	saver.Add( 3, &afkDisconnectTimer );
	saver.Add( 4, &timeScale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameSvcSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GameSvcSettings* parentPtr = (GameSvcSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameSvcSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "afkMessageTimer", &afkMessageTimer );
	saver.Add( "afkDisconnectTimer", &afkDisconnectTimer );
	saver.Add( "timeScale", &timeScale );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameSvcSettings::Assign( const GameSvcSettings& _gameSvcSettings )
{
	afkMessageTimer = _gameSvcSettings.afkMessageTimer;
	afkDisconnectTimer = _gameSvcSettings.afkDisconnectTimer;
	timeScale = _gameSvcSettings.timeScale;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlyphsDB::GlyphsDB()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphsDB::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphsDB::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GlyphsDB* parentPtr = (GlyphsDB*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphsDB::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphsDB::Assign( const GlyphsDB& _glyphsDB )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldRollItem::GoldRollItem() :
		count( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GoldRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GoldRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GoldRollItem* parentPtr = (GoldRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GoldRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "count", &count );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GoldRollItem::Assign( const GoldRollItem& _goldRollItem )
{
	count = _goldRollItem.count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdditionHeroExpBonus::AdditionHeroExpBonus() :
		percent( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdditionHeroExpBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GuildBonus*)this );
	saver.Add( 2, &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdditionHeroExpBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdditionHeroExpBonus* parentPtr = (AdditionHeroExpBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdditionHeroExpBonus::SerializeSelf( IXmlSaver &saver )
{
	GuildBonus::SerializeSelf( saver );
	saver.Add( "percent", &percent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdditionHeroExpBonus::Assign( const AdditionHeroExpBonus& _additionHeroExpBonus )
{
	percent = _additionHeroExpBonus.percent;
	tooltip = _additionHeroExpBonus.tooltip;
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
GuildLevels::GuildLevels() :
		requiredExpMultiplier( 100000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevels::operator&( IBinSaver &saver )
{
	saver.Add( 2, &requiredExpMultiplier );
	saver.Add( 3, &levels );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevels::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildLevels* parentPtr = (GuildLevels*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildLevels::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "requiredExpMultiplier", &requiredExpMultiplier );
	saver.Add( "levels", &levels );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildLevels::Assign( const GuildLevels& _guildLevels )
{
	requiredExpMultiplier = _guildLevels.requiredExpMultiplier;
	levels = _guildLevels.levels;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildResourceBonus::GuildResourceBonus() :
		resource( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildResourceBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GuildBonus*)this );
	saver.Add( 2, &resource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildResourceBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildResourceBonus* parentPtr = (GuildResourceBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildResourceBonus::SerializeSelf( IXmlSaver &saver )
{
	GuildBonus::SerializeSelf( saver );
	saver.Add( "resource", &resource );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildResourceBonus::Assign( const GuildResourceBonus& _guildResourceBonus )
{
	resource = _guildResourceBonus.resource;
	tooltip = _guildResourceBonus.tooltip;
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
Creature::Creature()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Creature::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Unit*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Creature::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Creature* parentPtr = (Creature*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Creature::SerializeSelf( IXmlSaver &saver )
{
	Unit::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Creature::Assign( const Creature& _creature )
{
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
HeroEnergyBonus::HeroEnergyBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroEnergyBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

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
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroEnergyBonus::Assign( const HeroEnergyBonus& _heroEnergyBonus )
{
	fakeFieldForCastle = _heroEnergyBonus.fakeFieldForCastle;
	modifiers.additiveValue = _heroEnergyBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _heroEnergyBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _heroEnergyBonus.gameSettings.maps;
	gameSettings.sessionType = _heroEnergyBonus.gameSettings.sessionType;
	heroes = _heroEnergyBonus.heroes;
	propertyTooltip = _heroEnergyBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroesDB::HeroesDB()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroesDB::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroesDB::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroesDB* parentPtr = (HeroesDB*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroesDB::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "heroes", &heroes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroesDB::Assign( const HeroesDB& _heroesDB )
{
	heroes = _heroesDB.heroes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroesLevelUps::HeroesLevelUps()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroesLevelUps::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroesLevelUps::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroesLevelUps* parentPtr = (HeroesLevelUps*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroesLevelUps::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroesLevelUps::Assign( const HeroesLevelUps& _heroesLevelUps )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroExperienceBonus::HeroExperienceBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroExperienceBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

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
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroExperienceBonus::Assign( const HeroExperienceBonus& _heroExperienceBonus )
{
	fakeFieldForCastle = _heroExperienceBonus.fakeFieldForCastle;
	modifiers.additiveValue = _heroExperienceBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _heroExperienceBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _heroExperienceBonus.gameSettings.maps;
	gameSettings.sessionType = _heroExperienceBonus.gameSettings.sessionType;
	heroes = _heroExperienceBonus.heroes;
	propertyTooltip = _heroExperienceBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroRanks::HeroRanks() :
		highLevelsMMRating( 2000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRanks::operator&( IBinSaver &saver )
{
	saver.Add( 2, &highLevelsMMRating );
	saver.Add( 3, &ranks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRanks::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroRanks* parentPtr = (HeroRanks*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRanks::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "highLevelsMMRating", &highLevelsMMRating );
	saver.Add( "ranks", &ranks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRanks::Assign( const HeroRanks& _heroRanks )
{
	highLevelsMMRating = _heroRanks.highLevelsMMRating;
	ranks = _heroRanks.ranks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroRollItem::HeroRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &hero );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroRollItem* parentPtr = (HeroRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "hero", &hero );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRollItem::Assign( const HeroRollItem& _heroRollItem )
{
	hero = _heroRollItem.hero;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroSkin::HeroSkin() :
		legal( false )
	, gender( GENDER_MALE )
	, heroRace( EHeroRaces( HERORACES_B | HERORACES_A ) )
	, botRoll( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroSkin::operator&( IBinSaver &saver )
{
	saver.Add( 2, &legal );
	saver.Add( 3, &persistentId );
	saver.Add( 4, &gender );
	saver.Add( 5, &heroRace );
	saver.Add( 6, &botRoll );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroSkin::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroSkin* parentPtr = (HeroSkin*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSkin::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "legal", &legal );
	saver.Add( "persistentId", &persistentId );
	saver.Add( "gender", &gender );
	saver.Add( "heroRace", &heroRace );
	saver.Add( "botRoll", &botRoll );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSkin::Assign( const HeroSkin& _heroSkin )
{
	legal = _heroSkin.legal;
	persistentId = _heroSkin.persistentId;
	gender = _heroSkin.gender;
	heroRace = _heroSkin.heroRace;
	botRoll = _heroSkin.botRoll;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImpulsiveBuffsContainer::ImpulsiveBuffsContainer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsContainer::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ImpulsiveBuffsContainer* parentPtr = (ImpulsiveBuffsContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveBuffsContainer::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveBuffsContainer::Assign( const ImpulsiveBuffsContainer& _impulsiveBuffsContainer )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapList::MapList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MapList* parentPtr = (MapList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "maps", &maps );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapList::Assign( const MapList& _mapList )
{
	maps = _mapList.maps;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapMMakingSettings::MapMMakingSettings() :
		mock( false )
	, isTournamentMap( false )
	, normalBasePointsRepeatFactor( 5 )
	, noobBasePointsRepeatFactor( 40 )
	, ratingDiffGrowTime( 180.0f )
	, fullSweepSubsetLimit( 15 )
	, fullSweepSubsetLimitPve( 15 )
	, estimFunDecreaseTimeBegin( 180 )
	, estimFunDecreaseTimeEnd( 300 )
	, estimFunDecreaseFactor( 0.5f )
	, estimFunManoeuvresDecreaseFactor( 0.5f )
	, identicalHeroesSampleLimit( 1 )
	, identicalGuardHeroesSampleLimit( 1 )
	, identicalNoobHeroesSampleLimit( 2 )
	, lowWaitTimeThreshold( 30 )
	, lowWaitTimeFactor( 2.0f )
	, manoeuvresMinPopulation( 25 )
	, manoeuvresMaxPopulation( 10 )
	, guardManoeuvresMinPopulation( 10 )
	, guardManoeuvresMaxPopulation( 10 )
	, manoeuvresWaitThreshold( 180.0f )
	, manoeuvresFullSweepSubset( 15 )
	, trainingFemaleBotsCount( 1 )
	, necessaryLadiesCount( 1 )
	, highRatingThreshold( 1800 )
	, proRatingThreshold( 2000 )
	, noobGamesMaxNormalRating( 1500 )
	, highRatingCooldown( 60 )
	, noobsTimeout( 45.0f )
	, minimalNoobsPercentage( 60 )
	, fullPartyGameRatingDiffMin( 30 )
	, fullPartyGameRatingDiffMax( 200 )
	, waitTimeSoftLimit( 240 )
	, waitTimeHardLimit( 600 )
	, teamLeaversTimeTrashold( 600 )
	, gameLeaversTimeTrashold( 300 )
	, recessionPremiumTimeThreshold( 0.0f )
	, playerDiff( 5 )
	, rankDifferenceTimePenalty( 180.0f )
	, heroClassLimitsAttenuationTime( 120.0f )
	, useRanking( false )
	, fullPartySize( 5 )
	, fullPartyVsRandomTimeThreshold( 30.0f )
	, localeWaitTimeThreshold( 45 )
	, TeamSideTimeTreshold( 120.0f )
{
	recessionTableForForceMM.resize( 3 );
	optimalClasses.resize( 7 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapMMakingSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &mock );
	saver.Add( 3, &isTournamentMap );
	saver.Add( 4, &estimFunctionWeights );
	saver.Add( 5, &normalBasePointsRepeatFactor );
	saver.Add( 6, &noobBasePointsRepeatFactor );
	saver.Add( 7, &ratingDiffGrowTime );
	saver.Add( 8, &fullSweepSubsetLimit );
	saver.Add( 9, &fullSweepSubsetLimitPve );
	saver.Add( 10, &estimFunDecreaseTimeBegin );
	saver.Add( 11, &estimFunDecreaseTimeEnd );
	saver.Add( 12, &estimFunDecreaseFactor );
	saver.Add( 13, &estimFunManoeuvresDecreaseFactor );
	saver.Add( 14, &identicalHeroesSampleLimit );
	saver.Add( 15, &identicalGuardHeroesSampleLimit );
	saver.Add( 16, &identicalNoobHeroesSampleLimit );
	saver.Add( 17, &lowWaitTimeThreshold );
	saver.Add( 18, &lowWaitTimeFactor );
	saver.Add( 19, &manoeuvresMinPopulation );
	saver.Add( 20, &manoeuvresMaxPopulation );
	saver.Add( 21, &guardManoeuvresMinPopulation );
	saver.Add( 22, &guardManoeuvresMaxPopulation );
	saver.Add( 23, &manoeuvresWaitThreshold );
	saver.Add( 24, &manoeuvresFullSweepSubset );
	saver.Add( 25, &trainingFemaleBotsCount );
	saver.Add( 26, &necessaryLadiesCount );
	saver.Add( 27, &partySkillCompensation );
	saver.Add( 28, &loseStreakCorrection );
	saver.Add( 29, &highRatingThreshold );
	saver.Add( 30, &proRatingThreshold );
	saver.Add( 31, &noobGamesMaxNormalRating );
	saver.Add( 32, &highRatingCooldown );
	saver.Add( 33, &noobsTimeout );
	saver.Add( 34, &minimalNoobsPercentage );
	saver.Add( 35, &fullPartyGameRatingDiffMin );
	saver.Add( 36, &fullPartyGameRatingDiffMax );
	saver.Add( 37, &waitTimeSoftLimit );
	saver.Add( 38, &waitTimeHardLimit );
	saver.Add( 39, &teamLeaversTimeTrashold );
	saver.Add( 40, &gameLeaversTimeTrashold );
	saver.Add( 41, &locationPingSettings );
	saver.Add( 42, &waitVsProbability );
	saver.Add( 43, &ranks );
	saver.Add( 44, &recessionTableForForceMM );
	saver.Add( 45, &recessionPremiumTable );
	saver.Add( 46, &recessionFullPartyTableForForceMM );
	saver.Add( 47, &recessionPremiumTimeThreshold );
	saver.Add( 48, &recessionTableForPlayerRatingMM );
	saver.Add( 49, &playerDiff );
	saver.Add( 50, &rankDifferenceTimePenalty );
	saver.Add( 51, &heroClassLimitsAttenuationTime );
	saver.Add( 52, &useRanking );
	saver.Add( 53, &optimalClasses );
	saver.Add( 54, &delayPerDonorLocalePlayer );
	saver.Add( 55, &fullPartySize );
	saver.Add( 56, &fullPartyVsRandomTimeThreshold );
	saver.Add( 57, &localeWaitTimeThreshold );
	saver.Add( 58, &ratingScale );
	saver.Add( 59, &forceScale );
	saver.Add( 60, &TeamSideTimeTreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapMMakingSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MapMMakingSettings* parentPtr = (MapMMakingSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapMMakingSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "mock", &mock );
	saver.Add( "isTournamentMap", &isTournamentMap );
	saver.Add( "estimFunctionWeights", &estimFunctionWeights );
	saver.Add( "normalBasePointsRepeatFactor", &normalBasePointsRepeatFactor );
	saver.Add( "noobBasePointsRepeatFactor", &noobBasePointsRepeatFactor );
	saver.Add( "ratingDiffGrowTime", &ratingDiffGrowTime );
	saver.Add( "fullSweepSubsetLimit", &fullSweepSubsetLimit );
	saver.Add( "fullSweepSubsetLimitPve", &fullSweepSubsetLimitPve );
	saver.Add( "estimFunDecreaseTimeBegin", &estimFunDecreaseTimeBegin );
	saver.Add( "estimFunDecreaseTimeEnd", &estimFunDecreaseTimeEnd );
	saver.Add( "estimFunDecreaseFactor", &estimFunDecreaseFactor );
	saver.Add( "estimFunManoeuvresDecreaseFactor", &estimFunManoeuvresDecreaseFactor );
	saver.Add( "identicalHeroesSampleLimit", &identicalHeroesSampleLimit );
	saver.Add( "identicalGuardHeroesSampleLimit", &identicalGuardHeroesSampleLimit );
	saver.Add( "identicalNoobHeroesSampleLimit", &identicalNoobHeroesSampleLimit );
	saver.Add( "lowWaitTimeThreshold", &lowWaitTimeThreshold );
	saver.Add( "lowWaitTimeFactor", &lowWaitTimeFactor );
	saver.Add( "manoeuvresMinPopulation", &manoeuvresMinPopulation );
	saver.Add( "manoeuvresMaxPopulation", &manoeuvresMaxPopulation );
	saver.Add( "guardManoeuvresMinPopulation", &guardManoeuvresMinPopulation );
	saver.Add( "guardManoeuvresMaxPopulation", &guardManoeuvresMaxPopulation );
	saver.Add( "manoeuvresWaitThreshold", &manoeuvresWaitThreshold );
	saver.Add( "manoeuvresFullSweepSubset", &manoeuvresFullSweepSubset );
	saver.Add( "trainingFemaleBotsCount", &trainingFemaleBotsCount );
	saver.Add( "necessaryLadiesCount", &necessaryLadiesCount );
	saver.Add( "partySkillCompensation", &partySkillCompensation );
	saver.Add( "loseStreakCorrection", &loseStreakCorrection );
	saver.Add( "highRatingThreshold", &highRatingThreshold );
	saver.Add( "proRatingThreshold", &proRatingThreshold );
	saver.Add( "noobGamesMaxNormalRating", &noobGamesMaxNormalRating );
	saver.Add( "highRatingCooldown", &highRatingCooldown );
	saver.Add( "noobsTimeout", &noobsTimeout );
	saver.Add( "minimalNoobsPercentage", &minimalNoobsPercentage );
	saver.Add( "fullPartyGameRatingDiffMin", &fullPartyGameRatingDiffMin );
	saver.Add( "fullPartyGameRatingDiffMax", &fullPartyGameRatingDiffMax );
	saver.Add( "waitTimeSoftLimit", &waitTimeSoftLimit );
	saver.Add( "waitTimeHardLimit", &waitTimeHardLimit );
	saver.Add( "teamLeaversTimeTrashold", &teamLeaversTimeTrashold );
	saver.Add( "gameLeaversTimeTrashold", &gameLeaversTimeTrashold );
	saver.Add( "locationPingSettings", &locationPingSettings );
	saver.Add( "waitVsProbability", &waitVsProbability );
	saver.Add( "ranks", &ranks );
	recessionTableForForceMM.resize( 3 );
	saver.Add( "recessionTableForForceMM", &recessionTableForForceMM );
	saver.Add( "recessionPremiumTable", &recessionPremiumTable );
	saver.Add( "recessionFullPartyTableForForceMM", &recessionFullPartyTableForForceMM );
	saver.Add( "recessionPremiumTimeThreshold", &recessionPremiumTimeThreshold );
	saver.Add( "recessionTableForPlayerRatingMM", &recessionTableForPlayerRatingMM );
	saver.Add( "playerDiff", &playerDiff );
	saver.Add( "rankDifferenceTimePenalty", &rankDifferenceTimePenalty );
	saver.Add( "heroClassLimitsAttenuationTime", &heroClassLimitsAttenuationTime );
	saver.Add( "useRanking", &useRanking );
	optimalClasses.resize( 7 );
	saver.Add( "optimalClasses", &optimalClasses );
	saver.Add( "delayPerDonorLocalePlayer", &delayPerDonorLocalePlayer );
	saver.Add( "fullPartySize", &fullPartySize );
	saver.Add( "fullPartyVsRandomTimeThreshold", &fullPartyVsRandomTimeThreshold );
	saver.Add( "localeWaitTimeThreshold", &localeWaitTimeThreshold );
	saver.Add( "ratingScale", &ratingScale );
	saver.Add( "forceScale", &forceScale );
	saver.Add( "TeamSideTimeTreshold", &TeamSideTimeTreshold );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapMMakingSettings::Assign( const MapMMakingSettings& _mapMMakingSettings )
{
	mock = _mapMMakingSettings.mock;
	isTournamentMap = _mapMMakingSettings.isTournamentMap;
	estimFunctionWeights.ladiesNumber = _mapMMakingSettings.estimFunctionWeights.ladiesNumber;
	estimFunctionWeights.genderPairs = _mapMMakingSettings.estimFunctionWeights.genderPairs;
	estimFunctionWeights.heroes = _mapMMakingSettings.estimFunctionWeights.heroes;
	estimFunctionWeights.ratingSpan = _mapMMakingSettings.estimFunctionWeights.ratingSpan;
	estimFunctionWeights.ratingPatternDelta = _mapMMakingSettings.estimFunctionWeights.ratingPatternDelta;
	estimFunctionWeights.ratingTeamAvgDelta = _mapMMakingSettings.estimFunctionWeights.ratingTeamAvgDelta;
	estimFunctionWeights.forceSpan = _mapMMakingSettings.estimFunctionWeights.forceSpan;
	estimFunctionWeights.heroClassesDifference = _mapMMakingSettings.estimFunctionWeights.heroClassesDifference;
	estimFunctionWeights.heroClassesOptimum = _mapMMakingSettings.estimFunctionWeights.heroClassesOptimum;
	normalBasePointsRepeatFactor = _mapMMakingSettings.normalBasePointsRepeatFactor;
	noobBasePointsRepeatFactor = _mapMMakingSettings.noobBasePointsRepeatFactor;
	ratingDiffGrowTime = _mapMMakingSettings.ratingDiffGrowTime;
	fullSweepSubsetLimit = _mapMMakingSettings.fullSweepSubsetLimit;
	fullSweepSubsetLimitPve = _mapMMakingSettings.fullSweepSubsetLimitPve;
	estimFunDecreaseTimeBegin = _mapMMakingSettings.estimFunDecreaseTimeBegin;
	estimFunDecreaseTimeEnd = _mapMMakingSettings.estimFunDecreaseTimeEnd;
	estimFunDecreaseFactor = _mapMMakingSettings.estimFunDecreaseFactor;
	estimFunManoeuvresDecreaseFactor = _mapMMakingSettings.estimFunManoeuvresDecreaseFactor;
	identicalHeroesSampleLimit = _mapMMakingSettings.identicalHeroesSampleLimit;
	identicalGuardHeroesSampleLimit = _mapMMakingSettings.identicalGuardHeroesSampleLimit;
	identicalNoobHeroesSampleLimit = _mapMMakingSettings.identicalNoobHeroesSampleLimit;
	lowWaitTimeThreshold = _mapMMakingSettings.lowWaitTimeThreshold;
	lowWaitTimeFactor = _mapMMakingSettings.lowWaitTimeFactor;
	manoeuvresMinPopulation = _mapMMakingSettings.manoeuvresMinPopulation;
	manoeuvresMaxPopulation = _mapMMakingSettings.manoeuvresMaxPopulation;
	guardManoeuvresMinPopulation = _mapMMakingSettings.guardManoeuvresMinPopulation;
	guardManoeuvresMaxPopulation = _mapMMakingSettings.guardManoeuvresMaxPopulation;
	manoeuvresWaitThreshold = _mapMMakingSettings.manoeuvresWaitThreshold;
	manoeuvresFullSweepSubset = _mapMMakingSettings.manoeuvresFullSweepSubset;
	trainingFemaleBotsCount = _mapMMakingSettings.trainingFemaleBotsCount;
	necessaryLadiesCount = _mapMMakingSettings.necessaryLadiesCount;
	partySkillCompensation = _mapMMakingSettings.partySkillCompensation;
	loseStreakCorrection.minStreak = _mapMMakingSettings.loseStreakCorrection.minStreak;
	loseStreakCorrection.forcePenalty = _mapMMakingSettings.loseStreakCorrection.forcePenalty;
	loseStreakCorrection.ratingPenalty = _mapMMakingSettings.loseStreakCorrection.ratingPenalty;
	loseStreakCorrection.firstCaseThreshold = _mapMMakingSettings.loseStreakCorrection.firstCaseThreshold;
	loseStreakCorrection.firstCasePenalty = _mapMMakingSettings.loseStreakCorrection.firstCasePenalty;
	loseStreakCorrection.secondCaseThreshold = _mapMMakingSettings.loseStreakCorrection.secondCaseThreshold;
	loseStreakCorrection.secondCasePenalty = _mapMMakingSettings.loseStreakCorrection.secondCasePenalty;
	loseStreakCorrection.thirdCaseThreshold = _mapMMakingSettings.loseStreakCorrection.thirdCaseThreshold;
	loseStreakCorrection.thirdCasePenalty = _mapMMakingSettings.loseStreakCorrection.thirdCasePenalty;
	highRatingThreshold = _mapMMakingSettings.highRatingThreshold;
	proRatingThreshold = _mapMMakingSettings.proRatingThreshold;
	noobGamesMaxNormalRating = _mapMMakingSettings.noobGamesMaxNormalRating;
	highRatingCooldown = _mapMMakingSettings.highRatingCooldown;
	noobsTimeout = _mapMMakingSettings.noobsTimeout;
	minimalNoobsPercentage = _mapMMakingSettings.minimalNoobsPercentage;
	fullPartyGameRatingDiffMin = _mapMMakingSettings.fullPartyGameRatingDiffMin;
	fullPartyGameRatingDiffMax = _mapMMakingSettings.fullPartyGameRatingDiffMax;
	waitTimeSoftLimit = _mapMMakingSettings.waitTimeSoftLimit;
	waitTimeHardLimit = _mapMMakingSettings.waitTimeHardLimit;
	teamLeaversTimeTrashold = _mapMMakingSettings.teamLeaversTimeTrashold;
	gameLeaversTimeTrashold = _mapMMakingSettings.gameLeaversTimeTrashold;
	locationPingSettings.nicePingThreshold = _mapMMakingSettings.locationPingSettings.nicePingThreshold;
	locationPingSettings.pingScaleMinFactor = _mapMMakingSettings.locationPingSettings.pingScaleMinFactor;
	locationPingSettings.worstPingWaitTimePenalty = _mapMMakingSettings.locationPingSettings.worstPingWaitTimePenalty;
	locationPingSettings.goodEnoughPingFactor = _mapMMakingSettings.locationPingSettings.goodEnoughPingFactor;
	locationPingSettings.ratingThreshold = _mapMMakingSettings.locationPingSettings.ratingThreshold;
	waitVsProbability.startingWaitTime = _mapMMakingSettings.waitVsProbability.startingWaitTime;
	waitVsProbability.endingWaitTime = _mapMMakingSettings.waitVsProbability.endingWaitTime;
	waitVsProbability.startingProbabilityWeight = _mapMMakingSettings.waitVsProbability.startingProbabilityWeight;
	waitVsProbability.endingProbabilityWeight = _mapMMakingSettings.waitVsProbability.endingProbabilityWeight;
	ranks = _mapMMakingSettings.ranks;
	recessionTableForForceMM = _mapMMakingSettings.recessionTableForForceMM;
	recessionPremiumTable = _mapMMakingSettings.recessionPremiumTable;
	recessionFullPartyTableForForceMM.recessionTable = _mapMMakingSettings.recessionFullPartyTableForForceMM.recessionTable;
	recessionFullPartyTableForForceMM.recessionPremium = _mapMMakingSettings.recessionFullPartyTableForForceMM.recessionPremium;
	recessionPremiumTimeThreshold = _mapMMakingSettings.recessionPremiumTimeThreshold;
	recessionTableForPlayerRatingMM.recessionTable = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionTable;
	recessionTableForPlayerRatingMM.recessionSideDiff = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionSideDiff;
	recessionTableForPlayerRatingMM.recessionPremiumTable = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionPremiumTable;
	recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold;
	recessionTableForPlayerRatingMM.recessionMaxPlayerRating = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionMaxPlayerRating;
	recessionTableForPlayerRatingMM.recessionMinPlayerRating = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionMinPlayerRating;
	playerDiff = _mapMMakingSettings.playerDiff;
	rankDifferenceTimePenalty = _mapMMakingSettings.rankDifferenceTimePenalty;
	heroClassLimitsAttenuationTime = _mapMMakingSettings.heroClassLimitsAttenuationTime;
	useRanking = _mapMMakingSettings.useRanking;
	optimalClasses = _mapMMakingSettings.optimalClasses;
	delayPerDonorLocalePlayer = _mapMMakingSettings.delayPerDonorLocalePlayer;
	fullPartySize = _mapMMakingSettings.fullPartySize;
	fullPartyVsRandomTimeThreshold = _mapMMakingSettings.fullPartyVsRandomTimeThreshold;
	localeWaitTimeThreshold = _mapMMakingSettings.localeWaitTimeThreshold;
	ratingScale.low = _mapMMakingSettings.ratingScale.low;
	ratingScale.high = _mapMMakingSettings.ratingScale.high;
	ratingScale.step = _mapMMakingSettings.ratingScale.step;
	ratingScale.diffLow = _mapMMakingSettings.ratingScale.diffLow;
	ratingScale.diffHigh = _mapMMakingSettings.ratingScale.diffHigh;
	forceScale.low = _mapMMakingSettings.forceScale.low;
	forceScale.high = _mapMMakingSettings.forceScale.high;
	forceScale.step = _mapMMakingSettings.forceScale.step;
	forceScale.diffLow = _mapMMakingSettings.forceScale.diffLow;
	forceScale.diffHigh = _mapMMakingSettings.forceScale.diffHigh;
	TeamSideTimeTreshold = _mapMMakingSettings.TeamSideTimeTreshold;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MarketingEventRollItem::MarketingEventRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarketingEventRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &persistentId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarketingEventRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MarketingEventRollItem* parentPtr = (MarketingEventRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarketingEventRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "persistentId", &persistentId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarketingEventRollItem::Assign( const MarketingEventRollItem& _marketingEventRollItem )
{
	persistentId = _marketingEventRollItem.persistentId;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModeRollSettings::ModeRollSettings() :
		scoresCap( 90 )
	, containersOnWin( 0 )
	, allowedRollGroups( TALENTROLLGROUP_ALL )
	, enduranceGain( 40 )
	, enduranceCoeff( 0.33f )
	, enduranceFameCoeff( 0.33f )
	, enduranceExperienceCoeff( 0.33f )
	, enduranceResourcesCoeff( 0.33f )
	, leaversAwardsCoeff( 0.3f )
	, reliabilityOnFinishWin( 3 )
	, reliabilityOnFinishLose( 5 )
	, reliabilityOnFinishPeriod( 1800 )
	, reliabilityOnFinishPerPeriod( 1 )
	, reliabilityOnLeave( -3 )
	, reliabilityOnLeavePeriod( 300 )
	, reliabilityOnLeavePerPeriod( -1 )
	, talentsMultiplicator( 1 )
	, enduranceDisableRollBoost( true )
	, fameLoseCoeff( 0.33f )
	, experienceLoseCoeff( 0.33f )
	, resourcesLoseCoeff( 1.0f )
	, dodgePointsOnLeave( 1 )
	, ratingChangeMultiplier( 1.0f )
	, minSessionDuration( 0 )
	, applyPremiumTalent( 0 )
	, version( 0 )
	, teamWinDisconnectedWin( false )
	, fullPartySize( 4 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModeRollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &scoresCap );
	saver.Add( 3, &containersOnWin );
	saver.Add( 4, &containersOnFWOD );
	saver.Add( 5, &containersBySpecialPoints );
	saver.Add( 6, &allowedRollGroups );
	saver.Add( 7, &containers );
	saver.Add( 8, &premiumContainers );
	saver.Add( 9, &additionalPremiumContainers );
	saver.Add( 10, &defaultContainer );
	saver.Add( 11, &eventContainers );
	saver.Add( 12, &premiumEventContainers );
	saver.Add( 13, &enduranceGain );
	saver.Add( 14, &enduranceCoeff );
	saver.Add( 15, &enduranceFameCoeff );
	saver.Add( 16, &enduranceExperienceCoeff );
	saver.Add( 17, &enduranceResourcesCoeff );
	saver.Add( 18, &leaversAwardsCoeff );
	saver.Add( 19, &reliabilityOnFinishWin );
	saver.Add( 20, &reliabilityOnFinishLose );
	saver.Add( 21, &reliabilityOnFinishPeriod );
	saver.Add( 22, &reliabilityOnFinishPerPeriod );
	saver.Add( 23, &reliabilityOnLeave );
	saver.Add( 24, &reliabilityOnLeavePeriod );
	saver.Add( 25, &reliabilityOnLeavePerPeriod );
	saver.Add( 26, &talentsMultiplicator );
	saver.Add( 27, &enduranceDisableRollBoost );
	saver.Add( 28, &famePerSession );
	saver.Add( 29, &fameLoseCoeff );
	saver.Add( 30, &experienceLoseCoeff );
	saver.Add( 31, &resourcesLoseCoeff );
	saver.Add( 32, &experiencePerSession );
	saver.Add( 33, &dodgePointsOnLeave );
	saver.Add( 34, &ratingChangeMultiplier );
	saver.Add( 35, &minSessionDuration );
	saver.Add( 36, &applyPremiumTalent );
	saver.Add( 37, &FWODRewardContainer );
	saver.Add( 38, &modeName );
	saver.Add( 39, &version );
	saver.Add( 40, &teamWinDisconnectedWin );
	saver.Add( 41, &clanWarsSettings );
	saver.Add( 42, &fullPartySize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModeRollSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ModeRollSettings* parentPtr = (ModeRollSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModeRollSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "scoresCap", &scoresCap );
	saver.Add( "containersOnWin", &containersOnWin );
	saver.Add( "containersOnFWOD", &containersOnFWOD );
	saver.Add( "containersBySpecialPoints", &containersBySpecialPoints );
	saver.Add( "allowedRollGroups", &allowedRollGroups );
	saver.Add( "containers", &containers );
	saver.Add( "premiumContainers", &premiumContainers );
	saver.Add( "additionalPremiumContainers", &additionalPremiumContainers );
	saver.Add( "defaultContainer", &defaultContainer );
	saver.Add( "eventContainers", &eventContainers );
	saver.Add( "premiumEventContainers", &premiumEventContainers );
	saver.Add( "enduranceGain", &enduranceGain );
	saver.Add( "enduranceCoeff", &enduranceCoeff );
	saver.Add( "enduranceFameCoeff", &enduranceFameCoeff );
	saver.Add( "enduranceExperienceCoeff", &enduranceExperienceCoeff );
	saver.Add( "enduranceResourcesCoeff", &enduranceResourcesCoeff );
	saver.Add( "leaversAwardsCoeff", &leaversAwardsCoeff );
	saver.Add( "reliabilityOnFinishWin", &reliabilityOnFinishWin );
	saver.Add( "reliabilityOnFinishLose", &reliabilityOnFinishLose );
	saver.Add( "reliabilityOnFinishPeriod", &reliabilityOnFinishPeriod );
	saver.Add( "reliabilityOnFinishPerPeriod", &reliabilityOnFinishPerPeriod );
	saver.Add( "reliabilityOnLeave", &reliabilityOnLeave );
	saver.Add( "reliabilityOnLeavePeriod", &reliabilityOnLeavePeriod );
	saver.Add( "reliabilityOnLeavePerPeriod", &reliabilityOnLeavePerPeriod );
	saver.Add( "talentsMultiplicator", &talentsMultiplicator );
	saver.Add( "enduranceDisableRollBoost", &enduranceDisableRollBoost );
	saver.Add( "famePerSession", &famePerSession );
	saver.Add( "fameLoseCoeff", &fameLoseCoeff );
	saver.Add( "experienceLoseCoeff", &experienceLoseCoeff );
	saver.Add( "resourcesLoseCoeff", &resourcesLoseCoeff );
	saver.Add( "experiencePerSession", &experiencePerSession );
	saver.Add( "dodgePointsOnLeave", &dodgePointsOnLeave );
	saver.Add( "ratingChangeMultiplier", &ratingChangeMultiplier );
	saver.Add( "minSessionDuration", &minSessionDuration );
	saver.Add( "applyPremiumTalent", &applyPremiumTalent );
	saver.Add( "FWODRewardContainer", &FWODRewardContainer );
	saver.Add( "modeName", &modeName );
	saver.Add( "version", &version );
	saver.Add( "teamWinDisconnectedWin", &teamWinDisconnectedWin );
	saver.Add( "clanWarsSettings", &clanWarsSettings );
	saver.Add( "fullPartySize", &fullPartySize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModeRollSettings::Assign( const ModeRollSettings& _modeRollSettings )
{
	scoresCap = _modeRollSettings.scoresCap;
	containersOnWin = _modeRollSettings.containersOnWin;
	containersOnFWOD = _modeRollSettings.containersOnFWOD;
	containersBySpecialPoints = _modeRollSettings.containersBySpecialPoints;
	allowedRollGroups = _modeRollSettings.allowedRollGroups;
	containers = _modeRollSettings.containers;
	premiumContainers = _modeRollSettings.premiumContainers;
	additionalPremiumContainers = _modeRollSettings.additionalPremiumContainers;
	defaultContainer = _modeRollSettings.defaultContainer;
	eventContainers = _modeRollSettings.eventContainers;
	premiumEventContainers = _modeRollSettings.premiumEventContainers;
	enduranceGain = _modeRollSettings.enduranceGain;
	enduranceCoeff = _modeRollSettings.enduranceCoeff;
	enduranceFameCoeff = _modeRollSettings.enduranceFameCoeff;
	enduranceExperienceCoeff = _modeRollSettings.enduranceExperienceCoeff;
	enduranceResourcesCoeff = _modeRollSettings.enduranceResourcesCoeff;
	leaversAwardsCoeff = _modeRollSettings.leaversAwardsCoeff;
	reliabilityOnFinishWin = _modeRollSettings.reliabilityOnFinishWin;
	reliabilityOnFinishLose = _modeRollSettings.reliabilityOnFinishLose;
	reliabilityOnFinishPeriod = _modeRollSettings.reliabilityOnFinishPeriod;
	reliabilityOnFinishPerPeriod = _modeRollSettings.reliabilityOnFinishPerPeriod;
	reliabilityOnLeave = _modeRollSettings.reliabilityOnLeave;
	reliabilityOnLeavePeriod = _modeRollSettings.reliabilityOnLeavePeriod;
	reliabilityOnLeavePerPeriod = _modeRollSettings.reliabilityOnLeavePerPeriod;
	talentsMultiplicator = _modeRollSettings.talentsMultiplicator;
	enduranceDisableRollBoost = _modeRollSettings.enduranceDisableRollBoost;
	famePerSession = _modeRollSettings.famePerSession;
	fameLoseCoeff = _modeRollSettings.fameLoseCoeff;
	experienceLoseCoeff = _modeRollSettings.experienceLoseCoeff;
	resourcesLoseCoeff = _modeRollSettings.resourcesLoseCoeff;
	experiencePerSession = _modeRollSettings.experiencePerSession;
	dodgePointsOnLeave = _modeRollSettings.dodgePointsOnLeave;
	ratingChangeMultiplier = _modeRollSettings.ratingChangeMultiplier;
	minSessionDuration = _modeRollSettings.minSessionDuration;
	applyPremiumTalent = _modeRollSettings.applyPremiumTalent;
	FWODRewardContainer = _modeRollSettings.FWODRewardContainer;
	modeName = _modeRollSettings.modeName;
	version = _modeRollSettings.version;
	teamWinDisconnectedWin = _modeRollSettings.teamWinDisconnectedWin;
	clanWarsSettings = _modeRollSettings.clanWarsSettings;
	fullPartySize = _modeRollSettings.fullPartySize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NothingRollItem::NothingRollItem() :
		dummy( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NothingRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &dummy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NothingRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NothingRollItem* parentPtr = (NothingRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NothingRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "dummy", &dummy );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NothingRollItem::Assign( const NothingRollItem& _nothingRollItem )
{
	dummy = _nothingRollItem.dummy;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlayerPointsBonus::PlayerPointsBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayerPointsBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayerPointsBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PlayerPointsBonus* parentPtr = (PlayerPointsBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerPointsBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerPointsBonus::Assign( const PlayerPointsBonus& _playerPointsBonus )
{
	fakeFieldForCastle = _playerPointsBonus.fakeFieldForCastle;
	modifiers.additiveValue = _playerPointsBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _playerPointsBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _playerPointsBonus.gameSettings.maps;
	gameSettings.sessionType = _playerPointsBonus.gameSettings.sessionType;
	heroes = _playerPointsBonus.heroes;
	propertyTooltip = _playerPointsBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PremiumAccRollItem::PremiumAccRollItem() :
		days( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumAccRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &days );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumAccRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PremiumAccRollItem* parentPtr = (PremiumAccRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PremiumAccRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "days", &days );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PremiumAccRollItem::Assign( const PremiumAccRollItem& _premiumAccRollItem )
{
	days = _premiumAccRollItem.days;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RandomTalentBonus::RandomTalentBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RandomTalentBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GuildBonus*)this );
	saver.Add( 2, &singleRollSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RandomTalentBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RandomTalentBonus* parentPtr = (RandomTalentBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomTalentBonus::SerializeSelf( IXmlSaver &saver )
{
	GuildBonus::SerializeSelf( saver );
	saver.Add( "singleRollSettings", &singleRollSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomTalentBonus::Assign( const RandomTalentBonus& _randomTalentBonus )
{
	singleRollSettings.rollContainer = _randomTalentBonus.singleRollSettings.rollContainer;
	singleRollSettings.allowedRollGroups = _randomTalentBonus.singleRollSettings.allowedRollGroups;
	singleRollSettings.version = _randomTalentBonus.singleRollSettings.version;
	tooltip = _randomTalentBonus.tooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RarityTalentListRollItem::RarityTalentListRollItem() :
		rarity( TALENTRARITY_CLASS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RarityTalentListRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &rarity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RarityTalentListRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RarityTalentListRollItem* parentPtr = (RarityTalentListRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RarityTalentListRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "rarity", &rarity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RarityTalentListRollItem::Assign( const RarityTalentListRollItem& _rarityTalentListRollItem )
{
	rarity = _rarityTalentListRollItem.rarity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceRollItem::ResourceRollItem() :
		type( RESOURCEROLLCONSTRAINT_SILVER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &customCurrencyId );
	saver.Add( 4, &itemsFromLord );
	saver.Add( 5, &itemsFromHero );
	saver.Add( 6, &itemsFromRank );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ResourceRollItem* parentPtr = (ResourceRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "customCurrencyId", &customCurrencyId );
	saver.Add( "itemsFromLord", &itemsFromLord );
	saver.Add( "itemsFromHero", &itemsFromHero );
	saver.Add( "itemsFromRank", &itemsFromRank );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceRollItem::Assign( const ResourceRollItem& _resourceRollItem )
{
	type = _resourceRollItem.type;
	customCurrencyId = _resourceRollItem.customCurrencyId;
	itemsFromLord = _resourceRollItem.itemsFromLord;
	itemsFromHero = _resourceRollItem.itemsFromHero;
	itemsFromRank = _resourceRollItem.itemsFromRank;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainer::RollContainer() :
		multiplicator( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &costByRank );
	saver.Add( 3, &name );
	saver.Add( 4, &items );
	saver.Add( 5, &multiplicator );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainer* parentPtr = (RollContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainer::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "costByRank", &costByRank );
	saver.Add( "name", &name );
	saver.Add( "items", &items );
	saver.Add( "multiplicator", &multiplicator );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainer::Assign( const RollContainer& _rollContainer )
{
	costByRank = _rollContainer.costByRank;
	name = _rollContainer.name;
	items = _rollContainer.items;
	multiplicator = _rollContainer.multiplicator;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainerCostByRank::RollContainerCostByRank()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCostByRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &costs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCostByRank::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainerCostByRank* parentPtr = (RollContainerCostByRank*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCostByRank::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "costs", &costs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCostByRank::Assign( const RollContainerCostByRank& _rollContainerCostByRank )
{
	costs = _rollContainerCostByRank.costs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainerCountByRank::RollContainerCountByRank()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCountByRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &counts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCountByRank::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainerCountByRank* parentPtr = (RollContainerCountByRank*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCountByRank::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "counts", &counts );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCountByRank::Assign( const RollContainerCountByRank& _rollContainerCountByRank )
{
	counts = _rollContainerCountByRank.counts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClanWarsRollItem::ClanWarsRollItem() :
		type( CLANWARSROLLITEMTYPE_CLANRATING )
	, count( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ClanWarsRollItem* parentPtr = (ClanWarsRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "count", &count );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsRollItem::Assign( const ClanWarsRollItem& _clanWarsRollItem )
{
	type = _clanWarsRollItem.type;
	count = _clanWarsRollItem.count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollSettings::RollSettings() :
		requiredLevelForExclusiveTalents( 21 )
	, requiredRatingForExclusiveTalents( 1600 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pvp );
	saver.Add( 3, &defaultRollContainerCostByRank );
	saver.Add( 4, &trainingFWODSettings );
	saver.Add( 5, &ratingModifiers );
	saver.Add( 6, &fullPartyRatingModifiers );
	saver.Add( 7, &forgeRollSettings );
	saver.Add( 8, &guildLevels );
	saver.Add( 9, &requiredLevelForExclusiveTalents );
	saver.Add( 10, &requiredRatingForExclusiveTalents );
	saver.Add( 11, &clanWarsSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollSettings* parentPtr = (RollSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "pvp", &pvp );
	saver.Add( "defaultRollContainerCostByRank", &defaultRollContainerCostByRank );
	saver.Add( "trainingFWODSettings", &trainingFWODSettings );
	saver.Add( "ratingModifiers", &ratingModifiers );
	saver.Add( "fullPartyRatingModifiers", &fullPartyRatingModifiers );
	saver.Add( "forgeRollSettings", &forgeRollSettings );
	saver.Add( "guildLevels", &guildLevels );
	saver.Add( "requiredLevelForExclusiveTalents", &requiredLevelForExclusiveTalents );
	saver.Add( "requiredRatingForExclusiveTalents", &requiredRatingForExclusiveTalents );
	saver.Add( "clanWarsSettings", &clanWarsSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollSettings::Assign( const RollSettings& _rollSettings )
{
	pvp = _rollSettings.pvp;
	defaultRollContainerCostByRank = _rollSettings.defaultRollContainerCostByRank;
	trainingFWODSettings = _rollSettings.trainingFWODSettings;
	ratingModifiers = _rollSettings.ratingModifiers;
	fullPartyRatingModifiers = _rollSettings.fullPartyRatingModifiers;
	forgeRollSettings.rollContainer = _rollSettings.forgeRollSettings.rollContainer;
	forgeRollSettings.allowedRollGroups = _rollSettings.forgeRollSettings.allowedRollGroups;
	forgeRollSettings.version = _rollSettings.forgeRollSettings.version;
	guildLevels = _rollSettings.guildLevels;
	requiredLevelForExclusiveTalents = _rollSettings.requiredLevelForExclusiveTalents;
	requiredRatingForExclusiveTalents = _rollSettings.requiredRatingForExclusiveTalents;
	clanWarsSettings = _rollSettings.clanWarsSettings;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScoringTable::ScoringTable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoringTable::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoringTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScoringTable* parentPtr = (ScoringTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScoringTable::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScoringTable::Assign( const ScoringTable& _scoringTable )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionAudioRoot::SessionAudioRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionAudioRoot::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionAudioRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionAudioRoot* parentPtr = (SessionAudioRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionAudioRoot::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionAudioRoot::Assign( const SessionAudioRoot& _sessionAudioRoot )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildWarEventPass::GuildWarEventPass() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildWarEventPass::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

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
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildWarEventPass::Assign( const GuildWarEventPass& _guildWarEventPass )
{
	fakeFieldForCastle = _guildWarEventPass.fakeFieldForCastle;
	gameSettings.maps = _guildWarEventPass.gameSettings.maps;
	gameSettings.sessionType = _guildWarEventPass.gameSettings.sessionType;
	heroes = _guildWarEventPass.heroes;
	propertyTooltip = _guildWarEventPass.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionLogicRoot::SessionLogicRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionLogicRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &aiLogic );
	saver.Add( 3, &scoringTable );
	saver.Add( 4, &unitLogicParameters );
	saver.Add( 5, &glyphsDB );
	saver.Add( 6, &heroes );
	saver.Add( 7, &heroesLevelups );
	saver.Add( 8, &impulsiveBuffs );
	saver.Add( 9, &defaultFormulas );
	saver.Add( 10, &mapList );
	saver.Add( 11, &guildBuffsCollection );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionLogicRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionLogicRoot* parentPtr = (SessionLogicRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionLogicRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "aiLogic", &aiLogic );
	saver.Add( "scoringTable", &scoringTable );
	saver.Add( "unitLogicParameters", &unitLogicParameters );
	saver.Add( "glyphsDB", &glyphsDB );
	saver.Add( "heroes", &heroes );
	saver.Add( "heroesLevelups", &heroesLevelups );
	saver.Add( "impulsiveBuffs", &impulsiveBuffs );
	saver.Add( "defaultFormulas", &defaultFormulas );
	saver.Add( "mapList", &mapList );
	saver.Add( "guildBuffsCollection", &guildBuffsCollection );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionLogicRoot::Assign( const SessionLogicRoot& _sessionLogicRoot )
{
	aiLogic = _sessionLogicRoot.aiLogic;
	scoringTable = _sessionLogicRoot.scoringTable;
	unitLogicParameters = _sessionLogicRoot.unitLogicParameters;
	glyphsDB = _sessionLogicRoot.glyphsDB;
	heroes = _sessionLogicRoot.heroes;
	heroesLevelups = _sessionLogicRoot.heroesLevelups;
	impulsiveBuffs = _sessionLogicRoot.impulsiveBuffs;
	defaultFormulas = _sessionLogicRoot.defaultFormulas;
	mapList = _sessionLogicRoot.mapList;
	guildBuffsCollection = _sessionLogicRoot.guildBuffsCollection;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionMessages::SessionMessages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionMessages::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionMessages::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionMessages* parentPtr = (SessionMessages*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionMessages::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionMessages::Assign( const SessionMessages& _sessionMessages )
{
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
SessionRoot::SessionRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr< SessionRoot > SessionRoot::instance;
void SessionRoot::InitRoot( const DBID& dbid ) { InitRoot( Get<SessionRoot>( dbid ) ); }
void SessionRoot::InitRoot( const SessionRoot* _instance ) { instance = _instance; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Ptr< SessionRoot >& SessionRoot::GetRoot()
{
	NI_ASSERT( IsValid( instance ), "Root for type \"SessionRoot\" not initialized" );
	return instance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &uiRoot );
	saver.Add( 3, &logicRoot );
	saver.Add( 4, &visualRoot );
	saver.Add( 5, &audioRoot );
	saver.Add( 6, &rollSettings );
	saver.Add( 7, &sessionMessages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionRoot* parentPtr = (SessionRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "uiRoot", &uiRoot );
	saver.Add( "logicRoot", &logicRoot );
	saver.Add( "visualRoot", &visualRoot );
	saver.Add( "audioRoot", &audioRoot );
	saver.Add( "rollSettings", &rollSettings );
	saver.Add( "sessionMessages", &sessionMessages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionRoot::Assign( const SessionRoot& _sessionRoot )
{
	uiRoot = _sessionRoot.uiRoot;
	logicRoot = _sessionRoot.logicRoot;
	visualRoot = _sessionRoot.visualRoot;
	audioRoot = _sessionRoot.audioRoot;
	rollSettings = _sessionRoot.rollSettings;
	sessionMessages = _sessionRoot.sessionMessages;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionTalentsBonus::SessionTalentsBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionTalentsBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionTalentsBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionTalentsBonus* parentPtr = (SessionTalentsBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionTalentsBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionTalentsBonus::Assign( const SessionTalentsBonus& _sessionTalentsBonus )
{
	fakeFieldForCastle = _sessionTalentsBonus.fakeFieldForCastle;
	modifiers.additiveValue = _sessionTalentsBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _sessionTalentsBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _sessionTalentsBonus.gameSettings.maps;
	gameSettings.sessionType = _sessionTalentsBonus.gameSettings.sessionType;
	heroes = _sessionTalentsBonus.heroes;
	propertyTooltip = _sessionTalentsBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionUIRoot::SessionUIRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionUIRoot::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionUIRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionUIRoot* parentPtr = (SessionUIRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionUIRoot::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionUIRoot::Assign( const SessionUIRoot& _sessionUIRoot )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClanPointsBonus::ClanPointsBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanPointsBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanPointsBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ClanPointsBonus* parentPtr = (ClanPointsBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanPointsBonus::SerializeSelf( IXmlSaver &saver )
{
	SessionValueBonus::SerializeSelf( saver );
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanPointsBonus::Assign( const ClanPointsBonus& _clanPointsBonus )
{
	fakeFieldForCastle = _clanPointsBonus.fakeFieldForCastle;
	modifiers.additiveValue = _clanPointsBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _clanPointsBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _clanPointsBonus.gameSettings.maps;
	gameSettings.sessionType = _clanPointsBonus.gameSettings.sessionType;
	heroes = _clanPointsBonus.heroes;
	propertyTooltip = _clanPointsBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionVisualRoot::SessionVisualRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionVisualRoot::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionVisualRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionVisualRoot* parentPtr = (SessionVisualRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionVisualRoot::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionVisualRoot::Assign( const SessionVisualRoot& _sessionVisualRoot )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SiegePointsBonus::SiegePointsBonus() :
		fakeFieldForCastle( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SiegePointsBonus::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SessionValueBonus*)this );
	saver.Add( 2, &fakeFieldForCastle );

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
	saver.Add( "fakeFieldForCastle", &fakeFieldForCastle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SiegePointsBonus::Assign( const SiegePointsBonus& _siegePointsBonus )
{
	fakeFieldForCastle = _siegePointsBonus.fakeFieldForCastle;
	modifiers.additiveValue = _siegePointsBonus.modifiers.additiveValue;
	modifiers.multiplicativeValue = _siegePointsBonus.modifiers.multiplicativeValue;
	gameSettings.maps = _siegePointsBonus.gameSettings.maps;
	gameSettings.sessionType = _siegePointsBonus.gameSettings.sessionType;
	heroes = _siegePointsBonus.heroes;
	propertyTooltip = _siegePointsBonus.propertyTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseHero::BaseHero() :
		gender( GENDER_MALE )
	, heroRace( EHeroRaces( HERORACES_B | HERORACES_A ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseHero::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Creature*)this );
	saver.Add( 2, &gender );
	saver.Add( 3, &mmakingAntagonists );
	saver.Add( 4, &heroRace );
	saver.Add( 5, &heroSkins );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseHero::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BaseHero* parentPtr = (BaseHero*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseHero::SerializeSelf( IXmlSaver &saver )
{
	Creature::SerializeSelf( saver );
	saver.Add( "gender", &gender );
	saver.Add( "mmakingAntagonists", &mmakingAntagonists );
	saver.Add( "heroRace", &heroRace );
	saver.Add( "heroSkins", &heroSkins );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseHero::Assign( const BaseHero& _baseHero )
{
	gender = _baseHero.gender;
	mmakingAntagonists = _baseHero.mmakingAntagonists;
	heroRace = _baseHero.heroRace;
	heroSkins = _baseHero.heroSkins;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkinRollItem::SkinRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &skin );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SkinRollItem* parentPtr = (SkinRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkinRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "skin", &skin );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkinRollItem::Assign( const SkinRollItem& _skinRollItem )
{
	skin = _skinRollItem.skin;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ability::Ability()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Ability::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Spell*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Ability::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Ability* parentPtr = (Ability*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ability::SerializeSelf( IXmlSaver &saver )
{
	Spell::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ability::Assign( const Ability& _ability )
{
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
Talent::Talent() :
		rarity( TALENTRARITY_ORDINARY )
	, vendorCost( 0 )
	, talentRollGroups( TALENTROLLGROUP_ALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Talent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Ability*)this );
	saver.Add( 2, &rarity );
	saver.Add( 3, &persistentId );
	saver.Add( 4, &vendorCost );
	saver.Add( 5, &talentRollGroups );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Talent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Talent* parentPtr = (Talent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Talent::SerializeSelf( IXmlSaver &saver )
{
	Ability::SerializeSelf( saver );
	saver.Add( "rarity", &rarity );
	saver.Add( "persistentId", &persistentId );
	saver.Add( "vendorCost", &vendorCost );
	saver.Add( "talentRollGroups", &talentRollGroups );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Talent::Assign( const Talent& _talent )
{
	rarity = _talent.rarity;
	persistentId = _talent.persistentId;
	vendorCost = _talent.vendorCost;
	talentRollGroups = _talent.talentRollGroups;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentRollItem::TalentRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &talent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentRollItem* parentPtr = (TalentRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "talent", &talent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentRollItem::Assign( const TalentRollItem& _talentRollItem )
{
	talent = _talentRollItem.talent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeEntity::TalentUpgradeEntity() :
		type( TALENTUPGRADEENTITYTYPE_RUNE )
	, talentLevelLimit( 0 )
	, probability( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntity::operator&( IBinSaver &saver )
{
	saver.Add( 2, &persistentId );
	saver.Add( 3, &type );
	saver.Add( 4, &talentLevelLimit );
	saver.Add( 5, &probability );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntity::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeEntity* parentPtr = (TalentUpgradeEntity*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntity::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "persistentId", &persistentId );
	saver.Add( "type", &type );
	saver.Add( "talentLevelLimit", &talentLevelLimit );
	saver.Add( "probability", &probability );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntity::Assign( const TalentUpgradeEntity& _talentUpgradeEntity )
{
	persistentId = _talentUpgradeEntity.persistentId;
	type = _talentUpgradeEntity.type;
	talentLevelLimit = _talentUpgradeEntity.talentLevelLimit;
	probability = _talentUpgradeEntity.probability;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeEntityRollItem::TalentUpgradeEntityRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntityRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &entity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntityRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeEntityRollItem* parentPtr = (TalentUpgradeEntityRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntityRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "entity", &entity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntityRollItem::Assign( const TalentUpgradeEntityRollItem& _talentUpgradeEntityRollItem )
{
	entity = _talentUpgradeEntityRollItem.entity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeProbabilityTable::TalentUpgradeProbabilityTable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbabilityTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &upgrades );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbabilityTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeProbabilityTable* parentPtr = (TalentUpgradeProbabilityTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeProbabilityTable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "upgrades", &upgrades );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeProbabilityTable::Assign( const TalentUpgradeProbabilityTable& _talentUpgradeProbabilityTable )
{
	upgrades = _talentUpgradeProbabilityTable.upgrades;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeRollItem::TalentUpgradeRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &upgradeTable );
	saver.Add( 3, &talentItem );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeRollItem* parentPtr = (TalentUpgradeRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "upgradeTable", &upgradeTable );
	saver.Add( "talentItem", &talentItem );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeRollItem::Assign( const TalentUpgradeRollItem& _talentUpgradeRollItem )
{
	upgradeTable = _talentUpgradeRollItem.upgradeTable;
	talentItem = _talentUpgradeRollItem.talentItem;
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Hero::Hero() :
		legal( true )
	, botRollMode( BOTROLLMODE_ENABLED )
{
	classEfficiency.resize( 7, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Hero::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseHero*)this );
	saver.Add( 2, &id );
	saver.Add( 3, &legal );
	saver.Add( 4, &botRollMode );
	saver.Add( 5, &classEfficiency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Hero::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Hero* parentPtr = (Hero*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hero::SerializeSelf( IXmlSaver &saver )
{
	BaseHero::SerializeSelf( saver );
	saver.Add( "id", &id );
	saver.Add( "legal", &legal );
	saver.Add( "botRollMode", &botRollMode );
	classEfficiency.resize( 7 );
	saver.Add( "classEfficiency", &classEfficiency );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hero::Assign( const Hero& _hero )
{
	id = _hero.id;
	legal = _hero.legal;
	botRollMode = _hero.botRollMode;
	classEfficiency = _hero.classEfficiency;
	gender = _hero.gender;
	mmakingAntagonists = _hero.mmakingAntagonists;
	heroRace = _hero.heroRace;
	heroSkins = _hero.heroSkins;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitsLogicParameters::UnitsLogicParameters()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitsLogicParameters::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitsLogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitsLogicParameters* parentPtr = (UnitsLogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitsLogicParameters::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitsLogicParameters::Assign( const UnitsLogicParameters& _unitsLogicParameters )
{
}
}; // namespace NDb
