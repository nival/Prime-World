#include "StdAfx.h"
#include "ShopController.h"

#include "../UI/FlashContainer2.h"
#include "../UI/ImageLabel.h"
#include "../UI/Cursor.h"

#include "AdventureFlashInterface.h"
#include "PFMaleHero.h"
#include "PFBuildings.h"
#include "AdventureTooltip.h"
#include "FlashFSCommands.h"
#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"
#include "PFConsumable.h"
#include "PFMaleHero.h"
#include "UIEventHandler.h"

namespace NGameX
{

ShopController::ShopController( const NDb::DBUIData * _uiData, UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler, NWorld::PFBaseMaleHero * _hero ) :
uiData( _uiData ),
flashInterface(_flashInterface),
hero(_hero),
eventHandler(_eventHandler),
flashWnd(flashContainer)
{
  using namespace FlashFSCommands;

  flashWnd->AddFSListner(ConvertToString(ShopItemToolTip), this);
  flashWnd->AddFSListner(ConvertToString(ShopItemClicked), this);
  flashWnd->AddFSListner(ConvertToString(ShopClosed), this);
  

  tooltip = new AdventureTooltip(tooltipWnd);
}

ShopController::~ShopController()
{
  using namespace FlashFSCommands;
  
  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(ShopItemToolTip));
  flashWnd->RemoveFSListner(ConvertToString(ShopItemClicked));
  flashWnd->RemoveFSListner(ConvertToString(ShopClosed));

}

void ShopController::SetShop( NWorld::PFShop * _shop )
{

  if (!IsValid(_shop) || !_shop->IsHeroNear(hero) || shop == _shop )
    return;

  shop = _shop;
  
  if (!IsValid(flashInterface))
    return;

  int itemsCount = shop->GetNumConsumables();

  itemStates.resize(itemsCount);

  flashInterface->SetShopItemsCount(itemsCount);

  for (int i = 0 ; i < itemsCount; i++)
  {
    itemStates[i] = ShopItemState::CanBuy;
    NDb::Ptr<NDb::Consumable> consumable = shop->GetConsumableDesc(i);
    flashInterface->SetShopItemIcon(i, consumable->image->textureFileName.c_str());
  }

  flashInterface->ShowShop(true);

}

void ShopController::Update( int mouseX, int mouseY )
{
  if (!IsValid(shop) || !IsValid(hero) || !IsValid(flashInterface))
    return;

  if (!shop->IsHeroNear(hero))
  {
    shop = 0;
    flashInterface->ShowShop(false);
    return;
  }

  for (int i = 0 ; i < shop->GetNumConsumables(); i++)
  {
    ShopItemState::EShopItemState itemState = shop->CanBuyConsumable(hero, i)? ShopItemState::CanBuy : ShopItemState::NotEnoughPrime;

    if (itemState!=itemStates[i])
    {
      itemStates[i] = itemState;
      flashInterface->SetShopItemState(i, itemState);
    }
  }

  if (tooltip->IsVisible())
  {
	  tooltip->SetLocation(mouseX , mouseY);
  }
}

void ShopController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  switch (ConvertToFSCommand(listenerID))
  {
  case ShopItemClicked:
    {
      int index;
      sscanf_s(args,"%d", &index);
      
      if (!IsValid(eventHandler))
        return;

      eventHandler->OnShopButtonClick(index);
      break;
    }
  case ShopItemToolTip:
    {
      int show, index;
      sscanf_s(args,"%d %d",&show, &index);
      ShowConsumableDesc(index, show);
      break;
    }
  case ShopClosed:
	  {
		  shop = 0;
		  break;
	  }
  default:
    {
      NI_ALWAYS_ASSERT("something bad happened to the event listener")
    }
  }
}

void ShopController::ShowConsumableDesc(int index, bool show)
{
  if (!IsValid(tooltip))
    return;

  if (!show)
  {
    tooltip->Show(false);
    eventHandler->TargetZoneTooltip(0);
    return;
  }

  if (!IsValid(shop))
    return;

  NDb::Ptr<NDb::Consumable> itemDesc = shop->GetConsumableDesc(index);
  if( !IsValid(itemDesc) )
  {
    //"UI: Invalid artifact pointer!" 
    return;
  }

  CObj<NWorld::PFConsumable> pConsumable( new NWorld::PFConsumable( 0, const_cast<NWorld::PFBaseMaleHero*>( hero.GetPtr() ), itemDesc ) );
  eventHandler->TargetZoneTooltip(pConsumable->GetAbility());

  NGameX::SConstUISubst subst;
  subst.Add( L"commonDescription", pConsumable->GetDBDesc()->commonDescription.GetText() );

  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init(pConsumable, itemDesc->description.GetText(), &subst);

  wstring text;
  precompiledTooltip.MakeText(text);

  tooltip->SetText( text, uiData->tooltipDownScaleLimit );
  tooltip->Show(true);
}


}//namespace NGameX