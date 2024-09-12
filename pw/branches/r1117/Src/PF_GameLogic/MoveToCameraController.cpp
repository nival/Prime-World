#include "stdafx.h"
#include "MoveToCameraController.h"
#include "Scene\Camera.h"


namespace PF_Core
{

MoveToCameraController::MoveToCameraController()
{
  pThis = this;
  curTime = totalTime = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveToCameraController::Update( SCameraPosition * pWantedPos, const SCameraPosition & currentPos, const SCameraPosition & wantedPos, Time timeDiff )
{
  if( curTime >= totalTime )
  {
    pThis = 0; //More safe delete this;
    return;
  }

  curTime += timeDiff;
  const float timeRelative = min( SmoothDampStepFactor( curTime / totalTime ), 1.0f );
  
  pWantedPos->vAnchor = positionInterpolator.Update( timeRelative );
  pWantedPos->fYaw    = yawInterpolator.Update( timeRelative );
  pWantedPos->fPitch  = pitchInterpolator.Update( timeRelative );
  pWantedPos->fRoll   = rollInterpolator.Update( timeRelative );
  pWantedPos->fRod    = rodInterpolator.Update( timeRelative );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveToCameraController::Init( const SCameraPosition &from, const SCameraPosition &to, Time totalTime_ )
{
  curTime = 0;
  totalTime = totalTime_;
  
  positionInterpolator.Init( from.vAnchor, to.vAnchor );
  yawInterpolator.Init( from.fYaw, to.fYaw );
  pitchInterpolator.Init( from.fPitch, to.fPitch );
  rollInterpolator.Init( from.fRoll, to.fRoll );
  rodInterpolator.Init( from.fRod, to.fRod );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveToCameraController::Init( const SCameraPosition &from, const NDb::ViewCamera &to, Time totalTime )
{
  SCameraPosition toRes;

  toRes.fPitch  = ToRadian( to.pitch );
  toRes.fRoll   = ToRadian( to.roll );
  toRes.fYaw    = ToRadian( to.yaw );
  toRes.fRod    = to.rod;
  toRes.vAnchor = to.anchor;
  
  Init( from, toRes, totalTime );
}

}