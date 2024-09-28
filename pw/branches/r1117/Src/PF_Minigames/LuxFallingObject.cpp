#include "stdafx.h"

#include "LuxFallingObject.h"
#include "EaselConstants.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SInitialConditions::SInitialConditions( const SVector & pos, const SVector & vel, const SVector & accel ) :
position( pos ), velocity( vel ), acceleration( accel)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SInitialConditions::SInitialConditions( const SVector & from, const SVector & to, int upvelocity, int gravity ) :
position( from ),
velocity( 0, -upvelocity ),
acceleration( 0, gravity )
{
  const double s = to.y - from.y;
  const double D = sqr( upvelocity ) + 2.0f * gravity * s;

  if ( D <= 1e-3 )
    return;

  const double t0 = ( (double)upvelocity + sqrt( D ) ) / (double)gravity;
  const double t1 = ( (double)upvelocity - sqrt( D ) ) / (double)gravity;

  double t = 0;
  if ( ( t0 > 0 ) && ( t1 > 0 ) )
    t = min( t0, t1 );
  else if ( t0 > 0 )
    t = t0;
  else if ( t1 > 0 )
    t = t1;
  else
    return;

  if ( t < 1e-3 )
    return;

  velocity.x = ( to.x - from.x ) / t;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLuxFallingObject::CLuxFallingObject( PF_Core::IWorld* _pWorld, const SInitialConditions & start ) :
EaselWorldObject( _pWorld ),
position( start.position ),
velocity( start.velocity ),
acceleration( start.acceleration ),
currentTime( 0 ),
isPicked( false )
{
}

CLuxFallingObject::CLuxFallingObject( PF_Core::IWorld* _pWorld, const CLuxFallingObject& rhs ) :
EaselWorldObject( _pWorld ),
position(rhs.position),
velocity(rhs.velocity),
acceleration(rhs.acceleration),
currentTime(rhs.currentTime),
isPicked(rhs.isPicked)
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLuxFallingObject::Update( int deltaTime )
{
  currentTime += deltaTime;

  double dt = deltaTime * 1e-3;
  velocity.x += (int)( 0.5 + dt * acceleration.x );
  velocity.y += (int)( 0.5 + dt * acceleration.y );

  position.x += (int)( 0.5 + dt * velocity.x );
  position.y += (int)( 0.5 + dt * velocity.y );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLuxFallingObject::IsInValidPosition() const
{
  if ( position.x < 0 )
    return false;
  if ( position.x > EaselConst::Get_LOGIC_FIELD_WIDTH() )
    return false;

  if ( position.y < -EaselConst::Get_LOGIC_FIELD_HEIGHT() ) //Let coin jump out above board
    return false;
  if ( position.y > EaselConst::Get_LOGIC_FIELD_HEIGHT() )
    return false;

  return true;
}

}

REGISTER_SAVELOAD_CLASS_NM( CLuxFallingObject, PF_Minigames );
