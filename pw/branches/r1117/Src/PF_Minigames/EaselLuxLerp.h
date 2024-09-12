#pragma once

//#include "EaselWorldClientConvertHelper.h"

namespace PF_Minigames
{
const CVec3 EASEL_NULL_LERP_VECTOR = CVec3(-1,-1,-1);

class LuxBall;
class LuxBall;
class LuxPlatform;
class CLuxFallingObject;
class ScorpionCoordsConverter;
class EaselWorldClientConvertHelper;

//////////////////////////////////////////////////////////////////////////
//
// Easel view data interpolation interface class
//
//////////////////////////////////////////////////////////////////////////
class ILuxViewLerp : public IObjectBase
{
public:
  ILuxViewLerp();
  virtual ~ILuxViewLerp();

  // getters
  float GetElapsedTime() const  { return timeElapsed; };
  float GetStepTime() const     { return timeStep;    };

  // lerp function, must be implemented by children. return false on fail
  virtual bool vLerp(Placement& result) = 0;
  
  // lerp stepper
  virtual bool vStep(float deltaTime) = 0;

  void IncrementElapsedTime(float _timeInc);

protected:
  float timeElapsed; // time elapsed between steps (incremented bu Updates)
  float timeStep;    // step timing
};

//////////////////////////////////////////////////////////////////////////
//
// linear interpolation object for position
// interpolates data on line between dots A and B
//
//////////////////////////////////////////////////////////////////////////
class ILuxViewPositionLinearLerp : public ILuxViewLerp
{
public:
  virtual ~ILuxViewPositionLinearLerp();

  virtual bool vLerp(Placement& result);

protected:  
  ILuxViewPositionLinearLerp();

  CVec3 pointA;
  CVec3 pointB;
};


//////////////////////////////////////////////////////////////////////////
//
// linear interpolation object for placement
// interpolates full placement
//
//////////////////////////////////////////////////////////////////////////
class ILuxViewPlacementLinearLerp : public ILuxViewLerp
{
public:
  virtual ~ILuxViewPlacementLinearLerp();
  virtual bool vLerp(Placement& result);

  void ForcePlacement(const Placement& placement);

protected:  
  ILuxViewPlacementLinearLerp();

  void SetPlacement(const Placement& _newPlacement, float _timeStep);

  Placement oldPlacement;
  Placement newPlacement;
  bool invalid;
  bool equal;
};


//////////////////////////////////////////////////////////////////////////
//
// Easel view ball interpolation
//
//////////////////////////////////////////////////////////////////////////
class BallCoordsConverter;

class LuxViewBallLerp : public ILuxViewPositionLinearLerp, public CObjectBase
{
  OBJECT_BASIC_METHODS( LuxViewBallLerp )
public:
  LuxViewBallLerp( LuxBall* refwpBall, BallCoordsConverter* refHelper);
  ~LuxViewBallLerp();

  virtual bool vStep(float deltaTime);
  virtual bool vLerp(Placement& result);

private:
  LuxViewBallLerp() {}

  // SVector to CVec3
  CPtr<BallCoordsConverter> helperConversion;

  CPtr<LuxBall> wpBall;  // luxor logic ball
};

//////////////////////////////////////////////////////////////////////////
//
// Easel platform interpolation class
//
//////////////////////////////////////////////////////////////////////////
class LuxViewPlatformLerp : public ILuxViewPositionLinearLerp, public CObjectBase
{
  OBJECT_BASIC_METHODS( LuxViewPlatformLerp )

public:
  LuxViewPlatformLerp(LuxPlatform *refwpPlatform, EaselWorldClientConvertHelper* refHelper);
  ~LuxViewPlatformLerp();

  virtual bool vLerp(Placement& result);
  virtual bool vStep(float deltaTime);

private:
  LuxViewPlatformLerp() {}

  // SVector to CVec3
  //EaselWorldClientConvertHelper helperConversion;
  CPtr<EaselWorldClientConvertHelper> helperConversion;

  CPtr<LuxPlatform> wpPlatform;  // luxor platform
};

//////////////////////////////////////////////////////////////////////////
//
// Easel drop interpolation class
//
//////////////////////////////////////////////////////////////////////////
class EaselBallViewLerp : public ILuxViewPlacementLinearLerp, public CObjectBase
{
  OBJECT_BASIC_METHODS( EaselBallViewLerp )

public:
  EaselBallViewLerp( LuxBall* refwpBall, BallCoordsConverter* refHelper);
  ~EaselBallViewLerp();

  virtual bool vLerp(Placement& result);
  virtual bool vStep(float deltaTime);

  void  ResetPosition();

private:
  EaselBallViewLerp() {}

  // SVector to CVec3
  CPtr<BallCoordsConverter> helperConversion;

  CVec3 CalculatePosition( LuxBall* ball );
  CQuat CalculateRotation( LuxBall* ball );
  CVec3 CalculateScale( LuxBall* ball );

  CPtr<LuxBall> wpBall;  // luxor logic ball

};

}
