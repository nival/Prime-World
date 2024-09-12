#pragma once

#include "MoverElement.h"

namespace EditorNative {
namespace Manipulators {
namespace Moving {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class AxisMoverElement sealed : MoverElement
	{
	private:
		Quaternion^ rotation;

	public:
		AxisMoverElement( Manipulator^ tool, System::Drawing::Color _color );
		AxisMoverElement( Manipulator^ tool, System::Drawing::Color _color, Quaternion^ rotation );

	protected:
		virtual void Draw( NScene::ICamera& camera ) override;
		virtual bool CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera ) override;

	internal:
		virtual CVec3 CalculateNewLocation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;
    virtual void UpdateParentRotation( bool IsGlobal, Quaternion^ rotation ) override;

	private:
		CVec3 CalculateEnd( const NScene::ICamera& camera );
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Moving
}	// namespace Manipulators
}	// namespace EditorNative
