#pragma once

#include "Vector3.h"
#include "EditorSceneObject.h"

namespace EditorNative {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class SimplePickResult
	{
	private:
		Vector3^ terrainIntersection;
		System::Collections::Generic::List<SceneElements::SceneObjects::EditorSceneObject^>^ pickedElements;
		bool hasTerrainIntersection;

	internal:
		SimplePickResult(
			Vector3^ _terrainIntersection,
			System::Collections::Generic::List<SceneElements::SceneObjects::EditorSceneObject^>^ _pickedElements,
			bool _hasTerrainIntersection
			)
			: terrainIntersection( _terrainIntersection ),
			pickedElements( _pickedElements ),
			hasTerrainIntersection ( _hasTerrainIntersection )
		{
		}

	public:

    Vector3^ zIntersection;
    bool hasZIntersection;

		property Vector3^ TerrainIntersection
		{
			Vector3^ get() { return terrainIntersection; }
		}

		property bool HasTerrainIntersection
		{
			//bool get() { return !ReferenceEquals( terrainIntersection, nullptr ); }
			bool get() { return hasTerrainIntersection; }
		}

		property array<SceneElements::SceneObjects::EditorSceneObject^>^ PickedElements
		{
			array<SceneElements::SceneObjects::EditorSceneObject^>^ get() { return pickedElements->ToArray(); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace EditorNative
