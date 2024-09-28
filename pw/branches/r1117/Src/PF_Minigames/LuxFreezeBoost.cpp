#include "stdafx.h"

#include "LuxFreezeBoost.h"

#include "LuxGameLogic.h"
#include "LuxGameBoard.h"
#include "LuxGameBoardChains.h"

namespace PF_Minigames
{

EEaselBoostFireMode::Enum LuxFreezeBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  inFreezeTime = 0.0;

  fIsFired = true;   // boost has been fired

  _gameLogic->GetGameBoard()->SetFrozen( true );

  return EEaselBoostFireMode::Activated;
}


void LuxFreezeBoost::vProcessStep( int deltaTime, LuxGameLogic* _gameLogic )
{
  if ( fIsFired  )
  {
    inFreezeTime += deltaTime; 

    if ( inFreezeTime >= freezeTime )
    {
      fIsFired = false;  // boost operation time has been ended

      _gameLogic->GetGameBoard()->SetFrozen( false );
    }
  }
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxFreezeBoost, PF_Minigames )
