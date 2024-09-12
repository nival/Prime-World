#include "stdafx.h"

#include "AnimatedSceneComponent.h"
#include "Scene.hpp"
#include "SceneUtils.h"
#include "../Render/SkeletalMesh.h"

namespace NScene
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Traverser>
struct ForAllSceneObjects : public IObjectFunctor, private NonCopyable 
{
  Traverser& traverser;

  ForAllSceneObjects( Traverser& _traverser ) : traverser(_traverser) {}

  void operator()(RenderableSceneObj &obj)
  {
    SceneObject* sceneObject = dynamic_cast<SceneObject*>( &obj ); 

    if ( sceneObject )
      sceneObject->Traverse( traverser );
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FXMaterialFinder : public Render::IMaterialProcessor
{
  bool found;
  FXMaterialFinder() : found(false) {}

  virtual void operator()(Render::BaseMaterial &material)
  {
    NDb::Ptr<NDb::Material> dbMaterial = material.GetDBMaterial();  

    switch ( dbMaterial->GetObjectTypeID() )
    {
    case NDb::ParticleFXMaterial::typeId :      
    case NDb::DecalMaterial::typeId :      
    case NDb::BasicFXMaterial::typeId :  
      found = true;
      break;
    }
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FXSwitcher : public FullTraverser
{
  bool enable;

  FXSwitcher( bool _enable ) : enable(_enable) {}

  void operator()( NScene::SceneComponent* comp ) const 
  {
    NScene::AnimatedSceneComponent* animComp = dynamic_cast<NScene::AnimatedSceneComponent*>( comp );

    if ( animComp )
    {
      nstl::vector<int> skinsID = animComp->GetActiveSkins();

      nstl::vector<int>::iterator it = skinsID.begin();
      nstl::vector<int>::iterator last = skinsID.end();

      for ( ; it != last; ++it )
      {
        FXMaterialFinder materialFinder;

        Render::BaseMaterial* material = animComp->GetGraphApplicator()->GetModel()->GetMaterial( *it );

        if ( material )
        {
          materialFinder( *material );

          if ( materialFinder.found )
            animComp->EnableSkin( *it, enable );
        }
      }
    }
    else
    {
      FXMaterialFinder materialFinder;

      comp->ForAllMaterials( materialFinder );

      if ( materialFinder.found )
        comp->DisableStrong( !enable );
    }
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableEffectsInScene( IScene* _scene, bool _enable )
{
  NI_ASSERT( _scene, "IScene is null" );
    
  IRenderableScene* renderableScene = _scene->GetRenderScene();  

  FXSwitcher switcher( _enable );
  ForAllSceneObjects<FXSwitcher> forAllSceneObjects( switcher );

  renderableScene->ForAllObjects( forAllSceneObjects );
}

void EnableEffectsInObject( SceneObject* so, bool _enable )
{
  FXSwitcher switcher( _enable );
  so->Traverse( switcher );
}

} //namespace NScene
