#include "stdafx.h"
#include "LuxPath.h"

#include "EaselTrajectory.h"
#include "EaselConstants.h"

#include "LuxGameLogic.h"

namespace PF_Minigames
{

  
LuxPath::LuxPath( PF_Core::IWorld* _pWorld, int _pathID, int _level, const NDb::DBEaselPath * _path )
: PF_Core::WorldObjectBase( _pWorld, false )
, pathID( _pathID )
, level( _level )
, dbPath( _path )
{
  CreateTrajectory();
}

LuxPath::~LuxPath()
{

}

void LuxPath::CreateTrajectory()
{
  nstl::vector<SVector> points;
  points.reserve( dbPath->spline.cpnum );

  vector<NDb::DBLogicPoint>::const_iterator it = dbPath->spline.points.point.begin();
  vector<NDb::DBLogicPoint>::const_iterator last = dbPath->spline.points.point.end();

  for ( ;it != last; ++it )
  {
    points.push_back(SVector(it->x*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER(),
                             it->y*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER()));

  }

  trajectory = new PolylineTrajectory( GetWorld() );
  trajectory->CreateFromBSpline( dbPath->spline.degree, points, EaselConst::Get_POLYLINE_SEGMENT_SIZE() );
}

PolylineTrajectory* LuxPath::GetTrajectory() const
{
  return trajectory;
}

const nstl::vector<NDb::DBTunnel>& LuxPath::GetTunnels() const
{
  return dbPath->splineData.tunnels.tunnel;
}


const NDb::DBEaselChains* LuxPath::GetChainsData() const
{
  return dbPath->splineData.chainparams[level];
}

const NDb::AnimatedPlacement& LuxPath::GetStartOffset() const 
{ 
  return dbPath->splineData.startPoint.placement; 
}

const NDb::AnimatedPlacement& LuxPath::GetEndOffset() const 
{ 
  return dbPath->splineData.endPoint.placement; 
};

bool LuxPath::IsPointInsideTunnel( int64 _point, LuxGameLogic* _gameLogic ) const
{
  float startOffset =_gameLogic->GetGameData()->commonParams->tunnels.startPointOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  float endOffset = _gameLogic->GetGameData()->commonParams->tunnels.endPointOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

  nstl::vector<NDb::DBTunnel>::const_iterator it = dbPath->splineData.tunnels.tunnel.begin();
  nstl::vector<NDb::DBTunnel>::const_iterator last = dbPath->splineData.tunnels.tunnel.end();

  for ( ; it != last ; ++it )
  {
    int64 _begin = it->begin * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
    int64 _end   = it->end * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

    if ( ( _begin + startOffset <= _point ) && ( _point <= _end + endOffset ) )
      return true;
  }

  return false;
}


}

REGISTER_SAVELOAD_CLASS_NM( LuxPath, PF_Minigames )
