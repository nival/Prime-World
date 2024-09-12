#include "stdafx.h"
#include "LandPlacementMutator.h"

namespace NScene
{

LandPlacementMutator::LandPlacementMutator( const HeightsController* controller, int _layer, bool _normalize )
:	pHeightController( controller )
, layer( _layer )
,	isNormalize( _normalize )
{

}

void LandPlacementMutator::Apply( Placement* placement ) const
{
	if ( !pHeightController )
	{
		return;
	}

	float z = 0.f;

	if ( isNormalize )
	{
		// Здесь происходит выравнивание объекта по нормали к поверхности

		// Считаем, что нормальная нормаль объекта - по оси z (вверх)
		CVec3 upvec(0.f,0.f,1.f);
		CVec3 normal;
		//TODO как быть с layer?
		pHeightController->GetHeight( placement->pos.x, placement->pos.y, 0, &z, &normal );

		// Получаем кватернион поворота от нормальной нормали объекта (которая по оси z вверх), к нормали террейна
		CQuat qrotate = ShortestArc( upvec, normal );

		placement->pos.z += z;
		placement->rot = qrotate * placement->rot;
	}
	else
	{
		pHeightController->GetHeight( placement->pos.x, placement->pos.y, 0, &z, 0 );
		placement->pos.z += z;
	}
}

}
