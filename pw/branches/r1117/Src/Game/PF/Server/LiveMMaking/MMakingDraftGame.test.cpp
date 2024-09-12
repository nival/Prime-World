//!Component('Server/LiveMMaking/MMakingUtils')
//!Component('Server/LiveMMaking/MmTesting')

#include "stdafx.h"
#include "MmTesting.h"
#include "MMakingDraftGame.h"


struct Test_MMakingDraftGame : public CxxTest::TestSuite, public MMakingTestBase
{
  ScopedPtr<mmaking::GeoTable> geolocation;
  ScopedPtr<mmaking::GeoTable> locales;
  StrongMT<mmaking::Loger> loger;

  virtual void setUp()
  {
  }



  virtual void tearDown()
  {
    tearDownMmTest();
    
    Reset( geolocation, 0 );
    Reset( locales, 0 );
    loger = 0;
  }


  void CustomInit( int heroesCount = 30, int botHeroesCount = 20, int enemyBotsHeroesCount = 10, bool maleHeroes = true , bool femaleHeroes = true )
  {
    setUpMmTest( heroesCount, botHeroesCount, enemyBotsHeroesCount, maleHeroes, femaleHeroes );

    loger = new mmaking::Loger( "mm_unittest", "Header" );
    Reset( geolocation,  new mmaking::GeoTable( "ru0", "", "" ) );
    Reset( locales,  new mmaking::GeoTable( "ru", "", "" ) );
  }
  

  void helper_add_requests( mmaking::MMakingDraftGame & draft, int t1males, int t1females, int t2males, int t2females )
  {
    mmaking::TUserId uid = 100500;

    if ( t1males + t1females )
    {
      Strong<mmaking::MmRequest> req = new mmaking::MmRequest( settings, 1, 0.0, mmaking::SRequestCommonData( lobby::ETeam::Team1, 101, true ) );
      vector<mmaking::SRequestMember> members;
      for ( int i = 0; i < t1males; ++i )
        members.push_back( mmaking::SRequestMember( uid++, MaleHero( i ), lobby::ESex::Male, mmaking::EBasket::Normal, 700, 700, 700, 100, mmaking::SGeoInfo( "ru" ), 0, 0, 1 ) );

      for ( int i = 0; i < t1females; ++i )
        members.push_back( mmaking::SRequestMember( uid++, FemaleHero( i ), lobby::ESex::Female, mmaking::EBasket::Normal, 700, 700, 700, 100, mmaking::SGeoInfo( "ru" ), 0, 0, 1 ) );

      req->Init( members, heroes, ranks, *Get( locales ), *Get( geolocation ), loger );
      draft.AddMemebers( req );
    }

    if ( t2males + t2females )
    {
      Strong<mmaking::MmRequest> req = new mmaking::MmRequest( settings, 2, 0.0, mmaking::SRequestCommonData( lobby::ETeam::Team2, 101, true ) );
      vector<mmaking::SRequestMember> members;

      for ( int i = 0; i < t2males; ++i )
        members.push_back( mmaking::SRequestMember( uid++, MaleHero( i ), lobby::ESex::Male, mmaking::EBasket::Normal, 700, 700, 700, 100, mmaking::SGeoInfo( "ru" ), 0, 0, 1 ) );

      for ( int i = 0; i < t2females; ++i )
        members.push_back( mmaking::SRequestMember( uid++, FemaleHero( i ), lobby::ESex::Female, mmaking::EBasket::Normal, 700, 700, 700, 100, mmaking::SGeoInfo( "ru" ), 0, 0, 1 ) );

      req->Init( members, heroes, ranks, *Get( locales ), *Get( geolocation ), loger );
      draft.AddMemebers( req );
    }

  }
  
  void test_basic()
  {
    CustomInit();

    mmaking::MMakingDraftGame draft;
    draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
    helper_add_requests( draft, 2, 1, 1, 0 );

    TS_ASSERT_EQUALS( draft.GameSize(), 4 );

    TS_ASSERT_EQUALS( draft.RequestsCount( lobby::ETeam::Team1 ), 1 );
    TS_ASSERT_EQUALS( draft.RequestsCount( lobby::ETeam::Team2 ), 1 );

    TS_ASSERT_EQUALS( draft.TeamSize( lobby::ETeam::Team1 ), 3 );
    TS_ASSERT_EQUALS( draft.TeamSize( lobby::ETeam::Team2 ), 1 );

    TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team1 ), 2 );
    TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team2 ), 1 );
    TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team1 ), 1 );
    TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team2 ), 0 );

    TS_ASSERT( !draft.CanGoToTeam( lobby::ETeam::Team1, 3 ) );
    TS_ASSERT( draft.CanGoToTeam( lobby::ETeam::Team2, 3 ) );
  }


  //TODO: tests for: FindHeroForPlayer, CountHeroesOfType, AssignAutoHeroes, ProduceResult  etc

  void test_bots_roll_disable()
  {
    CustomInit( 30, 20, 10 );

    //Heroes are randomized, let's try many times
    for ( int i = 0; i < 100; ++i ) {
      mmaking::MMakingDraftGame draft;
      draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
      helper_add_requests( draft, 1, 1, 0, 0 );
      draft.AddBots();

      mmaking::SGame game;
      draft.ProduceResult( game, NDb::MAPTYPE_PVP, "", 0.0 );

      for ( int j = 0; j < game.bots.size(); ++j ) {
        TS_ASSERT( game.bots[j].heroId.length() > 1 );
        int heroIndex = atoi( game.bots[j].heroId.c_str() + 1 );
        TS_ASSERT( heroIndex );
        if ( game.bots[j].team == lobby::ETeam::Team1 )
          TS_ASSERT( heroIndex <= 20 ) //Ally bots
        else
          TS_ASSERT( heroIndex <= 10 ); //Ally or foe bots
      }
    }
  }
  


  void test_bots_roll_gender1()
  {
    CustomInit();

    //Heroes are randomized, let's try many times
    for ( int i = 0; i < 100; ++i ) {
      mmaking::MMakingDraftGame draft;
      draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
      helper_add_requests( draft, 1, 0, 0, 0 );

      draft.AddBots( 2 );

      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team1 ), 3 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team1 ), 2 );
      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team2 ), 3 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team2 ), 2 );
    }
  }


  void test_bots_roll_gender2()
  {
    CustomInit();

    //Heroes are randomized, let's try many times
    for ( int i = 0; i < 100; ++i ) {
      mmaking::MMakingDraftGame draft;
      draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
      helper_add_requests( draft, 0, 0, 0, 2 );

      draft.AddBots( 1 );

      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team1 ), 4 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team1 ), 1 );
      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team2 ), 3 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team2 ), 2 );
    }
  }


  void test_bots_not_enough_heroes1()
  {
    CustomInit( 30, 1, 1 );

    //Heroes are randomized, let's try many times
    for ( int i = 0; i < 100; ++i ) {
      mmaking::MMakingDraftGame draft;
      draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
      helper_add_requests( draft, 1, 0, 0, 0 );

      draft.AddBots( 2 );

      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team1 ), 3 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team1 ), 2 );
      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team2 ), 3 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team2 ), 2 );
    }
  }

  void test_bots_not_enough_heroes2()
  {
    CustomInit( 30, 20, 10, true, false );

    //Heroes are randomized, let's try many times
    for ( int i = 0; i < 100; ++i ) {
      mmaking::MMakingDraftGame draft;
      draft.Init( 5, mmaking::EBasket::Undefined, lobby::ETeam::None, heroes );
      helper_add_requests( draft, 1, 0, 0, 0 );

      draft.AddBots( 2 );

      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team1 ), 5 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team1 ), 0 );
      TS_ASSERT_EQUALS( draft.Gentlemen( lobby::ETeam::Team2 ), 5 );
      TS_ASSERT_EQUALS( draft.Ladies( lobby::ETeam::Team2 ), 0 );
    }
  }


  void test_locations_compare()
  {
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "", "" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "", "012" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "5667", "" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "88", "77" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "", "_" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "_", "" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "_abc", "_qwe" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "", "x" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "x", "" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "1", "x" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "x1", "" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "ru0", "ru1" ) );
    TS_ASSERT( mmaking::GeoTable::LocationsIdEqual( "ru", "ru3" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru0", "" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru0", "us0" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru", "us" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru555", "en_x" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru", "russ" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru5", "russ" ) );
    TS_ASSERT( !mmaking::GeoTable::LocationsIdEqual( "ru2", "russ0" ) );
  }
};
