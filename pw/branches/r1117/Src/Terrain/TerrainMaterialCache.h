#pragma once

#include "../Render/MaterialSpec.h"

namespace Terrain {

class TerrainMaterialCache
{
public:
	TerrainMaterialCache();
	~TerrainMaterialCache();

	Render::BaseMaterial* GetMaterial(NDb::TextureCountPin texCount, NDb::TerrainUVSetPin uvSet);
	Render::BaseMaterial* GetDebugMaterial();

private:
	StaticArray<Render::BaseMaterial*, 8> cache;
	Render::BaseMaterial* pDebugMaterial;
};

} // namespace Terrain
