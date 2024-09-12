//!Component("Server/LobbySocial/SocialLobby")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "SocialLobbyPvxServices.h"
#include "SocialLobbyConfig.h"
#include "ISocialLobbyPvxSvc.h"


struct Test_SocialLobbyPvxSvc : public CxxTest::TestSuite
{
  class PvxSvcSimpleMock : public socialLobby::IPvxSvc, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( PvxSvcSimpleMock, socialLobby::IPvxSvc, BaseObjectMT );

  public:
    PvxSvcSimpleMock( const Transport::TServiceId & _svcid, const string & _clusterId ) :
    status( rpc::Connected ), svcid( _svcid ), clusterId( _clusterId ) {}

    virtual void NewGame( lobby::TSocialGameId _gameId, const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails, socialLobby::IPvxAcknowledge * _ack ) {}
    virtual void NewReconnectingUser( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, socialLobby::IPvxAcknowledge * _ack ) {}
    virtual void NewSpectator( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, const string& _login, socialLobby::IPvxAcknowledge * _ack, const wstring& nickname ) {}
    virtual void UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, socialLobby::IPvxAcknowledge* _ack ) {}

    //rpc::IRemoteEntity
    virtual rpc::Status GetStatus() { return status; }

    rpc::Status status;
    Transport::TServiceId svcid;
    string clusterId;
  };



  timer::Time testTime;
  Strong<socialLobby::PvxServices> testObj;
  std::vector<WeakMT<PvxSvcSimpleMock>> pvxMocks;


  struct TestOptions
  {
    int     pinnedLocationsThreshold;
    string  pinnedLocations;
    string  pinnedLocationsPriority;
    string  forceCluster;
    socialLobby::EPvxLobbyInstanceMode::Enum forceMode;
    vector<socialLobby::TUId> forceList;
    bool    zeroCapacity;

    TestOptions() :
    pinnedLocationsThreshold( 0 ),
    forceMode( socialLobby::EPvxLobbyInstanceMode::Normal ),
    zeroCapacity( false )
    {}
  };


  struct PvxSett : public socialLobby::PvxClusterSettings
  {
    PvxSett( unsigned _capacity, socialLobby::EPvxLobbyInstanceMode::Enum _specialMode, const vector<socialLobby::TUId> & _specialList )
    {
      capacity = _capacity;
      specialMode = _specialMode;
      specialList = _specialList;
    }
  };


  void setupTest( const TestOptions & testOptions = TestOptions() )
  {
    testTime = 0;

    Strong<socialLobby::Config> cfg = socialLobby::CreateConfigFromStatics();

    if ( !testOptions.pinnedLocations.empty() )
    {
      cfg->pinnedLocationsThreshold = testOptions.pinnedLocationsThreshold;
      cfg->pinnedLocations = testOptions.pinnedLocations;
      cfg->pinnedLocationsPriority = testOptions.pinnedLocationsPriority;
    }
    
    testObj = new socialLobby::PvxServices( cfg );

    const char * clusterIds[4] = { "A", "B", "C", "D" };
    unsigned locationCap[4] = { 100, 50, 50, 0 };
    const char * svcids[2] = { "svc0", "svc1" };
    pvxMocks.reserve( 8 );
    for ( size_t i = 0; i < ( testOptions.zeroCapacity ? 4u : 3u ); ++i )
    {
      socialLobby::EPvxLobbyInstanceMode::Enum forceMode = socialLobby::EPvxLobbyInstanceMode::Normal;
      vector<socialLobby::TUId> forceList;
      if ( testOptions.forceMode != socialLobby::EPvxLobbyInstanceMode::Normal )
        if ( testOptions.forceCluster == clusterIds[i] )
        {
          forceMode = testOptions.forceMode;
          forceList = testOptions.forceList;
        }

      for ( size_t j = 0; j < 2; ++j )
      {
        StrongMT<PvxSvcSimpleMock> pvx = new PvxSvcSimpleMock( svcids[j], clusterIds[i] );
        testObj->Add( pvx, clusterIds[i], svcids[j], PvxSett( locationCap[i], forceMode, forceList ) );
        pvxMocks.push_back( pvx.Get() );
      }
    }
  }

  virtual void tearDown()
  {
    testTime = 0;
    testObj = 0;
    pvxMocks.clear();
  }


  void helper( mmaking::SGame & game, int index, lobby::ETeam::Enum faction, const char * bestCluster, int ping, int partySize = 1, const char * geolocation = "AA" )
  {
    mmaking::SGeoInfo geo( "ua" );
    geo.location = geolocation;
    const char * clusterIds[4] = { "A", "B", "C", "D" };
    for ( int i = 0; i < 4; ++i )
      geo.pings.push_back( mmaking::SLocationPing( clusterIds[i], stricmp( clusterIds[i], bestCluster ) ? 100 : ping ) );

    game.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( faction, 101, true ), 1.0, index ) );
    for ( int i = 0; i < partySize; ++i )
      game.humans.back().members.push_back( mmaking::SRequestMember( index + i, "h", lobby::ESex::Male, mmaking::EBasket::Normal, 100, 100, 100, 100.0, geo, 0, 0, 1 ) );
  }


  void test_singles()
  {
    setupTest();

    mmaking::SGame game;
    for ( int i = 0; i < 5; ++i )
      helper( game, 1 + i, lobby::ETeam::Team1, "A", 50 );
    for ( int i = 0; i < 5; ++i )
      helper( game, 10 + i, lobby::ETeam::Team2, "A", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );
  }


  void test_party()
  {
    setupTest();

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "A", 50, 5 );
    helper( game, 10, lobby::ETeam::Team2, "A", 50, 5 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );
  }


  void test_prevailing1()
  {
    setupTest();

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "B", 50, 2 );
    helper( game, 10, lobby::ETeam::Team1, "C", 50, 3 );
    helper( game, 15, lobby::ETeam::Team2, "B", 50, 5 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );
  }


  void test_prevailing2()
  {
    setupTest();

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "C", 50, 5 );
    helper( game, 10, lobby::ETeam::Team2, "B", 50, 2 );
    helper( game, 15, lobby::ETeam::Team2, "C", 50, 3 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );
  }


  void test_unknown()
  {
    setupTest();

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "X", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );
  }


  void helper_killPvx( size_t idx ) {
    TS_ASSERT( idx >= 0 && idx < pvxMocks.size() );
    StrongMT<PvxSvcSimpleMock> locked = pvxMocks[idx].Lock();
    TS_ASSERT( locked );
    locked->status = rpc::Disconnected;

    testObj->Poll( testTime );
    testTime += 60.5;
    testObj->Poll( testTime );
  }


  void test_drop()
  {
    setupTest();

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "B", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );

    helper_killPvx( 2 ); //b0

    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );

    helper_killPvx( 3 ); //b1
    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );

    helper_killPvx( 0 ); //a0
    helper_killPvx( 1 ); //a1

    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );

    helper_killPvx( 4 ); //c0
    helper_killPvx( 5 ); //c1

    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "" );
  }


  void help_check_pvx( socialLobby::IPvxSvcWrapper * pvx, const string & clusterId, const Transport::TServiceId & svcid )
  {
    TS_ASSERT( pvx );
    TS_ASSERT_EQUALS( pvx->SvcId(), svcid );
    PvxSvcSimpleMock * mockPvx = dynamic_cast<PvxSvcSimpleMock *>( pvx->Remote() );
    TS_ASSERT( mockPvx );
    TS_ASSERT_EQUALS( mockPvx->svcid, svcid );
    TS_ASSERT_EQUALS( mockPvx->clusterId, clusterId );
  }

  void help_test_allocate( const string & clusterId, unsigned loadInc, const Transport::TServiceId & expectedSvcId )
  {
    Strong<socialLobby::IPvxSvcWrapper> pvx = testObj->Allocate( clusterId, loadInc );
    help_check_pvx( pvx, clusterId, expectedSvcId );
  }


  void test_load()
  {
    setupTest();

    help_test_allocate( "C", 10, "svc0" );
    help_test_allocate( "C", 6, "svc1" );
    help_test_allocate( "C", 6, "svc1" );
    help_test_allocate( "C", 6, "svc0" );
    help_test_allocate( "A", 10, "svc0" );
    help_test_allocate( "A", 10, "svc1" );
  }


  void test_load_notify()
  {
    setupTest();

    testObj->LoadNotify( "B", "svc0", 100 );
    testObj->LoadNotify( "B", "svc1", 80 );

    help_test_allocate( "B", 10, "svc1" );
    help_test_allocate( "B", 6, "svc1" );
    help_test_allocate( "B", 6, "svc1" );
    help_test_allocate( "B", 6, "svc0" );

    testObj->LoadNotify( "B", "svc0", 1000 );
    testObj->LoadNotify( "B", "svc1", 50 ); //decrease: 102 -> 50

    help_test_allocate( "B", 10, "svc1" );
  }


  void test_capacity()
  {
    setupTest();

    testObj->LoadNotify( "A", "svc0", 45 );
    testObj->LoadNotify( "A", "svc1", 45 );
    testObj->LoadNotify( "B", "svc0", 15 );
    testObj->LoadNotify( "B", "svc1", 15 );

    mmaking::SGame game;
    helper( game, 1, lobby::ETeam::Team1, "A", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );

    testObj->LoadNotify( "A", "svc0", 55 );
    testObj->LoadNotify( "A", "svc1", 55 );

    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );

    testObj->LoadNotify( "B", "svc0", 20 );
    testObj->LoadNotify( "B", "svc1", 20 );
    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );

    testObj->LoadNotify( "c", "svc0", 30 );
    testObj->LoadNotify( "c", "svc1", 30 );
    loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );
  }


  void test_allocate_first_available()
  {
    setupTest();

    helper_killPvx( 0 ); //a0
    helper_killPvx( 1 ); //a1

    Strong<socialLobby::IPvxSvcWrapper> pvx = testObj->Allocate( "A", 10 );
    help_check_pvx( pvx, "B", "svc0" );

    helper_killPvx( 2 ); //b0
    helper_killPvx( 3 ); //b1
    helper_killPvx( 4 ); //c0
    helper_killPvx( 5 ); //c1
    pvx = testObj->Allocate( "B", 10 );
    TS_ASSERT( !pvx );
  }


  void test_pinned_locations_broken_config1()
  {
    TestOptions topt;
    topt.pinnedLocations = "0, ABCDEFGHIJKOPQRSTUVW jhfgksajhfgkshjdfvgkjv, ,";
    topt.pinnedLocationsPriority = "qwqwqwqwqw -5";
    topt.pinnedLocationsThreshold = 2;
    setupTest( topt );
    TS_ASSERT( true );
  }


  void help_test_pinned_locations( mmaking::SGame & _game )
  {
    for ( int i = 0; i < 5; ++i )
      helper( _game, 1 + i, lobby::ETeam::Team1, "A", 50, 1, "AA" );

    for ( int i = 0; i < 3; ++i )
      helper( _game, 10 + i, lobby::ETeam::Team2, "B", 50, 1, "BB" );

    for ( int i = 0; i < 2; ++i )
      helper( _game, 20 + i, lobby::ETeam::Team2, "C", 50, 1, "CC" );
  }


  void test_pinned_locations_smoke()
  {
    TestOptions topt;
    topt.pinnedLocations = "CC c";
    topt.pinnedLocationsThreshold = 1;
    setupTest( topt );

    mmaking::SGame game;
    help_test_pinned_locations( game );

    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );
  }


  void test_two_pinned_locations()
  {
    TestOptions topt;
    topt.pinnedLocations = "CC c, BB b";
    topt.pinnedLocationsThreshold = 1;
    setupTest( topt );

    mmaking::SGame game;
    help_test_pinned_locations( game );

    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );
  }


  void test_pinned_locations_priority()
  {
    TestOptions topt;
    topt.pinnedLocations = "CC c, BB b";
    topt.pinnedLocationsPriority = "c 2";
    topt.pinnedLocationsThreshold = 1;
    setupTest( topt );

    mmaking::SGame game;
    help_test_pinned_locations( game );

    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );
  }


  void test_pinned_locations_threshold()
  {
    TestOptions topt;
    topt.pinnedLocations = "BB b";
    topt.pinnedLocationsThreshold = 4;
    setupTest( topt );

    mmaking::SGame game;
    help_test_pinned_locations( game );

    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );
  }


  void test_force_partial()
  {
    TestOptions topt;
    topt.forceMode = socialLobby::EPvxLobbyInstanceMode::ForcePartial;
    topt.forceCluster = "C";
    topt.forceList.push_back( 10 );
    topt.forceList.push_back( 11 );

    setupTest( topt );

    mmaking::SGame game;
    for ( int i = 0; i < 5; ++i )
      helper( game, 1 + i, lobby::ETeam::Team1, "A", 50 );
    for ( int i = 0; i < 5; ++i )
      helper( game, 10 + i, lobby::ETeam::Team2, "A", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "c" );
  }


  void test_force_full_fail()
  {
    TestOptions topt;
    topt.forceMode = socialLobby::EPvxLobbyInstanceMode::ForceFullGames;
    topt.forceCluster = "C";
    topt.forceList.push_back( 5 );
    topt.forceList.push_back( 12 );
    topt.forceList.push_back( 13 );

    setupTest( topt );

    mmaking::SGame game;
    for ( int i = 0; i < 5; ++i )
      helper( game, 1 + i, lobby::ETeam::Team1, "A", 50 );
    for ( int i = 0; i < 5; ++i )
      helper( game, 10 + i, lobby::ETeam::Team2, "A", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "a" );
  }


  void test_force_full()
  {
    TestOptions topt;
    topt.forceMode = socialLobby::EPvxLobbyInstanceMode::ForceFullGames;
    topt.forceCluster = "B";
    topt.forceList.push_back( 100 );
    for ( int i = 0; i < 5; ++i ) {
      topt.forceList.push_back( 1 + i );
      topt.forceList.push_back( 10 + i );
    }
    topt.forceList.push_back( 30 );

    setupTest( topt );

    mmaking::SGame game;
    for ( int i = 0; i < 5; ++i )
      helper( game, 1 + i, lobby::ETeam::Team1, "A", 50 );
    for ( int i = 0; i < 5; ++i )
      helper( game, 10 + i, lobby::ETeam::Team2, "A", 50 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "b" );
  }


  void test_zero_capacity_smoke()
  {
    TestOptions topt;
    topt.zeroCapacity = true;
    setupTest( topt );

    testObj->LoadNotify( "A", "svc0", 45 );
    testObj->LoadNotify( "A", "svc1", 45 );
    testObj->LoadNotify( "B", "svc0", 15 );
    testObj->LoadNotify( "B", "svc1", 15 );
    testObj->LoadNotify( "c", "svc0", 30 );
    testObj->LoadNotify( "c", "svc1", 30 );

    mmaking::SGame game1;
    helper( game1, 1, lobby::ETeam::Team1, "A", 50 );
    string loc1 = testObj->DetermineClusterForGame( game1 );
    TS_ASSERT_EQUALS( loc1, "a" );

    mmaking::SGame game2;
    helper( game2, 10, lobby::ETeam::Team1, "D", 50, 4 );
    string loc2 = testObj->DetermineClusterForGame( game2 );
    TS_ASSERT_EQUALS( loc2, "b" );

    //let's overload all non-zero-capacity clusters
    testObj->LoadNotify( "A", "svc0", 55 );
    testObj->LoadNotify( "A", "svc1", 55 );
    testObj->LoadNotify( "B", "svc0", 30 );
    testObj->LoadNotify( "B", "svc1", 30 );
    testObj->LoadNotify( "c", "svc0", 30 );
    testObj->LoadNotify( "c", "svc1", 30 );

    mmaking::SGame game3;
    helper( game3, 101, lobby::ETeam::Team2, "D", 50, 10 );
    string loc3 = testObj->DetermineClusterForGame( game3 );
    TS_ASSERT_EQUALS( loc3, "a" );
  }


  void test_zero_capacity_force()
  {
    TestOptions topt;
    topt.zeroCapacity = true;
    topt.forceMode = socialLobby::EPvxLobbyInstanceMode::ForcePartial;
    topt.forceCluster = "D";
    topt.forceList.push_back( 78 );
    setupTest( topt );

    testObj->LoadNotify( "A", "svc0", 45 );
    testObj->LoadNotify( "A", "svc1", 45 );
    testObj->LoadNotify( "B", "svc0", 15 );
    testObj->LoadNotify( "B", "svc1", 15 );
    testObj->LoadNotify( "c", "svc0", 30 );
    testObj->LoadNotify( "c", "svc1", 30 );

    mmaking::SGame game;
    helper( game, 78, lobby::ETeam::Team1, "A", 50, 4 );
    string loc = testObj->DetermineClusterForGame( game );
    TS_ASSERT_EQUALS( loc, "d" );
  }


  void test_settings_update()
  {
    Strong<socialLobby::Config> cfg = socialLobby::CreateConfigFromStatics();

    Strong<socialLobby::PvxServices> testObj = new socialLobby::PvxServices( cfg );

    PvxSett sett( 10, socialLobby::EPvxLobbyInstanceMode::Normal, vector<socialLobby::TUId>() );
    sett.specialList.push_back( 6144 );
    sett.specialList.push_back( 314 );
    StrongMT<PvxSvcSimpleMock> pvx5 = new PvxSvcSimpleMock( "lobby/5", "C" );
    StrongMT<PvxSvcSimpleMock> pvx3 = new PvxSvcSimpleMock( "lobby/3", "C" );
    StrongMT<PvxSvcSimpleMock> pvx6 = new PvxSvcSimpleMock( "lobby/6", "C" );
    testObj->Add( pvx5, pvx5->clusterId, pvx5->svcid, sett );

    Strong<socialLobby::PvxSubcluster> cluster = testObj->FindSubcluster( "C" );
    TS_ASSERT( cluster );

    TS_ASSERT_EQUALS( cluster->Capacity(), 10 );
    TS_ASSERT_EQUALS( cluster->SpecialMode(), socialLobby::EPvxLobbyInstanceMode::Normal );
    TS_ASSERT( !cluster->IsInSpecialList( 6111 ) );
    TS_ASSERT( cluster->IsInSpecialList( 6144 ) );
    TS_ASSERT( cluster->IsInSpecialList( 314 ) );

    sett.specialMode = socialLobby::EPvxLobbyInstanceMode::ForcePartial;
    sett.capacity = 25;

    //No update, "lobby/3" is earlier than "lobby/5"
    testObj->Add( pvx3, pvx3->clusterId, pvx3->svcid, sett );
    TS_ASSERT_EQUALS( cluster->Capacity(), 10 );
    TS_ASSERT_EQUALS( cluster->SpecialMode(), socialLobby::EPvxLobbyInstanceMode::Normal );

    //Still no update, "lobby/7" is unknown
    testObj->UpdateSettings( "C", "lobby/7", sett );
    TS_ASSERT_EQUALS( cluster->Capacity(), 10 );
    TS_ASSERT_EQUALS( cluster->SpecialMode(), socialLobby::EPvxLobbyInstanceMode::Normal );

    testObj->Add( pvx6, pvx6->clusterId, pvx6->svcid, sett );
    TS_ASSERT_EQUALS( cluster->Capacity(), 25 );
    TS_ASSERT_EQUALS( cluster->SpecialMode(), socialLobby::EPvxLobbyInstanceMode::ForcePartial );

    sett.capacity = 100500;
    sett.specialList.clear();
    sett.specialList.push_back( 1980 );
    testObj->UpdateSettings( "C", "lobby/6", sett );
    TS_ASSERT_EQUALS( cluster->Capacity(), 100500 );
    TS_ASSERT( !cluster->IsInSpecialList( 6144 ) );
    TS_ASSERT( cluster->IsInSpecialList( 1980 ) );

    //let's kill pvx3 & pvx6
    pvx6->status = rpc::Disconnected;
    pvx5->status = rpc::Disconnected;
    testObj->Poll( 1.0 );
    testObj->Poll( 1.0 + cfg->pvxDisconnectTimeout + 1.0 );

    //settings should be updated since all other instances is dead
    sett.capacity = 200;
    testObj->UpdateSettings( "C", "lobby/3", sett );
    TS_ASSERT( cluster->Capacity() == 200 );

    //pvx5 once again
    sett.capacity = 220;
    testObj->Add( pvx5, pvx5->clusterId, pvx5->svcid, sett );
    TS_ASSERT( cluster->Capacity() == 220 );
  }
};
