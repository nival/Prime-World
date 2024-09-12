// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "../Render/DBRender.h"
#include "DBSceneBase.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( ChildEffect );
REGISTER_DBRESOURCE( CollisionGeometry );
REGISTER_DBRESOURCE( Effect );
REGISTER_DBRESOURCE( GameObject );
REGISTER_DBRESOURCE( LandTemp );
REGISTER_DBRESOURCE( Road );
REGISTER_DBRESOURCE( ScriptPath );
REGISTER_DBRESOURCE( SoundSet );
REGISTER_DBRESOURCE( SoundSRC );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ELocatorAttachFlags value )
{
	switch( value )
	{
		case LOCATORATTACHFLAGS_NONE:
			return "None";
		case LOCATORATTACHFLAGS_USEJOINTSCALE:
			return "UseJointScale";
		case LOCATORATTACHFLAGS_USEJOINTROTATION:
			return "UseJointRotation";
		case LOCATORATTACHFLAGS_USEJOINTPOSITION:
			return "UseJointPosition";
		case LOCATORATTACHFLAGS_CANCELNORMALLEVELLING:
			return "CancelNormalLevelling";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ELocatorAttachFlags StringToEnum_ELocatorAttachFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ELocatorAttachFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "LOCATORATTACHFLAGS_NONE" ) == 0 )
		return LOCATORATTACHFLAGS_NONE;
	if ( strcmp( value, "UseJointScale" ) == 0 || strcmp( value, "LOCATORATTACHFLAGS_USEJOINTSCALE" ) == 0 )
		return LOCATORATTACHFLAGS_USEJOINTSCALE;
	if ( strcmp( value, "UseJointRotation" ) == 0 || strcmp( value, "LOCATORATTACHFLAGS_USEJOINTROTATION" ) == 0 )
		return LOCATORATTACHFLAGS_USEJOINTROTATION;
	if ( strcmp( value, "UseJointPosition" ) == 0 || strcmp( value, "LOCATORATTACHFLAGS_USEJOINTPOSITION" ) == 0 )
		return LOCATORATTACHFLAGS_USEJOINTPOSITION;
	if ( strcmp( value, "CancelNormalLevelling" ) == 0 || strcmp( value, "LOCATORATTACHFLAGS_CANCELNORMALLEVELLING" ) == 0 )
		return LOCATORATTACHFLAGS_CANCELNORMALLEVELLING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ELocatorAttachFlags", value ) );
	return LOCATORATTACHFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimFaceFXKey::AnimFaceFXKey() :
		startTime( 0.0f )
	, animation( 0 )
	, cycleCount( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimFaceFXKey::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startTime );
	saver.Add( 3, &animation );
	saver.Add( 4, &cycleCount );
	saver.Add( 5, &facefxname );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimFaceFXKey::operator&( IXmlSaver &saver )
{
	saver.Add( "startTime", &startTime );
	saver.Add( "animation", &animation );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "facefxname", &facefxname );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LightInstance::LightInstance() :
		scale( 1.0f )
	, speed( 1.0f )
	, offset( 0.0f )
	, cycleLength( 0.0f )
	, cycleCount( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &light );
	saver.Add( 3, &position );
	saver.Add( 4, &rotation );
	saver.Add( 5, &scale );
	saver.Add( 6, &speed );
	saver.Add( 7, &offset );
	saver.Add( 8, &cycleLength );
	saver.Add( 9, &cycleCount );
	saver.Add( 10, &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "light", &light );
	saver.Add( "position", &position );
	saver.Add( "rotation", &rotation );
	saver.Add( "scale", &scale );
	saver.Add( "speed", &speed );
	saver.Add( "offset", &offset );
	saver.Add( "cycleLength", &cycleLength );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "jointName", &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelInstance::ModelInstance() :
		speed( 1.0f )
	, offset( 0.0f )
	, cycleLength( 0.0f )
	, cycleCount( 0 )
	, duration( 0.0f )
	, fadein( 0.0f )
	, fadeout( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModelInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &model );
	saver.Add( 3, &anims );
	saver.Add( 4, &skins );
	saver.Add( 5, &trasform );
	saver.Add( 6, &speed );
	saver.Add( 7, &offset );
	saver.Add( 8, &cycleLength );
	saver.Add( 9, &cycleCount );
	saver.Add( 10, &duration );
	saver.Add( 11, &fadein );
	saver.Add( 12, &fadeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModelInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "model", &model );
	saver.Add( "anims", &anims );
	saver.Add( "skins", &skins );
	saver.Add( "trasform", &trasform );
	saver.Add( "speed", &speed );
	saver.Add( "offset", &offset );
	saver.Add( "cycleLength", &cycleLength );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "duration", &duration );
	saver.Add( "fadein", &fadein );
	saver.Add( "fadeout", &fadeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Locator::Locator() :
		flags( ELocatorAttachFlags( LOCATORATTACHFLAGS_USEJOINTPOSITION | LOCATORATTACHFLAGS_USEJOINTROTATION | LOCATORATTACHFLAGS_USEJOINTSCALE ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locator::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &offset2 );
	saver.Add( 4, &flags );
	saver.Add( 5, &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locator::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "offset2", &offset2 );
	saver.Add( "flags", &flags );
	saver.Add( "jointName", &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundInstance::SoundInstance() :
		offset( 0.0f )
	, cycleCount( 0 )
	, volume( 1.0f )
	, is3DSound( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundFile );
	saver.Add( 3, &offset );
	saver.Add( 4, &cycleCount );
	saver.Add( 5, &volume );
	saver.Add( 6, &is3DSound );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "soundFile", &soundFile );
	saver.Add( "offset", &offset );
	saver.Add( "cycleCount", &cycleCount );
	saver.Add( "volume", &volume );
	saver.Add( "is3DSound", &is3DSound );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectLockMask::ObjectLockMask() :
		tileSize( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockMask::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tileSize );
	saver.Add( 3, &mask );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockMask::operator&( IXmlSaver &saver )
{
	saver.Add( "tileSize", &tileSize );
	saver.Add( "mask", &mask );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RoadControlPoint::RoadControlPoint() :
		opacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadControlPoint::operator&( IBinSaver &saver )
{
	saver.Add( 1, (FlatSplineControlPointDesc*)this );
	saver.Add( 2, &opacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadControlPoint::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (FlatSplineControlPointDesc*)this );
	saver.Add( "opacity", &opacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RoadProperties::RoadProperties() :
		width( 2.0f )
	, border( 0.2f )
	, falloff( 0.1f )
	, opacity( 1.0f )
	, tileU( 1.0f )
	, tileV( 1.0f )
	, tileVBorder( 1.0f )
	, fit( false )
	, flip( false )
	, priority( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadProperties::operator&( IBinSaver &saver )
{
	saver.Add( 2, &width );
	saver.Add( 3, &border );
	saver.Add( 4, &falloff );
	saver.Add( 5, &opacity );
	saver.Add( 6, &tileU );
	saver.Add( 7, &tileV );
	saver.Add( 8, &tileVBorder );
	saver.Add( 9, &fit );
	saver.Add( 10, &flip );
	saver.Add( 11, &priority );
	saver.Add( 12, &materialN );
	saver.Add( 13, &materialA );
	saver.Add( 14, &materialB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadProperties::operator&( IXmlSaver &saver )
{
	saver.Add( "width", &width );
	saver.Add( "border", &border );
	saver.Add( "falloff", &falloff );
	saver.Add( "opacity", &opacity );
	saver.Add( "tileU", &tileU );
	saver.Add( "tileV", &tileV );
	saver.Add( "tileVBorder", &tileVBorder );
	saver.Add( "fit", &fit );
	saver.Add( "flip", &flip );
	saver.Add( "priority", &priority );
	saver.Add( "materialN", &materialN );
	saver.Add( "materialA", &materialA );
	saver.Add( "materialB", &materialB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundTrack::SoundTrack() :
		volume( 1.0f )
	, volumeRandomization( 0.0f )
	, priority( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundTrack::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sound );
	saver.Add( 3, &volume );
	saver.Add( 4, &volumeRandomization );
	saver.Add( 5, &priority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundTrack::operator&( IXmlSaver &saver )
{
	saver.Add( "sound", &sound );
	saver.Add( "volume", &volume );
	saver.Add( "volumeRandomization", &volumeRandomization );
	saver.Add( "priority", &priority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticModelInstance::StaticModelInstance() :
		offset( 0.0f )
	, duration( 0.0f )
	, fadein( 0.0f )
	, fadeout( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StaticModelInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &model );
	saver.Add( 3, &trasform );
	saver.Add( 4, &offset );
	saver.Add( 5, &duration );
	saver.Add( 6, &fadein );
	saver.Add( 7, &fadeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StaticModelInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "model", &model );
	saver.Add( "trasform", &trasform );
	saver.Add( "offset", &offset );
	saver.Add( "duration", &duration );
	saver.Add( "fadein", &fadein );
	saver.Add( "fadeout", &fadeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundObject::SoundObject()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundObject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundSet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundObject::operator&( IXmlSaver &saver )
{
	saver.Add( "soundSet", &soundSet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundEffect::SoundEffect() :
		pitch( 0.0f )
	, pitchRandomization( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SoundTrack*)this );
	saver.Add( 2, &pitch );
	saver.Add( 3, &pitchRandomization );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundEffect::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (SoundTrack*)this );
	saver.Add( "pitch", &pitch );
	saver.Add( "pitchRandomization", &pitchRandomization );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectInstance::EffectInstance()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &model );
	saver.Add( 3, &light );
	saver.Add( 4, &staticmodel );
	saver.Add( 5, &sound );
	saver.Add( 6, &fmodEvent );
	saver.Add( 7, &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "model", &model );
	saver.Add( "light", &light );
	saver.Add( "staticmodel", &staticmodel );
	saver.Add( "sound", &sound );
	saver.Add( "fmodEvent", &fmodEvent );
	saver.Add( "jointName", &jointName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SyncInfo::SyncInfo() :
		tempoSync( false )
	, toneSync( false )
	, offset( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SyncInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &midiFile );
	saver.Add( 3, &tempoSync );
	saver.Add( 4, &toneSync );
	saver.Add( 5, &offset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SyncInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "midiFile", &midiFile );
	saver.Add( "tempoSync", &tempoSync );
	saver.Add( "toneSync", &toneSync );
	saver.Add( "offset", &offset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ViewCamera::ViewCamera() :
		yaw( 0.0f )
	, pitch( 0.0f )
	, roll( 0.0f )
	, rod( 10 )
	, fov( 30 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ViewCamera::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &anchor );
	saver.Add( 4, &yaw );
	saver.Add( 5, &pitch );
	saver.Add( 6, &roll );
	saver.Add( 7, &rod );
	saver.Add( 8, &fov );
	saver.Add( 9, &environment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ViewCamera::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "anchor", &anchor );
	saver.Add( "yaw", &yaw );
	saver.Add( "pitch", &pitch );
	saver.Add( "roll", &roll );
	saver.Add( "rod", &rod );
	saver.Add( "fov", &fov );
	saver.Add( "environment", &environment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChildEffect::ChildEffect()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChildEffect::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tranformedchild );
	saver.Add( 3, &childeffect );
	saver.Add( 4, &transform );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChildEffect::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChildEffect* parentPtr = (ChildEffect*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChildEffect::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "tranformedchild", &tranformedchild );
	saver.Add( "childeffect", &childeffect );
	saver.Add( "transform", &transform );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChildEffect::Assign( const ChildEffect& _childEffect )
{
	tranformedchild = _childEffect.tranformedchild;
	childeffect = _childEffect.childeffect;
	transform = _childEffect.transform;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionGeometry::CollisionGeometry()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollisionGeometry::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &fileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollisionGeometry::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CollisionGeometry* parentPtr = (CollisionGeometry*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionGeometry::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "fileName", &fileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionGeometry::Assign( const CollisionGeometry& _collisionGeometry )
{
	srcFileName = _collisionGeometry.srcFileName;
	fileName = _collisionGeometry.fileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Effect::Effect() :
		randomizePhase( false )
	, randomizeSpeed( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Effect::operator&( IBinSaver &saver )
{
	saver.Add( 2, &landtemp );
	saver.Add( 3, &tranformedchild );
	saver.Add( 4, &child );
	saver.Add( 5, &effects );
	saver.Add( 6, &randomizePhase );
	saver.Add( 7, &randomizeSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Effect::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Effect* parentPtr = (Effect*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Effect::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "landtemp", &landtemp );
	saver.Add( "tranformedchild", &tranformedchild );
	saver.Add( "child", &child );
	saver.Add( "effects", &effects );
	saver.Add( "randomizePhase", &randomizePhase );
	saver.Add( "randomizeSpeed", &randomizeSpeed );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Effect::Assign( const Effect& _effect )
{
	landtemp = _effect.landtemp;
	tranformedchild = _effect.tranformedchild;
	child = _effect.child;
	effects = _effect.effects;
	randomizePhase = _effect.randomizePhase;
	randomizeSpeed = _effect.randomizeSpeed;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject() :
		minLockScale( 0.0f )
	, rounded( false )
	, heightObject( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameObject::operator&( IBinSaver &saver )
{
	saver.Add( 2, &collision );
	saver.Add( 3, &lockMask );
	saver.Add( 4, &minLockScale );
	saver.Add( 5, &rounded );
	saver.Add( 6, &heightObject );

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
	saver.Add( "collision", &collision );
	saver.Add( "lockMask", &lockMask );
	saver.Add( "minLockScale", &minLockScale );
	saver.Add( "rounded", &rounded );
	saver.Add( "heightObject", &heightObject );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::Assign( const GameObject& _gameObject )
{
	collision = _gameObject.collision;
	lockMask.tileSize = _gameObject.lockMask.tileSize;
	lockMask.mask = _gameObject.lockMask.mask;
	minLockScale = _gameObject.minLockScale;
	rounded = _gameObject.rounded;
	heightObject = _gameObject.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LandTemp::LandTemp() :
		speed( 0.1f )
	, randomSeed( 50 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LandTemp::operator&( IBinSaver &saver )
{
	saver.Add( 2, &speed );
	saver.Add( 3, &randomSeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LandTemp::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LandTemp* parentPtr = (LandTemp*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LandTemp::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "speed", &speed );
	saver.Add( "randomSeed", &randomSeed );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LandTemp::Assign( const LandTemp& _landTemp )
{
	speed = _landTemp.speed;
	randomSeed = _landTemp.randomSeed;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Road::Road()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Road::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &points );
	saver.Add( 3, &properties );
	saver.Add( 4, &bakedFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Road::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Road* parentPtr = (Road*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Road::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "points", &points );
	saver.Add( "properties", &properties );
	saver.Add( "bakedFileName", &bakedFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Road::Assign( const Road& _road )
{
	points = _road.points;
	properties.width = _road.properties.width;
	properties.border = _road.properties.border;
	properties.falloff = _road.properties.falloff;
	properties.opacity = _road.properties.opacity;
	properties.tileU = _road.properties.tileU;
	properties.tileV = _road.properties.tileV;
	properties.tileVBorder = _road.properties.tileVBorder;
	properties.fit = _road.properties.fit;
	properties.flip = _road.properties.flip;
	properties.priority = _road.properties.priority;
	properties.materialN = _road.properties.materialN;
	properties.materialA = _road.properties.materialA;
	properties.materialB = _road.properties.materialB;
	bakedFileName = _road.bakedFileName;
	collision = _road.collision;
	lockMask.tileSize = _road.lockMask.tileSize;
	lockMask.mask = _road.lockMask.mask;
	minLockScale = _road.minLockScale;
	rounded = _road.rounded;
	heightObject = _road.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptPath::ScriptPath()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPath::operator&( IBinSaver &saver )
{
	saver.Add( 1, (GameObject*)this );
	saver.Add( 2, &path );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptPath::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScriptPath* parentPtr = (ScriptPath*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptPath::SerializeSelf( IXmlSaver &saver )
{
	GameObject::SerializeSelf( saver );
	saver.Add( "path", &path );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptPath::Assign( const ScriptPath& _scriptPath )
{
	path = _scriptPath.path;
	collision = _scriptPath.collision;
	lockMask.tileSize = _scriptPath.lockMask.tileSize;
	lockMask.mask = _scriptPath.lockMask.mask;
	minLockScale = _scriptPath.minLockScale;
	rounded = _scriptPath.rounded;
	heightObject = _scriptPath.heightObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundSet::SoundSet() :
		priority( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSet::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sounds );
	saver.Add( 3, &priority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSet::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SoundSet* parentPtr = (SoundSet*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundSet::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "sounds", &sounds );
	saver.Add( "priority", &priority );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundSet::Assign( const SoundSet& _soundSet )
{
	sounds = _soundSet.sounds;
	priority = _soundSet.priority;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundSRC::SoundSRC()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSRC::operator&( IBinSaver &saver )
{
	saver.Add( 2, &soundFile );
	saver.Add( 3, &syncInfo );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundSRC::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SoundSRC* parentPtr = (SoundSRC*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundSRC::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "soundFile", &soundFile );
	saver.Add( "syncInfo", &syncInfo );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundSRC::Assign( const SoundSRC& _soundSRC )
{
	soundFile = _soundSRC.soundFile;
	syncInfo.midiFile = _soundSRC.syncInfo.midiFile;
	syncInfo.tempoSync = _soundSRC.syncInfo.tempoSync;
	syncInfo.toneSync = _soundSRC.syncInfo.toneSync;
	syncInfo.offset = _soundSRC.syncInfo.offset;
}
}; // namespace NDb
