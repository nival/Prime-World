#include "stdafx.h"

#include "PFTower.h"
#include "DBStats.h"
#include "TileMap.h"
#include "PFAIWorld.h"
#include "PFDispatchStrike1.h"
#include "PFApplicator.h"
#include "PFStatistics.h"
#include "DBGameLogic.h"

#include "Core/CoreFSM.h"
#include "Core/WorldCommand.h"
#include "PF_Core/EffectsPool.h"

#ifndef VISUAL_CUTTED
#include "PFClientBuilding.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

class PFTowerGuardState : public PFBaseUnitState
{
public:
  PFTowerGuardState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner);
  WORLD_OBJECT_METHODS(0xF5CC38B, PFTowerGuardState);
protected:
  virtual bool OnStep(float dt);
  virtual void OnLeave();
  PFTowerGuardState() {}
private:
  ZDATA_(PFBaseUnitState)
  CPtr<PFWorld> pWorld;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnitState*)this); f.Add(2,&pWorld); return 0; }
};

PFTowerGuardState::PFTowerGuardState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner)
  : PFBaseUnitState(pOwner)
  , pWorld(pWorld)
{
}

bool PFTowerGuardState::OnStep(float dt)
{
  if( !IsUnitValid(pOwner) )
    return true;

  CPtr<PFBaseUnit> pTarget = pOwner->FindTarget( pOwner->GetAttackRange(), false );
  if ( IsUnitValid(pTarget) )
  {
    pOwner->AssignTarget(pTarget, false);
    if ( pOwner->IsReadyToAttack() )
      pOwner->DoAttack();
  }
  else
  {
    pOwner->DropTarget();
  }

  return false;
}

void PFTowerGuardState::OnLeave()
{
  if ( IsUnitValid(pOwner) )
    pOwner->DropTarget();
}

//////////////////////////////////////////////////////////////////////////
PFTower::PFTower(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBattleBuilding(pWorld, dbObject)
  , screamCooldown(0.0f)
{
	pDesc = dynamic_cast<NDb::Tower const*>(dbObject.gameObject.GetPtr());
	NI_VERIFY( pDesc, "Invalid game object for the Tower", return; );

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFTower>( cp, pWorld->GetScene(), pDesc.GetPtr() ); //HAS
	Init(dbObject, pDesc, NDb::UNITTYPE_TOWER);
  
  ContolTurret(true);

  SetBaseAngle(pDesc->baseRotation);
  SetTurretParams( GetWorld()->GetAIWorld()->GetAIParameters().towerTurretParams );

  //count the towers for each faction in the game
  if ( pWorld != NULL && pWorld->GetStatistics() != NULL )
    pWorld->GetStatistics()->AddTowerToFaction(faction);

  PushState(new PFTowerGuardState(pWorld, this));
}

void PFTower::Reset()
{
	PFBattleBuilding::Reset();
	NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
	CreateClientObject<NGameX::PFTower>( cp, GetWorld()->GetScene(), pDesc.GetPtr() ); //HAS
}

PFTower::~PFTower()
{
}

float PFTower::OnDamage(const DamageDesc &desc)
{
  float ret = PFBattleBuilding::OnDamage(desc);

  if ( IsDead() )
    PFFsm::Cleanup();
  
  if ( screamCooldown < 0 && IsTargetValid(desc.pSender) && desc.pSender->GetFaction() != GetFaction() )
  {
    NI_ASSERT(GetWorld() && GetWorld()->GetAIWorld(), "Invalid World!");
    screamCooldown = GetWorld()->GetAIWorld()->GetAIParameters().heroScreamDelay;
    DoScream(desc.pSender, ScreamTarget::ScreamForHelp); // call to help!
  }

  return ret;
}

void PFTower::OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st )
{
  if ( ( st == ScreamTarget::ScreamAlert ) || !IsTargetInAttackRange( pTarget ) )
  {
    return;
  }
  PFBattleBuilding::OnScream( pTarget, st );
}

bool PFTower::Step(float dtInSeconds)
{
  if ( screamCooldown >= 0 )
    screamCooldown -= dtInSeconds;
  
  return PFBattleBuilding::Step(dtInSeconds);
}

void PFTower::OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc)
{
  GetWorld()->GetStatistics()->AddTowerDestroy(this, pKiller);
  PFBattleBuilding::OnUnitDie(pKiller, flags, pDamageDesc);
}

void PFTower::OnTargetAssigned()
{
  lastAngleResetDelay = -1.0f;
  deltaAngle          = DetectMinAngleDelta(currentAngle, NormalizeAngle( GetTargetAngle() ) );
  if ( ClientObject() )
  {
    ClientObject()->OnTargetAssigned();
  }
}

void PFTower::OnTargetDropped()
{
  lastAngleResetDelay = lastAngleResetDelayTime;
  if ( ClientObject() )
  {
    ClientObject()->OnTargetDropped();
  }
}

PFControllableTower::PFControllableTower(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFTower(pWorld, dbObject)
{
  if (!IsVulnerable())
  {
    SetVulnerable(true);
  }
  Cleanup( true );
}

// do not scream
float PFControllableTower::OnDamage(const DamageDesc &desc) 
{
  return PFTower::OnDamage(desc);
}

void PFControllableTower::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  PFTower::OnUnitDie(pKiller, flags, pDamageDesc);
  //Здесь было оповещение об окончании игры
}

bool  PFControllableTower::Step( float dtInSeconds )
{
  const CPtr<PFBaseUnit>& pTarget = GetCurrentTarget();
  if( IsUnitValid( pTarget ) )
  {
    if( IsTargetInAttackRange( pTarget ) && IsReadyToAttack() )
    {
      DoAttack();
    }
  }
  else
  {
    DropTarget();
  }

  return PFTower::Step( dtInSeconds );
}

// do not react on autotarget
void  PFControllableTower::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
}

// do not react on scream
void  PFControllableTower::OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st )
{
}


PFFountain::PFFountain(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBuilding(pWorld, dbObject)
{
	pDesc = dynamic_cast<NDb::Fountain const*>(dbObject.gameObject.GetPtr());

	NI_VERIFY( pDesc, "Invalid game object for the building", return; );

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFBuilding>( cp, pWorld->GetScene(), pDesc.GetPtr() ); //HAS
  Init(dbObject, pDesc, NDb::UNITTYPE_BUILDING);

  PushState(new PFTowerGuardState(pWorld, this));
  SetVulnerable( false ); // fountain cannot to be destroyed
}

void PFFountain::Reset()
{
	PFBuilding::Reset();
	NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
	CreateClientObject<NGameX::PFBuilding>( cp, GetWorld()->GetScene(), pDesc.GetPtr() ); //HAS
}

void PFFountain::OnDestroyContents()
{
  PFFsm::Cleanup();
  PFBuilding::OnDestroyContents();
}

void PFFountain::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
  AssignTarget(pTarget, bStrongTarget);
  PFBuilding::OnTarget(pTarget, bStrongTarget);
}

}

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFTower, NWorld)
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFControllableTower, NWorld)
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFFountain, NWorld);

REGISTER_WORLD_OBJECT_NM(PFTowerGuardState, NWorld);
