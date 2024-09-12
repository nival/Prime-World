#include "stdafx.h"
#include "TraceSceneComponent.h"
#include "RenderableScene.h"
#include "../Render/debugrenderer.h"

#include "../System/InlineProfiler.h"

namespace NScene
{

TraceSceneComponent::TraceSceneComponent( const Placement& pos )
:	SceneComponent(0, 0, pos), pSceneObject(NULL), pA(NULL), pB(NULL), waitingForFinish(false)
{
	localAABB.Set(CVec3(0.0f, 0.0f, 0.0f), CVec3(0.5f, 0.5f, 0.5f));
	trace.SetDBID(dbid);
}

TraceSceneComponent::TraceSceneComponent( const NDb::DBTraceSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
:	SceneComponent(pObject, pObj, pos), pDBObject(pObject), pSceneObject(NULL), pA(NULL), pB(NULL), waitingForFinish(false)
{
	localAABB.Set(CVec3(0.0f, 0.0f, 0.0f), CVec3(0.5f, 0.5f, 0.5f));
	TraceFX::Params params;
	params.maxLength = pObject->maxLength;
  params.maxStepLength = 2.0f * pObject->maxLength; // smirnov [2009/7/13]: todo: extern parameter?
	params.speedStart = pObject->speedStart;
	params.speedStop = pObject->speedStop;
	params.colorFirst = pObject->colorFirst;
	params.colorLast = pObject->colorLast;
	params.offsetColor = pObject->offsetColor;
	params.offsetAlpha = pObject->offsetAlpha;
	params.fadeoutSpeed = pObject->fadeoutSpeed;
	params.skewness = pObject->skewness;
	trace.SetParameters(params);
	trace.SetMaterial(pObject->material.GetPtr());
	trace.SetDBID(dbid);
}

TraceSceneComponent::~TraceSceneComponent()
{
}

void TraceSceneComponent::OnAfterAdded(class SceneObject *pObject)
{
	pSceneObject = pObject;
}

void TraceSceneComponent::Reinit()
{
  SceneComponent::Reinit();
  trace.Reinit();
  waitingForFinish = false; // in case updates were aborted w/o waiting for finish (e.g. object became invisible)
}

void TraceSceneComponent::OnTraversibleChanged()
{
  trace.Enable( disabledCount <= 0 );
}

void TraceSceneComponent::Deinit()
{
  trace.Enable(false);
  SceneComponent::Deinit();
  if (waitingForFinish)
  {
    DisableStrong(true);
    waitingForFinish = false;
  }
}

void TraceSceneComponent::DisableStrongWithWaitingForFinish()
{
  // smirnov [2009/9/9]: do not call parent because it will interrupt effect
  trace.Enable(false);
  waitingForFinish = !trace.IsOff();
  if (!waitingForFinish)
    DisableStrong(true);
}

void TraceSceneComponent::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  Render::BaseMaterial* pMaterial = trace.GetMaterial();
  if (pMaterial)
    proc(*pMaterial);
}

void TraceSceneComponent::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)
{
  NI_ASSERT(pDBObject.GetPtr() != NULL, "Cannot modify color while missing original data.");
  TraceFX::Params params(trace.GetParameters());
  params.colorFirst.Mad(pDBObject->colorFirst, mul, add);
  params.colorLast.Mad(pDBObject->colorLast, mul, add);
  trace.SetParameters(params);
}

void TraceSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  // Make result matrix
	Matrix43 resultmatrix;
	worldPlacement.GetMatrix( &resultmatrix );
	
	// Transform local AABB to global one
	worldAABB.Transform( resultmatrix, localAABB );

	// Update object's AABB
	pars.objectAABB.Grow(worldAABB);

	if (pSceneObject && !pA && !pB)
  {
		pA = pSceneObject->FindLocator(pDBObject->locator1Name.c_str());
		pB = pSceneObject->FindLocator(pDBObject->locator2Name.c_str());
	}

	if (pA && pB)
	{
		CVec3 markerA, markerB;
		pA->CalculateWorldPosition(markerA);
		pB->CalculateWorldPosition(markerB);

		trace.SetWorldMatrix(IDENTITY_MATRIX);
		trace.Update(markerA, markerB, timeDiff);
	}

  if (waitingForFinish && trace.IsOff())
  {
    DisableStrong(true);
    waitingForFinish = false;
  }
}

void TraceSceneComponent::Attach( SceneComponent* toadd )
{
  if ( !toadd )
    return;

  SceneComponent* it = toadd;
  do 
  {
    it->SetJointIdx( -1 );
    if ( it->GetLocatorName().length() && !pDBObject.IsEmpty() && !pDBObject->locatorList.IsEmpty() )
    {
      for ( int i = 0; i < pDBObject->locatorList->locators.size(); i++ )
      {
        if ( pDBObject->locatorList->locators[i].name == it->GetLocatorName() )
        {
          const NDb::Locator& locator = pDBObject->locatorList->locators[i];
          const Placement& offset = locator.offset2.GetPlace();
          it->SetLocatorPos( offset.pos, offset.rot, offset.scale );
          it->SetLocatorName( it->GetLocatorName(), pDBObject->locatorList->locators[i].flags );
          break;
        }
      }
    }
    it = it->GetBrother();
  } while ( it && it != toadd );

  SceneComponent::Attach( toadd );
}

void TraceSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
	SceneComponent::RenderToQueue(queue, sceneConstants);
	trace.RenderToQueue(queue);
}

bool TraceSceneComponent::Ready2Die()
{
  bool res = trace.IsOff();
  return res;
}
} // namespace NScene
