#include "stdafx.h"

#include "PFClientMultistateObject.h"
#include "PFClientNatureSceneObjectsHolder.h"

#include "../PF_Core/EffectsPool.h"

#include "../System/InlineProfiler.h"
#include "PFClientVisibilityMap.h"
#include "AdventureScreen.h"

namespace NGameX
{

void SetMaterialPriorityAsTerrainObject( NScene::SceneObject* pSO )
{
  if ( !pSO )
    return;

  struct Func : public Render::IMaterialProcessor
  {
    virtual void operator()(Render::BaseMaterial &material)
    {
      if(NDb::MATERIALPRIORITY_MESHESOPAQUE == material.GetPriority())
        material.SetPriority(NDb::MATERIALPRIORITY_TERRAINOBJECTS);
    }
  } f;

  NScene::ForAllMaterials( *pSO, f );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFClientMultiStateObject
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
PFClientMultiStateObject::PFClientMultiStateObject(const PF_Core::WorldObjectRef &pWO, NScene::IScene* pScene, NDb::AdvMapObject const& advMapObject, int faction)
: PFClientLogicObject( pWO, CreatePars(pScene, BADNODENAME, advMapObject) )
, active(true)
, isFreezed(false)
, visMapClient(0)
, visPos( advMapObject.offset.GetPlace().pos.x, advMapObject.offset.GetPlace().pos.y )
, isVisibleUnderWarfog(false)
{
  NI_ASSERT( advMapObject.gameObject && dynamic_cast<const NDb::MultiStateObject*>( advMapObject.gameObject.GetPtr() ), "PFClientMultiStateObject needs valid NDb::MultiStateObject object to construct!" );
  const NDb::MultiStateObject* mso = static_cast<const NDb::MultiStateObject*>( advMapObject.gameObject.GetPtr() );
  
  if(mso)
    isVisibleUnderWarfog = mso->isVisibleUnderWarfog;

  NGameX::AdventureScreen::Instance()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(advMapObject.gameObject), BADNODENAME);

  // Make placement
  Placement pl = NULLPLACEMENT;
  pl = advMapObject.offset.GetPlace();

  // Place it on terrain
  isHeightObject = advMapObject.gameObject->heightObject;
  if ( isHeightObject )
  {
    NScene::PlaceOnTerrain( pScene->GetHeightsController(), pl.pos, 0 );
  }
  else
  {
    NScene::PlaceOnTerrain( pScene->GetHeightsController(), pl.pos, 1 );
  }

  dbTrans = mso->effects;

  Reset( pSceneObjectsHolder, NatureSceneObjectsHolder::Create(pScene, this, pl, pWO->GetObjectId(), mso) );

  const bool night = WorldObject() ? WorldObject()->GetWorld()->IsNight() : false;

  pSceneObjectsHolder->SetActive( SelectSceneObjectIndex(faction, night), false );
  
  NScene::SceneObject* pSceneObject = GetSceneObject();
  if ( pSceneObject )
  {
    // Make size of unit
    if ( pSceneObject->GetRootComponent() )
    {
      CVec3 halfSize = pSceneObject->GetRootComponent()->GetWorldAABB().halfSize;
      unitSize = 2 * max( halfSize.x, halfSize.y );
    }
    
    if ( NScene::SceneComponent* sc = pSceneObject->GetRootComponent() )
    {
      if ( NDb::Ptr<NDb::TimeController> timeCtrl = sc->GetTimeControllerDesc() )
      {
        float fadein = timeCtrl->fadein;
        if ( fadein > 0.0f )
        {
          pSceneObject->UpdateForced(fadein);
          //pSceneObject->SetFreeze(true);
        }
      }
    }

    if ( isHeightObject )
    {
      SetMaterialPriorityAsTerrainObject( pSceneObject );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFClientMultiStateObject::NeedToUpdate() const
{
  return  ( pSceneObjectsHolder && pSceneObjectsHolder->NeedUpdateTransactions() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMultiStateObject::SubscribeToUpdate()
{
  if ( !active && NeedToUpdate() )
  {
    active = true;
    Subscribe();
  }
  else if ( active && !NeedToUpdate() )
  {
    active = false;
    Unsubscribe();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMultiStateObject::SetVisibility(bool bVisible_)
{
  bVisible = bVisible_;
  SubscribeToUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMultiStateObject::OnSceneObjectUpdate(NScene::SceneObject &/*sceneObject*/, float /*timeDiff*/)
{
  NI_PROFILE_FUNCTION
  
	UpdateVisibility();
  SubscribeToUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFClientMultiStateObject::OnSceneObjectBecomeVisible(class SceneObject &/*sceneObject*/, float /*timeBeingInvisible*/)
{
	UpdateVisibility();
  SubscribeToUpdate();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMultiStateObject::Hide(bool hide)
{
  NScene::SceneObject* pSceneObject = GetSceneObject();

  if ( !pSceneObject )
    return;

  if (hide)
  {
    if (pSceneObject->IsInScene())
    {
      pSceneObject->RemoveFromScene();
    }
  }
  else
  {
    if (const NWorld::PFLogicObject * pObject = WorldObject())
    {
      if (const NWorld::PFWorld * pWorld = pObject->GetWorld())
      {
        if (NScene::IScene * pScene = pWorld->GetScene())
        {
          if (!pSceneObject->IsInScene())
          {
            pSceneObject->AddToScene(pScene);
          }
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMultiStateObject::Update(float timeDelta)
{
  NI_PROFILE_FUNCTION

  PFClientLogicObject::Update(timeDelta);

  if ( isHeightObject )
  {
    SetMaterialPriorityAsTerrainObject( GetSceneObject() );
  }

  SubscribeToUpdate();
}

void PFClientMultiStateObject::DoFreeze()
{
	if ( visMapClient )
	{
		if ( isVisibleUnderWarfog || visMapClient->IsPointVisible( visPos ) )
		{
			if ( isFreezed )
			{
				for ( int i = 0; i < 3; i++ )
				{
					NScene::SceneObject* so = pSceneObjectsHolder->Get(i).__gEt__();
					if ( so )
					{
						so->SetFreeze( false );
					}
				}
				isFreezed = false;
			}
		}
		else
		{
			if ( !isFreezed )
			{
				for ( int i = 0; i < 3; i++ )
				{
					NScene::SceneObject* so = pSceneObjectsHolder->Get(i).__gEt__();
					if ( so )
					{
						so->SetFreeze( true );
					}
				}
				isFreezed = true;
			}
		}
	}
	else
	{
		AdventureScreen* screen = AdventureScreen::Instance();
		visMapClient = screen->GetClientVisibilityMap();
	}
}

void PFClientMultiStateObject::OnWorldObjectDie()
{
  if ( GetSceneObject() )
    GetSceneObject()->SetUpdateHook(0);

  PFClientLogicObject::OnWorldObjectDie();
}

int PFClientMultiStateObject::SelectSceneObjectIndex(const int natureType, const bool night)
{
  if (night)
    return NDb::KnownEnum<NDb::ENatureType>::SizeOf() + natureType;
  else
    return natureType;
}

void PFClientMultiStateObject::SetState(const int _natureType, const bool _night)
{
  pSceneObjectsHolder->SetActive( SelectSceneObjectIndex(_natureType, _night), bVisible );
  SubscribeToUpdate();
}

} //namespace NGameX
