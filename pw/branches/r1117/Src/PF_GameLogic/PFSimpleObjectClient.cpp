#include "stdafx.h"

#include "PFClientObjectHelpers.h"

#include "../PF_Core/ClientObject.h"
#include "../PF_Core/EffectsPool.h"
#include "../Scene/SceneObjectCreation.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/EditorSceneObject.h"
#include "../Scene/HeightsController.h"
#include "../Scene/SceneObjectCreation.h"
#include "../Scene/RoadSceneObject.h"
#include "../Scene/ParticleSceneComponent.h"

#include "PFSimpleObjectClient.h"
#include "PFClientVisibilityMap.h"
#include "AdventureScreen.h"

using namespace NScene;

namespace NGameX
{

AutoPtr<SceneObject> CreateSceneObject(const NDb::DBSceneObject* pModel, Placement const& place, int id, IScene* pAtScene, bool heightObject)
{
	Placement finalPlacement = place;
	//finalPlacement.pos   = CVec3(pos.x * 2.5f, pos.y * 2.5f, 0.0f ) + place.pos; // smirnov [2008/12/4]: what is 2.5? Terrain::GridConstants.metersPerTile?
	//finalPlacement.rot   = CQuat(FP_PI2 * (static_cast<float>(orientation)), CVec3(0.0f, 0.0f, 1.0f)) * place.rot;
	//finalPlacement.scale = place.scale;

	//
  if ( heightObject )
  {
	  PlaceOnTerrain( pAtScene->GetHeightsController(), finalPlacement.pos, 0 );
  }
  else
  {
    PlaceOnTerrain( pAtScene->GetHeightsController(), finalPlacement.pos, 1 );
  }

	AutoPtr<SceneObject> pObj;
	if (pModel)
		pObj = CreateSceneObject( pAtScene, *pModel, BADNODENAME );
	else
		pObj = AutoPtr<SceneObject>(new SceneObject(pAtScene));

	pObj->SetPlacement(finalPlacement);
	pObj->UpdateForced();
	pObj->AddToScene(pAtScene);

	//Test for DBParticleSceneComponent in Height Object
	if ( heightObject )
	{
		struct Proc : public NScene::FullTraverser
		{
			bool isFind;

			Proc() : isFind( false ) {}
			virtual void operator()( SceneComponent *pSC )
			{
				if ( !isFind )
				{
					if ( NScene::ParticleSceneComponent* particleSC = dynamic_cast<NScene::ParticleSceneComponent*>( pSC ) )
					{
						isFind = true;
					}
				}
			}
		} f;

		pObj->Traverse( f );
		NI_DATA_ASSERT( !f.isFind, NStr::StrFmt("Find DBParticleSceneComponent in height object %s", pModel->GetDBID().GetFormatted().c_str()) );
	}

	return pObj;
}

AutoPtr<SceneObject> CreateRoadSceneObject(const NDb::Road* pDBRoad, Placement const& place, int id, IScene* pAtScene)
{
  Placement finalPlacement = place;
  PlaceOnTerrain( pAtScene->GetHeightsController(), finalPlacement.pos, 1 );

  AutoPtr<SceneObject> pObj = AutoPtr<SceneObject>(new RoadSceneObject(pAtScene, pDBRoad, false));
  pObj->AddToScene(pAtScene);

  return pObj;
}

// AutoPtr<SceneObject> CreateSceneObject(const NDb::BaseVisualObject* pModel, Placement const& place, int id, IScene* pAtScene)
// {
// 	Placement finalPlacement = place;
// 	//finalPlacement.pos   = CVec3(pos.x * 2.5f, pos.y * 2.5f, 0.0f ) + place.pos; // smirnov [2008/12/4]: what is 2.5? Terrain::GridConstants.metersPerTile?
// 	//finalPlacement.rot   = CQuat(FP_PI2 * (static_cast<float>(orientation)), CVec3(0.0f, 0.0f, 1.0f)) * place.rot;
// 	//finalPlacement.scale = place.scale;
// 
// 	//
// 	PlaceOnTerrain( pAtScene->GetHeightsController(), finalPlacement.pos );
// 
// 	AutoPtr<SceneObject> pObj(new SceneObject(pAtScene));
// 	pObj->SetPlacement(finalPlacement);
// 
// 	vector<CObj<SceneComponent>> comps = ParseBaseVisualObject( pModel );
// 	for (int i = 0; i < comps.size(); i++)
// 		pObj->Add(Get(comps[i]));
// 
// 	pObj->UpdateForced();
// 	pObj->AddToScene(pAtScene);
// 
// 	return pObj;
// }



AutoPtr<NScene::SceneObject> CreateSceneObject(NDb::AdvMapObject const* pObject, int id, NScene::IScene* pAtScene)
{
  NI_VERIFY(pObject,             "Invalid Map Object provided!", return AutoPtr<NScene::SceneObject>(); ) ;
  NI_VERIFY(pObject->gameObject, "Invalid Map Object provided!", return AutoPtr<NScene::SceneObject>(); ) ;
  NI_VERIFY(pAtScene,            "Invalid Scene provided!",      return AutoPtr<NScene::SceneObject>(); ) ;

  const NDb::SingleStateObject* sso = dynamic_cast<const NDb::SingleStateObject*>(pObject->gameObject.GetPtr());
  if( sso && sso->sceneObject )
    return CreateSceneObject(sso->sceneObject.GetPtr(), pObject->offset.GetPlace(), id, pAtScene, pObject->gameObject->heightObject );

  const NDb::Road* road = dynamic_cast<const NDb::Road*>(pObject->gameObject.GetPtr());
  if ( road )
    return CreateRoadSceneObject(road, pObject->offset.GetPlace(), id, pAtScene);

//   else
//   if( pObject->gameObject->visualObject )
//   {
//     return CreateSceneObject(pObject->gameObject->visualObject.GetPtr(),
//       pObject->place.GetPlace(), pObject->orientation, id, pAtScene);
//   }

  NI_ALWAYS_ASSERT("Invalid visual object!");

  return AutoPtr<NScene::SceneObject>();
}

PFClientSimpleObject::PFClientSimpleObject(PF_Core::WorldObjectRef pWO, NDb::AdvMapObject const& dbObject, IScene* pScene)
: NWorld::PFClientObjectBase(pWO)
, isFreezed(false)
, visMapClient(0)
, visPos( dbObject.offset.GetPlace().pos.x, dbObject.offset.GetPlace().pos.y )
, isVisibleUnderWarfog(false)
{
	Subscribe();

  NDb::SimpleObject const *pSO = dynamic_cast<NDb::SimpleObject const *>(dbObject.gameObject.GetPtr());

  if(pSO)
    isVisibleUnderWarfog = pSO->isVisibleUnderWarfog; 

	PF_Core::WorldObjectBase* pWorldObject = GetWorldObject();	

	if(pScene && pWorldObject)
	{
    NGameX::AdventureScreen::Instance()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(dbObject.gameObject), BADNODENAME);
    pSceneObject = CreateSceneObject(&dbObject, pWorldObject->GetObjectId(), pScene);

		if ( pSceneObject && dbObject.gameObject->heightObject )
		{
			// Process scene object
			struct Func : public Render::IMaterialProcessor
			{
				virtual void operator()(Render::BaseMaterial &material)
				{
          if ( NDb::MATERIALPRIORITY_MESHESOPAQUE == material.GetPriority() )
						material.SetPriority(NDb::MATERIALPRIORITY_TERRAINOBJECTS);
				}
			} f;

			NScene::ForAllMaterials(*pSceneObject, f);
		}
	}
}

void PFClientSimpleObject::Hide(bool hide)
{
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
    if (const NWorld::PFSimpleObject * pObject = WorldObject())
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

void PFClientSimpleObject::DoFreeze()
{
	if ( visMapClient && pSceneObject )
	{
		if (isVisibleUnderWarfog || visMapClient->IsPointVisible( visPos ) )
		{
			if ( isFreezed )
			{
				pSceneObject->SetFreeze( false );
				isFreezed = false;
			}
		}
		else
		{
			if ( !isFreezed )
			{
				pSceneObject->SetFreeze( true );
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
} // namespace NGameX
