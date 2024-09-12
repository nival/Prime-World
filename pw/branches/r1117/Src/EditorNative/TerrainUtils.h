#pragma once

typedef Terrain::TerrainGeometryManager TGM;
typedef Terrain::Patch TP;

namespace EditorNative {
namespace Terrain {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TerrainUtils abstract sealed
	{
	public:
		static initonly int TexelsInPatch = 16;	 // smirnov [2008/12/4]: any way to use Terrain::GridConstants.texelsPerElement param?!
		static initonly float PatchSize = 10.0f/*TP::SIZE_OF_PATCH*/; // smirnov [2008/12/10]: exported static constant

		static initonly float CursorGranularity = PatchSize / 4;

		static float NearestGranularity( float x )
		{
			return floor(x / CursorGranularity + 0.5) * CursorGranularity;
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Terrain
}	// namespace EditorNative
