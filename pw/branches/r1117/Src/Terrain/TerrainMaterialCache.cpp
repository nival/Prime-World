#include "stdafx.h"
#include "TerrainMaterialCache.h"

namespace Terrain {

TerrainMaterialCache::TerrainMaterialCache() : pDebugMaterial(NULL)
{
	unsigned int numCombinations = NDb::KnownEnum<NDb::TextureCountPin>::SizeOf() * NDb::KnownEnum<NDb::TerrainUVSetPin>::SizeOf();
	ASSERT(cache.capacity() == numCombinations);
	for (unsigned int i = 0; i < numCombinations; i++)
		cache[i] = NULL;
}

TerrainMaterialCache::~TerrainMaterialCache()
{
	for (unsigned int i = 0; i < cache.capacity(); i++)
		if (cache[i] != NULL)
			delete cache[i];
	SAFE_DELETE(pDebugMaterial);
}

Render::BaseMaterial* TerrainMaterialCache::GetMaterial(NDb::TextureCountPin texCount, NDb::TerrainUVSetPin uvSet)
{
	unsigned int id = (unsigned int)texCount + (unsigned int)uvSet * NDb::KnownEnum<NDb::TextureCountPin>::SizeOf();
	Render::BaseMaterial*& material = cache[id];
	if (material == NULL)
	{
		material = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::TerrainElementMaterial::typeId ) );
		material->SetTextureCountPin(texCount);
		material->SetTerrainUVSetPin(uvSet);
		material->SetMaterialFlags((NDb::MaterialFlags)(material->GetMaterialFlags() | NDb::MATERIALFLAGS_SHADOWRECEIVER | NDb::MATERIALFLAGS_SHADOWCASTER));
	}
	return material;
}

Render::BaseMaterial* TerrainMaterialCache::GetDebugMaterial()
{
	if (pDebugMaterial == NULL)
		pDebugMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::TerrainElementDebugMaterial::typeId ) );
	return pDebugMaterial;
}

} // namespace Terrain

// end of TerrainMaterialCache.cpp
