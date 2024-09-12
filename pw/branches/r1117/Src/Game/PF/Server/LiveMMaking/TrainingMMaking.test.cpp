//!Component("Server/LiveMMaking/SimpleMMaking")
//!Component('Server/LiveMMaking/MmTesting')

#include "stdafx.h"
#include "MmTesting.h"
#include "SimpleMMaking.h"
#include "MMakingLog.h"



struct Test_TrainingMMaking : public CxxTest::TestSuite, public MMakingTestBase
{
  StrongMT<mmaking::SingleplayerMMaking> mm;
  mmaking::TRequestUId nextReqId;
  bool  manoeuvresEnabled;

  virtual void setUp()
  {
    manoeuvresEnabled = true;

    setUpMmTest();

    mmConfig->logLevel = mmaking::ELogLevel::Verbose;
    mm = new mmaking::SingleplayerMMaking( settings, mmConfig, heroes, 5, NDb::MAPTYPE_TRAINING, "MyMapId", 0 );
  }



  virtual void tearDown()
  {
    mm = 0;

    tearDownMmTest();
  }


  void Poll( timer::Time _t )
  {
    mm->SetTime( _t );
    mm->Poll();
  }


  mmaking::TRequestUId AddSingle( mmaking::TUserId _mmId, lobby::ETeam::Enum _team ) {
    return AddSingle( nextReqId++, 0, _mmId, _team, "M1", lobby::ESex::Male );
  }

  mmaking::TRequestUId AddSingle( mmaking::TUserId _mmId, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex ) {
    return AddSingle( nextReqId++, 0, _mmId, _team, _hero, _sex );
  }

  mmaking::TRequestUId AddSingle( mmaking::TRequestUId _reqUId, timer::Time _waitTime, mmaking::TUserId _mmId, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex )
  {
    mmaking::SRequestCommonData common( _team, 101, manoeuvresEnabled );

    vector<mmaking::SRequestMember> members( 1 );
    mmaking::SRequestMember & memb = members.back();
    memb.mmId = _mmId;
    memb.heroId = _hero;
    memb.sex = _sex;
    memb.playerRating = 0;

    mm->AddGroupRequest( _reqUId, common, members, 0, logicCallback );

    return _reqUId;
  }


  void CheckGame( const mmaking::SGame & _game, mmaking::TUserId _userId )
  {
    std::set<mmaking::TUserId> refUserIds;
    refUserIds.insert( _userId );
    CheckGame( _game, refUserIds );
  }

  void CheckGame( const mmaking::SGame & game, std::set<mmaking::TUserId> & _refUserIds )
  {
    TS_ASSERT( game.bots.size() == 10 - (int)_refUserIds.size() );
    TS_ASSERT( game.humans.size() == 1 );

    std::set<mmaking::TUserId> humanUserIds;
    for ( int i = 0; i < game.humans[0].members.size(); ++i )
      humanUserIds.insert( game.humans[0].members[i].mmId );

    TS_ASSERT_EQUALS( humanUserIds, _refUserIds );
    TS_ASSERT_EQUALS( humanUserIds.size() + game.bots.size(), mm->TeamSize() * 2 );

    int ladies[2] = { 0, 0 }, gents[2] = { 0, 0 };

    for ( int i = 0; i < game.humans.size(); ++i )
    {
      int teamIndex = lobby::ETeam::Index( game.humans[i].common.team );

      for ( int k = 0; k < game.humans[i].members.size(); ++k )
        if ( game.humans[i].members[k].sex == lobby::ESex::Male )
          ++gents[teamIndex];
        else if ( game.humans[i].members[k].sex == lobby::ESex::Female )
          ++ladies[teamIndex];
        else
          TS_ABORT();
    }

    std::set<std::string> botsHeroes[2];
    for ( int i = 0; i < game.bots.size(); ++i )
    {
      int teamIndex = -1;
      if ( game.bots[i].team == lobby::ETeam::Team1 )
        teamIndex = 0;
      else if ( game.bots[i].team == lobby::ETeam::Team2 )
        teamIndex = 1;
      else
        TS_ABORT();

      const string & heroId = game.bots[i].heroId;
      TS_ASSERT( !heroId.empty() );
      TS_ASSERT( heroId[0] == 'M' || heroId[0] == 'F' );
      if ( heroId[0] == 'M' )
        ++gents[teamIndex];
      else if ( heroId[0] == 'F' )
        ++ladies[teamIndex];
      else
        TS_ABORT();

      TS_ASSERT( botsHeroes[teamIndex].insert( std::string( heroId.c_str() ) ).second );
    }

    TS_ASSERT_EQUALS( gents[0] + ladies[0], gents[1] + ladies[1] );
  }


  void test_BasicTest1()
  {
    const int userIds[] = { 5, 10, 33 };
    const int count = sizeof( userIds ) / sizeof(int);

    for ( int i = 0; i < count; ++i )
    {
      lobby::ETeam::Enum team = ( i % 2 ) ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
      string hero = ( i % 2 ) ? MaleHero( i ) : FemaleHero( i );
      AddSingle( userIds[i], team, hero.c_str(), lobby::ESex::Male );
    }

    Poll( 5.0 );

    for ( int i = 0; i < count; ++i )
    {
      mmaking::SGame game;
      bool gameReady = mm->PopGame( game );
      TS_ASSERT( gameReady );
      CheckGame( game, userIds[i] );
    }

    Poll( 5.0 );

    mmaking::SGame game;
    TS_ASSERT( !mm->PopGame( game ) );
  }



  void test_Remove()
  {
    const int userIds[] = { 10, 20, 30, 40 };
    const int count = sizeof( userIds ) / sizeof(int);
    int reqIds[count] = {};

    for ( int i = 0; i < count; ++i )
    {
      lobby::ETeam::Enum team = ( i % 2 ) ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
      string hero = ( i % 2 ) ? MaleHero( i ) : FemaleHero( i );
      reqIds[i] = AddSingle( userIds[i], team, hero.c_str(), lobby::ESex::Male );
    }

    mm->RemoveRequest( reqIds[1], logicCallback );

    Poll( 5.0 );

    for ( int i = 0; i < count; ++i )
    {
      if ( i == 1 )
        continue;

      mmaking::SGame game;
      bool gameReady = mm->PopGame( game );
      TS_ASSERT( gameReady );
      CheckGame( game, userIds[i] );
    }

    Poll( 5.0 );

    mmaking::SGame game;
    TS_ASSERT( !mm->PopGame( game ) );
  }



  void test_Restore()
  {
    const int userIds[] = { 10, 20, 30, 40 };
    const int count = sizeof( userIds ) / sizeof(int);

    for ( int i = 0; i < count; ++i )
    {
      lobby::ETeam::Enum team = ( i % 2 ) ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
      string hero = ( i % 2 ) ? MaleHero( i ) : FemaleHero( i );
      AddSingle( userIds[i], team, hero.c_str(), lobby::ESex::Male );
    }

    Poll( 5.0 );

    mmaking::SGameParty gameElem[count] = {};

    for ( int i = 0; i < count; ++i )
    {
      mmaking::SGame game;
      bool gameReady = mm->PopGame( game );
      TS_ASSERT( gameReady );
      CheckGame( game, userIds[i] );
      gameElem[i] = game.humans[0];
    }

    {
      mmaking::SGame game;
      TS_ASSERT( !mm->PopGame( game ) );
    }

    const mmaking::SGameParty & prty = gameElem[2];
    AddSingle( prty.requestUId, prty.waitTime, prty.members[0].mmId, prty.common.team, prty.members[0].heroId.c_str(), prty.members[0].sex );

    Poll( 5.0 );

    {
      mmaking::SGame game;
      bool gameReady = mm->PopGame( game );
      TS_ASSERT( gameReady );
      CheckGame( game, prty.members[0].mmId );
    }

    {
      mmaking::SGame game;
      TS_ASSERT( !mm->PopGame( game ) );
    }
  }



  void test_Party()
  {
    mmaking::SGeoInfo geo( "ru" );

    vector<mmaking::SRequestMember> members;
    members.push_back( mmaking::SRequestMember( 10, "M1", lobby::ESex::Male, mmaking::EBasket::Normal, 0, 0, 0, 0, geo, 0, 0, 1 ) );
    members.push_back( mmaking::SRequestMember( 101, "M2", lobby::ESex::Male, mmaking::EBasket::Normal, 0, 0, 0, 0, geo, 0, 0, 1 ) );
    members.push_back( mmaking::SRequestMember( 1001, "F1", lobby::ESex::Female, mmaking::EBasket::Normal, 0, 0, 0, 0, geo, 0, 0, 1 ) );

    mm->AddGroupRequest( 1, mmaking::SRequestCommonData( lobby::ETeam::Team1, 101, manoeuvresEnabled ), members, 0, logicCallback );

    Poll( 5.0 );

    mmaking::SGame game;
    bool gameReady = mm->PopGame( game );
    TS_ASSERT( gameReady );

    std::set<mmaking::TUserId> userIds;
    userIds.insert( 10 );
    userIds.insert( 101 );
    userIds.insert( 1001 );
    CheckGame( game, userIds );

    Poll( 5.0 );

    TS_ASSERT( !mm->PopGame( game ) );
  }
};
