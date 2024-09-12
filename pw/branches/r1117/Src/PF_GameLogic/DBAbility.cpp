// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "../Render/DBRender.h"
#include "../PF_Core/DBEffect.h"
#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/DBAnimations.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBConsumable.h"
#include "../Scene/DBScene.h"
#include "DBAbility.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Spell );
BASIC_REGISTER_DBRESOURCE( BaseApplicator );
BASIC_REGISTER_DBRESOURCE( BuffApplicator );
REGISTER_DBRESOURCE( AbilityUpgradeApplicator );
REGISTER_DBRESOURCE( AbilityUpgradeTechApplicator );
REGISTER_DBRESOURCE( AbsorbShieldApplicator );
REGISTER_DBRESOURCE( AddApplicatorDuration );
REGISTER_DBRESOURCE( AddNaftaApplicator );
REGISTER_DBRESOURCE( AlternativeActivity );
REGISTER_DBRESOURCE( AlternativeTarget );
REGISTER_DBRESOURCE( ApplicatorNameOverrider );
REGISTER_DBRESOURCE( TargetSelector );
REGISTER_DBRESOURCE( ApplicatorsList );
REGISTER_DBRESOURCE( MultipleTargetSelector );
REGISTER_DBRESOURCE( MultipleTargetSelectorFiltered );
REGISTER_DBRESOURCE( AttackTargetApplicator );
REGISTER_DBRESOURCE( AttractApplicator );
REGISTER_DBRESOURCE( AuraApplicator );
REGISTER_DBRESOURCE( AbilityEndApplicator );
REGISTER_DBRESOURCE( Ability );
REGISTER_DBRESOURCE( MicroAI );
REGISTER_DBRESOURCE( BetweenUnitsTargetSelector );
REGISTER_DBRESOURCE( BounceApplicator );
REGISTER_DBRESOURCE( AbilityModApplicator );
REGISTER_DBRESOURCE( CapsuleTargetSelector );
REGISTER_DBRESOURCE( CastLimitation );
REGISTER_DBRESOURCE( ChainLightningApplicator );
REGISTER_DBRESOURCE( ChangeAnimationApplicator );
REGISTER_DBRESOURCE( ChangeAnimSetApplicator );
REGISTER_DBRESOURCE( ChangeBaseAttackApplicator );
REGISTER_DBRESOURCE( ChangeHeroStateApplicator );
REGISTER_DBRESOURCE( ChangeStateApplicator );
REGISTER_DBRESOURCE( ChannellingApplicator );
REGISTER_DBRESOURCE( CheckConditionTargetSelector );
REGISTER_DBRESOURCE( CloneHeroApplicator );
REGISTER_DBRESOURCE( SingleTargetSelector );
REGISTER_DBRESOURCE( ConditionCastLimitation );
REGISTER_DBRESOURCE( ConditionFormula );
REGISTER_DBRESOURCE( ConditionTargetSelector );
REGISTER_DBRESOURCE( ConvertTargetToLand );
REGISTER_DBRESOURCE( CountingTargetSelector );
REGISTER_DBRESOURCE( CreateGlyphApplicator );
REGISTER_DBRESOURCE( CreepBehaviourChangeApplicator );
REGISTER_DBRESOURCE( DamageApplicator );
REGISTER_DBRESOURCE( DamageReflectApplicator );
REGISTER_DBRESOURCE( DamagingLinksTargetSelector );
REGISTER_DBRESOURCE( DayNightTransitionApplicator );
REGISTER_DBRESOURCE( DealedDamageConverterApplicator );
REGISTER_DBRESOURCE( DefaultFormulas );
REGISTER_DBRESOURCE( DelayTargetSelector );
REGISTER_DBRESOURCE( DelegateDamageApplicator );
BASIC_REGISTER_DBRESOURCE( Dispatch );
REGISTER_DBRESOURCE( DispatchContinuous );
REGISTER_DBRESOURCE( DispatchByTime );
REGISTER_DBRESOURCE( DispatchCursor );
REGISTER_DBRESOURCE( DispatchImmediate );
REGISTER_DBRESOURCE( DispatchLinear );
REGISTER_DBRESOURCE( DispatchLinearWithLink );
REGISTER_DBRESOURCE( DispatchRockmanMace );
REGISTER_DBRESOURCE( DispellApplicator );
REGISTER_DBRESOURCE( DispellCastLimitation );
REGISTER_DBRESOURCE( DropTreeApplicator );
BASIC_REGISTER_DBRESOURCE( EventProcessorBase );
REGISTER_DBRESOURCE( EventProcessorApplicatorApplied );
REGISTER_DBRESOURCE( EventProcessorAbilityManacostTransformer );
REGISTER_DBRESOURCE( EventProcessorCancelDispatch );
REGISTER_DBRESOURCE( EventProcessorCondition );
REGISTER_DBRESOURCE( EventProcessorDamageTransformer );
REGISTER_DBRESOURCE( EventProcessorGroup );
REGISTER_DBRESOURCE( EventProcessorIncomingDamage );
REGISTER_DBRESOURCE( EventProcessorLastHit );
REGISTER_DBRESOURCE( EventProcessorOnConsumableObtained );
REGISTER_DBRESOURCE( EventProcessorOnDeath );
REGISTER_DBRESOURCE( EventProcessorOnTarget );
REGISTER_DBRESOURCE( EventProcessorOnUseAbilityForceStrike );
REGISTER_DBRESOURCE( EventProcessorOutgoingDamage );
REGISTER_DBRESOURCE( EventProcessorPickupGlyph );
REGISTER_DBRESOURCE( EventProcessorUnitDieNearMe );
REGISTER_DBRESOURCE( EyeApplicator );
REGISTER_DBRESOURCE( FilterTargetSelector );
REGISTER_DBRESOURCE( FirstTargetSelector );
REGISTER_DBRESOURCE( FixToCenterTargetSelector );
REGISTER_DBRESOURCE( FlagsApplicator );
REGISTER_DBRESOURCE( FlyApplicator );
REGISTER_DBRESOURCE( ForAllTargetsApplicator );
REGISTER_DBRESOURCE( FountainTargetSelector );
REGISTER_DBRESOURCE( FXApplicator );
REGISTER_DBRESOURCE( GhostMoveApplicator );
REGISTER_DBRESOURCE( GiveConsumable );
REGISTER_DBRESOURCE( HealApplicator );
REGISTER_DBRESOURCE( HeroEnumerator );
REGISTER_DBRESOURCE( HighlanderA1TargetSelector );
REGISTER_DBRESOURCE( InvalidAbilityTargetApplicator );
REGISTER_DBRESOURCE( InvisibilityApplicator );
REGISTER_DBRESOURCE( KickAwayApplicator );
REGISTER_DBRESOURCE( KillApplicator );
REGISTER_DBRESOURCE( ListOfTargetSelectors );
REGISTER_DBRESOURCE( LockTilesApplicator );
REGISTER_DBRESOURCE( MainBuildingTargetSelector );
REGISTER_DBRESOURCE( MarkerApplicator );
REGISTER_DBRESOURCE( MaximizingTargetSelector );
REGISTER_DBRESOURCE( BasicMicroAI );
REGISTER_DBRESOURCE( ModifyTerrainApplicator );
REGISTER_DBRESOURCE( MountApplicator );
REGISTER_DBRESOURCE( MovementControlApplicator );
REGISTER_DBRESOURCE( MoveToApplicator );
REGISTER_DBRESOURCE( ApplicatorRecipientsTargetSelector );
REGISTER_DBRESOURCE( AreaTargetSelector );
REGISTER_DBRESOURCE( MultipleTargetSelectorMicroAI );
REGISTER_DBRESOURCE( NaftaTransferApplicator );
REGISTER_DBRESOURCE( NearestInAreaTargetSelector );
REGISTER_DBRESOURCE( NearestTargetSelector );
REGISTER_DBRESOURCE( NotTargetOfSameAbilitySelector );
REGISTER_DBRESOURCE( OnDamageApplicator );
REGISTER_DBRESOURCE( PermanentStatModApplicator );
REGISTER_DBRESOURCE( PickupChannelingApplicator );
REGISTER_DBRESOURCE( PointTargetSelector );
REGISTER_DBRESOURCE( PositionCastLimitation );
REGISTER_DBRESOURCE( ProgramApplicator );
REGISTER_DBRESOURCE( RaiseFlagApplicator );
REGISTER_DBRESOURCE( RefreshCooldownApplicator );
REGISTER_DBRESOURCE( RelativeUnitTargetSelector );
REGISTER_DBRESOURCE( ResurrectApplicator );
REGISTER_DBRESOURCE( ScaleControlApplicator );
REGISTER_DBRESOURCE( SceneObjectChangeApplicator );
REGISTER_DBRESOURCE( SectorTargetSelector );
REGISTER_DBRESOURCE( SelectApplicatorTarget );
REGISTER_DBRESOURCE( SetAdvancedSummonTargetApplicator );
REGISTER_DBRESOURCE( SetTimescaleApplicator );
REGISTER_DBRESOURCE( ShiftApplicator );
REGISTER_DBRESOURCE( ShopTargetSelector );
REGISTER_DBRESOURCE( ComparingTargetSelector );
REGISTER_DBRESOURCE( BaseAttack );
REGISTER_DBRESOURCE( SpellApplicator );
REGISTER_DBRESOURCE( SpellPeriodicallyApplicator );
REGISTER_DBRESOURCE( SpellPeriodicallyVisualApplicator );
REGISTER_DBRESOURCE( SpellProbabilityApplicator );
REGISTER_DBRESOURCE( SpellSwitchApplicator );
REGISTER_DBRESOURCE( StatModApplicator );
REGISTER_DBRESOURCE( StatusApplicator );
REGISTER_DBRESOURCE( SummonApplicator );
BASIC_REGISTER_DBRESOURCE( SummonBehaviourBase );
REGISTER_DBRESOURCE( SummonBehaviourCommon );
REGISTER_DBRESOURCE( SummonBehaviourAdvanced );
REGISTER_DBRESOURCE( SummonEnumerator );
REGISTER_DBRESOURCE( TargetCastLimitation );
REGISTER_DBRESOURCE( TargetsCounterApplicator );
REGISTER_DBRESOURCE( AttackersTargetSelector );
REGISTER_DBRESOURCE( TargetSelectorMicroAI );
REGISTER_DBRESOURCE( TauntApplicator );
REGISTER_DBRESOURCE( TeleportApplicator );
REGISTER_DBRESOURCE( ThrowApplicator );
REGISTER_DBRESOURCE( TriggerApplicator );
REGISTER_DBRESOURCE( UIMessageApplicator );
REGISTER_DBRESOURCE( UnitConstant );
REGISTER_DBRESOURCE( UnitConstantsContainer );
REGISTER_DBRESOURCE( UnitEnumerator );
REGISTER_DBRESOURCE( UnitPlaceCorrector );
REGISTER_DBRESOURCE( UnitShiftTarget );
REGISTER_DBRESOURCE( ValueApplicator );
REGISTER_DBRESOURCE( VariableProxyApplicator );
REGISTER_DBRESOURCE( VictoryApplicator );
REGISTER_DBRESOURCE( WaitForSpellApplicator );
REGISTER_DBRESOURCE( WallTargetSelector );
REGISTER_DBRESOURCE( WatchApplicator );
REGISTER_DBRESOURCE( WeightTargetSelector );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#include "PFAdvancedSummon.h"
#include "PFAITargetSelectors.h"
#include "PFApplAura.h"
#include "PFApplBounce.h"
#include "PFApplBuff.h"
#include "PFApplChainLightning.h"
#include "PFApplChannelling.h"
#include "PFApplDelegateDamage.h"
#include "PFApplFx.h"
#include "PFApplHelper.h"
#include "PFApplInstant.h"
#include "PfApplMod.h"
#include "PFApplMod.h"
#include "PFApplMove.h"
#include "PFApplSpecial.h"
#include "PFApplSummon.h"
#include "PFCastLimitations.h"
#include "PFDispatchCursor.h"
#include "PFDispatchStrike1.h"
#include "PFHighlander.h"
#include "PFMicroAI.h"
#include "PFTargetSelector.h"
#include "PFTriggerApplicator.h"

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbility value )
{
	switch( value )
	{
		case ABILITY_ID_STATS:
			return "ID_Stats";
		case ABILITY_ID_1:
			return "ID_1";
		case ABILITY_ID_2:
			return "ID_2";
		case ABILITY_ID_3:
			return "ID_3";
		case ABILITY_ID_4:
			return "ID_4";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbility", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbility StringToEnum_EAbility( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbility)(NStr::ToInt( value ));
	if ( strcmp( value, "ID_Stats" ) == 0 || strcmp( value, "ABILITY_ID_STATS" ) == 0 )
		return ABILITY_ID_STATS;
	if ( strcmp( value, "ID_1" ) == 0 || strcmp( value, "ABILITY_ID_1" ) == 0 )
		return ABILITY_ID_1;
	if ( strcmp( value, "ID_2" ) == 0 || strcmp( value, "ABILITY_ID_2" ) == 0 )
		return ABILITY_ID_2;
	if ( strcmp( value, "ID_3" ) == 0 || strcmp( value, "ABILITY_ID_3" ) == 0 )
		return ABILITY_ID_3;
	if ( strcmp( value, "ID_4" ) == 0 || strcmp( value, "ABILITY_ID_4" ) == 0 )
		return ABILITY_ID_4;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbility", value ) );
	return ABILITY_ID_STATS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityAOEVisual value )
{
	switch( value )
	{
		case ABILITYAOEVISUAL_NONE:
			return "None";
		case ABILITYAOEVISUAL_DISK:
			return "Disk";
		case ABILITYAOEVISUAL_CONE:
			return "Cone";
		case ABILITYAOEVISUAL_CORRIDOR:
			return "Corridor";
		case ABILITYAOEVISUAL_CORRIDORMAX:
			return "CorridorMax";
		case ABILITYAOEVISUAL_UNATTACHEDSECTOR:
			return "UnattachedSector";
		case ABILITYAOEVISUAL_WALL:
			return "Wall";
		case ABILITYAOEVISUAL_ATTACHEDSECTOR:
			return "AttachedSector";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbilityAOEVisual", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityAOEVisual StringToEnum_EAbilityAOEVisual( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityAOEVisual)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_NONE" ) == 0 )
		return ABILITYAOEVISUAL_NONE;
	if ( strcmp( value, "Disk" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_DISK" ) == 0 )
		return ABILITYAOEVISUAL_DISK;
	if ( strcmp( value, "Cone" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_CONE" ) == 0 )
		return ABILITYAOEVISUAL_CONE;
	if ( strcmp( value, "Corridor" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_CORRIDOR" ) == 0 )
		return ABILITYAOEVISUAL_CORRIDOR;
	if ( strcmp( value, "CorridorMax" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_CORRIDORMAX" ) == 0 )
		return ABILITYAOEVISUAL_CORRIDORMAX;
	if ( strcmp( value, "UnattachedSector" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_UNATTACHEDSECTOR" ) == 0 )
		return ABILITYAOEVISUAL_UNATTACHEDSECTOR;
	if ( strcmp( value, "Wall" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_WALL" ) == 0 )
		return ABILITYAOEVISUAL_WALL;
	if ( strcmp( value, "AttachedSector" ) == 0 || strcmp( value, "ABILITYAOEVISUAL_ATTACHEDSECTOR" ) == 0 )
		return ABILITYAOEVISUAL_ATTACHEDSECTOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityAOEVisual", value ) );
	return ABILITYAOEVISUAL_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityCostMode value )
{
	switch( value )
	{
		case ABILITYCOSTMODE_ENERGY:
			return "Energy";
		case ABILITYCOSTMODE_LIFE:
			return "Life";
		case ABILITYCOSTMODE_ANY:
			return "Any";
		case ABILITYCOSTMODE_CUSTOM:
			return "Custom";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbilityCostMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityCostMode StringToEnum_EAbilityCostMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityCostMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "ABILITYCOSTMODE_ENERGY" ) == 0 )
		return ABILITYCOSTMODE_ENERGY;
	if ( strcmp( value, "Life" ) == 0 || strcmp( value, "ABILITYCOSTMODE_LIFE" ) == 0 )
		return ABILITYCOSTMODE_LIFE;
	if ( strcmp( value, "Any" ) == 0 || strcmp( value, "ABILITYCOSTMODE_ANY" ) == 0 )
		return ABILITYCOSTMODE_ANY;
	if ( strcmp( value, "Custom" ) == 0 || strcmp( value, "ABILITYCOSTMODE_CUSTOM" ) == 0 )
		return ABILITYCOSTMODE_CUSTOM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityCostMode", value ) );
	return ABILITYCOSTMODE_ENERGY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityFlags value )
{
	switch( value )
	{
		case ABILITYFLAGS_FOCUSONTARGET:
			return "FocusOnTarget";
		case ABILITYFLAGS_MOMENTARY:
			return "Momentary";
		case ABILITYFLAGS_APPLYTODEAD:
			return "ApplyToDead";
		case ABILITYFLAGS_MIRROREDBYCLONE:
			return "MirroredByClone";
		case ABILITYFLAGS_STAYINVISIBLE:
			return "StayInvisible";
		case ABILITYFLAGS_CHANNELINGCREATE:
			return "ChannelingCreate";
		case ABILITYFLAGS_CANUSEOUTOFRANGE:
			return "CanUseOutOfRange";
		case ABILITYFLAGS_DONTOPENWARFOG:
			return "DontOpenWarFog";
		case ABILITYFLAGS_INSTACAST:
			return "InstaCast";
		case ABILITYFLAGS_MOVING:
			return "Moving";
		case ABILITYFLAGS_USEATTACKTARGET:
			return "UseAttackTarget";
		case ABILITYFLAGS_WAITFORCHANNELING:
			return "WaitForChanneling";
		case ABILITYFLAGS_FOCUSINSTANTLY:
			return "FocusInstantly";
		case ABILITYFLAGS_MINIMAPTARGETMUSTBEALTERNATIVE:
			return "MinimapTargetMustBeAlternative";
		case ABILITYFLAGS_SPENDLIFEINSTEADENERGY:
			return "SpendLifeInsteadEnergy";
		case ABILITYFLAGS_SELFCASTING:
			return "SelfCasting";
		case ABILITYFLAGS_FORCEDONOTSTOPUNIT:
			return "ForceDoNotStopUnit";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityFlags StringToEnum_EAbilityFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "FocusOnTarget" ) == 0 || strcmp( value, "ABILITYFLAGS_FOCUSONTARGET" ) == 0 )
		return ABILITYFLAGS_FOCUSONTARGET;
	if ( strcmp( value, "Momentary" ) == 0 || strcmp( value, "ABILITYFLAGS_MOMENTARY" ) == 0 )
		return ABILITYFLAGS_MOMENTARY;
	if ( strcmp( value, "ApplyToDead" ) == 0 || strcmp( value, "ABILITYFLAGS_APPLYTODEAD" ) == 0 )
		return ABILITYFLAGS_APPLYTODEAD;
	if ( strcmp( value, "MirroredByClone" ) == 0 || strcmp( value, "ABILITYFLAGS_MIRROREDBYCLONE" ) == 0 )
		return ABILITYFLAGS_MIRROREDBYCLONE;
	if ( strcmp( value, "StayInvisible" ) == 0 || strcmp( value, "ABILITYFLAGS_STAYINVISIBLE" ) == 0 )
		return ABILITYFLAGS_STAYINVISIBLE;
	if ( strcmp( value, "ChannelingCreate" ) == 0 || strcmp( value, "ABILITYFLAGS_CHANNELINGCREATE" ) == 0 )
		return ABILITYFLAGS_CHANNELINGCREATE;
	if ( strcmp( value, "CanUseOutOfRange" ) == 0 || strcmp( value, "ABILITYFLAGS_CANUSEOUTOFRANGE" ) == 0 )
		return ABILITYFLAGS_CANUSEOUTOFRANGE;
	if ( strcmp( value, "DontOpenWarFog" ) == 0 || strcmp( value, "ABILITYFLAGS_DONTOPENWARFOG" ) == 0 )
		return ABILITYFLAGS_DONTOPENWARFOG;
	if ( strcmp( value, "InstaCast" ) == 0 || strcmp( value, "ABILITYFLAGS_INSTACAST" ) == 0 )
		return ABILITYFLAGS_INSTACAST;
	if ( strcmp( value, "Moving" ) == 0 || strcmp( value, "ABILITYFLAGS_MOVING" ) == 0 )
		return ABILITYFLAGS_MOVING;
	if ( strcmp( value, "UseAttackTarget" ) == 0 || strcmp( value, "ABILITYFLAGS_USEATTACKTARGET" ) == 0 )
		return ABILITYFLAGS_USEATTACKTARGET;
	if ( strcmp( value, "WaitForChanneling" ) == 0 || strcmp( value, "ABILITYFLAGS_WAITFORCHANNELING" ) == 0 )
		return ABILITYFLAGS_WAITFORCHANNELING;
	if ( strcmp( value, "FocusInstantly" ) == 0 || strcmp( value, "ABILITYFLAGS_FOCUSINSTANTLY" ) == 0 )
		return ABILITYFLAGS_FOCUSINSTANTLY;
	if ( strcmp( value, "MinimapTargetMustBeAlternative" ) == 0 || strcmp( value, "ABILITYFLAGS_MINIMAPTARGETMUSTBEALTERNATIVE" ) == 0 )
		return ABILITYFLAGS_MINIMAPTARGETMUSTBEALTERNATIVE;
	if ( strcmp( value, "SpendLifeInsteadEnergy" ) == 0 || strcmp( value, "ABILITYFLAGS_SPENDLIFEINSTEADENERGY" ) == 0 )
		return ABILITYFLAGS_SPENDLIFEINSTEADENERGY;
	if ( strcmp( value, "SelfCasting" ) == 0 || strcmp( value, "ABILITYFLAGS_SELFCASTING" ) == 0 )
		return ABILITYFLAGS_SELFCASTING;
	if ( strcmp( value, "ForceDoNotStopUnit" ) == 0 || strcmp( value, "ABILITYFLAGS_FORCEDONOTSTOPUNIT" ) == 0 )
		return ABILITYFLAGS_FORCEDONOTSTOPUNIT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityFlags", value ) );
	return ABILITYFLAGS_FOCUSONTARGET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityIdFlags value )
{
	switch( value )
	{
		case ABILITYIDFLAGS_SPECIFIC:
			return "Specific";
		case ABILITYIDFLAGS_BASEATTACK:
			return "BaseAttack";
		case ABILITYIDFLAGS_ABILITY1:
			return "Ability1";
		case ABILITYIDFLAGS_ABILITY2:
			return "Ability2";
		case ABILITYIDFLAGS_ABILITY3:
			return "Ability3";
		case ABILITYIDFLAGS_ABILITY4:
			return "Ability4";
		case ABILITYIDFLAGS_CONSUMABLES:
			return "Consumables";
		case ABILITYIDFLAGS_TALENTS:
			return "Talents";
		case ABILITYIDFLAGS_PORTAL:
			return "Portal";
		case ABILITYIDFLAGS_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityIdFlags StringToEnum_EAbilityIdFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityIdFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Specific" ) == 0 || strcmp( value, "ABILITYIDFLAGS_SPECIFIC" ) == 0 )
		return ABILITYIDFLAGS_SPECIFIC;
	if ( strcmp( value, "BaseAttack" ) == 0 || strcmp( value, "ABILITYIDFLAGS_BASEATTACK" ) == 0 )
		return ABILITYIDFLAGS_BASEATTACK;
	if ( strcmp( value, "Ability1" ) == 0 || strcmp( value, "ABILITYIDFLAGS_ABILITY1" ) == 0 )
		return ABILITYIDFLAGS_ABILITY1;
	if ( strcmp( value, "Ability2" ) == 0 || strcmp( value, "ABILITYIDFLAGS_ABILITY2" ) == 0 )
		return ABILITYIDFLAGS_ABILITY2;
	if ( strcmp( value, "Ability3" ) == 0 || strcmp( value, "ABILITYIDFLAGS_ABILITY3" ) == 0 )
		return ABILITYIDFLAGS_ABILITY3;
	if ( strcmp( value, "Ability4" ) == 0 || strcmp( value, "ABILITYIDFLAGS_ABILITY4" ) == 0 )
		return ABILITYIDFLAGS_ABILITY4;
	if ( strcmp( value, "Consumables" ) == 0 || strcmp( value, "ABILITYIDFLAGS_CONSUMABLES" ) == 0 )
		return ABILITYIDFLAGS_CONSUMABLES;
	if ( strcmp( value, "Talents" ) == 0 || strcmp( value, "ABILITYIDFLAGS_TALENTS" ) == 0 )
		return ABILITYIDFLAGS_TALENTS;
	if ( strcmp( value, "Portal" ) == 0 || strcmp( value, "ABILITYIDFLAGS_PORTAL" ) == 0 )
		return ABILITYIDFLAGS_PORTAL;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "ABILITYIDFLAGS_ALL" ) == 0 )
		return ABILITYIDFLAGS_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityIdFlags", value ) );
	return ABILITYIDFLAGS_SPECIFIC;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityModMode value )
{
	switch( value )
	{
		case ABILITYMODMODE_NAFTACOST:
			return "naftacost";
		case ABILITYMODMODE_MANACOST:
			return "manacost";
		case ABILITYMODMODE_COOLDOWN:
			return "cooldown";
		case ABILITYMODMODE_SCALE:
			return "scale";
		case ABILITYMODMODE_DURATION:
			return "duration";
		case ABILITYMODMODE_STATE:
			return "state";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbilityModMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityModMode StringToEnum_EAbilityModMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityModMode)(NStr::ToInt( value ));
	if ( strcmp( value, "naftacost" ) == 0 || strcmp( value, "ABILITYMODMODE_NAFTACOST" ) == 0 )
		return ABILITYMODMODE_NAFTACOST;
	if ( strcmp( value, "manacost" ) == 0 || strcmp( value, "ABILITYMODMODE_MANACOST" ) == 0 )
		return ABILITYMODMODE_MANACOST;
	if ( strcmp( value, "cooldown" ) == 0 || strcmp( value, "ABILITYMODMODE_COOLDOWN" ) == 0 )
		return ABILITYMODMODE_COOLDOWN;
	if ( strcmp( value, "scale" ) == 0 || strcmp( value, "ABILITYMODMODE_SCALE" ) == 0 )
		return ABILITYMODMODE_SCALE;
	if ( strcmp( value, "duration" ) == 0 || strcmp( value, "ABILITYMODMODE_DURATION" ) == 0 )
		return ABILITYMODMODE_DURATION;
	if ( strcmp( value, "state" ) == 0 || strcmp( value, "ABILITYMODMODE_STATE" ) == 0 )
		return ABILITYMODMODE_STATE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityModMode", value ) );
	return ABILITYMODMODE_NAFTACOST;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityType value )
{
	switch( value )
	{
		case ABILITYTYPE_SIMPLE:
			return "Simple";
		case ABILITYTYPE_ACTIVE:
			return "Active";
		case ABILITYTYPE_MULTIACTIVE:
			return "MultiActive";
		case ABILITYTYPE_PASSIVE:
			return "Passive";
		case ABILITYTYPE_AUTOCASTABLE:
			return "Autocastable";
		case ABILITYTYPE_SWITCHABLE:
			return "Switchable";
		case ABILITYTYPE_CHANNELLING:
			return "Channelling";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbilityType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityType StringToEnum_EAbilityType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityType)(NStr::ToInt( value ));
	if ( strcmp( value, "Simple" ) == 0 || strcmp( value, "ABILITYTYPE_SIMPLE" ) == 0 )
		return ABILITYTYPE_SIMPLE;
	if ( strcmp( value, "Active" ) == 0 || strcmp( value, "ABILITYTYPE_ACTIVE" ) == 0 )
		return ABILITYTYPE_ACTIVE;
	if ( strcmp( value, "MultiActive" ) == 0 || strcmp( value, "ABILITYTYPE_MULTIACTIVE" ) == 0 )
		return ABILITYTYPE_MULTIACTIVE;
	if ( strcmp( value, "Passive" ) == 0 || strcmp( value, "ABILITYTYPE_PASSIVE" ) == 0 )
		return ABILITYTYPE_PASSIVE;
	if ( strcmp( value, "Autocastable" ) == 0 || strcmp( value, "ABILITYTYPE_AUTOCASTABLE" ) == 0 )
		return ABILITYTYPE_AUTOCASTABLE;
	if ( strcmp( value, "Switchable" ) == 0 || strcmp( value, "ABILITYTYPE_SWITCHABLE" ) == 0 )
		return ABILITYTYPE_SWITCHABLE;
	if ( strcmp( value, "Channelling" ) == 0 || strcmp( value, "ABILITYTYPE_CHANNELLING" ) == 0 )
		return ABILITYTYPE_CHANNELLING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityType", value ) );
	return ABILITYTYPE_SIMPLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityTypeId value )
{
	switch( value )
	{
		case ABILITYTYPEID_BASEATTACK:
			return "BaseAttack";
		case ABILITYTYPEID_ABILITY0:
			return "Ability0";
		case ABILITYTYPEID_ABILITY1:
			return "Ability1";
		case ABILITYTYPEID_ABILITY2:
			return "Ability2";
		case ABILITYTYPEID_ABILITY3:
			return "Ability3";
		case ABILITYTYPEID_ABILITY4:
			return "Ability4";
		case ABILITYTYPEID_CONSUMABLE:
			return "Consumable";
		case ABILITYTYPEID_TALENT:
			return "Talent";
		case ABILITYTYPEID_TALENTFROMLIST:
			return "TalentFromList";
		case ABILITYTYPEID_IMPULSIVEBUFF:
			return "ImpulsiveBuff";
		case ABILITYTYPEID_SPECIAL:
			return "Special";
		case ABILITYTYPEID_PORTAL:
			return "Portal";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAbilityTypeId", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityTypeId StringToEnum_EAbilityTypeId( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityTypeId)(NStr::ToInt( value ));
	if ( strcmp( value, "BaseAttack" ) == 0 || strcmp( value, "ABILITYTYPEID_BASEATTACK" ) == 0 )
		return ABILITYTYPEID_BASEATTACK;
	if ( strcmp( value, "Ability0" ) == 0 || strcmp( value, "ABILITYTYPEID_ABILITY0" ) == 0 )
		return ABILITYTYPEID_ABILITY0;
	if ( strcmp( value, "Ability1" ) == 0 || strcmp( value, "ABILITYTYPEID_ABILITY1" ) == 0 )
		return ABILITYTYPEID_ABILITY1;
	if ( strcmp( value, "Ability2" ) == 0 || strcmp( value, "ABILITYTYPEID_ABILITY2" ) == 0 )
		return ABILITYTYPEID_ABILITY2;
	if ( strcmp( value, "Ability3" ) == 0 || strcmp( value, "ABILITYTYPEID_ABILITY3" ) == 0 )
		return ABILITYTYPEID_ABILITY3;
	if ( strcmp( value, "Ability4" ) == 0 || strcmp( value, "ABILITYTYPEID_ABILITY4" ) == 0 )
		return ABILITYTYPEID_ABILITY4;
	if ( strcmp( value, "Consumable" ) == 0 || strcmp( value, "ABILITYTYPEID_CONSUMABLE" ) == 0 )
		return ABILITYTYPEID_CONSUMABLE;
	if ( strcmp( value, "Talent" ) == 0 || strcmp( value, "ABILITYTYPEID_TALENT" ) == 0 )
		return ABILITYTYPEID_TALENT;
	if ( strcmp( value, "TalentFromList" ) == 0 || strcmp( value, "ABILITYTYPEID_TALENTFROMLIST" ) == 0 )
		return ABILITYTYPEID_TALENTFROMLIST;
	if ( strcmp( value, "ImpulsiveBuff" ) == 0 || strcmp( value, "ABILITYTYPEID_IMPULSIVEBUFF" ) == 0 )
		return ABILITYTYPEID_IMPULSIVEBUFF;
	if ( strcmp( value, "Special" ) == 0 || strcmp( value, "ABILITYTYPEID_SPECIAL" ) == 0 )
		return ABILITYTYPEID_SPECIAL;
	if ( strcmp( value, "Portal" ) == 0 || strcmp( value, "ABILITYTYPEID_PORTAL" ) == 0 )
		return ABILITYTYPEID_PORTAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityTypeId", value ) );
	return ABILITYTYPEID_BASEATTACK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAbilityUpgradeMode value )
{
	switch( value )
	{
		case ABILITYUPGRADEMODE_NONE:
			return "None";
		case ABILITYUPGRADEMODE_DONTUSEORIGINAL:
			return "DontUseOriginal";
		case ABILITYUPGRADEMODE_USEABILITYMANA:
			return "UseAbilityMana";
		case ABILITYUPGRADEMODE_USEABILITYCOOLDOWN:
			return "UseAbilityCooldown";
		case ABILITYUPGRADEMODE_USEGLYPH:
			return "UseGlyph";
		case ABILITYUPGRADEMODE_CHANGEICON:
			return "ChangeIcon";
		case ABILITYUPGRADEMODE_APPLYONCEPERCAST:
			return "ApplyOncePerCast";
		case ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET:
			return "ApplyOncePerCastPerTarget";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAbilityUpgradeMode StringToEnum_EAbilityUpgradeMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAbilityUpgradeMode)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_NONE" ) == 0 )
		return ABILITYUPGRADEMODE_NONE;
	if ( strcmp( value, "DontUseOriginal" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_DONTUSEORIGINAL" ) == 0 )
		return ABILITYUPGRADEMODE_DONTUSEORIGINAL;
	if ( strcmp( value, "UseAbilityMana" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_USEABILITYMANA" ) == 0 )
		return ABILITYUPGRADEMODE_USEABILITYMANA;
	if ( strcmp( value, "UseAbilityCooldown" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_USEABILITYCOOLDOWN" ) == 0 )
		return ABILITYUPGRADEMODE_USEABILITYCOOLDOWN;
	if ( strcmp( value, "UseGlyph" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_USEGLYPH" ) == 0 )
		return ABILITYUPGRADEMODE_USEGLYPH;
	if ( strcmp( value, "ChangeIcon" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_CHANGEICON" ) == 0 )
		return ABILITYUPGRADEMODE_CHANGEICON;
	if ( strcmp( value, "ApplyOncePerCast" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_APPLYONCEPERCAST" ) == 0 )
		return ABILITYUPGRADEMODE_APPLYONCEPERCAST;
	if ( strcmp( value, "ApplyOncePerCastPerTarget" ) == 0 || strcmp( value, "ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET" ) == 0 )
		return ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAbilityUpgradeMode", value ) );
	return ABILITYUPGRADEMODE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EApplicatorAppliedMode value )
{
	switch( value )
	{
		case APPLICATORAPPLIEDMODE_DEFAULT:
			return "Default";
		case APPLICATORAPPLIEDMODE_CANCEL:
			return "Cancel";
		case APPLICATORAPPLIEDMODE_SETNEWLIFETIME:
			return "SetNewLifetime";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EApplicatorAppliedMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EApplicatorAppliedMode StringToEnum_EApplicatorAppliedMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EApplicatorAppliedMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Default" ) == 0 || strcmp( value, "APPLICATORAPPLIEDMODE_DEFAULT" ) == 0 )
		return APPLICATORAPPLIEDMODE_DEFAULT;
	if ( strcmp( value, "Cancel" ) == 0 || strcmp( value, "APPLICATORAPPLIEDMODE_CANCEL" ) == 0 )
		return APPLICATORAPPLIEDMODE_CANCEL;
	if ( strcmp( value, "SetNewLifetime" ) == 0 || strcmp( value, "APPLICATORAPPLIEDMODE_SETNEWLIFETIME" ) == 0 )
		return APPLICATORAPPLIEDMODE_SETNEWLIFETIME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EApplicatorAppliedMode", value ) );
	return APPLICATORAPPLIEDMODE_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EApplicatorApplyTarget value )
{
	switch( value )
	{
		case APPLICATORAPPLYTARGET_APPLICATORTARGET:
			return "ApplicatorTarget";
		case APPLICATORAPPLYTARGET_ABILITYOWNER:
			return "AbilityOwner";
		case APPLICATORAPPLYTARGET_PREVAPPLICATORTARGET:
			return "PrevApplicatorTarget";
		case APPLICATORAPPLYTARGET_PREVAPPLICATORRECEIVER:
			return "PrevApplicatorReceiver";
		case APPLICATORAPPLYTARGET_HIER1UPAPPLICATORTARGET:
			return "Hier1UpApplicatorTarget";
		case APPLICATORAPPLYTARGET_HIER2UPAPPLICATORTARGET:
			return "Hier2UpApplicatorTarget";
		case APPLICATORAPPLYTARGET_HIER3UPAPPLICATORTARGET:
			return "Hier3UpApplicatorTarget";
		case APPLICATORAPPLYTARGET_ABILITYTARGET:
			return "AbilityTarget";
		case APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET:
			return "ApplicatorSelectedTarget";
		case APPLICATORAPPLYTARGET_CASTPOSITION:
			return "CastPosition";
		case APPLICATORAPPLYTARGET_CASTMASTERPOSITION:
			return "CastMasterPosition";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EApplicatorApplyTarget", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EApplicatorApplyTarget StringToEnum_EApplicatorApplyTarget( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EApplicatorApplyTarget)(NStr::ToInt( value ));
	if ( strcmp( value, "ApplicatorTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_APPLICATORTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_APPLICATORTARGET;
	if ( strcmp( value, "AbilityOwner" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_ABILITYOWNER" ) == 0 )
		return APPLICATORAPPLYTARGET_ABILITYOWNER;
	if ( strcmp( value, "PrevApplicatorTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_PREVAPPLICATORTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_PREVAPPLICATORTARGET;
	if ( strcmp( value, "PrevApplicatorReceiver" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_PREVAPPLICATORRECEIVER" ) == 0 )
		return APPLICATORAPPLYTARGET_PREVAPPLICATORRECEIVER;
	if ( strcmp( value, "Hier1UpApplicatorTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_HIER1UPAPPLICATORTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_HIER1UPAPPLICATORTARGET;
	if ( strcmp( value, "Hier2UpApplicatorTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_HIER2UPAPPLICATORTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_HIER2UPAPPLICATORTARGET;
	if ( strcmp( value, "Hier3UpApplicatorTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_HIER3UPAPPLICATORTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_HIER3UPAPPLICATORTARGET;
	if ( strcmp( value, "AbilityTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_ABILITYTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_ABILITYTARGET;
	if ( strcmp( value, "ApplicatorSelectedTarget" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET" ) == 0 )
		return APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET;
	if ( strcmp( value, "CastPosition" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_CASTPOSITION" ) == 0 )
		return APPLICATORAPPLYTARGET_CASTPOSITION;
	if ( strcmp( value, "CastMasterPosition" ) == 0 || strcmp( value, "APPLICATORAPPLYTARGET_CASTMASTERPOSITION" ) == 0 )
		return APPLICATORAPPLYTARGET_CASTMASTERPOSITION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EApplicatorApplyTarget", value ) );
	return APPLICATORAPPLYTARGET_APPLICATORTARGET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EApplicatorDamageType value )
{
	switch( value )
	{
		case APPLICATORDAMAGETYPE_MATERIAL:
			return "Material";
		case APPLICATORDAMAGETYPE_ENERGY:
			return "Energy";
		case APPLICATORDAMAGETYPE_MANA:
			return "Mana";
		case APPLICATORDAMAGETYPE_PURE:
			return "Pure";
		case APPLICATORDAMAGETYPE_NATIVE:
			return "Native";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EApplicatorDamageType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EApplicatorDamageType StringToEnum_EApplicatorDamageType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EApplicatorDamageType)(NStr::ToInt( value ));
	if ( strcmp( value, "Material" ) == 0 || strcmp( value, "APPLICATORDAMAGETYPE_MATERIAL" ) == 0 )
		return APPLICATORDAMAGETYPE_MATERIAL;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "APPLICATORDAMAGETYPE_ENERGY" ) == 0 )
		return APPLICATORDAMAGETYPE_ENERGY;
	if ( strcmp( value, "Mana" ) == 0 || strcmp( value, "APPLICATORDAMAGETYPE_MANA" ) == 0 )
		return APPLICATORDAMAGETYPE_MANA;
	if ( strcmp( value, "Pure" ) == 0 || strcmp( value, "APPLICATORDAMAGETYPE_PURE" ) == 0 )
		return APPLICATORDAMAGETYPE_PURE;
	if ( strcmp( value, "Native" ) == 0 || strcmp( value, "APPLICATORDAMAGETYPE_NATIVE" ) == 0 )
		return APPLICATORDAMAGETYPE_NATIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EApplicatorDamageType", value ) );
	return APPLICATORDAMAGETYPE_MATERIAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EApplyEffectOrientation value )
{
	switch( value )
	{
		case APPLYEFFECTORIENTATION_DEFAULT:
			return "Default";
		case APPLYEFFECTORIENTATION_RANDOM:
			return "Random";
		case APPLYEFFECTORIENTATION_MOTION:
			return "Motion";
		case APPLYEFFECTORIENTATION_LOGICALDIRECTION:
			return "LogicalDirection";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EApplyEffectOrientation", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EApplyEffectOrientation StringToEnum_EApplyEffectOrientation( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EApplyEffectOrientation)(NStr::ToInt( value ));
	if ( strcmp( value, "Default" ) == 0 || strcmp( value, "APPLYEFFECTORIENTATION_DEFAULT" ) == 0 )
		return APPLYEFFECTORIENTATION_DEFAULT;
	if ( strcmp( value, "Random" ) == 0 || strcmp( value, "APPLYEFFECTORIENTATION_RANDOM" ) == 0 )
		return APPLYEFFECTORIENTATION_RANDOM;
	if ( strcmp( value, "Motion" ) == 0 || strcmp( value, "APPLYEFFECTORIENTATION_MOTION" ) == 0 )
		return APPLYEFFECTORIENTATION_MOTION;
	if ( strcmp( value, "LogicalDirection" ) == 0 || strcmp( value, "APPLYEFFECTORIENTATION_LOGICALDIRECTION" ) == 0 )
		return APPLYEFFECTORIENTATION_LOGICALDIRECTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EApplyEffectOrientation", value ) );
	return APPLYEFFECTORIENTATION_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAttackersType value )
{
	switch( value )
	{
		case ATTACKERSTYPE_TARGETERS:
			return "Targeters";
		case ATTACKERSTYPE_DAMAGEDEALERS:
			return "DamageDealers";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAttackersType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAttackersType StringToEnum_EAttackersType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAttackersType)(NStr::ToInt( value ));
	if ( strcmp( value, "Targeters" ) == 0 || strcmp( value, "ATTACKERSTYPE_TARGETERS" ) == 0 )
		return ATTACKERSTYPE_TARGETERS;
	if ( strcmp( value, "DamageDealers" ) == 0 || strcmp( value, "ATTACKERSTYPE_DAMAGEDEALERS" ) == 0 )
		return ATTACKERSTYPE_DAMAGEDEALERS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAttackersType", value ) );
	return ATTACKERSTYPE_TARGETERS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAttackTargetEvadeAction value )
{
	switch( value )
	{
		case ATTACKTARGETEVADEACTION_ATTACKAGAIN:
			return "AttackAgain";
		case ATTACKTARGETEVADEACTION_STOPASCOMPLETE:
			return "StopAsComplete";
		case ATTACKTARGETEVADEACTION_STOPASFAILED:
			return "StopAsFailed";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAttackTargetEvadeAction", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAttackTargetEvadeAction StringToEnum_EAttackTargetEvadeAction( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAttackTargetEvadeAction)(NStr::ToInt( value ));
	if ( strcmp( value, "AttackAgain" ) == 0 || strcmp( value, "ATTACKTARGETEVADEACTION_ATTACKAGAIN" ) == 0 )
		return ATTACKTARGETEVADEACTION_ATTACKAGAIN;
	if ( strcmp( value, "StopAsComplete" ) == 0 || strcmp( value, "ATTACKTARGETEVADEACTION_STOPASCOMPLETE" ) == 0 )
		return ATTACKTARGETEVADEACTION_STOPASCOMPLETE;
	if ( strcmp( value, "StopAsFailed" ) == 0 || strcmp( value, "ATTACKTARGETEVADEACTION_STOPASFAILED" ) == 0 )
		return ATTACKTARGETEVADEACTION_STOPASFAILED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAttackTargetEvadeAction", value ) );
	return ATTACKTARGETEVADEACTION_ATTACKAGAIN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAuraVisualType value )
{
	switch( value )
	{
		case AURAVISUALTYPE_NONE:
			return "None";
		case AURAVISUALTYPE_ALLY:
			return "Ally";
		case AURAVISUALTYPE_ENEMY:
			return "Enemy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAuraVisualType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAuraVisualType StringToEnum_EAuraVisualType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAuraVisualType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "AURAVISUALTYPE_NONE" ) == 0 )
		return AURAVISUALTYPE_NONE;
	if ( strcmp( value, "Ally" ) == 0 || strcmp( value, "AURAVISUALTYPE_ALLY" ) == 0 )
		return AURAVISUALTYPE_ALLY;
	if ( strcmp( value, "Enemy" ) == 0 || strcmp( value, "AURAVISUALTYPE_ENEMY" ) == 0 )
		return AURAVISUALTYPE_ENEMY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAuraVisualType", value ) );
	return AURAVISUALTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBaseUnitEvent value )
{
	switch( value )
	{
		case BASEUNITEVENT_MOVE:
			return "Move";
		case BASEUNITEVENT_CASTMAGIC:
			return "CastMagic";
		case BASEUNITEVENT_USECONSUMABLE:
			return "UseConsumable";
		case BASEUNITEVENT_USETALENT:
			return "UseTalent";
		case BASEUNITEVENT_ATTACK:
			return "Attack";
		case BASEUNITEVENT_FORBIDMOVE:
			return "ForbidMove";
		case BASEUNITEVENT_FORBIDATTACK:
			return "ForbidAttack";
		case BASEUNITEVENT_FORBIDCAST:
			return "ForbidCast";
		case BASEUNITEVENT_FORCEDMOVE:
			return "ForcedMove";
		case BASEUNITEVENT_DISPATCHAPPLIED:
			return "DispatchApplied";
		case BASEUNITEVENT_DISPATCHEVADED:
			return "DispatchEvaded";
		case BASEUNITEVENT_DAMAGE:
			return "Damage";
		case BASEUNITEVENT_ISOLATE:
			return "Isolate";
		case BASEUNITEVENT_APPLICATORSTEP:
			return "ApplicatorStep";
		case BASEUNITEVENT_APPLICATORAPPLIED:
			return "ApplicatorApplied";
		case BASEUNITEVENT_DEATH:
			return "Death";
		case BASEUNITEVENT_ASSIGNTARGET:
			return "AssignTarget";
		case BASEUNITEVENT_LASTHIT:
			return "LastHit";
		case BASEUNITEVENT_FORBIDAUTOATTACK:
			return "ForbidAutoAttack";
		case BASEUNITEVENT_PICKUP:
			return "Pickup";
		case BASEUNITEVENT_RESURRECT:
			return "Resurrect";
		case BASEUNITEVENT_ABILITYSTART:
			return "AbilityStart";
		case BASEUNITEVENT_CHANNELINGCANCELED:
			return "ChannelingCanceled";
		case BASEUNITEVENT_CANCELINVISIBILITY:
			return "CancelInvisibility";
		case BASEUNITEVENT_UNSUMMON:
			return "Unsummon";
		case BASEUNITEVENT_CONSUMABLEOBTAINED:
			return "ConsumableObtained";
		case BASEUNITEVENT_USEPORTAL:
			return "UsePortal";
		case BASEUNITEVENT_WANTMOVETO:
			return "WantMoveTo";
		case BASEUNITEVENT_OUTGOINGDAMAGE:
			return "OutgoingDamage";
		case BASEUNITEVENT_DISPATCHMISSED:
			return "DispatchMissed";
		case BASEUNITEVENT_HEROKILLORASSIST:
			return "HeroKillOrAssist";
		case BASEUNITEVENT_MINIGAMESTARTED:
			return "MinigameStarted";
		case BASEUNITEVENT_MINIGAMEEXIT:
			return "MinigameExit";
		case BASEUNITEVENT_MINIGAMELEVELSTARTED:
			return "MinigameLevelStarted";
		case BASEUNITEVENT_MINIGAMELEVELWON:
			return "MinigameLevelWon";
		case BASEUNITEVENT_MINIGAMELEVELFAILED:
			return "MinigameLevelFailed";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBaseUnitEvent", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBaseUnitEvent StringToEnum_EBaseUnitEvent( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBaseUnitEvent)(NStr::ToInt( value ));
	if ( strcmp( value, "Move" ) == 0 || strcmp( value, "BASEUNITEVENT_MOVE" ) == 0 )
		return BASEUNITEVENT_MOVE;
	if ( strcmp( value, "CastMagic" ) == 0 || strcmp( value, "BASEUNITEVENT_CASTMAGIC" ) == 0 )
		return BASEUNITEVENT_CASTMAGIC;
	if ( strcmp( value, "UseConsumable" ) == 0 || strcmp( value, "BASEUNITEVENT_USECONSUMABLE" ) == 0 )
		return BASEUNITEVENT_USECONSUMABLE;
	if ( strcmp( value, "UseTalent" ) == 0 || strcmp( value, "BASEUNITEVENT_USETALENT" ) == 0 )
		return BASEUNITEVENT_USETALENT;
	if ( strcmp( value, "Attack" ) == 0 || strcmp( value, "BASEUNITEVENT_ATTACK" ) == 0 )
		return BASEUNITEVENT_ATTACK;
	if ( strcmp( value, "ForbidMove" ) == 0 || strcmp( value, "BASEUNITEVENT_FORBIDMOVE" ) == 0 )
		return BASEUNITEVENT_FORBIDMOVE;
	if ( strcmp( value, "ForbidAttack" ) == 0 || strcmp( value, "BASEUNITEVENT_FORBIDATTACK" ) == 0 )
		return BASEUNITEVENT_FORBIDATTACK;
	if ( strcmp( value, "ForbidCast" ) == 0 || strcmp( value, "BASEUNITEVENT_FORBIDCAST" ) == 0 )
		return BASEUNITEVENT_FORBIDCAST;
	if ( strcmp( value, "ForcedMove" ) == 0 || strcmp( value, "BASEUNITEVENT_FORCEDMOVE" ) == 0 )
		return BASEUNITEVENT_FORCEDMOVE;
	if ( strcmp( value, "DispatchApplied" ) == 0 || strcmp( value, "BASEUNITEVENT_DISPATCHAPPLIED" ) == 0 )
		return BASEUNITEVENT_DISPATCHAPPLIED;
	if ( strcmp( value, "DispatchEvaded" ) == 0 || strcmp( value, "BASEUNITEVENT_DISPATCHEVADED" ) == 0 )
		return BASEUNITEVENT_DISPATCHEVADED;
	if ( strcmp( value, "Damage" ) == 0 || strcmp( value, "BASEUNITEVENT_DAMAGE" ) == 0 )
		return BASEUNITEVENT_DAMAGE;
	if ( strcmp( value, "Isolate" ) == 0 || strcmp( value, "BASEUNITEVENT_ISOLATE" ) == 0 )
		return BASEUNITEVENT_ISOLATE;
	if ( strcmp( value, "ApplicatorStep" ) == 0 || strcmp( value, "BASEUNITEVENT_APPLICATORSTEP" ) == 0 )
		return BASEUNITEVENT_APPLICATORSTEP;
	if ( strcmp( value, "ApplicatorApplied" ) == 0 || strcmp( value, "BASEUNITEVENT_APPLICATORAPPLIED" ) == 0 )
		return BASEUNITEVENT_APPLICATORAPPLIED;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "BASEUNITEVENT_DEATH" ) == 0 )
		return BASEUNITEVENT_DEATH;
	if ( strcmp( value, "AssignTarget" ) == 0 || strcmp( value, "BASEUNITEVENT_ASSIGNTARGET" ) == 0 )
		return BASEUNITEVENT_ASSIGNTARGET;
	if ( strcmp( value, "LastHit" ) == 0 || strcmp( value, "BASEUNITEVENT_LASTHIT" ) == 0 )
		return BASEUNITEVENT_LASTHIT;
	if ( strcmp( value, "ForbidAutoAttack" ) == 0 || strcmp( value, "BASEUNITEVENT_FORBIDAUTOATTACK" ) == 0 )
		return BASEUNITEVENT_FORBIDAUTOATTACK;
	if ( strcmp( value, "Pickup" ) == 0 || strcmp( value, "BASEUNITEVENT_PICKUP" ) == 0 )
		return BASEUNITEVENT_PICKUP;
	if ( strcmp( value, "Resurrect" ) == 0 || strcmp( value, "BASEUNITEVENT_RESURRECT" ) == 0 )
		return BASEUNITEVENT_RESURRECT;
	if ( strcmp( value, "AbilityStart" ) == 0 || strcmp( value, "BASEUNITEVENT_ABILITYSTART" ) == 0 )
		return BASEUNITEVENT_ABILITYSTART;
	if ( strcmp( value, "ChannelingCanceled" ) == 0 || strcmp( value, "BASEUNITEVENT_CHANNELINGCANCELED" ) == 0 )
		return BASEUNITEVENT_CHANNELINGCANCELED;
	if ( strcmp( value, "CancelInvisibility" ) == 0 || strcmp( value, "BASEUNITEVENT_CANCELINVISIBILITY" ) == 0 )
		return BASEUNITEVENT_CANCELINVISIBILITY;
	if ( strcmp( value, "Unsummon" ) == 0 || strcmp( value, "BASEUNITEVENT_UNSUMMON" ) == 0 )
		return BASEUNITEVENT_UNSUMMON;
	if ( strcmp( value, "ConsumableObtained" ) == 0 || strcmp( value, "BASEUNITEVENT_CONSUMABLEOBTAINED" ) == 0 )
		return BASEUNITEVENT_CONSUMABLEOBTAINED;
	if ( strcmp( value, "UsePortal" ) == 0 || strcmp( value, "BASEUNITEVENT_USEPORTAL" ) == 0 )
		return BASEUNITEVENT_USEPORTAL;
	if ( strcmp( value, "WantMoveTo" ) == 0 || strcmp( value, "BASEUNITEVENT_WANTMOVETO" ) == 0 )
		return BASEUNITEVENT_WANTMOVETO;
	if ( strcmp( value, "OutgoingDamage" ) == 0 || strcmp( value, "BASEUNITEVENT_OUTGOINGDAMAGE" ) == 0 )
		return BASEUNITEVENT_OUTGOINGDAMAGE;
	if ( strcmp( value, "DispatchMissed" ) == 0 || strcmp( value, "BASEUNITEVENT_DISPATCHMISSED" ) == 0 )
		return BASEUNITEVENT_DISPATCHMISSED;
	if ( strcmp( value, "HeroKillOrAssist" ) == 0 || strcmp( value, "BASEUNITEVENT_HEROKILLORASSIST" ) == 0 )
		return BASEUNITEVENT_HEROKILLORASSIST;
	if ( strcmp( value, "MinigameStarted" ) == 0 || strcmp( value, "BASEUNITEVENT_MINIGAMESTARTED" ) == 0 )
		return BASEUNITEVENT_MINIGAMESTARTED;
	if ( strcmp( value, "MinigameExit" ) == 0 || strcmp( value, "BASEUNITEVENT_MINIGAMEEXIT" ) == 0 )
		return BASEUNITEVENT_MINIGAMEEXIT;
	if ( strcmp( value, "MinigameLevelStarted" ) == 0 || strcmp( value, "BASEUNITEVENT_MINIGAMELEVELSTARTED" ) == 0 )
		return BASEUNITEVENT_MINIGAMELEVELSTARTED;
	if ( strcmp( value, "MinigameLevelWon" ) == 0 || strcmp( value, "BASEUNITEVENT_MINIGAMELEVELWON" ) == 0 )
		return BASEUNITEVENT_MINIGAMELEVELWON;
	if ( strcmp( value, "MinigameLevelFailed" ) == 0 || strcmp( value, "BASEUNITEVENT_MINIGAMELEVELFAILED" ) == 0 )
		return BASEUNITEVENT_MINIGAMELEVELFAILED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBaseUnitEvent", value ) );
	return BASEUNITEVENT_MOVE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBaseUnitEventFlags value )
{
	switch( value )
	{
		case BASEUNITEVENTFLAGS_ZERO:
			return "Zero";
		case BASEUNITEVENTFLAGS_MOVE:
			return "Move";
		case BASEUNITEVENTFLAGS_CASTMAGIC:
			return "CastMagic";
		case BASEUNITEVENTFLAGS_USECONSUMABLE:
			return "UseConsumable";
		case BASEUNITEVENTFLAGS_USETALENT:
			return "UseTalent";
		case BASEUNITEVENTFLAGS_ATTACK:
			return "Attack";
		case BASEUNITEVENTFLAGS_FORBIDMOVE:
			return "ForbidMove";
		case BASEUNITEVENTFLAGS_FORBIDATTACK:
			return "ForbidAttack";
		case BASEUNITEVENTFLAGS_FORBIDCAST:
			return "ForbidCast";
		case BASEUNITEVENTFLAGS_FORCEDMOVE:
			return "ForcedMove";
		case BASEUNITEVENTFLAGS_DISPATCHAPPLIED:
			return "DispatchApplied";
		case BASEUNITEVENTFLAGS_DISPATCHEVADED:
			return "DispatchEvaded";
		case BASEUNITEVENTFLAGS_DAMAGE:
			return "Damage";
		case BASEUNITEVENTFLAGS_ISOLATE:
			return "Isolate";
		case BASEUNITEVENTFLAGS_APPLICATORSTEP:
			return "ApplicatorStep";
		case BASEUNITEVENTFLAGS_APPLICATORAPPLIED:
			return "ApplicatorApplied";
		case BASEUNITEVENTFLAGS_DEATH:
			return "Death";
		case BASEUNITEVENTFLAGS_ASSIGNTARGET:
			return "AssignTarget";
		case BASEUNITEVENTFLAGS_LASTHIT:
			return "LastHit";
		case BASEUNITEVENTFLAGS_FORBIDAUTOATTACK:
			return "ForbidAutoAttack";
		case BASEUNITEVENTFLAGS_PICKUP:
			return "Pickup";
		case BASEUNITEVENTFLAGS_RESURRECT:
			return "Resurrect";
		case BASEUNITEVENTFLAGS_ABILITYSTART:
			return "AbilityStart";
		case BASEUNITEVENTFLAGS_CHANNELINGCANCELED:
			return "ChannelingCanceled";
		case BASEUNITEVENTFLAGS_CANCELINVISIBILITY:
			return "CancelInvisibility";
		case BASEUNITEVENTFLAGS_UNSUMMON:
			return "Unsummon";
		case BASEUNITEVENTFLAGS_USEPORTAL:
			return "UsePortal";
		case BASEUNITEVENTFLAGS_DISPATCHMISSED:
			return "DispatchMissed";
		case BASEUNITEVENTFLAGS_HEROKILLORASSIST:
			return "HeroKillOrAssist";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBaseUnitEventFlags StringToEnum_EBaseUnitEventFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBaseUnitEventFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_ZERO" ) == 0 )
		return BASEUNITEVENTFLAGS_ZERO;
	if ( strcmp( value, "Move" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_MOVE" ) == 0 )
		return BASEUNITEVENTFLAGS_MOVE;
	if ( strcmp( value, "CastMagic" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_CASTMAGIC" ) == 0 )
		return BASEUNITEVENTFLAGS_CASTMAGIC;
	if ( strcmp( value, "UseConsumable" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_USECONSUMABLE" ) == 0 )
		return BASEUNITEVENTFLAGS_USECONSUMABLE;
	if ( strcmp( value, "UseTalent" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_USETALENT" ) == 0 )
		return BASEUNITEVENTFLAGS_USETALENT;
	if ( strcmp( value, "Attack" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_ATTACK" ) == 0 )
		return BASEUNITEVENTFLAGS_ATTACK;
	if ( strcmp( value, "ForbidMove" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_FORBIDMOVE" ) == 0 )
		return BASEUNITEVENTFLAGS_FORBIDMOVE;
	if ( strcmp( value, "ForbidAttack" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_FORBIDATTACK" ) == 0 )
		return BASEUNITEVENTFLAGS_FORBIDATTACK;
	if ( strcmp( value, "ForbidCast" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_FORBIDCAST" ) == 0 )
		return BASEUNITEVENTFLAGS_FORBIDCAST;
	if ( strcmp( value, "ForcedMove" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_FORCEDMOVE" ) == 0 )
		return BASEUNITEVENTFLAGS_FORCEDMOVE;
	if ( strcmp( value, "DispatchApplied" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_DISPATCHAPPLIED" ) == 0 )
		return BASEUNITEVENTFLAGS_DISPATCHAPPLIED;
	if ( strcmp( value, "DispatchEvaded" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_DISPATCHEVADED" ) == 0 )
		return BASEUNITEVENTFLAGS_DISPATCHEVADED;
	if ( strcmp( value, "Damage" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_DAMAGE" ) == 0 )
		return BASEUNITEVENTFLAGS_DAMAGE;
	if ( strcmp( value, "Isolate" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_ISOLATE" ) == 0 )
		return BASEUNITEVENTFLAGS_ISOLATE;
	if ( strcmp( value, "ApplicatorStep" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_APPLICATORSTEP" ) == 0 )
		return BASEUNITEVENTFLAGS_APPLICATORSTEP;
	if ( strcmp( value, "ApplicatorApplied" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_APPLICATORAPPLIED" ) == 0 )
		return BASEUNITEVENTFLAGS_APPLICATORAPPLIED;
	if ( strcmp( value, "Death" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_DEATH" ) == 0 )
		return BASEUNITEVENTFLAGS_DEATH;
	if ( strcmp( value, "AssignTarget" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_ASSIGNTARGET" ) == 0 )
		return BASEUNITEVENTFLAGS_ASSIGNTARGET;
	if ( strcmp( value, "LastHit" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_LASTHIT" ) == 0 )
		return BASEUNITEVENTFLAGS_LASTHIT;
	if ( strcmp( value, "ForbidAutoAttack" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_FORBIDAUTOATTACK" ) == 0 )
		return BASEUNITEVENTFLAGS_FORBIDAUTOATTACK;
	if ( strcmp( value, "Pickup" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_PICKUP" ) == 0 )
		return BASEUNITEVENTFLAGS_PICKUP;
	if ( strcmp( value, "Resurrect" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_RESURRECT" ) == 0 )
		return BASEUNITEVENTFLAGS_RESURRECT;
	if ( strcmp( value, "AbilityStart" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_ABILITYSTART" ) == 0 )
		return BASEUNITEVENTFLAGS_ABILITYSTART;
	if ( strcmp( value, "ChannelingCanceled" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_CHANNELINGCANCELED" ) == 0 )
		return BASEUNITEVENTFLAGS_CHANNELINGCANCELED;
	if ( strcmp( value, "CancelInvisibility" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_CANCELINVISIBILITY" ) == 0 )
		return BASEUNITEVENTFLAGS_CANCELINVISIBILITY;
	if ( strcmp( value, "Unsummon" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_UNSUMMON" ) == 0 )
		return BASEUNITEVENTFLAGS_UNSUMMON;
	if ( strcmp( value, "UsePortal" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_USEPORTAL" ) == 0 )
		return BASEUNITEVENTFLAGS_USEPORTAL;
	if ( strcmp( value, "DispatchMissed" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_DISPATCHMISSED" ) == 0 )
		return BASEUNITEVENTFLAGS_DISPATCHMISSED;
	if ( strcmp( value, "HeroKillOrAssist" ) == 0 || strcmp( value, "BASEUNITEVENTFLAGS_HEROKILLORASSIST" ) == 0 )
		return BASEUNITEVENTFLAGS_HEROKILLORASSIST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBaseUnitEventFlags", value ) );
	return BASEUNITEVENTFLAGS_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBehaviourChangeFlags value )
{
	switch( value )
	{
		case BEHAVIOURCHANGEFLAGS_ZERO:
			return "Zero";
		case BEHAVIOURCHANGEFLAGS_DUMMYBEHAVIOUR:
			return "DummyBehaviour";
		case BEHAVIOURCHANGEFLAGS_CHANGEFACTION:
			return "ChangeFaction";
		case BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON:
			return "PrimarySummon";
		case BEHAVIOURCHANGEFLAGS_CHANGEPERMANENTLY:
			return "ChangePermanently";
		case BEHAVIOURCHANGEFLAGS_CHANGETYPE2SUMMON:
			return "ChangeType2Summon";
		case BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR:
			return "DisableBehaviour";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBehaviourChangeFlags StringToEnum_EBehaviourChangeFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBehaviourChangeFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_ZERO" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_ZERO;
	if ( strcmp( value, "DummyBehaviour" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_DUMMYBEHAVIOUR" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_DUMMYBEHAVIOUR;
	if ( strcmp( value, "ChangeFaction" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_CHANGEFACTION" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_CHANGEFACTION;
	if ( strcmp( value, "PrimarySummon" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON;
	if ( strcmp( value, "ChangePermanently" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_CHANGEPERMANENTLY" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_CHANGEPERMANENTLY;
	if ( strcmp( value, "ChangeType2Summon" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_CHANGETYPE2SUMMON" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_CHANGETYPE2SUMMON;
	if ( strcmp( value, "DisableBehaviour" ) == 0 || strcmp( value, "BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR" ) == 0 )
		return BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBehaviourChangeFlags", value ) );
	return BEHAVIOURCHANGEFLAGS_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBetweenUnitsMode value )
{
	switch( value )
	{
		case BETWEENUNITSMODE_ALLPAIRS:
			return "AllPairs";
		case BETWEENUNITSMODE_CHAIN:
			return "Chain";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBetweenUnitsMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBetweenUnitsMode StringToEnum_EBetweenUnitsMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBetweenUnitsMode)(NStr::ToInt( value ));
	if ( strcmp( value, "AllPairs" ) == 0 || strcmp( value, "BETWEENUNITSMODE_ALLPAIRS" ) == 0 )
		return BETWEENUNITSMODE_ALLPAIRS;
	if ( strcmp( value, "Chain" ) == 0 || strcmp( value, "BETWEENUNITSMODE_CHAIN" ) == 0 )
		return BETWEENUNITSMODE_CHAIN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBetweenUnitsMode", value ) );
	return BETWEENUNITSMODE_ALLPAIRS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBounceFlags value )
{
	switch( value )
	{
		case BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS:
			return "BounceNextTargetOnLoss";
		case BOUNCEFLAGS_RENEWTARGETONSTART:
			return "RenewTargetOnStart";
		case BOUNCEFLAGS_STARTFROMOWNER:
			return "StartFromOwner";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBounceFlags StringToEnum_EBounceFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBounceFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "BounceNextTargetOnLoss" ) == 0 || strcmp( value, "BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS" ) == 0 )
		return BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS;
	if ( strcmp( value, "RenewTargetOnStart" ) == 0 || strcmp( value, "BOUNCEFLAGS_RENEWTARGETONSTART" ) == 0 )
		return BOUNCEFLAGS_RENEWTARGETONSTART;
	if ( strcmp( value, "StartFromOwner" ) == 0 || strcmp( value, "BOUNCEFLAGS_STARTFROMOWNER" ) == 0 )
		return BOUNCEFLAGS_STARTFROMOWNER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBounceFlags", value ) );
	return BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBuffBehavior value )
{
	switch( value )
	{
		case BUFFBEHAVIOR_ZERO:
			return "Zero";
		case BUFFBEHAVIOR_STOPONDISABLE:
			return "StopOnDisable";
		case BUFFBEHAVIOR_REMOVECHILDREN:
			return "RemoveChildren";
		case BUFFBEHAVIOR_DONTSHOWINBAR:
			return "DontShowInBar";
		case BUFFBEHAVIOR_DONTSTOPONDEATH:
			return "DontStopOnDeath";
		case BUFFBEHAVIOR_ENABLEDONSENDERDEATH:
			return "EnabledOnSenderDeath";
		case BUFFBEHAVIOR_DONTREMOVEEFFECT:
			return "DontRemoveEffect";
		case BUFFBEHAVIOR_APPLYTODEAD:
			return "ApplyToDead";
		case BUFFBEHAVIOR_DONTSTOPONSENDERDEATH:
			return "DontStopOnSenderDeath";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBuffBehavior StringToEnum_EBuffBehavior( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBuffBehavior)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "BUFFBEHAVIOR_ZERO" ) == 0 )
		return BUFFBEHAVIOR_ZERO;
	if ( strcmp( value, "StopOnDisable" ) == 0 || strcmp( value, "BUFFBEHAVIOR_STOPONDISABLE" ) == 0 )
		return BUFFBEHAVIOR_STOPONDISABLE;
	if ( strcmp( value, "RemoveChildren" ) == 0 || strcmp( value, "BUFFBEHAVIOR_REMOVECHILDREN" ) == 0 )
		return BUFFBEHAVIOR_REMOVECHILDREN;
	if ( strcmp( value, "DontShowInBar" ) == 0 || strcmp( value, "BUFFBEHAVIOR_DONTSHOWINBAR" ) == 0 )
		return BUFFBEHAVIOR_DONTSHOWINBAR;
	if ( strcmp( value, "DontStopOnDeath" ) == 0 || strcmp( value, "BUFFBEHAVIOR_DONTSTOPONDEATH" ) == 0 )
		return BUFFBEHAVIOR_DONTSTOPONDEATH;
	if ( strcmp( value, "EnabledOnSenderDeath" ) == 0 || strcmp( value, "BUFFBEHAVIOR_ENABLEDONSENDERDEATH" ) == 0 )
		return BUFFBEHAVIOR_ENABLEDONSENDERDEATH;
	if ( strcmp( value, "DontRemoveEffect" ) == 0 || strcmp( value, "BUFFBEHAVIOR_DONTREMOVEEFFECT" ) == 0 )
		return BUFFBEHAVIOR_DONTREMOVEEFFECT;
	if ( strcmp( value, "ApplyToDead" ) == 0 || strcmp( value, "BUFFBEHAVIOR_APPLYTODEAD" ) == 0 )
		return BUFFBEHAVIOR_APPLYTODEAD;
	if ( strcmp( value, "DontStopOnSenderDeath" ) == 0 || strcmp( value, "BUFFBEHAVIOR_DONTSTOPONSENDERDEATH" ) == 0 )
		return BUFFBEHAVIOR_DONTSTOPONSENDERDEATH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBuffBehavior", value ) );
	return BUFFBEHAVIOR_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EChannelingType value )
{
	switch( value )
	{
		case CHANNELINGTYPE_STREAMING:
			return "Streaming";
		case CHANNELINGTYPE_CREATION:
			return "Creation";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EChannelingType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EChannelingType StringToEnum_EChannelingType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EChannelingType)(NStr::ToInt( value ));
	if ( strcmp( value, "Streaming" ) == 0 || strcmp( value, "CHANNELINGTYPE_STREAMING" ) == 0 )
		return CHANNELINGTYPE_STREAMING;
	if ( strcmp( value, "Creation" ) == 0 || strcmp( value, "CHANNELINGTYPE_CREATION" ) == 0 )
		return CHANNELINGTYPE_CREATION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EChannelingType", value ) );
	return CHANNELINGTYPE_STREAMING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ECloneFlags value )
{
	switch( value )
	{
		case CLONEFLAGS_NONE:
			return "None";
		case CLONEFLAGS_GHOSTMOVE:
			return "GhostMove";
		case CLONEFLAGS_DOLEVELUP:
			return "DoLevelUp";
		case CLONEFLAGS_MIRROROWNERSPELLS:
			return "MirrorOwnerSpells";
		case CLONEFLAGS_USEABILITYAI:
			return "UseAbilityAI";
		case CLONEFLAGS_PLAYSUMMONEFFECT:
			return "PlaySummonEffect";
		case CLONEFLAGS_MAKESLAVE:
			return "MakeSlave";
		case CLONEFLAGS_COPYSTATS:
			return "CopyStats";
		case CLONEFLAGS_DUMMYBEHAVIOUR:
			return "DummyBehaviour";
		case CLONEFLAGS_INITTALENTS:
			return "InitTalents";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECloneFlags StringToEnum_ECloneFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECloneFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "CLONEFLAGS_NONE" ) == 0 )
		return CLONEFLAGS_NONE;
	if ( strcmp( value, "GhostMove" ) == 0 || strcmp( value, "CLONEFLAGS_GHOSTMOVE" ) == 0 )
		return CLONEFLAGS_GHOSTMOVE;
	if ( strcmp( value, "DoLevelUp" ) == 0 || strcmp( value, "CLONEFLAGS_DOLEVELUP" ) == 0 )
		return CLONEFLAGS_DOLEVELUP;
	if ( strcmp( value, "MirrorOwnerSpells" ) == 0 || strcmp( value, "CLONEFLAGS_MIRROROWNERSPELLS" ) == 0 )
		return CLONEFLAGS_MIRROROWNERSPELLS;
	if ( strcmp( value, "UseAbilityAI" ) == 0 || strcmp( value, "CLONEFLAGS_USEABILITYAI" ) == 0 )
		return CLONEFLAGS_USEABILITYAI;
	if ( strcmp( value, "PlaySummonEffect" ) == 0 || strcmp( value, "CLONEFLAGS_PLAYSUMMONEFFECT" ) == 0 )
		return CLONEFLAGS_PLAYSUMMONEFFECT;
	if ( strcmp( value, "MakeSlave" ) == 0 || strcmp( value, "CLONEFLAGS_MAKESLAVE" ) == 0 )
		return CLONEFLAGS_MAKESLAVE;
	if ( strcmp( value, "CopyStats" ) == 0 || strcmp( value, "CLONEFLAGS_COPYSTATS" ) == 0 )
		return CLONEFLAGS_COPYSTATS;
	if ( strcmp( value, "DummyBehaviour" ) == 0 || strcmp( value, "CLONEFLAGS_DUMMYBEHAVIOUR" ) == 0 )
		return CLONEFLAGS_DUMMYBEHAVIOUR;
	if ( strcmp( value, "InitTalents" ) == 0 || strcmp( value, "CLONEFLAGS_INITTALENTS" ) == 0 )
		return CLONEFLAGS_INITTALENTS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECloneFlags", value ) );
	return CLONEFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EConsumableOriginFlags value )
{
	switch( value )
	{
		case CONSUMABLEORIGINFLAGS_SHOP:
			return "Shop";
		case CONSUMABLEORIGINFLAGS_MINIGAME:
			return "Minigame";
		case CONSUMABLEORIGINFLAGS_PICKUPABLE:
			return "Pickupable";
		case CONSUMABLEORIGINFLAGS_APPLICATOR:
			return "Applicator";
		case CONSUMABLEORIGINFLAGS_SCRIPT:
			return "Script";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EConsumableOriginFlags StringToEnum_EConsumableOriginFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EConsumableOriginFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Shop" ) == 0 || strcmp( value, "CONSUMABLEORIGINFLAGS_SHOP" ) == 0 )
		return CONSUMABLEORIGINFLAGS_SHOP;
	if ( strcmp( value, "Minigame" ) == 0 || strcmp( value, "CONSUMABLEORIGINFLAGS_MINIGAME" ) == 0 )
		return CONSUMABLEORIGINFLAGS_MINIGAME;
	if ( strcmp( value, "Pickupable" ) == 0 || strcmp( value, "CONSUMABLEORIGINFLAGS_PICKUPABLE" ) == 0 )
		return CONSUMABLEORIGINFLAGS_PICKUPABLE;
	if ( strcmp( value, "Applicator" ) == 0 || strcmp( value, "CONSUMABLEORIGINFLAGS_APPLICATOR" ) == 0 )
		return CONSUMABLEORIGINFLAGS_APPLICATOR;
	if ( strcmp( value, "Script" ) == 0 || strcmp( value, "CONSUMABLEORIGINFLAGS_SCRIPT" ) == 0 )
		return CONSUMABLEORIGINFLAGS_SCRIPT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EConsumableOriginFlags", value ) );
	return CONSUMABLEORIGINFLAGS_SHOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDamageFilter value )
{
	switch( value )
	{
		case DAMAGEFILTER_ZERO:
			return "Zero";
		case DAMAGEFILTER_MELEE:
			return "Melee";
		case DAMAGEFILTER_RANGED:
			return "Ranged";
		case DAMAGEFILTER_MATERIAL:
			return "Material";
		case DAMAGEFILTER_ENERGY:
			return "Energy";
		case DAMAGEFILTER_PURE:
			return "Pure";
		case DAMAGEFILTER_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDamageFilter StringToEnum_EDamageFilter( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDamageFilter)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "DAMAGEFILTER_ZERO" ) == 0 )
		return DAMAGEFILTER_ZERO;
	if ( strcmp( value, "Melee" ) == 0 || strcmp( value, "DAMAGEFILTER_MELEE" ) == 0 )
		return DAMAGEFILTER_MELEE;
	if ( strcmp( value, "Ranged" ) == 0 || strcmp( value, "DAMAGEFILTER_RANGED" ) == 0 )
		return DAMAGEFILTER_RANGED;
	if ( strcmp( value, "Material" ) == 0 || strcmp( value, "DAMAGEFILTER_MATERIAL" ) == 0 )
		return DAMAGEFILTER_MATERIAL;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "DAMAGEFILTER_ENERGY" ) == 0 )
		return DAMAGEFILTER_ENERGY;
	if ( strcmp( value, "Pure" ) == 0 || strcmp( value, "DAMAGEFILTER_PURE" ) == 0 )
		return DAMAGEFILTER_PURE;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "DAMAGEFILTER_ALL" ) == 0 )
		return DAMAGEFILTER_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDamageFilter", value ) );
	return DAMAGEFILTER_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDamageMode value )
{
	switch( value )
	{
		case DAMAGEMODE_ZERO:
			return "Zero";
		case DAMAGEMODE_APPLYLIFEDRAINS:
			return "ApplyLifeDrains";
		case DAMAGEMODE_APPLYENERGYDRAINS:
			return "ApplyEnergyDrains";
		case DAMAGEMODE_DONTATTACKBACK:
			return "DontAttackBack";
		case DAMAGEMODE_COULDBECRITICAL:
			return "CouldBeCritical";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDamageMode StringToEnum_EDamageMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDamageMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "DAMAGEMODE_ZERO" ) == 0 )
		return DAMAGEMODE_ZERO;
	if ( strcmp( value, "ApplyLifeDrains" ) == 0 || strcmp( value, "DAMAGEMODE_APPLYLIFEDRAINS" ) == 0 )
		return DAMAGEMODE_APPLYLIFEDRAINS;
	if ( strcmp( value, "ApplyEnergyDrains" ) == 0 || strcmp( value, "DAMAGEMODE_APPLYENERGYDRAINS" ) == 0 )
		return DAMAGEMODE_APPLYENERGYDRAINS;
	if ( strcmp( value, "DontAttackBack" ) == 0 || strcmp( value, "DAMAGEMODE_DONTATTACKBACK" ) == 0 )
		return DAMAGEMODE_DONTATTACKBACK;
	if ( strcmp( value, "CouldBeCritical" ) == 0 || strcmp( value, "DAMAGEMODE_COULDBECRITICAL" ) == 0 )
		return DAMAGEMODE_COULDBECRITICAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDamageMode", value ) );
	return DAMAGEMODE_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDelegateDamageFlags value )
{
	switch( value )
	{
		case DELEGATEDAMAGEFLAGS_ALLOWDRAINS:
			return "AllowDrains";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDelegateDamageFlags StringToEnum_EDelegateDamageFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDelegateDamageFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "AllowDrains" ) == 0 || strcmp( value, "DELEGATEDAMAGEFLAGS_ALLOWDRAINS" ) == 0 )
		return DELEGATEDAMAGEFLAGS_ALLOWDRAINS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDelegateDamageFlags", value ) );
	return DELEGATEDAMAGEFLAGS_ALLOWDRAINS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDispatchAiming value )
{
	switch( value )
	{
		case DISPATCHAIMING_STRAIGHT:
			return "Straight";
		case DISPATCHAIMING_HOMING:
			return "Homing";
		case DISPATCHAIMING_PURSUE:
			return "Pursue";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDispatchAiming", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDispatchAiming StringToEnum_EDispatchAiming( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDispatchAiming)(NStr::ToInt( value ));
	if ( strcmp( value, "Straight" ) == 0 || strcmp( value, "DISPATCHAIMING_STRAIGHT" ) == 0 )
		return DISPATCHAIMING_STRAIGHT;
	if ( strcmp( value, "Homing" ) == 0 || strcmp( value, "DISPATCHAIMING_HOMING" ) == 0 )
		return DISPATCHAIMING_HOMING;
	if ( strcmp( value, "Pursue" ) == 0 || strcmp( value, "DISPATCHAIMING_PURSUE" ) == 0 )
		return DISPATCHAIMING_PURSUE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDispatchAiming", value ) );
	return DISPATCHAIMING_STRAIGHT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDispatchFlags value )
{
	switch( value )
	{
		case DISPATCHFLAGS_UPGRADABLE:
			return "Upgradable";
		case DISPATCHFLAGS_EVADABLE:
			return "Evadable";
		case DISPATCHFLAGS_AGGRESSIVE:
			return "Aggressive";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDispatchFlags StringToEnum_EDispatchFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDispatchFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Upgradable" ) == 0 || strcmp( value, "DISPATCHFLAGS_UPGRADABLE" ) == 0 )
		return DISPATCHFLAGS_UPGRADABLE;
	if ( strcmp( value, "Evadable" ) == 0 || strcmp( value, "DISPATCHFLAGS_EVADABLE" ) == 0 )
		return DISPATCHFLAGS_EVADABLE;
	if ( strcmp( value, "Aggressive" ) == 0 || strcmp( value, "DISPATCHFLAGS_AGGRESSIVE" ) == 0 )
		return DISPATCHFLAGS_AGGRESSIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDispatchFlags", value ) );
	return DISPATCHFLAGS_UPGRADABLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDispatchFlyMode value )
{
	switch( value )
	{
		case DISPATCHFLYMODE_PARABOLIC:
			return "Parabolic";
		case DISPATCHFLYMODE_LINEAR:
			return "Linear";
		case DISPATCHFLYMODE_FIXEDHEIGHT:
			return "FixedHeight";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDispatchFlyMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDispatchFlyMode StringToEnum_EDispatchFlyMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDispatchFlyMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Parabolic" ) == 0 || strcmp( value, "DISPATCHFLYMODE_PARABOLIC" ) == 0 )
		return DISPATCHFLYMODE_PARABOLIC;
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "DISPATCHFLYMODE_LINEAR" ) == 0 )
		return DISPATCHFLYMODE_LINEAR;
	if ( strcmp( value, "FixedHeight" ) == 0 || strcmp( value, "DISPATCHFLYMODE_FIXEDHEIGHT" ) == 0 )
		return DISPATCHFLYMODE_FIXEDHEIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDispatchFlyMode", value ) );
	return DISPATCHFLYMODE_PARABOLIC;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDispatchType value )
{
	switch( value )
	{
		case DISPATCHTYPE_IMMEDIATE:
			return "Immediate";
		case DISPATCHTYPE_LINEAR:
			return "Linear";
		case DISPATCHTYPE_BYTIME:
			return "ByTime";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDispatchType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDispatchType StringToEnum_EDispatchType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDispatchType)(NStr::ToInt( value ));
	if ( strcmp( value, "Immediate" ) == 0 || strcmp( value, "DISPATCHTYPE_IMMEDIATE" ) == 0 )
		return DISPATCHTYPE_IMMEDIATE;
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "DISPATCHTYPE_LINEAR" ) == 0 )
		return DISPATCHTYPE_LINEAR;
	if ( strcmp( value, "ByTime" ) == 0 || strcmp( value, "DISPATCHTYPE_BYTIME" ) == 0 )
		return DISPATCHTYPE_BYTIME;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDispatchType", value ) );
	return DISPATCHTYPE_IMMEDIATE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDispellPriority value )
{
	switch( value )
	{
		case DISPELLPRIORITY_NONDISPELLABLE:
			return "NonDispellable";
		case DISPELLPRIORITY_LOW:
			return "Low";
		case DISPELLPRIORITY_MEDIUM:
			return "Medium";
		case DISPELLPRIORITY_HIGH:
			return "High";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDispellPriority", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDispellPriority StringToEnum_EDispellPriority( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDispellPriority)(NStr::ToInt( value ));
	if ( strcmp( value, "NonDispellable" ) == 0 || strcmp( value, "DISPELLPRIORITY_NONDISPELLABLE" ) == 0 )
		return DISPELLPRIORITY_NONDISPELLABLE;
	if ( strcmp( value, "Low" ) == 0 || strcmp( value, "DISPELLPRIORITY_LOW" ) == 0 )
		return DISPELLPRIORITY_LOW;
	if ( strcmp( value, "Medium" ) == 0 || strcmp( value, "DISPELLPRIORITY_MEDIUM" ) == 0 )
		return DISPELLPRIORITY_MEDIUM;
	if ( strcmp( value, "High" ) == 0 || strcmp( value, "DISPELLPRIORITY_HIGH" ) == 0 )
		return DISPELLPRIORITY_HIGH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDispellPriority", value ) );
	return DISPELLPRIORITY_NONDISPELLABLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFXFlags value )
{
	switch( value )
	{
		case FXFLAGS_APPLYFXTOAUX:
			return "ApplyFXToAux";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFXFlags StringToEnum_EFXFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFXFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "ApplyFXToAux" ) == 0 || strcmp( value, "FXFLAGS_APPLYFXTOAUX" ) == 0 )
		return FXFLAGS_APPLYFXTOAUX;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFXFlags", value ) );
	return FXFLAGS_APPLYFXTOAUX;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGhostMoveMode value )
{
	switch( value )
	{
		case GHOSTMOVEMODE_IGNOREDYNAMIC:
			return "IgnoreDynamic";
		case GHOSTMOVEMODE_IGNOREBUILDINGS:
			return "IgnoreBuildings";
		case GHOSTMOVEMODE_IGNORESTATIC:
			return "IgnoreStatic";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGhostMoveMode StringToEnum_EGhostMoveMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGhostMoveMode)(NStr::ToInt( value ));
	if ( strcmp( value, "IgnoreDynamic" ) == 0 || strcmp( value, "GHOSTMOVEMODE_IGNOREDYNAMIC" ) == 0 )
		return GHOSTMOVEMODE_IGNOREDYNAMIC;
	if ( strcmp( value, "IgnoreBuildings" ) == 0 || strcmp( value, "GHOSTMOVEMODE_IGNOREBUILDINGS" ) == 0 )
		return GHOSTMOVEMODE_IGNOREBUILDINGS;
	if ( strcmp( value, "IgnoreStatic" ) == 0 || strcmp( value, "GHOSTMOVEMODE_IGNORESTATIC" ) == 0 )
		return GHOSTMOVEMODE_IGNORESTATIC;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGhostMoveMode", value ) );
	return GHOSTMOVEMODE_IGNOREDYNAMIC;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EHealTarget value )
{
	switch( value )
	{
		case HEALTARGET_HEALTH:
			return "Health";
		case HEALTARGET_ENERGY:
			return "Energy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EHealTarget", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EHealTarget StringToEnum_EHealTarget( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EHealTarget)(NStr::ToInt( value ));
	if ( strcmp( value, "Health" ) == 0 || strcmp( value, "HEALTARGET_HEALTH" ) == 0 )
		return HEALTARGET_HEALTH;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "HEALTARGET_ENERGY" ) == 0 )
		return HEALTARGET_ENERGY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EHealTarget", value ) );
	return HEALTARGET_HEALTH;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EKickAwayBehaviour value )
{
	switch( value )
	{
		case KICKAWAYBEHAVIOUR_KICKFROMSENDER:
			return "KickFromSender";
		case KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGET:
			return "KickFromHier1UpTarget";
		case KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGETMOVEDIRECTION:
			return "KickFromHier1UpTargetMoveDirection";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EKickAwayBehaviour", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EKickAwayBehaviour StringToEnum_EKickAwayBehaviour( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EKickAwayBehaviour)(NStr::ToInt( value ));
	if ( strcmp( value, "KickFromSender" ) == 0 || strcmp( value, "KICKAWAYBEHAVIOUR_KICKFROMSENDER" ) == 0 )
		return KICKAWAYBEHAVIOUR_KICKFROMSENDER;
	if ( strcmp( value, "KickFromHier1UpTarget" ) == 0 || strcmp( value, "KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGET" ) == 0 )
		return KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGET;
	if ( strcmp( value, "KickFromHier1UpTargetMoveDirection" ) == 0 || strcmp( value, "KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGETMOVEDIRECTION" ) == 0 )
		return KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGETMOVEDIRECTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EKickAwayBehaviour", value ) );
	return KICKAWAYBEHAVIOUR_KICKFROMSENDER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EKillMode value )
{
	switch( value )
	{
		case KILLMODE_NONE:
			return "None";
		case KILLMODE_DONTSHOWDEATH:
			return "DontShowDeath";
		case KILLMODE_INSTANTREMOVE:
			return "InstantRemove";
		case KILLMODE_UNSUMMON:
			return "Unsummon";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EKillMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EKillMode StringToEnum_EKillMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EKillMode)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "KILLMODE_NONE" ) == 0 )
		return KILLMODE_NONE;
	if ( strcmp( value, "DontShowDeath" ) == 0 || strcmp( value, "KILLMODE_DONTSHOWDEATH" ) == 0 )
		return KILLMODE_DONTSHOWDEATH;
	if ( strcmp( value, "InstantRemove" ) == 0 || strcmp( value, "KILLMODE_INSTANTREMOVE" ) == 0 )
		return KILLMODE_INSTANTREMOVE;
	if ( strcmp( value, "Unsummon" ) == 0 || strcmp( value, "KILLMODE_UNSUMMON" ) == 0 )
		return KILLMODE_UNSUMMON;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EKillMode", value ) );
	return KILLMODE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EParentNotification value )
{
	switch( value )
	{
		case PARENTNOTIFICATION_NA:
			return "NA";
		case PARENTNOTIFICATION_START:
			return "Start";
		case PARENTNOTIFICATION_STOP:
			return "Stop";
		case PARENTNOTIFICATION_DONE:
			return "Done";
		case PARENTNOTIFICATION_CANCEL:
			return "Cancel";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EParentNotification", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EParentNotification StringToEnum_EParentNotification( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EParentNotification)(NStr::ToInt( value ));
	if ( strcmp( value, "NA" ) == 0 || strcmp( value, "PARENTNOTIFICATION_NA" ) == 0 )
		return PARENTNOTIFICATION_NA;
	if ( strcmp( value, "Start" ) == 0 || strcmp( value, "PARENTNOTIFICATION_START" ) == 0 )
		return PARENTNOTIFICATION_START;
	if ( strcmp( value, "Stop" ) == 0 || strcmp( value, "PARENTNOTIFICATION_STOP" ) == 0 )
		return PARENTNOTIFICATION_STOP;
	if ( strcmp( value, "Done" ) == 0 || strcmp( value, "PARENTNOTIFICATION_DONE" ) == 0 )
		return PARENTNOTIFICATION_DONE;
	if ( strcmp( value, "Cancel" ) == 0 || strcmp( value, "PARENTNOTIFICATION_CANCEL" ) == 0 )
		return PARENTNOTIFICATION_CANCEL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EParentNotification", value ) );
	return PARENTNOTIFICATION_NA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EParentNotificationFlags value )
{
	switch( value )
	{
		case PARENTNOTIFICATIONFLAGS_ZERO:
			return "Zero";
		case PARENTNOTIFICATIONFLAGS_START:
			return "Start";
		case PARENTNOTIFICATIONFLAGS_STOP:
			return "Stop";
		case PARENTNOTIFICATIONFLAGS_DONE:
			return "Done";
		case PARENTNOTIFICATIONFLAGS_CANCEL:
			return "Cancel";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EParentNotificationFlags StringToEnum_EParentNotificationFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EParentNotificationFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "PARENTNOTIFICATIONFLAGS_ZERO" ) == 0 )
		return PARENTNOTIFICATIONFLAGS_ZERO;
	if ( strcmp( value, "Start" ) == 0 || strcmp( value, "PARENTNOTIFICATIONFLAGS_START" ) == 0 )
		return PARENTNOTIFICATIONFLAGS_START;
	if ( strcmp( value, "Stop" ) == 0 || strcmp( value, "PARENTNOTIFICATIONFLAGS_STOP" ) == 0 )
		return PARENTNOTIFICATIONFLAGS_STOP;
	if ( strcmp( value, "Done" ) == 0 || strcmp( value, "PARENTNOTIFICATIONFLAGS_DONE" ) == 0 )
		return PARENTNOTIFICATIONFLAGS_DONE;
	if ( strcmp( value, "Cancel" ) == 0 || strcmp( value, "PARENTNOTIFICATIONFLAGS_CANCEL" ) == 0 )
		return PARENTNOTIFICATIONFLAGS_CANCEL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EParentNotificationFlags", value ) );
	return PARENTNOTIFICATIONFLAGS_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPointTargetSelectorMode value )
{
	switch( value )
	{
		case POINTTARGETSELECTORMODE_TOOWNER:
			return "ToOwner";
		case POINTTARGETSELECTORMODE_TOTARGET:
			return "ToTarget";
		case POINTTARGETSELECTORMODE_RANGEFROMOWNER:
			return "RangeFromOwner";
		case POINTTARGETSELECTORMODE_RANGEFROMTARGET:
			return "RangeFromTarget";
		case POINTTARGETSELECTORMODE_INTERPOLATION:
			return "Interpolation";
		case POINTTARGETSELECTORMODE_OFFSETFROMOWNER:
			return "OffsetFromOwner";
		case POINTTARGETSELECTORMODE_RANGEFROMTARGETTOREQUESTER:
			return "RangeFromTargetToRequester";
		case POINTTARGETSELECTORMODE_OFFSETFROMTARGET:
			return "OffsetFromTarget";
		case POINTTARGETSELECTORMODE_RANDOMPOINT:
			return "RandomPoint";
		case POINTTARGETSELECTORMODE_RANDOMDIRECTION:
			return "RandomDirection";
		case POINTTARGETSELECTORMODE_RANGEFROMTARGETTOABILITY:
			return "RangeFromTargetToAbility";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPointTargetSelectorMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPointTargetSelectorMode StringToEnum_EPointTargetSelectorMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPointTargetSelectorMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ToOwner" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_TOOWNER" ) == 0 )
		return POINTTARGETSELECTORMODE_TOOWNER;
	if ( strcmp( value, "ToTarget" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_TOTARGET" ) == 0 )
		return POINTTARGETSELECTORMODE_TOTARGET;
	if ( strcmp( value, "RangeFromOwner" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANGEFROMOWNER" ) == 0 )
		return POINTTARGETSELECTORMODE_RANGEFROMOWNER;
	if ( strcmp( value, "RangeFromTarget" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANGEFROMTARGET" ) == 0 )
		return POINTTARGETSELECTORMODE_RANGEFROMTARGET;
	if ( strcmp( value, "Interpolation" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_INTERPOLATION" ) == 0 )
		return POINTTARGETSELECTORMODE_INTERPOLATION;
	if ( strcmp( value, "OffsetFromOwner" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_OFFSETFROMOWNER" ) == 0 )
		return POINTTARGETSELECTORMODE_OFFSETFROMOWNER;
	if ( strcmp( value, "RangeFromTargetToRequester" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANGEFROMTARGETTOREQUESTER" ) == 0 )
		return POINTTARGETSELECTORMODE_RANGEFROMTARGETTOREQUESTER;
	if ( strcmp( value, "OffsetFromTarget" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_OFFSETFROMTARGET" ) == 0 )
		return POINTTARGETSELECTORMODE_OFFSETFROMTARGET;
	if ( strcmp( value, "RandomPoint" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANDOMPOINT" ) == 0 )
		return POINTTARGETSELECTORMODE_RANDOMPOINT;
	if ( strcmp( value, "RandomDirection" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANDOMDIRECTION" ) == 0 )
		return POINTTARGETSELECTORMODE_RANDOMDIRECTION;
	if ( strcmp( value, "RangeFromTargetToAbility" ) == 0 || strcmp( value, "POINTTARGETSELECTORMODE_RANGEFROMTARGETTOABILITY" ) == 0 )
		return POINTTARGETSELECTORMODE_RANGEFROMTARGETTOABILITY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPointTargetSelectorMode", value ) );
	return POINTTARGETSELECTORMODE_TOOWNER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EScaleCalculationMode value )
{
	switch( value )
	{
		case SCALECALCULATIONMODE_SCALEISCOUNT:
			return "ScaleIsCount";
		case SCALECALCULATIONMODE_SCALEISTIME:
			return "ScaleIsTime";
		case SCALECALCULATIONMODE_SCALEISVPAR:
			return "ScaleIsVPar";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EScaleCalculationMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EScaleCalculationMode StringToEnum_EScaleCalculationMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EScaleCalculationMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ScaleIsCount" ) == 0 || strcmp( value, "SCALECALCULATIONMODE_SCALEISCOUNT" ) == 0 )
		return SCALECALCULATIONMODE_SCALEISCOUNT;
	if ( strcmp( value, "ScaleIsTime" ) == 0 || strcmp( value, "SCALECALCULATIONMODE_SCALEISTIME" ) == 0 )
		return SCALECALCULATIONMODE_SCALEISTIME;
	if ( strcmp( value, "ScaleIsVPar" ) == 0 || strcmp( value, "SCALECALCULATIONMODE_SCALEISVPAR" ) == 0 )
		return SCALECALCULATIONMODE_SCALEISVPAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EScaleCalculationMode", value ) );
	return SCALECALCULATIONMODE_SCALEISCOUNT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESortingOrder value )
{
	switch( value )
	{
		case SORTINGORDER_INCREASING:
			return "Increasing";
		case SORTINGORDER_DECREASING:
			return "Decreasing";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESortingOrder", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESortingOrder StringToEnum_ESortingOrder( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESortingOrder)(NStr::ToInt( value ));
	if ( strcmp( value, "Increasing" ) == 0 || strcmp( value, "SORTINGORDER_INCREASING" ) == 0 )
		return SORTINGORDER_INCREASING;
	if ( strcmp( value, "Decreasing" ) == 0 || strcmp( value, "SORTINGORDER_DECREASING" ) == 0 )
		return SORTINGORDER_DECREASING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESortingOrder", value ) );
	return SORTINGORDER_INCREASING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESpellTarget value )
{
	switch( value )
	{
		case SPELLTARGET_HEROMALE:
			return "HeroMale";
		case SPELLTARGET_HEROFEMALE:
			return "HeroFemale";
		case SPELLTARGET_SUMMON:
			return "Summon";
		case SPELLTARGET_CREEP:
			return "Creep";
		case SPELLTARGET_SIEGECREEP:
			return "SiegeCreep";
		case SPELLTARGET_NEUTRALCREEP:
			return "NeutralCreep";
		case SPELLTARGET_TOWER:
			return "Tower";
		case SPELLTARGET_MAINBUILDING:
			return "MainBuilding";
		case SPELLTARGET_BUILDING:
			return "Building";
		case SPELLTARGET_SHOP:
			return "Shop";
		case SPELLTARGET_TREE:
			return "Tree";
		case SPELLTARGET_PICKUPABLE:
			return "Pickupable";
		case SPELLTARGET_MINIGAMEPLACES:
			return "MinigamePlaces";
		case SPELLTARGET_DEADBODIES:
			return "DeadBodies";
		case SPELLTARGET_DUMMYUNIT:
			return "DummyUnit";
		case SPELLTARGET_FLAGPOLE:
			return "Flagpole";
		case SPELLTARGET_NEUTRALCHAMPION:
			return "NeutralChampion";
		case SPELLTARGET_NEUTRALBOSS:
			return "NeutralBoss";
		case SPELLTARGET_FACTIONCHAMPION:
			return "FactionChampion";
		case SPELLTARGET_ALLNEUTRALS:
			return "AllNeutrals";
		case SPELLTARGET_ALL:
			return "All";
		case SPELLTARGET_ALLWOBUILDINGS:
			return "AllWoBuildings";
		case SPELLTARGET_FLYING:
			return "Flying";
		case SPELLTARGET_LINEOFSIGHT:
			return "LineOfSight";
		case SPELLTARGET_VULNERABLETARGETSONLY:
			return "VulnerableTargetsOnly";
		case SPELLTARGET_LAND:
			return "Land";
		case SPELLTARGET_NEUTRAL:
			return "Neutral";
		case SPELLTARGET_AFFECTMOUNTED:
			return "AffectMounted";
		case SPELLTARGET_VISIBLETARGETSONLY:
			return "VisibleTargetsOnly";
		case SPELLTARGET_ALLY:
			return "Ally";
		case SPELLTARGET_ENEMY:
			return "Enemy";
		case SPELLTARGET_SELF:
			return "Self";
		case SPELLTARGET_ALLENEMIES:
			return "AllEnemies";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESpellTarget StringToEnum_ESpellTarget( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESpellTarget)(NStr::ToInt( value ));
	if ( strcmp( value, "HeroMale" ) == 0 || strcmp( value, "SPELLTARGET_HEROMALE" ) == 0 )
		return SPELLTARGET_HEROMALE;
	if ( strcmp( value, "HeroFemale" ) == 0 || strcmp( value, "SPELLTARGET_HEROFEMALE" ) == 0 )
		return SPELLTARGET_HEROFEMALE;
	if ( strcmp( value, "Summon" ) == 0 || strcmp( value, "SPELLTARGET_SUMMON" ) == 0 )
		return SPELLTARGET_SUMMON;
	if ( strcmp( value, "Creep" ) == 0 || strcmp( value, "SPELLTARGET_CREEP" ) == 0 )
		return SPELLTARGET_CREEP;
	if ( strcmp( value, "SiegeCreep" ) == 0 || strcmp( value, "SPELLTARGET_SIEGECREEP" ) == 0 )
		return SPELLTARGET_SIEGECREEP;
	if ( strcmp( value, "NeutralCreep" ) == 0 || strcmp( value, "SPELLTARGET_NEUTRALCREEP" ) == 0 )
		return SPELLTARGET_NEUTRALCREEP;
	if ( strcmp( value, "Tower" ) == 0 || strcmp( value, "SPELLTARGET_TOWER" ) == 0 )
		return SPELLTARGET_TOWER;
	if ( strcmp( value, "MainBuilding" ) == 0 || strcmp( value, "SPELLTARGET_MAINBUILDING" ) == 0 )
		return SPELLTARGET_MAINBUILDING;
	if ( strcmp( value, "Building" ) == 0 || strcmp( value, "SPELLTARGET_BUILDING" ) == 0 )
		return SPELLTARGET_BUILDING;
	if ( strcmp( value, "Shop" ) == 0 || strcmp( value, "SPELLTARGET_SHOP" ) == 0 )
		return SPELLTARGET_SHOP;
	if ( strcmp( value, "Tree" ) == 0 || strcmp( value, "SPELLTARGET_TREE" ) == 0 )
		return SPELLTARGET_TREE;
	if ( strcmp( value, "Pickupable" ) == 0 || strcmp( value, "SPELLTARGET_PICKUPABLE" ) == 0 )
		return SPELLTARGET_PICKUPABLE;
	if ( strcmp( value, "MinigamePlaces" ) == 0 || strcmp( value, "SPELLTARGET_MINIGAMEPLACES" ) == 0 )
		return SPELLTARGET_MINIGAMEPLACES;
	if ( strcmp( value, "DeadBodies" ) == 0 || strcmp( value, "SPELLTARGET_DEADBODIES" ) == 0 )
		return SPELLTARGET_DEADBODIES;
	if ( strcmp( value, "DummyUnit" ) == 0 || strcmp( value, "SPELLTARGET_DUMMYUNIT" ) == 0 )
		return SPELLTARGET_DUMMYUNIT;
	if ( strcmp( value, "Flagpole" ) == 0 || strcmp( value, "SPELLTARGET_FLAGPOLE" ) == 0 )
		return SPELLTARGET_FLAGPOLE;
	if ( strcmp( value, "NeutralChampion" ) == 0 || strcmp( value, "SPELLTARGET_NEUTRALCHAMPION" ) == 0 )
		return SPELLTARGET_NEUTRALCHAMPION;
	if ( strcmp( value, "NeutralBoss" ) == 0 || strcmp( value, "SPELLTARGET_NEUTRALBOSS" ) == 0 )
		return SPELLTARGET_NEUTRALBOSS;
	if ( strcmp( value, "FactionChampion" ) == 0 || strcmp( value, "SPELLTARGET_FACTIONCHAMPION" ) == 0 )
		return SPELLTARGET_FACTIONCHAMPION;
	if ( strcmp( value, "AllNeutrals" ) == 0 || strcmp( value, "SPELLTARGET_ALLNEUTRALS" ) == 0 )
		return SPELLTARGET_ALLNEUTRALS;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "SPELLTARGET_ALL" ) == 0 )
		return SPELLTARGET_ALL;
	if ( strcmp( value, "AllWoBuildings" ) == 0 || strcmp( value, "SPELLTARGET_ALLWOBUILDINGS" ) == 0 )
		return SPELLTARGET_ALLWOBUILDINGS;
	if ( strcmp( value, "Flying" ) == 0 || strcmp( value, "SPELLTARGET_FLYING" ) == 0 )
		return SPELLTARGET_FLYING;
	if ( strcmp( value, "LineOfSight" ) == 0 || strcmp( value, "SPELLTARGET_LINEOFSIGHT" ) == 0 )
		return SPELLTARGET_LINEOFSIGHT;
	if ( strcmp( value, "VulnerableTargetsOnly" ) == 0 || strcmp( value, "SPELLTARGET_VULNERABLETARGETSONLY" ) == 0 )
		return SPELLTARGET_VULNERABLETARGETSONLY;
	if ( strcmp( value, "Land" ) == 0 || strcmp( value, "SPELLTARGET_LAND" ) == 0 )
		return SPELLTARGET_LAND;
	if ( strcmp( value, "Neutral" ) == 0 || strcmp( value, "SPELLTARGET_NEUTRAL" ) == 0 )
		return SPELLTARGET_NEUTRAL;
	if ( strcmp( value, "AffectMounted" ) == 0 || strcmp( value, "SPELLTARGET_AFFECTMOUNTED" ) == 0 )
		return SPELLTARGET_AFFECTMOUNTED;
	if ( strcmp( value, "VisibleTargetsOnly" ) == 0 || strcmp( value, "SPELLTARGET_VISIBLETARGETSONLY" ) == 0 )
		return SPELLTARGET_VISIBLETARGETSONLY;
	if ( strcmp( value, "Ally" ) == 0 || strcmp( value, "SPELLTARGET_ALLY" ) == 0 )
		return SPELLTARGET_ALLY;
	if ( strcmp( value, "Enemy" ) == 0 || strcmp( value, "SPELLTARGET_ENEMY" ) == 0 )
		return SPELLTARGET_ENEMY;
	if ( strcmp( value, "Self" ) == 0 || strcmp( value, "SPELLTARGET_SELF" ) == 0 )
		return SPELLTARGET_SELF;
	if ( strcmp( value, "AllEnemies" ) == 0 || strcmp( value, "SPELLTARGET_ALLENEMIES" ) == 0 )
		return SPELLTARGET_ALLENEMIES;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESpellTarget", value ) );
	return SPELLTARGET_HEROMALE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStackingRule value )
{
	switch( value )
	{
		case STACKINGRULE_UNSTACKABLE:
			return "Unstackable";
		case STACKINGRULE_PARTIALLYSTACKABLE:
			return "PartiallyStackable";
		case STACKINGRULE_FULLYSTACKABLE:
			return "FullyStackable";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStackingRule", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStackingRule StringToEnum_EStackingRule( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStackingRule)(NStr::ToInt( value ));
	if ( strcmp( value, "Unstackable" ) == 0 || strcmp( value, "STACKINGRULE_UNSTACKABLE" ) == 0 )
		return STACKINGRULE_UNSTACKABLE;
	if ( strcmp( value, "PartiallyStackable" ) == 0 || strcmp( value, "STACKINGRULE_PARTIALLYSTACKABLE" ) == 0 )
		return STACKINGRULE_PARTIALLYSTACKABLE;
	if ( strcmp( value, "FullyStackable" ) == 0 || strcmp( value, "STACKINGRULE_FULLYSTACKABLE" ) == 0 )
		return STACKINGRULE_FULLYSTACKABLE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStackingRule", value ) );
	return STACKINGRULE_UNSTACKABLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStatConstraint value )
{
	switch( value )
	{
		case STATCONSTRAINT_NONE:
			return "None";
		case STATCONSTRAINT_UPPERLIMIT:
			return "UpperLimit";
		case STATCONSTRAINT_LOWERLIMIT:
			return "LowerLimit";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStatConstraint", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStatConstraint StringToEnum_EStatConstraint( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStatConstraint)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "STATCONSTRAINT_NONE" ) == 0 )
		return STATCONSTRAINT_NONE;
	if ( strcmp( value, "UpperLimit" ) == 0 || strcmp( value, "STATCONSTRAINT_UPPERLIMIT" ) == 0 )
		return STATCONSTRAINT_UPPERLIMIT;
	if ( strcmp( value, "LowerLimit" ) == 0 || strcmp( value, "STATCONSTRAINT_LOWERLIMIT" ) == 0 )
		return STATCONSTRAINT_LOWERLIMIT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStatConstraint", value ) );
	return STATCONSTRAINT_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStatusFlags value )
{
	switch( value )
	{
		case STATUSFLAGS_NONE:
			return "None";
		case STATUSFLAGS_UPDATELIFETIME:
			return "UpdateLifetime";
		case STATUSFLAGS_ISDEBUFF:
			return "IsDebuff";
		case STATUSFLAGS_STOPSAMECONFLICTED:
			return "StopSameConflicted";
		case STATUSFLAGS_ALWAYSMERGE:
			return "AlwaysMerge";
		case STATUSFLAGS_SHOWSINGLE:
			return "ShowSingle";
		case STATUSFLAGS_STOPALLCONFLICTED:
			return "StopAllConflicted";
		case STATUSFLAGS_ISBUFF:
			return "IsBuff";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStatusFlags StringToEnum_EStatusFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStatusFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "STATUSFLAGS_NONE" ) == 0 )
		return STATUSFLAGS_NONE;
	if ( strcmp( value, "UpdateLifetime" ) == 0 || strcmp( value, "STATUSFLAGS_UPDATELIFETIME" ) == 0 )
		return STATUSFLAGS_UPDATELIFETIME;
	if ( strcmp( value, "IsDebuff" ) == 0 || strcmp( value, "STATUSFLAGS_ISDEBUFF" ) == 0 )
		return STATUSFLAGS_ISDEBUFF;
	if ( strcmp( value, "StopSameConflicted" ) == 0 || strcmp( value, "STATUSFLAGS_STOPSAMECONFLICTED" ) == 0 )
		return STATUSFLAGS_STOPSAMECONFLICTED;
	if ( strcmp( value, "AlwaysMerge" ) == 0 || strcmp( value, "STATUSFLAGS_ALWAYSMERGE" ) == 0 )
		return STATUSFLAGS_ALWAYSMERGE;
	if ( strcmp( value, "ShowSingle" ) == 0 || strcmp( value, "STATUSFLAGS_SHOWSINGLE" ) == 0 )
		return STATUSFLAGS_SHOWSINGLE;
	if ( strcmp( value, "StopAllConflicted" ) == 0 || strcmp( value, "STATUSFLAGS_STOPALLCONFLICTED" ) == 0 )
		return STATUSFLAGS_STOPALLCONFLICTED;
	if ( strcmp( value, "IsBuff" ) == 0 || strcmp( value, "STATUSFLAGS_ISBUFF" ) == 0 )
		return STATUSFLAGS_ISBUFF;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStatusFlags", value ) );
	return STATUSFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStopBehaviour value )
{
	switch( value )
	{
		case STOPBEHAVIOUR_STOPBYTIME:
			return "StopByTime";
		case STOPBEHAVIOUR_STOPBYCHILD:
			return "StopByChild";
		case STOPBEHAVIOUR_STOPBYALLCHILDS:
			return "StopByAllChilds";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStopBehaviour", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStopBehaviour StringToEnum_EStopBehaviour( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStopBehaviour)(NStr::ToInt( value ));
	if ( strcmp( value, "StopByTime" ) == 0 || strcmp( value, "STOPBEHAVIOUR_STOPBYTIME" ) == 0 )
		return STOPBEHAVIOUR_STOPBYTIME;
	if ( strcmp( value, "StopByChild" ) == 0 || strcmp( value, "STOPBEHAVIOUR_STOPBYCHILD" ) == 0 )
		return STOPBEHAVIOUR_STOPBYCHILD;
	if ( strcmp( value, "StopByAllChilds" ) == 0 || strcmp( value, "STOPBEHAVIOUR_STOPBYALLCHILDS" ) == 0 )
		return STOPBEHAVIOUR_STOPBYALLCHILDS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStopBehaviour", value ) );
	return STOPBEHAVIOUR_STOPBYTIME;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESummonFlags value )
{
	switch( value )
	{
		case SUMMONFLAGS_NONE:
			return "None";
		case SUMMONFLAGS_ESSENTIAL:
			return "Essential";
		case SUMMONFLAGS_ALPHASUMMON:
			return "AlphaSummon";
		case SUMMONFLAGS_NOHEALTHPRIORITY:
			return "NoHealthPriority";
		case SUMMONFLAGS_COPYLEVELANDSTATS:
			return "CopyLevelAndStats";
		case SUMMONFLAGS_TURNBYMASTERDIRECTION:
			return "TurnByMasterDirection";
		case SUMMONFLAGS_NOSUMMONANIMATION:
			return "NoSummonAnimation";
		case SUMMONFLAGS_USEGLOWEFFECT:
			return "UseGlowEffect";
		case SUMMONFLAGS_NOCOLLISION:
			return "NoCollision";
		case SUMMONFLAGS_LIKEHERO:
			return "LikeHero";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESummonFlags StringToEnum_ESummonFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESummonFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "SUMMONFLAGS_NONE" ) == 0 )
		return SUMMONFLAGS_NONE;
	if ( strcmp( value, "Essential" ) == 0 || strcmp( value, "SUMMONFLAGS_ESSENTIAL" ) == 0 )
		return SUMMONFLAGS_ESSENTIAL;
	if ( strcmp( value, "AlphaSummon" ) == 0 || strcmp( value, "SUMMONFLAGS_ALPHASUMMON" ) == 0 )
		return SUMMONFLAGS_ALPHASUMMON;
	if ( strcmp( value, "NoHealthPriority" ) == 0 || strcmp( value, "SUMMONFLAGS_NOHEALTHPRIORITY" ) == 0 )
		return SUMMONFLAGS_NOHEALTHPRIORITY;
	if ( strcmp( value, "CopyLevelAndStats" ) == 0 || strcmp( value, "SUMMONFLAGS_COPYLEVELANDSTATS" ) == 0 )
		return SUMMONFLAGS_COPYLEVELANDSTATS;
	if ( strcmp( value, "TurnByMasterDirection" ) == 0 || strcmp( value, "SUMMONFLAGS_TURNBYMASTERDIRECTION" ) == 0 )
		return SUMMONFLAGS_TURNBYMASTERDIRECTION;
	if ( strcmp( value, "NoSummonAnimation" ) == 0 || strcmp( value, "SUMMONFLAGS_NOSUMMONANIMATION" ) == 0 )
		return SUMMONFLAGS_NOSUMMONANIMATION;
	if ( strcmp( value, "UseGlowEffect" ) == 0 || strcmp( value, "SUMMONFLAGS_USEGLOWEFFECT" ) == 0 )
		return SUMMONFLAGS_USEGLOWEFFECT;
	if ( strcmp( value, "NoCollision" ) == 0 || strcmp( value, "SUMMONFLAGS_NOCOLLISION" ) == 0 )
		return SUMMONFLAGS_NOCOLLISION;
	if ( strcmp( value, "LikeHero" ) == 0 || strcmp( value, "SUMMONFLAGS_LIKEHERO" ) == 0 )
		return SUMMONFLAGS_LIKEHERO;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESummonFlags", value ) );
	return SUMMONFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETargetSelectorFlags value )
{
	switch( value )
	{
		case TARGETSELECTORFLAGS_ZERO:
			return "Zero";
		case TARGETSELECTORFLAGS_IGNOREORIGINALTARGET:
			return "IgnoreOriginalTarget";
		case TARGETSELECTORFLAGS_DEADALLOWED:
			return "DeadAllowed";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETargetSelectorFlags StringToEnum_ETargetSelectorFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETargetSelectorFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "TARGETSELECTORFLAGS_ZERO" ) == 0 )
		return TARGETSELECTORFLAGS_ZERO;
	if ( strcmp( value, "IgnoreOriginalTarget" ) == 0 || strcmp( value, "TARGETSELECTORFLAGS_IGNOREORIGINALTARGET" ) == 0 )
		return TARGETSELECTORFLAGS_IGNOREORIGINALTARGET;
	if ( strcmp( value, "DeadAllowed" ) == 0 || strcmp( value, "TARGETSELECTORFLAGS_DEADALLOWED" ) == 0 )
		return TARGETSELECTORFLAGS_DEADALLOWED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETargetSelectorFlags", value ) );
	return TARGETSELECTORFLAGS_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETargetSelectorMode value )
{
	switch( value )
	{
		case TARGETSELECTORMODE_NORMAL:
			return "Normal";
		case TARGETSELECTORMODE_CAPTURETARGETS:
			return "CaptureTargets";
		case TARGETSELECTORMODE_SENDONCE:
			return "SendOnce";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETargetSelectorMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETargetSelectorMode StringToEnum_ETargetSelectorMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETargetSelectorMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "TARGETSELECTORMODE_NORMAL" ) == 0 )
		return TARGETSELECTORMODE_NORMAL;
	if ( strcmp( value, "CaptureTargets" ) == 0 || strcmp( value, "TARGETSELECTORMODE_CAPTURETARGETS" ) == 0 )
		return TARGETSELECTORMODE_CAPTURETARGETS;
	if ( strcmp( value, "SendOnce" ) == 0 || strcmp( value, "TARGETSELECTORMODE_SENDONCE" ) == 0 )
		return TARGETSELECTORMODE_SENDONCE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETargetSelectorMode", value ) );
	return TARGETSELECTORMODE_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETargetSelectorPoint value )
{
	switch( value )
	{
		case TARGETSELECTORPOINT_ABILITYOWNER:
			return "AbilityOwner";
		case TARGETSELECTORPOINT_CURRENTPOSITION:
			return "CurrentPosition";
		case TARGETSELECTORPOINT_PREVIOUSPOSITION:
			return "PreviousPosition";
		case TARGETSELECTORPOINT_OWNERDIRECTION:
			return "OwnerDirection";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETargetSelectorPoint", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETargetSelectorPoint StringToEnum_ETargetSelectorPoint( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETargetSelectorPoint)(NStr::ToInt( value ));
	if ( strcmp( value, "AbilityOwner" ) == 0 || strcmp( value, "TARGETSELECTORPOINT_ABILITYOWNER" ) == 0 )
		return TARGETSELECTORPOINT_ABILITYOWNER;
	if ( strcmp( value, "CurrentPosition" ) == 0 || strcmp( value, "TARGETSELECTORPOINT_CURRENTPOSITION" ) == 0 )
		return TARGETSELECTORPOINT_CURRENTPOSITION;
	if ( strcmp( value, "PreviousPosition" ) == 0 || strcmp( value, "TARGETSELECTORPOINT_PREVIOUSPOSITION" ) == 0 )
		return TARGETSELECTORPOINT_PREVIOUSPOSITION;
	if ( strcmp( value, "OwnerDirection" ) == 0 || strcmp( value, "TARGETSELECTORPOINT_OWNERDIRECTION" ) == 0 )
		return TARGETSELECTORPOINT_OWNERDIRECTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETargetSelectorPoint", value ) );
	return TARGETSELECTORPOINT_ABILITYOWNER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETeamID value )
{
	switch( value )
	{
		case TEAMID_A:
			return "A";
		case TEAMID_B:
			return "B";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETeamID", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETeamID StringToEnum_ETeamID( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETeamID)(NStr::ToInt( value ));
	if ( strcmp( value, "A" ) == 0 || strcmp( value, "TEAMID_A" ) == 0 )
		return TEAMID_A;
	if ( strcmp( value, "B" ) == 0 || strcmp( value, "TEAMID_B" ) == 0 )
		return TEAMID_B;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETeamID", value ) );
	return TEAMID_A;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EThrowType value )
{
	switch( value )
	{
		case THROWTYPE_THROW:
			return "Throw";
		case THROWTYPE_JUMP:
			return "Jump";
		case THROWTYPE_FLIP:
			return "Flip";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EThrowType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EThrowType StringToEnum_EThrowType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EThrowType)(NStr::ToInt( value ));
	if ( strcmp( value, "Throw" ) == 0 || strcmp( value, "THROWTYPE_THROW" ) == 0 )
		return THROWTYPE_THROW;
	if ( strcmp( value, "Jump" ) == 0 || strcmp( value, "THROWTYPE_JUMP" ) == 0 )
		return THROWTYPE_JUMP;
	if ( strcmp( value, "Flip" ) == 0 || strcmp( value, "THROWTYPE_FLIP" ) == 0 )
		return THROWTYPE_FLIP;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EThrowType", value ) );
	return THROWTYPE_THROW;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETraceMode value )
{
	switch( value )
	{
		case TRACEMODE_DYNAMIC:
			return "Dynamic";
		case TRACEMODE_STATIC:
			return "Static";
		case TRACEMODE_BUILDING:
			return "Building";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETraceMode StringToEnum_ETraceMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETraceMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Dynamic" ) == 0 || strcmp( value, "TRACEMODE_DYNAMIC" ) == 0 )
		return TRACEMODE_DYNAMIC;
	if ( strcmp( value, "Static" ) == 0 || strcmp( value, "TRACEMODE_STATIC" ) == 0 )
		return TRACEMODE_STATIC;
	if ( strcmp( value, "Building" ) == 0 || strcmp( value, "TRACEMODE_BUILDING" ) == 0 )
		return TRACEMODE_BUILDING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETraceMode", value ) );
	return TRACEMODE_DYNAMIC;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETriggerAbilitiesAbilitiesFlags value )
{
	switch( value )
	{
		case TRIGGERABILITIESABILITIESFLAGS_NONE:
			return "None";
		case TRIGGERABILITIESABILITIESFLAGS_BASEATTACK:
			return "BaseAttack";
		case TRIGGERABILITIESABILITIESFLAGS_ABILITY0:
			return "Ability0";
		case TRIGGERABILITIESABILITIESFLAGS_ABILITY1:
			return "Ability1";
		case TRIGGERABILITIESABILITIESFLAGS_ABILITY2:
			return "Ability2";
		case TRIGGERABILITIESABILITIESFLAGS_ABILITY3:
			return "Ability3";
		case TRIGGERABILITIESABILITIESFLAGS_ABILITY4:
			return "Ability4";
		case TRIGGERABILITIESABILITIESFLAGS_CONSUMABLE:
			return "Consumable";
		case TRIGGERABILITIESABILITIESFLAGS_TALENT:
			return "Talent";
		case TRIGGERABILITIESABILITIESFLAGS_SPECIAL:
			return "Special";
		case TRIGGERABILITIESABILITIESFLAGS_ALL:
			return "All";
		case TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT:
			return "OnlyClassTalent";
		case TRIGGERABILITIESABILITIESFLAGS_FROMLIST:
			return "FromList";
		case TRIGGERABILITIESABILITIESFLAGS_FROMALLY:
			return "FromAlly";
		case TRIGGERABILITIESABILITIESFLAGS_FROMENEMY:
			return "FromEnemy";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETriggerAbilitiesAbilitiesFlags StringToEnum_ETriggerAbilitiesAbilitiesFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETriggerAbilitiesAbilitiesFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_NONE" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_NONE;
	if ( strcmp( value, "BaseAttack" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_BASEATTACK" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_BASEATTACK;
	if ( strcmp( value, "Ability0" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ABILITY0" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ABILITY0;
	if ( strcmp( value, "Ability1" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ABILITY1" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ABILITY1;
	if ( strcmp( value, "Ability2" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ABILITY2" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ABILITY2;
	if ( strcmp( value, "Ability3" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ABILITY3" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ABILITY3;
	if ( strcmp( value, "Ability4" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ABILITY4" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ABILITY4;
	if ( strcmp( value, "Consumable" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_CONSUMABLE" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_CONSUMABLE;
	if ( strcmp( value, "Talent" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_TALENT" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_TALENT;
	if ( strcmp( value, "Special" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_SPECIAL" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_SPECIAL;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ALL" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ALL;
	if ( strcmp( value, "OnlyClassTalent" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT;
	if ( strcmp( value, "FromList" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_FROMLIST" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_FROMLIST;
	if ( strcmp( value, "FromAlly" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_FROMALLY" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_FROMALLY;
	if ( strcmp( value, "FromEnemy" ) == 0 || strcmp( value, "TRIGGERABILITIESABILITIESFLAGS_FROMENEMY" ) == 0 )
		return TRIGGERABILITIESABILITIESFLAGS_FROMENEMY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETriggerAbilitiesAbilitiesFlags", value ) );
	return TRIGGERABILITIESABILITIESFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETriggerEventCheckSender value )
{
	switch( value )
	{
		case TRIGGEREVENTCHECKSENDER_NONE:
			return "None";
		case TRIGGEREVENTCHECKSENDER_MATCHTARGET:
			return "MatchTarget";
		case TRIGGEREVENTCHECKSENDER_OBJECTFILTER:
			return "ObjectFilter";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETriggerEventCheckSender StringToEnum_ETriggerEventCheckSender( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETriggerEventCheckSender)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "TRIGGEREVENTCHECKSENDER_NONE" ) == 0 )
		return TRIGGEREVENTCHECKSENDER_NONE;
	if ( strcmp( value, "MatchTarget" ) == 0 || strcmp( value, "TRIGGEREVENTCHECKSENDER_MATCHTARGET" ) == 0 )
		return TRIGGEREVENTCHECKSENDER_MATCHTARGET;
	if ( strcmp( value, "ObjectFilter" ) == 0 || strcmp( value, "TRIGGEREVENTCHECKSENDER_OBJECTFILTER" ) == 0 )
		return TRIGGEREVENTCHECKSENDER_OBJECTFILTER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETriggerEventCheckSender", value ) );
	return TRIGGEREVENTCHECKSENDER_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETriggerEventFlags value )
{
	switch( value )
	{
		case TRIGGEREVENTFLAGS_NONE:
			return "None";
		case TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY:
			return "OnlyFirstFromAbility";
		case TRIGGEREVENTFLAGS_ONCEPERSTEP:
			return "OncePerStep";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETriggerEventFlags StringToEnum_ETriggerEventFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETriggerEventFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "TRIGGEREVENTFLAGS_NONE" ) == 0 )
		return TRIGGEREVENTFLAGS_NONE;
	if ( strcmp( value, "OnlyFirstFromAbility" ) == 0 || strcmp( value, "TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY" ) == 0 )
		return TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY;
	if ( strcmp( value, "OncePerStep" ) == 0 || strcmp( value, "TRIGGEREVENTFLAGS_ONCEPERSTEP" ) == 0 )
		return TRIGGEREVENTFLAGS_ONCEPERSTEP;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETriggerEventFlags", value ) );
	return TRIGGEREVENTFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitCreationPlace value )
{
	switch( value )
	{
		case UNITCREATIONPLACE_DIRECTTOTARGET:
			return "DirectToTarget";
		case UNITCREATIONPLACE_ATTARGET:
			return "AtTarget";
		case UNITCREATIONPLACE_ATCREATOR:
			return "AtCreator";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitCreationPlace", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitCreationPlace StringToEnum_EUnitCreationPlace( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitCreationPlace)(NStr::ToInt( value ));
	if ( strcmp( value, "DirectToTarget" ) == 0 || strcmp( value, "UNITCREATIONPLACE_DIRECTTOTARGET" ) == 0 )
		return UNITCREATIONPLACE_DIRECTTOTARGET;
	if ( strcmp( value, "AtTarget" ) == 0 || strcmp( value, "UNITCREATIONPLACE_ATTARGET" ) == 0 )
		return UNITCREATIONPLACE_ATTARGET;
	if ( strcmp( value, "AtCreator" ) == 0 || strcmp( value, "UNITCREATIONPLACE_ATCREATOR" ) == 0 )
		return UNITCREATIONPLACE_ATCREATOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitCreationPlace", value ) );
	return UNITCREATIONPLACE_DIRECTTOTARGET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitFlag value )
{
	switch( value )
	{
		case UNITFLAG_FORBIDMOVE:
			return "ForbidMove";
		case UNITFLAG_FORBIDSELECTTARGET:
			return "ForbidSelectTarget";
		case UNITFLAG_FORBIDATTACK:
			return "ForbidAttack";
		case UNITFLAG_FORBID_ABILITY1:
			return "Forbid_Ability1";
		case UNITFLAG_FORBID_ABILITY2:
			return "Forbid_Ability2";
		case UNITFLAG_FORBID_ABILITY3:
			return "Forbid_Ability3";
		case UNITFLAG_FORBID_ABILITY4:
			return "Forbid_Ability4";
		case UNITFLAG_FORBIDTAKEDAMAGE:
			return "ForbidTakeDamage";
		case UNITFLAG_FORBIDAUTOTARGETME:
			return "ForbidAutotargetMe";
		case UNITFLAG_FORBIDUSECONSUMABLES:
			return "ForbidUseConsumables";
		case UNITFLAG_FORBIDUSETALENTS:
			return "ForbidUseTalents";
		case UNITFLAG_ISOLATED:
			return "Isolated";
		case UNITFLAG_INVISIBLE:
			return "Invisible";
		case UNITFLAG_CANSEEINVISIBLE:
			return "CanSeeInvisible";
		case UNITFLAG_STUN:
			return "Stun";
		case UNITFLAG_FORBIDLIFERESTORE:
			return "ForbidLifeRestore";
		case UNITFLAG_FORBIDENERGYRESTORE:
			return "ForbidEnergyRestore";
		case UNITFLAG_IGNOREINVISIBLE:
			return "IgnoreInvisible";
		case UNITFLAG_FORBIDMOVESPECIAL:
			return "ForbidMoveSpecial";
		case UNITFLAG_FORBIDDEATH:
			return "ForbidDeath";
		case UNITFLAG_FORBIDINTERACT:
			return "ForbidInteract";
		case UNITFLAG_FLYING:
			return "Flying";
		case UNITFLAG_FORBIDAUTOATTACK:
			return "ForbidAutoAttack";
		case UNITFLAG_FORBIDPICK:
			return "ForbidPick";
		case UNITFLAG_FORBIDPLAYERCONTROL:
			return "ForbidPlayerControl";
		case UNITFLAG_CANTURNWHILEFORBIDMOVE:
			return "CanTurnWhileForbidMove";
		case UNITFLAG_FREEZE:
			return "Freeze";
		case UNITFLAG_IGNOREPUSH:
			return "IgnorePush";
		case UNITFLAG_FORBIDINVISIBILITY:
			return "ForbidInvisibility";
		case UNITFLAG_INMINIGAME:
			return "InMinigame";
		case UNITFLAG_LIVEAFTERDEATH:
			return "LiveAfterDeath";
		case UNITFLAG_FORBIDREWARDS:
			return "ForbidRewards";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitFlag StringToEnum_EUnitFlag( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitFlag)(NStr::ToInt( value ));
	if ( strcmp( value, "ForbidMove" ) == 0 || strcmp( value, "UNITFLAG_FORBIDMOVE" ) == 0 )
		return UNITFLAG_FORBIDMOVE;
	if ( strcmp( value, "ForbidSelectTarget" ) == 0 || strcmp( value, "UNITFLAG_FORBIDSELECTTARGET" ) == 0 )
		return UNITFLAG_FORBIDSELECTTARGET;
	if ( strcmp( value, "ForbidAttack" ) == 0 || strcmp( value, "UNITFLAG_FORBIDATTACK" ) == 0 )
		return UNITFLAG_FORBIDATTACK;
	if ( strcmp( value, "Forbid_Ability1" ) == 0 || strcmp( value, "UNITFLAG_FORBID_ABILITY1" ) == 0 )
		return UNITFLAG_FORBID_ABILITY1;
	if ( strcmp( value, "Forbid_Ability2" ) == 0 || strcmp( value, "UNITFLAG_FORBID_ABILITY2" ) == 0 )
		return UNITFLAG_FORBID_ABILITY2;
	if ( strcmp( value, "Forbid_Ability3" ) == 0 || strcmp( value, "UNITFLAG_FORBID_ABILITY3" ) == 0 )
		return UNITFLAG_FORBID_ABILITY3;
	if ( strcmp( value, "Forbid_Ability4" ) == 0 || strcmp( value, "UNITFLAG_FORBID_ABILITY4" ) == 0 )
		return UNITFLAG_FORBID_ABILITY4;
	if ( strcmp( value, "ForbidTakeDamage" ) == 0 || strcmp( value, "UNITFLAG_FORBIDTAKEDAMAGE" ) == 0 )
		return UNITFLAG_FORBIDTAKEDAMAGE;
	if ( strcmp( value, "ForbidAutotargetMe" ) == 0 || strcmp( value, "UNITFLAG_FORBIDAUTOTARGETME" ) == 0 )
		return UNITFLAG_FORBIDAUTOTARGETME;
	if ( strcmp( value, "ForbidUseConsumables" ) == 0 || strcmp( value, "UNITFLAG_FORBIDUSECONSUMABLES" ) == 0 )
		return UNITFLAG_FORBIDUSECONSUMABLES;
	if ( strcmp( value, "ForbidUseTalents" ) == 0 || strcmp( value, "UNITFLAG_FORBIDUSETALENTS" ) == 0 )
		return UNITFLAG_FORBIDUSETALENTS;
	if ( strcmp( value, "Isolated" ) == 0 || strcmp( value, "UNITFLAG_ISOLATED" ) == 0 )
		return UNITFLAG_ISOLATED;
	if ( strcmp( value, "Invisible" ) == 0 || strcmp( value, "UNITFLAG_INVISIBLE" ) == 0 )
		return UNITFLAG_INVISIBLE;
	if ( strcmp( value, "CanSeeInvisible" ) == 0 || strcmp( value, "UNITFLAG_CANSEEINVISIBLE" ) == 0 )
		return UNITFLAG_CANSEEINVISIBLE;
	if ( strcmp( value, "Stun" ) == 0 || strcmp( value, "UNITFLAG_STUN" ) == 0 )
		return UNITFLAG_STUN;
	if ( strcmp( value, "ForbidLifeRestore" ) == 0 || strcmp( value, "UNITFLAG_FORBIDLIFERESTORE" ) == 0 )
		return UNITFLAG_FORBIDLIFERESTORE;
	if ( strcmp( value, "ForbidEnergyRestore" ) == 0 || strcmp( value, "UNITFLAG_FORBIDENERGYRESTORE" ) == 0 )
		return UNITFLAG_FORBIDENERGYRESTORE;
	if ( strcmp( value, "IgnoreInvisible" ) == 0 || strcmp( value, "UNITFLAG_IGNOREINVISIBLE" ) == 0 )
		return UNITFLAG_IGNOREINVISIBLE;
	if ( strcmp( value, "ForbidMoveSpecial" ) == 0 || strcmp( value, "UNITFLAG_FORBIDMOVESPECIAL" ) == 0 )
		return UNITFLAG_FORBIDMOVESPECIAL;
	if ( strcmp( value, "ForbidDeath" ) == 0 || strcmp( value, "UNITFLAG_FORBIDDEATH" ) == 0 )
		return UNITFLAG_FORBIDDEATH;
	if ( strcmp( value, "ForbidInteract" ) == 0 || strcmp( value, "UNITFLAG_FORBIDINTERACT" ) == 0 )
		return UNITFLAG_FORBIDINTERACT;
	if ( strcmp( value, "Flying" ) == 0 || strcmp( value, "UNITFLAG_FLYING" ) == 0 )
		return UNITFLAG_FLYING;
	if ( strcmp( value, "ForbidAutoAttack" ) == 0 || strcmp( value, "UNITFLAG_FORBIDAUTOATTACK" ) == 0 )
		return UNITFLAG_FORBIDAUTOATTACK;
	if ( strcmp( value, "ForbidPick" ) == 0 || strcmp( value, "UNITFLAG_FORBIDPICK" ) == 0 )
		return UNITFLAG_FORBIDPICK;
	if ( strcmp( value, "ForbidPlayerControl" ) == 0 || strcmp( value, "UNITFLAG_FORBIDPLAYERCONTROL" ) == 0 )
		return UNITFLAG_FORBIDPLAYERCONTROL;
	if ( strcmp( value, "CanTurnWhileForbidMove" ) == 0 || strcmp( value, "UNITFLAG_CANTURNWHILEFORBIDMOVE" ) == 0 )
		return UNITFLAG_CANTURNWHILEFORBIDMOVE;
	if ( strcmp( value, "Freeze" ) == 0 || strcmp( value, "UNITFLAG_FREEZE" ) == 0 )
		return UNITFLAG_FREEZE;
	if ( strcmp( value, "IgnorePush" ) == 0 || strcmp( value, "UNITFLAG_IGNOREPUSH" ) == 0 )
		return UNITFLAG_IGNOREPUSH;
	if ( strcmp( value, "ForbidInvisibility" ) == 0 || strcmp( value, "UNITFLAG_FORBIDINVISIBILITY" ) == 0 )
		return UNITFLAG_FORBIDINVISIBILITY;
	if ( strcmp( value, "InMinigame" ) == 0 || strcmp( value, "UNITFLAG_INMINIGAME" ) == 0 )
		return UNITFLAG_INMINIGAME;
	if ( strcmp( value, "LiveAfterDeath" ) == 0 || strcmp( value, "UNITFLAG_LIVEAFTERDEATH" ) == 0 )
		return UNITFLAG_LIVEAFTERDEATH;
	if ( strcmp( value, "ForbidRewards" ) == 0 || strcmp( value, "UNITFLAG_FORBIDREWARDS" ) == 0 )
		return UNITFLAG_FORBIDREWARDS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitFlag", value ) );
	return UNITFLAG_FORBIDMOVE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitFlagType value )
{
	switch( value )
	{
		case UNITFLAGTYPE_FORBIDMOVE:
			return "ForbidMove";
		case UNITFLAGTYPE_FORBIDSELECTTARGET:
			return "ForbidSelectTarget";
		case UNITFLAGTYPE_FORBIDATTACK:
			return "ForbidAttack";
		case UNITFLAGTYPE_FORBID_ABILITY1:
			return "Forbid_Ability1";
		case UNITFLAGTYPE_FORBID_ABILITY2:
			return "Forbid_Ability2";
		case UNITFLAGTYPE_FORBID_ABILITY3:
			return "Forbid_Ability3";
		case UNITFLAGTYPE_FORBID_ABILITY4:
			return "Forbid_Ability4";
		case UNITFLAGTYPE_FORBIDTAKEDAMAGE:
			return "ForbidTakeDamage";
		case UNITFLAGTYPE_FORBIDAUTOTARGETME:
			return "ForbidAutotargetMe";
		case UNITFLAGTYPE_FORBIDUSECONSUMABLES:
			return "ForbidUseConsumables";
		case UNITFLAGTYPE_FORBIDUSETALENTS:
			return "ForbidUseTalents";
		case UNITFLAGTYPE_INVISIBLE:
			return "Invisible";
		case UNITFLAGTYPE_CANSEEINVISIBLE:
			return "CanSeeInvisible";
		case UNITFLAGTYPE_STUN:
			return "Stun";
		case UNITFLAGTYPE_FORBIDLIFERESTORE:
			return "ForbidLifeRestore";
		case UNITFLAGTYPE_FORBIDENERGYRESTORE:
			return "ForbidEnergyRestore";
		case UNITFLAGTYPE_IGNOREINVISIBLE:
			return "IgnoreInvisible";
		case UNITFLAGTYPE_FORBIDMOVESPECIAL:
			return "ForbidMoveSpecial";
		case UNITFLAGTYPE_FORBIDDEATH:
			return "ForbidDeath";
		case UNITFLAGTYPE_FORBIDINTERACT:
			return "ForbidInteract";
		case UNITFLAGTYPE_FLYING:
			return "Flying";
		case UNITFLAGTYPE_FORBIDAUTOATTACK:
			return "ForbidAutoAttack";
		case UNITFLAGTYPE_FORBIDPICK:
			return "ForbidPick";
		case UNITFLAGTYPE_FORBIDPLAYERCONTROL:
			return "ForbidPlayerControl";
		case UNITFLAGTYPE_CANTURNWHILEFORBIDMOVE:
			return "CanTurnWhileForbidMove";
		case UNITFLAGTYPE_FREEZE:
			return "Freeze";
		case UNITFLAGTYPE_IGNOREPUSH:
			return "IgnorePush";
		case UNITFLAGTYPE_FORBIDINVISIBILITY:
			return "ForbidInvisibility";
		case UNITFLAGTYPE_INMINIGAME:
			return "InMinigame";
		case UNITFLAGTYPE_LIVEAFTERDEATH:
			return "LiveAfterDeath";
		case UNITFLAGTYPE_FORBIDREWARDS:
			return "ForbidRewards";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitFlagType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitFlagType StringToEnum_EUnitFlagType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitFlagType)(NStr::ToInt( value ));
	if ( strcmp( value, "ForbidMove" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDMOVE" ) == 0 )
		return UNITFLAGTYPE_FORBIDMOVE;
	if ( strcmp( value, "ForbidSelectTarget" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDSELECTTARGET" ) == 0 )
		return UNITFLAGTYPE_FORBIDSELECTTARGET;
	if ( strcmp( value, "ForbidAttack" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDATTACK" ) == 0 )
		return UNITFLAGTYPE_FORBIDATTACK;
	if ( strcmp( value, "Forbid_Ability1" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBID_ABILITY1" ) == 0 )
		return UNITFLAGTYPE_FORBID_ABILITY1;
	if ( strcmp( value, "Forbid_Ability2" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBID_ABILITY2" ) == 0 )
		return UNITFLAGTYPE_FORBID_ABILITY2;
	if ( strcmp( value, "Forbid_Ability3" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBID_ABILITY3" ) == 0 )
		return UNITFLAGTYPE_FORBID_ABILITY3;
	if ( strcmp( value, "Forbid_Ability4" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBID_ABILITY4" ) == 0 )
		return UNITFLAGTYPE_FORBID_ABILITY4;
	if ( strcmp( value, "ForbidTakeDamage" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDTAKEDAMAGE" ) == 0 )
		return UNITFLAGTYPE_FORBIDTAKEDAMAGE;
	if ( strcmp( value, "ForbidAutotargetMe" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDAUTOTARGETME" ) == 0 )
		return UNITFLAGTYPE_FORBIDAUTOTARGETME;
	if ( strcmp( value, "ForbidUseConsumables" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDUSECONSUMABLES" ) == 0 )
		return UNITFLAGTYPE_FORBIDUSECONSUMABLES;
	if ( strcmp( value, "ForbidUseTalents" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDUSETALENTS" ) == 0 )
		return UNITFLAGTYPE_FORBIDUSETALENTS;
	if ( strcmp( value, "Invisible" ) == 0 || strcmp( value, "UNITFLAGTYPE_INVISIBLE" ) == 0 )
		return UNITFLAGTYPE_INVISIBLE;
	if ( strcmp( value, "CanSeeInvisible" ) == 0 || strcmp( value, "UNITFLAGTYPE_CANSEEINVISIBLE" ) == 0 )
		return UNITFLAGTYPE_CANSEEINVISIBLE;
	if ( strcmp( value, "Stun" ) == 0 || strcmp( value, "UNITFLAGTYPE_STUN" ) == 0 )
		return UNITFLAGTYPE_STUN;
	if ( strcmp( value, "ForbidLifeRestore" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDLIFERESTORE" ) == 0 )
		return UNITFLAGTYPE_FORBIDLIFERESTORE;
	if ( strcmp( value, "ForbidEnergyRestore" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDENERGYRESTORE" ) == 0 )
		return UNITFLAGTYPE_FORBIDENERGYRESTORE;
	if ( strcmp( value, "IgnoreInvisible" ) == 0 || strcmp( value, "UNITFLAGTYPE_IGNOREINVISIBLE" ) == 0 )
		return UNITFLAGTYPE_IGNOREINVISIBLE;
	if ( strcmp( value, "ForbidMoveSpecial" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDMOVESPECIAL" ) == 0 )
		return UNITFLAGTYPE_FORBIDMOVESPECIAL;
	if ( strcmp( value, "ForbidDeath" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDDEATH" ) == 0 )
		return UNITFLAGTYPE_FORBIDDEATH;
	if ( strcmp( value, "ForbidInteract" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDINTERACT" ) == 0 )
		return UNITFLAGTYPE_FORBIDINTERACT;
	if ( strcmp( value, "Flying" ) == 0 || strcmp( value, "UNITFLAGTYPE_FLYING" ) == 0 )
		return UNITFLAGTYPE_FLYING;
	if ( strcmp( value, "ForbidAutoAttack" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDAUTOATTACK" ) == 0 )
		return UNITFLAGTYPE_FORBIDAUTOATTACK;
	if ( strcmp( value, "ForbidPick" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDPICK" ) == 0 )
		return UNITFLAGTYPE_FORBIDPICK;
	if ( strcmp( value, "ForbidPlayerControl" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDPLAYERCONTROL" ) == 0 )
		return UNITFLAGTYPE_FORBIDPLAYERCONTROL;
	if ( strcmp( value, "CanTurnWhileForbidMove" ) == 0 || strcmp( value, "UNITFLAGTYPE_CANTURNWHILEFORBIDMOVE" ) == 0 )
		return UNITFLAGTYPE_CANTURNWHILEFORBIDMOVE;
	if ( strcmp( value, "Freeze" ) == 0 || strcmp( value, "UNITFLAGTYPE_FREEZE" ) == 0 )
		return UNITFLAGTYPE_FREEZE;
	if ( strcmp( value, "IgnorePush" ) == 0 || strcmp( value, "UNITFLAGTYPE_IGNOREPUSH" ) == 0 )
		return UNITFLAGTYPE_IGNOREPUSH;
	if ( strcmp( value, "ForbidInvisibility" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDINVISIBILITY" ) == 0 )
		return UNITFLAGTYPE_FORBIDINVISIBILITY;
	if ( strcmp( value, "InMinigame" ) == 0 || strcmp( value, "UNITFLAGTYPE_INMINIGAME" ) == 0 )
		return UNITFLAGTYPE_INMINIGAME;
	if ( strcmp( value, "LiveAfterDeath" ) == 0 || strcmp( value, "UNITFLAGTYPE_LIVEAFTERDEATH" ) == 0 )
		return UNITFLAGTYPE_LIVEAFTERDEATH;
	if ( strcmp( value, "ForbidRewards" ) == 0 || strcmp( value, "UNITFLAGTYPE_FORBIDREWARDS" ) == 0 )
		return UNITFLAGTYPE_FORBIDREWARDS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitFlagType", value ) );
	return UNITFLAGTYPE_FORBIDMOVE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitRelation value )
{
	switch( value )
	{
		case UNITRELATION_MASTER:
			return "Master";
		case UNITRELATION_TARGET:
			return "Target";
		case UNITRELATION_ALPHASUMMON:
			return "AlphaSummon";
		case UNITRELATION_MOUNT:
			return "Mount";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitRelation", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitRelation StringToEnum_EUnitRelation( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitRelation)(NStr::ToInt( value ));
	if ( strcmp( value, "Master" ) == 0 || strcmp( value, "UNITRELATION_MASTER" ) == 0 )
		return UNITRELATION_MASTER;
	if ( strcmp( value, "Target" ) == 0 || strcmp( value, "UNITRELATION_TARGET" ) == 0 )
		return UNITRELATION_TARGET;
	if ( strcmp( value, "AlphaSummon" ) == 0 || strcmp( value, "UNITRELATION_ALPHASUMMON" ) == 0 )
		return UNITRELATION_ALPHASUMMON;
	if ( strcmp( value, "Mount" ) == 0 || strcmp( value, "UNITRELATION_MOUNT" ) == 0 )
		return UNITRELATION_MOUNT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitRelation", value ) );
	return UNITRELATION_MASTER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUnitType value )
{
	switch( value )
	{
		case UNITTYPE_INVALID:
			return "Invalid";
		case UNITTYPE_HEROMALE:
			return "HeroMale";
		case UNITTYPE_HEROFEMALE:
			return "HeroFemale";
		case UNITTYPE_SUMMON:
			return "Summon";
		case UNITTYPE_CREEP:
			return "Creep";
		case UNITTYPE_SIEGECREEP:
			return "SiegeCreep";
		case UNITTYPE_NEUTRALCREEP:
			return "NeutralCreep";
		case UNITTYPE_TOWER:
			return "Tower";
		case UNITTYPE_BUILDING:
			return "Building";
		case UNITTYPE_MAINBUILDING:
			return "MainBuilding";
		case UNITTYPE_SHOP:
			return "Shop";
		case UNITTYPE_TREE:
			return "Tree";
		case UNITTYPE_PET:
			return "Pet";
		case UNITTYPE_PICKUPABLE:
			return "Pickupable";
		case UNITTYPE_MINIGAMEPLACE:
			return "MinigamePlace";
		case UNITTYPE_DEADBODY:
			return "DeadBody";
		case UNITTYPE_SIMPLEOBJECT:
			return "SimpleObject";
		case UNITTYPE_DUMMYUNIT:
			return "DummyUnit";
		case UNITTYPE_FLAGPOLE:
			return "Flagpole";
		case UNITTYPE_NEUTRALCHAMPION:
			return "NeutralChampion";
		case UNITTYPE_NEUTRALBOSS:
			return "NeutralBoss";
		case UNITTYPE_FACTIONCHAMPION:
			return "FactionChampion";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUnitType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUnitType StringToEnum_EUnitType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUnitType)(NStr::ToInt( value ));
	if ( strcmp( value, "Invalid" ) == 0 || strcmp( value, "UNITTYPE_INVALID" ) == 0 )
		return UNITTYPE_INVALID;
	if ( strcmp( value, "HeroMale" ) == 0 || strcmp( value, "UNITTYPE_HEROMALE" ) == 0 )
		return UNITTYPE_HEROMALE;
	if ( strcmp( value, "HeroFemale" ) == 0 || strcmp( value, "UNITTYPE_HEROFEMALE" ) == 0 )
		return UNITTYPE_HEROFEMALE;
	if ( strcmp( value, "Summon" ) == 0 || strcmp( value, "UNITTYPE_SUMMON" ) == 0 )
		return UNITTYPE_SUMMON;
	if ( strcmp( value, "Creep" ) == 0 || strcmp( value, "UNITTYPE_CREEP" ) == 0 )
		return UNITTYPE_CREEP;
	if ( strcmp( value, "SiegeCreep" ) == 0 || strcmp( value, "UNITTYPE_SIEGECREEP" ) == 0 )
		return UNITTYPE_SIEGECREEP;
	if ( strcmp( value, "NeutralCreep" ) == 0 || strcmp( value, "UNITTYPE_NEUTRALCREEP" ) == 0 )
		return UNITTYPE_NEUTRALCREEP;
	if ( strcmp( value, "Tower" ) == 0 || strcmp( value, "UNITTYPE_TOWER" ) == 0 )
		return UNITTYPE_TOWER;
	if ( strcmp( value, "Building" ) == 0 || strcmp( value, "UNITTYPE_BUILDING" ) == 0 )
		return UNITTYPE_BUILDING;
	if ( strcmp( value, "MainBuilding" ) == 0 || strcmp( value, "UNITTYPE_MAINBUILDING" ) == 0 )
		return UNITTYPE_MAINBUILDING;
	if ( strcmp( value, "Shop" ) == 0 || strcmp( value, "UNITTYPE_SHOP" ) == 0 )
		return UNITTYPE_SHOP;
	if ( strcmp( value, "Tree" ) == 0 || strcmp( value, "UNITTYPE_TREE" ) == 0 )
		return UNITTYPE_TREE;
	if ( strcmp( value, "Pet" ) == 0 || strcmp( value, "UNITTYPE_PET" ) == 0 )
		return UNITTYPE_PET;
	if ( strcmp( value, "Pickupable" ) == 0 || strcmp( value, "UNITTYPE_PICKUPABLE" ) == 0 )
		return UNITTYPE_PICKUPABLE;
	if ( strcmp( value, "MinigamePlace" ) == 0 || strcmp( value, "UNITTYPE_MINIGAMEPLACE" ) == 0 )
		return UNITTYPE_MINIGAMEPLACE;
	if ( strcmp( value, "DeadBody" ) == 0 || strcmp( value, "UNITTYPE_DEADBODY" ) == 0 )
		return UNITTYPE_DEADBODY;
	if ( strcmp( value, "SimpleObject" ) == 0 || strcmp( value, "UNITTYPE_SIMPLEOBJECT" ) == 0 )
		return UNITTYPE_SIMPLEOBJECT;
	if ( strcmp( value, "DummyUnit" ) == 0 || strcmp( value, "UNITTYPE_DUMMYUNIT" ) == 0 )
		return UNITTYPE_DUMMYUNIT;
	if ( strcmp( value, "Flagpole" ) == 0 || strcmp( value, "UNITTYPE_FLAGPOLE" ) == 0 )
		return UNITTYPE_FLAGPOLE;
	if ( strcmp( value, "NeutralChampion" ) == 0 || strcmp( value, "UNITTYPE_NEUTRALCHAMPION" ) == 0 )
		return UNITTYPE_NEUTRALCHAMPION;
	if ( strcmp( value, "NeutralBoss" ) == 0 || strcmp( value, "UNITTYPE_NEUTRALBOSS" ) == 0 )
		return UNITTYPE_NEUTRALBOSS;
	if ( strcmp( value, "FactionChampion" ) == 0 || strcmp( value, "UNITTYPE_FACTIONCHAMPION" ) == 0 )
		return UNITTYPE_FACTIONCHAMPION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUnitType", value ) );
	return UNITTYPE_INVALID;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUpdateDurationFlags value )
{
	switch( value )
	{
		case UPDATEDURATIONFLAGS_NONE:
			return "None";
		case UPDATEDURATIONFLAGS_CHECKBYFORMULANAME:
			return "CheckByFormulaName";
		case UPDATEDURATIONFLAGS_SETDURATION:
			return "SetDuration";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUpdateDurationFlags StringToEnum_EUpdateDurationFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUpdateDurationFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "UPDATEDURATIONFLAGS_NONE" ) == 0 )
		return UPDATEDURATIONFLAGS_NONE;
	if ( strcmp( value, "CheckByFormulaName" ) == 0 || strcmp( value, "UPDATEDURATIONFLAGS_CHECKBYFORMULANAME" ) == 0 )
		return UPDATEDURATIONFLAGS_CHECKBYFORMULANAME;
	if ( strcmp( value, "SetDuration" ) == 0 || strcmp( value, "UPDATEDURATIONFLAGS_SETDURATION" ) == 0 )
		return UPDATEDURATIONFLAGS_SETDURATION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUpdateDurationFlags", value ) );
	return UPDATEDURATIONFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUseMode value )
{
	switch( value )
	{
		case USEMODE_LISTASRULE:
			return "ListAsRule";
		case USEMODE_LISTASEXCEPTION:
			return "ListAsException";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUseMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUseMode StringToEnum_EUseMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUseMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ListAsRule" ) == 0 || strcmp( value, "USEMODE_LISTASRULE" ) == 0 )
		return USEMODE_LISTASRULE;
	if ( strcmp( value, "ListAsException" ) == 0 || strcmp( value, "USEMODE_LISTASEXCEPTION" ) == 0 )
		return USEMODE_LISTASEXCEPTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUseMode", value ) );
	return USEMODE_LISTASRULE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EWaitForSpellBehaviour value )
{
	switch( value )
	{
		case WAITFORSPELLBEHAVIOUR_ZERO:
			return "Zero";
		case WAITFORSPELLBEHAVIOUR_STOPWHENSPELLFINISHED:
			return "StopWhenSpellFinished";
		case WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET:
			return "UpdateParentTarget";
		case WAITFORSPELLBEHAVIOUR_DONTAPPLYEFFECTONFIRSTTARGET:
			return "DontApplyEffectOnFirstTarget";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EWaitForSpellBehaviour StringToEnum_EWaitForSpellBehaviour( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EWaitForSpellBehaviour)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "WAITFORSPELLBEHAVIOUR_ZERO" ) == 0 )
		return WAITFORSPELLBEHAVIOUR_ZERO;
	if ( strcmp( value, "StopWhenSpellFinished" ) == 0 || strcmp( value, "WAITFORSPELLBEHAVIOUR_STOPWHENSPELLFINISHED" ) == 0 )
		return WAITFORSPELLBEHAVIOUR_STOPWHENSPELLFINISHED;
	if ( strcmp( value, "UpdateParentTarget" ) == 0 || strcmp( value, "WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET" ) == 0 )
		return WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET;
	if ( strcmp( value, "DontApplyEffectOnFirstTarget" ) == 0 || strcmp( value, "WAITFORSPELLBEHAVIOUR_DONTAPPLYEFFECTONFIRSTTARGET" ) == 0 )
		return WAITFORSPELLBEHAVIOUR_DONTAPPLYEFFECTONFIRSTTARGET;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EWaitForSpellBehaviour", value ) );
	return WAITFORSPELLBEHAVIOUR_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SummonPlaceMode value )
{
	switch( value )
	{
		case SUMMONPLACEMODE_BYAPPLICATOR:
			return "ByApplicator";
		case SUMMONPLACEMODE_BYTARGETSELECTOR:
			return "ByTargetSelector";
		case SUMMONPLACEMODE_BYBEHAVIOUR:
			return "ByBehaviour";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SummonPlaceMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SummonPlaceMode StringToEnum_SummonPlaceMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SummonPlaceMode)(NStr::ToInt( value ));
	if ( strcmp( value, "ByApplicator" ) == 0 || strcmp( value, "SUMMONPLACEMODE_BYAPPLICATOR" ) == 0 )
		return SUMMONPLACEMODE_BYAPPLICATOR;
	if ( strcmp( value, "ByTargetSelector" ) == 0 || strcmp( value, "SUMMONPLACEMODE_BYTARGETSELECTOR" ) == 0 )
		return SUMMONPLACEMODE_BYTARGETSELECTOR;
	if ( strcmp( value, "ByBehaviour" ) == 0 || strcmp( value, "SUMMONPLACEMODE_BYBEHAVIOUR" ) == 0 )
		return SUMMONPLACEMODE_BYBEHAVIOUR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SummonPlaceMode", value ) );
	return SUMMONPLACEMODE_BYAPPLICATOR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SummonSource value )
{
	switch( value )
	{
		case SUMMONSOURCE_BYAPPLICATOR:
			return "ByApplicator";
		case SUMMONSOURCE_TARGETCLONE:
			return "TargetClone";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SummonSource", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SummonSource StringToEnum_SummonSource( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SummonSource)(NStr::ToInt( value ));
	if ( strcmp( value, "ByApplicator" ) == 0 || strcmp( value, "SUMMONSOURCE_BYAPPLICATOR" ) == 0 )
		return SUMMONSOURCE_BYAPPLICATOR;
	if ( strcmp( value, "TargetClone" ) == 0 || strcmp( value, "SUMMONSOURCE_TARGETCLONE" ) == 0 )
		return SUMMONSOURCE_TARGETCLONE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SummonSource", value ) );
	return SUMMONSOURCE_BYAPPLICATOR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SummonType value )
{
	switch( value )
	{
		case SUMMONTYPE_PRIMARY:
			return "Primary";
		case SUMMONTYPE_SECONDARY:
			return "Secondary";
		case SUMMONTYPE_PET:
			return "Pet";
		case SUMMONTYPE_CLONE:
			return "Clone";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SummonType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SummonType StringToEnum_SummonType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SummonType)(NStr::ToInt( value ));
	if ( strcmp( value, "Primary" ) == 0 || strcmp( value, "SUMMONTYPE_PRIMARY" ) == 0 )
		return SUMMONTYPE_PRIMARY;
	if ( strcmp( value, "Secondary" ) == 0 || strcmp( value, "SUMMONTYPE_SECONDARY" ) == 0 )
		return SUMMONTYPE_SECONDARY;
	if ( strcmp( value, "Pet" ) == 0 || strcmp( value, "SUMMONTYPE_PET" ) == 0 )
		return SUMMONTYPE_PET;
	if ( strcmp( value, "Clone" ) == 0 || strcmp( value, "SUMMONTYPE_CLONE" ) == 0 )
		return SUMMONTYPE_CLONE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SummonType", value ) );
	return SUMMONTYPE_PRIMARY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SummonTypeFlags value )
{
	switch( value )
	{
		case SUMMONTYPEFLAGS_PRIMARY:
			return "Primary";
		case SUMMONTYPEFLAGS_SECONDARY:
			return "Secondary";
		case SUMMONTYPEFLAGS_PET:
			return "Pet";
		case SUMMONTYPEFLAGS_CLONE:
			return "Clone";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SummonTypeFlags StringToEnum_SummonTypeFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SummonTypeFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "Primary" ) == 0 || strcmp( value, "SUMMONTYPEFLAGS_PRIMARY" ) == 0 )
		return SUMMONTYPEFLAGS_PRIMARY;
	if ( strcmp( value, "Secondary" ) == 0 || strcmp( value, "SUMMONTYPEFLAGS_SECONDARY" ) == 0 )
		return SUMMONTYPEFLAGS_SECONDARY;
	if ( strcmp( value, "Pet" ) == 0 || strcmp( value, "SUMMONTYPEFLAGS_PET" ) == 0 )
		return SUMMONTYPEFLAGS_PET;
	if ( strcmp( value, "Clone" ) == 0 || strcmp( value, "SUMMONTYPEFLAGS_CLONE" ) == 0 )
		return SUMMONTYPEFLAGS_CLONE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SummonTypeFlags", value ) );
	return SUMMONTYPEFLAGS_PRIMARY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TargetToLandMode value )
{
	switch( value )
	{
		case TARGETTOLANDMODE_FIRST:
			return "First";
		case TARGETTOLANDMODE_NEAREST:
			return "Nearest";
		case TARGETTOLANDMODE_CENTER:
			return "Center";
		case TARGETTOLANDMODE_CENTERTARGET:
			return "CenterTarget";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TargetToLandMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TargetToLandMode StringToEnum_TargetToLandMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TargetToLandMode)(NStr::ToInt( value ));
	if ( strcmp( value, "First" ) == 0 || strcmp( value, "TARGETTOLANDMODE_FIRST" ) == 0 )
		return TARGETTOLANDMODE_FIRST;
	if ( strcmp( value, "Nearest" ) == 0 || strcmp( value, "TARGETTOLANDMODE_NEAREST" ) == 0 )
		return TARGETTOLANDMODE_NEAREST;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "TARGETTOLANDMODE_CENTER" ) == 0 )
		return TARGETTOLANDMODE_CENTER;
	if ( strcmp( value, "CenterTarget" ) == 0 || strcmp( value, "TARGETTOLANDMODE_CENTERTARGET" ) == 0 )
		return TARGETTOLANDMODE_CENTERTARGET;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TargetToLandMode", value ) );
	return TARGETTOLANDMODE_FIRST;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const UnitDieKillersFlags value )
{
	switch( value )
	{
		case UNITDIEKILLERSFLAGS_KILLEDBYME:
			return "KilledByMe";
		case UNITDIEKILLERSFLAGS_KILLEDBYALLIES:
			return "KilledByAllies";
		case UNITDIEKILLERSFLAGS_KILLEDBYENEMY:
			return "KilledByEnemy";
		case UNITDIEKILLERSFLAGS_KILLEDBYMYSUMMONS:
			return "KilledByMySummons";
		case UNITDIEKILLERSFLAGS_KILLEDBYALL:
			return "KilledByAll";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const UnitDieKillersFlags StringToEnum_UnitDieKillersFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (UnitDieKillersFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "KilledByMe" ) == 0 || strcmp( value, "UNITDIEKILLERSFLAGS_KILLEDBYME" ) == 0 )
		return UNITDIEKILLERSFLAGS_KILLEDBYME;
	if ( strcmp( value, "KilledByAllies" ) == 0 || strcmp( value, "UNITDIEKILLERSFLAGS_KILLEDBYALLIES" ) == 0 )
		return UNITDIEKILLERSFLAGS_KILLEDBYALLIES;
	if ( strcmp( value, "KilledByEnemy" ) == 0 || strcmp( value, "UNITDIEKILLERSFLAGS_KILLEDBYENEMY" ) == 0 )
		return UNITDIEKILLERSFLAGS_KILLEDBYENEMY;
	if ( strcmp( value, "KilledByMySummons" ) == 0 || strcmp( value, "UNITDIEKILLERSFLAGS_KILLEDBYMYSUMMONS" ) == 0 )
		return UNITDIEKILLERSFLAGS_KILLEDBYMYSUMMONS;
	if ( strcmp( value, "KilledByAll" ) == 0 || strcmp( value, "UNITDIEKILLERSFLAGS_KILLEDBYALL" ) == 0 )
		return UNITDIEKILLERSFLAGS_KILLEDBYALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum UnitDieKillersFlags", value ) );
	return UNITDIEKILLERSFLAGS_KILLEDBYME;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicatorToProxy::ApplicatorToProxy()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorToProxy::operator&( IBinSaver &saver )
{
	saver.Add( 2, &applicator );
	saver.Add( 3, &variableNames );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorToProxy::operator&( IXmlSaver &saver )
{
	saver.Add( "applicator", &applicator );
	saver.Add( "variableNames", &variableNames );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicatorToExecute::ApplicatorToExecute() :
		continueEvents( PARENTNOTIFICATIONFLAGS_STOP )
	, stopEvents( PARENTNOTIFICATIONFLAGS_ZERO )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorToExecute::operator&( IBinSaver &saver )
{
	saver.Add( 2, &applicator );
	saver.Add( 3, &delay );
	saver.Add( 4, &continueCondition );
	saver.Add( 5, &stopCondition );
	saver.Add( 6, &continueEvents );
	saver.Add( 7, &stopEvents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorToExecute::operator&( IXmlSaver &saver )
{
	saver.Add( "applicator", &applicator );
	saver.Add( "delay", &delay );
	saver.Add( "continueCondition", &continueCondition );
	saver.Add( "stopCondition", &stopCondition );
	saver.Add( "continueEvents", &continueEvents );
	saver.Add( "stopEvents", &stopEvents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LightningLink::LightningLink()
{
	effect.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningLink::operator&( IBinSaver &saver )
{
	saver.Add( 2, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningLink::operator&( IXmlSaver &saver )
{
	effect.resize( 2 );
	saver.Add( "effect", &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Modifier::Modifier() :
		stat( STAT_LIFE )
	, topModifier( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Modifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stat );
	saver.Add( 3, &variable );
	saver.Add( 4, &addValue );
	saver.Add( 5, &multValue );
	saver.Add( 6, &topModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Modifier::operator&( IXmlSaver &saver )
{
	saver.Add( "stat", &stat );
	saver.Add( "variable", &variable );
	saver.Add( "addValue", &addValue );
	saver.Add( "multValue", &multValue );
	saver.Add( "topModifier", &topModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpawnStats::SpawnStats()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpawnStats::operator&( IBinSaver &saver )
{
	saver.Add( 2, &life );
	saver.Add( 3, &energy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpawnStats::operator&( IXmlSaver &saver )
{
	saver.Add( "life", &life );
	saver.Add( "energy", &energy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonBehaviourCommonParams::SummonBehaviourCommonParams() :
		responseRange( 0.0f )
	, responseTime( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourCommonParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &targetingParams );
	saver.Add( 3, &lashRange );
	saver.Add( 4, &responseRange );
	saver.Add( 5, &responseTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourCommonParams::operator&( IXmlSaver &saver )
{
	saver.Add( "targetingParams", &targetingParams );
	saver.Add( "lashRange", &lashRange );
	saver.Add( "responseRange", &responseRange );
	saver.Add( "responseTime", &responseTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TriggerAbilitiesFilter::TriggerAbilitiesFilter() :
		flags( ETriggerAbilitiesAbilitiesFlags( TRIGGERABILITIESABILITIESFLAGS_FROMENEMY | TRIGGERABILITIESABILITIESFLAGS_FROMALLY | TRIGGERABILITIESABILITIESFLAGS_ALL ) )
	, onlySingleTarget( false )
	, abilityCostMode( ABILITYCOSTMODE_ENERGY )
	, exceptThis( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerAbilitiesFilter::operator&( IBinSaver &saver )
{
	saver.Add( 2, &flags );
	saver.Add( 3, &onlySingleTarget );
	saver.Add( 4, &abilityCostMode );
	saver.Add( 5, &abilitiesList );
	saver.Add( 6, &exceptThis );
	saver.Add( 7, &abilityCondition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerAbilitiesFilter::operator&( IXmlSaver &saver )
{
	saver.Add( "flags", &flags );
	saver.Add( "onlySingleTarget", &onlySingleTarget );
	saver.Add( "abilityCostMode", &abilityCostMode );
	saver.Add( "abilitiesList", &abilitiesList );
	saver.Add( "exceptThis", &exceptThis );
	saver.Add( "abilityCondition", &abilityCondition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Spell::Spell()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spell::operator&( IBinSaver &saver )
{
	saver.Add( 2, &dispatch );
	saver.Add( 3, &applicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spell::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Spell* parentPtr = (Spell*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Spell::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "dispatch", &dispatch );
	saver.Add( "applicators", &applicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Spell::Assign( const Spell& _spell )
{
	dispatch = _spell.dispatch;
	applicators = _spell.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseApplicator::BaseApplicator() :
		applyTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, LoggingEvent( -1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 2, &enabled );
	saver.Add( 3, &applyTarget );
	saver.Add( 4, &formulaName );
	saver.Add( 5, &LoggingEvent );
	saver.Add( 6, &providerName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BaseApplicator* parentPtr = (BaseApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseApplicator::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "enabled", &enabled );
	saver.Add( "applyTarget", &applyTarget );
	saver.Add( "formulaName", &formulaName );
	saver.Add( "LoggingEvent", &LoggingEvent );
	saver.Add( "providerName", &providerName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseApplicator::Assign( const BaseApplicator& _baseApplicator )
{
	enabled = _baseApplicator.enabled;
	applyTarget = _baseApplicator.applyTarget;
	formulaName = _baseApplicator.formulaName;
	LoggingEvent = _baseApplicator.LoggingEvent;
	providerName = _baseApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* BaseApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return ( NWorld::PFBaseApplicator* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BuffApplicator::BuffApplicator() :
		behaviorFlags( BUFFBEHAVIOR_ZERO )
{
	effect.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuffApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &behaviorFlags );
	saver.Add( 3, &lifeTime );
	saver.Add( 4, &effect );
	saver.Add( 5, &startCondition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuffApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BuffApplicator* parentPtr = (BuffApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuffApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "behaviorFlags", &behaviorFlags );
	saver.Add( "lifeTime", &lifeTime );
	effect.resize( 2 );
	saver.Add( "effect", &effect );
	saver.Add( "startCondition", &startCondition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuffApplicator::Assign( const BuffApplicator& _buffApplicator )
{
	behaviorFlags = _buffApplicator.behaviorFlags;
	lifeTime = _buffApplicator.lifeTime;
	effect = _buffApplicator.effect;
	startCondition = _buffApplicator.startCondition;
	enabled = _buffApplicator.enabled;
	applyTarget = _buffApplicator.applyTarget;
	formulaName = _buffApplicator.formulaName;
	LoggingEvent = _buffApplicator.LoggingEvent;
	providerName = _buffApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* BuffApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return ( NWorld::PFBaseApplicator* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityUpgradeApplicator::AbilityUpgradeApplicator() :
		flags( ABILITYUPGRADEMODE_NONE )
	, targetAbility( ABILITYTYPEID_BASEATTACK )
	, useListAs( USEMODE_LISTASRULE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityUpgradeApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &flags );
	saver.Add( 3, &targetAbility );
	saver.Add( 4, &applicators );
	saver.Add( 5, &persistentApplicators );
	saver.Add( 6, &applyCount );
	saver.Add( 7, &talents );
	saver.Add( 8, &useListAs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityUpgradeApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AbilityUpgradeApplicator* parentPtr = (AbilityUpgradeApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityUpgradeApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "flags", &flags );
	saver.Add( "targetAbility", &targetAbility );
	saver.Add( "applicators", &applicators );
	saver.Add( "persistentApplicators", &persistentApplicators );
	saver.Add( "applyCount", &applyCount );
	saver.Add( "talents", &talents );
	saver.Add( "useListAs", &useListAs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityUpgradeApplicator::Assign( const AbilityUpgradeApplicator& _abilityUpgradeApplicator )
{
	flags = _abilityUpgradeApplicator.flags;
	targetAbility = _abilityUpgradeApplicator.targetAbility;
	applicators = _abilityUpgradeApplicator.applicators;
	persistentApplicators = _abilityUpgradeApplicator.persistentApplicators;
	applyCount = _abilityUpgradeApplicator.applyCount;
	talents = _abilityUpgradeApplicator.talents;
	useListAs = _abilityUpgradeApplicator.useListAs;
	behaviorFlags = _abilityUpgradeApplicator.behaviorFlags;
	lifeTime = _abilityUpgradeApplicator.lifeTime;
	effect = _abilityUpgradeApplicator.effect;
	startCondition = _abilityUpgradeApplicator.startCondition;
	enabled = _abilityUpgradeApplicator.enabled;
	applyTarget = _abilityUpgradeApplicator.applyTarget;
	formulaName = _abilityUpgradeApplicator.formulaName;
	LoggingEvent = _abilityUpgradeApplicator.LoggingEvent;
	providerName = _abilityUpgradeApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AbilityUpgradeApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAbilityUpgrade>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityUpgradeTechApplicator::AbilityUpgradeTechApplicator() :
		abilityObjectId( 0 )
	, abilityLastUseStep( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityUpgradeTechApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &abilityObjectId );
	saver.Add( 3, &abilityLastUseStep );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityUpgradeTechApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AbilityUpgradeTechApplicator* parentPtr = (AbilityUpgradeTechApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityUpgradeTechApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "abilityObjectId", &abilityObjectId );
	saver.Add( "abilityLastUseStep", &abilityLastUseStep );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityUpgradeTechApplicator::Assign( const AbilityUpgradeTechApplicator& _abilityUpgradeTechApplicator )
{
	abilityObjectId = _abilityUpgradeTechApplicator.abilityObjectId;
	abilityLastUseStep = _abilityUpgradeTechApplicator.abilityLastUseStep;
	enabled = _abilityUpgradeTechApplicator.enabled;
	applyTarget = _abilityUpgradeTechApplicator.applyTarget;
	formulaName = _abilityUpgradeTechApplicator.formulaName;
	LoggingEvent = _abilityUpgradeTechApplicator.LoggingEvent;
	providerName = _abilityUpgradeTechApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AbilityUpgradeTechApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplTechAbilityUpgrade>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbsorbShieldApplicator::AbsorbShieldApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbsorbShieldApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &damageToAbsorb );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbsorbShieldApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AbsorbShieldApplicator* parentPtr = (AbsorbShieldApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbsorbShieldApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "damageToAbsorb", &damageToAbsorb );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbsorbShieldApplicator::Assign( const AbsorbShieldApplicator& _absorbShieldApplicator )
{
	damageToAbsorb = _absorbShieldApplicator.damageToAbsorb;
	behaviorFlags = _absorbShieldApplicator.behaviorFlags;
	lifeTime = _absorbShieldApplicator.lifeTime;
	effect = _absorbShieldApplicator.effect;
	startCondition = _absorbShieldApplicator.startCondition;
	enabled = _absorbShieldApplicator.enabled;
	applyTarget = _absorbShieldApplicator.applyTarget;
	formulaName = _absorbShieldApplicator.formulaName;
	LoggingEvent = _absorbShieldApplicator.LoggingEvent;
	providerName = _absorbShieldApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AbsorbShieldApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFAbsorbShieldApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AddApplicatorDuration::AddApplicatorDuration() :
		flags( UPDATEDURATIONFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddApplicatorDuration::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &durationToAdd );
	saver.Add( 3, &applicators );
	saver.Add( 4, &flags );
	saver.Add( 5, &nameToCheck );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddApplicatorDuration::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AddApplicatorDuration* parentPtr = (AddApplicatorDuration*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddApplicatorDuration::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "durationToAdd", &durationToAdd );
	saver.Add( "applicators", &applicators );
	saver.Add( "flags", &flags );
	saver.Add( "nameToCheck", &nameToCheck );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddApplicatorDuration::Assign( const AddApplicatorDuration& _addApplicatorDuration )
{
	durationToAdd = _addApplicatorDuration.durationToAdd;
	applicators = _addApplicatorDuration.applicators;
	flags = _addApplicatorDuration.flags;
	nameToCheck = _addApplicatorDuration.nameToCheck;
	enabled = _addApplicatorDuration.enabled;
	applyTarget = _addApplicatorDuration.applyTarget;
	formulaName = _addApplicatorDuration.formulaName;
	LoggingEvent = _addApplicatorDuration.LoggingEvent;
	providerName = _addApplicatorDuration.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AddApplicatorDuration::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAddApplicatorDuration>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AddNaftaApplicator::AddNaftaApplicator() :
		isFromImpulseBuff( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddNaftaApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &nafta );
	saver.Add( 3, &isFromImpulseBuff );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddNaftaApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AddNaftaApplicator* parentPtr = (AddNaftaApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddNaftaApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "nafta", &nafta );
	saver.Add( "isFromImpulseBuff", &isFromImpulseBuff );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddNaftaApplicator::Assign( const AddNaftaApplicator& _addNaftaApplicator )
{
	nafta = _addNaftaApplicator.nafta;
	isFromImpulseBuff = _addNaftaApplicator.isFromImpulseBuff;
	enabled = _addNaftaApplicator.enabled;
	applyTarget = _addNaftaApplicator.applyTarget;
	formulaName = _addNaftaApplicator.formulaName;
	LoggingEvent = _addNaftaApplicator.LoggingEvent;
	providerName = _addNaftaApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AddNaftaApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFAddNaftaApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AlternativeActivity::AlternativeActivity() :
		flags( EAbilityFlags( 0 ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AlternativeActivity::operator&( IBinSaver &saver )
{
	saver.Add( 2, &useRange );
	saver.Add( 3, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AlternativeActivity::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AlternativeActivity* parentPtr = (AlternativeActivity*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AlternativeActivity::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "useRange", &useRange );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AlternativeActivity::Assign( const AlternativeActivity& _alternativeActivity )
{
	useRange = _alternativeActivity.useRange;
	flags = _alternativeActivity.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AlternativeTarget::AlternativeTarget() :
		index( 0 )
	, updateTarget( true )
	, fromMinimap( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AlternativeTarget::operator&( IBinSaver &saver )
{
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &index );
	saver.Add( 4, &updateTarget );
	saver.Add( 5, &fromMinimap );
	saver.Add( 6, &alternativeActivity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AlternativeTarget::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AlternativeTarget* parentPtr = (AlternativeTarget*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AlternativeTarget::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "index", &index );
	saver.Add( "updateTarget", &updateTarget );
	saver.Add( "fromMinimap", &fromMinimap );
	saver.Add( "alternativeActivity", &alternativeActivity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AlternativeTarget::Assign( const AlternativeTarget& _alternativeTarget )
{
	targetSelector = _alternativeTarget.targetSelector;
	index = _alternativeTarget.index;
	updateTarget = _alternativeTarget.updateTarget;
	fromMinimap = _alternativeTarget.fromMinimap;
	alternativeActivity = _alternativeTarget.alternativeActivity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicatorNameOverrider::ApplicatorNameOverrider()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorNameOverrider::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &applicator );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorNameOverrider::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ApplicatorNameOverrider* parentPtr = (ApplicatorNameOverrider*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorNameOverrider::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "applicator", &applicator );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorNameOverrider::Assign( const ApplicatorNameOverrider& _applicatorNameOverrider )
{
	applicator = _applicatorNameOverrider.applicator;
	enabled = _applicatorNameOverrider.enabled;
	applyTarget = _applicatorNameOverrider.applyTarget;
	formulaName = _applicatorNameOverrider.formulaName;
	LoggingEvent = _applicatorNameOverrider.LoggingEvent;
	providerName = _applicatorNameOverrider.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ApplicatorNameOverrider::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFBaseApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TargetSelector::TargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetSelector::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TargetSelector* parentPtr = (TargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetSelector::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetSelector::Assign( const TargetSelector& _targetSelector )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* TargetSelector::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFTargetSelector* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicatorsList::ApplicatorsList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorsList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &applicators );
	saver.Add( 3, &applicatorLists );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorsList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ApplicatorsList* parentPtr = (ApplicatorsList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorsList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "applicators", &applicators );
	saver.Add( "applicatorLists", &applicatorLists );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorsList::Assign( const ApplicatorsList& _applicatorsList )
{
	applicators = _applicatorsList.applicators;
	applicatorLists = _applicatorsList.applicatorLists;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultipleTargetSelector::MultipleTargetSelector() :
		mode( TARGETSELECTORMODE_NORMAL )
	, flags( TARGETSELECTORFLAGS_ZERO )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (TargetSelector*)this );
	saver.Add( 2, &mode );
	saver.Add( 3, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MultipleTargetSelector* parentPtr = (MultipleTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	TargetSelector::SerializeSelf( saver );
	saver.Add( "mode", &mode );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelector::Assign( const MultipleTargetSelector& _multipleTargetSelector )
{
	mode = _multipleTargetSelector.mode;
	flags = _multipleTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* MultipleTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFTargetSelector* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultipleTargetSelectorFiltered::MultipleTargetSelectorFiltered() :
		targetFilter( ESpellTarget( SPELLTARGET_ALLENEMIES | SPELLTARGET_VISIBLETARGETSONLY ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelectorFiltered::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetFilter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelectorFiltered::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MultipleTargetSelectorFiltered* parentPtr = (MultipleTargetSelectorFiltered*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelectorFiltered::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetFilter", &targetFilter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelectorFiltered::Assign( const MultipleTargetSelectorFiltered& _multipleTargetSelectorFiltered )
{
	targetFilter = _multipleTargetSelectorFiltered.targetFilter;
	mode = _multipleTargetSelectorFiltered.mode;
	flags = _multipleTargetSelectorFiltered.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* MultipleTargetSelectorFiltered::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFTargetSelector* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttackTargetApplicator::AttackTargetApplicator() :
		attackTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, attackCount( -1 )
	, evadeAction( ATTACKTARGETEVADEACTION_STOPASFAILED )
	, ignoreVisibility( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackTargetApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &attackTarget );
	saver.Add( 3, &attackCount );
	saver.Add( 4, &evadeAction );
	saver.Add( 5, &ignoreVisibility );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackTargetApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AttackTargetApplicator* parentPtr = (AttackTargetApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttackTargetApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "attackTarget", &attackTarget );
	saver.Add( "attackCount", &attackCount );
	saver.Add( "evadeAction", &evadeAction );
	saver.Add( "ignoreVisibility", &ignoreVisibility );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttackTargetApplicator::Assign( const AttackTargetApplicator& _attackTargetApplicator )
{
	attackTarget = _attackTargetApplicator.attackTarget;
	attackCount = _attackTargetApplicator.attackCount;
	evadeAction = _attackTargetApplicator.evadeAction;
	ignoreVisibility = _attackTargetApplicator.ignoreVisibility;
	behaviorFlags = _attackTargetApplicator.behaviorFlags;
	lifeTime = _attackTargetApplicator.lifeTime;
	effect = _attackTargetApplicator.effect;
	startCondition = _attackTargetApplicator.startCondition;
	enabled = _attackTargetApplicator.enabled;
	applyTarget = _attackTargetApplicator.applyTarget;
	formulaName = _attackTargetApplicator.formulaName;
	LoggingEvent = _attackTargetApplicator.LoggingEvent;
	providerName = _attackTargetApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AttackTargetApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAttackTarget>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttractApplicator::AttractApplicator() :
		distance( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttractApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &distance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttractApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AttractApplicator* parentPtr = (AttractApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttractApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "distance", &distance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttractApplicator::Assign( const AttractApplicator& _attractApplicator )
{
	distance = _attractApplicator.distance;
	enabled = _attractApplicator.enabled;
	applyTarget = _attractApplicator.applyTarget;
	formulaName = _attractApplicator.formulaName;
	LoggingEvent = _attractApplicator.LoggingEvent;
	providerName = _attractApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AttractApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAttract>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AuraApplicator::AuraApplicator() :
		targets( ESpellTarget( SPELLTARGET_VULNERABLETARGETSONLY | SPELLTARGET_ALL ) )
	, type( AURAVISUALTYPE_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &range );
	saver.Add( 4, &targets );
	saver.Add( 5, &type );
	saver.Add( 6, &applicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AuraApplicator* parentPtr = (AuraApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuraApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "range", &range );
	saver.Add( "targets", &targets );
	saver.Add( "type", &type );
	saver.Add( "applicators", &applicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuraApplicator::Assign( const AuraApplicator& _auraApplicator )
{
	targetSelector = _auraApplicator.targetSelector;
	range = _auraApplicator.range;
	targets = _auraApplicator.targets;
	type = _auraApplicator.type;
	applicators = _auraApplicator.applicators;
	behaviorFlags = _auraApplicator.behaviorFlags;
	lifeTime = _auraApplicator.lifeTime;
	effect = _auraApplicator.effect;
	startCondition = _auraApplicator.startCondition;
	enabled = _auraApplicator.enabled;
	applyTarget = _auraApplicator.applyTarget;
	formulaName = _auraApplicator.formulaName;
	LoggingEvent = _auraApplicator.LoggingEvent;
	providerName = _auraApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AuraApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAura>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityEndApplicator::AbilityEndApplicator() :
		cancelApplicators( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityEndApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &cancelApplicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityEndApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AbilityEndApplicator* parentPtr = (AbilityEndApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityEndApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "cancelApplicators", &cancelApplicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityEndApplicator::Assign( const AbilityEndApplicator& _abilityEndApplicator )
{
	cancelApplicators = _abilityEndApplicator.cancelApplicators;
	enabled = _abilityEndApplicator.enabled;
	applyTarget = _abilityEndApplicator.applyTarget;
	formulaName = _abilityEndApplicator.formulaName;
	LoggingEvent = _abilityEndApplicator.LoggingEvent;
	providerName = _abilityEndApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AbilityEndApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAbilityEnd>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ability::Ability() :
		aoeType( ABILITYAOEVISUAL_NONE )
	, aoeHeight( 0.0f )
	, aoePassabilityCheckMode( ETraceMode( 0 ) )
	, aoeDisplayOnMinimap( false )
	, type( ABILITYTYPE_PASSIVE )
	, activeCustomTrigger( true )
	, minUseRangeCorrection( 0.0f )
	, isUnitFreeAfterCast( true )
	, flags( ABILITYFLAGS_FOCUSONTARGET )
	, targetType( ESpellTarget( SPELLTARGET_VISIBLETARGETSONLY | SPELLTARGET_ALL ) )
	, requireLineOfSight( true )
	, warFogRemoveTime( 0.0f )
	, warFogRemoveRadius( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Ability::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Spell*)this );
	saver.Add( 2, &name );
	saver.Add( 3, &description );
	saver.Add( 4, &compiledDescriptionA );
	saver.Add( 5, &compiledDescriptionB );
	saver.Add( 6, &shortDescription );
	saver.Add( 7, &commonDescription );
	saver.Add( 8, &castLimitations );
	saver.Add( 9, &image );
	saver.Add( 10, &imageSecondState );
	saver.Add( 11, &aoeType );
	saver.Add( 12, &aoeSize );
	saver.Add( 13, &aoeMaterial );
	saver.Add( 14, &aoeHeight );
	saver.Add( 15, &useRangeMaterial );
	saver.Add( 16, &aoePassabilityCheckMode );
	saver.Add( 17, &aoeDisplayOnMinimap );
	saver.Add( 18, &type );
	saver.Add( 19, &cooldownTime );
	saver.Add( 20, &cooldownTimeSecondState );
	saver.Add( 21, &manaCost );
	saver.Add( 22, &activeCustomTrigger );
	saver.Add( 23, &useRange );
	saver.Add( 24, &minUseRangeCorrection );
	saver.Add( 25, &castAllowRange );
	saver.Add( 26, &allowChase );
	saver.Add( 27, &constants );
	saver.Add( 28, &conditionFormulas );
	saver.Add( 29, &isUnitFreeAfterCast );
	saver.Add( 30, &flags );
	saver.Add( 31, &targetType );
	saver.Add( 32, &requireLineOfSight );
	saver.Add( 33, &passiveApplicators );
	saver.Add( 34, &autoTargetSelector );
	saver.Add( 35, &microAI );
	saver.Add( 36, &node );
	saver.Add( 37, &marker );
	saver.Add( 38, &warFogRemoveTime );
	saver.Add( 39, &warFogRemoveRadius );
	saver.Add( 40, &alternativeTargets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Ability::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Ability* parentPtr = (Ability*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ability::SerializeSelf( IXmlSaver &saver )
{
	Spell::SerializeSelf( saver );
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "compiledDescriptionA", &compiledDescriptionA );
	saver.Add( "compiledDescriptionB", &compiledDescriptionB );
	saver.Add( "shortDescription", &shortDescription );
	saver.Add( "commonDescription", &commonDescription );
	saver.Add( "castLimitations", &castLimitations );
	saver.Add( "image", &image );
	saver.Add( "imageSecondState", &imageSecondState );
	saver.Add( "aoeType", &aoeType );
	saver.Add( "aoeSize", &aoeSize );
	saver.Add( "aoeMaterial", &aoeMaterial );
	saver.Add( "aoeHeight", &aoeHeight );
	saver.Add( "useRangeMaterial", &useRangeMaterial );
	saver.Add( "aoePassabilityCheckMode", &aoePassabilityCheckMode );
	saver.Add( "aoeDisplayOnMinimap", &aoeDisplayOnMinimap );
	saver.Add( "type", &type );
	saver.Add( "cooldownTime", &cooldownTime );
	saver.Add( "cooldownTimeSecondState", &cooldownTimeSecondState );
	saver.Add( "manaCost", &manaCost );
	saver.Add( "activeCustomTrigger", &activeCustomTrigger );
	saver.Add( "useRange", &useRange );
	saver.Add( "minUseRangeCorrection", &minUseRangeCorrection );
	saver.Add( "castAllowRange", &castAllowRange );
	saver.Add( "allowChase", &allowChase );
	saver.Add( "constants", &constants );
	saver.Add( "conditionFormulas", &conditionFormulas );
	saver.Add( "isUnitFreeAfterCast", &isUnitFreeAfterCast );
	saver.Add( "flags", &flags );
	saver.Add( "targetType", &targetType );
	saver.Add( "requireLineOfSight", &requireLineOfSight );
	saver.Add( "passiveApplicators", &passiveApplicators );
	saver.Add( "autoTargetSelector", &autoTargetSelector );
	saver.Add( "microAI", &microAI );
	saver.Add( "node", &node );
	saver.Add( "marker", &marker );
	saver.Add( "warFogRemoveTime", &warFogRemoveTime );
	saver.Add( "warFogRemoveRadius", &warFogRemoveRadius );
	saver.Add( "alternativeTargets", &alternativeTargets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ability::Assign( const Ability& _ability )
{
	name = _ability.name;
	description = _ability.description;
	compiledDescriptionA = _ability.compiledDescriptionA;
	compiledDescriptionB = _ability.compiledDescriptionB;
	shortDescription = _ability.shortDescription;
	commonDescription = _ability.commonDescription;
	castLimitations = _ability.castLimitations;
	image = _ability.image;
	imageSecondState = _ability.imageSecondState;
	aoeType = _ability.aoeType;
	aoeSize = _ability.aoeSize;
	aoeMaterial = _ability.aoeMaterial;
	aoeHeight = _ability.aoeHeight;
	useRangeMaterial = _ability.useRangeMaterial;
	aoePassabilityCheckMode = _ability.aoePassabilityCheckMode;
	aoeDisplayOnMinimap = _ability.aoeDisplayOnMinimap;
	type = _ability.type;
	cooldownTime = _ability.cooldownTime;
	cooldownTimeSecondState = _ability.cooldownTimeSecondState;
	manaCost = _ability.manaCost;
	activeCustomTrigger = _ability.activeCustomTrigger;
	useRange = _ability.useRange;
	minUseRangeCorrection = _ability.minUseRangeCorrection;
	castAllowRange = _ability.castAllowRange;
	allowChase = _ability.allowChase;
	constants = _ability.constants;
	conditionFormulas = _ability.conditionFormulas;
	isUnitFreeAfterCast = _ability.isUnitFreeAfterCast;
	flags = _ability.flags;
	targetType = _ability.targetType;
	requireLineOfSight = _ability.requireLineOfSight;
	passiveApplicators = _ability.passiveApplicators;
	autoTargetSelector = _ability.autoTargetSelector;
	microAI = _ability.microAI;
	node = _ability.node;
	marker = _ability.marker;
	warFogRemoveTime = _ability.warFogRemoveTime;
	warFogRemoveRadius = _ability.warFogRemoveRadius;
	alternativeTargets = _ability.alternativeTargets;
	dispatch = _ability.dispatch;
	applicators = _ability.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MicroAI::MicroAI()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MicroAI::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MicroAI::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MicroAI* parentPtr = (MicroAI*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MicroAI::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MicroAI::Assign( const MicroAI& _microAI )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFMicroAI* MicroAI::Create( NWorld::PFMicroAICreateParams const &cp ) const
{
	return ( NWorld::PFMicroAI* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BetweenUnitsTargetSelector::BetweenUnitsTargetSelector() :
		pairMode( BETWEENUNITSMODE_ALLPAIRS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BetweenUnitsTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &maxTargets );
	saver.Add( 4, &pairMode );
	saver.Add( 5, &minDistBetweenTargets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BetweenUnitsTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BetweenUnitsTargetSelector* parentPtr = (BetweenUnitsTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BetweenUnitsTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "maxTargets", &maxTargets );
	saver.Add( "pairMode", &pairMode );
	saver.Add( "minDistBetweenTargets", &minDistBetweenTargets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BetweenUnitsTargetSelector::Assign( const BetweenUnitsTargetSelector& _betweenUnitsTargetSelector )
{
	targetSelector = _betweenUnitsTargetSelector.targetSelector;
	maxTargets = _betweenUnitsTargetSelector.maxTargets;
	pairMode = _betweenUnitsTargetSelector.pairMode;
	minDistBetweenTargets = _betweenUnitsTargetSelector.minDistBetweenTargets;
	mode = _betweenUnitsTargetSelector.mode;
	flags = _betweenUnitsTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* BetweenUnitsTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFBetweenUnitsTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BounceApplicator::BounceApplicator() :
		startTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, flags( EBounceFlags( 0 ) )
{
	cancelEffect.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BounceApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &target );
	saver.Add( 3, &spell );
	saver.Add( 4, &targetsNumber );
	saver.Add( 5, &bounceDelay );
	saver.Add( 6, &startTarget );
	saver.Add( 7, &flags );
	saver.Add( 8, &cancelEffect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BounceApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BounceApplicator* parentPtr = (BounceApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "target", &target );
	saver.Add( "spell", &spell );
	saver.Add( "targetsNumber", &targetsNumber );
	saver.Add( "bounceDelay", &bounceDelay );
	saver.Add( "startTarget", &startTarget );
	saver.Add( "flags", &flags );
	cancelEffect.resize( 2 );
	saver.Add( "cancelEffect", &cancelEffect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceApplicator::Assign( const BounceApplicator& _bounceApplicator )
{
	target = _bounceApplicator.target;
	spell = _bounceApplicator.spell;
	targetsNumber = _bounceApplicator.targetsNumber;
	bounceDelay = _bounceApplicator.bounceDelay;
	startTarget = _bounceApplicator.startTarget;
	flags = _bounceApplicator.flags;
	cancelEffect = _bounceApplicator.cancelEffect;
	behaviorFlags = _bounceApplicator.behaviorFlags;
	lifeTime = _bounceApplicator.lifeTime;
	effect = _bounceApplicator.effect;
	startCondition = _bounceApplicator.startCondition;
	enabled = _bounceApplicator.enabled;
	applyTarget = _bounceApplicator.applyTarget;
	formulaName = _bounceApplicator.formulaName;
	LoggingEvent = _bounceApplicator.LoggingEvent;
	providerName = _bounceApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* BounceApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplBounce>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityModApplicator::AbilityModApplicator() :
		targetAbilities( ABILITYIDFLAGS_ALL )
	, mode( ABILITYMODMODE_NAFTACOST )
	, useListAs( USEMODE_LISTASEXCEPTION )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityModApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &addValue );
	saver.Add( 3, &multValue );
	saver.Add( 4, &targetAbilities );
	saver.Add( 5, &mode );
	saver.Add( 6, &specificAbility );
	saver.Add( 7, &talents );
	saver.Add( 8, &useListAs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityModApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AbilityModApplicator* parentPtr = (AbilityModApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityModApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "addValue", &addValue );
	saver.Add( "multValue", &multValue );
	saver.Add( "targetAbilities", &targetAbilities );
	saver.Add( "mode", &mode );
	saver.Add( "specificAbility", &specificAbility );
	saver.Add( "talents", &talents );
	saver.Add( "useListAs", &useListAs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AbilityModApplicator::Assign( const AbilityModApplicator& _abilityModApplicator )
{
	addValue = _abilityModApplicator.addValue;
	multValue = _abilityModApplicator.multValue;
	targetAbilities = _abilityModApplicator.targetAbilities;
	mode = _abilityModApplicator.mode;
	specificAbility = _abilityModApplicator.specificAbility;
	talents = _abilityModApplicator.talents;
	useListAs = _abilityModApplicator.useListAs;
	behaviorFlags = _abilityModApplicator.behaviorFlags;
	lifeTime = _abilityModApplicator.lifeTime;
	effect = _abilityModApplicator.effect;
	startCondition = _abilityModApplicator.startCondition;
	enabled = _abilityModApplicator.enabled;
	applyTarget = _abilityModApplicator.applyTarget;
	formulaName = _abilityModApplicator.formulaName;
	LoggingEvent = _abilityModApplicator.LoggingEvent;
	providerName = _abilityModApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* AbilityModApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAbilityMod>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CapsuleTargetSelector::CapsuleTargetSelector() :
		segmentBegin( TARGETSELECTORPOINT_ABILITYOWNER )
	, segmentEnd( TARGETSELECTORPOINT_CURRENTPOSITION )
	, cutoffFirstSegment( false )
	, segmentDirectionOffset( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CapsuleTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &segmentBegin );
	saver.Add( 3, &segmentEnd );
	saver.Add( 4, &segmentEndTargetSelector );
	saver.Add( 5, &range );
	saver.Add( 6, &rangeFromOwner );
	saver.Add( 7, &cutoffFirstSegment );
	saver.Add( 8, &segmentDirectionOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CapsuleTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CapsuleTargetSelector* parentPtr = (CapsuleTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CapsuleTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "segmentBegin", &segmentBegin );
	saver.Add( "segmentEnd", &segmentEnd );
	saver.Add( "segmentEndTargetSelector", &segmentEndTargetSelector );
	saver.Add( "range", &range );
	saver.Add( "rangeFromOwner", &rangeFromOwner );
	saver.Add( "cutoffFirstSegment", &cutoffFirstSegment );
	saver.Add( "segmentDirectionOffset", &segmentDirectionOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CapsuleTargetSelector::Assign( const CapsuleTargetSelector& _capsuleTargetSelector )
{
	segmentBegin = _capsuleTargetSelector.segmentBegin;
	segmentEnd = _capsuleTargetSelector.segmentEnd;
	segmentEndTargetSelector = _capsuleTargetSelector.segmentEndTargetSelector;
	range = _capsuleTargetSelector.range;
	rangeFromOwner = _capsuleTargetSelector.rangeFromOwner;
	cutoffFirstSegment = _capsuleTargetSelector.cutoffFirstSegment;
	segmentDirectionOffset = _capsuleTargetSelector.segmentDirectionOffset;
	targetFilter = _capsuleTargetSelector.targetFilter;
	mode = _capsuleTargetSelector.mode;
	flags = _capsuleTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* CapsuleTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFCapsuleTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CastLimitation::CastLimitation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CastLimitation::operator&( IBinSaver &saver )
{
	saver.Add( 2, &uiEvent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CastLimitation::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CastLimitation* parentPtr = (CastLimitation*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CastLimitation::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "uiEvent", &uiEvent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CastLimitation::Assign( const CastLimitation& _castLimitation )
{
	uiEvent = _castLimitation.uiEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFAbilityData* CastLimitation::Check( NWorld::CastLimitationsCheckParams const &cp ) const
{
	return ( const NWorld::PFAbilityData* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChainLightningApplicator::ChainLightningApplicator() :
		onJumpSpellScale( 1.0f )
	, betweenJumpsTimeInterval( 0.0f )
	, targetFilter( ESpellTarget( SPELLTARGET_ALLENEMIES | SPELLTARGET_VISIBLETARGETSONLY ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChainLightningApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &numJumps );
	saver.Add( 3, &spell );
	saver.Add( 4, &onJumpSpellScale );
	saver.Add( 5, &betweenJumpsTimeInterval );
	saver.Add( 6, &range );
	saver.Add( 7, &targetFilter );
	saver.Add( 8, &effectIndex );
	saver.Add( 9, &effects );
	saver.Add( 10, &jumpOnEvade );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChainLightningApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChainLightningApplicator* parentPtr = (ChainLightningApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChainLightningApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "numJumps", &numJumps );
	saver.Add( "spell", &spell );
	saver.Add( "onJumpSpellScale", &onJumpSpellScale );
	saver.Add( "betweenJumpsTimeInterval", &betweenJumpsTimeInterval );
	saver.Add( "range", &range );
	saver.Add( "targetFilter", &targetFilter );
	saver.Add( "effectIndex", &effectIndex );
	saver.Add( "effects", &effects );
	saver.Add( "jumpOnEvade", &jumpOnEvade );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChainLightningApplicator::Assign( const ChainLightningApplicator& _chainLightningApplicator )
{
	numJumps = _chainLightningApplicator.numJumps;
	spell = _chainLightningApplicator.spell;
	onJumpSpellScale = _chainLightningApplicator.onJumpSpellScale;
	betweenJumpsTimeInterval = _chainLightningApplicator.betweenJumpsTimeInterval;
	range = _chainLightningApplicator.range;
	targetFilter = _chainLightningApplicator.targetFilter;
	effectIndex = _chainLightningApplicator.effectIndex;
	effects = _chainLightningApplicator.effects;
	jumpOnEvade = _chainLightningApplicator.jumpOnEvade;
	enabled = _chainLightningApplicator.enabled;
	applyTarget = _chainLightningApplicator.applyTarget;
	formulaName = _chainLightningApplicator.formulaName;
	LoggingEvent = _chainLightningApplicator.LoggingEvent;
	providerName = _chainLightningApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChainLightningApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChainLightning>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeAnimationApplicator::ChangeAnimationApplicator() :
		animState( ANIMSTATES_INVALID )
	, upper( false )
	, affectAllSets( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeAnimationApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &animState );
	saver.Add( 3, &animation );
	saver.Add( 4, &marker );
	saver.Add( 5, &upper );
	saver.Add( 6, &affectAllSets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeAnimationApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeAnimationApplicator* parentPtr = (ChangeAnimationApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeAnimationApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "animState", &animState );
	saver.Add( "animation", &animation );
	saver.Add( "marker", &marker );
	saver.Add( "upper", &upper );
	saver.Add( "affectAllSets", &affectAllSets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeAnimationApplicator::Assign( const ChangeAnimationApplicator& _changeAnimationApplicator )
{
	animState = _changeAnimationApplicator.animState;
	animation = _changeAnimationApplicator.animation;
	marker = _changeAnimationApplicator.marker;
	upper = _changeAnimationApplicator.upper;
	affectAllSets = _changeAnimationApplicator.affectAllSets;
	behaviorFlags = _changeAnimationApplicator.behaviorFlags;
	lifeTime = _changeAnimationApplicator.lifeTime;
	effect = _changeAnimationApplicator.effect;
	startCondition = _changeAnimationApplicator.startCondition;
	enabled = _changeAnimationApplicator.enabled;
	applyTarget = _changeAnimationApplicator.applyTarget;
	formulaName = _changeAnimationApplicator.formulaName;
	LoggingEvent = _changeAnimationApplicator.LoggingEvent;
	providerName = _changeAnimationApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChangeAnimationApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChangeAnimation>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeAnimSetApplicator::ChangeAnimSetApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeAnimSetApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &animSet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeAnimSetApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeAnimSetApplicator* parentPtr = (ChangeAnimSetApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeAnimSetApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "animSet", &animSet );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeAnimSetApplicator::Assign( const ChangeAnimSetApplicator& _changeAnimSetApplicator )
{
	animSet = _changeAnimSetApplicator.animSet;
	behaviorFlags = _changeAnimSetApplicator.behaviorFlags;
	lifeTime = _changeAnimSetApplicator.lifeTime;
	effect = _changeAnimSetApplicator.effect;
	startCondition = _changeAnimSetApplicator.startCondition;
	enabled = _changeAnimSetApplicator.enabled;
	applyTarget = _changeAnimSetApplicator.applyTarget;
	formulaName = _changeAnimSetApplicator.formulaName;
	LoggingEvent = _changeAnimSetApplicator.LoggingEvent;
	providerName = _changeAnimSetApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChangeAnimSetApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChangeAnimSet>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeBaseAttackApplicator::ChangeBaseAttackApplicator() :
		applyPassivePart( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeBaseAttackApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &attackAbility );
	saver.Add( 3, &applyPassivePart );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeBaseAttackApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeBaseAttackApplicator* parentPtr = (ChangeBaseAttackApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeBaseAttackApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "attackAbility", &attackAbility );
	saver.Add( "applyPassivePart", &applyPassivePart );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeBaseAttackApplicator::Assign( const ChangeBaseAttackApplicator& _changeBaseAttackApplicator )
{
	attackAbility = _changeBaseAttackApplicator.attackAbility;
	applyPassivePart = _changeBaseAttackApplicator.applyPassivePart;
	behaviorFlags = _changeBaseAttackApplicator.behaviorFlags;
	lifeTime = _changeBaseAttackApplicator.lifeTime;
	effect = _changeBaseAttackApplicator.effect;
	startCondition = _changeBaseAttackApplicator.startCondition;
	enabled = _changeBaseAttackApplicator.enabled;
	applyTarget = _changeBaseAttackApplicator.applyTarget;
	formulaName = _changeBaseAttackApplicator.formulaName;
	LoggingEvent = _changeBaseAttackApplicator.LoggingEvent;
	providerName = _changeBaseAttackApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChangeBaseAttackApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChangeBaseAttack>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeHeroStateApplicator::ChangeHeroStateApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeHeroStateApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeHeroStateApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeHeroStateApplicator* parentPtr = (ChangeHeroStateApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeHeroStateApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeHeroStateApplicator::Assign( const ChangeHeroStateApplicator& _changeHeroStateApplicator )
{
	behaviorFlags = _changeHeroStateApplicator.behaviorFlags;
	lifeTime = _changeHeroStateApplicator.lifeTime;
	effect = _changeHeroStateApplicator.effect;
	startCondition = _changeHeroStateApplicator.startCondition;
	enabled = _changeHeroStateApplicator.enabled;
	applyTarget = _changeHeroStateApplicator.applyTarget;
	formulaName = _changeHeroStateApplicator.formulaName;
	LoggingEvent = _changeHeroStateApplicator.LoggingEvent;
	providerName = _changeHeroStateApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChangeHeroStateApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChangeHeroState>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeStateApplicator::ChangeStateApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeStateApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &newStateName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChangeStateApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChangeStateApplicator* parentPtr = (ChangeStateApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeStateApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "newStateName", &newStateName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangeStateApplicator::Assign( const ChangeStateApplicator& _changeStateApplicator )
{
	newStateName = _changeStateApplicator.newStateName;
	enabled = _changeStateApplicator.enabled;
	applyTarget = _changeStateApplicator.applyTarget;
	formulaName = _changeStateApplicator.formulaName;
	LoggingEvent = _changeStateApplicator.LoggingEvent;
	providerName = _changeStateApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChangeStateApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChangeState>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChannellingApplicator::ChannellingApplicator() :
		channelingType( CHANNELINGTYPE_STREAMING )
	, period( 0.0f )
	, interruptEvents( BASEUNITEVENTFLAGS_ZERO )
	, cancelOnInterrupt( false )
	, removeStartSpellEffectOnInterrupt( false )
	, cancelOnDisable( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChannellingApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &channelingType );
	saver.Add( 4, &applicatorsOnSelf );
	saver.Add( 5, &startSpell );
	saver.Add( 6, &periodicalSpell );
	saver.Add( 7, &stopSpell );
	saver.Add( 8, &cancelSpell );
	saver.Add( 9, &period );
	saver.Add( 10, &interruptEvents );
	saver.Add( 11, &cancelOnInterrupt );
	saver.Add( 12, &removeStartSpellEffectOnInterrupt );
	saver.Add( 13, &scaleWhenInterrupted );
	saver.Add( 14, &cancelOnDisable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChannellingApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChannellingApplicator* parentPtr = (ChannellingApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChannellingApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "channelingType", &channelingType );
	saver.Add( "applicatorsOnSelf", &applicatorsOnSelf );
	saver.Add( "startSpell", &startSpell );
	saver.Add( "periodicalSpell", &periodicalSpell );
	saver.Add( "stopSpell", &stopSpell );
	saver.Add( "cancelSpell", &cancelSpell );
	saver.Add( "period", &period );
	saver.Add( "interruptEvents", &interruptEvents );
	saver.Add( "cancelOnInterrupt", &cancelOnInterrupt );
	saver.Add( "removeStartSpellEffectOnInterrupt", &removeStartSpellEffectOnInterrupt );
	saver.Add( "scaleWhenInterrupted", &scaleWhenInterrupted );
	saver.Add( "cancelOnDisable", &cancelOnDisable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChannellingApplicator::Assign( const ChannellingApplicator& _channellingApplicator )
{
	targetSelector = _channellingApplicator.targetSelector;
	channelingType = _channellingApplicator.channelingType;
	applicatorsOnSelf = _channellingApplicator.applicatorsOnSelf;
	startSpell = _channellingApplicator.startSpell;
	periodicalSpell = _channellingApplicator.periodicalSpell;
	stopSpell = _channellingApplicator.stopSpell;
	cancelSpell = _channellingApplicator.cancelSpell;
	period = _channellingApplicator.period;
	interruptEvents = _channellingApplicator.interruptEvents;
	cancelOnInterrupt = _channellingApplicator.cancelOnInterrupt;
	removeStartSpellEffectOnInterrupt = _channellingApplicator.removeStartSpellEffectOnInterrupt;
	scaleWhenInterrupted = _channellingApplicator.scaleWhenInterrupted;
	cancelOnDisable = _channellingApplicator.cancelOnDisable;
	behaviorFlags = _channellingApplicator.behaviorFlags;
	lifeTime = _channellingApplicator.lifeTime;
	effect = _channellingApplicator.effect;
	startCondition = _channellingApplicator.startCondition;
	enabled = _channellingApplicator.enabled;
	applyTarget = _channellingApplicator.applyTarget;
	formulaName = _channellingApplicator.formulaName;
	LoggingEvent = _channellingApplicator.LoggingEvent;
	providerName = _channellingApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ChannellingApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplChannelling>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CheckConditionTargetSelector::CheckConditionTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CheckConditionTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &condition );
	saver.Add( 4, &minTargetsNumber );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CheckConditionTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CheckConditionTargetSelector* parentPtr = (CheckConditionTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckConditionTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "condition", &condition );
	saver.Add( "minTargetsNumber", &minTargetsNumber );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckConditionTargetSelector::Assign( const CheckConditionTargetSelector& _checkConditionTargetSelector )
{
	targetSelector = _checkConditionTargetSelector.targetSelector;
	condition = _checkConditionTargetSelector.condition;
	minTargetsNumber = _checkConditionTargetSelector.minTargetsNumber;
	mode = _checkConditionTargetSelector.mode;
	flags = _checkConditionTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* CheckConditionTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFCheckConditionTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CloneHeroApplicator::CloneHeroApplicator() :
		flags( ECloneFlags( CLONEFLAGS_PLAYSUMMONEFFECT | CLONEFLAGS_DOLEVELUP | CLONEFLAGS_GHOSTMOVE ) )
	, takeTypeUnit( ESpellTarget( SPELLTARGET_VULNERABLETARGETSONLY | SPELLTARGET_ALL ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CloneHeroApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &applicators );
	saver.Add( 3, &lifeTime );
	saver.Add( 4, &followRange );
	saver.Add( 5, &flags );
	saver.Add( 6, &targetingParams );
	saver.Add( 7, &maxCount );
	saver.Add( 8, &summonGroupName );
	saver.Add( 9, &spawnStats );
	saver.Add( 10, &takeModDmg );
	saver.Add( 11, &takeTypeUnit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CloneHeroApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CloneHeroApplicator* parentPtr = (CloneHeroApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloneHeroApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "applicators", &applicators );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "followRange", &followRange );
	saver.Add( "flags", &flags );
	saver.Add( "targetingParams", &targetingParams );
	saver.Add( "maxCount", &maxCount );
	saver.Add( "summonGroupName", &summonGroupName );
	saver.Add( "spawnStats", &spawnStats );
	saver.Add( "takeModDmg", &takeModDmg );
	saver.Add( "takeTypeUnit", &takeTypeUnit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloneHeroApplicator::Assign( const CloneHeroApplicator& _cloneHeroApplicator )
{
	applicators = _cloneHeroApplicator.applicators;
	lifeTime = _cloneHeroApplicator.lifeTime;
	followRange = _cloneHeroApplicator.followRange;
	flags = _cloneHeroApplicator.flags;
	targetingParams = _cloneHeroApplicator.targetingParams;
	maxCount = _cloneHeroApplicator.maxCount;
	summonGroupName = _cloneHeroApplicator.summonGroupName;
	spawnStats.life = _cloneHeroApplicator.spawnStats.life;
	spawnStats.energy = _cloneHeroApplicator.spawnStats.energy;
	takeModDmg = _cloneHeroApplicator.takeModDmg;
	takeTypeUnit = _cloneHeroApplicator.takeTypeUnit;
	enabled = _cloneHeroApplicator.enabled;
	applyTarget = _cloneHeroApplicator.applyTarget;
	formulaName = _cloneHeroApplicator.formulaName;
	LoggingEvent = _cloneHeroApplicator.LoggingEvent;
	providerName = _cloneHeroApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* CloneHeroApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplCloneHero>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleTargetSelector::SingleTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (TargetSelector*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SingleTargetSelector* parentPtr = (SingleTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	TargetSelector::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleTargetSelector::Assign( const SingleTargetSelector& _singleTargetSelector )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* SingleTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFTargetSelector* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionCastLimitation::ConditionCastLimitation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionCastLimitation::operator&( IBinSaver &saver )
{
	saver.Add( 1, (CastLimitation*)this );
	saver.Add( 2, &condition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionCastLimitation::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConditionCastLimitation* parentPtr = (ConditionCastLimitation*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionCastLimitation::SerializeSelf( IXmlSaver &saver )
{
	CastLimitation::SerializeSelf( saver );
	saver.Add( "condition", &condition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionCastLimitation::Assign( const ConditionCastLimitation& _conditionCastLimitation )
{
	condition = _conditionCastLimitation.condition;
	uiEvent = _conditionCastLimitation.uiEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFAbilityData* ConditionCastLimitation::Check( NWorld::CastLimitationsCheckParams const &cp ) const
{
	return NWorld::CheckConditionLimitation( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionFormula::ConditionFormula()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionFormula::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &condition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionFormula::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConditionFormula* parentPtr = (ConditionFormula*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionFormula::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "condition", &condition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionFormula::Assign( const ConditionFormula& _conditionFormula )
{
	name = _conditionFormula.name;
	condition = _conditionFormula.condition;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionTargetSelector::ConditionTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &condition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConditionTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConditionTargetSelector* parentPtr = (ConditionTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "condition", &condition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionTargetSelector::Assign( const ConditionTargetSelector& _conditionTargetSelector )
{
	targetSelector = _conditionTargetSelector.targetSelector;
	condition = _conditionTargetSelector.condition;
	mode = _conditionTargetSelector.mode;
	flags = _conditionTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ConditionTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFConditionTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConvertTargetToLand::ConvertTargetToLand() :
		aggregateMode( TARGETTOLANDMODE_FIRST )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConvertTargetToLand::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &aggregateMode );
	saver.Add( 3, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConvertTargetToLand::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConvertTargetToLand* parentPtr = (ConvertTargetToLand*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConvertTargetToLand::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "aggregateMode", &aggregateMode );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConvertTargetToLand::Assign( const ConvertTargetToLand& _convertTargetToLand )
{
	aggregateMode = _convertTargetToLand.aggregateMode;
	targetSelector = _convertTargetToLand.targetSelector;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ConvertTargetToLand::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFConvertTargetToLand( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CountingTargetSelector::CountingTargetSelector() :
		heroesFirst( false )
	, enableSorting( false )
	, order( SORTINGORDER_DECREASING )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountingTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &targetsNumber );
	saver.Add( 4, &heroesFirst );
	saver.Add( 5, &enableSorting );
	saver.Add( 6, &sortingValue );
	saver.Add( 7, &order );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountingTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CountingTargetSelector* parentPtr = (CountingTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CountingTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "targetsNumber", &targetsNumber );
	saver.Add( "heroesFirst", &heroesFirst );
	saver.Add( "enableSorting", &enableSorting );
	saver.Add( "sortingValue", &sortingValue );
	saver.Add( "order", &order );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CountingTargetSelector::Assign( const CountingTargetSelector& _countingTargetSelector )
{
	targetSelector = _countingTargetSelector.targetSelector;
	targetsNumber = _countingTargetSelector.targetsNumber;
	heroesFirst = _countingTargetSelector.heroesFirst;
	enableSorting = _countingTargetSelector.enableSorting;
	sortingValue = _countingTargetSelector.sortingValue;
	order = _countingTargetSelector.order;
	mode = _countingTargetSelector.mode;
	flags = _countingTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* CountingTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFCountingTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreateGlyphApplicator::CreateGlyphApplicator() :
		distance( -1.0f )
	, angle( -1.0f )
	, radius( -1.0f )
	, angleIsRelative( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreateGlyphApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &glyph );
	saver.Add( 3, &distance );
	saver.Add( 4, &angle );
	saver.Add( 5, &radius );
	saver.Add( 6, &angleIsRelative );
	saver.Add( 7, &absolutePosition );
	saver.Add( 8, &scriptName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreateGlyphApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CreateGlyphApplicator* parentPtr = (CreateGlyphApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateGlyphApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "glyph", &glyph );
	saver.Add( "distance", &distance );
	saver.Add( "angle", &angle );
	saver.Add( "radius", &radius );
	saver.Add( "angleIsRelative", &angleIsRelative );
	saver.Add( "absolutePosition", &absolutePosition );
	saver.Add( "scriptName", &scriptName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateGlyphApplicator::Assign( const CreateGlyphApplicator& _createGlyphApplicator )
{
	glyph = _createGlyphApplicator.glyph;
	distance = _createGlyphApplicator.distance;
	angle = _createGlyphApplicator.angle;
	radius = _createGlyphApplicator.radius;
	angleIsRelative = _createGlyphApplicator.angleIsRelative;
	absolutePosition = _createGlyphApplicator.absolutePosition;
	scriptName = _createGlyphApplicator.scriptName;
	enabled = _createGlyphApplicator.enabled;
	applyTarget = _createGlyphApplicator.applyTarget;
	formulaName = _createGlyphApplicator.formulaName;
	LoggingEvent = _createGlyphApplicator.LoggingEvent;
	providerName = _createGlyphApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* CreateGlyphApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplCreateGlyph>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepBehaviourChangeApplicator::CreepBehaviourChangeApplicator() :
		behaviourChangeFlags( BEHAVIOURCHANGEFLAGS_CHANGEFACTION )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepBehaviourChangeApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &behaviourChangeFlags );
	saver.Add( 3, &applicators );
	saver.Add( 4, &summonGroupName );
	saver.Add( 5, &behaviour );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepBehaviourChangeApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CreepBehaviourChangeApplicator* parentPtr = (CreepBehaviourChangeApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepBehaviourChangeApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "behaviourChangeFlags", &behaviourChangeFlags );
	saver.Add( "applicators", &applicators );
	saver.Add( "summonGroupName", &summonGroupName );
	saver.Add( "behaviour", &behaviour );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepBehaviourChangeApplicator::Assign( const CreepBehaviourChangeApplicator& _creepBehaviourChangeApplicator )
{
	behaviourChangeFlags = _creepBehaviourChangeApplicator.behaviourChangeFlags;
	applicators = _creepBehaviourChangeApplicator.applicators;
	summonGroupName = _creepBehaviourChangeApplicator.summonGroupName;
	behaviour = _creepBehaviourChangeApplicator.behaviour;
	behaviorFlags = _creepBehaviourChangeApplicator.behaviorFlags;
	lifeTime = _creepBehaviourChangeApplicator.lifeTime;
	effect = _creepBehaviourChangeApplicator.effect;
	startCondition = _creepBehaviourChangeApplicator.startCondition;
	enabled = _creepBehaviourChangeApplicator.enabled;
	applyTarget = _creepBehaviourChangeApplicator.applyTarget;
	formulaName = _creepBehaviourChangeApplicator.formulaName;
	LoggingEvent = _creepBehaviourChangeApplicator.LoggingEvent;
	providerName = _creepBehaviourChangeApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* CreepBehaviourChangeApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplCreepBehaviourChange>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DamageApplicator::DamageApplicator() :
		damageType( APPLICATORDAMAGETYPE_MATERIAL )
	, damageMode( DAMAGEMODE_ZERO )
	, cancelInvisibility( false )
	, timeLimiter( -1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &damage );
	saver.Add( 3, &damageType );
	saver.Add( 4, &damageMode );
	saver.Add( 5, &cancelInvisibility );
	saver.Add( 6, &uiEvent );
	saver.Add( 7, &timeLimiter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DamageApplicator* parentPtr = (DamageApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamageApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "damage", &damage );
	saver.Add( "damageType", &damageType );
	saver.Add( "damageMode", &damageMode );
	saver.Add( "cancelInvisibility", &cancelInvisibility );
	saver.Add( "uiEvent", &uiEvent );
	saver.Add( "timeLimiter", &timeLimiter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamageApplicator::Assign( const DamageApplicator& _damageApplicator )
{
	damage = _damageApplicator.damage;
	damageType = _damageApplicator.damageType;
	damageMode = _damageApplicator.damageMode;
	cancelInvisibility = _damageApplicator.cancelInvisibility;
	uiEvent = _damageApplicator.uiEvent;
	timeLimiter = _damageApplicator.timeLimiter;
	enabled = _damageApplicator.enabled;
	applyTarget = _damageApplicator.applyTarget;
	formulaName = _damageApplicator.formulaName;
	LoggingEvent = _damageApplicator.LoggingEvent;
	providerName = _damageApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DamageApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDamage>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DamageReflectApplicator::DamageReflectApplicator() :
		amountInPersent( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageReflectApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &amountInPersent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageReflectApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DamageReflectApplicator* parentPtr = (DamageReflectApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamageReflectApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "amountInPersent", &amountInPersent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamageReflectApplicator::Assign( const DamageReflectApplicator& _damageReflectApplicator )
{
	amountInPersent = _damageReflectApplicator.amountInPersent;
	behaviorFlags = _damageReflectApplicator.behaviorFlags;
	lifeTime = _damageReflectApplicator.lifeTime;
	effect = _damageReflectApplicator.effect;
	startCondition = _damageReflectApplicator.startCondition;
	enabled = _damageReflectApplicator.enabled;
	applyTarget = _damageReflectApplicator.applyTarget;
	formulaName = _damageReflectApplicator.formulaName;
	LoggingEvent = _damageReflectApplicator.LoggingEvent;
	providerName = _damageReflectApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DamageReflectApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDamageReflect>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DamagingLinksTargetSelector::DamagingLinksTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamagingLinksTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &linkEndsSelector );
	saver.Add( 3, &linkTargetsSelector );
	saver.Add( 4, &moveRange );
	saver.Add( 5, &minRangeFromLinkEnds );
	saver.Add( 6, &maxRangeFromLinkEnds );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamagingLinksTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DamagingLinksTargetSelector* parentPtr = (DamagingLinksTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamagingLinksTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "linkEndsSelector", &linkEndsSelector );
	saver.Add( "linkTargetsSelector", &linkTargetsSelector );
	saver.Add( "moveRange", &moveRange );
	saver.Add( "minRangeFromLinkEnds", &minRangeFromLinkEnds );
	saver.Add( "maxRangeFromLinkEnds", &maxRangeFromLinkEnds );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DamagingLinksTargetSelector::Assign( const DamagingLinksTargetSelector& _damagingLinksTargetSelector )
{
	linkEndsSelector = _damagingLinksTargetSelector.linkEndsSelector;
	linkTargetsSelector = _damagingLinksTargetSelector.linkTargetsSelector;
	moveRange = _damagingLinksTargetSelector.moveRange;
	minRangeFromLinkEnds = _damagingLinksTargetSelector.minRangeFromLinkEnds;
	maxRangeFromLinkEnds = _damagingLinksTargetSelector.maxRangeFromLinkEnds;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* DamagingLinksTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFDamagingLinksTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DayNightTransitionApplicator::DayNightTransitionApplicator() :
		desiredState( DAYNIGHTSTATE_NIGHT )
	, desiredStateFraction( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DayNightTransitionApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &desiredState );
	saver.Add( 3, &desiredStateFraction );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DayNightTransitionApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DayNightTransitionApplicator* parentPtr = (DayNightTransitionApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DayNightTransitionApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "desiredState", &desiredState );
	saver.Add( "desiredStateFraction", &desiredStateFraction );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DayNightTransitionApplicator::Assign( const DayNightTransitionApplicator& _dayNightTransitionApplicator )
{
	desiredState = _dayNightTransitionApplicator.desiredState;
	desiredStateFraction = _dayNightTransitionApplicator.desiredStateFraction;
	enabled = _dayNightTransitionApplicator.enabled;
	applyTarget = _dayNightTransitionApplicator.applyTarget;
	formulaName = _dayNightTransitionApplicator.formulaName;
	LoggingEvent = _dayNightTransitionApplicator.LoggingEvent;
	providerName = _dayNightTransitionApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DayNightTransitionApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDayNightTransition>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DealedDamageConverterApplicator::DealedDamageConverterApplicator() :
		scale( 1.0f )
	, deltaTime( 3.0f )
	, type( HEALTARGET_HEALTH )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DealedDamageConverterApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &scale );
	saver.Add( 3, &deltaTime );
	saver.Add( 4, &type );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DealedDamageConverterApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DealedDamageConverterApplicator* parentPtr = (DealedDamageConverterApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DealedDamageConverterApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "scale", &scale );
	saver.Add( "deltaTime", &deltaTime );
	saver.Add( "type", &type );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DealedDamageConverterApplicator::Assign( const DealedDamageConverterApplicator& _dealedDamageConverterApplicator )
{
	scale = _dealedDamageConverterApplicator.scale;
	deltaTime = _dealedDamageConverterApplicator.deltaTime;
	type = _dealedDamageConverterApplicator.type;
	enabled = _dealedDamageConverterApplicator.enabled;
	applyTarget = _dealedDamageConverterApplicator.applyTarget;
	formulaName = _dealedDamageConverterApplicator.formulaName;
	LoggingEvent = _dealedDamageConverterApplicator.LoggingEvent;
	providerName = _dealedDamageConverterApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DealedDamageConverterApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDealedDamageConverter>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DefaultFormulas::DefaultFormulas()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DefaultFormulas::operator&( IBinSaver &saver )
{
	saver.Add( 2, &floatFormulas );
	saver.Add( 3, &boolFormulas );
	saver.Add( 4, &intFormulas );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DefaultFormulas::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DefaultFormulas* parentPtr = (DefaultFormulas*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultFormulas::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "floatFormulas", &floatFormulas );
	saver.Add( "boolFormulas", &boolFormulas );
	saver.Add( "intFormulas", &intFormulas );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultFormulas::Assign( const DefaultFormulas& _defaultFormulas )
{
	floatFormulas = _defaultFormulas.floatFormulas;
	boolFormulas = _defaultFormulas.boolFormulas;
	intFormulas = _defaultFormulas.intFormulas;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DelayTargetSelector::DelayTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DelayTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &delay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DelayTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DelayTargetSelector* parentPtr = (DelayTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelayTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "delay", &delay );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelayTargetSelector::Assign( const DelayTargetSelector& _delayTargetSelector )
{
	targetSelector = _delayTargetSelector.targetSelector;
	delay = _delayTargetSelector.delay;
	mode = _delayTargetSelector.mode;
	flags = _delayTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* DelayTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFDelayTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateDamageApplicator::DelegateDamageApplicator() :
		flags( EDelegateDamageFlags( 0 ) )
	, infiniteTotalDamage( false )
	, ignoreDefences( false )
	, forceDontAttackBack( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DelegateDamageApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &damageToDelegate );
	saver.Add( 3, &damageToApply );
	saver.Add( 4, &totalDamage );
	saver.Add( 5, &flags );
	saver.Add( 6, &infiniteTotalDamage );
	saver.Add( 7, &ignoreDefences );
	saver.Add( 8, &forceDontAttackBack );
	saver.Add( 9, &delegateTargets );
	saver.Add( 10, &stopCondition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DelegateDamageApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DelegateDamageApplicator* parentPtr = (DelegateDamageApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelegateDamageApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "damageToDelegate", &damageToDelegate );
	saver.Add( "damageToApply", &damageToApply );
	saver.Add( "totalDamage", &totalDamage );
	saver.Add( "flags", &flags );
	saver.Add( "infiniteTotalDamage", &infiniteTotalDamage );
	saver.Add( "ignoreDefences", &ignoreDefences );
	saver.Add( "forceDontAttackBack", &forceDontAttackBack );
	saver.Add( "delegateTargets", &delegateTargets );
	saver.Add( "stopCondition", &stopCondition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelegateDamageApplicator::Assign( const DelegateDamageApplicator& _delegateDamageApplicator )
{
	damageToDelegate = _delegateDamageApplicator.damageToDelegate;
	damageToApply = _delegateDamageApplicator.damageToApply;
	totalDamage = _delegateDamageApplicator.totalDamage;
	flags = _delegateDamageApplicator.flags;
	infiniteTotalDamage = _delegateDamageApplicator.infiniteTotalDamage;
	ignoreDefences = _delegateDamageApplicator.ignoreDefences;
	forceDontAttackBack = _delegateDamageApplicator.forceDontAttackBack;
	delegateTargets = _delegateDamageApplicator.delegateTargets;
	stopCondition = _delegateDamageApplicator.stopCondition;
	behaviorFlags = _delegateDamageApplicator.behaviorFlags;
	lifeTime = _delegateDamageApplicator.lifeTime;
	effect = _delegateDamageApplicator.effect;
	startCondition = _delegateDamageApplicator.startCondition;
	enabled = _delegateDamageApplicator.enabled;
	applyTarget = _delegateDamageApplicator.applyTarget;
	formulaName = _delegateDamageApplicator.formulaName;
	LoggingEvent = _delegateDamageApplicator.LoggingEvent;
	providerName = _delegateDamageApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DelegateDamageApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDelegateDamage>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dispatch::Dispatch() :
		applyEffectOrientation( APPLYEFFECTORIENTATION_DEFAULT )
	, applyEffectRandomAnglePoints( 0 )
	, dieAfterApply( true )
	, alwaysApply( false )
	, applyEffectIgnoreVisibility( false )
	, flags( EDispatchFlags( 0 ) )
{
	dispatchEffect.resize( 2 );
	applyEffect.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Dispatch::operator&( IBinSaver &saver )
{
	saver.Add( 2, &dispatchEffect );
	saver.Add( 3, &applyEffect );
	saver.Add( 4, &applyEffectOrientation );
	saver.Add( 5, &applyEffectRandomAnglePoints );
	saver.Add( 6, &dieAfterApply );
	saver.Add( 7, &alwaysApply );
	saver.Add( 8, &applyEffectIgnoreVisibility );
	saver.Add( 9, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Dispatch::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Dispatch* parentPtr = (Dispatch*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dispatch::SerializeSelf( IXmlSaver &saver )
{
	dispatchEffect.resize( 2 );
	saver.Add( "dispatchEffect", &dispatchEffect );
	applyEffect.resize( 2 );
	saver.Add( "applyEffect", &applyEffect );
	saver.Add( "applyEffectOrientation", &applyEffectOrientation );
	saver.Add( "applyEffectRandomAnglePoints", &applyEffectRandomAnglePoints );
	saver.Add( "dieAfterApply", &dieAfterApply );
	saver.Add( "alwaysApply", &alwaysApply );
	saver.Add( "applyEffectIgnoreVisibility", &applyEffectIgnoreVisibility );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dispatch::Assign( const Dispatch& _dispatch )
{
	dispatchEffect = _dispatch.dispatchEffect;
	applyEffect = _dispatch.applyEffect;
	applyEffectOrientation = _dispatch.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatch.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatch.dieAfterApply;
	alwaysApply = _dispatch.alwaysApply;
	applyEffectIgnoreVisibility = _dispatch.applyEffectIgnoreVisibility;
	flags = _dispatch.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* Dispatch::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return ( NWorld::PFDispatch* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchContinuous::DispatchContinuous()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchContinuous::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Dispatch*)this );
	saver.Add( 2, &persistentApplicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchContinuous::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchContinuous* parentPtr = (DispatchContinuous*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchContinuous::SerializeSelf( IXmlSaver &saver )
{
	Dispatch::SerializeSelf( saver );
	saver.Add( "persistentApplicators", &persistentApplicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchContinuous::Assign( const DispatchContinuous& _dispatchContinuous )
{
	persistentApplicators = _dispatchContinuous.persistentApplicators;
	dispatchEffect = _dispatchContinuous.dispatchEffect;
	applyEffect = _dispatchContinuous.applyEffect;
	applyEffectOrientation = _dispatchContinuous.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchContinuous.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchContinuous.dieAfterApply;
	alwaysApply = _dispatchContinuous.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchContinuous.applyEffectIgnoreVisibility;
	flags = _dispatchContinuous.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchContinuous::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchContinuous>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchByTime::DispatchByTime() :
		cancelOnSenderDeath( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchByTime::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DispatchContinuous*)this );
	saver.Add( 2, &lifeTime );
	saver.Add( 3, &cancelOnSenderDeath );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchByTime::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchByTime* parentPtr = (DispatchByTime*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchByTime::SerializeSelf( IXmlSaver &saver )
{
	DispatchContinuous::SerializeSelf( saver );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "cancelOnSenderDeath", &cancelOnSenderDeath );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchByTime::Assign( const DispatchByTime& _dispatchByTime )
{
	lifeTime = _dispatchByTime.lifeTime;
	cancelOnSenderDeath = _dispatchByTime.cancelOnSenderDeath;
	persistentApplicators = _dispatchByTime.persistentApplicators;
	dispatchEffect = _dispatchByTime.dispatchEffect;
	applyEffect = _dispatchByTime.applyEffect;
	applyEffectOrientation = _dispatchByTime.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchByTime.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchByTime.dieAfterApply;
	alwaysApply = _dispatchByTime.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchByTime.applyEffectIgnoreVisibility;
	flags = _dispatchByTime.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchByTime::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchByTime>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchCursor::DispatchCursor() :
		fromLocator( "Attack" )
	, height( 0.0f )
	, cursorUpdateFrequency( 5 )
	, linkRange( 0.0f )
	, size( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchCursor::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DispatchContinuous*)this );
	saver.Add( 2, &speed );
	saver.Add( 3, &maxSpeed );
	saver.Add( 4, &fromLocator );
	saver.Add( 5, &height );
	saver.Add( 6, &lifeTime );
	saver.Add( 7, &cursorUpdateFrequency );
	saver.Add( 8, &linkRange );
	saver.Add( 9, &linkEffect );
	saver.Add( 10, &maxRangeMaterial );
	saver.Add( 11, &size );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchCursor::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchCursor* parentPtr = (DispatchCursor*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchCursor::SerializeSelf( IXmlSaver &saver )
{
	DispatchContinuous::SerializeSelf( saver );
	saver.Add( "speed", &speed );
	saver.Add( "maxSpeed", &maxSpeed );
	saver.Add( "fromLocator", &fromLocator );
	saver.Add( "height", &height );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "cursorUpdateFrequency", &cursorUpdateFrequency );
	saver.Add( "linkRange", &linkRange );
	saver.Add( "linkEffect", &linkEffect );
	saver.Add( "maxRangeMaterial", &maxRangeMaterial );
	saver.Add( "size", &size );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchCursor::Assign( const DispatchCursor& _dispatchCursor )
{
	speed = _dispatchCursor.speed;
	maxSpeed = _dispatchCursor.maxSpeed;
	fromLocator = _dispatchCursor.fromLocator;
	height = _dispatchCursor.height;
	lifeTime = _dispatchCursor.lifeTime;
	cursorUpdateFrequency = _dispatchCursor.cursorUpdateFrequency;
	linkRange = _dispatchCursor.linkRange;
	linkEffect = _dispatchCursor.linkEffect;
	maxRangeMaterial = _dispatchCursor.maxRangeMaterial;
	size = _dispatchCursor.size;
	persistentApplicators = _dispatchCursor.persistentApplicators;
	dispatchEffect = _dispatchCursor.dispatchEffect;
	applyEffect = _dispatchCursor.applyEffect;
	applyEffectOrientation = _dispatchCursor.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchCursor.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchCursor.dieAfterApply;
	alwaysApply = _dispatchCursor.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchCursor.applyEffectIgnoreVisibility;
	flags = _dispatchCursor.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchCursor::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchCursor>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchImmediate::DispatchImmediate() :
		instantApply( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchImmediate::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Dispatch*)this );
	saver.Add( 2, &instantApply );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchImmediate::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchImmediate* parentPtr = (DispatchImmediate*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchImmediate::SerializeSelf( IXmlSaver &saver )
{
	Dispatch::SerializeSelf( saver );
	saver.Add( "instantApply", &instantApply );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchImmediate::Assign( const DispatchImmediate& _dispatchImmediate )
{
	instantApply = _dispatchImmediate.instantApply;
	dispatchEffect = _dispatchImmediate.dispatchEffect;
	applyEffect = _dispatchImmediate.applyEffect;
	applyEffectOrientation = _dispatchImmediate.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchImmediate.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchImmediate.dieAfterApply;
	alwaysApply = _dispatchImmediate.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchImmediate.applyEffectIgnoreVisibility;
	flags = _dispatchImmediate.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchImmediate::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchImmediate>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchLinear::DispatchLinear() :
		aiming( DISPATCHAIMING_STRAIGHT )
	, maxDeviation( 180.0f )
	, speed( 0.0f )
	, locatorOrient( true )
	, fromLocator( "Attack" )
	, toLocator( "Body" )
	, height( 0.0f )
	, flyMode( DISPATCHFLYMODE_PARABOLIC )
	, maxDistance( -1.0f )
	, minRise( 0.0f )
	, maxRise( 0.0f )
	, killEffect( true )
	, suspendTime( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchLinear::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DispatchContinuous*)this );
	saver.Add( 2, &aiming );
	saver.Add( 3, &maxDeviation );
	saver.Add( 4, &speed );
	saver.Add( 5, &locatorOrient );
	saver.Add( 6, &fromLocator );
	saver.Add( 7, &toLocator );
	saver.Add( 8, &height );
	saver.Add( 9, &flyMode );
	saver.Add( 10, &maxDistance );
	saver.Add( 11, &minRise );
	saver.Add( 12, &maxRise );
	saver.Add( 13, &killEffect );
	saver.Add( 14, &suspendTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchLinear::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchLinear* parentPtr = (DispatchLinear*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchLinear::SerializeSelf( IXmlSaver &saver )
{
	DispatchContinuous::SerializeSelf( saver );
	saver.Add( "aiming", &aiming );
	saver.Add( "maxDeviation", &maxDeviation );
	saver.Add( "speed", &speed );
	saver.Add( "locatorOrient", &locatorOrient );
	saver.Add( "fromLocator", &fromLocator );
	saver.Add( "toLocator", &toLocator );
	saver.Add( "height", &height );
	saver.Add( "flyMode", &flyMode );
	saver.Add( "maxDistance", &maxDistance );
	saver.Add( "minRise", &minRise );
	saver.Add( "maxRise", &maxRise );
	saver.Add( "killEffect", &killEffect );
	saver.Add( "suspendTime", &suspendTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchLinear::Assign( const DispatchLinear& _dispatchLinear )
{
	aiming = _dispatchLinear.aiming;
	maxDeviation = _dispatchLinear.maxDeviation;
	speed = _dispatchLinear.speed;
	locatorOrient = _dispatchLinear.locatorOrient;
	fromLocator = _dispatchLinear.fromLocator;
	toLocator = _dispatchLinear.toLocator;
	height = _dispatchLinear.height;
	flyMode = _dispatchLinear.flyMode;
	maxDistance = _dispatchLinear.maxDistance;
	minRise = _dispatchLinear.minRise;
	maxRise = _dispatchLinear.maxRise;
	killEffect = _dispatchLinear.killEffect;
	suspendTime = _dispatchLinear.suspendTime;
	persistentApplicators = _dispatchLinear.persistentApplicators;
	dispatchEffect = _dispatchLinear.dispatchEffect;
	applyEffect = _dispatchLinear.applyEffect;
	applyEffectOrientation = _dispatchLinear.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchLinear.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchLinear.dieAfterApply;
	alwaysApply = _dispatchLinear.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchLinear.applyEffectIgnoreVisibility;
	flags = _dispatchLinear.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchLinear::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchUniformLinearMove>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchLinearWithLink::DispatchLinearWithLink()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchLinearWithLink::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DispatchLinear*)this );
	saver.Add( 2, &links );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchLinearWithLink::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchLinearWithLink* parentPtr = (DispatchLinearWithLink*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchLinearWithLink::SerializeSelf( IXmlSaver &saver )
{
	DispatchLinear::SerializeSelf( saver );
	saver.Add( "links", &links );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchLinearWithLink::Assign( const DispatchLinearWithLink& _dispatchLinearWithLink )
{
	links = _dispatchLinearWithLink.links;
	aiming = _dispatchLinearWithLink.aiming;
	maxDeviation = _dispatchLinearWithLink.maxDeviation;
	speed = _dispatchLinearWithLink.speed;
	locatorOrient = _dispatchLinearWithLink.locatorOrient;
	fromLocator = _dispatchLinearWithLink.fromLocator;
	toLocator = _dispatchLinearWithLink.toLocator;
	height = _dispatchLinearWithLink.height;
	flyMode = _dispatchLinearWithLink.flyMode;
	maxDistance = _dispatchLinearWithLink.maxDistance;
	minRise = _dispatchLinearWithLink.minRise;
	maxRise = _dispatchLinearWithLink.maxRise;
	killEffect = _dispatchLinearWithLink.killEffect;
	suspendTime = _dispatchLinearWithLink.suspendTime;
	persistentApplicators = _dispatchLinearWithLink.persistentApplicators;
	dispatchEffect = _dispatchLinearWithLink.dispatchEffect;
	applyEffect = _dispatchLinearWithLink.applyEffect;
	applyEffectOrientation = _dispatchLinearWithLink.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchLinearWithLink.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchLinearWithLink.dieAfterApply;
	alwaysApply = _dispatchLinearWithLink.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchLinearWithLink.applyEffectIgnoreVisibility;
	flags = _dispatchLinearWithLink.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchLinearWithLink::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchWithLink>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispatchRockmanMace::DispatchRockmanMace() :
		minDistance( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchRockmanMace::operator&( IBinSaver &saver )
{
	saver.Add( 1, (DispatchLinearWithLink*)this );
	saver.Add( 2, &minDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispatchRockmanMace::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispatchRockmanMace* parentPtr = (DispatchRockmanMace*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchRockmanMace::SerializeSelf( IXmlSaver &saver )
{
	DispatchLinearWithLink::SerializeSelf( saver );
	saver.Add( "minDistance", &minDistance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispatchRockmanMace::Assign( const DispatchRockmanMace& _dispatchRockmanMace )
{
	minDistance = _dispatchRockmanMace.minDistance;
	links = _dispatchRockmanMace.links;
	aiming = _dispatchRockmanMace.aiming;
	maxDeviation = _dispatchRockmanMace.maxDeviation;
	speed = _dispatchRockmanMace.speed;
	locatorOrient = _dispatchRockmanMace.locatorOrient;
	fromLocator = _dispatchRockmanMace.fromLocator;
	toLocator = _dispatchRockmanMace.toLocator;
	height = _dispatchRockmanMace.height;
	flyMode = _dispatchRockmanMace.flyMode;
	maxDistance = _dispatchRockmanMace.maxDistance;
	minRise = _dispatchRockmanMace.minRise;
	maxRise = _dispatchRockmanMace.maxRise;
	killEffect = _dispatchRockmanMace.killEffect;
	suspendTime = _dispatchRockmanMace.suspendTime;
	persistentApplicators = _dispatchRockmanMace.persistentApplicators;
	dispatchEffect = _dispatchRockmanMace.dispatchEffect;
	applyEffect = _dispatchRockmanMace.applyEffect;
	applyEffectOrientation = _dispatchRockmanMace.applyEffectOrientation;
	applyEffectRandomAnglePoints = _dispatchRockmanMace.applyEffectRandomAnglePoints;
	dieAfterApply = _dispatchRockmanMace.dieAfterApply;
	alwaysApply = _dispatchRockmanMace.alwaysApply;
	applyEffectIgnoreVisibility = _dispatchRockmanMace.applyEffectIgnoreVisibility;
	flags = _dispatchRockmanMace.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFDispatch* DispatchRockmanMace::Create( NWorld::PFDispatchCreateParams const &cp ) const
{
	return NWorld::FCreateDispatch<NWorld::PFDispatchRockmanMace>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispellApplicator::DispellApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispellApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &maxEffectsToDispell );
	saver.Add( 3, &targets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispellApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispellApplicator* parentPtr = (DispellApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispellApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "maxEffectsToDispell", &maxEffectsToDispell );
	saver.Add( "targets", &targets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispellApplicator::Assign( const DispellApplicator& _dispellApplicator )
{
	maxEffectsToDispell = _dispellApplicator.maxEffectsToDispell;
	targets = _dispellApplicator.targets;
	enabled = _dispellApplicator.enabled;
	applyTarget = _dispellApplicator.applyTarget;
	formulaName = _dispellApplicator.formulaName;
	LoggingEvent = _dispellApplicator.LoggingEvent;
	providerName = _dispellApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DispellApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDispell>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DispellCastLimitation::DispellCastLimitation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispellCastLimitation::operator&( IBinSaver &saver )
{
	saver.Add( 1, (CastLimitation*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DispellCastLimitation::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DispellCastLimitation* parentPtr = (DispellCastLimitation*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispellCastLimitation::SerializeSelf( IXmlSaver &saver )
{
	CastLimitation::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DispellCastLimitation::Assign( const DispellCastLimitation& _dispellCastLimitation )
{
	uiEvent = _dispellCastLimitation.uiEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFAbilityData* DispellCastLimitation::Check( NWorld::CastLimitationsCheckParams const &cp ) const
{
	return NWorld::CheckDispellLimitation( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DropTreeApplicator::DropTreeApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DropTreeApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DropTreeApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DropTreeApplicator* parentPtr = (DropTreeApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DropTreeApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DropTreeApplicator::Assign( const DropTreeApplicator& _dropTreeApplicator )
{
	enabled = _dropTreeApplicator.enabled;
	applyTarget = _dropTreeApplicator.applyTarget;
	formulaName = _dropTreeApplicator.formulaName;
	LoggingEvent = _dropTreeApplicator.LoggingEvent;
	providerName = _dropTreeApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* DropTreeApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplDropTree>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorBase::EventProcessorBase() :
		applyTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorBase::operator&( IBinSaver &saver )
{
	saver.Add( 2, &applyTarget );
	saver.Add( 3, &spell );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorBase* parentPtr = (EventProcessorBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorBase::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "applyTarget", &applyTarget );
	saver.Add( "spell", &spell );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorBase::Assign( const EventProcessorBase& _eventProcessorBase )
{
	applyTarget = _eventProcessorBase.applyTarget;
	spell = _eventProcessorBase.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorBase::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFEventProcessorBase* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorApplicatorApplied::EventProcessorApplicatorApplied() :
		filter( TRIGGERABILITIESABILITIESFLAGS_NONE )
	, mode( APPLICATORAPPLIEDMODE_DEFAULT )
	, senderMatchTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, checkSender( TRIGGEREVENTCHECKSENDER_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorApplicatorApplied::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &filter );
	saver.Add( 3, &applicatorTypesList );
	saver.Add( 4, &applicatorsList );
	saver.Add( 5, &mode );
	saver.Add( 6, &newLifetime );
	saver.Add( 7, &senderMatchTarget );
	saver.Add( 8, &checkSender );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorApplicatorApplied::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorApplicatorApplied* parentPtr = (EventProcessorApplicatorApplied*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorApplicatorApplied::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "filter", &filter );
	saver.Add( "applicatorTypesList", &applicatorTypesList );
	saver.Add( "applicatorsList", &applicatorsList );
	saver.Add( "mode", &mode );
	saver.Add( "newLifetime", &newLifetime );
	saver.Add( "senderMatchTarget", &senderMatchTarget );
	saver.Add( "checkSender", &checkSender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorApplicatorApplied::Assign( const EventProcessorApplicatorApplied& _eventProcessorApplicatorApplied )
{
	filter = _eventProcessorApplicatorApplied.filter;
	applicatorTypesList = _eventProcessorApplicatorApplied.applicatorTypesList;
	applicatorsList = _eventProcessorApplicatorApplied.applicatorsList;
	mode = _eventProcessorApplicatorApplied.mode;
	newLifetime = _eventProcessorApplicatorApplied.newLifetime;
	senderMatchTarget = _eventProcessorApplicatorApplied.senderMatchTarget;
	checkSender = _eventProcessorApplicatorApplied.checkSender;
	applyTarget = _eventProcessorApplicatorApplied.applyTarget;
	spell = _eventProcessorApplicatorApplied.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorApplicatorApplied::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorApplicatorApplied( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorAbilityManacostTransformer::EventProcessorAbilityManacostTransformer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorAbilityManacostTransformer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &filter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorAbilityManacostTransformer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorAbilityManacostTransformer* parentPtr = (EventProcessorAbilityManacostTransformer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorAbilityManacostTransformer::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "filter", &filter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorAbilityManacostTransformer::Assign( const EventProcessorAbilityManacostTransformer& _eventProcessorAbilityManacostTransformer )
{
	filter.flags = _eventProcessorAbilityManacostTransformer.filter.flags;
	filter.onlySingleTarget = _eventProcessorAbilityManacostTransformer.filter.onlySingleTarget;
	filter.abilityCostMode = _eventProcessorAbilityManacostTransformer.filter.abilityCostMode;
	filter.abilitiesList = _eventProcessorAbilityManacostTransformer.filter.abilitiesList;
	filter.exceptThis = _eventProcessorAbilityManacostTransformer.filter.exceptThis;
	filter.abilityCondition = _eventProcessorAbilityManacostTransformer.filter.abilityCondition;
	applyTarget = _eventProcessorAbilityManacostTransformer.applyTarget;
	spell = _eventProcessorAbilityManacostTransformer.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorAbilityManacostTransformer::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorAbilityManacostTransformer( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorCancelDispatch::EventProcessorCancelDispatch() :
		senderMatchTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, checkSender( TRIGGEREVENTCHECKSENDER_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorCancelDispatch::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &filter );
	saver.Add( 3, &senderMatchTarget );
	saver.Add( 4, &checkSender );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorCancelDispatch::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorCancelDispatch* parentPtr = (EventProcessorCancelDispatch*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorCancelDispatch::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "filter", &filter );
	saver.Add( "senderMatchTarget", &senderMatchTarget );
	saver.Add( "checkSender", &checkSender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorCancelDispatch::Assign( const EventProcessorCancelDispatch& _eventProcessorCancelDispatch )
{
	filter.flags = _eventProcessorCancelDispatch.filter.flags;
	filter.onlySingleTarget = _eventProcessorCancelDispatch.filter.onlySingleTarget;
	filter.abilityCostMode = _eventProcessorCancelDispatch.filter.abilityCostMode;
	filter.abilitiesList = _eventProcessorCancelDispatch.filter.abilitiesList;
	filter.exceptThis = _eventProcessorCancelDispatch.filter.exceptThis;
	filter.abilityCondition = _eventProcessorCancelDispatch.filter.abilityCondition;
	senderMatchTarget = _eventProcessorCancelDispatch.senderMatchTarget;
	checkSender = _eventProcessorCancelDispatch.checkSender;
	applyTarget = _eventProcessorCancelDispatch.applyTarget;
	spell = _eventProcessorCancelDispatch.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorCancelDispatch::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorCancelDispatch( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorCondition::EventProcessorCondition() :
		events( BASEUNITEVENTFLAGS_ZERO )
	, onlyParent( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorCondition::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &events );
	saver.Add( 3, &condition );
	saver.Add( 4, &onlyParent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorCondition::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorCondition* parentPtr = (EventProcessorCondition*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorCondition::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "events", &events );
	saver.Add( "condition", &condition );
	saver.Add( "onlyParent", &onlyParent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorCondition::Assign( const EventProcessorCondition& _eventProcessorCondition )
{
	events = _eventProcessorCondition.events;
	condition = _eventProcessorCondition.condition;
	onlyParent = _eventProcessorCondition.onlyParent;
	applyTarget = _eventProcessorCondition.applyTarget;
	spell = _eventProcessorCondition.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorCondition::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorCondition( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorDamageTransformer::EventProcessorDamageTransformer() :
		damageTypeFilter( DAMAGEFILTER_ALL )
	, senderMatchTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, matchTargetInverted( false )
	, treatDelegatedByDelegator( false )
	, objectFilter( SPELLTARGET_ALL )
	, checkSender( TRIGGEREVENTCHECKSENDER_NONE )
	, flags( TRIGGEREVENTFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorDamageTransformer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &damageTypeFilter );
	saver.Add( 3, &abilityFilter );
	saver.Add( 4, &add );
	saver.Add( 5, &mul );
	saver.Add( 6, &senderMatchTarget );
	saver.Add( 7, &matchTargetInverted );
	saver.Add( 8, &treatDelegatedByDelegator );
	saver.Add( 9, &objectFilter );
	saver.Add( 10, &checkSender );
	saver.Add( 11, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorDamageTransformer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorDamageTransformer* parentPtr = (EventProcessorDamageTransformer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorDamageTransformer::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "damageTypeFilter", &damageTypeFilter );
	saver.Add( "abilityFilter", &abilityFilter );
	saver.Add( "add", &add );
	saver.Add( "mul", &mul );
	saver.Add( "senderMatchTarget", &senderMatchTarget );
	saver.Add( "matchTargetInverted", &matchTargetInverted );
	saver.Add( "treatDelegatedByDelegator", &treatDelegatedByDelegator );
	saver.Add( "objectFilter", &objectFilter );
	saver.Add( "checkSender", &checkSender );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorDamageTransformer::Assign( const EventProcessorDamageTransformer& _eventProcessorDamageTransformer )
{
	damageTypeFilter = _eventProcessorDamageTransformer.damageTypeFilter;
	abilityFilter.flags = _eventProcessorDamageTransformer.abilityFilter.flags;
	abilityFilter.onlySingleTarget = _eventProcessorDamageTransformer.abilityFilter.onlySingleTarget;
	abilityFilter.abilityCostMode = _eventProcessorDamageTransformer.abilityFilter.abilityCostMode;
	abilityFilter.abilitiesList = _eventProcessorDamageTransformer.abilityFilter.abilitiesList;
	abilityFilter.exceptThis = _eventProcessorDamageTransformer.abilityFilter.exceptThis;
	abilityFilter.abilityCondition = _eventProcessorDamageTransformer.abilityFilter.abilityCondition;
	add = _eventProcessorDamageTransformer.add;
	mul = _eventProcessorDamageTransformer.mul;
	senderMatchTarget = _eventProcessorDamageTransformer.senderMatchTarget;
	matchTargetInverted = _eventProcessorDamageTransformer.matchTargetInverted;
	treatDelegatedByDelegator = _eventProcessorDamageTransformer.treatDelegatedByDelegator;
	objectFilter = _eventProcessorDamageTransformer.objectFilter;
	checkSender = _eventProcessorDamageTransformer.checkSender;
	flags = _eventProcessorDamageTransformer.flags;
	applyTarget = _eventProcessorDamageTransformer.applyTarget;
	spell = _eventProcessorDamageTransformer.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorDamageTransformer::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorDamageTransformer( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorGroup::EventProcessorGroup()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorGroup::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &processors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorGroup::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorGroup* parentPtr = (EventProcessorGroup*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorGroup::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "processors", &processors );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorGroup::Assign( const EventProcessorGroup& _eventProcessorGroup )
{
	processors = _eventProcessorGroup.processors;
	applyTarget = _eventProcessorGroup.applyTarget;
	spell = _eventProcessorGroup.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorGroup::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorGroup( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorIncomingDamage::EventProcessorIncomingDamage() :
		damageDelegateOwner( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorIncomingDamage::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &damageDelegate );
	saver.Add( 3, &damageDelegateOwner );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorIncomingDamage::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorIncomingDamage* parentPtr = (EventProcessorIncomingDamage*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorIncomingDamage::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "damageDelegate", &damageDelegate );
	saver.Add( "damageDelegateOwner", &damageDelegateOwner );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorIncomingDamage::Assign( const EventProcessorIncomingDamage& _eventProcessorIncomingDamage )
{
	damageDelegate = _eventProcessorIncomingDamage.damageDelegate;
	damageDelegateOwner = _eventProcessorIncomingDamage.damageDelegateOwner;
	applyTarget = _eventProcessorIncomingDamage.applyTarget;
	spell = _eventProcessorIncomingDamage.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorIncomingDamage::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorIncomingDamage( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorLastHit::EventProcessorLastHit()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorLastHit::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorLastHit::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorLastHit* parentPtr = (EventProcessorLastHit*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorLastHit::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorLastHit::Assign( const EventProcessorLastHit& _eventProcessorLastHit )
{
	applyTarget = _eventProcessorLastHit.applyTarget;
	spell = _eventProcessorLastHit.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorLastHit::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorLastHit( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorOnConsumableObtained::EventProcessorOnConsumableObtained() :
		origin( EConsumableOriginFlags( 0 ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnConsumableObtained::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &consumable );
	saver.Add( 3, &origin );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnConsumableObtained::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorOnConsumableObtained* parentPtr = (EventProcessorOnConsumableObtained*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnConsumableObtained::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "consumable", &consumable );
	saver.Add( "origin", &origin );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnConsumableObtained::Assign( const EventProcessorOnConsumableObtained& _eventProcessorOnConsumableObtained )
{
	consumable = _eventProcessorOnConsumableObtained.consumable;
	origin = _eventProcessorOnConsumableObtained.origin;
	applyTarget = _eventProcessorOnConsumableObtained.applyTarget;
	spell = _eventProcessorOnConsumableObtained.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorOnConsumableObtained::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorOnConsumableObtained( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorOnDeath::EventProcessorOnDeath() :
		senderMatchTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, objectFilter( SPELLTARGET_ALL )
	, checkSender( TRIGGEREVENTCHECKSENDER_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnDeath::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &castSpellDelay );
	saver.Add( 3, &senderMatchTarget );
	saver.Add( 4, &objectFilter );
	saver.Add( 5, &checkSender );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnDeath::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorOnDeath* parentPtr = (EventProcessorOnDeath*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnDeath::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "castSpellDelay", &castSpellDelay );
	saver.Add( "senderMatchTarget", &senderMatchTarget );
	saver.Add( "objectFilter", &objectFilter );
	saver.Add( "checkSender", &checkSender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnDeath::Assign( const EventProcessorOnDeath& _eventProcessorOnDeath )
{
	castSpellDelay = _eventProcessorOnDeath.castSpellDelay;
	senderMatchTarget = _eventProcessorOnDeath.senderMatchTarget;
	objectFilter = _eventProcessorOnDeath.objectFilter;
	checkSender = _eventProcessorOnDeath.checkSender;
	applyTarget = _eventProcessorOnDeath.applyTarget;
	spell = _eventProcessorOnDeath.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorOnDeath::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorOnDeath( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorOnTarget::EventProcessorOnTarget()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnTarget::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &minTargets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnTarget::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorOnTarget* parentPtr = (EventProcessorOnTarget*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnTarget::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "minTargets", &minTargets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnTarget::Assign( const EventProcessorOnTarget& _eventProcessorOnTarget )
{
	targetSelector = _eventProcessorOnTarget.targetSelector;
	minTargets = _eventProcessorOnTarget.minTargets;
	applyTarget = _eventProcessorOnTarget.applyTarget;
	spell = _eventProcessorOnTarget.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorOnTarget::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorOnTarget( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorOnUseAbilityForceStrike::EventProcessorOnUseAbilityForceStrike()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnUseAbilityForceStrike::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &filter );
	saver.Add( 3, &applicatorName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOnUseAbilityForceStrike::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorOnUseAbilityForceStrike* parentPtr = (EventProcessorOnUseAbilityForceStrike*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnUseAbilityForceStrike::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "filter", &filter );
	saver.Add( "applicatorName", &applicatorName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOnUseAbilityForceStrike::Assign( const EventProcessorOnUseAbilityForceStrike& _eventProcessorOnUseAbilityForceStrike )
{
	filter.flags = _eventProcessorOnUseAbilityForceStrike.filter.flags;
	filter.onlySingleTarget = _eventProcessorOnUseAbilityForceStrike.filter.onlySingleTarget;
	filter.abilityCostMode = _eventProcessorOnUseAbilityForceStrike.filter.abilityCostMode;
	filter.abilitiesList = _eventProcessorOnUseAbilityForceStrike.filter.abilitiesList;
	filter.exceptThis = _eventProcessorOnUseAbilityForceStrike.filter.exceptThis;
	filter.abilityCondition = _eventProcessorOnUseAbilityForceStrike.filter.abilityCondition;
	applicatorName = _eventProcessorOnUseAbilityForceStrike.applicatorName;
	applyTarget = _eventProcessorOnUseAbilityForceStrike.applyTarget;
	spell = _eventProcessorOnUseAbilityForceStrike.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorOnUseAbilityForceStrike::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorOnUseAbilityForceStrike( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorOutgoingDamage::EventProcessorOutgoingDamage() :
		damageTypeFilter( DAMAGEFILTER_ALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOutgoingDamage::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &damageTypeFilter );
	saver.Add( 3, &abilityFilter );
	saver.Add( 4, &modifiedDamage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorOutgoingDamage::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorOutgoingDamage* parentPtr = (EventProcessorOutgoingDamage*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOutgoingDamage::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "damageTypeFilter", &damageTypeFilter );
	saver.Add( "abilityFilter", &abilityFilter );
	saver.Add( "modifiedDamage", &modifiedDamage );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorOutgoingDamage::Assign( const EventProcessorOutgoingDamage& _eventProcessorOutgoingDamage )
{
	damageTypeFilter = _eventProcessorOutgoingDamage.damageTypeFilter;
	abilityFilter.flags = _eventProcessorOutgoingDamage.abilityFilter.flags;
	abilityFilter.onlySingleTarget = _eventProcessorOutgoingDamage.abilityFilter.onlySingleTarget;
	abilityFilter.abilityCostMode = _eventProcessorOutgoingDamage.abilityFilter.abilityCostMode;
	abilityFilter.abilitiesList = _eventProcessorOutgoingDamage.abilityFilter.abilitiesList;
	abilityFilter.exceptThis = _eventProcessorOutgoingDamage.abilityFilter.exceptThis;
	abilityFilter.abilityCondition = _eventProcessorOutgoingDamage.abilityFilter.abilityCondition;
	modifiedDamage = _eventProcessorOutgoingDamage.modifiedDamage;
	applyTarget = _eventProcessorOutgoingDamage.applyTarget;
	spell = _eventProcessorOutgoingDamage.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorOutgoingDamage::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorOutgoingDamage( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorPickupGlyph::EventProcessorPickupGlyph()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorPickupGlyph::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &filter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorPickupGlyph::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorPickupGlyph* parentPtr = (EventProcessorPickupGlyph*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorPickupGlyph::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "filter", &filter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorPickupGlyph::Assign( const EventProcessorPickupGlyph& _eventProcessorPickupGlyph )
{
	filter.flags = _eventProcessorPickupGlyph.filter.flags;
	filter.onlySingleTarget = _eventProcessorPickupGlyph.filter.onlySingleTarget;
	filter.abilityCostMode = _eventProcessorPickupGlyph.filter.abilityCostMode;
	filter.abilitiesList = _eventProcessorPickupGlyph.filter.abilitiesList;
	filter.exceptThis = _eventProcessorPickupGlyph.filter.exceptThis;
	filter.abilityCondition = _eventProcessorPickupGlyph.filter.abilityCondition;
	applyTarget = _eventProcessorPickupGlyph.applyTarget;
	spell = _eventProcessorPickupGlyph.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorPickupGlyph::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorPickupGlyph( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EventProcessorUnitDieNearMe::EventProcessorUnitDieNearMe() :
		targets( ESpellTarget( SPELLTARGET_ALLENEMIES | SPELLTARGET_ALLY ) )
	, killerFlags( UNITDIEKILLERSFLAGS_KILLEDBYALL )
	, senderMatchTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, checkSender( TRIGGEREVENTCHECKSENDER_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorUnitDieNearMe::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EventProcessorBase*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &targets );
	saver.Add( 4, &killerFlags );
	saver.Add( 5, &senderMatchTarget );
	saver.Add( 6, &checkSender );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EventProcessorUnitDieNearMe::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EventProcessorUnitDieNearMe* parentPtr = (EventProcessorUnitDieNearMe*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorUnitDieNearMe::SerializeSelf( IXmlSaver &saver )
{
	EventProcessorBase::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "targets", &targets );
	saver.Add( "killerFlags", &killerFlags );
	saver.Add( "senderMatchTarget", &senderMatchTarget );
	saver.Add( "checkSender", &checkSender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventProcessorUnitDieNearMe::Assign( const EventProcessorUnitDieNearMe& _eventProcessorUnitDieNearMe )
{
	range = _eventProcessorUnitDieNearMe.range;
	targets = _eventProcessorUnitDieNearMe.targets;
	killerFlags = _eventProcessorUnitDieNearMe.killerFlags;
	senderMatchTarget = _eventProcessorUnitDieNearMe.senderMatchTarget;
	checkSender = _eventProcessorUnitDieNearMe.checkSender;
	applyTarget = _eventProcessorUnitDieNearMe.applyTarget;
	spell = _eventProcessorUnitDieNearMe.spell;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFEventProcessorBase* EventProcessorUnitDieNearMe::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFEventProcessorUnitDieNearMe( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EyeApplicator::EyeApplicator() :
		flags( FACTIONFLAGS_SELF )
	, eyeTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, cancelObstacles( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EyeApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &visRange );
	saver.Add( 3, &flags );
	saver.Add( 4, &eyeTarget );
	saver.Add( 5, &cancelObstacles );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EyeApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EyeApplicator* parentPtr = (EyeApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EyeApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "visRange", &visRange );
	saver.Add( "flags", &flags );
	saver.Add( "eyeTarget", &eyeTarget );
	saver.Add( "cancelObstacles", &cancelObstacles );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EyeApplicator::Assign( const EyeApplicator& _eyeApplicator )
{
	visRange = _eyeApplicator.visRange;
	flags = _eyeApplicator.flags;
	eyeTarget = _eyeApplicator.eyeTarget;
	cancelObstacles = _eyeApplicator.cancelObstacles;
	behaviorFlags = _eyeApplicator.behaviorFlags;
	lifeTime = _eyeApplicator.lifeTime;
	effect = _eyeApplicator.effect;
	startCondition = _eyeApplicator.startCondition;
	enabled = _eyeApplicator.enabled;
	applyTarget = _eyeApplicator.applyTarget;
	formulaName = _eyeApplicator.formulaName;
	LoggingEvent = _eyeApplicator.LoggingEvent;
	providerName = _eyeApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* EyeApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplEye>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FilterTargetSelector::FilterTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FilterTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &suitableUnits );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FilterTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FilterTargetSelector* parentPtr = (FilterTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FilterTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "suitableUnits", &suitableUnits );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FilterTargetSelector::Assign( const FilterTargetSelector& _filterTargetSelector )
{
	targetSelector = _filterTargetSelector.targetSelector;
	suitableUnits = _filterTargetSelector.suitableUnits;
	mode = _filterTargetSelector.mode;
	flags = _filterTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* FilterTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFFilterTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FirstTargetSelector::FirstTargetSelector() :
		nearestTarget( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FirstTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &nearestTarget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FirstTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FirstTargetSelector* parentPtr = (FirstTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FirstTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "nearestTarget", &nearestTarget );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FirstTargetSelector::Assign( const FirstTargetSelector& _firstTargetSelector )
{
	targetSelector = _firstTargetSelector.targetSelector;
	nearestTarget = _firstTargetSelector.nearestTarget;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* FirstTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFFirstTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FixToCenterTargetSelector::FixToCenterTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FixToCenterTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &nameScriptArea );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FixToCenterTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FixToCenterTargetSelector* parentPtr = (FixToCenterTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FixToCenterTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "nameScriptArea", &nameScriptArea );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FixToCenterTargetSelector::Assign( const FixToCenterTargetSelector& _fixToCenterTargetSelector )
{
	targetSelector = _fixToCenterTargetSelector.targetSelector;
	nameScriptArea = _fixToCenterTargetSelector.nameScriptArea;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* FixToCenterTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFFixToCenterTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlagsApplicator::FlagsApplicator() :
		flag( EUnitFlag( 0 ) )
	, useListAs( USEMODE_LISTASRULE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagsApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &flag );
	saver.Add( 3, &talents );
	saver.Add( 4, &consumables );
	saver.Add( 5, &useListAs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagsApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FlagsApplicator* parentPtr = (FlagsApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagsApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "flag", &flag );
	saver.Add( "talents", &talents );
	saver.Add( "consumables", &consumables );
	saver.Add( "useListAs", &useListAs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagsApplicator::Assign( const FlagsApplicator& _flagsApplicator )
{
	flag = _flagsApplicator.flag;
	talents = _flagsApplicator.talents;
	consumables = _flagsApplicator.consumables;
	useListAs = _flagsApplicator.useListAs;
	behaviorFlags = _flagsApplicator.behaviorFlags;
	lifeTime = _flagsApplicator.lifeTime;
	effect = _flagsApplicator.effect;
	startCondition = _flagsApplicator.startCondition;
	enabled = _flagsApplicator.enabled;
	applyTarget = _flagsApplicator.applyTarget;
	formulaName = _flagsApplicator.formulaName;
	LoggingEvent = _flagsApplicator.LoggingEvent;
	providerName = _flagsApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* FlagsApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplFlags>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlyApplicator::FlyApplicator() :
		flightHeight( 3.0f )
	, startTime( 1.0f )
	, stopTime( 1.0f )
	, animatedStopTime( 1.0f )
	, collisionFlags( EGhostMoveMode( GHOSTMOVEMODE_IGNORESTATIC | GHOSTMOVEMODE_IGNOREBUILDINGS | GHOSTMOVEMODE_IGNOREDYNAMIC ) )
	, push( false )
	, radiusFixObstacle( 30.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlyApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &flightHeight );
	saver.Add( 3, &startTime );
	saver.Add( 4, &stopTime );
	saver.Add( 5, &animatedStopTime );
	saver.Add( 6, &collisionFlags );
	saver.Add( 7, &push );
	saver.Add( 8, &startSpell );
	saver.Add( 9, &stopSpell );
	saver.Add( 10, &replaceAnimations );
	saver.Add( 11, &radiusFixObstacle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlyApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FlyApplicator* parentPtr = (FlyApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlyApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "flightHeight", &flightHeight );
	saver.Add( "startTime", &startTime );
	saver.Add( "stopTime", &stopTime );
	saver.Add( "animatedStopTime", &animatedStopTime );
	saver.Add( "collisionFlags", &collisionFlags );
	saver.Add( "push", &push );
	saver.Add( "startSpell", &startSpell );
	saver.Add( "stopSpell", &stopSpell );
	saver.Add( "replaceAnimations", &replaceAnimations );
	saver.Add( "radiusFixObstacle", &radiusFixObstacle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlyApplicator::Assign( const FlyApplicator& _flyApplicator )
{
	flightHeight = _flyApplicator.flightHeight;
	startTime = _flyApplicator.startTime;
	stopTime = _flyApplicator.stopTime;
	animatedStopTime = _flyApplicator.animatedStopTime;
	collisionFlags = _flyApplicator.collisionFlags;
	push = _flyApplicator.push;
	startSpell = _flyApplicator.startSpell;
	stopSpell = _flyApplicator.stopSpell;
	replaceAnimations = _flyApplicator.replaceAnimations;
	radiusFixObstacle = _flyApplicator.radiusFixObstacle;
	behaviorFlags = _flyApplicator.behaviorFlags;
	lifeTime = _flyApplicator.lifeTime;
	effect = _flyApplicator.effect;
	startCondition = _flyApplicator.startCondition;
	enabled = _flyApplicator.enabled;
	applyTarget = _flyApplicator.applyTarget;
	formulaName = _flyApplicator.formulaName;
	LoggingEvent = _flyApplicator.LoggingEvent;
	providerName = _flyApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* FlyApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplFly>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ForAllTargetsApplicator::ForAllTargetsApplicator() :
		continueEvents( PARENTNOTIFICATIONFLAGS_ZERO )
	, stopEvents( PARENTNOTIFICATIONFLAGS_ZERO )
	, skipTargetIfInvalid( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForAllTargetsApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &targets );
	saver.Add( 3, &program );
	saver.Add( 4, &continueEvents );
	saver.Add( 5, &stopEvents );
	saver.Add( 6, &skipTargetIfInvalid );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForAllTargetsApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ForAllTargetsApplicator* parentPtr = (ForAllTargetsApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForAllTargetsApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "targets", &targets );
	saver.Add( "program", &program );
	saver.Add( "continueEvents", &continueEvents );
	saver.Add( "stopEvents", &stopEvents );
	saver.Add( "skipTargetIfInvalid", &skipTargetIfInvalid );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForAllTargetsApplicator::Assign( const ForAllTargetsApplicator& _forAllTargetsApplicator )
{
	targets = _forAllTargetsApplicator.targets;
	program = _forAllTargetsApplicator.program;
	continueEvents = _forAllTargetsApplicator.continueEvents;
	stopEvents = _forAllTargetsApplicator.stopEvents;
	skipTargetIfInvalid = _forAllTargetsApplicator.skipTargetIfInvalid;
	behaviorFlags = _forAllTargetsApplicator.behaviorFlags;
	lifeTime = _forAllTargetsApplicator.lifeTime;
	effect = _forAllTargetsApplicator.effect;
	startCondition = _forAllTargetsApplicator.startCondition;
	enabled = _forAllTargetsApplicator.enabled;
	applyTarget = _forAllTargetsApplicator.applyTarget;
	formulaName = _forAllTargetsApplicator.formulaName;
	LoggingEvent = _forAllTargetsApplicator.LoggingEvent;
	providerName = _forAllTargetsApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ForAllTargetsApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplForAllTargets>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FountainTargetSelector::FountainTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FountainTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FountainTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FountainTargetSelector* parentPtr = (FountainTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FountainTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FountainTargetSelector::Assign( const FountainTargetSelector& _fountainTargetSelector )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* FountainTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFFountainTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FXApplicator::FXApplicator() :
		flags( EFXFlags( 0 ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FXApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &auxillaryTarget );
	saver.Add( 3, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FXApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FXApplicator* parentPtr = (FXApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FXApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "auxillaryTarget", &auxillaryTarget );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FXApplicator::Assign( const FXApplicator& _fXApplicator )
{
	auxillaryTarget = _fXApplicator.auxillaryTarget;
	flags = _fXApplicator.flags;
	behaviorFlags = _fXApplicator.behaviorFlags;
	lifeTime = _fXApplicator.lifeTime;
	effect = _fXApplicator.effect;
	startCondition = _fXApplicator.startCondition;
	enabled = _fXApplicator.enabled;
	applyTarget = _fXApplicator.applyTarget;
	formulaName = _fXApplicator.formulaName;
	LoggingEvent = _fXApplicator.LoggingEvent;
	providerName = _fXApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* FXApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplFX>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GhostMoveApplicator::GhostMoveApplicator() :
		collisionFlags( EGhostMoveMode( 0 ) )
	, pushUnits( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GhostMoveApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &collisionFlags );
	saver.Add( 3, &pushUnits );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GhostMoveApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GhostMoveApplicator* parentPtr = (GhostMoveApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostMoveApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "collisionFlags", &collisionFlags );
	saver.Add( "pushUnits", &pushUnits );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostMoveApplicator::Assign( const GhostMoveApplicator& _ghostMoveApplicator )
{
	collisionFlags = _ghostMoveApplicator.collisionFlags;
	pushUnits = _ghostMoveApplicator.pushUnits;
	behaviorFlags = _ghostMoveApplicator.behaviorFlags;
	lifeTime = _ghostMoveApplicator.lifeTime;
	effect = _ghostMoveApplicator.effect;
	startCondition = _ghostMoveApplicator.startCondition;
	enabled = _ghostMoveApplicator.enabled;
	applyTarget = _ghostMoveApplicator.applyTarget;
	formulaName = _ghostMoveApplicator.formulaName;
	LoggingEvent = _ghostMoveApplicator.LoggingEvent;
	providerName = _ghostMoveApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* GhostMoveApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplGhostMove>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GiveConsumable::GiveConsumable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GiveConsumable::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &consumable );
	saver.Add( 3, &amount );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GiveConsumable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GiveConsumable* parentPtr = (GiveConsumable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GiveConsumable::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "consumable", &consumable );
	saver.Add( "amount", &amount );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GiveConsumable::Assign( const GiveConsumable& _giveConsumable )
{
	consumable = _giveConsumable.consumable;
	amount = _giveConsumable.amount;
	enabled = _giveConsumable.enabled;
	applyTarget = _giveConsumable.applyTarget;
	formulaName = _giveConsumable.formulaName;
	LoggingEvent = _giveConsumable.LoggingEvent;
	providerName = _giveConsumable.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* GiveConsumable::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplGiveConsumable>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HealApplicator::HealApplicator() :
		healTarget( HEALTARGET_HEALTH )
	, ignoreHealingMods( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HealApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &amount );
	saver.Add( 3, &healTarget );
	saver.Add( 4, &uiEvent );
	saver.Add( 5, &ignoreHealingMods );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HealApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HealApplicator* parentPtr = (HealApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HealApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "amount", &amount );
	saver.Add( "healTarget", &healTarget );
	saver.Add( "uiEvent", &uiEvent );
	saver.Add( "ignoreHealingMods", &ignoreHealingMods );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HealApplicator::Assign( const HealApplicator& _healApplicator )
{
	amount = _healApplicator.amount;
	healTarget = _healApplicator.healTarget;
	uiEvent = _healApplicator.uiEvent;
	ignoreHealingMods = _healApplicator.ignoreHealingMods;
	enabled = _healApplicator.enabled;
	applyTarget = _healApplicator.applyTarget;
	formulaName = _healApplicator.formulaName;
	LoggingEvent = _healApplicator.LoggingEvent;
	providerName = _healApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* HealApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplHeal>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroEnumerator::HeroEnumerator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroEnumerator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroEnumerator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroEnumerator* parentPtr = (HeroEnumerator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroEnumerator::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroEnumerator::Assign( const HeroEnumerator& _heroEnumerator )
{
	targetFilter = _heroEnumerator.targetFilter;
	mode = _heroEnumerator.mode;
	flags = _heroEnumerator.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* HeroEnumerator::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFHeroEnumerator( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HighlanderA1TargetSelector::HighlanderA1TargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HighlanderA1TargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &targetCount );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HighlanderA1TargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HighlanderA1TargetSelector* parentPtr = (HighlanderA1TargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HighlanderA1TargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "targetCount", &targetCount );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HighlanderA1TargetSelector::Assign( const HighlanderA1TargetSelector& _highlanderA1TargetSelector )
{
	range = _highlanderA1TargetSelector.range;
	targetCount = _highlanderA1TargetSelector.targetCount;
	targetFilter = _highlanderA1TargetSelector.targetFilter;
	mode = _highlanderA1TargetSelector.mode;
	flags = _highlanderA1TargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* HighlanderA1TargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFHighlanderA1TargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InvalidAbilityTargetApplicator::InvalidAbilityTargetApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvalidAbilityTargetApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvalidAbilityTargetApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			InvalidAbilityTargetApplicator* parentPtr = (InvalidAbilityTargetApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvalidAbilityTargetApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvalidAbilityTargetApplicator::Assign( const InvalidAbilityTargetApplicator& _invalidAbilityTargetApplicator )
{
	behaviorFlags = _invalidAbilityTargetApplicator.behaviorFlags;
	lifeTime = _invalidAbilityTargetApplicator.lifeTime;
	effect = _invalidAbilityTargetApplicator.effect;
	startCondition = _invalidAbilityTargetApplicator.startCondition;
	enabled = _invalidAbilityTargetApplicator.enabled;
	applyTarget = _invalidAbilityTargetApplicator.applyTarget;
	formulaName = _invalidAbilityTargetApplicator.formulaName;
	LoggingEvent = _invalidAbilityTargetApplicator.LoggingEvent;
	providerName = _invalidAbilityTargetApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* InvalidAbilityTargetApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplInvalidAbilityTarget>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InvisibilityApplicator::InvisibilityApplicator() :
		ignoreCancel( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvisibilityApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &fadeIn );
	saver.Add( 3, &onBecomeInvisible );
	saver.Add( 4, &ignoreCancel );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InvisibilityApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			InvisibilityApplicator* parentPtr = (InvisibilityApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvisibilityApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "fadeIn", &fadeIn );
	saver.Add( "onBecomeInvisible", &onBecomeInvisible );
	saver.Add( "ignoreCancel", &ignoreCancel );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InvisibilityApplicator::Assign( const InvisibilityApplicator& _invisibilityApplicator )
{
	fadeIn = _invisibilityApplicator.fadeIn;
	onBecomeInvisible = _invisibilityApplicator.onBecomeInvisible;
	ignoreCancel = _invisibilityApplicator.ignoreCancel;
	behaviorFlags = _invisibilityApplicator.behaviorFlags;
	lifeTime = _invisibilityApplicator.lifeTime;
	effect = _invisibilityApplicator.effect;
	startCondition = _invisibilityApplicator.startCondition;
	enabled = _invisibilityApplicator.enabled;
	applyTarget = _invisibilityApplicator.applyTarget;
	formulaName = _invisibilityApplicator.formulaName;
	LoggingEvent = _invisibilityApplicator.LoggingEvent;
	providerName = _invisibilityApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* InvisibilityApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplInvisibility>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KickAwayApplicator::KickAwayApplicator() :
		distance( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KickAwayApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &distance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KickAwayApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			KickAwayApplicator* parentPtr = (KickAwayApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KickAwayApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "distance", &distance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KickAwayApplicator::Assign( const KickAwayApplicator& _kickAwayApplicator )
{
	distance = _kickAwayApplicator.distance;
	enabled = _kickAwayApplicator.enabled;
	applyTarget = _kickAwayApplicator.applyTarget;
	formulaName = _kickAwayApplicator.formulaName;
	LoggingEvent = _kickAwayApplicator.LoggingEvent;
	providerName = _kickAwayApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* KickAwayApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplKickAway>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KillApplicator::KillApplicator() :
		flag( KILLMODE_NONE )
	, dontGiveRewards( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &flag );
	saver.Add( 3, &dontGiveRewards );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			KillApplicator* parentPtr = (KillApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "flag", &flag );
	saver.Add( "dontGiveRewards", &dontGiveRewards );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillApplicator::Assign( const KillApplicator& _killApplicator )
{
	flag = _killApplicator.flag;
	dontGiveRewards = _killApplicator.dontGiveRewards;
	enabled = _killApplicator.enabled;
	applyTarget = _killApplicator.applyTarget;
	formulaName = _killApplicator.formulaName;
	LoggingEvent = _killApplicator.LoggingEvent;
	providerName = _killApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* KillApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplKill>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ListOfTargetSelectors::ListOfTargetSelectors()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ListOfTargetSelectors::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelectors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ListOfTargetSelectors::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ListOfTargetSelectors* parentPtr = (ListOfTargetSelectors*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListOfTargetSelectors::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelectors", &targetSelectors );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListOfTargetSelectors::Assign( const ListOfTargetSelectors& _listOfTargetSelectors )
{
	targetSelectors = _listOfTargetSelectors.targetSelectors;
	mode = _listOfTargetSelectors.mode;
	flags = _listOfTargetSelectors.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ListOfTargetSelectors::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFListOfTargetSelectors( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LockTilesApplicator::LockTilesApplicator() :
		pushCaster( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LockTilesApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &lockMask );
	saver.Add( 3, &collision );
	saver.Add( 4, &pushCaster );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LockTilesApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LockTilesApplicator* parentPtr = (LockTilesApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LockTilesApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "lockMask", &lockMask );
	saver.Add( "collision", &collision );
	saver.Add( "pushCaster", &pushCaster );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LockTilesApplicator::Assign( const LockTilesApplicator& _lockTilesApplicator )
{
	lockMask.tileSize = _lockTilesApplicator.lockMask.tileSize;
	lockMask.mask = _lockTilesApplicator.lockMask.mask;
	collision = _lockTilesApplicator.collision;
	pushCaster = _lockTilesApplicator.pushCaster;
	behaviorFlags = _lockTilesApplicator.behaviorFlags;
	lifeTime = _lockTilesApplicator.lifeTime;
	effect = _lockTilesApplicator.effect;
	startCondition = _lockTilesApplicator.startCondition;
	enabled = _lockTilesApplicator.enabled;
	applyTarget = _lockTilesApplicator.applyTarget;
	formulaName = _lockTilesApplicator.formulaName;
	LoggingEvent = _lockTilesApplicator.LoggingEvent;
	providerName = _lockTilesApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* LockTilesApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplLockTiles>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainBuildingTargetSelector::MainBuildingTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainBuildingTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainBuildingTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MainBuildingTargetSelector* parentPtr = (MainBuildingTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainBuildingTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainBuildingTargetSelector::Assign( const MainBuildingTargetSelector& _mainBuildingTargetSelector )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* MainBuildingTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFMainBuildingTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MarkerApplicator::MarkerApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarkerApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &addValue );
	saver.Add( 3, &multValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarkerApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MarkerApplicator* parentPtr = (MarkerApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarkerApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "addValue", &addValue );
	saver.Add( "multValue", &multValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarkerApplicator::Assign( const MarkerApplicator& _markerApplicator )
{
	addValue = _markerApplicator.addValue;
	multValue = _markerApplicator.multValue;
	behaviorFlags = _markerApplicator.behaviorFlags;
	lifeTime = _markerApplicator.lifeTime;
	effect = _markerApplicator.effect;
	startCondition = _markerApplicator.startCondition;
	enabled = _markerApplicator.enabled;
	applyTarget = _markerApplicator.applyTarget;
	formulaName = _markerApplicator.formulaName;
	LoggingEvent = _markerApplicator.LoggingEvent;
	providerName = _markerApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* MarkerApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplMarker>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MaximizingTargetSelector::MaximizingTargetSelector() :
		searchFilter( ESpellTarget( SPELLTARGET_ALLENEMIES | SPELLTARGET_VISIBLETARGETSONLY ) )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MaximizingTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &range );
	saver.Add( 4, &searchRange );
	saver.Add( 5, &searchFilter );
	saver.Add( 6, &minTargetsNumber );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MaximizingTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MaximizingTargetSelector* parentPtr = (MaximizingTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaximizingTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "range", &range );
	saver.Add( "searchRange", &searchRange );
	saver.Add( "searchFilter", &searchFilter );
	saver.Add( "minTargetsNumber", &minTargetsNumber );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaximizingTargetSelector::Assign( const MaximizingTargetSelector& _maximizingTargetSelector )
{
	targetSelector = _maximizingTargetSelector.targetSelector;
	range = _maximizingTargetSelector.range;
	searchRange = _maximizingTargetSelector.searchRange;
	searchFilter = _maximizingTargetSelector.searchFilter;
	minTargetsNumber = _maximizingTargetSelector.minTargetsNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* MaximizingTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFMaximizingTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicMicroAI::BasicMicroAI() :
		castWhenIdle( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMicroAI::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MicroAI*)this );
	saver.Add( 2, &condition );
	saver.Add( 3, &castWhenIdle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMicroAI::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicMicroAI* parentPtr = (BasicMicroAI*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMicroAI::SerializeSelf( IXmlSaver &saver )
{
	MicroAI::SerializeSelf( saver );
	saver.Add( "condition", &condition );
	saver.Add( "castWhenIdle", &castWhenIdle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMicroAI::Assign( const BasicMicroAI& _basicMicroAI )
{
	condition = _basicMicroAI.condition;
	castWhenIdle = _basicMicroAI.castWhenIdle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFMicroAI* BasicMicroAI::Create( NWorld::PFMicroAICreateParams const &cp ) const
{
	return NWorld::CreateMicroAI<NWorld::PFBasicMicroAI>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModifyTerrainApplicator::ModifyTerrainApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModifyTerrainApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &durationTime );
	saver.Add( 3, &faction );
	saver.Add( 4, &modifRadius );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModifyTerrainApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ModifyTerrainApplicator* parentPtr = (ModifyTerrainApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyTerrainApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "durationTime", &durationTime );
	saver.Add( "faction", &faction );
	saver.Add( "modifRadius", &modifRadius );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyTerrainApplicator::Assign( const ModifyTerrainApplicator& _modifyTerrainApplicator )
{
	durationTime = _modifyTerrainApplicator.durationTime;
	faction = _modifyTerrainApplicator.faction;
	modifRadius = _modifyTerrainApplicator.modifRadius;
	enabled = _modifyTerrainApplicator.enabled;
	applyTarget = _modifyTerrainApplicator.applyTarget;
	formulaName = _modifyTerrainApplicator.formulaName;
	LoggingEvent = _modifyTerrainApplicator.LoggingEvent;
	providerName = _modifyTerrainApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ModifyTerrainApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplModifyTerrain>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MountApplicator::MountApplicator() :
		mountTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, controlMount( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MountApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &mountTarget );
	saver.Add( 3, &controlMount );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MountApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MountApplicator* parentPtr = (MountApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MountApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "mountTarget", &mountTarget );
	saver.Add( "controlMount", &controlMount );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MountApplicator::Assign( const MountApplicator& _mountApplicator )
{
	mountTarget = _mountApplicator.mountTarget;
	controlMount = _mountApplicator.controlMount;
	behaviorFlags = _mountApplicator.behaviorFlags;
	lifeTime = _mountApplicator.lifeTime;
	effect = _mountApplicator.effect;
	startCondition = _mountApplicator.startCondition;
	enabled = _mountApplicator.enabled;
	applyTarget = _mountApplicator.applyTarget;
	formulaName = _mountApplicator.formulaName;
	LoggingEvent = _mountApplicator.LoggingEvent;
	providerName = _mountApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* MountApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplMount>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MovementControlApplicator::MovementControlApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MovementControlApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MovementControlApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MovementControlApplicator* parentPtr = (MovementControlApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovementControlApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovementControlApplicator::Assign( const MovementControlApplicator& _movementControlApplicator )
{
	behaviorFlags = _movementControlApplicator.behaviorFlags;
	lifeTime = _movementControlApplicator.lifeTime;
	effect = _movementControlApplicator.effect;
	startCondition = _movementControlApplicator.startCondition;
	enabled = _movementControlApplicator.enabled;
	applyTarget = _movementControlApplicator.applyTarget;
	formulaName = _movementControlApplicator.formulaName;
	LoggingEvent = _movementControlApplicator.LoggingEvent;
	providerName = _movementControlApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* MovementControlApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplMovementControl>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MoveToApplicator::MoveToApplicator() :
		moveTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, pushUnits( false )
	, justRotate( false )
	, isNotStackable( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MoveToApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &moveRange );
	saver.Add( 3, &moveSpeed );
	saver.Add( 4, &moveTarget );
	saver.Add( 5, &offset );
	saver.Add( 6, &isMoveDirect );
	saver.Add( 7, &pushUnits );
	saver.Add( 8, &justRotate );
	saver.Add( 9, &isNotStackable );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MoveToApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MoveToApplicator* parentPtr = (MoveToApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveToApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "moveRange", &moveRange );
	saver.Add( "moveSpeed", &moveSpeed );
	saver.Add( "moveTarget", &moveTarget );
	saver.Add( "offset", &offset );
	saver.Add( "isMoveDirect", &isMoveDirect );
	saver.Add( "pushUnits", &pushUnits );
	saver.Add( "justRotate", &justRotate );
	saver.Add( "isNotStackable", &isNotStackable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveToApplicator::Assign( const MoveToApplicator& _moveToApplicator )
{
	moveRange = _moveToApplicator.moveRange;
	moveSpeed = _moveToApplicator.moveSpeed;
	moveTarget = _moveToApplicator.moveTarget;
	offset = _moveToApplicator.offset;
	isMoveDirect = _moveToApplicator.isMoveDirect;
	pushUnits = _moveToApplicator.pushUnits;
	justRotate = _moveToApplicator.justRotate;
	isNotStackable = _moveToApplicator.isNotStackable;
	behaviorFlags = _moveToApplicator.behaviorFlags;
	lifeTime = _moveToApplicator.lifeTime;
	effect = _moveToApplicator.effect;
	startCondition = _moveToApplicator.startCondition;
	enabled = _moveToApplicator.enabled;
	applyTarget = _moveToApplicator.applyTarget;
	formulaName = _moveToApplicator.formulaName;
	LoggingEvent = _moveToApplicator.LoggingEvent;
	providerName = _moveToApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* MoveToApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplMoveTo>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicatorRecipientsTargetSelector::ApplicatorRecipientsTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorRecipientsTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &applicator );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicatorRecipientsTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ApplicatorRecipientsTargetSelector* parentPtr = (ApplicatorRecipientsTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorRecipientsTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "applicator", &applicator );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicatorRecipientsTargetSelector::Assign( const ApplicatorRecipientsTargetSelector& _applicatorRecipientsTargetSelector )
{
	applicator = _applicatorRecipientsTargetSelector.applicator;
	mode = _applicatorRecipientsTargetSelector.mode;
	flags = _applicatorRecipientsTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ApplicatorRecipientsTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFApplicatorRecipientsTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AreaTargetSelector::AreaTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AreaTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &absolutePosition );
	saver.Add( 4, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AreaTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AreaTargetSelector* parentPtr = (AreaTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AreaTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "absolutePosition", &absolutePosition );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AreaTargetSelector::Assign( const AreaTargetSelector& _areaTargetSelector )
{
	range = _areaTargetSelector.range;
	absolutePosition = _areaTargetSelector.absolutePosition;
	targetSelector = _areaTargetSelector.targetSelector;
	targetFilter = _areaTargetSelector.targetFilter;
	mode = _areaTargetSelector.mode;
	flags = _areaTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* AreaTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAreaTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultipleTargetSelectorMicroAI::MultipleTargetSelectorMicroAI() :
		minTargetCount( 1 )
	, minTargetWeight( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelectorMicroAI::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicMicroAI*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &unitFilter );
	saver.Add( 4, &minTargetCount );
	saver.Add( 5, &minTargetWeight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MultipleTargetSelectorMicroAI::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MultipleTargetSelectorMicroAI* parentPtr = (MultipleTargetSelectorMicroAI*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelectorMicroAI::SerializeSelf( IXmlSaver &saver )
{
	BasicMicroAI::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "unitFilter", &unitFilter );
	saver.Add( "minTargetCount", &minTargetCount );
	saver.Add( "minTargetWeight", &minTargetWeight );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MultipleTargetSelectorMicroAI::Assign( const MultipleTargetSelectorMicroAI& _multipleTargetSelectorMicroAI )
{
	targetSelector = _multipleTargetSelectorMicroAI.targetSelector;
	unitFilter = _multipleTargetSelectorMicroAI.unitFilter;
	minTargetCount = _multipleTargetSelectorMicroAI.minTargetCount;
	minTargetWeight = _multipleTargetSelectorMicroAI.minTargetWeight;
	condition = _multipleTargetSelectorMicroAI.condition;
	castWhenIdle = _multipleTargetSelectorMicroAI.castWhenIdle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFMicroAI* MultipleTargetSelectorMicroAI::Create( NWorld::PFMicroAICreateParams const &cp ) const
{
	return NWorld::CreateMicroAI<NWorld::PFMultipleTargetSelectorMicroAI>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NaftaTransferApplicator::NaftaTransferApplicator() :
		naftaTransferTarget( APPLICATORAPPLYTARGET_ABILITYOWNER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NaftaTransferApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &naftaTransferTarget );
	saver.Add( 3, &amount );
	saver.Add( 4, &multiplier );
	saver.Add( 5, &addition );
	saver.Add( 6, &uiEvent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NaftaTransferApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NaftaTransferApplicator* parentPtr = (NaftaTransferApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NaftaTransferApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "naftaTransferTarget", &naftaTransferTarget );
	saver.Add( "amount", &amount );
	saver.Add( "multiplier", &multiplier );
	saver.Add( "addition", &addition );
	saver.Add( "uiEvent", &uiEvent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NaftaTransferApplicator::Assign( const NaftaTransferApplicator& _naftaTransferApplicator )
{
	naftaTransferTarget = _naftaTransferApplicator.naftaTransferTarget;
	amount = _naftaTransferApplicator.amount;
	multiplier = _naftaTransferApplicator.multiplier;
	addition = _naftaTransferApplicator.addition;
	uiEvent = _naftaTransferApplicator.uiEvent;
	enabled = _naftaTransferApplicator.enabled;
	applyTarget = _naftaTransferApplicator.applyTarget;
	formulaName = _naftaTransferApplicator.formulaName;
	LoggingEvent = _naftaTransferApplicator.LoggingEvent;
	providerName = _naftaTransferApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* NaftaTransferApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplNaftaTransfer>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NearestInAreaTargetSelector::NearestInAreaTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NearestInAreaTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &range );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NearestInAreaTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NearestInAreaTargetSelector* parentPtr = (NearestInAreaTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NearestInAreaTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "range", &range );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NearestInAreaTargetSelector::Assign( const NearestInAreaTargetSelector& _nearestInAreaTargetSelector )
{
	range = _nearestInAreaTargetSelector.range;
	targetFilter = _nearestInAreaTargetSelector.targetFilter;
	mode = _nearestInAreaTargetSelector.mode;
	flags = _nearestInAreaTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* NearestInAreaTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFNearestInAreaTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NearestTargetSelector::NearestTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NearestTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NearestTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NearestTargetSelector* parentPtr = (NearestTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NearestTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NearestTargetSelector::Assign( const NearestTargetSelector& _nearestTargetSelector )
{
	targetSelector = _nearestTargetSelector.targetSelector;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* NearestTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFNearestTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NotTargetOfSameAbilitySelector::NotTargetOfSameAbilitySelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NotTargetOfSameAbilitySelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &abilityCastersSelector );
	saver.Add( 4, &minDistBetweenTargets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NotTargetOfSameAbilitySelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NotTargetOfSameAbilitySelector* parentPtr = (NotTargetOfSameAbilitySelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NotTargetOfSameAbilitySelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "abilityCastersSelector", &abilityCastersSelector );
	saver.Add( "minDistBetweenTargets", &minDistBetweenTargets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NotTargetOfSameAbilitySelector::Assign( const NotTargetOfSameAbilitySelector& _notTargetOfSameAbilitySelector )
{
	targetSelector = _notTargetOfSameAbilitySelector.targetSelector;
	abilityCastersSelector = _notTargetOfSameAbilitySelector.abilityCastersSelector;
	minDistBetweenTargets = _notTargetOfSameAbilitySelector.minDistBetweenTargets;
	mode = _notTargetOfSameAbilitySelector.mode;
	flags = _notTargetOfSameAbilitySelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* NotTargetOfSameAbilitySelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFNotTargetOfSameAbilitySelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OnDamageApplicator::OnDamageApplicator() :
		filterFlags( DAMAGEFILTER_ALL )
	, spellTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OnDamageApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &filterFlags );
	saver.Add( 3, &spell );
	saver.Add( 4, &spellTarget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OnDamageApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			OnDamageApplicator* parentPtr = (OnDamageApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnDamageApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "filterFlags", &filterFlags );
	saver.Add( "spell", &spell );
	saver.Add( "spellTarget", &spellTarget );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnDamageApplicator::Assign( const OnDamageApplicator& _onDamageApplicator )
{
	filterFlags = _onDamageApplicator.filterFlags;
	spell = _onDamageApplicator.spell;
	spellTarget = _onDamageApplicator.spellTarget;
	behaviorFlags = _onDamageApplicator.behaviorFlags;
	lifeTime = _onDamageApplicator.lifeTime;
	effect = _onDamageApplicator.effect;
	startCondition = _onDamageApplicator.startCondition;
	enabled = _onDamageApplicator.enabled;
	applyTarget = _onDamageApplicator.applyTarget;
	formulaName = _onDamageApplicator.formulaName;
	LoggingEvent = _onDamageApplicator.LoggingEvent;
	providerName = _onDamageApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* OnDamageApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplOnDamage>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PermanentStatModApplicator::PermanentStatModApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PermanentStatModApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &modifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PermanentStatModApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PermanentStatModApplicator* parentPtr = (PermanentStatModApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PermanentStatModApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "modifier", &modifier );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PermanentStatModApplicator::Assign( const PermanentStatModApplicator& _permanentStatModApplicator )
{
	modifier.stat = _permanentStatModApplicator.modifier.stat;
	modifier.variable = _permanentStatModApplicator.modifier.variable;
	modifier.addValue = _permanentStatModApplicator.modifier.addValue;
	modifier.multValue = _permanentStatModApplicator.modifier.multValue;
	modifier.topModifier = _permanentStatModApplicator.modifier.topModifier;
	enabled = _permanentStatModApplicator.enabled;
	applyTarget = _permanentStatModApplicator.applyTarget;
	formulaName = _permanentStatModApplicator.formulaName;
	LoggingEvent = _permanentStatModApplicator.LoggingEvent;
	providerName = _permanentStatModApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* PermanentStatModApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplPermanentStatMod>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PickupChannelingApplicator::PickupChannelingApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PickupChannelingApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ChannellingApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PickupChannelingApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PickupChannelingApplicator* parentPtr = (PickupChannelingApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PickupChannelingApplicator::SerializeSelf( IXmlSaver &saver )
{
	ChannellingApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PickupChannelingApplicator::Assign( const PickupChannelingApplicator& _pickupChannelingApplicator )
{
	targetSelector = _pickupChannelingApplicator.targetSelector;
	channelingType = _pickupChannelingApplicator.channelingType;
	applicatorsOnSelf = _pickupChannelingApplicator.applicatorsOnSelf;
	startSpell = _pickupChannelingApplicator.startSpell;
	periodicalSpell = _pickupChannelingApplicator.periodicalSpell;
	stopSpell = _pickupChannelingApplicator.stopSpell;
	cancelSpell = _pickupChannelingApplicator.cancelSpell;
	period = _pickupChannelingApplicator.period;
	interruptEvents = _pickupChannelingApplicator.interruptEvents;
	cancelOnInterrupt = _pickupChannelingApplicator.cancelOnInterrupt;
	removeStartSpellEffectOnInterrupt = _pickupChannelingApplicator.removeStartSpellEffectOnInterrupt;
	scaleWhenInterrupted = _pickupChannelingApplicator.scaleWhenInterrupted;
	cancelOnDisable = _pickupChannelingApplicator.cancelOnDisable;
	behaviorFlags = _pickupChannelingApplicator.behaviorFlags;
	lifeTime = _pickupChannelingApplicator.lifeTime;
	effect = _pickupChannelingApplicator.effect;
	startCondition = _pickupChannelingApplicator.startCondition;
	enabled = _pickupChannelingApplicator.enabled;
	applyTarget = _pickupChannelingApplicator.applyTarget;
	formulaName = _pickupChannelingApplicator.formulaName;
	LoggingEvent = _pickupChannelingApplicator.LoggingEvent;
	providerName = _pickupChannelingApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* PickupChannelingApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplPickupChanneling>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointTargetSelector::PointTargetSelector() :
		mode( POINTTARGETSELECTORMODE_TOOWNER )
	, traceMode( ETraceMode( 0 ) )
	, checkMinRange( true )
	, paralleledTarget( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &mode );
	saver.Add( 4, &range );
	saver.Add( 5, &offset );
	saver.Add( 6, &traceMode );
	saver.Add( 7, &checkMinRange );
	saver.Add( 8, &paralleledTarget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PointTargetSelector* parentPtr = (PointTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PointTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "mode", &mode );
	saver.Add( "range", &range );
	saver.Add( "offset", &offset );
	saver.Add( "traceMode", &traceMode );
	saver.Add( "checkMinRange", &checkMinRange );
	saver.Add( "paralleledTarget", &paralleledTarget );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PointTargetSelector::Assign( const PointTargetSelector& _pointTargetSelector )
{
	targetSelector = _pointTargetSelector.targetSelector;
	mode = _pointTargetSelector.mode;
	range = _pointTargetSelector.range;
	offset = _pointTargetSelector.offset;
	traceMode = _pointTargetSelector.traceMode;
	checkMinRange = _pointTargetSelector.checkMinRange;
	paralleledTarget = _pointTargetSelector.paralleledTarget;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* PointTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFPointTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PositionCastLimitation::PositionCastLimitation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PositionCastLimitation::operator&( IBinSaver &saver )
{
	saver.Add( 1, (CastLimitation*)this );
	saver.Add( 2, &condition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PositionCastLimitation::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PositionCastLimitation* parentPtr = (PositionCastLimitation*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PositionCastLimitation::SerializeSelf( IXmlSaver &saver )
{
	CastLimitation::SerializeSelf( saver );
	saver.Add( "condition", &condition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PositionCastLimitation::Assign( const PositionCastLimitation& _positionCastLimitation )
{
	condition = _positionCastLimitation.condition;
	uiEvent = _positionCastLimitation.uiEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFAbilityData* PositionCastLimitation::Check( NWorld::CastLimitationsCheckParams const &cp ) const
{
	return NWorld::CheckPositionLimitation( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProgramApplicator::ProgramApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ProgramApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &applicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ProgramApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ProgramApplicator* parentPtr = (ProgramApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgramApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "applicators", &applicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgramApplicator::Assign( const ProgramApplicator& _programApplicator )
{
	applicators = _programApplicator.applicators;
	behaviorFlags = _programApplicator.behaviorFlags;
	lifeTime = _programApplicator.lifeTime;
	effect = _programApplicator.effect;
	startCondition = _programApplicator.startCondition;
	enabled = _programApplicator.enabled;
	applyTarget = _programApplicator.applyTarget;
	formulaName = _programApplicator.formulaName;
	LoggingEvent = _programApplicator.LoggingEvent;
	providerName = _programApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ProgramApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplProgram>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RaiseFlagApplicator::RaiseFlagApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RaiseFlagApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ChannellingApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RaiseFlagApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RaiseFlagApplicator* parentPtr = (RaiseFlagApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RaiseFlagApplicator::SerializeSelf( IXmlSaver &saver )
{
	ChannellingApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RaiseFlagApplicator::Assign( const RaiseFlagApplicator& _raiseFlagApplicator )
{
	targetSelector = _raiseFlagApplicator.targetSelector;
	channelingType = _raiseFlagApplicator.channelingType;
	applicatorsOnSelf = _raiseFlagApplicator.applicatorsOnSelf;
	startSpell = _raiseFlagApplicator.startSpell;
	periodicalSpell = _raiseFlagApplicator.periodicalSpell;
	stopSpell = _raiseFlagApplicator.stopSpell;
	cancelSpell = _raiseFlagApplicator.cancelSpell;
	period = _raiseFlagApplicator.period;
	interruptEvents = _raiseFlagApplicator.interruptEvents;
	cancelOnInterrupt = _raiseFlagApplicator.cancelOnInterrupt;
	removeStartSpellEffectOnInterrupt = _raiseFlagApplicator.removeStartSpellEffectOnInterrupt;
	scaleWhenInterrupted = _raiseFlagApplicator.scaleWhenInterrupted;
	cancelOnDisable = _raiseFlagApplicator.cancelOnDisable;
	behaviorFlags = _raiseFlagApplicator.behaviorFlags;
	lifeTime = _raiseFlagApplicator.lifeTime;
	effect = _raiseFlagApplicator.effect;
	startCondition = _raiseFlagApplicator.startCondition;
	enabled = _raiseFlagApplicator.enabled;
	applyTarget = _raiseFlagApplicator.applyTarget;
	formulaName = _raiseFlagApplicator.formulaName;
	LoggingEvent = _raiseFlagApplicator.LoggingEvent;
	providerName = _raiseFlagApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* RaiseFlagApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplRaiseFlag>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RefreshCooldownApplicator::RefreshCooldownApplicator() :
		flags( ABILITYIDFLAGS_ALL )
	, refreshThis( false )
	, useListAs( USEMODE_LISTASRULE )
	, allowCdIncrease( false )
	, reduceByPercent( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RefreshCooldownApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &flags );
	saver.Add( 3, &refreshThis );
	saver.Add( 4, &reductionAmount );
	saver.Add( 5, &talents );
	saver.Add( 6, &useListAs );
	saver.Add( 7, &allowCdIncrease );
	saver.Add( 8, &reduceByPercent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RefreshCooldownApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RefreshCooldownApplicator* parentPtr = (RefreshCooldownApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RefreshCooldownApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "flags", &flags );
	saver.Add( "refreshThis", &refreshThis );
	saver.Add( "reductionAmount", &reductionAmount );
	saver.Add( "talents", &talents );
	saver.Add( "useListAs", &useListAs );
	saver.Add( "allowCdIncrease", &allowCdIncrease );
	saver.Add( "reduceByPercent", &reduceByPercent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RefreshCooldownApplicator::Assign( const RefreshCooldownApplicator& _refreshCooldownApplicator )
{
	flags = _refreshCooldownApplicator.flags;
	refreshThis = _refreshCooldownApplicator.refreshThis;
	reductionAmount = _refreshCooldownApplicator.reductionAmount;
	talents = _refreshCooldownApplicator.talents;
	useListAs = _refreshCooldownApplicator.useListAs;
	allowCdIncrease = _refreshCooldownApplicator.allowCdIncrease;
	reduceByPercent = _refreshCooldownApplicator.reduceByPercent;
	enabled = _refreshCooldownApplicator.enabled;
	applyTarget = _refreshCooldownApplicator.applyTarget;
	formulaName = _refreshCooldownApplicator.formulaName;
	LoggingEvent = _refreshCooldownApplicator.LoggingEvent;
	providerName = _refreshCooldownApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* RefreshCooldownApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplRefreshCooldown>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RelativeUnitTargetSelector::RelativeUnitTargetSelector() :
		relation( UNITRELATION_MASTER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RelativeUnitTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &relation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RelativeUnitTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RelativeUnitTargetSelector* parentPtr = (RelativeUnitTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RelativeUnitTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "relation", &relation );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RelativeUnitTargetSelector::Assign( const RelativeUnitTargetSelector& _relativeUnitTargetSelector )
{
	relation = _relativeUnitTargetSelector.relation;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* RelativeUnitTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFRelativeUnitTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResurrectApplicator::ResurrectApplicator() :
		healthPercent( 100.0f )
	, energyPercent( 100.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResurrectApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &healthPercent );
	saver.Add( 3, &energyPercent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResurrectApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ResurrectApplicator* parentPtr = (ResurrectApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResurrectApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "healthPercent", &healthPercent );
	saver.Add( "energyPercent", &energyPercent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResurrectApplicator::Assign( const ResurrectApplicator& _resurrectApplicator )
{
	healthPercent = _resurrectApplicator.healthPercent;
	energyPercent = _resurrectApplicator.energyPercent;
	enabled = _resurrectApplicator.enabled;
	applyTarget = _resurrectApplicator.applyTarget;
	formulaName = _resurrectApplicator.formulaName;
	LoggingEvent = _resurrectApplicator.LoggingEvent;
	providerName = _resurrectApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ResurrectApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFResurrectApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScaleControlApplicator::ScaleControlApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScaleControlApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &desiredScale );
	saver.Add( 3, &changeSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScaleControlApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScaleControlApplicator* parentPtr = (ScaleControlApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScaleControlApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "desiredScale", &desiredScale );
	saver.Add( "changeSpeed", &changeSpeed );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScaleControlApplicator::Assign( const ScaleControlApplicator& _scaleControlApplicator )
{
	desiredScale = _scaleControlApplicator.desiredScale;
	changeSpeed = _scaleControlApplicator.changeSpeed;
	behaviorFlags = _scaleControlApplicator.behaviorFlags;
	lifeTime = _scaleControlApplicator.lifeTime;
	effect = _scaleControlApplicator.effect;
	startCondition = _scaleControlApplicator.startCondition;
	enabled = _scaleControlApplicator.enabled;
	applyTarget = _scaleControlApplicator.applyTarget;
	formulaName = _scaleControlApplicator.formulaName;
	LoggingEvent = _scaleControlApplicator.LoggingEvent;
	providerName = _scaleControlApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ScaleControlApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplScaleControl>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectChangeApplicator::SceneObjectChangeApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectChangeApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &sceneObjects );
	saver.Add( 3, &sceneObjectIndex );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SceneObjectChangeApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SceneObjectChangeApplicator* parentPtr = (SceneObjectChangeApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectChangeApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "sceneObjects", &sceneObjects );
	saver.Add( "sceneObjectIndex", &sceneObjectIndex );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectChangeApplicator::Assign( const SceneObjectChangeApplicator& _sceneObjectChangeApplicator )
{
	sceneObjects = _sceneObjectChangeApplicator.sceneObjects;
	sceneObjectIndex = _sceneObjectChangeApplicator.sceneObjectIndex;
	behaviorFlags = _sceneObjectChangeApplicator.behaviorFlags;
	lifeTime = _sceneObjectChangeApplicator.lifeTime;
	effect = _sceneObjectChangeApplicator.effect;
	startCondition = _sceneObjectChangeApplicator.startCondition;
	enabled = _sceneObjectChangeApplicator.enabled;
	applyTarget = _sceneObjectChangeApplicator.applyTarget;
	formulaName = _sceneObjectChangeApplicator.formulaName;
	LoggingEvent = _sceneObjectChangeApplicator.LoggingEvent;
	providerName = _sceneObjectChangeApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SceneObjectChangeApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSceneObjectChange>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SectorTargetSelector::SectorTargetSelector() :
		segmentBegin( TARGETSELECTORPOINT_ABILITYOWNER )
	, segmentEnd( TARGETSELECTORPOINT_CURRENTPOSITION )
	, angle( 90.0f )
	, centerIsSegmentEnd( false )
	, segmentDirectionOffset( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SectorTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &segmentBegin );
	saver.Add( 3, &segmentEnd );
	saver.Add( 4, &range );
	saver.Add( 5, &angle );
	saver.Add( 6, &centerIsSegmentEnd );
	saver.Add( 7, &segmentDirectionOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SectorTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SectorTargetSelector* parentPtr = (SectorTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SectorTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "segmentBegin", &segmentBegin );
	saver.Add( "segmentEnd", &segmentEnd );
	saver.Add( "range", &range );
	saver.Add( "angle", &angle );
	saver.Add( "centerIsSegmentEnd", &centerIsSegmentEnd );
	saver.Add( "segmentDirectionOffset", &segmentDirectionOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SectorTargetSelector::Assign( const SectorTargetSelector& _sectorTargetSelector )
{
	segmentBegin = _sectorTargetSelector.segmentBegin;
	segmentEnd = _sectorTargetSelector.segmentEnd;
	range = _sectorTargetSelector.range;
	angle = _sectorTargetSelector.angle;
	centerIsSegmentEnd = _sectorTargetSelector.centerIsSegmentEnd;
	segmentDirectionOffset = _sectorTargetSelector.segmentDirectionOffset;
	targetFilter = _sectorTargetSelector.targetFilter;
	mode = _sectorTargetSelector.mode;
	flags = _sectorTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* SectorTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFSectorTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SelectApplicatorTarget::SelectApplicatorTarget() :
		selectTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, applicatorIndex( 0 )
	, namedApplicatorTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SelectApplicatorTarget::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &selectTarget );
	saver.Add( 3, &applicatorName );
	saver.Add( 4, &applicatorIndex );
	saver.Add( 5, &namedApplicatorTarget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SelectApplicatorTarget::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SelectApplicatorTarget* parentPtr = (SelectApplicatorTarget*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SelectApplicatorTarget::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "selectTarget", &selectTarget );
	saver.Add( "applicatorName", &applicatorName );
	saver.Add( "applicatorIndex", &applicatorIndex );
	saver.Add( "namedApplicatorTarget", &namedApplicatorTarget );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SelectApplicatorTarget::Assign( const SelectApplicatorTarget& _selectApplicatorTarget )
{
	selectTarget = _selectApplicatorTarget.selectTarget;
	applicatorName = _selectApplicatorTarget.applicatorName;
	applicatorIndex = _selectApplicatorTarget.applicatorIndex;
	namedApplicatorTarget = _selectApplicatorTarget.namedApplicatorTarget;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* SelectApplicatorTarget::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFSelectApplicatorTarget( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SetAdvancedSummonTargetApplicator::SetAdvancedSummonTargetApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SetAdvancedSummonTargetApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SetAdvancedSummonTargetApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SetAdvancedSummonTargetApplicator* parentPtr = (SetAdvancedSummonTargetApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetAdvancedSummonTargetApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetAdvancedSummonTargetApplicator::Assign( const SetAdvancedSummonTargetApplicator& _setAdvancedSummonTargetApplicator )
{
	enabled = _setAdvancedSummonTargetApplicator.enabled;
	applyTarget = _setAdvancedSummonTargetApplicator.applyTarget;
	formulaName = _setAdvancedSummonTargetApplicator.formulaName;
	LoggingEvent = _setAdvancedSummonTargetApplicator.LoggingEvent;
	providerName = _setAdvancedSummonTargetApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SetAdvancedSummonTargetApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplAdvancedSummonSetTarget>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SetTimescaleApplicator::SetTimescaleApplicator() :
		desiredTimescale( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SetTimescaleApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &desiredTimescale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SetTimescaleApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SetTimescaleApplicator* parentPtr = (SetTimescaleApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetTimescaleApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "desiredTimescale", &desiredTimescale );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetTimescaleApplicator::Assign( const SetTimescaleApplicator& _setTimescaleApplicator )
{
	desiredTimescale = _setTimescaleApplicator.desiredTimescale;
	enabled = _setTimescaleApplicator.enabled;
	applyTarget = _setTimescaleApplicator.applyTarget;
	formulaName = _setTimescaleApplicator.formulaName;
	LoggingEvent = _setTimescaleApplicator.LoggingEvent;
	providerName = _setTimescaleApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SetTimescaleApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSetTimescale>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShiftApplicator::ShiftApplicator() :
		shiftTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShiftApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &shiftTarget );
	saver.Add( 3, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShiftApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ShiftApplicator* parentPtr = (ShiftApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShiftApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "shiftTarget", &shiftTarget );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShiftApplicator::Assign( const ShiftApplicator& _shiftApplicator )
{
	shiftTarget = _shiftApplicator.shiftTarget;
	targetSelector = _shiftApplicator.targetSelector;
	enabled = _shiftApplicator.enabled;
	applyTarget = _shiftApplicator.applyTarget;
	formulaName = _shiftApplicator.formulaName;
	LoggingEvent = _shiftApplicator.LoggingEvent;
	providerName = _shiftApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ShiftApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplShift>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShopTargetSelector::ShopTargetSelector() :
		secret( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShopTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &secret );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShopTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ShopTargetSelector* parentPtr = (ShopTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShopTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "secret", &secret );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShopTargetSelector::Assign( const ShopTargetSelector& _shopTargetSelector )
{
	secret = _shopTargetSelector.secret;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ShopTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFShopTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ComparingTargetSelector::ComparingTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComparingTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &referenceValue );
	saver.Add( 4, &valueToCompare );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComparingTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ComparingTargetSelector* parentPtr = (ComparingTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparingTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "referenceValue", &referenceValue );
	saver.Add( "valueToCompare", &valueToCompare );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparingTargetSelector::Assign( const ComparingTargetSelector& _comparingTargetSelector )
{
	targetSelector = _comparingTargetSelector.targetSelector;
	referenceValue = _comparingTargetSelector.referenceValue;
	valueToCompare = _comparingTargetSelector.valueToCompare;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* ComparingTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFComparingTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseAttack::BaseAttack() :
		isMelee( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseAttack::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Ability*)this );
	saver.Add( 2, &isMelee );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseAttack::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BaseAttack* parentPtr = (BaseAttack*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseAttack::SerializeSelf( IXmlSaver &saver )
{
	Ability::SerializeSelf( saver );
	saver.Add( "isMelee", &isMelee );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseAttack::Assign( const BaseAttack& _baseAttack )
{
	isMelee = _baseAttack.isMelee;
	name = _baseAttack.name;
	description = _baseAttack.description;
	compiledDescriptionA = _baseAttack.compiledDescriptionA;
	compiledDescriptionB = _baseAttack.compiledDescriptionB;
	shortDescription = _baseAttack.shortDescription;
	commonDescription = _baseAttack.commonDescription;
	castLimitations = _baseAttack.castLimitations;
	image = _baseAttack.image;
	imageSecondState = _baseAttack.imageSecondState;
	aoeType = _baseAttack.aoeType;
	aoeSize = _baseAttack.aoeSize;
	aoeMaterial = _baseAttack.aoeMaterial;
	aoeHeight = _baseAttack.aoeHeight;
	useRangeMaterial = _baseAttack.useRangeMaterial;
	aoePassabilityCheckMode = _baseAttack.aoePassabilityCheckMode;
	aoeDisplayOnMinimap = _baseAttack.aoeDisplayOnMinimap;
	type = _baseAttack.type;
	cooldownTime = _baseAttack.cooldownTime;
	cooldownTimeSecondState = _baseAttack.cooldownTimeSecondState;
	manaCost = _baseAttack.manaCost;
	activeCustomTrigger = _baseAttack.activeCustomTrigger;
	useRange = _baseAttack.useRange;
	minUseRangeCorrection = _baseAttack.minUseRangeCorrection;
	castAllowRange = _baseAttack.castAllowRange;
	allowChase = _baseAttack.allowChase;
	constants = _baseAttack.constants;
	conditionFormulas = _baseAttack.conditionFormulas;
	isUnitFreeAfterCast = _baseAttack.isUnitFreeAfterCast;
	flags = _baseAttack.flags;
	targetType = _baseAttack.targetType;
	requireLineOfSight = _baseAttack.requireLineOfSight;
	passiveApplicators = _baseAttack.passiveApplicators;
	autoTargetSelector = _baseAttack.autoTargetSelector;
	microAI = _baseAttack.microAI;
	node = _baseAttack.node;
	marker = _baseAttack.marker;
	warFogRemoveTime = _baseAttack.warFogRemoveTime;
	warFogRemoveRadius = _baseAttack.warFogRemoveRadius;
	alternativeTargets = _baseAttack.alternativeTargets;
	dispatch = _baseAttack.dispatch;
	applicators = _baseAttack.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpellApplicator::SpellApplicator() :
		spellTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &spellTarget );
	saver.Add( 4, &spell );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpellApplicator* parentPtr = (SpellApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "spellTarget", &spellTarget );
	saver.Add( "spell", &spell );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellApplicator::Assign( const SpellApplicator& _spellApplicator )
{
	targetSelector = _spellApplicator.targetSelector;
	spellTarget = _spellApplicator.spellTarget;
	spell = _spellApplicator.spell;
	enabled = _spellApplicator.enabled;
	applyTarget = _spellApplicator.applyTarget;
	formulaName = _spellApplicator.formulaName;
	LoggingEvent = _spellApplicator.LoggingEvent;
	providerName = _spellApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SpellApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSpell>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpellPeriodicallyApplicator::SpellPeriodicallyApplicator() :
		scaleMode( SCALECALCULATIONMODE_SCALEISCOUNT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellPeriodicallyApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &period );
	saver.Add( 3, &startOffset );
	saver.Add( 4, &scaleMode );
	saver.Add( 5, &targetSelector );
	saver.Add( 6, &spell );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellPeriodicallyApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpellPeriodicallyApplicator* parentPtr = (SpellPeriodicallyApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellPeriodicallyApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "period", &period );
	saver.Add( "startOffset", &startOffset );
	saver.Add( "scaleMode", &scaleMode );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "spell", &spell );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellPeriodicallyApplicator::Assign( const SpellPeriodicallyApplicator& _spellPeriodicallyApplicator )
{
	period = _spellPeriodicallyApplicator.period;
	startOffset = _spellPeriodicallyApplicator.startOffset;
	scaleMode = _spellPeriodicallyApplicator.scaleMode;
	targetSelector = _spellPeriodicallyApplicator.targetSelector;
	spell = _spellPeriodicallyApplicator.spell;
	behaviorFlags = _spellPeriodicallyApplicator.behaviorFlags;
	lifeTime = _spellPeriodicallyApplicator.lifeTime;
	effect = _spellPeriodicallyApplicator.effect;
	startCondition = _spellPeriodicallyApplicator.startCondition;
	enabled = _spellPeriodicallyApplicator.enabled;
	applyTarget = _spellPeriodicallyApplicator.applyTarget;
	formulaName = _spellPeriodicallyApplicator.formulaName;
	LoggingEvent = _spellPeriodicallyApplicator.LoggingEvent;
	providerName = _spellPeriodicallyApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SpellPeriodicallyApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSpellPeriodically>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpellPeriodicallyVisualApplicator::SpellPeriodicallyVisualApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellPeriodicallyVisualApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SpellPeriodicallyApplicator*)this );
	saver.Add( 2, &attackTimeOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellPeriodicallyVisualApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpellPeriodicallyVisualApplicator* parentPtr = (SpellPeriodicallyVisualApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellPeriodicallyVisualApplicator::SerializeSelf( IXmlSaver &saver )
{
	SpellPeriodicallyApplicator::SerializeSelf( saver );
	saver.Add( "attackTimeOffset", &attackTimeOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellPeriodicallyVisualApplicator::Assign( const SpellPeriodicallyVisualApplicator& _spellPeriodicallyVisualApplicator )
{
	attackTimeOffset = _spellPeriodicallyVisualApplicator.attackTimeOffset;
	period = _spellPeriodicallyVisualApplicator.period;
	startOffset = _spellPeriodicallyVisualApplicator.startOffset;
	scaleMode = _spellPeriodicallyVisualApplicator.scaleMode;
	targetSelector = _spellPeriodicallyVisualApplicator.targetSelector;
	spell = _spellPeriodicallyVisualApplicator.spell;
	behaviorFlags = _spellPeriodicallyVisualApplicator.behaviorFlags;
	lifeTime = _spellPeriodicallyVisualApplicator.lifeTime;
	effect = _spellPeriodicallyVisualApplicator.effect;
	startCondition = _spellPeriodicallyVisualApplicator.startCondition;
	enabled = _spellPeriodicallyVisualApplicator.enabled;
	applyTarget = _spellPeriodicallyVisualApplicator.applyTarget;
	formulaName = _spellPeriodicallyVisualApplicator.formulaName;
	LoggingEvent = _spellPeriodicallyVisualApplicator.LoggingEvent;
	providerName = _spellPeriodicallyVisualApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SpellPeriodicallyVisualApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSpellPeriodicallyVisual>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpellProbabilityApplicator::SpellProbabilityApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellProbabilityApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &probability );
	saver.Add( 3, &spell );
	saver.Add( 4, &spellIfFailed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellProbabilityApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpellProbabilityApplicator* parentPtr = (SpellProbabilityApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellProbabilityApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "probability", &probability );
	saver.Add( "spell", &spell );
	saver.Add( "spellIfFailed", &spellIfFailed );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellProbabilityApplicator::Assign( const SpellProbabilityApplicator& _spellProbabilityApplicator )
{
	probability = _spellProbabilityApplicator.probability;
	spell = _spellProbabilityApplicator.spell;
	spellIfFailed = _spellProbabilityApplicator.spellIfFailed;
	enabled = _spellProbabilityApplicator.enabled;
	applyTarget = _spellProbabilityApplicator.applyTarget;
	formulaName = _spellProbabilityApplicator.formulaName;
	LoggingEvent = _spellProbabilityApplicator.LoggingEvent;
	providerName = _spellProbabilityApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SpellProbabilityApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSpellProbability>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpellSwitchApplicator::SpellSwitchApplicator() :
		dontUseDispatches( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellSwitchApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &activeSpellIndex );
	saver.Add( 3, &dontUseDispatches );
	saver.Add( 4, &spells );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpellSwitchApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SpellSwitchApplicator* parentPtr = (SpellSwitchApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellSwitchApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "activeSpellIndex", &activeSpellIndex );
	saver.Add( "dontUseDispatches", &dontUseDispatches );
	saver.Add( "spells", &spells );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpellSwitchApplicator::Assign( const SpellSwitchApplicator& _spellSwitchApplicator )
{
	activeSpellIndex = _spellSwitchApplicator.activeSpellIndex;
	dontUseDispatches = _spellSwitchApplicator.dontUseDispatches;
	spells = _spellSwitchApplicator.spells;
	enabled = _spellSwitchApplicator.enabled;
	applyTarget = _spellSwitchApplicator.applyTarget;
	formulaName = _spellSwitchApplicator.formulaName;
	LoggingEvent = _spellSwitchApplicator.LoggingEvent;
	providerName = _spellSwitchApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SpellSwitchApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSpellSwitch>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatModApplicator::StatModApplicator() :
		dontUpdate( false )
	, constraint( STATCONSTRAINT_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatModApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &modifier );
	saver.Add( 3, &dontUpdate );
	saver.Add( 4, &statModName );
	saver.Add( 5, &constraint );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatModApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatModApplicator* parentPtr = (StatModApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatModApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "modifier", &modifier );
	saver.Add( "dontUpdate", &dontUpdate );
	saver.Add( "statModName", &statModName );
	saver.Add( "constraint", &constraint );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatModApplicator::Assign( const StatModApplicator& _statModApplicator )
{
	modifier.stat = _statModApplicator.modifier.stat;
	modifier.variable = _statModApplicator.modifier.variable;
	modifier.addValue = _statModApplicator.modifier.addValue;
	modifier.multValue = _statModApplicator.modifier.multValue;
	modifier.topModifier = _statModApplicator.modifier.topModifier;
	dontUpdate = _statModApplicator.dontUpdate;
	statModName = _statModApplicator.statModName;
	constraint = _statModApplicator.constraint;
	behaviorFlags = _statModApplicator.behaviorFlags;
	lifeTime = _statModApplicator.lifeTime;
	effect = _statModApplicator.effect;
	startCondition = _statModApplicator.startCondition;
	enabled = _statModApplicator.enabled;
	applyTarget = _statModApplicator.applyTarget;
	formulaName = _statModApplicator.formulaName;
	LoggingEvent = _statModApplicator.LoggingEvent;
	providerName = _statModApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* StatModApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplStatMod>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatusApplicator::StatusApplicator() :
		stackCount( 0 )
	, stackableAcrossUnits( STACKINGRULE_UNSTACKABLE )
	, power( 0 )
	, dispellPriority( DISPELLPRIORITY_MEDIUM )
	, stopBehaviour( STOPBEHAVIOUR_STOPBYTIME )
	, statusPosition( 0 )
	, flags( STATUSFLAGS_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatusApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &name );
	saver.Add( 3, &description );
	saver.Add( 4, &image );
	saver.Add( 5, &stackCount );
	saver.Add( 6, &stackableAcrossUnits );
	saver.Add( 7, &power );
	saver.Add( 8, &dispellPriority );
	saver.Add( 9, &stopBehaviour );
	saver.Add( 10, &applicators );
	saver.Add( 11, &unstackableWith );
	saver.Add( 12, &customCounter );
	saver.Add( 13, &customProgress );
	saver.Add( 14, &statusPosition );
	saver.Add( 15, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatusApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatusApplicator* parentPtr = (StatusApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatusApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "image", &image );
	saver.Add( "stackCount", &stackCount );
	saver.Add( "stackableAcrossUnits", &stackableAcrossUnits );
	saver.Add( "power", &power );
	saver.Add( "dispellPriority", &dispellPriority );
	saver.Add( "stopBehaviour", &stopBehaviour );
	saver.Add( "applicators", &applicators );
	saver.Add( "unstackableWith", &unstackableWith );
	saver.Add( "customCounter", &customCounter );
	saver.Add( "customProgress", &customProgress );
	saver.Add( "statusPosition", &statusPosition );
	saver.Add( "flags", &flags );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatusApplicator::Assign( const StatusApplicator& _statusApplicator )
{
	name = _statusApplicator.name;
	description = _statusApplicator.description;
	image = _statusApplicator.image;
	stackCount = _statusApplicator.stackCount;
	stackableAcrossUnits = _statusApplicator.stackableAcrossUnits;
	power = _statusApplicator.power;
	dispellPriority = _statusApplicator.dispellPriority;
	stopBehaviour = _statusApplicator.stopBehaviour;
	applicators = _statusApplicator.applicators;
	unstackableWith = _statusApplicator.unstackableWith;
	customCounter = _statusApplicator.customCounter;
	customProgress = _statusApplicator.customProgress;
	statusPosition = _statusApplicator.statusPosition;
	flags = _statusApplicator.flags;
	behaviorFlags = _statusApplicator.behaviorFlags;
	lifeTime = _statusApplicator.lifeTime;
	effect = _statusApplicator.effect;
	startCondition = _statusApplicator.startCondition;
	enabled = _statusApplicator.enabled;
	applyTarget = _statusApplicator.applyTarget;
	formulaName = _statusApplicator.formulaName;
	LoggingEvent = _statusApplicator.LoggingEvent;
	providerName = _statusApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* StatusApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplStatus>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonApplicator::SummonApplicator() :
		summonSource( SUMMONSOURCE_BYAPPLICATOR )
	, placeMode( SUMMONPLACEMODE_BYBEHAVIOUR )
	, flags( SUMMONFLAGS_NONE )
	, takeTypeUnit( ESpellTarget( SPELLTARGET_VULNERABLETARGETSONLY | SPELLTARGET_ALL ) )
	, openWarFog( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &summonSource );
	saver.Add( 3, &summonedUnits );
	saver.Add( 4, &summonedUnitIndex );
	saver.Add( 5, &summonedUnitsCount );
	saver.Add( 6, &behaviour );
	saver.Add( 7, &placeSelector );
	saver.Add( 8, &placeMode );
	saver.Add( 9, &lifeTime );
	saver.Add( 10, &applicators );
	saver.Add( 11, &flags );
	saver.Add( 12, &spawnStats );
	saver.Add( 13, &takeModDmg );
	saver.Add( 14, &takeTypeUnit );
	saver.Add( 15, &openWarFog );
	saver.Add( 16, &unsummonSortCriterion );
	saver.Add( 17, &summonGroupName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SummonApplicator* parentPtr = (SummonApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "summonSource", &summonSource );
	saver.Add( "summonedUnits", &summonedUnits );
	saver.Add( "summonedUnitIndex", &summonedUnitIndex );
	saver.Add( "summonedUnitsCount", &summonedUnitsCount );
	saver.Add( "behaviour", &behaviour );
	saver.Add( "placeSelector", &placeSelector );
	saver.Add( "placeMode", &placeMode );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "applicators", &applicators );
	saver.Add( "flags", &flags );
	saver.Add( "spawnStats", &spawnStats );
	saver.Add( "takeModDmg", &takeModDmg );
	saver.Add( "takeTypeUnit", &takeTypeUnit );
	saver.Add( "openWarFog", &openWarFog );
	saver.Add( "unsummonSortCriterion", &unsummonSortCriterion );
	saver.Add( "summonGroupName", &summonGroupName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonApplicator::Assign( const SummonApplicator& _summonApplicator )
{
	summonSource = _summonApplicator.summonSource;
	summonedUnits = _summonApplicator.summonedUnits;
	summonedUnitIndex = _summonApplicator.summonedUnitIndex;
	summonedUnitsCount = _summonApplicator.summonedUnitsCount;
	behaviour = _summonApplicator.behaviour;
	placeSelector = _summonApplicator.placeSelector;
	placeMode = _summonApplicator.placeMode;
	lifeTime = _summonApplicator.lifeTime;
	applicators = _summonApplicator.applicators;
	flags = _summonApplicator.flags;
	spawnStats.life = _summonApplicator.spawnStats.life;
	spawnStats.energy = _summonApplicator.spawnStats.energy;
	takeModDmg = _summonApplicator.takeModDmg;
	takeTypeUnit = _summonApplicator.takeTypeUnit;
	openWarFog = _summonApplicator.openWarFog;
	unsummonSortCriterion = _summonApplicator.unsummonSortCriterion;
	summonGroupName = _summonApplicator.summonGroupName;
	enabled = _summonApplicator.enabled;
	applyTarget = _summonApplicator.applyTarget;
	formulaName = _summonApplicator.formulaName;
	LoggingEvent = _summonApplicator.LoggingEvent;
	providerName = _summonApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* SummonApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplSummon>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonBehaviourBase::SummonBehaviourBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourBase::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SummonBehaviourBase* parentPtr = (SummonBehaviourBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourBase::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourBase::Assign( const SummonBehaviourBase& _summonBehaviourBase )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFSummonBehaviourDataBase* SummonBehaviourBase::Create() const
{
	return ( NWorld::PFSummonBehaviourDataBase* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonBehaviourCommon::SummonBehaviourCommon() :
		summonType( SUMMONTYPE_PRIMARY )
	, responseRange( 0.0f )
	, responseTime( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourCommon::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SummonBehaviourBase*)this );
	saver.Add( 2, &summonType );
	saver.Add( 3, &maxCount );
	saver.Add( 4, &maxThisCount );
	saver.Add( 5, &targetingParams );
	saver.Add( 6, &lashRange );
	saver.Add( 7, &responseRange );
	saver.Add( 8, &responseTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourCommon::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SummonBehaviourCommon* parentPtr = (SummonBehaviourCommon*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourCommon::SerializeSelf( IXmlSaver &saver )
{
	SummonBehaviourBase::SerializeSelf( saver );
	saver.Add( "summonType", &summonType );
	saver.Add( "maxCount", &maxCount );
	saver.Add( "maxThisCount", &maxThisCount );
	saver.Add( "targetingParams", &targetingParams );
	saver.Add( "lashRange", &lashRange );
	saver.Add( "responseRange", &responseRange );
	saver.Add( "responseTime", &responseTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourCommon::Assign( const SummonBehaviourCommon& _summonBehaviourCommon )
{
	summonType = _summonBehaviourCommon.summonType;
	maxCount = _summonBehaviourCommon.maxCount;
	maxThisCount = _summonBehaviourCommon.maxThisCount;
	targetingParams = _summonBehaviourCommon.targetingParams;
	lashRange = _summonBehaviourCommon.lashRange;
	responseRange = _summonBehaviourCommon.responseRange;
	responseTime = _summonBehaviourCommon.responseTime;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFSummonBehaviourDataBase* SummonBehaviourCommon::Create() const
{
	return new NWorld::PFSummonBehaviourDataCommon( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonBehaviourAdvanced::SummonBehaviourAdvanced()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourAdvanced::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SummonBehaviourCommon*)this );
	saver.Add( 2, &guardBehaviourParams );
	saver.Add( 3, &chaseBehaviourParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonBehaviourAdvanced::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SummonBehaviourAdvanced* parentPtr = (SummonBehaviourAdvanced*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourAdvanced::SerializeSelf( IXmlSaver &saver )
{
	SummonBehaviourCommon::SerializeSelf( saver );
	saver.Add( "guardBehaviourParams", &guardBehaviourParams );
	saver.Add( "chaseBehaviourParams", &chaseBehaviourParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonBehaviourAdvanced::Assign( const SummonBehaviourAdvanced& _summonBehaviourAdvanced )
{
	guardBehaviourParams.targetingParams = _summonBehaviourAdvanced.guardBehaviourParams.targetingParams;
	guardBehaviourParams.lashRange = _summonBehaviourAdvanced.guardBehaviourParams.lashRange;
	guardBehaviourParams.responseRange = _summonBehaviourAdvanced.guardBehaviourParams.responseRange;
	guardBehaviourParams.responseTime = _summonBehaviourAdvanced.guardBehaviourParams.responseTime;
	chaseBehaviourParams.targetingParams = _summonBehaviourAdvanced.chaseBehaviourParams.targetingParams;
	chaseBehaviourParams.lashRange = _summonBehaviourAdvanced.chaseBehaviourParams.lashRange;
	chaseBehaviourParams.responseRange = _summonBehaviourAdvanced.chaseBehaviourParams.responseRange;
	chaseBehaviourParams.responseTime = _summonBehaviourAdvanced.chaseBehaviourParams.responseTime;
	summonType = _summonBehaviourAdvanced.summonType;
	maxCount = _summonBehaviourAdvanced.maxCount;
	maxThisCount = _summonBehaviourAdvanced.maxThisCount;
	targetingParams = _summonBehaviourAdvanced.targetingParams;
	lashRange = _summonBehaviourAdvanced.lashRange;
	responseRange = _summonBehaviourAdvanced.responseRange;
	responseTime = _summonBehaviourAdvanced.responseTime;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFSummonBehaviourDataBase* SummonBehaviourAdvanced::Create() const
{
	return new NWorld::PFSummonBehaviourDataAdvanced( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SummonEnumerator::SummonEnumerator() :
		summonTypes( SUMMONTYPEFLAGS_PRIMARY )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonEnumerator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelector*)this );
	saver.Add( 2, &summonTypes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SummonEnumerator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SummonEnumerator* parentPtr = (SummonEnumerator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonEnumerator::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelector::SerializeSelf( saver );
	saver.Add( "summonTypes", &summonTypes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummonEnumerator::Assign( const SummonEnumerator& _summonEnumerator )
{
	summonTypes = _summonEnumerator.summonTypes;
	mode = _summonEnumerator.mode;
	flags = _summonEnumerator.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* SummonEnumerator::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFSummonEnumerator( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TargetCastLimitation::TargetCastLimitation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetCastLimitation::operator&( IBinSaver &saver )
{
	saver.Add( 1, (CastLimitation*)this );
	saver.Add( 2, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetCastLimitation::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TargetCastLimitation* parentPtr = (TargetCastLimitation*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetCastLimitation::SerializeSelf( IXmlSaver &saver )
{
	CastLimitation::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetCastLimitation::Assign( const TargetCastLimitation& _targetCastLimitation )
{
	targetSelector = _targetCastLimitation.targetSelector;
	uiEvent = _targetCastLimitation.uiEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFAbilityData* TargetCastLimitation::Check( NWorld::CastLimitationsCheckParams const &cp ) const
{
	return NWorld::CheckTargetLimitation( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TargetsCounterApplicator::TargetsCounterApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetsCounterApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetsCounterApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TargetsCounterApplicator* parentPtr = (TargetsCounterApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetsCounterApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetsCounterApplicator::Assign( const TargetsCounterApplicator& _targetsCounterApplicator )
{
	targetSelector = _targetsCounterApplicator.targetSelector;
	behaviorFlags = _targetsCounterApplicator.behaviorFlags;
	lifeTime = _targetsCounterApplicator.lifeTime;
	effect = _targetsCounterApplicator.effect;
	startCondition = _targetsCounterApplicator.startCondition;
	enabled = _targetsCounterApplicator.enabled;
	applyTarget = _targetsCounterApplicator.applyTarget;
	formulaName = _targetsCounterApplicator.formulaName;
	LoggingEvent = _targetsCounterApplicator.LoggingEvent;
	providerName = _targetsCounterApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* TargetsCounterApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplTargetsCounter>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttackersTargetSelector::AttackersTargetSelector() :
		type( ATTACKERSTYPE_TARGETERS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackersTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &damageDealTime );
	saver.Add( 4, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackersTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AttackersTargetSelector* parentPtr = (AttackersTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttackersTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "damageDealTime", &damageDealTime );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttackersTargetSelector::Assign( const AttackersTargetSelector& _attackersTargetSelector )
{
	type = _attackersTargetSelector.type;
	damageDealTime = _attackersTargetSelector.damageDealTime;
	targetSelector = _attackersTargetSelector.targetSelector;
	targetFilter = _attackersTargetSelector.targetFilter;
	mode = _attackersTargetSelector.mode;
	flags = _attackersTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* AttackersTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAttackersTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TargetSelectorMicroAI::TargetSelectorMicroAI()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetSelectorMicroAI::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BasicMicroAI*)this );
	saver.Add( 2, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TargetSelectorMicroAI::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TargetSelectorMicroAI* parentPtr = (TargetSelectorMicroAI*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetSelectorMicroAI::SerializeSelf( IXmlSaver &saver )
{
	BasicMicroAI::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetSelectorMicroAI::Assign( const TargetSelectorMicroAI& _targetSelectorMicroAI )
{
	targetSelector = _targetSelectorMicroAI.targetSelector;
	condition = _targetSelectorMicroAI.condition;
	castWhenIdle = _targetSelectorMicroAI.castWhenIdle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFMicroAI* TargetSelectorMicroAI::Create( NWorld::PFMicroAICreateParams const &cp ) const
{
	return NWorld::CreateMicroAI<NWorld::PFTargetSelectorMicroAI>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TauntApplicator::TauntApplicator() :
		tauntTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, strongTarget( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TauntApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &tauntTarget );
	saver.Add( 3, &strongTarget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TauntApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TauntApplicator* parentPtr = (TauntApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TauntApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "tauntTarget", &tauntTarget );
	saver.Add( "strongTarget", &strongTarget );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TauntApplicator::Assign( const TauntApplicator& _tauntApplicator )
{
	tauntTarget = _tauntApplicator.tauntTarget;
	strongTarget = _tauntApplicator.strongTarget;
	behaviorFlags = _tauntApplicator.behaviorFlags;
	lifeTime = _tauntApplicator.lifeTime;
	effect = _tauntApplicator.effect;
	startCondition = _tauntApplicator.startCondition;
	enabled = _tauntApplicator.enabled;
	applyTarget = _tauntApplicator.applyTarget;
	formulaName = _tauntApplicator.formulaName;
	LoggingEvent = _tauntApplicator.LoggingEvent;
	providerName = _tauntApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* TauntApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplTaunt>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeleportApplicator::TeleportApplicator() :
		teleportTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, pushUnits( false )
	, notifyInboundDispatches( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeleportApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &teleportTarget );
	saver.Add( 3, &maxDistance );
	saver.Add( 4, &disappearEffect );
	saver.Add( 5, &appearEffect );
	saver.Add( 6, &pushUnits );
	saver.Add( 7, &notifyInboundDispatches );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeleportApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TeleportApplicator* parentPtr = (TeleportApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeleportApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "teleportTarget", &teleportTarget );
	saver.Add( "maxDistance", &maxDistance );
	saver.Add( "disappearEffect", &disappearEffect );
	saver.Add( "appearEffect", &appearEffect );
	saver.Add( "pushUnits", &pushUnits );
	saver.Add( "notifyInboundDispatches", &notifyInboundDispatches );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeleportApplicator::Assign( const TeleportApplicator& _teleportApplicator )
{
	teleportTarget = _teleportApplicator.teleportTarget;
	maxDistance = _teleportApplicator.maxDistance;
	disappearEffect = _teleportApplicator.disappearEffect;
	appearEffect = _teleportApplicator.appearEffect;
	pushUnits = _teleportApplicator.pushUnits;
	notifyInboundDispatches = _teleportApplicator.notifyInboundDispatches;
	enabled = _teleportApplicator.enabled;
	applyTarget = _teleportApplicator.applyTarget;
	formulaName = _teleportApplicator.formulaName;
	LoggingEvent = _teleportApplicator.LoggingEvent;
	providerName = _teleportApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* TeleportApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplTeleport>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThrowApplicator::ThrowApplicator() :
		flightType( THROWTYPE_THROW )
	, collisionFlags( GHOSTMOVEMODE_IGNOREDYNAMIC )
	, trackTargetUnit( false )
	, maxHeight( 0.0f )
	, maxDistance( 0.0f )
	, takeOffTime( 0.0f )
	, landTime( 0.0f )
	, surfaceSpeedFromAG( true )
	, behaviorFlags( BUFFBEHAVIOR_ZERO )
	, lockRotation( false )
{
	flyEffect.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ThrowApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &flightType );
	saver.Add( 3, &collisionFlags );
	saver.Add( 4, &targetSelector );
	saver.Add( 5, &trackTargetUnit );
	saver.Add( 6, &startSpell );
	saver.Add( 7, &stopSpell );
	saver.Add( 8, &moveSpeed );
	saver.Add( 9, &flipTime );
	saver.Add( 10, &maxHeight );
	saver.Add( 11, &maxDistance );
	saver.Add( 12, &trajectory );
	saver.Add( 13, &angle );
	saver.Add( 14, &takeOffTime );
	saver.Add( 15, &landTime );
	saver.Add( 16, &surfaceSpeedFromAG );
	saver.Add( 17, &flyEffect );
	saver.Add( 18, &behaviorFlags );
	saver.Add( 19, &lockRotation );
	saver.Add( 20, &firstTargetToHit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ThrowApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ThrowApplicator* parentPtr = (ThrowApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ThrowApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "flightType", &flightType );
	saver.Add( "collisionFlags", &collisionFlags );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "trackTargetUnit", &trackTargetUnit );
	saver.Add( "startSpell", &startSpell );
	saver.Add( "stopSpell", &stopSpell );
	saver.Add( "moveSpeed", &moveSpeed );
	saver.Add( "flipTime", &flipTime );
	saver.Add( "maxHeight", &maxHeight );
	saver.Add( "maxDistance", &maxDistance );
	saver.Add( "trajectory", &trajectory );
	saver.Add( "angle", &angle );
	saver.Add( "takeOffTime", &takeOffTime );
	saver.Add( "landTime", &landTime );
	saver.Add( "surfaceSpeedFromAG", &surfaceSpeedFromAG );
	flyEffect.resize( 2 );
	saver.Add( "flyEffect", &flyEffect );
	saver.Add( "behaviorFlags", &behaviorFlags );
	saver.Add( "lockRotation", &lockRotation );
	saver.Add( "firstTargetToHit", &firstTargetToHit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ThrowApplicator::Assign( const ThrowApplicator& _throwApplicator )
{
	flightType = _throwApplicator.flightType;
	collisionFlags = _throwApplicator.collisionFlags;
	targetSelector = _throwApplicator.targetSelector;
	trackTargetUnit = _throwApplicator.trackTargetUnit;
	startSpell = _throwApplicator.startSpell;
	stopSpell = _throwApplicator.stopSpell;
	moveSpeed = _throwApplicator.moveSpeed;
	flipTime = _throwApplicator.flipTime;
	maxHeight = _throwApplicator.maxHeight;
	maxDistance = _throwApplicator.maxDistance;
	trajectory = _throwApplicator.trajectory;
	angle = _throwApplicator.angle;
	takeOffTime = _throwApplicator.takeOffTime;
	landTime = _throwApplicator.landTime;
	surfaceSpeedFromAG = _throwApplicator.surfaceSpeedFromAG;
	flyEffect = _throwApplicator.flyEffect;
	behaviorFlags = _throwApplicator.behaviorFlags;
	lockRotation = _throwApplicator.lockRotation;
	firstTargetToHit = _throwApplicator.firstTargetToHit;
	enabled = _throwApplicator.enabled;
	applyTarget = _throwApplicator.applyTarget;
	formulaName = _throwApplicator.formulaName;
	LoggingEvent = _throwApplicator.LoggingEvent;
	providerName = _throwApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ThrowApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplThrow>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TriggerApplicator::TriggerApplicator() :
		useAbilityCooldown( false )
	, useAbilityOwnerMana( false )
	, playAck( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &actionsCount );
	saver.Add( 3, &processor );
	saver.Add( 4, &useAbilityCooldown );
	saver.Add( 5, &useAbilityOwnerMana );
	saver.Add( 6, &playAck );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TriggerApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TriggerApplicator* parentPtr = (TriggerApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TriggerApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "actionsCount", &actionsCount );
	saver.Add( "processor", &processor );
	saver.Add( "useAbilityCooldown", &useAbilityCooldown );
	saver.Add( "useAbilityOwnerMana", &useAbilityOwnerMana );
	saver.Add( "playAck", &playAck );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TriggerApplicator::Assign( const TriggerApplicator& _triggerApplicator )
{
	actionsCount = _triggerApplicator.actionsCount;
	processor = _triggerApplicator.processor;
	useAbilityCooldown = _triggerApplicator.useAbilityCooldown;
	useAbilityOwnerMana = _triggerApplicator.useAbilityOwnerMana;
	playAck = _triggerApplicator.playAck;
	behaviorFlags = _triggerApplicator.behaviorFlags;
	lifeTime = _triggerApplicator.lifeTime;
	effect = _triggerApplicator.effect;
	startCondition = _triggerApplicator.startCondition;
	enabled = _triggerApplicator.enabled;
	applyTarget = _triggerApplicator.applyTarget;
	formulaName = _triggerApplicator.formulaName;
	LoggingEvent = _triggerApplicator.LoggingEvent;
	providerName = _triggerApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* TriggerApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFTriggerApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIMessageApplicator::UIMessageApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIMessageApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &message );
	saver.Add( 3, &value );
	saver.Add( 4, &uiEvent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIMessageApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIMessageApplicator* parentPtr = (UIMessageApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIMessageApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "message", &message );
	saver.Add( "value", &value );
	saver.Add( "uiEvent", &uiEvent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIMessageApplicator::Assign( const UIMessageApplicator& _uIMessageApplicator )
{
	message = _uIMessageApplicator.message;
	value = _uIMessageApplicator.value;
	uiEvent = _uIMessageApplicator.uiEvent;
	enabled = _uIMessageApplicator.enabled;
	applyTarget = _uIMessageApplicator.applyTarget;
	formulaName = _uIMessageApplicator.formulaName;
	LoggingEvent = _uIMessageApplicator.LoggingEvent;
	providerName = _uIMessageApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* UIMessageApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFUIMessageApplicator>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitConstant::UnitConstant()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitConstant::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &var );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitConstant::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitConstant* parentPtr = (UnitConstant*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitConstant::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "var", &var );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitConstant::Assign( const UnitConstant& _unitConstant )
{
	name = _unitConstant.name;
	var = _unitConstant.var;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitConstantsContainer::UnitConstantsContainer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitConstantsContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &vars );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitConstantsContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitConstantsContainer* parentPtr = (UnitConstantsContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitConstantsContainer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "vars", &vars );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitConstantsContainer::Assign( const UnitConstantsContainer& _unitConstantsContainer )
{
	vars = _unitConstantsContainer.vars;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitEnumerator::UnitEnumerator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitEnumerator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitEnumerator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitEnumerator* parentPtr = (UnitEnumerator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitEnumerator::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitEnumerator::Assign( const UnitEnumerator& _unitEnumerator )
{
	targetFilter = _unitEnumerator.targetFilter;
	mode = _unitEnumerator.mode;
	flags = _unitEnumerator.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* UnitEnumerator::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFUnitEnumerator( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitPlaceCorrector::UnitPlaceCorrector() :
		checkByRangeToRequester( false )
	, nativeTerrainOnly( false )
	, radius( 0.0f )
	, passabilityCheckMode( ETraceMode( 0 ) )
	, checkLineOfSight( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitPlaceCorrector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );
	saver.Add( 3, &checkByRangeToRequester );
	saver.Add( 4, &nativeTerrainOnly );
	saver.Add( 5, &radius );
	saver.Add( 6, &passabilityCheckMode );
	saver.Add( 7, &checkLineOfSight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitPlaceCorrector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitPlaceCorrector* parentPtr = (UnitPlaceCorrector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitPlaceCorrector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
	saver.Add( "checkByRangeToRequester", &checkByRangeToRequester );
	saver.Add( "nativeTerrainOnly", &nativeTerrainOnly );
	saver.Add( "radius", &radius );
	saver.Add( "passabilityCheckMode", &passabilityCheckMode );
	saver.Add( "checkLineOfSight", &checkLineOfSight );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitPlaceCorrector::Assign( const UnitPlaceCorrector& _unitPlaceCorrector )
{
	targetSelector = _unitPlaceCorrector.targetSelector;
	checkByRangeToRequester = _unitPlaceCorrector.checkByRangeToRequester;
	nativeTerrainOnly = _unitPlaceCorrector.nativeTerrainOnly;
	radius = _unitPlaceCorrector.radius;
	passabilityCheckMode = _unitPlaceCorrector.passabilityCheckMode;
	checkLineOfSight = _unitPlaceCorrector.checkLineOfSight;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* UnitPlaceCorrector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFUnitPlaceCorrector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitShiftTarget::UnitShiftTarget()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitShiftTarget::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &distance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitShiftTarget::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitShiftTarget* parentPtr = (UnitShiftTarget*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitShiftTarget::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "distance", &distance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitShiftTarget::Assign( const UnitShiftTarget& _unitShiftTarget )
{
	distance = _unitShiftTarget.distance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* UnitShiftTarget::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFUnitShiftTarget( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ValueApplicator::ValueApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValueApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValueApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ValueApplicator* parentPtr = (ValueApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ValueApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "value", &value );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ValueApplicator::Assign( const ValueApplicator& _valueApplicator )
{
	value = _valueApplicator.value;
	behaviorFlags = _valueApplicator.behaviorFlags;
	lifeTime = _valueApplicator.lifeTime;
	effect = _valueApplicator.effect;
	startCondition = _valueApplicator.startCondition;
	enabled = _valueApplicator.enabled;
	applyTarget = _valueApplicator.applyTarget;
	formulaName = _valueApplicator.formulaName;
	LoggingEvent = _valueApplicator.LoggingEvent;
	providerName = _valueApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* ValueApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplValue>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VariableProxyApplicator::VariableProxyApplicator()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VariableProxyApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &applicators );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VariableProxyApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			VariableProxyApplicator* parentPtr = (VariableProxyApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VariableProxyApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "applicators", &applicators );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VariableProxyApplicator::Assign( const VariableProxyApplicator& _variableProxyApplicator )
{
	applicators = _variableProxyApplicator.applicators;
	enabled = _variableProxyApplicator.enabled;
	applyTarget = _variableProxyApplicator.applyTarget;
	formulaName = _variableProxyApplicator.formulaName;
	LoggingEvent = _variableProxyApplicator.LoggingEvent;
	providerName = _variableProxyApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* VariableProxyApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplVariableProxy>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VictoryApplicator::VictoryApplicator() :
		destroyMainBuilding( false )
	, oppositeFaction( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VictoryApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseApplicator*)this );
	saver.Add( 2, &destroyMainBuilding );
	saver.Add( 3, &oppositeFaction );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VictoryApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			VictoryApplicator* parentPtr = (VictoryApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VictoryApplicator::SerializeSelf( IXmlSaver &saver )
{
	BaseApplicator::SerializeSelf( saver );
	saver.Add( "destroyMainBuilding", &destroyMainBuilding );
	saver.Add( "oppositeFaction", &oppositeFaction );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VictoryApplicator::Assign( const VictoryApplicator& _victoryApplicator )
{
	destroyMainBuilding = _victoryApplicator.destroyMainBuilding;
	oppositeFaction = _victoryApplicator.oppositeFaction;
	enabled = _victoryApplicator.enabled;
	applyTarget = _victoryApplicator.applyTarget;
	formulaName = _victoryApplicator.formulaName;
	LoggingEvent = _victoryApplicator.LoggingEvent;
	providerName = _victoryApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* VictoryApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplVictory>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WaitForSpellApplicator::WaitForSpellApplicator() :
		spellTarget( APPLICATORAPPLYTARGET_APPLICATORTARGET )
	, behaviour( WAITFORSPELLBEHAVIOUR_ZERO )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaitForSpellApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &spellTarget );
	saver.Add( 3, &spell );
	saver.Add( 4, &behaviour );
	saver.Add( 5, &firstTargetToHit );
	saver.Add( 6, &dispatchSource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaitForSpellApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WaitForSpellApplicator* parentPtr = (WaitForSpellApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaitForSpellApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "spellTarget", &spellTarget );
	saver.Add( "spell", &spell );
	saver.Add( "behaviour", &behaviour );
	saver.Add( "firstTargetToHit", &firstTargetToHit );
	saver.Add( "dispatchSource", &dispatchSource );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaitForSpellApplicator::Assign( const WaitForSpellApplicator& _waitForSpellApplicator )
{
	spellTarget = _waitForSpellApplicator.spellTarget;
	spell = _waitForSpellApplicator.spell;
	behaviour = _waitForSpellApplicator.behaviour;
	firstTargetToHit = _waitForSpellApplicator.firstTargetToHit;
	dispatchSource = _waitForSpellApplicator.dispatchSource;
	behaviorFlags = _waitForSpellApplicator.behaviorFlags;
	lifeTime = _waitForSpellApplicator.lifeTime;
	effect = _waitForSpellApplicator.effect;
	startCondition = _waitForSpellApplicator.startCondition;
	enabled = _waitForSpellApplicator.enabled;
	applyTarget = _waitForSpellApplicator.applyTarget;
	formulaName = _waitForSpellApplicator.formulaName;
	LoggingEvent = _waitForSpellApplicator.LoggingEvent;
	providerName = _waitForSpellApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* WaitForSpellApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplWaitForSpell>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WallTargetSelector::WallTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WallTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MultipleTargetSelectorFiltered*)this );
	saver.Add( 2, &origin );
	saver.Add( 3, &direction );
	saver.Add( 4, &length );
	saver.Add( 5, &width );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WallTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WallTargetSelector* parentPtr = (WallTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WallTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	MultipleTargetSelectorFiltered::SerializeSelf( saver );
	saver.Add( "origin", &origin );
	saver.Add( "direction", &direction );
	saver.Add( "length", &length );
	saver.Add( "width", &width );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WallTargetSelector::Assign( const WallTargetSelector& _wallTargetSelector )
{
	origin = _wallTargetSelector.origin;
	direction = _wallTargetSelector.direction;
	length = _wallTargetSelector.length;
	width = _wallTargetSelector.width;
	targetFilter = _wallTargetSelector.targetFilter;
	mode = _wallTargetSelector.mode;
	flags = _wallTargetSelector.flags;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* WallTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFWallTargetSelector( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WatchApplicator::WatchApplicator() :
		onSenderDispatchApply( PARENTNOTIFICATION_NA )
	, onSenderDispatchEvade( PARENTNOTIFICATION_NA )
	, onUnitDeath( PARENTNOTIFICATION_NA )
	, onFinish( PARENTNOTIFICATION_NA )
	, onSenderDispatchMiss( PARENTNOTIFICATION_NA )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WatchApplicator::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BuffApplicator*)this );
	saver.Add( 2, &onSenderDispatchApply );
	saver.Add( 3, &onSenderDispatchEvade );
	saver.Add( 4, &onUnitDeath );
	saver.Add( 5, &onFinish );
	saver.Add( 6, &onSenderDispatchMiss );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WatchApplicator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WatchApplicator* parentPtr = (WatchApplicator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WatchApplicator::SerializeSelf( IXmlSaver &saver )
{
	BuffApplicator::SerializeSelf( saver );
	saver.Add( "onSenderDispatchApply", &onSenderDispatchApply );
	saver.Add( "onSenderDispatchEvade", &onSenderDispatchEvade );
	saver.Add( "onUnitDeath", &onUnitDeath );
	saver.Add( "onFinish", &onFinish );
	saver.Add( "onSenderDispatchMiss", &onSenderDispatchMiss );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WatchApplicator::Assign( const WatchApplicator& _watchApplicator )
{
	onSenderDispatchApply = _watchApplicator.onSenderDispatchApply;
	onSenderDispatchEvade = _watchApplicator.onSenderDispatchEvade;
	onUnitDeath = _watchApplicator.onUnitDeath;
	onFinish = _watchApplicator.onFinish;
	onSenderDispatchMiss = _watchApplicator.onSenderDispatchMiss;
	behaviorFlags = _watchApplicator.behaviorFlags;
	lifeTime = _watchApplicator.lifeTime;
	effect = _watchApplicator.effect;
	startCondition = _watchApplicator.startCondition;
	enabled = _watchApplicator.enabled;
	applyTarget = _watchApplicator.applyTarget;
	formulaName = _watchApplicator.formulaName;
	LoggingEvent = _watchApplicator.LoggingEvent;
	providerName = _watchApplicator.providerName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFBaseApplicator* WatchApplicator::Create( NWorld::PFApplCreatePars const &cp ) const
{
	return NWorld::CreateApplicator<NWorld::PFApplWatch>( *this, cp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WeightTargetSelector::WeightTargetSelector()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WeightTargetSelector::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SingleTargetSelector*)this );
	saver.Add( 2, &targetSelector );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WeightTargetSelector::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WeightTargetSelector* parentPtr = (WeightTargetSelector*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeightTargetSelector::SerializeSelf( IXmlSaver &saver )
{
	SingleTargetSelector::SerializeSelf( saver );
	saver.Add( "targetSelector", &targetSelector );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeightTargetSelector::Assign( const WeightTargetSelector& _weightTargetSelector )
{
	targetSelector = _weightTargetSelector.targetSelector;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFTargetSelector* WeightTargetSelector::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFWeightTargetSelector( *this, world );
}
}; // namespace NDb
