#pragma once

#include "EaselNotifications.h"
#include "DBEasel.h"

#include "../PF_Core/WorldObject.h"


namespace PF_Minigames
{
 
// forward declarations
class Easel;
class EaselLevelStatistics;
_interface IPriestessProxy;
class PaintLogic;

// notifications
class EaselLevelWonBeginNotification;
class EaselGameLostNotification;

class EaselStatistics
{
public:
  EaselStatistics();
  ~EaselStatistics() {}

  void SetEasel( Easel* _easel ) { easel = _easel; }

  // start level and gather all statistics. returns pointer on new level statistic 
  const CObj<EaselLevelStatistics>& StartGatherFoNewLevel( PF_Core::IWorld* _pWorld, int paintId, int levelId);

  // stop gathering statistic for current level and store it in archive
  void StopGatherForLevel();

  // returns pointer to last started level. This level can be currently in play
  const EaselLevelStatistics * GetCurrentLevelStatistics() const { return currentLevel; }

  NDb::WonGameMedal GetLevelMedalEarned(int levelId) const;
  bool              IsGameFullyCompleted() const;

  void Copy( const EaselStatistics& _remoteStat );

private:

  ZDATA
  CPtr<Easel> easel;
  CObj<EaselLevelStatistics> currentLevel;

  StaticArray<int, NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf> levelWonCount;
  StaticArray<NDb::WonGameMedal, NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf> levelMedalEarned;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&easel); f.Add(3,&currentLevel); f.Add(4,&levelWonCount); f.Add(5,&levelMedalEarned); return 0; }
};


class EaselLevelStatistics : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4CD, EaselLevelStatistics )
    EaselLevelStatistics() {}
public:
  EaselLevelStatistics( PF_Core::IWorld* _pWorld, int _paintId, int _levelId );
  ~EaselLevelStatistics();

  // step processing mechanics
  void ProcessStep(int deltaTime);

  NDb::WonGameMedal GetMedal() const { return wonAwardMedal; }

  NDb::EEaselRoundStatus GetRoundStatus() const { return status; } 

  int GetPaintID() const { return paintId; }
  int GetLevelID() const { return levelId; }

  // common init/start methods
  void InitStats( Easel * _easel, IPriestessProxy* spProxy, PaintLogic * _paintLogic );

  void OnGameWon();
  void OnGameLost();

  void Copy( const EaselLevelStatistics* _remoteStat );

private:

  ZDATA_(PF_Core::WorldObjectBase)

  NDb::EEaselRoundStatus status;
  NDb::WonGameMedal wonAwardMedal;
  float elapsedTime;
  int paintId;
  int levelId;

  CPtr<IPriestessProxy> spPriestessProxy;

  NDb::Ptr<NDb::DBPriestessStats> priestessStats;
  NDb::Ptr<NDb::DBPriestessLevelStats> priestessLevelStats;
  NDb::Ptr<NDb::DBEaselGame> dbGame;

  CPtr<PaintLogic> paintLogic;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&status); f.Add(3,&wonAwardMedal); f.Add(4,&elapsedTime); f.Add(5,&paintId); f.Add(6,&levelId); f.Add(7,&spPriestessProxy); f.Add(8,&priestessStats); f.Add(9,&priestessLevelStats); f.Add(10,&dbGame); f.Add(11,&paintLogic); return 0; }
private:
};

} // namespace PF_Minigames
