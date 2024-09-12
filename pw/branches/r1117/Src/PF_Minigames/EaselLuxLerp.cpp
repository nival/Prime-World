#include "stdafx.h"

#include "EaselLuxLerp.h"

#include "../System/lerp.h"
#include "LuxBall.h"
#include "LuxPlatform.h"
#include "LuxFallingObject.h"

#include "EaselConstants.h"

#include "ViewBallCoordsConverter.h"

#include "EaselWorldClientConvertHelper.h"

#include "RollCoordsConverter.h"


namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class ILuxViewLerp implementation
//
//////////////////////////////////////////////////////////////////////////
ILuxViewLerp::ILuxViewLerp() : timeElapsed(0.0), timeStep(0.0)
{

}

ILuxViewLerp::~ILuxViewLerp()
{
  timeElapsed = 0.0;
  timeStep    = 0.0;
}

void ILuxViewLerp::IncrementElapsedTime(float _timeInc)
{
  NI_VERIFY(_timeInc >= 0, "time step is less than zero", return);

  if(timeElapsed < timeStep)
  {
    timeElapsed = min(timeElapsed + _timeInc, timeStep);
  }
    
  return;
}

//////////////////////////////////////////////////////////////////////////
//
// class ILuxViewPositionLinearLerp implementation
//
//////////////////////////////////////////////////////////////////////////
ILuxViewPositionLinearLerp::ILuxViewPositionLinearLerp() 
                   : ILuxViewLerp(), 
                     pointA(EASEL_NULL_LERP_VECTOR), pointB(EASEL_NULL_LERP_VECTOR)
{
  
}

ILuxViewPositionLinearLerp::~ILuxViewPositionLinearLerp()
{
  pointA = EASEL_NULL_LERP_VECTOR;
  pointB = EASEL_NULL_LERP_VECTOR;  
}

bool ILuxViewPositionLinearLerp::vLerp(Placement& result)
{
  result = NULLPLACEMENT;

  if(timeStep == 0 || pointA == EASEL_NULL_LERP_VECTOR || pointB == EASEL_NULL_LERP_VECTOR)
    return false;

  if(pointA == pointB)  // object state has not changed at all
  {
    result.pos = pointB;
    return true;
  }

  result.pos = Lerp(pointA,pointB,timeElapsed/timeStep);
  return true;
}

//////////////////////////////////////////////////////////////////////////
//
// class ILuxViewPlacementLinearLerp implementation
//
//////////////////////////////////////////////////////////////////////////
ILuxViewPlacementLinearLerp::ILuxViewPlacementLinearLerp() 
: ILuxViewLerp()
, invalid(true)
, equal(true)
{

}

ILuxViewPlacementLinearLerp::~ILuxViewPlacementLinearLerp()
{
  oldPlacement = NULLPLACEMENT;
  newPlacement = NULLPLACEMENT;
}

bool ILuxViewPlacementLinearLerp::vLerp(Placement& result)
{
  if( invalid )
  {
    result = NULLPLACEMENT;
    return false;
  }

  if(timeStep == 0)
  {
    result = newPlacement;
    return false;
  }

  if(equal)  // object state has not changed at all
  {
    result = newPlacement;
    return true;
  }

  float lerpFactor = timeElapsed / timeStep;

  result.pos = Lerp(oldPlacement.pos, newPlacement.pos, lerpFactor);
  result.rot.Interpolate( oldPlacement.rot, newPlacement.rot, lerpFactor );
  result.scale = Lerp(oldPlacement.scale, newPlacement.scale, lerpFactor);

  return true;
}

void ILuxViewPlacementLinearLerp::SetPlacement(const Placement& _newPlacement, float _timeStep)
{
  timeElapsed = 0;
  timeStep = _timeStep;

  if( _newPlacement.pos == EASEL_NULL_LERP_VECTOR )
    return;

  if( invalid )
    oldPlacement = _newPlacement;
  else
    oldPlacement = newPlacement;

  newPlacement = _newPlacement;

  invalid = !( oldPlacement.IsValid() && newPlacement.IsValid() );
  equal = (oldPlacement.pos == newPlacement.pos);
  equal = equal && (oldPlacement.rot == newPlacement.rot);
  equal = equal && (oldPlacement.scale == newPlacement.scale);
}

void ILuxViewPlacementLinearLerp::ForcePlacement(const Placement& placement)
{
  if( !invalid )
    SetPlacement( placement, 0 );

  SetPlacement( placement, 0 );
}

//////////////////////////////////////////////////////////////////////////
//
// class LuxViewBallLerp implementation
//
//////////////////////////////////////////////////////////////////////////
LuxViewBallLerp::LuxViewBallLerp(LuxBall* refwpBall,
                                 BallCoordsConverter* refHelper)
                : ILuxViewPositionLinearLerp(), wpBall(refwpBall),
                  helperConversion(refHelper)
{

}

LuxViewBallLerp::~LuxViewBallLerp()
{
 
}

bool LuxViewBallLerp::vStep(float deltaTime)
{
  pointA = pointB;

  if ( !IsValid( wpBall ) )
  { 
    timeElapsed = 0;
    timeStep    = 0;
    pointB = CVec3(0, 0, 0);
    return false;
  }
  
  timeElapsed = 0;
  timeStep    = deltaTime;

  pointB = helperConversion->GetClientCoords( wpBall );
  return true;
}

bool LuxViewBallLerp::vLerp(Placement& result)
{
  if(!ILuxViewPositionLinearLerp::vLerp(result))
  {
    return false;
  }

  if ( !IsValid( wpBall ) )
  { 
    pointB = CVec3(0, 0, 0);
    timeElapsed = 0;
    timeStep = 0;
    return false;
  }

  if ( wpBall->State() == BALL_STATE_ON_PLATFORM )
  {
    SVector coords = wpBall->Position();
    result.pos =  helperConversion->GetConverter()->ConvertWorldToClientCoordinates(coords);
  }

  return true;
}


//////////////////////////////////////////////////////////////////////////
//
// class LuxViewPlatformLerp implementation
//
//////////////////////////////////////////////////////////////////////////
LuxViewPlatformLerp::LuxViewPlatformLerp(LuxPlatform* refwpPlatform, EaselWorldClientConvertHelper* refHelper) : 
  ILuxViewPositionLinearLerp(), 
  wpPlatform(refwpPlatform), 
  helperConversion(refHelper)
{

}

LuxViewPlatformLerp::~LuxViewPlatformLerp()
{
  
}

bool  LuxViewPlatformLerp::vLerp(Placement& result)
{
  if( !ILuxViewPositionLinearLerp::vLerp(result) )
    return false;

  result.pos = helperConversion->ConvertWorldToClientCoordinates( wpPlatform->GetPlatformPos() );

  return true;
}


bool  LuxViewPlatformLerp::vStep(float deltaTime)
{
  pointA = pointB;

  SVector newCoord = wpPlatform->GetPlatformPos();
  if(newCoord.x < 0 || newCoord.y < 0)
    pointB = EASEL_NULL_LERP_VECTOR;   
  else  
    pointB = helperConversion->ConvertWorldToClientCoordinates( wpPlatform->GetPlatformPos() );

  timeElapsed = 0;
  timeStep    = deltaTime;

  return true;
}



//////////////////////////////////////////////////////////////////////////
//
// class LuxViewBallLerp implementation
//
//////////////////////////////////////////////////////////////////////////
EaselBallViewLerp::EaselBallViewLerp( LuxBall* refwpBall, BallCoordsConverter* refHelper )
: ILuxViewPlacementLinearLerp()
, wpBall(refwpBall)
, helperConversion(refHelper)
{
//  ResetPosition();
}

EaselBallViewLerp::~EaselBallViewLerp()
{
}

void  EaselBallViewLerp::ResetPosition()
{
  if ( !IsValid( wpBall ) )
    return;

  oldPlacement.pos = CalculatePosition( wpBall );
  oldPlacement.rot = CalculateRotation( wpBall );
  oldPlacement.scale = CalculateScale( wpBall );
  newPlacement = oldPlacement;
  invalid = false;
}

bool  EaselBallViewLerp::vLerp(Placement& result)
{
  if(!ILuxViewPlacementLinearLerp::vLerp(result))
  {
    return false;
  }

  if ( !IsValid( wpBall ) )
  { 
    SetPlacement(NULLPLACEMENT, 0);
    return false;
  }

  if ( wpBall->State() == BALL_STATE_ON_PLATFORM )
  {
    SVector coords = wpBall->Position();
    result.pos =  helperConversion->GetConverter()->ConvertWorldToClientCoordinates(coords);
  }

  return true;
}


bool EaselBallViewLerp::vStep(float deltaTime)
{
  if ( !IsValid( wpBall ) )
  { 
    SetPlacement(NULLPLACEMENT, 0);
    return false;
  }

  Placement newPlacement;

  newPlacement.pos = CalculatePosition( wpBall );
  newPlacement.rot = CalculateRotation( wpBall );
  newPlacement.scale = CalculateScale( wpBall );

  SetPlacement(newPlacement, deltaTime);

  return true;
}

CVec3 EaselBallViewLerp::CalculatePosition( LuxBall* ball )
{
  return helperConversion->GetClientCoords(ball);
}

CQuat EaselBallViewLerp::CalculateRotation( LuxBall* ball )
{
  CVec3 clientDirection = helperConversion->GetClientDirection( ball);
 
  // [@Irakly <neko.lich> Archangelsky@] TODO: 
  static CVec3 eul = CVec3(FP_PI, FP_PI, FP_PI2);

  SHMatrix matrix;
  SetLookAtZ( &matrix, CVec3(0, 0, 0), clientDirection );

  CQuat rotationQuat;
  rotationQuat.FromEulerMatrix( matrix );

  CVec3 eulDecomp;
  rotationQuat.DecompEulerAngles(&eulDecomp.x, &eulDecomp.y, &eulDecomp.z);
  eulDecomp += eul;
  rotationQuat.FromEulerAngles(eulDecomp.x, eulDecomp.y, eulDecomp.z);

  return rotationQuat;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 EaselBallViewLerp::CalculateScale( LuxBall* ball )
{
  int ballSize = abs( ball->Size() );

  static float xyScaleRatio = 1.5f;
  float scaleFactorY = float(ballSize) / EaselConst::Get_BALL_DEF_DIAMETER();
  float scaleFactorX = 1 - (scaleFactorY - 1)/xyScaleRatio;

  return CVec3(scaleFactorX, scaleFactorY, 1);
}

}

BASIC_REGISTER_CLASS( PF_Minigames::ILuxViewLerp )

BASIC_REGISTER_CLASS( PF_Minigames::LuxViewBallLerp )
BASIC_REGISTER_CLASS( PF_Minigames::LuxViewPlatformLerp )
BASIC_REGISTER_CLASS( PF_Minigames::EaselBallViewLerp )
