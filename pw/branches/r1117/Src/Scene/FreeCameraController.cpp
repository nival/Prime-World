#include "stdafx.h"
#include "FreeCameraController.hpp"
#include "../System/MathTools.h"

namespace NScene
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	FreeCameraController::FreeCameraController() 
		: catchMouseMoves( 0 )
		, mouse_move( "win_mouse_move" )
    , bSavedPosition(false)
    , bForcedPosition(false)
    , complete(false)
    , finalizing(false)
	{
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void FreeCameraController::SetManual( const CVec3& rotation, const CVec3& position, const SCameraPosition* saved /*= NULL*/ )
  {
    NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return; );

    NScene::SCameraPosition pos;
    pCamera->GetPosition(&pos);

    pos.fYaw = rotation.z;
    pos.fPitch = rotation.x;
    pos.fRoll = rotation.y;

    pos.ConvertFromDegToRad();

    CVec3 camDir = pos.GetCameraDir();
    Normalize( &camDir );
    pos.vAnchor = position + camDir * pos.fRod;

    pCamera->SetPosition( pos );
    // store this position to apply it on Update() as well
    if( saved && !bSavedPosition )
    {
      savedPosition = *saved;
      bSavedPosition = true;
    }

    forcedPosition = pos;
    bForcedPosition = true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void FreeCameraController::Shutdown( const SCameraPosition& pos )
  {
    forcedPosition = pos;
    finalizing = true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void FreeCameraController::Shutdown()
  {
    forcedPosition = savedPosition;
    finalizing = true;
  }
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool FreeCameraController::ProcessEvent( const Input::Event& eEvent )
	{
		if ( mouse_move.ProcessEvent( eEvent ) )
		{
			if ( catchMouseMoves > 0 )
			{
				--catchMouseMoves;
				return true;
			}
			return false;
		}

		return inputModifier.ProcessEvent( eEvent );
	}

  static float s_camera_forward_speed = 10.0, s_camera_side_speed = 10.0, s_camera_rotate_speed = 2.0;
  REGISTER_DEV_VAR( "free_camera_forward", s_camera_forward_speed, STORAGE_NONE );
  REGISTER_DEV_VAR( "free_camera_side", s_camera_side_speed, STORAGE_NONE );
  REGISTER_DEV_VAR( "free_camera_rotation", s_camera_rotate_speed, STORAGE_NONE );

  static bool s_camera_egocentric = false;
  REGISTER_DEV_VAR( "free_camera_egocentric", s_camera_egocentric, STORAGE_NONE );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void FreeCameraController::Update( SCameraPosition* pWantedPos, const SCameraPosition& currentPos, const SCameraPosition& wantedPos, Time timeDiff )
	{
		ASSERT( IsValid( pCamera ) );

    if( finalizing )
    {
      *pWantedPos = forcedPosition;
      complete = true;
      finalizing = false;
      return;
    }

		*pWantedPos = wantedPos;

    if (bForcedPosition)
    {
      *pWantedPos = forcedPosition;
      bForcedPosition = false;
      return;
    }

    const float fMousePitchD = inputModifier.mouse_pitch.RetrieveDelta();
		const float fMouseYawD = inputModifier.mouse_yaw.RetrieveDelta();
		const float fMouseFwdD = inputModifier.mouse_fwd.RetrieveDelta();
		const float fMouseStrafeD = inputModifier.mouse_strafe.RetrieveDelta();
		const float fMouseZoomD = inputModifier.mouse_zoom.RetrieveDelta();

		const float fMouseSumD = fabs(fMousePitchD) + fabs(fMouseYawD) + fabs(fMouseFwdD) + fabs(fMouseStrafeD) + fabs(fMouseZoomD);
		if ( fMouseSumD > 0 )
			catchMouseMoves = 2;

		float fPitchD  = ( s_camera_rotate_speed * inputModifier.pitch.RetrieveDelta() + fMousePitchD );
		float fYawD    = ( s_camera_rotate_speed * inputModifier.yaw.RetrieveDelta() + fMouseYawD );
		float fFwdD    = ( s_camera_forward_speed * inputModifier.fwd.RetrieveDelta() + fMouseFwdD );
		float fUpwdD   = ( s_camera_forward_speed * inputModifier.upward.RetrieveDelta()                 );
		float fStrafeD = ( s_camera_side_speed * inputModifier.strafe.RetrieveDelta() + fMouseStrafeD );
		float fZoomD   = ( s_camera_forward_speed * inputModifier.zoom.RetrieveDelta() + fMouseZoomD );

		pWantedPos->fPitch = ApplyLimits( wantedPos.fPitch + fPitchD, settings.minPitch, settings.maxPitch );
		pWantedPos->fYaw = ApplyLimits( wantedPos.fYaw - fYawD, settings.minYaw, settings.maxYaw );
		pWantedPos->fRoll = wantedPos.fRoll - s_camera_rotate_speed * inputModifier.roll.RetrieveDelta();
		float fUpwd = fUpwdD;
		float fFwd = fFwdD;
		float fStrafe = -fStrafeD;
		float fZoom = fZoomD;

		CVec3 vForwardDir = GetEulerYAxis( pWantedPos->fYaw, pWantedPos->fPitch, pWantedPos->fRoll );
		CVec3 vStrafeDir = GetEulerXAxis( pWantedPos->fYaw, pWantedPos->fPitch, pWantedPos->fRoll );
    CVec3 vUpwardDir = GetEulerZAxis( pWantedPos->fYaw, pWantedPos->fPitch, pWantedPos->fRoll );

    // zoom
		pWantedPos->fRod += fZoom;

    if ( s_camera_egocentric )
    { //Little hakka to disable camera anchor
      pWantedPos->vAnchor = pWantedPos->vAnchor - vForwardDir * pWantedPos->fRod;
			pWantedPos->fRod = 0;
    }
    else
    {
		  if ( pWantedPos->fRod < 0)
		  {
			  pWantedPos->vAnchor = pWantedPos->vAnchor - vForwardDir * pWantedPos->fRod;
			  pWantedPos->fRod = 0;
		  }
		  pWantedPos->fRod = ApplyLimits( pWantedPos->fRod, settings.minRod, settings.maxRod );
    }

		// upward
		if ( fabs2( vUpwardDir ) > 0 )
		{
			Normalize( &vUpwardDir );
			pWantedPos->vAnchor += vUpwardDir * fUpwd;
		}

		// forward
		vForwardDir.z = 0;
		if ( fabs2( vForwardDir ) > 0 )
		{
			Normalize( &vForwardDir );
			pWantedPos->vAnchor += vForwardDir * fFwd;
		}

		// strafe
		vStrafeDir.z = 0;
		if ( fabs2( vStrafeDir ) > 0 )
		{
			Normalize( &vStrafeDir );
			pWantedPos->vAnchor -= vStrafeDir * fStrafe;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ICameraController *CreateFreeCameraController()
	{
		return new FreeCameraController();
	}

}