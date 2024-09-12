#include "stdafx.h"
#include "Utility.h"
#include "ScalerElement.h"

using namespace System;
using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Scaling;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScalerElement::ScalerElement( Scaler^ tool, Color color )
: ManipulatorElement( tool, color ),
	scaler ( tool )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScalerElement::Draw( NScene::ICamera& camera )
{
  const CVec3 markerPosition = CalculateMarkerPosition( camera );
	const float s = MARKER_SIZE / 2;

	const CVec3 vertices[] =
		{
			markerPosition + Rotation.Rotate( CVec3( -s, -s,  s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3( -s,  s,  s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3(  s,  s,  s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3(  s, -s,  s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3( -s, -s, -s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3( -s,  s, -s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3(  s,  s, -s ) ) * CalculateScale( camera ),
			markerPosition + Rotation.Rotate( CVec3(  s, -s, -s ) ) * CalculateScale( camera )
		};

	Color currentColor = CurrentColor;

	DrawLine3D( vertices[0], vertices[1], currentColor );
	DrawLine3D( vertices[1], vertices[2], currentColor );
	DrawLine3D( vertices[2], vertices[3], currentColor );
	DrawLine3D( vertices[3], vertices[0], currentColor );

	DrawLine3D( vertices[0 + 4], vertices[1 + 4], currentColor );
	DrawLine3D( vertices[1 + 4], vertices[2 + 4], currentColor );
	DrawLine3D( vertices[2 + 4], vertices[3 + 4], currentColor );
	DrawLine3D( vertices[3 + 4], vertices[0 + 4], currentColor );

	DrawLine3D( vertices[0], vertices[4], currentColor );
	DrawLine3D( vertices[1], vertices[5], currentColor );
	DrawLine3D( vertices[2], vertices[6], currentColor );
	DrawLine3D( vertices[3], vertices[7], currentColor );

	DrawLine3D( Location, markerPosition, Color::DarkGray );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScalerElement::CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera )
{
	const CVec3 markerPosition = CalculateMarkerPosition( camera );

	static const CVec3 normals[] =
		{
			V3_AXIS_X,
			V3_AXIS_Y,
			V3_AXIS_Z,
			-V3_AXIS_X,
			-V3_AXIS_Y,
			-V3_AXIS_Z
		};

	static const CVec3 rights[] =
	{
		-V3_AXIS_Y,
		V3_AXIS_X,
		V3_AXIS_X
	};

	static const CVec3 ups[] =
	{
		V3_AXIS_Z,
		V3_AXIS_Z,
		-V3_AXIS_Y
	};

	const float scale = CalculateScale( camera );
	const float halfSize = MARKER_SIZE / 2 * scale;
	for ( int i = 0; i < sizeof( normals ) / sizeof( CVec3 ); ++i )
	{
		const CVec3 normal = Rotation.Rotate( normals[i] );
		const CVec3 center = markerPosition + normal * halfSize;
		const CVec3 intersection = GetRayIntersection( camera, cursorPosition, center, normal );
		const CVec3 right = Rotation.Rotate( rights[i % ( sizeof(rights) / sizeof( CVec3 ) )] );
		const CVec3 up = Rotation.Rotate( ups[i % ( sizeof(ups) / sizeof( CVec3 ) )] );

		const float projectionRight = right * ( intersection - center );
		const float projectionUp = up * ( intersection - center );

		if ( fabs( projectionRight ) <= halfSize && fabs( projectionUp ) <= halfSize )
		{
			return true;
		}
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScalerElement::OnCapturedChanged( bool captured )
{
	ManipulatorElement::OnCapturedChanged( captured );
	scaler->InitialScale = Scale;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
