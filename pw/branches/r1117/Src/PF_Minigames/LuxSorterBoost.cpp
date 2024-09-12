#include "stdafx.h"

#include "LuxSorterBoost.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "LuxSorterBoostFiredNotification.h"

namespace PF_Minigames

{

EEaselBoostFireMode::Enum LuxSorterBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  LuxSorterBoostFiredNotification *pnotification = new LuxSorterBoostFiredNotification();

  if ( IsValid( notifier ) )
    notifier->Notify(*pnotification);

  _gameLogic->GetGameBoard()->SortBalls();

  return EEaselBoostFireMode::Activated;
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxSorterBoost, PF_Minigames )
