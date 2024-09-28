#include "stdafx.h"
#include "Utility.h"
#include "MultiDirectionScalerElement.h"

using namespace System;
using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Scaling;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultiDirectionScalerElement::MultiDirectionScalerElement( Scaler^ tool, Color color )
: ScalerElement( tool, color )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 MultiDirectionScalerElement::CalculateMarkerPosition( NScene::ICamera& camera )
{
	return Location;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 MultiDirectionScalerElement::CalculateNewScale( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	if ( fabs( delta.x ) > 0.00001 )
	{
		const CVec3 intersection1 = GetRayIntersection( camera, initialCursorPosition, Location, GetCameraDir( camera ) );
		const CVec3 intersection2 = GetRayIntersection( camera, initialCursorPosition + CVec2( delta.x, 0), Location, GetCameraDir( camera ) );
		const float d = fabs( intersection2 - intersection1 ) * delta.x / fabs( delta.x );
		return Scale + ComponentProduct( CVec3( d, d, d ), InitialScale );
	}
	else
	{
		return Scale;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
