#include "stdafx.h"
#include "RollLogic.h"
#include "RollConfig.h"
#include "Db/DBServer.auto.h"
#include "PF_GameLogic/PFResourcesCollection.h"
#include "RatingCalc.h"
#include "System/InlineProfiler.h"
#include "TalentRollDataCache.h"
#include "RollLog.h"


namespace roll
{
  struct DropNRoll::RollContext
  {
    struct ExcludedRollItem
    {
      int index;
      float weight;

      ExcludedRollItem() : index(0), weight(0) {}
    };

    NCore::TalentRollItems * talentRollItems;
    int probsTotal;
    bool isPremiumDrop;
    vector<ExcludedRollItem> excludedRollItems; // For premium drop logic
    int probChange; // For premium drop logic
    bool talentsAlwaysOwnedByPlayer;
    UserId giverUser; // For premium drop logic
    bool dropAllItemsFromContainer;
    bool rollAsPremium;
    int premiumTalentsCount;

    buff::RollBonusContext* rollBonusContext;

    // Rules flags
    bool exceptOrdinaryTalent;
    bool exceptPearl; // исключить из ролла кристалы (обычные и красные)

    RollContext()
      : talentRollItems( 0 )
      , probsTotal( 0 )
      , isPremiumDrop(false)
      , probChange(0)
      , talentsAlwaysOwnedByPlayer(false)
      , giverUser(0)
      , dropAllItemsFromContainer(false)
      , rollAsPremium(false)
      , exceptOrdinaryTalent(false)
      , exceptPearl(false)
      , premiumTalentsCount(0)
      , rollBonusContext(0)
    {}

    vector<NCore::TalentRollItem>& GetTalentRollItems()
    {
      return rollAsPremium ? talentRollItems->premiumItems : talentRollItems->defaultItems;
    }

    bool FindExcludedRollItem( int index )
    {
      for ( int i = 0, cnt = excludedRollItems.size(); i < cnt; i++ )
      {
        if ( excludedRollItems[i].index == index )
          return true;
      }
      return false;
    }

    void AddExcludedRollItem( int index )
    {
      ExcludedRollItem& item = excludedRollItems.push_back();
      item.index = index;
    }

    void SetExcludedRollItemWeights()
    {
      NI_VERIFY( talentRollItems, "SetExcludedRollItemWeights: talentRollItems shouldn't be 0", return );

      const vector<NCore::TalentRollItem>& items = GetTalentRollItems();

      for ( int i = 0, cnt = excludedRollItems.size(); i < cnt; i++ )
      {
        const int idx = excludedRollItems[i].index;
        excludedRollItems[i].weight = (float)items[idx].probability / (float)probsTotal;
      }
    }

    void ClearProbsAndExcluded()
    {
      probsTotal = 0;
      probChange = 0;
      excludedRollItems.clear();
    }

    void UpdateRollDataProbs()
    {
      NI_VERIFY( talentRollItems, "UpdateRollDataProbs: talentRollItems shouldn't be 0", return );

      vector<NCore::TalentRollItem>& items = GetTalentRollItems();

      for ( int i = 0, cnt = excludedRollItems.size(); i < cnt; i++ )
      {
        const int idx = excludedRollItems[i].index;
        int& prob = items[idx].probability;
        prob -= nstl::min<int>( (float)(excludedRollItems[i].weight * probChange), prob );
      }
    }

    // Increase total probs if roll item passes or add to the list 
    void ProcessRollItem( NDb::RollItem const* rollItem, int index, float prob )
    {
      bool bPass = true;
      bPass = bPass && !( exceptOrdinaryTalent && CheckOrdinaryTalent( rollItem ) );
      bPass = bPass && !( exceptPearl          && CheckPearl( rollItem ) );

      if ( bPass )
      {
        probsTotal += prob;
      }
      else
      {
        AddExcludedRollItem( index );
      }
    }

    // Rules
    static bool CheckOrdinaryTalent( NDb::RollItem const* rollItem )
    {
      if ( NDb::RarityTalentListRollItem::SameType( rollItem ) )
      {
        NDb::RarityTalentListRollItem const* pRarityItem = static_cast<NDb::RarityTalentListRollItem const*>(rollItem);
        if ( pRarityItem->rarity == NDb::TALENTRARITY_ORDINARY )
        {
          return true;
        }
      }
      return false;
    }

    static bool CheckPearl( NDb::RollItem const* rollItem )
    {
      if ( NDb::ResourceRollItem::SameType( rollItem ) )
      {
        NDb::ResourceRollItem const* pResourceItem = static_cast<NDb::ResourceRollItem const*>(rollItem);
        if ( pResourceItem->type == NDb::RESOURCEROLLCONSTRAINT_PEARL 
          || pResourceItem->type == NDb::RESOURCEROLLCONSTRAINT_REDPEARL )
        {
          return true;
        }
      }
      return false;
    }
  };

  inline int GetHeroRatingAwardAmount( const vector<SAwardInfo>& awards )
  {
    for ( int i = 0; i < awards.size(); i++ )
    {
      if ( awards[i].type == EAwardType::HeroRating )
      {
        return awards[i].count;
      }
    }
    ROLL_LOG_ERR( "No hero rating change found in awards. 0 assumed." );
    return 0;
  }

  inline int GetRankByHeroRating( float heroRating, const NDb::HeroRanks* pDBHeroRanks )
  {
    // find a rank corresponding to the specified hero rating
    int rank = 0;
    for ( const int totalRanks = pDBHeroRanks->ranks.size() - 1; rank < totalRanks && heroRating >= pDBHeroRanks->ranks[rank+1].rating; rank++ ) {}

    return rank;
  }

  struct DropNRoll::RollInputData
  {
    ni_detail::UInt64 clientId;
    const NCore::PlayerInfo* playerInfo;
    int allowedRollGroups;
    float resourcesCoeff;
    float cristalsCoeff;
    float redCristalsCoeff;
    float customCurrencyCoeff;
    int newHeroRank;
    int newHeroRating;

    RollInputData() : clientId(0), playerInfo(0), allowedRollGroups(0), resourcesCoeff(0), newHeroRank(0), newHeroRating(0), cristalsCoeff(0), redCristalsCoeff(0), customCurrencyCoeff(0) {}

    explicit RollInputData( const SPreGamePerUserData & _perUserData, int _allowedRollGroups = 0, float _resourcesCoeff = 1.f, float _cristalsCoeff = 1.f, float _redCristalsCoeff = 1.f, float _customCurrencyCoeff = 1.f )
      : clientId(_perUserData.clientId)
      , playerInfo(&_perUserData.playerInfo)
      , allowedRollGroups(_allowedRollGroups) 
      , resourcesCoeff(_resourcesCoeff) 
      , newHeroRank(0)
      , newHeroRating(0) 
      , cristalsCoeff(_cristalsCoeff)
      , redCristalsCoeff(_redCristalsCoeff)
      , customCurrencyCoeff(_customCurrencyCoeff)
    {}

    void SetupNewHeroRankAndRating( const vector<roll::SAwardInfo>& _awards, const bool _isTraining, const NDb::HeroRanks* _heroRanks )
    {
      NI_VERIFY( playerInfo, "Zero playerInfo", return );
      // get new hero rank and remember it
      newHeroRating = playerInfo->heroRating;
      if ( !_isTraining ) // no hero rating change in training game
        newHeroRating += GetHeroRatingAwardAmount( _awards );
      newHeroRank = GetRankByHeroRating( newHeroRating, _heroRanks );
    }
  };

  int GetTalentVendorCostFromDB(const NDb::Talent* talent)
  {
    return (talent->vendorCost < 0) ? NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->talentVendorCostByRarity[talent->rarity] : talent->vendorCost;
  }


  NDb::Ptr<NDb::RollSettings> DropNRoll::DbRoot()
  {
    return NDb::SessionRoot::GetRoot()->rollSettings;
  }



  DropNRoll::DropNRoll( IConfigProvider * _cfg, const NDb::RollSettings * _rollSettings, const NDb::Ptr<NDb::MapList>& _mapList, NWorld::PFResourcesCollection * _talentsCollection ) :
  config( _cfg ),
    rollSettings( _rollSettings ),
    random( GetTickCount() ),
    talentsCollection( _talentsCollection )
  {
    rollDataCache = new TalentRollDataCache( timer::Now() );
    rollBonusDataCache = new roll::buff::RollBonusDataCache();

    talentsCollection->CollectTalents();

    GenerateRollTables( _mapList );
    ParseDropAllClientIds();

    heroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
    NI_DATA_ASSERT( heroRanks, "No HeroRanks" );

    NI_DATA_ASSERT( rollSettings->forgeRollSettings.rollContainer, "No forge rollContainer specified" );
  }



  void DropNRoll::ParseDropAllClientIds()
  {
    StrongMT<RollConfig> cfg = config->Cfg();

    for ( const char * src = cfg->dropAllClientIds.c_str(); *src; )
    {
      int pos = 0;
      char buf[64] = "";
      if ( sscanf( src, "%63[0-9]%n", buf, &pos ) != 1 )
        break;

      dropAllClientIds.push_back( atoi( buf ) );

      src += pos;
      pos=0;
      buf[0] = 0;
      if ( sscanf( src, "%63[ ,;\n\r]%n", buf, &pos ) != 1 )
        break;

      src += pos;
    }
  }



  void DropNRoll::Poll( timer::Time now )
  {
    rollDataCache->Poll( now );
  }



  inline float Lerp(float t0, float t1, float c)
  {
    return t0*(1.f-c)+t1*c;
  }




  inline int GetParameterFromLevel(const nstl::vector<NDb::RollLevelInfo>& params, int level, int defaultValue, NRandom::RandomGenerator & random)
  {
    level -= 1; //we need 0-based level

    int prevIndex = -1;
    int nextIndex = -1;
    bool needInterpolation = false;
    for (int i=0;i<params.size();++i)
    {
      if (params[i].level >= level)
      {
        nextIndex = i;
        if (params[i].level > level)
        {
          prevIndex = i-1;
          needInterpolation = true;
        }
        break;
      }
    }
    // if something found
    if (nextIndex >= 0 && nextIndex < params.size())
    {
      if (!needInterpolation)
      {
        return params[nextIndex].count + random.Next(0, params[nextIndex].deviation);
      } else
      {
        if (prevIndex >= 0)
        {
          int levelStepDiff = params[nextIndex].level-params[prevIndex].level;
          int levelDiff = level-params[prevIndex].level;
          float coeff = 0.f;
          if (levelStepDiff > 0)
          {
            coeff = float(levelDiff)/float(levelStepDiff);
          }
          return Lerp(params[prevIndex].count + random.Next(0, params[prevIndex].deviation), params[nextIndex].count + random.Next(0, params[nextIndex].deviation), coeff);  
        } 
        else
        {
          return params[nextIndex].count + random.Next(0, params[nextIndex].deviation);
        }
      }
    } else
    {
      if (params.size() > 0)
      {
        nextIndex = params.size()-1;
        return params[nextIndex].count + random.Next(0, params[nextIndex].deviation);
      } 
      else
      {
        return defaultValue;
      }
    }
  }


  inline bool IsPvPGameMode( const SPreGameData & _preGame ) 
  {
    return _preGame.mode == EMode::PvP || _preGame.mode == EMode::LobbyPvp;
  }


  inline float GetContainerCostByRank( const NDb::RollContainer *container, int rank )
  {
    NDb::Ptr<NDb::RollContainerCostByRank> pDBCostByRank = container->costByRank;
    if ( !pDBCostByRank )
      pDBCostByRank = DropNRoll::DbRoot()->defaultRollContainerCostByRank;

    const vector<float>& costs = pDBCostByRank->costs;

    NI_DATA_VERIFY( !costs.empty(), "Empty costs list", return 0 );

    if ( rank >= costs.size() )
    {
      ROLL_LOG_ERR( "No container cost found for specified hero rank. Nearest is used." );
      rank = costs.size() - 1;
    }
    return costs[rank];
  }

  inline int GetContainerCountByRank( const NDb::Ptr<NDb::RollContainerCountByRank> &pDBCostByRank, int rank, const FWODTalentsByRankList& fwodTalentsByRankList )
  {
    if ( !pDBCostByRank )
      return 0;

    const vector<int>& counts = pDBCostByRank->counts;

    NI_DATA_VERIFY( !counts.empty(), "Empty costs list", return 0 );

    if ( rank >= counts.size() )
    {
      ROLL_LOG_ERR( "No container cost found for specified hero rank. Nearest is used." );
      rank = counts.size() - 1;
    }

    ROLL_LOG_DBG("Get modified value for rank %d from roll_pvp_fwod_talents_by_rank_modifier_list", rank);
    int modifiedContainersCount = fwodTalentsByRankList.getValue(rank);

    ROLL_LOG_DBG("UnModified value for rank %d is %d", rank, counts[rank]);
    ROLL_LOG_DBG("Modified value for rank %d is %d", rank, modifiedContainersCount);

    return modifiedContainersCount != FWODTalentsByRankList::UNKNOWN_VALUE ? modifiedContainersCount : counts[rank];
  }

  inline NCore::TalentRollItems& GetModeRollTable( NCore::TTalentRollTable& rollTable, const string& modeName )
  {
    if ( rollTable.find( modeName ) == rollTable.end() )
    {
      ROLL_LOG_DBG( "Not found persistent roll data with key %s", modeName );
    }
    return rollTable[modeName];
  }

  void DropNRoll::FillRollTableFromContainer( const NDb::RollContainer* rollContainer, const int allowedRollGroups )
  {
    if ( !rollContainer )
      return;

    StrongMT<RollConfig> cfg = config->Cfg();

    for ( vector<NDb::RollItemProbability>::const_iterator itItem = rollContainer->items.begin(); itItem != rollContainer->items.end(); ++itItem )
    {
      if ( itItem->item )
      {
        if ( NDb::RarityTalentListRollItem::SameType( itItem->item ) ) // Process rarity item
        {
          const NDb::RarityTalentListRollItem* pRarityRollItem = static_cast<const NDb::RarityTalentListRollItem*>(itItem->item.GetPtr());

          for ( NWorld::PFResourcesCollection::TalentMap::const_iterator it = talentsCollection->GetTalents().begin(); it != talentsCollection->GetTalents().end(); ++it )
          {
            // Skip forbidden talents
            if ( !cfg->forbiddenTalentsList.empty() && cfg->forbiddenTalentsList.find( it->second->persistentId ) != nstl::string::npos )
              continue;

            // Talent has specified rarity and presents in specified roll groups
            if ( it->second->rarity == pRarityRollItem->rarity && ( it->second->talentRollGroups & allowedRollGroups ) != 0 )
            {
              vector<NDb::Ptr<NDb::Talent>>& talentsInGroup = talentRollTable[pRarityRollItem->rarity][allowedRollGroups];

              if ( talentsInGroup.find( it->second ) == talentsInGroup.end() )
                talentsInGroup.push_back( it->second );
            }
          }
        }
        else if ( NDb::RollContainer::SameType( itItem->item ) ) // Process nested roll container
        {
          FillRollTableFromContainer( static_cast<const NDb::RollContainer*>(itItem->item.GetPtr()), allowedRollGroups );
        }
      }
    }
  }



  void DropNRoll::GenerateRollTables( const NDb::Ptr<NDb::MapList>& mapList )
  {
    talentRollTable.clear();
    talentRollTable.resize( NDb::KnownEnum<NDb::ETalentRarity>::sizeOf );

    if ( !mapList )
      return;

    // Collect all roll settings referenced in maps
    vector<NDb::Ptr<NDb::ModeRollSettings>> referencedRollSettings;
    for ( vector<NDb::Ptr<NDb::AdvMapDescription>>::const_iterator itMap = mapList->maps.begin(); itMap != mapList->maps.end(); ++itMap )
    {
      const NDb::Ptr<NDb::AdvMapDescription>& mapDesc = *itMap;
      if ( mapDesc && mapDesc->rollSettings && referencedRollSettings.find( mapDesc->rollSettings ) == referencedRollSettings.end() )
      {
        referencedRollSettings.push_back( mapDesc->rollSettings );
      }
    }

    // Fill roll table from all containers in roll settings
    for ( vector<NDb::Ptr<NDb::ModeRollSettings>>::const_iterator itMap = referencedRollSettings.begin(); itMap != referencedRollSettings.end(); ++itMap )
    {
      const vector<NDb::Ptr<NDb::RollContainer>>& rollContainers = (*itMap)->containers;
      for ( vector<NDb::Ptr<NDb::RollContainer>>::const_iterator itContainer = rollContainers.begin(); itContainer != rollContainers.end(); ++itContainer )
      {
        FillRollTableFromContainer( *itContainer, (*itMap)->allowedRollGroups );
      }
    }

    // Fill roll table from all containers in guild roll
    if ( rollSettings->guildLevels )
    {
      const vector<NDb::GuildLevel>& levels = rollSettings->guildLevels->levels;
      for ( vector<NDb::GuildLevel>::const_iterator itLevel = levels.begin(); itLevel != levels.end(); ++itLevel )
      {
        const vector<NDb::Ptr<NDb::GuildBonus>>& bonuses = itLevel->Bonuses;
        for ( vector<NDb::Ptr<NDb::GuildBonus>>::const_iterator itBonus = bonuses.begin(); itBonus != bonuses.end(); ++itBonus )
        {
          const NDb::RandomTalentBonus* pDBRandomTalBonus = dynamic_cast<const NDb::RandomTalentBonus*>(itBonus->GetPtr());
          if ( pDBRandomTalBonus )
          {
            FillRollTableFromContainer( pDBRandomTalBonus->singleRollSettings.rollContainer, pDBRandomTalBonus->singleRollSettings.allowedRollGroups );
          }
        }
      }
    }

    FillRollTableFromContainer( rollSettings->forgeRollSettings.rollContainer, rollSettings->forgeRollSettings.allowedRollGroups );
  }



  void DropNRoll::_RollItemToContainer( vector<SAwardInfo> &_awards, RollContext & ctx, const NDb::RollItem* rollItem, const NDb::RollContainer* container, const RollInputData & userPreGame )
  {
    NI_VERIFY(rollItem, NI_STRFMT("Roll item not found for container %s", container->name), return);

    // nothing item
    const NDb::NothingRollItem* nothingItem = dynamic_cast< const NDb::NothingRollItem* >( rollItem );
    if ( nothingItem )
    {
      ROLL_LOG_DBG( "Rolling Nothing from container %s", container->name );
      return;
    }

    // talent
    const NDb::TalentRollItem* talentItem = dynamic_cast< const NDb::TalentRollItem* >( rollItem);
    if (talentItem)
    {
      NI_VERIFY(talentItem->talent, NI_STRFMT("Talent is not set for container %s, item %s", container->name, rollItem->GetObjectTypeName()), return);

      int count = 1;
      ROLL_LOG_DBG( "Award (type=Talent count=%d id=%s user=%d)", count, talentItem->talent->persistentId.c_str(), userPreGame.clientId );

      SAwardInfo &newAward = _awards.push_back( 
        SAwardInfo( 
        EAwardType::Talent, 
        Crc32Checksum().AddString( talentItem->talent->persistentId.c_str() ).Get(), 
        count, 
        GetTalentVendorCostFromDB(talentItem->talent), 
        ctx.talentsAlwaysOwnedByPlayer,
        ctx.isPremiumDrop, false, ctx.giverUser ) );

      //write bonus statistics
      if(ctx.rollBonusContext && ctx.rollBonusContext->bonus && !ctx.rollBonusContext->isApplied)
      {
        newAward.bonus.count += count;
        newAward.bonus.id = ctx.rollBonusContext->bonus->GetComposedID();

        ctx.rollBonusContext->isApplied = true;
      }

      return;
    }

    // resource
    const NDb::ResourceRollItem* resourceItem = dynamic_cast< const NDb::ResourceRollItem* >( rollItem);
    if (resourceItem)
    {
      string customCurrencyId;
      EAwardType::Enum resourceType = EAwardType::None;
      float resMul = userPreGame.resourcesCoeff;
      switch (resourceItem->type)
      {
      case NDb::RESOURCEROLLCONSTRAINT_SILVER:    resourceType = EAwardType::Silver; break;
      case NDb::RESOURCEROLLCONSTRAINT_RESOURCE1: resourceType = EAwardType::Resource1; break;
      case NDb::RESOURCEROLLCONSTRAINT_RESOURCE2: resourceType = EAwardType::Resource2; break;
      case NDb::RESOURCEROLLCONSTRAINT_RESOURCE3: resourceType = EAwardType::Resource3; break;
      case NDb::RESOURCEROLLCONSTRAINT_SHARD: resourceType = EAwardType::Shard; break;
      case NDb::RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY: 
        {
          resourceType = EAwardType::CustomCurrency; 
          customCurrencyId = resourceItem->customCurrencyId;
          resMul = userPreGame.customCurrencyCoeff;
          break;
        }
      case NDb::RESOURCEROLLCONSTRAINT_PEARL:
        {
          resourceType = EAwardType::Pearl;
          resMul = userPreGame.cristalsCoeff;
          break;
        }
      case NDb::RESOURCEROLLCONSTRAINT_REDPEARL:
        {
          resourceType = EAwardType::RedPearl;
          resMul = userPreGame.redCristalsCoeff;
          break;
        }
      }
      NI_VERIFY(resourceType != EAwardType::None, NI_STRFMT("Unknown resource type %d for container %s, item %s", (int)resourceItem->type, container->name, rollItem->GetObjectTypeName()), return);

      const int countLord = GetParameterFromLevel(resourceItem->itemsFromLord, userPreGame.playerInfo ? userPreGame.playerInfo->avatarLevel : 0, 0, random);
      const int countHero = GetParameterFromLevel(resourceItem->itemsFromHero, userPreGame.playerInfo ? userPreGame.playerInfo->heroLevel : 0, 0, random);
      const int countHeroRank = GetParameterFromLevel(resourceItem->itemsFromRank, userPreGame.newHeroRank + 1, 0, random); // ctx.newHeroRank +1 Because function accepts levels starting from 1, not 0
      const int count = countLord + countHero + countHeroRank;

      const int realCount = ceil( count * resMul );
      ROLL_LOG_DBG( "Award (type=%s ocount=%d(%d/%d/%d) count=%d user=%d)", NDb::EnumToString(resourceItem->type), count, countLord, countHero, countHeroRank, realCount, userPreGame.clientId );

      if (realCount > 0)
      {
        nstl::vector<SAwardInfo>::iterator it;
        for (it=_awards.begin();it!=_awards.end();++it)
        {
          SAwardInfo& awardInfo = (*it);
          if (awardInfo.type == resourceType && 
            (awardInfo.customCurrencyId.empty() || awardInfo.customCurrencyId == customCurrencyId))
            break;
        }

        if (it != _awards.end())
        {
          (*it).count += realCount;
        }
        else
        {
          SAwardInfo ainfo( resourceType, 0, realCount, 0, true, ctx.isPremiumDrop, false, ctx.giverUser );
          ainfo.customCurrencyId = customCurrencyId;
          _awards.push_back(ainfo);
        }
      }
      return;
    } 

    // container
    const NDb::RollContainer* containerItem = dynamic_cast< const NDb::RollContainer* >( rollItem);
    if (containerItem)
    {
      // https://devjira.SITE.com/browse/NUM_TASK
      RollContext _ctx;
      _ctx.rollAsPremium = ctx.rollAsPremium;
      _ctx.talentRollItems = NULL;
      RollPlayersAwardsFromContainer( _awards, _ctx, containerItem, userPreGame );
      return;
    } 

    // rarity list
    const NDb::RarityTalentListRollItem* rarityListItem = dynamic_cast< const NDb::RarityTalentListRollItem* >( rollItem);
    if (rarityListItem)
    {
      NDb::ETalentRarity rarity = rarityListItem->rarity;
      // NUM_TASK: replace small rarity to MAGNIFICENT
      if ( userPreGame.playerInfo && rarity < NDb::TALENTRARITY_MAGNIFICENT)
        rarity = NDb::TALENTRARITY_MAGNIFICENT;        

      const TalentGroupCollection& groupCollection = talentRollTable[rarity];
      TalentGroupCollection::const_iterator it = groupCollection.find( userPreGame.allowedRollGroups );
      if ( it != groupCollection.end() )
      {
        const nstl::vector<NDb::Ptr<NDb::Talent>>& talents = it->second;
        int index = random.Next(talents.size());
        if (index < talents.size())
        {
          int count = 1;
          ROLL_LOG_DBG( "Award (type=Talent count=%d id=%s user=%d)", count, talents[index]->persistentId.c_str(), userPreGame.clientId );
          SAwardInfo& newAward = _awards.push_back( 
            SAwardInfo( 
            EAwardType::Talent, 
            Crc32Checksum().AddString( talents[index]->persistentId.c_str() ).Get(), 
            count, 
            GetTalentVendorCostFromDB(talents[index]), 
            ctx.talentsAlwaysOwnedByPlayer,
            ctx.isPremiumDrop, false, ctx.giverUser) );

          //write bonus statistics
          if(ctx.rollBonusContext && ctx.rollBonusContext->bonus && !ctx.rollBonusContext->isApplied)
          {
            newAward.bonus.count += count;
            newAward.bonus.id = ctx.rollBonusContext->bonus->GetComposedID();

            ctx.rollBonusContext->isApplied = true;
          }

        }
      }
      return;
    }

      // marketing event
      const NDb::MarketingEventRollItem* marketingEventItem = dynamic_cast< const NDb::MarketingEventRollItem* >(rollItem);
      if ( marketingEventItem )
      {
        ROLL_LOG_DBG( "Award (type=MarketingEvent id=%s user=%d)", marketingEventItem->persistentId.c_str(), userPreGame.clientId );
        _awards.push_back( 
          SAwardInfo( 
          EAwardType::MarketingEvent, 
          Crc32Checksum().AddString( marketingEventItem->persistentId.c_str() ).Get(), 
          1, 
          0, 
          true ) );

        return;
      }

      ROLL_LOG_ERR( "Unsupported roll item type container %s, item %s", container->name, rollItem->GetObjectTypeName() );
    }





    void DropNRoll::ResetRollData( RollContext & ctx, const NDb::RollContainer * container, const int version /*= -1 */ )
    {
      NCore::TalentRollItems *& pCtxTalRollItems = ctx.talentRollItems;
      NI_VERIFY( pCtxTalRollItems, "Trying to reset empty roll data", return );

      vector<NCore::TalentRollItem>& rollItems = ctx.GetTalentRollItems();

      rollItems.clear();

      // set version if required
      if ( version > -1 )
      {
        pCtxTalRollItems->version = version;
      }

      ctx.ClearProbsAndExcluded();
      for ( int i = 0 ; i < container->items.size(); ++i )
      {
        NDb::Ptr<NDb::RollItem> const& rollItem = container->items[i].item;

        NI_VERIFY( rollItem, "Empty roll item in container!", continue );

        int prob = (float)( container->items[i].probability * 100.0f + 0.5f );
        rollItems.push_back( NCore::TalentRollItem( prob, Crc32Checksum().AddString( rollItem->GetDBID().GetFormatted().c_str() ).Get() ) );

        // Remember ordinary talent rollItem and do not increment probsTotal for it if premium drop is enabled
        ctx.ProcessRollItem( rollItem, i, prob );
      }

      // Setup ordinary talent roll item weight
      ctx.SetExcludedRollItemWeights();
    }





    void DropNRoll::ValidateRollData( RollContext & ctx, const NDb::RollContainer * container, const int version, const ni_detail::UInt64 userId )
    {
      NCore::TalentRollItems *& pCtxTalRollItems = ctx.talentRollItems;
      NI_VERIFY( pCtxTalRollItems, "Trying to validate empty roll data", return );

      vector<NCore::TalentRollItem>& rollItems = ctx.GetTalentRollItems();

      if ( rollItems.empty() )
      {
        ROLL_LOG_DBG( "Reset roll context for user %d. Empty context", userId );
        ResetRollData( ctx, container, version );
        return;
      }

      if ( pCtxTalRollItems->version != version )
      {
        ROLL_LOG_DBG( "Reset roll context for user %d. Version mismatch found %d, expected %d", userId, pCtxTalRollItems->version, version );
        ResetRollData( ctx, container, version );
        return;
      }

      ctx.ClearProbsAndExcluded();
      for ( int i = 0 ; i < container->items.size(); ++i )
      {
        NDb::Ptr<NDb::RollItem> const& rollItem = container->items[i].item;

        NI_VERIFY( rollItem, "Empty roll item in container!", continue );

        int crc = Crc32Checksum().AddString( rollItem->GetDBID().GetFormatted().c_str() ).Get();
        if ( rollItems[i].dbid != crc )
        {
          ROLL_LOG_DBG( "Reset roll context for user %d. Invalid item data crc32 %d, expected %d. Item is %s", userId, rollItems[i].dbid, crc, rollItem->GetDBID().GetFormatted() );
          ResetRollData( ctx, container, version );
          return;
        }

        // Remember ordinary talent rollItem and do not increment probsTotal for it if premium drop is enabled
        ctx.ProcessRollItem( rollItem, i, rollItems[i].probability );
      }

      // Setup ordinary talent roll item weight
      ctx.SetExcludedRollItemWeights();
    }




    void DropNRoll::_RollPlayersAwardsFromContainer( vector<SAwardInfo> & _awards, RollContext & ctx, const NDb::RollContainer* container, const RollInputData & userPreGame )
    {
      if ( ctx.dropAllItemsFromContainer ) // Roll all items from container
      {
        const NDb::RollItem* rollItem = 0;
        for ( int i = 0 ; i < container->items.size(); ++i )
        {
          rollItem = container->items[i].item;
          _RollItemToContainer(_awards, ctx, rollItem, container, userPreGame );
        }
      }
      else if ( ctx.talentRollItems ) // Roll random item from container when provided with persistent roll data
      {
        // reset roll data if 0 total probs
        if ( ctx.probsTotal == 0 )
        {
          ROLL_LOG_DBG( "Reset roll context for user %d. Total probability is zero", userPreGame.clientId );
          ResetRollData( ctx, container );
        }

        vector<NCore::TalentRollItem>& rollItems = ctx.GetTalentRollItems();

        int roll = random.Next( 0, ctx.probsTotal - 1 );
        int lowBound = 0;
        for ( int i = 0 ; i < container->items.size(); ++i )
        {
          // Skip excluded talent roll items (premium drop)
          if ( ctx.FindExcludedRollItem( i ) )
          {
            continue;
          }

          const NDb::Ptr<NDb::RollItem>& rollItem = container->items[i].item;

          int& currentProb = rollItems[i].probability;

          int highBound = lowBound + currentProb;
          if ( roll >= lowBound && roll < highBound )
          {
            int probDecreaseValue = min( 10, currentProb );
            currentProb -= probDecreaseValue;
            ctx.probsTotal -= probDecreaseValue;
            ctx.probChange += probDecreaseValue;

            _RollItemToContainer( _awards, ctx, rollItem, container, userPreGame );
            break;
          }
          else
          {
            lowBound = highBound;
          }
        }
      }
      else // Roll random item from container
      {
        struct ContainerWeightGetter
        {
          int operator()( const NDb::RollItemProbability& item ) const
          {
            return item.probability;
          }
        } cwg;

        const NDb::RollItemProbability& rollItem = random.RollFromContainerByWeight( container->items, cwg );

        NI_VERIFY( rollItem.item, "Invalid roll item", return );

        _RollItemToContainer( _awards, ctx, rollItem.item, container, userPreGame );
      }
    }

    void DropNRoll::RollPlayersAwardsFromContainer(vector<SAwardInfo>& _awards, RollContext & ctx, const NDb::RollContainer* container, const RollInputData & userPreGame )
    {
      const float cost = GetContainerCostByRank( container, userPreGame.newHeroRank );
      for (int i = 0;i < container->multiplicator; ++i)
      {
        ROLL_LOG_DBG( "Rolling awards for container (name=\"%s\" cost=%f items=%d)", container->name.c_str(), cost, container->items.size());
        _RollPlayersAwardsFromContainer( _awards, ctx, container, userPreGame );
      }
    }

    struct ContainerIsLess
    {
      ContainerIsLess( int heroRank_ ) : heroRank(heroRank_) {}
      bool operator()( const NDb::RollContainer*& a, const NDb::RollContainer* & b )
      {
        if( GetContainerCostByRank( a, heroRank ) < GetContainerCostByRank( b, heroRank ) )
          return false;
        return true;
      }
      int heroRank;
    };

    bool AwardIsLess( SAwardInfo*& a, SAwardInfo* &b)
    {
      if( a->vendorCost < b->vendorCost )
        return true;
      return false;
    }



    bool DropNRoll::IsResource(EAwardType::Enum value)
    {
      return (value == EAwardType::Silver 
        || value == EAwardType::Resource1
        || value == EAwardType::Resource2
        || value == EAwardType::Resource3
        || value == EAwardType::Pearl
        || value == EAwardType::RedPearl
        || value == EAwardType::Shard
        || value == EAwardType::CustomCurrency);
    }


    float DropNRoll::GetEnduranceCoeff(EAwardType::Enum awardType, const NDb::ModeRollSettings* settings, bool isHeroTired,  NCore::EBasket::Enum basket)
    {
      float res= 1.f;
      if (settings->enduranceDisableRollBoost || isHeroTired)
      {
        switch (awardType)
        {
        case EAwardType::Talent: 
          res *= settings->enduranceCoeff;
          break;
        case EAwardType::Fame: 
          res *= settings->enduranceFameCoeff;
          break;
        case EAwardType::Experience: 
          res *= settings->enduranceExperienceCoeff;
          break;
        default: 
          res *=IsResource(awardType)?settings->enduranceResourcesCoeff:settings->enduranceCoeff;
        }
      }
      if (basket == NCore::EBasket::Leaver)
        res *= settings->leaversAwardsCoeff;

      return res;
    }



    void DropNRoll::DropAllAwards( vector<SAwardInfo> & _awards )
    {
      _awards.push_back( SAwardInfo( EAwardType::Resource1, 0, 2, 0, true )  );
      _awards.push_back( SAwardInfo( EAwardType::Resource2, 0, 2, 0, true )  );
      _awards.push_back( SAwardInfo( EAwardType::Resource3, 0, 2, 0, true )  );
      _awards.push_back( SAwardInfo( EAwardType::Pearl, 0, 2, 0, true )  );
      _awards.push_back( SAwardInfo( EAwardType::Silver, 0, 1000, 0, true )  );
      // TODO: не добавляю red pearl, т.к. не понял назначение этой функции (больше всего похоже на дебажную)

      for ( NWorld::PFResourcesCollection::TalentMap::const_iterator it = talentsCollection->GetTalents().begin(); it != talentsCollection->GetTalents().end(); ++it )
      {
        // do not drop class talents
        if ( it->second->rarity == NDb::TALENTRARITY_CLASS )
          continue;

        _awards.push_back( SAwardInfo( EAwardType::Talent
          , Crc32Checksum().AddString( it->second->persistentId.c_str() ).Get()
          , 1
          , GetTalentVendorCostFromDB(it->second)
          , true ) );
      }
    }




    void DropNRoll::RollRating( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const NDb::AdvMapDescription * _map )
    {
      if ( !IsPvPGameMode( _preGame ) )
        return;

      RollSingleRating( _rollResult, EAwardType::PlayerRating, settings, _preGame, _postGame, &NCore::PlayerInfo::playerRating, _map );
      RollSingleRating( _rollResult, EAwardType::HeroRating, settings, _preGame, _postGame, &NCore::PlayerInfo::heroRating, _map );
    }



    void DropNRoll::RollSingleRating( vector<SUserAward> & _rollResult, EAwardType::Enum type, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, float NCore::PlayerInfo::*ratingField, const NDb::AdvMapDescription * _map )
    {
      RatingDeltaCalculator calculator( rollSettings, _map);
      for ( int i = 0; i < _rollResult.size(); ++i )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[i];
        if ( userPreData.faction == lobby::ETeam::None ) {
          ROLL_LOG_ERR( "Rating calculation failed because of user %d have no social data", userPreData.clientId );
          return;
        }
        calculator.AddPlayer( userPreData.faction, userPreData.clientId, userPreData.playerInfo.*ratingField, userPreData.playerInfo.partyId );
      }


      if ( !calculator.Calculate( _postGame.victoriousFaction ) ) {
        ROLL_LOG_ERR( "Player rating calculation failed");
        return;
      }

      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        float ratingChange = 0;
        if ( !calculator.GetDelta( userPreData.clientId, ratingChange, true ) ) {
          ROLL_LOG_ERR( "Player rating calculation failed for user %d", userPreData.clientId );
          continue;
        }

        if ( ( ratingChange > 0 ) && ( userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame ) )
          ratingChange *= -1;

        if ( ratingChange != 0 ) //mmmm... Since rating change is float...
        {
          ROLL_LOG_DBG( "Award (type=%s, count=%f, user=%d)", EAwardType::ToString(type), ratingChange, userPreData.clientId );
          _rollResult[userIndex].awards.push_back( SAwardInfo( type, userPreData.playerInfo.heroId, ratingChange, 0, true ) );
        }
      }
    }


    bool DropNRoll::RollEventContainers( SUserAward & userAward, const NDb::ModeRollSettings * settings, 
      const SPreGamePerUserData & userPreData, const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, 
      const bool isPlayerVictorious, const RollConfig* _cfg )
    {
      // roll input data
      RollInputData userRollInput( userPreData, settings->allowedRollGroups ); // it is supposed that no resources except pearl is rolled from containers, so resourceCoeff = 1
      userRollInput.SetupNewHeroRankAndRating( userAward.awards, _preGame.mode == EMode::Train, heroRanks );

      // is premium
      const bool hasPremium = userPreData.playerInfo.hasPremium;

      // выбираем контейнер
      const NDb::RollContainer* container = NULL;
      {
        const vector<NDb::Ptr<NDb::RollContainer>>& dbContainers = hasPremium ? settings->premiumEventContainers : settings->eventContainers;
        int dbContainerIdx = hasPremium ? config->Cfg()->premiumEventContainersIndex : config->Cfg()->eventContainersIndex;
        if (dbContainerIdx < 0 || dbContainerIdx >= dbContainers.size())
          return false;
        container = dbContainers[dbContainerIdx];
      }

      // контекст
      RollContext ctx;
      {
        ctx.rollAsPremium = hasPremium;
        ctx.talentRollItems = NULL;
      }

      // ролим за очки
      RollContainerForScore(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx, container);

      // ролим за доп очки
      RollContainerForAdditionalScore(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx, container);

      // ролим дефолтовую награду
      RollDefaultContainer(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx);

      return true;
    }


    void DropNRoll::RollUsualContainers( SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg )
    {
      // проверки
      if ( settings->premiumContainers.empty() )
      {
        ROLL_LOG_DBG( "No premium containers defined in %s", settings->GetDBID().GetFormatted() );
        return;
      }
      if ( settings->containers.empty() )
      {
        ROLL_LOG_DBG( "No default containers defined in %s", settings->GetDBID().GetFormatted() );
        return;
      }

      // roll input data
      RollInputData userRollInput( userPreData, settings->allowedRollGroups ); // it is supposed that no resources except pearl is rolled from containers, so resourceCoeff = 1
      userRollInput.SetupNewHeroRankAndRating( userAward.awards, _preGame.mode == EMode::Train, heroRanks );

      // is premium
      const bool hasPremium = userPreData.playerInfo.hasPremium;

      // выбираем контейнер
      const NDb::RollContainer* container = NULL;
      {
        // !Nested containers currently are NOT supported!
        // !Only single container is supported currently!
        // Select default or premium containers
        const vector<NDb::Ptr<NDb::RollContainer>>& dbContainers = hasPremium ? settings->premiumContainers : settings->containers;
        // sort roll containers
        nstl::vector<const NDb::RollContainer*> containers;
        containers.reserve(dbContainers.size());
        for ( int i = 0; i < dbContainers.size(); ++i )
          containers.push_back(dbContainers[i]);
        nstl::sort( containers.begin(), containers.end(), ContainerIsLess(userRollInput.newHeroRank) );
        // end of sort
        if(containers.empty())
        {
          ROLL_LOG_DBG("Unable to get a roll containers for client %d. Cancel RollTalentsForPlayer.", userPreData.clientId);
          return;
        }
        //
        container = containers[0];
      }

      // контекст
      RollContext ctx;
      {
        ctx.rollAsPremium = hasPremium;
        ctx.talentRollItems = &(GetModeRollTable( userAward.talentRollData.rollTable, settings->modeName ));
        if ( ctx.talentRollItems )
          ValidateRollData( ctx, container, settings->version, userPreData.clientId );
      }

      // ролим за очки
      RollContainerForScore(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx, container);

      // ролим за доп очки
      RollContainerForAdditionalScore(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx, container);

      // ролим дефолтовую награду
      RollDefaultContainer(userAward, settings, userPreData, userPostData, _preGame, 
        isPlayerVictorious, _cfg, userRollInput, ctx);
    }


    void DropNRoll::RollContainerForScore(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
      const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
      RollInputData & userRollInput, RollContext & ctx, const NDb::RollContainer* container)
    {
      // считаем очки
      float score = 0;
      {
        score = userPostData.scoring.score * settings->talentsMultiplicator;
        ROLL_LOG_DBG( "Rolling awards (user=%d score=%f)", userPreData.clientId, score );
        if (score > settings->scoresCap)
        {
          ROLL_LOG_DBG( "Scores capped (user=%d original=%f new=%d)", userPreData.clientId, score, settings->scoresCap );
          score = settings->scoresCap;
        }
        score *= IsPvPGameMode(_preGame) ? _cfg->pvpTalentsAmountModifier : _cfg->pveTalentsAmountModifier;
      }

      // more config coeffs!
      float ccCoeff = isPlayerVictorious ? 1.f : (_cfg->customCurrencyLoseCoeff >= .0f ? _cfg->customCurrencyLoseCoeff : 1.0f);
      userRollInput.customCurrencyCoeff = ccCoeff * (_cfg->scoreContCCAmountModifier >= .0f ? _cfg->scoreContCCAmountModifier : 1.0f);
      userRollInput.cristalsCoeff = _cfg->cristalsAmountModifier > 1.0f ? _cfg->cristalsAmountModifier : 1.0f;
      userRollInput.redCristalsCoeff = _cfg->redCristalsAmountModifier > 1.0f ? _cfg->redCristalsAmountModifier : 1.0f;

      // ролим за очки
      float constainerCost = GetContainerCostByRank( container, userRollInput.newHeroRank );
      while ( score > 0 && score >= constainerCost )
      {
        // roll from container
        RollPlayersAwardsFromContainer( userAward.awards, ctx, container, userRollInput );
        NI_VERIFY(constainerCost > 0, "Zero cost container detected (infinite loop), roll aborted", break);
        score -= constainerCost;
      }
    }


    void DropNRoll::RollContainerForAdditionalScore(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
      const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
      RollInputData & userRollInput, RollContext & ctx, const NDb::RollContainer* container)
    {
      // считаем доп очки
      int additionalContainers = 0;
      {
        ROLL_LOG_DBG( "Rolling additional containers (user=%d)", userPreData.clientId );
        // Awards for special points
        const int specPoints = userPostData.scoring.specialPoints;
        // Find how mush containers to roll for gained points
        if ( settings->containersBySpecialPoints && specPoints > 0 )
        {
          const vector<NDb::PointsToContainers>& items = settings->containersBySpecialPoints->items;
          for ( int i = 0, count = items.size(); i < count; ++i )
          {
            if ( items[i].specialPoints > specPoints )
              break;

            additionalContainers = items[i].containers;
          }
        }
        ROLL_LOG_DBG( "  Containers count by special points: %d (spec.points=%d)", additionalContainers, specPoints );
        // Explicit awards on player victory
        int explicitContainers = 0;
        if ( isPlayerVictorious )
          explicitContainers = settings->containersOnWin;
        ROLL_LOG_DBG( "  Explicit containers count (containersOnWin): %d", explicitContainers );
        additionalContainers += explicitContainers;
        additionalContainers *= IsPvPGameMode(_preGame) ? _cfg->pvpTalentsAmountModifier : _cfg->pveTalentsAmountModifier;
      }

      // more config coeffs!
      float ccCoeff = isPlayerVictorious ? 1.f : (_cfg->customCurrencyLoseCoeff >= .0f ? _cfg->customCurrencyLoseCoeff : 1.0f);
      userRollInput.customCurrencyCoeff = ccCoeff * (_cfg->specialContCCAmountModifier >= .0f ? _cfg->specialContCCAmountModifier : 1.0f);
      userRollInput.cristalsCoeff = _cfg->cristalsAmountModifier > 1.0f ? _cfg->cristalsAmountModifier : 1.0f;
      userRollInput.redCristalsCoeff = _cfg->redCristalsAmountModifier > 1.0f ? _cfg->redCristalsAmountModifier : 1.0f;

      // ролим за доп очки
      for ( int i = 0; i < additionalContainers; ++i )
      {
        RollPlayersAwardsFromContainer( userAward.awards, ctx, container, userRollInput );
      }
    }


    void DropNRoll::RollDefaultContainer(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
      const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
      RollInputData & userRollInput, RollContext & ctx)
    {
      // ролим дефолтовую награду
      if (settings->defaultContainer)
      {
        // Apply resource coeffs on default container
        float resCoeff = isPlayerVictorious ? 1.f : settings->resourcesLoseCoeff;
        float ccCoeff = isPlayerVictorious ? 1.f : (_cfg->customCurrencyLoseCoeff >= .0f ? _cfg->customCurrencyLoseCoeff : 1.0f);
        userRollInput.resourcesCoeff = resCoeff * _cfg->resourcesAmountModifier; // apply config modifiers
        userRollInput.customCurrencyCoeff = ccCoeff * (_cfg->defaultContCCAmountModifier >= .0f ? _cfg->defaultContCCAmountModifier : 1.0f);
        userRollInput.cristalsCoeff = _cfg->cristalsAmountModifier > 1.0f ? _cfg->cristalsAmountModifier : 1.0f;
        userRollInput.redCristalsCoeff = _cfg->redCristalsAmountModifier > 1.0f ? _cfg->redCristalsAmountModifier : 1.0f;

        // roll default container
        ctx.dropAllItemsFromContainer = true; // drop all items from default container
        RollPlayersAwardsFromContainer( userAward.awards, ctx, settings->defaultContainer, userRollInput );
      }
    }

    
    void DropNRoll::AwardHeroEnergy( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        if ( userPreData.faction == lobby::ETeam::None )
        {
          ROLL_LOG_ERR( "AwardHeroEnergy failed (user=%d reason=no social team data)", userPreData.clientId );
          continue;
        }

        SUserAward & userAward = _rollResult[userIndex];

        // always rolling hero energy changes
        if ( userPostData.statistics.clientState != Peered::EGameFinishClientState::NotConnected )
        {
          int enduranceGain = settings->enduranceGain;
          if (userPreData.playerInfo.heroEnergy < uint(enduranceGain))
          {
            enduranceGain = userPreData.playerInfo.heroEnergy;
          }
          ROLL_LOG_DBG( "Award (type=HeroEnergy count=%d hero=%d user=%d)", -enduranceGain, userPreData.playerInfo.heroId, userPreData.clientId );
          userAward.awards.push_back( 
            SAwardInfo( 
            EAwardType::HeroEnergy, 
            userPreData.playerInfo.heroId, 
            -enduranceGain, 
            0, 
            true
            ) );
        }
      }
    }


    void DropNRoll::AwardHeroExperienceAndFame( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg )
    {
      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        if ( userPreData.faction == lobby::ETeam::None )
        {
          ROLL_LOG_ERR( "AwardHeroExperienceAndFame failed (user=%d reason=no social team data)", userPreData.clientId );
          continue;
        }

        // leavers don't receive any fame or experience
        if (userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame)
        {
          continue;
        }

        // here we processing only userPostData.statistics.clientState == FinishedGame 
        SUserAward & userAward = _rollResult[userIndex];

        const bool isPlayerVictorious = ( _postGame.victoriousFaction == userPreData.faction );

        int experience = GetParameterFromLevel(settings->experiencePerSession, userPreData.playerInfo.heroLevel, 0, random);
        experience *= userPreData.playerInfo.dropRate * _cfg->expAmountModifier; // apply Drop Rate and config modifier
        if ( isPlayerVictorious == false )
        {
          experience *= settings->experienceLoseCoeff;
        }

        ROLL_LOG_DBG( "Award (type=HeroExperience count=%d hero=%d level=%d user=%d )", experience, userPreData.playerInfo.heroId, userPreData.playerInfo.heroLevel, userPreData.clientId );

        userAward.awards.push_back( 
          SAwardInfo( 
          EAwardType::Experience, 
          userPreData.playerInfo.heroId, 
          experience, 
          0, 
          true
          ) );

        int fame = GetParameterFromLevel(settings->famePerSession, userPreData.playerInfo.heroLevel, 0, random);
        fame *= userPreData.playerInfo.dropRate; // apply Drop Rate
        if ( isPlayerVictorious == false )
        {
          fame *= settings->fameLoseCoeff;
        }
        ROLL_LOG_DBG( "Award (type=Fame count=%d hero=%d level=%d user=%d)", fame, userPreData.playerInfo.heroId, userPreData.playerInfo.heroLevel, userPreData.clientId );
        userAward.awards.push_back( SAwardInfo( EAwardType::Fame, userPreData.playerInfo.heroId, fame, 0, true ) );
      }
    }



    void DropNRoll::RollContainers( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg )
    {
      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        if ( userPreData.faction == lobby::ETeam::None )
        {
          ROLL_LOG_ERR( "Containers roll failed (user=%d reason=no social team data)", userPreData.clientId );
          continue;
        }

        // leavers don't receive any container awards
        if (userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame)
        {
          continue;
        }

        SUserAward & userAward = _rollResult[userIndex];

        const bool isPlayerVictorious = ( _postGame.victoriousFaction == userPreData.faction );

        // Cheat drop for specified clients
        if ( dropAllClientIds.find( userPreData.clientId ) != dropAllClientIds.end() )
        {
          DropAllAwards( userAward.awards );
          continue;
        }
        // end of cheat drop

        if ( !settings )
          continue;

        const NDb::ModeRollSettings* settingsForRoll = settings;

        if ( _preGame.mode == EMode::Train )
        {
          // skip talent awarding from failed training
          if ( isPlayerVictorious == false )
            continue;

          // check for training fwod
          if ( userPreData.playerInfo.fwod )
          {
            if ( rollSettings->trainingFWODSettings )
              settingsForRoll = rollSettings->trainingFWODSettings; // use special award settings for training FWOD
            else
              ROLL_LOG_DBG( "Training FWOD settings not found. Using original settings." );
          }
        }

        // ролим либо евентовые награды, либо обычные
        if (!RollEventContainers(userAward, settingsForRoll, userPreData, userPostData, _preGame, isPlayerVictorious, _cfg))
          RollUsualContainers( userAward, settingsForRoll, userPreData, userPostData, _preGame, isPlayerVictorious, _cfg );

        // Mark all talents and resources as Tasty awards for training fwod
        if ( _preGame.mode == EMode::Train && userPreData.playerInfo.fwod )
        {
          for ( int i = 0, sz = userAward.awards.size(); i < sz; i++ )
          {
            SAwardInfo& award = userAward.awards[i];
            if ( IsResource( award.type ) || award.type == EAwardType::Talent )
              award.isTasty = true;
          }
        }
      }
    }




    void DropNRoll::RollReliabilityAndDodge( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      if ( !IsPvPGameMode( _preGame ) )
        return;

      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        SUserAward & userAward = _rollResult[userIndex];

        if ( userPreData.faction == lobby::ETeam::None )
          continue;

        int reliabilityChange = 0;

        if (userPostData.statistics.clientState == Peered::EGameFinishClientState::FinishedGame)  
        {
          if ( userPreData.faction == _postGame.victoriousFaction)
            reliabilityChange = settings->reliabilityOnFinishWin;
          else
            reliabilityChange = settings->reliabilityOnFinishLose;

          if (settings->reliabilityOnFinishPeriod > 0)
            reliabilityChange += settings->reliabilityOnFinishPerPeriod*(_postGame.totalSeconds/settings->reliabilityOnFinishPeriod);
        }
        else
        {
          reliabilityChange = settings->reliabilityOnLeave;
          if (settings->reliabilityOnLeavePeriod > 0)
            reliabilityChange += settings->reliabilityOnLeavePerPeriod*(userPostData.statistics.totalAfkSeconds/settings->reliabilityOnLeavePeriod);

          if ( _preGame.mode == EMode::LobbyPvp )
          {
            const int dodgePoints = settings->dodgePointsOnLeave;
            ROLL_LOG_DBG( "Award (type=DodgePoints count=%d user=%d)", dodgePoints, userPreData.clientId );
            userAward.awards.push_back( SAwardInfo( EAwardType::DodgePoints, 0, dodgePoints, 0, true ) );
          }
        }

        ROLL_LOG_DBG( "Award (type=Reliability count=%d user=%d)", reliabilityChange, userPreData.clientId );
        userAward.awards.push_back( SAwardInfo( EAwardType::Reliability, 0, reliabilityChange, 0, true ) ); 
      }
    }




    void DropNRoll::RollEndurance( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      for ( int userIdx = 0; userIdx < _rollResult.size(); ++userIdx )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIdx];

        // Do not apply endurance if dropping by cheat
        if ( dropAllClientIds.find( userPreData.clientId ) != dropAllClientIds.end() )
        {
          continue;
        }

        SUserAward & userAward = _rollResult[userIdx];

        nstl::vector<SAwardInfo*> awards;
        awards.reserve( userAward.awards.size() );

        nstl::vector<SAwardInfo*> amountAwards;
        amountAwards.reserve( userAward.awards.size() );

        for (int i = 0; i < userAward.awards.size(); ++i)
        {
          if (!userAward.awards[i].isOwnedByPlayer)
          {
            awards.push_back(&userAward.awards[i]);
          }
          else 
            if (userAward.awards[i].type == EAwardType::Experience 
              || userAward.awards[i].type == EAwardType::Fame
              || IsResource(userAward.awards[i].type))
            {
              amountAwards.push_back(&userAward.awards[i]);
            }
        }

        bool isHeroTired = userPreData.playerInfo.hasFullLibrary;

        if ( isHeroTired ){
          if (userPreData.playerInfo.hasFullLibrary)
          {
            ROLL_LOG_DBG( "Hero library is full.");
          }

          if (userPreData.playerInfo.basket == NCore::EBasket::Leaver)
            ROLL_LOG_DBG( "Player is Leaver.");

          ROLL_LOG_DBG( "Hero is tired. Applying endurance modifiers for awards. user %d", userPreData.clientId );
        }

        if (awards.size() > 0)
        {
          ROLL_LOG_DBG( "Total %d ownable awards granted to user %d", awards.size(), userPreData.clientId );

          nstl::sort( awards.begin(), awards.end(), AwardIsLess );

          float giveCoeff = GetEnduranceCoeff(EAwardType::Talent, settings, isHeroTired, userPreData.playerInfo.basket);
          float giveCount = awards.size()*giveCoeff;
          int totalGiveCount = Round(giveCount);
          if (totalGiveCount == 0 && giveCount > 0.f)
          {
            totalGiveCount = 1;
          }
          ROLL_LOG_DBG( "Total %d awards owned by user %d now", totalGiveCount, userPreData.clientId );
          for (int i = 0; i < totalGiveCount; ++i)
          {
            awards[i]->isOwnedByPlayer = true;
          }
        }
        if (amountAwards.size() > 0)
        {
          ROLL_LOG_DBG( "Amount awards granted (count=%d)", amountAwards.size() );
          nstl::vector<SAwardInfo> additionalAwards;
          additionalAwards.reserve(amountAwards.size());
          for (int i=0;i<amountAwards.size();++i)
          {
            float giveCoeff = GetEnduranceCoeff(amountAwards[i]->type, settings, isHeroTired, userPreData.playerInfo.basket);
            float giveCount = amountAwards[i]->count*giveCoeff;
            int totalGiveCount = ceil(giveCount);
            if (totalGiveCount < amountAwards[i]->count)
            {
              SAwardInfo& ainfo = additionalAwards.push_back();
              ainfo = *amountAwards[i];
              ainfo.count = amountAwards[i]->count-totalGiveCount; 
              ainfo.isOwnedByPlayer = false;
              ROLL_LOG_DBG( "Award splitted (type=%d count=%d/%d user=%d)", (int)ainfo.type, totalGiveCount, ainfo.count, userPreData.clientId );
              amountAwards[i]->count = totalGiveCount;
            }
          }
          for (int i=0;i<additionalAwards.size();++i)
          {
            userAward.awards.push_back(additionalAwards[i]);
          }
        }
      }
    }

    void DropNRoll::RollFWOD( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg )
    {
      if ( !settings->FWODRewardContainer )
        return;

      FWODTalentsByRankList fwodTalentsByRankModifier(_cfg->fwodTalentsByRankList);

      bool isPvPGame =  IsPvPGameMode(_preGame);

      for ( int userIdx = 0; userIdx < _rollResult.size(); ++userIdx )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIdx];
        const SPostGamePerUserData & userPostData = _postGame.users[userIdx];

        SUserAward & userAward = _rollResult[userIdx];

        // only victorious players and those who finished game
        if ( _postGame.victoriousFaction != userPreData.faction || userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame )
          continue;

        // only those who can apply fwod
        if ( !userPreData.playerInfo.fwod )
          continue;

        ROLL_LOG_DBG( "Rolling FWOD award (user=%d)", userPreData.clientId );

        RollInputData userRollInput( userPreData, settings->allowedRollGroups );
        userRollInput.SetupNewHeroRankAndRating( userAward.awards,  _preGame.mode == EMode::Train, heroRanks );

        RollContext ctx;
        ctx.talentsAlwaysOwnedByPlayer = true; // talent rewards in FWOD are unaffected by any conditions
        ctx.rollAsPremium = userPreData.playerInfo.hasPremium;

        int fwodContainersCount = 0;

        //roll talents from premiumCotainer or defaultContainer
        ctx.talentRollItems = &(GetModeRollTable( userAward.talentRollData.rollTable, settings->modeName ));
        ctx.exceptPearl = true;

        if(settings->containersOnFWOD)
        {
          int additionalContainersFWOD = GetContainerCountByRank(settings->containersOnFWOD, userRollInput.newHeroRank, fwodTalentsByRankModifier);
          float fwodTalentsByRankMultiplier = 1.f;

          if(isPvPGame)
            fwodTalentsByRankMultiplier = _cfg->pvpFWODTalentsByRankMultiplier;

          fwodContainersCount = Round(additionalContainersFWOD * fwodTalentsByRankMultiplier);
        }

        const vector<NDb::Ptr<NDb::RollContainer>> &dbContainers = ctx.rollAsPremium ? settings->premiumContainers : settings->containers;
        const NDb::Ptr<NDb::RollContainer> &container = dbContainers[0];

        ValidateRollData( ctx, container, settings->version, userPreData.clientId );

        while(0 != fwodContainersCount--)
        {
          RollPlayersAwardsFromContainer( userAward.awards, ctx, container, userRollInput );
        }


        ctx.dropAllItemsFromContainer = true;

        if(isPvPGame)
        {
          userRollInput.resourcesCoeff = _cfg->pvpFWODResourcesAmountModifier > 1.0f ? _cfg->pvpFWODResourcesAmountModifier : 1.0f;
          userRollInput.cristalsCoeff = _cfg->pvpFWODCristalsAmountModifier > 1.0f ? _cfg->pvpFWODCristalsAmountModifier : 1.0f;
          userRollInput.redCristalsCoeff = _cfg->pvpFWODRedCristalsAmountModifier > 1.0f ? _cfg->pvpFWODRedCristalsAmountModifier : 1.0f;
          userRollInput.customCurrencyCoeff = _cfg->pvpFWODCustomCurrencyAmountModifier >= .0f ? _cfg->pvpFWODCustomCurrencyAmountModifier : 1.0f;
        }

        //roll resources from FWODRewardContainer
        RollPlayersAwardsFromContainer( userAward.awards, ctx, settings->FWODRewardContainer, userRollInput );

        // Mark best talent as Tasty
        int bestAwardIndex = -1;
        uint bestVendorCost = 0;
        vector<SAwardInfo>& awards = _rollResult[userIdx].awards;
        for ( int i = 0, sz = awards.size(); i < sz; i++ )
        {
          if ( awards[i].type != EAwardType::Talent )
            continue;

          if ( awards[i].vendorCost > bestVendorCost )
          {
            bestAwardIndex = i;
            bestVendorCost = awards[i].vendorCost;
          }
        }
        if ( bestAwardIndex > -1 )
        {
          awards[bestAwardIndex].isTasty = true;
        }
      }
    }



    void DropNRoll::ApplyPremium( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * _settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg )
    {
      map<int,RollContext> contexts;

      for ( int userIdx = 0; userIdx < _rollResult.size(); ++userIdx )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIdx];
        const SPostGamePerUserData & userPostData = _postGame.users[userIdx];

        // only those who finished game
        if ( userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame )
          continue;

        // only players with premium account
        if ( !userPreData.playerInfo.hasPremium )
          continue;

        const bool isPlayerVictorious = ( _postGame.victoriousFaction == userPreData.faction );

        const float premiumAmount = userPreData.playerInfo.dropRate - 1.0f;

        SUserAward & userAward = _rollResult[userIdx];

        // Apply drop rate and mark talents
        vector<SAwardInfo>& awards = userAward.awards;

        // If training fwod then use alternative settings
        const NDb::ModeRollSettings * settings = _settings;
        const bool conditionForTrainingExplicitAward = isPlayerVictorious && userPreData.playerInfo.fwod && rollSettings->trainingFWODSettings;
        const bool isTraining = _preGame.mode == EMode::Train;
        if ( isTraining && conditionForTrainingExplicitAward )
        {
          settings = rollSettings->trainingFWODSettings;
        }

        int premiumTalentsCountForWinning = (settings->applyPremiumTalent > 0 && _cfg->rollApplyPremiumTalentsForWinning >= 0) ? _cfg->rollApplyPremiumTalentsForWinning : settings->applyPremiumTalent;
        int premiumTalentsCountForLosing = (settings->applyPremiumTalent > 0 && _cfg->rollApplyPremiumTalentsForLosing >= 0 ) ? _cfg->rollApplyPremiumTalentsForLosing : settings->applyPremiumTalent;

        int premiumContainersSize = settings->additionalPremiumContainers.size();

        if(premiumContainersSize == 0)
          ROLL_LOG_DBG( "Premium rewards calculation failed because premiumContainers is not setup (premiumContainers.size == 0), skipping premium reward calculation.");

        // Explicit premium reward (only talents with rarity good+)
        if ( (premiumTalentsCountForWinning >= 0 && premiumTalentsCountForLosing >= 0) 
          && ( !isTraining || conditionForTrainingExplicitAward ) && premiumContainersSize > 0 )
        {
          ROLL_LOG_DBG( "Rolling Premium award (user=%d)", userPreData.clientId );

          RollInputData userRollInput( userPreData, settings->allowedRollGroups, 1.0f );
          userRollInput.SetupNewHeroRankAndRating( userAward.awards, isTraining, heroRanks );

          // Only single container supported
          NDb::RollContainer const* pDBRollContainer = settings->additionalPremiumContainers[0];

          // Get context for specified user
          if ( contexts.find( userIdx ) == contexts.end() )
          {
            RollContext& ctx = contexts[userIdx];
            ctx.talentRollItems = &(GetModeRollTable( userAward.talentRollData.rollTable, settings->modeName ));
            ctx.isPremiumDrop = true;
            ctx.talentsAlwaysOwnedByPlayer = true; // talent rewards in Premium are unaffected by any conditions
            ctx.rollAsPremium = true;
            // Set Rules
            ValidateRollData( ctx, pDBRollContainer, settings->version, userPreData.clientId );
          }
          RollContext& ctx = contexts[userIdx];
          ctx.giverUser = userPreData.clientId;
          ctx.premiumTalentsCount = isPlayerVictorious ? premiumTalentsCountForWinning : premiumTalentsCountForLosing; 

          while(0 != ctx.premiumTalentsCount--)
          {
            RollPlayersAwardsFromContainer( userAward.awards, ctx, pDBRollContainer, userRollInput );
          }

          // If victorious then give reward to other teammates too
          if ( isPlayerVictorious )
          {
            ROLL_LOG_DBG( "Rolling Premium awards for teammates" );

            for ( int otherUserIdx = 0; otherUserIdx < _rollResult.size(); ++otherUserIdx )
            {
              const SPreGamePerUserData & otherUserPreData = _preGame.users[otherUserIdx];
              SUserAward & otherUserAward = _rollResult[otherUserIdx];

              // Skip self and not teammates
              if ( otherUserIdx == userIdx || otherUserPreData.faction != userPreData.faction )
                continue;

              // Get context for specified user
              if ( contexts.find( otherUserIdx ) == contexts.end() )
              {
                RollContext& ctx = contexts[otherUserIdx];
                ctx.talentRollItems = &(GetModeRollTable( otherUserAward.talentRollData.rollTable, settings->modeName ));
                ctx.isPremiumDrop = true;
                ctx.talentsAlwaysOwnedByPlayer = true; // talent rewards in Premium are unaffected by any conditions
                ctx.rollAsPremium = true;
                // Set Rules
                ValidateRollData( ctx, pDBRollContainer, settings->version, otherUserPreData.clientId );
              }
              RollContext& ctx = contexts[otherUserIdx];
              ctx.giverUser = userPreData.clientId;
              ctx.premiumTalentsCount = premiumTalentsCountForWinning;

              RollInputData otherUserRollInput( otherUserPreData, settings->allowedRollGroups, 1.0f );
              otherUserRollInput.SetupNewHeroRankAndRating( otherUserAward.awards, isTraining, heroRanks );

              while(0 != ctx.premiumTalentsCount--)
              {
                RollPlayersAwardsFromContainer( otherUserAward.awards, ctx, pDBRollContainer, otherUserRollInput );
              }
            }
          }
        }
        // End of explicit award

        // Drop additional resources
        for ( int i = 0, sz = awards.size(); i < sz; i++ )
        {
          const EAwardType::Enum awardType = awards[i].type;

          if ( IsResource( awardType ) /* && !userPreData.playerInfo.fwod*/ )
          {
            const int count = awards[i].count * premiumAmount;
            if ( count > 0 )
            {

              SAwardInfo ainfo( awardType, 0, count, awards[i].vendorCost, awards[i].isOwnedByPlayer, true, awards[i].isTasty );
              ainfo.customCurrencyId = awards[i].customCurrencyId;
              awards.push_back(ainfo);

              ROLL_LOG_DBG( "Premium award (type=%s count=%d user=%d)", EAwardType::ToString(awardType), count, userPreData.clientId );
            }
          }
        }
      }
    }

    // Marketing Events Item Roll
    void DropNRoll::RollMarketingEvents( vector<SUserAward> & _rollResult, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      if ( _preGame.mode == EMode::Train )
        return;

      for ( int userIdx = 0; userIdx < _rollResult.size(); ++userIdx )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIdx];
        const SPostGamePerUserData & userPostData = _postGame.users[userIdx];

        // only those who finished game
        if ( userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame )
          continue;

        // do not roll if player has fwod but not a winner
        if ( userPreData.playerInfo.fwod && userPreData.faction != _postGame.victoriousFaction )
          continue;

        const nstl::string& containerDbid = userPreData.playerInfo.goldLampRollContainer;
        if ( containerDbid.empty() )
          continue;

        NDb::Ptr<NDb::RollContainer> marketingEventContainer = NDb::Get<NDb::RollContainer>( NDb::DBID( containerDbid ) );

        NI_VERIFY( marketingEventContainer, NI_STRFMT( "Invalid marketing event container dbid: %s", containerDbid.c_str() ), continue );

        const RollInputData userRollInput( userPreData );
        RollContext ctx;
        RollPlayersAwardsFromContainer( _rollResult[userIdx].awards, ctx, marketingEventContainer, userRollInput );
      }
    }

    //////////////////////////////////////////////////////////////////////////
    // Guild Roll
    //////////////////////////////////////////////////////////////////////////
    struct DropNRoll::RollGuildData : NCore::GuildData
    {
      lobby::ETeam::Enum faction;

      RollGuildData() :
      GuildData(),
        faction( lobby::ETeam::None )
      {}

      RollGuildData( const GuildData& _guildData ) :
      GuildData( _guildData ),
        faction( lobby::ETeam::None )
      {}
    };



    void DropNRoll::FillRollGuildData( const SPreGameData & _preGame, const SPostGameData & _postGame, map<NCore::TGuildAuid, RollGuildData>& _rollGuildsData )
    {
      int userCount = _postGame.users.size();
      for ( int userIndex = 0; userIndex < userCount; ++userIndex )
      {
        const SPreGamePerUserData & userPreGame = _preGame.users[userIndex];
        const NCore::GuildData& gd = userPreGame.playerInfo.guildData;
        if (!gd.guidWarEventPass)
          continue;
        
        if (_rollGuildsData.find(gd.id) == _rollGuildsData.end())
        {
          _rollGuildsData[gd.id] = gd;
          _rollGuildsData[gd.id].faction = userPreGame.faction;
        }
      }
    }


    void DropNRoll::RollGuildAwards( map<NCore::TGuildAuid, SGuildAward>& _guildAwards, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const NDb::AdvMapDescription * _map )
    {
      if (!IsPvPGameMode( _preGame ))
        return;

      //if (_preGame.guildData.guilds.empty())
      //  return;

      ROLL_LOG_DBG( "Rolling guild awards for guilds");

      map<NCore::TGuildAuid, RollGuildData> rollGuildsData;
      //guildData.resize(gui);

      FillRollGuildData( _preGame, _postGame, rollGuildsData );

      if ( rollGuildsData.empty())
      {
        ROLL_LOG_DBG( "Guild data not found within players. Guild awarding skipped" );
        return;
      }
      
      // с введением клановых ивентов рейтинг теперь не добавка к дневному рейтингу клана, а очки, которые надо вычесть из пула ивента - начисляются ниже
      //RollGuildRating( _guildAwards, rollGuildsData, _preGame, _postGame, _map );

      const NDb::GuildLevels* pDBGuildLevels = rollSettings->guildLevels;
      if ( !pDBGuildLevels )
      {
        ROLL_LOG_DBG( "No GuildLevels defined. Guild awarding skipped." );
        return;
      }

      // Награды для гильдий
      for (map<NCore::TGuildAuid,RollGuildData>::const_iterator it = rollGuildsData.begin(); it != rollGuildsData.end(); ++it)
      {
        const RollGuildData& rollGuildData = it->second;
        // Только победившая гильдия получает свои награды
        if ( _postGame.victoriousFaction != rollGuildData.faction )
          continue;

        if (_guildAwards.find(rollGuildData.id) == _guildAwards.end())
          _guildAwards[rollGuildData.id] = SGuildAward(rollGuildData.id);
        
        vector<SAwardInfo>& guildAwards = _guildAwards[rollGuildData.id].awards;


        bool bGuildResourceBonusProcessed = false;
        bool bRandomTalentBonusProcessed = false;

        // Process GuildLevels
        // Стартуем с уровня гильдии. В процессе проверяем для отдельных наград на уровень домика.
        const vector<NDb::GuildLevel>& guildLevels = pDBGuildLevels->levels;
        const int lastLevel = min( rollGuildData.level, guildLevels.size() - 1 );
        for ( int level = lastLevel; level >= 0; --level )
        {
          // Process bonuses from single GuildLevel
          const vector<NDb::Ptr<NDb::GuildBonus>>& bonuses = guildLevels[level].Bonuses;
          for ( int bonusIndex = 0, bonusCount = bonuses.size(); bonusIndex < bonusCount; ++bonusIndex )
          {
            const NDb::GuildBonus* pDBGuildBonus = bonuses[bonusIndex];
            if ( !pDBGuildBonus )
              continue;

            // Guild resource
            if ( !bGuildResourceBonusProcessed && NDb::GuildResourceBonus::SameType( pDBGuildBonus ) )
            {
              bGuildResourceBonusProcessed = true;

              const NDb::GuildResourceBonus *pGuildResBonus = static_cast<const NDb::GuildResourceBonus *>(pDBGuildBonus);

              const int count = pGuildResBonus->resource;
              guildAwards.push_back( SAwardInfo( EAwardType::GuildResource, 0, count, 0, true ) );
              ROLL_LOG_DBG( "Guild award (type=GuildResource count=%d guildId=%d)", count, rollGuildData.id );
            }
            // Random talent
            else if ( !bRandomTalentBonusProcessed && NDb::RandomTalentBonus::SameType( pDBGuildBonus ) )
            {
              bRandomTalentBonusProcessed = true;

              const NDb::RandomTalentBonus *pAddExpBonus = static_cast<const NDb::RandomTalentBonus *>(pDBGuildBonus);

              NDb::RollContainer const* pDBRollContainer = pAddExpBonus->singleRollSettings.rollContainer;
              if ( pDBRollContainer )
              {
                // Реализовано с использованием существующего механизма ролла из контейнера по вероятностям

                RollInputData rollInput;
                rollInput.clientId = rollGuildData.id;
                rollInput.allowedRollGroups = pAddExpBonus->singleRollSettings.allowedRollGroups;

                RollContext ctx;
                ctx.talentsAlwaysOwnedByPlayer = true;

                RollPlayersAwardsFromContainer( guildAwards, ctx, pDBRollContainer, rollInput );
              }
            }
          }
          // End of process bonuses from single level

          if ( bGuildResourceBonusProcessed && bRandomTalentBonusProcessed )
            break;
        }
      }
    }


    void DropNRoll::RollGuildMembersAwards( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      if ( !IsPvPGameMode( _preGame ) )
        return;

      const NDb::GuildLevels* pDBGuildLevels = rollSettings->guildLevels;
      if ( !pDBGuildLevels )
      {
        ROLL_LOG_DBG( "No GuildLevels defined. Guild members awarding skipped." );
        return;
      }

      // Награды для членов гильдии
      // Сейчас даются независимо от гильдийности боя. Пока только +% к опыту
      for ( int userIndex = 0, userSize = _rollResult.size(); userIndex < userSize; ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];
        vector<SAwardInfo>& awards = _rollResult[userIndex].awards;

        // Only guild members with guild war event pass
        if ( userPreData.playerInfo.guildData.id == 0 || !userPreData.playerInfo.guildData.guidWarEventPass)
          continue;

        
        // only those who finished game
        if ( userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame )
          continue;

        const int buildingLevel = userPreData.playerInfo.guildData.buildingLevel;

        // No building, skip
        if ( buildingLevel < 0 )
          continue;

        bool bAddExpBonusProcessed = false;

        // Process GuildLevels
        // Стартуем с уровня домика
        const vector<NDb::GuildLevel>& guildLevels = pDBGuildLevels->levels;
        const int lastLevel = min( buildingLevel, guildLevels.size() - 1 );
        for ( int level = lastLevel; level >= 0; --level )
        {
          // Process bonuses from single GuildLevel
          const vector<NDb::Ptr<NDb::GuildBonus>>& bonuses = guildLevels[level].Bonuses;
          for ( int bonusIndex = 0, bonusCount = bonuses.size(); bonusIndex < bonusCount; ++bonusIndex )
          {
            const NDb::GuildBonus* pDBGuildBonus = bonuses[bonusIndex];
            if ( !pDBGuildBonus )
              continue;

            // Additional hero exp
            if ( !bAddExpBonusProcessed && NDb::AdditionHeroExpBonus::SameType( pDBGuildBonus ) )
            {
              bAddExpBonusProcessed = true;

              const NDb::AdditionHeroExpBonus *pAddExpBonus = static_cast<const NDb::AdditionHeroExpBonus *>(pDBGuildBonus);

              for ( int i = 0, sz = awards.size(); i < sz; i++ )
              {
                if ( awards[i].type == EAwardType::Experience )
                {
                  const int count = float( awards[i].count ) * pAddExpBonus->percent * 0.01f;
                  awards.push_back( SAwardInfo( EAwardType::Experience, awards[i].id, count, 0, awards[i].isOwnedByPlayer, false, false, 0, true ) );
                  ROLL_LOG_DBG( "Guild member award (type=Experience count=%d user=%d)", count, userPreData.clientId );
                }
              }
            }
          }
          if ( bAddExpBonusProcessed )
            break;
        }
      }
    }

    void DropNRoll::RollClanWarUsersAwards( vector<SUserAward> & _rollResult, GuildWarEventrPointsCalculator& calculator)
    {
      if (!calculator.IsValidSettings())
        return;

      ROLL_LOG_MSG("Begin roll clanWar users awards.");

      calculator.CalculatePoints(_rollResult);

      ROLL_LOG_MSG("End of clanWar users awards roll.");
    }

    void DropNRoll::PrepareClanWarGuildsAwards( vector<SUserAward> & _rollResult, map<NCore::TGuildAuid, SGuildAward>& _guildAwards, GuildWarEventrPointsCalculator& calculator )
    {
      if (!calculator.IsValidSettings())
        return;
      
      ROLL_LOG_MSG("Begin roll clanWar guilds awards.");
      
      calculator.FinalizeClanWarAwards(_rollResult, _guildAwards);

      ROLL_LOG_MSG("End of clanWar guilds awards roll.");
    }

    //////////////////////////////////////////////////////////////////////////
    // End of Guild Roll
    //////////////////////////////////////////////////////////////////////////


    void DropNRoll::RollTalentsBuff(SUserAward& userAward, buff::RollBonusContext* rollBonusContext, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData )
    {
      if(!settings)
      {
        ROLL_LOG_DBG("Unable to get ModeRollSettings. Skip RollTalentsBuff for client %d.", userPreData.clientId);
        return;
      }

      if(!rollBonusContext || !rollBonusContext->bonus)
      {
        ROLL_LOG_DBG("Invalid rollBonusContext. Skip RollTalentsBuff for client %d.", userPreData.clientId);
        return;
      }

      RollInputData userRollInput( userPreData, settings->allowedRollGroups );

      userRollInput.newHeroRating =  userPreData.playerInfo.heroRating + GetHeroRatingAwardAmount( userAward.awards );
      userRollInput.newHeroRank = GetRankByHeroRating(userRollInput.newHeroRating, heroRanks);

      const bool hasPremium = userPreData.playerInfo.hasPremium;

      // Select default or premium containers
      const vector<NDb::Ptr<NDb::RollContainer>>& dbContainers = hasPremium ? settings->premiumContainers : settings->containers;

      // sort roll containers
      nstl::vector<const NDb::RollContainer*> containers;
      containers.reserve(dbContainers.size());
      for ( int i = 0; i < dbContainers.size(); ++i )
      {
        containers.push_back(dbContainers[i]);
      }
      nstl::sort( containers.begin(), containers.end(), ContainerIsLess(userRollInput.newHeroRank) );
      // end of sort

      if(containers.empty())
      {
        ROLL_LOG_DBG("Unable to get a roll containers for client %d. Cancel RollTalentsBuff.", userPreData.clientId);
        return;
      }

      int index = 0;
      RollContext ctx;

      ctx.rollBonusContext = rollBonusContext;
      ctx.rollAsPremium = hasPremium;
      ctx.talentsAlwaysOwnedByPlayer = true;
      ctx.talentRollItems = &(GetModeRollTable( userAward.talentRollData.rollTable, settings->modeName ));
      if ( ctx.talentRollItems )
        ValidateRollData( ctx, containers[index], settings->version, userPreData.clientId );

      // roll
      int additionalContainers = ctx.rollBonusContext->bonus->GetAdd();

      for ( int i = 0; i < additionalContainers; ++i )
      {
        _RollPlayersAwardsFromContainer( userAward.awards, ctx, containers[index], userRollInput );
      }

    }

    void DropNRoll::ApplyBuffsOnUserAwards(const SPreGamePerUserData & userPreData, vector<SUserAward>& userAwards, const NDb::ModeRollSettings * settings)
    {
      typedef vector<SAwardInfo> SAwardInfoCollection;
      typedef vector<SUserAward> SUserAwardCollection;
      typedef vector<SGuildAward> SGuildAwardCollection;

      struct UserAwardFinder
      {
        UserAwardFinder(Transport::TClientId cid) : cid_(cid){}

        bool operator()(const SUserAward& award)
        {
          return award.userId == cid_;
        }
        Transport::TClientId cid_;
      };

      struct UserAwardInfoFinder
      {
        UserAwardInfoFinder(roll::EAwardType::Enum awardType) : awardType_(awardType){}

        bool operator()(const SAwardInfo& award)
        {
          return award.type == awardType_;
        }
        roll::EAwardType::Enum awardType_;
      };

      //---------------------------------------------------------------------------------------------------------------------------------

      typedef vector<buff::RollBonus*> RollBonusCollection;
      RollBonusCollection bonuses;

      Transport::TClientId cid = userPreData.clientId;

      buff::RollBonusHolder& bonusHolder = rollBonusDataCache->GetUserBonuses(cid);
      bonusHolder.GetAllBonuses(bonuses);

      if(!bonuses.size())
      {
        ROLL_LOG_DBG("Client %d does not have any bonuses.", cid);
        return;
      }

      SUserAwardCollection::iterator awardIterator = nstl::find_if(userAwards.begin(), userAwards.end(), UserAwardFinder(cid));
      if(awardIterator == userAwards.end())
      {
        ROLL_LOG_ERR("No awards collection for client %d found.", cid);
        return;
      }

      RollBonusCollection::const_iterator bonusIterator = bonuses.begin();
      for(;bonusIterator != bonuses.end();++bonusIterator)
      {
        if(!bonusIterator) continue;
        buff::RollBonus* bonus = (*bonusIterator);
        if(!bonus) continue;

        roll::EAwardType::Enum awardType = bonus->GetType();

        // NUM_TASK
//         if(!awardIterator->playerWin)
//         {
//           ROLL_LOG_DBG("All guilds buffs should be apply only for winners (client %d).", cid);
//           continue;
//         }

        SAwardInfo* userAwardInfo = 0;
        bool isNew = false;
          
        SAwardInfoCollection::iterator awardInfoIterator = nstl::find_if(awardIterator->awards.begin(), awardIterator->awards.end(), UserAwardInfoFinder( awardType ));
        if(awardInfoIterator != awardIterator->awards.end())
        {
          userAwardInfo = awardInfoIterator;
        }
        else if(awardType != roll::EAwardType::Talent)
        {
          isNew = true;
          ROLL_LOG_DBG ("Award of type %s not found. Creating new one for client %d.", roll::EAwardType::ToString(awardType), cid);
          userAwardInfo = &awardIterator->awards.push_back();
          userAwardInfo->isOwnedByPlayer = true;
          userAwardInfo->type = awardType;
          userAwardInfo->giverUser = userPreData.clientId;
        }

        switch(awardType)
        {
        case roll::EAwardType::Talent:
          {
            buff::RollBonusContext rollBonusContext(bonus);
            RollTalentsBuff((*awardIterator), &rollBonusContext, settings, userPreData);

            if(rollBonusDataCache->GetStatistics() && rollBonusContext.isApplied)
            {
              rollBonusDataCache->GetStatistics()->Add(cid, bonus->GetBuffIDs());
              ROLL_LOG_DBG( "Award buff has applied (talents buff id=%s count=%d user=%d)", bonus->GetComposedID(), bonus->GetAdd(), cid );
            }
          }
          break;
        default:
          {
            float bonusValue = rollBonusDataCache->ApplyBuff<float>(cid, *userAwardInfo);
            if(rollBonusDataCache->hasBonusValue(*userAwardInfo))
            {
              userAwardInfo->count += bonusValue;
              //TODO: бонусы могут быть теперь комбинированные - надо допилить нормальное логгирование всех id
              ROLL_LOG_DBG( "Award buff has applied (buff id=%s type=%s count=%d (%d) user=%d)", userAwardInfo->bonus.id, roll::EAwardType::ToString(userAwardInfo->type), userAwardInfo->count, userAwardInfo->bonus.count, cid );
            }
            else
            {
              ROLL_LOG_DBG( "No bonusValue after the buff has applied (buff id=%s type=%s user=%d)", userAwardInfo->bonus.id, roll::EAwardType::ToString(userAwardInfo->type),  userAwardInfo->bonus.count, cid );
              if (isNew)
                awardIterator->awards.pop_back();
            }
          }
        }
      }
    }


    void DropNRoll::ApplyBuffs(vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg )
    {

      ROLL_LOG_MSG("Buff apply has begun.");

      for(int userIdx = 0; userIdx < _preGame.users.size(); ++userIdx)
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIdx];
        const SPostGamePerUserData & userPostData = _postGame.users[userIdx];

        if(userPostData.statistics.clientState == Peered::EGameFinishClientState::FinishedGame)
          ApplyBuffsOnUserAwards(userPreData, _rollResult, settings);
        else
        {
          ROLL_LOG_DBG("Client %d not finished game, skip buff calculation.", userPreData.clientId );
        }
      }

      ROLL_LOG_MSG("All buffs has applied.");
    }


    void DropNRoll::RollAwards( vector<SUserAward> & _rollResult, map<NCore::TGuildAuid, SGuildAward> & _guildAwards, const SPreGameData & _preGame, const SPostGameData & _postGame )
    {
      NI_PROFILE_FUNCTION;

      NI_VERIFY( _preGame.users.size() == _postGame.users.size(), "Inconsistent user number in pre and post-game data", return );
      int userCount = _postGame.users.size();
      for ( int i = 0; i < userCount; ++i )
        NI_VERIFY( _preGame.users[i].clientId == _postGame.users[i].clientId, "Wrong clients order in roll data", return );

      StrongMT<RollConfig> _cfg = config->Cfg();

      ROLL_LOG_DBG("Roll amount modifiers (for %s game): talents=%.1f resources=%.1f exp=%.1f", IsPvPGameMode(_preGame) ? "PVP" : "PVE",
        IsPvPGameMode(_preGame) ? _cfg->pvpTalentsAmountModifier : _cfg->pveTalentsAmountModifier, _cfg->resourcesAmountModifier,
        _cfg->expAmountModifier );

      //Basic actions
      _rollResult.clear();
      _rollResult.resize( userCount );

      _guildAwards.clear();


      NI_VERIFY( rollSettings, "Common roll settings not found, awarding skipped", return );

      NDb::Ptr<NDb::AdvMapDescription> advMapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( _preGame.mapDesc ) );
      NI_VERIFY( advMapDesc, NI_STRFMT( "Map desc \"%s\" not found, awarding skipped", _preGame.mapDesc ), return );

      NDb::Ptr<NDb::ModeRollSettings> settings = advMapDesc->rollSettings;

      ROLL_LOG_DBG("Specified roll setting: %s", _preGame.mapDesc.c_str() );


      //init rollBuffs
      rollBonusDataCache->InitDataCache(advMapDesc, _preGame.sessionType);


      for ( int userIndex = 0; userIndex < userCount; ++userIndex )
      {
        const SPreGamePerUserData & userPreGame = _preGame.users[userIndex];
        Transport::TClientId clientId = userPreGame.clientId;

        SUserAward & userAward = _rollResult[userIndex];
        userAward.userId = clientId;

        //collect rollBuffs
        rollBonusDataCache->CollectBuffs(clientId, userPreGame.playerInfo.aBuffs);

        // Pass talent roll data anyways
        rollDataCache->GetCorrectData( userAward.talentRollData, userPreGame.playerInfo.talentRollData, clientId );
        userAward.talentRollData.generationIndex += 1;

        ROLL_LOG_DBG( "Player info loaded1 (user=%d heroId=%d heroEnergy=%d avatarLevel=%d heroLevel=%d hsHealth=%.2f hsMana=%.2f hsStrength=%.2f hsIntellect=%.2f)",
          clientId,
          userPreGame.playerInfo.heroId, 
          userPreGame.playerInfo.heroEnergy, 
          userPreGame.playerInfo.avatarLevel, 
          userPreGame.playerInfo.heroLevel,
          userPreGame.playerInfo.hsHealth,
          userPreGame.playerInfo.hsMana,
          userPreGame.playerInfo.hsStrength,
          userPreGame.playerInfo.hsIntellect
          );
        ROLL_LOG_DBG( "Player info loaded2 (user=%d hsAgility=%.2f hsCunning=%.2f hsFortitude=%.2f hsWill=%.2f heroExp=%d)",
          clientId,
          userPreGame.playerInfo.hsAgility,
          userPreGame.playerInfo.hsCunning,
          userPreGame.playerInfo.hsFortitude,
          userPreGame.playerInfo.hsWill,
          userPreGame.playerInfo.heroExp
          );
        ROLL_LOG_DBG( "Player info loaded3 (user=%d heroRating=%.2f, playerRating=%.2f, dropRate=%.2f, fwod=%d, goldLampRollContainer='%s', hasFullLibrary=%d)",
          clientId,
          userPreGame.playerInfo.heroRating,
          userPreGame.playerInfo.playerRating,
          userPreGame.playerInfo.dropRate,
          userPreGame.playerInfo.fwod,
          userPreGame.playerInfo.goldLampRollContainer,
          userPreGame.playerInfo.hasFullLibrary
          );
        ROLL_LOG_DBG( "Player info loaded4 (user=%d guildData: id=%d, level=%d, buildingLevel=%d, rating=%.2f)",
          clientId,
          userPreGame.playerInfo.guildData.id,
          userPreGame.playerInfo.guildData.level,
          userPreGame.playerInfo.guildData.buildingLevel,
          userPreGame.playerInfo.guildData.rating
          );

        ROLL_LOG_DBG( "Player info loaded5 (user=%d rollBuff=[%s])",
          clientId,
          rollBonusDataCache->GetPlayerBonusesAsString(clientId)
          );
      }

      bool playerWin = false;
      bool disconnectedWin = (!settings) ? false : settings->teamWinDisconnectedWin;

      // Detect winners and leavers
      for ( int userIndex = 0; userIndex < _rollResult.size(); ++userIndex )
      {
        const SPreGamePerUserData & userPreData = _preGame.users[userIndex];
        const SPostGamePerUserData & userPostData = _postGame.users[userIndex];

        playerWin = _postGame.victoriousFaction == userPreData.faction;

        if( playerWin )
          _rollResult[userIndex].playerWin = true;

        if ( userPostData.statistics.clientState != Peered::EGameFinishClientState::FinishedGame &&
          !(disconnectedWin && playerWin) )
          _rollResult[userIndex].playerLeaver = true;

        _rollResult[userIndex].hadPreGameLobby = ( _preGame.mode == EMode::LobbyPvp );
      }

      // Tutorial may have no roll settings
      if ( !settings )
      {
        ROLL_LOG_DBG( "No game mode roll settings defined for %s, awarding skipped", _preGame.mapDesc.c_str() );
        return;
      }


      // Cancel awarding on short games
      if ( settings->minSessionDuration > 0 && _postGame.totalSeconds < (uint)settings->minSessionDuration )
      {
        ROLL_LOG_DBG( "Awarding disabled for due to a short game duration. game=%016x, duration=%d", _preGame.socialLobbyGameId, _postGame.totalSeconds );

        UpdateRollDataCache( _rollResult );

        return;
      }

      // Uncommon session result. No awarding
      if ( _postGame.gameResult != lobby::EGameResult::SyncResults || _postGame.victoriousFaction == lobby::ETeam::None )
      {
        ROLL_LOG_DBG( "Invalid session results: %s. Awarding skipped.", lobby::EGameResult::ToString( _postGame.gameResult ) );

        UpdateRollDataCache( _rollResult );

        return;
      }

      // Custom game awarding: only hero endurance
      if ( _preGame.mode == EMode::CustomGame )
      {
        ROLL_LOG_DBG( "Awarding for custom game. game=%016x", _preGame.socialLobbyGameId );
        return;
      }

      RollReliabilityAndDodge( _rollResult, settings, _preGame, _postGame );

      RollRating( _rollResult, settings, _preGame, _postGame, advMapDesc );

      AwardHeroEnergy( _rollResult, settings, _preGame, _postGame );

      AwardHeroExperienceAndFame( _rollResult, settings, _preGame, _postGame, _cfg );

      RollContainers( _rollResult, settings, _preGame, _postGame, _cfg );

      RollEndurance( _rollResult, settings, _preGame, _postGame );

      RollFWOD( _rollResult, settings, _preGame, _postGame, _cfg );

      ApplyPremium( _rollResult, settings, _preGame, _postGame, _cfg );

      RollMarketingEvents( _rollResult, _preGame, _postGame );

      RollGuildMembersAwards( _rollResult, settings, _preGame, _postGame );

      ClanWarsAwardsSettingsHolder cwSettings(settings->clanWarsSettings.GetPtr(), advMapDesc->teamSize, settings);
      GuildWarEventrPointsCalculator cwAwardsCalculator(cwSettings, _preGame, _postGame);
      RollClanWarUsersAwards(_rollResult, cwAwardsCalculator);
      ApplyBuffs(_rollResult, settings, _preGame, _postGame, _cfg);

      RollGuildAwards( _guildAwards, settings, _preGame, _postGame, advMapDesc );
      PrepareClanWarGuildsAwards(_rollResult, _guildAwards, cwAwardsCalculator);

      UpdateRollDataCache( _rollResult );
      UpdateRollBuffStatistics( _rollResult );
    }

    void DropNRoll::UpdateRollBuffStatistics(vector<SUserAward> & _rollResult)
    {
      if(rollBonusDataCache && rollBonusDataCache->GetStatistics())
      {
        rollBonusDataCache->GetStatistics()->Upload( _rollResult );
      }
    }

    void DropNRoll::UpdateRollDataCache( vector<SUserAward> & _rollResult )
    {
      for ( int i = 0; i < _rollResult.size(); ++i )
        rollDataCache->Put( _rollResult[i].userId, _rollResult[i].talentRollData );
    }

    void DropNRoll::RollForge( SUserAward & _award, const SForgeRollData & _data )
    {
      NDb::RollContainer const* pDBForgeRollCont = rollSettings->forgeRollSettings.rollContainer;

      Transport::TClientId clientId = _data.uid;
      _award.userId = clientId;
      rollDataCache->GetCorrectData( _award.talentRollData, _data.talentRollData, clientId );
      _award.talentRollData.generationIndex += 1;

      RollInputData userPreData;
      userPreData.clientId = clientId;
      userPreData.allowedRollGroups = rollSettings->forgeRollSettings.allowedRollGroups;

      RollContext ctx;
      ctx.talentsAlwaysOwnedByPlayer = true;
      ctx.talentRollItems = &_award.talentRollData.rollTable["forge_roll"];
      /*ctx.rollAsPremium = _data.premium;*/

      ValidateRollData( ctx, pDBForgeRollCont,rollSettings->forgeRollSettings.version, userPreData.clientId );

      for ( int rollNumber = 0, totalRollCnt = _data.count; rollNumber < totalRollCnt; rollNumber++ )
      {
        RollPlayersAwardsFromContainer( _award.awards, ctx, pDBForgeRollCont, userPreData );
      }

      rollDataCache->Put( clientId, _award.talentRollData );
    }

    ///////////////////////////////////////////////////////////////////////////////


    GuildWarEventrPointsCalculator::GuildWarEventrPointsCalculator( const ClanWarsAwardsSettingsHolder& cwSettings, const SPreGameData& preGame, const SPostGameData& postGame)
      :  cwSettings_(cwSettings), preGame_(preGame), postGame_(postGame)
    {
      CollectClanMembersData();
    }

    bool GuildWarEventrPointsCalculator::CollectClanMembersData()
    {
      struct PlayerFinder
      {
        PlayerFinder(Transport::TClientId pid): pid_(pid){}
        bool operator()(const SPostGamePerUserData& data)
        {
          return data.clientId == pid_;
        }
        Transport::TClientId pid_;
      };

      vector<roll::SPreGamePerUserData>::const_iterator pguIter = preGame_.users.begin();
      lobby::ETeam::Enum victoriousFaction = postGame_.victoriousFaction;

      for(;pguIter != preGame_.users.end(); ++pguIter)
      {
        Transport::TClientId clientId = pguIter->clientId;

        //check for user clan (guildData.id > 0)
        lobby::TGuildAuid clanId = pguIter->playerInfo.guildData.id;
        if(clanId > 0 && pguIter->playerInfo.guildData.guidWarEventPass)
        {
          bool isWinner = pguIter->faction == victoriousFaction;
          
          vector<SPostGamePerUserData>::const_iterator mit = find_if(postGame_.users.begin(), postGame_.users.end(), PlayerFinder(clientId));
          NI_VERIFY( mit != postGame_.users.end(), NI_STRFMT("Can't find pregame user id [%d] in post game users", clientId), continue );

          clansData_.AddMember(clanId, clientId, isWinner, pguIter->faction, mit->scoring.score, pguIter->playerInfo.hasPremium);
        }

        // подсчитываем кол-во чуваков в пати в команде, чтобы потом дать бонус клановых очков, если против како-го то юзера играли юзеры в пати
        if(pguIter->playerInfo.partyId > 0)
        {
          ++playersInParties_[pguIter->faction];
        }
      }

      return true;
    }

    int GuildWarEventrPointsCalculator::GetMaxHeroRankInTeam(lobby::ETeam::Enum team)
    {

      typedef nstl::map<int, int> RatingsCountMap;
      typedef nstl::map<uint, vector<PartyUser>> PartyData;
      typedef vector<PartyUser> PartyUsers;

      int count_ = 0;
      int rank_ = 0;
      RatingsCountMap ratings;
      PartyData parties;

      //prepare parties data
      TSPreGamePerUserDataUsers::const_iterator uit = preGame_.users.begin();
      for (;uit != preGame_.users.end(); ++uit)
      {
        if(team == uit->faction)
        {
          parties[uit->playerInfo.partyId].push_back(PartyUser(uit->playerInfo.partyId, uit->clientId, uit->playerInfo.heroRating));
        }
      }

      struct rank_asc
      {
        bool operator() (const PartyUser& i,const PartyUser& j) { return (i.rank_ < j.rank_);}
      }rank_asc_;

      //update_ratings
      PartyData::iterator pit = parties.begin();
      for (;pit != parties.end(); ++pit)
      {
        if(pit->first != 0)
        {
          sort(pit->second.begin(), pit->second.end(), rank_asc_);
          int max_rank = pit->second[pit->second.size() - 1].rank_;
          int new_rank = max_rank - 1;

          PartyUsers::iterator uit = pit->second.begin();
          for(;uit != pit->second.end();++uit)
          {
            if(uit->rank_ < max_rank){
              uit->rank_ = new_rank;
            }
          }
        }
      }

      //calc rating groups
      pit = parties.begin();
      for (;pit != parties.end(); ++pit)
      {
        PartyUsers::iterator uit = pit->second.begin();
        for(;uit != pit->second.end(); ++uit)
        {
          count_ = max(count_, ++ratings[uit->rank_]);
        }
      }

      // get max rank
      RatingsCountMap::const_iterator rit = ratings.begin();

      for (;rit != ratings.end(); ++rit)
      {
        if(rit->second == count_){
          rank_ = max(rank_, rit->first);
        }
      }

      return rank_;
    }

    bool GuildWarEventrPointsCalculator::IsTeamFullParty(lobby::ETeam::Enum team)
    {
      bool isFullParty = false;
      //full party size is teamSize - 1
      int fullPartyFromPlayersCount = cwSettings_.GetTeamSize() - 1;

      nstl::map<uint, int> paties;

      TSPreGamePerUserDataUsers::const_iterator uit = preGame_.users.begin();
      for (;uit != preGame_.users.end(); ++uit)
      {
        if(team == uit->faction)
        {
          uint partiyId = uit->playerInfo.partyId;
          if(partiyId)
          {
            ++paties[partiyId];
            if(paties[partiyId] >= fullPartyFromPlayersCount)
            {
              isFullParty = true;
              break;
            }
          }
        }
      }

      return isFullParty;
    }

    bool GuildWarEventrPointsCalculator::IsValidSettings() const
    {
      if (!cwSettings_.GetSettings() || !IsPvPGameMode(preGame_))
        return false;

      return true;
    }
    void GuildWarEventrPointsCalculator::CalculatePoints( vector<roll::SUserAward> & playersAwards  )
    {

      lobby::ETeam::Enum foeTeam = postGame_.victoriousFaction == lobby::ETeam::Team1 ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
      int foeInPartyCount = GetFoeInPartiesCount(foeTeam);
      float foeCountsModifierBonus = GetFoeCountsModifierBonus(foeInPartyCount);
      float basePoints = cwSettings_.GetSettings()->basePoints;
      float clanPointsMultiplier = cwSettings_.GetSettings()->clanPoints;
      bool normalizeBySessionScores = cwSettings_.GetSettings()->normalizeBySessionScores; 
      

      int rank = GetMaxHeroRankInTeam(foeTeam);
      float defeatedFoeRankModifierBonus = GetDefeatedFoeRankModifierBonus(rank);

      nstl::vector<roll::SUserAward>::iterator awIter = playersAwards.begin();
      for(;awIter != playersAwards.end(); ++awIter)
      {
        // NUM_TASK
        // if(!awIter->playerWin) continue;
        
        //check player clan
        const ClanDataAgregator::ClanMemberData* clanMember = clansData_.FindMember(awIter->userId);
        if(!clanMember || clanMember->cid_ == 0) continue;
      
        float sessionScoreModifier = 1.0f;
        if(normalizeBySessionScores)
          sessionScoreModifier = clanMember->sessionScore/cwSettings_.GetRollSettings()->scoresCap;
        
        float playerPoints = 0.f;
        //calculate clan wars points
        float partyClanMembersModifierBonus = GetPartyClanMembersModifierBonus(clanMember->cid_);

        if(clansData_.IsClanInBothTeam(clanMember->cid_))
        {
          playerPoints = basePoints + defeatedFoeRankModifierBonus;
        }
        else
        {
          playerPoints = basePoints * (1.0f + partyClanMembersModifierBonus + foeCountsModifierBonus) + defeatedFoeRankModifierBonus;
        }

        playerPoints *= sessionScoreModifier;

        float clanPoints = playerPoints * clanPointsMultiplier;

        playerPoints = Round(playerPoints - clanPoints);
        clanPoints = Round(clanPoints);

        ROLL_LOG_DBG( "Award (type=%s count=%d user=%d)", roll::EAwardType::ToString(roll::EAwardType::ClanWarsPlayerRating), playerPoints, awIter->userId );
        ROLL_LOG_DBG( "Award (type=%s count=%d user=%d)", roll::EAwardType::ToString(roll::EAwardType::ClanWarsClanRating), clanPoints, awIter->userId );

        //add awards
        awIter->awards.push_back(SAwardInfo(roll::EAwardType::ClanWarsPlayerRating, 0, playerPoints, 0, true, clanMember->hasPremium_));
        awIter->awards.push_back(SAwardInfo(roll::EAwardType::ClanWarsClanRating, 0, clanPoints, 0, true)); // это в разборе наград отправляется в статистику и в пересчет рейтинга мембера и только
        awIter->awards.push_back(SAwardInfo(roll::EAwardType::GuildWarEventPoints, 0, clanPoints, 0, true)); // это не уйдет в персональных наградах, а будет агрегированно в гильдейскую
      }
    }

    void GuildWarEventrPointsCalculator::FinalizeClanWarAwards(vector<roll::SUserAward> & playersAwards, map<NCore::TGuildAuid, SGuildAward>& guildAwards)
    {
      // аггрегируем очки стратегии (клана) и очки клановго ивента от всех мемберов в клановую награду, а так же применяем премиум к очкам тактики (игрока)

      struct UserAwardInfoFinder
      {
        UserAwardInfoFinder(roll::EAwardType::Enum awardType) : awardType_(awardType){}

        bool operator()(const SAwardInfo& award)
        {
          return award.type == awardType_;
        }
        roll::EAwardType::Enum awardType_;
      };

      vector<roll::SUserAward>::iterator awIter = playersAwards.begin();
      for(;awIter != playersAwards.end(); ++awIter)
      {
        // NUM_TASK
        // if(!awIter->playerWin) continue;

        //check player clan
        const ClanDataAgregator::ClanMemberData* clanMember = clansData_.FindMember(awIter->userId);
        if(!clanMember || clanMember->cid_ == 0) continue;

        SAwardInfo* userAwardInfo = 0;

        vector<roll::SAwardInfo>::iterator awardInfoIterator;

        if ( clanMember->hasPremium_ )
        {
          // игрокам с премиумом может приехать больше поинтов, если дизайнеры соблаговолят
          //суммируем, чтобы отправить в гильдию клановые очки от всех мемберов победивших в бою
          awardInfoIterator = find_if(awIter->awards.begin(), awIter->awards.end(), UserAwardInfoFinder(roll::EAwardType::ClanWarsPlayerRating));
          if(awardInfoIterator != awIter->awards.end())
          {
            userAwardInfo = awardInfoIterator;
            userAwardInfo->count *= cwSettings_.GetSettings()->premiumAccountModifier;
          }
        }

        //суммируем, чтобы отправить в гильдию клановые очки от всех мемберов победивших в бою
        awardInfoIterator = find_if(awIter->awards.begin(), awIter->awards.end(), UserAwardInfoFinder(roll::EAwardType::ClanWarsClanRating));
        if(awardInfoIterator != awIter->awards.end())
        {
          userAwardInfo = awardInfoIterator;
          AddClanPoints(guildAwards, clanMember->cid_, userAwardInfo->count, roll::EAwardType::ClanWarsClanRating);
        }
        
        //а теперь подсчитаем сколько всего очков из пула выжрал клан за этот бой
        awardInfoIterator = find_if(awIter->awards.begin(), awIter->awards.end(), UserAwardInfoFinder(roll::EAwardType::GuildWarEventPoints));
        if(awardInfoIterator != awIter->awards.end())
        {
          userAwardInfo = awardInfoIterator;
          AddClanPoints(guildAwards, clanMember->cid_, userAwardInfo->count, roll::EAwardType::GuildWarEventPoints);

          //удалим из личных наград, ибо они там не нужны более
          awIter->awards.erase(awardInfoIterator);
        }
      }
    }

    void GuildWarEventrPointsCalculator::AddClanPoints( map<NCore::TGuildAuid, SGuildAward>& guildAwards, NCore::TGuildAuid clanId, float count, roll::EAwardType::Enum pointsType )
    {
      if (guildAwards.find(clanId) == guildAwards.end())
        guildAwards[clanId] = roll::SGuildAward(clanId);
      
      roll::SGuildAward& currentGuildAwards = guildAwards[clanId];
      

      ROLL_LOG_DBG( "Add clan rating (clan id=%d)", clanId);

      // try to update award of type ClanWarsClanRating
      vector<roll::SAwardInfo>::iterator ait = RollTools::FindAwardByType(currentGuildAwards.awards, pointsType);
      if(ait != currentGuildAwards.awards.end())
      {
        //clan and award of desired type found 
        ait->count += count;
        ROLL_LOG_DBG( "Award (type=%s count=%d (sum=%d) clan id=%d)", roll::EAwardType::ToString(pointsType), count, ait->count, clanId );

      }
      else
      {
        //new award of this type for clan
        currentGuildAwards.awards.push_back(SAwardInfo(pointsType, 0, count, 0, true, false, false, 0, true));
        ROLL_LOG_DBG( "Award (type=%s count=%d clan id=%d)", roll::EAwardType::ToString(pointsType), count, clanId );
      }
    }

    float GuildWarEventrPointsCalculator::GetPartyClanMembersModifierBonus(lobby::TGuildAuid clanId)
    {
      float partyClanMembersModifier = 0.f;

      if(!cwSettings_.GetSettings()->partyClanMembersModifier.size())
      {
        return partyClanMembersModifier;
      }

      int membersCount = clansData_.MembersCount(clanId);
      if(membersCount > 0)
      {
        nstl::vector< NDb::BaseModifierFromQuantity >::const_iterator iter = cwSettings_.GetSettings()->partyClanMembersModifier.begin();
        for(;iter != cwSettings_.GetSettings()->partyClanMembersModifier.end(); ++iter)
        {
          if(iter->quantity == membersCount){
            partyClanMembersModifier = iter->percent;
            break;
          }
        }
      }

      return partyClanMembersModifier;
    }

    float GuildWarEventrPointsCalculator::GetFoeCountsModifierBonus(int foeCount)
    {
      float foeCountsModifier = 0.f;

      if(!cwSettings_.GetSettings()->foeCountsModifier.size())
      {
        return foeCountsModifier;
      }

      nstl::vector< NDb::BaseModifierFromQuantity >::const_iterator iter = cwSettings_.GetSettings()->foeCountsModifier.begin();
      for(;iter != cwSettings_.GetSettings()->foeCountsModifier.end(); ++iter)
      {
        if(iter->quantity == foeCount){
          foeCountsModifier = iter->percent;
          break;
        }
      }

      return foeCountsModifier;
    }

    float GuildWarEventrPointsCalculator::GetDefeatedFoeRankModifierBonus(float rank)
    {
      float defeatedFoeRankModifier = 0.f;
      size_t modifierSize = cwSettings_.GetSettings()->defeatedFoeRankModifier.size();

      if(!modifierSize || rank < 0 || rank > modifierSize)
      {
        ROLL_LOG_ERR("GetDefeatedFoeRankModifierBonus has wrong rank parameter or defeatedFoeRankModifier is empty");
        return defeatedFoeRankModifier;
      }

      return defeatedFoeRankModifier = cwSettings_.GetSettings()->defeatedFoeRankModifier[rank];
    }

    int GuildWarEventrPointsCalculator::GetFoeInPartiesCount( lobby::ETeam::Enum team )
    {
      TPlayersInParties::const_iterator it = playersInParties_.find(team);
      if(it != playersInParties_.end())
        return it->second;

      return 0;
    }


    void ClanDataAgregator::AddMember( lobby::TGuildAuid cId, Transport::TClientId pId, bool isWinner, lobby::ETeam::Enum team, float score, bool hasPremium)
    {
      clansMembers_[cId].push_back(ClanMemberData(cId, pId, isWinner, team, score, hasPremium));
      if(isWinner)
        clansInWinnerTeam_.push_back(cId);
    }

    size_t ClanDataAgregator::ClansCount()
    {
      return clansMembers_.size();
    }

    const ClanDataAgregator::ClanMemberData* ClanDataAgregator::FindMember( Transport::TClientId pId )
    {
      struct PlayerFinder
      {
        PlayerFinder(Transport::TClientId pid): pid_(pid){}
        bool operator()(const ClanMemberData& data)
        {
          return data.pid_ == pid_;
        }
        Transport::TClientId pid_;
      };

      TClanMembers::const_iterator iter = clansMembers_.begin();
      for(;iter != clansMembers_.end(); ++iter)
      {
        TMembers::const_iterator mit = find_if(iter->second.begin(), iter->second.end(), PlayerFinder(pId));
        if(mit != iter->second.end())
          return mit;
      }

      return 0;
    }

    size_t ClanDataAgregator::MembersCount( lobby::TGuildAuid cid )
    {
      size_t count = 0;

      TClanMembers::const_iterator cmit = clansMembers_.find(cid);
      if(cmit != clansMembers_.end()) 
        count = cmit->second.size();

      return count;
    }

    bool ClanDataAgregator::IsClanInWinnersTeam( lobby::TGuildAuid cid )
    {
      TWinClans::const_iterator wcit = clansInWinnerTeam_.find(cid);
      if(wcit != clansInWinnerTeam_.end())
        return true;

      return false;
    }

    bool ClanDataAgregator::IsClanInBothTeam( lobby::TGuildAuid cid )
    {
      TClanMembers::const_iterator cmit = clansMembers_.find(cid);
      if(cmit != clansMembers_.end()) 
      {
        TMembers::const_iterator iter = cmit->second.begin();
        lobby::ETeam::Enum team = iter->team_;
        for(;iter != cmit->second.end(); ++iter)
        {
          if(team != iter->team_)
          {
            return true;
          }
        }
      }

      return false;
    }


  } //namespace roll

  NI_DEFINE_REFCOUNT( roll::DropNRoll );
