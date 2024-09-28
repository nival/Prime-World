#pragma once

#include "../UI/FSCommandListner.h"

namespace NWorld
{
  class PFBaseMaleHero;
  class PFShop;
}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}

namespace ShopItemState
{
  enum EShopItemState;
}

namespace NGameX
{
class AdventureFlashInterface;
class AdventureTooltip;
_interface IUIEventHandler;

class ShopController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ShopController, UI::IFSCommandListner, BaseObjectST );

public:
   ShopController( const NDb::DBUIData * _uiData, UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler, NWorld::PFBaseMaleHero * _hero );
   ~ShopController();

  void SetShop(NWorld::PFShop * _shop);
  const NWorld::PFShop * GetShop() const {return shop;}

  void Update(int mouseX, int mouseY);

  bool IsShopOpen() const { return (shop.GetPtr() != 0); }

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:
  void ShowConsumableDesc(int index, bool show);

  NDb::Ptr<NDb::DBUIData>         uiData;

  Weak<UI::FlashContainer2> flashWnd;

  ConstPtr<NWorld::PFBaseMaleHero>  hero;
  ConstPtr<NWorld::PFShop>          shop;

  CObj<AdventureTooltip>        tooltip;
  Weak<AdventureFlashInterface>          flashInterface;
  Weak<IUIEventHandler>         eventHandler;

  vector<ShopItemState::EShopItemState> itemStates;
  
};

} //namespace NGameX
