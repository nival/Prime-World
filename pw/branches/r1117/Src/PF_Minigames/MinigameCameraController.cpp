#include "stdafx.h"

#include "../Scene/Camera.h"
#include "../Scene/SceneObject.h"

#include "MinigameCameraController.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

namespace 
{
  const float CameraFPS = 100.f;

  const float springK = 30.0f;
  const float dampingK = 10.0f;
  const float angularTreshold = ToRadian( 0.3f );

  const float linearSpringK = 30.0f;
  const float linearDampingK = 10.0f;
  const float linearTreshold = 0.03f;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameCameraController::MinigameCameraController() :
  deltaReminder(0.f),
  lockTarget(false),
  positionInterpolator( linearDampingK, linearSpringK, linearTreshold ),
  yawInterpolator( dampingK, springK, angularTreshold ),
  pitchInterpolator( dampingK, springK, angularTreshold ),
  rollInterpolator( dampingK, springK, angularTreshold ),
  rodInterpolator( linearDampingK, linearSpringK, linearTreshold ),
  fovInterpolator( dampingK, springK, angularTreshold )
{
  wantedPosition.fPitch = -0.7f;
  wantedPosition.fRod = 12.f;
  wantedPosition.fRoll = 0.0;
  wantedPosition.fYaw = -FP_PI2;

  target = VNULL3;
  wantedFov = 70.f;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MinigameCameraController::ProcessEvent( const Input::Event& eEvent )
{
  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::EnableInterpolation( bool enable )
{
  positionInterpolator.Enable( enable );
  yawInterpolator.Enable( enable );
  pitchInterpolator.Enable( enable );
  rollInterpolator.Enable( enable );
  rodInterpolator.Enable( enable );
  fovInterpolator.Enable( enable );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::ChangeCamera( const NDb::ViewCamera& cameraDB )
{
  basePosition.fPitch = ToRadian( cameraDB.pitch );
  basePosition.fRoll  = ToRadian( cameraDB.roll );
  basePosition.fYaw   = ToRadian( cameraDB.yaw );

  basePosition.fRod   = cameraDB.rod;

  wantedFov = cameraDB.fov;

  basePosition.vAnchor = cameraDB.anchor;

  RecalculateWantedPosition();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::ChangeCamera( const NScene::SCameraPosition& position )
{
  basePosition = position; 

  RecalculateWantedPosition();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::ApplyResolutionModifcators()
{
  NI_VERIFY( IsValid( pCamera ), "MinigameCameraController, camera is invalid", return );

  static const float baseCoef = 1024.f / 768.f;
  float rodCoef = pCamera->GetScreenWidth() / ( pCamera->GetScreenHeight() * baseCoef );

  NI_VERIFY(rodCoef > 0, "MinigameCameraController: rod coefficient is less than zero", rodCoef = 1.0f);

  if ( rodCoef < 1.f )
    rodCoef = 1 / rodCoef;

  basePosition.fRod *= rodCoef;

  RecalculateWantedPosition();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::SCameraPosition MinigameCameraController::GetCameraParams() const
{
  return basePosition;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::Update( NScene::SCameraPosition* pNewPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& dummy, NScene::Time timeDiff )
{
  if ( IsNearPositions( currentPos, wantedPosition ) )
    return;

  float commonDelta = timeDiff + deltaReminder;

  deltaReminder = fmod( commonDelta, 1.f / CameraFPS );
  int numSubSteps = Float2Int( floor( commonDelta * CameraFPS ) );

  *pNewPos = currentPos;

  //FIXME: не уверен, что это все необходимо, возможно currentPos не отличается сохраненных значений
  pitchInterpolator.Set( currentPos.fPitch );
  yawInterpolator.Set( currentPos.fYaw );
  rollInterpolator.Set( currentPos.fRoll );
  rodInterpolator.Set( currentPos.fRod );
  positionInterpolator.Set( currentPos.vAnchor );
  fovInterpolator.Set( pCamera->GetFOV() );

  //DebugTrace( "Cam pos: %7.3f, %7.3f, %7.3f,  vel: %7.3f, %7.3f, %7.3f,  yaw = %7.3f,  fov = %7.3f",
  //  positionInterpolator.Get().x, positionInterpolator.Get().y, positionInterpolator.Get().z,
  //  positionInterpolator.Velocity().x, positionInterpolator.Velocity().y, positionInterpolator.Velocity().z,
  //  pNewPos->fYaw, fovInterpolator.Get() );

  for (int i = 0; i < numSubSteps; ++i)
    UpdateStep( pNewPos, *pNewPos, *pNewPos, 1.f / CameraFPS );

  pNewPos->fPitch = pitchInterpolator.Get();
  pNewPos->fYaw = yawInterpolator.Get();
  pNewPos->fRod = rodInterpolator.Get();
  pNewPos->fRoll = rollInterpolator.Get();
  pNewPos->vAnchor = positionInterpolator.Get();

  pCamera->SetFOV( fovInterpolator.Get() );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::UpdateStep( NScene::SCameraPosition* pNewPos, const NScene::SCameraPosition& currentPos
  , const NScene::SCameraPosition&dummy, NScene::Time timeDiff )
{
  pitchInterpolator.Update( wantedPosition.fPitch, timeDiff );
  yawInterpolator.Update( wantedPosition.fYaw, timeDiff );
  rollInterpolator.Update( wantedPosition.fRoll, timeDiff );
  rodInterpolator.Update( wantedPosition.fRod, timeDiff );
  positionInterpolator.Update( wantedPosition.vAnchor, timeDiff );
  fovInterpolator.Update( wantedFov, timeDiff );

  // 		CVec3 cameraForwardDir;
  // 		CQuat q = CQuat( pNewPos->fYaw, V3_AXIS_Z ) * CQuat( pNewPos->fPitch, V3_AXIS_X )* CQuat( pNewPos->fRoll, V3_AXIS_Y );
  // 		q.GetYAxis( &cameraForwardDir );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::SetTarget( const Placement& _target )
{
  if(lockTarget)
  {
    return;
  }

  target = _target;

  RecalculateWantedPosition();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameCameraController::RecalculateWantedPosition()
{
  wantedPosition = basePosition;

  // apply target
  float targetPitch = 0;
  float targetRoll = 0;
  float targetYaw = 0;
  target.rot.DecompEulerAngles(&targetYaw, &targetPitch, &targetRoll);

  wantedPosition.fPitch += targetPitch;
  wantedPosition.fRoll += targetRoll;
  wantedPosition.fYaw += targetYaw;

  target.Transform( basePosition.vAnchor, wantedPosition.vAnchor );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MinigameCameraController::IsCameraInWantedPosition() const
{
  NI_VERIFY( IsValid( pCamera ), "MinigameCameraController, camera is invalid", return true);

  NScene::SCameraPosition currentCameraPosition;
  pCamera->GetPosition(&currentCameraPosition);

  return IsNearPositions( currentCameraPosition, wantedPosition );
}

bool MinigameCameraController::IsNearPositions(const NScene::SCameraPosition& first, const NScene::SCameraPosition& second) const
{
  return IsAlmostZero( first.fPitch - second.fPitch, first.fYaw - second.fYaw )
    && IsAlmostZero( first.fRoll - second.fRoll, first.fRod - second.fRod)
    && IsAlmostZero( first.vAnchor - second.vAnchor );
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::MinigameCameraController)