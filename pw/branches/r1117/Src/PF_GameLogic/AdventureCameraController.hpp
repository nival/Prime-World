#pragma once

#include "../Scene/CameraController.h"
#include "../Scene/Camera.h"
#include "../Scene/CameraInputModifier.h"
#include "../Scene/FreeCameraController.hpp"


namespace NScene 
{ 
  _interface IScene; 
}

namespace NDb
{
  struct AdventureCameraSettings;
}

namespace NWorld
{
  class PFBaseUnit;
}

namespace NGameX
{
	class PFClientBaseMovingUnit;
	class PFClientBaseUnit;
  
	/**
	 *	camera at the adventure map
	 *	design can be seen at http://SITE
	 */
	class AdventureCameraController
		: public NScene::ICameraController
	{
	public:
		typedef NScene::Time Time;

    struct CameraSettings
		{
      //NDb::DampSmoothing
      float dampTimeObserv;
      float dampTimeMove;
      float anchorShiftObserv;
      float firstJumpTime;
      float zoomFactorMove;
      float zoomFactorObserv;
      float maxSpeed;
      float timeToMaxSpeed;
      float projCorretionShiftObservMaxZoom;
      float projCorretionShiftObservMinZoom;

			/** limits */
			float minRod, maxRod, minPitch, maxPitch, minYaw, maxYaw, centerYaw;

      float maxZoomFactor;

      /** periods */
      float horRotPeriod, vertRotPeriod;
      float horFreezeTime, horFreezeTimeCur;

      // 
      CVec2 limitEllipse;
      CVec2 centerOffset;

			float fov;
      float fovCorrectionAngle;

			/** manipulator factors */
			float zoomFactor;
			float pannedFactor;

			/** speed parameter */
			float movementSpeed;

			///< camera radius
			float cameraRadius;

      ///< height filtration coeffs
      float   hSmoothStep;
      int     hSmoothDiscrete;
      float   hSmoothSigma;

      ///< prevent landscape penetration coeffs
      int     pitchDiscrete;
      float   pitchRConst;
      float   pitchRMax;
      float   minCameraHeight;
      
      float startRodValue;

			CameraSettings( const NDb::AdventureCameraSettings * cameraSettings );
			
			float RodToZoom( float rod ) const;
			float ZoomToRod( float zoom ) const;
		};

		OBJECT_BASIC_METHODS( AdventureCameraController );
	protected:

		///< affected camera
		CPtr<NScene::ICamera> pCamera;
		///< camera movement restrictions
		//CameraSettings settings;
		CameraSettings settings;
		///< input processor
		NScene::CameraInputModifier inputModifier;
		/// extra position offset
		CVec2 positionModifier;

		///< affected scene
		CPtr<NScene::IScene> pScene;

		///< observing object
    CPtr<PFClientBaseMovingUnit> pObservingObject;

		///< current angular speed
		CVec3 angularSpeed;
    ///< current linear speed
    CVec3 linearSpeed;

    nstl::vector<float> frameDiffSamples;
    int nextSample;

		///< elapsed time
		Time elapsedTime;
		///< remaining time
		Time remainingTime;
		///< total movement time (estimate)
		Time totalTime;

		///< camera own time system
		NHPTimer::STime lastTime;

		///< align layer to terrain by default
		static const int DEFAULT_LAYER = 1;

    ///< camera zoom params
    float   zoomNext;
    float   zoomCurr;
    float   zoomPrev;

    bool    mouseZoomUsed; // True if mouse wheel or keys for zoom were used last frame
    float   userRod; // Rod adjusted by user
    float   userPitch; // Pitch adjusted by user

    // camera input-correction
    CVec3 prevPath;
    float inputWaitTime;

    // alternative tracking mode
    CVec3 observerShift;
    CVec3 lastObjectDirection;
    CVec3 lastObjectPosition;

    float deltaReminder;

    // camera position modified from outside of normal Update() cycle
    NScene::SCameraPosition forcedPosition;
    bool bForcedPosition;

    CVec2 mapSize;

    bool locked;
    bool forbidMouseZoom;
    bool forbidObserving;
    
    CVec3 currDiff;
    bool externalMovedOnPrevFrame;
    float continiusMovementTime;

    bool mouseZoomEnabled;

    float zoomManualDest;
    float zoomManualPeriod;

    CObj<NScene::ICallBackCameraController> callbackRodSmooth;

	public:
    AdventureCameraController( NScene::IScene*, const CVec2& _mapSize, const NDb::AdventureCameraSettings * cameraSettings );

		const bool IsEffect() const { return false; }
		const bool IsActive() const;// { return true; }

    bool IsCameraValid() const { return IsValid(pCamera); }

    float GetUserRod() const { return userRod; }
    float GetUserPitch() const { return userPitch; }

		void Update( NScene::SCameraPosition* pWantedPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff );
    
    bool ProcessEvent( const Input::Event &	_eEvent );

    void SetInitialParameters(float* rod = NULL, float* pitch = NULL, float* yaw = NULL);

		/** set camera position where we want to travel */		
		virtual bool SetCameraAnchor( const CVec3&, bool resetObserver = true );
		virtual bool SetCameraAnchor( PFClientBaseUnit* );
		/** set camera zoom in range [0 .. 1] */
		virtual bool SetCameraZoom( float zoom );
		virtual bool SetObservedObject( PFClientBaseMovingUnit * pObject, bool lockCamera = false );		

		/** add external force to camera position in screen coordinates */
		virtual void AddOffsetToPosition( const CVec2& acceleration );

		/** check for observed object identity */
		virtual bool IsObservedObject( PFClientBaseUnit* ) const;
    virtual bool IsObservingMode() const { return pObservingObject != 0; }

    virtual void Lock( bool lock ) { locked = lock; }
    virtual void LockZoom( bool lock ) { forbidMouseZoom = lock; }
    virtual bool IsLocked() const { return locked; }
    void LockObserve( bool lock ) { forbidObserving = lock; }

    float GetFOV() { return settings.fov; }
    const CameraSettings & GetSettings() const { return settings; }

    float GetFovCorrectionAngle() { return settings.fovCorrectionAngle; }

    static void SetBoolean( bool _predict );

    void EnableMouseZoom(bool enable) { mouseZoomEnabled = enable;}

    void GetCameraPosition(NScene::SCameraPosition * pos) const;

    void SetSmoothMotionRodCallback( const float rod, NScene::ICallBackCameraController* functor );
    
    void SetManualZoom( float rod, float time );

	protected:
    AdventureCameraController():settings(0) {}

		virtual void SetCamera( NScene::ICamera* _pCamera );
		virtual bool SetCameraPosition( const NScene::SCameraPosition& position );

		/** smooth camera position movement, return wanted rod */
		virtual float SmoothCameraRod( const NScene::SCameraPosition& position, const NScene::SCameraPosition& previousPosition );

		/** get eternal linear acceleration (from input for example)*/
		virtual CVec3 GetExternalLinearModifiers( const NScene::SCameraPosition& currentPosition );

		//bool ApplyAnchorModifier( NScene::SCameraPosition& position );
		virtual bool ApplyOrientationModifier( NScene::SCameraPosition& position, float dt );

    /** align position to layer height */
    virtual void CorrectHeight( CVec3& position );

    /**  */
    virtual void CorrectAncorZ( NScene::SCameraPosition& position, float dt );

		/** update time */
		virtual void UpdateTime( Time dt );

		/** update settings */
		virtual void UpdateSettings();

		/** reset movement parameters */
		virtual void Reset();

		/** apply environment limits */
		virtual void ApplyEnvironmentLimits( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos ) const;

		/** check sphere penetration with terrain, point - camera world position, return true if no penetration*/
		virtual bool PenetratedWithTerrain( CVec3* pPenetratDirection, const CVec3& point ) const;
    virtual bool PenetratedWithBorder( CVec3* pPenetratDirection, const CVec3& point ) const;

private:
    void UpdateInternal( NScene::SCameraPosition* pWantedPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff, bool useScrolling );

    void CalculateXYAnchorPosition ( const NScene::SCameraPosition& position, CVec3& path, float dt );
    void CalculateXYAnchorPosition2 ( const NScene::SCameraPosition& position, CVec3& path, float dt );
    void PenetratedAnchorWithBorder( NScene::SCameraPosition& position, CVec3& path );
    void CalculateZAnchorPosition  ( NScene::SCameraPosition& position, CVec3& path, float dt );
    CVec3 ApplySpeedLimits         ( CVec3& path, float dt );
    void ApplyCameraZoom    ( NScene::SCameraPosition& position, float zoom ) const;
    float CalcCameraZoom    ( NScene::SCameraPosition& position ) const;
    void LandscapeIntersection     ( NScene::SCameraPosition& position );

    void CheckXYShift( CVec3& path );
    
    float UpdateZoom( float dt, NScene::SCameraPosition& position );
    float CalcZoomFactor( float fRod, float zoomFactor ) const;
    float CalcProjShift( float fRod ) const;
    float UpdateCurSpeed( float curTimeDelta );
	};



  /************************************************************************/
  /*AdvancedFreeCameraController                                          */
  /************************************************************************/
  
  class AdvancedFreeCameraController
    : public NScene::FreeCameraController
  {
  public:
    typedef NScene::Time Time;

    OBJECT_BASIC_METHODS( AdvancedFreeCameraController );
  protected:

    ConstPtr<PFClientBaseMovingUnit> pObservingObject;
    CPtr<NScene::IScene> pScene;

    CVec3 currDiff;
    CVec3 linearSpeed;

  public:
    AdvancedFreeCameraController( NScene::IScene* );

    const bool IsEffect() const { return false; }
    void Update( NScene::SCameraPosition* pWantedPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff );

    void SetObservingUnit( const NWorld::PFBaseUnit * pUnit );		
    /** set camera position where we want to travel */		
    virtual bool SetCameraAnchor( const CVec3&, bool resetObserver = true );
    virtual bool SetCameraAnchor( const PFClientBaseUnit* );
    virtual bool IsObservingMode() const { return pObservingObject.GetPtr() != 0; }

 protected:
    virtual bool SetObservedObject( const PFClientBaseMovingUnit * pObject);		

    /** check for observed object identity */
    virtual bool IsObservedObject( const PFClientBaseUnit* ) const;
    

    AdvancedFreeCameraController() : pScene(0) {}
    virtual bool SetCameraPosition( const NScene::SCameraPosition& position );

    /** align position to layer height */
    virtual void CorrectHeight( CVec3& position );
  private:
    static const int DEFAULT_LAYER = 1;
    void UpdateInternal( NScene::SCameraPosition* pWantedPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff, bool useScrolling );

    void CalculateXYAnchorPosition ( const NScene::SCameraPosition& position, CVec3& path, float dt );
    void CheckXYShift( CVec3& path );
    float CalcZoomFactor( float fRod, float zoomFactor ) const;
    float CalcProjShift( float fRod ) const;
  };


}
