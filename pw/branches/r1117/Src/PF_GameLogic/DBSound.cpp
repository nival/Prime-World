// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBSound.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SoundRoot );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SoundAmbientGroup value )
{
	switch( value )
	{
		case SOUNDAMBIENTGROUP_BASEA:
			return "BaseA";
		case SOUNDAMBIENTGROUP_BASEB:
			return "BaseB";
		case SOUNDAMBIENTGROUP_FORESTN:
			return "ForestN";
		case SOUNDAMBIENTGROUP_FORESTA:
			return "ForestA";
		case SOUNDAMBIENTGROUP_FORESTB:
			return "ForestB";
		case SOUNDAMBIENTGROUP_WATER:
			return "Water";
		case SOUNDAMBIENTGROUP_ROAD:
			return "Road";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SoundAmbientGroup", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SoundAmbientGroup StringToEnum_SoundAmbientGroup( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SoundAmbientGroup)(NStr::ToInt( value ));
	if ( strcmp( value, "BaseA" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_BASEA" ) == 0 )
		return SOUNDAMBIENTGROUP_BASEA;
	if ( strcmp( value, "BaseB" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_BASEB" ) == 0 )
		return SOUNDAMBIENTGROUP_BASEB;
	if ( strcmp( value, "ForestN" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_FORESTN" ) == 0 )
		return SOUNDAMBIENTGROUP_FORESTN;
	if ( strcmp( value, "ForestA" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_FORESTA" ) == 0 )
		return SOUNDAMBIENTGROUP_FORESTA;
	if ( strcmp( value, "ForestB" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_FORESTB" ) == 0 )
		return SOUNDAMBIENTGROUP_FORESTB;
	if ( strcmp( value, "Water" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_WATER" ) == 0 )
		return SOUNDAMBIENTGROUP_WATER;
	if ( strcmp( value, "Road" ) == 0 || strcmp( value, "SOUNDAMBIENTGROUP_ROAD" ) == 0 )
		return SOUNDAMBIENTGROUP_ROAD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SoundAmbientGroup", value ) );
	return SOUNDAMBIENTGROUP_BASEA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SoundScene value )
{
	switch( value )
	{
		case SOUNDSCENE_SESSIONA:
			return "SessionA";
		case SOUNDSCENE_SESSIONB:
			return "SessionB";
		case SOUNDSCENE_MINIGAME_02:
			return "Minigame_02";
		case SOUNDSCENE_LOADING:
			return "Loading";
		case SOUNDSCENE_DEAD:
			return "Dead";
		case SOUNDSCENE_BATTLE:
			return "Battle";
		case SOUNDSCENE_WIN:
			return "Win";
		case SOUNDSCENE_DEFEAT:
			return "Defeat";
		case SOUNDSCENE_TUTORIALA:
			return "TutorialA";
		case SOUNDSCENE_TUTORIALB:
			return "TutorialB";
		case SOUNDSCENE_TOWERDEATH:
			return "TowerDeath";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SoundScene", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SoundScene StringToEnum_SoundScene( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SoundScene)(NStr::ToInt( value ));
	if ( strcmp( value, "SessionA" ) == 0 || strcmp( value, "SOUNDSCENE_SESSIONA" ) == 0 )
		return SOUNDSCENE_SESSIONA;
	if ( strcmp( value, "SessionB" ) == 0 || strcmp( value, "SOUNDSCENE_SESSIONB" ) == 0 )
		return SOUNDSCENE_SESSIONB;
	if ( strcmp( value, "Minigame_02" ) == 0 || strcmp( value, "SOUNDSCENE_MINIGAME_02" ) == 0 )
		return SOUNDSCENE_MINIGAME_02;
	if ( strcmp( value, "Loading" ) == 0 || strcmp( value, "SOUNDSCENE_LOADING" ) == 0 )
		return SOUNDSCENE_LOADING;
	if ( strcmp( value, "Dead" ) == 0 || strcmp( value, "SOUNDSCENE_DEAD" ) == 0 )
		return SOUNDSCENE_DEAD;
	if ( strcmp( value, "Battle" ) == 0 || strcmp( value, "SOUNDSCENE_BATTLE" ) == 0 )
		return SOUNDSCENE_BATTLE;
	if ( strcmp( value, "Win" ) == 0 || strcmp( value, "SOUNDSCENE_WIN" ) == 0 )
		return SOUNDSCENE_WIN;
	if ( strcmp( value, "Defeat" ) == 0 || strcmp( value, "SOUNDSCENE_DEFEAT" ) == 0 )
		return SOUNDSCENE_DEFEAT;
	if ( strcmp( value, "TutorialA" ) == 0 || strcmp( value, "SOUNDSCENE_TUTORIALA" ) == 0 )
		return SOUNDSCENE_TUTORIALA;
	if ( strcmp( value, "TutorialB" ) == 0 || strcmp( value, "SOUNDSCENE_TUTORIALB" ) == 0 )
		return SOUNDSCENE_TUTORIALB;
	if ( strcmp( value, "TowerDeath" ) == 0 || strcmp( value, "SOUNDSCENE_TOWERDEATH" ) == 0 )
		return SOUNDSCENE_TOWERDEATH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SoundScene", value ) );
	return SOUNDSCENE_SESSIONA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundAmbientDesc::SoundAmbientDesc() :
		reverbPresetName( "Ambient" )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundAmbientDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &paramName );
	saver.Add( 3, &color );
	saver.Add( 4, &reverbPresetName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundAmbientDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "paramName", &paramName );
	saver.Add( "color", &color );
	saver.Add( "reverbPresetName", &reverbPresetName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TimerSounds::TimerSounds() :
		timeToRestorePitch( 5.0f )
	, timeToTickOnStart( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerSounds::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startTimerSound );
	saver.Add( 3, &startEventA );
	saver.Add( 4, &startEventB );
	saver.Add( 5, &deadTimerSound );
	saver.Add( 6, &deadReverbName );
	saver.Add( 7, &timeToRestorePitch );
	saver.Add( 8, &timeToTickOnStart );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerSounds::operator&( IXmlSaver &saver )
{
	saver.Add( "startTimerSound", &startTimerSound );
	saver.Add( "startEventA", &startEventA );
	saver.Add( "startEventB", &startEventB );
	saver.Add( "deadTimerSound", &deadTimerSound );
	saver.Add( "deadReverbName", &deadReverbName );
	saver.Add( "timeToRestorePitch", &timeToRestorePitch );
	saver.Add( "timeToTickOnStart", &timeToTickOnStart );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundRoot::SoundRoot() :
		timerHeroAskIdle( 15.0f )
	, timeToTowerDeath( 60.0f )
{
	sceneScenes.resize( 11 );
	ambienceGroups.resize( 7 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr< SoundRoot > SoundRoot::instance;
void SoundRoot::InitRoot( const DBID& dbid ) { InitRoot( Get<SoundRoot>( dbid ) ); }
void SoundRoot::InitRoot( const SoundRoot* _instance ) { instance = _instance; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Ptr< SoundRoot >& SoundRoot::GetRoot()
{
	NI_ASSERT( IsValid( instance ), "Root for type \"SoundRoot\" not initialized" );
	return instance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sceneScenes );
	saver.Add( 3, &timerSounds );
	saver.Add( 4, &heartbeat );
	saver.Add( 5, &heartbeatFemale );
	saver.Add( 6, &heartbeatParamName );
	saver.Add( 7, &ambient );
	saver.Add( 8, &ambienceGroups );
	saver.Add( 9, &preferencesVolumeHasChanged );
	saver.Add( 10, &lastHit );
	saver.Add( 11, &timerHeroAskIdle );
	saver.Add( 12, &timeToTowerDeath );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SoundRoot* parentPtr = (SoundRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundRoot::SerializeSelf( IXmlSaver &saver )
{
	sceneScenes.resize( 11 );
	saver.Add( "sceneScenes", &sceneScenes );
	saver.Add( "timerSounds", &timerSounds );
	saver.Add( "heartbeat", &heartbeat );
	saver.Add( "heartbeatFemale", &heartbeatFemale );
	saver.Add( "heartbeatParamName", &heartbeatParamName );
	saver.Add( "ambient", &ambient );
	ambienceGroups.resize( 7 );
	saver.Add( "ambienceGroups", &ambienceGroups );
	saver.Add( "preferencesVolumeHasChanged", &preferencesVolumeHasChanged );
	saver.Add( "lastHit", &lastHit );
	saver.Add( "timerHeroAskIdle", &timerHeroAskIdle );
	saver.Add( "timeToTowerDeath", &timeToTowerDeath );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundRoot::Assign( const SoundRoot& _soundRoot )
{
	sceneScenes = _soundRoot.sceneScenes;
	timerSounds.startTimerSound.projectName = _soundRoot.timerSounds.startTimerSound.projectName;
	timerSounds.startTimerSound.groupName = _soundRoot.timerSounds.startTimerSound.groupName;
	timerSounds.startTimerSound.eventName = _soundRoot.timerSounds.startTimerSound.eventName;
	timerSounds.startEventA.projectName = _soundRoot.timerSounds.startEventA.projectName;
	timerSounds.startEventA.groupName = _soundRoot.timerSounds.startEventA.groupName;
	timerSounds.startEventA.eventName = _soundRoot.timerSounds.startEventA.eventName;
	timerSounds.startEventB.projectName = _soundRoot.timerSounds.startEventB.projectName;
	timerSounds.startEventB.groupName = _soundRoot.timerSounds.startEventB.groupName;
	timerSounds.startEventB.eventName = _soundRoot.timerSounds.startEventB.eventName;
	timerSounds.deadTimerSound.projectName = _soundRoot.timerSounds.deadTimerSound.projectName;
	timerSounds.deadTimerSound.groupName = _soundRoot.timerSounds.deadTimerSound.groupName;
	timerSounds.deadTimerSound.eventName = _soundRoot.timerSounds.deadTimerSound.eventName;
	timerSounds.deadReverbName = _soundRoot.timerSounds.deadReverbName;
	timerSounds.timeToRestorePitch = _soundRoot.timerSounds.timeToRestorePitch;
	timerSounds.timeToTickOnStart = _soundRoot.timerSounds.timeToTickOnStart;
	heartbeat.projectName = _soundRoot.heartbeat.projectName;
	heartbeat.groupName = _soundRoot.heartbeat.groupName;
	heartbeat.eventName = _soundRoot.heartbeat.eventName;
	heartbeatFemale.projectName = _soundRoot.heartbeatFemale.projectName;
	heartbeatFemale.groupName = _soundRoot.heartbeatFemale.groupName;
	heartbeatFemale.eventName = _soundRoot.heartbeatFemale.eventName;
	heartbeatParamName = _soundRoot.heartbeatParamName;
	ambient.projectName = _soundRoot.ambient.projectName;
	ambient.groupName = _soundRoot.ambient.groupName;
	ambient.eventName = _soundRoot.ambient.eventName;
	ambienceGroups = _soundRoot.ambienceGroups;
	preferencesVolumeHasChanged.projectName = _soundRoot.preferencesVolumeHasChanged.projectName;
	preferencesVolumeHasChanged.groupName = _soundRoot.preferencesVolumeHasChanged.groupName;
	preferencesVolumeHasChanged.eventName = _soundRoot.preferencesVolumeHasChanged.eventName;
	lastHit.projectName = _soundRoot.lastHit.projectName;
	lastHit.groupName = _soundRoot.lastHit.groupName;
	lastHit.eventName = _soundRoot.lastHit.eventName;
	timerHeroAskIdle = _soundRoot.timerHeroAskIdle;
	timeToTowerDeath = _soundRoot.timeToTowerDeath;
}
}; // namespace NDb
