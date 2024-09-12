#pragma once

#include "EaselNotifications.h"
#include "DBEasel.h"

namespace PF_Minigames
{

class LuxChainElementExplodedNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0x9763CB40, LuxChainElementExplodedNotification);
public:

  LuxChainElementExplodedNotification()
  : EaselNotifier::tNotification()
  , pointExplosion(0,0)
  , colorExplosion(NDb::COLOR_ANY)
  , explodedBallsNum(0) 
  {
    
  }

  // explosion params
  SVector     pointExplosion;
  NDb::EColor colorExplosion;
  int         explodedBallsNum;

};

} // namespace PF_Minigames
