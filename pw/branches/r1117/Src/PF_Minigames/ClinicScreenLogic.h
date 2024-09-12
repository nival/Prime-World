#pragma once

#include "MinigameScreenLogic.h"
#include "ClinicGiftsDialog.h"
#include "../PF_GameLogic/GameMenuInterfaces.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
class Clinic;
class MinigameWorldObject;
class MinigameClientObject;
class Minigames;
class ClinicCreepClientObject;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
_interface IScene;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
enum ECreepWish;
struct MinigameUIStylesDesc;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
struct AABB;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

class ClinicGameMenuProxy;

class ClinicScreenLogic : public PF_Minigames::MinigameScreenLogic
{
  friend ClinicGameMenuProxy;

  NI_DECLARE_REFCOUNT_CLASS_1( ClinicScreenLogic, PF_Minigames::MinigameScreenLogic );
  DECLARE_LUA_TYPEINFO( ClinicScreenLogic );

public:
  ClinicScreenLogic();

  void SetCursorPos( const CVec2& _cursorPos );

  void OnLeftClick();
  void OnRightClick();
  void OnEscapeKey();

  virtual void  Step(float deltaTime);
  virtual bool  GetCursor( string * id, const UI::Point & screenCoords ) const;

  void InitScene(PF_Minigames::Minigames * _minigames, int _levelID);

  ///Lua///
  void PopGameMenu();

private:
  CObj<ClinicGameMenuProxy> gameMenuProxy;
  CPtr<NScene::IScene> scene;
  CPtr<PF_Minigames::Clinic> clinic;

  //Раздельная обработка клика и mouse over!
  CVec2 cursorPos;
  CPtr<PF_Minigames::MinigameWorldObject> currentWorldClickPick;
  CPtr<PF_Minigames::MinigameClientObject> currentClientOverPick;

  Strong<ClinicGiftsDialog> giftsDialog;

  bool exitDone;


  void UpdatePick();

  const NDb::MinigameUIStylesDesc & GetUIStylesDesc() const;

  void UpdateGameTime();
  void UpdateGameHearts(int hearts);

  void ProcessCounters();

  //ClinicGameMenuProxy
  void GameMenuClosed();
  void AbortMinigameLevel();

protected:
  virtual void ExitGame();
};

}
