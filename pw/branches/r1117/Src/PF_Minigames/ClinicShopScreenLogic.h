#pragma once

#include "../Client/Tooltips.h"

#include "ClinicBuyDialog.h"
#include "MinigamePauseDialog.h"
#include "MinigameScreenLogic.h"
#include "ClinicGiftsDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
  class Clinic;
  class MinigameWorldObject;
  class MinigameCameraController;
  class Minigames;
  class ClinicItem;
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

class ImageLabel;

class ClinicShopScreenLogic : public PF_Minigames::MinigameScreenLogic
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClinicShopScreenLogic, PF_Minigames::MinigameScreenLogic );
  DECLARE_LUA_TYPEINFO( ClinicShopScreenLogic );

public:
  ClinicShopScreenLogic();

  bool OnMouseMove( const CVec2 & cursorPos );
  bool OnLeftClick( const CVec2 & cursorPos );

  virtual void OnEscapeKey();

  void InitScene(PF_Minigames::Minigames * _minigames);
  void InitLayout();

  //Lua callbacks
  virtual void ExitGame();
  bool SelectItem( UI::Window * pItem );
  void HiliteItem( UI::Window * pItem, bool selection);
  void TryToBuy();
  void BuyNow();

protected:
  virtual void Step( float deltaTime );

private:
  struct SItem
  {
    CPtr<PF_Minigames::ClinicItem> item;
    bool affordable;
    bool canBeBought;
    Weak<UI::ImageLabel> pPriceWnd, pGrayPriceWnd; //For price
    explicit SItem(PF_Minigames::ClinicItem * _pItem) : item(_pItem), affordable(false), canBeBought(false) {}
    SItem() : item(NULL), affordable(false), canBeBought(false) {}
  };

  typedef map<Weak<UI::Window>, SItem> TWindowsItems;

  CPtr<NScene::IScene> scene;
  CPtr<PF_Minigames::Clinic> clinic;

  Strong<ClinigBuyDialog> buyDialog;
  Strong<PF_Minigames::MinigamePauseDialog> pauseDialog;

  TWindowsItems itemsWindows;
  Weak<UI::Window> currentItem, selectedItemWindow;
  Weak<UI::Window> hilitedSelItem, hilitedItem;
  float timeSinceLastUpdate;

  bool SetupItem( UI::Window * pItemWnd, PF_Minigames::ClinicItem * pItem);
  void SetItemState( UI::Window * pItemWnd, const char * id );
  void EnableBuy(bool enable);
  void Deselect();
};

}
