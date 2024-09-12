#include "stdafx.h"
#include "LightningSceneComponent.h"
#include "RenderableScene.h"
#include "../Render/debugrenderer.h"

#include "../System/InlineProfiler.h"

namespace NScene
{

LightningSceneComponent::LightningSceneComponent( const Placement& pos )
:	SceneComponent(0, 0, pos), pSceneObject(NULL), pA(NULL), pB(NULL)
{
	localAABB.Set(CVec3(0.0f, 0.0f, 0.0f), CVec3(0.5f, 0.5f, 0.5f));
	lightning.SetDBID(dbid);
}

LightningSceneComponent::LightningSceneComponent( const NDb::DBLightningSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
:	SceneComponent(pObject, pObj, pos), pDBObject(pObject), pSceneObject(NULL), pA(NULL), pB(NULL)
{
	localAABB.Set(CVec3(0.0f, 0.0f, 0.0f), CVec3(0.5f, 0.5f, 0.5f));
	lightning.SetMaterial(pDBObject->material.GetPtr());
	lightning.SetParameters(pDBObject->fxParams);
	lightning.SetDBID(dbid);
}

LightningSceneComponent::~LightningSceneComponent()
{
}

void LightningSceneComponent::OnAfterAdded(class SceneObject *pObject)
{
	pSceneObject = pObject;
}

void LightningSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  // Make result matrix
	Matrix43 resultmatrix;
	worldPlacement.GetMatrix( &resultmatrix );
	
	// Transform local AABB to global one
	worldAABB.Transform( resultmatrix, localAABB );

	// Update object's AABB
	pars.objectAABB.Grow(worldAABB);

	if (pSceneObject && !pA && !pB) {
		pA = pSceneObject->FindLocator(pDBObject->fromLocator.c_str());
		pB = pSceneObject->FindLocator(pDBObject->toLocator.c_str());
	}

  CVec3 markerA(-2.5f, 0.0f, 0.0f);
  CVec3 markerB(+2.5f, 0.0f, 0.0f);
	if (pA && pB)
	{
		pA->CalculateWorldPosition(markerA);
		pB->CalculateWorldPosition(markerB);
  }

	lightning.SetWorldMatrix(IDENTITY_MATRIX);
	lightning.Update(markerA, markerB, timeDiff);
}

void LightningSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
	SceneComponent::RenderToQueue(queue, sceneConstants);
	lightning.RenderToQueue(queue);
}

void LightningSceneComponent::ForAllMaterials(Render::IMaterialProcessor &proc)
{
	Render::BaseMaterial* pMaterial = lightning.GetMaterial();
	if (pMaterial)
		proc(*pMaterial);
}

void LightningSceneComponent::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)
{
	NI_ASSERT(pDBObject.GetPtr() != NULL, "Cannot modify color while missing original data.");
	LightningFX::Params params(lightning.GetParameters());
	params.color.Mad(params.color, mul, add);
	lightning.SetParameters(params);
}


} // namespace NScene
