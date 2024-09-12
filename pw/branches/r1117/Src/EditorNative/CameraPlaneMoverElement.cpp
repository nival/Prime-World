#include "stdafx.h"
#include "Settings.h"
#include "Utility.h"
#include "CameraPlaneMoverElement.h"

using namespace System;
using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Moving;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraPlaneMoverElement::CameraPlaneMoverElement( Manipulator^ tool, System::Drawing::Color color )
: MoverElement( tool, color )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CameraPlaneMoverElement::Draw( NScene::ICamera& camera )
{
	const float size = SIZE;

	const CVec2 upLeft = PerformProjection( camera, Location ) + CVec2( -size / 2, -size / 2 );
	const CVec2 upRight = upLeft + CVec2( size, 0 );
	const CVec2 downRight = upRight + CVec2( 0, size );
	const CVec2 downLeft = upLeft + CVec2( 0, size );

	DrawLine2D( upLeft, upRight, CurrentColor );
	DrawLine2D( upRight, downRight, CurrentColor );
	DrawLine2D( downRight, downLeft, CurrentColor );
	DrawLine2D( downLeft, upLeft, CurrentColor );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CameraPlaneMoverElement::CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera )
{
	const float size = SIZE;
	const float hotSpotSize = CURSOR_HOT_SPOT_SIZE;

	const CVec2 location = PerformProjection( camera, Location );

	const float up = location.y - size / 2;
	const float cursorUp = cursorPosition.y - hotSpotSize / 2;

	const float down = location.y + size / 2;
	const float cursorDown = cursorPosition.y + hotSpotSize / 2;

	const float right = location.x + size / 2;
	const float cursorRight = cursorPosition.x + hotSpotSize / 2;

	const float left = location.x - size / 2;
	const float cursorLeft = cursorPosition.x - hotSpotSize / 2;

	return IntervalsIntersected( up, down, cursorUp, cursorDown ) && IntervalsIntersected( left, right, cursorLeft, cursorRight );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 CameraPlaneMoverElement::CalculateNewLocation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	if ( fabs( delta ) > 0 )
	{
		CVec3 dummy;

		CVec3 initialRayFar;
		camera.GetProjectiveRayPoints( &dummy, &initialRayFar, initialCursorPosition );

		CVec3 currentRayFar;
		camera.GetProjectiveRayPoints( &dummy, &currentRayFar, initialCursorPosition + delta );

		CVec3 cameraLocation;
		camera.GetProjectiveRay( &cameraLocation, &dummy, initialCursorPosition );

		const CVec3 direction = currentRayFar - initialRayFar;
		const float coef = fabs( Location - cameraLocation ) / fabs( initialRayFar - cameraLocation );

		return Location + direction * coef;
	}
	else
	{
		return Location;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
