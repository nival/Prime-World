#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "SceneObject.h"

#include "TraceFX.h"

namespace NScene
{

class TraceSceneComponent : public SceneComponent
{
	TraceSceneComponent() : pA(NULL), pB(NULL) {}

public:
	typedef NDb::DBTraceSceneComponent NDbType;

	TraceSceneComponent( const Placement& pos );
	TraceSceneComponent( const NDb::DBTraceSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
	~TraceSceneComponent();

	virtual void OnAfterAdded(SceneObject *pObject);
  virtual void Reinit();
  virtual void Deinit();
  virtual void DisableStrongWithWaitingForFinish();
  virtual bool Ready2Die();

  virtual void Attach( SceneComponent* toadd );

  virtual void ForAllMaterials(Render::IMaterialProcessor &proc);
  virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);
	virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

  virtual void OnTraversibleChanged();

private:
	NDb::Ptr<NDb::DBTraceSceneComponent> pDBObject;
	TraceFX trace;
	Render::AABB localAABB;

	SceneObject const* pSceneObject;
	Locator const* pA;
	Locator const* pB;
  bool waitingForFinish;
};

}

