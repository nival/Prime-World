#pragma once

#include "ManipulatorElement.h"

namespace EditorNative {
namespace Manipulators {
namespace Rotation {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class RotatorElement abstract : ManipulatorElement
	{
	internal:
		RotatorElement( Manipulator^ tool, System::Drawing::Color color );

	internal:
		CQuat CalculateNewRotation( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera );

	protected:
		virtual void Draw( NScene::ICamera& camera ) override sealed;
		virtual bool CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera ) override sealed;

		virtual CQuat CalculateRotation( NScene::ICamera& camera ) abstract;

		virtual property float Radius
		{
			virtual float get() abstract;
		}

	private:
		nstl::vector<CVec3> CalculateCirclePoints( NScene::ICamera& camera, int deltaDegree );
		void DrawCircle( const nstl::vector<CVec3>& points );
		int FindNearestPointIndex( const nstl::vector<CVec3>& points, const CVec2& cursorPosition, NScene::ICamera& camera );
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Rotation
}	// namespace Manipulators
}	// namespace EditorNative
