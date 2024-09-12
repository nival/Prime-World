#include "stdafx.h"
#include "LuxPlatformBoard.h"

#include "DBEasel.h"

#include "LuxBoost.h"
#include "LuxJokerBoost.h"
#include "LuxPaintBlastBoost.h"

#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "MinigameSessionInterface.h"

#include "LuxDef.h"

#include "EaselConstants.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class LuxPlatformBoard implementation
//
//////////////////////////////////////////////////////////////////////////
LuxPlatformBoard::LuxPlatformBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic ) 
: ILuxBoard( BOARD_PLATFORM, _gameLogic )
, PF_Core::WorldObjectBase( _pWorld, false )
, shouldGenerateNewBalls(true)
, createBullet(false)
, doWaitCreation(false)
, pauseTime(1000)
, currentPauseTime(0)
, leftClicks(0)
, rightClicks(0)
{
  platform = new LuxPlatform( _gameLogic->GetEasel(), gameLogic->GetNotifier() );

  pauseTime = _gameLogic->GetGameData()->commonParams->ballFireInterval * 1000.f;

  // setting start platform position
  SVector startPos( EaselConst::Get_LOGIC_FIELD_WIDTH() / 2 , EaselConst::Get_LOGIC_FIELD_HEIGHT() / 2 );
  platform->SetPlatformPos(startPos); 
}


LuxPlatformBoard::~LuxPlatformBoard()
{
}

bool LuxPlatformBoard::vProcessInput( const SEaselMouseInput & mouseInput )
{
  // checking only XCoords since there's only horizontal line trajectory
  SVector currPosition = platform->GetPlatformPos();
	currPosition.x = Clamp( mouseInput.xCoord, 
      int( EaselConst::Get_BORDER_WIDTH_OFFSET() ), 
      int( EaselConst::Get_LOGIC_FIELD_WIDTH() - EaselConst::Get_BORDER_WIDTH_OFFSET() ) );

	platform->SetPlatformPos(currPosition);   // setting new platform position

  // button click can only be processed at level run time 
  if ( gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN)
    return true;

  if ( mouseInput.leftBtnClicked )
    leftClicks++;
  if ( mouseInput.rightBtnClicked )
    rightClicks++;

  return true;
}

void LuxPlatformBoard::ProcessClicks()
{
  // checking left mouse button click
  if ( leftClicks > 0 )
  {
    // if bullet ball is not fired, then fire him
    // and send bullet fired notification
    CObj<LuxBall> ball = platform->FireBulletBall();

    if ( IsValid( ball ) )
    {
      gameLogic->GetGameBoard()->BallFired( ball );
      doWaitCreation = true;
      currentPauseTime = 0;
    }

    leftClicks--;
  }

  // checking right mouse button
  if ( rightClicks > 0 )
  {
    // right mouse button is pressed
    // we can change color of bullet ball
    if ( IsValid( platform->GetBulletBall() ) )
    {
      platform->SwapBalls();

      CPtr<LuxBall> ball = platform->GetBulletBall();
      ball->SetColor( ball->Color() ); // no provide notification (ball corol changed)  // !!!
    }

    rightClicks--;
  }
}

void LuxPlatformBoard::ProcessStep( int deltaTime, LuxGameLogic* _gameLogic )
{
  if ( gameLogic->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_RUN )
  {
    ProcessClicks();

    if ( doWaitCreation )
    {
      currentPauseTime += deltaTime;

      if ( currentPauseTime >= pauseTime )
      {
        createBullet = true;
        doWaitCreation = false;
      }
    }

    if ( shouldGenerateNewBalls )
    { 
      platform->InitialCreateBalls( _gameLogic->GetGameBoard() );
      shouldGenerateNewBalls = false;
    }
    else
    {
      if ( platform->UpdateBalls( createBullet, _gameLogic->GetGameBoard() ) )
      {
        createBullet = false;
      }
    }

    platform->Update( deltaTime );
  }
}

LuxBall* LuxPlatformBoard::CreatePaintBlastBall()
{
  return platform->CreatePaintBlastBall();
}

LuxBall*  LuxPlatformBoard::CreateJokerBall()
{
  return platform->CreateJokerBall();
}


}	// namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LuxPlatformBoard, PF_Minigames )
