// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBStats.h"
#include "../Terrain/DBTerrain.h"
#include "../Sound/DBSound.h"
#include "../Render/DBRender.h"
#include "../PF_Core/DBEffect.h"
#include "../Render/DBRenderResources.h"
#include "../PF_GameLogic/DBServer.h"
#include "../Scene/DBSceneBase.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../UI/DBVotingForSurrender.h"
#include "../PF_GameLogic/DBTalent.h"
#include "../libdb/DB.h"
#include "DBAdvMap.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AdvMap );
REGISTER_DBRESOURCE( AdvMapCameraSpline );
REGISTER_DBRESOURCE( AdvMapDescription );
REGISTER_DBRESOURCE( AdvMapHeroesOverride );
REGISTER_DBRESOURCE( AdvMapHeroesOverrideData );
REGISTER_DBRESOURCE( AdvMapSettings );
REGISTER_DBRESOURCE( AdvMapWaterZone );
REGISTER_DBRESOURCE( CreepAnnounceList );
REGISTER_DBRESOURCE( DbAdvMapCTESettings );
REGISTER_DBRESOURCE( DictionaryPreloadingResources );
REGISTER_DBRESOURCE( FWODVisualInfo );
REGISTER_DBRESOURCE( GameSvcSettings );
REGISTER_DBRESOURCE( GlyphManagerParams );
REGISTER_DBRESOURCE( HeroNaftaParams );
REGISTER_DBRESOURCE( ScriptPolygonArea );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
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
const char *EnumToString( const PartyMode value )
{
	switch( value )
	{
		case PARTYMODE_NOTALLOWED:
			return "NotAllowed";
		case PARTYMODE_ONLYALLIES:
			return "OnlyAllies";
		case PARTYMODE_ALLIESANDENEMIES:
			return "AlliesAndEnemies";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum PartyMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PartyMode StringToEnum_PartyMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PartyMode)(NStr::ToInt( value ));
	if ( strcmp( value, "NotAllowed" ) == 0 || strcmp( value, "PARTYMODE_NOTALLOWED" ) == 0 )
		return PARTYMODE_NOTALLOWED;
	if ( strcmp( value, "OnlyAllies" ) == 0 || strcmp( value, "PARTYMODE_ONLYALLIES" ) == 0 )
		return PARTYMODE_ONLYALLIES;
	if ( strcmp( value, "AlliesAndEnemies" ) == 0 || strcmp( value, "PARTYMODE_ALLIESANDENEMIES" ) == 0 )
		return PARTYMODE_ALLIESANDENEMIES;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PartyMode", value ) );
	return PARTYMODE_NOTALLOWED;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapObject::AdvMapObject() :
		player( PLAYERID_NONE )
	, lockMap( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapObject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &gameObject );
	saver.Add( 3, &offset );
	saver.Add( 4, &player );
	saver.Add( 5, &lockMap );
	saver.Add( 6, &scriptName );
	saver.Add( 7, &scriptGroupName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapObject::operator&( IXmlSaver &saver )
{
	saver.Add( "gameObject", &gameObject );
	saver.Add( "offset", &offset );
	saver.Add( "player", &player );
	saver.Add( "lockMap", &lockMap );
	saver.Add( "scriptName", &scriptName );
	saver.Add( "scriptGroupName", &scriptGroupName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapPlayerData::AdvMapPlayerData()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapPlayerData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &hero );
	saver.Add( 3, &nickname );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapPlayerData::operator&( IXmlSaver &saver )
{
	saver.Add( "hero", &hero );
	saver.Add( "nickname", &nickname );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepAnnounce::CreepAnnounce()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepAnnounce::operator&( IBinSaver &saver )
{
	saver.Add( 2, &spawner );
	saver.Add( 3, &creeps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepAnnounce::operator&( IXmlSaver &saver )
{
	saver.Add( "spawner", &spawner );
	saver.Add( "creeps", &creeps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoadingBackgroundImages::LoadingBackgroundImages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LoadingBackgroundImages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &back );
	saver.Add( 3, &logo );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LoadingBackgroundImages::operator&( IXmlSaver &saver )
{
	saver.Add( "back", &back );
	saver.Add( "logo", &logo );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PrimeSettings::PrimeSettings() :
		giveWorldPrimeToDead( true )
	, giveWorldPrimeRessurectDelay( 0.0f )
	, startPrimePerTeam( 1500 )
	, giveWorldPrimeAmount( 2 )
	, naftaForKill( -1.0f )
	, naftaForAssist( -1.0f )
	, naftaSpecForKill( -1.0f )
	, teamNaftaForPresence( -1.0f )
	, awardSpecRange( 32.0f )
	, awardTeamRange( 25.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PrimeSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &giveWorldPrimeToDead );
	saver.Add( 3, &giveWorldPrimeRessurectDelay );
	saver.Add( 4, &startPrimePerTeam );
	saver.Add( 5, &giveWorldPrimeAmount );
	saver.Add( 6, &multipliers );
	saver.Add( 7, &naftaForKill );
	saver.Add( 8, &naftaForAssist );
	saver.Add( 9, &naftaSpecForKill );
	saver.Add( 10, &teamNaftaForPresence );
	saver.Add( 11, &neutralKillExperienceModifier );
	saver.Add( 12, &heroNaftaParams );
	saver.Add( 13, &awardSpecRange );
	saver.Add( 14, &awardTeamRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PrimeSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "giveWorldPrimeToDead", &giveWorldPrimeToDead );
	saver.Add( "giveWorldPrimeRessurectDelay", &giveWorldPrimeRessurectDelay );
	saver.Add( "startPrimePerTeam", &startPrimePerTeam );
	saver.Add( "giveWorldPrimeAmount", &giveWorldPrimeAmount );
	saver.Add( "multipliers", &multipliers );
	saver.Add( "naftaForKill", &naftaForKill );
	saver.Add( "naftaForAssist", &naftaForAssist );
	saver.Add( "naftaSpecForKill", &naftaSpecForKill );
	saver.Add( "teamNaftaForPresence", &teamNaftaForPresence );
	saver.Add( "neutralKillExperienceModifier", &neutralKillExperienceModifier );
	saver.Add( "heroNaftaParams", &heroNaftaParams );
	saver.Add( "awardSpecRange", &awardSpecRange );
	saver.Add( "awardTeamRange", &awardTeamRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceDesc::ResourceDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &key );
	saver.Add( 3, &resource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "key", &key );
	saver.Add( "resource", &resource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptArea::ScriptArea() :
		radius( 10.0f )
	, targetType( SPELLTARGET_ALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptArea::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &position );
	saver.Add( 4, &radius );
	saver.Add( 5, &targetType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptArea::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "position", &position );
	saver.Add( "radius", &radius );
	saver.Add( "targetType", &targetType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptPolygonAreaPolygon::ScriptPolygonAreaPolygon()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPolygonAreaPolygon::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &indexes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPolygonAreaPolygon::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "indexes", &indexes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatisticBackgoundImages::StatisticBackgoundImages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatisticBackgoundImages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &normal );
	saver.Add( 3, &win );
	saver.Add( 4, &loose );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatisticBackgoundImages::operator&( IXmlSaver &saver )
{
	saver.Add( "normal", &normal );
	saver.Add( "win", &win );
	saver.Add( "loose", &loose );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TriggerMarkerBinding::TriggerMarkerBinding()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerMarkerBinding::operator&( IBinSaver &saver )
{
	saver.Add( 2, &TriggerPoint );
	saver.Add( 3, &MarkerPoints );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerMarkerBinding::operator&( IXmlSaver &saver )
{
	saver.Add( "TriggerPoint", &TriggerPoint );
	saver.Add( "MarkerPoints", &MarkerPoints );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMap::AdvMap()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMap::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cameraSettings );
	saver.Add( 3, &minimapImages );
	saver.Add( 4, &objects );
	saver.Add( 5, &terrain );
	saver.Add( 6, &soundEnvironment );
	saver.Add( 7, &lightEnvironment );
	saver.Add( 8, &nightLightEnvironment );
	saver.Add( 9, &bakedLighting );
	saver.Add( 10, &pointLights );
	saver.Add( 11, &scriptAreas );
	saver.Add( 12, &ObjectsLayerFileName );
	saver.Add( 13, &waterMapFileName );
	saver.Add( 14, &ambienceMap );
	saver.Add( 15, &mapSettings );
	saver.Add( 16, &postEffect );
	saver.Add( 17, &dayNightSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMap::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMap* parentPtr = (AdvMap*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMap::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "cameraSettings", &cameraSettings );
	saver.Add( "minimapImages", &minimapImages );
	saver.Add( "objects", &objects );
	saver.Add( "terrain", &terrain );
	saver.Add( "soundEnvironment", &soundEnvironment );
	saver.Add( "lightEnvironment", &lightEnvironment );
	saver.Add( "nightLightEnvironment", &nightLightEnvironment );
	saver.Add( "bakedLighting", &bakedLighting );
	saver.Add( "pointLights", &pointLights );
	saver.Add( "scriptAreas", &scriptAreas );
	saver.Add( "ObjectsLayerFileName", &ObjectsLayerFileName );
	saver.Add( "waterMapFileName", &waterMapFileName );
	saver.Add( "ambienceMap", &ambienceMap );
	saver.Add( "mapSettings", &mapSettings );
	saver.Add( "postEffect", &postEffect );
	saver.Add( "dayNightSettings", &dayNightSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMap::Assign( const AdvMap& _advMap )
{
	cameraSettings = _advMap.cameraSettings;
	minimapImages = _advMap.minimapImages;
	objects = _advMap.objects;
	terrain = _advMap.terrain;
	soundEnvironment = _advMap.soundEnvironment;
	lightEnvironment = _advMap.lightEnvironment;
	nightLightEnvironment = _advMap.nightLightEnvironment;
	bakedLighting.dynObjLightingGridResX = _advMap.bakedLighting.dynObjLightingGridResX;
	bakedLighting.dynObjLightingGridResY = _advMap.bakedLighting.dynObjLightingGridResY;
	bakedLighting.renderedEnvironmentEffect = _advMap.bakedLighting.renderedEnvironmentEffect;
	bakedLighting.renderedEnvironmentRange = _advMap.bakedLighting.renderedEnvironmentRange;
	bakedLighting.dynObjBakedLighting = _advMap.bakedLighting.dynObjBakedLighting;
	bakedLighting.vertexColorsFileName = _advMap.bakedLighting.vertexColorsFileName;
	pointLights = _advMap.pointLights;
	scriptAreas = _advMap.scriptAreas;
	ObjectsLayerFileName = _advMap.ObjectsLayerFileName;
	waterMapFileName = _advMap.waterMapFileName;
	ambienceMap.texture = _advMap.ambienceMap.texture;
	ambienceMap.radius = _advMap.ambienceMap.radius;
	ambienceMap.directivity = _advMap.ambienceMap.directivity;
	mapSettings = _advMap.mapSettings;
	postEffect = _advMap.postEffect;
	dayNightSettings.initialState = _advMap.dayNightSettings.initialState;
	dayNightSettings.initialStateFraction = _advMap.dayNightSettings.initialStateFraction;
	dayNightSettings.transitionDuration = _advMap.dayNightSettings.transitionDuration;
	dayNightSettings.transitionThreshold = _advMap.dayNightSettings.transitionThreshold;
	dayNightSettings.dayDuration = _advMap.dayNightSettings.dayDuration;
	dayNightSettings.nightDuration = _advMap.dayNightSettings.nightDuration;
	dayNightSettings.twilightDuration = _advMap.dayNightSettings.twilightDuration;
	dayNightSettings.twilightFraction = _advMap.dayNightSettings.twilightFraction;
	dayNightSettings.nightSpecularReduction = _advMap.dayNightSettings.nightSpecularReduction;
	dayNightSettings.hideDayNightWidget = _advMap.dayNightSettings.hideDayNightWidget;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapCameraSpline::AdvMapCameraSpline() :
		hight( 5 )
	, SmoothStart( false )
	, StartTime( 1.0f )
	, SmoothEnd( false )
	, EndTime( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCameraSpline::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &points );
	saver.Add( 3, &hight );
	saver.Add( 4, &SmoothStart );
	saver.Add( 5, &StartTime );
	saver.Add( 6, &SmoothEnd );
	saver.Add( 7, &EndTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapCameraSpline::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapCameraSpline* parentPtr = (AdvMapCameraSpline*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCameraSpline::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "points", &points );
	saver.Add( "hight", &hight );
	saver.Add( "SmoothStart", &SmoothStart );
	saver.Add( "StartTime", &StartTime );
	saver.Add( "SmoothEnd", &SmoothEnd );
	saver.Add( "EndTime", &EndTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapCameraSpline::Assign( const AdvMapCameraSpline& _advMapCameraSpline )
{
	points = _advMapCameraSpline.points;
	hight = _advMapCameraSpline.hight;
	SmoothStart = _advMapCameraSpline.SmoothStart;
	StartTime = _advMapCameraSpline.StartTime;
	SmoothEnd = _advMapCameraSpline.SmoothEnd;
	EndTime = _advMapCameraSpline.EndTime;
	collision = _advMapCameraSpline.collision;
	lockMask.tileSize = _advMapCameraSpline.lockMask.tileSize;
	lockMask.mask = _advMapCameraSpline.lockMask.mask;
	minLockScale = _advMapCameraSpline.minLockScale;
	rounded = _advMapCameraSpline.rounded;
	heightObject = _advMapCameraSpline.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapDescription::AdvMapDescription() :
		mapType( MAPTYPE_PVP )
	, PartyMode( PARTYMODE_ALLIESANDENEMIES )
	, acceptNeeded( false )
	, teamSize( 5 )
	, minTeamSize( -1 )
	, maxUncompleteTeamSize( -1 )
	, productionMode( false )
	, victoryPoint( 1.0f )
	, canUseSkins( true )
	, botsUseSkins( false )
	, minimalGuildFightTeam( 3 )
	, playSameTeamTimeOut( 30 )
	, AvailableForLeavers( true )
	, PlusPointForLeave( false )
	, MinusPointsPerFullGame( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &title );
	saver.Add( 3, &loadingBackgroundImages );
	saver.Add( 4, &statisticBackgroundImages );
	saver.Add( 5, &modeVisualDescription );
	saver.Add( 6, &image );
	saver.Add( 7, &mapType );
	saver.Add( 8, &mapWithBots );
	saver.Add( 9, &PartyMode );
	saver.Add( 10, &acceptNeeded );
	saver.Add( 11, &description );
	saver.Add( 12, &map );
	saver.Add( 13, &heroesOverride );
	saver.Add( 14, &matchmakingSettings );
	saver.Add( 15, &teamSize );
	saver.Add( 16, &minTeamSize );
	saver.Add( 17, &maxUncompleteTeamSize );
	saver.Add( 18, &productionMode );
	saver.Add( 19, &mapSettings );
	saver.Add( 20, &rollSettings );
	saver.Add( 21, &guardRollSettings );
	saver.Add( 22, &scoringTable );
	saver.Add( 23, &victoryPoint );
	saver.Add( 24, &FWODGroup );
	saver.Add( 25, &FirstWinVisualInfo );
	saver.Add( 26, &canUseSkins );
	saver.Add( 27, &botsUseSkins );
	saver.Add( 28, &minimalGuildFightTeam );
	saver.Add( 29, &gameSvcSettings );
	saver.Add( 30, &playSameTeamTimeOut );
	saver.Add( 31, &AvailableForLeavers );
	saver.Add( 32, &PlusPointForLeave );
	saver.Add( 33, &MinusPointsPerFullGame );

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
	saver.Add( "title", &title );
	saver.Add( "loadingBackgroundImages", &loadingBackgroundImages );
	saver.Add( "statisticBackgroundImages", &statisticBackgroundImages );
	saver.Add( "modeVisualDescription", &modeVisualDescription );
	saver.Add( "image", &image );
	saver.Add( "mapType", &mapType );
	saver.Add( "mapWithBots", &mapWithBots );
	saver.Add( "PartyMode", &PartyMode );
	saver.Add( "acceptNeeded", &acceptNeeded );
	saver.Add( "description", &description );
	saver.Add( "map", &map );
	saver.Add( "heroesOverride", &heroesOverride );
	saver.Add( "matchmakingSettings", &matchmakingSettings );
	saver.Add( "teamSize", &teamSize );
	saver.Add( "minTeamSize", &minTeamSize );
	saver.Add( "maxUncompleteTeamSize", &maxUncompleteTeamSize );
	saver.Add( "productionMode", &productionMode );
	saver.Add( "mapSettings", &mapSettings );
	saver.Add( "rollSettings", &rollSettings );
	saver.Add( "guardRollSettings", &guardRollSettings );
	saver.Add( "scoringTable", &scoringTable );
	saver.Add( "victoryPoint", &victoryPoint );
	saver.Add( "FWODGroup", &FWODGroup );
	saver.Add( "FirstWinVisualInfo", &FirstWinVisualInfo );
	saver.Add( "canUseSkins", &canUseSkins );
	saver.Add( "botsUseSkins", &botsUseSkins );
	saver.Add( "minimalGuildFightTeam", &minimalGuildFightTeam );
	saver.Add( "gameSvcSettings", &gameSvcSettings );
	saver.Add( "playSameTeamTimeOut", &playSameTeamTimeOut );
	saver.Add( "AvailableForLeavers", &AvailableForLeavers );
	saver.Add( "PlusPointForLeave", &PlusPointForLeave );
	saver.Add( "MinusPointsPerFullGame", &MinusPointsPerFullGame );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapDescription::Assign( const AdvMapDescription& _advMapDescription )
{
	title = _advMapDescription.title;
	loadingBackgroundImages.back = _advMapDescription.loadingBackgroundImages.back;
	loadingBackgroundImages.logo = _advMapDescription.loadingBackgroundImages.logo;
	statisticBackgroundImages.normal = _advMapDescription.statisticBackgroundImages.normal;
	statisticBackgroundImages.win = _advMapDescription.statisticBackgroundImages.win;
	statisticBackgroundImages.loose = _advMapDescription.statisticBackgroundImages.loose;
	modeVisualDescription = _advMapDescription.modeVisualDescription;
	image = _advMapDescription.image;
	mapType = _advMapDescription.mapType;
	mapWithBots = _advMapDescription.mapWithBots;
	PartyMode = _advMapDescription.PartyMode;
	acceptNeeded = _advMapDescription.acceptNeeded;
	description = _advMapDescription.description;
	map = _advMapDescription.map;
	heroesOverride = _advMapDescription.heroesOverride;
	matchmakingSettings = _advMapDescription.matchmakingSettings;
	teamSize = _advMapDescription.teamSize;
	minTeamSize = _advMapDescription.minTeamSize;
	maxUncompleteTeamSize = _advMapDescription.maxUncompleteTeamSize;
	productionMode = _advMapDescription.productionMode;
	mapSettings = _advMapDescription.mapSettings;
	rollSettings = _advMapDescription.rollSettings;
	guardRollSettings = _advMapDescription.guardRollSettings;
	scoringTable = _advMapDescription.scoringTable;
	victoryPoint = _advMapDescription.victoryPoint;
	FWODGroup = _advMapDescription.FWODGroup;
	FirstWinVisualInfo = _advMapDescription.FirstWinVisualInfo;
	canUseSkins = _advMapDescription.canUseSkins;
	botsUseSkins = _advMapDescription.botsUseSkins;
	minimalGuildFightTeam = _advMapDescription.minimalGuildFightTeam;
	gameSvcSettings = _advMapDescription.gameSvcSettings;
	playSameTeamTimeOut = _advMapDescription.playSameTeamTimeOut;
	AvailableForLeavers = _advMapDescription.AvailableForLeavers;
	PlusPointForLeave = _advMapDescription.PlusPointForLeave;
	MinusPointsPerFullGame = _advMapDescription.MinusPointsPerFullGame;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapHeroesOverride::AdvMapHeroesOverride() :
		shuffleHeroesInTeam( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapHeroesOverride::operator&( IBinSaver &saver )
{
	saver.Add( 2, &singlePlayerMale );
	saver.Add( 3, &singlePlayerFemale );
	saver.Add( 4, &shuffleHeroesInTeam );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapHeroesOverride::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapHeroesOverride* parentPtr = (AdvMapHeroesOverride*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapHeroesOverride::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "singlePlayerMale", &singlePlayerMale );
	saver.Add( "singlePlayerFemale", &singlePlayerFemale );
	saver.Add( "shuffleHeroesInTeam", &shuffleHeroesInTeam );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapHeroesOverride::Assign( const AdvMapHeroesOverride& _advMapHeroesOverride )
{
	singlePlayerMale = _advMapHeroesOverride.singlePlayerMale;
	singlePlayerFemale = _advMapHeroesOverride.singlePlayerFemale;
	shuffleHeroesInTeam = _advMapHeroesOverride.shuffleHeroesInTeam;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapHeroesOverrideData::AdvMapHeroesOverrideData()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapHeroesOverrideData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ownHero );
	saver.Add( 3, &allies );
	saver.Add( 4, &enemies );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapHeroesOverrideData::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapHeroesOverrideData* parentPtr = (AdvMapHeroesOverrideData*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapHeroesOverrideData::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "ownHero", &ownHero );
	saver.Add( "allies", &allies );
	saver.Add( "enemies", &enemies );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapHeroesOverrideData::Assign( const AdvMapHeroesOverrideData& _advMapHeroesOverrideData )
{
	ownHero.hero = _advMapHeroesOverrideData.ownHero.hero;
	ownHero.nickname = _advMapHeroesOverrideData.ownHero.nickname;
	allies = _advMapHeroesOverrideData.allies;
	enemies = _advMapHeroesOverrideData.enemies;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapSettings::AdvMapSettings() :
		battleStartDelay( 10 )
	, towersVulnerabilityDelay( 0 )
	, useCustomBattleStartAnnouncement( false )
	, showAllHeroes( true )
	, force( 125.0f )
	, minRequiredHeroForce( 0.0f )
	, maxRequiredHeroForce( 10000.0f )
	, fullPartyOnly( false )
	, trainingForceCoeff( 1.0f )
	, enableAnnouncements( true )
	, enablePortalTalent( true )
	, enableAllScriptFunctions( false )
	, enableStatistics( true )
	, creepLevelCap( -1 )
	, emblemHeroNeeds( 3 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &battleStartDelay );
	saver.Add( 3, &towersVulnerabilityDelay );
	saver.Add( 4, &customBattleStartAnnouncement );
	saver.Add( 5, &useCustomBattleStartAnnouncement );
	saver.Add( 6, &showAllHeroes );
	saver.Add( 7, &force );
	saver.Add( 8, &minRequiredHeroForce );
	saver.Add( 9, &maxRequiredHeroForce );
	saver.Add( 10, &fullPartyOnly );
	saver.Add( 11, &dictionary );
	saver.Add( 12, &primeSettings );
	saver.Add( 13, &dialogsCollection );
	saver.Add( 14, &hintsCollection );
	saver.Add( 15, &questsCollection );
	saver.Add( 16, &trainingForceCoeff );
	saver.Add( 17, &scriptFileName );
	saver.Add( 18, &heroRespawnParams );
	saver.Add( 19, &triggerMarkerBinding );
	saver.Add( 20, &creepAnnounceList );
	saver.Add( 21, &votingForSurrender );
	saver.Add( 22, &overrideTooltipParams );
	saver.Add( 23, &overrideMinimapParams );
	saver.Add( 24, &overridePortalTalent );
	saver.Add( 25, &overrideGlyphSettings );
	saver.Add( 26, &overrideBotsSettings );
	saver.Add( 27, &enableAnnouncements );
	saver.Add( 28, &enablePortalTalent );
	saver.Add( 29, &enableAllScriptFunctions );
	saver.Add( 30, &enableStatistics );
	saver.Add( 31, &creepLevelCap );
	saver.Add( 32, &emblemHeroNeeds );

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
	saver.Add( "battleStartDelay", &battleStartDelay );
	saver.Add( "towersVulnerabilityDelay", &towersVulnerabilityDelay );
	saver.Add( "customBattleStartAnnouncement", &customBattleStartAnnouncement );
	saver.Add( "useCustomBattleStartAnnouncement", &useCustomBattleStartAnnouncement );
	saver.Add( "showAllHeroes", &showAllHeroes );
	saver.Add( "force", &force );
	saver.Add( "minRequiredHeroForce", &minRequiredHeroForce );
	saver.Add( "maxRequiredHeroForce", &maxRequiredHeroForce );
	saver.Add( "fullPartyOnly", &fullPartyOnly );
	saver.Add( "dictionary", &dictionary );
	saver.Add( "primeSettings", &primeSettings );
	saver.Add( "dialogsCollection", &dialogsCollection );
	saver.Add( "hintsCollection", &hintsCollection );
	saver.Add( "questsCollection", &questsCollection );
	saver.Add( "trainingForceCoeff", &trainingForceCoeff );
	saver.Add( "scriptFileName", &scriptFileName );
	saver.Add( "heroRespawnParams", &heroRespawnParams );
	saver.Add( "triggerMarkerBinding", &triggerMarkerBinding );
	saver.Add( "creepAnnounceList", &creepAnnounceList );
	saver.Add( "votingForSurrender", &votingForSurrender );
	saver.Add( "overrideTooltipParams", &overrideTooltipParams );
	saver.Add( "overrideMinimapParams", &overrideMinimapParams );
	saver.Add( "overridePortalTalent", &overridePortalTalent );
	saver.Add( "overrideGlyphSettings", &overrideGlyphSettings );
	saver.Add( "overrideBotsSettings", &overrideBotsSettings );
	saver.Add( "enableAnnouncements", &enableAnnouncements );
	saver.Add( "enablePortalTalent", &enablePortalTalent );
	saver.Add( "enableAllScriptFunctions", &enableAllScriptFunctions );
	saver.Add( "enableStatistics", &enableStatistics );
	saver.Add( "creepLevelCap", &creepLevelCap );
	saver.Add( "emblemHeroNeeds", &emblemHeroNeeds );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapSettings::Assign( const AdvMapSettings& _advMapSettings )
{
	battleStartDelay = _advMapSettings.battleStartDelay;
	towersVulnerabilityDelay = _advMapSettings.towersVulnerabilityDelay;
	customBattleStartAnnouncement.imageBurn = _advMapSettings.customBattleStartAnnouncement.imageBurn;
	customBattleStartAnnouncement.imageFreeze = _advMapSettings.customBattleStartAnnouncement.imageFreeze;
	customBattleStartAnnouncement.announcementText = _advMapSettings.customBattleStartAnnouncement.announcementText;
	customBattleStartAnnouncement.battleStartSound.projectName = _advMapSettings.customBattleStartAnnouncement.battleStartSound.projectName;
	customBattleStartAnnouncement.battleStartSound.groupName = _advMapSettings.customBattleStartAnnouncement.battleStartSound.groupName;
	customBattleStartAnnouncement.battleStartSound.eventName = _advMapSettings.customBattleStartAnnouncement.battleStartSound.eventName;
	useCustomBattleStartAnnouncement = _advMapSettings.useCustomBattleStartAnnouncement;
	showAllHeroes = _advMapSettings.showAllHeroes;
	force = _advMapSettings.force;
	minRequiredHeroForce = _advMapSettings.minRequiredHeroForce;
	maxRequiredHeroForce = _advMapSettings.maxRequiredHeroForce;
	fullPartyOnly = _advMapSettings.fullPartyOnly;
	dictionary = _advMapSettings.dictionary;
	primeSettings.giveWorldPrimeToDead = _advMapSettings.primeSettings.giveWorldPrimeToDead;
	primeSettings.giveWorldPrimeRessurectDelay = _advMapSettings.primeSettings.giveWorldPrimeRessurectDelay;
	primeSettings.startPrimePerTeam = _advMapSettings.primeSettings.startPrimePerTeam;
	primeSettings.giveWorldPrimeAmount = _advMapSettings.primeSettings.giveWorldPrimeAmount;
	primeSettings.multipliers = _advMapSettings.primeSettings.multipliers;
	primeSettings.naftaForKill = _advMapSettings.primeSettings.naftaForKill;
	primeSettings.naftaForAssist = _advMapSettings.primeSettings.naftaForAssist;
	primeSettings.naftaSpecForKill = _advMapSettings.primeSettings.naftaSpecForKill;
	primeSettings.teamNaftaForPresence = _advMapSettings.primeSettings.teamNaftaForPresence;
	primeSettings.neutralKillExperienceModifier = _advMapSettings.primeSettings.neutralKillExperienceModifier;
	primeSettings.heroNaftaParams = _advMapSettings.primeSettings.heroNaftaParams;
	primeSettings.awardSpecRange = _advMapSettings.primeSettings.awardSpecRange;
	primeSettings.awardTeamRange = _advMapSettings.primeSettings.awardTeamRange;
	dialogsCollection = _advMapSettings.dialogsCollection;
	hintsCollection = _advMapSettings.hintsCollection;
	questsCollection = _advMapSettings.questsCollection;
	trainingForceCoeff = _advMapSettings.trainingForceCoeff;
	scriptFileName = _advMapSettings.scriptFileName;
	heroRespawnParams = _advMapSettings.heroRespawnParams;
	triggerMarkerBinding = _advMapSettings.triggerMarkerBinding;
	creepAnnounceList = _advMapSettings.creepAnnounceList;
	votingForSurrender = _advMapSettings.votingForSurrender;
	overrideTooltipParams = _advMapSettings.overrideTooltipParams;
	overrideMinimapParams = _advMapSettings.overrideMinimapParams;
	overridePortalTalent = _advMapSettings.overridePortalTalent;
	overrideGlyphSettings = _advMapSettings.overrideGlyphSettings;
	overrideBotsSettings = _advMapSettings.overrideBotsSettings;
	enableAnnouncements = _advMapSettings.enableAnnouncements;
	enablePortalTalent = _advMapSettings.enablePortalTalent;
	enableAllScriptFunctions = _advMapSettings.enableAllScriptFunctions;
	enableStatistics = _advMapSettings.enableStatistics;
	creepLevelCap = _advMapSettings.creepLevelCap;
	emblemHeroNeeds = _advMapSettings.emblemHeroNeeds;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapWaterZone::AdvMapWaterZone()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapWaterZone::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &area );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapWaterZone::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapWaterZone* parentPtr = (AdvMapWaterZone*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapWaterZone::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "area", &area );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapWaterZone::Assign( const AdvMapWaterZone& _advMapWaterZone )
{
	area.points = _advMapWaterZone.area.points;
	area.HasWidth = _advMapWaterZone.area.HasWidth;
	area.IsCircle = _advMapWaterZone.area.IsCircle;
	area.AbsolutePosition = _advMapWaterZone.area.AbsolutePosition;
	collision = _advMapWaterZone.collision;
	lockMask.tileSize = _advMapWaterZone.lockMask.tileSize;
	lockMask.mask = _advMapWaterZone.lockMask.mask;
	minLockScale = _advMapWaterZone.minLockScale;
	rounded = _advMapWaterZone.rounded;
	heightObject = _advMapWaterZone.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepAnnounceList::CreepAnnounceList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepAnnounceList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &list );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepAnnounceList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CreepAnnounceList* parentPtr = (CreepAnnounceList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepAnnounceList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "list", &list );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepAnnounceList::Assign( const CreepAnnounceList& _creepAnnounceList )
{
	list = _creepAnnounceList.list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DbAdvMapCTESettings::DbAdvMapCTESettings()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbAdvMapCTESettings::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AdvMapSettings*)this );
	saver.Add( 2, &altarName_A );
	saver.Add( 3, &altarName_B );
	saver.Add( 4, &dragonSpawnerName );
	saver.Add( 5, &damageVariableName );
	saver.Add( 6, &damageAnimationTable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbAdvMapCTESettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DbAdvMapCTESettings* parentPtr = (DbAdvMapCTESettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DbAdvMapCTESettings::SerializeSelf( IXmlSaver &saver )
{
	AdvMapSettings::SerializeSelf( saver );
	saver.Add( "altarName_A", &altarName_A );
	saver.Add( "altarName_B", &altarName_B );
	saver.Add( "dragonSpawnerName", &dragonSpawnerName );
	saver.Add( "damageVariableName", &damageVariableName );
	saver.Add( "damageAnimationTable", &damageAnimationTable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DbAdvMapCTESettings::Assign( const DbAdvMapCTESettings& _dbAdvMapCTESettings )
{
	altarName_A = _dbAdvMapCTESettings.altarName_A;
	altarName_B = _dbAdvMapCTESettings.altarName_B;
	dragonSpawnerName = _dbAdvMapCTESettings.dragonSpawnerName;
	damageVariableName = _dbAdvMapCTESettings.damageVariableName;
	damageAnimationTable = _dbAdvMapCTESettings.damageAnimationTable;
	battleStartDelay = _dbAdvMapCTESettings.battleStartDelay;
	towersVulnerabilityDelay = _dbAdvMapCTESettings.towersVulnerabilityDelay;
	customBattleStartAnnouncement.imageBurn = _dbAdvMapCTESettings.customBattleStartAnnouncement.imageBurn;
	customBattleStartAnnouncement.imageFreeze = _dbAdvMapCTESettings.customBattleStartAnnouncement.imageFreeze;
	customBattleStartAnnouncement.announcementText = _dbAdvMapCTESettings.customBattleStartAnnouncement.announcementText;
	customBattleStartAnnouncement.battleStartSound.projectName = _dbAdvMapCTESettings.customBattleStartAnnouncement.battleStartSound.projectName;
	customBattleStartAnnouncement.battleStartSound.groupName = _dbAdvMapCTESettings.customBattleStartAnnouncement.battleStartSound.groupName;
	customBattleStartAnnouncement.battleStartSound.eventName = _dbAdvMapCTESettings.customBattleStartAnnouncement.battleStartSound.eventName;
	useCustomBattleStartAnnouncement = _dbAdvMapCTESettings.useCustomBattleStartAnnouncement;
	showAllHeroes = _dbAdvMapCTESettings.showAllHeroes;
	force = _dbAdvMapCTESettings.force;
	minRequiredHeroForce = _dbAdvMapCTESettings.minRequiredHeroForce;
	maxRequiredHeroForce = _dbAdvMapCTESettings.maxRequiredHeroForce;
	fullPartyOnly = _dbAdvMapCTESettings.fullPartyOnly;
	dictionary = _dbAdvMapCTESettings.dictionary;
	primeSettings.giveWorldPrimeToDead = _dbAdvMapCTESettings.primeSettings.giveWorldPrimeToDead;
	primeSettings.giveWorldPrimeRessurectDelay = _dbAdvMapCTESettings.primeSettings.giveWorldPrimeRessurectDelay;
	primeSettings.startPrimePerTeam = _dbAdvMapCTESettings.primeSettings.startPrimePerTeam;
	primeSettings.giveWorldPrimeAmount = _dbAdvMapCTESettings.primeSettings.giveWorldPrimeAmount;
	primeSettings.multipliers = _dbAdvMapCTESettings.primeSettings.multipliers;
	primeSettings.naftaForKill = _dbAdvMapCTESettings.primeSettings.naftaForKill;
	primeSettings.naftaForAssist = _dbAdvMapCTESettings.primeSettings.naftaForAssist;
	primeSettings.naftaSpecForKill = _dbAdvMapCTESettings.primeSettings.naftaSpecForKill;
	primeSettings.teamNaftaForPresence = _dbAdvMapCTESettings.primeSettings.teamNaftaForPresence;
	primeSettings.neutralKillExperienceModifier = _dbAdvMapCTESettings.primeSettings.neutralKillExperienceModifier;
	primeSettings.heroNaftaParams = _dbAdvMapCTESettings.primeSettings.heroNaftaParams;
	primeSettings.awardSpecRange = _dbAdvMapCTESettings.primeSettings.awardSpecRange;
	primeSettings.awardTeamRange = _dbAdvMapCTESettings.primeSettings.awardTeamRange;
	dialogsCollection = _dbAdvMapCTESettings.dialogsCollection;
	hintsCollection = _dbAdvMapCTESettings.hintsCollection;
	questsCollection = _dbAdvMapCTESettings.questsCollection;
	trainingForceCoeff = _dbAdvMapCTESettings.trainingForceCoeff;
	scriptFileName = _dbAdvMapCTESettings.scriptFileName;
	heroRespawnParams = _dbAdvMapCTESettings.heroRespawnParams;
	triggerMarkerBinding = _dbAdvMapCTESettings.triggerMarkerBinding;
	creepAnnounceList = _dbAdvMapCTESettings.creepAnnounceList;
	votingForSurrender = _dbAdvMapCTESettings.votingForSurrender;
	overrideTooltipParams = _dbAdvMapCTESettings.overrideTooltipParams;
	overrideMinimapParams = _dbAdvMapCTESettings.overrideMinimapParams;
	overridePortalTalent = _dbAdvMapCTESettings.overridePortalTalent;
	overrideGlyphSettings = _dbAdvMapCTESettings.overrideGlyphSettings;
	overrideBotsSettings = _dbAdvMapCTESettings.overrideBotsSettings;
	enableAnnouncements = _dbAdvMapCTESettings.enableAnnouncements;
	enablePortalTalent = _dbAdvMapCTESettings.enablePortalTalent;
	enableAllScriptFunctions = _dbAdvMapCTESettings.enableAllScriptFunctions;
	enableStatistics = _dbAdvMapCTESettings.enableStatistics;
	creepLevelCap = _dbAdvMapCTESettings.creepLevelCap;
	emblemHeroNeeds = _dbAdvMapCTESettings.emblemHeroNeeds;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DictionaryPreloadingResources::DictionaryPreloadingResources()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DictionaryPreloadingResources::operator&( IBinSaver &saver )
{
	saver.Add( 2, &resources );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DictionaryPreloadingResources::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DictionaryPreloadingResources* parentPtr = (DictionaryPreloadingResources*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DictionaryPreloadingResources::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "resources", &resources );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DictionaryPreloadingResources::Assign( const DictionaryPreloadingResources& _dictionaryPreloadingResources )
{
	resources = _dictionaryPreloadingResources.resources;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FWODVisualInfo::FWODVisualInfo()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FWODVisualInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &icon );
	saver.Add( 3, &iconSmall );
	saver.Add( 4, &tooltip );
	saver.Add( 5, &sessionTooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FWODVisualInfo::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FWODVisualInfo* parentPtr = (FWODVisualInfo*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FWODVisualInfo::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "icon", &icon );
	saver.Add( "iconSmall", &iconSmall );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "sessionTooltip", &sessionTooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FWODVisualInfo::Assign( const FWODVisualInfo& _fWODVisualInfo )
{
	icon = _fWODVisualInfo.icon;
	iconSmall = _fWODVisualInfo.iconSmall;
	tooltip = _fWODVisualInfo.tooltip;
	sessionTooltip = _fWODVisualInfo.sessionTooltip;
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
GlyphManagerParams::GlyphManagerParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphManagerParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &settings );
	saver.Add( 3, &glyphs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphManagerParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GlyphManagerParams* parentPtr = (GlyphManagerParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphManagerParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "settings", &settings );
	saver.Add( "glyphs", &glyphs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlyphManagerParams::Assign( const GlyphManagerParams& _glyphManagerParams )
{
	settings.minNormalSpawnDelay = _glyphManagerParams.settings.minNormalSpawnDelay;
	settings.maxNormalSpawnDelay = _glyphManagerParams.settings.maxNormalSpawnDelay;
	settings.minAfterPickupSpawnDelay = _glyphManagerParams.settings.minAfterPickupSpawnDelay;
	settings.maxAfterPickupSpawnDelay = _glyphManagerParams.settings.maxAfterPickupSpawnDelay;
	settings.spawnAttemptDelayDecrease = _glyphManagerParams.settings.spawnAttemptDelayDecrease;
	settings.maxInstances = _glyphManagerParams.settings.maxInstances;
	settings.spawnMode = _glyphManagerParams.settings.spawnMode;
	glyphs = _glyphManagerParams.glyphs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroNaftaParams::HeroNaftaParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroNaftaParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &naftaForKill );
	saver.Add( 3, &naftaForAssist );
	saver.Add( 4, &naftaSpecForKill );
	saver.Add( 5, &teamNaftaForPresence );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroNaftaParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroNaftaParams* parentPtr = (HeroNaftaParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroNaftaParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "naftaForKill", &naftaForKill );
	saver.Add( "naftaForAssist", &naftaForAssist );
	saver.Add( "naftaSpecForKill", &naftaSpecForKill );
	saver.Add( "teamNaftaForPresence", &teamNaftaForPresence );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroNaftaParams::Assign( const HeroNaftaParams& _heroNaftaParams )
{
	naftaForKill = _heroNaftaParams.naftaForKill;
	naftaForAssist = _heroNaftaParams.naftaForAssist;
	naftaSpecForKill = _heroNaftaParams.naftaSpecForKill;
	teamNaftaForPresence = _heroNaftaParams.teamNaftaForPresence;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptPolygonArea::ScriptPolygonArea()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPolygonArea::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &points );
	saver.Add( 3, &polygons );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPolygonArea::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScriptPolygonArea* parentPtr = (ScriptPolygonArea*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptPolygonArea::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "points", &points );
	saver.Add( "polygons", &polygons );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptPolygonArea::Assign( const ScriptPolygonArea& _scriptPolygonArea )
{
	points = _scriptPolygonArea.points;
	polygons = _scriptPolygonArea.polygons;
	collision = _scriptPolygonArea.collision;
	lockMask.tileSize = _scriptPolygonArea.lockMask.tileSize;
	lockMask.mask = _scriptPolygonArea.lockMask.mask;
	minLockScale = _scriptPolygonArea.minLockScale;
	rounded = _scriptPolygonArea.rounded;
	heightObject = _scriptPolygonArea.heightObject;
}
}; // namespace NDb
