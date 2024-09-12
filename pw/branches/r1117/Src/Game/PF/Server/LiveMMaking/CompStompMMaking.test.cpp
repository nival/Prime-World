//!Component('Server/LiveMMaking/SimpleMMaking')
//!Component('Server/LiveMMaking/MmTesting')

#include "stdafx.h"

#include "SimpleMMaking.h"
#include "MMakingLog.h"
#include "MmTesting.h"

#include <set>


struct Test_CompStompMMaking : public CxxTest::TestSuite, public MMakingTestBase
{
  StrongMT<mmaking::CompStompMMaking> mm;

  virtual void setUp()
  {
    setUpMmTest();

    mmConfig->logLevel = mmaking::ELogLevel::Verbose;
    mm = new mmaking::CompStompMMaking( settings, mmConfig, heroes, 5, NDb::MAPTYPE_PVP, "MyMapId", 30.0, 0 );
    mm->EnableAlgoStartRotation( false );
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
    mmaking::SRequestCommonData common( _team, 101, true );

    vector<mmaking::SRequestMember> members( 1 );
    mmaking::SRequestMember & memb = members.back();
    memb.mmId = _mmId;
    memb.heroId = _hero;
    memb.sex = _sex;
    memb.playerRating = 0; //TODO
    memb.guardRating = 0; //TODO

    mm->AddGroupRequest( _reqUId, common, members, 0, logicCallback );

    return _reqUId;
  }


  struct STestReq
  {
    mmaking::TRequestUId  reqId;
    mmaking::TUserId      mmId;

    STestReq() : reqId( 0 ), mmId( 0 ) {}
    STestReq( mmaking::TRequestUId _reqId, mmaking::TUserId _mmId ) : reqId( _reqId ), mmId( _mmId ) {}
  };

  typedef vector<STestReq> TTestGame;


  void AddReqs( TTestGame & _testGame, int baseUserId, lobby::ETeam::Enum team, int count )
  {
    _testGame.reserve( _testGame.size() + count );
    for ( int i = 0; i < count; ++i )
    {
      string hero = ( i % 2 ) ? MaleHero( i % 5 ) : FemaleHero( i % 5 );

      mmaking::TUserId userId = baseUserId + i;
      mmaking::TRequestUId reqId = AddSingle( userId, team, hero.c_str(), lobby::ESex::Male );
      _testGame.push_back( STestReq( reqId, userId ) );
    }
  }


  void CheckNoGame()
  {
    mmaking::SGame game;
    TS_ASSERT( !mm->PopGame( game ) );
  }


  void CheckGame( lobby::ETeam::Enum humanTeam, const TTestGame & _testGame )
  {
    mmaking::SGame game;
    bool gameReady = mm->PopGame( game );
    TS_ASSERT( gameReady );

    TS_ASSERT( game.bots.size() == mm->TeamSize() * 2 - _testGame.size() );
    TS_ASSERT( game.humans.size() == _testGame.size() );

    int ladies[2] = { 0, 0 }, gents[2] = { 0, 0 };

    TS_ASSERT_EQUALS( game.humans.size() + game.bots.size(), mm->TeamSize() * 2 );

    std::set<mmaking::TUserId> humanUserIds;

    for ( int i = 0; i < game.humans.size(); ++i )
    {
      TS_ASSERT_EQUALS( game.humans[i].common.team, humanTeam );

      int teamIndex = lobby::ETeam::Index( game.humans[i].common.team );

      for ( int j = 0; j < game.humans[i].members.size(); ++j )
      {
        if ( game.humans[i].members[j].sex == lobby::ESex::Male )
          ++gents[teamIndex];
        else if ( game.humans[i].members[j].sex == lobby::ESex::Female )
          ++ladies[teamIndex];
        else
          TS_ABORT();

        bool idIsUnique = humanUserIds.insert( game.humans[i].members[j].mmId ).second;
        TS_ASSERT( idIsUnique );
      }
    }

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
    }

    TS_ASSERT_EQUALS( gents[0] + ladies[0], gents[1] + ladies[1] );

    std::set<mmaking::TUserId> testUserIds;
    for ( int i = 0; i < _testGame.size(); ++i )
      testUserIds.insert( _testGame[i].mmId );

    TS_ASSERT_EQUALS( humanUserIds, testUserIds );
  }



  void test_Basic()
  {
    TTestGame team1, team2_1, team2_2;

    Poll( 1.0 );

    AddReqs( team1, 100, lobby::ETeam::Team1, 5 );
    AddReqs( team2_1, 110, lobby::ETeam::Team2, 5 );
    AddReqs( team2_2, 120, lobby::ETeam::Team2, 5 );

    Poll( 5.0 );

    CheckGame( lobby::ETeam::Team1, team1 );
    //Two full games in team2 and one through threshold
    CheckGame( lobby::ETeam::Team2, team2_1 );
    CheckGame( lobby::ETeam::Team2, team2_2 );

    Poll( 10.0 );
    CheckNoGame();
  }



  void test_Threshold()
  {
    TTestGame team1, team2_1, team2_2;

    Poll( 1.0 );

    AddReqs( team1, 100, lobby::ETeam::Team1, 2 );
    AddReqs( team2_1, 200, lobby::ETeam::Team2, 5 );
    AddReqs( team2_2, 210, lobby::ETeam::Team2, 2 );

    CheckGame( lobby::ETeam::Team2, team2_1 );
    CheckNoGame();

    Poll( 10.0 );
    CheckNoGame();

    AddReqs( team1, 110, lobby::ETeam::Team1, 2 );

    CheckNoGame();
    Poll( 20.0 );
    CheckNoGame();

    AddReqs( team2_2, 230, lobby::ETeam::Team2, 1 );

    Poll( 25.0 );
    CheckNoGame();
    Poll( 35.0 );
    CheckNoGame();

    Poll( 45.0 );
    CheckGame( lobby::ETeam::Team1, team1 );
    CheckNoGame();

    Poll( 55.0 );
    CheckGame( lobby::ETeam::Team2, team2_2 );
    CheckNoGame();
  }



  void test_Remove()
  {
    TTestGame team1;

    Poll( 1.0 );

    AddReqs( team1, 100, lobby::ETeam::Team1, 3 );

    CheckNoGame();
    Poll( 30.0 );
    CheckNoGame();

    mm->RemoveRequest( team1[2].reqId, logicCallback );
    team1.erase( team1.begin() + 2 );

    CheckNoGame();
    Poll( 60.0 );

    CheckGame( lobby::ETeam::Team1, team1 );
    CheckNoGame();
  }


  void test_Restore()
  {
    TTestGame team2;

    Poll( 1.0 );
    AddReqs( team2, 110, lobby::ETeam::Team2, 5 );
    Poll( 5.0 );
    CheckGame( lobby::ETeam::Team2, team2 );
    Poll( 10.0 );
    CheckNoGame();
  }
};
