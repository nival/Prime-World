#include "stdafx.h"
#include "AdventureCameraController.hpp"
#include "PFClientBaseMovingUnit.h"
#include "PFBaseUnit.h"
#include "AdventureScreen.h"
#include "../Scene/Scene.h"
#include "../Terrain/Terrain.h"
#include "../Render/debugrenderer.h"
#include "../Client/ScreenBase.h"
#include "Scene/FreeCameraController.hpp"
#include "../Client/MainTimer.h"

//#include "DBStats.h"


namespace NSoundScene
{
	void EventSystemSetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor );
}
namespace
{
  ///< debug var to drawing intersected point
	DEV_VAR_STATIC bool gDrawCameraTerrainProjection = false;
	DEV_VAR_STATIC bool gDisableHeroCamera = false;
  DEV_VAR_STATIC bool g_bCamDisableZ = false;
  DEV_VAR_STATIC float g_inputWaitPeriod = 0.1f;

  // Alternative tracking
  // 1 - semi casual mode
  // 2 - full casual mode
  DEV_VAR_STATIC int g_alternativeTracking = 3;
  DEV_VAR_STATIC float g_alternativeTrackingBorder = 0.2f;

	REGISTER_DEV_VAR( "draw_camera_terrain_projection", gDrawCameraTerrainProjection, STORAGE_NONE );
	REGISTER_DEV_VAR( "disable_hero_camera", gDisableHeroCamera, STORAGE_NONE );
  REGISTER_DEV_VAR( "camera_disable_z", g_bCamDisableZ, STORAGE_NONE );

  REGISTER_DEV_VAR( "camera_alt_tracking", g_alternativeTracking, STORAGE_USER );
  REGISTER_DEV_VAR( "camera_alt_border", g_alternativeTrackingBorder, STORAGE_NONE );

  DEV_VAR_STATIC bool g_cameraNewMode = true;
  DEV_VAR_STATIC float g_observeCamMaxZSpeed = 3.f;

  static const int NUM_FRAME_SAMPLES = 10;

  DEV_VAR_STATIC float s_free_camera_damp = 0.5f;
  DEV_VAR_STATIC float s_free_camera_observershift = 1.5f;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<CVec3> camera_CameraAnchor      ( "01 Anchor", "Camera" );
static NDebug::DebugVar<CVec3> camera_CameraPos         ( "02 Position", "Camera" );
static NDebug::DebugVar<CVec3> camera_CameraOrientation ( "03 Orientation", "Camera" );
static NDebug::DebugVar<CVec3> camera_CameraLinearSpeed ( "04 dv", "Camera" );
static NDebug::StringDebugVar  camera_CameraDestination ( "08 Destination point", "Camera" );
static NDebug::StringDebugVar  camera_ObservedByCamera  ( "09 Observed object", "Camera" );
static NDebug::DebugVar<float> camera_ds_length         ( "10 Length", "Camera" );
static NDebug::DebugVar<float> camera_dt                ( "11 Delta Time", "Camera" );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  AdventureCameraController::CameraSettings::CameraSettings( const NDb::AdventureCameraSettings * cameraSettings )
    : minRod( 20.0f ), maxRod( 40.f ), maxPitch( ToRadian( -20.f ) ), minPitch( ToRadian( -60.f ) ), minYaw( ToRadian( -80.f ) ), maxYaw( ToRadian( 80.f )  ), centerYaw( ToRadian( 0.f )  )
      , maxZoomFactor( 1.0f )
      , horRotPeriod( 0.5f ), vertRotPeriod( 2.0f )
      , zoomFactor( 1.f ), pannedFactor( 2.0f )
      , movementSpeed( 20.f )
      , cameraRadius( 1.f )
      , fov( 70.f )
      , fovCorrectionAngle( 66.f )
      , limitEllipse (VNULL2)
      , pitchDiscrete   (3)
      , pitchRMax       (3.f)
      , pitchRConst     (1.f)
      , minCameraHeight (1.f)
      , centerOffset(VNULL2)

    {
      if ( cameraSettings )
      {
        movementSpeed = cameraSettings->movementSpeed;

        maxPitch = ToRadian( -cameraSettings->vertAngleBottom );
        minPitch = ToRadian( -cameraSettings->vertAngleTop );

        minRod = cameraSettings->vertLengthBottom ;
        maxRod = cameraSettings->vertLengthTop;

        float deltaYaw = cameraSettings->horAngle;
        centerYaw = ToRadian( cameraSettings->horCenterAngle );
        minYaw = ToRadian( -deltaYaw ) + centerYaw;
        maxYaw = ToRadian( +deltaYaw ) + centerYaw;

        maxZoomFactor = cameraSettings->maxZoomFactor;

        horRotPeriod = cameraSettings->horTime;
        vertRotPeriod = cameraSettings->vertTime;

        limitEllipse.x = cameraSettings->limitRadiusHor;
        limitEllipse.y = cameraSettings->limitRadiusVert;
        centerOffset = cameraSettings->centerOffset;

        fov = cameraSettings->fov;
        fovCorrectionAngle = cameraSettings->fovCorrectionAngle;

        // read height smoothing data
        hSmoothDiscrete = cameraSettings->smoothDiscrete;
        if (hSmoothDiscrete > 0)
        {
          hSmoothStep = cameraSettings->smoothRadius / hSmoothDiscrete;
        }
        else
          hSmoothStep = 0.f;

        hSmoothSigma = cameraSettings->smoothDensity;

        pitchDiscrete   = cameraSettings->pitchDiscrete;
        pitchRMax       = cameraSettings->pitchRMax;
        pitchRConst     = cameraSettings->pitchRConst;
        minCameraHeight = cameraSettings->minCameraHeight;

        NI_VERIFY(horRotPeriod > 0.f, "wrong horizontal period data", horRotPeriod = 0.1f);
        NI_VERIFY(limitEllipse.x > 0.f, "wrong camera horizontal limit", limitEllipse.x = -1.f);
        NI_VERIFY(limitEllipse.y > 0.f, "wrong camera vertical limit", limitEllipse.y = -1.f);

        NI_VERIFY(hSmoothDiscrete >= 0, "wrong height discrete data", hSmoothDiscrete = 0);
        NI_VERIFY(hSmoothStep >= 0.f, "wrong height radius data", hSmoothStep = 0.f);
        NI_VERIFY(hSmoothSigma > 0.f, "wrong height sigma data", hSmoothSigma = 0.1f);

        NI_VERIFY(pitchDiscrete >= 0, "wrong pitch discrete data", pitchDiscrete = 0);
        NI_VERIFY(pitchRMax > 0.f, "wrong pitch radius-max data", pitchRMax = 3.f);
        NI_VERIFY(pitchRConst > 0.f, "wrong pitch radius-const data", pitchRConst = 1.f);
        NI_VERIFY(minCameraHeight > 0.f, "wrong min height data", minCameraHeight = 1.f);

        zoomFactor = cameraSettings->zoomSpeed;
        
        dampTimeObserv = cameraSettings->dampSmoothing.dampTimeObserv;
        dampTimeMove = cameraSettings->dampSmoothing.dampTimeMove;
        anchorShiftObserv = cameraSettings->dampSmoothing.anchorShiftObserv;
        firstJumpTime = cameraSettings->dampSmoothing.firstJumpTime;
        zoomFactorMove = cameraSettings->dampSmoothing.zoomFactorMove;
        zoomFactorObserv = cameraSettings->dampSmoothing.zoomFactorObserv;
        maxSpeed = cameraSettings->dampSmoothing.maxSpeed;
        timeToMaxSpeed = cameraSettings->dampSmoothing.timeToMaxSpeed;
        projCorretionShiftObservMaxZoom = cameraSettings->dampSmoothing.projCorretionShiftObservMaxZoom;
        projCorretionShiftObservMinZoom = cameraSettings->dampSmoothing.projCorretionShiftObservMinZoom;
        startRodValue = ZoomToRod( 1.0f );
      }

      horFreezeTime = 0.05f;
      horFreezeTimeCur = 0.f;
    }
    
  float AdventureCameraController::CameraSettings::RodToZoom( float rod ) const
  {
    return (rod - minRod) / (maxRod - minRod);
  }
   
  float AdventureCameraController::CameraSettings::ZoomToRod( float zoom ) const
  {
    return minRod + (maxRod - minRod) * zoom;
  }

  AdventureCameraController::AdventureCameraController( NScene::IScene* _pScene, const CVec2 & _mapSize, const NDb::AdventureCameraSettings * cameraSettings ) :
    settings( cameraSettings )
    , angularSpeed( VNULL3 )
    , linearSpeed( VNULL3 )
    , pScene( _pScene )
    , remainingTime( 0.f )
    , elapsedTime( 0.f )
    , totalTime( 0.f )
    , positionModifier( VNULL2 )
    , pObservingObject( 0 )
    , zoomNext(1.f)
    , zoomCurr(1.f)  
    , zoomPrev(1.0f)
    , mouseZoomUsed(false)
    , prevPath(V3_AXIS_X)
    , inputWaitTime(0)
    , lastTime(0)
    , deltaReminder(0.f)
    , nextSample(0)
    , frameDiffSamples( NUM_FRAME_SAMPLES, 0.f )
    , bForcedPosition(false)
    , observerShift( VNULL3 )
    , lastObjectDirection( VNULL3 )
    , mapSize(_mapSize)
    , locked(false)
    , forbidMouseZoom(false)
    , forbidObserving(false)
    , currDiff( VNULL3 )
    , externalMovedOnPrevFrame( false )
    , continiusMovementTime(0)
    , mouseZoomEnabled(true)
    , zoomManualDest(-1.f)
    , zoomManualPeriod(-1.f)
    , callbackRodSmooth(0)
    {
      ASSERT( IsValid( pScene ) );
    }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::ProcessEvent( const Input::Event& message )
	{
		return inputModifier.ProcessEvent( message );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::SetCamera( NScene::ICamera* _pCamera )
	{
		pCamera = _pCamera;		
	}

	const bool AdventureCameraController::IsActive() const { return !gDisableHeroCamera; }

  void AdventureCameraController::SetInitialParameters(float* rod /* NULL */, float* pitch /* NULL */, float* yaw /* NULL */)
  {
    //init camera in vert position
    NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return; );

    NScene::SCameraPosition position;
    pCamera->GetPosition( &position );

    position.fPitch = pitch ? *pitch : settings.minPitch;
    position.fRod = rod ? *rod : settings.maxRod;
    position.fYaw = yaw ? *yaw : settings.centerYaw;

    SetCameraPosition( position );
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace
	{
		inline float ApplyLimits( float value, float min, float max )
		{
			return min > max ? value : Clamp( value, min, max );
		}
		
		inline float GetDelta( float& value )
		{
			const float old = value;
			value = 0.f;
			return old;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CVec3 AdventureCameraController::GetExternalLinearModifiers( const NScene::SCameraPosition& currentPosition )
	{
    float inpDeltaFoward = 0.0f;
    float inpDeltaStrafe = 0.0f;
    float posDeltaFoward = 0.0f;
    float posDeltaStrafe = 0.0f;

    if (!locked && !forbidObserving )
    {
      inpDeltaFoward = inputModifier.GetDeltaFoward();
      inpDeltaStrafe = inputModifier.GetDeltaStrafe();
      posDeltaFoward = GetDelta( positionModifier.y );
      posDeltaStrafe = GetDelta( positionModifier.x );
    }

		/*
		static float s_prevInpDeltaStrafe = 0.0f;
		if (inpDeltaFoward == 0.0f)
		{
			if (s_prevInpDeltaStrafe != 0.0f && s_prevInpDeltaStrafe * inpDeltaStrafe >= 0.0f)
				inpDeltaStrafe = s_prevInpDeltaStrafe;
			else
				s_prevInpDeltaStrafe = inpDeltaStrafe;
		}
		else
			s_prevInpDeltaStrafe = inpDeltaStrafe;
		*/
		
		const float deltaFoward = ( inpDeltaFoward + posDeltaFoward ) * settings.pannedFactor * currentPosition.fRod;
		const float deltaStrafe = ( inpDeltaStrafe + posDeltaStrafe ) * settings.pannedFactor * currentPosition.fRod;
		
		CVec3 acceleration = VNULL3;

		// forward
		const bool changedForward = deltaFoward != 0.f;
		if ( changedForward )
		{
			CVec3 forwardDir = GetEulerXAxis( currentPosition.fYaw + FP_PI2, currentPosition.fPitch, currentPosition.fRoll );
			forwardDir.z = 0.f;
			Normalize( &forwardDir );
			acceleration += forwardDir * deltaFoward;
		}

		// strafe
		const bool changedStrafe = deltaStrafe != 0.f;
		if ( changedStrafe )
		{
			CVec3 strafeDir = GetEulerYAxis( currentPosition.fYaw + FP_PI2, currentPosition.fPitch, currentPosition.fRoll );
			strafeDir.z = 0.f;
			Normalize( &strafeDir );
			acceleration -= strafeDir * deltaStrafe;
		}

		return acceleration;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::AddOffsetToPosition( const CVec2& offset )
	{
		const float modifier = 0.05f;
		positionModifier += offset * modifier;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::CorrectHeight( CVec3& position )
	{
		const NScene::IHeightsController& heights = pScene->GetHeightsController();
		heights.GetHeight( position.x, position.y, DEFAULT_LAYER, &position.z, 0 );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool AdventureCameraController::ApplyOrientationModifier( NScene::SCameraPosition& position, float dt )
	{
    // calculate wanted orientation

    // calculate horizontal rotation
    const float deltaYaw = inputModifier.GetDeltaYaw();
    float speedYaw = 0.f;

    float limitMin = settings.minYaw; 
    float limitMax = settings.maxYaw;

    if (deltaYaw > 0.f)
    {
      settings.horFreezeTimeCur = settings.horFreezeTime;

      if (position.fYaw >= settings.centerYaw)
      {
        speedYaw = 1.f;

        // lock to the border
        if (position.fYaw == settings.maxYaw)
        {
          speedYaw = 0.f;
        }
      }
      if (position.fYaw < settings.centerYaw)
        speedYaw = 2.f;
    }
    else if (deltaYaw < 0.f)
    {
      settings.horFreezeTimeCur = settings.horFreezeTime;

      if (-position.fYaw >= settings.centerYaw)
      {
        speedYaw = -1.f;

        // lock to the border
        if (position.fYaw == settings.minYaw)
          speedYaw = 0.f;
      }
      if (-position.fYaw < settings.centerYaw)
        speedYaw = -2.f;
    }
    else if (deltaYaw == 0.f)
    {
      if (settings.horFreezeTimeCur > 0.f)
        settings.horFreezeTimeCur -= dt;
      else
      {
        if (position.fYaw > settings.centerYaw)
        {
          speedYaw = -1.f;
          limitMin = settings.centerYaw;
        }
        if (position.fYaw < settings.centerYaw)
        {
          speedYaw = 1.f;
          limitMax = settings.centerYaw;
        }
      }
    }
    
    speedYaw *= ((settings.maxYaw - settings.minYaw) / 2.f) / settings.horRotPeriod;
    position.fYaw = ApplyLimits( position.fYaw + speedYaw * dt, limitMin, limitMax );
    // end of horizontal rotation calculation
    
    return deltaYaw != 0.f || UpdateZoom(dt, position) != 0.f;   
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  float AdventureCameraController::UpdateZoom( float dt, NScene::SCameraPosition& position )
  {

    //Check for external zoom change
    bool bZoomExtChanged = false;
    const float calcZoom = CalcCameraZoom( position );
    if( fabs(calcZoom - zoomCurr) > EPS_VALUE )
    {
      zoomCurr = zoomNext = zoomPrev = calcZoom;
      bZoomExtChanged = true;
    }

    // ручное плавное изменение зума
    if( zoomManualDest >= 0 && fabs(zoomManualDest - zoomCurr) < EPS_VALUE ) 
    {
      if( IsValid( callbackRodSmooth ) )
        callbackRodSmooth->CallBack();
      zoomManualDest = -1.f;
      callbackRodSmooth = 0;
      zoomManualPeriod = -1.f;
    }

    if (bZoomExtChanged)
      return 0;
    
    float mouseZoomWheelDelta = inputModifier.GetDeltaMouseZoom();
    float mouseZoomKeyDelta = inputModifier.GetDeltaZoom();
    
    const float manualZoom = (zoomManualDest >= 0) ? zoomManualDest - zoomCurr : 0;
    const float deltaZoom = (mouseZoomKeyDelta + ( (mouseZoomEnabled && !forbidMouseZoom)? mouseZoomWheelDelta : 0)  )* settings.zoomFactor;

    if(!mouseZoomUsed)
    {
      mouseZoomUsed = mouseZoomWheelDelta != 0.0f || mouseZoomKeyDelta != 0.0f;
    }

    // If input key is opposite to current movement, then start new movement from current point
    if ((Sign(deltaZoom) * Sign(zoomNext - zoomCurr)) == -1.f)
    {
      zoomNext = zoomCurr;
    }

    if( zoomManualDest >= 0 && manualZoom != 0.0f )
    {
      if( manualZoom > 0 )
      {
        // calculate new zoom value
        zoomNext = ApplyLimits( zoomNext + deltaZoom + manualZoom, 0.f, zoomManualDest );
      }
      else
      {
        // calculate new zoom value
        zoomNext = ApplyLimits( zoomNext + deltaZoom + manualZoom, zoomManualDest, settings.maxZoomFactor );
      }
    }
    else
    {
      // calculate new zoom value
      zoomNext = ApplyLimits( zoomNext + deltaZoom , 0.f, settings.maxZoomFactor );
    }

    // apply soft movement to next value
    zoomPrev = zoomCurr;
    bool zoomNeedsUpdate = fabs(zoomNext - zoomCurr) > EPS_VALUE;
    if (zoomNeedsUpdate)
    {
      float direction = Sign(zoomNext - zoomCurr);

      float zoomSpeed;
      if( zoomManualPeriod >= 0.f && fabs(zoomManualPeriod) > EPS_VALUE )
        zoomSpeed = 1.f / zoomManualPeriod;
      else if ( zoomManualPeriod >= 0.f && fabs(zoomManualPeriod) <= EPS_VALUE )
        zoomSpeed = 10000.f;
      else
        zoomSpeed = 1.f / settings.vertRotPeriod;

      zoomCurr += zoomSpeed * dt * direction;

      // clamp values if speed fast
      if (direction > 0.f)
        zoomCurr = ApplyLimits(zoomCurr, 0.f, zoomNext);
      else
        zoomCurr = ApplyLimits( zoomCurr, zoomNext, settings.maxZoomFactor );
    }

    // transform zoom value to camera Rod & Pitch
    ApplyCameraZoom(position, zoomCurr);

    // Store customized user zoom
    if(mouseZoomUsed && !zoomNeedsUpdate)
    {
      userRod = position.fRod;
      userPitch = position.fPitch;
      mouseZoomUsed = false;
    }
    
    return deltaZoom;
  }

  void AdventureCameraController::SetManualZoom( float rod, float time )
  {
    NI_VERIFY( rod >= settings.minRod && rod <= settings.ZoomToRod(settings.maxZoomFactor), "invalid zoom parameter", return );
    NI_VERIFY( time >= 0, "invalid time parameter", return );

    zoomManualDest = GetSettings().RodToZoom( rod );

    if( fabs(time) < EPS_VALUE )
    {
      zoomManualPeriod = 0.f;
      return;
    }

    float velocity = settings.ZoomToRod( fabs(zoomCurr  - zoomManualDest) ) / time;
    zoomManualPeriod = (settings.ZoomToRod(settings.maxZoomFactor) - settings.minRod) / velocity;
  }

  void AdventureCameraController::GetCameraPosition(NScene::SCameraPosition * pos) const
  {
    NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return; );

    if (pos)
    {
      pCamera->GetPosition(pos);
    }
  }

  void AdventureCameraController::SetSmoothMotionRodCallback( const float rod, NScene::ICallBackCameraController* functor )
  {
    SetManualZoom(rod, 0.8f);
    callbackRodSmooth = functor;
  }

	bool AdventureCameraController::SetCameraPosition( const NScene::SCameraPosition& wantedPos)
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );

    //DebugTrace("SetCameraPosition (%f, %f)", wantedPos.GetCameraPos().x, wantedPos.GetCameraPos().y);

		pCamera->SetPosition( wantedPos );
		angularSpeed = VNULL3;
    linearSpeed = VNULL3;
		remainingTime = 0.f;
		totalTime = 0.f;

    // store this position to apply it on Update() as well
    forcedPosition = wantedPos;
    bForcedPosition = true;

		return true;
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::SetCameraAnchor( const CVec3& anchor, bool resetObserver )
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );

		// reset observing object
		if( resetObserver )
			SetObservedObject( 0 );

    NScene::SCameraPosition wantedPos;
    pCamera->GetPosition( &wantedPos );

    wantedPos.vAnchor = anchor;
    PenetratedWithBorder( &wantedPos.vAnchor, anchor );
    CorrectHeight( wantedPos.vAnchor );
		return SetCameraPosition( wantedPos );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::SetCameraAnchor( PFClientBaseUnit* pObject )
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );
		NI_VERIFY( pObject, "Invalid object!", return false; );

		// get world 3d position
		return SetCameraAnchor( pObject->GetPosition().pos, pObservingObject != pObject );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::SetCameraZoom( float zoom )
	{
		NI_VERIFY( zoom >= 0 && zoom <= 1.f, "Invalid zoom!", return false; );

		NScene::SCameraPosition position;
		pCamera->GetPosition( &position );
		position.fRod = ( settings.maxRod - settings.minRod ) * zoom + settings.minRod;
		pCamera->SetPosition( position );

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float AdventureCameraController::SmoothCameraRod( const NScene::SCameraPosition& position, const NScene::SCameraPosition& previousPosition )
	{
		const CVec3 point = position.GetCameraPos();
		const CVec3 previousPoint = previousPosition.GetCameraPos();
		const float dz = point.z - previousPoint.z;

		if( dz < -FP_EPSILON )
		//if( fabs( dz ) > FP_EPSILON )
		{
			const float h = position.vAnchor.z - point.z;
			NI_ASSERT( fabs( h ) > FP_EPSILON, "Invalid height!" );

			const float alpha = 1.f + dz / h;
			return ApplyLimits( position.fRod * alpha, settings.minRod, settings.maxRod );
		}
		else
			return position.fRod;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::SetObservedObject( PFClientBaseMovingUnit * pObject, bool lockCamera /*= false*/ )
	{
		if ( pObject == pObservingObject )
    {
      if ( g_alternativeTracking != 1 )
			  return false;

      pObservingObject = 0;
    }
    else
    {
      pObservingObject = pObject;
    }

    observerShift       = VNULL3;
    lastObjectDirection = VNULL3;
    lastObjectPosition  = VNULL3;
    positionModifier    = VNULL2;
    inputModifier.ClearDeltaFoward();
    inputModifier.ClearDeltaStrafe();

    locked = lockCamera;

		if ( IsValid( pObservingObject ) && g_alternativeTracking != 3 )
    {
      SetCameraAnchor( pObservingObject );

      if (IsValid(pObservingObject))
        lastObjectPosition = pObservingObject->GetPosition().pos;
    }

		return pObservingObject != 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::IsObservedObject( PFClientBaseUnit* pObject ) const
	{
		return pObservingObject == pObject;		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::UpdateTime( Time dt )
	{
		if( remainingTime > FP_EPSILON )
		{
			elapsedTime += dt;
			remainingTime -= dt;
			totalTime -= dt;

			if( remainingTime < FP_EPSILON )
			{
				// stop movement
				elapsedTime += remainingTime;
				remainingTime = 0.f;
				totalTime = 0.f;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// CRAP {
	namespace
	{
    // height filtration coefficients
    bool gUseDebugSettings = false;
    int  ghFiltCnt = 3;
    float ghFiltSigma = 2.f;
    float ghFiltStep = 1.0f;

    REGISTER_DEV_VAR( "camera_settings_use_debug", gUseDebugSettings, STORAGE_NONE );
    REGISTER_DEV_VAR( "camera_settings_h_discrete", ghFiltCnt, STORAGE_NONE );
    REGISTER_DEV_VAR( "camera_settings_h_step", ghFiltStep, STORAGE_NONE );
    REGISTER_DEV_VAR( "camera_settings_h_sigma", ghFiltSigma, STORAGE_NONE );

    AdventureCameraController::CameraSettings GetGlobalSetting( const AdventureCameraController::CameraSettings& refference )
		{
			AdventureCameraController::CameraSettings settings = refference;

      if (!gUseDebugSettings)
        return settings;

      settings.hSmoothDiscrete = ghFiltCnt;
      settings.hSmoothStep = ghFiltStep;
      settings.hSmoothSigma = ghFiltSigma;	

			return settings;
		}
	}
	// CRAP }

	void AdventureCameraController::UpdateSettings()
	{
		settings = GetGlobalSetting( settings );
	}

  static bool g_bPredict = false;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdventureCameraController::SetBoolean( bool _predict )
  {
    g_bPredict = _predict;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdventureCameraController::Update( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff )
  {
//     float timeDelta = float(NHPTimer::GetTimePassedAndUpdateTime(lastTime));
//     if (timeDiff > 0.0f && timeDelta > 0.0f)
//       timeDiff = timeDelta; 

    float avgDelta = timeDiff;
    
    if( g_alternativeTracking != 3 )
    {
      frameDiffSamples[nextSample] = timeDiff;
      nextSample = ( nextSample + 1 ) % NUM_FRAME_SAMPLES;

      for ( int i = 0; i < NUM_FRAME_SAMPLES; ++i )
      {
        avgDelta += frameDiffSamples[i];
      }

      avgDelta /= float( NUM_FRAME_SAMPLES );
    }

    if (float timeScale = NMainLoop::GetTimeScale())
    {
      avgDelta /= timeScale;
    }

    NScene::SCameraPosition const *actualWantedPos = &wantedPos;
    if (bForcedPosition)
    {
      actualWantedPos = &forcedPosition;
      bForcedPosition = false;
    }

    if (IsValid(pCamera))
      pCamera->SetFOV(settings.fov);

    UpdateInternal( pResultPos, currentPos, *actualWantedPos, avgDelta, true );	
    //UpdateI( pResultPos, currentPos, *actualWantedPos, timeDiff );	

    // Experiments with Fixed Step :

//     float commonDelta = timeDiff + deltaReminder;
// 
//     const float CameraFPS = 60.f;
// 
//     deltaReminder = fmod( commonDelta, 1.f / CameraFPS );
//     int numSubSteps = Float2Int( floor( commonDelta * CameraFPS ) );
// 
//     *pResultPos = currentPos;
// 
//     for (int i = 0; i < numSubSteps; ++i)
//     {
//       UpdateI( pResultPos, *pResultPos, *actualWantedPos, 1.f / CameraFPS );			
//     }

//     static float previousDiff = 0.f;
// 
//     previousDiff = ( previousDiff + timeDiff ) * 0.5f;
// 
//     systemLog( NLogg::LEVEL_MESSAGE ) << " D: " << previousDiff << endl;

//    UpdateI( pResultPos, *pResultPos, *pResultPos, timeDiff );			
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdventureCameraController::UpdateInternal( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time dt, bool useScrolling )
  {
    NI_VERIFY( pResultPos, "Invalid result storage!", return; );
    NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return; );

		*pResultPos = wantedPos;

    UpdateSettings();

    // TODO: separate linear and angular movement
    ApplyOrientationModifier( *pResultPos, dt );

    CVec3 ds = VNULL3;
    // calculate plane movement
    
    if (useScrolling)
    {
      if( g_alternativeTracking != 3 )
        CalculateXYAnchorPosition(*pResultPos, ds, dt);
      else
        CalculateXYAnchorPosition2(*pResultPos, ds, dt);
    }
      
    // Apply limit border
    //if ( !IsObservingMode() )
    {
      PenetratedAnchorWithBorder(*pResultPos, ds);

      CVec3 dv = ds / dt;
      if( !IsAlmostZero( ds ) && g_alternativeTracking != 3 )
      {
        // calculate vertical movement
        if (!g_bCamDisableZ)
          CalculateZAnchorPosition(*pResultPos, ds, dt);

        // apply maximum speed
        dv = ApplySpeedLimits(ds, dt);
        //dv = ApplySpeedLimits(ds, 0.015f);
      }
      
      // modify position
      pResultPos->vAnchor += ds;

      // modify camera Rod to prevent landscape intersection
      LandscapeIntersection(*pResultPos);

      //systemLog( NLogg::LEVEL_MESSAGE ) << "length: " << ds.Length() << " dt: " << dt << endl;
      if( gDrawCameraTerrainProjection )
      {
        Render::DebugRenderer::DrawPoint3D( pResultPos->vAnchor, 0.4f, Render::Color( 0, 0, 255 ), true );
        //Render::DebugRenderer::DrawPoint3D( point, 0.2f, Render::Color( 0, 255, 0 ), true );
      }

      // update metrics
      {
        camera_CameraAnchor.SetValue( pResultPos->vAnchor );
        camera_CameraPos.SetValue( pResultPos->GetCameraPos() );
        camera_CameraOrientation.SetValue( CVec3( pResultPos->fYaw, pResultPos->fPitch, pResultPos->fRoll ) );			

        camera_CameraLinearSpeed.SetValue(dv);

        if( pObservingObject == 0 )
          camera_ObservedByCamera.SetValue( "none" );

        camera_ds_length.SetValue(ds.Length());
        camera_dt.SetValue(dt);

        //DebugTrace( "metrics: ds: %2.4f dt: %2.4f dv: %2.4f real_dt: %2.4f real_dv: %2.4f", fabs( ds ), dt, fabs( dv ), real_dt, real_dv );
      }
    }
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void AdventureCameraController::CorrectAncorZ(NScene::SCameraPosition& position, float dt)
  {
    // set correct height
    const NScene::IHeightsController& heights = pScene->GetHeightsController();
    float height;
    // modify z-coordinate
    heights.GetHeight( position.GetCameraPos().x, position.GetCameraPos().y, DEFAULT_LAYER, &height, 0 );
    float rightH = NMath::Sin(-position.fPitch) * position.fRod;

    float delta = (rightH + height) - position.GetCameraPos().z;
    if (delta > 0.f)
    {
      float sign = delta > 0.f ? 1.f : -1.f;
      static float speed = 10.f;
      float maxDZ = speed * dt;
      if (fabs(delta) > maxDZ)
        delta = maxDZ * sign;

      position.vAnchor.z += delta;
    }
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::ApplyEnvironmentLimits( NScene::SCameraPosition* pCurrentPos, const NScene::SCameraPosition& wantedPos ) const
	{
		CVec3 point = pCurrentPos->GetCameraPos();

		// restore old position
		if( PenetratedWithTerrain( 0, point ) )
			*pCurrentPos = wantedPos;

		// check camera position on penetration with terrain
		while( PenetratedWithTerrain( 0, point ) )
		{
			const CVec3 ds( 0, 0, 0.5f );
			point += ds; 
      pCurrentPos->vAnchor += ds;
		}

    CVec3 border;
    /*
    if ( PenetratedWithBorder( &border, point ) )
    {
      //if (!pObservingObject)
        pCurrentPos->vAnchor += border - point;
      //else
      //{
      //  pCurrentPos->fPitch = wantedPos.fPitch;
      //  pCurrentPos->fYaw = wantedPos.fYaw;
      //  pCurrentPos->fRoll = wantedPos.fRoll;
      //}
    }
    */
    if ( PenetratedWithBorder( &border, pCurrentPos->vAnchor ))
      pCurrentPos->vAnchor = border;

		if( gDrawCameraTerrainProjection )
		{
			Render::DebugRenderer::DrawPoint3D( pCurrentPos->vAnchor, 0.4f, Render::Color( 0, 0, 255 ), true );
			//Render::DebugRenderer::DrawPoint3D( point, 0.2f, Render::Color( 0, 255, 0 ), true );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdventureCameraController::Reset()
	{
		remainingTime = 0.f;
		totalTime = 0.f;
		elapsedTime = 0.f;
		angularSpeed = VNULL3;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdventureCameraController::PenetratedWithTerrain( CVec3* pPenetration, const CVec3& point ) const
	{
		NI_VERIFY( IsValid( pCamera ) && IsValid( pScene ), "Invalid offected camera or scene!", return false; );

		const NScene::IHeightsController& heights = pScene->GetHeightsController();
		
		// select nearest terrain cells
		CVec3 projectedPoint( point.x - settings.cameraRadius, point.y - settings.cameraRadius, point.z );
		const CVec2 bounds( point.x + settings.cameraRadius, point.y + settings.cameraRadius );
		// CRAP {
		const float step = 2.5f * 0.25f;
		// CRAP }

    //CRAP, another one :-)
    //The cycle below can become infinite if 'point' components become large enough
    //Then 'step' will sunk in 'point' FP mantissa
    //So we set up a backup hard limit for iterations
    int iterationsHardLimit = Max( 1, (int)( 1.0f + 2.0f * settings.cameraRadius / step ) );
    iterationsHardLimit = iterationsHardLimit * iterationsHardLimit * 2;

		bool projected = true;
		float minDistance = FP_MAX_VALUE;
		CVec3 minNormal = VNULL3;

    int iterations = 0;
		for( ; projectedPoint.x <= bounds.x; projectedPoint.x += step )
			for( ; projectedPoint.y <= bounds.y; projectedPoint.y += step )
			{
        ++iterations;
        NI_VERIFY( iterations < iterationsHardLimit, "Wrong camera point!", return false );

				float& height = projectedPoint.z;
				CVec3 normal( 0.f, 0.f, 1.f );
				// get height and normal
				if( heights.GetHeight( projectedPoint.x, projectedPoint.y, DEFAULT_LAYER, &height, &normal ) )
				{
					// project to plane
					const SPlane plane( normal, - normal * projectedPoint );
					const float distance = plane.GetDistanceToPoint( point );

					if( distance >= minDistance || distance < 0.f )
						continue;
					
					minDistance = distance;
					minNormal = normal;
				}
				else
					projected = false;
			}

		if( minDistance != FP_MAX_VALUE )
		{
			if( pPenetration )
				*pPenetration = point - minNormal * minDistance;
			return minDistance < settings.cameraRadius;
		}
		else
			return projected;
	}

  // penetration with circular
  bool AdventureCameraController::PenetratedWithBorder( CVec3* pPenetration, const CVec3& point ) const
  {
    bool penetration = false;
    CVec2 center;

    center = mapSize * 0.5f;
    center += settings.centerOffset;

    CVec2 point2D;
    point2D.x = point.x;
    point2D.y = point.y;

    point2D -= center;

    float scale = (point2D.x * point2D.x) / (settings.limitEllipse.x * settings.limitEllipse.x) +
                  (point2D.y * point2D.y) / (settings.limitEllipse.y * settings.limitEllipse.y);
    scale = sqrt(scale);

    if (scale > 1.f)
    {
      penetration = true;

      if (pPenetration)
      {
        pPenetration->x = center.x + point2D.x / scale;
        pPenetration->y = center.y + point2D.y / scale;
        pPenetration->z = point.z;
      }
    }

    return penetration;
  }

  void AdventureCameraController::CalculateXYAnchorPosition( const NScene::SCameraPosition& currentPosition, CVec3 &path, float dt )
  {
    // check external forces
    path = GetExternalLinearModifiers( currentPosition );
    bool externalModification = !IsAlmostZero( path );

    if ( externalModification )
    {
      inputWaitTime = g_inputWaitPeriod;
      lastObjectDirection = VNULL3;
    }
    else if ( !externalModification && (inputWaitTime > 0) && !g_alternativeTracking )
    {
      inputWaitTime -= dt;
      path = prevPath;
      externalModification = !IsAlmostZero( path );
      NI_ASSERT(true == externalModification, "camera path invalid");
    }

    if( !externalModification )
    {
      if( IsObservingMode() && !forbidObserving )
      {
        PFClientBaseMovingUnit* pSceneObject = pObservingObject.GetPtr();

        if(pSceneObject != NULL && pSceneObject->GetSceneObject() != NULL)
        {
          // get world 3d position
          const CVec3 position( pSceneObject->GetPosition().pos );

          // ...
          camera_ObservedByCamera.SetValue( "Observing" );

          
          //     if ( g_alternativeTracking == 2 && IsValid( pObservingObject ) )
          //     {
          // //       NScene::SCameraPosition cameraPos;
          // //       pCamera->GetPosition( &cameraPos );
          // 
          //       CVec3 newPos = pObservingObject->GetPosition().pos;
          //       CVec3 dir = newPos - lastObjectPosition;
          //       Normalize( &dir );
          // 
          //       if ( !IsAlmostZero( dir ) )
          //         lastObjectDirection = dir;
          // 
          //       acceleration += lastObjectDirection;
          // 
          // //       newPos - cameraPos.vAnchor;
          // // 
          // //       lastObjectPosition = newPos;
          //     }



          if ( g_alternativeTracking == 1 )
          {
            path = ( position + observerShift ) - currentPosition.vAnchor;
          }
          else if ( g_alternativeTracking == 2 )
          {
            CVec3 newPos = pObservingObject->GetPosition().pos;
            CVec3 dir = newPos - lastObjectPosition;
            Normalize( &dir );

            lastObjectPosition = newPos;

            if ( !IsAlmostZero( dir ) )
              lastObjectDirection = dir;

            if ( !IsAlmostZero( dir ) )
            {
              path = ( position + dir * 1000.f ) - currentPosition.vAnchor;
              path.z = 0.f;
              Normalize( &path );
              path *= settings.movementSpeed * dt;

              CheckXYShift( path ); 

              observerShift += path;
            }

            path = ( position + observerShift ) - currentPosition.vAnchor;
          }
          else
          {
            path = position-currentPosition.vAnchor;
            //currentPosition.vAnchor = position;
            //path = CVec3(0,0,0);
          }
        }
      }
    }
    else
    {
      if ( IsObservingMode() && !g_alternativeTracking && !locked )
        SetObservedObject(0);

      path.z = 0.f;

      Normalize(&path);
      path *= settings.movementSpeed * dt;

      if ( g_alternativeTracking && IsValid( pObservingObject ) )
      {
        const CVec3 position( pObservingObject->GetPosition().pos );

        CheckXYShift( path ); 

        observerShift += path;
        path = ( position + observerShift ) - currentPosition.vAnchor;
      }
    }

    // when moving too slow, don't update direction
    if (!IsAlmostZero( path ))
    {
      prevPath = path;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  float AdventureCameraController::CalcZoomFactor( float fRod, float zoomFactor ) const
  {
     /* Maple
       restart;
       F := x->k*x + b;
       constants := constants, ZF, TOne;
       Fac := solve([F(TOne) = 1, F(0) = ZF] );
       Res := eval( F(fRod), Fac );
       plot( eval(Res, {ZF = 0.3, TOne = 60} ), fRod=0..100, y=0..5 );
     */
     
     //Точка в которой значение коэффициента должно быть равно 1     
		 const float baseRodValue = settings.startRodValue;

     return  zoomFactor - ( zoomFactor - 1 ) * fRod / baseRodValue;     
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       
  float AdventureCameraController::UpdateCurSpeed( float curTimeDelta )
  {
    //Вычисляем время которое пользователь не отпускает клавишу движения      
    if( externalMovedOnPrevFrame )
      continiusMovementTime += curTimeDelta;
    else
      continiusMovementTime = 0;

    if( continiusMovementTime < settings.timeToMaxSpeed )
    {
      //Ускорение движение вычисляется исходя из максимальной скорости и времени её достижения
      const float accel = ( settings.maxSpeed - settings.movementSpeed ) / settings.timeToMaxSpeed; 
      return settings.movementSpeed + accel * continiusMovementTime;
    } 
    else
      return settings.maxSpeed;
  }       
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  inline CVec2 ToVec2( const CVec3 &v )
  {
    return CVec2( v.x, v.y ); 
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  float AdventureCameraController::CalcProjShift( float fRod ) const
  {
    //Значение зума в интервале [0, 1]
    const float normZood = settings.RodToZoom(fRod) / settings.maxZoomFactor;
    
    return Lerp( 
      settings.projCorretionShiftObservMaxZoom, 
      settings.projCorretionShiftObservMinZoom,
      normZood
    ); 
  }
       
  void AdventureCameraController::CalculateXYAnchorPosition2 ( const NScene::SCameraPosition& position, CVec3& path, float dt )
  {
    float damp_time;
    CVec2 heightPos;
  
    //Если мы следим за героем
    if( IsObservingMode() && pObservingObject != 0 && !forbidObserving && pObservingObject->GetSceneObject() != 0)
    {
        //Смещаем точку привязки камеры вперед, относительно направления взгляда героя
        const Placement &pls = pObservingObject->GetPosition();
        
        const float zoomFactor = CalcZoomFactor( position.fRod, settings.zoomFactorObserv );
        
        //Ось, направленая из спины героя
        CVec3 shift = pls.rot.GetYAxis(); 
        Normalize(&shift);
        
        //Смещаем камеру по направлению взгляда героя, с учётом зума
        shift *= -settings.anchorShiftObserv * zoomFactor;
        
        //Затем корректируем проекцию, т.е. смещаем позицию в ту же сторону в 
        //которую направлена камера для то, чтобы в центре был сам герой, а не его ботинки
        shift += position.GetCameraDir() * CalcProjShift( position.fRod );
                
        //Итоговое смещение камеры
        currDiff = pls.pos - position.vAnchor + shift;
        
        //Для того, что бы при движении героя и сильном приближении была возможность видеть
        //происходящее впереди, время лага пружины будет зависеть от зума 
        damp_time = settings.dampTimeObserv * zoomFactor;
        
        //Высоту камеры нужно брать в той точке, где стоит герой, иначе
        //иногда он не полностью попадает в кадр
        heightPos = ToVec2( pls.pos );
    }
    else
    {
      CVec3 extDiff = GetExternalLinearModifiers( position );   

      //Если это первое нажатие кнопки движения камеры, то нам нужно сразу сместить 
      //камеру на значительное расстояние. Это нужно для того, чтобы повысить 
      //отзывчивость камеры, которая без такого смещения ощутимо "сопротивляется"
      //движению
      const float curTimeDelta = externalMovedOnPrevFrame ? dt : settings.firstJumpTime;
                
      //Камера должна двигаться равномерно в любую сторону, поэтому от 
      //внешних модификаторов оставляем только направление
      Normalize(&extDiff);
      extDiff *= UpdateCurSpeed( curTimeDelta ) * curTimeDelta;
      
      //Смещение камеры должно зависеть от текущего зума, иначе, при приближении к земле,
      //очень сложно её подвинуть к конкретному предмету
      extDiff *= CalcZoomFactor( position.fRod, settings.zoomFactorMove );
      currDiff += extDiff; 
      
      damp_time = settings.dampTimeMove;
      externalMovedOnPrevFrame = !IsAlmostZero(extDiff);
      
      //Высота в конечной точке движения
      heightPos = ToVec2( position.vAnchor + currDiff );
    }
    
    //Корректируем высоту
    float curHeight;
    
    if( pScene->GetHeightsController().GetHeight(heightPos.x, heightPos.y, DEFAULT_LAYER, &curHeight, 0) )
      currDiff.z = curHeight - position.vAnchor.z;
    
    path = SmoothCritDamp( VNULL3, currDiff, linearSpeed, dt, damp_time );
    currDiff -= path;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void AdventureCameraController::CheckXYShift( CVec3& path )
  {
    const CVec3 position( pObservingObject->GetPosition().pos );

    NScene::SCameraPosition cameraPos;
    pCamera->GetPosition( &cameraPos );

    SHMatrix projViewMtx = pCamera->GetProjectiveMatrix() * pCamera->GetViewMatrix();

    CVec4 toTargetPre( position, 1.f );
    CVec4 toTargetPost( position - path, 1.f );

    CVec4 toTargetPreT;
    CVec4 toTargetPostT;

    projViewMtx.RotateHVector( &toTargetPreT, toTargetPre );
    projViewMtx.RotateHVector( &toTargetPostT, toTargetPost );

    toTargetPreT /= toTargetPreT.w;
    toTargetPostT /= toTargetPostT.w;

    float pitchTan = tan( cameraPos.fPitch / 2.0f );

    if ( fabs( toTargetPostT.y ) > (1.f - g_alternativeTrackingBorder) && fabs( toTargetPostT.y ) > fabs( toTargetPreT.y ) )
      path.y = 0;

    if ( fabs( toTargetPostT.x ) > (1.f - g_alternativeTrackingBorder) && fabs( toTargetPostT.x ) > fabs( toTargetPreT.x ) )
    {
      if ( (toTargetPostT.y - toTargetPreT.y) < 0.f )
        path.x = -1.f * Sign( toTargetPostT.x ) * path.y * pitchTan;
      else
        path.x = 0.f;
    }
  }


  namespace
  {
  float _getGaussianCoeff(int i, int j, int cnt, float step, float sigma)
  {
    NI_ASSERT(-cnt <= i && i <= cnt, "wrong idx of height-filtration matrix");
    NI_ASSERT(-cnt <= j && j <= cnt, "wrong idx of height-filtration matrix");

    // apply 3-sigma rule
    //g_hFiltSigma = g_hFiltStep * g_hFiltCnt / 3.f;

    float x = i * step;
    float y = j * step;

    float sigmaSQ = (2 *sigma * sigma);
    float power = - (x*x + y*y) / sigmaSQ;

    //А здесь разве не должен быть корень?
    //http://en.wikipedia.org/wiki/Normal_distribution
    return (1.f / (PI * sigmaSQ)) * exp(power);
  }
  }

  void AdventureCameraController::CalculateZAnchorPosition( NScene::SCameraPosition& currentPosition, CVec3 &path, float dt )
  {
    if (IsObservingMode())
    {
      float maxZStep = g_observeCamMaxZSpeed * dt;

      if (path.z >= 0.f)
      {
        path.z = min(path.z, maxZStep);
      }
      else
      {
        path.z = max(path.z, -maxZStep);
      }
      return;
    }

    //NI_ASSERT(path.z == 0.f, "some camera-logic proglem");

    // set correct height
    const NScene::IHeightsController& heights = pScene->GetHeightsController();

    float height = 0.f;
    float sum_coeff = 0.f;
    NI_ASSERT(settings.hSmoothDiscrete >= 0, "wrong filtration ponts count");
    for (int i = -settings.hSmoothDiscrete; i <= settings.hSmoothDiscrete; ++i)
    {
      for (int j = -settings.hSmoothDiscrete; j <= settings.hSmoothDiscrete; ++j)
      {
        CVec3 dest = currentPosition.vAnchor + path + CVec3(i * settings.hSmoothStep, j * settings.hSmoothStep, 0.f);
        float coeff = _getGaussianCoeff(i, j, settings.hSmoothDiscrete, settings.hSmoothStep, settings.hSmoothSigma);
        float h;

        sum_coeff += coeff;

        // modify z-coordinate
        heights.GetHeight( dest.x, dest.y, DEFAULT_LAYER, &h, 0 );

        if( gDrawCameraTerrainProjection )
        {
          Render::DebugRenderer::DrawPoint3D( dest, 0.2f, Render::Color( 0.5, 0, 0 ), true );
        }

        height += coeff * h;
      }
    }

    // arithmetic middle 
    height /= sum_coeff;

    path.z = height - currentPosition.vAnchor.z;
  }

  void AdventureCameraController::PenetratedAnchorWithBorder( NScene::SCameraPosition& currentPosition, CVec3& path )
  {
    CVec3 dest = path + currentPosition.vAnchor;

    // modify x,y-coordinates
    CVec3 border;
    if ( PenetratedWithBorder( &border, dest ) )
    {
      dest = border;
      path = dest - currentPosition.vAnchor;
    }
  }

  CVec3 AdventureCameraController::ApplySpeedLimits ( CVec3& path, float dt)
  {
    float maxL = settings.movementSpeed * dt;
    float t = path.Length() / maxL;

    if (t > 1.f)
      path /= t;

    return path / dt;
  }

  void AdventureCameraController::ApplyCameraZoom( NScene::SCameraPosition& position, float zoom ) const
  {
    NI_ASSERT(zoom >= 0.f && zoom <= settings.maxZoomFactor, "error");
    position.fPitch = settings.minPitch + (settings.maxPitch - settings.minPitch) * (1.f - zoom);
    position.fRod   = settings.ZoomToRod(zoom);
  }
  
  float AdventureCameraController::CalcCameraZoom ( NScene::SCameraPosition& position ) const
  {
    const float zoomPitch = 1.f - (position.fPitch - settings.minPitch) / (settings.maxPitch - settings.minPitch);
    const float zoomRod = settings.RodToZoom( position.fRod );
    const float zoomAvg = (zoomPitch + zoomRod) / 2;
   
    return Clamp( zoomAvg, 0.0f, settings.maxZoomFactor );
  }

  namespace
  {
  float _getPitchCoeff (float r, float RConst, float Rmax)
  {
    if (Rmax - RConst < EPS_VALUE)
      return 1.f;

    if (r < RConst)
      return 1.f;

    if (r > Rmax)
      return 0.f;

    return 1.f - (r - RConst) / (Rmax - RConst);
  }
  }

  void AdventureCameraController::LandscapeIntersection ( NScene::SCameraPosition& position )
  {
    // Если меняем принудительно из скрипта - то ландшафт не чекаем NUM_TASK
    if ( zoomManualDest >= 0 )
      return;

    // set correct height
    const NScene::IHeightsController& heights = pScene->GetHeightsController();

    CVec3 const camPos = position.GetCameraPos();
    float hCurrent = position.fRod * sin(-position.fPitch) + position.vAnchor.z;
        
    float hMax = 0.f;
    float step;
    if (settings.pitchDiscrete > 0)
        step = settings.pitchRMax / settings.pitchDiscrete;
      else
        step = 0.f;

      NI_ASSERT(settings.pitchDiscrete >= 0, "wrong filtration ponts count");
      for (int i = -settings.pitchDiscrete; i <= settings.pitchDiscrete; ++i)
      {
        for (int j = -settings.pitchDiscrete; j <= settings.pitchDiscrete; ++j)
        {
          CVec3 offset(i * step, j * step, 0.f);
          CVec3 dest = camPos + offset;

          float coeff = _getPitchCoeff(offset.Length(), settings.pitchRConst, settings.pitchRMax);
          float h;

          heights.GetHeight( dest.x, dest.y, DEFAULT_LAYER, &h, 0 );

          h += settings.minCameraHeight;

          // store maximum value
          hMax = Max(hMax, (h - hCurrent) * coeff);
        }
      }

    float hWish = hMax + position.fRod * sin(-position.fPitch);

    if ( position.fRod * sin(-position.fPitch) - hWish < -EPS_VALUE )
    {
      zoomCurr = zoomPrev;
      ApplyCameraZoom(position, zoomCurr);
    }

    while ((position.fRod * sin(-position.fPitch) - hWish < -EPS_VALUE ) && zoomCurr < 1.f)
    {
      zoomCurr = ApplyLimits( zoomCurr + 0.01f, 0.f, settings.maxZoomFactor );
      ApplyCameraZoom(position, zoomCurr);
    }
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /************************************************************************/
  /*AdvancedFreeCameraController                                          */
  /************************************************************************/

  bool ToggleObservingObject( const char *name, const vector<wstring> &params )
  {
    bool freeCam = false;
    if ((params.size() < 1) || (params.size() > 2))
    {
      freeCam = true;
    }
    else
    {
      freeCam = (bool)NGlobal::VariantValue( params[0] ).GetFloat();
    }

    if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
    {
      CPtr<AdvancedFreeCameraController> pCamCtrl = pAdvScreen->GetFreeCamera();
      if ( IsValid(pCamCtrl) )
      {
        pCamCtrl->SetObservingUnit( freeCam ? pAdvScreen->GetCurrentSelectedObject() : 0 );
      }
    }

    return true;
  }  
  AdvancedFreeCameraController::AdvancedFreeCameraController( NScene::IScene* pScene ) : 
    FreeCameraController()
    , pObservingObject( 0 )
    , currDiff( VNULL3 )
    , linearSpeed( VNULL3 )
    , pScene( pScene )
    {
      NI_ASSERT ( IsValid(pScene), "Wrong IScene! ");
    }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float AdvancedFreeCameraController::CalcZoomFactor( float fRod, float zoomFactor ) const
  {
     //Точка в которой значение коэффициента должно быть равно 1     
		 const float baseRodValue = 1;//settings.startRodValue;

     return  zoomFactor - ( zoomFactor - 1 ) * fRod / baseRodValue;     
  } 

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AdvancedFreeCameraController::CorrectHeight( CVec3& position )
	{
		const NScene::IHeightsController& heights = pScene->GetHeightsController();
		heights.GetHeight( position.x, position.y, DEFAULT_LAYER, &position.z, 0 );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdvancedFreeCameraController::SetObservingUnit( const NWorld::PFBaseUnit * pUnit )
  {
    if (pUnit && !pUnit->IsDead())
    {
      NWorld::PFBaseMovingUnit const * pMoving = dynamic_cast<NWorld::PFBaseMovingUnit const *>(pUnit);
      if (pMoving)
        SetObservedObject(pMoving->ClientObject());
      else
      {
        SetObservedObject( 0 );
        SetCameraAnchor( pUnit->GetPosition() );
      }
    }
    else
      SetObservedObject(0);
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool AdvancedFreeCameraController::SetCameraPosition( const NScene::SCameraPosition& wantedPos)
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );

	//	pCamera->SetPosition( wantedPos );
    currDiff = VNULL3;
    linearSpeed = VNULL3;
		
    // store this position to apply it on Update() as well
    forcedPosition = wantedPos;
    bForcedPosition = true;

		return true;
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdvancedFreeCameraController::SetCameraAnchor( const CVec3& anchor, bool resetObserver )
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );

		// reset observing object
		if( resetObserver )
			SetObservedObject( 0 );

    NScene::SCameraPosition wantedPos;
    pCamera->GetPosition( &wantedPos );

    wantedPos.vAnchor = anchor;
    CorrectHeight( wantedPos.vAnchor );
		return SetCameraPosition( wantedPos );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdvancedFreeCameraController::SetCameraAnchor( const PFClientBaseUnit* pObject )
	{
		NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return false; );
		NI_VERIFY( pObject, "Invalid object!", return false; );

		// get world 3d position
		return SetCameraAnchor( pObject->GetPosition().pos, pObservingObject != pObject );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool AdvancedFreeCameraController::SetObservedObject( const PFClientBaseMovingUnit * pObject )
	{
		if ( pObject == pObservingObject )
      return false;
    else
      pObservingObject = pObject;

    inputModifier.ClearDeltaFoward();
    inputModifier.ClearDeltaStrafe();

		if ( IsValid( pObservingObject ) )
      SetCameraAnchor( pObservingObject );

		return pObservingObject.GetPtr() != 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool AdvancedFreeCameraController::IsObservedObject( const PFClientBaseUnit* pObject ) const
	{
		return pObservingObject == pObject;		
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdvancedFreeCameraController::Update( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time timeDiff )
  {
    NScene::SCameraPosition const *actualWantedPos = &wantedPos;
    if (bForcedPosition)
    {
      actualWantedPos = &forcedPosition;
      bForcedPosition = false;
    }

    if (IsObservingMode())
    {
      inputModifier.ClearDeltaFoward();
      inputModifier.ClearDeltaStrafe();

      UpdateInternal( pResultPos, currentPos, *actualWantedPos, timeDiff, false );	
      actualWantedPos = pResultPos;
    }
      
    FreeCameraController::Update(pResultPos, currentPos, *actualWantedPos, timeDiff);
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void AdvancedFreeCameraController::UpdateInternal( NScene::SCameraPosition* pResultPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& wantedPos, NScene::Time dt, bool useScrolling )
  {
    NI_VERIFY( pResultPos, "Invalid result storage!", return; );
    NI_VERIFY( IsValid( pCamera ), "Invalid affected camera!", return; );

		*pResultPos = wantedPos;

    CVec3 ds = VNULL3;
    CalculateXYAnchorPosition ( *pResultPos, ds, dt );

    {
      CVec3 dv = ds / dt;
      // modify position
      pResultPos->vAnchor += ds;

      if( gDrawCameraTerrainProjection )
        Render::DebugRenderer::DrawPoint3D( pResultPos->vAnchor, 0.4f, Render::Color( 0, 0, 255 ), true );
    }
  }
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       
  
  float AdvancedFreeCameraController::CalcProjShift( float fRod ) const
  {
   /* //Значение зума в интервале [0, 1]
    const float normZood = settings.RodToZoom(fRod) / settings.maxZoomFactor;
    
    return Lerp( 
      settings.projCorretionShiftObservMaxZoom, 
      settings.projCorretionShiftObservMinZoom,
      normZood
    ); */
    return 0.8f;
  }
       
  void AdvancedFreeCameraController::CalculateXYAnchorPosition ( const NScene::SCameraPosition& position, CVec3& path, float dt )
  {
    float damp_time = 0.0f;
    CVec2 heightPos;
  
    //Если мы следим за героем
    if( IsObservingMode() && IsValid(pObservingObject) && pObservingObject->GetSceneObject() != 0)
    {
        //Смещаем точку привязки камеры вперед, относительно направления взгляда героя
        const Placement &pls = pObservingObject->GetPosition();
        
        const float zoomFactor = CalcZoomFactor( position.fRod, 1.0f );
        
        //Ось, направленая из спины героя
        CVec3 shift = pls.rot.GetYAxis(); 
        Normalize(&shift);
        
        //Смещаем камеру по направлению взгляда героя, с учётом зума
        shift *= - s_free_camera_observershift * zoomFactor;
        
        //Затем корректируем проекцию, т.е. смещаем позицию в ту же сторону в 
        //которую направлена камера для то, чтобы в центре был сам герой, а не его ботинки
        shift += position.GetCameraDir() * CalcProjShift( position.fRod );
                
        //Итоговое смещение камеры
        currDiff = pls.pos - position.vAnchor + shift;
        
        //Для того, что бы при движении героя и сильном приближении была возможность видеть
        //происходящее впереди, время лага пружины будет зависеть от зума 
        damp_time = s_free_camera_damp * zoomFactor;
        
        //Высоту камеры нужно брать в той точке, где стоит герой, иначе
        //иногда он не полностью попадает в кадр
        heightPos = ToVec2( pls.pos );
    }
    
    //Корректируем высоту
    float curHeight;
    
    if( pScene->GetHeightsController().GetHeight(heightPos.x, heightPos.y, DEFAULT_LAYER, &curHeight, 0) )
      currDiff.z = curHeight - position.vAnchor.z;
    
    path = SmoothCritDamp( VNULL3, currDiff, linearSpeed, dt, damp_time );
    currDiff -= path;
  }
}

REGISTER_CMD( free_camera_follow, NGameX::ToggleObservingObject );
REGISTER_DEV_VAR( "free_camera_damp", s_free_camera_damp, STORAGE_NONE );
REGISTER_DEV_VAR( "free_camera_observershift", s_free_camera_observershift, STORAGE_NONE );

