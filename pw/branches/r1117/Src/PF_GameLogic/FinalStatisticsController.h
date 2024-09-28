#pragma once

#include "../UI/FSCommandListner.h"
#include "System/StarForce/StarForce.h"

namespace NWorld
{
  class PFWorld;
}

namespace NDb
{
  struct ScoringTable;
}

namespace NGameX
{
  class HeroTitleCalculator;
  class AdventureTooltip;
}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}

namespace NGameX
{
class AdventureFlashInterface;
_interface IUIEventHandler;

class FinalStatisticsController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( FinalStatisticsController, UI::IFSCommandListner, BaseObjectST );

public:
  FinalStatisticsController(UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, NWorld::PFWorld * _world, IUIEventHandler * eventHandler);

  STARFORCE_EXPORT void FillFinalData( HeroTitleCalculator const* heroTitleCalculator );

  void Update(int mouseX, int mouseY);

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

#ifndef _SHIPPING
  void ForceSetTitle( NDb::EHeroTitle title ) { setCheatTitle = true; cheatTitle = title; }
  bool setCheatTitle;
  NDb::EHeroTitle cheatTitle;
#endif  

private:

  Weak<AdventureFlashInterface>          flashInterface;
  ConstPtr<NWorld::PFWorld>     world;
  Weak<IUIEventHandler>   eventHandler;

  CObj<AdventureTooltip>        tooltip;

  map<int,wstring>    achievTooltips;
  map<int,wstring>    titleTooltips;

  NDb::Ptr<NDb::ScoringTable> scoring;
};

} //namespace NGameX