#include "stdafx.h"
#include "SplineCameraController.h"
#include "Scene\Camera.h"
#include "System\lerp.h"


namespace PF_Core
{
const float CAMERA_FPS = 180.f;

SplineCameraController::SplineCameraController( bool correctTiming ) :
  firstUpdate(true),
  curTime(0),
  totalTime(0),
  saveRod(0.f),
  lastPos(0.f,0.f,0.f),
  velocity(0.f),
  lastRelativeCurTime(0.f),
  deltaReminder(0.f),
  finalizing(false),
  scaleCameraFPS(1.f / CAMERA_FPS )
{
  pThis = this;
  placementSpline.SetTimingCorrection( correctTiming );
}


  
void SplineCameraController::Update( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff )
{
  if(finalizing)
    return;

  float commonDelta = timeDiff + deltaReminder;

  deltaReminder = fmod( commonDelta, scaleCameraFPS );
  int numSubSteps = Float2Int( floor( commonDelta * CAMERA_FPS ) );

  *pResultPos = currentPos;
  NScene::SCameraPosition const *actualWantedPos = &wantedPos;

  for (int i = 0; i < numSubSteps; ++i)
  {
    if ( UpdateInternal( pResultPos, *pResultPos, *actualWantedPos, scaleCameraFPS ) )
      return;
  }
  //DebugTrace("dt= %4.3d, cur= %4.3d", commonDelta, curTime );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SplineCameraController::UpdateInternal( SCameraPosition * pWantedPos, const SCameraPosition & currentPos, const SCameraPosition & wantedPos, Time timeDiff )
{
  CVec3 curPosition;
  CQuat curRotation;

  curTime += timeDiff;

  const float timeRelative = SmoothDampStepFactor( curTime / totalTime );
  const float diffRelative = ( timeRelative * totalTime - lastRelativeCurTime );
  lastRelativeCurTime = timeRelative * totalTime;

  if ( placementSpline.Move( diffRelative * velocity, curPosition, curRotation, 3000 ) )
  {
    pThis = 0; //More safe delete this;
    return true;
  }

  curRotation.Normalize();

  curRotation.DecompEulerAngles( &pWantedPos->fYaw, &pWantedPos->fPitch, &pWantedPos->fRoll );

  CVec3 camDir = pWantedPos->GetCameraDir();
  Normalize( &camDir );

  lastPos = curPosition;

  pWantedPos->vAnchor = curPosition + camDir * pWantedPos->fRod;

  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SplineCameraController::Init( const vector<CVec3>& positions, const vector<CVec3>& rotations, Time _totalTime )
{
  const int size = positions.size();

  NI_ASSERT( size == rotations.size() && size > 1 ,"bad size of arrays")
      
  curTime = 0.f;
  lastRelativeCurTime = 0.f;
  totalTime = _totalTime;
  firstUpdate = true;
  finalizing = false;

  placementSpline.Setup( positions, rotations, 0.f, 3000 );
  placementSpline.SetToBegin();
  velocity = placementSpline.GetTotalLength() / totalTime;
}

void SplineCameraController::Init( const vector<CVec3>& positions, const vector<CVec3>& rotations, Time _totalTime, const vector<float>& tensions )
{
  const int size = positions.size();

  NI_ASSERT( size == rotations.size() && size == tensions.size() && size > 1 ,"bad size of arrays")

  curTime = 0.f;
  lastRelativeCurTime = 0.f;
  totalTime = _totalTime;
  firstUpdate = true;
  finalizing = false;

  placementSpline.Setup( positions, rotations, 0.f, 3000 );
  placementSpline.SetToBegin();
  velocity = placementSpline.GetTotalLength() / totalTime;
}

void SplineCameraController::Shutdown()
{
  finalizing = true;
  totalTime = 0.0f;
  velocity = 0.0f;

  pThis = 0;
}

}
