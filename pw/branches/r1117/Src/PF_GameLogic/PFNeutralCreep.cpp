#include "stdafx.h"

#include "PFNeutralCreep.h"
#include "PFCommonCreep.h"
#include "AdventureScreen.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#include "PFClientObjectHelpers.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

namespace
{
  bool    g_bSpawnNeutralCreeps = true;
  bool    g_bKillCreepsOnSpawnerHide = true;
}

namespace NWorld
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFNeutralCreepSpawner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFNeutralCreepSpawner::PFNeutralCreepSpawner(PFWorld* pWorld, const NDb::AdvMapObject &dbObject)
  : PFBaseSpawner(pWorld, dbObject)
  , minAttackRange(10000.0f)
{
  spawnerDesc = dynamic_cast<NDb::AdvMapNeutralCreepSpawner const*>(dbObject.gameObject.GetPtr());
  NI_VERIFY( spawnerDesc, "Invalid creep spawner", return; );

  SetCreepsLevel( spawnerDesc->baseLevel, true );

	// Precache creeps
#ifndef VISUAL_CUTTED
	for ( vector<NDb::AdvMapNeutralCreepsGroup>::const_iterator iGroup = spawnerDesc->groups.begin(); iGroup != spawnerDesc->groups.end(); ++iGroup )
	{
		for ( vector<NDb::NeutralSpawnObject>::const_iterator iCreep = iGroup->creeps.begin(); iCreep != iGroup->creeps.end(); ++iCreep )
		{
			if ( iCreep->creep )
			{
				pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(iCreep->creep), SUMMONNODE );

				if ( iCreep->creep->sceneObject )
					NScene::SceneObjectsPool::Get()->Reserve( pWorld->GetScene(), iCreep->creep->sceneObject, 1, SUMMONNODE );

        // precache
        if ( iCreep->creep->image )
        {
          CObj<Render::Texture> texture = iCreep->creep->image->Load();
          texture = 0;
        }
			}
		}
	}
#endif

	CreateClientObject<NGameX::PFClientNeutralCreepSpawner>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool PFNeutralCreepSpawner::Step(float dtInSeconds)
//{
//  NI_PROFILE_FUNCTION
//  
//  PFBaseSpawner::Step(dtInSeconds);
//
//  return true;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFNeutralCreepSpawner::CanSpawnWave() const
{
  bool canSpawn = false;

  if ( g_bSpawnNeutralCreeps && PFBaseSpawner::CanSpawnWave() && GetWorld()->GetAIWorld()->GetSpawnNeutralCreeps() 
        && spawnerDesc->groups.size() && GetSpawnDelay() < 0 )
  {
    // Exceed limit? or we have some creeps left?
    int waveCount = spawnerDesc->waveCount;
    canSpawn = (waveCount > GetSpawnWaveCounter()) && waveCount || !waveCount;
    canSpawn &= creeps.empty();
  }

  return canSpawn;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFNeutralCreepSpawner::OnAfterReset()
{
  CreateClientObject<NGameX::PFClientNeutralCreepSpawner>();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFNeutralCreepSpawner::SpawnCreeps()
{
  minAttackRange = 10000.0f;
  creeps.clear();

  int groupIndex = GetWorld()->GetRndGen()->Next( 0, spawnerDesc->groups.size() - 1 );
  vector<NDb::AdvMapNeutralCreepsGroup>::const_iterator iGroup = &spawnerDesc->groups[groupIndex];
  for ( vector<NDb::NeutralSpawnObject>::const_iterator iCreep = iGroup->creeps.begin(); iCreep != iGroup->creeps.end(); ++iCreep )
  {
    if ( iCreep->creep && (iCreep->waveDelayToAppear <= GetSpawnWaveCounter()) )
    {
      PFNeutralCreep* neutralCreep = new PFNeutralCreep(GetWorld(), *iCreep->creep, GetCreepPosition(iCreep->offset.GetPlace()), 
                                               iCreep->useSpawnerWalkLimit, iCreep->limitWalkDistance, this, 
                                               GetRelativeTargets( spawnerDesc->path, iCreep->offset.GetPlace().pos),
                                               GetLifeTimeLevelUpInterval(), GetLifeTimeLevelUpIncrement(), iCreep->specialAwarding );

      InitializeCreep(neutralCreep, iCreep->creep->recolor);
      RegisterCreep(neutralCreep);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreepSpawner::InitializeCreep( PFNeutralCreep* neutralCreep, const Render::HDRColor& recolor )
{
  ApplyStatModifiers(neutralCreep);

  
  const int levelsToGrow = GetCreepsLevel() - neutralCreep->GetNaftaLevel();
  if ( levelsToGrow > 0 )
  {
    neutralCreep->DoLevelups( levelsToGrow );
  }

  if ( IsValid( neutralCreep->ClientObject() ) )
  {
    if ( recolor.A > 0.0f )
    {
      neutralCreep->ClientObject()->Recolor( recolor );
    }

    neutralCreep->ClientObject()->Summon();
  }

  if ( neutralCreep->GetAttackRange() < minAttackRange )
    minAttackRange = neutralCreep->GetAttackRange();

  creeps.push_back( neutralCreep );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreepSpawner::AwardForCreepKill(NaftaAward& award) const
{
  if (spawnerDesc->naftaForGroupKill > 0)
  {
    //give nafta for the last one
    if ( (spawnerDesc->waveCount && creeps.size() == 1) && GetSpawnWaveCounter() == spawnerDesc->waveCount )
      award.toKiller += spawnerDesc->naftaForGroupKill;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreepSpawner::DropCreep( PFNeutralCreep *pCreep)
{
  TCreeps::iterator it = find( creeps.begin(), creeps.end(), pCreep );
  if ( it != creeps.end() )
    creeps.erase( it );

  // If all creeps are killed/charmed - reset spawnDelay, so they will appear only after full spawnDelay countdown
  if ( creeps.empty() )
  {
    SetSpawnDelay( spawnerDesc->spawnDelay );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreepSpawner::DropAllCreeps()
{
  if (creeps.size() > 0)
  {
    creeps.clear();
    SetSpawnDelay( spawnerDesc->spawnDelay );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPtr<PFBaseUnit> PFNeutralCreepSpawner::GetSpawnTarget( CPtr<PFBaseMovingUnit>& pUnit, float range, const bool checkRange /*=true*/ )
{
  NI_PROFILE_FUNCTION

  TCreeps::iterator it = creeps.begin();
  while (it != creeps.end())
  {
    if (PFNeutralCreep * pCreep = (*it))
    {
      if( pCreep == pUnit ) 
      {
        ++it;
        continue;
      }

      if( PFBaseUnit* target = pCreep->GetCurrentTarget() )
      {
        if( !checkRange )
          return( target );

        if( pUnit->IsTargetInRange( target, range ) )
          return( target );
      }
    }
    ++it;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreepSpawner::Hide(bool hide)
{
  if (hide)
  {
    RemoveClientObject();

    if (g_bKillCreepsOnSpawnerHide)
    {
      // Creeps are dropped via this calls chain: KillUnit->OnUnitDie->DettachFromSpawner
      while ( !creeps.empty() )
      {
        TCreeps::iterator it = creeps.begin();
        if ( IsValid(*it))
        {
          (*it)->KillUnit(0, PFBaseUnit::UNITDIEFLAGS_NONE);
        }
        else
        {
          NI_ALWAYS_ASSERT("Bad creep pointer in spawner!");
          creeps.pop_front();
        }
      }
    }
  }
  else
  {
    CreateClientObject<NGameX::PFClientNeutralCreepSpawner>();
  }

  if (!g_bKillCreepsOnSpawnerHide)
  {
    TCreeps::iterator it = creeps.begin();
    while (it != creeps.end())
    {
      if (PFNeutralCreep * pCreep = (*it))
      {
        if (!pCreep->CheckFlag(NDb::UNITFLAG_ISOLATED))
        {
          pCreep->Cleanup();
          pCreep->Hide(hide);
        }
        else if (pCreep->ClientObject())
        {
          pCreep->ClientObject()->OnHide(true);
          pCreep->UpdateHiddenState(false);
        }
      }
      ++it;
    }
  }
}

NDb::MapForceStatModifierApplication PFNeutralCreepSpawner::GetMapForceStatModifierApplication() const
{
  if (IsValid(spawnerDesc))
    return spawnerDesc->mapForceStatModifierApplication;
  // TODO: ?
  return NDb::MAPFORCESTATMODIFIERAPPLICATION_ALL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFNeutralCreep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFNeutralCreep::PFNeutralCreep( PFWorld* pWorld, const NDb::AdvMapCreep &creepObj, const Placement& placement, bool useSpawnerWalkLimit, float limitWalkDistance, 
                               PFNeutralCreepSpawner* parentSpawner, const vector<CVec2>& waypoints, float interval /*= 0.0f*/, int increment /*= 0*/, bool specialAwarding_ /*= false*/ )
  : PFBaseCreep( pWorld, creepObj, NDb::FACTION_NEUTRAL, GetUnitTypeByCreepType( creepObj.creepType ), -1, placement, interval, increment, false, parentSpawner->GetMapForceStatModifierApplication() ) // creeps are not bound to players
  , spawner( parentSpawner )
  , needRotate( false )
  , initialPlacement(placement)
  , walkLimit(limitWalkDistance)
  , attachedToSpawner( true )
  , specialAwarding(specialAwarding_)
{
  initialPlacement.pos = GetPosition(); // actual spawned position

  InitializeSummonBehavior();
  if ( GetBaseMoveSpeed() == 0.0f )
  {
    positionBySpawner = GetPosition().AsVec2D();
  }
  else
  {
    positionBySpawner = placement.pos.AsVec2D(); // original position assigned by spawner
  }

  CObj<PFBaseBehaviour> pB( new PFNeutralCreepBehaviour( this, initialPlacement, waypoints ) );
	AddBehaviourOnTop( pB );
  nativeBehaviour = pB;

  if (IsValid(spawner))
  {
    if (NDb::AdvMapNeutralCreepSpawner const * pSpawnerDesc = spawner->GetDBDesc())
    {
      if (useSpawnerWalkLimit)
      {
        walkLimit = pSpawnerDesc->limitWalkDistance;
      }
    }
  }
}

void PFNeutralCreep::OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags /*= UNITDIEFLAGS_NONE*/, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  PFBaseCreep::OnUnitDie( pKiller, flags, pDamageDesc );

  // Спаунер может использоваться при получении награды через PFNeutralCreepBehaviour::GetKillerAward, поэтому отцепляем после обработки игромеханической смерти
  // Note: Hide function relies on this dettach!
  DettachFromSpawner();
}

void PFNeutralCreep::OnAfterReset()
{
  PFBaseCreep::OnAfterReset();

  if ( GetBaseMoveSpeed() == 0.0f )
  {
    // востанавливаем ориентацию крипов заданную дизайнерами (в частности ориентацию змея)
    CQuat rotation;
    rotation = initialPlacement.rot;
    CALL_CLIENT_1ARGS( SetRotation, rotation );
  }
  else
  {
    CVec2 dir = GetMoveDirection();
    CQuat rotation;
    float pitch = 0, yaw = 0, roll = 0;
    float dstAngle = atan2( dir.x, -dir.y );
    rotation.DecompEulerAngles( &yaw, &pitch, &roll );
    rotation.FromEulerAngles( dstAngle, pitch, roll );
    CALL_CLIENT_1ARGS( SetRotation, rotation );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreep::ChangeFaction( NDb::EFaction newFaction )
{
  if (GetFaction() == newFaction)
    return;
  PFBaseCreep::ChangeFaction( newFaction );
  if ( nativeBehaviour )
  {
    if ( nativeBehaviour == Behaviour() )
    nativeBehaviour->SetFaction( newFaction );
  }
}

void PFNeutralCreep::DettachFromSpawner()
{
  if ( attachedToSpawner && IsValid(spawner))
  {
    spawner->DropCreep(this);
    attachedToSpawner = false;
    //spawner = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBID* PFNeutralCreep::GetSpawnerDBID() const
{ 
  if( GetSpawner() ) 
    return &(GetSpawner()->GetDBDesc()->GetDBID());
  else return NULL; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreep::DisableLevelUps()
{
  levelUpInfo.timeLevelUpInterval  = 0.0f;
  levelUpInfo.timeLevelUpIncrement = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNeutralCreep::RotateIfNeeded()
{
  if (GetNeedRotate() && !IsMoving())
  {
    if (ClientObject())
      ClientObject()->TurnBy(initialPlacement.rot);

    SetNeedRotate( false );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const vector<CVec2>* PFNeutralCreep::GetWaypoints() const
{
  PFNeutralCreepBehaviour* pBehaviour = dynamic_cast<PFNeutralCreepBehaviour*>(Behaviour());
  if ( !pBehaviour )
    return 0;
  return &(pBehaviour->WayPoints());
}


bool PFNeutralCreep::SetCreepBehavior( const string& behavior, const vector<string>& params )
{
  CObj<PFBaseBehaviour> pB = 0;
  if ( behavior == "MoveTo" )
  {
    pB = PFNeutralCreepMoveToPointBehaviour::CreateWithParams( this, params );
  }
  else if ( behavior == "PathMove" )
  {
    pB = PFNeutralCreepMoveByPathBehaviour::CreateWithParams( this, params );
  }
  else if ( behavior == "Chase" )
  {
    pB = PFNeutralCreepChaseBehaviour::CreateWithParams( this, params );
  }

  if ( !pB )
    return false;

  if ( IsValid(nativeBehaviour) )
  {
    pB->SetFaction( nativeBehaviour->GetFaction() );
    pB->SetUnitType(  nativeBehaviour->GetUnitType() );
    if ( nativeBehaviour == Behaviour()  )
    {
      RemoveBehaviour( nativeBehaviour.GetPtr() );
      AddBehaviourOnTop( pB );
    }
    else 
    {
      behaviourList.insertAfter( pB, nativeBehaviour );
      behaviourList.remove(nativeBehaviour);
      nativeBehaviour->OnStop();
    }
  }
  else 
  {
    AddBehaviourOnTop( pB );
  }

  nativeBehaviour = pB;
  return true;
}

bool PFNeutralCreep::IsAggressiveNeutralCreep() const
{
  if ( nativeBehaviour == Behaviour() && GetSpawner() && GetSpawner()->GetDBDesc()->isAggressive )
    return true;

  return false;
}

} // namespace NWorld


REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFNeutralCreep,             NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFNeutralCreepSpawner,      NWorld)

REGISTER_DEV_VAR("spawn_neutral_creeps",  g_bSpawnNeutralCreeps,  STORAGE_NONE);
REGISTER_DEV_VAR("kill_creeps_on_spawner_hide",  g_bKillCreepsOnSpawnerHide,  STORAGE_NONE);
