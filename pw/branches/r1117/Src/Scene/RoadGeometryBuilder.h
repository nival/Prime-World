#pragma once
#ifndef ROADGEOMETRYBUILDER_H_INCLUDED
#define ROADGEOMETRYBUILDER_H_INCLUDED

#include "../System/BitData.h"
#include "../System/Spline.h"
#include "../Terrain/TerrainElementManager.h"
#include "../MeshConverter/MeshHeader.h"
#include <Terrain/RoadGeometryVertex.h>

namespace Render {
  struct MeshGeometry;
}

class RoadGeometryBuilder
{
public:
  // don't forget to change BAKED_FILE_VERSION
  typedef ::RoadGeometryVertex RoadGeometryVertex;

  RoadGeometryBuilder();
  ~RoadGeometryBuilder();

  void Begin( NDb::Road const *_pDBRoad, CCompositeBSplineWidth<CVec2>* _pSpline );
  void AddTerrainElement( Terrain::TerrainElement const* pElement, Terrain::TerrainElementId elementID, bool recollect );
  void RemoveDuplicates();
  Render::MeshGeometry* End();

private:
  struct TerrainElementInfo
  {
    CArray1Bit marks;
    nstl::vector<CVec3> projected; 
    nstl::vector<unsigned> indices;
    nstl::vector<unsigned> reindex;
    bool isEmpty;
    unsigned numVerticesUsed;

    TerrainElementInfo() : isEmpty(false), numVerticesUsed(0) {}
  };

  typedef nstl::map<Terrain::TerrainElementId, TerrainElementInfo> TerrainInfos;

  void Classify();
  void Squeeze();
  void Merge();

  void ProjectVertices(TerrainElementStrideNew const* pVB, unsigned numVertices, vector<CVec3> &mapping, CArray1Bit &verticesOnRoad);
  void CullTriangles(unsigned const* pIB, unsigned numIndices, CArray1Bit const &verticesOnRoad, nstl::vector<CVec3> const &mapping, vector<unsigned> &newIB);
  void AddVertices(TerrainElementStrideNew const* pVB, const vector<CVec3>& mapping, CArray1Bit &marks, unsigned numMarkedVertices);

  TerrainElementInfo& CollectInfo( Terrain::TerrainElement const* pElement, Terrain::TerrainElementId elementID, bool recollect );

private:
  NDb::Road const *pDBRoad;
  CCompositeBSplineWidth<CVec2>* pSpline;

  nstl::vector<RoadGeometryVertex> roadVertices;
  nstl::vector<unsigned> roadIndices;

  TerrainInfos terrainInfos;
};

#endif // ROADGEOMETRYBUILDER_H_INCLUDED
