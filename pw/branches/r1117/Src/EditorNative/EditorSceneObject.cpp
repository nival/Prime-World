#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "../Scene/EditorSceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/WaterSceneComponent.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

struct FindWaterComponent : public NScene::GenericTraverser, private NonCopyable
{
  NScene::WaterSceneComponent* result;

  FindWaterComponent() : result( 0 ) {}

  void operator()( NScene::SceneComponent *sc )
  {
    if ( !result )
    {
      result = dynamic_cast<NScene::WaterSceneComponent*>( sc );
    }
  }
};

static void AttachSkin( String^ skinName, NDb::Ptr<NDb::Skeleton> pSkel, NScene::EditorSceneObject *pObj )
{
	string skinName_s = ToMBCS( skinName );

	pObj->ShowSkin( skinName_s, true );
}

static void AttachSkin( int skinName, NScene::EditorSceneObject *pObj, float renderTime )
{
	pObj->ShowSkin( skinName, true );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject::EditorSceneObject( DBID^ _dbId )
:	dbId ( _dbId )
,	ppObject ( nullptr )
,	animationIndex( 0 )
,	activeDBID( libdb::DB::DBID::Empty )
, initialPlacement(new Placement(NULLPLACEMENT))
, effect(0)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::IntPtr EditorSceneObject::GetAnimGraph( libdb::DB::DBID^ _dbId )
{
	if (_dbId->IsEmpty)
	{
    NDb::Ptr<NDb::DBAnimatedSceneComponent> pSkel = GetObject<NDb::DBAnimatedSceneComponent>( DbId );
    if(pSkel.IsEmpty())
    {
      return System::IntPtr(nullptr);
    }

    System::IntPtr ptr = System::IntPtr( Object->GetAnimationGraph() );
    return ptr;
	}

  NDb::Ptr<NDb::DBAnimatedSceneComponent> pSkel = GetObject<NDb::DBAnimatedSceneComponent>( _dbId );
  if(pSkel.IsEmpty())
  {
    return System::IntPtr(nullptr);
  }

	string filename = ToMBCS( _dbId->FileName );
	string id = ToMBCS( _dbId->Id );
	NDb::DBID dbid(filename, id);
  System::IntPtr ptr = System::IntPtr( Object->GetAnimationGraph( dbid ) );

	return ptr;
}

System::IntPtr EditorSceneObject::GetExtPars( libdb::DB::DBID^ _dbId )
{
  if (_dbId->IsEmpty)
  {
    NDb::Ptr<NDb::DBAnimatedSceneComponent> pSkel = GetObject<NDb::DBAnimatedSceneComponent>( DbId );
    if(pSkel.IsEmpty())
    {
      return System::IntPtr(nullptr);
    }

    return System::IntPtr(Object->GetExternalParameters());
  }

  NDb::Ptr<NDb::DBAnimatedSceneComponent> pSkel = GetObject<NDb::DBAnimatedSceneComponent>( _dbId );
  if(pSkel.IsEmpty())
  {
    return System::IntPtr(nullptr);
  }

	string filename = ToMBCS( _dbId->FileName );
	string id = ToMBCS( _dbId->Id );
	NDb::DBID dbid(filename, id);
	return System::IntPtr( Object->GetExternalParameters( dbid ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

System::Collections::Generic::IList<DBTypes::Animation^>^ EditorSceneObject::GetAnimationList( libdb::DB::DBID^ _dbId )
{
	NDb::Ptr<NDb::DBAnimatedSceneComponent> pSkel = GetObject<NDb::DBAnimatedSceneComponent>( DbId );
	if(pSkel.IsEmpty())
	{
		return nullptr;
	}

	return nullptr;
}

NScene::EditorSceneObject* EditorSceneObject::CreateNativeObject( NScene::IScene& scene )
{
  return CreateNativeObject( scene, false );
}

NScene::EditorSceneObject* EditorSceneObject::CreateNativeObject( NScene::IScene& scene, bool isCollObject )
{
	NScene::EditorSceneObject* pSO = 0;

  if ( !isCollObject )
    NScene::CollisionGeometry::GetCollisionManager().Clear();

  if ( DbId->IsEmpty )
    return nullptr;

	NDb::Ptr<NDb::StaticMesh> pStaticMesh = GetObject<NDb::StaticMesh>( DbId );
  NDb::Ptr<NDb::DBSceneObject> pDBSO = GetObject<NDb::DBSceneObject>( DbId );
  NDb::Ptr<NDb::DBSceneComponent> pDBSC = GetObject<NDb::DBSceneComponent>( DbId );
	if ( !pStaticMesh.IsEmpty() )
    pSO = NScene::CreateEditorSceneObject( &scene, pStaticMesh, *initialPlacement );
  if ( !pDBSO.IsEmpty() )
  {
    pSO = NScene::CreateEditorSceneObject( &scene, pDBSO, *initialPlacement, true, false );
    if ( !pDBSO->collisionGeometry.IsEmpty() )
    {
      const NDb::Ptr<NDb::CollisionGeometry> dbGeom = GetObject<NDb::CollisionGeometry>(libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( pDBSO->collisionGeometry->GetDBID() ) ) ));
      if ( !dbGeom.IsEmpty() )
      {
        pSO->RegisterCollisionGeometry( dbGeom );
      }
    }
  }
  if ( !pDBSC.IsEmpty() )
    pSO = NScene::CreateEditorSceneObject( &scene, pDBSC, *initialPlacement );

  if ( !pSO )
    return nullptr;

	pSO->TurnOffSkins();

	for ( int i = 0; i < visibleSkins.Count; i++ )
	{
		AttachSkin( visibleSkins[i], pSO, 0.f );
	}

	if (activeDBID->IsEmpty)
	{
		/* Commented by EugBel (27-March-2009) to prevent simultaneous usage of AnimationGraph by panels "AnimationGraph" and "Animations"
       ///eugbel///AGvsAN
    pSO->StartAnimation( animationIndex );
    */
	}
	else
	{
		string filename = ToMBCS( activeDBID->FileName );
		string id = ToMBCS( activeDBID->Id );
		NDb::DBID dbid(filename, id);
		pSO->StartAnimation( dbid, animationIndex );
	}

	return pSO;
}

void EditorSceneObject::ShowSkin( int skinName, bool show, libdb::DB::DBID^ _dbId )
{
	activeDBID = _dbId;

  if ( !Object )
  {
    return;
  }

	if ( skinName < 0 )
	{
		return;
	}

	if ( show )
	{
		if ( !visibleSkins.Contains( skinName ) )
		{
			visibleSkins.Add( skinName );
		}
	}
	else
	{
		if ( visibleSkins.Contains( skinName ) )
		{
			visibleSkins.Remove( skinName );
		}
	}

	if (_dbId->IsEmpty)
	{
		Object->TurnOffSkins();

		for ( int i = 0; i < visibleSkins.Count; i++ )
		{
			Object->ShowSkin( visibleSkins[i], true );
		}
	}
	else
	{
    string filename = ToMBCS( _dbId->FileName );
    string id = ToMBCS( _dbId->Id );
    NDb::DBID dbid(filename, id);

    Object->TurnOffSkins(dbid);

		for ( int i = 0; i < visibleSkins.Count; i++ )
		{
			Object->ShowSkin( dbid, visibleSkins[i], true );
		}
	}
}

void EditorSceneObject::StartAnimation( int _animationIndex, libdb::DB::DBID^ _dbId )
{
  if ( !Object )
  {
    return;
  }

	animationIndex = _animationIndex;
	activeDBID = _dbId;

	if (_dbId->IsEmpty)
	{
		Object->StartAnimation( animationIndex );
	}
	else
	{
		string filename = ToMBCS( _dbId->FileName );
		string id = ToMBCS( _dbId->Id );
		NDb::DBID dbid(filename, id);
		Object->StartAnimation( dbid, animationIndex );
	}
}

void EditorSceneObject::Create( System::IntPtr _scene )
{
  NScene::IScene* scene = static_cast<NScene::IScene*>(_scene.ToPointer());
  if ( effect )
  {
    effect->AddToScene( scene );
		FillEditorSceneComponents( effect );
  }
  else
  {
	  NScene::EditorSceneObject* pObject = CreateNativeObject( *scene );
	  if ( pObject != nullptr )
	  {
      pObject->SetPositionWithPlacingOnTerrain(*initialPlacement);
		  ppObject = pObject;
			FillEditorSceneComponents( ppObject );
	  }
  }
}

System::Collections::Generic::List<int>^ EditorSceneObject::GetActiveSkins( libdb::DB::DBID^ _dbId )
{
  System::Collections::Generic::List<int>^ result = gcnew System::Collections::Generic::List<int>();
	if ( Object )
	{
		string filename = ToMBCS( _dbId->FileName );
		string id = ToMBCS( _dbId->Id );
		NDb::DBID dbid(filename, id);
		const nstl::vector<int> r = Object->GetActiveSkins(dbid);
		for ( int i = 0; i < r.size(); i++ )
		{
			result->Add( r[i] );
		}
	}

  return result;
}

static EditorSceneComponent^ FillEditorSceneComponent( NScene::SceneComponent* sc, EditorSceneObject^ so );

static EditorSceneComponent^ CreateEditorSceneComponent( NScene::SceneComponent* sc, EditorSceneObject^ so )
{
  EditorSceneComponent^ esc = gcnew EditorSceneComponent();
  esc->brothers = gcnew System::Collections::Generic::List<EditorSceneComponent^>();
  esc->child = nullptr;
  esc->sceneComponent = sc;
  esc->sceneObject = so;

  return esc;
}


static void FillBrother( EditorSceneComponent^ esc, System::Collections::Generic::List<EditorSceneComponent^>^ brothers, EditorSceneObject^ so )
{
  for ( int i = 0; i < brothers->Count; i++ )
  {
    if ( esc != brothers[i] )
    {
      esc->brothers->Add( brothers[i] );
    }
  }
  if ( esc->sceneComponent->GetChild() )
  {
    esc->child = FillEditorSceneComponent( esc->sceneComponent->GetChild(), so );
  }
}

static EditorSceneComponent^ FillEditorSceneComponent( NScene::SceneComponent* sc, EditorSceneObject^ so )
{
  EditorSceneComponent^ esc = CreateEditorSceneComponent( sc, so );
  esc->brothers->Add( esc );

  NScene::SceneComponent* it = sc->GetBrother();
  while ( it && it != sc )
  {
    esc->brothers->Add( CreateEditorSceneComponent( it, so ) );
    it = it->GetBrother();
  }

  for( int i = 0; i < esc->brothers->Count; i++  )
  {
    if ( esc != esc->brothers[i] )
    {
      FillBrother( esc->brothers[i], esc->brothers, so );
    }
  }
  esc->brothers->Remove(esc);

  if ( sc->GetChild() )
  {
    esc->child = FillEditorSceneComponent( sc->GetChild(), so );
  }

  return esc;
}

void EditorSceneObject::FillEditorSceneComponents( NScene::SceneObject* so )
{
  if ( so == nullptr )
  {
    rootEditorSceneComponent = nullptr;
    return;
  }

  if ( !so->GetRootComponent() )
  {
    rootEditorSceneComponent = nullptr;
    return;
  }
  
  if ( IsNeedFillSceneHierarchy() )
  {
    rootEditorSceneComponent = FillEditorSceneComponent( so->GetRootComponent(), this );
  }
  else
  {
    rootEditorSceneComponent = nullptr;
  }
}

void EditorSceneObject::SetInitialPlacement( DBTypes::Placement2^ _placement )
{
  convertPlacement(_placement, initialPlacement);
}

DBTypes::Placement2^ EditorSceneObject::GetInitialPlacement()
{
  DBTypes::Placement2^ result = gcnew DBTypes::Placement2();
  convertPlacement(initialPlacement, result);
  return result;
}

void EditorSceneObject::SetCurrentPlacement( DBTypes::Placement^ _placement )
{
  if ( Object )
  {
    Placement* curPlacement = new Placement();
    convertPlacement( _placement, curPlacement );
    Object->SetPositionWithPlacingOnTerrain( *curPlacement );
  }
}

DBTypes::Placement^ EditorSceneObject::GetCurrentPlacement()
{
  DBTypes::Placement^ result = gcnew DBTypes::Placement();
  if ( Object )
  {
    Placement curPlacement = Object->GetPosition();
    convertPlacement( &curPlacement, result );
  }
  return result;
}

void EditorSceneObject::Reinit()
{
  if ( effect )
  {
    effect->Reinit();
  }
  if ( Object )
  {
    Object->Reinit();
    Object->UpdateForced();
  }
}

void EditorSceneObject::ClearVisibleSkins()
{
  visibleSkins.Clear();
}

void EditorSceneObject::Delete( System::IntPtr _scene )
{
  NScene::IScene* scene = static_cast<NScene::IScene*>(_scene.ToPointer());
  if ( effect )
  {
    effect->Deinit();
    effect->RemoveFromScene();
  }
  if ( ppObject )
  {
    ppObject->Deinit();
    scene->RemoveObject( ppObject );
  }
  ppObject = nullptr;
  rootEditorSceneComponent = nullptr;
}

System::Collections::Generic::List<System::String^>^ EditorSceneObject::GetLocatorsNames()
{
  System::Collections::Generic::List<System::String^>^ names = gcnew System::Collections::Generic::List<System::String^>();
  if (Object)
  {
    vector<string const *> namesv = Object->GetLocatorsNames();

    for (int i = 0; i < namesv.size(); ++i)
    {
      names->Add( FromMBCS( *namesv[i] ) );
    }
  }

  return names;
}

void EditorSceneObject::AttachToByLocator( System::String^ _name, EditorSceneObject^ so, DBTypes::Placement2^ _placement )
{
  if ( Object )
  {
    Placement nPlacement;
    convertPlacement(_placement, &nPlacement);
    string name = ToMBCS(_name);
    if ( so->GetRootEditorSceneComponent() != nullptr )
      Object->AttachToByLocator( name.c_str(), so->GetRootEditorSceneComponent()->sceneComponent, &nPlacement );
    //so->GetRootEditorSceneComponent()->sceneComponent->SetParentTransformUsageFlags(0);
    FillEditorSceneComponents( ppObject );
  }
}


DBTypes::Placement^ EditorSceneObject::GetStandAloneEffectPlacement( System::String^ parentType, int parentFlags )
{
  DBTypes::Placement^ resPlace = gcnew DBTypes::Placement();
  if ( Object )
  {
    
    const char *locatorName = ToMBCS(parentType).c_str();
    const NScene::Locator *pL = Object->FindLocator( locatorName );
    Placement pos;
    if (pL)
    {
      pL->CalculateWorldPlacement(pos);
    }
    else
    {
      pos = Object->GetPosition();
    }

    if ( !((int)parentFlags & NDb::STANDALONEEFFECTFLAGS_USEPARENTROTATION) )
    {
      pos.rot = QNULL;
    }
    if ( !((int)parentFlags & NDb::STANDALONEEFFECTFLAGS_USEPARENTSCALE) )
    {
      pos.scale = CVec3( 1.0f, 1.0f, 1.0f );
    }

    convertPlacement( &pos, resPlace );
    return resPlace;
  }
  return nullptr;
}

void EditorSceneObject::SetOpacity( float val )
{
  NScene::BasicMaterialProc proc(val);

  if ( Object )
  {
    ForAllMaterials( *Object, proc );
  }
}

void EditorSceneObject::SelectLocator( System::String^ locatorName )
{
  if ( Object )
  {
    System::Collections::Generic::List<System::String^>^ locators = GetLocatorsNames();
    for ( int i = 0; i < locators->Count; i++ )
    {
      if ( locators[i] == locatorName )
      {
        Object->SelectLocator( i );
        return;
      }
    }
    Object->SelectLocator( -1 );
  }
}

void EditorSceneObject::SetTerrainLikeObject()
{
  if ( Object )
  {
    NScene::MaterialPriorityChanger f( NDb::MATERIALPRIORITY_TERRAINOBJECTS );
    NScene::ForAllMaterials( *Object, f );
  }
}

void EditorSceneObject::SetParentTransformUsageFlags( unsigned int _flags )
{
  if ( Object )
  {
    Object->SetParentTransformUsageFlags( _flags );
  }  
}

bool EditorSceneObject::IsContainWaterComponent()
{
  if ( Object )
  {
    FindWaterComponent f;
    Object->Traverse( f );

    if ( f.result )
      return true;
  }
  return false;
}

void EditorSceneObject::ApplyTrack( String^ track )
{
  if ( Object )
  {
    nstl::string trackName = ToMBCS( track );
    Object->ApplyTrack( trackName );
  }
}