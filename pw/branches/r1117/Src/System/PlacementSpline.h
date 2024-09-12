#ifndef __PLACEMENT_SPLINE_H__
#define __PLACEMENT_SPLINE_H__

#include "Spline.h"

class CPlacementSpline
{
public:
  CPlacementSpline();

  void Setup( const nstl::vector<CVec3>& _points, const nstl::vector<CVec3>& _angles, float tension, int _quantNumber );

  void SetTimingCorrection( bool enabled ) { timingCorrection = enabled; }
  void SetToBegin();
  bool Move( float deltaX, CVec3& _pos, CQuat& _rot, int numMoveQuants);

  void GetValues( float t, CVec3& _pos, CQuat& _rot );

  float GetTotalLength() const;

private:

  void InitPositionSpline( const nstl::vector<CVec3>& _points, const CVec3& startDir, const CVec3& endDir, float tension = 0.f );
  void InitRotationSpline( const nstl::vector<CQuat>& _points, const CQuat& startDir, const CQuat& endDir, float tension );

  float CalculateSegmentLength( int _segmentId );

  void FindSegment( int *pSeg, float *pT, float length );

  void GetValues( int seg, float segt, CVec3& _pos, CQuat& _rot );

  int quantNumber;

  // position spline
  CCubicSpline1D x;
  CCubicSpline1D y;
  CCubicSpline1D z;

  vector<float> segmentLengths; 

  //rotation spline
  CCubicSpline1D rx;
  CCubicSpline1D ry;
  CCubicSpline1D rz;
  CCubicSpline1D rw;

  int currentSegment;
  float currentT;
  float currentPos;
  bool timingCorrection;
};


#endif // __PLACEMENT_SPLINE_H__
