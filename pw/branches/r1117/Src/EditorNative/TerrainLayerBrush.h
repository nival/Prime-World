#pragma once

namespace EditorNative {
namespace Terrain {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TerrainLayerBrush sealed
	{
	private:
		initonly array<bool, 2>^ powers;

	public:
		TerrainLayerBrush( array<bool, 2>^ powers );

	public:
		property bool default[int,int]
		{
			bool get( int row, int column ) { return powers[row, column]; }
		}

		property int Width
		{
			int get() { return powers->GetLength( 1 ); }
		}

		property int Height
		{
			int get() { return powers->GetLength( 0 ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Terrain
}	// namespace EditorNative
