#include "stdafx.h"

#include "Vector3.h"
#include "Quaternion.h"
#include "PlacementSpline.h"
#include "System/PlacementSpline.h"

using namespace EditorNative;

void PlacementSpline::Setup( IList<Vector3^>^ _points, IList<Vector3^>^ _angles, float tension, int quantNumber )
{
  vector<CVec3> pointsNative;
  vector<CVec3> anglesNative;

  for each ( Vector3^ vec in _points ) 
  {
    CVec3 vecNative;
    vecNative.Set( vec->X, vec->Y, vec->Z );
    pointsNative.push_back( vecNative );
  }

  for each ( Vector3^ vec in _angles ) 
  {
    CVec3 vecNative;
    vecNative.Set( vec->X, vec->Y, vec->Z );
    anglesNative.push_back( vecNative );
  }

  spline->Setup( pointsNative, anglesNative, tension, quantNumber );
}

void PlacementSpline::GetValue( float t, Vector3^ _pos, Quaternion^ _quat )
{
  CVec3 pos;
  CQuat quat;

  spline->GetValues( t, pos, quat );

  _pos->X = pos.x;
  _pos->Y = pos.y;
  _pos->Z = pos.z;

  _quat->X = quat.x;
  _quat->Y = quat.y;
  _quat->Z = quat.z;
  _quat->W = quat.w;
}
