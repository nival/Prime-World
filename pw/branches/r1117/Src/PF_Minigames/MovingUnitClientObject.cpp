#include "stdafx.h"

#include "../Scene/CollisionHull.h"
#include "../Scene/SceneObject.h"

#include "MovingUnitClientObject.h"
#include "MovingUnitController.h"
#include "MinigameWorldObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MovingUnitClientObject::MovingUnitClientObject()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MovingUnitClientObject::~MovingUnitClientObject()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::SceneObject* MovingUnitClientObject::Init( MinigameWorldObject* _worldObject, NScene::IScene* _scene, const NDb::DBSceneObject* _DBSceneObject, const Placement& _placement, bool collidable )
{
  MinigameClientObject::Init( _worldObject, _scene, _DBSceneObject, _placement, collidable );

  controller = new MovingUnitController( Get( sceneObject ) );

	return Get( sceneObject );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitClientObject::Update( float deltaTime, bool gameOnPause )
{
  if ( IsValid( worldObject ) && !gameOnPause )
  {
    bool goInstantly = false;
    const Placement& targetPlacement = worldObject->GetTarget( goInstantly );

    if ( goInstantly )
    {
      SetPlacement( targetPlacement );
    }
    else
    {
      Placement currentPlacement = GetPlacement();
      CVec3 movementDir = targetPlacement.pos - currentPlacement.pos;

      Normalize( &movementDir );
      currentPlacement.pos += movementDir * deltaTime * worldObject->GetLinearVelocity();

      SetPlacement( currentPlacement, true );
    }
  }

  // Update collision hull
  if ( IsValid( collisionHull ) )
  {
    Matrix43 matrix;
    GetPlacement().GetMatrix( &matrix );
    collisionHull->SetPosition( matrix, 0 );
  }

  controller->Update( deltaTime );
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::MovingUnitClientObject)
