#pragma once

#include "../UI/FSCommandListner.h"
#include "ActionBarController.h"

namespace NWorld        { class PFTalent; }
namespace TalentUIState { enum  ETalentUIState; }
namespace NWorld        { class PFBaseMaleHero; }

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}


namespace NGameX
{
class AdventureFlashInterface;
_interface IUIEventHandler;
class      AdventureTooltip;

class TalentPanelNew : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( TalentPanelNew, UI::IFSCommandListner, BaseObjectST );

public:
  TalentPanelNew( const NDb::DBUIData * _uiData, UI::FlashContainer2 * flashContainer, AdventureFlashInterface * _flashInterface,  IUIEventHandler * _eventHandler, UI::ImageLabel * _tooltipWindow );
  void SetHero( NWorld::PFBaseMaleHero * pMale );
      
  void Update(int mouseX, int mouseY);

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

 
private:

  void ProcessTalentClick( const char* args );
  void ProcessTalentTooltip( const char* args );

  int GetTalentsCountX() const;
  int GetTalentsCountY() const;

  TalentUIState::ETalentUIState GetUITalentState(int column, int row);

  //tooltips
  void ShowTooltip( int column, int row, bool show );
  void UpdateTooltipText(int column, int row);

  NDb::Ptr<NDb::DBUIData>       uiData;

  CObj<AdventureTooltip>        tooltip;
 
  ConstPtr<NWorld::PFBaseMaleHero> hero;
    
  Weak<AdventureFlashInterface> flashInterface;
  Weak<UI::FlashContainer2>     flashWindow;
  Weak<IUIEventHandler>         eventHandler;
  vector<TalentUIState::ETalentUIState> talentStates;
};

} //namespace NGameX
