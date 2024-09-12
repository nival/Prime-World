#pragma once

#ifndef VISUAL_CUTTED
#include "../Render/aabb.h"
#endif

namespace Render
{
	struct TerrainElementGeometryRaw;
	class BaseMaterial;
	class ConvexVolume;
}

namespace Terrain {

	class TerrainElement;
	class Terrain;

	typedef long TerrainElementId;
	static const TerrainElementId TERRAINELEMENTID_BAD = -1;

	struct TerrainElementInfo
	{
		TerrainElementId id;
		TerrainElement* pElement;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class TerrainElementManager
	{
	public:
		TerrainElementManager();
		~TerrainElementManager();

		void SetOwner(Terrain* owner) { pOwner = owner; }
		void Initialize();

		TerrainElementId AddElement(Render::TerrainElementGeometryRaw const& rawData, Render::BaseMaterial* pLocalMaterial, const Matrix43& worldMatrix);
		void RemoveElement(TerrainElementId id);
		void RemoveElements();

#ifndef VISUAL_CUTTED
    template <class FUNCTOR> void ForAllElements(FUNCTOR& func);
		template <class FUNCTOR> void ForAllElementInfos(FUNCTOR& func);
		template <class FUNCTOR> void ForAllElementInfosAABB(FUNCTOR& func, Render::AABB const& bounds);

    const Render::AABB &GetWorldAABB() const { return worldAABB; }
#endif

		TerrainElement* GetElement(TerrainElementId id) { return GetElementInfo(id).pElement; }
		unsigned GetElementRow(TerrainElementId id) const { return (id-1) / xCount; }
		unsigned GetElementColumn(TerrainElementId id) const { return (id-1) % xCount; }
		
		unsigned GetMaxRow() const { return yCount - 1; }
		unsigned GetMaxColumn() const { return xCount - 1; }
		
		TerrainElementId GetFirstElementId() const { return 1; }
		TerrainElementId GetLastElementId() const { return xCount * yCount; }

		SVector ProjectOnGrid(float x, float y);
		TerrainElementId LocateElement(float x, float y);
		TerrainElementId LocateElement(const Matrix43& worldMatrix);
		TerrainElementId LocateElement(unsigned row, unsigned column);
		TerrainElementInfo& GetElementInfo(TerrainElementId id);

	private:
		typedef nstl::vector<TerrainElementInfo> TerrainElementList;

	private:
		Terrain* pOwner; // smirnov [2008/12/11]: CPtr<> is not possible here

		unsigned xCount;
		unsigned yCount;
		TerrainElementList elemList;

#ifndef VISUAL_CUTTED
    Render::AABB worldAABB;
#endif
};

#ifndef VISUAL_CUTTED
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class FUNCTOR> void TerrainElementManager::ForAllElements(FUNCTOR& func)
	{
		for (TerrainElementList::const_iterator it = elemList.begin(); it != elemList.end(); ++it)
			if (it->pElement)
				func(*it->pElement);
	}

	template <class FUNCTOR> void TerrainElementManager::ForAllElementInfos(FUNCTOR& func)
	{
		for (TerrainElementList::const_iterator it = elemList.begin(); it != elemList.end(); ++it)
			if (it->pElement)
				func(*it);
	}

	template <class FUNCTOR> void TerrainElementManager::ForAllElementInfosAABB(FUNCTOR& func, Render::AABB const& bounds)
	{
    CVec2 lb(bounds.center.AsVec2D() - bounds.halfSize.AsVec2D()), rt(bounds.center.AsVec2D() + bounds.halfSize.AsVec2D());
    SVector lbGridCoords(ProjectOnGrid(lb.x, lb.y)), rtGridCoords(ProjectOnGrid(rt.x, rt.y));

    lbGridCoords.x = ClampFast(lbGridCoords.x, 0, GetMaxRow());
    lbGridCoords.y = ClampFast(lbGridCoords.y, 0, GetMaxColumn());
    rtGridCoords.x = ClampFast(rtGridCoords.x, 0, GetMaxRow());
    rtGridCoords.y = ClampFast(rtGridCoords.y, 0, GetMaxColumn());

    for (unsigned i = (unsigned)lbGridCoords.y, endI = (unsigned)rtGridCoords.y + 1; i != endI; ++i)
      for (unsigned j = (unsigned)lbGridCoords.x, endJ = (unsigned)rtGridCoords.x + 1; j != endJ; ++j)
      {
        TerrainElementInfo &elemInfo = GetElementInfo(LocateElement(i, j));
			  if (elemInfo.pElement && bounds.IsIntersectedBy(elemInfo.pElement->GetWorldAABB())) // smirnov [2008/11/28]: need to speedup this
				  func(elemInfo);
      }

    //for (TerrainElementList::const_iterator it = elemList.begin(); it != elemList.end(); ++it)
		//	if (it->pElement && bounds.IsIntersectedBy(it->pElement->GetWorldAABB())) // smirnov [2008/11/28]: need to speedup this
		//		func(*it);
	}
#endif

} // namespace Terrain
