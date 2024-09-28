#pragma once

#include "Manipulator.h"
#include "AxisRotatorElement.h"
#include "CameraPlaneRotatorElement.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
namespace Rotation {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class Rotator sealed : Manipulator
	{
	private:
		array<ManipulatorElement^>^ elements;

	internal:
		Rotator( ManipulatorsController^ controller );
		virtual void Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;

	internal:
		virtual void OnTransformControllerChanged() override;

	protected:
		virtual property array<ManipulatorElement^>^ GraphicElements
		{
			virtual array<ManipulatorElement^>^ get() override { return elements; }
		}

    virtual void UpdateParentRotation() override;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Rotation
}	// namespace Manipulators
}	// namespace EditorNative
