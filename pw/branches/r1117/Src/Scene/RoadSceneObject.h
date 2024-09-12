#pragma once
#ifndef _ROADSCENEOBJECT_H_
#define _ROADSCENEOBJECT_H_

#include "Scene.h"
#include "SceneObject.h"
#include "../Render/RenderComponent.h"
#include "../System/Spline.h"
#include "../System/BitData.h"
#include "../Terrain/TerrainElementManager.h"
#include "RoadGeometryBuilder.h"

namespace Terrain
{
  namespace EModification
  {
    enum Enum;
  }
}

namespace Terrain
{
  struct PatchMapping;
}

namespace NScene
{

class RoadSceneObject : public SceneObject, public Render::RenderComponent
{
public:
  DECLARE_NEWDELETE_ALIGN16(RoadSceneObject)

  RoadSceneObject( IScene* _pScene, const NDb::Road* _pDBRoad, bool _bEditable = false );
  virtual ~RoadSceneObject();

  DEF_RGROUP(RG_ROADS)

  virtual void RemoveFromScene();

  // reconstruct road upon request
  void Rebuild(bool useBakedData = false);

  // save binary data to load later in runtime instead of reconstructing
  void Store(Stream *pStream);

  // reconstruct road upon parameters change (spline shape, width, etc.)
  void OnDBResourceChanged( const NDb::DBID& dbid );

  // for picking road in editor
  bool IsIntersectWith( float terrainX, float terrainY, const CVec3& pickLocation );

  // render additional helpers etc.
  void RenderDebug( Render::IDebugRender* _debugRenderer );

  // process console commands
  static bool OnRoadShowCommand(const char *pName, const vector<wstring>& params);
  static bool OnRoadSplineCommand(const char *pName, const vector<wstring>& params);

  //////////////////////////////////////////////////////////////////////////
  // From NScene::SceneObject

  // add batches to the render queue
  virtual void Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );

  // call drawing routines for debugging
  virtual void DebugDraw( Render::IDebugRender* _debugRenderer ) {} // inconvenient method, RenderDebug() is used instead [6/24/2010 smirnov]

  //////////////////////////////////////////////////////////////////////////
  // From Render::RenderComponent

  // add batches to the render queue [internal?]
  virtual void RenderToQueue( Render::BatchQueue& queue );

  Render::OcclusionQueries* GetQueries() const { return 0; }
  
  // setup shader constants right before sending primitive to DirectX
  virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;

private:
  // load binary data
  bool Load(Stream *pStream);

  // load previously saved binary data instead of reconstructing in runtime
  bool Load(const string& fileName);

  // reconstruct road spline
  void RebuildSpline();

  // reconstruct road geometry by spline
  void RebuildGeometry();

  // set material pins values
  void UpdatePins(Render::BaseMaterial* pMaterial);

  // build geometry for all terrain elements
  void ProcessTerrainElements();

  void PrepareSplineElementsMask();
  
  // build geometry for specified terrain element
  void TerrainElementGatherTriangles( Terrain::TerrainElementId id, bool forceUpdate );

  float GetWidth(float at) const
  {
    if (!Get(pSpline))
      return 0.f;

    return pSpline->GetWidth(at);
  }

  void BuildAABB();

  static void TerrainModificationCB( void *pData, int flags, int elementID, Terrain::EModification::Enum callbackType );

private:
  bool bEditable;
  bool bDebugGeometry;
  NDb::ChangeablePtr<NDb::Road> pDBRoad;
  ScopedPtr<Render::MeshGeometry> pGeometry;
  ScopedPtr<Render::BaseMaterial> pMaterialN;
  ScopedPtr<Render::BaseMaterial> pMaterialA;
  ScopedPtr<Render::BaseMaterial> pMaterialB;

  ScopedPtr<CCompositeBSplineWidth<CVec2>> pSpline;
  CArray1Bit splineMask;
  bool needUpdateMask;

  CArray1Bit updateMask;

  ScopedPtr<RoadGeometryBuilder> pBuilder;
  ScopedPtr<Terrain::PatchMapping> pPatchMapping;
  //ScopedArray< ScopedPtr<Render::Primitive> > primitives;
  ScopedPtr<Render::IRenderablePrimitive> primitive;

  static int s_showGeometry;
  static int s_showSpline;
};

} // namespace NScene

#endif // _ROADSCENEOBJECT_H_
