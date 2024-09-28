#include "stdafx.h"

#include "../Render/VertexColorStream.h"
#include "../System/DebugVar.h"

#include "SceneObject.h"
#include "CollisionMap.h"
#include "CollisionHull.h"
#include "GeometryBuilders.h"
#include "StaticSceneComponent.h"
#include "AnimatedSceneComponent.h"
#include "AnimatedSplitSceneComponent.h"
#include "ParticleSceneComponent.h"
#include "SoundSceneComponent.h"
#include "TraceSceneComponent.h"
#include "LightningSceneComponent.h"
#include "WaterSceneComponent.h"
#include "TestSceneComponent.h"
#include "VertexColorManager.h"
#include "SceneObjectCreation.h"
#include "System/InlineProfiler.h"


namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static NDebug::PerformanceDebugVar objectCreationTime( "SceneObjectCreation", "RenderOffline", 1000, 5000, false );

  static float collisionInflateCoef = 2.3f;
  static float collisionInflateMaxSize = 2.5f;
  REGISTER_DEV_VAR( "collision_inflate_coef", collisionInflateCoef, STORAGE_NONE );
  REGISTER_DEV_VAR( "collision_inflate_max_size", collisionInflateMaxSize, STORAGE_NONE );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

bool NeedToCreateProxySceneComponent(const NDb::AttachedSceneComponent &attachedProxy)
{
	if (attachedProxy.events || attachedProxy.placement.pos.IsAnimated() || 
			attachedProxy.placement.rot.IsAnimated() || attachedProxy.placement.scale.IsAnimated())
		return true;

	if (attachedProxy.timeController)
	{
		const vector<NDb::AttachedSceneComponent> &attacheds = attachedProxy.component->attached;
		for (int i = 0; i < attacheds.size(); ++i)
			if (attacheds[i].timeController)
				return true;
	}

  if (attachedProxy.component->orientation != NDb::SCORIENTATION_DEFAULT)
  {
    return true;
  }

	return false;
}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> ParseSceneObject( const NDb::DBSceneObject* pVisual, IParseLocatorFunc &lf, const nstl::string& nodeName, bool isEditor, bool isStaticAndAnimatedOnly )
{
	NDb::Ptr<NDb::DBSceneObject> pHold( pVisual );
	if ( pVisual )
	{
    HierarchyCreator creator(lf, nodeName, isStaticAndAnimatedOnly);
		return creator.ParseAttachedSceneComponents( pVisual->attached, isEditor );
	}
	else
		return vector<CObj<SceneComponent>>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> ParseSceneComponent( const NDb::DBSceneComponent* pVisual, IParseLocatorFunc &lf, bool isEditor )
{
	HierarchyCreator creator(lf, BADNODENAME);
	return creator.ParseSceneComponent( pVisual, isEditor );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AutoPtr<NScene::SceneObject> CreateSceneObject( IScene *pScene, const NDb::DBSceneObject& sceneObject, const nstl::string& nodeName )
{
  NDebug::PerformanceDebugVarGuard guard( objectCreationTime, false );

	AutoPtr<SceneObject> pResult( new SceneObject(pScene, &sceneObject) );

	// Attach scene components to scene object
	ObjAddLocatorFunc lf(*pResult);
  vector<CObj<SceneComponent>> comps = ParseSceneObject(&sceneObject, lf, nodeName);
	for ( int  i = 0; i < comps.size(); i++ )
		pResult->Add( comps[i] );

	NI_DATA_ASSERT(comps.size() > 0, NStr::StrFmt("Scene object %s doesn't have components", GetFormattedDbId(sceneObject.GetDBID()).c_str()));

  if( MeshVertexColorsManager* pVCM = pScene->GetMeshVertexColorsManager() )
  {
    LoadColorsTraverser traverser(*pVCM);
    pVCM->SceneObjectVCBegin( &sceneObject.GetDBID() );
    pResult->Traverse(traverser);
    pVCM->SceneObjectVCEnd( &sceneObject.GetDBID() );
  }

	return pResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppendComponentsToSceneObject( SceneObject &object, const NDb::DBSceneComponent &sceneComponent )
{
	NScene::IScene *pScene = object.GetScene();
	MeshVertexColorsManager *pVCM = pScene ? pScene->GetMeshVertexColorsManager() : 0;

	// Attach scene components to scene object
	ObjAddLocatorFunc lf(object);
	vector<CObj<SceneComponent>> comps = ParseSceneComponent( &sceneComponent, lf, pVCM );
	for ( int  i = 0; i < comps.size(); i++ )
		object.Add( comps[i] );

	NI_DATA_ASSERT(comps.size() > 0, NStr::StrFmt("Scene object %s doesn't have components", GetFormattedDbId(sceneComponent.GetDBID()).c_str()));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AutoPtr<NScene::SceneObject> CreateSceneObject( IScene *pScene, const NDb::DBSceneComponent& sceneComponent )
{
  NDebug::PerformanceDebugVarGuard guard( objectCreationTime, false );

	AutoPtr<NScene::SceneObject> pResult( new SceneObject(pScene) );
	AppendComponentsToSceneObject(*pResult, sceneComponent);
	return pResult;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<StaticSceneComponent> HierarchyCreator::Create( const NDb::DBStaticSceneComponent* pDBComponent, const NDb::AttachedSceneComponent* pAttached, const Placement& transform )
{
	if ( pDBComponent->materialsReferences.empty() || pDBComponent->srcFileName.empty() )
		return 0;

	// Create static scene component
	return new StaticSceneComponent( pDBComponent, pAttached, transform);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> HierarchyCreator::ParseAttachedSceneComponents( const vector<NDb::AttachedSceneComponent> &attached, bool isEditor )
{
  NI_PROFILE_HEAVY_FUNCTION
  
	vector<CObj<SceneComponent>> rootComponents;

	for ( int i = 0; i < attached.size(); i++ )
    if(const NDb::Ptr<NDb::DBSceneComponent> &currComponent = attached[i].component)
	  {
      //TODO: Only edit
		  if (currComponent->GetObjectTypeID() != NDb::DBSceneComponent::typeId || 
			    NeedToCreateProxySceneComponent(attached[i]) || isEditor )
		  {
		    NI_PROFILE_HEAVY_BLOCK( "Block A" );
  		  
        if ( isStaticAndAnimatedOnly )
        {
          const NDb::DBSceneComponent* const currComponentPtr = currComponent.GetPtr();
          if ( dynamic_cast<const NDb::DBAnimatedSceneComponent*>(currComponentPtr) == 0
            && dynamic_cast<const NDb::DBStaticSceneComponent*>(currComponentPtr) == 0)
          {
            continue;
          }
        }

        NI_PROFILE_HEAVY_BLOCK( "Block A1" );

			  CObj<SceneComponent> pSC = currComponent->Create(*this, &attached[i], NULLPLACEMENT);
			  if ( pSC )
			  {
			    NI_PROFILE_HEAVY_BLOCK( "Block A2" );
				  pSC->SetLocatorName( attached[i].locatorName );
				  pSC->SetParentTransformUsageFlags( attached[i].attachFlags );
				  pSC->Init();

				  rootComponents.push_back( pSC );

          if ( !currComponent->locatorList.IsEmpty() )
          {
				    vector<NDb::Locator> const &locators = currComponent->locatorList->locators;
				    for ( int k = 0; k < locators.size(); ++k )
				    {
					    lf( locators[k], pSC );
				    }
          }

				  vector<CObj<SceneComponent>> comps = ParseAttachedSceneComponent( &attached[i], isEditor );
				  for ( int k = 0; k < comps.size(); k++ )
					  pSC->Attach( comps[k] );
			  }
		  }
		  else
		  {
		    NI_PROFILE_HEAVY_BLOCK( "Block B" );
  		
			  // Merge attached components into hierarchy
			  vector<CObj<SceneComponent>> comps = ParseAttachedSceneComponent( &attached[i], isEditor );

        if ( !currComponent->locatorList.IsEmpty() )
        {
          NI_PROFILE_HEAVY_BLOCK( "Block B2" );
          vector<NDb::Locator> const &locators = currComponent->locatorList->locators;
          if ( comps.size() )
          {
            for (int k = 0; k < locators.size(); ++k)
            {
              lf( locators[k], comps[0] );
            }
          }
        }
        
        NI_PROFILE_HEAVY_BLOCK( "Block B3" );

			  for ( int k = 0; k < comps.size(); k++ )
			  {
				  // Propagate proxy joint name to it's children
				  if ( attached[i].locatorName.length() )
				  {
					  comps[k]->SetLocatorName( attached[i].locatorName );
				  }

          comps[k]->SetParentTransformUsageFlags( attached[i].attachFlags );

				  // Use time controller from proxy component
				  if ( attached[i].timeController )
				  {
					  comps[k]->SetTimeController( attached[i].timeController );
				  }

				  // Set placement of proxy as base for it's children
				  comps[k]->AddBase( attached[i].placement.pos.begin()->value, 
				                     attached[i].placement.rot.begin()->value,
					                   attached[i].placement.scale.begin()->value );

				  // Propagate proxy id to it's children

          if ( !attached[i].id.empty() )
          {
            NI_DATA_ASSERT( !comps[k]->GetId().length(), NStr::StrFmt("In Proxy (%s) in component (%d) id already exist", 
              GetFormattedDbId(currComponent->GetDBID()).c_str(), k ) );
            comps[k]->SetId( attached[i].id );
          }
  				
				  rootComponents.push_back( comps[k] );
			  }
		  }
	  }

	return rootComponents;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> HierarchyCreator::ParseAttachedSceneComponent( const NDb::AttachedSceneComponent* pVisual, bool isEditor )
{
	return ParseAttachedSceneComponents( pVisual->component->attached, isEditor );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> HierarchyCreator::ParseAttachedSceneComponent( const NDb::DBSceneComponent* pVisual, bool isEditor )
{
	if ( pVisual )
	{
		return ParseAttachedSceneComponents( pVisual->attached, isEditor );
	}
	else
	{
		vector<CObj<SceneComponent>> rootComponents;
		return rootComponents;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> HierarchyCreator::ParseSceneComponent( const NDb::DBSceneComponent* pVisual, bool isEditor )
{
	vector<CObj<SceneComponent>> result;

	if ( !pVisual )
		return result;

	if ( pVisual->GetObjectTypeID() == NDb::DBSceneComponent::typeId && isEditor )
  {
    vector<CObj<SceneComponent>> attached = ParseAttachedSceneComponent( pVisual, isEditor );
    if ( attached.size() && !pVisual->locatorList.IsEmpty() )
    {
      vector<NDb::Locator> const &locators = pVisual->locatorList->locators;
      for (int k = 0; k < locators.size(); ++k)
      {
        lf( locators[k], attached[0] );
      }
    }
		return attached;
  }

	CObj<SceneComponent> pSC = pVisual->Create(*this, 0, NULLPLACEMENT);
	if (pSC)
	{
		pSC->Init();
		
		vector<CObj<SceneComponent>> attached = ParseAttachedSceneComponent( pVisual, isEditor );
		for ( int i = 0; i < attached.size(); i++ )
		{
			pSC->Attach( attached[i] );
		}
		result.push_back( pSC );

    if ( !pVisual->locatorList.IsEmpty() )
    {
      vector<NDb::Locator> const &locators = pVisual->locatorList->locators;
      for (int k = 0; k < locators.size(); ++k)
      {
        lf( locators[k], pSC );
      }
    }
	}

	return result;
}








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OBSOLETE EFFECT CODE?	////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<StaticSceneComponent> CreateStatic( const NDb::Effect* pVisual, int effIdx, const Placement& transform )
{
	return CObj<StaticSceneComponent>(0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<SoundSceneComponent> CreateSound( const NDb::Effect* pVisual, int effIdx, const Placement& transform )
{
	return CObj<SoundSceneComponent>(0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
// obsolete [10/19/2009 smirnov]
CObj<ParticleSceneComponent> CreateParticle( const NDb::Effect* pVisual, int effIdx, const Placement& transform )
{
	const NDb::ParticleInstance& particle = pVisual->effects[effIdx].particle;

	if ( particle.particle )
	{
		Placement offset;
		offset.FromMatrix( particle.trasform );
		offset += transform;

		CObj<ParticleSceneComponent> sc = new ParticleSceneComponent( &particle, offset );
		//sc->SetTimeParams( particle.speed, particle.offset, particle.cycleLength, particle.cycleCount, particle.duration, sc->GetPureAnimationTime() );

		sc->SetLocatorName( pVisual->effects[effIdx].jointName );

		return sc;
	}

	return CObj<ParticleSceneComponent>(0);
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<AnimatedSceneComponent> CreateAnimated( const NDb::Effect* pVisual, int effIdx, const Placement& transform )
{
	const NDb::ModelInstance& model = pVisual->effects[effIdx].model;

	if ( model.model )
	{
		Placement offset;
		offset.FromMatrix( model.trasform );
		offset += transform;

		CObj<AnimatedSceneComponent> sc = new AnimatedSceneComponent( model.model, offset );
		//sc->SetTimeParams( model.speed, model.offset, model.cycleLength, model.cycleCount, model.duration, sc->GetPureAnimationTime() );
		sc->SetLocatorName( pVisual->effects[effIdx].jointName );

		return sc;
	}

	return CObj<AnimatedSceneComponent>(0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> ParseEffect( const NDb::Effect* pVisual, const Placement& offset )
{
	vector<CObj<SceneComponent>> rootComponents;

	if ( pVisual && pVisual->effects.size() )
	{

		// 		rootComponents.push_back( new ParticleSceneComponent( 0, pVisual, IDENTITY_MATRIX, 0, 0, "" ) );

		CObj<SceneComponent> toattach;

		for ( int effIdx = 0; effIdx < pVisual->effects.size(); effIdx++ )
		{
			NI_ALWAYS_ASSERT("Code supposed to be OBSOLETE is called!");
			CObj<SceneComponent> toadd = CreateStatic( pVisual, effIdx, offset );
			if ( toadd )
			{
				rootComponents.push_back( toadd );
				toattach = toadd;
			}
			toadd = CreateAnimated( pVisual, effIdx, offset );
			if ( toadd )
			{
				rootComponents.push_back( toadd );
				toattach = toadd;
			}
// 			toadd = CreateParticle( pVisual, effIdx, offset );
// 			if ( toadd )
// 			{
// 				rootComponents.push_back( toadd );
// 				toattach = toadd;
// 			}
			toadd = CreateSound( pVisual, effIdx, offset );
			if ( toadd )
			{
				rootComponents.push_back( toadd );
				toattach = toadd;
			}
		}

		const NDb::ChildEffect* child = pVisual->tranformedchild;
		CObj<SceneComponent> toattach_child;

		while ( toattach && child && child->childeffect )
		{
			toattach_child = 0;

			Placement transform;
			transform.FromMatrix( child->transform );

			vector<CObj<SceneComponent>> comps = ParseEffect(child->childeffect, transform);
			for ( int i = 0; i < comps.size(); i++ )
			{
				if ( comps[i] )
				{
					toattach->Attach( comps[i] );
					toattach_child = comps[i];
				}
			}

			toattach = toattach_child;
			child = child->tranformedchild;
		}
	}

	return rootComponents;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> ParseAnimated( const NDb::Skeleton* pVisual )
{
	vector<CObj<SceneComponent>> rootComponents;

	if ( pVisual )
	{
		rootComponents.push_back( new AnimatedSceneComponent( pVisual, NULLPLACEMENT ) );
	}

	return rootComponents;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CObj<SceneComponent>> ParseStaticMesh( const NDb::StaticMesh* pVisual )
{
	vector<CObj<SceneComponent>> rootComponents;

	if ( pVisual )
	{
		rootComponents.push_back( new StaticSceneComponent( pVisual, NULLPLACEMENT ) );
	}

	return rootComponents;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CObj<SceneComponent> CreateAnimatedSceneComponent(const NDb::DBAnimatedSceneComponent &dbObj, HierarchyCreator &creator, 
                                                          const NDb::AttachedSceneComponent* pAttached, const Placement& transform)
{
  if (dbObj.additionalGraph.IsEmpty())
    return new NScene::AnimatedSceneComponent( &dbObj, pAttached, transform, creator.GetNodeName() );
  else
   return new NScene::AnimatedSplitSceneComponent( &dbObj, pAttached, transform, creator.GetNodeName() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EstimateSceneObjectHullAABB(SceneObject &so, Render::AABB &aabb)
{
	struct Trav : public FullTraverser, public NonCopyable
	{
		Render::AABB &aabb;

		Trav(Render::AABB &aabb_) : aabb(aabb_) {}
		void operator()(NScene::SceneComponent *pSC) 
		{ 
			if ( dynamic_cast<NScene::StaticSceneComponent*>(pSC) || 
				dynamic_cast<NScene::AnimatedSceneComponent*>(pSC) || 
				dynamic_cast<NScene::AnimatedSplitSceneComponent*>(pSC) )
      {
        Render::AABB transformedAABB;
        Matrix43 transform;
        pSC->GetOriginalPlacement().GetMatrix( &transform );
        transformedAABB.Transform( transform, pSC->GetLocalAABB() );
				aabb.Grow(transformedAABB); 
      }
		}
	} trav(aabb);

	aabb.Init2Empty();
	so.ForAllRoots(trav);
}

CollisionHull* MakeCollisionHullForObject( SceneObject &so, const NDb::CollisionGeometry* pCollGeo )
{
	CollisionMap* pCollMap = so.GetScene()->GetCollisionMap();
	if (!pCollMap)
		return 0;

	NScene::CollisionGeometry* pCollisionGeometry = 0;
  int pieceId = 0;

	if ( !pCollGeo )
	{
    Render::AABB aabb;
    EstimateSceneObjectHullAABB(so, aabb);

	  CVec3 pyramidPos = aabb.center;
	  pyramidPos.z -= aabb.halfSize.z;

	  // Create collision hull
	  vector<CVec3> pnts;
	  vector<CollisionGeometry::Triangle> tris;
    CVec3 sizeBox = 2.0f * aabb.halfSize;

    if ( fabs( sizeBox.x, sizeBox.y ) < collisionInflateMaxSize )
    {
      sizeBox.x *= collisionInflateCoef;
      sizeBox.y *= collisionInflateCoef;
      pieceId = 1;
    }

	  pCollisionGeometry = NScene::CreatePyramid( pyramidPos, sizeBox, 0.9f, true, pnts, tris );
  }
	else
	{
    pCollisionGeometry = CollisionGeometry::GetCollisionManager().Create(pCollGeo);
	}

  CollisionHull* hull = 0;
  Matrix43 position;
  so.GetPosition().GetMatrix( &position );

  if( IsValid(pCollisionGeometry) )
	  hull = pCollMap->CreateHull( &so, pieceId, pCollisionGeometry, position, 0 );

  return hull;
}

CollisionHull* MakeSmallCollisionHullForObject( SceneObject &so, const NDb::CollisionGeometry* pCollGeo )
{
  CollisionMap* pCollMap = so.GetScene()->GetCollisionMap();
  if (!pCollMap)
    return 0;

  NScene::CollisionGeometry* pCollisionGeometry = 0;
  int pieceId = 0;

  if ( !pCollGeo )
  {
    Render::AABB aabb;
    EstimateSceneObjectHullAABB(so, aabb);

    CVec3 pyramidPos = aabb.center;
    pyramidPos.z -= aabb.halfSize.z;

    // Create collision hull
    vector<CVec3> pnts;
    vector<CollisionGeometry::Triangle> tris;
    CVec3 sizeBox = 2.0f * aabb.halfSize;

    pCollisionGeometry = NScene::CreatePyramid( pyramidPos, sizeBox, 0.9f, true, pnts, tris );
  }
  else
  {
    return 0;
  }

  CollisionHull* hull = 0;
  Matrix43 position;
  so.GetPosition().GetMatrix( &position );

  if( IsValid(pCollisionGeometry) )
    hull = pCollMap->CreateHull( &so, pieceId, pCollisionGeometry, position, 0 );

  return hull;
}

}


