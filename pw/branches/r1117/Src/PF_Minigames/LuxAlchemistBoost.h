#ifndef LUXALCHEMISTBOOST_H_INCLUDED
#define LUXALCHEMISTBOOST_H_INCLUDED

#include "LuxBoost.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxAlchemistBoost : public LuxBoost
{
  OBJECT_METHODS(0x9D6BD3C0, LuxAlchemistBoost);

public:
  LuxAlchemistBoost( PF_Core::IWorld* _pWorld, Easel * _easel, const nstl::string &_refstrName, long _cooldown, int _accessLevel,
                      int _price, int _alchemistTime, int _additionalPaint, float _paintMult );

  ~LuxAlchemistBoost() {}

  virtual bool IsActive() const { return isActive; }
  virtual float ActivityProgress() const;

  virtual void Abort();

  virtual void OnUnusedPaint( LuxGameLogic* _gameLogic, const SVector& explosionPoint, NDb::EColor explosionColor, int explodedBallsNum );

private:
  LuxAlchemistBoost() {}

  ZDATA_(LuxBoost)
  // boost fired flag
  bool isActive;

  // internal data
  float alchemistTimeLeft;
  float alchemistTime;

  int unusedPaintAmount;

  int additionalPaint;
  float paintMult;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(LuxBoost*)this); f.Add(2,&isActive); f.Add(3,&alchemistTimeLeft); f.Add(4,&alchemistTime); f.Add(5,&unusedPaintAmount); f.Add(6,&additionalPaint); f.Add(7,&paintMult); return 0; }
protected:

  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic );
};

} //namespace PF_Minigames

#endif //LUXALCHEMISTBOOST_H_INCLUDED
