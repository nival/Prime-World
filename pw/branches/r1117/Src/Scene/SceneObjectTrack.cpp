#include "stdafx.h"
#include "SceneObjectTrack.h"

namespace NScene
{

void SceneObjectTrack::Reinit( const NDb::SceneObjectTrack* track )
{
  lastStep = false;
  dbResource = track;

  basePlacement = NULLPLACEMENT;
  animatedPlacement.Init( dbResource->placement, 0.0f );
  placement = basePlacement + animatedPlacement;

  opacityTrack.Init( &opacity, dbResource->opacity, 0.0f );
  curTime = 0.0f;
  length = animatedPlacement.EvaluateAnimationLength();
  if ( opacityTrack.IsAnimated() )
    length = Max( length, opacityTrack.GetLength() );
}

void SceneObjectTrack::Update( float timeDiff )
{
  if ( !dbResource.IsEmpty() && lastStep )
  {
    dbResource = 0;
    lastStep = false;
    return;
  }

  if ( !dbResource.IsEmpty() )
  {
    curTime += timeDiff;
    if ( curTime > length )
    {
      lastStep = true;
    }

    animatedPlacement.Step( timeDiff );
    placement = animatedPlacement;

    if ( isDirected )
    {
      const float roll = placement.rot.GetRoll();
      placement.rot = CQuat( roll, direction ^ CVec3( 0.0f, 0.0f, 1.0f ) );
    }

    opacityTrack.Step( timeDiff );
  }
}

void SceneObjectTrack::SetDirection( const CVec3& dir )
{
  isDirected = true;
  direction = dir;
}

const Placement& SceneObjectTrack::GetCurrentPlacement() const
{
  return placement;
}

float SceneObjectTrack::GetCurrentOpacity() const
{
  return opacity;
}

float SceneObjectTrack::GetLength() const
{
  return length;
}

void SceneObjectTrack::Reset()
{
	dbResource = 0;
	lastStep = false;
	curTime = 0.0f;
	length = 0.0f;
	opacity = 1.0f;
}

}