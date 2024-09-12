#include "RollBuff.h"
#include "RollLog.h"

namespace roll
{

  namespace buff
  {

//TODO: comment next line (ROLL_EXTEND_LOG) for release version
#ifndef _SHIPPING
    #define ROLL_EXTEND_LOG 
#endif

    RollBonusStatistic::RollBonusStatistic() {}

    void RollBonusStatistic::Add(ClientID cid, const nstl::set<nstl::string>& buffDBIDs)
    {
      if(!buffDBIDs.empty())
        statCollection_[cid].insert(buffDBIDs.begin(), buffDBIDs.end());
    }
    
   void RollBonusStatistic::Upload(nstl::vector<SUserAward> & awards)
    {
      nstl::vector<SUserAward>::iterator awardIterator = awards.begin();
      for(;awardIterator != awards.end(); ++awardIterator)
      {
        BuffIdCollection& buffs = statCollection_[awardIterator->userId];

        awardIterator->appliedRollBuffs.clear();
        BuffIdCollection::const_iterator buffIdIterator = buffs.begin();

        for(;buffIdIterator != buffs.end(); ++buffIdIterator)
        {
          awardIterator->appliedRollBuffs.insert(*buffIdIterator);
        }
      }
    }

    /////////////////////////////////////////////////////////////////////////

    RollBonus::RollBonus(): awardType_(roll::EAwardType::None), add_(0.0f), mul_(0.0f) {}
    
    RollBonus::RollBonus(const nstl::string& dbid, roll::EAwardType::Enum awardType, float add, float mul)
      : id_(dbid), awardType_(awardType), add_(add), mul_(mul)
    {}

    RollBonus::RollBonus(const nstl::string& dbid, NDb::EResourceType resType, float add, float mul)
      :id_(dbid), add_(add), mul_(mul)
    {
      roll::EAwardType::Enum resourceType;
      
      switch (resType)
      {
      case NDb::RESOURCETYPE_SILVER:    resourceType = EAwardType::Silver; break;
      case NDb::RESOURCETYPE_RESOURCE1: resourceType = EAwardType::Resource1; break;
      case NDb::RESOURCETYPE_RESOURCE2: resourceType = EAwardType::Resource2; break;
      case NDb::RESOURCETYPE_RESOURCE3: resourceType = EAwardType::Resource3; break;
      case NDb::RESOURCETYPE_CRYSTAL: resourceType = EAwardType::Pearl; break;
      case NDb::RESOURCETYPE_REDCRYSTAL: resourceType = EAwardType::RedPearl; break;
      default: resourceType = EAwardType::None;
      }

      awardType_ = resourceType;
    }

    RollBonus::~RollBonus(){}

    roll::EAwardType::Enum RollBonus::GetType() const
    {
      return awardType_;
    }

    const nstl::string& RollBonus::GetID() const
    {
      return id_;
    }

    const nstl::string& RollBonus::GetComposedID() const
    {
      return composedId_;
    }

    void RollBonus::SetBuffId(const nstl::string& id)
    {
      buffId_.insert(id);
      if (!composedId_.empty())
        composedId_ += ",";
      composedId_ += id;
    }

    const nstl::set<nstl::string>& RollBonus::GetBuffIDs() const
    {
      return buffId_;
    }

    const float RollBonus::GetAdd() const
    {
      return add_;
    }

    /////////////////////////////////////////////////////////////////////////

    RollBonusHolder::RollBonusHolder(){}

    RollBonusHolder::~RollBonusHolder()
    {
      RollBonusHolder::BonusHolder::iterator holderIterator;

      for(holderIterator = bonusHolder_.begin(); holderIterator != bonusHolder_.end(); ++holderIterator)
      {
        delete holderIterator->second;
      }
    }

    bool RollBonusHolder::AddBonus(RollBonus* bonus, const string& buffId)
    {
      bool result = false;
      roll::EAwardType::Enum awardType = bonus->GetType();

      if (bonus && awardType != roll::EAwardType::None)
      {
        //NI_VERIFY( bonusHolder_.find(awardType) == bonusHolder_.end(), "already have bonus with that type!", return result );
        if (bonusHolder_.find(awardType) != bonusHolder_.end())
        {
          bonusHolder_[awardType]->Compose(bonus, buffId);
        }
        else
        {
          bonusHolder_[awardType] = bonus;
          bonus->SetBuffId(buffId);
        }
        result = true;
      }

      return result;
    }

    RollBonus* RollBonusHolder::GetBonus(roll::EAwardType::Enum awardType)
    {
      return bonusHolder_[awardType];
    }

    void RollBonusHolder::GetAllBonuses(nstl::vector<RollBonus*>& bonuses)
    {
      BonusHolder::const_iterator bonusIterator = bonusHolder_.begin();
      for(;bonusIterator != bonusHolder_.end(); ++bonusIterator)
      {
        bonuses.push_back(bonusIterator->second);
      }
    }

    RollBonus* RollBonusHolder::CreateBonus(const NDb::Ptr<NDb::SessionBonus> bonus)
    {
      if(!bonus) return NULL;

      nstl::string strDbid = bonus->GetDBID().GetFormatted();

      NDb::HeroExperienceBonus const * heroExperienceBonus = dynamic_cast<NDb::HeroExperienceBonus const *>(bonus.GetPtr());
      if(heroExperienceBonus)
      {
        return new RollBonus(strDbid, roll::EAwardType::Experience, heroExperienceBonus->modifiers.additiveValue, heroExperienceBonus->modifiers.multiplicativeValue);
      }

      NDb::SessionResourceBonus const * sessionResourceBonus = dynamic_cast<NDb::SessionResourceBonus const *>(bonus.GetPtr());
      if(sessionResourceBonus)
      {
        return new RollBonus(strDbid, sessionResourceBonus->resource, sessionResourceBonus->modifiers.additiveValue, sessionResourceBonus->modifiers.multiplicativeValue);
      }

      NDb::SessionTalentsBonus const * sessionTalentsBonus = dynamic_cast<NDb::SessionTalentsBonus const *>(bonus.GetPtr());
      if(sessionTalentsBonus)
      {
        return new RollBonus(strDbid, roll::EAwardType::Talent, sessionTalentsBonus->modifiers.additiveValue, sessionTalentsBonus->modifiers.multiplicativeValue);
      }

      NDb::ClanPointsBonus const * clanPointsBonus = dynamic_cast<NDb::ClanPointsBonus const *>(bonus.GetPtr());
      if(clanPointsBonus)
      {
        return new RollBonus(strDbid, roll::EAwardType::ClanWarsClanRating, clanPointsBonus->modifiers.additiveValue, clanPointsBonus->modifiers.multiplicativeValue);
      }

      NDb::PlayerPointsBonus const * playerPointsBonus = dynamic_cast<NDb::PlayerPointsBonus const *>(bonus.GetPtr());
      if(playerPointsBonus)
      {
        return new RollBonus(strDbid, roll::EAwardType::ClanWarsPlayerRating, playerPointsBonus->modifiers.additiveValue, playerPointsBonus->modifiers.multiplicativeValue);
      }

      return NULL;
    }


    /////////////////////////////////////////////////////////////////////////

    RollBonusDataCache::RollBonusDataCache()
      :map_(NULL), sessionType_(NDb::SESSIONTYPE_ALL)
    {
      try
      {
      statistics_ = new RollBonusStatistic();
      }
      catch(...)
      {
		    ROLL_LOG_DBG("Unable to create RollBonusStatistic.");
      }
    }

    RollBonusDataCache::~RollBonusDataCache()
    {
      delete statistics_;
    }

    void RollBonusDataCache::InitDataCache(NDb::Ptr<NDb::AdvMapDescription> mapDesc, lobby::ETypeOfSession::Enum sessionType)
    {
      dataCache_.clear();

      map_ = mapDesc;

      switch(sessionType)
      {
      case lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE:
        sessionType_  = NDb::SESSIONTYPE_GUILDBATTLE;
        break;
      case lobby::ETypeOfSession::SESSIONTYPE_USUALBATTLE:
        sessionType_  = NDb::SESSIONTYPE_USUALBATTLE;
        break;
      default:
        sessionType_  = NDb::SESSIONTYPE_ALL;
      }

      ROLL_LOG_DBG("Init RollBonusDataCache for map: %s and sessionType : %d", map_->GetDBID().GetFormatted(), (int)sessionType_);
    }

    nstl::string RollBonusDataCache::GetPlayerBonusesAsString(ClientID cid)
    {
      typedef nstl::vector<RollBonus*> RollBonusCollection;
  
      nstl::string buffer;
      RollBonusHolder& bonusHolder = dataCache_[cid];
      
      RollBonusCollection bonuses;
      bonusHolder.GetAllBonuses(bonuses);
      
      RollBonusCollection::const_iterator bonusIterator = bonuses.begin();
      for(; bonusIterator != bonuses.end(); ++bonusIterator)
      {
        if(*bonusIterator && !(*bonusIterator)->GetID().empty())
        {
          buffer += (*bonusIterator)->GetID();
          buffer += ";";
        }
      }
      return buffer;
    }

    void RollBonusDataCache::CollectBuffs(ClientID cid, const PlayerBonuses& bonusStr)
    {

      string strBonus;
      RollTools::VectorToString(bonusStr, strBonus);

      ROLL_LOG_DBG("Begin CollectBuffs (ClientID=%d, bonusStrInput={%s})", cid, strBonus);

      PlayerBonuses::const_iterator bonusStrIterator;
      for(bonusStrIterator = bonusStr.begin(); bonusStrIterator != bonusStr.end(); ++bonusStrIterator)
      {
        if(!bonusStrIterator->empty())
        {
          ROLL_LOG_DBG("Process (ClientID=%d, bonusStr=%s)", cid, *bonusStrIterator);

          size_t delimPos = bonusStrIterator->find(":");
          if(delimPos != nstl::string::npos)
          {
            AddBonus(cid, bonusStrIterator->substr(0, delimPos), bonusStrIterator->substr(delimPos + 1));
          }
          else
          {
            ROLL_LOG_DBG("Process failed (ClientID=%d, bonusStr=%s)", cid, *bonusStrIterator);
          }
        }
      }

      ROLL_LOG_DBG("End CollectBuffs (ClientID=%d)", cid);
    }
/*
    bool RollBonusDataCache::IsValidBonus(const nstl::string& strDbid)
    {
      NDb::Ptr<NDb::SessionValueBonus> bonus = RollBonusHolder::GetDbBonus<NDb::SessionValueBonus>(strDbid);
      if(!bonus)
      {
        ROLL_LOG_DBG("Unable to GetDbBonus(%s) skip this bonus.", strDbid);
        return false;
      }

#ifdef ROLL_EXTEND_LOG
      string maps;
      RollTools::EnumMapsAsString(bonus->gameSettings.maps, maps);
      ROLL_LOG_DBG("Bonus (%s) validation input: sessionType=%d, maps=[%s]", strDbid, (int)bonus->gameSettings.sessionType, maps);
#endif//ROLL_EXTEND_LOG

      bool validationResult = IsValidBonus(bonus);
#ifdef ROLL_EXTEND_LOG
      ROLL_LOG_DBG("Bonus final validation result = %s", (validationResult) ? "Valid" : "Invalid" );
#endif//ROLL_EXTEND_LOG
      return validationResult;
    }*/

    bool RollBonusDataCache::IsValidBonus(const NDb::SessionBonus* bonus)
    {
      typedef nstl::vector< NDb::Ptr< NDb::AdvMapDescription > > AdvMapCollection;
      bool result = false;

      if(!bonus)
      {
        ROLL_LOG_DBG("Invalid bonus pinter, skip this bonus.");
        return result;
      }

      if(bonus->gameSettings.maps.size())
      {
        AdvMapCollection::const_iterator found = bonus->gameSettings.maps.find(map_);
        if(found != bonus->gameSettings.maps.end())
        {
          result = true;
        }
      }
      else
      {
        //valid for any map
        result = true;
      }

#ifdef ROLL_EXTEND_LOG
      string maps;
      RollTools::EnumMapsAsString(bonus->gameSettings.maps, maps);
      ROLL_LOG_DBG("Bonus (%s) validation input: sessionType=%d, maps=[%s]", bonus->GetDBID().GetFormatted(), (int)bonus->gameSettings.sessionType, maps);
      ROLL_LOG_DBG("Bonus gameSettings.maps validation result = %d", result); 
#endif//ROLL_EXTEND_LOG
      bool sessionTypeValidationResult = (bonus->gameSettings.sessionType == NDb::SESSIONTYPE_ALL || bonus->gameSettings.sessionType == sessionType_);
#ifdef ROLL_EXTEND_LOG
      ROLL_LOG_DBG("Bonus gameSettings.sessionType validation result = %d", sessionTypeValidationResult); 
#endif//ROLL_EXTEND_LOG
      result = result && sessionTypeValidationResult;

      return result;
    }

    void RollBonusDataCache::AddBonus(ClientID cid, const nstl::string& buffDBid, const nstl::string& bonusInlineId)
    {
      typedef nstl::vector< NDb::Ptr< NDb::GuildShopItemBonus > > BuffBonuses;

      ROLL_LOG_DBG("Try to AddBonus (%s)  for ClientID (%d)", buffDBid, cid);

      NDb::Ptr<NDb::GuildBuff> pBuff = NDb::Get<NDb::GuildBuff>( NDb::DBID(buffDBid) );
      if(!pBuff)
      {
        ROLL_LOG_DBG("Unable to GetDbBonus(%s) skip this bonus.", buffDBid);
        return;
      }

      //find inlined bonus by id
      struct BonusFinder
      {
        BonusFinder(const nstl::string& inlineId): id_(inlineId){} 
        bool operator()(const NDb::GuildShopItemBonus * bonus)
        {
          return bonus && (id_.compare(bonus->GetDBID().GetId()) == 0 );
        }
        nstl::string id_;
      };

      BonusFinder bonusFinder(bonusInlineId);

      BuffBonuses::const_iterator bonusesIterator = nstl::find_if(pBuff->bonuses.begin(), pBuff->bonuses.end(), bonusFinder);

      if(bonusesIterator == pBuff->bonuses.end()) 
      {
        ROLL_LOG_DBG("Bonus (%s) not found in buff %s", buffDBid, pBuff->persistentId);
        return;
      }

      NDb::SessionBonus const * sessionBonus = dynamic_cast<NDb::SessionBonus const *>(bonusesIterator->GetPtr());
     
      //check founded bonus
      if(!sessionBonus || !IsValidBonus(sessionBonus))
      {
        ROLL_LOG_DBG("Bonus (%s) validation failed for ClientID (%d)", buffDBid, cid);
        return;
      }

      RollBonus* bonus = RollBonusHolder::CreateBonus(sessionBonus);
      if(bonus)
      {
        //bonus->SetBuffId(pBuff->persistentId);

        RollBonusHolder& bonusHolder = dataCache_[cid];
        bonusHolder.AddBonus(bonus, pBuff->persistentId);
        ROLL_LOG_DBG("Bonus (%s) was added to client (%d)", buffDBid, cid );
      }
    }

    /////////////////////////////////////////////////////////////////////////
  }
}
