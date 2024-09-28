#include "stdafx.h"
#include "Utility.h"
#include "Settings.h"
#include "RotatorElement.h"

using namespace System;
using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Rotation;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RotatorElement::RotatorElement( Manipulator^ tool, System::Drawing::Color color )
: ManipulatorElement( tool, color )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nstl::vector<CVec3> RotatorElement::CalculateCirclePoints( NScene::ICamera& camera, int deltaDegree )
{
	const CVec3 location = Location;
	const CQuat rotation = CalculateRotation( camera );
	const CVec3 base = rotation.Rotate( V3_AXIS_X ) * ( CalculateScale( camera ) * Radius );
	const CVec3 normal = rotation.Rotate( V3_AXIS_Z );

	nstl::vector<CVec3> points;
	for ( int degree = 0; degree < 360; degree += deltaDegree )
	{
		points.push_back( location + CQuat( ToRadian( degree ), normal, true ).Rotate( base ) );
	}
	return points;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RotatorElement::DrawCircle( const nstl::vector<CVec3>& points )
{
	Color curentColor = CurrentColor;
	for ( int i = 0; i < points.size() - 1; ++i )
	{
		DrawLine3D( points[i], points[i + 1], curentColor );
	}
	DrawLine3D( points[points.size() - 1], points[0], curentColor );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RotatorElement::Draw( NScene::ICamera& camera )
{
	DrawCircle( CalculateCirclePoints( camera, 10 ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RotatorElement::CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera )
{
  //for rotators we need more accurate click
	const float hotSpotSize = ROTATOR_HOT_SPOT_SIZE;

	nstl::vector<CVec3> points( CalculateCirclePoints( camera, 1 ) );
	for ( int i = 0; i < points.size(); ++i )
	{
		if ( IsInRect( PerformProjection( camera, points[i] ), cursorPosition, hotSpotSize ) )
		{
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CQuat RotatorElement::CalculateNewRotation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	if ( fabs( delta ) == 0 )
	{
		return Rotation;
	}

	nstl::vector<CVec3> points( CalculateCirclePoints( camera, 1 ) );
	int i = FindNearestPointIndex( points, initialCursorPosition, camera );

	if ( i < 0 )
	{
		return Rotation;
	}

	const CVec3 begin = points[i];
	const CVec3 end = points[(i + 1) % points.size()];

	Render::DebugRenderer::DrawPoint3D( points[i], 0.01f * CalculateScale( camera ), Render::Color( 255, 255, 255 ), true );

	const CVec3 normal = CalculateRotation( camera ).Rotate( V3_AXIS_Z );

	const CVec3 beginRealDelta = GetRayIntersection( camera, initialCursorPosition, Location, normal );
	const CVec3 endRealDelta = GetRayIntersection( camera, initialCursorPosition + delta, Location, normal );

	const float projection = ( end - begin ) * ( endRealDelta - beginRealDelta ) / fabs( end - begin );
	const CVec3 realDelta = ( end - begin ) * ( projection / fabs( end - begin ) );

	const float radius = fabs( Location - beginRealDelta );

	if ( fabs( projection ) > 0.00001 && radius > 0.00001 )
	{
		return CQuat( projection / fabs( projection ) * fabs( realDelta ) / radius, normal, true ) * Rotation;
	}
	else
	{
		return Rotation;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RotatorElement::FindNearestPointIndex( const nstl::vector<CVec3>& points, const CVec2& cursorPosition, NScene::ICamera& camera )
{
	const CVec3 location = Location;
	const CVec3 intersection = GetRayIntersection( camera, cursorPosition, location, CalculateRotation( camera ).Rotate( V3_AXIS_Z ) );
	const CVec3 delta =  intersection - location;
	const float length = fabs( delta );

	if ( length > 0.0001 )
	{
		const CVec3 point = location + delta / length * ( CalculateScale( camera ) * Radius );
		float minDistIndex = 0;
		float minDist = Single::MaxValue;
		for ( int i = 0; i < points.size(); ++i )
		{
			const float dist = fabs( PerformProjection( camera, points[i] ) - cursorPosition );
			if ( dist < minDist )
			{
				minDist = dist;
				minDistIndex = i;
			}
		}
		return minDistIndex;
	}
	else
	{
		return -1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
