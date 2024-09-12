#pragma once

#include "Camera.h"
#include "CameraController.h"
#include "CameraInputModifier.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	class FreeCameraController: public ICameraController
	{
	private:
		OBJECT_BASIC_METHODS(FreeCameraController);

		struct CameraSettings
		{
			float minRod, maxRod, minPitch, maxPitch, minYaw, maxYaw;
			float attenuation;
			float minHeight;
			float scrollZoomAcceleration;
			float scrollSpeed;
			float zoomAcceleration;
			float zoomSpeed;
			float yawSpeed;
			float yawZoomAcceleration;
			float pitchSpeed;

			CameraSettings()
				: minRod( 0.0f ), maxRod( 1000.f ), minPitch( -FP_PI2 ), maxPitch( +FP_PI2 ), minYaw( 0.f ), maxYaw( 0.f ),
				attenuation(1), minHeight(4), scrollZoomAcceleration(1.2f), scrollSpeed( 1.0f ), zoomAcceleration( 5.f ),
				zoomSpeed( 0.1f ), yawSpeed( 1 ), pitchSpeed( 1 ), yawZoomAcceleration(1)
			{}
		};

		int catchMouseMoves;
		Input::CommandReference mouse_move;
    
    NScene::SCameraPosition savedPosition;
    bool bSavedPosition;

    bool complete;
    bool finalizing;

	protected:
    CameraInputModifier inputModifier;


    CPtr<ICamera> pCamera;
		CameraSettings settings;
    NScene::SCameraPosition forcedPosition;
    bool bForcedPosition;

  public:
		FreeCameraController();

    void SetManual( const CVec3& rotation, const CVec3& position, const SCameraPosition* saved = NULL );
    void Shutdown( const SCameraPosition& pos );
    void Shutdown();

		virtual const bool IsEffect() const { return false; }
		virtual const bool IsActive() const { return !complete; }

		virtual void Update( SCameraPosition* pWantedPos, const SCameraPosition& currentPos, const SCameraPosition& wantedPos, Time timeDiff );
		virtual bool ProcessEvent( const Input::Event &	_eEvent );

	private:
		virtual void SetCamera( ICamera* _pCamera ) { pCamera = _pCamera; }
	};

	inline float ApplyLimits( float fValue, float fMin, float fMax )
	{
		if ( fMin >= fMax )
			return fValue;
		return Clamp( fValue, fMin, fMax );
	}

}
