#include "stdafx.h"
#include "PickResult.h"

using namespace System::Collections::Generic;

using namespace EditorNative;
using namespace EditorNative::SceneElements;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PickResult::PickResult( Vector3^ _terrainIntersection, List<SceneElement^>^ _pickedElements, bool _hasTerrainIntersection )
: terrainIntersection( _terrainIntersection ),
	pickedElements( _pickedElements ),
	hasTerrainIntersection ( _hasTerrainIntersection )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
