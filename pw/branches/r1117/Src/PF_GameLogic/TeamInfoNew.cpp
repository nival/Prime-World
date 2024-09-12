#include "stdafx.h"
#include "TeamInfoNew.h"
#include "UnitInfoNew.h"
#include "PFHero.h"

#include "DBStats.h"

#include "AdventureFlashInterface.h"
#include "../UI/FlashContainer2.h"
#include "UIEventHandler.h"
#include "FlashFSCommands.h"


namespace NGameX
{
  TeamInfoNew::TeamInfoNew( UI::FlashContainer2* _wnd, AdventureFlashInterface * _flashInterface, NWorld::PFBaseHero const *_ourHero, IUIEventHandler * _eventHandler, const NDb::DBUIData * _uiData, HeroRankCalculator * _heroRanksCalculator)
    : ourHero(_ourHero)
    , flashInterface(_flashInterface)
    , eventHandler(_eventHandler)
    , flashWnd(_wnd)
    , heroRankCalculator(_heroRanksCalculator)
    , uiData(_uiData)
  {
    NI_VERIFY(IsValid(ourHero) && IsValid(flashInterface), "ivalid ctor params", return);
    heroInfos.reserve(10);
    ///тут передаетс€ фракци€ только дл€ того чтобы себ€ впихнуть первым в статистику с нужной стороны
    flashInterface->SetOurHeroIdententity(ourHero->GetPlayerId(), ourHero->GetFaction(), ourHero->GetBaseAttackDamageType(), ourHero->GetLeagueIndex(), ourHero->GetOwnLeaguePlace(), ourHero->GetLeaguePlaces());

    if (uiData)
    {
      int size = uiData->forceColors.forceColors.size();

      vector<int> force(size);
      vector<uint> colors(size);

      for (int i = 0; i< size; i++)
      {
        force[i] = uiData->forceColors.forceColors[i].force;
        colors[i] = uiData->forceColors.forceColors[i].color.Dummy;
      }
      flashInterface->SetForceColorTable(force, colors);
    }
    using namespace FlashFSCommands;

    flashWnd->AddFSListner(ConvertToString(HeroClicked), this);
    flashWnd->AddFSListner(ConvertToString(HeroDoubleClicked), this);
    flashWnd->AddFSListner(ConvertToString(LostFocusFromAvatar), this);
  }

  TeamInfoNew::~TeamInfoNew()
  {
    using namespace FlashFSCommands;

    if (!IsValid(flashWnd))
      return;

    flashWnd->RemoveFSListner(ConvertToString(HeroClicked));
    flashWnd->RemoveFSListner(ConvertToString(HeroDoubleClicked));
    flashWnd->RemoveFSListner(ConvertToString(LostFocusFromAvatar));

  }
   

  void TeamInfoNew::AddHero( NWorld::PFBaseHero const *hero, bool isPremium )
  {
    NI_VERIFY(IsValid(hero) && IsValid(ourHero), "invalid hero to show", return);

    string  flagIcon;
    wstring flagTooltip;

    if(!hero->GetPlayer()->IsBot())
    {
      if( hero->GetFlagId().empty() && uiData->countryFlags.size()>0)
      {
        flagIcon = uiData->countryFlags[0].icon->textureFileName;
        flagTooltip = uiData ->countryFlags[0].tooltip.GetText();
      }
      else
      {
        bool founded = false;
       
        for (vector<NDb::CountryFlag>::const_iterator it = uiData->countryFlags.begin(); it != uiData->countryFlags.end(); ++it )
        {
          if (it->id == hero->GetFlagId() )
          {
            flagIcon = it->icon->textureFileName;
            flagTooltip = it->tooltip.GetText();
            founded = true;
          }
        }
        if (!founded)
        {
          for (vector<NDb::Ptr<NDb::CustomFlag>>::const_iterator it = uiData->customFlags.begin(); it != uiData->customFlags.end(); ++it )
          {
            if ((*it)->id == hero->GetFlagId() )
            {
              flagIcon = (*it)->icon->textureFileName;
              flagTooltip = (*it)->tooltip.GetText();
              founded = true;
            }
          }
        }
        if (!founded)
        {
          for (vector<NDb::Ptr<NDb::CustomFlag>>::const_iterator it = uiData->adminFlags.begin(); it != uiData->adminFlags.end(); ++it )
          {
            if ((*it)->id == hero->GetFlagId() )
            {
              flagIcon = (*it)->icon->textureFileName;
              flagTooltip = (*it)->tooltip.GetText();
              founded = true;
            }
          }
        }
      }
    }
    
   if (hero->GetPlayer()->IsBot())
   {
     if(hero->GetOriginalFaction()==NDb::FACTION_FREEZE)
     {
       flagIcon= uiData->botFlags.doctDefaultFlag.icon->textureFileName;
       flagTooltip=uiData->botFlags.doctDefaultFlag.tooltip.GetText();
     }
     else
     {
       flagIcon = uiData->botFlags.adornianDefaultFlag.icon->textureFileName;
       flagTooltip=uiData->botFlags.adornianDefaultFlag.tooltip.GetText();
     }
   }

    heroInfos.push_back(new HeroInfoNew(flashInterface, hero, hero->GetFaction() != ourHero->GetFaction(), heroRankCalculator, isPremium,flagIcon,flagTooltip));
    heroes[hero->GetPlayerId()] = hero;
  }

  void TeamInfoNew::ShowHeroPortrait( NWorld::PFBaseHero const *hero )
  {
    flashInterface->ShowHeroPortrait( hero->GetPlayerId(), hero->GetFaction() != ourHero->GetFaction() );
  }

  void TeamInfoNew::Update()
  {
    for (int i= 0; i<heroInfos.size(); i++)
      heroInfos[i]->Update();
  }

  void TeamInfoNew::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
  {
    if (!args || ! _wnd)
      return;

     using namespace FlashFSCommands;

    if (Equals(LostFocusFromAvatar, listenerID))
    {
      eventHandler->CancelObservingObject();
      return;
    }

    int heroID = 0;

    sscanf_s(args,"%d", &heroID);

    HeroesById::iterator heroIter = heroes.find(heroID);
    if (heroIter == heroes.end())
      return;

    NWorld::PFBaseHero * hero = heroIter->second;

    if (Equals(HeroClicked, listenerID))
      eventHandler->OnUnitAvatarMouseClick(hero, UI::EMButton::Left);
    else if (Equals(HeroDoubleClicked, listenerID))
      eventHandler->OnUnitAvatarMouseDblClick(hero, UI::EMButton::Left);
  }


}

NI_DEFINE_REFCOUNT(NGameX::TeamInfoNew);
