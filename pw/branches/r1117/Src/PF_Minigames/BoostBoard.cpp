#include "stdafx.h"

#include "BoostBoard.h"

#include "LuxDef.h"

#include "EaselPriestess.h"

#include "Easel.h"
#include "MinigameSessionInterface.h"

#include "DBEasel.h"
#include "../PF_GameLogic/DBMinigamesTypes.h"

#include "LuxMagnet.h"

#include "BoostsFactory.h"

#include "LuxAlchemistBoostsNotifications.h"

#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class LuxBoostBoard implementation
//
//////////////////////////////////////////////////////////////////////////
LuxBoostBoard::LuxBoostBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic )
: PF_Core::WorldObjectBase( _pWorld, false ),
  ILuxBoard( BOARD_BOOSTS, _gameLogic )
{
  CPtr<Easel> easel = _gameLogic->GetEasel();

  int levelID = easel->GetStatistics().GetCurrentLevelStatistics()->GetLevelID();

  const Easel::CurrentBoosts& currentBoosts = easel->GetCurrentBoosts();
  int boostCount = easel->GetLevelBoostCount( levelID );
  boosts.resize( boostCount );

  LuxBoostsFactory factory( _gameLogic->GetEasel() );

  for ( int i = 0; i < boostCount; ++i )
  {
    boosts[i] =  factory.CreateBoost( currentBoosts[i], _gameLogic->GetGameData() );
  }
}

LuxBoostBoard::~LuxBoostBoard()
{

}

void LuxBoostBoard::ProcessStep( int _deltaTime, LuxGameLogic* _gameLogic )
{
  if ( _gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN )
  {
    Boosts::iterator it = boosts.begin();
    Boosts::iterator last = boosts.end();

    for ( ; it != last; ++it )
    {
      (*it)->Abort();
    }

    return;
  }

  int currentAccessLevel = gameLogic->GetPristessProxy()->GetMinigameLevel();
  int currentGold = gameLogic->GetPristessProxy()->GetGold();

  for( Boosts::iterator it = boosts.begin(); it != boosts.end(); ++it )
  {
    (*it)->ProcessStep( _deltaTime, currentAccessLevel, currentGold, gameLogic );
  }
}

void LuxBoostBoard::OnUnusedPaint( const SVector& explosionPoint, NDb::EColor explosionColor, int explodedBallsNum )
{
  Boosts::iterator it = boosts.begin();
  Boosts::iterator last = boosts.end();

  for ( ; it != last; ++it )
  {
    (*it)->OnUnusedPaint( GetGameLogic(), explosionPoint, explosionColor, explodedBallsNum );
  }
}


LuxBoost* LuxBoostBoard::GetBoost( NDb::EBoostType _type )
{
  Boosts::iterator it = boosts.begin();
  Boosts::iterator last = boosts.end();

  for ( ; it != last; ++it )
  {
    if ( (*it)->GetBoostType() == _type )
      return *it;
  }

  return 0;
}


void LuxBoostBoard::FireBoost( NDb::EBoostType _type )
{
  if( gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN )
    return;

  CPtr<LuxBoost> boost = GetBoost( _type );

  if ( IsValid( boost ) )
  {
    if( ( gameLogic->GetPristessProxy()->GetGold() >= boost->GetPrice() ) && !ThereAreWaitingBoosts() )
    {
      boost->FireBoost( gameLogic );
    }
  }
}

bool LuxBoostBoard::vProcessInput( const SEaselMouseInput & mouseInput )
{
  for( Boosts::iterator it = boosts.begin(); it != boosts.end(); ++it )
  {
    if ( (*it)->ProcessInput( mouseInput, gameLogic ) )
      return true;
  }

  return false;
}

bool LuxBoostBoard::ThereAreWaitingBoosts() const
{
  for( Boosts::const_iterator it = boosts.begin(); it != boosts.end(); ++it )
  {
    if ( (*it)->IsWaitingActivation() )
      return true;
  }

  return false;
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxBoostBoard, PF_Minigames )
