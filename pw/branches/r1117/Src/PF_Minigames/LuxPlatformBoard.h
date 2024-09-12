#pragma once

#include "LuxDef.h"
#include "LuxBoard.h"
#include "LuxPlatform.h"

#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{

// forward declarations
class LuxPlatform;

//////////////////////////////////////////////////////////////////////////
//
// Platform Board class, is responsible for platform trajectory
// calculation
// processes events BALL_HIT and BALL_MISS
//
//////////////////////////////////////////////////////////////////////////
class LuxPlatformBoard : public ILuxBoard, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C1, LuxPlatformBoard )

public:
	LuxPlatformBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic );
	~LuxPlatformBoard();

	// input processing implementation
	virtual bool vProcessInput( const SEaselMouseInput & mouseInput );
  virtual void ProcessStep( int deltaTime, LuxGameLogic* _gameLogic );

  LuxPlatform * GetPlatform() { return platform; }

  LuxBall*  CreatePaintBlastBall();
  LuxBall*  CreateJokerBall();

private:
  LuxPlatformBoard() : ILuxBoard( BOARD_NULL, 0 ) {}

  void ProcessClicks();

private:
  ZDATA_(ILuxBoard)
  ZPARENT(PF_Core::WorldObjectBase)

  CObj<LuxPlatform> platform;

  bool createBullet;

  bool doWaitCreation;
  int pauseTime;
  int currentPauseTime;
  bool shouldGenerateNewBalls;

  int leftClicks;
  int rightClicks;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ILuxBoard*)this); f.Add(2,(PF_Core::WorldObjectBase*)this); f.Add(3,&platform); f.Add(4,&createBullet); f.Add(5,&doWaitCreation); f.Add(6,&pauseTime); f.Add(7,&currentPauseTime); f.Add(8,&shouldGenerateNewBalls); f.Add(9,&leftClicks); f.Add(10,&rightClicks); return 0; }

};

} // namespace PF_Minigames