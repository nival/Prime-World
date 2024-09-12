#pragma once

#include "ManipulatorElement.h"
#include "Scaler.h"

namespace EditorNative {
namespace Manipulators {
namespace Scaling {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class ScalerElement abstract : ManipulatorElement
	{
	private:
		literal float MARKER_SIZE = 0.1f;

	private:
		Scaler^ scaler;

	internal:
		ScalerElement( Scaler^ tool, System::Drawing::Color color );

	internal:
		virtual CVec3 CalculateNewScale( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) abstract;

	protected:
		virtual void Draw( NScene::ICamera& camera ) override sealed;
		virtual bool CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera ) override sealed;
		virtual void OnCapturedChanged( bool captured ) override sealed;

		virtual CVec3 CalculateMarkerPosition( NScene::ICamera& camera ) abstract;

		property CVec3 InitialScale
		{
			CVec3 get() { return scaler->InitialScale; }
		}

    property CVec3 ManipulatorScale
		{
			CVec3 get() { return scaler->ManipulatorScale; }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Scaling
}	// namespace Manipulators
}	// namespace EditorNative
