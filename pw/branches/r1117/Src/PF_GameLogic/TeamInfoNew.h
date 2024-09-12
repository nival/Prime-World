#pragma once

#include "../UI/FSCommandListner.h"

namespace UI
{
  class FlashContainer2;
}

namespace NWorld
{
  class PFBaseHero;
}

namespace NDb
{
  struct DBUIData;
}


namespace NGameX
{

class AdventureFlashInterface;
class HeroInfoNew;
class HeroRankCalculator;
_interface IUIEventHandler;


class TeamInfoNew : public BaseObjectST, public UI::IFSCommandListner
{
  NI_DECLARE_REFCOUNT_CLASS_2( TeamInfoNew, BaseObjectST, UI::IFSCommandListner );

public :
  TeamInfoNew(UI::FlashContainer2* _wnd, AdventureFlashInterface * _flashInterface, NWorld::PFBaseHero const *_ourHero, IUIEventHandler * _eventHandler, const NDb::DBUIData * uiData, HeroRankCalculator * _heroRanksCalculator);
  ~TeamInfoNew();

  void AddHero( NWorld::PFBaseHero const *hero, bool isPremium );
  void ShowHeroPortrait( NWorld::PFBaseHero const *hero );
  void Update();
  const NWorld::PFBaseHero* GetOurHero() const { return ourHero; }

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:
  typedef vector<Strong<HeroInfoNew>> HeroInfos;
  HeroInfos heroInfos;

  Weak<UI::FlashContainer2> flashWnd;

  ConstPtr<NWorld::PFBaseHero>  ourHero;
  Weak<AdventureFlashInterface>          flashInterface;
  Weak<IUIEventHandler>         eventHandler;
  Strong<HeroRankCalculator>    heroRankCalculator;

  
  typedef hash_map<int, ConstPtr<NWorld::PFBaseHero>> HeroesById;
  HeroesById heroes;
  NDb::Ptr<NDb::DBUIData>       uiData;
};

}
