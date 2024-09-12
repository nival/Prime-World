#include "stdafx.h"

#include "LuxJokerBoost.h"
#include "LuxGameLogic.h"
#include "LuxPlatformBoard.h"

namespace PF_Minigames
{

EEaselBoostFireMode::Enum LuxJokerBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  jokerBall = _gameLogic->GetPlatformBoard()->CreateJokerBall();
  return EEaselBoostFireMode::WaitingActivation;
}

void LuxJokerBoost::vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic ) 
{
  if ( IsValid( jokerBall ) )
  {
    if ( jokerBall->State() != BALL_STATE_ON_PLATFORM )
    {
      CompleteBoostFire();
      jokerBall = 0;
    }
  }
}


}

REGISTER_SAVELOAD_CLASS_NM( LuxJokerBoost, PF_Minigames )
