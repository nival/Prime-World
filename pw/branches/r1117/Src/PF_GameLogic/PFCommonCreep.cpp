#include "stdafx.h"

#include "PFCommonCreep.h"
#include "PFNeutralCreep.h"

#include "TileMap.h"

#include "DBStats.h"
#include "DBGameLogic.h"
#include "PFBaseUnitStates.h"
#include "PFAIWorld.h"
#include "../System/InlineProfiler.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#include "PFClientObjectHelpers.h"
#include "PF_Core/EffectsPool.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

#define GET_AI_PARAM(param) GetWorld()->GetAIWorld()->GetAIParameters().param
#define GET_AI_PARAM2(param, force) (force > 0 ? force : GetWorld()->GetAIWorld()->GetAIParameters().param)

static NDebug::DebugVar<unsigned int> spawn_CommonCreepCnt( "CommonCreepCnt", "Spawn" );


#ifdef DEBUG_NEUTRALS_STATES
#define DEBUG_PRINT(a) DebugTrace(a);
#else
#define DEBUG_PRINT(a)
#endif


namespace
{
  int     g_bSpawnCreeps          = 0xFFFF;
  float   g_fCreepWayPointRadius  = 7.5f;
  float   g_fCreepForceSpawnDelay = 0.0f;
  int     g_nCreepForceSpawnLevel = 0;
  int     g_nCreepForceWaveNum    = 0;
  float   g_farestCreepPositionUpdateInterval = 1.0f;
  int     g_maxCreepsTotalCount = 0; // эта переменная перегружает то, что задано в AILogicParameters::maxCreepsCount
}

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFCreepSpawner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFCreepSpawner::PFCreepSpawner(PFWorld* pWorld, const NDb::AdvMapObject& dbObject)
  : PFBaseSpawner(pWorld, dbObject, pWorld->GetAIWorld()->GetBattleStartDelay())
  , farestCreepPositionUpdateOffset(g_farestCreepPositionUpdateInterval)
  , farestCreepPosition(dbObject.offset.GetPlace().pos.AsVec2D())
  , isOppositeBarracksDestroyed( false )
{
  spawnerDesc = dynamic_cast<NDb::AdvMapCreepSpawner const*>(dbObject.gameObject.GetPtr());
  NI_VERIFY(spawnerDesc, "Invalid creep spawner", return;);
  
  if (spawnerDesc->mustRegisterInAIWorld)
  {
    pWorld->GetAIWorld()->RegisterCreepSpawner( spawnerDesc->faction, spawnerDesc->routeID, GetObjectId() );
  }  
  
#ifndef VISUAL_CUTTED
  for( vector<NDb::SpawnObject>::const_iterator iCreep = spawnerDesc->creeps.begin(), iEnd = spawnerDesc->creeps.end(); iCreep != iEnd; ++iCreep )
  {
    if ( iCreep->creep )
		{
			pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(iCreep->creep), SUMMONNODE);

			if ( iCreep->creep->sceneObject )
				NScene::SceneObjectsPool::Get()->Reserve( pWorld->GetScene(), iCreep->creep->sceneObject, 5, SUMMONNODE );

      // precache
      if ( iCreep->creep->image )
      {
        CObj<Render::Texture> texture = iCreep->creep->image->Load();
        texture = 0;
      }

      iCreep->timer.GetPtr();
    }
  }
#endif

  for (vector<CVec2>::const_iterator it = spawnerDesc->path.begin(), end = spawnerDesc->path.end(); it != end; ++it)
    targets.push_back(*it);

  statFactors.resize( NDb::KnownEnum<NDb::EStat>::SizeOf(), 1.0f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreepSpawner::SetCreepsPower(CreepsPower power)
{
  if ( power==powerLarge )
  {
    vector<float> const& stats = GET_AI_PARAM(quarterDestroyStatsMultipliers);
    NI_VERIFY( stats.size() == NDb::KnownEnum<NDb::EStat>::SizeOf(), "Wrong stats count in quarterDestroyStatsMultipliers (\"GameLogic/AILogic.AILP", return; );
    statFactors = stats;
    isOppositeBarracksDestroyed = true;
  }
  else if ( power==powerMega )
  {
    SetCreepsLevel(GET_AI_PARAM(creepLevelCap));
    isOppositeBarracksDestroyed = true;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FloatSign(float val)
{
  double one = 1.0;
  double res =_copysign( one, val );
  return (int)res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 GetRotatedRelativePos( CVec2 const & point1, CVec2 const & point2, CVec2 const & point3, CVec2  const & relative )
{
  CVec2 dir1 = (point2-point1);
  CVec2 dir2 = (point3-point2);
  Normalize(&dir1);
  Normalize(&dir2);

  float dot = dir1.Dot(dir2);

  float rad = acos( dot );//NMath::ACos( dot );
  float euler = ToDegree( rad );
  CVec2 cross = dir1.CProduct(dir2);
  bool inverseAngle = (Sign(cross.x) * Sign(cross.y) > 0.0f);
  if ( fabs(euler-90.0f) < 1e-6f )
  {
    inverseAngle = (Sign(cross.x) > 0.0f);
  }

  euler = inverseAngle? 360.0f-euler: euler;

  //rotation
  rad = ToRadian( euler );

  CQuat rotator;
  rotator.FromEulerAngles(rad, 0.0f, 0.0f);
  CVec3 relative3d(relative.x, relative.y, 0.0f);
  CVec3 res;
  rotator.Rotate(&res,relative3d);
  return CVec2(res.x, res.y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CVec2> GetRelativeTargets( const vector<CVec2>& targets, CVec3 const & unitRelativePos )
{
  if (targets.empty())
    return targets;
  //NI_VERIFY(targets.size(), "unit doesnt have control points!?", return targets);

  vector<CVec2> relativeTargets;
  relativeTargets.reserve(targets.size());

  CVec2 newRelativePos = unitRelativePos.AsVec2D();

  //first one without changes
  relativeTargets.push_back(targets[0] + newRelativePos);

  for (int i = 1; i< targets.size()-1; i++)
  {
    newRelativePos = GetRotatedRelativePos( targets[i-1], targets[i], targets[i+1], newRelativePos);
    relativeTargets.push_back(targets[i] + newRelativePos);
  }

  //for the last one use the prev position
  relativeTargets.push_back(targets[targets.size()-1] + newRelativePos);

  return relativeTargets;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool bShowDebugWarning = true;
bool PFCreepSpawner::CanSpawnWave() const
{
  int maxCreepCount = GetWorld()->GetAIWorld()->GetAIParameters().maxCreepsCount;
  if (bShowDebugWarning && g_maxCreepsTotalCount > 0)
  {
    bShowDebugWarning = false;
    DebugTrace("MaxCreepsCount (%d) was overridden by creep_max_total_count (%d)", maxCreepCount, g_maxCreepsTotalCount );
    maxCreepCount = g_maxCreepsTotalCount;
  }

  // Spawn only if delay is over, max count not exceeded and spawn for relevant faction is not restricted
  return GetWorld()->GetAIWorld()->GetSpawnCreeps() && 
    PFBaseSpawner::CanSpawnWave() &&  GetSpawnDelay() < 0 && 
    GetWorld()->GetRegisteredCreepsCount() < maxCreepCount && 
    ( g_bSpawnCreeps & ( 1 << spawnerDesc->faction ) ) 
    ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreepSpawner::SpawnCreeps()
{
  for ( vector<NDb::SpawnObject>::const_iterator iCreep = spawnerDesc->creeps.begin(); 
          iCreep != spawnerDesc->creeps.end(); ++iCreep )
  {
    // Check if the creep should be spawned in the current wave
    int waveSpawnedCount = g_nCreepForceWaveNum > 0 ? g_nCreepForceWaveNum : GetSpawnWaveCounter();
    int startDelay = iCreep->timer ? iCreep->timer->startDelay : 0;
    int spawnDelay = iCreep->timer ? iCreep->timer->spawnDelay : 1;

    bool spawnBeforeBarracksDestroy = iCreep->timer ? ( iCreep->timer->spawnType & NDb::SPAWNTYPE_BEFORE ) : true;
    bool spawnAfterBarracksDestroy  = iCreep->timer ? ( iCreep->timer->spawnType & NDb::SPAWNTYPE_AFTER  ) : true;

    bool timeCheck       = waveSpawnedCount >= startDelay;
    bool modulusCheck    = ( spawnDelay <= 0 ) || ( ( ( waveSpawnedCount - startDelay ) % spawnDelay ) == 0 );
    bool barracsCheck    = ( !isOppositeBarracksDestroyed && spawnBeforeBarracksDestroy ) || ( isOppositeBarracksDestroyed && spawnAfterBarracksDestroy );
    if ( !timeCheck || ! modulusCheck || !barracsCheck )
    {
      continue;
    }

    if ( (startDelay > waveSpawnedCount) || ((spawnDelay > 0)&&(waveSpawnedCount - startDelay!=(int)((float)((waveSpawnedCount - startDelay)/spawnDelay)*spawnDelay))))
      continue;

    if ( iCreep->creep )
    {
      NI_PROFILE_BLOCK( "CommonCreep" );

      spawn_CommonCreepCnt.AddValue(1.0f);

      PFCommonCreep* pCreep = new PFCommonCreep( GetWorld(), *iCreep->creep, spawnerDesc->faction, 
                                                  GetCreepPosition(iCreep->place.GetPlace()), 
                                                  GetRelativeTargets( targets, iCreep->place.GetPlace().pos),
                                                  GetLifeTimeLevelUpInterval(), GetLifeTimeLevelUpIncrement(), this );

      InitializeCreep(pCreep, iCreep->creep->recolor);
      RegisterCreep(pCreep);
    }
  }

  SetSpawnDelay( GET_AI_PARAM2(creepsWavesDelay, g_fCreepForceSpawnDelay) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreepSpawner::InitializeCreep( PFCommonCreep* pCreep, const Render::HDRColor& recolor )
{
  ApplyStatModifiers(pCreep);
  creepsRing.addLast(pCreep);

  

  //Модели крипов реюзаются, поэтому надо сбросить цвет в дефолтный
#ifndef VISUAL_CUTTED
  {
    NI_PROFILE_BLOCK( "Recolor" );
    if ( pCreep->ClientObject() )
    {
      PF_Core::ColorModificationChannel* pChannel = 
        pCreep->ClientObject()->CreateColorModificationChannel(PF_Core::CMC_EFFECT2);
      pChannel->SetMulColor( Render::HDRColor( 1.0f , 1.f, 1.0f, 1.0f ) );
      if ( recolor.A > 0.0f )
        pCreep->ClientObject()->Recolor( recolor );
    }
  }
#endif //VISUAL_CUTTED
  pCreep->SetPower(GetCreepsLevel(), statFactors);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFCreepSpawner::Step(float dtInSeconds)
{
  PFBaseSpawner::Step(dtInSeconds);

  StepFarestCreepPosition(dtInSeconds);

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreepSpawner::StepFarestCreepPosition(float dtInSeconds)
{
  farestCreepPositionUpdateOffset-=dtInSeconds;
  if (farestCreepPositionUpdateOffset < 0)
  {
    const CVec2& startPos = GetSpawnPosition().pos.AsVec2D();
    farestCreepPositionUpdateOffset = g_farestCreepPositionUpdateInterval;
    farestCreepPosition = startPos;
    
    if ( !creepsRing.empty() && !targets.empty() )
    {
      CVec2 const& lastTarget = targets.back();
      float minDistance2 = fabs2( lastTarget - startPos );
      
      for (ring::Range<PFCommonCreep::CreepsRing> it(creepsRing); it; ++it)
      {
        PFCommonCreep *pCrep = &(*it);
        CVec2 const& creepPosition = pCrep->GetPosition().AsVec2D();
        float dist2 = fabs2( creepPosition - lastTarget );
        if ( minDistance2 > dist2 )
        {
          farestCreepPosition = creepPosition;
          minDistance2 = dist2;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFCommonCreep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFCommonCreep::PFCommonCreep( PFWorld* pWorld, const NDb::AdvMapCreep& creepObj, NDb::EFaction faction, const Placement& position, const vector<CVec2>& targets, float interval /* = 0.0f */, int increment /* = 0 */, PFCreepSpawner* parentSpawner/* = NULL */)
  : PFBaseCreep( pWorld, creepObj, faction, GetUnitTypeByCreepType( creepObj.creepType ), -1, position, interval, increment )  // creeps are not bound to players
  , minigameCreepID(-1)
  , spawner(parentSpawner)
  , walkLimit(-1.0f)
  , initialPlacement(position)
{
  NI_PROFILE_FUNCTION
  InitializeSummonBehavior();

  //++PFCreepSpawner::totalCreepsCount;
  GetWorld()->RegisterCreep(this);

  if ( IsValid(spawner) && targets.empty() )
  {
    if (NDb::AdvMapCreepSpawner const * pSpawnerDesc = spawner->GetDBDesc())
    {
        walkLimit = pSpawnerDesc->limitWalkDistance;
    }

    if ( GetBaseMoveSpeed() == 0.0f )
      initialPlacement.pos = GetPosition();

    CObj<PFBaseBehaviour> pB( new PFEvadeCreepBehaviour( this, initialPlacement ) );
    AddBehaviourOnTop( pB );
  }
  else
  {
    CObj<PFBaseBehaviour> pB(new PFCommonCreepBehaviour( this, targets ) );
    AddBehaviourOnTop( pB );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreep::SetPower(int level, const vector<float>& statFactors)
{
  // For now level is 1.
  int levelUps = level - 1;
  int forcedLevelUps = g_nCreepForceSpawnLevel - 1;

  DoLevelups( forcedLevelUps > 1 ? forcedLevelUps : levelUps );
  
  if ( !statFactors.empty() )
  {
    NI_ASSERT( statFactors.size() == NDb::KnownEnum<NDb::EStat>::SizeOf(), "Wrong size of creep power stats multipliers count!" );
    for ( int statId = 0; statId < NDb::KnownEnum<NDb::EStat>::SizeOf(); ++ statId )
    {
      NI_VERIFY( statFactors[statId] > EPS_VALUE, "Wrong stat multiplier!", continue; );

      if( StatValueWithModifiers* pStat = GetStat( NDb::EStat(statId) ) )
        pStat->SetCoreValue( pStat->GetCoreValue() * statFactors[statId] );
    }
  }
  InitializeLifeEnergy();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreep::OnInvalidPath()
{
	targetRevisionTime = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreep::RotateIfNeeded()
{
  if (GetNeedRotate() && !IsMoving())
  {
    if (ClientObject())
      ClientObject()->TurnBy(initialPlacement.rot);

    SetNeedRotate( false );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBID* PFCommonCreep::GetSpawnerDBID() const
{ 
  if( GetSpawner() ) 
    return &(GetSpawner()->GetDBDesc()->GetDBID());
  else return NULL; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreep::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  PFBaseCreep::OnUnitDie(pKiller, flags, pDamageDesc);
  //--PFCreepSpawner::totalCreepsCount;
  GetWorld()->UnregisterCreep(this);

  if (creepsRingPart.isLinked())
    CreepsRing::remove(this);

  /*
#ifndef VISUAL_CUTTED
  if ( minigameCreepID != -1 )
  {
    CPtr<PF_Minigames::IMinigamesMain> sharedData = GetWorld()->GetMinigamesMain();

    if ( IsValid( sharedData ) )
      sharedData->ReturnCreep( minigameCreepID );
  }
#endif //!VISUAL_CUTTED
  */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreep::OnDestroyContents()
{
  if (creepsRingPart.isLinked())
    CreepsRing::remove(this);
  PFBaseCreep::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFNeutralCreepBehaviour
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
PFEvadeCreepBehaviour::PFEvadeCreepBehaviour( PFCommonCreep* pCreep, const Placement& _initialPlacement )
: PFBaseBehaviour( pCreep )
, initialPlacement( _initialPlacement )
, targetingRange( 0.0f )
, useEvade( false )
{
  NI_VERIFY( IsValid( pCreep ), "invalid owner(paranoid?)", return );
  targetingRange = pCreep->GetTargetingRange();

  if (PFCreepSpawner const * pSpawner = pCreep->GetSpawner())
  {
    if (NDb::AdvMapCreepSpawner const * pSpawnerDesc = pSpawner->GetDBDesc())
    {
      useEvade = pSpawnerDesc->useEvade;

      if (useEvade)
      {
        evadeParams.SetData(pSpawnerDesc->evadeParams);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFEvadeCreepBehaviour::OnStep( float dtInSeconds )
{
  NI_PROFILE_FUNCTION

    if (pUnit->IsDead())
      return true;  // Do nothing if dead

  if ( pUnit->IsMicroAiEnabled() )
  {
    if ( pUnit->HaveAbilityInProgress() )
    {
      return true; // Do nothing during channeling
    }
    if ( pUnit->UseAbilityWithMicroAI() )
    {
      return true; // We cast ability on this step
    }
  }

  if (pUnit->GetCurrentState() == 0)
  {
    PFBaseUnit* pTarget = NULL;

    if ( targetingRange > 0.f )
    {
      pTarget = pUnit->FindTarget( targetingRange );
    }

    if ( IsUnitValid( pTarget ) )
    {
      DEBUG_PRINT("PFEvadeCreepBehaviour::OnStep EnqueueAttackState");
      EnqueueAttackState( pUnit, pTarget, false, true, true );
      pUnit->SetNeedRotate( true );
      return true;
    }
    else
    {
      if ( !useEvade && !IsCreepAtSpawner( 4.0f ) )
      {
        if (!pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ))
        {
          DEBUG_PRINT("PFEvadeCreepBehaviour::OnStep PushState PFBaseUnitCombatMoveState 1");
          pUnit->PushState( new PFBaseUnitCombatMoveState( GetWorld(), pUnit, initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * 4.0f ) );
          pUnit->SetNeedRotate( true );
          return true;
        }
      }
      else
      {
        pUnit->RotateIfNeeded();
      }
    }
  }

  PFCommonCreep * pCommonCreep = static_cast<PFCommonCreep*>( pUnit.GetPtr() );
  NI_VERIFY( pCommonCreep, "Common creep behaviour without common creep!", return true; );
  float walkLimit = pCommonCreep->GetWalkLimit();

  bool evade = false;

  if( IsValid( pUnit->GetCurrentTarget()) )
  {
    if( !CanSelectTarget(pUnit->GetCurrentTarget() ) && !pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
      evade = true;
  }
  else
  {
    // If there is a walk limit set - do checks and send the creep back to the spawner if needed
    if (!pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) && walkLimit >= 0.0f && fabs2(walkLimit) < fabs2(pUnit->GetPosition().AsVec2D() - pCommonCreep->GetSpawner()->GetSpawnPosition().pos.AsVec2D()))
      evade = true;
  }

  if( evade )
  {
    if (useEvade)
    {
      DEBUG_PRINT("PFEvadeCreepBehaviour::OnStep EnqueueState PFNeutralCreepEvadeState");
      pUnit->EnqueueState(new PFNeutralCreepEvadeState( GetWorld(), pUnit, initialPlacement), true);
      return true;
    }
    else
    {
      if ( !IsCreepAtSpawner( 2.0f ) )
      {
        DEBUG_PRINT("PFEvadeCreepBehaviour::OnStep EnqueueState PFBaseUnitCombatMoveState 2");
        pUnit->EnqueueState( new PFBaseUnitCombatMoveState( GetWorld(), pUnit, initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * 2.0f ), true );
        pUnit->SetNeedRotate( true );
        return true;
      }
    }
  }

  if ( useEvade && pUnit->IsIdle() && ( !IsCreepAtSpawner( 2.0f ) || pUnit->GetHealth() < pUnit->GetMaxHealth() || pUnit->GetEnergy() < pUnit->GetMaxEnergy() ) )
  {
    DEBUG_PRINT("PFEvadeCreepBehaviour::OnStep PushState PFNeutralCreepWaitState");
    pUnit->PushState(new PFNeutralCreepWaitState( GetWorld(), pUnit, initialPlacement, evadeParams.waitForNextTargetTime));
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEvadeCreepBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
  NI_VERIFY( IsUnitValid( pTarget ) && pTarget->IsVulnerable(), "Invalid Target!", return; );

  if ( pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDATTACK ) )
  {
    return; // Attack forbid flag not empty!
  }

  DEBUG_PRINT("PFEvadeCreepBehaviour::OnTarget PushAttackState");
  pUnit->DropStates();
  PushAttackState( pUnit, pUnit, pTarget, bStrongTarget, false, true );
  pUnit->SetNeedRotate( true );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEvadeCreepBehaviour::OnDamage( const PFBaseUnitDamageDesc& desc )
{
  // Don't counterattack here, as it currently happens in PFBaseBehaviour.
  // Neutral creep will autotarget using weights and then attack if needed

  if (useEvade && !pUnit->IsDead() && pUnit->GetCurrentState() == 0)
  {
    DEBUG_PRINT("PFEvadeCreepBehaviour::OnDamage PushState PFNeutralCreepWaitState");
    pUnit->PushState(new PFNeutralCreepWaitState( GetWorld(), pUnit, initialPlacement, evadeParams.waitForEvadeTime));
  }
}

bool PFEvadeCreepBehaviour::CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget /*= false*/ ) const
{
  PFCommonCreep * pCommonCreep = static_cast<PFCommonCreep*>( pUnit.GetPtr() );
  float walkLimit = pCommonCreep->GetWalkLimit();
  if ( walkLimit < 0.0f )
    return true;

  PFCreepSpawner const* pSpawner = pCommonCreep->GetSpawner();

  return fabs2( pTarget->GetPosition().AsVec2D() - pSpawner->GetSpawnPosition().pos.AsVec2D()) <= fabs2( walkLimit + pCommonCreep->GetAttackRange() );
}

bool PFEvadeCreepBehaviour::IsCreepAtSpawner( float distInTiles ) const
{
  return pUnit->IsPositionInRange( initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * distInTiles );
}

bool PFEvadeCreepBehaviour::IsInDefaultState() const
{
  return pUnit->IsIdle() && IsCreepAtSpawner( 4.0f );
}

bool PFEvadeCreepBehaviour::IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const
{
  PFCreepSpawner const* pSpawner = GetUnit()->GetSpawner();
  if ( originalAttackedFaction == NDb::FACTION_NEUTRAL && pSpawner )
  {
    CDynamicCast<PFCommonCreep> pAttackedCommon(pAttacked);
    if ( pAttackedCommon )
    {
      return pAttackedCommon->GetSpawner() == pSpawner;
    }
  }

  return PFBaseBehaviour::IsAttackedUnitAlly( pAttacked, originalAttackedFaction );
}

void PFEvadeCreepBehaviour::Resume()
{
  PFBaseBehaviour::Resume();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFCommonCreepBehaviour::OnStep(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
  
	CPtr<PFCreature> pUnit = static_cast<PFCreature*>(GetUnit().GetPtr());
	if ( pUnit->IsDead() )
		return true;

  if (pUnit->IsMicroAiEnabled())
  {
    if ( pUnit->HaveAbilityInProgress() )
      return true; // Do nothing during channeling
    if (pUnit->UseAbilityWithMicroAI())
      return true; // We cast ability on this step
  }

	if ( IsUnitValid( pUnit->GetCurrentTarget() ) )
	{
		// Combat mode - creep is in PFBaseUnitAttackState
		NI_ASSERT( pUnit->GetCurrentState(), "We have Target in idle mode!" );
		return true;
	}

	CPtr<PFBaseUnit> pTarget = pUnit->FindTarget( pUnit->GetTargetingRange() );
	if ( IsUnitValid(pTarget) )
	{
		pUnit->DropStates();
		pUnit->PushState( new PFBaseUnitAttackState( pUnit->GetWorld(), CPtr<PFBaseMovingUnit>(pUnit), pTarget, false) );
		pUnit->DoScream( pTarget, ScreamTarget::ScreamAlert ); // scream alert!
		return true;
	}

	if ( pUnit->IsIdle() && !wayPoints.empty() && !pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
	{
    CPtr<PFBaseMovingUnit> pMoving = static_cast<PFBaseMovingUnit*>(GetUnit().GetPtr());
		pUnit->PushState( new PFBaseUnitPathMovingState(pMoving, wayPoints, g_fCreepWayPointRadius) );
    pUnit->FSMStep(0.0f);
	}

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCommonCreepBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
	NI_VERIFY( IsUnitValid(pTarget) && pTarget->IsVulnerable(), "Invalid Target!", return; );

	if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
		return; // Attack forbid flag not empty!

  CPtr<PFBaseMovingUnit> pMovingUnit = static_cast<PFBaseMovingUnit*>(GetUnit().GetPtr());

	pUnit->DropStates();
	pUnit->PushState( new PFBaseUnitAttackState(pUnit->GetWorld(), pMovingUnit, pTarget, bStrongTarget) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreepSpawner::OnDestroyContents()
{
  Clear(creepsRing);
  PFWorldObjectBase::OnDestroyContents();
}


} // namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFCommonCreep,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFCreepSpawner,  NWorld)


REGISTER_WORLD_OBJECT_NM(PFCommonCreepBehaviour, NWorld)
REGISTER_WORLD_OBJECT_NM(PFEvadeCreepBehaviour, NWorld)

REGISTER_DEV_VAR("spawn_creeps",                  g_bSpawnCreeps,                       STORAGE_NONE);
REGISTER_DEV_VAR("creep_waypoint_radius",         g_fCreepWayPointRadius,               STORAGE_NONE);
REGISTER_DEV_VAR("creep_force_spawn_delay",       g_fCreepForceSpawnDelay,              STORAGE_NONE);
REGISTER_DEV_VAR("creep_force_spawn_level",       g_nCreepForceSpawnLevel,              STORAGE_NONE);
REGISTER_DEV_VAR("creep_force_wave_num",          g_nCreepForceWaveNum,                 STORAGE_NONE);
REGISTER_DEV_VAR("creep_max_total_count",         g_maxCreepsTotalCount,                STORAGE_NONE);
REGISTER_DEV_VAR("creep_farest_update_interval",  g_farestCreepPositionUpdateInterval,  STORAGE_NONE);
