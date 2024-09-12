// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "../Render/DBRender.h"
#include "../Scene/DBSceneBase.h"
#include "DBScene.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AnimatedPlacementResource );
REGISTER_DBRESOURCE( SCEvent );
BASIC_REGISTER_DBRESOURCE( DBSceneResource );
REGISTER_DBRESOURCE( DBAnimKey );
REGISTER_DBRESOURCE( DBAttachAnimKey );
REGISTER_DBRESOURCE( DBSceneComponentBase );
REGISTER_DBRESOURCE( DBSceneComponent );
REGISTER_DBRESOURCE( DBAnimatedSceneComponent );
REGISTER_DBRESOURCE( DBLightningSceneComponent );
REGISTER_DBRESOURCE( DBSceneObject );
REGISTER_DBRESOURCE( DBParticleSceneComponent );
REGISTER_DBRESOURCE( DBSoundSceneComponent );
REGISTER_DBRESOURCE( DBStaticSceneComponent );
REGISTER_DBRESOURCE( DBTraceSceneComponent );
REGISTER_DBRESOURCE( DBWaterInfo );
REGISTER_DBRESOURCE( DBWaterSceneComponent );
REGISTER_DBRESOURCE( EnableDisableSCEvents );
REGISTER_DBRESOURCE( EnableDisableSkinEvents );
REGISTER_DBRESOURCE( GroundHitSCEvent );
REGISTER_DBRESOURCE( LocatorList );
REGISTER_DBRESOURCE( NamedSCEvent );
REGISTER_DBRESOURCE( SceneObjectTrack );
REGISTER_DBRESOURCE( SceneObjectTracks );
REGISTER_DBRESOURCE( AnimationSCEvent );
REGISTER_DBRESOURCE( TimeController );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef VISUAL_CUTTED
#include "AnimatedSceneComponent.h"
#include "LightningSceneComponent.h"
#include "ParticleSceneComponent.h"
#include "SceneComponent.h"
#include "SceneObjectCreation.h"
#include "SoundSceneComponent.h"
#include "TraceSceneComponent.h"
#include "WaterSceneComponent.h"
#endif // #ifndef VISUAL_CUTTED

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnimEventType value )
{
	switch( value )
	{
		case ANIMEVENTTYPE_NODEENTER:
			return "NodeEnter";
		case ANIMEVENTTYPE_NODELEAVE:
			return "NodeLeave";
		case ANIMEVENTTYPE_NODEPARAM:
			return "NodeParam";
		case ANIMEVENTTYPE_MARKER:
			return "Marker";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnimEventType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnimEventType StringToEnum_EAnimEventType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnimEventType)(NStr::ToInt( value ));
	if ( strcmp( value, "NodeEnter" ) == 0 || strcmp( value, "ANIMEVENTTYPE_NODEENTER" ) == 0 )
		return ANIMEVENTTYPE_NODEENTER;
	if ( strcmp( value, "NodeLeave" ) == 0 || strcmp( value, "ANIMEVENTTYPE_NODELEAVE" ) == 0 )
		return ANIMEVENTTYPE_NODELEAVE;
	if ( strcmp( value, "NodeParam" ) == 0 || strcmp( value, "ANIMEVENTTYPE_NODEPARAM" ) == 0 )
		return ANIMEVENTTYPE_NODEPARAM;
	if ( strcmp( value, "Marker" ) == 0 || strcmp( value, "ANIMEVENTTYPE_MARKER" ) == 0 )
		return ANIMEVENTTYPE_MARKER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnimEventType", value ) );
	return ANIMEVENTTYPE_NODEENTER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAttachFlags value )
{
	switch( value )
	{
		case ATTACHFLAGS_NONE:
			return "None";
		case ATTACHFLAGS_USEPARENTSCALE:
			return "UseParentScale";
		case ATTACHFLAGS_USEPARENTROTATION:
			return "UseParentRotation";
		case ATTACHFLAGS_USEPARENTTIME:
			return "UseParentTime";
		case ATTACHFLAGS_USEAGSPEEDCOEFF:
			return "UseAGSpeedCoeff";
		case ATTACHFLAGS_STAYINWORLD:
			return "StayInWorld";
		case ATTACHFLAGS_CANCELOFFSETSCALING:
			return "CancelOffsetScaling";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAttachFlags StringToEnum_EAttachFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAttachFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ATTACHFLAGS_NONE" ) == 0 )
		return ATTACHFLAGS_NONE;
	if ( strcmp( value, "UseParentScale" ) == 0 || strcmp( value, "ATTACHFLAGS_USEPARENTSCALE" ) == 0 )
		return ATTACHFLAGS_USEPARENTSCALE;
	if ( strcmp( value, "UseParentRotation" ) == 0 || strcmp( value, "ATTACHFLAGS_USEPARENTROTATION" ) == 0 )
		return ATTACHFLAGS_USEPARENTROTATION;
	if ( strcmp( value, "UseParentTime" ) == 0 || strcmp( value, "ATTACHFLAGS_USEPARENTTIME" ) == 0 )
		return ATTACHFLAGS_USEPARENTTIME;
	if ( strcmp( value, "UseAGSpeedCoeff" ) == 0 || strcmp( value, "ATTACHFLAGS_USEAGSPEEDCOEFF" ) == 0 )
		return ATTACHFLAGS_USEAGSPEEDCOEFF;
	if ( strcmp( value, "StayInWorld" ) == 0 || strcmp( value, "ATTACHFLAGS_STAYINWORLD" ) == 0 )
		return ATTACHFLAGS_STAYINWORLD;
	if ( strcmp( value, "CancelOffsetScaling" ) == 0 || strcmp( value, "ATTACHFLAGS_CANCELOFFSETSCALING" ) == 0 )
		return ATTACHFLAGS_CANCELOFFSETSCALING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAttachFlags", value ) );
	return ATTACHFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEnableDisableOrder value )
{
	switch( value )
	{
		case ENABLEDISABLEORDER_ENABLETHENDISABLE:
			return "EnableThenDisable";
		case ENABLEDISABLEORDER_DISABLETHENENABLE:
			return "DisableThenEnable";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEnableDisableOrder", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEnableDisableOrder StringToEnum_EEnableDisableOrder( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEnableDisableOrder)(NStr::ToInt( value ));
	if ( strcmp( value, "EnableThenDisable" ) == 0 || strcmp( value, "ENABLEDISABLEORDER_ENABLETHENDISABLE" ) == 0 )
		return ENABLEDISABLEORDER_ENABLETHENDISABLE;
	if ( strcmp( value, "DisableThenEnable" ) == 0 || strcmp( value, "ENABLEDISABLEORDER_DISABLETHENENABLE" ) == 0 )
		return ENABLEDISABLEORDER_DISABLETHENENABLE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEnableDisableOrder", value ) );
	return ENABLEDISABLEORDER_ENABLETHENDISABLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGroupFlags value )
{
	switch( value )
	{
		case GROUPFLAGS_NONE:
			return "None";
		case GROUPFLAGS_RECOLORABLE:
			return "Recolorable";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGroupFlags StringToEnum_EGroupFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGroupFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "GROUPFLAGS_NONE" ) == 0 )
		return GROUPFLAGS_NONE;
	if ( strcmp( value, "Recolorable" ) == 0 || strcmp( value, "GROUPFLAGS_RECOLORABLE" ) == 0 )
		return GROUPFLAGS_RECOLORABLE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGroupFlags", value ) );
	return GROUPFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ELightningAnimType value )
{
	switch( value )
	{
		case LIGHTNINGANIMTYPE_NONE:
			return "None";
		case LIGHTNINGANIMTYPE_SEQUENTIAL:
			return "Sequential";
		case LIGHTNINGANIMTYPE_RANDOMIZED:
			return "Randomized";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ELightningAnimType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ELightningAnimType StringToEnum_ELightningAnimType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ELightningAnimType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "LIGHTNINGANIMTYPE_NONE" ) == 0 )
		return LIGHTNINGANIMTYPE_NONE;
	if ( strcmp( value, "Sequential" ) == 0 || strcmp( value, "LIGHTNINGANIMTYPE_SEQUENTIAL" ) == 0 )
		return LIGHTNINGANIMTYPE_SEQUENTIAL;
	if ( strcmp( value, "Randomized" ) == 0 || strcmp( value, "LIGHTNINGANIMTYPE_RANDOMIZED" ) == 0 )
		return LIGHTNINGANIMTYPE_RANDOMIZED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ELightningAnimType", value ) );
	return LIGHTNINGANIMTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EOrientType value )
{
	switch( value )
	{
		case ORIENTTYPE_NONE:
			return "None";
		case ORIENTTYPE_AXIS:
			return "Axis";
		case ORIENTTYPE_SPEED:
			return "Speed";
		case ORIENTTYPE_PLANE:
			return "Plane";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EOrientType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EOrientType StringToEnum_EOrientType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EOrientType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ORIENTTYPE_NONE" ) == 0 )
		return ORIENTTYPE_NONE;
	if ( strcmp( value, "Axis" ) == 0 || strcmp( value, "ORIENTTYPE_AXIS" ) == 0 )
		return ORIENTTYPE_AXIS;
	if ( strcmp( value, "Speed" ) == 0 || strcmp( value, "ORIENTTYPE_SPEED" ) == 0 )
		return ORIENTTYPE_SPEED;
	if ( strcmp( value, "Plane" ) == 0 || strcmp( value, "ORIENTTYPE_PLANE" ) == 0 )
		return ORIENTTYPE_PLANE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EOrientType", value ) );
	return ORIENTTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESCOrientation value )
{
	switch( value )
	{
		case SCORIENTATION_DEFAULT:
			return "Default";
		case SCORIENTATION_CAMERA:
			return "Camera";
		case SCORIENTATION_CAMERAFIXEDZ:
			return "CameraFixedZ";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESCOrientation", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESCOrientation StringToEnum_ESCOrientation( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESCOrientation)(NStr::ToInt( value ));
	if ( strcmp( value, "Default" ) == 0 || strcmp( value, "SCORIENTATION_DEFAULT" ) == 0 )
		return SCORIENTATION_DEFAULT;
	if ( strcmp( value, "Camera" ) == 0 || strcmp( value, "SCORIENTATION_CAMERA" ) == 0 )
		return SCORIENTATION_CAMERA;
	if ( strcmp( value, "CameraFixedZ" ) == 0 || strcmp( value, "SCORIENTATION_CAMERAFIXEDZ" ) == 0 )
		return SCORIENTATION_CAMERAFIXEDZ;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESCOrientation", value ) );
	return SCORIENTATION_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStandAloneEffectFlags value )
{
	switch( value )
	{
		case STANDALONEEFFECTFLAGS_NONE:
			return "None";
		case STANDALONEEFFECTFLAGS_USEPARENTSCALE:
			return "UseParentScale";
		case STANDALONEEFFECTFLAGS_USEPARENTROTATION:
			return "UseParentRotation";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStandAloneEffectFlags StringToEnum_EStandAloneEffectFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStandAloneEffectFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "STANDALONEEFFECTFLAGS_NONE" ) == 0 )
		return STANDALONEEFFECTFLAGS_NONE;
	if ( strcmp( value, "UseParentScale" ) == 0 || strcmp( value, "STANDALONEEFFECTFLAGS_USEPARENTSCALE" ) == 0 )
		return STANDALONEEFFECTFLAGS_USEPARENTSCALE;
	if ( strcmp( value, "UseParentRotation" ) == 0 || strcmp( value, "STANDALONEEFFECTFLAGS_USEPARENTROTATION" ) == 0 )
		return STANDALONEEFFECTFLAGS_USEPARENTROTATION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStandAloneEffectFlags", value ) );
	return STANDALONEEFFECTFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const Sound3DSimultType value )
{
	switch( value )
	{
		case SOUND3DSIMULTTYPE_MELEE:
			return "Melee";
		case SOUND3DSIMULTTYPE_RANGE:
			return "Range";
		case SOUND3DSIMULTTYPE_CREEPDEATH:
			return "CreepDeath";
		case SOUND3DSIMULTTYPE_INFINITE:
			return "Infinite";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum Sound3DSimultType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Sound3DSimultType StringToEnum_Sound3DSimultType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (Sound3DSimultType)(NStr::ToInt( value ));
	if ( strcmp( value, "Melee" ) == 0 || strcmp( value, "SOUND3DSIMULTTYPE_MELEE" ) == 0 )
		return SOUND3DSIMULTTYPE_MELEE;
	if ( strcmp( value, "Range" ) == 0 || strcmp( value, "SOUND3DSIMULTTYPE_RANGE" ) == 0 )
		return SOUND3DSIMULTTYPE_RANGE;
	if ( strcmp( value, "CreepDeath" ) == 0 || strcmp( value, "SOUND3DSIMULTTYPE_CREEPDEATH" ) == 0 )
		return SOUND3DSIMULTTYPE_CREEPDEATH;
	if ( strcmp( value, "Infinite" ) == 0 || strcmp( value, "SOUND3DSIMULTTYPE_INFINITE" ) == 0 )
		return SOUND3DSIMULTTYPE_INFINITE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum Sound3DSimultType", value ) );
	return SOUND3DSIMULTTYPE_MELEE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimatedPlacement::AnimatedPlacement()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimatedPlacement::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pos );
	saver.Add( 3, &rot );
	saver.Add( 4, &scale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimatedPlacement::operator&( IXmlSaver &saver )
{
	saver.Add( "pos", &pos );
	saver.Add( "rot", &rot );
	saver.Add( "scale", &scale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttachedSceneComponent::AttachedSceneComponent() :
		attachFlags( EAttachFlags( ATTACHFLAGS_USEAGSPEEDCOEFF | ATTACHFLAGS_USEPARENTTIME | ATTACHFLAGS_USEPARENTROTATION | ATTACHFLAGS_USEPARENTSCALE ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttachedSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 2, &component );
	saver.Add( 3, &locatorName );
	saver.Add( 4, &timeController );
	saver.Add( 5, &placement );
	saver.Add( 6, &attachFlags );
	saver.Add( 7, &id );
	saver.Add( 8, &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttachedSceneComponent::operator&( IXmlSaver &saver )
{
	saver.Add( "component", &component );
	saver.Add( "locatorName", &locatorName );
	saver.Add( "timeController", &timeController );
	saver.Add( "placement", &placement );
	saver.Add( "attachFlags", &attachFlags );
	saver.Add( "id", &id );
	saver.Add( "events", &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLightningFXParams::DBLightningFXParams() :
		animAtlasSize( 1 )
	, animFirstFrame( 0 )
	, animLastFrame( 0 )
	, animSpeed( 0.0f )
	, animType( LIGHTNINGANIMTYPE_NONE )
	, opacityDistance1( 0.0f )
	, opacityDistance2( 0.0f )
	, radius( 0.25f )
	, scrollSpeed( 0.0f )
	, tiling( 5.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLightningFXParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &animAtlasSize );
	saver.Add( 3, &animFirstFrame );
	saver.Add( 4, &animLastFrame );
	saver.Add( 5, &animSpeed );
	saver.Add( 6, &animType );
	saver.Add( 7, &opacityDistance1 );
	saver.Add( 8, &opacityDistance2 );
	saver.Add( 9, &color );
	saver.Add( 10, &radius );
	saver.Add( 11, &scrollSpeed );
	saver.Add( 12, &tiling );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLightningFXParams::operator&( IXmlSaver &saver )
{
	saver.Add( "animAtlasSize", &animAtlasSize );
	saver.Add( "animFirstFrame", &animFirstFrame );
	saver.Add( "animLastFrame", &animLastFrame );
	saver.Add( "animSpeed", &animSpeed );
	saver.Add( "animType", &animType );
	saver.Add( "opacityDistance1", &opacityDistance1 );
	saver.Add( "opacityDistance2", &opacityDistance2 );
	saver.Add( "color", &color );
	saver.Add( "radius", &radius );
	saver.Add( "scrollSpeed", &scrollSpeed );
	saver.Add( "tiling", &tiling );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkinPart::SkinPart()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinPart::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SkinPartBase*)this );
	saver.Add( 2, &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinPart::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (SkinPartBase*)this );
	saver.Add( "events", &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimatedPlacementResource::AnimatedPlacementResource()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimatedPlacementResource::operator&( IBinSaver &saver )
{
	saver.Add( 2, &placement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimatedPlacementResource::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AnimatedPlacementResource* parentPtr = (AnimatedPlacementResource*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedPlacementResource::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "placement", &placement );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedPlacementResource::Assign( const AnimatedPlacementResource& _animatedPlacementResource )
{
	placement.pos = _animatedPlacementResource.placement.pos;
	placement.rot = _animatedPlacementResource.placement.rot;
	placement.scale = _animatedPlacementResource.placement.scale;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SCEvent::SCEvent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SCEvent::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SCEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SCEvent* parentPtr = (SCEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SCEvent::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SCEvent::Assign( const SCEvent& _sCEvent )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSceneResource::DBSceneResource()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneResource::operator&( IBinSaver &saver )
{
	saver.Add( 2, &attached );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneResource::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBSceneResource* parentPtr = (DBSceneResource*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneResource::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "attached", &attached );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneResource::Assign( const DBSceneResource& _dBSceneResource )
{
	attached = _dBSceneResource.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBAnimKey::DBAnimKey()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAnimKey::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAnimKey::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBAnimKey* parentPtr = (DBAnimKey*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAnimKey::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAnimKey::Assign( const DBAnimKey& _dBAnimKey )
{
	name = _dBAnimKey.name;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBAttachAnimKey::DBAttachAnimKey()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAttachAnimKey::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBAnimKey*)this );
	saver.Add( 2, &component );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAttachAnimKey::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBAttachAnimKey* parentPtr = (DBAttachAnimKey*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAttachAnimKey::SerializeSelf( IXmlSaver &saver )
{
	DBAnimKey::SerializeSelf( saver );
	saver.Add( "component", &component );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAttachAnimKey::Assign( const DBAttachAnimKey& _dBAttachAnimKey )
{
	component = _dBAttachAnimKey.component;
	name = _dBAttachAnimKey.name;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSceneComponentBase::DBSceneComponentBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneComponentBase::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneResource*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneComponentBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBSceneComponentBase* parentPtr = (DBSceneComponentBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneComponentBase::SerializeSelf( IXmlSaver &saver )
{
	DBSceneResource::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneComponentBase::Assign( const DBSceneComponentBase& _dBSceneComponentBase )
{
	attached = _dBSceneComponentBase.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBSceneComponentBase::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return ( CObj<NScene::SceneComponent> )(0);
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSceneComponent::DBSceneComponent() :
		orientation( SCORIENTATION_DEFAULT )
	, groupFlags( GROUPFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponentBase*)this );
	saver.Add( 2, &locatorList );
	saver.Add( 3, &orientation );
	saver.Add( 4, &groupFlags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBSceneComponent* parentPtr = (DBSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponentBase::SerializeSelf( saver );
	saver.Add( "locatorList", &locatorList );
	saver.Add( "orientation", &orientation );
	saver.Add( "groupFlags", &groupFlags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneComponent::Assign( const DBSceneComponent& _dBSceneComponent )
{
	locatorList = _dBSceneComponent.locatorList;
	orientation = _dBSceneComponent.orientation;
	groupFlags = _dBSceneComponent.groupFlags;
	attached = _dBSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::SceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBAnimatedSceneComponent::DBAnimatedSceneComponent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAnimatedSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &additionalGraph );
	saver.Add( 3, &splitBoneName );
	saver.Add( 4, &srcFileName );
	saver.Add( 5, &skeletonFileName );
	saver.Add( 6, &skins );
	saver.Add( 7, &animations );
	saver.Add( 8, &faceFXAnims );
	saver.Add( 9, &animGraph );
	saver.Add( 10, &aabb );
	saver.Add( 11, &anims );
	saver.Add( 12, &skinOn );
	saver.Add( 13, &keys );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAnimatedSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBAnimatedSceneComponent* parentPtr = (DBAnimatedSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAnimatedSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "additionalGraph", &additionalGraph );
	saver.Add( "splitBoneName", &splitBoneName );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "skeletonFileName", &skeletonFileName );
	saver.Add( "skins", &skins );
	saver.Add( "animations", &animations );
	saver.Add( "faceFXAnims", &faceFXAnims );
	saver.Add( "animGraph", &animGraph );
	saver.Add( "aabb", &aabb );
	saver.Add( "anims", &anims );
	saver.Add( "skinOn", &skinOn );
	saver.Add( "keys", &keys );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBAnimatedSceneComponent::Assign( const DBAnimatedSceneComponent& _dBAnimatedSceneComponent )
{
	additionalGraph = _dBAnimatedSceneComponent.additionalGraph;
	splitBoneName = _dBAnimatedSceneComponent.splitBoneName;
	srcFileName = _dBAnimatedSceneComponent.srcFileName;
	skeletonFileName = _dBAnimatedSceneComponent.skeletonFileName;
	skins = _dBAnimatedSceneComponent.skins;
	animations = _dBAnimatedSceneComponent.animations;
	faceFXAnims = _dBAnimatedSceneComponent.faceFXAnims;
	animGraph = _dBAnimatedSceneComponent.animGraph;
	aabb.minX = _dBAnimatedSceneComponent.aabb.minX;
	aabb.maxX = _dBAnimatedSceneComponent.aabb.maxX;
	aabb.minY = _dBAnimatedSceneComponent.aabb.minY;
	aabb.maxY = _dBAnimatedSceneComponent.aabb.maxY;
	aabb.minZ = _dBAnimatedSceneComponent.aabb.minZ;
	aabb.maxZ = _dBAnimatedSceneComponent.aabb.maxZ;
	anims = _dBAnimatedSceneComponent.anims;
	skinOn = _dBAnimatedSceneComponent.skinOn;
	keys = _dBAnimatedSceneComponent.keys;
	locatorList = _dBAnimatedSceneComponent.locatorList;
	orientation = _dBAnimatedSceneComponent.orientation;
	groupFlags = _dBAnimatedSceneComponent.groupFlags;
	attached = _dBAnimatedSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBAnimatedSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateAnimatedSceneComponent( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLightningSceneComponent::DBLightningSceneComponent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLightningSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &material );
	saver.Add( 3, &fromLocator );
	saver.Add( 4, &toLocator );
	saver.Add( 5, &fxParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLightningSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBLightningSceneComponent* parentPtr = (DBLightningSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLightningSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "material", &material );
	saver.Add( "fromLocator", &fromLocator );
	saver.Add( "toLocator", &toLocator );
	saver.Add( "fxParams", &fxParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLightningSceneComponent::Assign( const DBLightningSceneComponent& _dBLightningSceneComponent )
{
	material = _dBLightningSceneComponent.material;
	fromLocator = _dBLightningSceneComponent.fromLocator;
	toLocator = _dBLightningSceneComponent.toLocator;
	fxParams.animAtlasSize = _dBLightningSceneComponent.fxParams.animAtlasSize;
	fxParams.animFirstFrame = _dBLightningSceneComponent.fxParams.animFirstFrame;
	fxParams.animLastFrame = _dBLightningSceneComponent.fxParams.animLastFrame;
	fxParams.animSpeed = _dBLightningSceneComponent.fxParams.animSpeed;
	fxParams.animType = _dBLightningSceneComponent.fxParams.animType;
	fxParams.opacityDistance1 = _dBLightningSceneComponent.fxParams.opacityDistance1;
	fxParams.opacityDistance2 = _dBLightningSceneComponent.fxParams.opacityDistance2;
	fxParams.color = _dBLightningSceneComponent.fxParams.color;
	fxParams.radius = _dBLightningSceneComponent.fxParams.radius;
	fxParams.scrollSpeed = _dBLightningSceneComponent.fxParams.scrollSpeed;
	fxParams.tiling = _dBLightningSceneComponent.fxParams.tiling;
	locatorList = _dBLightningSceneComponent.locatorList;
	orientation = _dBLightningSceneComponent.orientation;
	groupFlags = _dBLightningSceneComponent.groupFlags;
	attached = _dBLightningSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBLightningSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::LightningSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSceneObject::DBSceneObject() :
		ignoreAttachesToNonDefaultLocators( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneObject::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneResource*)this );
	saver.Add( 2, &tracksList );
	saver.Add( 3, &collisionGeometry );
	saver.Add( 4, &ignoreAttachesToNonDefaultLocators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSceneObject::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBSceneObject* parentPtr = (DBSceneObject*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneObject::SerializeSelf( IXmlSaver &saver )
{
	DBSceneResource::SerializeSelf( saver );
	saver.Add( "tracksList", &tracksList );
	saver.Add( "collisionGeometry", &collisionGeometry );
	saver.Add( "ignoreAttachesToNonDefaultLocators", &ignoreAttachesToNonDefaultLocators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSceneObject::Assign( const DBSceneObject& _dBSceneObject )
{
	tracksList = _dBSceneObject.tracksList;
	collisionGeometry = _dBSceneObject.collisionGeometry;
	ignoreAttachesToNonDefaultLocators = _dBSceneObject.ignoreAttachesToNonDefaultLocators;
	attached = _dBSceneObject.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBParticleSceneComponent::DBParticleSceneComponent() :
		camoffset( 0.0f )
	, orient( ORIENTTYPE_NONE )
	, leaveParticlesWhereStarted( false )
	, deathFadeOutTime( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBParticleSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &camoffset );
	saver.Add( 3, &orient );
	saver.Add( 4, &pivot );
	saver.Add( 5, &leaveParticlesWhereStarted );
	saver.Add( 6, &deathFadeOutTime );
	saver.Add( 7, &material );
	saver.Add( 8, &uvPairs );
	saver.Add( 9, &aabb );
	saver.Add( 10, &fxFileName );
	saver.Add( 11, &srcFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBParticleSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBParticleSceneComponent* parentPtr = (DBParticleSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBParticleSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "camoffset", &camoffset );
	saver.Add( "orient", &orient );
	saver.Add( "pivot", &pivot );
	saver.Add( "leaveParticlesWhereStarted", &leaveParticlesWhereStarted );
	saver.Add( "deathFadeOutTime", &deathFadeOutTime );
	saver.Add( "material", &material );
	saver.Add( "uvPairs", &uvPairs );
	saver.Add( "aabb", &aabb );
	saver.Add( "fxFileName", &fxFileName );
	saver.Add( "srcFileName", &srcFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBParticleSceneComponent::Assign( const DBParticleSceneComponent& _dBParticleSceneComponent )
{
	camoffset = _dBParticleSceneComponent.camoffset;
	orient = _dBParticleSceneComponent.orient;
	pivot = _dBParticleSceneComponent.pivot;
	leaveParticlesWhereStarted = _dBParticleSceneComponent.leaveParticlesWhereStarted;
	deathFadeOutTime = _dBParticleSceneComponent.deathFadeOutTime;
	material = _dBParticleSceneComponent.material;
	uvPairs = _dBParticleSceneComponent.uvPairs;
	aabb.minX = _dBParticleSceneComponent.aabb.minX;
	aabb.maxX = _dBParticleSceneComponent.aabb.maxX;
	aabb.minY = _dBParticleSceneComponent.aabb.minY;
	aabb.maxY = _dBParticleSceneComponent.aabb.maxY;
	aabb.minZ = _dBParticleSceneComponent.aabb.minZ;
	aabb.maxZ = _dBParticleSceneComponent.aabb.maxZ;
	fxFileName = _dBParticleSceneComponent.fxFileName;
	srcFileName = _dBParticleSceneComponent.srcFileName;
	locatorList = _dBParticleSceneComponent.locatorList;
	orientation = _dBParticleSceneComponent.orientation;
	groupFlags = _dBParticleSceneComponent.groupFlags;
	attached = _dBParticleSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBParticleSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::ParticleSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSoundSceneComponent::DBSoundSceneComponent() :
		timeInterval( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSoundSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &desc );
	saver.Add( 3, &timeInterval );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSoundSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBSoundSceneComponent* parentPtr = (DBSoundSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSoundSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "desc", &desc );
	saver.Add( "timeInterval", &timeInterval );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBSoundSceneComponent::Assign( const DBSoundSceneComponent& _dBSoundSceneComponent )
{
	desc.projectName = _dBSoundSceneComponent.desc.projectName;
	desc.groupName = _dBSoundSceneComponent.desc.groupName;
	desc.eventName = _dBSoundSceneComponent.desc.eventName;
	timeInterval = _dBSoundSceneComponent.timeInterval;
	locatorList = _dBSoundSceneComponent.locatorList;
	orientation = _dBSoundSceneComponent.orientation;
	groupFlags = _dBSoundSceneComponent.groupFlags;
	attached = _dBSoundSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBSoundSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::SoundSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBStaticSceneComponent::DBStaticSceneComponent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBStaticSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &geometryFileName );
	saver.Add( 4, &aabb );
	saver.Add( 5, &materialsReferences );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBStaticSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBStaticSceneComponent* parentPtr = (DBStaticSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBStaticSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "geometryFileName", &geometryFileName );
	saver.Add( "aabb", &aabb );
	saver.Add( "materialsReferences", &materialsReferences );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBStaticSceneComponent::Assign( const DBStaticSceneComponent& _dBStaticSceneComponent )
{
	srcFileName = _dBStaticSceneComponent.srcFileName;
	geometryFileName = _dBStaticSceneComponent.geometryFileName;
	aabb.minX = _dBStaticSceneComponent.aabb.minX;
	aabb.maxX = _dBStaticSceneComponent.aabb.maxX;
	aabb.minY = _dBStaticSceneComponent.aabb.minY;
	aabb.maxY = _dBStaticSceneComponent.aabb.maxY;
	aabb.minZ = _dBStaticSceneComponent.aabb.minZ;
	aabb.maxZ = _dBStaticSceneComponent.aabb.maxZ;
	materialsReferences = _dBStaticSceneComponent.materialsReferences;
	locatorList = _dBStaticSceneComponent.locatorList;
	orientation = _dBStaticSceneComponent.orientation;
	groupFlags = _dBStaticSceneComponent.groupFlags;
	attached = _dBStaticSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBStaticSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::StaticSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBTraceSceneComponent::DBTraceSceneComponent() :
		maxLength( 1.0f )
	, speedStart( 10.0f )
	, speedStop( 2.0f )
	, offsetColor( 0.0f )
	, offsetAlpha( 0.0f )
	, fadeoutSpeed( 10.0f )
	, skewness( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTraceSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &material );
	saver.Add( 3, &locator1Name );
	saver.Add( 4, &locator2Name );
	saver.Add( 5, &maxLength );
	saver.Add( 6, &speedStart );
	saver.Add( 7, &speedStop );
	saver.Add( 8, &colorFirst );
	saver.Add( 9, &colorLast );
	saver.Add( 10, &offsetColor );
	saver.Add( 11, &offsetAlpha );
	saver.Add( 12, &fadeoutSpeed );
	saver.Add( 13, &skewness );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTraceSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBTraceSceneComponent* parentPtr = (DBTraceSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBTraceSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "material", &material );
	saver.Add( "locator1Name", &locator1Name );
	saver.Add( "locator2Name", &locator2Name );
	saver.Add( "maxLength", &maxLength );
	saver.Add( "speedStart", &speedStart );
	saver.Add( "speedStop", &speedStop );
	saver.Add( "colorFirst", &colorFirst );
	saver.Add( "colorLast", &colorLast );
	saver.Add( "offsetColor", &offsetColor );
	saver.Add( "offsetAlpha", &offsetAlpha );
	saver.Add( "fadeoutSpeed", &fadeoutSpeed );
	saver.Add( "skewness", &skewness );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBTraceSceneComponent::Assign( const DBTraceSceneComponent& _dBTraceSceneComponent )
{
	material = _dBTraceSceneComponent.material;
	locator1Name = _dBTraceSceneComponent.locator1Name;
	locator2Name = _dBTraceSceneComponent.locator2Name;
	maxLength = _dBTraceSceneComponent.maxLength;
	speedStart = _dBTraceSceneComponent.speedStart;
	speedStop = _dBTraceSceneComponent.speedStop;
	colorFirst = _dBTraceSceneComponent.colorFirst;
	colorLast = _dBTraceSceneComponent.colorLast;
	offsetColor = _dBTraceSceneComponent.offsetColor;
	offsetAlpha = _dBTraceSceneComponent.offsetAlpha;
	fadeoutSpeed = _dBTraceSceneComponent.fadeoutSpeed;
	skewness = _dBTraceSceneComponent.skewness;
	locatorList = _dBTraceSceneComponent.locatorList;
	orientation = _dBTraceSceneComponent.orientation;
	groupFlags = _dBTraceSceneComponent.groupFlags;
	attached = _dBTraceSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBTraceSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::TraceSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBWaterInfo::DBWaterInfo() :
		tiling( 2.0f )
	, shininess( 4.0f )
	, ripples( 1.0f )
	, ripplesHeight( 0.1f )
	, distance( 5.0f )
	, refraction( 1.05f )
	, depth( 10.0f )
	, depthReflect( 0.0f )
	, causticsTiling( 2.0f )
	, causticsIntensity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBWaterInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tiling );
	saver.Add( 3, &shininess );
	saver.Add( 4, &ripples );
	saver.Add( 5, &ripplesHeight );
	saver.Add( 6, &distance );
	saver.Add( 7, &refraction );
	saver.Add( 8, &depth );
	saver.Add( 9, &depthReflect );
	saver.Add( 10, &speed );
	saver.Add( 11, &causticsTiling );
	saver.Add( 12, &causticsIntensity );
	saver.Add( 13, &gradientMap );
	saver.Add( 14, &causticsMap );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBWaterInfo::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBWaterInfo* parentPtr = (DBWaterInfo*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBWaterInfo::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "tiling", &tiling );
	saver.Add( "shininess", &shininess );
	saver.Add( "ripples", &ripples );
	saver.Add( "ripplesHeight", &ripplesHeight );
	saver.Add( "distance", &distance );
	saver.Add( "refraction", &refraction );
	saver.Add( "depth", &depth );
	saver.Add( "depthReflect", &depthReflect );
	saver.Add( "speed", &speed );
	saver.Add( "causticsTiling", &causticsTiling );
	saver.Add( "causticsIntensity", &causticsIntensity );
	saver.Add( "gradientMap", &gradientMap );
	saver.Add( "causticsMap", &causticsMap );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBWaterInfo::Assign( const DBWaterInfo& _dBWaterInfo )
{
	tiling = _dBWaterInfo.tiling;
	shininess = _dBWaterInfo.shininess;
	ripples = _dBWaterInfo.ripples;
	ripplesHeight = _dBWaterInfo.ripplesHeight;
	distance = _dBWaterInfo.distance;
	refraction = _dBWaterInfo.refraction;
	depth = _dBWaterInfo.depth;
	depthReflect = _dBWaterInfo.depthReflect;
	speed = _dBWaterInfo.speed;
	causticsTiling = _dBWaterInfo.causticsTiling;
	causticsIntensity = _dBWaterInfo.causticsIntensity;
	gradientMap = _dBWaterInfo.gradientMap;
	causticsMap = _dBWaterInfo.causticsMap;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBWaterSceneComponent::DBWaterSceneComponent() :
		waterLevel( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBWaterSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBStaticSceneComponent*)this );
	saver.Add( 2, &water );
	saver.Add( 3, &waterLevel );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBWaterSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBWaterSceneComponent* parentPtr = (DBWaterSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBWaterSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBStaticSceneComponent::SerializeSelf( saver );
	saver.Add( "water", &water );
	saver.Add( "waterLevel", &waterLevel );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBWaterSceneComponent::Assign( const DBWaterSceneComponent& _dBWaterSceneComponent )
{
	water = _dBWaterSceneComponent.water;
	waterLevel = _dBWaterSceneComponent.waterLevel;
	srcFileName = _dBWaterSceneComponent.srcFileName;
	geometryFileName = _dBWaterSceneComponent.geometryFileName;
	aabb.minX = _dBWaterSceneComponent.aabb.minX;
	aabb.maxX = _dBWaterSceneComponent.aabb.maxX;
	aabb.minY = _dBWaterSceneComponent.aabb.minY;
	aabb.maxY = _dBWaterSceneComponent.aabb.maxY;
	aabb.minZ = _dBWaterSceneComponent.aabb.minZ;
	aabb.maxZ = _dBWaterSceneComponent.aabb.maxZ;
	materialsReferences = _dBWaterSceneComponent.materialsReferences;
	locatorList = _dBWaterSceneComponent.locatorList;
	orientation = _dBWaterSceneComponent.orientation;
	groupFlags = _dBWaterSceneComponent.groupFlags;
	attached = _dBWaterSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> DBWaterSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<NScene::WaterSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EnableDisableSCEvents::EnableDisableSCEvents() :
		order( ENABLEDISABLEORDER_ENABLETHENDISABLE )
	, restartComponent( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableDisableSCEvents::operator&( IBinSaver &saver )
{
	saver.Add( 2, &order );
	saver.Add( 3, &restartComponent );
	saver.Add( 4, &enableEvents );
	saver.Add( 5, &disableEvents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableDisableSCEvents::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EnableDisableSCEvents* parentPtr = (EnableDisableSCEvents*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableDisableSCEvents::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "order", &order );
	saver.Add( "restartComponent", &restartComponent );
	saver.Add( "enableEvents", &enableEvents );
	saver.Add( "disableEvents", &disableEvents );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableDisableSCEvents::Assign( const EnableDisableSCEvents& _enableDisableSCEvents )
{
	order = _enableDisableSCEvents.order;
	restartComponent = _enableDisableSCEvents.restartComponent;
	enableEvents = _enableDisableSCEvents.enableEvents;
	disableEvents = _enableDisableSCEvents.disableEvents;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EnableDisableSkinEvents::EnableDisableSkinEvents() :
		order( ENABLEDISABLEORDER_ENABLETHENDISABLE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableDisableSkinEvents::operator&( IBinSaver &saver )
{
	saver.Add( 2, &order );
	saver.Add( 3, &enableEvents );
	saver.Add( 4, &disableEvents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableDisableSkinEvents::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EnableDisableSkinEvents* parentPtr = (EnableDisableSkinEvents*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableDisableSkinEvents::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "order", &order );
	saver.Add( "enableEvents", &enableEvents );
	saver.Add( "disableEvents", &disableEvents );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableDisableSkinEvents::Assign( const EnableDisableSkinEvents& _enableDisableSkinEvents )
{
	order = _enableDisableSkinEvents.order;
	enableEvents = _enableDisableSkinEvents.enableEvents;
	disableEvents = _enableDisableSkinEvents.disableEvents;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GroundHitSCEvent::GroundHitSCEvent() :
		heightAboveGround( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GroundHitSCEvent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SCEvent*)this );
	saver.Add( 2, &heightAboveGround );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GroundHitSCEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GroundHitSCEvent* parentPtr = (GroundHitSCEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GroundHitSCEvent::SerializeSelf( IXmlSaver &saver )
{
	SCEvent::SerializeSelf( saver );
	saver.Add( "heightAboveGround", &heightAboveGround );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GroundHitSCEvent::Assign( const GroundHitSCEvent& _groundHitSCEvent )
{
	heightAboveGround = _groundHitSCEvent.heightAboveGround;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocatorList::LocatorList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LocatorList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &locators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LocatorList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LocatorList* parentPtr = (LocatorList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocatorList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "locators", &locators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocatorList::Assign( const LocatorList& _locatorList )
{
	locators = _locatorList.locators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NamedSCEvent::NamedSCEvent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NamedSCEvent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SCEvent*)this );
	saver.Add( 2, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NamedSCEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NamedSCEvent* parentPtr = (NamedSCEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NamedSCEvent::SerializeSelf( IXmlSaver &saver )
{
	SCEvent::SerializeSelf( saver );
	saver.Add( "name", &name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NamedSCEvent::Assign( const NamedSCEvent& _namedSCEvent )
{
	name = _namedSCEvent.name;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectTrack::SceneObjectTrack()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectTrack::operator&( IBinSaver &saver )
{
	saver.Add( 2, &placement );
	saver.Add( 3, &opacity );
	saver.Add( 4, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectTrack::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SceneObjectTrack* parentPtr = (SceneObjectTrack*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectTrack::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "placement", &placement );
	saver.Add( "opacity", &opacity );
	saver.Add( "name", &name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectTrack::Assign( const SceneObjectTrack& _sceneObjectTrack )
{
	placement.pos = _sceneObjectTrack.placement.pos;
	placement.rot = _sceneObjectTrack.placement.rot;
	placement.scale = _sceneObjectTrack.placement.scale;
	opacity = _sceneObjectTrack.opacity;
	name = _sceneObjectTrack.name;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectTracks::SceneObjectTracks()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectTracks::operator&( IBinSaver &saver )
{
	saver.Add( 2, &animatedTracks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectTracks::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SceneObjectTracks* parentPtr = (SceneObjectTracks*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectTracks::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "animatedTracks", &animatedTracks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectTracks::Assign( const SceneObjectTracks& _sceneObjectTracks )
{
	animatedTracks = _sceneObjectTracks.animatedTracks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimationSCEvent::AnimationSCEvent() :
		type( ANIMEVENTTYPE_NODEPARAM )
	, animParam( 0.0f )
	, probability( 100.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimationSCEvent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SCEvent*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &name );
	saver.Add( 4, &animParam );
	saver.Add( 5, &probability );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimationSCEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AnimationSCEvent* parentPtr = (AnimationSCEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimationSCEvent::SerializeSelf( IXmlSaver &saver )
{
	SCEvent::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "name", &name );
	saver.Add( "animParam", &animParam );
	saver.Add( "probability", &probability );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimationSCEvent::Assign( const AnimationSCEvent& _animationSCEvent )
{
	type = _animationSCEvent.type;
	name = _animationSCEvent.name;
	animParam = _animationSCEvent.animParam;
	probability = _animationSCEvent.probability;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TimeController::TimeController() :
		speed( 1.0f )
	, startDelay( 0.0f )
	, firstCycleOffset( 0.0f )
	, firstCycleOffsetDelta( 0.0f )
	, cycleLength( 0.0f )
	, cycleCount( 1 )
	, fadein( 0.0f )
	, fadeout( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TimeController::operator&( IBinSaver &saver )
{
	saver.Add( 2, &speed );
	saver.Add( 3, &startDelay );
	saver.Add( 4, &firstCycleOffset );
	saver.Add( 5, &firstCycleOffsetDelta );
	saver.Add( 6, &cycleLength );
	saver.Add( 7, &cycleCount );
	saver.Add( 8, &fadein );
	saver.Add( 9, &fadeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TimeController::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TimeController* parentPtr = (TimeController*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "speed", &speed );
	saver.Add( "startDelay", &startDelay );
	saver.Add( "firstCycleOffset", &firstCycleOffset );
	saver.Add( "firstCycleOffsetDelta", &firstCycleOffsetDelta );
	saver.Add( "cycleLength", &cycleLength );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "fadein", &fadein );
	saver.Add( "fadeout", &fadeout );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::Assign( const TimeController& _timeController )
{
	speed = _timeController.speed;
	startDelay = _timeController.startDelay;
	firstCycleOffset = _timeController.firstCycleOffset;
	firstCycleOffsetDelta = _timeController.firstCycleOffsetDelta;
	cycleLength = _timeController.cycleLength;
	cycleCount = _timeController.cycleCount;
	fadein = _timeController.fadein;
	fadeout = _timeController.fadeout;
}
}; // namespace NDb
