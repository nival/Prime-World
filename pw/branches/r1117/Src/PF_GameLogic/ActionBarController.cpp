#include "StdAfx.h"
#include "ActionBarController.h"

#include "PFMaleHero.h"
#include "PFTalent.h"
#include "PFConsumable.h"
#include "DBTalent.h"
#include "DBConsumable.h"
#include "AdventureTooltip.h"
#include "FlashFSCommands.h"

#include "AdventureFlashInterface.h"
#include "../UI/FlashContainer2.h"

#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"
#include "UIEventHandler.h"

namespace 
{
  static const int SlotsCount = NDb::KnownEnum<NDb::ETalentSlot>::sizeOf;
  static const int LevelCount = NDb::KnownEnum<NDb::ETalentLevel>::sizeOf;
  static const SVector NO_TARGET = SVector(-1, -1);
  static bool lockActionBar = false;
  REGISTER_VAR( "lock_actionbar", lockActionBar, STORAGE_USER );
}


namespace NGameX
{

SlotStatus::SlotStatus()
  :  slotState (ActionBarSlotState::Active)
  ,  cooldown(0)
  ,  maxCooldown(0)
{}

bool SlotStatus::operator==( const SlotStatus &other ) const
{
  return memcmp( this, &other, sizeof(SlotStatus) ) == 0;
}



ActionBarController::ActionBarController( const NDb::DBUIData * _uiData, UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler, const NWorld::PFBaseMaleHero * _hero, UI::ImageLabel * _tooltipWindow ) :
uiData( _uiData ),
flashInterface(_flashInterface),
hero(_hero),
globalCooldown(100),
primeAmount(0),
zzGoldAmount(0),
eventHandler(_eventHandler),
flashWnd(flashContainer),
targetingPortal(false)
{
  using namespace FlashFSCommands;

  flashWnd->AddFSListner(ConvertToString(TalentActionToolTip), this);
  flashWnd->AddFSListner(ConvertToString(ItemActionToolTip), this);
  flashWnd->AddFSListner(ConvertToString(PortalClick), this);
  flashWnd->AddFSListner(ConvertToString(PortalTooltip), this);
  flashWnd->AddFSListner(ConvertToString(ActionBarLock), this);

  
  
  tooltip =  new NGameX::AdventureTooltip( _tooltipWindow );

  targetingTalent = NO_TARGET;
  int talentsCount = LevelCount * SlotsCount;
  slotStatuses.resize( talentsCount );
  slotActivated.resize( talentsCount, false);

  _flashInterface->LockActionBar(lockActionBar);
}



ActionBarController::~ActionBarController()
{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(TalentActionToolTip));
  flashWnd->RemoveFSListner(ConvertToString(ItemActionToolTip));
  flashWnd->RemoveFSListner(ConvertToString(PortalClick));
  flashWnd->RemoveFSListner(ConvertToString(PortalTooltip));
  flashWnd->RemoveFSListner(ConvertToString(ActionBarLock));


}


void ActionBarController::Update(int prime, int zzGold)
{
  if (!IsValid(flashInterface))
    return;
    
  RecryptImpl();
  
  //update talents
  for (int level = 0; level < LevelCount; ++level)
  {
    for (int slot = 0; slot < SlotsCount; ++slot)
    {
      NWorld::PFTalent * talent = hero->GetTalent(level, slot);
      
      if (!talent)
        continue;

      SlotStatus status = GetTalentStatus(talent);
      
      //check target
      if (targetingTalent == SVector(slot, level))
      {
        status.slotState = ActionBarSlotState::Chosen;
      }

      int slotIndex = slot + level*SlotsCount;

      bool isTalentActivated = talent->IsActivated();
      if (!slotActivated[slotIndex] && isTalentActivated)
      {
        slotActivated[slotIndex] = isTalentActivated;
      }
      else if (status == slotStatuses[slotIndex])
        continue;

      slotStatuses[slotIndex] = status;
      bool isAlternativeStateOn = talent->IsOn() && talent->IsMultiState() || talent->IsSecondState();
      flashInterface->SetTalentStatus(slot, level, status.slotState, status.cooldown, status.maxCooldown, isAlternativeStateOn);
    }
  }


   NWorld::PFTalent * portal = hero->GetPortal();
      
   if (portal)
   {
     SlotStatus status = GetTalentStatus(portal);

     //check target
     if (targetingPortal)
     {
       status.slotState = ActionBarSlotState::Chosen;
     }

      
     if ( !(status == portalStatus))
     {
       portalStatus = status;
       flashInterface->SetPortalStatus(status.slotState, status.cooldown, status.maxCooldown);
     }
   } 


  //global cooldown
  float curGlobalCooldown = hero->GetGlobalActionsCooldown();
  if (curGlobalCooldown!=globalCooldown)
  {
    globalCooldown = curGlobalCooldown;
    flashInterface->SetGlobalCooldown(globalCooldown, hero->GetGlobalCooldown());
  }

  //ZZGold
  if (prime!= primeAmount || zzGold!=zzGoldAmount)
  {
    primeAmount = prime;
    zzGoldAmount = zzGold;
    flashInterface->SetHeroDevelopmentParams(prime, zzGold);
  }

}

SlotStatus ActionBarController::GetTalentStatus( const NWorld::PFTalent * talent )
{
  SlotStatus status;

  if (!IsValid(talent))
    return status;

  status.cooldown = talent->GetCurrentCooldown();
  status.maxCooldown = talent->GetCooldown();

  if (talent->CanBeUsed())
  {
    if (talent->IsMultiState())
    {
      status.slotState = talent->IsOn()? ActionBarSlotState::ActiveSpecial : ActionBarSlotState::ActivetedSpecial;
    }
    else
    {
      status.slotState = ActionBarSlotState::Active;
    }
  }
  
  bool isEnoughMana = talent->IsEnoughMana() || ( talent->IsMultiState() && talent->IsOn() );
  
  // cast limitation has less priority than mana lack
  if ( !talent->IsCastSelfLimitationPassed() )
    status.slotState = ActionBarSlotState::Disabled;

  if (!isEnoughMana)
  {
    if ( talent->DoesSpendLifeInsteadEnergy() )
      status.slotState = ActionBarSlotState::NotEnoughLife;
    else
      status.slotState = ActionBarSlotState::NotEnoughMana;
  }

  if (talent->IsForbidded() || !talent->IsActive())
    status.slotState = ActionBarSlotState::Disabled;

  return status;
}

void ActionBarController::UseSlot( int slotIndex )
{
  if (!IsValid(flashInterface))
    return;

  flashInterface->UseSlot(slotIndex);
}

void ActionBarController::TalentWaitingForTarget( int column, int raw )
{
  DropTarget();
  //DebugTrace("Set target (col = %d, raw = %d)");
  targetingTalent.x = column;
  targetingTalent.y = raw;
}

void ActionBarController::DropTarget()
{
  //DebugTrace("drop target");
  targetingTalent = NO_TARGET;
  targetingPortal = false;
}

//TalentActionToolTip
void ActionBarController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  if (!IsValid(tooltip))
    return;

  int show = 0;

  switch (ConvertToFSCommand(listenerID))
  {
  case TalentActionToolTip:
    {
      int column, raw;

      sscanf_s(args,"%d %d %d", &show, &column, &raw);

      if (show)
        ShowTalentTooltip(column, raw);

      break;
    }
  case ItemActionToolTip:
    {
      int index;
      sscanf_s(args,"%d %d",&show, &index);
      if (show)
        ShowItemTooltip(index);
      break;
    }

  case PortalTooltip:
    {
      sscanf_s(args,"%d",&show);
      if (show)
        ShowPortalTooltip();
      break;
    }

  case PortalClick:
    {
      eventHandler->OnPortalClick();
      return;
    }

  case ActionBarLock:
    {
      int lock;
      sscanf_s(args,"%d", &lock);
      lockActionBar = lock;
      flashInterface->LockActionBar(lockActionBar);
      return;
    }
  }

  //NOTE: этот код отрабатывает только в случае тултипов тк в последних двух случаях стоит return
  tooltip->Show(show);
  if (!show)
    eventHandler->TargetZoneTooltip(0);
}

void ActionBarController::ShowTalentTooltip( int column, int raw )
{
  ShowTalentTooltip(hero->GetTalent(raw, column));
}

void ActionBarController::ShowPortalTooltip()
{
  ShowTalentTooltip(hero->GetPortal());
}


void ActionBarController::ShowTalentTooltip( NWorld::PFTalent * pTalent )
{
  if (!IsValid(pTalent))
    return;

  
  typedef NMeta::MakeTypeList<NWorld::PFTalent, NWorld::PFBaseMaleHero>::Result myList;
  UnitInfoNameMap<myList> myMap;

  Field<NWorld::PFTalent>(myMap).pObject       = pTalent;
  Field<NWorld::PFBaseMaleHero>(myMap).pObject = hero;

  NI_VERIFY(pTalent->GetTalentDesc(), "Wrong DB ptr", return);

  SConstUISubst subst;
  subst.Add( L"commonDescription", pTalent->GetTalentDesc()->commonDescription.GetText() );
  PrecompiledTooltip pt;
  bool useShortDesc = pTalent->GetTalentDesc()->shortDescription.GetText().size();
  wstring const & talentDesc = useShortDesc ? pTalent->GetTalentDesc()->shortDescription.GetText() :
    pTalent->GetTalentDesc()->description.GetText();

  pt.Init( &myMap, talentDesc, &subst );

  wstring newText;
  pt.MakeText(newText);

  tooltip->SetText( newText, uiData->tooltipDownScaleLimit );

  eventHandler->TargetZoneTooltip(pTalent);
}

void ActionBarController::ShowItemTooltip(int itemIndex)
{
  const NWorld::PFConsumable * pConsumable = hero->GetConsumable(itemIndex);

  if (!IsValid(pConsumable))
    return;

  SConstUISubst subst;
  subst.Add( L"commonDescription", pConsumable->GetDBDesc()->commonDescription.GetText() );

  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init(pConsumable, pConsumable->GetDBDesc()->shortDescription.GetText(), &subst);

  wstring text;
  precompiledTooltip.MakeText(text);

  tooltip->SetText( text, uiData->tooltipDownScaleLimit );

  eventHandler->TargetZoneTooltip(pConsumable->GetAbility());
}



}

NI_DEFINE_REFCOUNT( NGameX::ActionBarController )


