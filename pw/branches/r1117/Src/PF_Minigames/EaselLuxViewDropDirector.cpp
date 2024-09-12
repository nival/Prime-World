#include "stdafx.h"

#include "EaselLuxViewDropDirector.h"

#include "Easel.h"
#include "EaselWorldClientConvertHelper.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class LuxViewBallRotator implementation
//
//////////////////////////////////////////////////////////////////////////
LuxViewDropDirector::LuxViewDropDirector() :
  direction(1, 0)
, rotationQuat(0, 0, 0)
, zeroDist(VNULL3)
{

}

LuxViewDropDirector::~LuxViewDropDirector()
{
}

void LuxViewDropDirector::SetEasel( Easel* _easel ) 
{ 
  easel = _easel; 
  zeroDist = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( SVector(0, 0));
}

bool LuxViewDropDirector::CalculateOrientation()
{
  if ( !IsValid( easel ) )
    return false;

  CVec3 clientDirection = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( direction );

  // [@Irakly <neko.lich> Archangelsky@] TODO: 
  static CVec3 eul = CVec3(FP_PI, FP_PI, FP_PI2);

  SHMatrix matrix;
  SetLookAtZ( &matrix, zeroDist, clientDirection );

  rotationQuat.FromEulerMatrix( matrix );

  CVec3 eulDecomp;
  rotationQuat.DecompEulerAngles(&eulDecomp.x, &eulDecomp.y, &eulDecomp.z);
  eulDecomp += eul;
  rotationQuat.FromEulerAngles(eulDecomp.x, eulDecomp.y, eulDecomp.z);

  return true;
}

bool LuxViewDropDirector::SetDirection( const SVector& _direction )
{
  if(direction == SVector(0, 0))
  {
    return false;
  }

  direction = _direction;
  return CalculateOrientation();
}

} // namespace PF_Minigames