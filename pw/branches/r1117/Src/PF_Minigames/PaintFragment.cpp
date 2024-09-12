#include "stdafx.h"

#include "DBEasel.h"
#include "PaintPoint.h"
#include "PaintFragment.h"

#include "EaselMath.h"

namespace PF_Minigames
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPaintFragment::CPaintFragment( PF_Core::IWorld* _pWorld, const NDb::DBFragment& _dbFragment ) :
  PF_Core::WorldObjectBase( _pWorld, false )
{
  fragmentPoints.reserve( _dbFragment.fragmentPoints.size() );

  // need to create fragment points
  nstl::vector<NDb::Ptr<NDb::DBPainterPoint>>::const_iterator pointsIter = _dbFragment.fragmentPoints.begin();

  for (; pointsIter != _dbFragment.fragmentPoints.end(); ++pointsIter)
  {
    SVector pointCoord;
    pointCoord.x = (*pointsIter)->pointCoords.xCoord*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
    pointCoord.y = (*pointsIter)->pointCoords.yCoord*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

    CObj<CPainterPoint> point = new CPainterPoint( _pWorld, this, pointCoord, (*pointsIter)->pointCapacity, (*pointsIter)->pointColor );
    fragmentPoints.push_back( point );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPaintFragment::~CPaintFragment()
{
  fragmentPoints.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CPaintFragment::CheckIfHasColor( NDb::EColor color ) const
{
  FragmentPoints::const_iterator pointsIter = fragmentPoints.begin();
  for(; pointsIter != fragmentPoints.end(); pointsIter++)
  {
    if( (*pointsIter)->GetColor() == color )
      return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CPaintFragment::CheckIfPainted()
{
  FragmentPoints::iterator pointsIter = fragmentPoints.begin();
  for(; pointsIter != fragmentPoints.end(); pointsIter++)
  {
    if ( (*pointsIter)->HasRoom()  )
      return false;
  }

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CPaintFragment::GetColorAmount(NDb::EColor color) const
{
  int result = 0;

  FragmentPoints::const_iterator pointsIter = fragmentPoints.begin();
  for(; pointsIter != fragmentPoints.end(); pointsIter++)
  {
    const CPainterPoint& point = **pointsIter;
    if( point.GetColor() == color )
      result += point.GetAmount();
  }

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CPaintFragment::GetColorCapacity(NDb::EColor color) const
{
  int result = 0;

  FragmentPoints::const_iterator pointsIter = fragmentPoints.begin();
  for( ; pointsIter != fragmentPoints.end(); pointsIter++)
  {
    const CPainterPoint& point = **pointsIter;
    if( point.GetColor() == color )
      result += point.GetCapacity();
  }

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CPaintFragment::GetRemainCapacity( NDb::EColor color ) const
{
  return ( GetColorCapacity( color ) - GetColorAmount( color ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint* CPaintFragment::GetPoint( int point )
{
  if ( point >= GetNumPoints() )
    return false;

  return fragmentPoints[point];
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CPaintFragment::GetPointColorAmount( NDb::EColor color, int point ) const
{
  NI_VERIFY( point >= 0 && point < GetNumPoints(), "CPaintFragment: point id is out of range", return 0 );

  if( fragmentPoints[point]->GetColor() != color )
    return 0;

  return fragmentPoints[point]->GetAmount();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint* CPaintFragment::GetClosestPoint( FragmentPoints & points, const SVector & destCoord, bool notFilledOnly, NDb::EColor color, int64 & refDist, bool ignoreMagent )
{
  CPainterPoint * closest = 0;
  int64 closestRange = 0;

  for( FragmentPoints::iterator pointsIter = points.begin(); pointsIter != points.end(); pointsIter++ )
  {
    CPainterPoint * point = (*pointsIter);

    if ( !ignoreMagent && point->GetMode() == EPainterPointMode::MagnetInstalled )
      continue;

    if ( notFilledOnly )
      if( !point->HasRoom() )
        continue;

    if ( color != NDb::COLOR_ANY )
      if ( point->GetColor() != color )
        continue;

    int64 range = CalculateDistance( destCoord, point->GetCoord() );

    if ( closest )
      if( range > closestRange )
        continue;

    closestRange = range;
    closest = point;
  }

  if ( closest )
  {
    refDist = closestRange;
    return closest;
  }

  refDist = 0;
  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint * CPaintFragment::GetClosestPoint( const SVector & destCoord, bool notFilledOnly, NDb::EColor color, int64 & refDist, bool ignoreMagent )
{
  return GetClosestPoint( fragmentPoints, destCoord, notFilledOnly, color, refDist, ignoreMagent );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint * CPaintFragment::GetLeastFilledPoint()
{
  CPainterPoint * best = 0;
  int biggestRoom = 0;

  for( FragmentPoints::iterator pointsIter = fragmentPoints.begin(); pointsIter != fragmentPoints.end(); pointsIter++ )
  {
    CPainterPoint * point = (*pointsIter);

    int room = point->GetRoomLeft();

    if ( !best || ( room > biggestRoom ) )
    {
      best = point;
      biggestRoom = room;
    }
  }

  return best;
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( CPaintFragment, PF_Minigames )
