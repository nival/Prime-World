#pragma once

#include "../Render/RenderComponent.h"
#include "../Render/sceneconstants.h"
#include "../Render/batch.h"
#include "../Render/omnilight.h"
#include "../Render/ConvexVolume.h"
#include "../Render/visitmarker.h"
#include "../Scene/VoxelGridObj.h"
#include "DBScene.h"
#include "../System/SimpleSignalST.h"

namespace Terrain
{
	class Terrain;
}

namespace Render
{
  _interface IDebugRender;
}

#define GROUPFLAGS_ALL  0x7FFFFFFF

class RenderableSceneObj : public NScene::VoxelGridObj
{
public:
  virtual void Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL ) = 0;
  virtual void DebugDraw( Render::IDebugRender* _debugRenderer ) = 0;
};

struct IObjectFunctor
{
  typedef NScene::VoxelGridObj::RenderGroups RenderGroups;

  IObjectFunctor(RenderGroups _group = NScene::VoxelGridObj::NUM_GROUPS) : group(_group) {}
  RenderGroups getRenderGroup() const { return group; }

  virtual void operator()(RenderableSceneObj &obj) = 0;

private:
  NScene::VoxelGridObj::RenderGroups group;
};

struct FrustumIntersection
{
	CVec2 points[4];
};


class IRenderableScene
{
public:
  typedef SimpleSignalST<bool, IRenderableScene> SkipFrameSignal;

	virtual void PrepareForRendering() = 0;

	virtual const Render::ConvexVolume& GetCameraFrustum() const = 0;

	virtual const FrustumIntersection& GetCameraFrustumIntersection() const = 0;

	virtual const Render::AABB& GetFrustumAABB() const = 0;

	virtual Terrain::Terrain* GetRenderableTerrain() const = 0;

  virtual void ForAllObjects(IObjectFunctor &func) = 0;
	virtual void ForAllObjectsInCamera(IObjectFunctor &func, bool bNewProcess = true) = 0;
	virtual void ForAllObjectsInFrustum(IObjectFunctor &func, Render::ConvexVolume const &frustum, bool bNewProcess = true) = 0;
	virtual void ForAllObjectsInBBox(IObjectFunctor &func, const Render::AABB& aabb, bool bNewProcess = true) = 0;

	//virtual RenderableList& GetRenderableList( const RenderRequestInfo& info ) = 0;
	virtual const Render::SceneConstants& GetSceneConstants() = 0;
	virtual const Render::SceneConstants& GetSceneConstants(const NDb::ELightEnvironment selector) const = 0;
	virtual float GetCameraRod() const = 0;
	virtual void SetCulledScreenSize( float ) = 0;

  virtual bool NeedDebugRender() = 0;
};
