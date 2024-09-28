#pragma once

#include "Manipulator.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
namespace Scaling {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class Scaler sealed : Manipulator
	{
	private:
		array<ManipulatorElement^>^ elements;
		Vector3^ initialScale;
    Vector3^ manipulatorScale;

	internal:
		Scaler( ManipulatorsController^ controller );

	internal:
		virtual void OnTransformControllerChanged() override;
    virtual void StartDrag() override;
		virtual void Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) override;
    virtual void EndDrag() override;

    property CVec3 ManipulatorScale
		{
			CVec3 get() { return manipulatorScale->Native; }
			void set( CVec3 value ) { manipulatorScale = gcnew Vector3( value ); }
		}

		property CVec3 InitialScale
		{
			CVec3 get() { return initialScale->Native; }
			void set( CVec3 value ) { initialScale = gcnew Vector3( value ); }
		}

	protected:
		virtual property array<ManipulatorElement^>^ GraphicElements
		{
			virtual array<ManipulatorElement^>^ get() override { return elements; }
		}

    virtual void UpdateParentRotation() override {}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Scaling
}	// namespace Manipulators
}	// namespace EditorNative
