#ifndef _ROLL_LOGIC_DBG_
#define _ROLL_LOGIC_DBG_

#include "RollLogic.h"
#include <bitset>


namespace roll
{
  namespace dbg{

    /////////////////////////////////////////////////////////////////////////////

    template <typename T, int enum_size>
    class EnumFlags{

      typedef std::bitset<enum_size> t_bitset;
    public:
      EnumFlags():type_flags_(){}

      t_bitset& set(T value)
      {
        return type_flags_.set(value);
      }

      t_bitset& set()
      {
        return type_flags_.set();
      }

      t_bitset& reset()
      {
        return type_flags_.reset();
      }

      bool test(T value) const
      {
        return type_flags_.test(value);
      }

      bool any()
      {
        return type_flags_.any();
      }

      int count(){return type_flags_.count();}

    private:
      t_bitset type_flags_;
    };

    typedef EnumFlags<EAwardType::Enum, EAwardType::NumOfAwardTypes> EAwardTypeFlags;

    /////////////////////////////////////////////////////////////////////////////

    //for testing purpose
    class DropNRollTests : public BaseObjectST
    {

      NI_DECLARE_REFCOUNT_CLASS_1( DropNRollTests, BaseObjectST );

    public:

      DropNRollTests(DropNRoll* rollLogic): rollLogic_(rollLogic){}

      void UpdateRollDataCache( vector<SUserAward> & _rollResult )
      {
        rollLogic_->UpdateRollDataCache(_rollResult);
      }

      void CorrectData(vector<SUserAward> & _award,const SPreGameData & _preGame, lobby::TUserId clientId)
      {
        int userCount = _preGame.users.size();

        for ( int userIndex = 0; userIndex < userCount; ++userIndex )
        {
          const SPreGamePerUserData & userPreGame = _preGame.users[userIndex];
          Transport::TClientId clientId = userPreGame.clientId;

          SUserAward & userAward = _award[userIndex];
          userAward.userId = clientId;
          // Pass talent roll data anyways

          Weak<roll::TalentRollDataCache> rollDataCache = rollLogic_->rollDataCache.Get();

          rollDataCache->GetCorrectData( userAward.talentRollData, userPreGame.playerInfo.talentRollData, clientId );
          userAward.talentRollData.generationIndex += 1;
        }
      }
      void FillRollTableFromContainer( const NDb::RollContainer* rollContainer, const int allowedRollGroups ){
        rollLogic_->FillRollTableFromContainer(rollContainer, allowedRollGroups);
      }

      //-----------------------------------------------------------------------

      void RollContainers( )
      {
        rollLogic_->RollContainers( rollResult_, GetRollSettings(), preGame_, postGame_, rollLogic_->GetConfig()->Cfg());
      }

      void RollFWOD( )
      {
        rollLogic_->RollFWOD( rollResult_, GetRollSettings(), preGame_, postGame_, rollLogic_->GetConfig()->Cfg() );
      }

      void RollClanWarsAwards()
      {
        ClanWarsAwardsSettingsHolder cwSettings(GetRollSettings()->clanWarsSettings, GetMap()->teamSize );
        rollLogic_->RollClanWarsAwards(rollResult_, guildAwards_, cwSettings , preGame_, postGame_, rollLogic_->GetConfig()->Cfg());
      }
      void RollRating()
      {
        rollLogic_->RollRating(rollResult_, GetRollSettings(),preGame_, postGame_,GetMap());
      }
      void RollClanWarsAwards(const ClanWarsAwardsSettingsHolder &cwSettings)
      {
        rollLogic_->RollClanWarsAwards(rollResult_, guildAwards_, cwSettings , preGame_, postGame_, rollLogic_->GetConfig()->Cfg());
      }

      //-----------------------------------------------------------------------

      struct UserFinderInGameByClientId{
        UserFinderInGameByClientId(): id_(-1){}
        UserFinderInGameByClientId(int id): id_(id){}
        template<typename T>
        bool operator()(const T& userData){
          return userData.clientId == id_;
        }
        Transport::TClientId id_;
      } ;

      struct UserFinderInUserAwardByUserId{
        UserFinderInUserAwardByUserId(): id_(-1){}
        UserFinderInUserAwardByUserId(int id): id_(id){}
        bool operator()(const roll::SUserAward& userData){
          return userData.userId == id_;
        }
        Transport::TClientId id_;
      } ;

      template<typename T, class finder>
      T* findUserData(nstl::vector<T>& data, int playerId) {
        nstl::vector<T>::iterator iter = find_if(data.begin(), data.end(), finder(playerId));

        if(iter == data.end())
          TS_FAIL("User not found.");

        return iter;
      }

      //-----------------------------------------------------------------------

      void SetupGame(const nstl::string& mapDesc, roll::EMode::Enum mode, uint totalSeconds)
      {
        preGame_.mode = mode;
        preGame_.socialLobbyGameId = 1;
        preGame_.mapDesc = mapDesc;

        postGame_.gameResult = lobby::EGameResult::SyncResults;
        postGame_.totalSeconds = totalSeconds;

        ClenupPreGameData();
        ClenupPostGameData();
      }

      void ClenupPostGameData(){
        vector<roll::SPostGamePerUserData>& vecPostUserData = postGame_.users;
        vecPostUserData.clear();
      }

      void ClenupPreGameData(){
        vector<roll::SPreGamePerUserData>& vecPreUserData = preGame_.users;
        vecPreUserData.clear();
      }

      void ClenupGuildAwards(){
        guildAwards_.clear();
      }

      void ClenupRollResult(){
        rollResult_.clear();
      }

      const NDb::AdvMapDescription* GetMap()
      {
        const NDb::AdvMapDescription* mapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID(preGame_.mapDesc) );
        if(!mapDesc) TS_FAIL("Unable to load AdvMapDescription");
        return mapDesc;
      }
      NDb::Ptr<NDb::RollSettings> GetRollSet()
      {
          return rollLogic_->DbRoot();
      }
      const NDb::ModeRollSettings* GetRollSettings(){
        const NDb::AdvMapDescription* mapDesc = GetMap();

        const NDb::ModeRollSettings* rollSettings = mapDesc->rollSettings;
        NI_VERIFY( rollSettings, "", return 0 );

        return rollSettings;
      }

      void ResetRollResults(){
        int userCount = postGame_.users.size();
        rollResult_.clear();
        rollResult_.resize( userCount );

        for ( int userIndex = 0; userIndex < userCount; ++userIndex )
        {
          const SPreGamePerUserData & userPreGame = preGame_.users[userIndex];
          Transport::TClientId clientId = userPreGame.clientId;

          SUserAward & userAward = rollResult_[userIndex];
          userAward.userId = clientId;
          userAward.talentRollData.generationIndex += 1;

          bool playerWin = postGame_.victoriousFaction == userPreGame.faction;

          if( playerWin )
            rollResult_[userIndex].playerWin = true;
        }
      }

      void SetupPlayerPostGameRatings(int playerId, int newHeroRating, int newPlayerRating)
      {

        roll::SUserAward* userAwards = findUserData<roll::SUserAward, UserFinderInUserAwardByUserId>(rollResult_, playerId);

        if(!userAwards)
        {
          TS_FAIL("Player not found.");
        }
        else
        {
          vector<roll::SAwardInfo>& awards = userAwards->awards;

          roll::SAwardInfo& awardHeroRating = awards.push_back();
          awardHeroRating.type = EAwardType::HeroRating;
          awardHeroRating.count = newHeroRating;

          roll::SAwardInfo& awardPlayerRating = awards.push_back();
          awardPlayerRating.type = EAwardType::PlayerRating;
          awardPlayerRating.count = newPlayerRating;
        }
      }

      void SetupPreGamePlayer(int playerId, lobby::ETeam::Enum faction, uint heroEnergy, float heroRating,
        float heroPlayerRating, bool heroHasPremium, bool heroFwod, NCore::TAwardsBuffs* aBuffs = 0, int partyId = 0)
      {
        vector<roll::SPreGamePerUserData>& vecPreUserData = preGame_.users;
        roll::SPreGamePerUserData & preUserData = vecPreUserData.push_back();
        preUserData.clientId = playerId;
        preUserData.faction = faction;
        preUserData.playerInfo.auid = playerId;
        preUserData.playerInfo.heroEnergy = heroEnergy;
        preUserData.playerInfo.guardRating = 1500;
        preUserData.playerInfo.playerRating = heroPlayerRating;
        preUserData.playerInfo.heroRating = heroRating;
        preUserData.playerInfo.hasPremium = heroHasPremium;
        preUserData.playerInfo.fwod = heroFwod;
        preUserData.playerInfo.partyId = partyId;

        if(aBuffs)
          preUserData.playerInfo.aBuffs = *aBuffs;
      }

      void SetupPlayerClanData(int playerId, NCore::GuildData& clanData)
      {
        roll::SPreGamePerUserData* userData = findUserData<roll::SPreGamePerUserData, UserFinderInGameByClientId>(preGame_.users, playerId);
        userData->playerInfo.guildData = clanData;
      }

      lobby::ETeam::Enum GetOppositeFaction(lobby::ETeam::Enum faction)
      {
        return faction == lobby::ETeam::Team1 ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
      }

      void SetupPostGamePlayer(int playerId, int newHeroRating, int newPlayerRating, uint heroScore, bool isWinner, Peered::EGameFinishClientState::Enum gameFinishClientState)
      {
        lobby::ETeam::Enum victoriousFaction = lobby::ETeam::None;

        const roll::SPreGamePerUserData* userData = findUserData<roll::SPreGamePerUserData, UserFinderInGameByClientId>(preGame_.users, playerId);

        if(isWinner)
        {
          victoriousFaction = userData->faction;
        }
        else
        {
          victoriousFaction = GetOppositeFaction(userData->faction);
        }

        postGame_.victoriousFaction = victoriousFaction;

        vector<roll::SPostGamePerUserData>& vecPostUserData = postGame_.users;
        roll::SPostGamePerUserData & postUserData = vecPostUserData.push_back();
        postUserData.clientId = playerId;
        postUserData.statistics.clientId = playerId;
        postUserData.statistics.clientState = gameFinishClientState;
        postUserData.scoring.score = heroScore;

        ResetRollResults();
        SetupPlayerPostGameRatings(playerId, newHeroRating, newPlayerRating);
      }

      void SetupTestCollections(nstl::vector<int>& test_data){
        const NDb::HeroRanks* pDBHeroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
        typedef nstl::vector<NDb::Rank> TRanksCollection;
        const TRanksCollection &ratings = pDBHeroRanks->ranks;

        int rank = 0;
        const int rating_mod = 1001;

        for(TRanksCollection::const_iterator iter = ratings.begin() + 1; iter != ratings.end(); ++iter)
        {
          test_data.push_back(ratings[rank + 1].rating - rating_mod);
          ++rank;
        }
      }

      //nstl::vector<roll::SUserAward>& GetRollResult(){return rollResult_;}

      int MaxTalents4Rank( int rank )
      {
        int cur_score_cap = GetRollSettings()->scoresCap;
        NDb::Ptr<NDb::RollContainerCostByRank> pDBCostByRank = DropNRoll::DbRoot()->defaultRollContainerCostByRank;
        const vector<float>& costs = pDBCostByRank->costs;

        if (rank < 0 || rank > costs.size()) TS_FAIL("MaxTalents4Rank rank parameter out of rank range");

        return static_cast<int>(static_cast<float>(cur_score_cap) / costs[rank]);
      }

      const roll::EAwardType::Enum GetAwardTypeFromResourceConstraint( const NDb::ResourceRollConstraint type ) const
      {
        switch (type)
        {
        case NDb::RESOURCEROLLCONSTRAINT_SILVER:
          return roll::EAwardType::Silver;
        case NDb::RESOURCEROLLCONSTRAINT_PEARL:
          return roll::EAwardType::Pearl;
        case NDb::RESOURCEROLLCONSTRAINT_RESOURCE1:
          return roll::EAwardType::Resource1;
        case NDb::RESOURCEROLLCONSTRAINT_RESOURCE2:
          return roll::EAwardType::Resource2;
        case NDb::RESOURCEROLLCONSTRAINT_RESOURCE3:
          return roll::EAwardType::Resource3;
        default:
          return roll::EAwardType::Silver;
        }  
      }

      int MaxItemFWOD4Rank(const roll::dbg::EAwardTypeFlags& flags, int rank){
        const NDb::Ptr< NDb::RollContainer > rewCont = GetRollSettings()->FWODRewardContainer;
        const nstl::vector< NDb::RollItemProbability >* items = &rewCont->items;
        nstl::vector< NDb::RollItemProbability >::const_iterator item = items->begin();
        int counter = 0;
        for(;item != items->end(); ++item)
        {
          NDb::ResourceRollItem resItem;
          resItem.OverridableAssign(item->item);
          if(flags.test(GetAwardTypeFromResourceConstraint(resItem.type))){
            nstl::vector< NDb::RollLevelInfo >* itemsFromX = 0;
            //hack!
            if(resItem.type == NDb::RESOURCEROLLCONSTRAINT_PEARL)
              itemsFromX = &resItem.itemsFromLord;
            else
              itemsFromX = &resItem.itemsFromRank;
            nstl::vector< NDb::RollLevelInfo >::const_iterator ifrIter = itemsFromX->begin();
            for(; ifrIter != itemsFromX->end();++ifrIter)
            {
              counter += ifrIter->count;
            }
          }
        }
        return counter;
      }

      int MaxTalentsFWOD4Rank(const roll::dbg::EAwardTypeFlags& flags, int rank)
      {
        const NDb::Ptr< NDb::RollContainerCountByRank > rewCont = GetRollSettings()->containersOnFWOD;

        if(rank > rewCont->counts.size() || rank < 0)
          TS_FAIL("MaxTalentsFWOD4Rank rank parameter out of rank range");

        return rewCont->counts[rank];
      }

      static NCore::GuildData CreateClan(lobby::TGuildAuid id, int level = 1){
        NCore::GuildData clan;
        clan.id = id;
        clan.level = level;

        return clan;
      }

      //static int GetRatingFromRank(int rank){
      //  NDb::Ptr< NDb::HeroRanks > heroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
      //  if(heroRanks && (rank < 0 || rank > heroRanks->ranks.size())) TS_FAIL("rank parameter out of rank range");
      //  return heroRanks->ranks[rank].rating;
      //}

      //static int GetRankFromRating(int rating)
      //{
      //  NDb::Ptr< NDb::HeroRanks > heroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
      //  if(rating < 0 || rating > heroRanks->ranks.size()) return 0;

      //  int rank = 0;
      //  vector< NDb::Rank >::const_iterator rit = heroRanks->ranks.begin();

      //  for(;rit != heroRanks->ranks.end(); ++rit)
      //  {

      //  }

      //  return rank;
      //}

      const SPreGameData& GetPreGame() const
      {
        return preGame_;
      }

      const SPostGameData& GetPostGame() const
      {
        return postGame_;
      }

      nstl::vector<roll::SUserAward>& GetRollResult()
      {
        return rollResult_;
      }

      nstl::vector<roll::SGuildAward>& GetGuildAwards()
      {
        return guildAwards_;
      }

      roll::buff::RollBonusDataCache* GetRollBonusCache() const
      {
        return rollLogic_->rollBonusDataCache;
      }

      void SetSessionType(lobby::ETypeOfSession::Enum type)
      {
        preGame_.sessionType = type;
      }

      Strong<roll::buff::RollBonusDataCache> GetBuffCache()
      {
        return rollLogic_->rollBonusDataCache;
      }

      void UpdateRollBuffStatistics()
      {
        rollLogic_->UpdateRollBuffStatistics( rollResult_ );
      }


    private:
      DropNRoll* rollLogic_;

      roll::SPreGameData       preGame_;
      roll::SPostGameData      postGame_;
      nstl::vector<roll::SUserAward> rollResult_;
      nstl::vector<roll::SGuildAward> guildAwards_;

    };

    /////////////////////////////////////////////////////////////////////////////

  }
}

#endif _ROLL_LOGIC_DBG_
