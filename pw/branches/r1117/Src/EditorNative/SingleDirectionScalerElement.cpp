#include "stdafx.h"
#include "Utility.h"
#include "SingleDirectionScalerElement.h"

using namespace System;
using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Scaling;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleDirectionScalerElement::SingleDirectionScalerElement( Scaler^ tool, Color color, Vector3^ _offsetDirection )
: ScalerElement( tool, color ),
	offsetDirection( _offsetDirection )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 SingleDirectionScalerElement::CalculateMarkerPosition( NScene::ICamera& camera )
{
  CVec3 sc = Scale - ManipulatorScale + CVec3( 1, 1, 1 );

  return Location + Rotation.Rotate( ComponentProduct( offsetDirection->Native, sc ) ) * CalculateScale( camera );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 SingleDirectionScalerElement::CalculateNewScale( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	const CVec3 dir = CalculateMarkerPosition( camera ) - Location;
	const CVec3 direction = dir / fabs( dir );
	const CVec2 projectedDirection = PerformProjection( camera, Location + direction ) - PerformProjection( camera, Location );

	const float projectedDirectionLength = fabs( projectedDirection );
	if ( projectedDirectionLength > 0.00001 )
	{
		const float projection = projectedDirection * delta / projectedDirectionLength;
		const CVec3 realDelta = direction * ( projection / projectedDirectionLength ) / CalculateScale( camera );
		CQuat invertRotation = Rotation;
		invertRotation.Inverse();
		return Scale + ComponentProduct( invertRotation.Rotate( realDelta ), ComponentFabs( InitialScale ) );
	}
	else
	{
		return Scale;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
