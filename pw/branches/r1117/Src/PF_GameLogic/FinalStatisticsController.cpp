#include "StdAfx.h"
#include "FinalStatisticsController.h"

#include "HeroScoreWrapper.h"
#include "HeroTitleCalculator.h"
#include "AdventureFlashInterface.h"
#include "AdventureScreen.h"
#include "AdventureTooltip.h"
#include "FlashFSCommands.h"

#include "PFWorld.h"
#include "PFHero.h"
#include "PFPlayer.h"
#include "PFHeroStatistics.h"
#include "PFAchievement.h"

#include "../UI/FlashContainer2.h"

#include "../System/InlineProfiler.h"
#include "PrecompiledTooltips.h"


namespace
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct ScoreNameMap : public NNameMap::Map
	{
		NAMEMAP_DECLARE;
	public:
		ScoreNameMap (float _score, const wstring & _name) : score(_score), achievName(_name) {}
    const nstl::wstring &  GetName() const { return achievName;} 
	private:
		float score;
    nstl::wstring achievName;
	};

	NAMEMAP_BEGIN(ScoreNameMap)
		NAMEMAP_VAR_RO(score);
    //NAMEMAP_VAR_RO(achievName);
    NAMEMAP_FUNC_RO(name, & ScoreNameMap::GetName )
	NAMEMAP_END
}




namespace NGameX

{

  FinalStatisticsController::FinalStatisticsController(UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, NWorld::PFWorld * _world, IUIEventHandler * _eventHandler )
: world(_world)
, flashInterface(_flashInterface)
, eventHandler(_eventHandler)
#ifndef _SHIPPING
, setCheatTitle( false )
#endif
{
  using namespace FlashFSCommands;

  flashContainer->AddFSListner(ConvertToString(TitleTooltip), this);
  flashContainer->AddFSListner(ConvertToString(ExploitTooltip), this);
  flashContainer->AddFSListner(ConvertToString(ShareFinalStatistics), this);
  flashContainer->AddFSListner(ConvertToString(PlaySameTeam), this);

  tooltip = new AdventureTooltip(tooltipWnd);
}

void FinalStatisticsController::Update( int mouseX, int mouseY )
{
  if (tooltip->IsVisible())
  {
    tooltip->SetLocation(mouseX , mouseY);
  }
}

void FinalStatisticsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  wstring text;

  int show, index;

  sscanf_s(args,"%d %d",&show, &index);

  switch (ConvertToFSCommand(listenerID))
  {
  case TitleTooltip:
    {
      if (titleTooltips.find(index) != titleTooltips.end())
        text = titleTooltips[index];

      break;
    }
  case ExploitTooltip:
    {
      if (achievTooltips.find(index) != achievTooltips.end())
        text = achievTooltips[index];
   
      break;
    }
  case ShareFinalStatistics:
    {
      if (eventHandler)
        eventHandler->ShareFinalStatistics();
      return;
    }
  case PlaySameTeam:
    {
      unsigned agreed;

      const int argsRead = sscanf_s(args, "%u", &agreed);

      if (argsRead < 1)
        agreed = 0U;

      if (eventHandler)
        eventHandler->PlaySameTeam(agreed != 0U);

      return;
    }
  default:
    {
      NI_ALWAYS_ASSERT("something bad happened to the event listener")
    }
  }

  if (!show)
  {
    tooltip->Show(false);
    return;
  }

  tooltip->SetText(text);
  tooltip->Show(true);
}

#pragma code_seg(push, "~")

void FinalStatisticsController::FillFinalData( HeroTitleCalculator const* heroTitleCalculator )
{
  STARFORCE_STOPWATCH();

  NI_PROFILE_FUNCTION

    if (!IsValid(world) || !IsValid(flashInterface))
      return;

  scoring = world->GetStatistics()->GetScoringTable();

  CObj<HeroScoreWrapper> heroScore = new HeroScoreWrapper();

  for (int i = 0; i < world->GetPlayersCount(); ++i)
  {
    const NWorld::PFPlayer * player = world->GetPlayer(i);
    if (!IsValid(player))
      continue;

    const NWorld::PFBaseHero * hero = player->GetHero();
    if (!IsValid(hero))
      continue;

    int playerID    = player->GetPlayerID();

    int maxPriority = 0;
    // find max priority
    heroScore->SetHero(player->GetHero());
    for (int i=0; i<NDb::KnownEnum<NDb::EScoreType>::SizeOf();i++)
    {
      NDb::EScoreType scoreType = (NDb::EScoreType)i;
      int score = heroScore->GetHeroScore(scoreType);
      if (score<=0)
        continue;

      const NDb::ScoreDescription & scoreDesc = scoring->scoreDescriptions[scoreType];
      if (scoreDesc.outputPriority > maxPriority)
      {
        maxPriority = scoreDesc.outputPriority;
      }
    }

    //score part
    for (int priority = maxPriority; priority >= 0; priority--)
    {    
      heroScore->SetHero(player->GetHero());
      for (int i=0; i<NDb::KnownEnum<NDb::EScoreType>::SizeOf();i++)
      {
        NDb::EScoreType scoreType = (NDb::EScoreType)i;
        int score = heroScore->GetHeroScore(scoreType);
        if (score<=0)
          continue;

        const NDb::ScoreDescription & scoreDesc = scoring->scoreDescriptions[scoreType];
        if (scoreDesc.outputPriority == priority)
        {
          const char * scoreImagePath = IsValid(scoreDesc.icon)? scoreDesc.icon->textureFileName.c_str(): "";
          flashInterface->AddHeroResults(playerID, scoreImagePath, score, scoreDesc.name.GetText());
        }
      }
    }

    //title part
    NDb::EHeroTitle heroTitle = heroTitleCalculator->GetHeroTitle(hero);
#ifndef _SHIPPING
    if ( setCheatTitle )
      heroTitle = cheatTitle;
#endif
    const NDb::HeroTitle& titleDesc = scoring->heroTitles[heroTitle];
    const wstring& titleName = hero->IsMale()? titleDesc.maleName.GetText(): titleDesc.femaleName.GetText();
    const char * titleImagePath = IsValid(titleDesc.image)? titleDesc.image->textureFileName.c_str(): "";

    wstring text;
    ScoreNameMap scoreMap (titleDesc.score, titleName);
    NGameX::PrecompiledTooltip preTooltip;
    preTooltip.Init( &scoreMap, titleDesc.tooltip.GetText());
    preTooltip.MakeText( text );

    titleTooltips[playerID] = text;

    flashInterface->SetFinalHeroTitle(playerID, titleName, titleImagePath, playerID);

    //achiev part
    struct AchievementCounter
    {
      AchievementCounter & operator=( const AchievementCounter & ) {return *this;}

      AchievementCounter(int _heroID, AdventureFlashInterface * _flashInterface,  map<int,wstring>  &  _achievTooltips)
        : heroID(_heroID)
        , achievTooltips(_achievTooltips)
        , flashInterface(_flashInterface)
        , counter(0)
      {}


      void operator()(const NWorld::PFAchievBase* p)
      { 
        if (!IsValid(p))
          return;

        NDb::Ptr<NDb::AchievBase> achievDB = p->GetDBBase();

        if (p->count != 0 )
        {
          wstring text;
          ScoreNameMap scoreMap (p->score, achievDB->name.GetText());
          NGameX::PrecompiledTooltip tooltip;
          tooltip.Init( &scoreMap, p->GetTooltip().GetText() );
          tooltip.MakeText( text );

          int compositeTooltipId = counter | (heroID << 16);
          achievTooltips[compositeTooltipId] = text;

          const NDb::Ptr<NDb::Texture>& image = p->GetImage();
          const char* achievImagePath = IsValid(image)?  image->textureFileName.c_str(): "";
          flashInterface->AddHeroExploit(heroID, achievImagePath, compositeTooltipId);

          counter++;
        }
      }

      map<int,wstring>  &  achievTooltips;
      int heroID;
      bool fillTooltips;
      Weak<AdventureFlashInterface>     flashInterface;
      int counter;

    } achievementCounter(playerID, flashInterface, achievTooltips);

    hero->GetHeroStatistics()->ForAllAchievements(achievementCounter);

  }
}

#pragma code_seg(pop)

}
