#pragma once

#include "RollTypes.h"
#include "RollTools.h"
#include "Db/DBServer.auto.h"

namespace roll
{

  namespace buff
  {

    /////////////////////////////////////////////////////////////////////////////////////

    typedef Transport::TClientId ClientID;
    typedef NCore::TAwardsBuffs PlayerBonuses;


    class RollBonusStatistic
    {
      typedef nstl::set<nstl::string> BuffIdCollection;
      typedef nstl::map<ClientID, BuffIdCollection> StatisticCollection;

    public:
      RollBonusStatistic();
      void Add(ClientID cid, const nstl::set<nstl::string>& buffDBIDs);
      void Upload(nstl::vector<SUserAward> & awards);

    private:
      StatisticCollection statCollection_;
    };

    /////////////////////////////////////////////////////////////////////////////////////

    class RollBonus
    {
    public:
      RollBonus();
      RollBonus(const nstl::string& dbid, roll::EAwardType::Enum awardType, float add, float mul);
      RollBonus(const nstl::string& dbid, NDb::EResourceType resType, float add, float mul);

      virtual ~RollBonus();

      void SetBuffId(const nstl::string& id);
      const nstl::string& GetComposedID() const;
      roll::EAwardType::Enum GetType() const;

      template <typename T>
      T Apply(T baseValue)
      {
        if(mul_ <= 0.0f)
          return add_;

        return baseValue * mul_ + add_;
      }

//       template <typename T>
//       T Apply(SAwardInfo& award)
//       {
//         award.bonus.count = Apply<T>(award.count);
//         award.bonus.ids = GetBuffIDs();
// 
//         return award.bonus.count;
//       }

      void Compose(RollBonus* otherBonus, const nstl::string& buffId)
      {
        SetBuffId(buffId);
        mul_ += otherBonus->mul_;
        add_ += otherBonus->add_;
      }

      const nstl::string& GetID() const;
      const nstl::set<nstl::string>& GetBuffIDs() const;
      const float GetAdd() const;

    private:
      float add_;
      float mul_;
      roll::EAwardType::Enum awardType_;
      nstl::string id_;
      nstl::set<nstl::string> buffId_;
      nstl::string composedId_;
    };

    /////////////////////////////////////////////////////////////////////////////////////

    class RollBonusHolder
    {
      typedef nstl::map<roll::EAwardType::Enum, RollBonus*> BonusHolder;

    public:
      RollBonusHolder();
      virtual ~RollBonusHolder();

      bool AddBonus(RollBonus* bonus, const string& buffId);

      template <typename T>
      const RollBonus* ApplyBonus(roll::EAwardType::Enum awardType, T oldValue, T& bonusValue, set<string>& appliedBuffs)
      {
        //afterBuffValue = oldValue;
        RollBonus* bonus = bonusHolder_[awardType];
        if(bonus)
        {
          bonusValue = bonus->Apply<T>(oldValue);
          appliedBuffs = bonus->GetBuffIDs();
        }        
        return bonus;        
      }

//       template <typename T>
//       set<string> ApplyBonus(SAwardInfo& award, T& afterBuffValue)
//       {
//         //T afterBuffValue = 0;
//         set<string> buffIds;
//         RollBonus* bonus = bonusHolder_[award.type];
//         if(bonus)
//         {
//           afterBuffValue = bonus->Apply<T>(award);
//         }        
//         return afterBuffValue;
//       }

      void GetAllBonuses(nstl::vector<RollBonus*>& bonuses);
      RollBonus* GetBonus(roll::EAwardType::Enum awardType);

      static RollBonus* CreateBonus(const NDb::Ptr<NDb::SessionBonus> bonus);

    private:
      BonusHolder bonusHolder_;
    };

    /////////////////////////////////////////////////////////////////////////////////////

    class RollBonusDataCache : public BaseObjectST
    {
      NI_DECLARE_REFCOUNT_CLASS_1( RollBonusDataCache, BaseObjectST );

      typedef Transport::TClientId ClientID;
      typedef NCore::TAwardsBuffs PlayerBonuses;
      typedef nstl::map<ClientID, RollBonusHolder> DataCache;

    public:
      RollBonusDataCache();
      virtual ~RollBonusDataCache();

      nstl::string GetPlayerBonusesAsString(ClientID cid);
      void CollectBuffs(ClientID cid, const PlayerBonuses& bonusStr);

      void InitDataCache(NDb::Ptr<NDb::AdvMapDescription> mapDesc, lobby::ETypeOfSession::Enum sessionType);

      RollBonus* GetBonus(ClientID cid, roll::EAwardType::Enum awardType)
      {
        RollBonusHolder& bonusHolder = dataCache_[cid];
        RollBonus* bonus = bonusHolder.GetBonus(awardType);

        if(!bonus) return 0;
        return bonus;
      }

      RollBonusHolder& GetUserBonuses(ClientID cid)
      {
        return dataCache_[cid];
      }

//       template <typename T>
//       T ApplyBuff(ClientID cid, roll::EAwardType::Enum awardType, T baseValue)
//       {
//         RollBonusHolder& bonusHolder = dataCache_[cid];
//         T afterBuffValue;
//         nstl::string buffId = bonusHolder.ApplyBonus<T>(awardType, baseValue, afterBuffValue);
// 
//         if(statistics_ && baseValue != afterBuffValue)
//           statistics_->Add(cid, buffId);
// 
//         return afterBuffValue;
//       }

      template <typename T>
      T ApplyBuff(ClientID cid, SAwardInfo& award)
      {
        RollBonusHolder& bonusHolder = dataCache_[cid];
        set<string> appliedBuffs;
        T bonusValue = 0;
        const RollBonus* aplliedBonus = bonusHolder.ApplyBonus<T>(award.type, award.count, bonusValue, appliedBuffs);
        
        if (aplliedBonus && !appliedBuffs.empty())
        {
          award.bonus.count = bonusValue;
          award.bonus.id = aplliedBonus->GetComposedID();
          if(statistics_)
            statistics_->Add(cid, appliedBuffs);
        }
        
        return bonusValue;
      }

      static bool hasBonusValue(const SAwardInfo& award)
      {
        return award.bonus.count > 0;
      }

      RollBonusStatistic* GetStatistics() const
      {
        return statistics_;
      }

    private:
      void AddBonus(ClientID cid, const nstl::string& bonusDbid, const nstl::string& bonusInlineId);
      
  //    bool IsValidBonus(const nstl::string& strDbid);
      bool IsValidBonus(const NDb::SessionBonus* bonus);
      
    private:
      NDb::Ptr<NDb::AdvMapDescription> map_;
	    NDb::ESessionType sessionType_;
      DataCache dataCache_;
      RollBonusStatistic* statistics_;
    };

    /////////////////////////////////////////////////////////////////////////////////////

    struct RollBonusContext
    {
      RollBonusContext() : isApplied(false), bonus(0) {}
      RollBonusContext(RollBonus *rollBonus) : isApplied(false), bonus(rollBonus) {}
      
      RollBonus *bonus;
      bool isApplied;
    };

  };
};
