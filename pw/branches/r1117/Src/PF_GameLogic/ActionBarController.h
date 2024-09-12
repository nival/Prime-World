#pragma once

#include "../UI/FSCommandListner.h"
#include "System/StarForce/HiddenVars.h"

namespace ActionBarSlotState  {  enum EActionBarSlotState; }

namespace UI                  
{  
  class FlashContainer2;
  class ImageLabel;

}

namespace NWorld              
{  
  class PFBaseMaleHero;
  class PFTalent;
}

namespace NGameX
{

class AdventureFlashInterface;
class AdventureTooltip;
_interface IUIEventHandler;

struct SlotStatus
{
  SlotStatus();
  ActionBarSlotState::EActionBarSlotState slotState;
  float cooldown;
  float maxCooldown;
  bool operator==(const SlotStatus &other) const;
};

class ActionBarController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ActionBarController, UI::IFSCommandListner, BaseObjectST );

public:
  ActionBarController( const NDb::DBUIData * _uiData, UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler, const NWorld::PFBaseMaleHero * _hero, UI::ImageLabel * _tooltipWindow );
  ~ActionBarController();

  void Update(int prime, int zzGold);
  void UseSlot(int slotIndex);

  void TalentWaitingForTarget(int column, int raw);
  SVector GetTargetingTalent() const { return targetingTalent; }
  void SetPortalWaiting() { DropTarget(); targetingPortal = true;}
  void DropTarget();

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  static SlotStatus GetTalentStatus(const NWorld::PFTalent * talent);

private:
  void ShowTalentTooltip(int column, int raw);

  void ShowTalentTooltip( NWorld::PFTalent * pTalent );
  void ShowItemTooltip(int itemIndex);


  NDb::Ptr<NDb::DBUIData> uiData;

  Weak<UI::FlashContainer2> flashWnd;

  SlotStatus portalStatus;

  vector<SlotStatus> slotStatuses;
  vector<bool> slotActivated;
  ConstPtr<NWorld::PFBaseMaleHero> hero;
  Weak<AdventureFlashInterface> flashInterface;
  Weak<IUIEventHandler> eventHandler;
   
  //tooltips
  CObj<NGameX::AdventureTooltip> tooltip;

  SVector targetingTalent;

  bool targetingPortal;

  float globalCooldown;
  Protection::HiddenVar<int, 27>::T primeAmount;
  Protection::HiddenVar<int, 28>::T zzGoldAmount;
  
private:
  void RecryptImpl()
  {
    Recrypt( primeAmount );
    Recrypt( zzGoldAmount );
  }
  void ShowPortalTooltip();
};
}

