#pragma once

#include "LuxBoost.h"

#include "LuxDef.h"
#include "DBEasel.h"

namespace PF_Minigames

{
//////////////////////////////////////////////////////////////////////////
//
// sorter boost class
//
//////////////////////////////////////////////////////////////////////////
class LuxSorterBoost : public LuxBoost
{
  OBJECT_METHODS(0x9D6BD3C7, LuxSorterBoost);

public:
  LuxSorterBoost( PF_Core::IWorld* _pWorld, Easel * _easel, 
                 const nstl::string & _refstrName, long _cooldown,
                 int _accessLevel, int _price ) :
  LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_SORTER, _refstrName, _cooldown, _accessLevel, _price ) {};

  ~LuxSorterBoost() {};

private:
  LuxSorterBoost() {}

protected:

  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic ) {}
};

}