#include "stdafx.h"

#include "RoadGeometryBuilder.h"

#include "../Terrain/TerrainElement.h"
#include "../Render/smartrenderer.h"
#include "../System/BitData.h"
//#include "../System/iterator.h"
#include <Render/CleanGeometry.h>

namespace 
{
  static unsigned const REINDEX_SKIP = 0xFFFFFFFFU;    // note: number of vertices guaranteed to be less than that [5/14/2010 smirnov]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoadGeometryBuilder::RoadGeometryBuilder()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoadGeometryBuilder::~RoadGeometryBuilder()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoadGeometryBuilder::Begin(NDb::Road const *_pDBRoad, CCompositeBSplineWidth<CVec2>* _pSpline)
{
  NI_ASSERT(_pDBRoad, "NULL pointer passed");
  NI_ASSERT(_pSpline, "NULL pointer passed");
  NI_ASSERT(_pSpline->GetNumSegments() == _pDBRoad->points.size() - 1, "Spline doesn't fit the road");
  pDBRoad = _pDBRoad;
  pSpline = _pSpline;

  roadVertices.clear();
  roadIndices.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculate spline mapping for given vertices
// out:  mapping - (x, y, w) array, where x = distance from spline
//                                        y = parameter along spline
//                                        w = spline width at this parameter
//       verticesOnRoad - bit marks for vertices lying inside road

void RoadGeometryBuilder::ProjectVertices(TerrainElementStrideNew const* pVB, unsigned numVertices, vector<CVec3> &mapping, CArray1Bit &verticesOnRoad)
{
  mapping.resize(numVertices);
  verticesOnRoad.SetSize(numVertices);
  verticesOnRoad.FillZero();

  // the first and the last segment length
  float startLen = pSpline->GetLength(1.0f);
  float endLen = pSpline->GetTotalLength() - pSpline->GetLength(pSpline->GetNumSegments() - 1);

  // express meters in spline segments
  const float overestimationInMeters = 2.0f; // depends on world scale and tessellation [8/17/2010 smirnov]
  float startEps = startLen > 0.0f ? overestimationInMeters / startLen : 0.0f;
  float endEps = endLen > 0.0f ? overestimationInMeters / endLen : 0.0f;
  float widthEps = 2.0f; // depends on world scale and tessellation [2/3/2011 smirnov]

  for (unsigned i = 0; i < numVertices; ++i)
  {
    TerrainElementStrideNew const* pVertex = &pVB[i];

    // find projection on spline
    CVec2 const& pos = pVertex->position.AsVec2D();
    float t = pSpline->GetClosestPointExt(pos);
    CVec2 splinePos = pSpline->GetExt(t);

    // save coordinates
    float w = pSpline->GetWidthExt(t);
    float dist = fabs(pos - splinePos);
    mapping[i] = CVec3(dist, t, w);

    // mark vertex if it's inside (on the road)
    // (with a bit of overestimation)
    if (t >= -startEps && t <= pSpline->GetNumSegments() + endEps && dist < w + widthEps)
      verticesOnRoad.SetData(i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// build new index buffer containing only triangles that have at least one vertex marked "on-the-road"

void RoadGeometryBuilder::CullTriangles(unsigned const* pIB, unsigned numIndices, CArray1Bit const &verticesOnRoad, nstl::vector<CVec3> const &mapping, vector<unsigned> &newIB)
{
  unsigned numVertices = verticesOnRoad.GetSize();
  newIB.reserve(numIndices);

  float maxLength = 0.5f * (float)pSpline->GetNumSegments();

  for (unsigned i = 0; i < numIndices; i += 3)
  {
    unsigned i0 = *pIB++;
    unsigned i1 = *pIB++;
    unsigned i2 = *pIB++;
    NI_VERIFY(i0 < numVertices && i1 < numVertices && i2 < numVertices,
      NStr::StrFmt("One of indices exceed number of vertices (%i): %i, %i, %i", numVertices, i0, i1, i2), continue);

    // check for triangles with huge mapping
    float d01 = fabs(mapping[i0].y - mapping[i1].y);
    float d02 = fabs(mapping[i0].y - mapping[i2].y);
    float d12 = fabs(mapping[i1].y - mapping[i2].y);
    float len = Max(Max(d01, d02), d12);
    if (len >= maxLength)
      continue;

    // check to see if any vertex is on the road
    if (verticesOnRoad.GetData(i0) | verticesOnRoad.GetData(i1) | verticesOnRoad.GetData(i2))
    {
      // add this triangle
      newIB.push_back(i0);
      newIB.push_back(i1);
      newIB.push_back(i2);
    }
  }
  NI_ASSERT(newIB.size() % 3 == 0, "Triangles should be added as a whole");
  NI_ASSERT(newIB.size() <= (int)numIndices, "Some extra triangles appeared");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy marked vertices from source VB to road VB

void RoadGeometryBuilder::AddVertices(TerrainElementStrideNew const* pVB, const vector<CVec3>& mapping, CArray1Bit &marks, unsigned numMarkedVertices)
{
  unsigned numVertices = marks.GetSize();
  unsigned prevNumVertices = roadVertices.size();
  roadVertices.reserve(prevNumVertices + numMarkedVertices);
  for (unsigned i = 0; i < numVertices; ++i)
  {
    if (!marks.GetData(i))
      continue;

    RoadGeometryVertex& vtx = roadVertices.push_back();
    TerrainElementStrideNew const* pVertex = &pVB[i];
    vtx.position = pVertex->position;
    vtx.color0 = pVertex->color0;
    vtx.color1 = pVertex->color1;

    // calculate opacity
    float a = 1.f;
    if (mapping[i].y < 0.f)
    {
      a = pDBRoad->points[0].opacity;
    }
    else if (mapping[i].y > pSpline->GetNumSegments())
    {
      a = pDBRoad->points[pSpline->GetNumSegments()].opacity;
    }
    else
    {
      int segm;
      float offs;
      pSpline->SegmentAndOffset(mapping[i].y, segm, offs);
      a = (1-offs) * pDBRoad->points[segm].opacity + offs * pDBRoad->points[segm + 1].opacity;
    }

    // determine on what side of the spline we are
    CVec2 d = pVertex->position.AsVec2D() - pSpline->GetExt(mapping[i].y);
    CVec2 tg = pSpline->GetDiff1Ext(mapping[i].y);

    vtx.params.x = Sign(Cross(d, tg)) * mapping[i].x;
    vtx.params.y = pSpline->GetLengthExt(mapping[i].y);
    vtx.params.z = mapping[i].z;
    vtx.params.w = a;

  }
  NI_ASSERT(roadVertices.size() == (int)(prevNumVertices + numMarkedVertices), "Failed to add all vertices correctly");
}


RoadGeometryBuilder::TerrainElementInfo& RoadGeometryBuilder::CollectInfo( Terrain::TerrainElement const* pElement, Terrain::TerrainElementId elementID, bool recollect )
{
  TerrainInfos::iterator it = terrainInfos.find( elementID );

  if ( it != terrainInfos.end() && !recollect )
    return it->second;

  TerrainElementInfo& info = terrainInfos[ elementID ];

  NI_ASSERT(pElement, "NULL pointer to TerrainElement passed");

  // access source element vertices
  DXVertexBufferRef pSourceVB = pElement->mesh.GetVertexBuffer();
  NI_VERIFY(Get(pSourceVB), "NULL vertex buffer in TerrainElement", return info);
  D3DVERTEXBUFFER_DESC vbDesc;
  pSourceVB->GetDesc(&vbDesc);
  NI_VERIFY(vbDesc.Format == D3DFMT_VERTEXDATA, "TerrainElement vertex buffer has unsupported format", return info);
  NI_VERIFY(vbDesc.Size > 0, "Empty vertex buffer in TerrainElement", return info);
  NI_VERIFY(vbDesc.Size % sizeof(TerrainElementStrideNew) == 0, "TerrainElement vertex buffer size doesn't match vertex size", return info);
  const unsigned numVertices = vbDesc.Size / sizeof(TerrainElementStrideNew);

  // access source element indices
  DXIndexBufferRef pSourceIB = pElement->mesh.GetIndexBuffer();
  NI_VERIFY(Get(pSourceIB), "NULL index buffer in TerrainElement", return info);
  D3DINDEXBUFFER_DESC ibDesc;
  pSourceIB->GetDesc(&ibDesc);
  NI_VERIFY(ibDesc.Format == D3DFMT_INDEX32, "TerrainElement index buffer has unsupported format", return info);
  NI_VERIFY(ibDesc.Size > 0, "Empty index buffer in TerrainElement", return info);
  NI_VERIFY(ibDesc.Size % (3 * sizeof(unsigned)) == 0, "TerrainElement index buffer size doesn't match triangle list", return info);
  unsigned numIndices = ibDesc.Size / sizeof(unsigned);

  // marks for several vertex culling steps
  info.marks.SetSize(numVertices);
  info.marks.FillZero();

  TerrainElementStrideNew const* pSourceVertices = Render::LockVB<TerrainElementStrideNew>(Get(pSourceVB), D3DLOCK_READONLY);
  NI_VERIFY(pSourceVertices, "Unable to lock TerrainElement vertices for reading", return info);

  //////////////////////////////////////////////////////////////////////////
  // project all vertices on spline

  // (x,y,w): x - distance to spline, y - parameter along spline, w - spline width at this parameter
  info.projected.clear(); 

  ProjectVertices(pSourceVertices, numVertices, info.projected, info.marks);

  pSourceVB->Unlock();
  // early cull for the entire terrain element
  if (info.marks.IsZeroFilled())
  {
    // no triangles are needed
    info.isEmpty = true;
    return info;
  }

  info.isEmpty = false;

  //////////////////////////////////////////////////////////////////////////
  // cull triangles that are entirely outside
  info.indices.clear();
  {
    unsigned const* pSourceIndices = Render::LockIB(Get(pSourceIB), D3DLOCK_READONLY);
    NI_VERIFY(pSourceIndices, "Unable to lock TerrainElement indices for reading", pSourceVB->Unlock(); return info);

    CullTriangles(pSourceIndices, numIndices, info.marks, info.projected, info.indices);
    NI_ASSERT(!info.indices.empty(), "No affected triangles found but this case is checked earlier with 'marks' array");

    pSourceIB->Unlock();
  }

  // mark used vertices
  info.marks.FillZero();
  for (unsigned i = 0, n = info.indices.size(); i < n; ++i)
    info.marks.SetData(info.indices[i]);

  // reindex to cull unused vertices
  info.reindex.resize(numVertices);
  unsigned lastFreeIndex = 0;
  for (unsigned i = 0; i < numVertices; ++i)
    info.reindex[i] = info.marks.GetData(i) ? lastFreeIndex++ : REINDEX_SKIP;
  info.numVerticesUsed = lastFreeIndex;
  NI_ASSERT(info.numVerticesUsed <= numVertices, "Some extra vertices appeared");

  return info;
}



void RoadGeometryBuilder::AddTerrainElement( Terrain::TerrainElement const* pElement, Terrain::TerrainElementId elementID, bool recollect )
{
  TerrainElementInfo& info = CollectInfo( pElement, elementID, recollect );

  if ( info.isEmpty )
    return;

  // К этому моменту получены следующие данные:
  // "pSourceVertices[N]" содержит для каждой вершины оригинальные данные террейна
  // "projected[N]" содержит для каждой вершины ее координаты в системе сплайна
  // "indices[]" содержит нужные треугольники (тройки индексов)
  // "marks[N]" содержит пометки для каждой вершины (нужна или нет)
  // "numVerticesUsed" содержит количество нужных вершин
  // "reindex[N]" для каждой вершины содержит ее новый номер или "REINDEX_SKIP"

  //////////////////////////////////////////////////////////////////////////
  // copy used vertices and triangles to the common arrays

  DXVertexBufferRef pSourceVB = pElement->mesh.GetVertexBuffer();
  NI_VERIFY(Get(pSourceVB), "NULL vertex buffer in TerrainElement", return);
  TerrainElementStrideNew const* pSourceVertices = Render::LockVB<TerrainElementStrideNew>(Get(pSourceVB), D3DLOCK_READONLY);
  NI_VERIFY(pSourceVertices, "Unable to lock TerrainElement vertices for reading", return);

  unsigned prevNumVertices = roadVertices.size();
  AddVertices(pSourceVertices, info.projected, info.marks, info.numVerticesUsed);

  // fill indices
  {
    unsigned prevNumIndices = roadIndices.size();
    roadIndices.reserve(prevNumIndices + info.indices.size());
    for (unsigned i = 0, n = info.indices.size(); i < n; ++i)
    {
      unsigned index = info.reindex[info.indices[i]];
      NI_ASSERT(index != REINDEX_SKIP, "Triangle references vertex that was culled");
      roadIndices.push_back(prevNumVertices + index); // include offset
    }
    NI_ASSERT(roadIndices.size() == (int)prevNumIndices + info.indices.size(), "Failed to add all indices correctly");
  }

  pSourceVB->Unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename IndicesContainerType> // IndicesContainerType should be vector-alike
static void RemoveDuplicateTriangles(IndicesContainerType& _indices)
{
  UINT newSize = Render::RemoveDuplicateTriangles(&_indices[0], _indices.size());

  _indices.resize(newSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct hash<CVec3>
{
  size_t operator()(const CVec3& _s) const 
  {
    typedef const unsigned CU;
    return (CU&)_s.x ^ CU(17 * ((CU&)_s.y) ^ CU(17 * (CU&)_s.z));
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoadGeometryBuilder::RemoveDuplicates()
{
  const int numVertices = roadVertices.size();
  vector<unsigned> reindex(numVertices);
  hash_map<CVec3, unsigned> vertexMap;

  int i = 0;
  RoadGeometryVertex *pLast = roadVertices.begin();
  const RoadGeometryVertex * const pEnd = roadVertices.end();
  for(const RoadGeometryVertex *pCurr = pLast; pCurr != pEnd; ++pCurr)
  {
    hash_map<CVec3, unsigned>::iterator const it = vertexMap.find(pCurr->position);
    size_t idx;
    if(vertexMap.end() == it) {
      idx = vertexMap.size();
      vertexMap[pCurr->position] = idx;

      if(pLast != pCurr)
        *pLast = *pCurr;

      ++pLast;
    }
    else {
      idx = it->second;
#ifdef _DEBUG
      //NI_ASSERT(roadVertices[idx].position == pCurr->position, "RoadGeometryBuilder::RemoveDuplicates : wrong positions");
      NI_ASSERT(roadVertices[idx].params == pCurr->params, "RoadGeometryBuilder::RemoveDuplicates : wrong params");
      //NI_ASSERT(roadVertices[idx].color == pCurr->color, "RoadGeometryBuilder::RemoveDuplicates : wrong colors");
#endif // _DEBUG
    }
    reindex[i++] = idx;
  }
  roadVertices.resize( vertexMap.size() );

  const int numIndices = roadIndices.size();
  for(int i = 0; i < numIndices; ++i) {
    roadIndices[i] = reindex[roadIndices[i]];
    ASSERT(roadVertices.size() > (int)roadIndices[i]);
  }

  RemoveDuplicateTriangles(roadIndices);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Render::MeshGeometry* RoadGeometryBuilder::End()
{
  if (roadVertices.size() == 0)
  {
    return NULL;
  }

  RemoveDuplicates();

  // create DirectX buffers from collected data
  DXVertexBufferRef vb = Render::CreateVB(roadVertices.size() * sizeof(RoadGeometryVertex), Render::RENDER_POOL_MANAGED, &roadVertices[0]);
  NI_VERIFY(Get(vb), "Unable to create vertex buffer for road geometry", return NULL);
  DXIndexBufferRef ib = Render::CreateIB(roadIndices.size() * sizeof(unsigned), Render::RENDER_POOL_MANAGED, &roadIndices[0]);
  NI_VERIFY(Get(ib), "Unable to create index buffer for road geometry", return NULL);

  // create geometry structure
  Render::MeshGeometry* pGeometry = new Render::MeshGeometry();
  pGeometry->materialCount = 1;
  pGeometry->fragmentCount = 1;
  pGeometry->materialID[0] = 0;
  Render::Primitive* pPrimitive = pGeometry->primitives.push_back(new Render::Primitive());
  pPrimitive->SetVertexStream(vb, sizeof(RoadGeometryVertex));
  pPrimitive->SetIndexBuffer(ib);

  // vertex format
  Render::VertexFormatDescriptor fmt;
  fmt.AddVertexElement(Render::VertexElementDescriptor(0, offsetof(RoadGeometryVertex, position), Render::VERTEXELEMENTTYPE_FLOAT3,   Render::VERETEXELEMENTUSAGE_POSITION, 0));
  fmt.AddVertexElement(Render::VertexElementDescriptor(0, offsetof(RoadGeometryVertex, color0),   Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR, 0));
  fmt.AddVertexElement(Render::VertexElementDescriptor(0, offsetof(RoadGeometryVertex, color1),   Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR, 1));
  fmt.AddVertexElement(Render::VertexElementDescriptor(0, offsetof(RoadGeometryVertex, params),   Render::VERTEXELEMENTTYPE_FLOAT4,   Render::VERETEXELEMENTUSAGE_TEXCOORD, 0));
  pPrimitive->SetVertexDeclaration(Render::SmartRenderer::GetVertexFormatDeclaration(fmt));

  // primitive data
  Render::DipDescriptor &dip = pPrimitive->GetDipDescriptor();
  dip.primitiveType = Render::RENDERPRIMITIVE_TRIANGLELIST;
  dip.baseVertexIndex = 0;
  dip.minIndex = 0;
  dip.numVertices = roadVertices.size();
  dip.startIndex = 0;
  dip.primitiveCount = roadIndices.size() / 3;
  pGeometry->triangleCount = dip.primitiveCount;

  return pGeometry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// end of RoadGeometryBuilder.cpp
