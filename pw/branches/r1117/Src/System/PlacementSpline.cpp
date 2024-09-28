#include "stdafx.h"

#include "PlacementSpline.h"


CPlacementSpline::CPlacementSpline() : 
  quantNumber( 10 ), 
  currentSegment( 0 ),
  currentT(0.f),
  currentPos(0.f),
  timingCorrection(false)
{

}

void CPlacementSpline::SetToBegin()
{
  currentSegment = 0;
  currentT = 0.f;
  currentPos = 0.f;
}

bool CPlacementSpline::Move( float deltaX, CVec3& _pos, CQuat& _rot, int numMoveQuants )
{
  float currentDeltaX = 0.f;
  float deltaT = 1.f / float( numMoveQuants );

  CVec3 prevPos;
  CQuat prevQuat;

  GetValues( currentSegment, currentT, prevPos, prevQuat );

  for( ;; ) 
  {
    currentT += deltaT;
    if ( currentT > 1.f )
    {
      currentT -= float( int( currentT ) );
      currentSegment++;

      if ( currentSegment >= segmentLengths.size() )
      {
        GetValues( currentSegment, 1.f, prevPos, prevQuat );
        return true;
      }
    }

    GetValues( currentSegment, currentT, _pos, _rot );

    float nextDeltaX = fabs( _pos - prevPos );
    currentDeltaX += nextDeltaX;

    if ( currentDeltaX > deltaX )
    {
      if ( timingCorrection )
      {
        // корректируем время назад на часть шага, на которую проскочили вперед (приблизительно, линейной интерполяцией)
        currentT -= ( currentDeltaX - deltaX ) * ( deltaT / nextDeltaX );
      }
      return false;
    }

    prevPos = _pos;
  }

  return false;
}


void CPlacementSpline::Setup( const nstl::vector<CVec3>& _points, const nstl::vector<CVec3>& _angles, float tension, int _quantNumber )
{
  quantNumber = _quantNumber;

  const int size = _points.size();

  NI_VERIFY( size == _angles.size() && size > 1 , "bad size of arrays", return );

  const CVec3 startDir = _points[0] - _points[1];
  const CVec3 endDir = _points[size-1] - _points[size-2];

  InitPositionSpline( _points, startDir, endDir );

  vector<CQuat> rot;

  for( int i = 0; i < _angles.size(); i++ )
  {
    CQuat temp;
    temp.FromEulerAngles( _angles[i].z * FP_PI / 180.0f, _angles[i].x * FP_PI / 180.0f, _angles[i].y * FP_PI / 180.0f );
    temp.Normalize();
    rot.push_back( temp );
  }

  InitRotationSpline( rot, rot.front(), rot.back(), tension );
}

void CPlacementSpline::InitRotationSpline( const nstl::vector<CQuat>& _points, const CQuat& startDir, const CQuat& endDir, float tension )
{
  NI_VERIFY( _points.size() > 1, "path too short", return );

  int sz = _points.size();
  vector<float> temp;
  temp.resize( sz + 2 );

  SHMatrix coefs;
  CCubicSpline1D::FillCoefMatrix( coefs, tension );

  temp[0] = _points[0].x - startDir.x;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].x;
  temp[sz + 1] = _points[sz - 1].x + endDir.x;
  rx.Setup( coefs, temp );

  temp[0] = _points[0].y - startDir.y;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].y;
  temp[sz + 1] = _points[sz - 1].y + endDir.y;
  ry.Setup( coefs, temp );

  temp[0] = _points[0].z - startDir.z;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].z;
  temp[sz + 1] = _points[sz - 1].z + endDir.z;
  rz.Setup( coefs, temp );

  temp[0] = _points[0].w - startDir.w;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].w;
  temp[sz + 1] = _points[sz - 1].w + endDir.w;
  rw.Setup( coefs, temp );
}

void CPlacementSpline::InitPositionSpline( const nstl::vector<CVec3>& _points, const CVec3& startDir, const CVec3& endDir, float tension/* = 0.f*/)
{
  NI_VERIFY( _points.size() > 1, "path too short", return );

  int sz = _points.size();
  vector<float> temp;
  temp.resize( sz + 2 );

  SHMatrix coefs;
  CCubicSpline1D::FillCoefMatrix( coefs, tension );

  temp[0] = _points[0].x - startDir.x;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].x;
  temp[sz + 1] = _points[sz - 1].x + endDir.x;
  x.Setup( coefs, temp );

  temp[0] = _points[0].y - startDir.y;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].y;
  temp[sz + 1] = _points[sz - 1].y + endDir.y;
  y.Setup( coefs, temp );

  temp[0] = _points[0].z - startDir.z;
  for( int i = 0; i < sz; ++i )
    temp[i + 1] = _points[i].z;
  temp[sz + 1] = _points[sz - 1].z + endDir.z;
  z.Setup( coefs, temp );

  segmentLengths.resize( _points.size() - 1 );
  float sumLength = 0.f;

  for ( int i = 0; i < _points.size() - 1; ++i )
  {
    sumLength += CalculateSegmentLength( i );
    segmentLengths[ i ] = sumLength;
  }
}

float CPlacementSpline::CalculateSegmentLength( int _segmentId )
{
  float length = 0.f;

  CVec3 point1;
  CVec3 point2;

  point1.x = x.GetValue( _segmentId, 0.f );
  point1.y = y.GetValue( _segmentId, 0.f );
  point1.z = z.GetValue( _segmentId, 0.f );
  
  for ( int i = 1; i <= quantNumber; ++i )
  {
    float t = float( i ) / float( quantNumber );

    point2.x = x.GetValue( _segmentId, t );
    point2.y = y.GetValue( _segmentId, t );
    point2.z = z.GetValue( _segmentId, t );

    length += fabs( point2 - point1 );
    point1 = point2;
  }

  return length;
}

float CPlacementSpline::GetTotalLength() const
{
  if ( segmentLengths.size() < 1 )
    return 0.f;

  return segmentLengths.back();
}

void CPlacementSpline::FindSegment( int *pSeg, float *pT, float t )
{
  t = Clamp( t, 0.f, GetTotalLength() );

  int sz = segmentLengths.size();
  *pSeg = sz - 1;

  for( int i = 0; i < sz; ++i )
  {
    if ( t <= segmentLengths[i] )
    {
      *pSeg = i;
      break;
    }
  }
  float segStart = ( *pSeg == 0 ? 0 : segmentLengths[*pSeg - 1] );
  *pT = fabs( t - segStart ) < EPS_VALUE ? 0 : ( t - segStart ) / ( segmentLengths[*pSeg] - segStart ); 
}


void CPlacementSpline::GetValues( float t, CVec3& _pos, CQuat& _rot )
{
  int seg;
  float t1;

  FindSegment( &seg, &t1, GetTotalLength() * t );

  GetValues( seg, t1, _pos, _rot );
}

void CPlacementSpline::GetValues( int seg, float segt, CVec3& _pos, CQuat& _rot )
{
  seg = Clamp( seg, 0, segmentLengths.size() - 1 );

  _pos.x = x.GetValue( seg, segt );
  _pos.y = y.GetValue( seg, segt );
  _pos.z = z.GetValue( seg, segt );

  _rot.x = rx.GetValue( seg, segt );
  _rot.y = ry.GetValue( seg, segt );
  _rot.z = rz.GetValue( seg, segt );
  _rot.w = rw.GetValue( seg, segt );
}


