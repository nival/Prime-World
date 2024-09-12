//!Component('Server/Roll/RollLogic')
//!Component('Server/Db')
//!Component("System/FileSystem/TestFileSystem")

#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include <System/TestSuite.h>
//#include "RollLogic.h"
#include "RollLogicDbg.h"
#include "RollLog.h"
#include "RollTools.h"

#include "PF_GameLogic/PFResourcesCollection.h"
#include "System/FileSystem/WinFileSystem.h"
//#include "System/FileSystem/TestFileSystem.h"
#include "System/FileSystem/FilePath.h"
#include "System/FileSystem/FileUtils.h"

using namespace roll;


struct Test_RollLogic : public CxxTest::TestSuite
{
  StrongMT<roll::IConfigProvider> config;

  virtual void setUpSuite()
  {
    RootFileSystem::RegisterFileSystem( new WinFileSystem( "../../../../../../Data/", false ) );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );
    NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID( "Session.ROOT" ) ) );
    config = roll::CreateConfigFromStatics();
  }

  virtual void tearDownSuite()
  {
    NDb::SessionRoot::InitRoot( 0 );
  }

  int GetAwardCount(const vector<roll::SAwardInfo> & awards, roll::EAwardType::Enum awardType)
  {
    int awardCount = 0;

    for (int i = 0; i < awards.size(); ++i)
    {
      if (awards[i].type == awardType)
      {
        awardCount += awards[i].count;
      }
    }

    return awardCount;
  }

  int GetAwardTypeCount( const vector<roll::SAwardInfo> & awards, roll::EAwardType::Enum awardType )
  {
    int awardCount = 0;

    for (int i = 0; i < awards.size(); ++i)
    {
      if (awards[i].type == awardType)
      {
        awardCount++;
      }
    }

    return awardCount;
  }

  int GetTotalRollAwardsCount( const vector<roll::SUserAward> & rollResult )
  {
    int awards = 0;
    for ( int i = 0, total = rollResult.size(); i < total; ++i )
    {
      awards += rollResult[i].awards.size();
    }
    return awards;
  }

  int GetTotalRollAwardsCountByUserId( const vector<roll::SUserAward> & rollResult, int userId )
  {
    int awards = 0;
    for ( int i = 0, total = rollResult.size(); i < total; ++i )
    {
      if(rollResult[i].userId == userId)
        awards += rollResult[i].awards.size();
    }
    return awards;
  }

  struct ItemCounter{
    ItemCounter():counter_(0.f){}
    float& total() {return counter_;}
    float counter_;
  };

  static float GetTotalRollTalentsCount(const vector<roll::SAwardInfo>& awards, const roll::dbg::EAwardTypeFlags& desired_types){

    struct TalentsCounter : public ItemCounter{
      TalentsCounter(const roll::dbg::EAwardTypeFlags& desired_types):desired_types_(desired_types){}
      void operator()(const roll::SAwardInfo& award){
        if(desired_types_.test(award.type)){
          total() += award.count;
        }
      }
      roll::dbg::EAwardTypeFlags desired_types_;
    };

    TalentsCounter talents_counter(desired_types);
    return nstl::for_each(awards.begin(), awards.end(), talents_counter).total();
  }

  static float GetTotalRollTalentsCountByUserId(const vector<roll::SUserAward> & rollResult, int userId, const roll::dbg::EAwardTypeFlags& desired_types){
    
    struct AwardsCounter: public ItemCounter{
      AwardsCounter(int userId, const roll::dbg::EAwardTypeFlags& desired_types):userId_(userId), desired_types_(desired_types){}
      void operator()(const roll::SUserAward& award){
        if(award.userId == userId_){
          total() += GetTotalRollTalentsCount(award.awards,desired_types_);
        }
      }
      int userId_;
      roll::dbg::EAwardTypeFlags desired_types_;
    };

    AwardsCounter talents_counter(userId, desired_types);
    return nstl::for_each(rollResult.begin(), rollResult.end(), talents_counter).total();
  }

  static int GetTotalRollCountByClanId(const nstl::vector<roll::SGuildAward> & rollResult, int clanId, const roll::dbg::EAwardTypeFlags& desired_types){

    struct AwardsCounter: public ItemCounter{
      AwardsCounter(int clanId, const roll::dbg::EAwardTypeFlags& desired_types):clanId_(clanId), desired_types_(desired_types){}
      void operator()(const roll::SGuildAward& award){
        if(award.guildId == clanId_){
          total() += GetTotalRollTalentsCount(award.awards,desired_types_);
        }
      }
      int clanId_;
      roll::dbg::EAwardTypeFlags desired_types_;
    };

    AwardsCounter talents_counter(clanId, desired_types);
    return nstl::for_each(rollResult.begin(), rollResult.end(), talents_counter).total();
  }


  void Setup2Players( vector<roll::SPreGamePerUserData>& vecPreUserData, vector<roll::SPostGamePerUserData>& vecPostUserData )
  {
    const int id1 = 101;
    const int id2 = 102;

    roll::SPreGamePerUserData & preUserData = vecPreUserData.push_back();
    preUserData.clientId = id1;
    preUserData.faction = lobby::ETeam::Team1;
    preUserData.playerInfo.auid = id1;
    preUserData.playerInfo.heroEnergy = 100;
    preUserData.playerInfo.guardRating = 1500;
    preUserData.playerInfo.playerRating = 1500;
    preUserData.playerInfo.heroRating = 1600;
    preUserData.playerInfo.hasPremium = true;
    preUserData.playerInfo.fwod = true;

    roll::SPreGamePerUserData & preUserData2 = vecPreUserData.push_back();
    preUserData2.clientId = id2;
    preUserData2.faction = lobby::ETeam::Team2;
    preUserData2.playerInfo.auid = id2;
    preUserData2.playerInfo.heroEnergy = 100;
    preUserData2.playerInfo.guardRating = 1500;
    preUserData2.playerInfo.playerRating = 1500;
    preUserData2.playerInfo.heroRating = 1500;
    preUserData2.playerInfo.hasPremium = true;
    preUserData2.playerInfo.fwod = true;

    roll::SPostGamePerUserData & postUserData = vecPostUserData.push_back();
    postUserData.clientId = id1;
    postUserData.scoring.score = 150;
    postUserData.statistics.clientId = id1;
    postUserData.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;

    roll::SPostGamePerUserData & postUserData2 = vecPostUserData.push_back();
    postUserData2.clientId = id2;
    postUserData2.scoring.score = 150;
    postUserData2.statistics.clientId = id2;
    postUserData2.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;
  }

  void Setup2Players( vector<roll::SPreGamePerUserData>& vecPreUserData, vector<roll::SPostGamePerUserData>& vecPostUserData,
    uint hero1Energy, uint hero2Energy, uint hero1score, uint hero2score, float hero1Rating, float hero2Rating,
    float hero1playerRating, float hero2playerRating, bool hero1hasPremium, bool hero2hasPremium, bool hero1fwod, bool hero2fwod)
  {
    const int id1 = 101;
    const int id2 = 102;

    roll::SPreGamePerUserData & preUserData = vecPreUserData.push_back();
    preUserData.clientId = id1;
    preUserData.faction = lobby::ETeam::Team1;
    preUserData.playerInfo.auid = id1;
    preUserData.playerInfo.heroEnergy = hero1Energy;
    preUserData.playerInfo.guardRating = 1500;
    preUserData.playerInfo.playerRating = hero1playerRating;
    preUserData.playerInfo.heroRating = hero1Rating;
    preUserData.playerInfo.hasPremium = hero1hasPremium;
    preUserData.playerInfo.fwod = hero1fwod;

    roll::SPreGamePerUserData & preUserData2 = vecPreUserData.push_back();
    preUserData2.clientId = id2;
    preUserData2.faction = lobby::ETeam::Team2;
    preUserData2.playerInfo.auid = id2;
    preUserData2.playerInfo.heroEnergy = hero2Energy;
    preUserData2.playerInfo.guardRating = 1500;
    preUserData2.playerInfo.playerRating = hero2playerRating;
    preUserData2.playerInfo.heroRating = hero2Rating;
    preUserData2.playerInfo.hasPremium = hero2hasPremium;
    preUserData2.playerInfo.fwod = hero2fwod;

    roll::SPostGamePerUserData & postUserData = vecPostUserData.push_back();
    postUserData.clientId = id1;
    postUserData.scoring.score = hero1score;
    postUserData.statistics.clientId = id1;
    postUserData.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;

    roll::SPostGamePerUserData & postUserData2 = vecPostUserData.push_back();
    postUserData2.clientId = id2;
    postUserData2.scoring.score = hero2score;
    postUserData2.statistics.clientId = id2;
    postUserData2.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;
  }


  /////////////////////////////////////////////////////////////////////////////

  void test_Leaver()
  {
    Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );
    vector<roll::SUserAward> rollResult;
    vector<roll::SGuildAward> guildAwards;
    roll::SPreGameData preGame;
    roll::SPostGameData postGame;

    preGame.mode = roll::EMode::PvP;
    preGame.socialLobbyGameId = 1;
    preGame.mapDesc = "Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb";

    Setup2Players( preGame.users, postGame.users );

    postGame.gameResult = lobby::EGameResult::SyncResults;
    postGame.victoriousFaction = lobby::ETeam::Team2;
    postGame.totalSeconds = 1800;

    roll::SPostGamePerUserData & postUserData2 = postGame.users[1];
    // Leaver
    postUserData2.statistics.clientState = Peered::EGameFinishClientState::Disconnected;

    rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);

    int leaver = -1;
    for ( int i = 0, totalAwards = rollResult.size(); i < totalAwards; ++i )
    {
      if ( rollResult[i].userId == postUserData2.clientId )
      {
        leaver = i;
      }
    }

    TS_ASSERT( leaver != -1 );

    if ( leaver == -1 )
      return;

    TS_ASSERT( rollResult[leaver].playerLeaver );

    vector<roll::SAwardInfo>& awards = rollResult[leaver].awards;

    int talents = 0;
    for ( int i = 0, totalAwards = awards.size(); i < totalAwards; ++i )
    {
      if ( awards[i].type == roll::EAwardType::Talent || awards[i].type == roll::EAwardType::Pearl )
      {
        talents++;
      }
    }

    TS_ASSERT( talents == 0 );

    int reliability = GetAwardCount( awards, roll::EAwardType::Reliability );

    TS_ASSERT( reliability < 0 );

    int heroRating = GetAwardCount( awards, roll::EAwardType::HeroRating );

    TS_ASSERT( heroRating < 0 );
  }

  void test_InvalidSessionResultNoAwards()
  {
    Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );
    vector<roll::SUserAward> rollResult;
    vector<roll::SGuildAward> guildAwards;
    roll::SPreGameData preGame;
    roll::SPostGameData postGame;

    preGame.mode = roll::EMode::PvP;
    preGame.socialLobbyGameId = 1;
    preGame.mapDesc = "Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb";

    Setup2Players( preGame.users, postGame.users );

    // No results
    postGame.gameResult = lobby::EGameResult::NoResults;
    postGame.victoriousFaction = lobby::ETeam::Team2;
    postGame.totalSeconds = 1800;

    rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);

    int awards = GetTotalRollAwardsCount( rollResult );

    TS_ASSERT( awards == 0 );
  }

  void test_ShortGameNoAwards()
  {
    Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );
    vector<roll::SUserAward> rollResult;
    vector<roll::SGuildAward> guildAwards;
    roll::SPreGameData preGame;
    roll::SPostGameData postGame;

    preGame.mode = roll::EMode::PvP;
    preGame.socialLobbyGameId = 1;
    preGame.mapDesc = "Maps/Multiplayer/MOBA/Training.ADMPDSCR.xdb";

    Setup2Players( preGame.users, postGame.users );

    const NDb::AdvMapDescription* mapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( preGame.mapDesc ) );
    NI_VERIFY( mapDesc, "", return );

    const NDb::ModeRollSettings* modeRollSettings = mapDesc->rollSettings;
    NI_VERIFY( modeRollSettings, "", return );

    const float minDuration = modeRollSettings->minSessionDuration;
    NI_VERIFY( minDuration > 0, "Expected valid min session duration", return );

    postGame.gameResult = lobby::EGameResult::SyncResults;
    postGame.victoriousFaction = lobby::ETeam::Team2;
    // set duration less than minDuration
    postGame.totalSeconds = minDuration - 1;

    rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);

    int awards = GetTotalRollAwardsCount( rollResult );

    TS_ASSERT( awards == 0 );
  }

  void test_CustomGameNoAwards()
  {
    Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );
    vector<roll::SUserAward> rollResult;
    vector<roll::SGuildAward> guildAwards;
    roll::SPreGameData preGame;
    roll::SPostGameData postGame;

    // Custom game
    preGame.mode = roll::EMode::CustomGame;
    preGame.socialLobbyGameId = 1;
    preGame.mapDesc = "Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb";

    Setup2Players( preGame.users, postGame.users );

    postGame.gameResult = lobby::EGameResult::SyncResults;
    postGame.victoriousFaction = lobby::ETeam::Team2;
    postGame.totalSeconds = 1800;

    rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);

    int totalAwards = GetTotalRollAwardsCount( rollResult );

    TS_ASSERT( 0 == totalAwards ); 
  }

  void test_VictoryForMissingPlayersOnTournamentMap()
  {

    Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );
    vector<roll::SUserAward> rollResult;
    vector<roll::SGuildAward> guildAwards;
    roll::SPreGameData preGame;
    roll::SPostGameData postGame;

    preGame.mode = roll::EMode::PvP;
    preGame.socialLobbyGameId = 1;

    //tournament map
    preGame.mapDesc = "/Maps/Multiplayer/MOBA/Mod5/_.ADMPDSCR.xdb";

    const NDb::AdvMapDescription* mapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( preGame.mapDesc ) );
    NI_VERIFY( mapDesc, "", return );

    const NDb::ModeRollSettings* modeRollSettings = mapDesc->rollSettings;
    NI_VERIFY( modeRollSettings, "", return );

    TS_ASSERT(modeRollSettings->teamWinDisconnectedWin == true);

    Setup2Players( preGame.users, postGame.users );

    postGame.gameResult = lobby::EGameResult::SyncResults;
    postGame.totalSeconds = 1800;

    roll::SPostGamePerUserData &disconnectedPlayer = postGame.users[0];
    disconnectedPlayer.statistics.clientState = Peered::EGameFinishClientState::Disconnected;
    
    postGame.victoriousFaction = preGame.users[0].faction;
    postGame.victoriousFaction = lobby::ETeam::Team1;

    rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);

    vector<roll::SUserAward>::const_iterator iter = rollResult.begin();

    const roll::SUserAward* userAward = NULL;

    while(iter != rollResult.end())
    {
      userAward = iter++;
      if(userAward->userId == disconnectedPlayer.clientId)
        break;
    }

    TS_ASSERT(userAward->playerLeaver == false);

  }

  /*
  Базовый тест выдачи максимального количества талантов при максимальном количистве очков
  для всех ранков за победу и поражение.
  */

  void test_Roll_Containers_4All_Ranks_4Winner_And_Defeated_With_MaxScore()
  {
    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    const int playerId = 101;

    //map, mode, duration
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    //roll result check awards types
    roll::dbg::EAwardTypeFlags desired_awards_types;
    desired_awards_types.set(EAwardType::Talent).set(EAwardType::Pearl);

    //playerId, playerTeam, heroEnergy, heroRating, heroPlayerRating, heroHasPremium, heroFwod
    rollLogicDbg.SetupPreGamePlayer(playerId, lobby::ETeam::Team1, 50, 1000.f, 1000.f, false, false);

    //prepare and run tests
    nstl::vector<int> test_data;
    rollLogicDbg.SetupTestCollections(test_data);

    const uint hero_score = 200;
    int cur_rank = 0;

    bool is_player_winner = true;

    for(nstl::vector<int>::iterator iter = test_data.begin(); iter != test_data.end(); ++iter, ++cur_rank){

      int rating_delta = *iter;

      //playerId, newHeroRating, newPlayerRating, heroScore, isWinnerFaction, gameFinishClientState
      rollLogicDbg.ClenupPostGameData();
      rollLogicDbg.SetupPostGamePlayer(playerId, rating_delta, rating_delta, hero_score, is_player_winner, Peered::EGameFinishClientState::FinishedGame);

      //roll
      rollLogicDbg.RollContainers();

      int talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);

      TS_ASSERT( talents_count == rollLogicDbg.MaxTalents4Rank(cur_rank));
    }

    cur_rank = 0;
    is_player_winner = false;

    for(nstl::vector<int>::iterator iter = test_data.begin(); iter != test_data.end(); ++iter, ++cur_rank){

      int rating_delta = *iter;

      //playerId, newHeroRating, newPlayerRating, heroScore, isWinnerFaction, gameFinishClientState
      rollLogicDbg.ClenupPostGameData();
      rollLogicDbg.SetupPostGamePlayer(playerId, rating_delta, rating_delta, hero_score, is_player_winner, Peered::EGameFinishClientState::FinishedGame);

      //roll
      rollLogicDbg.RollContainers();

      int talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);

      TS_ASSERT( talents_count == rollLogicDbg.MaxTalents4Rank(cur_rank));
    }

  }

  /*
  Базовый тест выдачи максимального количества талантов за поражение и победу
  при минимальном колличестве очков для всех ранков.
  */

  void test_Roll_Containers_4All_Ranks_4Winner_And_Defeated_With_MinScore()
  {
    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    const int playerId = 101;

    //map, mode, duration
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    //roll result check awards types
    roll::dbg::EAwardTypeFlags desired_awards_types;
    desired_awards_types.set(EAwardType::Talent).set(EAwardType::Pearl);

    //playerId, playerTeam, heroEnergy, heroRating, heroPlayerRating, heroHasPremium, heroFwod
    rollLogicDbg.SetupPreGamePlayer(playerId, lobby::ETeam::Team1, 50, 1000.f, 1000.f, false, false);

    //prepare and run tests
    nstl::vector<int> test_data;
    rollLogicDbg.SetupTestCollections(test_data);

    const uint hero_score = 0;
    int cur_rank = 0;

    bool is_player_winner = true;

    for(nstl::vector<int>::iterator iter = test_data.begin(); iter != test_data.end(); ++iter, ++cur_rank){

      int rating_delta = *iter;

      //playerId, newHeroRating, newPlayerRating, heroScore, isWinnerFaction, gameFinishClientState
      rollLogicDbg.ClenupPostGameData();
      rollLogicDbg.SetupPostGamePlayer(playerId, rating_delta, rating_delta, hero_score, is_player_winner, Peered::EGameFinishClientState::FinishedGame);

      //roll
      rollLogicDbg.RollContainers();

      int talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);
      TS_ASSERT( talents_count == 0);
    }

    cur_rank = 0;
    is_player_winner = false;

    for(nstl::vector<int>::iterator iter = test_data.begin(); iter != test_data.end(); ++iter, ++cur_rank){

      int rating_delta = *iter;
      rollLogicDbg.ClenupPostGameData();
      rollLogicDbg.SetupPostGamePlayer(playerId, rating_delta, rating_delta, hero_score, is_player_winner, Peered::EGameFinishClientState::FinishedGame);

      rollLogicDbg.RollContainers();

      int talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);
      TS_ASSERT( talents_count == 0);
    }

  }

/*
  Тестирование выдачи фиксированного количества наград за FWOD
*/
  void test_Roll_Containers_4One_With_FWOD()
  {
    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    const int playerId = 101;
    const int hero_score = 150;

    //map, mode, duration
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    //Setup 1 rank player with 150 points and FWOD
    rollLogicDbg.SetupPreGamePlayer(playerId, lobby::ETeam::Team1, 50, 1000.f, 1000.f, false, true);
    rollLogicDbg.SetupPostGamePlayer(playerId, 199, 199, hero_score, true, Peered::EGameFinishClientState::FinishedGame);

    //roll
    rollLogicDbg.RollFWOD();

    //roll result check awards types
    roll::dbg::EAwardTypeFlags desired_awards_types;
    //expected types: talent
    desired_awards_types.set(EAwardType::Talent);
    int talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);
    TS_ASSERT( talents_count == rollLogicDbg.MaxTalentsFWOD4Rank(desired_awards_types, 1));

    //expected types: pearl
    desired_awards_types.reset().set(EAwardType::Pearl);
    talents_count = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), playerId, desired_awards_types);
    TS_ASSERT( talents_count == rollLogicDbg.MaxItemFWOD4Rank(desired_awards_types, 1));
  }


  void foeCountsModifier(nstl::vector< NDb::BaseModifierFromQuantity > & vec)
  {
    vec.clear();
    NDb::BaseModifierFromQuantity mod;

    mod.quantity = 2;
    mod.percent = 0.2f;
    vec.push_back(mod);

    mod.quantity = 3;
    mod.percent = 0.3f;
    vec.push_back(mod);

    mod.quantity = 4;
    mod.percent = 0.4f;
    vec.push_back(mod);

    mod.quantity = 5;
    mod.percent = 0.5f;
    vec.push_back(mod);
  }

  void defeatedFoeRatingModifier(nstl::vector< float > & vec)
  {
    vec.clear();
    int rankCount = 13;

    float value = 0.f;
    for(int i = 0; i < rankCount; ++i)
    {
      value = static_cast<float>(i) + 1.0f;
      vec.push_back(value);
    }
  }

  void partyClanMembersModifier(nstl::vector< NDb::BaseModifierFromQuantity > & vec)
  {
    vec.clear();
    NDb::BaseModifierFromQuantity mod;
    mod.quantity = 2;
    mod.percent = 0.2f;
    vec.push_back(mod);

    mod.quantity = 3;
    mod.percent = 0.4f;
    vec.push_back(mod);

    mod.quantity = 4;
    mod.percent = 0.6f;
    vec.push_back(mod);

    mod.quantity = 5;
    mod.percent = 0.8f;
    vec.push_back(mod);
  }

  struct PlayerTestData{
    int playerId;
    int playerRank;
    int partyId;
    NCore::GuildData playerClan;

    PlayerTestData(int player, int rank, NCore::GuildData clan, int party_id = -1) 
      : playerId(player), playerClan(clan), playerRank(rank), partyId(party_id){}
  };

  /////////////////////////////////////////////////////////////////////////////

  void test_ClanWars_RatingCalculator()
  {
    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    //map, mode, duration
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    //Prepare clan wars settings

    NDb::ClanWarsSettings clwSettings;
    clwSettings.basePoints = 10;
    clwSettings.clanPoints = 0.3f; 
    foeCountsModifier(clwSettings.foeCountsModifier);
    defeatedFoeRatingModifier(clwSettings.defeatedFoeRankModifier);
    partyClanMembersModifier(clwSettings.partyClanMembersModifier);

    ClanWarsAwardsSettingsHolder cwSettingsHolder(&clwSettings, rollLogicDbg.GetMap()->teamSize);

    //Setup players 
    const int teamSize = 5;
    const int totalPlayers = teamSize * 2;

    using namespace roll;

    /*
    command A vs commandB
    1800 ( N )   :   1810
    1500 ( N )   :   1830
    1899 ( N )   :   1820
    1810         :  1899
    1820         :   1800
    N - это один клан
    */
    PlayerTestData players[totalPlayers] = {
      //team A
      PlayerTestData(100, 1800, dbg::DropNRollTests::CreateClan(1), 1),
      PlayerTestData(101, 1500, dbg::DropNRollTests::CreateClan(1), 1),
      PlayerTestData(102, 1899, dbg::DropNRollTests::CreateClan(1), 1),
      PlayerTestData(103, 1810, dbg::DropNRollTests::CreateClan(5), 0),
      PlayerTestData(104, 1820, dbg::DropNRollTests::CreateClan(5), 0),
      //Team B
      PlayerTestData(200, 1810, dbg::DropNRollTests::CreateClan(4), 2),
      PlayerTestData(201, 1830, dbg::DropNRollTests::CreateClan(2), 2),
      PlayerTestData(202, 1820, dbg::DropNRollTests::CreateClan(2), 2),
      PlayerTestData(203, 1899, dbg::DropNRollTests::CreateClan(1), 0),
      PlayerTestData(204, 1800, dbg::DropNRollTests::CreateClan(3), 0)
    };

    for(int i = 0; i < totalPlayers; ++i)
    {
      lobby::ETeam::Enum teamId = i < teamSize ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
      bool isWinner = i < teamSize ? true: false;

      int heroScore = isWinner ? 50 : 0;
      //int rating = RollTools::RatingFromRank(players[i].playerRank);
      int rating = players[i].playerRank;

      rollLogicDbg.SetupPreGamePlayer(players[i].playerId, teamId, 50, rating, rating, false, false, 0, players[i].partyId);
      rollLogicDbg.SetupPlayerClanData(players[i].playerId, players[i].playerClan);

      rollLogicDbg.SetupPostGamePlayer(players[i].playerId, 99, 99, heroScore, isWinner, Peered::EGameFinishClientState::FinishedGame);
    }

    ClanWarRatingCalculator cwRatingCalculator(cwSettingsHolder, rollLogicDbg.GetPreGame(), rollLogicDbg.GetPostGame());
    cwRatingCalculator.CalculateRating(rollLogicDbg.GetRollResult(), rollLogicDbg.GetGuildAwards());

    roll::dbg::EAwardTypeFlags desired_awards_types;
    desired_awards_types.reset().set(roll::EAwardType::ClanWarsPlayerRating);

    int points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[0].playerId, desired_awards_types);
    TS_ASSERT( points == 13);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[1].playerId, desired_awards_types);
    TS_ASSERT( points == 13);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[2].playerId, desired_awards_types);
    TS_ASSERT( points == 13);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[3].playerId, desired_awards_types);
    TS_ASSERT( points == 16);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[4].playerId, desired_awards_types);
    TS_ASSERT( points == 16);

    desired_awards_types.reset().set(roll::EAwardType::ClanWarsClanRating);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[0].playerId, desired_awards_types);
    TS_ASSERT( points == 5);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[1].playerId, desired_awards_types);
    TS_ASSERT( points == 5);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[2].playerId, desired_awards_types);
    TS_ASSERT( points == 5);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[3].playerId, desired_awards_types);
    TS_ASSERT( points == 7);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[4].playerId, desired_awards_types);
    TS_ASSERT( points == 7);

    desired_awards_types.reset().set(roll::EAwardType::ClanWarsClanRating);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 1, desired_awards_types);
    TS_ASSERT( points == 15);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 5, desired_awards_types);
    TS_ASSERT( points == 14);

    //Second test, second team (20x players) is winner

    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);
    rollLogicDbg.ClenupGuildAwards();
    rollLogicDbg.ClenupRollResult();

    for(int i = 0; i < totalPlayers; ++i)
    {
      lobby::ETeam::Enum teamId = i > teamSize - 1 ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
      bool isWinner = i > teamSize - 1 ? true: false;

      int heroScore = isWinner ? 50 : 0;
      //int rating = RollTools::RatingFromRank(players[i].playerRank);
      int rating = players[i].playerRank;

      rollLogicDbg.SetupPreGamePlayer(players[i].playerId, teamId, 50, rating, rating, false, false, 0, players[i].partyId);
      rollLogicDbg.SetupPlayerClanData(players[i].playerId, players[i].playerClan);

      rollLogicDbg.SetupPostGamePlayer(players[i].playerId, 99, 99, heroScore, isWinner, Peered::EGameFinishClientState::FinishedGame);
    }

    ClanWarRatingCalculator cwRatingCalculator1(cwSettingsHolder, rollLogicDbg.GetPreGame(), rollLogicDbg.GetPostGame());
    cwRatingCalculator1.CalculateRating(rollLogicDbg.GetRollResult(), rollLogicDbg.GetGuildAwards());

    desired_awards_types.reset().set(roll::EAwardType::ClanWarsPlayerRating);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[5].playerId, desired_awards_types);
    TS_ASSERT( points == 15);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[6].playerId, desired_awards_types);
    TS_ASSERT( points == 16);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[7].playerId, desired_awards_types);
    TS_ASSERT( points == 16);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[8].playerId, desired_awards_types);
    TS_ASSERT( points == 13);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[9].playerId, desired_awards_types);
    TS_ASSERT( points == 15);

    desired_awards_types.reset().set(roll::EAwardType::ClanWarsClanRating);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[5].playerId, desired_awards_types);
    TS_ASSERT( points == 6);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[6].playerId, desired_awards_types);
    TS_ASSERT( points == 7);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[7].playerId, desired_awards_types);
    TS_ASSERT( points == 7);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[8].playerId, desired_awards_types);
    TS_ASSERT( points == 5);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[9].playerId, desired_awards_types);
    TS_ASSERT( points == 6);

    desired_awards_types.reset().set(roll::EAwardType::ClanWarsClanRating);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 2, desired_awards_types);
    TS_ASSERT( points == 14);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 4, desired_awards_types);
    TS_ASSERT( points == 6);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 3, desired_awards_types);
    TS_ASSERT( points == 6);

    points = GetTotalRollCountByClanId(rollLogicDbg.GetGuildAwards(), 1, desired_awards_types);
    TS_ASSERT( points == 5);

  }

void test_ClanWars_RatingAwards()
  {

    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    NDb::ClanWarsSettings clwSettings;
    clwSettings.basePoints = 10;
    clwSettings.clanPoints = 0.3f; 
    foeCountsModifier(clwSettings.foeCountsModifier);
    defeatedFoeRatingModifier(clwSettings.defeatedFoeRankModifier);
    partyClanMembersModifier(clwSettings.partyClanMembersModifier);

    ClanWarsAwardsSettingsHolder cwSettingsHolder(&clwSettings, rollLogicDbg.GetMap()->teamSize);

    const int teamSize = 5;
    const int totalPlayers = teamSize * 2;

    using namespace roll;

    PlayerTestData players[totalPlayers] = {
      //team A
      PlayerTestData(100, 1687.36, dbg::DropNRollTests::CreateClan(1378684502018), 0),
      PlayerTestData(101, 1650.00, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(102, 1675.00, dbg::DropNRollTests::CreateClan(1206885810177), 0),
      PlayerTestData(103, 1695.89, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(104, 1685.63, dbg::DropNRollTests::CreateClan(0), 0),
      //Team B
      PlayerTestData(200, 1648.93, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(201, 1621.27, dbg::DropNRollTests::CreateClan(1374389534721), 0),
      PlayerTestData(202, 1661.00, dbg::DropNRollTests::CreateClan(55834574849), 0),
      PlayerTestData(203, 1642.61, dbg::DropNRollTests::CreateClan(55834574849), 0),
      PlayerTestData(204, 1613.44, dbg::DropNRollTests::CreateClan(55834574849), 0)
    };

    for(int i = 0; i < totalPlayers; ++i)
    {
      lobby::ETeam::Enum teamId = i < teamSize ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
      bool isWinner = teamId == lobby::ETeam::Team2 ? true: false;

      int heroScore = isWinner ? 50 : 0;
      //int rating = RollTools::RatingFromRank(players[i].playerRank);
      int rating = players[i].playerRank;

      rollLogicDbg.SetupPreGamePlayer(players[i].playerId, teamId, 50, rating, rating, false, false, 0, players[i].partyId);
      rollLogicDbg.SetupPlayerClanData(players[i].playerId, players[i].playerClan);

      rollLogicDbg.SetupPostGamePlayer(players[i].playerId, 99, 99, heroScore, isWinner, Peered::EGameFinishClientState::FinishedGame);
    }

    rollLogicDbg.RollClanWarsAwards(cwSettingsHolder);

    roll::dbg::EAwardTypeFlags desired_awards_types;
    desired_awards_types.reset().set(roll::EAwardType::ClanWarsPlayerRating);

    int points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[5].playerId, desired_awards_types);
    TS_ASSERT( points == 0);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[6].playerId, desired_awards_types);
    TS_ASSERT( points == 11);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[7].playerId, desired_awards_types);
    TS_ASSERT( points == 14);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[8].playerId, desired_awards_types);
    TS_ASSERT( points == 14);

    points = GetTotalRollTalentsCountByUserId(rollLogicDbg.GetRollResult(), players[9].playerId, desired_awards_types);
    TS_ASSERT( points == 14);

  }

  //////////////////////////////////////////////////////////////////////////////

  float myceil(float f){
    f = f * 10;
    int fi = f;
    return ((float)fi)/10.f;

  }

  void checkRatingRoll(PlayerTestData* players, float* ratingDiff, roll::dbg::DropNRollTests& rollLogicDbg, const int teamSize, const int totalPlayers)
  {
      
      for(int i = 0; i < totalPlayers; ++i)
      {
          lobby::ETeam::Enum teamId = i < teamSize ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
          bool isWinner = teamId == lobby::ETeam::Team2 ? true: false;

          int rating = players[i].playerRank;

          rollLogicDbg.SetupPreGamePlayer(players[i].playerId, teamId, 100, rating, rating, true, true, 0, players[i].partyId);
          rollLogicDbg.SetupPostGamePlayer(players[i].playerId, 0, 0, 150, isWinner, Peered::EGameFinishClientState::FinishedGame);
      }

      //roll
      rollLogicDbg.RollRating();
      rollLogicDbg.UpdateRollDataCache(  rollLogicDbg.GetRollResult() );
      //float ratingDiff[totalPlayers] = { -13.8f, -9.1f, -11.2f, -12.1f, -7.9f, 22.1f, 19.3f, 11.9f, 11.2f, 21.6f };


      roll::dbg::EAwardTypeFlags desired_awards_types;
      desired_awards_types.reset().set(roll::EAwardType::HeroRating);
      float heroRating = 0.0f;
      for(int i = 0; i < totalPlayers; ++i)
      {
          heroRating = GetTotalRollTalentsCountByUserId( rollLogicDbg.GetRollResult(), players[i].playerId, desired_awards_types );
          TS_ASSERT( myceil(heroRating) == ratingDiff[i]);
      }

  }

void test_Roll_Rating()
{
    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    NDb::Ptr<NDb::RollSettings> settings = roll::DropNRoll::DbRoot();

    roll::DropNRoll rollLogic(config, settings, NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection);
    
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const int teamSize = 5;
    const int totalPlayers = teamSize * 2;

    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);

    PlayerTestData players[totalPlayers] = {
        //team A
        PlayerTestData(100, 2864.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(101, 2568.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(102, 2675.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(103, 2726.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(104, 2506.f, dbg::DropNRollTests::CreateClan(0), 0),
        //Team B
        PlayerTestData(200, 2200.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(201, 2396.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(202, 2456.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(203, 2497.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(204, 2247.f, dbg::DropNRollTests::CreateClan(0), 1)
    };
    //roll
    float ratingDiff[totalPlayers] = { -13.8f, -9.1f, -11.2f, -12.1f, -7.9f, 22.1f, 19.3f, 11.9f, 11.2f, 21.6f };
    checkRatingRoll(players, ratingDiff, rollLogicDbg, teamSize, totalPlayers);
    
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);
    // with marshal
    PlayerTestData players1[totalPlayers] = {
        //team A
        PlayerTestData(100, 2291.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(101, 2240.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(102, 2035.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(103, 2209.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(104, 2500.f, dbg::DropNRollTests::CreateClan(0), 0),
        //Team B
        PlayerTestData(200, 2000.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(201, 2114.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(202, 2101.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(203, 2300.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(204, 2650.f, dbg::DropNRollTests::CreateClan(0), 1)
    };
    //roll
    float ratingDiff1[totalPlayers] = { -10.2f, -8.8f, -5.5f, -8.0f, -10.2f, 25.0f, 15.9f, 16.3f, 10.6f, 1.9f };
    checkRatingRoll(players1, ratingDiff1, rollLogicDbg, teamSize, totalPlayers);

    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);
    // with recruit
    PlayerTestData players2[totalPlayers] = {
        //team A
        PlayerTestData(100, 1199.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(101, 1000.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(102, 1094.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(103, 1053.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(104, 1100.f, dbg::DropNRollTests::CreateClan(0), 0),
        //Team B
        PlayerTestData(200, 1090.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(201, 1048.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(202, 1105.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(203, 1099.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(204, 1120.f, dbg::DropNRollTests::CreateClan(0), 1)
    };
    //roll
    float ratingDiff2[totalPlayers] = { -16.3f, -7.9f, -11.6f, -9.9f, -11.8f, 23.9f, 26.7f, 22.9f, 23.3f, 21.9f };
    checkRatingRoll(players2, ratingDiff2, rollLogicDbg, teamSize, totalPlayers);


    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);
    
    // with recruit
    PlayerTestData players3[totalPlayers] = {
        //team A
        PlayerTestData(100, 2291.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(101, 2240.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(102, 2035.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(103, 2209.f, dbg::DropNRollTests::CreateClan(0), 0),
        PlayerTestData(104, 2500.f, dbg::DropNRollTests::CreateClan(0), 0),
        //Team B
        PlayerTestData(200, 1862.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(201, 2114.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(202, 2101.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(203, 2300.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(204, 2650.f, dbg::DropNRollTests::CreateClan(0), 1)
    };
    //roll
    float ratingDiff3[totalPlayers] = { -10.7f, -9.4f, -6.4f, -8.6f, -10.4f, 27.4f, 15.9f, 16.3f, 10.6f, 1.9f };
    checkRatingRoll(players3, ratingDiff3, rollLogicDbg, teamSize, totalPlayers);
    
    
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);
    // full vs full
    PlayerTestData players4[totalPlayers] = {
        //team A
        PlayerTestData(100, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(101, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(102, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(103, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(104, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        //Team B
        PlayerTestData(200, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(201, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(202, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(203, 2100.f, dbg::DropNRollTests::CreateClan(0), 1),
        PlayerTestData(204, 2100.f, dbg::DropNRollTests::CreateClan(0), 1)
    };
    //roll
    float ratingDiff4[totalPlayers] = { -12.0f, -12.0f, -12.0f, -12.0f, -12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f };
    checkRatingRoll(players4, ratingDiff4, rollLogicDbg, teamSize, totalPlayers);
    
     //mix party vs full party  -> 5 vs 2 + 2 + 1  
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);
    
    PlayerTestData players5[totalPlayers] = {
      //team A
      PlayerTestData(100, 1786.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(101, 1848.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(102, 1758.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(103, 1786.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(104, 1806.f, dbg::DropNRollTests::CreateClan(0), 1),
      //Team B
      PlayerTestData(200, 1847.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(201, 1864.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(202, 1805.f, dbg::DropNRollTests::CreateClan(0), 3),
      PlayerTestData(203, 1806.f, dbg::DropNRollTests::CreateClan(0), 3),
      PlayerTestData(204, 1832.f, dbg::DropNRollTests::CreateClan(0), 0 )
    };
    //roll
    float ratingDiff5[totalPlayers] = { -13.90f, -16.70f, -12.70f, -13.90f, -14.80f, 18.20f, 17.40f, 20.10f, 20.00f, 18.90f };
    checkRatingRoll(players5, ratingDiff5, rollLogicDbg, teamSize, totalPlayers);

    //mix party vs full party  -> 2 + 1 + 1 +1 vs 3 + 1 + 1  
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);

    PlayerTestData players6[totalPlayers] = {
      //team A
      PlayerTestData(100, 1887.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(101, 1882.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(102, 1861.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(103, 1845.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(104, 1811.f, dbg::DropNRollTests::CreateClan(0), 0),
      //Team B
      PlayerTestData(200, 1801.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(201, 1826.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(202, 1870.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(203, 1808.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(204, 1858.f, dbg::DropNRollTests::CreateClan(0), 0 )
    };
    //roll
    float ratingDiff6[totalPlayers] = { -18.40f, -18.20f, -17.20f, -16.50f, -15.00f, 18.50f, 17.40f, 15.40f, 18.20f, 15.90f };
    checkRatingRoll(players6, ratingDiff6, rollLogicDbg, teamSize, totalPlayers);


    //mix party vs full party  ->  1 + 4 vs 2 + 1 + 1 + 1  
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);

    PlayerTestData players7[totalPlayers] = {
      //team A
      PlayerTestData(100, 1800.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(101, 1847.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(102, 1887.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(103, 1807.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(104, 1803.f, dbg::DropNRollTests::CreateClan(0), 1),
      //Team B
      PlayerTestData(200, 1869.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(201, 1877.f, dbg::DropNRollTests::CreateClan(0), 2),
      PlayerTestData(202, 1823.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(203, 1841.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(204, 1893.f, dbg::DropNRollTests::CreateClan(0), 0 )
    };
    //roll
    float ratingDiff7[totalPlayers] = { -13.20f, -15.30f, -17.20f, -13.50f, -13.30f, 17.70f, 17.40f, 19.70f, 19.00f, 16.70f };
    checkRatingRoll(players7, ratingDiff7, rollLogicDbg, teamSize, totalPlayers);

    //mix party vs full party  ->  1 + 4 vs 2 + 1 + 1 + 1  
    rollLogicDbg.SetupGame("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb", roll::EMode::PvP, 1800);

    PlayerTestData players8[totalPlayers] = {
      //team A
      PlayerTestData(100, 1250.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(101, 1124.f, dbg::DropNRollTests::CreateClan(0), 1),
      PlayerTestData(102, 1138.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(103, 1208.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(104, 995.f, dbg::DropNRollTests::CreateClan(0), 0),
      //Team B
      PlayerTestData(200, 951.f, dbg::DropNRollTests::CreateClan(0),  0),
      PlayerTestData(201, 1014.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(202, 1009.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(203, 1100.f, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(204, 1299.f, dbg::DropNRollTests::CreateClan(0), 0 )
    };
    //roll
    float ratingDiff8[totalPlayers] = { -22.8f, -18.20f, -18.70f, -21.40f, -12.90f, 47.30f, 32.10f, 32.40f, 26.80f, 13.40f };
    checkRatingRoll(players8, ratingDiff8, rollLogicDbg, teamSize, totalPlayers);


}

void test_RollBuffs()
  {

    CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();
    roll::DropNRoll rollLogic(config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
    roll::dbg::DropNRollTests rollLogicDbg( &rollLogic );

    const nstl::string map("Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb");
    rollLogicDbg.SetupGame(map, roll::EMode::PvP, 1800);

    rollLogicDbg.GetBuffCache()->InitDataCache(rollLogicDbg.GetMap(), lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE);

    NDb::ClanWarsSettings clwSettings;
    clwSettings.basePoints = 10;
    clwSettings.clanPoints = 0.3f; 
    foeCountsModifier(clwSettings.foeCountsModifier);
    defeatedFoeRatingModifier(clwSettings.defeatedFoeRankModifier);
    partyClanMembersModifier(clwSettings.partyClanMembersModifier);

    ClanWarsAwardsSettingsHolder cwSettingsHolder(&clwSettings, rollLogicDbg.GetMap()->teamSize);

    const int teamSize = 5;
    const int totalPlayers = teamSize * 2;

    using namespace roll;

    NCore::TAwardsBuffs buff;
    buff.push_back("/Items/GuildBuffs/B036_allresources_cw:548BCBB1-830E-4928-AC81-10ABD9C15F59");
    buff.push_back("/Items/GuildBuffs/B036_allresources_cw:76C645B1-EC7C-46D1-8545-D2712047D6B8");
    buff.push_back("/Items/GuildBuffs/B036_allresources_cw:D70D2DDA-847B-4386-95BF-2D2207A43F19");

    PlayerTestData players[totalPlayers] = {
      //team A
      PlayerTestData(100, 1687.36, dbg::DropNRollTests::CreateClan(1378684502018), 0),
      PlayerTestData(101, 1650.00, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(102, 1675.00, dbg::DropNRollTests::CreateClan(1206885810177), 0),
      PlayerTestData(103, 1695.89, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(104, 1685.63, dbg::DropNRollTests::CreateClan(0), 0),
      //Team B
      PlayerTestData(200, 1648.93, dbg::DropNRollTests::CreateClan(0), 0),
      PlayerTestData(201, 1621.27, dbg::DropNRollTests::CreateClan(1374389534721), 0),
      PlayerTestData(202, 1661.00, dbg::DropNRollTests::CreateClan(55834574849), 0),
      PlayerTestData(203, 1642.61, dbg::DropNRollTests::CreateClan(55834574849), 0),
      PlayerTestData(204, 1613.44, dbg::DropNRollTests::CreateClan(55834574849), 0)
    };

    for(int i = 0; i < totalPlayers; ++i)
    {
      lobby::ETeam::Enum teamId = i < teamSize ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
      bool isWinner = teamId == lobby::ETeam::Team2 ? true: false;

      int heroScore = isWinner ? 50 : 0;
      int rating = players[i].playerRank;

      rollLogicDbg.SetupPreGamePlayer(players[i].playerId, teamId, 50, rating, rating, false, false, &buff, players[i].partyId);
      rollLogicDbg.SetupPlayerClanData(players[i].playerId, players[i].playerClan);

      rollLogicDbg.GetBuffCache()->CollectBuffs(players[i].playerId, buff);

      rollLogicDbg.SetupPostGamePlayer(players[i].playerId, 99, 99, heroScore, isWinner, Peered::EGameFinishClientState::FinishedGame);
    }

    rollLogicDbg.SetSessionType(lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE);
    rollLogicDbg.RollContainers();

    rollLogicDbg.UpdateRollBuffStatistics();


}
};