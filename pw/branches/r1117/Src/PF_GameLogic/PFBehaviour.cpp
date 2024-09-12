#include "stdafx.h"

#include "PFBaseUnit.h"
#include "PFBaseMovingUnit.h"
#include "PFBehaviour.h"
#include "PFAIWorld.h"
#include "PFBaseUnitStates.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonBehaviour::UnsummonFunc::operator() (PFSummonBehaviour *pBehaviour)
{
  if ( pBehaviour->GetUnit()->GetMasterUnit() == master )
    pBehaviour->Unsummon();
  else
    pBehaviour->OnStop();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseBehaviour::PFBaseBehaviour(PFBaseMovingUnit *_pUnit)
 : PFWorldObjectBase( _pUnit->GetWorld(), 0 ), pUnit(_pUnit), faction(_pUnit->GetFaction()),
 unitType(_pUnit->GetUnitType()), isEnabled(true)
{
}

void PFBaseBehaviour::Enable()
{
  isEnabled = true;
}

void PFBaseBehaviour::Disable()
{
  isEnabled = false;

  pUnit->DropStates();
  pUnit->DropTarget();
  pUnit->ClearScreamTargets();
  pUnit->RemoveLastAttackData();
  pUnit->RemoveLastHeroAttackData();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseBehaviour::OnStep(float dtInSeconds)
{
	return true;
}

void PFBaseBehaviour::OnDamage( PFBaseUnitDamageDesc const & desc)
{
  if( IsUnitValid( pUnit->GetCurrentTarget() ) )
    return;

  if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
    return; // Attack forbid flag not empty!

  CPtr<PFBaseUnit> pSender = IsValid(desc.pSender) ? ( desc.pSender->IsMounted() ? desc.pSender->GetMountedOn() : desc.pSender ) : NULL;
  if ( IsTargetValid(pSender) && pSender->IsVisibleForFaction(pUnit->GetFaction()) && !desc.dontAttackBack )
  {
    PushAttackState( pUnit, pUnit, pSender, false, true );
  }
}

bool PFBaseBehaviour::IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const
{
  return pUnit->IsAttackedUnitAlly( pAttacked, originalAttackedFaction );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Screamer : public NonCopyable
{
  Screamer( const CPtr<PFBaseUnit>& pSender, const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
    : pSender( pSender ), pTarget( pTarget ), st( st ) {}

  void operator() ( PFBaseUnit &unit )
  {
    const CPtr<PFBaseUnit> pUnit( &unit );
    if ( ( pSender != pUnit ) && IsUnitValid( pUnit ) )
    {
      // Check distance to new target - it must be less then chasing range + atack range
      const float maxAlarmOnScreamRange = pUnit->GetChaseRange() + pUnit->GetAttackRange();

      if ( !pUnit->IsTargetInRange( pTarget, maxAlarmOnScreamRange ) )
      {
        return;
      }

      if ( st == ScreamTarget::ScreamAlert )
      {
        if ( !pUnit->IsTargetInRange( pTarget, pUnit->GetTargetingRange() ) )
        {
          return; // ignore alert screams if target is in targeting range
        }
      }

      pUnit->OnScream( pTarget, st );
    }
  }

  CPtr<PFBaseUnit> pSender;
  CPtr<PFBaseUnit> pTarget;
  const ScreamTarget::ScreamType st;
};

void PFBaseBehaviour::DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
{
  Screamer screamer( pUnit.GetPtr(), pTarget, st );
  GetWorld()->GetAIWorld()->ForAllUnitsInRange( pUnit->GetPosition(), pUnit->GetScreamRange(), screamer, UnitMaskingPredicate( 1 << pUnit->GetFaction() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFSummonBehaviour::PFSummonBehaviour( PFBaseMovingUnit* _pUnit, PFBaseUnit* _pMaster, const NDb::SummonBehaviourBase* _pBehaviourData, float _maxLifeTime, int _behaviourFlags )
  : PFBaseBehaviour( _pUnit )
  , pMaster( _pMaster )
  , lifeTime( 0.0f )
  , maxLifeTime( _maxLifeTime )
  , behaviourFlags( _behaviourFlags )
  , index( -1 )
  , lashRange(0.0f)
  , responseRange(0.0f)
  , responseTime(0.0f)
  , pBehaviourDb(_pBehaviourData)
{
}

PFSummonBehaviour::PFSummonBehaviour()
  : pMaster( 0 )
  , lifeTime( 0.0f )
  , maxLifeTime( 0.0f )
  , behaviourFlags( 0 )
  , index( -1 )
  , lashRange(0.0f)
  , responseRange(0.0f)
  , responseTime(0.0f)
  , pBehaviourDb(NULL)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonBehaviour::Unsummon()
{
  lifeTime = -1.0f;

  pUnit->KillUnit(NULL, PFBaseUnit::UNITDIEFLAGS_UNSUMMON );
}

//////////////////////////////////////////////////////////////////////////
float PFSummonBehaviour::GetLashRange() const
{
  if ( lashRange > 0 )
    return lashRange;

  if ( IsValid(pUnit) )
    return pUnit->GetChaseRange();

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFSummonBehaviour::OnStep( float dtInSeconds )
{
  bool bRet = PFBaseBehaviour::OnStep( dtInSeconds );

  lifeTime += dtInSeconds;

  if ( maxLifeTime > EPS_VALUE )
  {
    if ( ( lifeTime > maxLifeTime ) && ( behaviourFlags & BEHAVIOURFLAGS_CONTROLLEDLIFETIME ) )
    {
      Unsummon();
    }
  }

  return bRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBehaviourGroup::AddBehavior(CPtr<PFSummonBehaviour> const &behaviour)
{
  int index = 0;

  ++groupSize;

  ring::Range<PFSummonBehaviour::GroupRing> it(group);
  while ( it && it->GetIndex() == index)
  {
    ++it;
    ++index;
  }
  behaviour->SetIndex(index);
  PFSummonBehaviour::GroupRing::insertBefore(behaviour, &(*it));

  ++namedGroupsSize[behaviour->GetGroupName()];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBehaviourGroup::RemoveBehavior(CPtr<PFSummonBehaviour> const &behaviour)
{
  NI_VERIFY(groupSize > 0, "Wrong group size", return; );
  
  --groupSize;

  PFSummonBehaviour::GroupRing::safeRemove(behaviour);
  
  --namedGroupsSize[behaviour->GetGroupName()];
}

int PFBehaviourGroup::GetSize( const string& summonGroupName ) const
{
  map<string, int>::const_iterator it = namedGroupsSize.find( summonGroupName );
  if ( it != namedGroupsSize.end() )
    return it->second;
  
  return 0;
}

}

REGISTER_WORLD_OBJECT_NM(PFBaseBehaviour, NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonBehaviour, NWorld);
REGISTER_WORLD_OBJECT_NM(PFBehaviourGroup, NWorld);