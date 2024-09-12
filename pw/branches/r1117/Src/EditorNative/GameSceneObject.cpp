#include "stdafx.h"
#include "Utility.h"
#include "TerrainUtils.h"
#include "GameSceneObject.h"
#include "Settings.h"
#include "EditorScene.h"
#include "../Scene/LightingScene.h"
#include "../Scene/EditorSceneObject.h"
#include "../Scene/CollisionGeometry.h"
#include "../Scene/SceneUtils.h"

using namespace System;

using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;
using namespace EditorNative::Terrain;

static int GetSkinIndex( const vector<NDb::SkinPart>& skins, const string& skinName )
{
	for ( int i = 0; i < skins.size(); ++i )
	{
		if ( skins[i].skinPartName == skinName )
		{
			return i;
		}
	}
	return -1;
}

static void AttachSkin( String^ skinName, NDb::Ptr<NDb::Skeleton> pSkel, NScene::EditorSceneObject *pObj, float renderTime )
{
	string skinName_s = ToMBCS( skinName );

	pObj->ShowSkin( skinName_s, true );
}

static bool IsValidAnimationIndex( const vector<NDb::Animation>& animations, int animationIndex )
{
	return animationIndex >= 0 && animationIndex < animations.size();
}

static void ActivateAnimation( NScene::EditorSceneObject *pObj, int animationIndex , float renderTime )
{
	pObj->StartAnimation( animationIndex );
}

void GameSceneObject::Initialize( DBTypes::GameObject^ gameObj, int layer, bool isPlacedToMap, System::String^ scriptGN )
{
  scriptGroupName = scriptGN;
  isFreezed = false;
  isMSO = false;
  isSound = false;
  this->isPlacedToMap = isPlacedToMap;
  sceneObjects = gcnew System::Collections::Generic::List<NativeSceneObject^>();
  for each( libdb::DB::DBID^ dbid in InitSceneObjects( gameObj ) )
    sceneObjects->Add( gcnew NativeSceneObject( dbid ) );

  currentSceneObject = 0;
  pointLight = nullptr;
  isPointLight = false;
  gameObject = gameObj;
  isHidden = false;
  isPlaceOnTerrain = true;
  isFullyLoaded = false;
}

GameSceneObject::GameSceneObject( libdb::DB::DBID^ dbid, int layer, System::String^ scriptGN )
{
  scriptGroupName = scriptGN;
  isFreezed = false;
  isMSO = false;
  isSound = false;
  sceneObjects = gcnew System::Collections::Generic::List<NativeSceneObject^>();
  if ( !dbid->IsEmpty )
  {
    sceneObjects->Add( gcnew NativeSceneObject( dbid ) );
  }
  currentSceneObject = 0;
  pointLight = nullptr;
  isPointLight = false;
  gameObject = nullptr;
  isHidden = false;
  isPlaceOnTerrain = true;
  isFullyLoaded = false;
}

GameSceneObject::GameSceneObject( DBTypes::GameObject^ gameObj, int layer, System::String^ scriptGN )
{
  this->Initialize( gameObj, layer, true, scriptGN );
}

GameSceneObject::GameSceneObject( DBTypes::GameObject^ gameObj, int layer, bool isPlacedToMap, System::String^ scriptGN )
{
  this->Initialize( gameObj, layer, isPlacedToMap, scriptGN );
}


GameSceneObject::~GameSceneObject()
{
  this->!GameSceneObject();
}

GameSceneObject::!GameSceneObject()
{
  if ( isPointLight && pointLight && !ReferenceEquals( Scene, nullptr ) && Scene->GetLightScene() )
  {
    Scene->GetLightScene()->DeleteLight(pointLight);
  }
  Scene = nullptr;
}

void GameSceneObject::CreateSceneObjects( NScene::IScene& scene )
{
	Placement place( LocationInternal, RotationInternal, CVec3( 1, 1, 1 ) );

  CObj<NScene::CollisionHull> pCollisionHull;
  CObj<NScene::CollisionHull> pSmallCollisionHull;
  CObj<NScene::CollisionHull> pCollisionHullGeometry;
  CObj<NScene::CollisionHull> pSmallCollisionHullGeometry;
  bool loaded = false;
  bool loadedGeometry = false;

	for ( int i = 0; i < sceneObjects->Count; i++ )
  {
		if ( sceneObjects[i]->ppObject )
			delete sceneObjects[i]->ppObject;

    sceneObjects[i]->ppObject = 0; 
    if ( !isFullyLoaded && i != currentSceneObject ) continue;

    if ( sceneObjects[i]->dbId->IsEmpty )
      continue;

    NDb::Ptr<NDb::DBSceneObject> pDBSVisual;
    pDBSVisual = GetObject<NDb::DBSceneObject>( sceneObjects[i]->dbId );
    if ( pDBSVisual.IsEmpty() )
      continue;

    NScene::EditorSceneObject* sceneObj;
    sceneObj = NScene::CreateEditorSceneObject( &scene, pDBSVisual, place, i == currentSceneObject, !isFullyLoaded );

    if( !loaded ) // на все объекты mso только одна геометрия для коллизий
    {
      pCollisionHull = sceneObj->GetCollision();
      pSmallCollisionHull = sceneObj->GetSmallCollision();
      loaded = true;
    }
    else
    {
      sceneObj->UnregisterCollisionGeometry();

      sceneObj->SetCollision( pCollisionHull, pSmallCollisionHull );
    }

    //it uses in EditorScene::Pick for optimization
    sceneObj->SetOwnerID(GetOwnerId());
    
    if ( gameObject && !pDBSVisual->collisionGeometry.IsEmpty() )
    {
      const NDb::Ptr<NDb::CollisionGeometry> dbGeom = GetObject<NDb::CollisionGeometry>(libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( pDBSVisual->collisionGeometry->GetDBID() ) ) ));
      if ( !dbGeom.IsEmpty() )
      {
        sceneObj->RegisterCollisionGeometry( dbGeom );

        if( !loadedGeometry ) // на все объекты mso только одна геометрия для коллизий
        {
          pCollisionHullGeometry = sceneObj->GetCollision();
          pSmallCollisionHullGeometry = sceneObj->GetSmallCollision();
          loadedGeometry = true;
        }
        else
        {
          sceneObj->UnregisterCollisionGeometry();

          sceneObj->SetCollision( pCollisionHullGeometry, pSmallCollisionHullGeometry );
        }

        if ( gameObject->heightObject )
          sceneObj->SetLayer( 0 );
      }
    }

    sceneObj->SetPlaceOnTerrain( isPlaceOnTerrain );
    sceneObjects[i]->ppObject = sceneObj;

    if ( isFreezed && sceneObj && sceneObj->GetRootComponent() )
    {
      NDb::Ptr<NDb::TimeController> pTimeCtrl = sceneObj->GetRootComponent()->GetTimeControllerDesc();
      float startTime = 0.0f;
      if ( pTimeCtrl )
      {
        startTime = pTimeCtrl->startDelay + pTimeCtrl->fadein;
      }

      sceneObj->Reinit();
      sceneObj->UpdateForced( startTime );
    }

    if ( !Scene->IsEnabledEffectsInScene )
      NScene::EnableEffectsInObject( sceneObj, false );

    if ( IsSound() && i > 1 )
    {
      sceneObj->Deinit();
    }
  }
}

Bound^ GameSceneObject::BoundingBox::get()
{
  if ( IsValid )
  {
    SBound bound;
    Object->GetBound(bound);
    return gcnew Bound( LocationInternal + bound.s.ptCenter, bound.ptHalfBox );
  }
  else
  {
    return nullptr;
  }
}

bool GameSceneObject::IsEqual( NScene::EditorSceneObject* ptr )
{
  return IsValid && ptr == Object;
}

void GameSceneObject::Reload()
{
  EditorScene^ scene = Scene;
  Scene = nullptr;
  Scene = scene;
}

void GameSceneObject::CollisionGeometryVisible::set( bool value )
{
  if ( IsValid )
  {
    sceneObjects[currentSceneObject]->collisionGeometryVisible = value;
    if ( CollisionGeometryVisible )
    {
			Object->Highlight( NScene::HT_COLLISION );
    }
    else
    {
			NScene::HighlightType htype = NScene::HT_OFF;
			if ( IsSelected )
			{
				htype = Scene->GetDrawCollisionSelection() ? NScene::HT_COLLISION : NScene::HT_COLOR;
			}
			Object->Highlight( htype );
    }
  }
}

void GameSceneObject::OnPositionChanged()
{
  if ( IsValid )
  {
    Placement pos( LocationInternal, RotationInternal, ScaleInternal );
    Object->SetPositionWithPlacingOnTerrain( pos );
    if ( IsMSO() && Scene->HasTerrain )
    {
      int nature = Scene->SceneTerrain->GetFraction( pos.pos.x, pos.pos.y );
      SetSceneObject( nature );
    }
    
    // notify lighting scene about changes
    for each ( NativeSceneObject^ obj in sceneObjects )
    {
      if (obj->ppObject)
      {
        Scene->GetLightScene()->UpdateObject(obj->ppObject);
      }
    }
  }
}

void GameSceneObject::OnSelectionChanged()
{
  if ( IsValid )
  {
    if ( IsSelected )
    {
			NScene::HighlightType htype = Scene->GetDrawCollisionSelection() ? NScene::HT_COLLISION : NScene::HT_COLOR;
			Object->Highlight( htype );
    }
    else
    {
			Object->Highlight( CollisionGeometryVisible ? NScene::HT_COLLISION : NScene::HT_OFF );
    }
  }
}

void GameSceneObject::OnShowSelectionChanged( System::Object^ sender, System::EventArgs^ e )
{
  if ( IsValid )
	{
		NScene::HighlightType htype = NScene::HT_OFF;
		if ( IsSelected && Scene->ShowSelection )
		{
			htype = Scene->GetDrawCollisionSelection() ? NScene::HT_COLLISION : NScene::HT_COLOR;
		}

		Object->Highlight( htype );
	}
}

void GameSceneObject::OnBeforeOwnerChanged()
{
  if ( IsValid )
  {
    if ( isPointLight && pointLight && !ReferenceEquals( Scene, nullptr ) && Scene->GetLightScene() )
    {
      Scene->GetLightScene()->DeleteLight(pointLight);
    }

    Scene->ShowSelectionChanged -= gcnew EventHandler( this, &GameSceneObject::OnShowSelectionChanged );
    Scene->NativeScene->RemoveObject( Object );
    for ( int i = 0; i < sceneObjects->Count; i++ )
    {
      delete sceneObjects[i]->ppObject;
      sceneObjects[i]->ppObject = 0;
    }
  }
}

void GameSceneObject::OnOwnerChanged()
{
  if ( ReferenceEquals( Scene, nullptr ) )
		return;

  if ( isPointLight && Scene->GetLightScene() )
    pointLight = Scene->GetLightScene()->CreateLight();

  isFullyLoaded = Scene->IsMapLoaded;

  //TODO: Set start SceneObject in MSO
  if ( IsMSO() && Scene->HasTerrain )
  {
    Placement pos( LocationInternal, RotationInternal, ScaleInternal );
    int nature = Scene->SceneTerrain->GetFraction( pos.pos.x, pos.pos.y );
    if ( nature >= 0 && nature < sceneObjects->Count )
      currentSceneObject = nature;
  }

  if ( IsSound() && IsMSO() )
  {
    currentSceneObject = 0;
  }

  CreateSceneObjects( *Scene->NativeScene );
	if ( IsValid )
  {
    Scene->ShowSelectionChanged += gcnew EventHandler( this, &GameSceneObject::OnShowSelectionChanged );
    CollisionGeometryVisible = CollisionGeometryVisible;	// nice way for reinit collision visibility :-)
    OnPositionChanged();
  }
}

void GameSceneObject::CreateLight()
{
  isPointLight = true;
}

void GameSceneObject::UpdateLightInfo( DBTypes::PointLightInfo^ pointLightInfo )
{
  if ( isPointLight && pointLight )
  {
    pointLight->m_attenuationType = static_cast<NDb::Attenuation>(pointLightInfo->attenuation);
    pointLight->m_diffuseColor.A = pointLightInfo->diffuse->A;
    pointLight->m_diffuseColor.R = pointLightInfo->diffuse->R;
    pointLight->m_diffuseColor.G = pointLightInfo->diffuse->G;
    pointLight->m_diffuseColor.B = pointLightInfo->diffuse->B;
    pointLight->m_diffuseIntensity = pointLightInfo->diffuseIntensity;
    pointLight->m_flags = static_cast<NDb::PointLightFlags>(pointLightInfo->flags);
    pointLight->SetLocation(CVec3(pointLightInfo->location->x, pointLightInfo->location->y, pointLightInfo->location->z));
    pointLight->SetRange(pointLightInfo->range);
    if ( !ReferenceEquals( Scene, nullptr ) && Scene->GetLightScene() )
    {
      Scene->GetLightScene()->UpdateLight(pointLight);
    }
  }
}

void GameSceneObject::SetCurrentPlacement( DBTypes::Placement^ _placement )
{
  if ( Object )
  {
    Placement* curPlacement = new Placement();
    convertPlacement( _placement, curPlacement );
    Object->SetPositionWithPlacingOnTerrain( *curPlacement );
    delete curPlacement;
  }
}

void GameSceneObject::ReplaceObjectOnTerrain()
{
  if ( Object )
  {
    Object->ReplaceObjectOnTerrain();
  }
}

void GameSceneObject::AddObjectToHeightMap()
{
  if ( Object && gameObject && gameObject->heightObject )
  {
    NScene::CollisionHull* hull = Object->GetCollision();
    NDb::Ptr<NDb::DBSceneObject> pDBSVisual;
    pDBSVisual = GetObject<NDb::DBSceneObject>( sceneObjects[currentSceneObject]->dbId );
    if ( !pDBSVisual->collisionGeometry.IsEmpty() && hull )
    {
      Scene->AddObjectToLayer( 1, hull );
      Object->SetLayer( 0 );
    }
  }
}

void GameSceneObject::SetSceneObject(int index)
{
  if ( IsSound() )
  {
    if ( IsMSO() )
    {
      DBTypes::Placement^ pos = GetCurrentPlacement();
      for ( int i = 1; i < sceneObjects->Count; i++ )
      {
        if ( sceneObjects[i]->ppObject )
        {
          sceneObjects[i]->ppObject->Deinit();
        }
      }
      if ( index+1 < sceneObjects->Count && sceneObjects[index+1]->ppObject )
      {
        float height = 0.0f;
        Placement* curPlacement = new Placement();
        convertPlacement( pos, curPlacement );
        Scene->NativeScene->GetHeightsController().GetHeight( curPlacement->pos.x, curPlacement->pos.y, 1, &height, 0 );
        curPlacement->pos.z -= height;
        sceneObjects[index+1]->ppObject->SetPositionWithPlacingOnTerrain( *curPlacement );
        delete curPlacement;
        sceneObjects[index+1]->ppObject->UpdateForced(0.0f);
      }

    }
  }
  else
  {
    DBTypes::Placement^ pos = GetCurrentPlacement();

    // TODO: !!!
    if (IsMSO())
    {
      if (Scene->NightLighting)
      {
        switch (index)
        {
        case 0:
        case 1:
        case 2:
          index += 3;
          break;
        }
      }
    }

    Hide( false );
    currentSceneObject = index;
    Show( false );

    if ( Object )
    {
      float height = 0.0f;
      Placement* curPlacement = new Placement();
      convertPlacement( pos, curPlacement );
      Scene->NativeScene->GetHeightsController().GetHeight( curPlacement->pos.x, curPlacement->pos.y, 1, &height, 0 );
      curPlacement->pos.z -= height;
      Object->SetPositionWithPlacingOnTerrain( *curPlacement );
      delete curPlacement;
    }
  }
}

void GameSceneObject::SetCurrentPlacement( DBTypes::Placement2^ _placement )
{
  if ( Object )
  {
    Placement* curPlacement = new Placement();
    convertPlacement( _placement, curPlacement );
    Object->SetPositionWithPlacingOnTerrain( *curPlacement );
    delete curPlacement;
  }
}

DBTypes::Placement^ GameSceneObject::GetCurrentPlacement()
{
  DBTypes::Placement^ result = gcnew DBTypes::Placement();
  if ( Object )
  {
    Placement curPlacement = Object->GetPosition();
    convertPlacement( &curPlacement, result );
  }
  else
  {
    result->location->x = LocationInternal.x;
    result->location->y = LocationInternal.y;
    result->location->z = LocationInternal.z;

    float height = 0.0f;
    Scene->NativeScene->GetHeightsController().GetHeight( result->location->x, result->location->y, 1, &height, 0 );
    result->location->z += height;

    result->rotation->x = RotationInternal.x;
    result->rotation->y = RotationInternal.y;
    result->rotation->z = RotationInternal.z;
    result->rotation->w = RotationInternal.w;
    result->scale->x = ScaleInternal.x;
    result->scale->y = ScaleInternal.y;
    result->scale->z = ScaleInternal.z;
  }
  return result;
}

void GameSceneObject::Hide( bool resetSelection )
{
  if ( IsValid)
    Scene->NativeScene->RemoveObject( Object );
  isHidden = true;
  if ( resetSelection )
    IsSelectable = false;
}

void GameSceneObject::Show( bool resetSelection )
{
  if ( isHidden )
  {
    if ( Object )
      Scene->NativeScene->AddSceneObject( Object );
    isHidden = false;
    if ( resetSelection )
      IsSelectable = true;
  }
}

void GameSceneObject::Draw() 
{
  if ( isPointLight && pointLight && IsSelected )
  {
    float range = pointLight->GetRange();
    CVec3 location = pointLight->GetLocation();
    Render::Color yellowColor( 255, 255, 0 );

    CQuat rot[3];
    rot[0] = QNULL;
    rot[1] = CQuat( float( PI / 2 ), V3_AXIS_Y );
    rot[2] = CQuat( float( PI / 2 ), V3_AXIS_X );

    for ( int i = 0; i < 3; i++ )
    {
      nstl::vector<CVec3> points;
      CalculateCirclePoints( Scene->NativeCamera, 10, rot[i], location, range, points );
      DrawCircle( points, yellowColor );
    }
  }
}

void GameSceneObject::SetOwnerId(int id)
{
  SceneElement::SetOwnerId(id);

	for each ( NativeSceneObject^ so in sceneObjects )
	{
    if(so->ppObject != nullptr)
    {
      so->ppObject->SetOwnerID(id);
    }
	}

}