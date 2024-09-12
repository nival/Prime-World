#include "StdAfx.h"
#include "PFBaseSpawner.h"
#include "PFAIContainer.h"

#define GET_AI_PARAM(param) GetWorld()->GetAIWorld()->GetAIParameters().param

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseSpawner::PFBaseSpawner( PFWorld* pWorld, const NDb::AdvMapObject& dbObject, float timeOffset /*= 0*/ ) 
 : PFWorldObjectBase( pWorld, 1 )
 , level( 1 ) // level must start with 1 to match minimum base level, which is set on BaseUnit level
 , levelUpTimer( timeOffset )
 , spawnDelay( 0.0f )
 , spawnWaveCounter( 0 )
 , spawnPosition( dbObject.offset.GetPlace() )
 , creepsInWaveCounter(0)
 , enabled(true)
{
  spawnerName = dbObject.scriptName;

  if (pWorld)
  {
    if (PFAIWorld const * pAIWorld = pWorld->GetAIWorld())
      spawnDelay = pAIWorld->GetBattleStartDelay();

    if (PFAIContainer * pAIContainer = pWorld->GetAIContainer())
      pAIContainer->RegisterObject(this, "", dbObject.scriptGroupName);
  }

  spawnerDesc = dynamic_cast<NDb::BaseCreepSpawner const *>(dbObject.gameObject.GetPtr());
  NI_VERIFY( IsValid(spawnerDesc), "Invalid creep spawner!", return; );

  spawnDelay += spawnerDesc->firstSpawnTimeOffset;

  levelUpInfo.timeLevelUpInterval   = GetTimeLevelUpInterval();
  levelUpInfo.timeLevelUpIncrement  = GetTimeLevelUpIncrement();
  levelUpInfo.spawnLevelUpInterval  = spawnerDesc->levelUpInfo.spawnLevelUpInterval;
  levelUpInfo.spawnLevelUpIncrement = spawnerDesc->levelUpInfo.spawnLevelUpIncrement;

  if (levelUpInfo.timeLevelUpInterval > 0.0f)
    levelUpTimer += levelUpInfo.timeLevelUpInterval;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseSpawner::RegisterCreep(PFBaseCreep * pCreep)
{
  ++creepsInWaveCounter;
  
  if (!spawnerName.empty())
  {
    string groupName = NStr::StrFmt( "%s_w%d", spawnerName.c_str(), spawnWaveCounter+1 );
    string creepName = NStr::StrFmt( "%s_w%d_c%d", spawnerName.c_str(), spawnWaveCounter+1, creepsInWaveCounter );

    if (PFWorld * pWorld = GetWorld())
    {
      if (PFAIContainer * pAIContainer = pWorld->GetAIContainer())
      {
        pAIContainer->RegisterObject(pCreep, creepName, groupName);
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseSpawner::MakeLevelupsForTimeDelta( float dtInSeconds )
{
  if ( levelUpInfo.timeLevelUpInterval > 0.0f && levelUpInfo.timeLevelUpIncrement >= 1 )
  {
    float timeAfterStep = dtInSeconds + levelUpInfo.timeLevelUpInterval - levelUpTimer;
    int fullIntervals = (int)floor( timeAfterStep / levelUpInfo.timeLevelUpInterval );
    float toNextLevelup = timeAfterStep - fullIntervals * levelUpInfo.timeLevelUpInterval;
    levelUpTimer = levelUpInfo.timeLevelUpInterval - toNextLevelup;
    SetCreepsLevel( level + levelUpInfo.timeLevelUpIncrement * fullIntervals );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseSpawner::Step( float dtInSeconds )
{
  NI_PROFILE_FUNCTION

  if ( spawnDelay >= 0.0f )
    spawnDelay -= dtInSeconds;

  if ( CanSpawnWave() )
  {
    SpawnWave();
  }

  StepCreepsTimeLevel(dtInSeconds);

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseSpawner::SpawnWave()
{
  creepsInWaveCounter = 0;
  SpawnCreeps();
  ++spawnWaveCounter;
  StepCreepsWaveLevel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseSpawner::StepCreepsTimeLevel( float dtInSeconds )
{
  if ( ( level >= GetMaxCreepsLevel() ) 
      || ( levelUpInfo.timeLevelUpInterval < 0.0f ) || ( levelUpInfo.timeLevelUpIncrement < 1 ) )
    return;

  if ( GetWorld()->GetAIWorld()->IsCreepLevelupPaused() )
    return;

  levelUpTimer -= dtInSeconds;
  if ( levelUpTimer < 0 )
  {
    SetCreepsLevel( level + levelUpInfo.timeLevelUpIncrement );

    levelUpTimer = levelUpInfo.timeLevelUpInterval;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseSpawner::StepCreepsWaveLevel()
{
  if (levelUpInfo.spawnLevelUpInterval > 0 && levelUpInfo.spawnLevelUpIncrement > 0 
      && spawnWaveCounter % levelUpInfo.spawnLevelUpInterval == 0)
  {
    SetCreepsLevel( level + levelUpInfo.spawnLevelUpIncrement );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseSpawner::GetTimeLevelUpInterval() const
{
  if (!IsValid(spawnerDesc))
    return 0.0f;

  if (spawnerDesc->levelUpInfo.interval != -1.0f)
    return spawnerDesc->levelUpInfo.interval;

  return GET_AI_PARAM( creepsLevelUpInfo.interval );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseSpawner::GetTimeLevelUpIncrement() const
{
  if (!IsValid(spawnerDesc))
    return 0;

  if (spawnerDesc->levelUpInfo.increment != -1)
    return spawnerDesc->levelUpInfo.increment;

  return GET_AI_PARAM( creepsLevelUpInfo.increment );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseSpawner::GetLifeTimeLevelUpInterval() const
{
  if (!IsValid(spawnerDesc) || !spawnerDesc->levelUpInfo.lifetimeLevelUp)
    return 0.0f;

  return GetTimeLevelUpInterval();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseSpawner::GetLifeTimeLevelUpIncrement() const
{
  if (!IsValid(spawnerDesc) || !spawnerDesc->levelUpInfo.lifetimeLevelUp)
    return 0;

  return GetTimeLevelUpIncrement();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Placement PFBaseSpawner::GetCreepPosition(Placement const & creepOffset) const
{
  // We use only spawner position and creep position offset here to initialize creep's starting position
  Matrix43 m;
  spawnPosition.GetMatrix(&m);
  Placement creepPosition = Transform(creepOffset.pos, m);

  // And here we calculate the rotation of the creep, so it will look to the same direction as it's spawner
  CQuat relativeRot(creepOffset.rot );
  relativeRot.Inverse();
  creepPosition.rot = spawnPosition.rot * relativeRot;

  return creepPosition;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apply stats modifiers to the specified creep unit. Should be called from deriving classes for each created creep unit.
void PFBaseSpawner::ApplyStatModifiers(PFBaseCreep * creep) const
{
  if (!creep)
    return;

  StatModifiers::const_iterator itCurr = statModifiers.begin();
  StatModifiers::const_iterator itLast = statModifiers.end();

  for (; itCurr != itLast; ++itCurr)
  {
    NWorld::ValueWithModifiers * unitValue(creep->GetStat((*itCurr).stat));

    if (unitValue)
    {
			unitValue->AddModifier((*itCurr).statMult, 0.0f, PF_Core::WORLD_ID, (*itCurr).isTop);
    }
  }
}

int PFBaseSpawner::GetMaxCreepsLevel() const
{
  return GetWorld()->GetAIWorld()->GetCreepLevelCap();
}


} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFBaseSpawner,   NWorld);

