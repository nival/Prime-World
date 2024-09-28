#pragma once

#include "LuxBoost.h"

#include "LuxDef.h"
#include "DBEasel.h"

namespace PF_Minigames
{

class LuxBall;

class LuxJokerBoost : public LuxBoost
{
  OBJECT_METHODS(0x9D6BD3C4, LuxJokerBoost);

public:
  LuxJokerBoost( PF_Core::IWorld* _pWorld, Easel * _easel, 
                const nstl::string & _refstrName, long _cooldown,
                int _accessLevel, int _price )
  : LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_JOKER, _refstrName, _cooldown, _accessLevel, _price )
  {

  }

  ~LuxJokerBoost() {};

  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic );

private:
  LuxJokerBoost() {}

  CPtr<LuxBall> jokerBall;
};

}