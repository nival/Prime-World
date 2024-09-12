#pragma once

#include "ManipulatorElement.h"

namespace EditorNative {
namespace Manipulators {
namespace Moving {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class MoverElement abstract : ManipulatorElement
	{
	public:
		MoverElement( Manipulator^ tool, System::Drawing::Color color );

	internal:
		virtual CVec3 CalculateNewLocation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) abstract;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Moving
}	// namespace Manipulators
}	// namespace EditorNative
