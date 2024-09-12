#include "stdafx.h"

#include "PFCreep.h"
#include "PFAbilityData.h"
#include "PFAIWorld.h"
#include "../System/InlineProfiler.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFBaseCreep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseCreep::PFBaseCreep( PFWorld* pWorld, const NDb::Creature& creepObj, NDb::EFaction faction, 
                         NDb::EUnitType unitType, int playerId, const Placement& position, 
                         float interval /* = 0.0f */, int increment /* = 0*/, 
                         bool bStartIdleAnimation /* = false*/,
                         const NDb::MapForceStatModifierApplication mapForceStatModifierApplication /* = NDb::MAPFORCESTATMODIFIERAPPLICATION_ALL*/)
  : PFCreature(pWorld, position.pos, position.Get2DDirection(), creepObj)
  , timeBeforeActivate(-1)
  , levelUpInfo( interval, increment )
  , levelUpTimer( interval )
  , warfogFaction( faction )
{
  NI_PROFILE_FUNCTION

  {
    NI_PROFILE_BLOCK( "CreateClientObject" );
    NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];
    CreateClientObject<NGameX::PFCreep>( NGameX::PFCreep::CreatePars( creepObj.sceneObject, pAnimSet, pWorld->GetScene(), SUMMONNODE, bStartIdleAnimation ) );
    CALL_CLIENT_1ARGS( SetRotation, position.rot );
  }

	// Initialize base unit
  PFBaseUnit::InitData data;
  data.faction      = faction;
  data.type         = unitType;
  data.playerId     = playerId;
  data.pObjectDesc  = &creepObj;
  Initialize(data);
  InitBaseAttack();

  // Only creeps should modify their stats by force
  ModifyStatsByForce(mapForceStatModifierApplication);

  DoLevelups(1);
    
  // Upgrade creeps abilities
  {
    NI_PROFILE_BLOCK( "Abilities" );
    UpgradeAbilities();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Special constructor for PFBaseSummonedUnit
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseCreep::PFBaseCreep( PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Creature &unitDesc )
: PFCreature(pWorld, pos, direction, unitDesc)
, timeBeforeActivate(-1)
, levelUpInfo( 0, 0 )
, levelUpTimer( 0 )
, warfogFaction( NDb::FACTION_NEUTRAL)
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::Initialize(InitData const& data)
{
  warfogFaction = data.faction;
  PFCreature::Initialize( data );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::Reset()
{
	PFCreature::Reset();

  if ( !IsDead() )
  {
    NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];
    CreateClientObject<NGameX::PFCreep>( NGameX::PFCreep::CreatePars( dbUnitDesc->sceneObject, pAnimSet, GetWorld()->GetScene(), SUMMONNODE ) );
  }
}

void PFBaseCreep::InitializeSummonBehavior()
{
  NI_PROFILE_FUNCTION

  if (IsValid(ClientObject()))
  {
    CALL_CLIENT(Summon); 

    timeBeforeActivate = ClientObject()->GetStateDuration(NDb::ANIMSTATES_SUMMON);
  }

  if (timeBeforeActivate > EPS_VALUE)
    AddFlag(NDb::UNITFLAG_FORBIDMOVE | NDb::UNITFLAG_FORBIDATTACK | NDb::UNITFLAG_FORBIDAUTOTARGETME | 
      NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseCreep::CanLevelUpNow() const
{
  return !IsInCombat();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::MakeLevelupsForTimeDelta( float dtInSeconds )
{
  if ( ShouldGainLevels() )
  {
    float timeAfterStep = dtInSeconds + levelUpInfo.timeLevelUpInterval - levelUpTimer;
    int fullIntervals = (int)floor( timeAfterStep / levelUpInfo.timeLevelUpInterval );
    float toNextLevelup = timeAfterStep - fullIntervals * levelUpInfo.timeLevelUpInterval;
    levelUpTimer = levelUpInfo.timeLevelUpInterval - toNextLevelup;
    DoLevelups( levelUpInfo.timeLevelUpIncrement * fullIntervals );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::ChangeFaction( NDb::EFaction newFaction )
{
  SetWarfogFaction( newFaction );
  PFCreature::ChangeFaction( newFaction );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::SetWarfogFaction( NDb::EFaction _faction )
{
  if ( warfogFaction == _faction )
    return;
  warfogFaction = _faction;
  // Reopen War Fog for a new faction
  CloseWarFog(true);
  OpenWarFog();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseCreep::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
  
  if ( ( timeBeforeActivate > EPS_VALUE ) && ( ( timeBeforeActivate -= dtInSeconds ) <= EPS_VALUE ) )
  {
    RemoveFlag( NDb::UNITFLAG_FORBIDMOVE | NDb::UNITFLAG_FORBIDATTACK | NDb::UNITFLAG_FORBIDAUTOTARGETME | 
      NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4 );
  }

  if ( ShouldGainLevels() && !GetWorld()->GetAIWorld()->IsCreepLevelupPaused() )
  {
    levelUpTimer -= dtInSeconds;
    if ( ( levelUpTimer <= 0.0f ) && CanLevelUpNow() )
    {
      DoLevelups( levelUpInfo.timeLevelUpIncrement );
      levelUpTimer = levelUpInfo.timeLevelUpInterval;
    }
  }

  return PFCreature::Step(dtInSeconds);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::RemoveCorpse()
{
  PFCreature::RemoveCorpse();
  Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseCreep::OnDestroyContents()
{
  PFFsm::Cleanup();
  PFCreature::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseCreep::GetManaCostModifier( bool altCost /*= false*/ ) const
{
  return stats->GetIncrementForceModifier();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EUnitType PFBaseCreep::GetUnitTypeByCreepType( NDb::ECreepType creepType )
{
  switch ( creepType )
  {
    case NDb::CREEPTYPE_FACTIONALNORMAL:
      return NDb::UNITTYPE_CREEP;

    case NDb::CREEPTYPE_FACTIONALSIEGE:
      return NDb::UNITTYPE_SIEGECREEP;

    case NDb::CREEPTYPE_FACTIONALCHAMPION:
      return NDb::UNITTYPE_FACTIONCHAMPION;

    case NDb::CREEPTYPE_NEUTRALMINION:
      return NDb::UNITTYPE_NEUTRALCREEP;

    case NDb::CREEPTYPE_NEUTRALNORMAL:
      return NDb::UNITTYPE_NEUTRALCREEP;

    case NDb::CREEPTYPE_NEUTRALCHAMPION:
      return NDb::UNITTYPE_NEUTRALCHAMPION;

    case NDb::CREEPTYPE_NEUTRALBOSS:
      return NDb::UNITTYPE_NEUTRALBOSS;

    default:
      NI_ALWAYS_ASSERT("Unknown CreepType!");
      return NDb::UNITTYPE_CREEP;
  }
}

} // namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBaseCreep, NWorld)

