#include "stdafx.h"
/*
#include "WarCraftCameraController.h"

namespace NGameX
{
	WarCraftCameraController::WarCraftCameraController( NScene::IScene* pScene )
		: AdventureCameraController( pScene )
		, locked( false )
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WarCraftCameraController::SetObservedObject( IH6ClientObjectBase* pObject )
	{
		const bool result = AdventureCameraController::SetObservedObject( pObject );
		const float unzoomed = 1.f;
		SetCameraZoom( unzoomed );
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	namespace
	{
		inline float ApplyLimits( float value, float min, float max )
		{
			return min >= max ? value : Clamp( value, min, max );
		}

		float minYaw = -70.f;
		float maxYaw = 70.f;
	
		float angularVelocity = 1.f;

		REGISTER_DEV_VAR( "camera_yaw_min", minYaw, STORAGE_GLOBAL );
		REGISTER_DEV_VAR( "camera_yaw_max", maxYaw, STORAGE_GLOBAL );
		REGISTER_DEV_VAR( "camera_angular_velocity", angularVelocity, STORAGE_GLOBAL );
	}

	void WarCraftCameraController::UpdateSettings()
	{
		AdventureCameraController::UpdateSettings();

		AdventureCameraController::settings.minYaw = ToRadian( minYaw );
		AdventureCameraController::settings.maxYaw = ToRadian( maxYaw );
		settings.angularVelocity = angularVelocity;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WarCraftCameraController::ApplyOrientationModifier( NScene::SCameraPosition& position )
	{
		const AdventureCameraController::CameraSettings& settings = AdventureCameraController::settings;

		// calculate wanted orientation
		const float deltaYaw = inputModifier.GetDeltaYaw();
		const float deltaZoom = inputModifier.GetDeltaZoom() * settings.zoomFactor * ( fabs( position.fRod ) + 2.f ) / 2.f;
		position.fRod = ApplyLimits( position.fRod + deltaZoom, settings.minRod, settings.maxRod );

		// interpolate pitch now
		const float t = 1.f - ( position.fRod - settings.minRod ) / ( settings.maxRod - settings.minRod );
		position.fPitch = ( settings.maxPitch - settings.minPitch ) * t + settings.minPitch;
		position.fYaw = ApplyLimits( position.fYaw - settings.rotationFactor * deltaYaw, settings.minYaw, settings.maxYaw );

		if( inputModifier.mouse_locked.IsActive() )
			locked = true;

		//if( !inputModifier.mouse_unlocked.IsActive() )
		//	locked = false;

		return deltaZoom != 0.f || deltaYaw != 0.f || inputModifier.touched || locked;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CVec3 WarCraftCameraController::CalculateAngularAcceleration( const NScene::SCameraPosition& currentPosition, NScene::Time dt )
	{
		const float baseAngle = 0.f;
		if( currentPosition.fYaw != baseAngle )
		{
			// estimate time
			const float dPhi = baseAngle - currentPosition.fYaw;
			NScene::Time time = dPhi / settings.angularVelocity;
			if( time > dt ) time = dt;
			else if( time < -dt ) time = -dt;
			return CVec3( 0.f, settings.angularVelocity * time, 0.f );
		}
		else
			return VNULL3;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WarCraftCameraController::ModifyOrientation( NScene::SCameraPosition& position, const CVec3& dPhi )
	{
		if( IsAlmostZero( dPhi ) )
		{
			position.fYaw += dPhi.y;
		}
	}
}
*/