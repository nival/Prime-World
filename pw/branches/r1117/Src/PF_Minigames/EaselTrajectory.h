#pragma once

#include "../PF_Core/WorldObject.h"

#include "EaselDef.h"
#include "DBEasel.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// B spline trajectory
//
//////////////////////////////////////////////////////////////////////////
const int    MAX_NUM_CONTROL_POINTS   = 100;
const int    POINT_CONTAINER_CAPACITY = 100;
const double SPLINE_PRECICE           = 0.001;

// using SVector structure in container is too heavy
// so we are making a substitute
struct SplinePoint
{
  int x;
  int y;
};

//////////////////////////////////////////////////////////////////////////
//
// Spline class itself
//
//////////////////////////////////////////////////////////////////////////
class CBSplineTrajectory
{
  // points container typedef
  typedef nstl::vector<SplinePoint> VecPoints;
  typedef VecPoints::iterator       VPIter;

public:

  // paths leght typedef
  typedef nstl::map<int64,SplinePoint> MapPoints;
  typedef MapPoints::iterator          MPIter;

  CBSplineTrajectory(int iDegree,const SVector *pCP,int numCPs);
  ~CBSplineTrajectory();

  // length operations
  virtual int64 GetLenght();
  virtual int   GetCoordsByLenght(int64 length,
                                  /*out*/SVector &refCoords);
  virtual int   GetTangentByLenght(int64 length, /*out*/SVector &refTangent);

  const MapPoints& GetSplinePoints() const {return splinePointsMap;}

private:
  CBSplineTrajectory() {}

  // interaction helpers
  // checks x intersection (x1,x2 - line ends)
  bool CheckIntersectsX(int x1,int x2, int target);
  bool CheckIntersectsY(int y1,int y2, int target);
  int  FindYIntersectionPoint(SplinePoint pt1,SplinePoint pt2,int x);
  int  FindXIntersectionPoint(SplinePoint pt1,SplinePoint pt2,int y);

  // point calculation
  void InitInternalPointContainer();
  void UninitInternalPointContainer();
  
  // calculated map points
  MapPoints splinePointsMap;
  int64     splineLength;

  //////////////////////////////////////////////////////////////////////////
  // UNDONE !!!! возможно стоит вынести в отдельный класс
  //

  // calculated spline points
  // these are deBoorg points, means, each of them is connected with simple line
  
  //VecPoints vecSplinePoints; 

  // clean up operations
  void ClearCPStorage();
  void ClearNodeVector();

  // nodes vector creation
  void CreateNodesVector();

  // recursive deBoor algorithm implementation
  // u - step value
  // i - current control point number
  // r - curve degree
  CVec2 CalculateDeBoor(int r, int i, double u);

  int curveDegree;       // 3 for cubical splines
  int numControlPoints;  // current control points number

  SVector currCP[MAX_NUM_CONTROL_POINTS];   // current control points;

  int nodeVector[MAX_NUM_CONTROL_POINTS+5]; // nodes vector

  //
  //
  //////////////////////////////////////////////////////////////////////////

protected:
    

};

//////////////////////////////////////////////////////////////////////////
//
// Polyline trajectory. Can be used for approximation of BSplines.
//
//////////////////////////////////////////////////////////////////////////
class PolylineTrajectory : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D8AF4C1, PolylineTrajectory )

  struct PolylinePoint
  {
    PolylinePoint() : pos(0,0), tangent(0,0) {}

    CVec2 pos;
    CVec2 tangent;
  };

  // points container typedef
  typedef nstl::vector<PolylinePoint> VecPoints;
  typedef VecPoints::iterator       VPIter;

public:

  PolylineTrajectory( PF_Core::IWorld* _pWorld );
  ~PolylineTrajectory();

  bool CreateFromBSpline(int _splineDegree, nstl::vector<SVector> _controlPoints, int _deltaLength);

  // length operations
  virtual int64 GetLenght();
  virtual int   GetCoordsByLenght(int64 length,
                                  /*out*/SVector &refCoords);
  virtual int   GetTangentByLenght(int64 length, /*out*/SVector &refTangent);

private:
  PolylineTrajectory() {}

  // interaction helpers
  // checks x intersection (x1,x2 - line ends)
  bool CheckIntersectsX(int x1,int x2, int target);
  bool CheckIntersectsY(int y1,int y2, int target);
  int  FindYIntersectionPoint(SVector pt1, SVector pt2, int x);
  int  FindXIntersectionPoint(SVector pt1, SVector pt2, int y);

  // point calculation
  void InitInternalPointContainer();
  void UninitInternalPointContainer();


  ZDATA_(PF_Core::WorldObjectBase)

  VecPoints polyline;
  int64     polylineLength;
  int64     deltaLength;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&polyline); f.Add(3,&polylineLength); f.Add(4,&deltaLength); return 0; }
};

}