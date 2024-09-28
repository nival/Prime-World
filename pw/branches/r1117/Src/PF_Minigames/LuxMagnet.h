#pragma once

#include "../PF_Core/WorldObject.h"

#include "EaselConstants.h"
#include "LuxCollidable.h"

namespace NDb
{
  enum EColor;
}

namespace PF_Minigames
{

class LuxBoost;
class LuxGameLogic;
class CPainterPoint;

class LuxMagnet : public ICollidable, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS(0x9D6BC441, LuxMagnet);

public:
  LuxMagnet( PF_Core::IWorld* _pWorld, int _scanTime,int _R1,int _R2, int _numBalls, LuxBoost * _magnetBoost );
  ~LuxMagnet();

  void Step( int deltaTime,  LuxGameLogic* _gameLogic );

  // getter methods
  int GetScanTime()       const { return scanTime; };
  int GetRadiusInternal() const { return radiusR1*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER(); };
  int GetRadiusExternal() const { return radiusR2*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER(); };

  // from ICollidable
  virtual const SVector & Position() const;
  virtual int         Size() const { return EaselConst::Get_BALL_DEF_DIAMETER(); }
  virtual int         Speed() const { return 0; }
  virtual const SVector & Direction() const { static SVector dir(0, -1); return dir; }

  virtual bool        Hit();
  virtual bool IsExhausted() const;

  // magnet methods
  NDb::EColor GetColor() const;

  void SetPainterPoint( CPainterPoint* _point ) { colorPoint = _point; }

  LuxBoost * GetMagnetBoost() const { return magnetBoost; }

private:
  LuxMagnet() {}

  void Complete();
  void ProcessMagnetOperation( LuxGameLogic* _gameLogic );

  ZDATA_(PF_Core::WorldObjectBase)
  ZNOPARENT(ICollidable)
  // internal data
  int scanTime;
  int radiusR1;
  int radiusR2;
  int numBallsToEat;
  int ballsEaten;      // balls already consumed by magnet  
  bool killed;
  bool complete;

  CPtr<LuxBoost> magnetBoost;
  CPtr<CPainterPoint> colorPoint;

  int magnetTimer;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&scanTime); f.Add(3,&radiusR1); f.Add(4,&radiusR2); f.Add(5,&numBallsToEat); f.Add(6,&ballsEaten); f.Add(7,&killed); f.Add(8,&complete); f.Add(9,&magnetBoost); f.Add(10,&colorPoint); f.Add(11,&magnetTimer); return 0; }
};

}