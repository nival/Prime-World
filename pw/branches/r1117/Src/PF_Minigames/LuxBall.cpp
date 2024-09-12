#include "stdafx.h"

#include "LuxBall.h"

#include "LuxBallHitNotification.h"
#include "LuxBallMissNotification.h"
#include "LuxBallExplodedNotification.h"
#include "LuxBallFiredNotification.h"
#include "LuxBallColorChangedNotification.h"
#include "LuxBallCreateNotification.h"
#include "LuxBallDeleteNotification.h"
#include "LuxBallInTunnelNotifications.h"

#include "EaselConstants.h"


namespace 
{
  static float BALL_IN_TUNNEL_OPACITY = 0.5f;
  REGISTER_DEV_VAR("Easel_TunnelBall_Opacity",BALL_IN_TUNNEL_OPACITY,STORAGE_NONE);
}

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBall::LuxBall( PF_Core::IWorld* _pWorld, IEaselNotifier * _pnotifier, EBallType::Enum startType, const SVector & startPos, NDb::EColor startColor ) :
PF_Core::WorldObjectBase( _pWorld, false ),
position(startPos),
color( startColor),
state( BALL_STATE_UNKNOWN ),
type( startType ),
size( EaselConst::Get_BALL_DEF_DIAMETER() ),
speed( 0 ),
direction( 1, 0 ),
coveredPath( -1 ),
pNotifier( _pnotifier ),
lastTunnelPoint( -1.0e10f ), //CRAP: this is an INT!
nextTunnelPoint( -1.0e10f ) //CRAP: this is an INT!
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBall::~LuxBall()
{
}


void LuxBall::OnAfterReset()
{
  if (state == BALL_STATE_ON_BOARD || state == BALL_STATE_ON_PLATFORM || state == BALL_STATE_IN_TUNNEL )
    InitVisual();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::InitVisual()
{
  SendBallCreatedNotification();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::OnDestroyContents()
{
  SendBallDestroyedNotification();
  PF_Core::WorldObjectBase::OnDestroyContents();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SetColor(NDb::EColor _color)
{
  color = _color;
  SendBallColorChangedNotification();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SetState(BallState _state)
{
  if ( state == _state )
    return;

  BallState _prevState = state;
  state = _state;

  switch ( _state )
  {
  case BALL_STATE_ON_PLATFORM:
    break;

  case BALL_STATE_FIRED:
    SendBallFiredNotification(); 
    break;

  case BALL_STATE_EXPLODED:
    SendBallExplodedNotification();
    break;

  case BALL_STATE_ON_BOARD:
    if(_prevState == BALL_STATE_IN_TUNNEL)        
      SendBallLeavesTunnelNotification();  

  case BALL_STATE_IN_TUNNEL: 
    SendBallEntersTunnelNotification();
    break;

  case BALL_STATE_HIT_MATCH:
    SendBallHitChainNotification(true);
    break;

  case BALL_STATE_HIT_MISSMATCH:
    SendBallHitChainNotification(false);
    break;

  case BALL_STATE_MISSED:
    SendBallMissedNotification();
    break;
  }

  return;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBall::SetCoveredPath(int64 _coveredPath)
{
  coveredPath = _coveredPath;
  return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallHitChainNotification(bool fMatch)
{
  LuxBallHitChainNotification *pNotification = new LuxBallHitChainNotification();
  pNotification->fColorMatch = fMatch;
  pNotification->wpBall = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallMissedNotification()
{
  LuxBallMissNotification *pNotification = new LuxBallMissNotification();
  pNotification->wpBall = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallExplodedNotification()
{
  LuxBallExplodedNotification *pNotification = new LuxBallExplodedNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallFiredNotification()
{
  LuxBallFiredNotification *pNotification = new LuxBallFiredNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallColorChangedNotification()
{
  LuxBallColorChangedNotification *pNotification = new LuxBallColorChangedNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallCreatedNotification()
{
  LuxBallCreateNotification *pNotification = new LuxBallCreateNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallDestroyedNotification()
{
  if ( !pNotifier )
    return;
  LuxBallDeleteNotification *pNotification = new LuxBallDeleteNotification();
  pNotification->ballPointer = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallEntersTunnelNotification()
{ 
  LuxBallEntersTunnelNotification *pNotification = new LuxBallEntersTunnelNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
} 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::SendBallLeavesTunnelNotification()
{
  LuxBallLeavesTunnelNotification *pNotification = new LuxBallLeavesTunnelNotification();
  pNotification->ball = this;

  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::GetVectorVelocityAndDir( ICollidable* _collidable, double& velocityX, double& velocityY, double& dirX, double& dirY )
{
  dirX = _collidable->Direction().x;
  dirY = _collidable->Direction().y;

  Normalize( dirX, dirY );

  velocityX = dirX * _collidable->Speed();
  velocityY = dirY * _collidable->Speed();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::GetVectorVelocity( ICollidable* _collidable, double& velocityX, double& velocityY )
{
  // $TODO [AZ] Get rid of int & int64 arithmetics

  double vx = _collidable->Direction().x;
  double vy = _collidable->Direction().y;

  Normalize( vx, vy );

  velocityX = vx * _collidable->Speed();
  velocityY = vy * _collidable->Speed();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LuxBall::GetInsertionShift( ICollidable* _other, double collisionTime )
{
  double VX1, VX2, VY1, VY2;
  double DX1, DX2, DY1, DY2;

  GetVectorVelocityAndDir( this, VX1, VY1, DX1, DY1 );
  GetVectorVelocityAndDir( _other, VX2, VY2, DX2, DY2 );

  CVec2 firstBallPoint( position.x, position.y );
  CVec2 secondBallPoint( _other->Position().x, _other->Position().y );

  firstBallPoint = firstBallPoint + CVec2( VX1, VY1 ) * collisionTime;
  secondBallPoint = secondBallPoint + CVec2( VX2, VY2 ) * collisionTime;

  CVec2 toBullet = firstBallPoint - secondBallPoint;
  Normalize( toBullet.x, toBullet.y );
  CVec2 direction = CVec2( DX2, DY2 ); 

  return direction.Dot( toBullet );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBall::GetCollisionPoint( ICollidable* _other, double collisionTime, double& collisionX, double& collisionY )
{
  double VX1, VX2, VY1, VY2;
  double DX1, DX2, DY1, DY2;

  GetVectorVelocityAndDir( this, VX1, VY1, DX1, DY1 );
  GetVectorVelocityAndDir( _other, VX2, VY2, DX2, DY2 );

  CVec2 firstBallPoint( position.x, position.y );
  CVec2 secondBallPoint( _other->Position().x, _other->Position().y );

  firstBallPoint = firstBallPoint + CVec2( VX1, VY1 ) * collisionTime;
  secondBallPoint = secondBallPoint + CVec2( VX2, VY2 ) * collisionTime;

  CVec2 centerPoint;
  centerPoint.Interpolate( firstBallPoint, firstBallPoint, 0.5f );

  collisionX = centerPoint.x;
  collisionY = centerPoint.y;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBall::GetCollisionTime( ICollidable* _other, double& collisionTime )
{
  double L = size / 2 + _other->Size() / 2;

  SVector otherPos = _other->Position();
  double dX  = position.x - otherPos.x;
  double dY  = position.y - otherPos.y;
  double VX1, VX2, VY1, VY2;

  GetVectorVelocity( this, VX1, VY1 );
  GetVectorVelocity( _other, VX2, VY2 );

  double dVX = VX1 - VX2;
  double dVY = VY1 - VY2;

  double A = dVX * dVX + dVY * dVY;
  double B = 2 * ( dX * dVX + dY * dVY );
  double C = dX * dX + dY * dY - L * L;

  const double eps = EaselConst::Get_LOGIC_FIELD_WIDTH() * 1e-6;

  //Случай точного пересечения траекторий
  if ( fabs( A ) < eps )
  {
    if ( fabs( B ) < eps )
      return false;

    collisionTime = - C / B;

    return true;
  }

  double D = B * B - 4 * A * C;

  //Correct FP-math
  if ( D < -eps )
    return false;
  if ( D < +eps)
    D = 0;

  double sqRes = sqrt( double( D ) );
  double sqResI = sqRes;
  double collisionTime1 = (-B + sqResI ) / ( 2 * A );
  double collisionTime2 = (-B - sqResI ) / ( 2 * A );

  if ( collisionTime1 < 0 )
  {
    if ( collisionTime2 < 0 )
      return false;
    
    collisionTime = collisionTime2;
    return true;
  }
  else
  {
    if ( collisionTime2 < 0 )
    {
      collisionTime = collisionTime1;
      return true;
    }

    collisionTime = Min( collisionTime1, collisionTime2 );
    return true;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBall::CanCollide() const
{
  if ( ( state == BALL_STATE_ROLL_IN ) || ( state == BALL_STATE_ROLL_OUT ))
    return false;

  int64 tunnelOffset = EaselConst::Get_BALL_DEF_DIAMETER();
  int64 diffWithTunnel = coveredPath - lastTunnelPoint;

  if ( state == BALL_STATE_IN_TUNNEL && (diffWithTunnel > tunnelOffset) )
    return false;

  return true;
}

}

BASIC_REGISTER_CLASS( PF_Minigames::ICollidable )
REGISTER_SAVELOAD_CLASS_NM( LuxBall, PF_Minigames )
