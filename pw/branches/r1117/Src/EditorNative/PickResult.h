#pragma once

#include "Vector3.h"
#include "SceneElement.h"

namespace EditorNative {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class PickResult
	{
	private:
		Vector3^ terrainIntersection;
		System::Collections::Generic::List<SceneElements::SceneElement^>^ pickedElements;
		bool hasTerrainIntersection;

	internal:
		PickResult(
			Vector3^ terrainIntersection,
			System::Collections::Generic::List<SceneElements::SceneElement^>^ pickedElements,
			bool hasTerrainIntersection
			);

	public:
		property Vector3^ TerrainIntersection
		{
			Vector3^ get() { return terrainIntersection; }
		}

		property bool HasTerrainIntersection
		{
			//bool get() { return !ReferenceEquals( terrainIntersection, nullptr ); }
			bool get() { return hasTerrainIntersection; }
		}

		property array<SceneElements::SceneElement^>^ PickedElements
		{
			array<SceneElements::SceneElement^>^ get() { return pickedElements->ToArray(); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
