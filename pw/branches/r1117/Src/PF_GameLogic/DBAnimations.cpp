// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBAnimations.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AnimSet );
REGISTER_DBRESOURCE( EmoteSettings );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnimStatePlayMode value )
{
	switch( value )
	{
		case ANIMSTATEPLAYMODE_PLAYNORMAL:
			return "PlayNormal";
		case ANIMSTATEPLAYMODE_PLAYUPPER:
			return "PlayUpper";
		case ANIMSTATEPLAYMODE_PLAYBOTH:
			return "PlayBoth";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnimStatePlayMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnimStatePlayMode StringToEnum_EAnimStatePlayMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnimStatePlayMode)(NStr::ToInt( value ));
	if ( strcmp( value, "PlayNormal" ) == 0 || strcmp( value, "ANIMSTATEPLAYMODE_PLAYNORMAL" ) == 0 )
		return ANIMSTATEPLAYMODE_PLAYNORMAL;
	if ( strcmp( value, "PlayUpper" ) == 0 || strcmp( value, "ANIMSTATEPLAYMODE_PLAYUPPER" ) == 0 )
		return ANIMSTATEPLAYMODE_PLAYUPPER;
	if ( strcmp( value, "PlayBoth" ) == 0 || strcmp( value, "ANIMSTATEPLAYMODE_PLAYBOTH" ) == 0 )
		return ANIMSTATEPLAYMODE_PLAYBOTH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnimStatePlayMode", value ) );
	return ANIMSTATEPLAYMODE_PLAYNORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnimStates value )
{
	switch( value )
	{
		case ANIMSTATES_INVALID:
			return "Invalid";
		case ANIMSTATES_IDLE:
			return "Idle";
		case ANIMSTATES_STUN:
			return "Stun";
		case ANIMSTATES_MOVE:
			return "Move";
		case ANIMSTATES_BLOCKEDMOVE:
			return "BlockedMove";
		case ANIMSTATES_ATTACK:
			return "Attack";
		case ANIMSTATES_ABILITY1:
			return "Ability1";
		case ANIMSTATES_ABILITY2:
			return "Ability2";
		case ANIMSTATES_ABILITY3:
			return "Ability3";
		case ANIMSTATES_ABILITY4:
			return "Ability4";
		case ANIMSTATES_DEATH:
			return "Death";
		case ANIMSTATES_RESURRECT:
			return "Resurrect";
		case ANIMSTATES_SUMMON:
			return "Summon";
		case ANIMSTATES_UNSUMMON:
			return "Unsummon";
		case ANIMSTATES_HELLO:
			return "Hello";
		case ANIMSTATES_HAPPY:
			return "Happy";
		case ANIMSTATES_SAD:
			return "Sad";
		case ANIMSTATES_MINIGAMING:
			return "Minigaming";
		case ANIMSTATES_SPECIAL1:
			return "Special1";
		case ANIMSTATES_SPECIAL2:
			return "Special2";
		case ANIMSTATES_SPECIAL3:
			return "Special3";
		case ANIMSTATES_SPECIAL4:
			return "Special4";
		case ANIMSTATES_HIDE:
			return "Hide";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnimStates", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnimStates StringToEnum_EAnimStates( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnimStates)(NStr::ToInt( value ));
	if ( strcmp( value, "Invalid" ) == 0 || strcmp( value, "ANIMSTATES_INVALID" ) == 0 )
		return ANIMSTATES_INVALID;
	if ( strcmp( value, "Idle" ) == 0 || strcmp( value, "ANIMSTATES_IDLE" ) == 0 )
		return ANIMSTATES_IDLE;
	if ( strcmp( value, "Stun" ) == 0 || strcmp( value, "ANIMSTATES_STUN" ) == 0 )
		return ANIMSTATES_STUN;
	if ( strcmp( value, "Move" ) == 0 || strcmp( value, "ANIMSTATES_MOVE" ) == 0 )
		return ANIMSTATES_MOVE;
	if ( strcmp( value, "BlockedMove" ) == 0 || strcmp( value, "ANIMSTATES_BLOCKEDMOVE" ) == 0 )
		return ANIMSTATES_BLOCKEDMOVE;
	if ( strcmp( value, "Attack" ) == 0 || strcmp( value, "ANIMSTATES_ATTACK" ) == 0 )
		return ANIMSTATES_ATTACK;
	if ( strcmp( value, "Ability1" ) == 0 || strcmp( value, "ANIMSTATES_ABILITY1" ) == 0 )
		return ANIMSTATES_ABILITY1;
	if ( strcmp( value, "Ability2" ) == 0 || strcmp( value, "ANIMSTATES_ABILITY2" ) == 0 )
		return ANIMSTATES_ABILITY2;
	if ( strcmp( value, "Ability3" ) == 0 || strcmp( value, "ANIMSTATES_ABILITY3" ) == 0 )
		return ANIMSTATES_ABILITY3;
	if ( strcmp( value, "Ability4" ) == 0 || strcmp( value, "ANIMSTATES_ABILITY4" ) == 0 )
		return ANIMSTATES_ABILITY4;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "ANIMSTATES_DEATH" ) == 0 )
		return ANIMSTATES_DEATH;
	if ( strcmp( value, "Resurrect" ) == 0 || strcmp( value, "ANIMSTATES_RESURRECT" ) == 0 )
		return ANIMSTATES_RESURRECT;
	if ( strcmp( value, "Summon" ) == 0 || strcmp( value, "ANIMSTATES_SUMMON" ) == 0 )
		return ANIMSTATES_SUMMON;
	if ( strcmp( value, "Unsummon" ) == 0 || strcmp( value, "ANIMSTATES_UNSUMMON" ) == 0 )
		return ANIMSTATES_UNSUMMON;
	if ( strcmp( value, "Hello" ) == 0 || strcmp( value, "ANIMSTATES_HELLO" ) == 0 )
		return ANIMSTATES_HELLO;
	if ( strcmp( value, "Happy" ) == 0 || strcmp( value, "ANIMSTATES_HAPPY" ) == 0 )
		return ANIMSTATES_HAPPY;
	if ( strcmp( value, "Sad" ) == 0 || strcmp( value, "ANIMSTATES_SAD" ) == 0 )
		return ANIMSTATES_SAD;
	if ( strcmp( value, "Minigaming" ) == 0 || strcmp( value, "ANIMSTATES_MINIGAMING" ) == 0 )
		return ANIMSTATES_MINIGAMING;
	if ( strcmp( value, "Special1" ) == 0 || strcmp( value, "ANIMSTATES_SPECIAL1" ) == 0 )
		return ANIMSTATES_SPECIAL1;
	if ( strcmp( value, "Special2" ) == 0 || strcmp( value, "ANIMSTATES_SPECIAL2" ) == 0 )
		return ANIMSTATES_SPECIAL2;
	if ( strcmp( value, "Special3" ) == 0 || strcmp( value, "ANIMSTATES_SPECIAL3" ) == 0 )
		return ANIMSTATES_SPECIAL3;
	if ( strcmp( value, "Special4" ) == 0 || strcmp( value, "ANIMSTATES_SPECIAL4" ) == 0 )
		return ANIMSTATES_SPECIAL4;
	if ( strcmp( value, "Hide" ) == 0 || strcmp( value, "ANIMSTATES_HIDE" ) == 0 )
		return ANIMSTATES_HIDE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnimStates", value ) );
	return ANIMSTATES_INVALID;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEmotePermission value )
{
	switch( value )
	{
		case EMOTEPERMISSION_PLAYNONE:
			return "PlayNone";
		case EMOTEPERMISSION_PLAYUPPER:
			return "PlayUpper";
		case EMOTEPERMISSION_PLAYLOWER:
			return "PlayLower";
		case EMOTEPERMISSION_PLAYBOTH:
			return "PlayBoth";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEmotePermission", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEmotePermission StringToEnum_EEmotePermission( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEmotePermission)(NStr::ToInt( value ));
	if ( strcmp( value, "PlayNone" ) == 0 || strcmp( value, "EMOTEPERMISSION_PLAYNONE" ) == 0 )
		return EMOTEPERMISSION_PLAYNONE;
	if ( strcmp( value, "PlayUpper" ) == 0 || strcmp( value, "EMOTEPERMISSION_PLAYUPPER" ) == 0 )
		return EMOTEPERMISSION_PLAYUPPER;
	if ( strcmp( value, "PlayLower" ) == 0 || strcmp( value, "EMOTEPERMISSION_PLAYLOWER" ) == 0 )
		return EMOTEPERMISSION_PLAYLOWER;
	if ( strcmp( value, "PlayBoth" ) == 0 || strcmp( value, "EMOTEPERMISSION_PLAYBOTH" ) == 0 )
		return EMOTEPERMISSION_PLAYBOTH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEmotePermission", value ) );
	return EMOTEPERMISSION_PLAYNONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEmotion value )
{
	switch( value )
	{
		case EMOTION_HAPPY:
			return "Happy";
		case EMOTION_SAD:
			return "Sad";
		case EMOTION_HELLO:
			return "Hello";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEmotion", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEmotion StringToEnum_EEmotion( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEmotion)(NStr::ToInt( value ));
	if ( strcmp( value, "Happy" ) == 0 || strcmp( value, "EMOTION_HAPPY" ) == 0 )
		return EMOTION_HAPPY;
	if ( strcmp( value, "Sad" ) == 0 || strcmp( value, "EMOTION_SAD" ) == 0 )
		return EMOTION_SAD;
	if ( strcmp( value, "Hello" ) == 0 || strcmp( value, "EMOTION_HELLO" ) == 0 )
		return EMOTION_HELLO;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEmotion", value ) );
	return EMOTION_HAPPY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimStateDataNew::AnimStateDataNew() :
		animState( ANIMSTATES_INVALID )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateDataNew::operator&( IBinSaver &saver )
{
	saver.Add( 2, &animState );
	saver.Add( 3, &node );
	saver.Add( 4, &marker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateDataNew::operator&( IXmlSaver &saver )
{
	saver.Add( "animState", &animState );
	saver.Add( "node", &node );
	saver.Add( "marker", &marker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimStateData::AnimStateData() :
		playMode( ANIMSTATEPLAYMODE_PLAYBOTH )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &commonNode );
	saver.Add( 3, &upperNode );
	saver.Add( 4, &playMode );
	saver.Add( 5, &commonMarker );
	saver.Add( 6, &upperMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateData::operator&( IXmlSaver &saver )
{
	saver.Add( "commonNode", &commonNode );
	saver.Add( "upperNode", &upperNode );
	saver.Add( "playMode", &playMode );
	saver.Add( "commonMarker", &commonMarker );
	saver.Add( "upperMarker", &upperMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimStateChanger::AnimStateChanger()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateChanger::operator&( IBinSaver &saver )
{
	saver.Add( 2, &oldAnimation );
	saver.Add( 3, &newAnimation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimStateChanger::operator&( IXmlSaver &saver )
{
	saver.Add( "oldAnimation", &oldAnimation );
	saver.Add( "newAnimation", &newAnimation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EmotePlayNodeParams::EmotePlayNodeParams()
{
	permissions.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EmotePlayNodeParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &permissions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EmotePlayNodeParams::operator&( IXmlSaver &saver )
{
	permissions.resize( 3 );
	saver.Add( "permissions", &permissions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimSet::AnimSet()
{
	states.resize( 23 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimSet::operator&( IBinSaver &saver )
{
	saver.Add( 2, &states );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimSet::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AnimSet* parentPtr = (AnimSet*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimSet::SerializeSelf( IXmlSaver &saver )
{
	states.resize( 23 );
	saver.Add( "states", &states );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimSet::Assign( const AnimSet& _animSet )
{
	states = _animSet.states;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EmoteSettings::EmoteSettings()
{
	nodes.resize( 23 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EmoteSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nodes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EmoteSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EmoteSettings* parentPtr = (EmoteSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EmoteSettings::SerializeSelf( IXmlSaver &saver )
{
	nodes.resize( 23 );
	saver.Add( "nodes", &nodes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EmoteSettings::Assign( const EmoteSettings& _emoteSettings )
{
	nodes = _emoteSettings.nodes;
}
}; // namespace NDb
