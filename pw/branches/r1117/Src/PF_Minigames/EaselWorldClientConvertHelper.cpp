#include "stdafx.h"

#include "EaselWorldClientConvertHelper.h"

#include "Easel.h"
#include "EaselConstants.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

#include "../Render/debugrenderer.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselWorldClientConvertHelper::EaselWorldClientConvertHelper()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselWorldClientConvertHelper::Init(const CPtr<Easel>& _easel, const CVec3& _position)
{
  NI_VERIFY( IsValid(_easel), "EaselWorldClientConvertHelper: easel is invalid", return;);

  easel = _easel;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselWorldClientConvertHelper::SetPlacement(const Placement& _placement)
{
  Placement luxorPlacement = easel->GetData()->commonParams->luxorPlacement.GetPlace();
  minigamePlacement = _placement;

  Placement luxorPlacement2 = NULLPLACEMENT;
  luxorPlacement2.pos = luxorPlacement.pos;

  Matrix43 transform2;
  luxorPlacement2.GetMatrix(&transform2);

  luxorPlacement.pos = CVec3(0, 0 ,0);
  luxorPlacement.GetMatrix(&transform);

  transform = transform*transform2;

  minigamePlacement.GetMatrix(&minigameTransform);

  transform = minigameTransform * transform;
  transformInversed = transform.GetInversed();

  zeroCoordinates = ConvertWorldToClientCoordinates(SVector(0, 0));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 EaselWorldClientConvertHelper::ConvertWorldToClientCoordinates( const SVector& worldCoords, int z /*= 0*/ ) const
{
	CVec3 result(0, 0, 0);

  // [@Irakly <neko.lich> Archangelsky@] TODO : позагонятся с потерей точности на переводе. EaselConst::Get_LOGIC_FIELD_HEIGHT() и LOGIC_FIELD_WIDTH 
  // в неправильном порядке случайно
	result.x = (float)worldCoords.x / EaselConst::Get_LOGIC_FIELD_HEIGHT();
	result.y = (float)worldCoords.y / EaselConst::Get_LOGIC_FIELD_WIDTH();
  result.z = z / EaselConst::Get_LOGIC_FIELD_WIDTH();

	if(result.Length() > 100)
	{
		return CVec3(0, 0, 0);
	}

  result = Transform(result, transform);

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVector EaselWorldClientConvertHelper::ConvertClientToWorldCoordinates( const CVec3& clientCoords ) const
{
  SVector result(0, 0);

  CVec3 coordsInWorld = Transform( clientCoords, transformInversed );

  // [@Irakly <neko.lich> Archangelsky@] TODO : позагонятся с потерей точности на переводе.
  result.x = coordsInWorld.x * EaselConst::Get_LOGIC_FIELD_WIDTH();
  result.y = coordsInWorld.y * EaselConst::Get_LOGIC_FIELD_HEIGHT();

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EaselWorldClientConvertHelper::ConvertClientToWorldLength( float clientLength ) const
{
  CVec3 coordsInWorld1 = Transform( CVec3( clientLength, 0.f, 0.f ), transformInversed );
  CVec3 coordsInWorld2 = Transform( CVec3( 0.f, 0.f, 0.f ), transformInversed );
  float length = (coordsInWorld1 - coordsInWorld2).Length() * EaselConst::Get_LOGIC_FIELD_WIDTH();
  return static_cast<int>(length);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVector EaselWorldClientConvertHelper::ConvertScreenToWorldCoordinates( const CVec2& screenCoords ) const
{
  NI_VERIFY( IsValid(easel), "", return SVector(0, 0););

  SVector result;

  NI_VERIFY( IsValid( easel->GetScene() ), "", return SVector( 0, 0 ) );
  NScene::ICamera * camera =  easel->GetScene()->GetCamera();
  NI_VERIFY( IsValid( camera ), "", return SVector( 0, 0 ) );

  CVec3 nearPoint;
  CVec3 farPoint;
  camera->GetProjectiveRayPoints(&nearPoint, &farPoint, screenCoords);

  nearPoint = nearPoint - minigamePlacement.pos;
  farPoint = farPoint - minigamePlacement.pos;

  static int mult = 1000;
  static int offset = 0;

  // k = ((x-x0)/(x1-x0)) = ((y-y0)/(y1-y0)) = (z-z0)/(z1-z0)

  // z = 0
  float k = -nearPoint.z/(farPoint.z - nearPoint.z);
  float x = k * (farPoint.x - nearPoint.x) + nearPoint.x;
  float y = k * (farPoint.y - nearPoint.y) + nearPoint.y;
 
  CVec3 point(x, y, 0);
  point = point + minigamePlacement.pos;

  CVec3 coordsInWorld = Transform( point, transformInversed );

  result.x = coordsInWorld.x*mult + offset;
  result.y = coordsInWorld.y*mult + offset;

  return result;
}

}

REGISTER_SAVELOAD_CLASS_NM( EaselWorldClientConvertHelper, PF_Minigames )