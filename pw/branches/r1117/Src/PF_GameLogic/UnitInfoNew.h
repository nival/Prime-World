#pragma once

#include "AdventureFlashInterface.h"
#include "../UI/FSCommandListner.h"

namespace UI
{
  class FlashContainer2;
}

namespace NWorld
{
  class PFBaseHero;
  class PFBaseUnit;
}

namespace NGameX
{

class HeroRankCalculator;
_interface IUIEventHandler;

class HeroInfoNew : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( HeroInfoNew, BaseObjectST );

public:
  HeroInfoNew( AdventureFlashInterface* _flashInterface, NWorld::PFBaseHero const* _hero, bool _isEnemy, HeroRankCalculator * heroRankCalculator, bool isPremium, string & flagIcon, wstring & flagTooltip);
  void Update();

private:
  ConstPtr<NWorld::PFBaseHero> hero;
  Weak<AdventureFlashInterface> flashInterface;
  bool isEnemy;
  bool isCameraLocked;

  HeroInfoParams currentParams;
};


class SelectionInfo : public BaseObjectST, public UI::IFSCommandListner
{
  NI_DECLARE_REFCOUNT_CLASS_2( SelectionInfo, BaseObjectST, UI::IFSCommandListner );

public:
  SelectionInfo( UI::FlashContainer2* _wnd, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler);

  void SetUnit(NWorld::PFBaseUnit const* _unit, bool _isEnemy);
  NWorld::PFBaseUnit const * GetUnit() { return unit;}
  void Update();

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:

  ConstPtr<NWorld::PFBaseUnit>  unit;
  ConstPtr<NWorld::PFBaseHero>  unitAsHero;
  Weak<AdventureFlashInterface>      flashInterface;
  Weak<IUIEventHandler>         eventHandler;
  bool isEnemy;

  HeroInfoParams currentParams;
};

}
