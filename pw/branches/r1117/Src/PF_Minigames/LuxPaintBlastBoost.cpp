#include "stdafx.h"

#include "LuxPaintBlastBoost.h"
#include "LuxGameLogic.h"
#include "LuxPlatformBoard.h"
#include "LuxBall.h"

namespace PF_Minigames
{

EEaselBoostFireMode::Enum LuxPaintBlastBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  blastBall = _gameLogic->GetPlatformBoard()->CreatePaintBlastBall();
  return EEaselBoostFireMode::WaitingActivation;
}


void LuxPaintBlastBoost::vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic ) 
{
  if ( IsValid( blastBall ) )
  {
    if ( blastBall->State() != BALL_STATE_ON_PLATFORM )
    {
      CompleteBoostFire();
      blastBall = 0;
    }
  }
}
}

REGISTER_SAVELOAD_CLASS_NM( LuxPaintBlastBoost, PF_Minigames )