#include "stdafx.h"

#include "PFPureClientObject.h"
#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"

BASIC_REGISTER_CLASS( NGameX::PFPureClientObject );

namespace NGameX
{
  PFPureClientObject::PFPureClientObject( const NDb::AdvMapObject& dbAdvMapObject, NScene::IScene* _pScene )
    : pScene( _pScene )
  {
    if ( dbAdvMapObject.gameObject )
    {
      placement = dbAdvMapObject.offset.GetPlace();

      const NDb::SingleStateObject* sso = dynamic_cast<NDb::SingleStateObject const*>( dbAdvMapObject.gameObject.GetPtr() );
      const NDb::DBSceneObject* pSceneObject = sso ? sso->sceneObject.GetPtr() : NULL;

      pSceneObjectsHolder = AutoPtr<ISceneObjectsHolder>( new SingleSceneObjectHolder( pScene, -1, placement, pSceneObject, NULL, "" ) );
    }

    Subscribe();
  }

  NScene::SceneObject* PFPureClientObject::GetSceneObject() const
  {
    NI_VERIFY( pSceneObjectsHolder != NULL, "pSceneObjectsHolder must be valid!", return NULL );
    const NScene::SceneObjectRef& obj = pSceneObjectsHolder->GetActive();
    return obj ? Get( obj ) : NULL;
  }

  void PFPureClientObject::SetPosition( const CVec3& pos )
  {
    placement.pos = pos;
    GetSceneObject()->SetPositionAndRotation( placement );
  }

  void PFPureClientObject::SetRotation( const CQuat& rot )
  {
    placement.rot = rot;
    GetSceneObject()->SetPositionAndRotation( placement );
  }

  void PFPureClientObject::SetPosition( const CVec2& pos )
  {
    placement.pos = CVec3( pos, 0.0f );
    NScene::PlaceOnTerrain( pScene->GetHeightsController(), placement.pos, 1 );
    GetSceneObject()->SetPositionAndRotation( placement );
  }

  void PFPureClientObject::SetVisibility( bool _isVisible )
  {
    isVisible = _isVisible;
    if ( pSceneObjectsHolder )
    {
      pSceneObjectsHolder->SetVisibility( isVisible );
    }
  }

  void PFPureClientObject::UpdateVisibility()
  {
    if (const NGameX::AdventureScreen * const screen = NGameX::AdventureScreen::Instance())
    {
      const VisibilityMapClient* visMap = screen->GetClientVisibilityMap();

      SetVisibility( visMap && visMap->IsPointVisible( placement.pos.AsVec2D() ) );
    }
  }


  void PFPureClientObject::Update( float timeDiff )
  {
    if ( pSceneObjectsHolder )
    {
      pSceneObjectsHolder->Update( timeDiff );
    }

    UpdateVisibility();
  }
} // namespace NGameX