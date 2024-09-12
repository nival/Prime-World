#include "StdAfx.h"

#include "InventoryController.h"

#include "InventoryInterface.h"
#include "UIEventHandler.h"
#include "AdventureFlashInterface.h"
#include "PFConsumable.h"
#include "DBConsumable.h"
#include "PFAbilityData.h"
#include "FlashFSCommands.h"

//for tooltips
#include "AdventureTooltip.h"
#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"

#include "../ui/FlashContainer2.h"
#include "../ui/ImageLabel.h"
//#include "../UI/Cursor.h"

namespace
{
  static const int NO_TARGET = -1;
}

namespace NGameX
{

InventoryController::InventorySlotStatus::InventorySlotStatus()
  :  slotState (ActionBarSlotState::Active)
  ,  count(0)
  ,  cooldown(0)
  ,  maxCooldown(0)
{
}

InventoryController::InventorySlotStatus::InventorySlotStatus( int _count, ActionBarSlotState::EActionBarSlotState _slotState, float _cooldown, float _maxCooldown )
:  slotState (_slotState)
,  count(_count)
,  cooldown(_cooldown)
,  maxCooldown(_maxCooldown)
{

}

bool InventoryController::InventorySlotStatus::operator==( const InventorySlotStatus &other ) const
{
  return memcmp( this, &other, sizeof(InventoryController::InventorySlotStatus) ) == 0;
}

InventoryController::InventoryController( UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler, const NWorld::IInventory * _inventory )
: inventory(_inventory)
, flashInterface(_flashInterface)
, eventHandler(_eventHandler)
, targetingConsumable(NO_TARGET)
, emptySlotStatus(0, ActionBarSlotState::Disabled, -1, -1)
, flashWnd(flashContainer)
{
  using namespace FlashFSCommands;

  flashWnd->AddFSListner(ConvertToString(InventoryItemClicked), this);
  flashWnd->AddFSListner(ConvertToString(InventoryItemToolTip), this);

  slotStatuses.resize(32, emptySlotStatus);
  tooltip = new AdventureTooltip(tooltipWnd);
}

InventoryController::~InventoryController()
{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(InventoryItemClicked));
  flashWnd->RemoveFSListner(ConvertToString(InventoryItemToolTip));
}


void InventoryController::Update( int mouseX, int mouseY )
{
  if (!IsValid(inventory))
    return;
  
  int slotsCount = inventory->GetSlotCount();
  if(slotStatuses.size()<slotsCount)
    slotStatuses.resize(slotsCount, emptySlotStatus);

  for (int i = 0; i<slotsCount; i++)  
  {
    const NWorld::PFConsumable * consumable = inventory->GetConsumable(i);

    InventorySlotStatus status = GetItemStatus(consumable);

    //check target
    if (targetingConsumable == i)
    {
      status.slotState = ActionBarSlotState::Chosen;
    }

    if (status==slotStatuses[i])
      continue;

    if (slotStatuses[i] == emptySlotStatus)
    {
      flashInterface->SetInventoryItemIcon(i, consumable->GetDBDesc()->image->textureFileName.c_str());
      if ( consumable->GetActionBarIndex() != -2 )
        flashInterface->AddInventoryItemToActionBar(i);
    }
    

    slotStatuses[i] = status;

    if (status == emptySlotStatus)
    {
       // flash part won't implicitly reset cd label when setting empty icon, so do it explicitly
      flashInterface->SetInventoryItemState(i, emptySlotStatus.count, emptySlotStatus.slotState, emptySlotStatus.cooldown, emptySlotStatus.maxCooldown);
      flashInterface->SetInventoryItemIcon(i, "");
    }
    else
    {
      flashInterface->SetInventoryItemState(i, status.count, status.slotState, status.cooldown, status.maxCooldown);
    }
  }

  if (tooltip->IsVisible())
  {
    tooltip->SetLocation(mouseX , mouseY);
  }
}

InventoryController::InventorySlotStatus InventoryController::GetItemStatus( const NWorld::PFConsumable * consumable )
{
  if (!IsValid(consumable) || !IsValid(inventory))
    return emptySlotStatus;

  InventorySlotStatus slotStatus = emptySlotStatus;
  
  slotStatus.cooldown = consumable->GetAbility()->GetCurrentCooldown();
  slotStatus.maxCooldown =  consumable->GetAbility()->GetCooldown();
  slotStatus.count = consumable->GetQuantity();

  NWorld::PFAbilityData * ability = consumable->GetAbility();
  bool isForbidden = IsValid(ability)? ability->IsForbidded() || !ability->IsCastSelfLimitationPassed() || !ability->IsActive(): true;

  slotStatus.slotState = !isForbidden && inventory->CanUseConsumables() ? ActionBarSlotState::Active : ActionBarSlotState::Disabled;

  return slotStatus;
}

void InventoryController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  switch (ConvertToFSCommand(listenerID))
  {
  case InventoryItemClicked:
    {
      int index;
      sscanf_s(args,"%d", &index);

      if (!IsValid(eventHandler))
        return;
      int slotsCount = inventory->GetSlotCount();

      if (index>=0 && index<slotsCount)
        eventHandler->OnItemButtonClick(index);

      break;
    }
  case InventoryItemToolTip:
    {
      int show, index;
      sscanf_s(args,"%d %d",&show, &index);
      ShowConsumableDesc(index, show);
      break;
    }
  default:
    {
      NI_ALWAYS_ASSERT("something bad happened to the event listener")
    }
  }
}


void InventoryController::ShowConsumableDesc(int index, bool show)
{
  if (!IsValid(tooltip) || !IsValid(inventory))
    return;

  if (!show)
  {
    tooltip->Show(false);
    eventHandler->TargetZoneTooltip(0);
    return;
  }

 const NWorld::PFConsumable * pConsumable = inventory->GetConsumable(index);
 NI_VERIFY(IsValid(pConsumable), "invalid tooltip index", return);
 eventHandler->TargetZoneTooltip(pConsumable->GetAbility());

 if (!IsValid(pConsumable))
   return;

  NGameX::SConstUISubst subst;
  subst.Add( L"commonDescription", pConsumable->GetDBDesc()->commonDescription.GetText() );

  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init(pConsumable, pConsumable->GetDBDesc()->shortDescription.GetText(), &subst);

  wstring text;
  precompiledTooltip.MakeText(text);

  tooltip->SetText(text);
  tooltip->Show(true);
}

void InventoryController::DropTarget()
{
  targetingConsumable = NO_TARGET;
}


}//namespace NGameX

NI_DEFINE_REFCOUNT(NGameX::InventoryController)