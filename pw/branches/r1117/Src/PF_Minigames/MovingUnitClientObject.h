#pragma once

#include "MinigameClientObject.h"

namespace PF_Minigames
{

class MovingUnitController;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovingUnitClientObject : public MinigameClientObject
{
	OBJECT_BASIC_METHODS( MovingUnitClientObject )

public:
  MovingUnitClientObject();
	virtual ~MovingUnitClientObject();

  // from MinigameClientObject

  virtual NScene::SceneObject* Init( MinigameWorldObject* _worldObject, NScene::IScene* _scene, const NDb::DBSceneObject* _DBSceneObject, const Placement& _placement, bool collidable );
  virtual void Update( float deltaTime, bool gameOnPause );

  MovingUnitController * GetController() { return IsValid(controller) ? controller : NULL; }
  
private:
  CObj<MovingUnitController> controller;
};

} // namespace PF_Minigames

