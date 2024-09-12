// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Scene/DBScene.h"
#include "../Render/DBRender.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../Render/DBRenderResources.h"
#include "DBEffect.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( EffectBase );
REGISTER_DBRESOURCE( BasicEffect );
REGISTER_DBRESOURCE( BasicEffectStandalone );
REGISTER_DBRESOURCE( CameraShakeSceneComponent );
REGISTER_DBRESOURCE( ChangeMaterialEffect );
REGISTER_DBRESOURCE( PositionRandomizer );
REGISTER_DBRESOURCE( BasicEffectAttached );
REGISTER_DBRESOURCE( ControlledStatusEffect );
REGISTER_DBRESOURCE( EffectGenSceneComponent );
REGISTER_DBRESOURCE( EffectList );
REGISTER_DBRESOURCE( EffectSelector );
REGISTER_DBRESOURCE( EffectsPool );
REGISTER_DBRESOURCE( EnableSCEffect );
REGISTER_DBRESOURCE( GhostEffect );
REGISTER_DBRESOURCE( LightningEffect );
REGISTER_DBRESOURCE( ParticleSceneComponentWithEffect );
REGISTER_DBRESOURCE( CircleRandomizer );
REGISTER_DBRESOURCE( PostFXParams );
REGISTER_DBRESOURCE( RectangleRandomizer );
REGISTER_DBRESOURCE( ScaleColorEffect );
REGISTER_DBRESOURCE( SpringSceneComponent );
REGISTER_DBRESOURCE( TextureAnimated );
REGISTER_DBRESOURCE( TextureRecolorable );
REGISTER_DBRESOURCE( Trace );
REGISTER_DBRESOURCE( TraceGenSceneComponent );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef VISUAL_CUTTED
#include "AnimatedTexture.h"
#include "CameraShakeSceneComponent.h"
#include "ChangeMaterialEffect.h"
#include "EffectGenSceneComponent.h"
#include "EffectsPool.h"
#include "EnableSCEffect.h"
#include "GhostEffect.h"
#include "LightningEffect.h"
#include "ParticleSceneComponentWithEffect.h"
#include "RecolorableTexture.h"
#include "ScaleColorEffect.h"
#include "SpringSceneComponent.h"
#include "TraceGenSceneComponent.h"
#endif // #ifndef VISUAL_CUTTED

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectAlignment value )
{
	switch( value )
	{
		case EFFECTALIGNMENT_NONE:
			return "None";
		case EFFECTALIGNMENT_GROUND:
			return "Ground";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectAlignment", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectAlignment StringToEnum_EEffectAlignment( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectAlignment)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "EFFECTALIGNMENT_NONE" ) == 0 )
		return EFFECTALIGNMENT_NONE;
	if ( strcmp( value, "Ground" ) == 0 || strcmp( value, "EFFECTALIGNMENT_GROUND" ) == 0 )
		return EFFECTALIGNMENT_GROUND;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectAlignment", value ) );
	return EFFECTALIGNMENT_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectAttachType value )
{
	switch( value )
	{
		case EFFECTATTACHTYPE_GENERAL:
			return "General";
		case EFFECTATTACHTYPE_ABOVE:
			return "Above";
		case EFFECTATTACHTYPE_GROUND:
			return "Ground";
		case EFFECTATTACHTYPE_BODY:
			return "Body";
		case EFFECTATTACHTYPE_DEATH:
			return "Death";
		case EFFECTATTACHTYPE_HEAD:
			return "Head";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectAttachType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectAttachType StringToEnum_EEffectAttachType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectAttachType)(NStr::ToInt( value ));
	if ( strcmp( value, "General" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_GENERAL" ) == 0 )
		return EFFECTATTACHTYPE_GENERAL;
	if ( strcmp( value, "Above" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_ABOVE" ) == 0 )
		return EFFECTATTACHTYPE_ABOVE;
	if ( strcmp( value, "Ground" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_GROUND" ) == 0 )
		return EFFECTATTACHTYPE_GROUND;
	if ( strcmp( value, "Body" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_BODY" ) == 0 )
		return EFFECTATTACHTYPE_BODY;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_DEATH" ) == 0 )
		return EFFECTATTACHTYPE_DEATH;
	if ( strcmp( value, "Head" ) == 0 || strcmp( value, "EFFECTATTACHTYPE_HEAD" ) == 0 )
		return EFFECTATTACHTYPE_HEAD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectAttachType", value ) );
	return EFFECTATTACHTYPE_GENERAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectDeathType value )
{
	switch( value )
	{
		case EFFECTDEATHTYPE_MANUAL:
			return "Manual";
		case EFFECTDEATHTYPE_ANIM:
			return "Anim";
		case EFFECTDEATHTYPE_TIME:
			return "Time";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectDeathType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectDeathType StringToEnum_EEffectDeathType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectDeathType)(NStr::ToInt( value ));
	if ( strcmp( value, "Manual" ) == 0 || strcmp( value, "EFFECTDEATHTYPE_MANUAL" ) == 0 )
		return EFFECTDEATHTYPE_MANUAL;
	if ( strcmp( value, "Anim" ) == 0 || strcmp( value, "EFFECTDEATHTYPE_ANIM" ) == 0 )
		return EFFECTDEATHTYPE_ANIM;
	if ( strcmp( value, "Time" ) == 0 || strcmp( value, "EFFECTDEATHTYPE_TIME" ) == 0 )
		return EFFECTDEATHTYPE_TIME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectDeathType", value ) );
	return EFFECTDEATHTYPE_MANUAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectEvent value )
{
	switch( value )
	{
		case EFFECTEVENT_ATTACK:
			return "Attack";
		case EFFECTEVENT_DEATH:
			return "Death";
		case EFFECTEVENT_STOP:
			return "Stop";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectEvent", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectEvent StringToEnum_EEffectEvent( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectEvent)(NStr::ToInt( value ));
	if ( strcmp( value, "Attack" ) == 0 || strcmp( value, "EFFECTEVENT_ATTACK" ) == 0 )
		return EFFECTEVENT_ATTACK;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "EFFECTEVENT_DEATH" ) == 0 )
		return EFFECTEVENT_DEATH;
	if ( strcmp( value, "Stop" ) == 0 || strcmp( value, "EFFECTEVENT_STOP" ) == 0 )
		return EFFECTEVENT_STOP;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectEvent", value ) );
	return EFFECTEVENT_ATTACK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectGenPolicy value )
{
	switch( value )
	{
		case EFFECTGENPOLICY_START:
			return "Start";
		case EFFECTGENPOLICY_DEATH:
			return "Death";
		case EFFECTGENPOLICY_REGULAR:
			return "Regular";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectGenPolicy", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectGenPolicy StringToEnum_EEffectGenPolicy( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectGenPolicy)(NStr::ToInt( value ));
	if ( strcmp( value, "Start" ) == 0 || strcmp( value, "EFFECTGENPOLICY_START" ) == 0 )
		return EFFECTGENPOLICY_START;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "EFFECTGENPOLICY_DEATH" ) == 0 )
		return EFFECTGENPOLICY_DEATH;
	if ( strcmp( value, "Regular" ) == 0 || strcmp( value, "EFFECTGENPOLICY_REGULAR" ) == 0 )
		return EFFECTGENPOLICY_REGULAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectGenPolicy", value ) );
	return EFFECTGENPOLICY_START;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectGroupFlags value )
{
	switch( value )
	{
		case EFFECTGROUPFLAGS_NONE:
			return "None";
		case EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION:
			return "IgnoreColorModification";
		case EFFECTGROUPFLAGS_IGNOREINVISIBILITY:
			return "IgnoreInvisibility";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectGroupFlags StringToEnum_EEffectGroupFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectGroupFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "EFFECTGROUPFLAGS_NONE" ) == 0 )
		return EFFECTGROUPFLAGS_NONE;
	if ( strcmp( value, "IgnoreColorModification" ) == 0 || strcmp( value, "EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION" ) == 0 )
		return EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION;
	if ( strcmp( value, "IgnoreInvisibility" ) == 0 || strcmp( value, "EFFECTGROUPFLAGS_IGNOREINVISIBILITY" ) == 0 )
		return EFFECTGROUPFLAGS_IGNOREINVISIBILITY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectGroupFlags", value ) );
	return EFFECTGROUPFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffects value )
{
	switch( value )
	{
		case EFFECTS_EMPTY:
			return "Empty";
		case EFFECTS_LEVELUP:
			return "LevelUp";
		case EFFECTS_CLICKONTERRAIN:
			return "ClickOnTerrain";
		case EFFECTS_ONDAMAGEFRAGTEAMA:
			return "OnDamageFragTeamA";
		case EFFECTS_ONDAMAGEFRAGTEAMB:
			return "OnDamageFragTeamB";
		case EFFECTS_ONBUILDINGDESTRUCTTEAMA:
			return "OnBuildingDestructTeamA";
		case EFFECTS_ONBUILDINGDESTRUCTTEAMB:
			return "OnBuildingDestructTeamB";
		case EFFECTS_CONTROLLEDHEROAURA:
			return "ControlledHeroAura";
		case EFFECTS_SELECTIONAURASELF:
			return "SelectionAuraSelf";
		case EFFECTS_SELECTIONAURAALLY:
			return "SelectionAuraAlly";
		case EFFECTS_SELECTIONAURAHOSTILE:
			return "SelectionAuraHostile";
		case EFFECTS_PRESELECTIONAURASELF:
			return "PreSelectionAuraSelf";
		case EFFECTS_PRESELECTIONAURAALLY:
			return "PreSelectionAuraAlly";
		case EFFECTS_PRESELECTIONAURAHOSTILE:
			return "PreSelectionAuraHostile";
		case EFFECTS_SELECTIONPICKSELF:
			return "SelectionPickSelf";
		case EFFECTS_SELECTIONPICKALLY:
			return "SelectionPickAlly";
		case EFFECTS_SELECTIONPICKHOSTILE:
			return "SelectionPickHostile";
		case EFFECTS_SELECTIONBUILDINGPICKSELF:
			return "SelectionBuildingPickSelf";
		case EFFECTS_SELECTIONBUILDINGPICKALLY:
			return "SelectionBuildingPickAlly";
		case EFFECTS_SELECTIONBUILDINGPICKHOSTILE:
			return "SelectionBuildingPickHostile";
		case EFFECTS_MARKERALLY:
			return "MarkerAlly";
		case EFFECTS_MARKERHOSTILE:
			return "MarkerHostile";
		case EFFECTS_MARKERCHAT:
			return "MarkerChat";
		case EFFECTS_DEFAULTEFFECT:
			return "DefaultEffect";
		case EFFECTS_GLOWEFFECTA:
			return "GlowEffectA";
		case EFFECTS_GLOWEFFECTB:
			return "GlowEffectB";
		case EFFECTS_ROTATEANIMATIONEFFECT:
			return "RotateAnimationEffect";
		case EFFECTS_MINIGAMESCROLLGIVEN:
			return "MinigameScrollGiven";
		case EFFECTS_TOWERATTACKEFFECTALLY:
			return "TowerAttackEffectAlly";
		case EFFECTS_TOWERATTACKEFFECTENEMY:
			return "TowerAttackEffectEnemy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffects", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffects StringToEnum_EEffects( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffects)(NStr::ToInt( value ));
	if ( strcmp( value, "Empty" ) == 0 || strcmp( value, "EFFECTS_EMPTY" ) == 0 )
		return EFFECTS_EMPTY;
	if ( strcmp( value, "LevelUp" ) == 0 || strcmp( value, "EFFECTS_LEVELUP" ) == 0 )
		return EFFECTS_LEVELUP;
	if ( strcmp( value, "ClickOnTerrain" ) == 0 || strcmp( value, "EFFECTS_CLICKONTERRAIN" ) == 0 )
		return EFFECTS_CLICKONTERRAIN;
	if ( strcmp( value, "OnDamageFragTeamA" ) == 0 || strcmp( value, "EFFECTS_ONDAMAGEFRAGTEAMA" ) == 0 )
		return EFFECTS_ONDAMAGEFRAGTEAMA;
	if ( strcmp( value, "OnDamageFragTeamB" ) == 0 || strcmp( value, "EFFECTS_ONDAMAGEFRAGTEAMB" ) == 0 )
		return EFFECTS_ONDAMAGEFRAGTEAMB;
	if ( strcmp( value, "OnBuildingDestructTeamA" ) == 0 || strcmp( value, "EFFECTS_ONBUILDINGDESTRUCTTEAMA" ) == 0 )
		return EFFECTS_ONBUILDINGDESTRUCTTEAMA;
	if ( strcmp( value, "OnBuildingDestructTeamB" ) == 0 || strcmp( value, "EFFECTS_ONBUILDINGDESTRUCTTEAMB" ) == 0 )
		return EFFECTS_ONBUILDINGDESTRUCTTEAMB;
	if ( strcmp( value, "ControlledHeroAura" ) == 0 || strcmp( value, "EFFECTS_CONTROLLEDHEROAURA" ) == 0 )
		return EFFECTS_CONTROLLEDHEROAURA;
	if ( strcmp( value, "SelectionAuraSelf" ) == 0 || strcmp( value, "EFFECTS_SELECTIONAURASELF" ) == 0 )
		return EFFECTS_SELECTIONAURASELF;
	if ( strcmp( value, "SelectionAuraAlly" ) == 0 || strcmp( value, "EFFECTS_SELECTIONAURAALLY" ) == 0 )
		return EFFECTS_SELECTIONAURAALLY;
	if ( strcmp( value, "SelectionAuraHostile" ) == 0 || strcmp( value, "EFFECTS_SELECTIONAURAHOSTILE" ) == 0 )
		return EFFECTS_SELECTIONAURAHOSTILE;
	if ( strcmp( value, "PreSelectionAuraSelf" ) == 0 || strcmp( value, "EFFECTS_PRESELECTIONAURASELF" ) == 0 )
		return EFFECTS_PRESELECTIONAURASELF;
	if ( strcmp( value, "PreSelectionAuraAlly" ) == 0 || strcmp( value, "EFFECTS_PRESELECTIONAURAALLY" ) == 0 )
		return EFFECTS_PRESELECTIONAURAALLY;
	if ( strcmp( value, "PreSelectionAuraHostile" ) == 0 || strcmp( value, "EFFECTS_PRESELECTIONAURAHOSTILE" ) == 0 )
		return EFFECTS_PRESELECTIONAURAHOSTILE;
	if ( strcmp( value, "SelectionPickSelf" ) == 0 || strcmp( value, "EFFECTS_SELECTIONPICKSELF" ) == 0 )
		return EFFECTS_SELECTIONPICKSELF;
	if ( strcmp( value, "SelectionPickAlly" ) == 0 || strcmp( value, "EFFECTS_SELECTIONPICKALLY" ) == 0 )
		return EFFECTS_SELECTIONPICKALLY;
	if ( strcmp( value, "SelectionPickHostile" ) == 0 || strcmp( value, "EFFECTS_SELECTIONPICKHOSTILE" ) == 0 )
		return EFFECTS_SELECTIONPICKHOSTILE;
	if ( strcmp( value, "SelectionBuildingPickSelf" ) == 0 || strcmp( value, "EFFECTS_SELECTIONBUILDINGPICKSELF" ) == 0 )
		return EFFECTS_SELECTIONBUILDINGPICKSELF;
	if ( strcmp( value, "SelectionBuildingPickAlly" ) == 0 || strcmp( value, "EFFECTS_SELECTIONBUILDINGPICKALLY" ) == 0 )
		return EFFECTS_SELECTIONBUILDINGPICKALLY;
	if ( strcmp( value, "SelectionBuildingPickHostile" ) == 0 || strcmp( value, "EFFECTS_SELECTIONBUILDINGPICKHOSTILE" ) == 0 )
		return EFFECTS_SELECTIONBUILDINGPICKHOSTILE;
	if ( strcmp( value, "MarkerAlly" ) == 0 || strcmp( value, "EFFECTS_MARKERALLY" ) == 0 )
		return EFFECTS_MARKERALLY;
	if ( strcmp( value, "MarkerHostile" ) == 0 || strcmp( value, "EFFECTS_MARKERHOSTILE" ) == 0 )
		return EFFECTS_MARKERHOSTILE;
	if ( strcmp( value, "MarkerChat" ) == 0 || strcmp( value, "EFFECTS_MARKERCHAT" ) == 0 )
		return EFFECTS_MARKERCHAT;
	if ( strcmp( value, "DefaultEffect" ) == 0 || strcmp( value, "EFFECTS_DEFAULTEFFECT" ) == 0 )
		return EFFECTS_DEFAULTEFFECT;
	if ( strcmp( value, "GlowEffectA" ) == 0 || strcmp( value, "EFFECTS_GLOWEFFECTA" ) == 0 )
		return EFFECTS_GLOWEFFECTA;
	if ( strcmp( value, "GlowEffectB" ) == 0 || strcmp( value, "EFFECTS_GLOWEFFECTB" ) == 0 )
		return EFFECTS_GLOWEFFECTB;
	if ( strcmp( value, "RotateAnimationEffect" ) == 0 || strcmp( value, "EFFECTS_ROTATEANIMATIONEFFECT" ) == 0 )
		return EFFECTS_ROTATEANIMATIONEFFECT;
	if ( strcmp( value, "MinigameScrollGiven" ) == 0 || strcmp( value, "EFFECTS_MINIGAMESCROLLGIVEN" ) == 0 )
		return EFFECTS_MINIGAMESCROLLGIVEN;
	if ( strcmp( value, "TowerAttackEffectAlly" ) == 0 || strcmp( value, "EFFECTS_TOWERATTACKEFFECTALLY" ) == 0 )
		return EFFECTS_TOWERATTACKEFFECTALLY;
	if ( strcmp( value, "TowerAttackEffectEnemy" ) == 0 || strcmp( value, "EFFECTS_TOWERATTACKEFFECTENEMY" ) == 0 )
		return EFFECTS_TOWERATTACKEFFECTENEMY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffects", value ) );
	return EFFECTS_EMPTY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEffectSelectionPolicy value )
{
	switch( value )
	{
		case EFFECTSELECTIONPOLICY_RANDOM:
			return "Random";
		case EFFECTSELECTIONPOLICY_SEQUENTIAL:
			return "Sequential";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEffectSelectionPolicy", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEffectSelectionPolicy StringToEnum_EEffectSelectionPolicy( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEffectSelectionPolicy)(NStr::ToInt( value ));
	if ( strcmp( value, "Random" ) == 0 || strcmp( value, "EFFECTSELECTIONPOLICY_RANDOM" ) == 0 )
		return EFFECTSELECTIONPOLICY_RANDOM;
	if ( strcmp( value, "Sequential" ) == 0 || strcmp( value, "EFFECTSELECTIONPOLICY_SEQUENTIAL" ) == 0 )
		return EFFECTSELECTIONPOLICY_SEQUENTIAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEffectSelectionPolicy", value ) );
	return EFFECTSELECTIONPOLICY_RANDOM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EnableSCEffectMode value )
{
	switch( value )
	{
		case NABLESCEFFECTMODE_COMPONENTID:
			return "ComponentId";
		case NABLESCEFFECTMODE_EVENTNAME:
			return "EventName";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EnableSCEffectMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EnableSCEffectMode StringToEnum_EnableSCEffectMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EnableSCEffectMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ComponentId" ) == 0 || strcmp( value, "NABLESCEFFECTMODE_COMPONENTID" ) == 0 )
		return NABLESCEFFECTMODE_COMPONENTID;
	if ( strcmp( value, "EventName" ) == 0 || strcmp( value, "NABLESCEFFECTMODE_EVENTNAME" ) == 0 )
		return NABLESCEFFECTMODE_EVENTNAME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EnableSCEffectMode", value ) );
	return NABLESCEFFECTMODE_COMPONENTID;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectEventAction::EffectEventAction()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectEventAction::operator&( IBinSaver &saver )
{
	saver.Add( 2, &animation );
	saver.Add( 3, &marker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectEventAction::operator&( IXmlSaver &saver )
{
	saver.Add( "animation", &animation );
	saver.Add( "marker", &marker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpringParamDynamics::SpringParamDynamics() :
		speed( 1.0f )
	, maxValue( -1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpringParamDynamics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &speed );
	saver.Add( 3, &maxValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpringParamDynamics::operator&( IXmlSaver &saver )
{
	saver.Add( "speed", &speed );
	saver.Add( "maxValue", &maxValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TraceInfo::TraceInfo()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nodeName );
	saver.Add( 3, &locatorName );
	saver.Add( 4, &traces );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "nodeName", &nodeName );
	saver.Add( "locatorName", &locatorName );
	saver.Add( "traces", &traces );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectBase::EffectBase() :
		deathType( EFFECTDEATHTYPE_MANUAL )
	, lifeTime( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectBase::operator&( IBinSaver &saver )
{
	saver.Add( 2, &deathType );
	saver.Add( 3, &lifeTime );
	saver.Add( 4, &enableCondition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectBase::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectBase* parentPtr = (EffectBase*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< EffectBase > parentStateCopier( this, stateManager.states, &EffectBase::NewEffectBase );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< EffectBase > reader( this, stateManager.states, &EffectBase::NewEffectBase );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectBase::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "deathType", &deathType );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "enableCondition", &enableCondition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectBase::Assign( const EffectBase& _effectBase )
{
	deathType = _effectBase.deathType;
	lifeTime = _effectBase.lifeTime;
	enableCondition = _effectBase.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> EffectBase::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return ( CObj<PF_Core::BasicEffect> )(0);
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicEffect::BasicEffect() :
		fadeIn( 0.0f )
	, fadeOut( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &component );
	saver.Add( 3, &fadeIn );
	saver.Add( 4, &fadeOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicEffect* parentPtr = (BasicEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< BasicEffect > parentStateCopier( this, stateManager.states, &BasicEffect::NewBasicEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< BasicEffect > reader( this, stateManager.states, &BasicEffect::NewBasicEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "component", &component );
	saver.Add( "fadeIn", &fadeIn );
	saver.Add( "fadeOut", &fadeOut );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::Assign( const BasicEffect& _basicEffect )
{
	component = _basicEffect.component;
	fadeIn = _basicEffect.fadeIn;
	fadeOut = _basicEffect.fadeOut;
	deathType = _basicEffect.deathType;
	lifeTime = _basicEffect.lifeTime;
	enableCondition = _basicEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> BasicEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return ( CObj<PF_Core::BasicEffect> )(0);
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicEffectStandalone::BasicEffectStandalone() :
		visibilityLimited( false )
	, visibleTime( 0.0f )
	, isVisibleUnderWarfog( false )
	, parentType( "General" )
	, parentFlags( STANDALONEEFFECTFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffectStandalone::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicEffect*)this );
	saver.Add( 2, &visibilityLimited );
	saver.Add( 3, &visibleTime );
	saver.Add( 4, &isVisibleUnderWarfog );
	saver.Add( 5, &parentType );
	saver.Add( 6, &parentFlags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffectStandalone::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicEffectStandalone* parentPtr = (BasicEffectStandalone*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< BasicEffectStandalone > parentStateCopier( this, stateManager.states, &BasicEffectStandalone::NewBasicEffectStandalone );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< BasicEffectStandalone > reader( this, stateManager.states, &BasicEffectStandalone::NewBasicEffectStandalone );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::SerializeSelf( IXmlSaver &saver )
{
	BasicEffect::SerializeSelf( saver );
	saver.Add( "visibilityLimited", &visibilityLimited );
	saver.Add( "visibleTime", &visibleTime );
	saver.Add( "isVisibleUnderWarfog", &isVisibleUnderWarfog );
	saver.Add( "parentType", &parentType );
	saver.Add( "parentFlags", &parentFlags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::Assign( const BasicEffectStandalone& _basicEffectStandalone )
{
	visibilityLimited = _basicEffectStandalone.visibilityLimited;
	visibleTime = _basicEffectStandalone.visibleTime;
	isVisibleUnderWarfog = _basicEffectStandalone.isVisibleUnderWarfog;
	parentType = _basicEffectStandalone.parentType;
	parentFlags = _basicEffectStandalone.parentFlags;
	component = _basicEffectStandalone.component;
	fadeIn = _basicEffectStandalone.fadeIn;
	fadeOut = _basicEffectStandalone.fadeOut;
	deathType = _basicEffectStandalone.deathType;
	lifeTime = _basicEffectStandalone.lifeTime;
	enableCondition = _basicEffectStandalone.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> BasicEffectStandalone::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::BasicEffectStandalone>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraShakeSceneComponent::CameraShakeSceneComponent() :
		range( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CameraShakeSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &displacement );
	saver.Add( 3, &range );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CameraShakeSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CameraShakeSceneComponent* parentPtr = (CameraShakeSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CameraShakeSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "displacement", &displacement );
	saver.Add( "range", &range );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CameraShakeSceneComponent::Assign( const CameraShakeSceneComponent& _cameraShakeSceneComponent )
{
	displacement = _cameraShakeSceneComponent.displacement;
	range = _cameraShakeSceneComponent.range;
	locatorList = _cameraShakeSceneComponent.locatorList;
	orientation = _cameraShakeSceneComponent.orientation;
	groupFlags = _cameraShakeSceneComponent.groupFlags;
	attached = _cameraShakeSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> CameraShakeSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<PF_Core::CameraShakeSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeMaterialEffect::ChangeMaterialEffect() :
		fadeInTime( 1.0f )
	, fadeOutTime( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeMaterialEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &fadeInTime );
	saver.Add( 3, &fadeOutTime );
	saver.Add( 4, &materials );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeMaterialEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeMaterialEffect* parentPtr = (ChangeMaterialEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< ChangeMaterialEffect > parentStateCopier( this, stateManager.states, &ChangeMaterialEffect::NewChangeMaterialEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< ChangeMaterialEffect > reader( this, stateManager.states, &ChangeMaterialEffect::NewChangeMaterialEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeMaterialEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "fadeInTime", &fadeInTime );
	saver.Add( "fadeOutTime", &fadeOutTime );
	saver.Add( "materials", &materials );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeMaterialEffect::Assign( const ChangeMaterialEffect& _changeMaterialEffect )
{
	fadeInTime = _changeMaterialEffect.fadeInTime;
	fadeOutTime = _changeMaterialEffect.fadeOutTime;
	materials = _changeMaterialEffect.materials;
	deathType = _changeMaterialEffect.deathType;
	lifeTime = _changeMaterialEffect.lifeTime;
	enableCondition = _changeMaterialEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> ChangeMaterialEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::ChangeMaterialEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PositionRandomizer::PositionRandomizer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PositionRandomizer::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PositionRandomizer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PositionRandomizer* parentPtr = (PositionRandomizer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PositionRandomizer::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PositionRandomizer::Assign( const PositionRandomizer& _positionRandomizer )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicEffectAttached::BasicEffectAttached() :
		attachType( "General" )
	, attachFlags( ATTACHFLAGS_NONE )
	, groupFlags( EFFECTGROUPFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffectAttached::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicEffect*)this );
	saver.Add( 2, &attachType );
	saver.Add( 3, &attachFlags );
	saver.Add( 4, &groupFlags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicEffectAttached::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicEffectAttached* parentPtr = (BasicEffectAttached*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< BasicEffectAttached > parentStateCopier( this, stateManager.states, &BasicEffectAttached::NewBasicEffectAttached );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< BasicEffectAttached > reader( this, stateManager.states, &BasicEffectAttached::NewBasicEffectAttached );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SerializeSelf( IXmlSaver &saver )
{
	BasicEffect::SerializeSelf( saver );
	saver.Add( "attachType", &attachType );
	saver.Add( "attachFlags", &attachFlags );
	saver.Add( "groupFlags", &groupFlags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::Assign( const BasicEffectAttached& _basicEffectAttached )
{
	attachType = _basicEffectAttached.attachType;
	attachFlags = _basicEffectAttached.attachFlags;
	groupFlags = _basicEffectAttached.groupFlags;
	component = _basicEffectAttached.component;
	fadeIn = _basicEffectAttached.fadeIn;
	fadeOut = _basicEffectAttached.fadeOut;
	deathType = _basicEffectAttached.deathType;
	lifeTime = _basicEffectAttached.lifeTime;
	enableCondition = _basicEffectAttached.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> BasicEffectAttached::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::BasicEffectAttached>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ControlledStatusEffect::ControlledStatusEffect()
{
	eventActions.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ControlledStatusEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicEffectAttached*)this );
	saver.Add( 2, &eventActions );
	saver.Add( 3, &onDeathEffect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ControlledStatusEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ControlledStatusEffect* parentPtr = (ControlledStatusEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< ControlledStatusEffect > parentStateCopier( this, stateManager.states, &ControlledStatusEffect::NewControlledStatusEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< ControlledStatusEffect > reader( this, stateManager.states, &ControlledStatusEffect::NewControlledStatusEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ControlledStatusEffect::SerializeSelf( IXmlSaver &saver )
{
	BasicEffectAttached::SerializeSelf( saver );
	eventActions.resize( 3 );
	saver.Add( "eventActions", &eventActions );
	saver.Add( "onDeathEffect", &onDeathEffect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ControlledStatusEffect::Assign( const ControlledStatusEffect& _controlledStatusEffect )
{
	eventActions = _controlledStatusEffect.eventActions;
	onDeathEffect = _controlledStatusEffect.onDeathEffect;
	attachType = _controlledStatusEffect.attachType;
	attachFlags = _controlledStatusEffect.attachFlags;
	groupFlags = _controlledStatusEffect.groupFlags;
	component = _controlledStatusEffect.component;
	fadeIn = _controlledStatusEffect.fadeIn;
	fadeOut = _controlledStatusEffect.fadeOut;
	deathType = _controlledStatusEffect.deathType;
	lifeTime = _controlledStatusEffect.lifeTime;
	enableCondition = _controlledStatusEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> ControlledStatusEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::ControlledStatusEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectGenSceneComponent::EffectGenSceneComponent() :
		generationPolicy( EFFECTGENPOLICY_START )
	, minPeriod( 1.0f )
	, maxPeriod( 1.0f )
	, randomizeDirection( false )
	, alignment( EFFECTALIGNMENT_NONE )
	, offset( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectGenSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &effect );
	saver.Add( 3, &generationPolicy );
	saver.Add( 4, &minPeriod );
	saver.Add( 5, &maxPeriod );
	saver.Add( 6, &posRandomizer );
	saver.Add( 7, &randomizeDirection );
	saver.Add( 8, &alignment );
	saver.Add( 9, &offset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectGenSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectGenSceneComponent* parentPtr = (EffectGenSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectGenSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "effect", &effect );
	saver.Add( "generationPolicy", &generationPolicy );
	saver.Add( "minPeriod", &minPeriod );
	saver.Add( "maxPeriod", &maxPeriod );
	saver.Add( "posRandomizer", &posRandomizer );
	saver.Add( "randomizeDirection", &randomizeDirection );
	saver.Add( "alignment", &alignment );
	saver.Add( "offset", &offset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectGenSceneComponent::Assign( const EffectGenSceneComponent& _effectGenSceneComponent )
{
	effect = _effectGenSceneComponent.effect;
	generationPolicy = _effectGenSceneComponent.generationPolicy;
	minPeriod = _effectGenSceneComponent.minPeriod;
	maxPeriod = _effectGenSceneComponent.maxPeriod;
	posRandomizer = _effectGenSceneComponent.posRandomizer;
	randomizeDirection = _effectGenSceneComponent.randomizeDirection;
	alignment = _effectGenSceneComponent.alignment;
	offset = _effectGenSceneComponent.offset;
	locatorList = _effectGenSceneComponent.locatorList;
	orientation = _effectGenSceneComponent.orientation;
	groupFlags = _effectGenSceneComponent.groupFlags;
	attached = _effectGenSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> EffectGenSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<PF_Core::EffectGenSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectList::EffectList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectList::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &effects );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectList::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectList* parentPtr = (EffectList*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< EffectList > parentStateCopier( this, stateManager.states, &EffectList::NewEffectList );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< EffectList > reader( this, stateManager.states, &EffectList::NewEffectList );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectList::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "effects", &effects );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectList::Assign( const EffectList& _effectList )
{
	effects = _effectList.effects;
	deathType = _effectList.deathType;
	lifeTime = _effectList.lifeTime;
	enableCondition = _effectList.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> EffectList::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return ( CObj<PF_Core::BasicEffect> )(0);
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectSelector::EffectSelector() :
		selectionPolicy( EFFECTSELECTIONPOLICY_RANDOM )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectSelector::operator&( IBinSaver &saver )
{
	saver.Add( 2, &effects );
	saver.Add( 3, &selectionPolicy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectSelector* parentPtr = (EffectSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectSelector::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "effects", &effects );
	saver.Add( "selectionPolicy", &selectionPolicy );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectSelector::Assign( const EffectSelector& _effectSelector )
{
	effects = _effectSelector.effects;
	selectionPolicy = _effectSelector.selectionPolicy;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectsPool::EffectsPool()
{
	effectsList.resize( 30 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectsPool::operator&( IBinSaver &saver )
{
	saver.Add( 2, &effectsList );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectsPool::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EffectsPool* parentPtr = (EffectsPool*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectsPool::SerializeSelf( IXmlSaver &saver )
{
	effectsList.resize( 30 );
	saver.Add( "effectsList", &effectsList );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectsPool::Assign( const EffectsPool& _effectsPool )
{
	effectsList = _effectsPool.effectsList;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EnableSCEffect::EnableSCEffect() :
		mode( NABLESCEFFECTMODE_COMPONENTID )
	, enable( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableSCEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &nameStart );
	saver.Add( 3, &nameStop );
	saver.Add( 4, &mode );
	saver.Add( 5, &enable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EnableSCEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EnableSCEffect* parentPtr = (EnableSCEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< EnableSCEffect > parentStateCopier( this, stateManager.states, &EnableSCEffect::NewEnableSCEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< EnableSCEffect > reader( this, stateManager.states, &EnableSCEffect::NewEnableSCEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableSCEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "nameStart", &nameStart );
	saver.Add( "nameStop", &nameStop );
	saver.Add( "mode", &mode );
	saver.Add( "enable", &enable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableSCEffect::Assign( const EnableSCEffect& _enableSCEffect )
{
	nameStart = _enableSCEffect.nameStart;
	nameStop = _enableSCEffect.nameStop;
	mode = _enableSCEffect.mode;
	enable = _enableSCEffect.enable;
	deathType = _enableSCEffect.deathType;
	lifeTime = _enableSCEffect.lifeTime;
	enableCondition = _enableSCEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> EnableSCEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::EnableSCEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GhostEffect::GhostEffect()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GhostEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GhostEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GhostEffect* parentPtr = (GhostEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< GhostEffect > parentStateCopier( this, stateManager.states, &GhostEffect::NewGhostEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< GhostEffect > reader( this, stateManager.states, &GhostEffect::NewGhostEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostEffect::Assign( const GhostEffect& _ghostEffect )
{
	deathType = _ghostEffect.deathType;
	lifeTime = _ghostEffect.lifeTime;
	enableCondition = _ghostEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> GhostEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::GhostEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LightningEffect::LightningEffect() :
		controlledVisibility( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &component );
	saver.Add( 3, &controlledVisibility );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LightningEffect* parentPtr = (LightningEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< LightningEffect > parentStateCopier( this, stateManager.states, &LightningEffect::NewLightningEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< LightningEffect > reader( this, stateManager.states, &LightningEffect::NewLightningEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightningEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "component", &component );
	saver.Add( "controlledVisibility", &controlledVisibility );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightningEffect::Assign( const LightningEffect& _lightningEffect )
{
	component = _lightningEffect.component;
	controlledVisibility = _lightningEffect.controlledVisibility;
	deathType = _lightningEffect.deathType;
	lifeTime = _lightningEffect.lifeTime;
	enableCondition = _lightningEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> LightningEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::LightningEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleSceneComponentWithEffect::ParticleSceneComponentWithEffect()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleSceneComponentWithEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBParticleSceneComponent*)this );
	saver.Add( 2, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleSceneComponentWithEffect::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ParticleSceneComponentWithEffect* parentPtr = (ParticleSceneComponentWithEffect*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponentWithEffect::SerializeSelf( IXmlSaver &saver )
{
	DBParticleSceneComponent::SerializeSelf( saver );
	saver.Add( "effect", &effect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponentWithEffect::Assign( const ParticleSceneComponentWithEffect& _particleSceneComponentWithEffect )
{
	effect = _particleSceneComponentWithEffect.effect;
	camoffset = _particleSceneComponentWithEffect.camoffset;
	orient = _particleSceneComponentWithEffect.orient;
	pivot = _particleSceneComponentWithEffect.pivot;
	leaveParticlesWhereStarted = _particleSceneComponentWithEffect.leaveParticlesWhereStarted;
	deathFadeOutTime = _particleSceneComponentWithEffect.deathFadeOutTime;
	material = _particleSceneComponentWithEffect.material;
	uvPairs = _particleSceneComponentWithEffect.uvPairs;
	aabb.minX = _particleSceneComponentWithEffect.aabb.minX;
	aabb.maxX = _particleSceneComponentWithEffect.aabb.maxX;
	aabb.minY = _particleSceneComponentWithEffect.aabb.minY;
	aabb.maxY = _particleSceneComponentWithEffect.aabb.maxY;
	aabb.minZ = _particleSceneComponentWithEffect.aabb.minZ;
	aabb.maxZ = _particleSceneComponentWithEffect.aabb.maxZ;
	fxFileName = _particleSceneComponentWithEffect.fxFileName;
	srcFileName = _particleSceneComponentWithEffect.srcFileName;
	locatorList = _particleSceneComponentWithEffect.locatorList;
	orientation = _particleSceneComponentWithEffect.orientation;
	groupFlags = _particleSceneComponentWithEffect.groupFlags;
	attached = _particleSceneComponentWithEffect.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> ParticleSceneComponentWithEffect::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<PF_Core::ParticleSceneComponentWithEffect>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CircleRandomizer::CircleRandomizer() :
		radius( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CircleRandomizer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (PositionRandomizer*)this );
	saver.Add( 2, &radius );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CircleRandomizer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CircleRandomizer* parentPtr = (CircleRandomizer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CircleRandomizer::SerializeSelf( IXmlSaver &saver )
{
	PositionRandomizer::SerializeSelf( saver );
	saver.Add( "radius", &radius );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CircleRandomizer::Assign( const CircleRandomizer& _circleRandomizer )
{
	radius = _circleRandomizer.radius;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PostFXParams::PostFXParams() :
		mipMapLodBias( 0.0f )
{
	fullScreenFXParams.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PostFXParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fullScreenFXParams );
	saver.Add( 3, &mipMapLodBias );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PostFXParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PostFXParams* parentPtr = (PostFXParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PostFXParams::SerializeSelf( IXmlSaver &saver )
{
	fullScreenFXParams.resize( 3 );
	saver.Add( "fullScreenFXParams", &fullScreenFXParams );
	saver.Add( "mipMapLodBias", &mipMapLodBias );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PostFXParams::Assign( const PostFXParams& _postFXParams )
{
	fullScreenFXParams = _postFXParams.fullScreenFXParams;
	mipMapLodBias = _postFXParams.mipMapLodBias;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RectangleRandomizer::RectangleRandomizer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RectangleRandomizer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (PositionRandomizer*)this );
	saver.Add( 2, &min );
	saver.Add( 3, &max );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RectangleRandomizer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RectangleRandomizer* parentPtr = (RectangleRandomizer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RectangleRandomizer::SerializeSelf( IXmlSaver &saver )
{
	PositionRandomizer::SerializeSelf( saver );
	saver.Add( "min", &min );
	saver.Add( "max", &max );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RectangleRandomizer::Assign( const RectangleRandomizer& _rectangleRandomizer )
{
	min = _rectangleRandomizer.min;
	max = _rectangleRandomizer.max;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScaleColorEffect::ScaleColorEffect() :
		scale( 1.0f )
	, blendMode( BLENDMODE_LERPBYALPHA )
	, fadeInTime( 1.0f )
	, fadeOutTime( 1.0f )
	, fullRecolor( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScaleColorEffect::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EffectBase*)this );
	saver.Add( 2, &scale );
	saver.Add( 3, &colorMul );
	saver.Add( 4, &colorAdd );
	saver.Add( 5, &blendMode );
	saver.Add( 6, &scaleIn );
	saver.Add( 7, &scaleOut );
	saver.Add( 8, &fadeInTime );
	saver.Add( 9, &fadeOutTime );
	saver.Add( 10, &fullRecolor );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScaleColorEffect::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScaleColorEffect* parentPtr = (ScaleColorEffect*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< ScaleColorEffect > parentStateCopier( this, stateManager.states, &ScaleColorEffect::NewScaleColorEffect );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< ScaleColorEffect > reader( this, stateManager.states, &ScaleColorEffect::NewScaleColorEffect );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScaleColorEffect::SerializeSelf( IXmlSaver &saver )
{
	EffectBase::SerializeSelf( saver );
	saver.Add( "scale", &scale );
	saver.Add( "colorMul", &colorMul );
	saver.Add( "colorAdd", &colorAdd );
	saver.Add( "blendMode", &blendMode );
	saver.Add( "scaleIn", &scaleIn );
	saver.Add( "scaleOut", &scaleOut );
	saver.Add( "fadeInTime", &fadeInTime );
	saver.Add( "fadeOutTime", &fadeOutTime );
	saver.Add( "fullRecolor", &fullRecolor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScaleColorEffect::Assign( const ScaleColorEffect& _scaleColorEffect )
{
	scale = _scaleColorEffect.scale;
	colorMul = _scaleColorEffect.colorMul;
	colorAdd = _scaleColorEffect.colorAdd;
	blendMode = _scaleColorEffect.blendMode;
	scaleIn = _scaleColorEffect.scaleIn;
	scaleOut = _scaleColorEffect.scaleOut;
	fadeInTime = _scaleColorEffect.fadeInTime;
	fadeOutTime = _scaleColorEffect.fadeOutTime;
	fullRecolor = _scaleColorEffect.fullRecolor;
	deathType = _scaleColorEffect.deathType;
	lifeTime = _scaleColorEffect.lifeTime;
	enableCondition = _scaleColorEffect.enableCondition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<PF_Core::BasicEffect> ScaleColorEffect::Retrieve( PF_Core::ObjectsPool &pool ) const
{
	return PF_Core::CreateEffectFromPool<PF_Core::ScaleColorEffect>( *this, pool );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpringSceneComponent::SpringSceneComponent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpringSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &posDynamics );
	saver.Add( 3, &rotDynamics );
	saver.Add( 4, &scaleDynamics );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpringSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpringSceneComponent* parentPtr = (SpringSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpringSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "posDynamics", &posDynamics );
	saver.Add( "rotDynamics", &rotDynamics );
	saver.Add( "scaleDynamics", &scaleDynamics );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpringSceneComponent::Assign( const SpringSceneComponent& _springSceneComponent )
{
	posDynamics.speed = _springSceneComponent.posDynamics.speed;
	posDynamics.maxValue = _springSceneComponent.posDynamics.maxValue;
	rotDynamics.speed = _springSceneComponent.rotDynamics.speed;
	rotDynamics.maxValue = _springSceneComponent.rotDynamics.maxValue;
	scaleDynamics.speed = _springSceneComponent.scaleDynamics.speed;
	scaleDynamics.maxValue = _springSceneComponent.scaleDynamics.maxValue;
	locatorList = _springSceneComponent.locatorList;
	orientation = _springSceneComponent.orientation;
	groupFlags = _springSceneComponent.groupFlags;
	attached = _springSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> SpringSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<PF_Core::SpringSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureAnimated::TextureAnimated() :
		animCount( 1 )
	, animSpeed( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureAnimated::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Texture*)this );
	saver.Add( 2, &animCount );
	saver.Add( 3, &animSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureAnimated::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TextureAnimated* parentPtr = (TextureAnimated*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureAnimated::SerializeSelf( IXmlSaver &saver )
{
	Texture::SerializeSelf( saver );
	saver.Add( "animCount", &animCount );
	saver.Add( "animSpeed", &animSpeed );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureAnimated::Assign( const TextureAnimated& _textureAnimated )
{
	animCount = _textureAnimated.animCount;
	animSpeed = _textureAnimated.animSpeed;
	srcFileName = _textureAnimated.srcFileName;
	textureFileName = _textureAnimated.textureFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<Render::Texture> TextureAnimated::Load() const
{
	return PF_Core::LoadAnimatedTexture( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Render::Texture> TextureAnimated::LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const
{
	return PF_Core::LoadAnimatedTextureIntoPool( *this, canBeVisualDegrade, texturePoolId );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureRecolorable::TextureRecolorable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureRecolorable::operator&( IBinSaver &saver )
{
	saver.Add( 1, (TextureBase*)this );
	saver.Add( 2, &main );
	saver.Add( 3, &mask );
	saver.Add( 4, &baseRGB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureRecolorable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TextureRecolorable* parentPtr = (TextureRecolorable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureRecolorable::SerializeSelf( IXmlSaver &saver )
{
	TextureBase::SerializeSelf( saver );
	saver.Add( "main", &main );
	saver.Add( "mask", &mask );
	saver.Add( "baseRGB", &baseRGB );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureRecolorable::Assign( const TextureRecolorable& _textureRecolorable )
{
	main = _textureRecolorable.main;
	mask = _textureRecolorable.mask;
	baseRGB = _textureRecolorable.baseRGB;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<Render::Texture> TextureRecolorable::Load() const
{
	return PF_Core::LoadRecolorableTexture( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Render::Texture> TextureRecolorable::LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const
{
	return PF_Core::LoadRecolorableTextureInPool( *this, canBeVisualDegrade, texturePoolId );
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Trace::Trace()
{
	terrainTrace.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Trace::operator&( IBinSaver &saver )
{
	saver.Add( 2, &waterTrace );
	saver.Add( 3, &terrainTrace );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Trace::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Trace* parentPtr = (Trace*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Trace::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "waterTrace", &waterTrace );
	terrainTrace.resize( 3 );
	saver.Add( "terrainTrace", &terrainTrace );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Trace::Assign( const Trace& _trace )
{
	waterTrace = _trace.waterTrace;
	terrainTrace = _trace.terrainTrace;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TraceGenSceneComponent::TraceGenSceneComponent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceGenSceneComponent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DBSceneComponent*)this );
	saver.Add( 2, &defaultTraces );
	saver.Add( 3, &defaultLocatorName );
	saver.Add( 4, &traceByAnim );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceGenSceneComponent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TraceGenSceneComponent* parentPtr = (TraceGenSceneComponent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraceGenSceneComponent::SerializeSelf( IXmlSaver &saver )
{
	DBSceneComponent::SerializeSelf( saver );
	saver.Add( "defaultTraces", &defaultTraces );
	saver.Add( "defaultLocatorName", &defaultLocatorName );
	saver.Add( "traceByAnim", &traceByAnim );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraceGenSceneComponent::Assign( const TraceGenSceneComponent& _traceGenSceneComponent )
{
	defaultTraces = _traceGenSceneComponent.defaultTraces;
	defaultLocatorName = _traceGenSceneComponent.defaultLocatorName;
	traceByAnim = _traceGenSceneComponent.traceByAnim;
	locatorList = _traceGenSceneComponent.locatorList;
	orientation = _traceGenSceneComponent.orientation;
	groupFlags = _traceGenSceneComponent.groupFlags;
	attached = _traceGenSceneComponent.attached;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<NScene::SceneComponent> TraceGenSceneComponent::Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const
{
	return NScene::CreateSceneComponent<PF_Core::TraceGenSceneComponent>( *this, creator, pAttached, transform );
}
#endif // #ifndef VISUAL_CUTTED
}; // namespace NDb
