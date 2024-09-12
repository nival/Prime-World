#pragma once
#include "PFWorldObjectBase.h"
#include "PFAIWorld.h"
#include "PFCreep.h"


namespace NWorld
{

struct StatModifier
{
  StatModifier()
    : stat(NDb::EStat(-1)) , statMult(1.0f) , isTop(false) {}

  StatModifier(NDb::EStat _stat, float _statMult, bool _isTop)
    : stat(_stat) , statMult(_statMult) , isTop(_isTop) {}

  NDb::EStat stat;
  float statMult;
  bool isTop;
};

typedef list<StatModifier> StatModifiers;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base creep spawner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseSpawner: public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0x8B77A480, PFBaseSpawner );

  struct LevelUpInfo
  {
    ZDATA
    float timeLevelUpInterval;
    int   timeLevelUpIncrement;
    int   spawnLevelUpInterval;
    int   spawnLevelUpIncrement;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&timeLevelUpInterval); f.Add(3,&timeLevelUpIncrement); f.Add(4,&spawnLevelUpInterval); f.Add(5,&spawnLevelUpIncrement); return 0; }

    bool ShouldGainLevels() const { return ( ( timeLevelUpInterval > 0.0f ) && ( timeLevelUpIncrement > 0 ) ); }
    const LevelUpInfo( float _timeLevelUpInterval = 0.0f, int _timeLevelUpIncrement = 0, int _spawnLevelUpInterval = 0, int _spawnLevelUpIncrement = 0 ) 
      : timeLevelUpInterval( _timeLevelUpInterval ), timeLevelUpIncrement( _timeLevelUpIncrement ), spawnLevelUpInterval(_spawnLevelUpInterval), spawnLevelUpIncrement(_spawnLevelUpIncrement) { }
  };

  nstl::string spawnerName;
  NDb::Ptr<NDb::BaseCreepSpawner> spawnerDesc;
  int creepsInWaveCounter;

  ZDATA_(PFWorldObjectBase)
  int           level;
  float         levelUpTimer;
  LevelUpInfo   levelUpInfo;
  StatModifiers statModifiers;
  float         spawnDelay;
  int           spawnWaveCounter;
  Placement     spawnPosition;
  bool          enabled;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&level); f.Add(3,&levelUpTimer); f.Add(4,&levelUpInfo); f.Add(5,&statModifiers); f.Add(6,&spawnDelay); f.Add(7,&spawnWaveCounter); f.Add(8,&spawnPosition); f.Add(9,&enabled); return 0; }

  void AddStatModifier(NDb::EStat stat, float statMult, bool isTop) { statModifiers.push_back(StatModifier(stat, statMult, isTop)); }

  Placement const & GetSpawnPosition() const { return spawnPosition; }
  const string & GetSpawnerName() const { return spawnerName; }
  int GetLastWave() const { return spawnWaveCounter; }
  int GetCreepsInLastWave() const { return creepsInWaveCounter; }
  virtual NDb::EFaction GetFaction() const { return NDb::EFaction(-1); }

  void SpawnWave();

  virtual void Hide(bool hide) { enabled = !hide; }

  virtual NDb::BaseCreepSpawner const* GetDBDesc() const { return spawnerDesc; }

  void MakeLevelupsForTimeDelta( float dtInSeconds );
protected:
  PFBaseSpawner( PFWorld* pWorld, const NDb::AdvMapObject& dbObject, float timeOffset = 0 );

  virtual bool Step( float dtInSeconds );
  void StepCreepsTimeLevel( float dtInSeconds );
  void StepCreepsWaveLevel();

  void RegisterCreep(PFBaseCreep * pCreep);


  int   GetMaxCreepsLevel() const;
  int   GetCreepsLevel() const { return level; }
  float GetSpawnDelay() const { return spawnDelay; }
  int   GetSpawnWaveCounter() const { return spawnWaveCounter; }

  float GetTimeLevelUpInterval() const;
  int   GetTimeLevelUpIncrement() const;
  float GetLifeTimeLevelUpInterval() const;
  int   GetLifeTimeLevelUpIncrement() const;

  Placement GetCreepPosition(Placement const & creepOffset) const;

  void SetCreepsLevel( int newLevel, bool ignoreCap = false ) { level = max( ignoreCap ? newLevel : min( GetMaxCreepsLevel(), newLevel ), 1); }
  void SetSpawnDelay( float newDelay ) { spawnDelay = newDelay; }

  virtual bool CanSpawnWave() const { return enabled; };

  virtual void SpawnCreeps() {};

  explicit PFBaseSpawner() {}

  void ApplyStatModifiers(NWorld::PFBaseCreep * creep) const;
};

} // namespace NWorld
