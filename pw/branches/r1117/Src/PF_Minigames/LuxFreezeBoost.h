#pragma once

#include "LuxBoost.h"

#include "LuxDef.h"

#include "DBEasel.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
class LuxFreezeBoost : public LuxBoost
{
  OBJECT_METHODS(0x9D6BD3C2, LuxFreezeBoost);

public:
  LuxFreezeBoost( PF_Core::IWorld* _pWorld, Easel * _easel, 
                 const nstl::string &_refstrName,long _cooldown,
                 int _accessLevel,int _price,int _freezetime )
  : LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_FREEZE, _refstrName, _cooldown, _accessLevel, _price )
  , freezeTime(_freezetime*1000)
  , fIsFired(false)
  , inFreezeTime(0.0)
  {
    NI_DATA_ASSERT(freezeTime >= 0,"FreezeBoost: freeze time parameter is invalid");
  }

  ~LuxFreezeBoost() {}

private:
  LuxFreezeBoost() {}

  ZDATA_(LuxBoost)
  // boost fired flag
  bool  fIsFired;
  float inFreezeTime;    //  time spent being frozen

  // internal data
  float freezeTime;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(LuxBoost*)this); f.Add(2,&fIsFired); f.Add(3,&inFreezeTime); f.Add(4,&freezeTime); return 0; }

protected:
  // boost fire method
  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime, LuxGameLogic* _gameLogic );
};

}