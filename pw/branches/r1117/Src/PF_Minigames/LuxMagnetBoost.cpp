#include "stdafx.h"

#include "LuxMagnetBoost.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"
#include "PaintLogic.h"

#include "LuxMagnet.h"

#include "PaintPoint.h"
#include "PaintFragment.h"

namespace PF_Minigames
{


void LuxMagnetBoost::Start()
{
  currentState = EState::Started;
  closestPoint = 0;
  painterPoints.clear();
  newMagnet = 0;
}

EEaselBoostFireMode::Enum LuxMagnetBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  Start();

  newMagnet = new LuxMagnet( GetWorld(), searchInterval, radiusR1, radiusR2, numBallToEat, this );

  _gameLogic->GetGameBoard()->AddCollider( newMagnet );

  return EEaselBoostFireMode::WaitingActivation;
}

void LuxMagnetBoost::StepInstalledMagnets( int deltaTime,  LuxGameLogic* _gameLogic )
{
  {
    Magnets::iterator it = installedMagnets.begin();
    Magnets::iterator last = installedMagnets.end();

    for (; it != last; ++it )
    {
      (*it)->Step( deltaTime, _gameLogic );
    }
  }

  {
    Magnets::iterator it = installedMagnets.begin();

    for ( ; it != installedMagnets.end(); )
    {
      if ( (*it)->IsExhausted() )
        it = installedMagnets.erase( it );
      else
        ++it;
    }
  }
}

void LuxMagnetBoost::vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic )
{
  StepInstalledMagnets( deltaTime, _gameLogic );

  if ( currentState == EState::None )
    return;

  switch(currentState)
  {
  case EState::Started:
    {
      _gameLogic->GetPaintLogic()->GetPainterPoints( painterPoints );  // получить color points

      if ( painterPoints.empty()  )
      {
        currentState = EState::None;  
      }
      else
      {
        HighlightFragmentsWithMagnet( true, _gameLogic );
        currentState = EState::WaitingForPlacement;
      }
    }
    break;

  case EState::WaitingForPlacement:
    {
      // определить расстояние до ближайщей color point
      closestPoint = LocateClosestPainterPoint( userPos );
      if ( !IsValid( closestPoint ) ) 
      {
        HighlightFragmentsWithMagnet( false, _gameLogic );
        currentState = EState::None;  
        break;
      }

      HighlightFragmentsWithMagnet( true, _gameLogic );
      closestPoint->SetMode( EPainterPointMode::MagnetPreselect );
      newMagnet->SetPainterPoint( closestPoint );
    }

    break;

  case EState::Placed:
    {
      if ( !IsValid( closestPoint ) ) 
      {
        HighlightFragmentsWithMagnet( false, _gameLogic );
        currentState = EState::None;  
        break;
      }

      InstallMagnet( closestPoint, _gameLogic );

      HighlightFragmentsWithMagnet( false, _gameLogic );
      closestPoint->SetMode( EPainterPointMode::MagnetInstalled );

      currentState = EState::None;
    }

    break;
  }
}

void LuxMagnetBoost::HighlightFragmentsWithMagnet( bool _highlight, LuxGameLogic* _gameLogic )
{
  struct Traverse
  {
    bool highlight;

    Traverse( bool _highlight ) : highlight(_highlight) {}

    void operator ()( CPainterPoint* _point )
    {
      if ( _point->GetMode() != EPainterPointMode::MagnetInstalled )
        _point->SetMode( highlight ? EPainterPointMode::MagnetHighlight : EPainterPointMode::None );
    }    
  } func( _highlight );

  _gameLogic->GetPaintLogic()->ForAllPoints( func );
}


CPainterPoint* LuxMagnetBoost::LocateClosestPainterPoint( const SVector& _currPos )
{
  if ( painterPoints.empty()  )
    return 0;

  int64 dest = 0;

  return CPaintFragment::GetClosestPoint( painterPoints, _currPos, true, NDb::COLOR_ANY, dest );
}


void LuxMagnetBoost::InstallMagnet( CPainterPoint* _point, LuxGameLogic* _gameLogic )
{
  CompleteBoostFire();

  installedMagnets.push_back( newMagnet );
  newMagnet = 0;
}


bool LuxMagnetBoost::ProcessInput( const SEaselMouseInput & mouseInput, LuxGameLogic* _gameLogic )
{
  if ( currentState == EState::WaitingForPlacement )
  {
    if( mouseInput.xCoord < 0 )
      userPos.x = 0;
    else if ( mouseInput.xCoord > EaselConst::Get_LOGIC_FIELD_WIDTH() )
      userPos.x = EaselConst::Get_LOGIC_FIELD_WIDTH();
    else
      userPos.x = mouseInput.xCoord;

    if( mouseInput.yCoord < 0 )
      userPos.y = 0;
    else if( mouseInput.yCoord > EaselConst::Get_LOGIC_FIELD_HEIGHT() )
      userPos.y = EaselConst::Get_LOGIC_FIELD_HEIGHT();
    else
      userPos.y = mouseInput.yCoord;

    if ( mouseInput.leftBtnClicked && IsValid( closestPoint ) )
    {
      currentState = EState::Placed;
    }

    return true;
  }

  return false;
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxMagnetBoost, PF_Minigames )
