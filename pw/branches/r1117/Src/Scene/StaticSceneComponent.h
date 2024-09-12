#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "../Render/StaticMesh.h"

namespace Render
{
  class MeshVertexColors;
}

namespace NScene
{

class LightingScene;

class StaticSceneComponent : public SceneComponent
{
protected:
	ScopedPtr<Render::StaticMeshBase> pStaticMesh;
	float time;
  bool needLightingSH;

	StaticSceneComponent() : time ( 0.f ), pStaticMesh( 0 ), needLightingSH(false) {}

private:
  bool CheckMaterials(const NDb::DBStaticSceneComponent* pDBComponent, NDb::LightingPin* pLighting);

  NDb::Ptr<NDb::DBStaticSceneComponent> pDBObject;

public:
	typedef NDb::DBStaticSceneComponent NDbType;

	StaticSceneComponent(const NDb::StaticMesh* pObject, const Placement& pos);
	StaticSceneComponent(const NDb::DBStaticSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos);

	virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

  virtual void Attach( SceneComponent* toadd );


	virtual void OnAfterAdded(class SceneObject *pObject);

	virtual void ForAllMaterials(Render::IMaterialProcessor &proc);

  Render::MeshVertexColors const *GetVertexColors() const { return pStaticMesh ? pStaticMesh->GetVertexColors() : NULL; }
  bool LoadVertexColors(NScene::MeshVertexColorsManager &man, int componentIdx); // returns true on success
  void CalculateLighting(Render::SceneConstants const &sceneConst) { CalculateLightingEx(sceneConst, NDb::LIGHTENVIRONMENT_DAY); }
  void CalculateLightingEx(Render::SceneConstants const &sceneConst, NDb::ELightEnvironment const selector)
  {
    if (pStaticMesh)
      pStaticMesh->CalculateLightingEx(sceneConst, selector);
  }

  bool BakedLightingUsed();
  void AddGeometryCRC(Crc32Checksum &crc);
};

}

