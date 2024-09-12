#pragma once

#include "PF_Core/BasicEffect.h"
#include "PF_Core/EffectsPool.h"

namespace NGameX
{

struct ResourcesPreloader : public NDb::IResourcesProcessor
{
  CObj<NScene::IScene> scene;
	const nstl::string& nodeName;
  hash_set<NDb::DBID> excludes;
  nstl::string skinId;

  ResourcesPreloader( NScene::IScene * _scene, const NDb::DbResource * _excludeResource, const nstl::string& nodeName, const nstl::string& _skinId ) 
		: scene( _scene ), nodeName(nodeName), skinId( _skinId )
  {
    if ( _excludeResource )
    {
      excludes.insert( _excludeResource->GetDBID() );
    }
  }

  ResourcesPreloader( NScene::IScene * _scene, const nstl::list<const NDb::DbResource*>& excludedResources , const nstl::string& nodeName, const nstl::string& _skinId ) 
    : scene( _scene ), nodeName(nodeName), skinId( _skinId )
  {
    if ( excludedResources.size() )
    {
      nstl::list<const NDb::DbResource*>::const_iterator it = excludedResources.begin();
      for ( ; it != excludedResources.end(); ++it )
      {
        NI_VERIFY((*it), "Empty resource ptr added to exlude list on preload", continue);
        excludes.insert( (*it)->GetDBID() );
      }
    }
  }

	ResourcesPreloader& operator=(const ResourcesPreloader&)
	{
		return *this;
	}

  virtual bool Call( const NDb::DBID&dbid, const NDb::DbResource* pResource )
  {
    if ( excludes.find( pResource->GetDBID() ) != excludes.end() )
      return false;

    excludes.insert( pResource->GetDBID() );

    const NDb::EffectBase* effect = dynamic_cast<const NDb::EffectBase*>( pResource );

    if ( effect )
    {
      if ( effect->GetObjectTypeID() == NDb::BasicEffectStandalone::typeId || 
          effect->GetObjectTypeID() == NDb::BasicEffectAttached::typeId || 
          effect->GetObjectTypeID() == NDb::LightningEffect::typeId ||
          effect->GetObjectTypeID() == NDb::ControlledStatusEffect::typeId )
      {
        NDb::Ptr<NDb::EffectBase> toLoad( effect );
        if ( !skinId.empty() )
        {
          toLoad.ChangeState( skinId );
        }

        CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->Retrieve( toLoad );
        pEffect->DieImmediate();

        return true; // If control status effect - need to go deeper
      }
    }

    const NDb::DBSceneObject* sceneObj = dynamic_cast<const NDb::DBSceneObject *>( pResource );

    if ( sceneObj && scene )
    {
      NDb::Ptr<NDb::DBSceneObject> toLoad( sceneObj );
      if ( !skinId.empty() )
      {
        toLoad.ChangeState( skinId );
      }

      NScene::SceneObjectsPool::Get()->Reserve( scene, toLoad, 1, nodeName );
      return true;
    }

    const NDb::Material* dbMaterial = dynamic_cast<const NDb::Material *>( pResource );

    if ( dbMaterial )
    {
      NDb::Ptr<NDb::Material> toLoad( dbMaterial );
      if ( !skinId.empty() )
      {
        toLoad.ChangeState( skinId );
      }

      Render::Material* material = Render::CreateRenderMaterial( toLoad );
      delete material;
      return false;
    }

    const NDb::Texture* dbTexture = dynamic_cast<const NDb::Texture *>( pResource );

    if ( dbTexture )
    {
      NDb::Ptr<NDb::Texture> toLoad( dbTexture );
      if ( !skinId.empty() )
      {
        toLoad.ChangeState( skinId );
      }

      CObj<Render::Texture> texture = toLoad->Load();
      texture = 0;
      return false;
    }

    const NDb::CollisionGeometry* dbColGeom = dynamic_cast<const NDb::CollisionGeometry *>( pResource );

    if ( dbColGeom )
    {
      NDb::Ptr<NDb::CollisionGeometry> toLoad( dbColGeom );
      if ( !skinId.empty() )
      {
        toLoad.ChangeState( skinId );
      }

      CObj<NScene::CollisionGeometry> collisionGeometry = NScene::CollisionGeometry::GetCollisionManager().Create( toLoad );
      collisionGeometry = 0;
      return false;
    }

    return true;
  }

  virtual bool LoadResources() { return true; }
};

}