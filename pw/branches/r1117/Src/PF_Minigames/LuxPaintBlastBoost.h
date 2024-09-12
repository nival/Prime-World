#pragma once

#include "LuxBoost.h"

#include "LuxDef.h"
#include "DBEasel.h"

namespace PF_Minigames
{
class LuxBall;

class LuxPaintBlastBoost : public LuxBoost
{
  OBJECT_METHODS(0x9D6BD3C6, LuxPaintBlastBoost);

public:
  LuxPaintBlastBoost( PF_Core::IWorld* _pWorld, Easel * _easel, const nstl::string &_refstrName,long _cooldown,
                     int _accessLevel,int _price,int _radius ) :
  LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_PAINTBLAST, _refstrName, _cooldown, _accessLevel, _price ),
  boostRadius(_radius)
  {

  }

  ~LuxPaintBlastBoost()
  {
    boostRadius = 0;
  }

  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic );

private:
  LuxPaintBlastBoost() {}

  ZDATA_(LuxBoost)
    // internal data
    int boostRadius;
    CPtr<LuxBall> blastBall;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(LuxBoost*)this); f.Add(2,&boostRadius); f.Add(3,&blastBall); return 0; }
};


}