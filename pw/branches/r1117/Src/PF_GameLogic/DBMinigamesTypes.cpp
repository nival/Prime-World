// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBMinigamesTypes.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( MinigamePlaceParams );
REGISTER_DBRESOURCE( MinigameVisualStateChange );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ChangesApplyType value )
{
	switch( value )
	{
		case CHANGESAPPLYTYPE_DONOTAPPLY:
			return "DoNotApply";
		case CHANGESAPPLYTYPE_APPLYDEFAULT:
			return "ApplyDefault";
		case CHANGESAPPLYTYPE_APPLYABSOLUTEROTATION:
			return "ApplyAbsoluteRotation";
		case CHANGESAPPLYTYPE_APPLYABSOLUTEALL:
			return "ApplyAbsoluteAll";
		case CHANGESAPPLYTYPE_APPLYRELATIONAL:
			return "ApplyRelational";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ChangesApplyType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ChangesApplyType StringToEnum_ChangesApplyType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ChangesApplyType)(NStr::ToInt( value ));
	if ( strcmp( value, "DoNotApply" ) == 0 || strcmp( value, "CHANGESAPPLYTYPE_DONOTAPPLY" ) == 0 )
		return CHANGESAPPLYTYPE_DONOTAPPLY;
	if ( strcmp( value, "ApplyDefault" ) == 0 || strcmp( value, "CHANGESAPPLYTYPE_APPLYDEFAULT" ) == 0 )
		return CHANGESAPPLYTYPE_APPLYDEFAULT;
	if ( strcmp( value, "ApplyAbsoluteRotation" ) == 0 || strcmp( value, "CHANGESAPPLYTYPE_APPLYABSOLUTEROTATION" ) == 0 )
		return CHANGESAPPLYTYPE_APPLYABSOLUTEROTATION;
	if ( strcmp( value, "ApplyAbsoluteAll" ) == 0 || strcmp( value, "CHANGESAPPLYTYPE_APPLYABSOLUTEALL" ) == 0 )
		return CHANGESAPPLYTYPE_APPLYABSOLUTEALL;
	if ( strcmp( value, "ApplyRelational" ) == 0 || strcmp( value, "CHANGESAPPLYTYPE_APPLYRELATIONAL" ) == 0 )
		return CHANGESAPPLYTYPE_APPLYRELATIONAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ChangesApplyType", value ) );
	return CHANGESAPPLYTYPE_DONOTAPPLY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBidonType value )
{
	switch( value )
	{
		case BIDONTYPE_NONE:
			return "None";
		case BIDONTYPE_SPEEDCLOCK:
			return "Speedclock";
		case BIDONTYPE_SLOWDOWNGLUE:
			return "Slowdownglue";
		case BIDONTYPE_MAGICPOINTER:
			return "Magicpointer";
		case BIDONTYPE_PALETTE:
			return "Palette";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBidonType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBidonType StringToEnum_EBidonType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBidonType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "BIDONTYPE_NONE" ) == 0 )
		return BIDONTYPE_NONE;
	if ( strcmp( value, "Speedclock" ) == 0 || strcmp( value, "BIDONTYPE_SPEEDCLOCK" ) == 0 )
		return BIDONTYPE_SPEEDCLOCK;
	if ( strcmp( value, "Slowdownglue" ) == 0 || strcmp( value, "BIDONTYPE_SLOWDOWNGLUE" ) == 0 )
		return BIDONTYPE_SLOWDOWNGLUE;
	if ( strcmp( value, "Magicpointer" ) == 0 || strcmp( value, "BIDONTYPE_MAGICPOINTER" ) == 0 )
		return BIDONTYPE_MAGICPOINTER;
	if ( strcmp( value, "Palette" ) == 0 || strcmp( value, "BIDONTYPE_PALETTE" ) == 0 )
		return BIDONTYPE_PALETTE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBidonType", value ) );
	return BIDONTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MinigameClientType value )
{
	switch( value )
	{
		case MINIGAMECLIENTTYPE_LOCAL:
			return "Local";
		case MINIGAMECLIENTTYPE_REMOTE:
			return "Remote";
		case MINIGAMECLIENTTYPE_ANY:
			return "Any";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MinigameClientType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MinigameClientType StringToEnum_MinigameClientType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MinigameClientType)(NStr::ToInt( value ));
	if ( strcmp( value, "Local" ) == 0 || strcmp( value, "MINIGAMECLIENTTYPE_LOCAL" ) == 0 )
		return MINIGAMECLIENTTYPE_LOCAL;
	if ( strcmp( value, "Remote" ) == 0 || strcmp( value, "MINIGAMECLIENTTYPE_REMOTE" ) == 0 )
		return MINIGAMECLIENTTYPE_REMOTE;
	if ( strcmp( value, "Any" ) == 0 || strcmp( value, "MINIGAMECLIENTTYPE_ANY" ) == 0 )
		return MINIGAMECLIENTTYPE_ANY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MinigameClientType", value ) );
	return MINIGAMECLIENTTYPE_LOCAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MinigameVisualState value )
{
	switch( value )
	{
		case MINIGAMEVISUALSTATE_NONE:
			return "None";
		case MINIGAMEVISUALSTATE_SESSION:
			return "Session";
		case MINIGAMEVISUALSTATE_CLINIC_LOBBY:
			return "Clinic_Lobby";
		case MINIGAMEVISUALSTATE_CLINIC_INGAME:
			return "Clinic_InGame";
		case MINIGAMEVISUALSTATE_CLINIC_SHOP:
			return "Clinic_Shop";
		case MINIGAMEVISUALSTATE_EASEL_LOBBY:
			return "Easel_Lobby";
		case MINIGAMEVISUALSTATE_EASEL_LEAVINGLOBBY:
			return "Easel_LeavingLobby";
		case MINIGAMEVISUALSTATE_EASEL_INGAME:
			return "Easel_InGame";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MinigameVisualState", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MinigameVisualState StringToEnum_MinigameVisualState( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MinigameVisualState)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_NONE" ) == 0 )
		return MINIGAMEVISUALSTATE_NONE;
	if ( strcmp( value, "Session" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_SESSION" ) == 0 )
		return MINIGAMEVISUALSTATE_SESSION;
	if ( strcmp( value, "Clinic_Lobby" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_CLINIC_LOBBY" ) == 0 )
		return MINIGAMEVISUALSTATE_CLINIC_LOBBY;
	if ( strcmp( value, "Clinic_InGame" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_CLINIC_INGAME" ) == 0 )
		return MINIGAMEVISUALSTATE_CLINIC_INGAME;
	if ( strcmp( value, "Clinic_Shop" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_CLINIC_SHOP" ) == 0 )
		return MINIGAMEVISUALSTATE_CLINIC_SHOP;
	if ( strcmp( value, "Easel_Lobby" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_EASEL_LOBBY" ) == 0 )
		return MINIGAMEVISUALSTATE_EASEL_LOBBY;
	if ( strcmp( value, "Easel_LeavingLobby" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_EASEL_LEAVINGLOBBY" ) == 0 )
		return MINIGAMEVISUALSTATE_EASEL_LEAVINGLOBBY;
	if ( strcmp( value, "Easel_InGame" ) == 0 || strcmp( value, "MINIGAMEVISUALSTATE_EASEL_INGAME" ) == 0 )
		return MINIGAMEVISUALSTATE_EASEL_INGAME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MinigameVisualState", value ) );
	return MINIGAMEVISUALSTATE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigamePlaceParams::MinigamePlaceParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamePlaceParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stateChanges );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamePlaceParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinigamePlaceParams* parentPtr = (MinigamePlaceParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePlaceParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "stateChanges", &stateChanges );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePlaceParams::Assign( const MinigamePlaceParams& _minigamePlaceParams )
{
	stateChanges = _minigamePlaceParams.stateChanges;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameVisualStateChange::MinigameVisualStateChange() :
		fromState( MINIGAMEVISUALSTATE_NONE )
	, toState( MINIGAMEVISUALSTATE_NONE )
	, clientType( MINIGAMECLIENTTYPE_ANY )
	, changePlacement( CHANGESAPPLYTYPE_DONOTAPPLY )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigameVisualStateChange::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fromState );
	saver.Add( 3, &toState );
	saver.Add( 4, &clientType );
	saver.Add( 5, &newPlacement );
	saver.Add( 6, &changePlacement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigameVisualStateChange::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinigameVisualStateChange* parentPtr = (MinigameVisualStateChange*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameVisualStateChange::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "fromState", &fromState );
	saver.Add( "toState", &toState );
	saver.Add( "clientType", &clientType );
	saver.Add( "newPlacement", &newPlacement );
	saver.Add( "changePlacement", &changePlacement );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameVisualStateChange::Assign( const MinigameVisualStateChange& _minigameVisualStateChange )
{
	fromState = _minigameVisualStateChange.fromState;
	toState = _minigameVisualStateChange.toState;
	clientType = _minigameVisualStateChange.clientType;
	newPlacement.pos = _minigameVisualStateChange.newPlacement.pos;
	newPlacement.rot = _minigameVisualStateChange.newPlacement.rot;
	newPlacement.scale = _minigameVisualStateChange.newPlacement.scale;
	changePlacement = _minigameVisualStateChange.changePlacement;
}
}; // namespace NDb
