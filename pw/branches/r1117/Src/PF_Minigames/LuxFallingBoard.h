#pragma once

#include "../PF_Core/WorldObject.h"

#include "LuxBoard.h"
#include "LuxBall.h"

#include "EaselTrajectory.h"

#include "Random.h"


namespace PF_Minigames
{

class LuxBallDeleteNotification;
class CLuxFallingObject;

class LuxPlatformBoard;

//////////////////////////////////////////////////////////////////////////
//
// falling board for all falling objects and catch operations
// processes inner events EVENT_OBJECT_FALLING
// send notifications
//
//////////////////////////////////////////////////////////////////////////
class LuxFallingBoard : public ILuxBoard, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C5, LuxFallingBoard )

public:
  LuxFallingBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic );
  ~LuxFallingBoard();

  void DropCoin( const SVector & from );

  void ResetFallingObjects();
  virtual void ProcessStep( int deltaTime, LuxGameLogic* _gameLogic );

  typedef nstl::list<CObj<CLuxFallingObject>> FallingObjects;
  FallingObjects& GetFallingObjects() { return objects; }

private:

  LuxFallingBoard() : ILuxBoard( BOARD_NULL, 0 ) { }

  void MoveFallingObjects(int deltaTime);
  void RemovePassedObjects(float _deltaTime);
  bool CheckObjectPlatformIntersection( const CLuxFallingObject * object ) const;
  void PickObjectsByPlatform(float _deltaTime);

  ZDATA_(ILuxBoard)
  ZPARENT(PF_Core::WorldObjectBase)

  SVector platformPos;
  SVector prevPlatformPos;
  NDb::Coin coinData;

  FallingObjects objects;
  RandomGenerator randomGenerator;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ILuxBoard*)this); f.Add(2,(PF_Core::WorldObjectBase*)this); f.Add(3,&platformPos); f.Add(4,&prevPlatformPos); f.Add(5,&coinData); f.Add(6,&objects); f.Add(7,&randomGenerator); return 0; }

};

}
