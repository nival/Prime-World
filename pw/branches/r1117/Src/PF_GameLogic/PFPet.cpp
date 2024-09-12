#include "stdafx.h"

#include "PFPet.h"
#include "PFHero.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////
// State

PFPetAIBaseState::PFPetAIBaseState(CPtr<PFBasePetUnit> const& pPet)
: PFBasePetUnitState( pPet )
, minEscortDistance( pPet->GetObjectSize() * 0.5f )
, maxEscortDistance( 0.0f )
{
  if ( IsUnitValid( pPet ) )
  {
    pPetKeeper = pPet->GetKeeper();
    maxEscortDistance = pPet->GetChaseRange();
  }
}

bool PFPetAIBaseState::OnStep( float dt )
{
  // Режим следования за игроком. Перемещаемся в позицию рядом с игроком
  // Если в targetingRange появляется враг - ...

  if ( GetCurrentState() )
  {
    FSMStep(dt);
  }

  // Invalid pet or invalid
  if ( !IsUnitValid( pOwner ) || !IsValid( pPetKeeper ) )
  {
    return true;
  }

  if ( !GetCurrentState() )
  {
    const CVec2 vPetKeeperPosition = pPetKeeper->IsDead() ? pPetKeeper->GetSpawnPosition().AsVec2D() : pPetKeeper->GetPosition().AsVec2D();
    if ( pOwner->IsPositionInRange( vPetKeeperPosition, maxEscortDistance ) )
    {
      // Движемся за мастером
      const CVec2 escortPosition = pPetKeeper->IsDead() ? pPetKeeper->GetSpawnPosition().AsVec2D() : pPetKeeper->GetPetEscortPosition().AsVec2D();
      if ( !pOwner->IsPositionInRange( escortPosition, minEscortDistance ) )
      {
        pOwner->MoveTo( escortPosition );
      }
    }
  }

  return false;
}



//////////////////////////////////////////////////////////////////////////
// Unit

PFBasePetUnit::PFBasePetUnit(CPtr<PFWorld> pWorld, const NDb::BasePet &petObj, CPtr<PFBaseHero> pKeeper_)
  : PFCreature(pWorld, pKeeper_->GetPetEscortPosition(), CVec2(0.0f, 1.0f),  petObj)
  , pKeeper(pKeeper_)
{
  // Initialize base unit
  PFBaseUnit::InitData data;
  data.faction      = pKeeper->GetFaction();
  data.type         = NDb::UNITTYPE_PET;
  data.playerId     = pKeeper->GetPlayerId();
  data.pObjectDesc  = &petObj;
  Initialize(data);

  NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];
  CreateClientObject<NGameX::PFCreep>(NGameX::PFCreep::CreatePars(petObj.sceneObject, pAnimSet, pWorld->GetScene(), BADNODENAME));

  SetVulnerable(true);

  EnqueueState(new PFPetAIBaseState(this), true);
}

void PFBasePetUnit::Reset()
{
	PFCreature::Reset();
	NDb::Ptr<NDb::AnimSet> pAnimSet = NDb::SessionRoot::GetRoot()->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];
	CreateClientObject<NGameX::PFCreep>(NGameX::PFCreep::CreatePars(dbUnitDesc->sceneObject, pAnimSet, GetWorld()->GetScene(), BADNODENAME)); //HAS
}

//
PFBasePetUnit *CreateTestPet( PFWorld* pWorld, const char *name, const CPtr<PFBaseHero>& pKeeper)
{
  NDb::Ptr<NDb::BasePet> pDBPet = NDb::Get<NDb::BasePet>(NDb::DBID(name));
  NI_VERIFY(IsValid(pDBPet), NStr::StrFmt("Cannot find pet: %s", name), return NULL;);

  NI_ASSERT(IsUnitValid(pKeeper), "Invalid pet keeper");

  return new PFBasePetUnit( pWorld, *pDBPet, pKeeper);
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFPetAIBaseState, NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBasePetUnit, NWorld)
