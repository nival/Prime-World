#include "stdafx.h"
#include "PFClientBaseMovingUnit.h"
#include "PFAIWorld.h"
#include "PFBaseMovingUnit.h"
#include "../System/InlineProfiler.h"
#include "../System/Spline.h"
#include "../Core/Scheduler.h"
#include "AdventureScreen.h"
#include "../Terrain/Terrain.h"
//#define DEBUG_HEIGHT		1

using namespace NScene;

#define HEIGHT_DELTA_THRESHOLD 0.01f

namespace
{
  DEV_VAR_STATIC bool g_smoothTurnsEnabled = false;
  DEV_VAR_STATIC float g_smoothTurnsThreshold = 25.0f;
  DEV_VAR_STATIC float g_smoothTurnsSpeedMul = 5.5f;

  class RotSpeedInitializer
  {
    float value;
    bool  initialized;
  public:
    RotSpeedInitializer() : initialized( false ), value( 0.0f ) {}
    void Init( PF_Core::IWorld const* pIWorld, bool vertical )
    {
      if( initialized )
        return;

      NWorld::PFWorld const* pWorld = dynamic_cast<NWorld::PFWorld const*>(pIWorld);
      if( NWorld::PFAIWorld const* pAIWorld = pWorld ? pWorld->GetAIWorld() : NULL )
      {
        if ( vertical )
        {
          value = pAIWorld->GetAIParameters().rotationSpeedZ;
        }
        else
        {
          value = pAIWorld->GetAIParameters().rotationSpeed;
        }
        initialized = true;
      }
    }

    inline operator float () const { return value; }
  }g_rotSpeed, g_rotSpeedZ;
}

namespace NGameX
{

float NormalizeAngle(float angle)
{
  NI_ASSERT(-1000.0f < angle && angle <= 1000.0f, "Strange angle");
  if (-FP_PI <= angle && angle < FP_PI)
    return angle;
  else if (angle > 0)
    return fmodf(angle + FP_PI, FP_2PI) - FP_PI;
  else // angle < 0 -- fmod() produces undesirable result
    return -fmodf(-angle + FP_PI, FP_2PI) + FP_PI;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const float NON_FLIGHT_HEIGHT = -10000; // deep underground

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientBaseMovingUnit::PFClientBaseMovingUnit( const PF_Core::WorldObjectRef &pWO, const CreatePars &cp )
  : PFClientBaseUnit(pWO, cp)
  , isMove( false )
  , isStopPending( false )
  , isFlying( false )
  , isFlyingByTrajectory( false )
  , isFlyingHeightAbsolute( false )
  , speed( 0.0f )
  , heightSpeed( 0.0f )
  , turnSpeed( 0.0f )
  , curAngle( 0.0f )
  , dstAngle( 0.0f )
  , curAngleZ( 0.0f )
  , dstAngleZ( 0.0f )
  , rotSpeed( 0.0f )
  , rotSpeedZ( 0.0f )
  , destination( GetSceneObject()->GetPosition().pos )
  , dstHeight( NON_FLIGHT_HEIGHT )
  , curHeight( NON_FLIGHT_HEIGHT )
  , flightStartHeight( NON_FLIGHT_HEIGHT )
  , flightEndHeight( NON_FLIGHT_HEIGHT )
  , flightTime( 0.0f )
  , flightDuration( 0.0f )
  , flightHeightModifier( 0.0f )
{
  NI_PROFILE_FUNCTION

	// Invisible by default (compared with base class)
	GetSceneObject()->SetupForLighting(); // still here, but may remove in future [3/5/2010 smirnov]
	
  g_rotSpeed.Init( pWO->GetWorld(), false );
  g_rotSpeedZ.Init( pWO->GetWorld(), true );

  //On terrain
  Placement newposrot = GetSceneObject()->GetPosition();
  newposrot.pos.z = 0.0f;
  UpdatePlacement( newposrot );

	if ( WorldObject()->IsVisibleForFaction( AdventureScreen::Instance()->GetPlayerFaction() ) )
	{
		bVisible = true;
		pSceneObjectsHolder->SetVisibility(true);
		GetSceneObject()->GetCollision()->SetEnabled(true);
		if ( GetSceneObject()->GetSmallCollision() )
		{
			GetSceneObject()->GetSmallCollision()->SetEnabled(true);
		}
	}
	else
	{
		bVisible = false;
		pSceneObjectsHolder->SetVisibility(false);
		GetSceneObject()->GetCollision()->SetEnabled(false);
		if ( GetSceneObject()->GetSmallCollision() )
		{
			GetSceneObject()->GetSmallCollision()->SetEnabled(false);
		}
	}

  betaSpline3D.Init( 1.0f, -1.0f );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFClientBaseMovingUnit::LookTo( const CVec2& target, bool instantRotate, float time /* = 0.0f */ )
{
  CVec2 dir = target - GetSceneObject()->GetPosition().pos.AsVec2D();
  if ( instantRotate )
  {
    if ( fabs2( dir ) > EPS_VALUE )
    {
      Placement newposrot = GetSceneObject()->GetPosition();
      float pitch = 0, yaw = 0, roll = 0;
      dstAngle = curAngle = atan2( dir.x, -dir.y );
      newposrot.rot.DecompEulerAngles( &yaw, &pitch, &roll );
      newposrot.rot.FromEulerAngles( dstAngle, pitch, roll );
      GetSceneObject()->SetPositionAndRotation( newposrot );
    }
  }
  else
  {
    CalculateRotationParams( dir, time );
  }
}

void PFClientBaseMovingUnit::TurnBy( CQuat const& quat )
{
  CalculateRotationParams( quat.GetYaw() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::CalculateRotationParams( const CVec2& dir, float time /* = 0.0f */ )
{
  // calculate rotation params
  if ( fabs2( dir ) > fabs2( 0.02f ) )
  {
    CalculateRotationParams( atan2( dir.x, -dir.y ), time );
  }
}

void PFClientBaseMovingUnit::CalculateRotationParams( float angle, float time /* = 0.0f */ )
{
  // get current rotation
  float tmpPitch = 0, tmpRoll = 0;
  GetSceneObject()->GetPosition().rot.DecompEulerAngles( &curAngle, &tmpPitch, &tmpRoll );

  dstAngle = angle;

  // get angle delta
  float rotDelta  = NormalizeAngle(dstAngle - curAngle);

  // compute rotation speed
  if ( time > EPS_VALUE )
    rotSpeed = fabs(rotDelta) / Max( time, pScene->GetStepLengthInSeconds() );
  else
    //rotSpeed = Min( ToRadian(g_rotSpeed), fabs(rotDelta) / pScene->GetStepLengthInSeconds() );
  {
    rotSpeed = Min( ToRadian(g_rotSpeed), fabs(rotDelta) / pScene->GetStepLengthInSeconds() );

    if ( g_smoothTurnsEnabled && isMove && fabs(rotDelta) < ToRadian(g_smoothTurnsThreshold) )
    {
      float x = rotDelta*1.4f;
      rotSpeed = Min( rotSpeed, (x*x)*g_smoothTurnsSpeedMul );
    }
  }

  rotSpeed *= ((rotDelta  < 0.0f) ? -1 : 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::OnMoveTo( const CVec2& newpos, bool animate )
{
  // @BVS@TODO Remove hacka after another way of client creation
  if ( !GetSceneObject() )
  {
    return;
  }

  CVec2 dir = newpos - GetSceneObject()->GetPosition().pos.AsVec2D();

	if ( fabs2( dir ) < EPS_VALUE )
  {
    return; // movement amount is too small
  }

  isStopPending = false;
  if ( !isMove )
  {
    isMove = true;
    OnStartMoving( animate );
  }

  destination = CVec3( newpos, 0.0f );
  //TODO Проблема в задаче NUM_TASK
  //float rawSpeed = WorldObject() ? WorldObject()->GetUnitSpeed() : 10.0f;
  float rawSpeed = 10.0f;
  speed       = rawSpeed * fabs( dir );

  CalculateRotationParams( dir );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float PFClientBaseMovingUnit::GetTerrainHeight( const CVec2& pos ) const
{
  float result = 0.0f;

	const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return 0.0f );

  const bool heightTaken = pSO->GetScene()->GetHeightsController().GetHeight( pos.x, pos.y, 1, &result, 0 );
  NI_VERIFY( heightTaken, "Error in terrain height estimation!", return 0.0f );

  return result;
}

float PFClientBaseMovingUnit::GetTerrainHeight() const
{
	const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return 0.0f );

  CVec3 pos = pSO->GetPosition().pos;
  return GetTerrainHeight( CVec2( pos.x, pos.y ) );
}

CVec3 PFClientBaseMovingUnit::GetTerrainNormal( const CVec2& pos ) const
{
  CVec3 result;
  float height;

  const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return CVec3( 0.0f, 0.0f, 0.0f ) );

  const bool normalTaken = pSO->GetScene()->GetHeightsController().GetHeight( pos.x, pos.y, 1, &height, &result );
  NI_VERIFY( normalTaken, "Error in terrain height estimation!", return CVec3( 0.0f, 0.0f, 1.0f ) );

  return result;
}

CVec3 PFClientBaseMovingUnit::GetTerrainNormal() const
{
  const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return CVec3( 0.0f, 0.0f, 0.0f ) );

  CVec3 pos = pSO->GetPosition().pos;
  return GetTerrainNormal( CVec2( pos.x, pos.y ) );
}


CVec3 PFClientBaseMovingUnit::GetTerrainNormalSmooth( const CVec2& pos ) const
{
  CVec3 result;

  const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return CVec3( 0.0f, 0.0f, 0.0f ) );

  const Terrain::GridConstants& params = pSO->GetScene()->GetTerrain()->GetGridConstants();
  /*const float nTileX = pos.x / params.metersPerTile;
  const float nTileY = pos.y / params.metersPerTile;
*/
  CVec3 defaultNormal( 0.0f, 0.0f, 1.0f );

  
  if ( !WorldObject()->IsHero() && cashedNormal != defaultNormal )
  {
    const float delta = params.metersPerTile*0.3f;
    if ( fabs(pos.x - cashedTilePos.x) < delta && fabs(pos.y - cashedTilePos.y) < delta )
      return cashedNormal;
  }

  const int numCtrlTiles = 3; // 3*3 = 9 tiles
  float u;
  float v;
  float ctrlPoints[16];        // (3+1)^2 = 16 points for 9 tiles
  const bool pointsTaken = pSO->GetScene()->GetHeightsController().GetHeightsOfSquareArea( numCtrlTiles, pos.x, pos.y, u, v, ctrlPoints );
  NI_VERIFY( pointsTaken, "Error in terrain height estimation!", return CVec3( 0.0f, 0.0f, 1.0f ) );

  CBetaSpline3D spline = betaSpline3D;
  spline.GetNormal( &result, u, v, ctrlPoints );
  
  cashedTilePos.x = pos.x;
  cashedTilePos.y = pos.y;
  cashedNormal = result;

  return result;
}

CVec3 PFClientBaseMovingUnit::GetTerrainNormalSmooth() const
{
  NI_PROFILE_FUNCTION

  const SceneObject *pSO = GetSceneObject();
  NI_VERIFY( pSO, "Can't get current height without correct scene object!", return CVec3( 0.0f, 0.0f, 0.0f ) );

  return GetTerrainNormalSmooth( pSO->GetPosition().pos.AsVec2D() );
}


void PFClientBaseMovingUnit::SetFlightHeight( float height, bool absolute )
{
  isFlyingHeightAbsolute = absolute;

  if ( !isFlyingHeightAbsolute )
  {
    height += GetTerrainHeight();
  }

  dstHeight = height;

  const float delta = dstHeight - curHeight;
  if ( fabs2( delta ) < fabs2( HEIGHT_DELTA_THRESHOLD ) )
  {
    heightSpeed = 0.0f;
    curHeight = dstHeight;
  }
  else
  {
    heightSpeed = delta / pScene->GetStepLengthInSeconds();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::SetFlightAngle(float angle)
{
  dstAngleZ = angle;

  // compute rotation speed
  float rotDeltaZ = NormalizeAngle( dstAngleZ - curAngleZ );
  rotSpeedZ = Min( ToRadian( g_rotSpeedZ ), fabs( rotDeltaZ ) / pScene->GetStepLengthInSeconds() );
  rotSpeedZ *= rotDeltaZ < 0.0f ? -1 : 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::StartFlying()
{
  isFlying = true;
  curHeight = GetTerrainHeight();
  SetFlightHeight( curHeight, true );
  isFlyingByTrajectory = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::StartFlying( NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> trajectory,
                                          NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> angle,
                                          float flightDuration_, float heightModifier, const CVec2& startPos, const CVec2& endPos, NDb::EThrowType _flightType )
{
  curHeight = GetTerrainHeight();
  SetFlightHeight( curHeight, true );

  flightStartHeight = GetTerrainHeight( startPos );
  flightEndHeight = GetTerrainHeight( endPos );

  heightWrapper.Init( &dstHeight, trajectory, 0.0f );
  angleWrapper.Init( &dstAngleZ, angle, 0.0f );

  flightTime = 0.0f;
  flightDuration = flightDuration_;
  flightHeightModifier = heightModifier;

  flightType = _flightType;

  isFlying = true;
  isFlyingByTrajectory = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::StopFlying()
{
  SetFlightHeight( 0.0f, false );
  SetFlightAngle( 0.0f );

  isFlying = false;
  isFlyingByTrajectory = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::UpdateMovement( const float timeDiff )
{
  NI_PROFILE_FUNCTION

  NScene::SceneObject* const pSceneObject = GetSceneObject();
  NI_VERIFY(pSceneObject, "Invalid scene object", return);
  Placement newposrot = pSceneObject->GetPosition();
  bool canStop = true;

  if ( isMove )
  {
    CVec3 deltaPos = destination - newposrot.pos;
    deltaPos.z = 0;
    float dist   = fabs( deltaPos );
    float toMove = speed * timeDiff;
    if ( dist > toMove )
    {
      newposrot.pos += deltaPos * toMove / dist;
      canStop = false;
    }
    else
    {
      newposrot.pos = destination;
    }
    if ( speed < 0.001f ) // this may happen when OnMoveTo's target is near unit's position; note: EPS_VALUE is too small
      canStop = true;
  }

  float angleDelta  = NormalizeAngle( curAngle  - dstAngle  );
  float angleDeltaZ = NormalizeAngle( curAngleZ - dstAngleZ );

  const bool needRotate  = fabs( angleDelta  ) > EPS_VALUE;
  bool needRotateZ = fabs( angleDeltaZ ) > EPS_VALUE;

  if ( needRotate )
  {
    float toRotate  = rotSpeed * timeDiff;

    if ( fabs( angleDelta ) > fabs( toRotate ) )
    {
      curAngle += toRotate;
    }
    else
    {
      curAngle = dstAngle;	// stop rotation
    }
    curAngle = NormalizeAngle( curAngle );
  }

  if ( needRotateZ )
  {
    float toRotateZ = rotSpeedZ * timeDiff;

    if ( fabs( angleDeltaZ ) > fabs( toRotateZ ) )
    {
      curAngleZ += toRotateZ;
    }
    else
    {
      curAngleZ = dstAngleZ;	// stop z rotation
    }
    curAngleZ = NormalizeAngle( curAngleZ );
  }

  if ( isFlyingByTrajectory )
  {
    if ( angleWrapper.IsAnimated() )
    {
      angleWrapper.Step( timeDiff / flightDuration * angleWrapper.GetLength()  );
    }
    else if ( flightType == NDb::THROWTYPE_JUMP )
    {
      float diff = heightWrapper.GetDiff();
      dstAngleZ = ToDegree( atan( diff ) );
    }
    dstAngleZ = -ToRadian( dstAngleZ );
    if ( fabs(curAngleZ - dstAngleZ) > EPS_VALUE )
    {
      curAngleZ = dstAngleZ;
      needRotateZ = true;
    }
  }

  if ( needRotate || needRotateZ )
  {
    newposrot.rot.FromEulerAngles( curAngle, 0, -curAngleZ );
  }

  //applying terrain normal
  if ( !isFlying )
  {
   float normalLevelling = WorldObject()->GetNormalLevelling();
   NI_DATA_VERIFY( ( ( normalLevelling >= 0.0f ) && ( normalLevelling <= 1.0f ) ), "normalLevelling should be in [0,1]!", normalLevelling = 0.0f );

   if ( normalLevelling > 0.0f )
   {
     CVec3 defaultNormal( 0.0f, 0.0f, 1.0f );
     CVec3 normal( defaultNormal );

     CVec3 terrainNormal = GetTerrainNormalSmooth();

     bool normalizeSuccess = Normalize( &terrainNormal );
     NI_VERIFY( normalizeSuccess, "Bad terrain normal!", terrainNormal = defaultNormal );

     normal = Lerp( defaultNormal, terrainNormal, normalLevelling );

     newposrot.rot.FromEulerAngles( newposrot.rot.GetYaw(), 0.0f, 0.0f );
     newposrot.rot.FromToRotation( defaultNormal, normal );
   }
  }

  bool heightChanged = ( heightSpeed != 0.0f );
  if ( heightChanged )
  {
    float delta2 = fabs2( dstHeight - curHeight );
    float toMove = timeDiff * heightSpeed;
    if ( delta2 < fabs2( HEIGHT_DELTA_THRESHOLD ) || fabs2( toMove ) >= delta2 )
    {
			curHeight   = dstHeight;
			heightSpeed = 0.0f;
    }
    else
    {
      curHeight += toMove;
    }
  }

  if ( isFlyingByTrajectory )
  {
    if ( heightWrapper.IsAnimated() )
    {
      heightWrapper.Step( timeDiff / flightDuration * heightWrapper.GetLength()  );
      dstHeight *= flightHeightModifier;
    }

    flightTime += timeDiff;
    float frac = flightTime / flightDuration;
    if ( frac > 1.0f )
    {
      frac = 1.0f;
    }
    dstHeight += Lerp( flightStartHeight, flightEndHeight, frac );
    if ( fabs(curHeight - dstHeight) > EPS_VALUE )
    {
      curHeight = dstHeight;
      heightChanged = true;
    }
  }

  if ( !heightChanged && !isFlying )
  {
    curHeight = dstHeight = NON_FLIGHT_HEIGHT;
  }

#if DEBUG_HEIGHT
  float h = newposrot.pos.z;
#endif
  if ( isMove || needRotate || needRotateZ || heightChanged )
  {
    newposrot.pos.z = 0;
    UpdatePlacement(newposrot);
#if DEBUG_HEIGHT
    h = newposrot.pos.z;
#endif
    if ( curHeight > newposrot.pos.z )
    {
      newposrot.pos.z = curHeight;
      SetPlacement(newposrot);
    }
  }

#if DEBUG_HEIGHT
  Render::DebugRenderer::DrawText3D(NStr::StrFmt(
		"Terrain: %.1f\n"
		"CurrH: %.1f\n"
		"Height: %.1f -> %.1f\n"
		"Speed: %.1g",
		h, newposrot.pos.z, curHeight, dstHeight, heightSpeed),
		newposrot.pos + CVec3(0,0,8), 14, Render::Color(255,255,255));
#endif

  // stop animation when needed
  if ( isStopPending && canStop )
  {
    isMove      = isStopPending = false;
    destination = newposrot.pos;
    OnStopped();
  }

  if ( WorldObject()->IsMount() && pSceneObject )
  {
    pSceneObject->UpdateForced( 0.0f, false, IsVisible() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::OnTeleportTo( const CVec2& target, bool needReplace /* = false */ )
{
	SceneObject *pSO = GetSceneObject();
  if( !pSO )
  {
    return;
  }

  Placement placement = pSO->GetPosition();

  placement.rot.FromEulerAngles( NormalizeAngle( curAngle ), 0, 0 );

  placement.pos = CVec3( target, 0.0f );
  
  if ( !isFlying )
  {
    if ( needReplace )
      UpdatePlacement( placement );
  }
  else
  {
    if ( !isFlyingHeightAbsolute )
    {
      const float heightDiff = GetTerrainHeight( target ) - GetTerrainHeight();
      dstHeight += heightDiff;
      curHeight += heightDiff;
    }

    placement.pos.z	= curHeight;

    if ( needReplace )
      SetPlacement( placement );
  }

	// Ensure first full update
  if ( pSO->GetScene() )
	{
    pSO->MarkAsVisible();
    pSO->UpdateForced( 0.0f, false, IsVisible() );
	}

  UpdateVisibility();

  // stop moving
  dstAngle    = curAngle;
  isMove      = isStopPending = false;
  destination = placement.pos;

  OnStopped();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::OnHide(bool hide)
{
  if ( hide )
  {
    SceneObject *pSO = GetSceneObject();
    if( pSO )
    {
      // Skip all transactions 
      pSO->Update( pScene->GetStepLength(), true );
    }
  }

  PFClientBaseUnit::OnHide(hide);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::OnStop()
{
  isStopPending = isMove;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::Stand()
{
  // stop any updates!
  dstAngle = curAngle;
  isMove   = isStopPending = false;

  if( SceneObject *pSO = GetSceneObject())
  {
    Placement placement = pSO->GetPosition();
    destination         = placement.pos;
  }

  OnStopped();
}

void PFClientBaseMovingUnit::SynchronizeVisualPosition()
{
  OnTeleportTo( WorldObject()->GetPosition().AsVec2D() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseMovingUnit::SetRotation( CQuat const &quat )
{
  dstAngle = curAngle = quat.GetYaw();
  PFClientLogicObject::SetRotation( quat );
}

} // namespace

//////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR("use_smooth_turns", g_smoothTurnsEnabled,    STORAGE_NONE);
REGISTER_DEV_VAR("smooth_turns_threshold", g_smoothTurnsThreshold,    STORAGE_NONE);
REGISTER_DEV_VAR("smooth_turns_speedmul", g_smoothTurnsSpeedMul,    STORAGE_NONE);