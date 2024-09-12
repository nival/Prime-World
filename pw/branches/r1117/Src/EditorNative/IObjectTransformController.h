#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "TransformParameters.h"

namespace EditorNative {
namespace Manipulators {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public interface class IObjectTransformController
	{
		virtual property TransformParameters^ MovingX
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ MovingY
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ MovingZ
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ RotationYaw
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ RotationPitch
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ RotationRoll
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ ScalingX
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ ScalingY
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property TransformParameters^ ScalingZ
		{
			virtual TransformParameters^ get() abstract;
		}

		virtual property Vector3^ Location
		{
			virtual Vector3^ get() abstract;
			virtual void set( Vector3^ value ) abstract;
		}

		virtual property Quaternion^ Rotation
		{
			virtual Quaternion^ get() abstract;
			virtual void set( Quaternion^ value ) abstract;
		}

		virtual property Vector3^ Scale
		{
			virtual Vector3^ get() abstract;
			virtual void set( Vector3^ value ) abstract;
		}
    virtual property bool IsCommonCenter
		{
			virtual bool get() abstract;
			virtual void set( bool value ) abstract;
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Manipulators
}	// namespace EditorNative
