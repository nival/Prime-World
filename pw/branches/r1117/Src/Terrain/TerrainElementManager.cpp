#include "stdafx.h"

#include "TerrainElementManager.h"
#include "TerrainElement.h"
#include "Terrain.h"
#include "../Render/MeshResource.h"
#include "../Render/MaterialSpec.h"
#include "../Render/RenderResourceManager.h"

namespace Terrain {

TerrainElementManager::TerrainElementManager() : pOwner(NULL), xCount(0), yCount(0)
{
}

TerrainElementManager::~TerrainElementManager()
{
	RemoveElements();
}

void TerrainElementManager::Initialize()
{
	xCount = pOwner->GetGridConstants().sizeInElements.x;
	yCount = pOwner->GetGridConstants().sizeInElements.y;

	TerrainElementInfo empty = {-1, NULL};
	elemList.resize(xCount * yCount + 1, empty); // smirnov [2008/11/27]: [0] is not used

#ifndef VISUAL_CUTTED
  worldAABB.Init2Empty();
#endif
}

TerrainElementId TerrainElementManager::LocateElement(unsigned row, unsigned column)
{
	NI_ASSERT(column < xCount && row < yCount, "Terrain element is out of bounds");
	return row * xCount + column + 1;	// smirnov [2008/11/27]: [0] is not used
}

TerrainElementId TerrainElementManager::LocateElement(const Matrix43& worldMatrix)
{
	SVector gridCoord = ProjectOnGrid(worldMatrix._14, worldMatrix._24);
	TerrainElementId id = LocateElement(unsigned(gridCoord.y), unsigned(gridCoord.x));
	return id;
}

TerrainElementId TerrainElementManager::LocateElement(float x, float y)
{
	SVector gridCoord = ProjectOnGrid(x, y);
	TerrainElementId id = LocateElement(unsigned(gridCoord.y), unsigned(gridCoord.x));
	return id;
}

SVector TerrainElementManager::ProjectOnGrid(float x, float y)
{
	float elementSize = pOwner->GetGridConstants().metersPerElement;
	SVector gridCoord(int(x / elementSize), int(y / elementSize));
	return gridCoord;
}

TerrainElementInfo& TerrainElementManager::GetElementInfo(TerrainElementId id)
{
	NI_ASSERT(0 <= id && id < elemList.size(), "Logic failure");
	TerrainElementInfo& info = elemList[id];
	NI_ASSERT(info.id == id || (info.id == TERRAINELEMENTID_BAD && info.pElement == NULL), "Logic failure");
	return info;
}


TerrainElementId TerrainElementManager::AddElement(Render::TerrainElementGeometryRaw const& rawData, Render::BaseMaterial* pLocalMaterial, const Matrix43& worldMatrix)
{
	TerrainElementId id = LocateElement(worldMatrix);
	TerrainElementInfo& info = GetElementInfo(id);
	NI_ASSERT(info.id == TERRAINELEMENTID_BAD, "TerrainElementId conflicts!");
	info.id = id;
	info.pElement = new TerrainElement(pOwner);

#ifndef VISUAL_CUTTED
  // setup fields
	Render::RenderResourceManager::CreateTerrainFragmentGeometry(&info.pElement->mesh, rawData);
	info.pElement->pLocalMaterial = pLocalMaterial;

	// recalculate AABB
	const int stride = rawData.vertexBufferStride;
	const int numberOfPoints = rawData.vertexBufferSize / rawData.vertexBufferStride;
	info.pElement->worldAABB.Calculate( numberOfPoints, reinterpret_cast<CVec3*>( rawData.vertexBuffer ), stride );
  worldAABB.Grow(info.pElement->GetWorldAABB());
#endif

	return id;
}

void TerrainElementManager::RemoveElement(TerrainElementId id)
{
	TerrainElementInfo& info = GetElementInfo(id);
	if (info.pElement)
		delete info.pElement;

	info.id = TERRAINELEMENTID_BAD;
	info.pElement = NULL;
}

void TerrainElementManager::RemoveElements()
{
	for (TerrainElementList::iterator it = elemList.begin(), itend = elemList.end(); it != itend; ++it)
	{
		TerrainElementInfo& info = *it;
		if (info.pElement)
			delete info.pElement;

		info.id = TERRAINELEMENTID_BAD;
		info.pElement = NULL;
	}
}

} // namespace Terrain

// end of TerrainFragmentManager.cpp
