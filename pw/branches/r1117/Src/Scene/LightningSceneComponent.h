#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "SceneObject.h"

#include "LightningFX.h"

namespace NScene
{

class LightningSceneComponent : public SceneComponent
{
	LightningSceneComponent() : pA(NULL), pB(NULL) {}

public:
	typedef NDb::DBLightningSceneComponent NDbType;

	LightningSceneComponent( const Placement& pos );
	LightningSceneComponent( const NDb::DBLightningSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
	~LightningSceneComponent();

	virtual void OnAfterAdded(SceneObject *pObject);

	virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

	virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);
	virtual void ForAllMaterials(Render::IMaterialProcessor &proc);

private:
	NDb::Ptr<NDb::DBLightningSceneComponent> pDBObject;
	LightningFX lightning;

	SceneObject const* pSceneObject;
	Locator const* pA;
	Locator const* pB;
};

}

