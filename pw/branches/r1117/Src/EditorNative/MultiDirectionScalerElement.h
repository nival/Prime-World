#pragma once

#include "ScalerElement.h"

namespace EditorNative {
namespace Manipulators {
namespace Scaling {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class MultiDirectionScalerElement sealed : ScalerElement
	{
	internal:
		MultiDirectionScalerElement( Scaler^ tool, System::Drawing::Color color );

	internal:
		virtual CVec3 CalculateNewScale( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;

	protected:
		virtual CVec3 CalculateMarkerPosition( NScene::ICamera& camera ) override;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Scaling
}	// namespace Manipulators
}	// namespace EditorNative
