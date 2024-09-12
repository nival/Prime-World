#include "stdafx.h"

#include "Vector3.h"
#include "CubicSpline3D.h"

using namespace EditorNative;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CubicSpline3D::Length::get()
{
  return spline->GetTotalLength();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CubicSpline3D::Segments::get()
{
  return spline->GetSegmentNumber();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3^ CubicSpline3D::GetValue( float t )
{
  CVec3 res;
  spline->GetValue(&res,t);

  return gcnew Vector3( res );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CubicSpline3D::Setup( IList<Vector3^>^ path, Vector3^ startDir, Vector3^ endDir, float tension )
{
  vector<CVec3> pathNative;
  CVec3         startDirNative;
  CVec3         endDirNative;

  for each ( Vector3^ vec in path ) 
  {
    CVec3 vecNative;
    vecNative.Set( vec->X, vec->Y, vec->Z );
    pathNative.push_back( vecNative );
  }
  
  startDirNative.Set( startDir->X, startDir->Y, startDir->Z );
  endDirNative.Set( endDir->X, endDir->Y, endDir->Z );
  
  return( spline->Setup( pathNative, startDirNative, endDirNative, tension ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CubicSpline3D::Setup( IList<Vector3^>^ path, Vector3^ startDir, Vector3^ endDir )
{
  return( Setup( path, startDir, endDir, 0) );
}