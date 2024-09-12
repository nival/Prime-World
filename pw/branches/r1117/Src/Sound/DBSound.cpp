// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "DBSound.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( FMODEventProject );
REGISTER_DBRESOURCE( Sound2D );
REGISTER_DBRESOURCE( SoundEnvironment );
REGISTER_DBRESOURCE( SoundStream );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAskSounds value )
{
	switch( value )
	{
		case ASKSOUNDS_MOVE:
			return "MOVE";
		case ASKSOUNDS_ABILITY_1:
			return "ABILITY_1";
		case ASKSOUNDS_ABILITY_2:
			return "ABILITY_2";
		case ASKSOUNDS_ABILITY_3:
			return "ABILITY_3";
		case ASKSOUNDS_ABILITY_ULT:
			return "ABILITY_ULT";
		case ASKSOUNDS_ATTACK:
			return "ATTACK";
		case ASKSOUNDS_DEATH:
			return "DEATH";
		case ASKSOUNDS_REVIVE:
			return "REVIVE";
		case ASKSOUNDS_KILL:
			return "KILL";
		case ASKSOUNDS_IDLE:
			return "IDLE";
		case ASKSOUNDS_RAISEFLAG:
			return "RAISEFLAG";
		case ASKSOUNDS_KILLCHAMPION:
			return "KILLCHAMPION";
		case ASKSOUNDS_MINIGAMEWIN:
			return "MINIGAMEWIN";
		case ASKSOUNDS_MINIGAMEFAIL:
			return "MINIGAMEFAIL";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAskSounds", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAskSounds StringToEnum_EAskSounds( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAskSounds)(NStr::ToInt( value ));
	if ( strcmp( value, "MOVE" ) == 0 || strcmp( value, "ASKSOUNDS_MOVE" ) == 0 )
		return ASKSOUNDS_MOVE;
	if ( strcmp( value, "ABILITY_1" ) == 0 || strcmp( value, "ASKSOUNDS_ABILITY_1" ) == 0 )
		return ASKSOUNDS_ABILITY_1;
	if ( strcmp( value, "ABILITY_2" ) == 0 || strcmp( value, "ASKSOUNDS_ABILITY_2" ) == 0 )
		return ASKSOUNDS_ABILITY_2;
	if ( strcmp( value, "ABILITY_3" ) == 0 || strcmp( value, "ASKSOUNDS_ABILITY_3" ) == 0 )
		return ASKSOUNDS_ABILITY_3;
	if ( strcmp( value, "ABILITY_ULT" ) == 0 || strcmp( value, "ASKSOUNDS_ABILITY_ULT" ) == 0 )
		return ASKSOUNDS_ABILITY_ULT;
	if ( strcmp( value, "ATTACK" ) == 0 || strcmp( value, "ASKSOUNDS_ATTACK" ) == 0 )
		return ASKSOUNDS_ATTACK;
	if ( strcmp( value, "DEATH" ) == 0 || strcmp( value, "ASKSOUNDS_DEATH" ) == 0 )
		return ASKSOUNDS_DEATH;
	if ( strcmp( value, "REVIVE" ) == 0 || strcmp( value, "ASKSOUNDS_REVIVE" ) == 0 )
		return ASKSOUNDS_REVIVE;
	if ( strcmp( value, "KILL" ) == 0 || strcmp( value, "ASKSOUNDS_KILL" ) == 0 )
		return ASKSOUNDS_KILL;
	if ( strcmp( value, "IDLE" ) == 0 || strcmp( value, "ASKSOUNDS_IDLE" ) == 0 )
		return ASKSOUNDS_IDLE;
	if ( strcmp( value, "RAISEFLAG" ) == 0 || strcmp( value, "ASKSOUNDS_RAISEFLAG" ) == 0 )
		return ASKSOUNDS_RAISEFLAG;
	if ( strcmp( value, "KILLCHAMPION" ) == 0 || strcmp( value, "ASKSOUNDS_KILLCHAMPION" ) == 0 )
		return ASKSOUNDS_KILLCHAMPION;
	if ( strcmp( value, "MINIGAMEWIN" ) == 0 || strcmp( value, "ASKSOUNDS_MINIGAMEWIN" ) == 0 )
		return ASKSOUNDS_MINIGAMEWIN;
	if ( strcmp( value, "MINIGAMEFAIL" ) == 0 || strcmp( value, "ASKSOUNDS_MINIGAMEFAIL" ) == 0 )
		return ASKSOUNDS_MINIGAMEFAIL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAskSounds", value ) );
	return ASKSOUNDS_MOVE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SoundCameraType value )
{
	switch( value )
	{
		case SOUNDCAMERATYPE_TOPDOWN:
			return "TopDown";
		case SOUNDCAMERATYPE_PERSPECTIVE:
			return "Perspective";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SoundCameraType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SoundCameraType StringToEnum_SoundCameraType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SoundCameraType)(NStr::ToInt( value ));
	if ( strcmp( value, "TopDown" ) == 0 || strcmp( value, "SOUNDCAMERATYPE_TOPDOWN" ) == 0 )
		return SOUNDCAMERATYPE_TOPDOWN;
	if ( strcmp( value, "Perspective" ) == 0 || strcmp( value, "SOUNDCAMERATYPE_PERSPECTIVE" ) == 0 )
		return SOUNDCAMERATYPE_PERSPECTIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SoundCameraType", value ) );
	return SOUNDCAMERATYPE_TOPDOWN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBFMODEventDesc::DBFMODEventDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFMODEventDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &projectName );
	saver.Add( 3, &groupName );
	saver.Add( 4, &eventName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFMODEventDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "projectName", &projectName );
	saver.Add( "groupName", &groupName );
	saver.Add( "eventName", &eventName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMODEvent::FMODEvent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEvent::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEvent::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMODEventGroup::FMODEventGroup()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &groups );
	saver.Add( 4, &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "groups", &groups );
	saver.Add( "events", &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMODGroupInstance::FMODGroupInstance()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODGroupInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &project );
	saver.Add( 3, &fmodGroup );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODGroupInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "project", &project );
	saver.Add( "fmodGroup", &fmodGroup );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMODEventInstance::FMODEventInstance()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fmodGroup );
	saver.Add( 3, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "fmodGroup", &fmodGroup );
	saver.Add( "name", &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MusicDesc::MusicDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MusicDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cueName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MusicDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "cueName", &cueName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundAmbienceMap::SoundAmbienceMap() :
		radius( 30.0f )
	, directivity( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundAmbienceMap::operator&( IBinSaver &saver )
{
	saver.Add( 2, &texture );
	saver.Add( 3, &radius );
	saver.Add( 4, &directivity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundAmbienceMap::operator&( IXmlSaver &saver )
{
	saver.Add( "texture", &texture );
	saver.Add( "radius", &radius );
	saver.Add( "directivity", &directivity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundCamera::SoundCamera() :
		type( SOUNDCAMERATYPE_PERSPECTIVE )
	, multiplier( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundCamera::operator&( IBinSaver &saver )
{
	saver.Add( 2, &type );
	saver.Add( 3, &multiplier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundCamera::operator&( IXmlSaver &saver )
{
	saver.Add( "type", &type );
	saver.Add( "multiplier", &multiplier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundSceneGroupDesc::SoundSceneGroupDesc() :
		pitch( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSceneGroupDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &categoryName );
	saver.Add( 3, &pitch );
	saver.Add( 4, &volume );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSceneGroupDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "categoryName", &categoryName );
	saver.Add( "pitch", &pitch );
	saver.Add( "volume", &volume );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundSceneDesc::SoundSceneDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSceneDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundSceneGroups );
	saver.Add( 3, &cue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSceneDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "soundSceneGroups", &soundSceneGroups );
	saver.Add( "cue", &cue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMODEventProject::FMODEventProject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventProject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &groups );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FMODEventProject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FMODEventProject* parentPtr = (FMODEventProject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FMODEventProject::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "groups", &groups );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FMODEventProject::Assign( const FMODEventProject& _fMODEventProject )
{
	name = _fMODEventProject.name;
	groups = _fMODEventProject.groups;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound2D::Sound2D() :
		offset( 0.0f )
	, cycleCount( 1 )
	, volume( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sound2D::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundFile );
	saver.Add( 3, &offset );
	saver.Add( 4, &cycleCount );
	saver.Add( 5, &volume );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sound2D::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Sound2D* parentPtr = (Sound2D*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound2D::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "soundFile", &soundFile );
	saver.Add( "offset", &offset );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "volume", &volume );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound2D::Assign( const Sound2D& _sound2D )
{
	soundFile = _sound2D.soundFile;
	offset = _sound2D.offset;
	cycleCount = _sound2D.cycleCount;
	volume = _sound2D.volume;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundEnvironment::SoundEnvironment()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundEnvironment::operator&( IBinSaver &saver )
{
	saver.Add( 2, &language );
	saver.Add( 3, &soundCamera );
	saver.Add( 4, &fevFiles );
	saver.Add( 5, &banks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundEnvironment::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SoundEnvironment* parentPtr = (SoundEnvironment*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundEnvironment::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "language", &language );
	saver.Add( "soundCamera", &soundCamera );
	saver.Add( "fevFiles", &fevFiles );
	saver.Add( "banks", &banks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundEnvironment::Assign( const SoundEnvironment& _soundEnvironment )
{
	language = _soundEnvironment.language;
	soundCamera.type = _soundEnvironment.soundCamera.type;
	soundCamera.multiplier = _soundEnvironment.soundCamera.multiplier;
	fevFiles = _soundEnvironment.fevFiles;
	banks = _soundEnvironment.banks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundStream::SoundStream() :
		cycleCount( 0 )
	, volume( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundStream::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundFile );
	saver.Add( 3, &cycleCount );
	saver.Add( 4, &volume );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundStream::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SoundStream* parentPtr = (SoundStream*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundStream::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "soundFile", &soundFile );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "volume", &volume );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundStream::Assign( const SoundStream& _soundStream )
{
	soundFile = _soundStream.soundFile;
	cycleCount = _soundStream.cycleCount;
	volume = _soundStream.volume;
}
}; // namespace NDb
