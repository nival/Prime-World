#pragma once

#include "RotatorElement.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
namespace Rotation {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class AxisRotatorElement sealed : RotatorElement
	{
	private:
		Quaternion^ rotation;
    bool IsGlobal;

	internal:
		AxisRotatorElement( Manipulator^ tool, System::Drawing::Color _color );
		AxisRotatorElement( Manipulator^ tool, System::Drawing::Color _color, Quaternion^ rotation );
    virtual void UpdateParentRotation( bool IsGlobal, Quaternion^ rotation ) override;

	protected:
		virtual CQuat CalculateRotation( NScene::ICamera& camera ) override;

		virtual property float Radius
		{
			virtual float get() override { return 0.45f; }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Rotation
}	// namespace Manipulators
}	// namespace EditorNative
