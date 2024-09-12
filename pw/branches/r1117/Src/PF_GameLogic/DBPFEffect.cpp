// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_Core/DBEffect.h"
#include "../Scene/DBScene.h"
#include "DBPFEffect.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AuraEffect );
REGISTER_DBRESOURCE( EffectSwitcher );
REGISTER_DBRESOURCE( InvisibilityEffect );
REGISTER_DBRESOURCE( MinimapEffect );
REGISTER_DBRESOURCE( PlayAnimationEffect );
REGISTER_DBRESOURCE( PriestessSignEffect );
REGISTER_DBRESOURCE( RandomEffect );
REGISTER_DBRESOURCE( UnitSceneObjectModify );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef VISUAL_CUTTED
#include "PFAuraEffect.h"
#include "PFEffectRandom.h"
#include "PFEffectSwitcher.h"
#include "PFInvisibilityEffect.h"
#include "PFMinimapEffect.h"
#include "PFPlayAnimEffect.h"
#include "PFPriestessSignEffect.h"
#include "PFUnitSceneObjectModify.h"
#endif // #ifndef VISUAL_CUTTED

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAuraType value )
{
	switch( value )
	{
		case AURATYPE_ALLY:
			return "Ally";
		case AURATYPE_ENEMY:
			return "Enemy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAuraType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAuraType StringToEnum_EAuraType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAuraType)(NStr::ToInt( value ));
	if ( strcmp( value, "Ally" ) == 0 || strcmp( value, "AURATYPE_ALLY" ) == 0 )
		return AURATYPE_ALLY;
	if ( strcmp( value, "Enemy" ) == 0 || strcmp( value, "AURATYPE_ENEMY" ) == 0 )
		return AURATYPE_ENEMY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAuraType", value ) );
	return AURATYPE_ALLY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectSwitchLogic value )
{
	switch( value )
	{
		case EFFECTSWITCHLOGIC_FACTIONVISIBILITY:
			return "FactionVisibility";
		case EFFECTSWITCHLOGIC_SENDERFACTION:
			return "SenderFaction";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectSwitchLogic", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectSwitchLogic StringToEnum_EEffectSwitchLogic( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectSwitchLogic)(NStr::ToInt( value ));
	if ( strcmp( value, "FactionVisibility" ) == 0 || strcmp( value, "EFFECTSWITCHLOGIC_FACTIONVISIBILITY" ) == 0 )
		return EFFECTSWITCHLOGIC_FACTIONVISIBILITY;
	if ( strcmp( value, "SenderFaction" ) == 0 || strcmp( value, "EFFECTSWITCHLOGIC_SENDERFACTION" ) == 0 )
		return EFFECTSWITCHLOGIC_SENDERFACTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectSwitchLogic", value ) );
	return EFFECTSWITCHLOGIC_FACTIONVISIBILITY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMinimapEffects value )
{
	switch( value )
	{
		case MINIMAPEFFECTS_EGGCARRIER:
			return "EggCarrier";
		case MINIMAPEFFECTS_MARKERALLY:
			return "MarkerAlly";
		case MINIMAPEFFECTS_MARKERHOSTILE:
			return "MarkerHostile";
		case MINIMAPEFFECTS_CHAT:
			return "Chat";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMinimapEffects", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMinimapEffects StringToEnum_EMinimapEffects( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMinimapEffects)(NStr::ToInt( value ));
	if ( strcmp( value, "EggCarrier" ) == 0 || strcmp( value, "MINIMAPEFFECTS_EGGCARRIER" ) == 0 )
		return MINIMAPEFFECTS_EGGCARRIER;
	if ( strcmp( value, "MarkerAlly" ) == 0 || strcmp( value, "MINIMAPEFFECTS_MARKERALLY" ) == 0 )
		return MINIMAPEFFECTS_MARKERALLY;
	if ( strcmp( value, "MarkerHostile" ) == 0 || strcmp( value, "MINIMAPEFFECTS_MARKERHOSTILE" ) == 0 )
		return MINIMAPEFFECTS_MARKERHOSTILE;
	if ( strcmp( value, "Chat" ) == 0 || strcmp( value, "MINIMAPEFFECTS_CHAT" ) == 0 )
		return MINIMAPEFFECTS_CHAT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMinimapEffects", value ) );
	return MINIMAPEFFECTS_EGGCARRIER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESceneObjectVisibilityMode value )
{
	switch( value )
	{
		case SCENEOBJECTVISIBILITYMODE_ASOBJECT:
			return "AsObject";
		case SCENEOBJECTVISIBILITYMODE_ASBUILDING:
			return "AsBuilding";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESceneObjectVisibilityMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESceneObjectVisibilityMode StringToEnum_ESceneObjectVisibilityMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESceneObjectVisibilityMode)(NStr::ToInt( value ));
	if ( strcmp( value, "AsObject" ) == 0 || strcmp( value, "SCENEOBJECTVISIBILITYMODE_ASOBJECT" ) == 0 )
		return SCENEOBJECTVISIBILITYMODE_ASOBJECT;
	if ( strcmp( value, "AsBuilding" ) == 0 || strcmp( value, "SCENEOBJECTVISIBILITYMODE_ASBUILDING" ) == 0 )
		return SCENEOBJECTVISIBILITYMODE_ASBUILDING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESceneObjectVisibilityMode", value ) );
	return SCENEOBJECTVISIBILITYMODE_ASOBJECT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitSceneObjectModifyMode value )
{
	switch( value )
	{
		case UNITSCENEOBJECTMODIFYMODE_APPEND:
			return "Append";
		case UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC:
			return "ReplaceStatic";
		case UNITSCENEOBJECTMODIFYMODE_REPLACEANIMATED:
			return "ReplaceAnimated";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitSceneObjectModifyMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitSceneObjectModifyMode StringToEnum_EUnitSceneObjectModifyMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitSceneObjectModifyMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Append" ) == 0 || strcmp( value, "UNITSCENEOBJECTMODIFYMODE_APPEND" ) == 0 )
		return UNITSCENEOBJECTMODIFYMODE_APPEND;
	if ( strcmp( value, "ReplaceStatic" ) == 0 || strcmp( value, "UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC" ) == 0 )
		return UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC;
	if ( strcmp( value, "ReplaceAnimated" ) == 0 || strcmp( value, "UNITSCENEOBJECTMODIFYMODE_REPLACEANIMATED" ) == 0 )
		return UNITSCENEOBJECTMODIFYMODE_REPLACEANIMATED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitSceneObjectModifyMode", value ) );
	return UNITSCENEOBJECTMODIFYMODE_APPEND;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AuraEffect::AuraEffect() :
		type( AURATYPE_ENEMY )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &type );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AuraEffect* parentPtr = (AuraEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< AuraEffect > parentStateCopier( this, stateManager.states, &AuraEffect::NewAuraEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< AuraEffect > reader( this, stateManager.states, &AuraEffect::NewAuraEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuraEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "type", &type );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuraEffect::Assign( const AuraEffect& _auraEffect )
{
	type = _auraEffect.type;
	deathType = _auraEffect.deathType;
	lifeTime = _auraEffect.lifeTime;
	enableCondition = _auraEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> AuraEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFAuraEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectSwitcher::EffectSwitcher() :
		logic( EFFECTSWITCHLOGIC_FACTIONVISIBILITY )
	, isVisibleUnderWarfog( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectSwitcher::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &logic );
	saver.Add( 3, &effectOnVisible );
	saver.Add( 4, &effectOnInvisible );
	saver.Add( 5, &isVisibleUnderWarfog );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectSwitcher::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectSwitcher* parentPtr = (EffectSwitcher*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< EffectSwitcher > parentStateCopier( this, stateManager.states, &EffectSwitcher::NewEffectSwitcher );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< EffectSwitcher > reader( this, stateManager.states, &EffectSwitcher::NewEffectSwitcher );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectSwitcher::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "logic", &logic );
	saver.Add( "effectOnVisible", &effectOnVisible );
	saver.Add( "effectOnInvisible", &effectOnInvisible );
	saver.Add( "isVisibleUnderWarfog", &isVisibleUnderWarfog );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectSwitcher::Assign( const EffectSwitcher& _effectSwitcher )
{
	logic = _effectSwitcher.logic;
	effectOnVisible = _effectSwitcher.effectOnVisible;
	effectOnInvisible = _effectSwitcher.effectOnInvisible;
	isVisibleUnderWarfog = _effectSwitcher.isVisibleUnderWarfog;
	deathType = _effectSwitcher.deathType;
	lifeTime = _effectSwitcher.lifeTime;
	enableCondition = _effectSwitcher.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> EffectSwitcher::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFEffectSwitcher>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InvisibilityEffect::InvisibilityEffect()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvisibilityEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ScaleColorEffect*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvisibilityEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			InvisibilityEffect* parentPtr = (InvisibilityEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< InvisibilityEffect > parentStateCopier( this, stateManager.states, &InvisibilityEffect::NewInvisibilityEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< InvisibilityEffect > reader( this, stateManager.states, &InvisibilityEffect::NewInvisibilityEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvisibilityEffect::SerializeSelf( IXmlSaver &saver )
{
	ScaleColorEffect::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvisibilityEffect::Assign( const InvisibilityEffect& _invisibilityEffect )
{
	scale = _invisibilityEffect.scale;
	colorMul = _invisibilityEffect.colorMul;
	colorAdd = _invisibilityEffect.colorAdd;
	blendMode = _invisibilityEffect.blendMode;
	scaleIn = _invisibilityEffect.scaleIn;
	scaleOut = _invisibilityEffect.scaleOut;
	fadeInTime = _invisibilityEffect.fadeInTime;
	fadeOutTime = _invisibilityEffect.fadeOutTime;
	fullRecolor = _invisibilityEffect.fullRecolor;
	deathType = _invisibilityEffect.deathType;
	lifeTime = _invisibilityEffect.lifeTime;
	enableCondition = _invisibilityEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> InvisibilityEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::InvisibilityEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinimapEffect::MinimapEffect() :
		effect( MINIMAPEFFECTS_EGGCARRIER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinimapEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinimapEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinimapEffect* parentPtr = (MinimapEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< MinimapEffect > parentStateCopier( this, stateManager.states, &MinimapEffect::NewMinimapEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< MinimapEffect > reader( this, stateManager.states, &MinimapEffect::NewMinimapEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinimapEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "effect", &effect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinimapEffect::Assign( const MinimapEffect& _minimapEffect )
{
	effect = _minimapEffect.effect;
	deathType = _minimapEffect.deathType;
	lifeTime = _minimapEffect.lifeTime;
	enableCondition = _minimapEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> MinimapEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFMinimapEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlayAnimationEffect::PlayAnimationEffect() :
		markerReachTime( 0.0f )
	, goToOtherNodeOnStop( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayAnimationEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &animGraphNode );
	saver.Add( 3, &markerReachTime );
	saver.Add( 4, &marker );
	saver.Add( 5, &goToOtherNodeOnStop );
	saver.Add( 6, &returnAnimGraphNode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayAnimationEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PlayAnimationEffect* parentPtr = (PlayAnimationEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< PlayAnimationEffect > parentStateCopier( this, stateManager.states, &PlayAnimationEffect::NewPlayAnimationEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< PlayAnimationEffect > reader( this, stateManager.states, &PlayAnimationEffect::NewPlayAnimationEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayAnimationEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "animGraphNode", &animGraphNode );
	saver.Add( "markerReachTime", &markerReachTime );
	saver.Add( "marker", &marker );
	saver.Add( "goToOtherNodeOnStop", &goToOtherNodeOnStop );
	saver.Add( "returnAnimGraphNode", &returnAnimGraphNode );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayAnimationEffect::Assign( const PlayAnimationEffect& _playAnimationEffect )
{
	animGraphNode = _playAnimationEffect.animGraphNode;
	markerReachTime = _playAnimationEffect.markerReachTime;
	marker = _playAnimationEffect.marker;
	goToOtherNodeOnStop = _playAnimationEffect.goToOtherNodeOnStop;
	returnAnimGraphNode = _playAnimationEffect.returnAnimGraphNode;
	deathType = _playAnimationEffect.deathType;
	lifeTime = _playAnimationEffect.lifeTime;
	enableCondition = _playAnimationEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> PlayAnimationEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFPlayAnimEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriestessSignEffect::PriestessSignEffect() :
		flyInDelay( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PriestessSignEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicEffectStandalone*)this );
	saver.Add( 2, &soulEffect );
	saver.Add( 3, &destinationLocator );
	saver.Add( 4, &flyInDelay );
	saver.Add( 5, &flyInPath );
	saver.Add( 6, &flyInAnim );
	saver.Add( 7, &flyOutAnim );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PriestessSignEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PriestessSignEffect* parentPtr = (PriestessSignEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< PriestessSignEffect > parentStateCopier( this, stateManager.states, &PriestessSignEffect::NewPriestessSignEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< PriestessSignEffect > reader( this, stateManager.states, &PriestessSignEffect::NewPriestessSignEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PriestessSignEffect::SerializeSelf( IXmlSaver &saver )
{
	BasicEffectStandalone::SerializeSelf( saver );
	saver.Add( "soulEffect", &soulEffect );
	saver.Add( "destinationLocator", &destinationLocator );
	saver.Add( "flyInDelay", &flyInDelay );
	saver.Add( "flyInPath", &flyInPath );
	saver.Add( "flyInAnim", &flyInAnim );
	saver.Add( "flyOutAnim", &flyOutAnim );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PriestessSignEffect::Assign( const PriestessSignEffect& _priestessSignEffect )
{
	soulEffect = _priestessSignEffect.soulEffect;
	destinationLocator = _priestessSignEffect.destinationLocator;
	flyInDelay = _priestessSignEffect.flyInDelay;
	flyInPath = _priestessSignEffect.flyInPath;
	flyInAnim = _priestessSignEffect.flyInAnim;
	flyOutAnim = _priestessSignEffect.flyOutAnim;
	visibilityLimited = _priestessSignEffect.visibilityLimited;
	visibleTime = _priestessSignEffect.visibleTime;
	isVisibleUnderWarfog = _priestessSignEffect.isVisibleUnderWarfog;
	parentType = _priestessSignEffect.parentType;
	parentFlags = _priestessSignEffect.parentFlags;
	component = _priestessSignEffect.component;
	fadeIn = _priestessSignEffect.fadeIn;
	fadeOut = _priestessSignEffect.fadeOut;
	deathType = _priestessSignEffect.deathType;
	lifeTime = _priestessSignEffect.lifeTime;
	enableCondition = _priestessSignEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> PriestessSignEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PriestessSignEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RandomEffect::RandomEffect()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RandomEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &effects );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RandomEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RandomEffect* parentPtr = (RandomEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< RandomEffect > parentStateCopier( this, stateManager.states, &RandomEffect::NewRandomEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< RandomEffect > reader( this, stateManager.states, &RandomEffect::NewRandomEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "effects", &effects );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomEffect::Assign( const RandomEffect& _randomEffect )
{
	effects = _randomEffect.effects;
	deathType = _randomEffect.deathType;
	lifeTime = _randomEffect.lifeTime;
	enableCondition = _randomEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> RandomEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFEffectRandom>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitSceneObjectModify::UnitSceneObjectModify() :
		mode( UNITSCENEOBJECTMODIFYMODE_APPEND )
	, visibilityMode( SCENEOBJECTVISIBILITYMODE_ASOBJECT )
{
	sceneObjects.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitSceneObjectModify::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &mode );
	saver.Add( 3, &visibilityMode );
	saver.Add( 4, &sceneObjects );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitSceneObjectModify::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitSceneObjectModify* parentPtr = (UnitSceneObjectModify*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< UnitSceneObjectModify > parentStateCopier( this, stateManager.states, &UnitSceneObjectModify::NewUnitSceneObjectModify );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< UnitSceneObjectModify > reader( this, stateManager.states, &UnitSceneObjectModify::NewUnitSceneObjectModify );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitSceneObjectModify::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "mode", &mode );
	saver.Add( "visibilityMode", &visibilityMode );
	sceneObjects.resize( 3 );
	saver.Add( "sceneObjects", &sceneObjects );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitSceneObjectModify::Assign( const UnitSceneObjectModify& _unitSceneObjectModify )
{
	mode = _unitSceneObjectModify.mode;
	visibilityMode = _unitSceneObjectModify.visibilityMode;
	sceneObjects = _unitSceneObjectModify.sceneObjects;
	deathType = _unitSceneObjectModify.deathType;
	lifeTime = _unitSceneObjectModify.lifeTime;
	enableCondition = _unitSceneObjectModify.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> UnitSceneObjectModify::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<NGameX::PFUnitSceneObjectModify>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
}; // namespace NDb
