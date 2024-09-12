#include "stdafx.h"

#include "PFSummoned.h"
#include "PFSummonState.h"
#include "PFAIWorld.h"

#include "PFMaleHero.h"
#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#include "PFClientSummoned.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

#include "PFClientApplicators.h"
#include "DBAbility.h"

#include "PFApplSummon.h"
#include "../System/PlaneGeometry.h"
#include "../System/InlineProfiler.h"

#include "PFBaseUnitStates.h"

namespace 
{
  static bool g_debugSummonStates = false;
}

REGISTER_DEV_VAR("debug_summon_states", g_debugSummonStates, STORAGE_NONE);


namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFSummonedUnitBehaviour* PFSummonedUnitBehaviour::Create(PFBaseMovingUnit *pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourData, float lifeTime, int behaviourFlags)
{
  return new PFSummonedUnitBehaviour(pUnit, pMaster, pBehaviourData, lifeTime, behaviourFlags);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFSummonedUnitBehaviour::PFSummonedUnitBehaviour( PFBaseMovingUnit* pUnit, const CPtr<PFBaseUnit>& pMaster, const NDb::SummonBehaviourBase* pBehaviourData, float lifeTime, int behaviourFlags )
  : PFSummonBehaviour( pUnit, pMaster, pBehaviourData, lifeTime, behaviourFlags ) 
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitBehaviour::UpdateClientColor()
{
  NI_ASSERT(pUnit, "Behavior unit is empty!");
  pUnit->UpdateClientColor();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFSummonedUnitAIBehaviour* PFSummonedUnitAIBehaviour::Create(PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster,
                const NDb::SummonBehaviourBase* pBehaviourBase, NDb::SummonType summonType, float lifeTime, int behaviourFlags)
{
  return new PFSummonedUnitAIBehaviour(pUnit, pMaster, pBehaviourBase, summonType, lifeTime, behaviourFlags);
}

PFSummonedUnitAIBehaviour::PFSummonedUnitAIBehaviour(PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster,
                const NDb::SummonBehaviourBase* pBehaviourBase, NDb::SummonType summonType, float lifeTime, int behaviourFlags)
  : PFSummonedUnitBehaviour( pUnit, pMaster, pBehaviourBase, lifeTime, behaviourFlags )
  , summonType(summonType)
  , isSuspended(false)
{
  // Note that master loses alpha summon only on a death of the latter
  if ( (behaviourFlags & BEHAVIOURFLAGS_ALPHASUMMON) != 0 )
    pMaster->SetAlphaSummon( pUnit );

  pMaster->AddEventListener(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 PFSummonedUnitAIBehaviour::GetMasterOffset() const
{
  CVec2 result( 0.0f, 0.0f );

  if ( PFBaseMovingUnit* pMoving = dynamic_cast<PFBaseMovingUnit*>( pMaster.GetPtr() ) )
  {
    result = pMoving->GetMoveDirection();
    Normalize( &result );

    int   count;
    float distance;
    float angle;
    if ( summonType == NDb::SUMMONTYPE_PRIMARY )
    {
      count    = pMaster->GetSummonedGroup( NDb::SUMMONTYPE_PRIMARY )->GetMaxSize();
      distance = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.primarySummonEscortDistance;
      angle    = count > 2 ? - FP_PI / count : -FP_PI4;
    }
    else if ( summonType == NDb::SUMMONTYPE_PET)
    {
      count    = pMaster->GetSummonedGroup( NDb::SUMMONTYPE_PET )->GetMaxSize();
      distance = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.petEscortDistance;
      angle    = count > 2 ? - FP_PI / count : -FP_PI4;
    }
    else
    {
      NI_ASSERT( summonType == NDb::SUMMONTYPE_SECONDARY, "Wrong summon type" );

      count    = pMaster->GetSummonedGroup( NDb::SUMMONTYPE_SECONDARY )->GetMaxSize();
      distance = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.secondarySummonEscortDistance;
      angle    = -3.0f * FP_PI4;
    }

    NI_ASSERT( count >= 1, "This function should not be called when count == 0" );
    if ( count > 2 )
      angle += FP_2PI * float( GetIndex() ) / float( count );
    else if ( GetIndex() == 1 )
      angle = -angle;

    RotatePoint( &result, angle );

    result *= distance; // magic summon unit offset
  }

  return result;
}
//////////////////////////////////////////////////////////////////////////
unsigned int PFSummonedUnitAIBehaviour::OnEvent( const PFBaseUnitEvent *pEvent )
{
  NDb::EBaseUnitEvent eventType = pEvent->GetType();

  if ( !IsValid(pUnit) )
    return 0;

  if ( NDb::BASEUNITEVENT_WANTMOVETO == eventType )
  {
    if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPLAYERCONTROL) )
      return 0;

    if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE) )
      return 0; // Move forbid flag not empty!
    
    if ( !IsValid(pMaster) || pMaster->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE) )
      return 0;

    PFHeroEventWantMoveTo const* pWantMoveEvent = dynamic_cast<PFHeroEventWantMoveTo const*>( pEvent );
    if ( pWantMoveEvent )
    {
      CVec2 masterDestination = pWantMoveEvent->GetDestination();
      if (masterDestination == VNULL2)
      {
        pUnit->DropStates();
        pUnit->Stop();
        pUnit->PushState( new PFSummonAIBaseState(pUnit) );
      }
      else
      {
        const float& range = GetResponseRange();
        if ( range > 0.0f && !pUnit->IsPositionInRange(masterDestination, range) )
        {
          //CVec2 targetPosition = masterDestination + GetMasterOffset();
          PFSummonAIBaseState* pState = 0;
          if ( !pUnit->GetCurrentState() || pUnit->GetCurrentState()->GetTypeId() != PFSummonAIBaseState::typeId )
          {
            pUnit->DropStates();
            pState = new PFSummonAIBaseState(pUnit);
            pUnit->PushState( pState );
          }
          else 
          {
            NI_VERIFY(  pState = dynamic_cast<PFSummonAIBaseState*>(pUnit->GetCurrentState()), "Wrong summon AI state", return 0; )
          }

          pState->SetIgnoreTimer(GetResponseTime());
          //     pState->SetWantedDestination(targetPosition);
        }
      }
    }
  }
  else if ( NDb::BASEUNITEVENT_ASSIGNTARGET == eventType )
  {
    if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPLAYERCONTROL) )
      return 0;

    PFBaseUnitAssignTargetEvent const* pAssignTargetEvent = dynamic_cast<PFBaseUnitAssignTargetEvent const*>( pEvent );
    if ( !pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDSELECTTARGET ) )
    {
      OnTarget(pAssignTargetEvent->pTarget, pAssignTargetEvent->strongTarget);
    }
  }


  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFSummonedUnitAIBehaviour::OnStep(float dtInSeconds)
{
	CPtr<PFBaseMovingUnit> pUnit = GetUnit();
  CPtr<PFCreature> pCreature = dynamic_cast<PFCreature*>(pUnit.GetPtr());
  if (IsValid(pCreature) && pCreature->IsMicroAiEnabled())
  {
    if ( pCreature->HaveAbilityInProgress() )
      return true; // Do nothing during channeling
    if ( pCreature->UseAbilityWithMicroAI() )
      return true; // We cast ability on this step
  }

  const NDb::SummonBehaviourBase*   pSummonBehaviourBase   = GetDB();
  const NDb::SummonBehaviourCommon* pSummonBehaviourCommon = dynamic_cast<const NDb::SummonBehaviourCommon*>( pSummonBehaviourBase );

  if(pSummonBehaviourCommon)
  {
    SetLashRange( pSummonBehaviourCommon->lashRange(pMaster, pUnit, NULL, 15.f ) );
  }

  // Enqueue base summon IA state on idle
  if ( IsValid(pUnit) && !pUnit->GetCurrentState() )
    pUnit->EnqueueState( new PFSummonAIBaseState(pUnit), true );

  if (g_debugSummonStates && pUnit->GetCurrentState())
  {
    //WorldObjectBase* wo = dynamic_cast<WorldObjectBase*>(pUnit->GetCurrentState());
    CVec3 pos = pUnit->GetPosition();
    pos.z += 6.0f;
    Render::Color white( 255, 255, 255, 255 );
    Render::DebugRenderer::DrawText3D( pUnit->GetCurrentState()->GetObjectTypeName(), pos, 20, white);
  }


  return PFSummonedUnitBehaviour::OnStep(dtInSeconds);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
  NI_VERIFY( IsUnitValid(pTarget) && pTarget->IsVulnerable(), "Invalid Target!", return; );
  CPtr<PFBaseMovingUnit> pUnit = GetUnit();

  if ( !IsValid( pUnit ) )
    return;

	if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
		return; // Attack forbid flag not empty!

	pUnit->DropStates();
	pUnit->PushState( new PFSummonAIAttackState(pUnit, pTarget, bStrongTarget) );
}

bool PFSummonedUnitAIBehaviour::CanSelectTarget( const PFBaseUnit* pTarget, bool mustSeeTarget /*= false*/ ) const
{
  if ( pUnit->GetCurrentState() && pUnit->GetCurrentState()->GetTypeId() == PFSummonAIBaseState::typeId )
  {
    PFSummonAIBaseState* state = dynamic_cast<PFSummonAIBaseState*>(pUnit->GetCurrentState());
    NI_ASSERT( state != NULL, "Summon state is wrong");
    if ( !state->CanSelectTarget(pTarget) )
      return false;
  }

  if(pUnit->IsInTaunt())
    return true;

  float lashRange = Min( GetLashRange(), pUnit->GetChaseRange() );

  return IsValid( pMaster )
    && ( lashRange < EPS_VALUE || pMaster->IsTargetInRange( pTarget, lashRange + pUnit->GetAttackRange() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::OnStop()
{
	if ( IsValid( pMaster ) )
  {
    if ( !isSuspended )
    {
      pMaster->GetSummonedGroup(GetSummonType())->RemoveBehavior(this);

      if ( behaviourFlags & BEHAVIOURFLAGS_ALPHASUMMON )
      {
        pMaster->SetAlphaSummon( NULL );
      }
    }
    pMaster = NULL;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::Suspend()
{
  if ( IsValid( pMaster ) )
  {
    pMaster->GetSummonedGroup(GetSummonType())->RemoveBehavior(this);
    isSuspended = true;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::Resume()
{
  if ( IsValid( pMaster ) )
  {
    pMaster->GetSummonedGroup(GetSummonType())->AddBehavior(this);
    isSuspended = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::AcquireBehaviourDefinedSpawnPosition(Target& spawnPosition) const
{
  NI_VERIFY( IsValid(pMaster), "Uninitialized summoned unit used!", return; );

  CVec3 correctedPos( 0, 0, 0 );
  float range = 0;
  if ( summonType == NDb::SUMMONTYPE_PRIMARY )
    range = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.primarySummonEscortDistance;
  else if ( summonType == NDb::SUMMONTYPE_SECONDARY )
    range = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.secondarySummonEscortDistance;
  else if ( summonType == NDb::SUMMONTYPE_PET )
    range = GetWorld()->GetAIWorld()->GetAIParameters().commonSummonParameters.petEscortDistance;

  pUnit->FindFreePlace2( GetEscortPosition(), pMaster->GetPosition().AsVec2D(), range, correctedPos.AsVec2D(), true );
  spawnPosition.SetPosition( correctedPos );
}

//////////////////////////////////////////////////////////////////////////
void PFSummonedUnitAIBehaviour::OnDamage( PFBaseUnitDamageDesc const & desc )
{
  if( IsUnitValid( pUnit->GetCurrentTarget() ) )
    return;

  if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
    return; // Attack forbid flag not empty!

  CPtr<PFBaseUnit> pSender = IsValid(desc.pSender) ? ( desc.pSender->IsMounted() ? desc.pSender->GetMountedOn() : desc.pSender ) : NULL;

  if ( IsTargetValid(pSender) && pSender->IsVisibleForFaction(pUnit->GetFaction()) && !desc.dontAttackBack && pSender->GetFaction() != GetFaction() )
  {
    if ( !CanSelectTarget(pSender) )
      return;

    pUnit->DropStates();
    pUnit->PushState( new PFSummonAIAttackState(pUnit, pSender, false) );
    pUnit->DoScream( pSender, ScreamTarget::ScreamAlert );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseSummonedUnit::PFBaseSummonedUnit( CPtr<PFWorld> const& pWorld, NDb::Creature const* creepObj, NDb::EUnitType unitType, CPtr<PFBaseUnit> const& pMaster, Placement const& placement, bool noSummonAnimation /* = false*/, bool _attachGlowEffect /* = false*/, bool _openWarFog /*  = true*/)
: PFBaseCreep(pWorld, placement.pos, placement.Get2DDirection(), *creepObj)
, takeModDmg( 1.f )
, takeTypeUnit( NDb::ESpellTarget( 0 ) )
, attachGlowEffect(_attachGlowEffect)
, openWarFog( _openWarFog )
{
  NI_PROFILE_FUNCTION

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pMaster.GetPtr() );

  SetMaster(pMaster);

  if ( pHero )
    SetSkin(pHero->GetSkinId());

  NI_DATA_VERIFY(GetDeathParams(), "Death parameters are not setted", return)

  MakeClientObject(pHero, creepObj, noSummonAnimation);
  CALL_CLIENT_1ARGS( SetRotation, placement.rot );

  PFBaseUnit::InitData data;
  data.faction      = pMaster->GetFaction();
  data.type         = unitType;
  data.playerId     = pMaster->GetPlayerId();
  data.pObjectDesc  = creepObj;
  Initialize(data);
  InitBaseAttack();

  if ( !openWarFog )
    PFBaseCreep::CloseWarFog(true);

  if ( !noSummonAnimation )
    InitializeSummonBehavior();

  // Copy stat modifiers with PF_Core::WORLD_ID provider from the master, just in case the "global_stat_scale" cheat was used
  CopyStatModifiersFrom(pMaster, PF_Core::WORLD_ID);

  DoLevelups(1);
  SetNaftaLevel( pMaster->GetNaftaLevel() );

  // Upgrade summon abilities
  {
    NI_PROFILE_BLOCK( "Abilities" );
    UpgradeAbilities();
  }

  const NDb::CreepSkin* pSkin = GetCreepSkin();
  if (pSkin && pHero)
  {

#ifndef _SHIPPING
    {
      // прочекаем, классовый ли это саммон или нет, т.к. у не классовых не должно быть скинов
      const NDb::Hero* pDbHero = dynamic_cast<const NDb::Hero*>(pHero->GetDbHero());

      //Do not check summons skins in custom game because there one faction for both sides. 
      if(!pWorld->GetIAdventureScreen()->IsCustomSessionType())
      {
        const NDb::Summoned* pDbSummoned = dynamic_cast<const NDb::Summoned*>(DbUnitDesc()); 

        bool bFound = false;
        typedef vector<NDb::SummonedUnits> TSummonContainer;
        TSummonContainer::const_iterator summonIter = pDbHero->summonedUnits.begin();
        for( ; summonIter != pDbHero->summonedUnits.end(); ++summonIter )
        {
          const NDb::Summoned* otherSideUnit = (pHero->GetFaction() == NDb::FACTION_FREEZE) ? summonIter->unitB : summonIter->unitA;
          const NDb::Summoned* ourSideUnit = (pHero->GetFaction() == NDb::FACTION_FREEZE) ? summonIter->unitA : summonIter->unitB;

          if (!ourSideUnit && otherSideUnit)
            ourSideUnit = otherSideUnit;
          // для каждого саммона нашей фракции надо добавить в список исключаемых из прелоада ресурсов те скины, которые не будут использоваться
          if (ourSideUnit == pDbSummoned)
          {
            bFound = true;
            break;
          }
        }

        NI_DATA_ASSERT(bFound, NStr::StrFmt("Summon %s must be added to a hero's (%s) \'summonedUnit\' list!", 
          pDbSummoned->GetDBID().GetFormatted(), pDbHero->persistentId));
      }
    }
#endif

    description       = pSkin->description.GetText();
    pImage            = pSkin->image;
  }

  if ( attachGlowEffect )
    CALL_CLIENT( AttachGlowEffect );
}
//////////////////////////////////////////////////////////////////////////

void PFBaseSummonedUnit::MakeClientObject(PFBaseMaleHero* pHero, NDb::Creature const* dbSummonedObj, bool noSummonAnimation /*= true*/)
{
  {
    NI_PROFILE_BLOCK( "CreateClientObject" );
    NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];

    NDb::Summoned const* pDBSummoned = dynamic_cast<NDb::Summoned const*>(dbSummonedObj);
    if ( pHero && pDBSummoned )
    {
      CreateClientObject<NGameX::PFClientSummoned>(    
        NGameX::PFClientSummoned::CreatePars( *pDBSummoned, pAnimSet.GetPtr(), 
        pHero->GetWorld()->GetScene(), pHero->GetFaction(), SUMMONNODE, 
        noSummonAnimation, pHero->GetSkinId()) );
    }
    else
    {
      CreateClientObject<NGameX::PFCreep>( NGameX::PFCreep::CreatePars( dbSummonedObj->sceneObject, pAnimSet, GetWorld()->GetScene(), SUMMONNODE, noSummonAnimation ) );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseSummonedUnit::OnBeforeDamage(const DamageDesc &desc)
{
  if ( UnitMaskingPredicate( this, takeTypeUnit )( *desc.pSender ) )
    return ( desc.amount * takeModDmg );

  return PFBaseUnit::OnBeforeDamage( desc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseSummonedUnit::OnDamage(const DamageDesc &desc)
{
  if ( UnitMaskingPredicate( this, takeTypeUnit )( *desc.pSender ) )
  {
    DamageDesc descNew;
    descNew = desc;
    descNew.amount *= takeModDmg;
    
    return PFBaseUnit::OnDamage( descNew );
  }

  return PFBaseUnit::OnDamage( desc );
}

void PFBaseSummonedUnit::Reset()
{
  // перескочим через одного предка PFBaseCreep::Reset() т.к. там создается клиентский объект с неправильными (не саммоновскими) параметрами
  PFCreature::Reset();

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pMaster.GetPtr() );
  if ( pHero )
    SetSkin(pHero->GetSkinId());

  const NDb::Creature* pDbSummoned = dynamic_cast<const NDb::Creature*>(DbUnitDesc());
  NI_ASSERT(pDbSummoned, "Wrong type of summoned creature!");
  if ( !IsDead() )
    MakeClientObject(pHero, pDbSummoned);

  const NDb::CreepSkin* pSkin = GetCreepSkin();

  // восстанавливаем оверрайд имени и иконки от скина
  if ( pHero && pSkin )
  {
    description       = pSkin->description.GetText();
    pImage            = pSkin->image;
  }
}

void PFBaseSummonedUnit::OnAfterReset()
{
  PFBaseCreep::OnAfterReset();

  if ( attachGlowEffect )
    CALL_CLIENT( AttachGlowEffect );


}

bool PFBaseSummonedUnit::SetSkin( const nstl::string& skinId )
{
  NDb::Ptr<NDb::CreepSkin> prevSkin = GetCreepSkin();
  const NDb::Summoned* pDbSummoned = dynamic_cast<const NDb::Summoned*>(DbUnitDesc());

  if ( !pDbSummoned )
    return false;

  // найдем нужный скин, если юзер выбрал его для игры
  if (!skinId.empty() && skinId != "default")
  {
    vector<NDb::Ptr<NDb::CreepSkin>>::const_iterator it = pDbSummoned->creepSkins.begin();
    for ( ; it != pDbSummoned->creepSkins.end(); ++it )
    {
      if ((*it)->heroPersistentId == skinId)
      {
        pCurrentSkin = *it;
        break;
      }
    }
  }
  else
  {
    pCurrentSkin = 0;
  }

  if (prevSkin == pCurrentSkin)
    return false;

  return true;
}

const NDb::UnitDeathParameters* PFBaseSummonedUnit::GetDeathParams() const
{
  const NDb::CreepSkin* currentSkin = GetCreepSkin();

  if (currentSkin && IsValid(currentSkin->deathParameters))
    return currentSkin->deathParameters;

  return PFBaseCreep::GetDeathParams();
}

void PFSummonedUnitBehaviour::GetKillerAward(CPtr<PFBaseUnit> pKiller, NaftaAward& award)
{
  award.toKiller += pUnit->GetGold();
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBaseSummonedUnit, NWorld)
REGISTER_WORLD_OBJECT_NM( PFSummonedUnitBehaviour, NWorld )
REGISTER_WORLD_OBJECT_NM( PFSummonedUnitAIBehaviour, NWorld )
