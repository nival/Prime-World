#pragma once

#include "../Client/ScreenUILogicBase.h"
#include "MinigameScreenLogic.h"
#include "../Scene/Camera.h"

namespace NScene
{
	_interface IScene;
}


namespace PF_Minigames
{


class MinigameCameraController;
class MinigameLobbyScreen;
class Minigames;
class Clinic;


class MinigameLobbyScreenLogic : public MinigameScreenLogic
{
  NI_DECLARE_REFCOUNT_CLASS_1( MinigameLobbyScreenLogic, MinigameScreenLogic );

public:
  DECLARE_LUA_TYPEINFO( MinigameLobbyScreenLogic );

  MinigameLobbyScreenLogic();

  void InitScene( PF_Minigames::Minigames* _minigames );
  void OnBecameFront();

	void ExitLobby();
  bool IsExitingFromLobby() const { return waitForCameraMovement > 0; } //FIXME: strut

  virtual void  Step( float deltaTime );

  void SetScreen( PF_Minigames::MinigameLobbyScreen * _screen ) { screen = _screen; }
  PF_Minigames::MinigameLobbyScreen * GetScreen() { return screen; }

private:
  CObj<PF_Minigames::MinigameCameraController> cameraController;
  CPtr<PF_Minigames::Minigames> minigames;

  NScene::SCameraPosition saveCameraParams;
  CVec3 cameraPositionSave;
  float cameraFOVSave;
  Weak<PF_Minigames::MinigameLobbyScreen> screen;

  float waitForCameraMovement;
};

} //namespace PF_Minigames
