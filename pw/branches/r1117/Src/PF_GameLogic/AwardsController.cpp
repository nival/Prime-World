#include "StdAfx.h"
#include "AwardsController.h"

#include "../UI/FlashContainer2.h"
#include "../UI/ImageLabel.h"
#include "../UI/Root.h"

#include "AdventureFlashInterface.h"
#include "AdventureTooltip.h"
#include "FlashFSCommands.h"
#include "PFWorld.h"

#include "DBTalent.h"
#include "DBServer.h"
#include "DBHeroRanks.h"
#include "DBResources.h"

#include "PFResourcesCollectionClient.h"
#include "HeroRankCalculator.h"

#include "PlayerData.h"
#include "PrecompiledTooltips.h"


namespace
{
int GetOrder(roll::EAwardType::Enum  type)
{
	switch (type)
	{
	case roll::EAwardType::Talent: return 0;
  case roll::EAwardType::MarketingEvent: return 1;
 
	case roll::EAwardType::Resource1: return 2;
	case roll::EAwardType::Resource2: return 3;
	case roll::EAwardType::Resource3: return 4;

	case roll::EAwardType::Silver: return 5;
	case roll::EAwardType::Pearl: return 6;
  
  case roll::EAwardType::ClanWarsPlayerRating: return 7;
  case roll::EAwardType::ClanWarsClanRating: return 8;

  case roll::EAwardType::CustomCurrency: return 9;
	}  

	return 100500;
}
}


namespace NGameX
{

AwardsController::AwardsController( UI::FlashContainer2* flashContainer, NDb::AILogicParameters const& _dbLogic, const NDb::DBUIData * _uiData,UI::ImageLabel * tooltipWnd
                                   , AdventureFlashInterface * _flashInterface, const NWorld::PFResourcesCollection * _resources
                                   , NDb::EFaction _faction, int _experience, int _rating, HeroRankCalculator  *_rankCalculator, const PlayerDataManager* playersData_ )
                                   : flashWnd(flashContainer)
                                   , dbLogic(_dbLogic)
                                   , uiData(_uiData)
                                   , flashInterface(_flashInterface)
                                   , resources(_resources)
                                   , faction(_faction)
                                   , experience(_experience)
                                   , rating(_rating)
																	 , rankCalculator (_rankCalculator)
																	 , playersData(playersData_)

{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->AddFSListner(ConvertToString(AwardTooltip), this);

  tooltip = new AdventureTooltip(tooltipWnd);
}



AwardsController::~AwardsController()
{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(AwardTooltip));
}



void AwardsController::Update( int mouseX, int mouseY )
{
  if (awards.empty())
    return;

  if (tooltip->IsVisible())
  {
    tooltip->SetLocation(mouseX , mouseY);
  }
}

void AwardsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  FlashFSCommands::EFlashFSCommands command = ConvertToFSCommand(listenerID);

  if (command!= AwardTooltip)
  {
    NI_ALWAYS_ASSERT("something bad happened to the AwardsController event listener")
    return;
  }

  int show, index;
  sscanf_s(args,"%d %d",&show, &index);

  if (index <0 || index>=awards.size())
  {
    NI_ALWAYS_ASSERT("bad index in AwardTooltip");
    return;
  }

	wstring tooltipText = awards[index].tooltip;

	if (awards[index].giverUser && IsValid(playersData))
	{
		const PlayerData & playerData = playersData->GetPlayerDataByUser(awards[index].giverUser );

		PrecompiledTooltip pt;
		pt.Init( &playerData, uiData->premiumVisualInfo.premiumTooltipAddition.GetText() );

		wstring newText;
		pt.MakeText(newText);
		tooltipText += newText;
	}
	

  tooltip->SetText( tooltipText );
  tooltip->Show(show && tooltipText.size()>0);
}

void AwardsController::AwardUser( const nstl::vector<AwardData> & _awards )
{
  if (!IsValid(resources) || !IsValid(uiData) || !flashInterface)
    return;
#ifndef _SHIPPING
  awards.clear();
#endif
  NI_VERIFY(awards.size() == 0, "Awards already received!", return;);

  awards.reserve( _awards.size() );

  int earnedExp = 0;

	vector<Award> resourceAwards;


  for ( int i=0; i < _awards.size(); i++ )
  {
    const AwardData  & sAward = _awards[i];

    if ( !sAward.isOwnedByPlayer )
      continue;

    Award award;
    award.count = sAward.count;
    award.vendorConst = sAward.vendorCost;

		award.isTasty = sAward.isTasty;
		award.type = sAward.type;
		award.giverUser = sAward.giverUser;

    switch (sAward.type)
    {
    case roll::EAwardType::Talent:
      {
        NDb::Ptr<NDb::Talent> dbTalent;
#ifndef _SHIPPING
        if (!sAward.persistentId.empty())
          dbTalent = resources->FindTalentById(sAward.persistentId);
        else
#endif
        dbTalent = resources->FindTalentById(sAward.id);

        NI_VERIFY(dbTalent, "invalid talent for awards", continue);

        DebugTrace("recieved award (type=talent count=%d owned=%d id=%s giver = %d)", award.count, sAward.isOwnedByPlayer, dbTalent->persistentId.c_str(), award.giverUser );
        if(!dbTalent->compiledDescriptionA.GetText().empty() && dbTalent->compiledDescriptionB.GetText().empty())
          award.tooltip = dbTalent->compiledDescriptionA.GetText();
        else
          award.tooltip = faction == NDb::FACTION_BURN? dbTalent->compiledDescriptionB.GetText(): dbTalent->compiledDescriptionA.GetText();
        award.image = dbTalent->image? dbTalent->image->textureFileName: "";
				awards.push_back(award);
        break;
      }
    case roll::EAwardType::MarketingEvent:
      {
        NDb::Ptr<NDb::MarketingEventRollItem> dbMarketingItem = resources->FindMarketingById(sAward.id);

        NI_VERIFY(dbMarketingItem, "invalid marketingItem for awards", continue);

        DebugTrace("recieved award (type=marketingItem count=%d owned=%d id=%s giver = %d)", award.count, sAward.isOwnedByPlayer, dbMarketingItem->persistentId.c_str(), award.giverUser );

        wstring buffer;
        UI::SubstituteText( buffer, dbMarketingItem->tooltip.GetText().c_str() );

        award.tooltip = buffer;
        award.image = dbMarketingItem->image? dbMarketingItem->image->textureFileName: "";
        awards.push_back(award);
        break;
      }
    case roll::EAwardType::Experience:
      {
        earnedExp += sAward.count;
        DebugTrace("recieved award (type=experience count=%d)", sAward.count );
        break;
      }
		case roll::EAwardType::HeroRating:
			{
				const NDb::Rank & rank = rankCalculator->GetRank(rating + sAward.count);
				flashInterface->AwardDeltaRaiting(sAward.count,  rankCalculator->GetRankIcon(faction, rank), rankCalculator->GetRankName(faction, rank) );
				DebugTrace("recieved award (type=raiting count=%d)", sAward.count);
				break;
			}
    case roll::EAwardType::Silver:
    case roll::EAwardType::Pearl:
    case roll::EAwardType::Resource1:
    case roll::EAwardType::Resource2:
    case roll::EAwardType::Resource3:
    case roll::EAwardType::RedPearl:
      {
        const NDb::EResourceType resourceType = GetResourceTypeByType( sAward.type );
        
        DebugTrace("recieved award (type=%s count=%d owned=%d, isTasty %b)", NDb::EnumToString( resourceType ), award.count, sAward.isOwnedByPlayer, award.isTasty );
        FillResourceAward(award, resourceType, faction);
        resourceAwards.push_back(award);
        break;
      }
    case roll::EAwardType::ClanWarsClanRating:
    case roll::EAwardType::ClanWarsPlayerRating:
      {
        const NDb::EClanWarsResourceType resourceType = GetCWResourceTypeByAwardType( sAward.type );
        const NDb::ResourceDescription & resource = GetResource<NDb::EClanWarsResourceType>(uiData->clanWarsResourcesDescriptions, resourceType);

        DebugTrace("recieved ClanWars award (type=%s count=%d owned=%d, isTasty %b)", NDb::EnumToString( resourceType ), award.count, sAward.isOwnedByPlayer, award.isTasty );
        FillResourceAward(award, resource, faction);
        awards.push_back(award);
        break;
      }
    case roll::EAwardType::CustomCurrency:
      {
        DebugTrace("recieved award (type=custom currency id=%s count=%d)", sAward.customCurrencyId, sAward.count);
        NI_VERIFY(IsValid(uiData->currencies), "uiData->currencies is null", break);
        const nstl::vector<NDb::CurrencyDescription> & cList = uiData->currencies->CurrencyList;
        bool foundCurrency = false;
        for (int i = 0; i < cList.size(); ++i)
        {
          if (cList[i].Id == sAward.customCurrencyId)
          {
            award.image = cList[i].Icon->textureFileName;
            award.tooltip = cList[i].Description.GetText();
            resourceAwards.push_back(award);
            foundCurrency = true;
            break;
          }
        }
        NI_VERIFY(foundCurrency, NStr::StrFmt("unknown custom currency: %s", sAward.customCurrencyId), break);
      }
      break;
    default:
      {
        //Skip all other types
        continue;
      }
    }
  }

	vector<Award> filteredAwards;

	for(int i = 0; i<resourceAwards.size(); i++)
	{
		int filteredIndex = -1;
		for(int j = 0; j<filteredAwards.size(); j++)
		{
			//сравниваем по картинке
			if (resourceAwards[i].image == filteredAwards[j].image)
			{
				filteredIndex = j;
				break;
			}
		}
		
		//не нашли уже такой элемент
		if (filteredIndex == -1)
		{
			filteredAwards.push_back(resourceAwards[i]);
			continue;
		}

		
		//Ќашли уже нужный. надо теперь сложить две награды
		Award & finalAward = filteredAwards[filteredIndex];
		Award & curAward = resourceAwards[i];

		finalAward.count += curAward.count;
		finalAward.isTasty |= curAward.isTasty;
	}


	//теперь уже добавл€ем полную сумму
	for(int i = 0; i<filteredAwards.size(); i++)
		awards.push_back(filteredAwards[i]);

  if (dbLogic.levelToExperienceTable)
    flashInterface->SetHeroExperience(experience, earnedExp, dbLogic.levelToExperienceTable->Levels);

  struct AwardComparator
  { 
    bool operator()( const Award & first, const Award & second )
    {
			int orderFirst = GetOrder(first.type);
			int orderSecond = GetOrder(second.type);
			
			if (orderFirst ==  orderSecond)
				return first.vendorConst < second.vendorConst;

			return orderFirst < orderSecond;
    }
  } comp;

  nstl::sort(awards.begin(), awards.end(), comp);

  flashInterface->StartAwarding();

  for (int i=0; i< awards.size(); i++)
  {
    const Award & award = awards[i];
    DebugTrace("Call AddAward image = %s, count = %d", award.image.c_str(), award.count );
    flashInterface->AddOurHeroAward(i, award.image.c_str(), award.count, award.isTasty, award.giverUser != 0);
  }
  

  flashInterface->FinishAwarding();
}

const NDb::EResourceType AwardsController::GetResourceTypeByType( const roll::EAwardType::Enum type ) const
{
  switch (type)
  {
    case roll::EAwardType::Silver:
      return NDb::RESOURCETYPE_SILVER;
    case roll::EAwardType::Pearl:
      return NDb::RESOURCETYPE_CRYSTAL;
    case roll::EAwardType::Resource1:
      return NDb::RESOURCETYPE_RESOURCE1;
    case roll::EAwardType::Resource2:
      return NDb::RESOURCETYPE_RESOURCE2;
    case roll::EAwardType::Resource3:
      return NDb::RESOURCETYPE_RESOURCE3;
    case roll::EAwardType::RedPearl:
      return NDb::RESOURCETYPE_REDCRYSTAL;
    default:
      return NDb::RESOURCETYPE_SILVER;
  }  
}

const NDb::EClanWarsResourceType AwardsController::GetCWResourceTypeByAwardType( const roll::EAwardType::Enum type ) const
{
  switch (type)
  {
    case roll::EAwardType::ClanWarsClanRating:
      return NDb::CLANWARSRESOURCETYPE_CLANRATING;
  default:
    return NDb::CLANWARSRESOURCETYPE_PLAYERRATING;
  }  
}


void AwardsController::FillResourceAward(Award &award, const NDb::EResourceType resourceType, NDb::EFaction faction)
{
  const NDb::ResourceDescription &resource = uiData->resourcesDescriptions[resourceType];

  NDb::Ptr<NDb::Texture> image = faction == NDb::FACTION_BURN? resource.imageBurn: resource.imageFreeze;
  award.image = image? image->textureFileName: "";
  award.tooltip = faction == NDb::FACTION_BURN? resource.resourceTooltipBurn.GetText(): resource.resourceTooltipFreeze.GetText(); 
}

void AwardsController::FillResourceAward(Award &award, const NDb::ResourceDescription &resource, NDb::EFaction faction)
{
  NDb::Ptr<NDb::Texture> image = faction == NDb::FACTION_BURN? resource.imageBurn: resource.imageFreeze;
  award.image = image? image->textureFileName: "";
  award.tooltip = faction == NDb::FACTION_BURN? resource.resourceTooltipBurn.GetText(): resource.resourceTooltipFreeze.GetText(); 
}


}

NI_DEFINE_REFCOUNT(NGameX::AwardsController)

