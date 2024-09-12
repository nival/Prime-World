#pragma once

#include "Manipulator.h"
#include "AxisMoverElement.h"
#include "CameraPlaneMoverElement.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
namespace Moving {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class Mover sealed : Manipulator
	{
	private:
		array<ManipulatorElement^>^ elements;

  internal:
		Mover( ManipulatorsController^ controller );

	internal:
		virtual void OnTransformControllerChanged() override;
		virtual void Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;

	protected:
		virtual property array<ManipulatorElement^>^ GraphicElements
		{
			virtual array<ManipulatorElement^>^ get() override { return elements; }
		}

    virtual void UpdateParentRotation() override;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Moving
}	// namespace Manipulators
}	// namespace EditorNative
