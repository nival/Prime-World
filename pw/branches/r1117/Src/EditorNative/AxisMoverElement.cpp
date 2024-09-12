#include "stdafx.h"
#include "Utility.h"
#include "Settings.h"
#include "AxisMoverElement.h"
#include "Quaternion.h"

using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Moving;

static bool HasCrossing(
	const CVec2& p11, const CVec2& p12,   // координаты первого отрезка
	const CVec2& p21, const CVec2& p22		// координаты второго отрезка
	)
{
	// знаменатель
	double Z  = (p12.y-p11.y)*(p21.x-p22.x)-(p21.y-p22.y)*(p12.x-p11.x);
	// числитель 1
	double Ca = (p12.y-p11.y)*(p21.x-p11.x)-(p21.y-p11.y)*(p12.x-p11.x);
	// числитель 2
	double Cb = (p21.y-p11.y)*(p21.x-p22.x)-(p21.y-p22.y)*(p21.x-p11.x);

	// если числители и знаменатель = 0, прямые совпадают
	if( (Z == 0)&&(Ca == 0)&&(Cb == 0) )
	{
		return true;
	}

	// если знаменатель = 0, прямые параллельны
	if( Z == 0 )
	{
		return false;
	}

	double Ua = Ca/Z;
	double Ub = Cb/Z;

	// если 0<=Ua<=1 и 0<=Ub<=1, точка пересечения в пределах отрезков
	if( (0 <= Ua)&&(Ua <= 1)&&(0 <= Ub)&&(Ub <= 1) )
	{
		return true;
	}
	// иначе точка пересечения за пределами отрезков
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AxisMoverElement::AxisMoverElement( Manipulator^ tool, System::Drawing::Color color )
: MoverElement( tool, color ),
	rotation(Quaternion::Identity)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AxisMoverElement::AxisMoverElement( Manipulator^ tool, System::Drawing::Color color, Quaternion^ _rotation )
: MoverElement( tool, color ),
	rotation(_rotation)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AxisMoverElement::Draw( NScene::ICamera& camera )
{
	const CVec3 begin = Location;
	const CVec3 end = CalculateEnd( camera );
	const CVec3 direction = end - begin;
	const CVec3 dir = direction / fabs( direction );

	const CVec3 axis = abs( rotation->Y ) > 0.0001 ? V3_AXIS_Y : V3_AXIS_Z;
	const CVec3 delta = CQuat( float( PI / 16 ), axis ).Rotate( -direction / 4 );
	const float angle = float( PI / 2 );

	const CVec3 direction1 = CQuat( 0 * angle, dir ).Rotate( delta );
	const CVec3 direction2 = CQuat( 1 * angle, dir ).Rotate( delta );
	const CVec3 direction3 = CQuat( 2 * angle, dir ).Rotate( delta );
	const CVec3 direction4 = CQuat( 3 * angle, dir ).Rotate( delta );

	System::Drawing::Color currentColor = CurrentColor;

	DrawLine3D( begin, end, currentColor );

	DrawLine3D( end, end + direction1, currentColor );
	DrawLine3D( end, end + direction2, currentColor );
	DrawLine3D( end, end + direction3, currentColor );
	DrawLine3D( end, end + direction4, currentColor );

	DrawLine3D( end + direction1, end + direction2, currentColor );
	DrawLine3D( end + direction2, end + direction3, currentColor );
	DrawLine3D( end + direction3, end + direction4, currentColor );
	DrawLine3D( end + direction4, end + direction1, currentColor );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AxisMoverElement::UpdateParentRotation( bool IsGlobal, Quaternion^ rotation )
{
  parentRotation = rotation;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 AxisMoverElement::CalculateEnd( const NScene::ICamera& camera )
{
	const CVec3 begin = Location;
  
  CVec3 dir = rotation->Native.Rotate( V3_AXIS_X );
  dir = parentRotation->Native.Rotate( dir );

	const CVec3 direction = dir * CalculateScale( camera ) / 1.5;
	return begin + direction;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AxisMoverElement::CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera )
{
	const float hotSpotSize = CURSOR_HOT_SPOT_SIZE;

	const CVec3 begin = Location;
	const CVec3 end = CalculateEnd( camera );

	const CVec2 projectedBegin = PerformProjection( camera, begin );
	const CVec2 projectedEnd = PerformProjection( camera, end );

	const CVec2 upLeft = cursorPosition + CVec2( -hotSpotSize / 2, -hotSpotSize / 2 );
	const CVec2 upRight = upLeft + CVec2( hotSpotSize, 0 );
	const CVec2 downRight = upRight + CVec2( 0, hotSpotSize );
	const CVec2 downLeft = upLeft + CVec2( 0, hotSpotSize );

	return
		HasCrossing( projectedBegin, projectedEnd, upLeft, upRight ) ||
		HasCrossing( projectedBegin, projectedEnd, upRight, downRight ) ||
		HasCrossing( projectedBegin, projectedEnd, downRight, downLeft ) ||
		HasCrossing( projectedBegin, projectedEnd, downLeft, upLeft );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 AxisMoverElement::CalculateNewLocation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	if ( fabs( delta ) > 0 )
	{
		const CVec3 begin = Location;
		const CVec3 end = CalculateEnd( camera );

		const CVec2 projectedBegin = PerformProjection( camera, begin );
		const CVec2 projectedEnd = PerformProjection( camera, end );

		const CVec2 projectedDir = projectedEnd - projectedBegin;
		const float projection = projectedDir * delta / fabs( projectedDir );

		const CVec3 dir = end - begin;
		const float coef = projection / fabs( projectedDir );

		return Location + ( end - begin ) * coef;
	}
	else
	{
		return Location;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
