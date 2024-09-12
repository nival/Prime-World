#include "stdafx.h"

#include "LuxDef.h"

#include "../System/lerp.h"

#include "EaselTrajectory.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class CBSplineTrajectory implementation
//
//////////////////////////////////////////////////////////////////////////
CBSplineTrajectory::CBSplineTrajectory(int iDegree,const SVector *pCP,int numCPs)
                   : curveDegree(iDegree),
                     splineLength(0)
{
    NI_ASSERT(pCP != NULL,"Passed BSpline control points array is NULL");

    for(int i=0; i<numCPs; i++)
        currCP[i] = *(pCP+i);

    numControlPoints = numCPs;

    // creating nodes vector
    CreateNodesVector();

    // creating calculated points vector
    //vecSplinePoints.reserve(POINT_CONTAINER_CAPACITY);  
    InitInternalPointContainer();
}

CBSplineTrajectory::~CBSplineTrajectory()
{
    curveDegree      = 0;
    numControlPoints = 0;
    splineLength     = 0;

    // clearing storages
    ClearCPStorage();
    ClearNodeVector();

    // clearing calculated points vector
    UninitInternalPointContainer();
}

void CBSplineTrajectory::ClearCPStorage()
{
    for(int i=0; i<MAX_NUM_CONTROL_POINTS;i++)
        currCP[i] = SVector(0,0);
}

void CBSplineTrajectory::ClearNodeVector()
{
    for(int i=0; i<MAX_NUM_CONTROL_POINTS+5;i++)
        nodeVector[i] = 0;
}

bool CBSplineTrajectory::CheckIntersectsX(int x1,int x2, int target)
{
    if((target > x1 && target > x2) || (target < x1 && target < x2))
        return false;
    else
        return true;
}

bool CBSplineTrajectory::CheckIntersectsY(int y1,int y2, int target)
{
    if((target > y1 && target > y2) || (target < y1 && target < y2))
        return false;
    else
        return true;
}

int CBSplineTrajectory::FindYIntersectionPoint(SplinePoint pt1,SplinePoint pt2,int x)
{
    if(pt1.y == pt2.y)
        return pt1.y;

    int deltaY = abs((pt1.x-x)*(pt2.y-pt1.y)/(pt2.x-pt1.x));
    if(pt1.y > pt2.y)
        return pt2.y+deltaY;
    else 
        return pt1.y+deltaY;
}

int  CBSplineTrajectory::FindXIntersectionPoint(SplinePoint pt1,SplinePoint pt2,int y)
{
    if(pt1.x == pt2.x)
        return pt1.x;

    int deltaX = abs((pt2.y-y)*(pt2.x-pt1.x)/(pt2.y-pt1.y));
    if(pt1.x > pt2.x)
        return pt2.x+deltaX;
    else
        return pt1.x+deltaX;
}

int64 CBSplineTrajectory::GetLenght()
{
    return splineLength;
}

int CBSplineTrajectory::GetCoordsByLenght(int64 length,
                                          /*out*/SVector &refCoords)
{
    // [@Pavel <GnoM> Cherniavski@] TODO: Данный метод будет вызываться чаще всего
    // его нужно однозначно оптимизировать .....
    
    if ( splinePointsMap.empty()  )
        return LUX_ERROR;

    if(length == 0)
    {
      refCoords.x = splinePointsMap[0].x;
      refCoords.y = splinePointsMap[0].y;
      return LUX_OK;
    }

    // we need to find borders, containing current coordinates 
    MPIter mapIterA = splinePointsMap.begin();  // A point
    MPIter mapIterB = splinePointsMap.begin();  // B point
    for(; mapIterB != splinePointsMap.end(); mapIterB++)
    {
        // checking is coords are inside the interval
        if(length >= mapIterA->first && length < mapIterB->first)
        {
             // got interval
             int64 lengthInside = length-mapIterA->first;
             int64 lenghtInterval = mapIterB->first-mapIterA->first;

             int x1 = mapIterA->second.x;
             int y1 = mapIterA->second.y;

             int x2 = mapIterB->second.x;
             int y2 = mapIterB->second.y;

             refCoords.x = ((x2-x1)*lengthInside/lenghtInterval) + x1; 
             refCoords.y = ((y2-y1)*lengthInside/lenghtInterval) + y1;
                              
             return LUX_OK;
        }

        mapIterA = mapIterB;
    }

    if(length == mapIterA->first)
    {
      refCoords.x = mapIterA->second.x;
      refCoords.y = mapIterA->second.y;
      return LUX_OK;
    }

    // if we are here, that means the length is bigger than spline length
    return LUX_LENGHT_TOO_BIG;
}

int CBSplineTrajectory::GetTangentByLenght(int64 length, /*out*/SVector &refTangent)
{
  // [@Pavel <GnoM> Cherniavski@] TODO: Данный метод будет вызываться чаще всего
  // его нужно однозначно оптимизировать .....

  if(splinePointsMap.size() < 2)
    return LUX_ERROR;

  MPIter mapIterA = splinePointsMap.begin();  // A point
  MPIter mapIterB = mapIterA;  // B point
  ++mapIterB;

  if(length <= mapIterA->first)
  {
    refTangent.x = mapIterB->second.x - mapIterA->second.x;
    refTangent.y = mapIterB->second.y - mapIterA->second.y;

    return LUX_OK;
  }

  // we need to find borders, containing current coordinates 
  for(; mapIterB != splinePointsMap.end(); mapIterB++)
  {
    // checking is coords are inside the interval
    if(length >= mapIterA->first && length < mapIterB->first)
    {

      refTangent.x = mapIterB->second.x - mapIterA->second.x;
      refTangent.y = mapIterB->second.y - mapIterA->second.y;

      return LUX_OK;
    }

    mapIterA = mapIterB;
  }

  // if we are here, that means the length is bigger than spline length
  return LUX_LENGHT_TOO_BIG;
}


void CBSplineTrajectory::InitInternalPointContainer()
{
  splinePointsMap.clear();

  CVec2 coordSecond;
  CVec2 coordFirst = currCP[0].ToCVec2();	

  int64 lenghtComplete = 0;    // complete spline lenght

  for(double i=0; i<nodeVector[curveDegree+numControlPoints];i+=0.01)   // точность прохода 
  {
    coordSecond = CalculateDeBoor(curveDegree, floor(i), i);

    // calculating line length
    double deltaX = abs(coordSecond.x-coordFirst.x);
    double deltaY = abs(coordSecond.y-coordFirst.y);

    lenghtComplete += sqrt(deltaX*deltaX+deltaY*deltaY);

    SplinePoint splinePoint;
    splinePoint.x = coordSecond.x;
    splinePoint.y = coordSecond.y;
    
    // adding new point to container    
    splinePointsMap.insert(make_pair(lenghtComplete,splinePoint));
            
    coordFirst = coordSecond;
  }

  // processing final control point
  double deltaX = abs(coordFirst.x-currCP[numControlPoints-1].x);
  double deltaY = abs(coordFirst.y-currCP[numControlPoints-1].y);

  lenghtComplete += sqrt(deltaX*deltaX+deltaY*deltaY);
      
  SplinePoint splinePoint;
  splinePoint.x = currCP[numControlPoints-1].x;
  splinePoint.y = currCP[numControlPoints-1].y;

  // adding new point to container    
  splinePointsMap.insert(make_pair(lenghtComplete,splinePoint));

  // saving complete lenght
  splineLength = lenghtComplete;
}

void CBSplineTrajectory::UninitInternalPointContainer()
{
    splinePointsMap.clear();
}

void CBSplineTrajectory::CreateNodesVector()
{
  int knots = 0;

  for(int i=0; i<(curveDegree+numControlPoints+1); i++)						// n+m+1 = nr of nodes
  {
    if(i>curveDegree && i<=numControlPoints)
    {
      ++knots;
    }
    nodeVector[i] = knots;
  }
}

CVec2 CBSplineTrajectory::CalculateDeBoor(int r, int i, double u)
{
  if( r == 0 )   // calculation is done
  {
    return currCP[i].ToCVec2();
  }
  double pre = (u-nodeVector[i+r])/(nodeVector[i+curveDegree+1]-nodeVector[i+r]);	// pre calculations
  return ((CalculateDeBoor(r-1, i, u)*(1-pre)) + (CalculateDeBoor(r-1, i+1, u)*(pre)));
}


//////////////////////////////////////////////////////////////////////////
PolylineTrajectory::PolylineTrajectory(  PF_Core::IWorld* _pWorld  )
: PF_Core::WorldObjectBase( _pWorld, false )
{

}

PolylineTrajectory::~PolylineTrajectory()
{
}

bool PolylineTrajectory::CreateFromBSpline(int _splineDegree, nstl::vector<SVector> _controlPoints, int _deltaLength)
{
  if( (_deltaLength == 0) || (_splineDegree < 1) )
  {
    return false;
  }

  deltaLength = _deltaLength;

  if(_controlPoints.empty())
  {
    return true;
  }

  // create BSpline
  CBSplineTrajectory bspline(_splineDegree, &_controlPoints[0], _controlPoints.size());

  const CBSplineTrajectory::MapPoints& bsplinePoints = bspline.GetSplinePoints();

  // polyline should have at least 2 points
  if(bsplinePoints.size() < 2)
  {
    return false;
  }

  // reserve 
  polyline.reserve( bspline.GetLenght() / deltaLength + 1 );

  CBSplineTrajectory::MPIter currentControlPoint = bsplinePoints.begin();
  const CBSplineTrajectory::MPIter endControlPoint = bsplinePoints.end();

  // store first point 
  PolylinePoint newPoint;
  newPoint.pos.x = currentControlPoint->second.x;
  newPoint.pos.y = currentControlPoint->second.y;
  
  int64 lastPointLength = deltaLength;

  CBSplineTrajectory::MPIter lastControlPoint = currentControlPoint;
  ++currentControlPoint;

  // ..calculate first point tangent
  newPoint.tangent.x = currentControlPoint->second.x - newPoint.pos.x;
  newPoint.tangent.y = currentControlPoint->second.y - newPoint.pos.y;
  polyline.push_back(newPoint);

  // traverse through all points
  for(; currentControlPoint != endControlPoint; ++currentControlPoint)
  {
    // calculate current spline segment length 
    double segmentLength = currentControlPoint->first - lastControlPoint->first;

    // leave out segments with zero length
    if(segmentLength == 0)
    {
      lastControlPoint = currentControlPoint;
      continue;
    }

    // calculate approximation tangent for new points
    newPoint.tangent.x = currentControlPoint->second.x - lastControlPoint->second.x;
    newPoint.tangent.y = currentControlPoint->second.y - lastControlPoint->second.y;
  
    // split spline segment on small segments with deltaLength size
    while(currentControlPoint->first > lastPointLength)
    {
      // calculate new point position
      float lerpFactor = double(currentControlPoint->first - lastPointLength)/segmentLength;
      newPoint.pos.x = Lerp(currentControlPoint->second.x, lastControlPoint->second.x, lerpFactor);
      newPoint.pos.y = Lerp(currentControlPoint->second.y, lastControlPoint->second.y, lerpFactor);

      polyline.push_back(newPoint);

      lastPointLength += deltaLength;
    }

    lastControlPoint = currentControlPoint;
  }

  // calculate polyline length
  if(!polyline.empty())
  {
    polylineLength = deltaLength * (polyline.size() - 1); 
  }

  return true;
}

bool PolylineTrajectory::CheckIntersectsX(int x1,int x2, int target)
{
  if((target > x1 && target > x2) || (target < x1 && target < x2))
    return false;
  else
    return true;
}

bool PolylineTrajectory::CheckIntersectsY(int y1,int y2, int target)
{
  if((target > y1 && target > y2) || (target < y1 && target < y2))
    return false;
  else
    return true;
}
 
int PolylineTrajectory::FindYIntersectionPoint(SVector pt1, SVector pt2,int x)
{
  if(pt1.x == pt2.x)
  {
    return pt1.x;
  }

  if(pt1.y == pt2.y)
  {
    return pt1.y;
  }

  int deltaY = abs((pt1.x-x)*(pt2.y-pt1.y)/(pt2.x-pt1.x));
  if(pt1.y > pt2.y)
    return pt2.y+deltaY;
  else 
    return pt1.y+deltaY;
}

int  PolylineTrajectory::FindXIntersectionPoint(SVector pt1, SVector pt2,int y)
{
  if(pt1.x == pt2.x)
  {
    return pt1.x;
  }

  if(pt1.y == pt2.y)
  {
    return pt1.y;
  }

  int deltaX = abs((pt2.y-y)*(pt2.x-pt1.x)/(pt2.y-pt1.y));
  if(pt1.x > pt2.x)
    return pt2.x+deltaX;
  else
    return pt1.x+deltaX;
}
 
int64 PolylineTrajectory::GetLenght()
{
  return polylineLength;
}

int PolylineTrajectory::GetCoordsByLenght(int64 length,
                                          /*out*/SVector &refCoords)
{

  if(length < 0)
  {
    return LUX_LENGHT_LESS_ZERO;
  }

  // polyline should at least have 1 control point
  if(polyline.empty() || deltaLength == 0)
  {
    return LUX_ERROR;
  }

  // shot over the spline
  if(length > polylineLength)
  {
    return LUX_LENGHT_TOO_BIG;
  }

  // there is no need for interpolation on the last point
  if(length == polylineLength)
  {
    refCoords = polyline.back().pos;
    return LUX_OK;
  }

  // calculate first point id for segment
  int segmentId = length/deltaLength;

  // calculate coordinates from interpolation between start and end points
  float lerpFactor = float(length - segmentId*deltaLength)/float(deltaLength);
  refCoords.x = Lerp( polyline[segmentId].pos.x, polyline[segmentId+1].pos.x, lerpFactor );
  refCoords.y = Lerp( polyline[segmentId].pos.y, polyline[segmentId+1].pos.y, lerpFactor );

  return LUX_OK;
}

int PolylineTrajectory::GetTangentByLenght(int64 length, /*out*/SVector &refTangent)
{
  // polyline should have at least one point
  if(polyline.empty() || deltaLength == 0)
  {
    return LUX_ERROR;
  }

  // for all coordinates less than zero tangent will be taken from first control point
  if(length < 0)
  {
    refTangent = polyline.front().tangent;
    return LUX_OK;
  }

  // for all coordinates greater or equal to spline length tangent will be taken from last control point
  if(length >= polylineLength)
  {
    refTangent = polyline.back().tangent;
    return LUX_LENGHT_TOO_BIG;
  } 

  //  calculate first point 
  int segmentId = length/deltaLength;

  // interpolate tangent by coordinate
  float lerpFactor = float(length - segmentId*deltaLength)/float(deltaLength);
  refTangent.x = Lerp( polyline[segmentId].tangent.x, polyline[segmentId+1].tangent.x, lerpFactor );
  refTangent.y = Lerp( polyline[segmentId].tangent.y, polyline[segmentId+1].tangent.y, lerpFactor );

  return LUX_OK;
}

}

REGISTER_SAVELOAD_CLASS_NM( PolylineTrajectory, PF_Minigames )
