#pragma once
/*
#include "AdventureCameraController.hpp"

namespace NGameX
{
	//camera at the adventure map like in war craft 3
	class WarCraftCameraController
		: public AdventureCameraController
	{
	public:
		struct CameraSettings : AdventureCameraController::CameraSettings
		{
			float angularVelocity;
			CameraSettings()
				: angularVelocity( 1.f )
			{
				minYaw = -30.f;
				maxYaw = 30.f;
			}
		};

	private:
		CameraSettings settings;
		bool locked;

	public:
		WarCraftCameraController( NScene::IScene* );
		bool SetObservedObject( IH6ClientObjectBase* );

	protected:
		OBJECT_BASIC_METHODS( WarCraftCameraController );
		WarCraftCameraController() {}

		bool ApplyOrientationModifier( NScene::SCameraPosition& position );
		void ModifyOrientation( NScene::SCameraPosition& position, const CVec3& dPhi );

		CVec3 CalculateAngularAcceleration( const NScene::SCameraPosition& currentPosition, NScene::Time dt );

		// update settings
		void UpdateSettings();
	};
}
*/