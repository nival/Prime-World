#pragma once

#include "Vector3.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class Bound sealed
	{
	private:
		initonly Vector3^ center;
		initonly Vector3^ halfSize;

	internal:
		Bound( const CVec3& center, const CVec3& halfSize );

	public:
		property Vector3^ Center
		{
			Vector3^ get() { return center; }
		}

		property Vector3^ HalfSize
		{
			Vector3^ get() { return halfSize; }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
