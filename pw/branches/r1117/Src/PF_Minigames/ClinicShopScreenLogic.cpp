#include "stdafx.h"

#include "ClinicShopScreenLogic.h"

#include "../UI/ImageLabel.h"
#include "../UI/Root.h"
#include "../UI/ScrollList.h"

#include "../Client/ScreenCommands.h"

#include "../Scene/Camera.h"
#include "../Scene/CollisionHull.h"

#include "Minigames.h"
#include "MinigameWorldObject.h"
#include "MinigameClientObject.h"
#include "MinigamesMain.h"
#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "ClinicEntrance.h"
#include "ClinicCommands.h"

#include "../Core/WorldCommand.h"


namespace UI
{
using namespace NScript;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( ClinicShopScreenLogic, PF_Minigames::MinigameScreenLogic )
  LUA_METHOD( ExitGame )
  LUA_METHOD( SelectItem )
  LUA_METHOD( HiliteItem )
  LUA_METHOD( TryToBuy )
  LUA_METHOD( BuyNow )
END_LUA_TYPEINFO( ClinicShopScreenLogic )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicShopScreenLogic::ClinicShopScreenLogic() :
scene(NULL),
clinic(NULL),
timeSinceLastUpdate(0)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::InitScene( PF_Minigames::Minigames * _minigames )
{
	clinic = _minigames->GetNativeMinigame<PF_Minigames::Clinic>( "Clinic" );

  buyDialog = new ClinigBuyDialog;
  buyDialog->Set(clinic);

  pauseDialog = new PF_Minigames::MinigamePauseDialog;
  pauseDialog->Set(clinic, this);

	NI_VERIFY( IsValid( clinic ), "", return );

	scene = _minigames->GetNativeMain()->GetScene();

  _minigames->GetNativeMain()->SendWorldCommand(PF_Minigames::CreateStartClinicLevelCommand(_minigames->GetWorldSessionInterface(), 0, false));
}

struct SItemSorter
{
  int access;
  int cost;
  wstring name;
  int index;
  SItemSorter() : access(0), cost(0), index(0) {}
  SItemSorter(int _access, int _cost, const wstring & _name, int idx) : access(_access), cost(_cost), name(_name), index(idx) {}
  bool operator < (const SItemSorter & right) const
  {
    if(access < right.access)
      return true;
    if(access > right.access)
      return false;
    if(cost < right.cost)
      return true;
    if(cost > right.cost)
      return false;
    if(name < right.name)
      return true;
    if(name > right.name)
      return false;
    return index < right.index;
  }
};
typedef map<SItemSorter, CPtr<PF_Minigames::ClinicItem> > TClinicShopItemSorter;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::InitLayout()
{
  NI_VERIFY(IsValid(clinic), "", return);

  UI::ScrollList * pList = UI::GetChildChecked<UI::ScrollList>(pBaseWindow, "ItemsList", true);
  NI_VERIFY(pList, "Absent some of the shop screen UI componets!", return; );

  //lets get items
  PF_Minigames::Clinic::ClinicItems allItems;
  clinic->RetrieveAllItems(&allItems);

  //then sort em
  TClinicShopItemSorter sorter;
  int index = 0;
  for(PF_Minigames::Clinic::ClinicItems::iterator it = allItems.begin(); it != allItems.end(); ++it, ++index)
  {
    PF_Minigames::ClinicItem * pItem = *it;
    if(!pItem->IsBought() && (pItem->GetCost() > 0))
    {
      SItemSorter id(pItem->GetAccessibility(), pItem->GetCost(),  pItem->GetName(), index);
      sorter[id] = pItem;
    }
  }
  allItems.clear();

  //populate UI list
  for(TClinicShopItemSorter::iterator it = sorter.begin(); it != sorter.end(); ++it)
    if(UI::Window * item = pList->AddItem(NStr::StrFmt("%i", it->first.index), "Item"))
        SetupItem(item, it->second);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreenLogic::SetupItem( UI::Window * pItemWnd, PF_Minigames::ClinicItem * pItem )
{
  SItem & item = (itemsWindows[pItemWnd] = SItem(pItem));

  item.affordable = clinic->GetGold() >= item.item->GetCost();
  item.canBeBought = clinic->ItemCanBeBought(pItem, true);

  //setup item price table
  item.pPriceWnd = UI::GetChildChecked<UI::ImageLabel>(pItemWnd, "Price", true);
  item.pGrayPriceWnd = UI::GetChildChecked<UI::ImageLabel>(pItemWnd, "PriceGray", true);

  if(item.pPriceWnd && item.pGrayPriceWnd)
  {
    wstring coinText = pItemWnd->GetRelatedText("Coin");
    wstring priceText = NStr::StrFmtW(L"%i%s", item.item->GetCost(), coinText.c_str());
    //Если /пока/ денег на шмот не хватает, то возможно мы сможем их накопить
    item.pPriceWnd->SetCaptionTextW(priceText);
    item.pGrayPriceWnd->SetCaptionTextW(priceText);

    bool showPrice = item.affordable && item.canBeBought;
    item.pPriceWnd->Show(showPrice);
    item.pGrayPriceWnd->Show(!showPrice);
  }

  //set lock image and gray cover
  UI::ImageLabel * pLock = UI::GetChildChecked<UI::ImageLabel>(pItemWnd, "Lock", true);
  UI::ImageLabel * pGrayer = UI::GetChildChecked<UI::ImageLabel>(pItemWnd, "Grayer", true);
  if(pLock && pGrayer)
  {
    pLock->Show(!item.canBeBought);
    pGrayer->Show(!item.canBeBought);
  }

  //update icon
  UI::ImageLabel * pIcon = UI::GetChildChecked<UI::ImageLabel>(pItemWnd, "Icon", true);
  if ( pIcon )
    pIcon->SetBackgroundMaterial( pItem->GetIconMaterial() );

  //set state
  SetItemState( pItemWnd, "" );
  return item.canBeBought;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::SetItemState( UI::Window * pItemWnd, const char * id )
{
  pItemWnd->CallHandler( "SetItemState", id );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::EnableBuy(bool enable)
{
  UI::Window * pBuyButt = UI::GetChildChecked<UI::Window>(pBaseWindow, "BuyButton", true);
  if(pBuyButt)
    pBuyButt->Enable(enable);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::Step( float deltaTime )
{
  const float CHECK_RATE = .25f;
  MinigameScreenLogic::Step( deltaTime );

  timeSinceLastUpdate += deltaTime;
  if ( timeSinceLastUpdate < CHECK_RATE )
    return;
  timeSinceLastUpdate -= CHECK_RATE;

  if( !IsValid( clinic ) )
    return;
  if( !IsValid( clinic->GetMinigames()->GetWorldSessionInterface() ) )
    return;

  ///DEBU///
  UI::ImageLabel * pMoney = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "Money", true);
  if(pMoney)
    pMoney->SetCaptionTextW(NStr::StrFmtW(L"%i <image:Price_icon align=center>", clinic->GetGold()));
  ///DEBU///

  UI::ImageLabel * pPanel = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescPanel", true);

  //Во время работы магазина предмет может стать:
  // - купленным, тогда его надо удалить
  // - стать недоступным по цене, тогда надо поправить плашку с денгами
  // - стать доступным по цене, тогда тоже надо поправить плашку с денгами
  int gold = clinic->GetGold();
  for(TWindowsItems::iterator it = itemsWindows.begin(); it != itemsWindows.end(); )
  {
    if(!IsValid(it->second.item))
    {
      ++it;
      continue;
    }

    //if its current item, check for its availability to enable 'Buy' button
    //...and dont forget to change that freakin scene object color
    //..and dont forget to hide that info panel
    //TODO: refactor it somehow to reduce copying of this 'setup/update' code...
    if(it->first == currentItem)
    {
      bool newCanBB = clinic->ItemCanBeBought(it->second.item, false);
      if((it->second.canBeBought && it->second.affordable) != newCanBB)
      {
        EnableBuy(newCanBB);
        if(pPanel) pPanel->Show(newCanBB);
      }
    }

    if(it->second.item->IsBought())
    {
      it->first->Close();
      TWindowsItems::iterator next = it;
      ++next;
      itemsWindows.erase(it);
      it = next;
      continue;
    }

    //affordable
    bool newAffordable = (it->second.item->GetCost() < gold);
    if(newAffordable != it->second.affordable)
    {
      it->second.affordable = newAffordable;
      if(IsValid(it->second.pPriceWnd) && IsValid(it->second.pGrayPriceWnd))
      {
        bool showPrice = it->second.affordable && it->second.canBeBought;
        it->second.pPriceWnd->Show(showPrice);
        it->second.pGrayPriceWnd->Show(!showPrice);
      }
    }

    //scene object color
    if(it->first == currentItem)
    {
      PF_Minigames::MinigameClientObject * pClientObject = clinic->GetClientObject(it->second.item->GetObjectID());
      if(pClientObject)
      {
        pClientObject->SetVisible(true);
        pClientObject->SetMulColor(it->second.affordable ? clinic->GetClinicDesc()->preselection.colorNotBought : clinic->GetClinicDesc()->preselection.colorNotBoughtUnavailable);
      }
    }

    ++it;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreenLogic::OnMouseMove( const CVec2 & cursorPos )
{
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreenLogic::OnLeftClick(const CVec2 & cursorPos)
{
  Deselect();
  HiliteItem( 0, true );

  UI::ImageLabel * pPanel = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescPanel", true);
  if( pPanel )
    pPanel->Show( false );

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::OnEscapeKey()
{
  ExitGame();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::Deselect()
{
  if(IsValid(selectedItemWindow))
  {
    TWindowsItems::iterator it = itemsWindows.find(selectedItemWindow);
    if(it != itemsWindows.end())
    {
      CPtr< PF_Minigames::ClinicItem > logicItem = it->second.item;

      if( IsValid( logicItem ) )
      {
        PF_Minigames::MinigameClientObject * pClientObject = clinic->GetClientObject( logicItem->GetObjectID() );
        if(pClientObject)
        {
          if ( !logicItem->IsBought() )
            pClientObject->SetVisible(false);
          pClientObject->SetMulColor(clinic->GetClinicDesc()->preselection.colorPreselect);
        }
      }
//      itemsWindows.erase(it);
    }

    selectedItemWindow->Close();
    selectedItemWindow = 0;

    currentItem = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::ExitGame()
{
  //Stop clinic(shop) level
  PF_Minigames::MinigameCreeps spawnCreeps;
  CObj<NCore::WorldCommand> worldCommand = PF_Minigames::CreateStopClinicLevelCommand(clinic->GetMinigames()->GetWorldSessionInterface(), spawnCreeps);
  clinic->GetMinigames()->GetNativeMain()->SendWorldCommand( worldCommand );

  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( "ClinicShopScreen" ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreenLogic::SelectItem( UI::Window * pItem )
{
  UI::ImageLabel * pPanel = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescPanel", true);
  NI_VERIFY(pPanel, "Some layout elements does not exist", return false);

  UI::Window * pItemWnd = dynamic_cast<UI::Window *>( pItem );

  //we cant select displayable item' control
  if(IsValid(selectedItemWindow) && pItemWnd == selectedItemWindow)
    return false;

  TWindowsItems::iterator it = itemsWindows.find(pItemWnd);
  if(it == itemsWindows.end())
  {
    pPanel->Show(false);
    EnableBuy(false);
    return false;
  }

  NI_ASSERT( IsValid(it->second.item), "" );
  PF_Minigames::ClinicItem * pClinicItem = it->second.item;

  //we wont select same item
  if( it->first == currentItem )
    return false;
  //we wont select that we cant buy
  if( !clinic->ItemCanBeBought( pClinicItem, true ) )
    return false;

  Deselect(); // Destroys 'selectedItemWindow' item and corresponding 'itemsWindows' entry

  currentItem = it->first;

  pPanel->Show(true);

  //set descr text
  UI::ImageLabel * pName = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescItemName", true);
  if(pName)
    pName->SetCaptionTextW(pClinicItem->GetName());

  UI::ImageLabel * pDesc = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescItemText", true);
  if(pDesc)
    pDesc->SetCaptionTextW(pClinicItem->GetDescription());

  //setup item
  UI::ImageLabel * pTable = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "DescItemTable", true);
  if(pTable)
  {
    selectedItemWindow = pPanel->CreateChild("DescItem_procedural", "Item",
      pTable->GetPos().x, pTable->GetPos().y,
      pTable->GetSize().x, pTable->GetSize().y,
      NDb::UIELEMENTHALIGN_LEFT, NDb::UIELEMENTVALIGN_TOP);

    SetupItem(selectedItemWindow, pClinicItem);
  }

  //show & hilite scene model
  PF_Minigames::MinigameClientObject * pClientObject = clinic->GetClientObject(pClinicItem->GetObjectID());
  if(pClientObject)
  {
    pClientObject->SetVisible(true);
    pClientObject->SetMulColor(it->second.affordable ? clinic->GetClinicDesc()->preselection.colorNotBought : clinic->GetClinicDesc()->preselection.colorNotBoughtUnavailable);
  }

  //set 'buy' button
  bool enable = clinic->ItemCanBeBought(pClinicItem, false);
  EnableBuy(enable);
  return enable;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::HiliteItem( UI::Window * pItemWnd, bool selection)
{
  if(IsValid(selectedItemWindow) && pItemWnd == selectedItemWindow)
      return;

  TWindowsItems::iterator it = itemsWindows.find(pItemWnd);
  if(it != itemsWindows.end())
    if(!it->second.canBeBought)
      return;

  if(selection)
  {
    if ( pItemWnd != hilitedSelItem )
    {
      //change ui controls state
      if (IsValid(hilitedSelItem))
        if (hilitedSelItem == hilitedItem)
          SetItemState( hilitedSelItem,  "hilited" );
        else
          SetItemState( hilitedSelItem, "" );

      hilitedSelItem = pItemWnd;
      if( IsValid( hilitedSelItem ) )
        SetItemState( hilitedSelItem, "selected" );
    }
  }
  else
  {
    if ( pItemWnd != hilitedItem )
    {
      //change ui control state
      if(IsValid(hilitedItem) && hilitedItem != hilitedSelItem)
        SetItemState( hilitedItem,  "" );

      hilitedItem = pItemWnd;
      if(IsValid(hilitedItem) && hilitedItem != hilitedSelItem)
        SetItemState( hilitedItem,  "hilited" );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::TryToBuy()
{
  TWindowsItems::iterator it = itemsWindows.find(selectedItemWindow);
  if(it == itemsWindows.end())
    return;

  if(it->second.item)
    buyDialog->Popup(it->second.item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreenLogic::BuyNow()
{
  TWindowsItems::iterator it = itemsWindows.find(selectedItemWindow);
  if(it == itemsWindows.end())
    return;

  if(!IsValid(it->second.item))
    return;

  CPtr<PF_Minigames::MinigamesMain> mgMain = clinic->GetMinigames()->GetNativeMain();
  PF_Minigames::IWorldSessionInterface * session = clinic->GetMinigames()->GetWorldSessionInterface();

  if( IsValid( it->second.item ) )
    mgMain->SendWorldCommand( PF_Minigames::CreateClinicBuyCommand( session, it->second.item->GetObjectID() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI
