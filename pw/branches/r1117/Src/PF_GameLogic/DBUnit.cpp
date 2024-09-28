// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRender.h"
#include "../Scene/DBScene.h"
#include "../Render/DBRenderResources.h"
#include "../PF_Core/DBEffect.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBTalent.h"
#include "../PF_GameLogic/DBMinigamesTypes.h"
#include "../PF_GameLogic/DBConsumable.h"
#include "../PF_GameLogic/DBStats.h"
#include "DBUnit.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SingleStateObject );
REGISTER_DBRESOURCE( BaseCreepSpawner );
REGISTER_DBRESOURCE( AdvMapNeutralCreepSpawner );
REGISTER_DBRESOURCE( AdvMapObstacle );
REGISTER_DBRESOURCE( AoeVisual );
REGISTER_DBRESOURCE( AskSoundsRef );
REGISTER_DBRESOURCE( AdvMapCreepSpawner );
REGISTER_DBRESOURCE( Unit );
REGISTER_DBRESOURCE( Creature );
REGISTER_DBRESOURCE( Building );
BASIC_REGISTER_DBRESOURCE( BattleBuilding );
REGISTER_DBRESOURCE( Tower );
REGISTER_DBRESOURCE( AdvMapCreep );
REGISTER_DBRESOURCE( CreepSkin );
REGISTER_DBRESOURCE( CreepSpawnTimer );
REGISTER_DBRESOURCE( Critter );
REGISTER_DBRESOURCE( Flagpole );
REGISTER_DBRESOURCE( Fountain );
REGISTER_DBRESOURCE( Glyph );
REGISTER_DBRESOURCE( GlyphsDB );
REGISTER_DBRESOURCE( GlyphSpawner );
REGISTER_DBRESOURCE( BaseHero );
REGISTER_DBRESOURCE( HeroesLevelUps );
REGISTER_DBRESOURCE( HeroPlaceHolder );
REGISTER_DBRESOURCE( HeroResource );
REGISTER_DBRESOURCE( HeroSkin );
REGISTER_DBRESOURCE( Interaction );
REGISTER_DBRESOURCE( KillExperienceModifier );
REGISTER_DBRESOURCE( MainBuilding );
REGISTER_DBRESOURCE( MinigamePlace );
REGISTER_DBRESOURCE( MSOTransactions );
REGISTER_DBRESOURCE( MultiStateObject );
REGISTER_DBRESOURCE( Quarter );
REGISTER_DBRESOURCE( ScriptedFlagpole );
REGISTER_DBRESOURCE( Shop );
REGISTER_DBRESOURCE( SimpleObject );
REGISTER_DBRESOURCE( Hero );
REGISTER_DBRESOURCE( Summoned );
REGISTER_DBRESOURCE( ControllableTower );
REGISTER_DBRESOURCE( TreeObject );
REGISTER_DBRESOURCE( BasePet );
REGISTER_DBRESOURCE( UnitCategories );
REGISTER_DBRESOURCE( UnitCategoriesParams );
REGISTER_DBRESOURCE( UsableBuilding );
REGISTER_DBRESOURCE( WarFogUnblock );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BooleanLockMode value )
{
	switch( value )
	{
		case BOOLEANLOCKMODE_LOCK:
			return "Lock";
		case BOOLEANLOCKMODE_UNLOCK:
			return "UnLock";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BooleanLockMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BooleanLockMode StringToEnum_BooleanLockMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BooleanLockMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Lock" ) == 0 || strcmp( value, "BOOLEANLOCKMODE_LOCK" ) == 0 )
		return BOOLEANLOCKMODE_LOCK;
	if ( strcmp( value, "UnLock" ) == 0 || strcmp( value, "BOOLEANLOCKMODE_UNLOCK" ) == 0 )
		return BOOLEANLOCKMODE_UNLOCK;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BooleanLockMode", value ) );
	return BOOLEANLOCKMODE_LOCK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAskRecipient value )
{
	switch( value )
	{
		case ASKRECIPIENT_SELF:
			return "Self";
		case ASKRECIPIENT_TARGET:
			return "Target";
		case ASKRECIPIENT_ALLIES:
			return "Allies";
		case ASKRECIPIENT_ENEMIES:
			return "Enemies";
		case ASKRECIPIENT_ALL:
			return "All";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAskRecipient", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAskRecipient StringToEnum_EAskRecipient( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAskRecipient)(NStr::ToInt( value ));
	if ( strcmp( value, "Self" ) == 0 || strcmp( value, "ASKRECIPIENT_SELF" ) == 0 )
		return ASKRECIPIENT_SELF;
	if ( strcmp( value, "Target" ) == 0 || strcmp( value, "ASKRECIPIENT_TARGET" ) == 0 )
		return ASKRECIPIENT_TARGET;
	if ( strcmp( value, "Allies" ) == 0 || strcmp( value, "ASKRECIPIENT_ALLIES" ) == 0 )
		return ASKRECIPIENT_ALLIES;
	if ( strcmp( value, "Enemies" ) == 0 || strcmp( value, "ASKRECIPIENT_ENEMIES" ) == 0 )
		return ASKRECIPIENT_ENEMIES;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "ASKRECIPIENT_ALL" ) == 0 )
		return ASKRECIPIENT_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAskRecipient", value ) );
	return ASKRECIPIENT_SELF;
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
const char *EnumToString( const ECreepType value )
{
	switch( value )
	{
		case CREEPTYPE_FACTIONALNORMAL:
			return "FactionalNormal";
		case CREEPTYPE_FACTIONALSIEGE:
			return "FactionalSiege";
		case CREEPTYPE_FACTIONALCHAMPION:
			return "FactionalChampion";
		case CREEPTYPE_NEUTRALMINION:
			return "NeutralMinion";
		case CREEPTYPE_NEUTRALNORMAL:
			return "NeutralNormal";
		case CREEPTYPE_NEUTRALCHAMPION:
			return "NeutralChampion";
		case CREEPTYPE_NEUTRALBOSS:
			return "NeutralBoss";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ECreepType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECreepType StringToEnum_ECreepType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECreepType)(NStr::ToInt( value ));
	if ( strcmp( value, "FactionalNormal" ) == 0 || strcmp( value, "CREEPTYPE_FACTIONALNORMAL" ) == 0 )
		return CREEPTYPE_FACTIONALNORMAL;
	if ( strcmp( value, "FactionalSiege" ) == 0 || strcmp( value, "CREEPTYPE_FACTIONALSIEGE" ) == 0 )
		return CREEPTYPE_FACTIONALSIEGE;
	if ( strcmp( value, "FactionalChampion" ) == 0 || strcmp( value, "CREEPTYPE_FACTIONALCHAMPION" ) == 0 )
		return CREEPTYPE_FACTIONALCHAMPION;
	if ( strcmp( value, "NeutralMinion" ) == 0 || strcmp( value, "CREEPTYPE_NEUTRALMINION" ) == 0 )
		return CREEPTYPE_NEUTRALMINION;
	if ( strcmp( value, "NeutralNormal" ) == 0 || strcmp( value, "CREEPTYPE_NEUTRALNORMAL" ) == 0 )
		return CREEPTYPE_NEUTRALNORMAL;
	if ( strcmp( value, "NeutralChampion" ) == 0 || strcmp( value, "CREEPTYPE_NEUTRALCHAMPION" ) == 0 )
		return CREEPTYPE_NEUTRALCHAMPION;
	if ( strcmp( value, "NeutralBoss" ) == 0 || strcmp( value, "CREEPTYPE_NEUTRALBOSS" ) == 0 )
		return CREEPTYPE_NEUTRALBOSS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECreepType", value ) );
	return CREEPTYPE_FACTIONALNORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDamageType value )
{
	switch( value )
	{
		case DAMAGETYPE_MATERIAL:
			return "Material";
		case DAMAGETYPE_ENERGY:
			return "Energy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDamageType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDamageType StringToEnum_EDamageType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDamageType)(NStr::ToInt( value ));
	if ( strcmp( value, "Material" ) == 0 || strcmp( value, "DAMAGETYPE_MATERIAL" ) == 0 )
		return DAMAGETYPE_MATERIAL;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "DAMAGETYPE_ENERGY" ) == 0 )
		return DAMAGETYPE_ENERGY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDamageType", value ) );
	return DAMAGETYPE_MATERIAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGlyph value )
{
	switch( value )
	{
		case GLYPH_DOUBLEDAMAGER:
			return "DoubleDamager";
		case GLYPH_LIFERESTORER:
			return "LifeRestorer";
		case GLYPH_ENERGYRESTORER:
			return "EnergyRestorer";
		case GLYPH_REFRESHER:
			return "Refresher";
		case GLYPH_BOOSTER:
			return "Booster";
		case GLYPH_INVISIBLER:
			return "Invisibler";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EGlyph", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGlyph StringToEnum_EGlyph( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGlyph)(NStr::ToInt( value ));
	if ( strcmp( value, "DoubleDamager" ) == 0 || strcmp( value, "GLYPH_DOUBLEDAMAGER" ) == 0 )
		return GLYPH_DOUBLEDAMAGER;
	if ( strcmp( value, "LifeRestorer" ) == 0 || strcmp( value, "GLYPH_LIFERESTORER" ) == 0 )
		return GLYPH_LIFERESTORER;
	if ( strcmp( value, "EnergyRestorer" ) == 0 || strcmp( value, "GLYPH_ENERGYRESTORER" ) == 0 )
		return GLYPH_ENERGYRESTORER;
	if ( strcmp( value, "Refresher" ) == 0 || strcmp( value, "GLYPH_REFRESHER" ) == 0 )
		return GLYPH_REFRESHER;
	if ( strcmp( value, "Booster" ) == 0 || strcmp( value, "GLYPH_BOOSTER" ) == 0 )
		return GLYPH_BOOSTER;
	if ( strcmp( value, "Invisibler" ) == 0 || strcmp( value, "GLYPH_INVISIBLER" ) == 0 )
		return GLYPH_INVISIBLER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGlyph", value ) );
	return GLYPH_DOUBLEDAMAGER;
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
const char *EnumToString( const ESelectionAoeVisualType value )
{
	switch( value )
	{
		case SELECTIONAOEVISUALTYPE_PRIMARY:
			return "Primary";
		case SELECTIONAOEVISUALTYPE_SECONDARY:
			return "Secondary";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESelectionAoeVisualType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESelectionAoeVisualType StringToEnum_ESelectionAoeVisualType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESelectionAoeVisualType)(NStr::ToInt( value ));
	if ( strcmp( value, "Primary" ) == 0 || strcmp( value, "SELECTIONAOEVISUALTYPE_PRIMARY" ) == 0 )
		return SELECTIONAOEVISUALTYPE_PRIMARY;
	if ( strcmp( value, "Secondary" ) == 0 || strcmp( value, "SELECTIONAOEVISUALTYPE_SECONDARY" ) == 0 )
		return SELECTIONAOEVISUALTYPE_SECONDARY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESelectionAoeVisualType", value ) );
	return SELECTIONAOEVISUALTYPE_PRIMARY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESpawnType value )
{
	switch( value )
	{
		case SPAWNTYPE_BEFORE:
			return "Before";
		case SPAWNTYPE_AFTER:
			return "After";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESpawnType StringToEnum_ESpawnType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESpawnType)(NStr::ToInt( value ));
	if ( strcmp( value, "Before" ) == 0 || strcmp( value, "SPAWNTYPE_BEFORE" ) == 0 )
		return SPAWNTYPE_BEFORE;
	if ( strcmp( value, "After" ) == 0 || strcmp( value, "SPAWNTYPE_AFTER" ) == 0 )
		return SPAWNTYPE_AFTER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESpawnType", value ) );
	return SPAWNTYPE_BEFORE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitCategory value )
{
	switch( value )
	{
		case UNITCATEGORY_INVALID:
			return "Invalid";
		case UNITCATEGORY_HEROES:
			return "Heroes";
		case UNITCATEGORY_CREEPS:
			return "Creeps";
		case UNITCATEGORY_BUILDINGS:
			return "Buildings";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitCategory", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitCategory StringToEnum_EUnitCategory( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitCategory)(NStr::ToInt( value ));
	if ( strcmp( value, "Invalid" ) == 0 || strcmp( value, "UNITCATEGORY_INVALID" ) == 0 )
		return UNITCATEGORY_INVALID;
	if ( strcmp( value, "Heroes" ) == 0 || strcmp( value, "UNITCATEGORY_HEROES" ) == 0 )
		return UNITCATEGORY_HEROES;
	if ( strcmp( value, "Creeps" ) == 0 || strcmp( value, "UNITCATEGORY_CREEPS" ) == 0 )
		return UNITCATEGORY_CREEPS;
	if ( strcmp( value, "Buildings" ) == 0 || strcmp( value, "UNITCATEGORY_BUILDINGS" ) == 0 )
		return UNITCATEGORY_BUILDINGS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitCategory", value ) );
	return UNITCATEGORY_INVALID;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MapForceStatModifierApplication value )
{
	switch( value )
	{
		case MAPFORCESTATMODIFIERAPPLICATION_NONE:
			return "None";
		case MAPFORCESTATMODIFIERAPPLICATION_BASE:
			return "Base";
		case MAPFORCESTATMODIFIERAPPLICATION_LEVELUP:
			return "LevelUp";
		case MAPFORCESTATMODIFIERAPPLICATION_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MapForceStatModifierApplication StringToEnum_MapForceStatModifierApplication( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MapForceStatModifierApplication)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MAPFORCESTATMODIFIERAPPLICATION_NONE" ) == 0 )
		return MAPFORCESTATMODIFIERAPPLICATION_NONE;
	if ( strcmp( value, "Base" ) == 0 || strcmp( value, "MAPFORCESTATMODIFIERAPPLICATION_BASE" ) == 0 )
		return MAPFORCESTATMODIFIERAPPLICATION_BASE;
	if ( strcmp( value, "LevelUp" ) == 0 || strcmp( value, "MAPFORCESTATMODIFIERAPPLICATION_LEVELUP" ) == 0 )
		return MAPFORCESTATMODIFIERAPPLICATION_LEVELUP;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "MAPFORCESTATMODIFIERAPPLICATION_ALL" ) == 0 )
		return MAPFORCESTATMODIFIERAPPLICATION_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MapForceStatModifierApplication", value ) );
	return MAPFORCESTATMODIFIERAPPLICATION_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NeutralSpawnObject::NeutralSpawnObject() :
		waveDelayToAppear( 0 )
	, useSpawnerWalkLimit( true )
	, limitWalkDistance( -1.0f )
	, specialAwarding( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NeutralSpawnObject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &creep );
	saver.Add( 3, &offset );
	saver.Add( 4, &waveDelayToAppear );
	saver.Add( 5, &useSpawnerWalkLimit );
	saver.Add( 6, &limitWalkDistance );
	saver.Add( 7, &specialAwarding );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NeutralSpawnObject::operator&( IXmlSaver &saver )
{
	saver.Add( "creep", &creep );
	saver.Add( "offset", &offset );
	saver.Add( "waveDelayToAppear", &waveDelayToAppear );
	saver.Add( "useSpawnerWalkLimit", &useSpawnerWalkLimit );
	saver.Add( "limitWalkDistance", &limitWalkDistance );
	saver.Add( "specialAwarding", &specialAwarding );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AskSettings::AskSettings() :
		minInterval( 3.0f )
	, ask3dRecipient( ASKRECIPIENT_ENEMIES )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minInterval );
	saver.Add( 3, &ask3dRecipient );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "minInterval", &minInterval );
	saver.Add( "ask3dRecipient", &ask3dRecipient );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AskSounds::AskSounds()
{
	sounds.resize( 14 );
	sounds3d.resize( 14 );
	settings.resize( 14 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSounds::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sounds );
	saver.Add( 3, &sounds3d );
	saver.Add( 4, &settings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSounds::operator&( IXmlSaver &saver )
{
	sounds.resize( 14 );
	saver.Add( "sounds", &sounds );
	sounds3d.resize( 14 );
	saver.Add( "sounds3d", &sounds3d );
	settings.resize( 14 );
	saver.Add( "settings", &settings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvadeData::EvadeData() :
		waitForEvadeTime( 3.0f )
	, waitForNextTargetTime( 3.0f )
	, evadeTimeout( 60.0f )
	, restoreHealthPercent( 0.2f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvadeData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &waitForEvadeTime );
	saver.Add( 3, &waitForNextTargetTime );
	saver.Add( 4, &evadeTimeout );
	saver.Add( 5, &restoreHealthPercent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvadeData::operator&( IXmlSaver &saver )
{
	saver.Add( "waitForEvadeTime", &waitForEvadeTime );
	saver.Add( "waitForNextTargetTime", &waitForNextTargetTime );
	saver.Add( "evadeTimeout", &evadeTimeout );
	saver.Add( "restoreHealthPercent", &restoreHealthPercent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlyphEntry::GlyphEntry() :
		weight( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphEntry::operator&( IBinSaver &saver )
{
	saver.Add( 2, &glyph );
	saver.Add( 3, &weight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphEntry::operator&( IXmlSaver &saver )
{
	saver.Add( "glyph", &glyph );
	saver.Add( "weight", &weight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LevelDiffModifier::LevelDiffModifier() :
		difference( 0 )
	, modifier( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelDiffModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &difference );
	saver.Add( 3, &modifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelDiffModifier::operator&( IXmlSaver &saver )
{
	saver.Add( "difference", &difference );
	saver.Add( "modifier", &modifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LevelUpInfo::LevelUpInfo() :
		lifetimeLevelUp( false )
	, interval( -1.0f )
	, increment( -1 )
	, spawnLevelUpInterval( 0 )
	, spawnLevelUpIncrement( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelUpInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lifetimeLevelUp );
	saver.Add( 3, &interval );
	saver.Add( 4, &increment );
	saver.Add( 5, &spawnLevelUpInterval );
	saver.Add( 6, &spawnLevelUpIncrement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelUpInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "lifetimeLevelUp", &lifetimeLevelUp );
	saver.Add( "interval", &interval );
	saver.Add( "increment", &increment );
	saver.Add( "spawnLevelUpInterval", &spawnLevelUpInterval );
	saver.Add( "spawnLevelUpIncrement", &spawnLevelUpIncrement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapNeutralCreepsGroup::AdvMapNeutralCreepsGroup()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapNeutralCreepsGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &creeps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapNeutralCreepsGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "creeps", &creeps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpawnObject::SpawnObject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpawnObject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &creep );
	saver.Add( 3, &place );
	saver.Add( 4, &timer );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpawnObject::operator&( IXmlSaver &saver )
{
	saver.Add( "creep", &creep );
	saver.Add( "place", &place );
	saver.Add( "timer", &timer );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonedUnits::SummonedUnits()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonedUnits::operator&( IBinSaver &saver )
{
	saver.Add( 2, &unitA );
	saver.Add( 3, &unitB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonedUnits::operator&( IXmlSaver &saver )
{
	saver.Add( "unitA", &unitA );
	saver.Add( "unitB", &unitB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TransactionEffects::TransactionEffects()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TransactionEffects::operator&( IBinSaver &saver )
{
	saver.Add( 2, &effectIn );
	saver.Add( 3, &effectOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TransactionEffects::operator&( IXmlSaver &saver )
{
	saver.Add( "effectIn", &effectIn );
	saver.Add( "effectOut", &effectOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitCategoryParams::UnitCategoryParams() :
		selectionPriority( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategoryParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &selectionPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategoryParams::operator&( IXmlSaver &saver )
{
	saver.Add( "selectionPriority", &selectionPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleStateObject::SingleStateObject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleStateObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &sceneObject );

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
	saver.Add( "sceneObject", &sceneObject );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleStateObject::Assign( const SingleStateObject& _singleStateObject )
{
	sceneObject = _singleStateObject.sceneObject;
	collision = _singleStateObject.collision;
	lockMask.tileSize = _singleStateObject.lockMask.tileSize;
	lockMask.mask = _singleStateObject.lockMask.mask;
	minLockScale = _singleStateObject.minLockScale;
	rounded = _singleStateObject.rounded;
	heightObject = _singleStateObject.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseCreepSpawner::BaseCreepSpawner() :
		firstSpawnTimeOffset( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseCreepSpawner::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &levelUpInfo );
	saver.Add( 3, &firstSpawnTimeOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseCreepSpawner::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BaseCreepSpawner* parentPtr = (BaseCreepSpawner*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseCreepSpawner::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "levelUpInfo", &levelUpInfo );
	saver.Add( "firstSpawnTimeOffset", &firstSpawnTimeOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseCreepSpawner::Assign( const BaseCreepSpawner& _baseCreepSpawner )
{
	levelUpInfo.lifetimeLevelUp = _baseCreepSpawner.levelUpInfo.lifetimeLevelUp;
	levelUpInfo.interval = _baseCreepSpawner.levelUpInfo.interval;
	levelUpInfo.increment = _baseCreepSpawner.levelUpInfo.increment;
	levelUpInfo.spawnLevelUpInterval = _baseCreepSpawner.levelUpInfo.spawnLevelUpInterval;
	levelUpInfo.spawnLevelUpIncrement = _baseCreepSpawner.levelUpInfo.spawnLevelUpIncrement;
	firstSpawnTimeOffset = _baseCreepSpawner.firstSpawnTimeOffset;
	collision = _baseCreepSpawner.collision;
	lockMask.tileSize = _baseCreepSpawner.lockMask.tileSize;
	lockMask.mask = _baseCreepSpawner.lockMask.mask;
	minLockScale = _baseCreepSpawner.minLockScale;
	rounded = _baseCreepSpawner.rounded;
	heightObject = _baseCreepSpawner.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapNeutralCreepSpawner::AdvMapNeutralCreepSpawner() :
		spawnDelay( 45 )
	, waveCount( 0 )
	, baseLevel( 0 )
	, naftaForGroupKill( 0 )
	, minimapIcon( MINIMAPICONS_DEFAULT )
	, showMinimapIcon( true )
	, limitWalkDistance( -1.0f )
	, useEvade( true )
	, isAggressive( false )
	, mapForceStatModifierApplication( MAPFORCESTATMODIFIERAPPLICATION_ALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapNeutralCreepSpawner::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseCreepSpawner*)this );
	saver.Add( 2, &groups );
	saver.Add( 3, &spawnDelay );
	saver.Add( 4, &waveCount );
	saver.Add( 5, &baseLevel );
	saver.Add( 6, &naftaForGroupKill );
	saver.Add( 7, &minimapIcon );
	saver.Add( 8, &showMinimapIcon );
	saver.Add( 9, &path );
	saver.Add( 10, &limitWalkDistance );
	saver.Add( 11, &useEvade );
	saver.Add( 12, &evadeParams );
	saver.Add( 13, &isAggressive );
	saver.Add( 14, &mapForceStatModifierApplication );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapNeutralCreepSpawner::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapNeutralCreepSpawner* parentPtr = (AdvMapNeutralCreepSpawner*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapNeutralCreepSpawner::SerializeSelf( IXmlSaver &saver )
{
	BaseCreepSpawner::SerializeSelf( saver );
	saver.Add( "groups", &groups );
	saver.Add( "spawnDelay", &spawnDelay );
	saver.Add( "waveCount", &waveCount );
	saver.Add( "baseLevel", &baseLevel );
	saver.Add( "naftaForGroupKill", &naftaForGroupKill );
	saver.Add( "minimapIcon", &minimapIcon );
	saver.Add( "showMinimapIcon", &showMinimapIcon );
	saver.Add( "path", &path );
	saver.Add( "limitWalkDistance", &limitWalkDistance );
	saver.Add( "useEvade", &useEvade );
	saver.Add( "evadeParams", &evadeParams );
	saver.Add( "isAggressive", &isAggressive );
	saver.Add( "mapForceStatModifierApplication", &mapForceStatModifierApplication );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapNeutralCreepSpawner::Assign( const AdvMapNeutralCreepSpawner& _advMapNeutralCreepSpawner )
{
	groups = _advMapNeutralCreepSpawner.groups;
	spawnDelay = _advMapNeutralCreepSpawner.spawnDelay;
	waveCount = _advMapNeutralCreepSpawner.waveCount;
	baseLevel = _advMapNeutralCreepSpawner.baseLevel;
	naftaForGroupKill = _advMapNeutralCreepSpawner.naftaForGroupKill;
	minimapIcon = _advMapNeutralCreepSpawner.minimapIcon;
	showMinimapIcon = _advMapNeutralCreepSpawner.showMinimapIcon;
	path = _advMapNeutralCreepSpawner.path;
	limitWalkDistance = _advMapNeutralCreepSpawner.limitWalkDistance;
	useEvade = _advMapNeutralCreepSpawner.useEvade;
	evadeParams.waitForEvadeTime = _advMapNeutralCreepSpawner.evadeParams.waitForEvadeTime;
	evadeParams.waitForNextTargetTime = _advMapNeutralCreepSpawner.evadeParams.waitForNextTargetTime;
	evadeParams.evadeTimeout = _advMapNeutralCreepSpawner.evadeParams.evadeTimeout;
	evadeParams.restoreHealthPercent = _advMapNeutralCreepSpawner.evadeParams.restoreHealthPercent;
	isAggressive = _advMapNeutralCreepSpawner.isAggressive;
	mapForceStatModifierApplication = _advMapNeutralCreepSpawner.mapForceStatModifierApplication;
	levelUpInfo.lifetimeLevelUp = _advMapNeutralCreepSpawner.levelUpInfo.lifetimeLevelUp;
	levelUpInfo.interval = _advMapNeutralCreepSpawner.levelUpInfo.interval;
	levelUpInfo.increment = _advMapNeutralCreepSpawner.levelUpInfo.increment;
	levelUpInfo.spawnLevelUpInterval = _advMapNeutralCreepSpawner.levelUpInfo.spawnLevelUpInterval;
	levelUpInfo.spawnLevelUpIncrement = _advMapNeutralCreepSpawner.levelUpInfo.spawnLevelUpIncrement;
	firstSpawnTimeOffset = _advMapNeutralCreepSpawner.firstSpawnTimeOffset;
	collision = _advMapNeutralCreepSpawner.collision;
	lockMask.tileSize = _advMapNeutralCreepSpawner.lockMask.tileSize;
	lockMask.mask = _advMapNeutralCreepSpawner.lockMask.mask;
	minLockScale = _advMapNeutralCreepSpawner.minLockScale;
	rounded = _advMapNeutralCreepSpawner.rounded;
	heightObject = _advMapNeutralCreepSpawner.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapObstacle::AdvMapObstacle() :
		opaque( false )
	, LockMode( BOOLEANLOCKMODE_LOCK )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapObstacle::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &opaque );
	saver.Add( 3, &LockMode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapObstacle::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapObstacle* parentPtr = (AdvMapObstacle*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapObstacle::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "opaque", &opaque );
	saver.Add( "LockMode", &LockMode );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapObstacle::Assign( const AdvMapObstacle& _advMapObstacle )
{
	opaque = _advMapObstacle.opaque;
	LockMode = _advMapObstacle.LockMode;
	collision = _advMapObstacle.collision;
	lockMask.tileSize = _advMapObstacle.lockMask.tileSize;
	lockMask.mask = _advMapObstacle.lockMask.mask;
	minLockScale = _advMapObstacle.minLockScale;
	rounded = _advMapObstacle.rounded;
	heightObject = _advMapObstacle.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AoeVisual::AoeVisual()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AoeVisual::operator&( IBinSaver &saver )
{
	saver.Add( 2, &size );
	saver.Add( 3, &enabled );
	saver.Add( 4, &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AoeVisual::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AoeVisual* parentPtr = (AoeVisual*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AoeVisual::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "size", &size );
	saver.Add( "enabled", &enabled );
	saver.Add( "material", &material );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AoeVisual::Assign( const AoeVisual& _aoeVisual )
{
	size = _aoeVisual.size;
	enabled = _aoeVisual.enabled;
	material = _aoeVisual.material;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AskSoundsRef::AskSoundsRef()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSoundsRef::operator&( IBinSaver &saver )
{
	saver.Add( 2, &asks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AskSoundsRef::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AskSoundsRef* parentPtr = (AskSoundsRef*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AskSoundsRef::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "asks", &asks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AskSoundsRef::Assign( const AskSoundsRef& _askSoundsRef )
{
	asks.sounds = _askSoundsRef.asks.sounds;
	asks.sounds3d = _askSoundsRef.asks.sounds3d;
	asks.settings = _askSoundsRef.asks.settings;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapCreepSpawner::AdvMapCreepSpawner() :
		faction( FACTION_NEUTRAL )
	, routeID( ROUTE_CENTER )
	, mustRegisterInAIWorld( true )
	, useEvade( true )
	, limitWalkDistance( -1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCreepSpawner::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseCreepSpawner*)this );
	saver.Add( 2, &creeps );
	saver.Add( 3, &path );
	saver.Add( 4, &faction );
	saver.Add( 5, &routeID );
	saver.Add( 6, &mustRegisterInAIWorld );
	saver.Add( 7, &useEvade );
	saver.Add( 8, &evadeParams );
	saver.Add( 9, &limitWalkDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCreepSpawner::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapCreepSpawner* parentPtr = (AdvMapCreepSpawner*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCreepSpawner::SerializeSelf( IXmlSaver &saver )
{
	BaseCreepSpawner::SerializeSelf( saver );
	saver.Add( "creeps", &creeps );
	saver.Add( "path", &path );
	saver.Add( "faction", &faction );
	saver.Add( "routeID", &routeID );
	saver.Add( "mustRegisterInAIWorld", &mustRegisterInAIWorld );
	saver.Add( "useEvade", &useEvade );
	saver.Add( "evadeParams", &evadeParams );
	saver.Add( "limitWalkDistance", &limitWalkDistance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCreepSpawner::Assign( const AdvMapCreepSpawner& _advMapCreepSpawner )
{
	creeps = _advMapCreepSpawner.creeps;
	path = _advMapCreepSpawner.path;
	faction = _advMapCreepSpawner.faction;
	routeID = _advMapCreepSpawner.routeID;
	mustRegisterInAIWorld = _advMapCreepSpawner.mustRegisterInAIWorld;
	useEvade = _advMapCreepSpawner.useEvade;
	evadeParams.waitForEvadeTime = _advMapCreepSpawner.evadeParams.waitForEvadeTime;
	evadeParams.waitForNextTargetTime = _advMapCreepSpawner.evadeParams.waitForNextTargetTime;
	evadeParams.evadeTimeout = _advMapCreepSpawner.evadeParams.evadeTimeout;
	evadeParams.restoreHealthPercent = _advMapCreepSpawner.evadeParams.restoreHealthPercent;
	limitWalkDistance = _advMapCreepSpawner.limitWalkDistance;
	levelUpInfo.lifetimeLevelUp = _advMapCreepSpawner.levelUpInfo.lifetimeLevelUp;
	levelUpInfo.interval = _advMapCreepSpawner.levelUpInfo.interval;
	levelUpInfo.increment = _advMapCreepSpawner.levelUpInfo.increment;
	levelUpInfo.spawnLevelUpInterval = _advMapCreepSpawner.levelUpInfo.spawnLevelUpInterval;
	levelUpInfo.spawnLevelUpIncrement = _advMapCreepSpawner.levelUpInfo.spawnLevelUpIncrement;
	firstSpawnTimeOffset = _advMapCreepSpawner.firstSpawnTimeOffset;
	collision = _advMapCreepSpawner.collision;
	lockMask.tileSize = _advMapCreepSpawner.lockMask.tileSize;
	lockMask.mask = _advMapCreepSpawner.lockMask.mask;
	minLockScale = _advMapCreepSpawner.minLockScale;
	rounded = _advMapCreepSpawner.rounded;
	heightObject = _advMapCreepSpawner.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Unit::Unit() :
		overtipBarsWidth( 0 )
	, overtipVerticalOffset( 0.0f )
	, nativeAttack( DAMAGETYPE_MATERIAL )
	, nativeDefence( DAMAGETYPE_MATERIAL )
	, size( 2.0f )
	, sizeDynamic( -1.0f )
	, normalLevelling( 0.0f )
	, minimapIcon( MINIMAPICONS_DEFAULT )
	, pathFindingSteps( 1 )
{
	abilities.resize( 5 );
	selectionAoe.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Unit::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleStateObject*)this );
	saver.Add( 2, &stats );
	saver.Add( 3, &targetingParams );
	saver.Add( 4, &attackAbility );
	saver.Add( 5, &description );
	saver.Add( 6, &image );
	saver.Add( 7, &overtipBarsWidth );
	saver.Add( 8, &overtipVerticalOffset );
	saver.Add( 9, &nativeAttack );
	saver.Add( 10, &nativeDefence );
	saver.Add( 11, &deathParameters );
	saver.Add( 12, &abilities );
	saver.Add( 13, &size );
	saver.Add( 14, &sizeDynamic );
	saver.Add( 15, &normalLevelling );
	saver.Add( 16, &minimapIcon );
	saver.Add( 17, &selectionAoe );
	saver.Add( 18, &pathFindingSteps );
	saver.Add( 19, &interaction );

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
	saver.Add( "stats", &stats );
	saver.Add( "targetingParams", &targetingParams );
	saver.Add( "attackAbility", &attackAbility );
	saver.Add( "description", &description );
	saver.Add( "image", &image );
	saver.Add( "overtipBarsWidth", &overtipBarsWidth );
	saver.Add( "overtipVerticalOffset", &overtipVerticalOffset );
	saver.Add( "nativeAttack", &nativeAttack );
	saver.Add( "nativeDefence", &nativeDefence );
	saver.Add( "deathParameters", &deathParameters );
	abilities.resize( 5 );
	saver.Add( "abilities", &abilities );
	saver.Add( "size", &size );
	saver.Add( "sizeDynamic", &sizeDynamic );
	saver.Add( "normalLevelling", &normalLevelling );
	saver.Add( "minimapIcon", &minimapIcon );
	selectionAoe.resize( 2 );
	saver.Add( "selectionAoe", &selectionAoe );
	saver.Add( "pathFindingSteps", &pathFindingSteps );
	saver.Add( "interaction", &interaction );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Unit::Assign( const Unit& _unit )
{
	stats = _unit.stats;
	targetingParams = _unit.targetingParams;
	attackAbility = _unit.attackAbility;
	description = _unit.description;
	image = _unit.image;
	overtipBarsWidth = _unit.overtipBarsWidth;
	overtipVerticalOffset = _unit.overtipVerticalOffset;
	nativeAttack = _unit.nativeAttack;
	nativeDefence = _unit.nativeDefence;
	deathParameters = _unit.deathParameters;
	abilities = _unit.abilities;
	size = _unit.size;
	sizeDynamic = _unit.sizeDynamic;
	normalLevelling = _unit.normalLevelling;
	minimapIcon = _unit.minimapIcon;
	selectionAoe = _unit.selectionAoe;
	pathFindingSteps = _unit.pathFindingSteps;
	interaction = _unit.interaction;
	sceneObject = _unit.sceneObject;
	collision = _unit.collision;
	lockMask.tileSize = _unit.lockMask.tileSize;
	lockMask.mask = _unit.lockMask.mask;
	minLockScale = _unit.minLockScale;
	rounded = _unit.rounded;
	heightObject = _unit.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Creature::Creature()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Creature::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Unit*)this );
	saver.Add( 2, &recolor );

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
	saver.Add( "recolor", &recolor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Creature::Assign( const Creature& _creature )
{
	recolor = _creature.recolor;
	stats = _creature.stats;
	targetingParams = _creature.targetingParams;
	attackAbility = _creature.attackAbility;
	description = _creature.description;
	image = _creature.image;
	overtipBarsWidth = _creature.overtipBarsWidth;
	overtipVerticalOffset = _creature.overtipVerticalOffset;
	nativeAttack = _creature.nativeAttack;
	nativeDefence = _creature.nativeDefence;
	deathParameters = _creature.deathParameters;
	abilities = _creature.abilities;
	size = _creature.size;
	sizeDynamic = _creature.sizeDynamic;
	normalLevelling = _creature.normalLevelling;
	minimapIcon = _creature.minimapIcon;
	selectionAoe = _creature.selectionAoe;
	pathFindingSteps = _creature.pathFindingSteps;
	interaction = _creature.interaction;
	sceneObject = _creature.sceneObject;
	collision = _creature.collision;
	lockMask.tileSize = _creature.lockMask.tileSize;
	lockMask.mask = _creature.lockMask.mask;
	minLockScale = _creature.minLockScale;
	rounded = _creature.rounded;
	heightObject = _creature.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Building::Building() :
		faction( FACTION_NEUTRAL )
	, routeID( ROUTE_UNASSIGNED )
	, routeLevel( 0 )
	, showRuinDelay( 0.0f )
	, ruinLocator( "Crash" )
	, isDecoration( false )
	, levelUpInterval( 0.0f )
	, updateUnderWarfog( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Building::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Unit*)this );
	saver.Add( 2, &faction );
	saver.Add( 3, &routeID );
	saver.Add( 4, &routeLevel );
	saver.Add( 5, &ruinSceneObject );
	saver.Add( 6, &showRuinDelay );
	saver.Add( 7, &ruinLocator );
	saver.Add( 8, &onDamageFragEffect );
	saver.Add( 9, &onDestructionEffect );
	saver.Add( 10, &isDecoration );
	saver.Add( 11, &minimapIconOffset );
	saver.Add( 12, &levelUpInterval );
	saver.Add( 13, &updateUnderWarfog );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Building::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Building* parentPtr = (Building*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Building::SerializeSelf( IXmlSaver &saver )
{
	Unit::SerializeSelf( saver );
	saver.Add( "faction", &faction );
	saver.Add( "routeID", &routeID );
	saver.Add( "routeLevel", &routeLevel );
	saver.Add( "ruinSceneObject", &ruinSceneObject );
	saver.Add( "showRuinDelay", &showRuinDelay );
	saver.Add( "ruinLocator", &ruinLocator );
	saver.Add( "onDamageFragEffect", &onDamageFragEffect );
	saver.Add( "onDestructionEffect", &onDestructionEffect );
	saver.Add( "isDecoration", &isDecoration );
	saver.Add( "minimapIconOffset", &minimapIconOffset );
	saver.Add( "levelUpInterval", &levelUpInterval );
	saver.Add( "updateUnderWarfog", &updateUnderWarfog );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Building::Assign( const Building& _building )
{
	faction = _building.faction;
	routeID = _building.routeID;
	routeLevel = _building.routeLevel;
	ruinSceneObject = _building.ruinSceneObject;
	showRuinDelay = _building.showRuinDelay;
	ruinLocator = _building.ruinLocator;
	onDamageFragEffect = _building.onDamageFragEffect;
	onDestructionEffect = _building.onDestructionEffect;
	isDecoration = _building.isDecoration;
	minimapIconOffset = _building.minimapIconOffset;
	levelUpInterval = _building.levelUpInterval;
	updateUnderWarfog = _building.updateUnderWarfog;
	stats = _building.stats;
	targetingParams = _building.targetingParams;
	attackAbility = _building.attackAbility;
	description = _building.description;
	image = _building.image;
	overtipBarsWidth = _building.overtipBarsWidth;
	overtipVerticalOffset = _building.overtipVerticalOffset;
	nativeAttack = _building.nativeAttack;
	nativeDefence = _building.nativeDefence;
	deathParameters = _building.deathParameters;
	abilities = _building.abilities;
	size = _building.size;
	sizeDynamic = _building.sizeDynamic;
	normalLevelling = _building.normalLevelling;
	minimapIcon = _building.minimapIcon;
	selectionAoe = _building.selectionAoe;
	pathFindingSteps = _building.pathFindingSteps;
	interaction = _building.interaction;
	sceneObject = _building.sceneObject;
	collision = _building.collision;
	lockMask.tileSize = _building.lockMask.tileSize;
	lockMask.mask = _building.lockMask.mask;
	minLockScale = _building.minLockScale;
	rounded = _building.rounded;
	heightObject = _building.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BattleBuilding::BattleBuilding() :
		baseRotation( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BattleBuilding::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );
	saver.Add( 2, &baseRotation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BattleBuilding::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BattleBuilding* parentPtr = (BattleBuilding*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BattleBuilding::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
	saver.Add( "baseRotation", &baseRotation );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BattleBuilding::Assign( const BattleBuilding& _battleBuilding )
{
	baseRotation = _battleBuilding.baseRotation;
	faction = _battleBuilding.faction;
	routeID = _battleBuilding.routeID;
	routeLevel = _battleBuilding.routeLevel;
	ruinSceneObject = _battleBuilding.ruinSceneObject;
	showRuinDelay = _battleBuilding.showRuinDelay;
	ruinLocator = _battleBuilding.ruinLocator;
	onDamageFragEffect = _battleBuilding.onDamageFragEffect;
	onDestructionEffect = _battleBuilding.onDestructionEffect;
	isDecoration = _battleBuilding.isDecoration;
	minimapIconOffset = _battleBuilding.minimapIconOffset;
	levelUpInterval = _battleBuilding.levelUpInterval;
	updateUnderWarfog = _battleBuilding.updateUnderWarfog;
	stats = _battleBuilding.stats;
	targetingParams = _battleBuilding.targetingParams;
	attackAbility = _battleBuilding.attackAbility;
	description = _battleBuilding.description;
	image = _battleBuilding.image;
	overtipBarsWidth = _battleBuilding.overtipBarsWidth;
	overtipVerticalOffset = _battleBuilding.overtipVerticalOffset;
	nativeAttack = _battleBuilding.nativeAttack;
	nativeDefence = _battleBuilding.nativeDefence;
	deathParameters = _battleBuilding.deathParameters;
	abilities = _battleBuilding.abilities;
	size = _battleBuilding.size;
	sizeDynamic = _battleBuilding.sizeDynamic;
	normalLevelling = _battleBuilding.normalLevelling;
	minimapIcon = _battleBuilding.minimapIcon;
	selectionAoe = _battleBuilding.selectionAoe;
	pathFindingSteps = _battleBuilding.pathFindingSteps;
	interaction = _battleBuilding.interaction;
	sceneObject = _battleBuilding.sceneObject;
	collision = _battleBuilding.collision;
	lockMask.tileSize = _battleBuilding.lockMask.tileSize;
	lockMask.mask = _battleBuilding.lockMask.mask;
	minLockScale = _battleBuilding.minLockScale;
	rounded = _battleBuilding.rounded;
	heightObject = _battleBuilding.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tower::Tower()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Tower::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BattleBuilding*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Tower::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Tower* parentPtr = (Tower*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower::SerializeSelf( IXmlSaver &saver )
{
	BattleBuilding::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower::Assign( const Tower& _tower )
{
	baseRotation = _tower.baseRotation;
	faction = _tower.faction;
	routeID = _tower.routeID;
	routeLevel = _tower.routeLevel;
	ruinSceneObject = _tower.ruinSceneObject;
	showRuinDelay = _tower.showRuinDelay;
	ruinLocator = _tower.ruinLocator;
	onDamageFragEffect = _tower.onDamageFragEffect;
	onDestructionEffect = _tower.onDestructionEffect;
	isDecoration = _tower.isDecoration;
	minimapIconOffset = _tower.minimapIconOffset;
	levelUpInterval = _tower.levelUpInterval;
	updateUnderWarfog = _tower.updateUnderWarfog;
	stats = _tower.stats;
	targetingParams = _tower.targetingParams;
	attackAbility = _tower.attackAbility;
	description = _tower.description;
	image = _tower.image;
	overtipBarsWidth = _tower.overtipBarsWidth;
	overtipVerticalOffset = _tower.overtipVerticalOffset;
	nativeAttack = _tower.nativeAttack;
	nativeDefence = _tower.nativeDefence;
	deathParameters = _tower.deathParameters;
	abilities = _tower.abilities;
	size = _tower.size;
	sizeDynamic = _tower.sizeDynamic;
	normalLevelling = _tower.normalLevelling;
	minimapIcon = _tower.minimapIcon;
	selectionAoe = _tower.selectionAoe;
	pathFindingSteps = _tower.pathFindingSteps;
	interaction = _tower.interaction;
	sceneObject = _tower.sceneObject;
	collision = _tower.collision;
	lockMask.tileSize = _tower.lockMask.tileSize;
	lockMask.mask = _tower.lockMask.mask;
	minLockScale = _tower.minLockScale;
	rounded = _tower.rounded;
	heightObject = _tower.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapCreep::AdvMapCreep() :
		creepType( CREEPTYPE_FACTIONALNORMAL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCreep::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Creature*)this );
	saver.Add( 2, &creepType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCreep::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapCreep* parentPtr = (AdvMapCreep*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCreep::SerializeSelf( IXmlSaver &saver )
{
	Creature::SerializeSelf( saver );
	saver.Add( "creepType", &creepType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCreep::Assign( const AdvMapCreep& _advMapCreep )
{
	creepType = _advMapCreep.creepType;
	recolor = _advMapCreep.recolor;
	stats = _advMapCreep.stats;
	targetingParams = _advMapCreep.targetingParams;
	attackAbility = _advMapCreep.attackAbility;
	description = _advMapCreep.description;
	image = _advMapCreep.image;
	overtipBarsWidth = _advMapCreep.overtipBarsWidth;
	overtipVerticalOffset = _advMapCreep.overtipVerticalOffset;
	nativeAttack = _advMapCreep.nativeAttack;
	nativeDefence = _advMapCreep.nativeDefence;
	deathParameters = _advMapCreep.deathParameters;
	abilities = _advMapCreep.abilities;
	size = _advMapCreep.size;
	sizeDynamic = _advMapCreep.sizeDynamic;
	normalLevelling = _advMapCreep.normalLevelling;
	minimapIcon = _advMapCreep.minimapIcon;
	selectionAoe = _advMapCreep.selectionAoe;
	pathFindingSteps = _advMapCreep.pathFindingSteps;
	interaction = _advMapCreep.interaction;
	sceneObject = _advMapCreep.sceneObject;
	collision = _advMapCreep.collision;
	lockMask.tileSize = _advMapCreep.lockMask.tileSize;
	lockMask.mask = _advMapCreep.lockMask.mask;
	minLockScale = _advMapCreep.minLockScale;
	rounded = _advMapCreep.rounded;
	heightObject = _advMapCreep.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepSkin::CreepSkin()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepSkin::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroPersistentId );
	saver.Add( 3, &description );
	saver.Add( 4, &image );
	saver.Add( 5, &sceneObject );
	saver.Add( 6, &deathParameters );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepSkin::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CreepSkin* parentPtr = (CreepSkin*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepSkin::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "heroPersistentId", &heroPersistentId );
	saver.Add( "description", &description );
	saver.Add( "image", &image );
	saver.Add( "sceneObject", &sceneObject );
	saver.Add( "deathParameters", &deathParameters );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepSkin::Assign( const CreepSkin& _creepSkin )
{
	heroPersistentId = _creepSkin.heroPersistentId;
	description = _creepSkin.description;
	image = _creepSkin.image;
	sceneObject = _creepSkin.sceneObject;
	deathParameters = _creepSkin.deathParameters;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepSpawnTimer::CreepSpawnTimer() :
		startDelay( 0 )
	, spawnDelay( 1 )
	, spawnType( ESpawnType( SPAWNTYPE_AFTER | SPAWNTYPE_BEFORE ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepSpawnTimer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startDelay );
	saver.Add( 3, &spawnDelay );
	saver.Add( 4, &spawnType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepSpawnTimer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CreepSpawnTimer* parentPtr = (CreepSpawnTimer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepSpawnTimer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "startDelay", &startDelay );
	saver.Add( "spawnDelay", &spawnDelay );
	saver.Add( "spawnType", &spawnType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepSpawnTimer::Assign( const CreepSpawnTimer& _creepSpawnTimer )
{
	startDelay = _creepSpawnTimer.startDelay;
	spawnDelay = _creepSpawnTimer.spawnDelay;
	spawnType = _creepSpawnTimer.spawnType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Critter::Critter() :
		moveRadius( 0.0f )
	, alarmRadius( 0.0f )
	, calmDownTime( 0.0f )
	, moveSpeed( 0.0f )
	, isVisibleUnderWarfog( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Critter::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleStateObject*)this );
	saver.Add( 2, &moveRadius );
	saver.Add( 3, &alarmRadius );
	saver.Add( 4, &calmDownTime );
	saver.Add( 5, &moveSpeed );
	saver.Add( 6, &isVisibleUnderWarfog );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Critter::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Critter* parentPtr = (Critter*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Critter::SerializeSelf( IXmlSaver &saver )
{
	SingleStateObject::SerializeSelf( saver );
	saver.Add( "moveRadius", &moveRadius );
	saver.Add( "alarmRadius", &alarmRadius );
	saver.Add( "calmDownTime", &calmDownTime );
	saver.Add( "moveSpeed", &moveSpeed );
	saver.Add( "isVisibleUnderWarfog", &isVisibleUnderWarfog );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Critter::Assign( const Critter& _critter )
{
	moveRadius = _critter.moveRadius;
	alarmRadius = _critter.alarmRadius;
	calmDownTime = _critter.calmDownTime;
	moveSpeed = _critter.moveSpeed;
	isVisibleUnderWarfog = _critter.isVisibleUnderWarfog;
	sceneObject = _critter.sceneObject;
	collision = _critter.collision;
	lockMask.tileSize = _critter.lockMask.tileSize;
	lockMask.mask = _critter.lockMask.mask;
	minLockScale = _critter.minLockScale;
	rounded = _critter.rounded;
	heightObject = _critter.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Flagpole::Flagpole()
{
	effect.resize( 2 );
	factionImages.resize( 2 );
	factionDescriptions.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Flagpole::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Unit*)this );
	saver.Add( 2, &ownerTowers );
	saver.Add( 3, &effect );
	saver.Add( 4, &factionImages );
	saver.Add( 5, &factionDescriptions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Flagpole::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Flagpole* parentPtr = (Flagpole*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Flagpole::SerializeSelf( IXmlSaver &saver )
{
	Unit::SerializeSelf( saver );
	saver.Add( "ownerTowers", &ownerTowers );
	effect.resize( 2 );
	saver.Add( "effect", &effect );
	factionImages.resize( 2 );
	saver.Add( "factionImages", &factionImages );
	factionDescriptions.resize( 2 );
	saver.Add( "factionDescriptions", &factionDescriptions );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Flagpole::Assign( const Flagpole& _flagpole )
{
	ownerTowers = _flagpole.ownerTowers;
	effect = _flagpole.effect;
	factionImages = _flagpole.factionImages;
	factionDescriptions = _flagpole.factionDescriptions;
	stats = _flagpole.stats;
	targetingParams = _flagpole.targetingParams;
	attackAbility = _flagpole.attackAbility;
	description = _flagpole.description;
	image = _flagpole.image;
	overtipBarsWidth = _flagpole.overtipBarsWidth;
	overtipVerticalOffset = _flagpole.overtipVerticalOffset;
	nativeAttack = _flagpole.nativeAttack;
	nativeDefence = _flagpole.nativeDefence;
	deathParameters = _flagpole.deathParameters;
	abilities = _flagpole.abilities;
	size = _flagpole.size;
	sizeDynamic = _flagpole.sizeDynamic;
	normalLevelling = _flagpole.normalLevelling;
	minimapIcon = _flagpole.minimapIcon;
	selectionAoe = _flagpole.selectionAoe;
	pathFindingSteps = _flagpole.pathFindingSteps;
	interaction = _flagpole.interaction;
	sceneObject = _flagpole.sceneObject;
	collision = _flagpole.collision;
	lockMask.tileSize = _flagpole.lockMask.tileSize;
	lockMask.mask = _flagpole.lockMask.mask;
	minLockScale = _flagpole.minLockScale;
	rounded = _flagpole.rounded;
	heightObject = _flagpole.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Fountain::Fountain()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Fountain::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Fountain::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Fountain* parentPtr = (Fountain*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Fountain::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Fountain::Assign( const Fountain& _fountain )
{
	faction = _fountain.faction;
	routeID = _fountain.routeID;
	routeLevel = _fountain.routeLevel;
	ruinSceneObject = _fountain.ruinSceneObject;
	showRuinDelay = _fountain.showRuinDelay;
	ruinLocator = _fountain.ruinLocator;
	onDamageFragEffect = _fountain.onDamageFragEffect;
	onDestructionEffect = _fountain.onDestructionEffect;
	isDecoration = _fountain.isDecoration;
	minimapIconOffset = _fountain.minimapIconOffset;
	levelUpInterval = _fountain.levelUpInterval;
	updateUnderWarfog = _fountain.updateUnderWarfog;
	stats = _fountain.stats;
	targetingParams = _fountain.targetingParams;
	attackAbility = _fountain.attackAbility;
	description = _fountain.description;
	image = _fountain.image;
	overtipBarsWidth = _fountain.overtipBarsWidth;
	overtipVerticalOffset = _fountain.overtipVerticalOffset;
	nativeAttack = _fountain.nativeAttack;
	nativeDefence = _fountain.nativeDefence;
	deathParameters = _fountain.deathParameters;
	abilities = _fountain.abilities;
	size = _fountain.size;
	sizeDynamic = _fountain.sizeDynamic;
	normalLevelling = _fountain.normalLevelling;
	minimapIcon = _fountain.minimapIcon;
	selectionAoe = _fountain.selectionAoe;
	pathFindingSteps = _fountain.pathFindingSteps;
	interaction = _fountain.interaction;
	sceneObject = _fountain.sceneObject;
	collision = _fountain.collision;
	lockMask.tileSize = _fountain.lockMask.tileSize;
	lockMask.mask = _fountain.lockMask.mask;
	minLockScale = _fountain.minLockScale;
	rounded = _fountain.rounded;
	heightObject = _fountain.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Glyph::Glyph() :
		id( GLYPH_DOUBLEDAMAGER )
	, naftaCost( 0 )
	, openWarFogRadius( 0.0f )
	, minimapIcon( MINIMAPICONS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Glyph::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Ability*)this );
	saver.Add( 2, &id );
	saver.Add( 3, &gameObject );
	saver.Add( 4, &color );
	saver.Add( 5, &naftaCost );
	saver.Add( 6, &openWarFogRadius );
	saver.Add( 7, &minimapIcon );
	saver.Add( 8, &pickupAbility );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Glyph::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Glyph* parentPtr = (Glyph*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Glyph::SerializeSelf( IXmlSaver &saver )
{
	Ability::SerializeSelf( saver );
	saver.Add( "id", &id );
	saver.Add( "gameObject", &gameObject );
	saver.Add( "color", &color );
	saver.Add( "naftaCost", &naftaCost );
	saver.Add( "openWarFogRadius", &openWarFogRadius );
	saver.Add( "minimapIcon", &minimapIcon );
	saver.Add( "pickupAbility", &pickupAbility );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Glyph::Assign( const Glyph& _glyph )
{
	id = _glyph.id;
	gameObject = _glyph.gameObject;
	color = _glyph.color;
	naftaCost = _glyph.naftaCost;
	openWarFogRadius = _glyph.openWarFogRadius;
	minimapIcon = _glyph.minimapIcon;
	pickupAbility = _glyph.pickupAbility;
	name = _glyph.name;
	description = _glyph.description;
	compiledDescriptionA = _glyph.compiledDescriptionA;
	compiledDescriptionB = _glyph.compiledDescriptionB;
	shortDescription = _glyph.shortDescription;
	commonDescription = _glyph.commonDescription;
	castLimitations = _glyph.castLimitations;
	image = _glyph.image;
	imageSecondState = _glyph.imageSecondState;
	aoeType = _glyph.aoeType;
	aoeSize = _glyph.aoeSize;
	aoeMaterial = _glyph.aoeMaterial;
	aoeHeight = _glyph.aoeHeight;
	useRangeMaterial = _glyph.useRangeMaterial;
	aoePassabilityCheckMode = _glyph.aoePassabilityCheckMode;
	aoeDisplayOnMinimap = _glyph.aoeDisplayOnMinimap;
	type = _glyph.type;
	cooldownTime = _glyph.cooldownTime;
	cooldownTimeSecondState = _glyph.cooldownTimeSecondState;
	manaCost = _glyph.manaCost;
	activeCustomTrigger = _glyph.activeCustomTrigger;
	useRange = _glyph.useRange;
	minUseRangeCorrection = _glyph.minUseRangeCorrection;
	castAllowRange = _glyph.castAllowRange;
	allowChase = _glyph.allowChase;
	constants = _glyph.constants;
	conditionFormulas = _glyph.conditionFormulas;
	isUnitFreeAfterCast = _glyph.isUnitFreeAfterCast;
	flags = _glyph.flags;
	targetType = _glyph.targetType;
	requireLineOfSight = _glyph.requireLineOfSight;
	passiveApplicators = _glyph.passiveApplicators;
	autoTargetSelector = _glyph.autoTargetSelector;
	microAI = _glyph.microAI;
	node = _glyph.node;
	marker = _glyph.marker;
	warFogRemoveTime = _glyph.warFogRemoveTime;
	warFogRemoveRadius = _glyph.warFogRemoveRadius;
	alternativeTargets = _glyph.alternativeTargets;
	dispatch = _glyph.dispatch;
	applicators = _glyph.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlyphsDB::GlyphsDB()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphsDB::operator&( IBinSaver &saver )
{
	saver.Add( 2, &glyphs );

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
	saver.Add( "glyphs", &glyphs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphsDB::Assign( const GlyphsDB& _glyphsDB )
{
	glyphs = _glyphsDB.glyphs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlyphSpawner::GlyphSpawner() :
		useGlyphManager( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphSpawner::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &useGlyphManager );
	saver.Add( 3, &settings );
	saver.Add( 4, &glyphs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphSpawner::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GlyphSpawner* parentPtr = (GlyphSpawner*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphSpawner::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "useGlyphManager", &useGlyphManager );
	saver.Add( "settings", &settings );
	saver.Add( "glyphs", &glyphs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphSpawner::Assign( const GlyphSpawner& _glyphSpawner )
{
	useGlyphManager = _glyphSpawner.useGlyphManager;
	settings.minNormalSpawnDelay = _glyphSpawner.settings.minNormalSpawnDelay;
	settings.maxNormalSpawnDelay = _glyphSpawner.settings.maxNormalSpawnDelay;
	settings.minAfterPickupSpawnDelay = _glyphSpawner.settings.minAfterPickupSpawnDelay;
	settings.maxAfterPickupSpawnDelay = _glyphSpawner.settings.maxAfterPickupSpawnDelay;
	settings.spawnAttemptDelayDecrease = _glyphSpawner.settings.spawnAttemptDelayDecrease;
	settings.maxInstances = _glyphSpawner.settings.maxInstances;
	settings.spawnMode = _glyphSpawner.settings.spawnMode;
	glyphs = _glyphSpawner.glyphs;
	collision = _glyphSpawner.collision;
	lockMask.tileSize = _glyphSpawner.lockMask.tileSize;
	lockMask.mask = _glyphSpawner.lockMask.mask;
	minLockScale = _glyphSpawner.minLockScale;
	rounded = _glyphSpawner.rounded;
	heightObject = _glyphSpawner.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseHero::BaseHero() :
		gender( GENDER_MALE )
	, heroRace( EHeroRaces( HERORACES_B | HERORACES_A ) )
{
	heroSceneObjects.resize( 2 );
	askLists.resize( 2 );
	askListsSecondState.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseHero::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Creature*)this );
	saver.Add( 2, &heroSceneObjects );
	saver.Add( 3, &gender );
	saver.Add( 4, &askLists );
	saver.Add( 5, &askListsSecondState );
	saver.Add( 6, &heroNameA );
	saver.Add( 7, &heroNameB );
	saver.Add( 8, &heroImageA );
	saver.Add( 9, &heroImageB );
	saver.Add( 10, &persistentId );
	saver.Add( 11, &antagonistId );
	saver.Add( 12, &mmakingAntagonists );
	saver.Add( 13, &minimapIconA );
	saver.Add( 14, &minimapIconB );
	saver.Add( 15, &heroRace );
	saver.Add( 16, &recommendedStats );
	saver.Add( 17, &heroSkins );
	saver.Add( 18, &summonedUnits );
	saver.Add( 19, &uniqueResource );

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
	heroSceneObjects.resize( 2 );
	saver.Add( "heroSceneObjects", &heroSceneObjects );
	saver.Add( "gender", &gender );
	askLists.resize( 2 );
	saver.Add( "askLists", &askLists );
	askListsSecondState.resize( 2 );
	saver.Add( "askListsSecondState", &askListsSecondState );
	saver.Add( "heroNameA", &heroNameA );
	saver.Add( "heroNameB", &heroNameB );
	saver.Add( "heroImageA", &heroImageA );
	saver.Add( "heroImageB", &heroImageB );
	saver.Add( "persistentId", &persistentId );
	saver.Add( "antagonistId", &antagonistId );
	saver.Add( "mmakingAntagonists", &mmakingAntagonists );
	saver.Add( "minimapIconA", &minimapIconA );
	saver.Add( "minimapIconB", &minimapIconB );
	saver.Add( "heroRace", &heroRace );
	saver.Add( "recommendedStats", &recommendedStats );
	saver.Add( "heroSkins", &heroSkins );
	saver.Add( "summonedUnits", &summonedUnits );
	saver.Add( "uniqueResource", &uniqueResource );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseHero::Assign( const BaseHero& _baseHero )
{
	heroSceneObjects = _baseHero.heroSceneObjects;
	gender = _baseHero.gender;
	askLists = _baseHero.askLists;
	askListsSecondState = _baseHero.askListsSecondState;
	heroNameA = _baseHero.heroNameA;
	heroNameB = _baseHero.heroNameB;
	heroImageA = _baseHero.heroImageA;
	heroImageB = _baseHero.heroImageB;
	persistentId = _baseHero.persistentId;
	antagonistId = _baseHero.antagonistId;
	mmakingAntagonists = _baseHero.mmakingAntagonists;
	minimapIconA = _baseHero.minimapIconA;
	minimapIconB = _baseHero.minimapIconB;
	heroRace = _baseHero.heroRace;
	recommendedStats = _baseHero.recommendedStats;
	heroSkins = _baseHero.heroSkins;
	summonedUnits = _baseHero.summonedUnits;
	uniqueResource = _baseHero.uniqueResource;
	recolor = _baseHero.recolor;
	stats = _baseHero.stats;
	targetingParams = _baseHero.targetingParams;
	attackAbility = _baseHero.attackAbility;
	description = _baseHero.description;
	image = _baseHero.image;
	overtipBarsWidth = _baseHero.overtipBarsWidth;
	overtipVerticalOffset = _baseHero.overtipVerticalOffset;
	nativeAttack = _baseHero.nativeAttack;
	nativeDefence = _baseHero.nativeDefence;
	deathParameters = _baseHero.deathParameters;
	abilities = _baseHero.abilities;
	size = _baseHero.size;
	sizeDynamic = _baseHero.sizeDynamic;
	normalLevelling = _baseHero.normalLevelling;
	minimapIcon = _baseHero.minimapIcon;
	selectionAoe = _baseHero.selectionAoe;
	pathFindingSteps = _baseHero.pathFindingSteps;
	interaction = _baseHero.interaction;
	sceneObject = _baseHero.sceneObject;
	collision = _baseHero.collision;
	lockMask.tileSize = _baseHero.lockMask.tileSize;
	lockMask.mask = _baseHero.lockMask.mask;
	minLockScale = _baseHero.minLockScale;
	rounded = _baseHero.rounded;
	heightObject = _baseHero.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroesLevelUps::HeroesLevelUps()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroesLevelUps::operator&( IBinSaver &saver )
{
	saver.Add( 2, &developmentPoints );
	saver.Add( 3, &killExperienceModifiers );

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
	saver.Add( "developmentPoints", &developmentPoints );
	saver.Add( "killExperienceModifiers", &killExperienceModifiers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroesLevelUps::Assign( const HeroesLevelUps& _heroesLevelUps )
{
	developmentPoints = _heroesLevelUps.developmentPoints;
	killExperienceModifiers = _heroesLevelUps.killExperienceModifiers;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroPlaceHolder::HeroPlaceHolder() :
		teamId( TEAMID_A )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroPlaceHolder::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &teamId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroPlaceHolder::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroPlaceHolder* parentPtr = (HeroPlaceHolder*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroPlaceHolder::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "teamId", &teamId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroPlaceHolder::Assign( const HeroPlaceHolder& _heroPlaceHolder )
{
	teamId = _heroPlaceHolder.teamId;
	collision = _heroPlaceHolder.collision;
	lockMask.tileSize = _heroPlaceHolder.lockMask.tileSize;
	lockMask.mask = _heroPlaceHolder.lockMask.mask;
	minLockScale = _heroPlaceHolder.minLockScale;
	rounded = _heroPlaceHolder.rounded;
	heightObject = _heroPlaceHolder.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroResource::HeroResource() :
		castleValueMaximum( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroResource::operator&( IBinSaver &saver )
{
	saver.Add( 2, &formulaNameValue );
	saver.Add( 3, &formulaNameMaximum );
	saver.Add( 4, &formulaNameRegeneration );
	saver.Add( 5, &overtipManaProgressMaterial );
	saver.Add( 6, &uiManaBarColor );
	saver.Add( 7, &name );
	saver.Add( 8, &tooltip );
	saver.Add( 9, &castleValueMaximum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroResource::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroResource* parentPtr = (HeroResource*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroResource::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "formulaNameValue", &formulaNameValue );
	saver.Add( "formulaNameMaximum", &formulaNameMaximum );
	saver.Add( "formulaNameRegeneration", &formulaNameRegeneration );
	saver.Add( "overtipManaProgressMaterial", &overtipManaProgressMaterial );
	saver.Add( "uiManaBarColor", &uiManaBarColor );
	saver.Add( "name", &name );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "castleValueMaximum", &castleValueMaximum );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroResource::Assign( const HeroResource& _heroResource )
{
	formulaNameValue = _heroResource.formulaNameValue;
	formulaNameMaximum = _heroResource.formulaNameMaximum;
	formulaNameRegeneration = _heroResource.formulaNameRegeneration;
	overtipManaProgressMaterial = _heroResource.overtipManaProgressMaterial;
	uiManaBarColor = _heroResource.uiManaBarColor;
	name = _heroResource.name;
	tooltip = _heroResource.tooltip;
	castleValueMaximum = _heroResource.castleValueMaximum;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroSkin::HeroSkin() :
		legal( false )
	, gender( GENDER_MALE )
	, heroRace( EHeroRaces( HERORACES_B | HERORACES_A ) )
	, cost( 500 )
	, mute( false )
	, botRoll( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroSkin::operator&( IBinSaver &saver )
{
	saver.Add( 2, &legal );
	saver.Add( 3, &persistentId );
	saver.Add( 4, &gender );
	saver.Add( 5, &heroName );
	saver.Add( 6, &heroImageA );
	saver.Add( 7, &heroImageB );
	saver.Add( 8, &heroRenderA );
	saver.Add( 9, &heroRenderB );
	saver.Add( 10, &heroRace );
	saver.Add( 11, &sceneObject );
	saver.Add( 12, &askList );
	saver.Add( 13, &askListSecondState );
	saver.Add( 14, &deathParameters );
	saver.Add( 15, &cost );
	saver.Add( 16, &mute );
	saver.Add( 17, &botRoll );
	saver.Add( 18, &antagonistSkinId );

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
	saver.Add( "heroName", &heroName );
	saver.Add( "heroImageA", &heroImageA );
	saver.Add( "heroImageB", &heroImageB );
	saver.Add( "heroRenderA", &heroRenderA );
	saver.Add( "heroRenderB", &heroRenderB );
	saver.Add( "heroRace", &heroRace );
	saver.Add( "sceneObject", &sceneObject );
	saver.Add( "askList", &askList );
	saver.Add( "askListSecondState", &askListSecondState );
	saver.Add( "deathParameters", &deathParameters );
	saver.Add( "cost", &cost );
	saver.Add( "mute", &mute );
	saver.Add( "botRoll", &botRoll );
	saver.Add( "antagonistSkinId", &antagonistSkinId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroSkin::Assign( const HeroSkin& _heroSkin )
{
	legal = _heroSkin.legal;
	persistentId = _heroSkin.persistentId;
	gender = _heroSkin.gender;
	heroName = _heroSkin.heroName;
	heroImageA = _heroSkin.heroImageA;
	heroImageB = _heroSkin.heroImageB;
	heroRenderA = _heroSkin.heroRenderA;
	heroRenderB = _heroSkin.heroRenderB;
	heroRace = _heroSkin.heroRace;
	sceneObject = _heroSkin.sceneObject;
	askList = _heroSkin.askList;
	askListSecondState = _heroSkin.askListSecondState;
	deathParameters = _heroSkin.deathParameters;
	cost = _heroSkin.cost;
	mute = _heroSkin.mute;
	botRoll = _heroSkin.botRoll;
	antagonistSkinId = _heroSkin.antagonistSkinId;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Interaction::Interaction() :
		allowedFactions( FACTIONFLAGS_SELF )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Interaction::operator&( IBinSaver &saver )
{
	saver.Add( 2, &externalAbility );
	saver.Add( 3, &allowedFactions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Interaction::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Interaction* parentPtr = (Interaction*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interaction::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "externalAbility", &externalAbility );
	saver.Add( "allowedFactions", &allowedFactions );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interaction::Assign( const Interaction& _interaction )
{
	externalAbility = _interaction.externalAbility;
	allowedFactions = _interaction.allowedFactions;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KillExperienceModifier::KillExperienceModifier() :
		otherDifferenceLessCoeff( 10.0f )
	, otherDifferenceGreaterCoeff( 150.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillExperienceModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &otherDifferenceLessCoeff );
	saver.Add( 3, &otherDifferenceGreaterCoeff );
	saver.Add( 4, &levelModifiers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillExperienceModifier::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			KillExperienceModifier* parentPtr = (KillExperienceModifier*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillExperienceModifier::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "otherDifferenceLessCoeff", &otherDifferenceLessCoeff );
	saver.Add( "otherDifferenceGreaterCoeff", &otherDifferenceGreaterCoeff );
	saver.Add( "levelModifiers", &levelModifiers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillExperienceModifier::Assign( const KillExperienceModifier& _killExperienceModifier )
{
	otherDifferenceLessCoeff = _killExperienceModifier.otherDifferenceLessCoeff;
	otherDifferenceGreaterCoeff = _killExperienceModifier.otherDifferenceGreaterCoeff;
	levelModifiers = _killExperienceModifier.levelModifiers;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainBuilding::MainBuilding() :
		aoeUnitsCount( 10 )
	, aoeUnitsTypes( SPELLTARGET_ALL )
	, aoeUnitsFactions( EFactionFlags( FACTIONFLAGS_OPPOSITE | FACTIONFLAGS_NEUTRAL ) )
	, aoeRadius( 20.0f )
	, minAOEDelay( 10.0f )
	, maxAOEDelay( 20.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainBuilding::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );
	saver.Add( 2, &aoeUnitsCount );
	saver.Add( 3, &aoeUnitsTypes );
	saver.Add( 4, &aoeUnitsFactions );
	saver.Add( 5, &aoeRadius );
	saver.Add( 6, &minAOEDelay );
	saver.Add( 7, &maxAOEDelay );
	saver.Add( 8, &aoeAttack );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainBuilding::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MainBuilding* parentPtr = (MainBuilding*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainBuilding::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
	saver.Add( "aoeUnitsCount", &aoeUnitsCount );
	saver.Add( "aoeUnitsTypes", &aoeUnitsTypes );
	saver.Add( "aoeUnitsFactions", &aoeUnitsFactions );
	saver.Add( "aoeRadius", &aoeRadius );
	saver.Add( "minAOEDelay", &minAOEDelay );
	saver.Add( "maxAOEDelay", &maxAOEDelay );
	saver.Add( "aoeAttack", &aoeAttack );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainBuilding::Assign( const MainBuilding& _mainBuilding )
{
	aoeUnitsCount = _mainBuilding.aoeUnitsCount;
	aoeUnitsTypes = _mainBuilding.aoeUnitsTypes;
	aoeUnitsFactions = _mainBuilding.aoeUnitsFactions;
	aoeRadius = _mainBuilding.aoeRadius;
	minAOEDelay = _mainBuilding.minAOEDelay;
	maxAOEDelay = _mainBuilding.maxAOEDelay;
	aoeAttack = _mainBuilding.aoeAttack;
	faction = _mainBuilding.faction;
	routeID = _mainBuilding.routeID;
	routeLevel = _mainBuilding.routeLevel;
	ruinSceneObject = _mainBuilding.ruinSceneObject;
	showRuinDelay = _mainBuilding.showRuinDelay;
	ruinLocator = _mainBuilding.ruinLocator;
	onDamageFragEffect = _mainBuilding.onDamageFragEffect;
	onDestructionEffect = _mainBuilding.onDestructionEffect;
	isDecoration = _mainBuilding.isDecoration;
	minimapIconOffset = _mainBuilding.minimapIconOffset;
	levelUpInterval = _mainBuilding.levelUpInterval;
	updateUnderWarfog = _mainBuilding.updateUnderWarfog;
	stats = _mainBuilding.stats;
	targetingParams = _mainBuilding.targetingParams;
	attackAbility = _mainBuilding.attackAbility;
	description = _mainBuilding.description;
	image = _mainBuilding.image;
	overtipBarsWidth = _mainBuilding.overtipBarsWidth;
	overtipVerticalOffset = _mainBuilding.overtipVerticalOffset;
	nativeAttack = _mainBuilding.nativeAttack;
	nativeDefence = _mainBuilding.nativeDefence;
	deathParameters = _mainBuilding.deathParameters;
	abilities = _mainBuilding.abilities;
	size = _mainBuilding.size;
	sizeDynamic = _mainBuilding.sizeDynamic;
	normalLevelling = _mainBuilding.normalLevelling;
	minimapIcon = _mainBuilding.minimapIcon;
	selectionAoe = _mainBuilding.selectionAoe;
	pathFindingSteps = _mainBuilding.pathFindingSteps;
	interaction = _mainBuilding.interaction;
	sceneObject = _mainBuilding.sceneObject;
	collision = _mainBuilding.collision;
	lockMask.tileSize = _mainBuilding.lockMask.tileSize;
	lockMask.mask = _mainBuilding.lockMask.mask;
	minLockScale = _mainBuilding.minLockScale;
	rounded = _mainBuilding.rounded;
	heightObject = _mainBuilding.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigamePlace::MinigamePlace()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamePlace::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );
	saver.Add( 2, &placeParams );
	saver.Add( 3, &minigameId );
	saver.Add( 4, &artifactsSpawnPosition );
	saver.Add( 5, &onIdleEffect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamePlace::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinigamePlace* parentPtr = (MinigamePlace*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePlace::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
	saver.Add( "placeParams", &placeParams );
	saver.Add( "minigameId", &minigameId );
	saver.Add( "artifactsSpawnPosition", &artifactsSpawnPosition );
	saver.Add( "onIdleEffect", &onIdleEffect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePlace::Assign( const MinigamePlace& _minigamePlace )
{
	placeParams = _minigamePlace.placeParams;
	minigameId = _minigamePlace.minigameId;
	artifactsSpawnPosition = _minigamePlace.artifactsSpawnPosition;
	onIdleEffect = _minigamePlace.onIdleEffect;
	faction = _minigamePlace.faction;
	routeID = _minigamePlace.routeID;
	routeLevel = _minigamePlace.routeLevel;
	ruinSceneObject = _minigamePlace.ruinSceneObject;
	showRuinDelay = _minigamePlace.showRuinDelay;
	ruinLocator = _minigamePlace.ruinLocator;
	onDamageFragEffect = _minigamePlace.onDamageFragEffect;
	onDestructionEffect = _minigamePlace.onDestructionEffect;
	isDecoration = _minigamePlace.isDecoration;
	minimapIconOffset = _minigamePlace.minimapIconOffset;
	levelUpInterval = _minigamePlace.levelUpInterval;
	updateUnderWarfog = _minigamePlace.updateUnderWarfog;
	stats = _minigamePlace.stats;
	targetingParams = _minigamePlace.targetingParams;
	attackAbility = _minigamePlace.attackAbility;
	description = _minigamePlace.description;
	image = _minigamePlace.image;
	overtipBarsWidth = _minigamePlace.overtipBarsWidth;
	overtipVerticalOffset = _minigamePlace.overtipVerticalOffset;
	nativeAttack = _minigamePlace.nativeAttack;
	nativeDefence = _minigamePlace.nativeDefence;
	deathParameters = _minigamePlace.deathParameters;
	abilities = _minigamePlace.abilities;
	size = _minigamePlace.size;
	sizeDynamic = _minigamePlace.sizeDynamic;
	normalLevelling = _minigamePlace.normalLevelling;
	minimapIcon = _minigamePlace.minimapIcon;
	selectionAoe = _minigamePlace.selectionAoe;
	pathFindingSteps = _minigamePlace.pathFindingSteps;
	interaction = _minigamePlace.interaction;
	sceneObject = _minigamePlace.sceneObject;
	collision = _minigamePlace.collision;
	lockMask.tileSize = _minigamePlace.lockMask.tileSize;
	lockMask.mask = _minigamePlace.lockMask.mask;
	minLockScale = _minigamePlace.minLockScale;
	rounded = _minigamePlace.rounded;
	heightObject = _minigamePlace.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MSOTransactions::MSOTransactions()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MSOTransactions::operator&( IBinSaver &saver )
{
	saver.Add( 2, &effectN );
	saver.Add( 3, &effectA );
	saver.Add( 4, &effectB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MSOTransactions::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MSOTransactions* parentPtr = (MSOTransactions*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MSOTransactions::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "effectN", &effectN );
	saver.Add( "effectA", &effectA );
	saver.Add( "effectB", &effectB );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MSOTransactions::Assign( const MSOTransactions& _mSOTransactions )
{
	effectN.effectIn = _mSOTransactions.effectN.effectIn;
	effectN.effectOut = _mSOTransactions.effectN.effectOut;
	effectA.effectIn = _mSOTransactions.effectA.effectIn;
	effectA.effectOut = _mSOTransactions.effectA.effectOut;
	effectB.effectIn = _mSOTransactions.effectB.effectIn;
	effectB.effectOut = _mSOTransactions.effectB.effectOut;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultiStateObject::MultiStateObject() :
		opaque( false )
	, fadeInOffset( 0.0f )
	, dropTime( 1.0f )
	, isVisibleUnderWarfog( false )
	, distinct( false )
{
	sceneObjects.resize( 3 );
	nightSceneObjects.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultiStateObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &sceneObjects );
	saver.Add( 3, &nightSceneObjects );
	saver.Add( 4, &effects );
	saver.Add( 5, &nightEffects );
	saver.Add( 6, &opaque );
	saver.Add( 7, &fadeInOffset );
	saver.Add( 8, &dropTime );
	saver.Add( 9, &isVisibleUnderWarfog );
	saver.Add( 10, &distinct );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultiStateObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MultiStateObject* parentPtr = (MultiStateObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiStateObject::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	sceneObjects.resize( 3 );
	saver.Add( "sceneObjects", &sceneObjects );
	nightSceneObjects.resize( 3 );
	saver.Add( "nightSceneObjects", &nightSceneObjects );
	saver.Add( "effects", &effects );
	saver.Add( "nightEffects", &nightEffects );
	saver.Add( "opaque", &opaque );
	saver.Add( "fadeInOffset", &fadeInOffset );
	saver.Add( "dropTime", &dropTime );
	saver.Add( "isVisibleUnderWarfog", &isVisibleUnderWarfog );
	saver.Add( "distinct", &distinct );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiStateObject::Assign( const MultiStateObject& _multiStateObject )
{
	sceneObjects = _multiStateObject.sceneObjects;
	nightSceneObjects = _multiStateObject.nightSceneObjects;
	effects = _multiStateObject.effects;
	nightEffects = _multiStateObject.nightEffects;
	opaque = _multiStateObject.opaque;
	fadeInOffset = _multiStateObject.fadeInOffset;
	dropTime = _multiStateObject.dropTime;
	isVisibleUnderWarfog = _multiStateObject.isVisibleUnderWarfog;
	distinct = _multiStateObject.distinct;
	collision = _multiStateObject.collision;
	lockMask.tileSize = _multiStateObject.lockMask.tileSize;
	lockMask.mask = _multiStateObject.lockMask.mask;
	minLockScale = _multiStateObject.minLockScale;
	rounded = _multiStateObject.rounded;
	heightObject = _multiStateObject.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Quarter::Quarter()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Quarter::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Quarter::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Quarter* parentPtr = (Quarter*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Quarter::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Quarter::Assign( const Quarter& _quarter )
{
	faction = _quarter.faction;
	routeID = _quarter.routeID;
	routeLevel = _quarter.routeLevel;
	ruinSceneObject = _quarter.ruinSceneObject;
	showRuinDelay = _quarter.showRuinDelay;
	ruinLocator = _quarter.ruinLocator;
	onDamageFragEffect = _quarter.onDamageFragEffect;
	onDestructionEffect = _quarter.onDestructionEffect;
	isDecoration = _quarter.isDecoration;
	minimapIconOffset = _quarter.minimapIconOffset;
	levelUpInterval = _quarter.levelUpInterval;
	updateUnderWarfog = _quarter.updateUnderWarfog;
	stats = _quarter.stats;
	targetingParams = _quarter.targetingParams;
	attackAbility = _quarter.attackAbility;
	description = _quarter.description;
	image = _quarter.image;
	overtipBarsWidth = _quarter.overtipBarsWidth;
	overtipVerticalOffset = _quarter.overtipVerticalOffset;
	nativeAttack = _quarter.nativeAttack;
	nativeDefence = _quarter.nativeDefence;
	deathParameters = _quarter.deathParameters;
	abilities = _quarter.abilities;
	size = _quarter.size;
	sizeDynamic = _quarter.sizeDynamic;
	normalLevelling = _quarter.normalLevelling;
	minimapIcon = _quarter.minimapIcon;
	selectionAoe = _quarter.selectionAoe;
	pathFindingSteps = _quarter.pathFindingSteps;
	interaction = _quarter.interaction;
	sceneObject = _quarter.sceneObject;
	collision = _quarter.collision;
	lockMask.tileSize = _quarter.lockMask.tileSize;
	lockMask.mask = _quarter.lockMask.mask;
	minLockScale = _quarter.minLockScale;
	rounded = _quarter.rounded;
	heightObject = _quarter.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptedFlagpole::ScriptedFlagpole()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptedFlagpole::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Flagpole*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptedFlagpole::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScriptedFlagpole* parentPtr = (ScriptedFlagpole*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptedFlagpole::SerializeSelf( IXmlSaver &saver )
{
	Flagpole::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptedFlagpole::Assign( const ScriptedFlagpole& _scriptedFlagpole )
{
	ownerTowers = _scriptedFlagpole.ownerTowers;
	effect = _scriptedFlagpole.effect;
	factionImages = _scriptedFlagpole.factionImages;
	factionDescriptions = _scriptedFlagpole.factionDescriptions;
	stats = _scriptedFlagpole.stats;
	targetingParams = _scriptedFlagpole.targetingParams;
	attackAbility = _scriptedFlagpole.attackAbility;
	description = _scriptedFlagpole.description;
	image = _scriptedFlagpole.image;
	overtipBarsWidth = _scriptedFlagpole.overtipBarsWidth;
	overtipVerticalOffset = _scriptedFlagpole.overtipVerticalOffset;
	nativeAttack = _scriptedFlagpole.nativeAttack;
	nativeDefence = _scriptedFlagpole.nativeDefence;
	deathParameters = _scriptedFlagpole.deathParameters;
	abilities = _scriptedFlagpole.abilities;
	size = _scriptedFlagpole.size;
	sizeDynamic = _scriptedFlagpole.sizeDynamic;
	normalLevelling = _scriptedFlagpole.normalLevelling;
	minimapIcon = _scriptedFlagpole.minimapIcon;
	selectionAoe = _scriptedFlagpole.selectionAoe;
	pathFindingSteps = _scriptedFlagpole.pathFindingSteps;
	interaction = _scriptedFlagpole.interaction;
	sceneObject = _scriptedFlagpole.sceneObject;
	collision = _scriptedFlagpole.collision;
	lockMask.tileSize = _scriptedFlagpole.lockMask.tileSize;
	lockMask.mask = _scriptedFlagpole.lockMask.mask;
	minLockScale = _scriptedFlagpole.minLockScale;
	rounded = _scriptedFlagpole.rounded;
	heightObject = _scriptedFlagpole.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shop::Shop()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Shop::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );
	saver.Add( 2, &shop );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Shop::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Shop* parentPtr = (Shop*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shop::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
	saver.Add( "shop", &shop );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shop::Assign( const Shop& _shop )
{
	shop = _shop.shop;
	faction = _shop.faction;
	routeID = _shop.routeID;
	routeLevel = _shop.routeLevel;
	ruinSceneObject = _shop.ruinSceneObject;
	showRuinDelay = _shop.showRuinDelay;
	ruinLocator = _shop.ruinLocator;
	onDamageFragEffect = _shop.onDamageFragEffect;
	onDestructionEffect = _shop.onDestructionEffect;
	isDecoration = _shop.isDecoration;
	minimapIconOffset = _shop.minimapIconOffset;
	levelUpInterval = _shop.levelUpInterval;
	updateUnderWarfog = _shop.updateUnderWarfog;
	stats = _shop.stats;
	targetingParams = _shop.targetingParams;
	attackAbility = _shop.attackAbility;
	description = _shop.description;
	image = _shop.image;
	overtipBarsWidth = _shop.overtipBarsWidth;
	overtipVerticalOffset = _shop.overtipVerticalOffset;
	nativeAttack = _shop.nativeAttack;
	nativeDefence = _shop.nativeDefence;
	deathParameters = _shop.deathParameters;
	abilities = _shop.abilities;
	size = _shop.size;
	sizeDynamic = _shop.sizeDynamic;
	normalLevelling = _shop.normalLevelling;
	minimapIcon = _shop.minimapIcon;
	selectionAoe = _shop.selectionAoe;
	pathFindingSteps = _shop.pathFindingSteps;
	interaction = _shop.interaction;
	sceneObject = _shop.sceneObject;
	collision = _shop.collision;
	lockMask.tileSize = _shop.lockMask.tileSize;
	lockMask.mask = _shop.lockMask.mask;
	minLockScale = _shop.minLockScale;
	rounded = _shop.rounded;
	heightObject = _shop.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleObject::SimpleObject() :
		health( -1 )
	, opaque( false )
	, isVisibleUnderWarfog( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SimpleObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleStateObject*)this );
	saver.Add( 2, &health );
	saver.Add( 3, &opaque );
	saver.Add( 4, &isVisibleUnderWarfog );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SimpleObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SimpleObject* parentPtr = (SimpleObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleObject::SerializeSelf( IXmlSaver &saver )
{
	SingleStateObject::SerializeSelf( saver );
	saver.Add( "health", &health );
	saver.Add( "opaque", &opaque );
	saver.Add( "isVisibleUnderWarfog", &isVisibleUnderWarfog );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleObject::Assign( const SimpleObject& _simpleObject )
{
	health = _simpleObject.health;
	opaque = _simpleObject.opaque;
	isVisibleUnderWarfog = _simpleObject.isVisibleUnderWarfog;
	sceneObject = _simpleObject.sceneObject;
	collision = _simpleObject.collision;
	lockMask.tileSize = _simpleObject.lockMask.tileSize;
	lockMask.mask = _simpleObject.lockMask.mask;
	minLockScale = _simpleObject.minLockScale;
	rounded = _simpleObject.rounded;
	heightObject = _simpleObject.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Hero::Hero() :
		legal( true )
	, botRollMode( BOTROLLMODE_ENABLED )
	, canMount( false )
	, askBlessCooldown( 0.0f )
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
	saver.Add( 6, &canMount );
	saver.Add( 7, &askBlessCooldown );
	saver.Add( 8, &defaultTalentsSets );

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
	saver.Add( "canMount", &canMount );
	saver.Add( "askBlessCooldown", &askBlessCooldown );
	saver.Add( "defaultTalentsSets", &defaultTalentsSets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hero::Assign( const Hero& _hero )
{
	id = _hero.id;
	legal = _hero.legal;
	botRollMode = _hero.botRollMode;
	classEfficiency = _hero.classEfficiency;
	canMount = _hero.canMount;
	askBlessCooldown = _hero.askBlessCooldown;
	defaultTalentsSets = _hero.defaultTalentsSets;
	heroSceneObjects = _hero.heroSceneObjects;
	gender = _hero.gender;
	askLists = _hero.askLists;
	askListsSecondState = _hero.askListsSecondState;
	heroNameA = _hero.heroNameA;
	heroNameB = _hero.heroNameB;
	heroImageA = _hero.heroImageA;
	heroImageB = _hero.heroImageB;
	persistentId = _hero.persistentId;
	antagonistId = _hero.antagonistId;
	mmakingAntagonists = _hero.mmakingAntagonists;
	minimapIconA = _hero.minimapIconA;
	minimapIconB = _hero.minimapIconB;
	heroRace = _hero.heroRace;
	recommendedStats = _hero.recommendedStats;
	heroSkins = _hero.heroSkins;
	summonedUnits = _hero.summonedUnits;
	uniqueResource = _hero.uniqueResource;
	recolor = _hero.recolor;
	stats = _hero.stats;
	targetingParams = _hero.targetingParams;
	attackAbility = _hero.attackAbility;
	description = _hero.description;
	image = _hero.image;
	overtipBarsWidth = _hero.overtipBarsWidth;
	overtipVerticalOffset = _hero.overtipVerticalOffset;
	nativeAttack = _hero.nativeAttack;
	nativeDefence = _hero.nativeDefence;
	deathParameters = _hero.deathParameters;
	abilities = _hero.abilities;
	size = _hero.size;
	sizeDynamic = _hero.sizeDynamic;
	normalLevelling = _hero.normalLevelling;
	minimapIcon = _hero.minimapIcon;
	selectionAoe = _hero.selectionAoe;
	pathFindingSteps = _hero.pathFindingSteps;
	interaction = _hero.interaction;
	sceneObject = _hero.sceneObject;
	collision = _hero.collision;
	lockMask.tileSize = _hero.lockMask.tileSize;
	lockMask.mask = _hero.lockMask.mask;
	minLockScale = _hero.minLockScale;
	rounded = _hero.rounded;
	heightObject = _hero.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Summoned::Summoned()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Summoned::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Creature*)this );
	saver.Add( 2, &creepSkins );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Summoned::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Summoned* parentPtr = (Summoned*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summoned::SerializeSelf( IXmlSaver &saver )
{
	Creature::SerializeSelf( saver );
	saver.Add( "creepSkins", &creepSkins );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summoned::Assign( const Summoned& _summoned )
{
	creepSkins = _summoned.creepSkins;
	recolor = _summoned.recolor;
	stats = _summoned.stats;
	targetingParams = _summoned.targetingParams;
	attackAbility = _summoned.attackAbility;
	description = _summoned.description;
	image = _summoned.image;
	overtipBarsWidth = _summoned.overtipBarsWidth;
	overtipVerticalOffset = _summoned.overtipVerticalOffset;
	nativeAttack = _summoned.nativeAttack;
	nativeDefence = _summoned.nativeDefence;
	deathParameters = _summoned.deathParameters;
	abilities = _summoned.abilities;
	size = _summoned.size;
	sizeDynamic = _summoned.sizeDynamic;
	normalLevelling = _summoned.normalLevelling;
	minimapIcon = _summoned.minimapIcon;
	selectionAoe = _summoned.selectionAoe;
	pathFindingSteps = _summoned.pathFindingSteps;
	interaction = _summoned.interaction;
	sceneObject = _summoned.sceneObject;
	collision = _summoned.collision;
	lockMask.tileSize = _summoned.lockMask.tileSize;
	lockMask.mask = _summoned.lockMask.mask;
	minLockScale = _summoned.minLockScale;
	rounded = _summoned.rounded;
	heightObject = _summoned.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ControllableTower::ControllableTower()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ControllableTower::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Tower*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ControllableTower::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ControllableTower* parentPtr = (ControllableTower*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ControllableTower::SerializeSelf( IXmlSaver &saver )
{
	Tower::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ControllableTower::Assign( const ControllableTower& _controllableTower )
{
	baseRotation = _controllableTower.baseRotation;
	faction = _controllableTower.faction;
	routeID = _controllableTower.routeID;
	routeLevel = _controllableTower.routeLevel;
	ruinSceneObject = _controllableTower.ruinSceneObject;
	showRuinDelay = _controllableTower.showRuinDelay;
	ruinLocator = _controllableTower.ruinLocator;
	onDamageFragEffect = _controllableTower.onDamageFragEffect;
	onDestructionEffect = _controllableTower.onDestructionEffect;
	isDecoration = _controllableTower.isDecoration;
	minimapIconOffset = _controllableTower.minimapIconOffset;
	levelUpInterval = _controllableTower.levelUpInterval;
	updateUnderWarfog = _controllableTower.updateUnderWarfog;
	stats = _controllableTower.stats;
	targetingParams = _controllableTower.targetingParams;
	attackAbility = _controllableTower.attackAbility;
	description = _controllableTower.description;
	image = _controllableTower.image;
	overtipBarsWidth = _controllableTower.overtipBarsWidth;
	overtipVerticalOffset = _controllableTower.overtipVerticalOffset;
	nativeAttack = _controllableTower.nativeAttack;
	nativeDefence = _controllableTower.nativeDefence;
	deathParameters = _controllableTower.deathParameters;
	abilities = _controllableTower.abilities;
	size = _controllableTower.size;
	sizeDynamic = _controllableTower.sizeDynamic;
	normalLevelling = _controllableTower.normalLevelling;
	minimapIcon = _controllableTower.minimapIcon;
	selectionAoe = _controllableTower.selectionAoe;
	pathFindingSteps = _controllableTower.pathFindingSteps;
	interaction = _controllableTower.interaction;
	sceneObject = _controllableTower.sceneObject;
	collision = _controllableTower.collision;
	lockMask.tileSize = _controllableTower.lockMask.tileSize;
	lockMask.mask = _controllableTower.lockMask.mask;
	minLockScale = _controllableTower.minLockScale;
	rounded = _controllableTower.rounded;
	heightObject = _controllableTower.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TreeObject::TreeObject() :
		wonderfulTree( false )
{
	stubsSceneObjects.resize( 3 );
	nightStubsSceneObjects.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TreeObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultiStateObject*)this );
	saver.Add( 2, &stubsSceneObjects );
	saver.Add( 3, &nightStubsSceneObjects );
	saver.Add( 4, &wonderfulTree );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TreeObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TreeObject* parentPtr = (TreeObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TreeObject::SerializeSelf( IXmlSaver &saver )
{
	MultiStateObject::SerializeSelf( saver );
	stubsSceneObjects.resize( 3 );
	saver.Add( "stubsSceneObjects", &stubsSceneObjects );
	nightStubsSceneObjects.resize( 3 );
	saver.Add( "nightStubsSceneObjects", &nightStubsSceneObjects );
	saver.Add( "wonderfulTree", &wonderfulTree );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TreeObject::Assign( const TreeObject& _treeObject )
{
	stubsSceneObjects = _treeObject.stubsSceneObjects;
	nightStubsSceneObjects = _treeObject.nightStubsSceneObjects;
	wonderfulTree = _treeObject.wonderfulTree;
	sceneObjects = _treeObject.sceneObjects;
	nightSceneObjects = _treeObject.nightSceneObjects;
	effects = _treeObject.effects;
	nightEffects = _treeObject.nightEffects;
	opaque = _treeObject.opaque;
	fadeInOffset = _treeObject.fadeInOffset;
	dropTime = _treeObject.dropTime;
	isVisibleUnderWarfog = _treeObject.isVisibleUnderWarfog;
	distinct = _treeObject.distinct;
	collision = _treeObject.collision;
	lockMask.tileSize = _treeObject.lockMask.tileSize;
	lockMask.mask = _treeObject.lockMask.mask;
	minLockScale = _treeObject.minLockScale;
	rounded = _treeObject.rounded;
	heightObject = _treeObject.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasePet::BasePet() :
		test( 0.15f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasePet::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Creature*)this );
	saver.Add( 2, &test );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasePet::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasePet* parentPtr = (BasePet*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasePet::SerializeSelf( IXmlSaver &saver )
{
	Creature::SerializeSelf( saver );
	saver.Add( "test", &test );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasePet::Assign( const BasePet& _basePet )
{
	test = _basePet.test;
	recolor = _basePet.recolor;
	stats = _basePet.stats;
	targetingParams = _basePet.targetingParams;
	attackAbility = _basePet.attackAbility;
	description = _basePet.description;
	image = _basePet.image;
	overtipBarsWidth = _basePet.overtipBarsWidth;
	overtipVerticalOffset = _basePet.overtipVerticalOffset;
	nativeAttack = _basePet.nativeAttack;
	nativeDefence = _basePet.nativeDefence;
	deathParameters = _basePet.deathParameters;
	abilities = _basePet.abilities;
	size = _basePet.size;
	sizeDynamic = _basePet.sizeDynamic;
	normalLevelling = _basePet.normalLevelling;
	minimapIcon = _basePet.minimapIcon;
	selectionAoe = _basePet.selectionAoe;
	pathFindingSteps = _basePet.pathFindingSteps;
	interaction = _basePet.interaction;
	sceneObject = _basePet.sceneObject;
	collision = _basePet.collision;
	lockMask.tileSize = _basePet.lockMask.tileSize;
	lockMask.mask = _basePet.lockMask.mask;
	minLockScale = _basePet.minLockScale;
	rounded = _basePet.rounded;
	heightObject = _basePet.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitCategories::UnitCategories()
{
	elements.resize( 22 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategories::operator&( IBinSaver &saver )
{
	saver.Add( 2, &elements );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategories::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitCategories* parentPtr = (UnitCategories*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitCategories::SerializeSelf( IXmlSaver &saver )
{
	elements.resize( 22 );
	saver.Add( "elements", &elements );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitCategories::Assign( const UnitCategories& _unitCategories )
{
	elements = _unitCategories.elements;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitCategoriesParams::UnitCategoriesParams()
{
	elements.resize( 4 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategoriesParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &elements );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCategoriesParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitCategoriesParams* parentPtr = (UnitCategoriesParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitCategoriesParams::SerializeSelf( IXmlSaver &saver )
{
	elements.resize( 4 );
	saver.Add( "elements", &elements );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitCategoriesParams::Assign( const UnitCategoriesParams& _unitCategoriesParams )
{
	elements = _unitCategoriesParams.elements;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UsableBuilding::UsableBuilding()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UsableBuilding::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Building*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UsableBuilding::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UsableBuilding* parentPtr = (UsableBuilding*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UsableBuilding::SerializeSelf( IXmlSaver &saver )
{
	Building::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UsableBuilding::Assign( const UsableBuilding& _usableBuilding )
{
	faction = _usableBuilding.faction;
	routeID = _usableBuilding.routeID;
	routeLevel = _usableBuilding.routeLevel;
	ruinSceneObject = _usableBuilding.ruinSceneObject;
	showRuinDelay = _usableBuilding.showRuinDelay;
	ruinLocator = _usableBuilding.ruinLocator;
	onDamageFragEffect = _usableBuilding.onDamageFragEffect;
	onDestructionEffect = _usableBuilding.onDestructionEffect;
	isDecoration = _usableBuilding.isDecoration;
	minimapIconOffset = _usableBuilding.minimapIconOffset;
	levelUpInterval = _usableBuilding.levelUpInterval;
	updateUnderWarfog = _usableBuilding.updateUnderWarfog;
	stats = _usableBuilding.stats;
	targetingParams = _usableBuilding.targetingParams;
	attackAbility = _usableBuilding.attackAbility;
	description = _usableBuilding.description;
	image = _usableBuilding.image;
	overtipBarsWidth = _usableBuilding.overtipBarsWidth;
	overtipVerticalOffset = _usableBuilding.overtipVerticalOffset;
	nativeAttack = _usableBuilding.nativeAttack;
	nativeDefence = _usableBuilding.nativeDefence;
	deathParameters = _usableBuilding.deathParameters;
	abilities = _usableBuilding.abilities;
	size = _usableBuilding.size;
	sizeDynamic = _usableBuilding.sizeDynamic;
	normalLevelling = _usableBuilding.normalLevelling;
	minimapIcon = _usableBuilding.minimapIcon;
	selectionAoe = _usableBuilding.selectionAoe;
	pathFindingSteps = _usableBuilding.pathFindingSteps;
	interaction = _usableBuilding.interaction;
	sceneObject = _usableBuilding.sceneObject;
	collision = _usableBuilding.collision;
	lockMask.tileSize = _usableBuilding.lockMask.tileSize;
	lockMask.mask = _usableBuilding.lockMask.mask;
	minLockScale = _usableBuilding.minLockScale;
	rounded = _usableBuilding.rounded;
	heightObject = _usableBuilding.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WarFogUnblock::WarFogUnblock() :
		radius( 0 )
	, faction( EFactionFlags( FACTIONFLAGS_FACTIONBURN | FACTIONFLAGS_FACTIONFREEZE ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WarFogUnblock::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &radius );
	saver.Add( 3, &faction );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WarFogUnblock::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WarFogUnblock* parentPtr = (WarFogUnblock*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WarFogUnblock::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "radius", &radius );
	saver.Add( "faction", &faction );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WarFogUnblock::Assign( const WarFogUnblock& _warFogUnblock )
{
	radius = _warFogUnblock.radius;
	faction = _warFogUnblock.faction;
	collision = _warFogUnblock.collision;
	lockMask.tileSize = _warFogUnblock.lockMask.tileSize;
	lockMask.mask = _warFogUnblock.lockMask.mask;
	minLockScale = _warFogUnblock.minLockScale;
	rounded = _warFogUnblock.rounded;
	heightObject = _warFogUnblock.heightObject;
}
}; // namespace NDb
