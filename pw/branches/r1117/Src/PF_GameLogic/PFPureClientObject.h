#pragma once 

#include "../Scene/SceneObject.h"
#include "../PF_Core/ClientObject.h"
#include "PFClientSceneObjectsHolders.h"

namespace NDb 
{
  struct AdvMapObject; 
}

namespace NGameX
{
  class ISceneObjectsHolder;

  class PFPureClientObject : public PF_Core::PureClientObjectBase
  {
    OBJECT_METHODS( 0x2B832C01, PFPureClientObject );

  public:
    bool IsVisible() const { return isVisible; }
    void SetVisibility( bool _isVisible );
    void UpdateVisibility();
    NScene::SceneObject* GetSceneObject() const;

    void SetPosition( const CVec2& pos );
    void SetPosition( const CVec3& pos );
    void SetRotation( const CQuat& rot );

    const CVec3& GetPosition() const { return placement.pos; }
    const CQuat& GetRotation() const { return placement.rot; }
    const Placement& GetPlacement() const { return placement; }

  protected:
    PFPureClientObject( const NDb::AdvMapObject& dbAdvMapObject, NScene::IScene* _pScene );
    explicit PFPureClientObject() {  }
    
    virtual void Update( float timeDiff );

    NScene::IScene* GetScene() const { return pScene; }

  private:
    AutoPtr<ISceneObjectsHolder> pSceneObjectsHolder;
    bool isVisible;
    Placement placement;
    NScene::IScene* pScene;
  };
}