#pragma once

#include "IObjectTransformController.h"

namespace EditorNative {
namespace Manipulators {
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class CompositeTransformController sealed : Manipulators::IObjectTransformController
	{
	private:
		array<Manipulators::IObjectTransformController^>^ controllers;

		Manipulators::TransformParameters^ movingX;
		Manipulators::TransformParameters^ movingY;
		Manipulators::TransformParameters^ movingZ;
		Manipulators::TransformParameters^ rotationYaw;
		Manipulators::TransformParameters^ rotationPitch;
		Manipulators::TransformParameters^ rotationRoll;
		Manipulators::TransformParameters^ scalingX;
		Manipulators::TransformParameters^ scalingY;
		Manipulators::TransformParameters^ scalingZ;

		Vector3^ tempLocation;
		Quaternion^ tempRotation;
		Vector3^ tempScale;
    bool isCommonCenter;

	public:
		CompositeTransformController( array<Manipulators::IObjectTransformController^>^ controllers );

	public:
		virtual property Manipulators::TransformParameters^ MovingX
		{
			virtual Manipulators::TransformParameters^ get() sealed { return movingX; }
		}

		virtual property Manipulators::TransformParameters^ MovingY
		{
			virtual Manipulators::TransformParameters^ get() sealed { return movingY; }
		}

		virtual property Manipulators::TransformParameters^ MovingZ
		{
			virtual Manipulators::TransformParameters^ get() sealed { return movingZ; }
		}

		virtual property Manipulators::TransformParameters^ RotationYaw
		{
			virtual Manipulators::TransformParameters^ get() sealed { return rotationYaw; }
		}

		virtual property Manipulators::TransformParameters^ RotationPitch
		{
			virtual Manipulators::TransformParameters^ get() sealed { return rotationPitch; }
		}

		virtual property Manipulators::TransformParameters^ RotationRoll
		{
			virtual Manipulators::TransformParameters^ get() sealed { return rotationRoll; }
		}

		virtual property Manipulators::TransformParameters^ ScalingX
		{
			virtual Manipulators::TransformParameters^ get() sealed { return scalingX; }
		}

		virtual property Manipulators::TransformParameters^ ScalingY
		{
			virtual Manipulators::TransformParameters^ get() sealed { return scalingY; }
		}

		virtual property Manipulators::TransformParameters^ ScalingZ
		{
			virtual Manipulators::TransformParameters^ get() sealed { return scalingZ; }
		}

		virtual property Vector3^ Location
		{
			virtual Vector3^ get() sealed { return tempLocation; }
			virtual void set( Vector3^ value ) sealed;
		}

		virtual property Quaternion^ Rotation
		{
			virtual Quaternion^ get() sealed { return tempRotation; }
			virtual void set( Quaternion^ value ) sealed;
		}

		virtual property Vector3^ Scale
		{
			virtual Vector3^ get() sealed { return tempScale; }
			virtual void set( Vector3^ value ) sealed;
		}
    
    virtual property bool IsCommonCenter
		{
			virtual bool get() sealed { return isCommonCenter; }
      virtual void set( bool value ) sealed { isCommonCenter = value; }
		}
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
}
