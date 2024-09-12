#pragma once

#include "MoverElement.h"

namespace EditorNative {
namespace Manipulators {
namespace Moving {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class CameraPlaneMoverElement sealed : MoverElement
	{
	private:
		static const float SIZE = 20;

	public:
		CameraPlaneMoverElement( Manipulator^ tool, System::Drawing::Color _color );

	internal:
		virtual CVec3 CalculateNewLocation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;

	protected:
		virtual void Draw( NScene::ICamera& camera ) override;
		virtual bool CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera ) override;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Moving
}	// namespace Manipulators
}	// namespace EditorNative
