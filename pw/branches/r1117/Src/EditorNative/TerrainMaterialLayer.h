#pragma once

#include "TerrainLayer.h"

namespace EditorNative {
namespace Terrain {
namespace Layers {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TerrainMaterialLayer : TerrainLayer
	{
	private:
		int index;

	internal:
		TerrainMaterialLayer( );
		TerrainMaterialLayer( int index );

	public:
		property virtual System::Byte default[int, int]
		{
			virtual System::Byte get( int x, int y ) override sealed;
			virtual void set( int x, int y, System::Byte value ) override sealed;
		}

		property int Index
		{
			int get() { return index; }
			protected: void set( int value ) { index = value; }
		}

	internal:
		property virtual bool IsValid
		{
			virtual bool get() override sealed { return TerrainLayer::IsValid && index >= 0; }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Layers
}	// namespace Terrain
}	// namespace EditorNative
