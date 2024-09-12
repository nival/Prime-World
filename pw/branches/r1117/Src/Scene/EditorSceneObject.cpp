#include "stdafx.h"

#include "../Render/debugrenderer.h"
#include "../Render/StaticMesh.h"

#include "EditorSceneObject.h"
#include "AnimatedSceneComponent.h"
#include "ParticleSceneComponent.h"
#include "StaticSceneComponent.h"
#include "TraceSceneComponent.h"
#include "LightningSceneComponent.h"
#include "RenderableScene.h"
#include "GeometryBuilders.h"
#include "SceneObjectCreation.h"
#include "SceneObjectUtils.h"
#include "VertexColorManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

struct FindAnimatedComponentByDBID : public GenericTraverser, private NonCopyable
{
	AnimatedSceneComponent* result;
	const NDb::DBID& dbid;

	FindAnimatedComponentByDBID( const NDb::DBID& _dbid ) : dbid( _dbid ), result( 0 ) {}

	void operator()( SceneComponent *sc )
	{
		if ( sc->GetDBID() == dbid )
		{
			result = dynamic_cast<AnimatedSceneComponent*>( sc );
		}
	}
};

struct FindFirstAnimatedOrStaticComponent : public GenericTraverser, private NonCopyable
{
  AnimatedSceneComponent* result_ac;
  StaticSceneComponent* result_sc;

  FindFirstAnimatedOrStaticComponent() : result_ac( 0 ), result_sc( 0 ) {}

  void operator()( SceneComponent *sc )
  {
    if ( !result_ac && !result_sc )
    {
      result_ac = dynamic_cast<AnimatedSceneComponent*>( sc );
      result_sc = dynamic_cast<StaticSceneComponent*>( sc );
    }
  }
};

struct SetParentTransformUsage : public GenericTraverser, private NonCopyable
{
  unsigned int flags;

  SetParentTransformUsage( unsigned int _flags ) : flags( _flags ) {}

  void operator()( SceneComponent *sc )
  {
    sc->SetParentTransformUsageFlags( flags );
  }
};

static bool g_renderObjectLocators = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject::EditorSceneObject( IScene *pScene, const NDb::DbResource* _pHoldResource, const vector<CObj<SceneComponent>>& components, const Placement& placement, const NDb::DBSceneObject* db ) 
:	SceneObject( pScene, db )
, highlightType( HT_OFF )
, pHoldResource( _pHoldResource )
, selectedLocator(-1)
, isPlaceOnTerrain( true )
, layer( 1 )
{
	for( vector<CObj<SceneComponent>>::const_iterator it = components.begin(); it != components.end(); ++it )
		Add( *it );

  if(_pHoldResource && pScene)
    if( MeshVertexColorsManager* pVCM = pScene->GetMeshVertexColorsManager() )
    {
        LoadColorsTraverser traverser(*pVCM);
        pVCM->SceneObjectVCBegin( &_pHoldResource->GetDBID() );
        Traverse(traverser);
        pVCM->SceneObjectVCEnd( &_pHoldResource->GetDBID() );
    }

  Placement newPlacement = placement; 
  pScene->GetHeightsController().GetHeight( newPlacement.pos.x, newPlacement.pos.y, 0, &newPlacement.pos.z, NULL );
  newPlacement.pos.z += placement.pos.z;
  SetPlacement( newPlacement );

	UpdateForced();
	RegisterCollisionGeometry( 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject::EditorSceneObject( IScene *pScene, const NDb::DbResource* _pHoldResource, CObj<SceneComponent> pComponent, const Placement& placement, const NDb::DBSceneObject* db ) 
:	SceneObject( pScene, db )
, highlightType( HT_OFF )
, pHoldResource( _pHoldResource )
, selectedLocator(-1)
, isPlaceOnTerrain( true )
, layer( 1 )
{
	Add( pComponent );

  if(_pHoldResource && pScene)
    if( MeshVertexColorsManager* pVCM = pScene->GetMeshVertexColorsManager() )
    {
      LoadColorsTraverser traverser(*pVCM);
      pVCM->SceneObjectVCBegin( &_pHoldResource->GetDBID() );
      Traverse(traverser);
      pVCM->SceneObjectVCEnd( &_pHoldResource->GetDBID() );
    }

  Placement newPlacement = placement; 
  pScene->GetHeightsController().GetHeight( newPlacement.pos.x, newPlacement.pos.y, 0, &newPlacement.pos.z, NULL );
  newPlacement.pos.z += placement.pos.z;
  SetPlacement( newPlacement );

	UpdateForced();
	RegisterCollisionGeometry( 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject::~EditorSceneObject()
{
	UnregisterCollisionGeometry();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::Highlight( HighlightType _highlight )
{
	Render::HDRColor mulColor( 1.f, 1.0f, 1.0f, 1.0f );
	struct Coloriser : public NScene::TraverserByGroupFlags
	{ 
		mutable NScene::MaterialColorAndOpacityChanger mproc;

		Coloriser( Render::HDRColor const& mulColor ) 
			: NScene::TraverserByGroupFlags( 0, true ), mproc( mulColor, Render::HDRColor(0.0f,0.0f,0.f,0.f) ) 
		{
		}

		bool NeedToProcess(const SceneComponent* comp)const
		{
			return true;
		}

		void operator()( NScene::SceneComponent* comp ) const 
		{
			comp->ForAllMaterials(mproc);
		}

	} coloriser( mulColor );
	Traverse(coloriser);

	highlightType = _highlight;

	if ( highlightType == HT_COLOR )
	{
		Render::HDRColor mulColor( 0.308f, 1.0f, 0.078f, 1.0f );
		struct Coloriser : public NScene::TraverserByGroupFlags
		{ 
			mutable NScene::MaterialColorAndOpacityChanger mproc;

			Coloriser( Render::HDRColor const& mulColor ) 
				: NScene::TraverserByGroupFlags( 0, true ), mproc( mulColor, Render::HDRColor(0.0f,0.0f,0.f,0.f) ) 
			{
			}

			bool NeedToProcess(const SceneComponent* comp)const
			{
				return true;
			}

			void operator()( NScene::SceneComponent* comp ) const 
			{
				comp->ForAllMaterials(mproc);
			}

		} coloriser( mulColor );
		Traverse(coloriser);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::ShowSkin( const string& skinName, bool show )
{
 	if ( !GetRootComponent() )
	{
		return;
	}

	AnimatedSceneComponent* sc = dynamic_cast<AnimatedSceneComponent*>( GetRootComponent() );

	if ( !sc )
	{
		return;
	}

	sc->ShowSkin( skinName, show );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::ShowSkin( int skinName, bool show )
{
	if ( !GetRootComponent() )
	{
		return;
	}

	AnimatedSceneComponent* sc = dynamic_cast<AnimatedSceneComponent*>( GetRootComponent() );

	if ( !sc )
	{
		return;
	}

	sc->ShowSkin( skinName, show );
}

void EditorSceneObject::ShowSkin( const NDb::DBID& dbid, int skinName, bool show )
{
	FindAnimatedComponentByDBID f( dbid );

	Traverse(f);

	if ( f.result )
	{
		f.result->ShowSkin( skinName, show );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::TurnOffSkins()
{
	if ( !GetRootComponent() )
	{
		return;
	}

	AnimatedSceneComponent* sc = dynamic_cast<AnimatedSceneComponent*>( GetRootComponent() );

	if ( !sc )
	{
		return;
	}

	sc->TurnOffSkins();
}

void EditorSceneObject::TurnOffSkins( const NDb::DBID& dbid )
{
	FindAnimatedComponentByDBID f( dbid );

	Traverse(f);

	if ( f.result )
	{
		f.result->TurnOffSkins();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::StartAnimation( int animationIndex )
{
	if ( !GetRootComponent() )
	{
		return;
	}

	AnimatedSceneComponent* sc = dynamic_cast<AnimatedSceneComponent*>( GetRootComponent() );

	if ( !sc )
	{
		return;
	}

	sc->StartAnimation( animationIndex ); // kind of hack to save ability of using "Show animations" dialog
}

void EditorSceneObject::StartAnimation( const NDb::DBID& dbid, int animationIndex )
{
	FindAnimatedComponentByDBID f( dbid );

	Traverse(f);

	if ( f.result )
	{
		f.result->StartAnimation( animationIndex ); // kind of hack to save ability of using "Show animations" dialog
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
::DiAnimGraph* EditorSceneObject::GetAnimationGraph()
{
  if ( !GetRootComponent() )
  {
    return NULL;
  }

  AnimatedSceneComponent* sc = dynamic_cast<AnimatedSceneComponent*>( GetRootComponent() );

  if ( !sc )
  {
    return NULL;
  }

  return sc->GetMainAnimGraph();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnimGraph const* EditorSceneObject::GetAnimationGraph() const
{
  if ( !GetRootComponent() )
  {
    return NULL;
  }

  AnimatedSceneComponent const* sc = dynamic_cast<AnimatedSceneComponent const*>(GetRootComponent());

  if ( !sc )
  {
    return NULL;
  }

  return sc->GetMainAnimGraph();
}

::DiAnimGraph* EditorSceneObject::GetAnimationGraph( const NDb::DBID& dbid )
{
	FindAnimatedComponentByDBID f( dbid );

	Traverse(f);

	if ( f.result )
	{
		return f.result->GetMainAnimGraph();
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars * EditorSceneObject::GetExternalParameters()
{
  if ( !GetRootComponent() )
  {
    return NULL;
  }

  AnimatedSceneComponent * sc = dynamic_cast<AnimatedSceneComponent *>(GetRootComponent());

  if ( !sc )
  {
    return NULL;
  }

  return sc->GetExtPars();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars const* EditorSceneObject::GetExternalParameters() const
{
  if ( !GetRootComponent() )
  {
    return NULL;
  }

  AnimatedSceneComponent const* sc = dynamic_cast<AnimatedSceneComponent const*>(GetRootComponent());

  if ( !sc )
  {
    return NULL;
  }

  return sc->GetExtPars();
}

DiAnGrExtPars * EditorSceneObject::GetExternalParameters( const NDb::DBID& dbid )
{
	FindAnimatedComponentByDBID f( dbid );

	Traverse(f);

	if ( f.result )
	{
		return f.result->GetExtPars();
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::AnimationVector const * EditorSceneObject::GetAnimations() const
{
  if ( !GetRootComponent() )
  {
    return NULL;
  }

  AnimatedSceneComponent const * sc = dynamic_cast<AnimatedSceneComponent const*>( GetRootComponent() );

  if ( !sc )
  {
    return NULL;
  }

  return &sc->GetGraphBlender()->GetAnimationVector();
}

nstl::vector<int> EditorSceneObject::GetActiveSkins( const NDb::DBID& dbid )
{
  FindAnimatedComponentByDBID f( dbid );

  Traverse(f);

  if ( f.result )
  {
    return f.result->GetActiveSkins();
  }

  return nstl::vector<int>();
}

void EditorSceneObject::SetPositionWithPlacingOnTerrain( const Placement& _pos )
{
	originalPlacement = _pos;
	Placement pos = _pos;
  if ( isPlaceOnTerrain )
	  PlaceOnTerrain(pScene->GetHeightsController(), pos.pos, layer );
	SetPlacement( pos );
}

void EditorSceneObject::ReplaceObjectOnTerrain()
{
  CVec3 pos = originalPlacement.pos;
  if ( isPlaceOnTerrain )
    PlaceOnTerrain(pScene->GetHeightsController(), pos, layer );
  SetPosition(pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::Update( float timeDiff, bool isForcedUpdate )
{
	SceneObject::Update( timeDiff, isForcedUpdate );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorSceneObject::Render( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants, int groupFlagsFilter )
{
  struct Func
  {
    int idx;
    Locator const *found;

    Func(int idx) : idx(idx), found(NULL) {}
    void operator() (Locator const &l)
    {
      if (idx == 0)
      {
        found = &l;
      }
      --idx;
    }
  };

  Render::DebugRender debugRender;

  SceneObject::Render( queue, sceneConstants, groupFlagsFilter );

	if ( highlightType == HT_COLLISION )
	{
    // Render collision hull
		GetCollision()->DebugRender( &debugRender );
		// Draw AABB's for all scene components
		//DebugDrawAABBs( &debugRender, Render::Color(0xFF, 0x00, 0x00));
	}

	if (g_renderObjectLocators)
		DebugDrawLocators( &debugRender );

  if ( selectedLocator != -1 )
  {
    Func f(selectedLocator);
    ForAllLocators(f);
    if (f.found)
    {
      f.found->DebugRender( &debugRender );
    }
  }
}

void EditorSceneObject::GetEditorSimpleBound(SBound &bound) const
{
  FindFirstAnimatedOrStaticComponent f;

  Traverse(f);

  if ( f.result_ac )
  {
    bound.BoxExInit(f.result_ac->GetLocalAABB().center, f.result_ac->GetLocalAABB().halfSize);
    return;
  }
  if ( f.result_sc )
  {
    bound.BoxExInit(f.result_sc->GetLocalAABB().center, f.result_sc->GetLocalAABB().halfSize);
    return;
  }

  bound.BoxExInit(worldAABB.center, worldAABB.halfSize);
  bound.s.ptCenter -= GetPosition().pos;
}

void EditorSceneObject::SetParentTransformUsageFlags( unsigned int _flags )
{
  if ( GetRootComponent() )
  {
    GetRootComponent()->SetParentTransformUsageFlags( _flags );

    NScene::SceneComponent* brother = GetRootComponent()->GetBrother();
    while ( brother && brother != GetRootComponent() )
    {
      brother->SetParentTransformUsageFlags( _flags );
      brother = brother->GetBrother();
    }
  }


  //SetParentTransformUsage f( _flags );
  //Traverse(f);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string const *> EditorSceneObject::GetLocatorsNames()
{
  struct Func
  {
  public:
    vector<string const *> names;

    void operator() (NScene::Locator const &l)
    {
      names.push_back( &l.locator.name );
    }
  } f;
  ForAllLocators(f);
  return f.names;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::Effect* pVisual, const Placement& placement )
{
	EditorSceneObject* pResult = new EditorSceneObject( pScene, pVisual, ParseEffect( pVisual, NULLPLACEMENT ), placement, 0 );
  if ( pResult->GetRootComponent() )
  {
  	pScene->AddSceneObject( pResult );
  }
	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::StaticMesh* pVisual, const Placement& placement )
{
	EditorSceneObject* pResult = new EditorSceneObject( pScene, pVisual, ParseStaticMesh( pVisual ), placement, 0 );
  if ( pResult->GetRootComponent() )
  {
  	pScene->AddSceneObject( pResult );
  }
	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::Skeleton* pVisual, const Placement& placement )
{
	EditorSceneObject* pResult = new EditorSceneObject( pScene, pVisual, ParseAnimated( pVisual ), placement, 0 );
  if ( pResult->GetRootComponent() )
  {
  	pScene->AddSceneObject( pResult );
  }
	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollectLocatorsFunc : public IParseLocatorFunc
{
public:
  void operator() (NDb::Locator const &locator, SceneComponent *pSC)
  {
    NScene::Locator l;
    l.locator = locator;
    l.pSC = pSC;
    
    locators.push_back(l);
  }

  vector<NScene::Locator> &GetLocators() { return locators; }

protected:
  vector<NScene::Locator> locators;
};

EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::DBSceneObject* pVisual, const Placement& placement, bool addToScene, bool isStaticAndAnimatedOnly )
{
  CollectLocatorsFunc lf;
  EditorSceneObject* pResult = new EditorSceneObject( pScene, pVisual, ParseSceneObject( pVisual, lf, BADNODENAME, true, isStaticAndAnimatedOnly ), placement, pVisual );
  
  for (int i = 0; i < lf.GetLocators().size(); ++i)
  {
    pResult->AddLocator(lf.GetLocators()[i]);
  }

	if ( addToScene && pResult->GetRootComponent() )
	{
		pScene->AddSceneObject( pResult );
	}

	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::DBSceneComponent* pVisual, const Placement& placement )
{
  CollectLocatorsFunc lf;
  EditorSceneObject* pResult = new EditorSceneObject( pScene, pVisual, ParseSceneComponent( pVisual, lf, true ), placement, 0 );

  for (int i = 0; i < lf.GetLocators().size(); ++i)
  {
    pResult->AddLocator(lf.GetLocators()[i]);
  }

  if ( pResult->GetRootComponent() )
  {
    pScene->AddSceneObject( pResult );
  }
  return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ToggleShowLocators()
{
	g_renderObjectLocators = !g_renderObjectLocators;
}
}
