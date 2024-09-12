#include "stdafx.h"

#include "Easel.h"

#include "LuxFallingObject.h"
#include "LuxFallingBoard.h"
#include "LuxPlatformBoard.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"
#include "EaselPriestess.h"
#include "EaselWorld.h"

#include "Random.h"
#include "../System/lerp.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxFallingBoard::LuxFallingBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic )
: PF_Core::WorldObjectBase( _pWorld, false ),
  ILuxBoard( BOARD_FALLING, _gameLogic ),
  platformPos(0,0),
  prevPlatformPos(0,0)
{
  coinData = _gameLogic->GetGameData()->commonParams->coin;
  randomGenerator.SetRandomSeed(_gameLogic->GetEasel()->GetRandomSeed());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxFallingBoard::~LuxFallingBoard()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxFallingBoard::CheckObjectPlatformIntersection( const CLuxFallingObject * object ) const
{
  double radius = EaselConst::Get_BALL_DEF_DIAMETER() * coinData.catchRadius;

  double sum1x = object->GetPosition().x;
  double sum1y = object->GetPosition().y;

  double sum2x = (double( platformPos.x ) + double( prevPlatformPos.x )) / 2.0;
  double sum2y = EaselConst::Get_LOGIC_FIELD_HEIGHT();

  sum1x -= sum2x;
  sum1y -= sum2y;

  double distance = sqrt( sum1x * sum1x + sum1y * sum1y );

  if ( distance < radius ) 
    return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::PickObjectsByPlatform( float deltaTime )
{
  for ( FallingObjects::iterator it = objects.begin(); it != objects.end(); ++it )
  {
    if ( CheckObjectPlatformIntersection( *it ) )
    {
      gameLogic->GetPristessProxy()->AddGoldDelayed( gameLogic->GetGameData()->priestessStats->coinNafta );
      DevTrace( "MG2 DEBUG: Add gold for PickObjectsByPlatform: coinNafta(%d) = total(%d)", gameLogic->GetGameData()->priestessStats->coinNafta, gameLogic->GetGameData()->priestessStats->coinNafta );
      (*it)->SetPicked(true);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::RemovePassedObjects(float _deltaTime)
{
  for ( FallingObjects::iterator it = objects.begin(); it != objects.end(); )
  {
    if ( !(*it)->IsInValidPosition() || (*it)->IsPicked() )
    {
      it = objects.erase( it );
    }
    else
      ++it;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::ResetFallingObjects()
{
  objects.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::DropCoin( const SVector & fallFrom )
{
  if ( randomGenerator.Random( 0, 100 ) > coinData.fallingPercentage )
    return;

  if ( gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN )
    return;

  SVector fallTo;
  fallTo.y = EaselConst::Get_LOGIC_FIELD_HEIGHT() * 1.2f;
  fallTo.x = randomGenerator.Random( 0.0f, EaselConst::Get_LOGIC_FIELD_WIDTH() );

  SInitialConditions start( fallFrom, fallTo, EaselConst::Get_BALL_DEF_DIAMETER() * coinData.jumpSpeed, EaselConst::Get_BALL_DEF_DIAMETER() * coinData.gravity );
  CObj<CLuxFallingObject> object = new CLuxFallingObject( gameLogic->GetEasel()->GetPFWorld(), start );
  objects.push_back( object );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::MoveFallingObjects( int deltaTime )
{
  for( FallingObjects::iterator it = objects.begin(); it != objects.end(); ++it )
    (*it)->Update( deltaTime );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxFallingBoard::ProcessStep( int deltaTime, LuxGameLogic* _gameLogic )
{
  prevPlatformPos = platformPos;
  platformPos = _gameLogic->GetPlatformBoard()->GetPlatform()->GetPlatformPos();

  RemovePassedObjects(deltaTime);
  MoveFallingObjects(deltaTime);
  PickObjectsByPlatform(deltaTime);
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxFallingBoard, PF_Minigames )
