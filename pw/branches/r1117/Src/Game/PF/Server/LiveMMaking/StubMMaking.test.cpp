//!Component("Server/LiveMMaking/SimpleMMaking")
//!Component('Server/LiveMMaking/MmTesting')

#include "stdafx.h"
#include "MmTesting.h"
#include "SimpleMMaking.h"
#include "MMakingLog.h"

#include <set>


struct Test_StubMMaking : public CxxTest::TestSuite, public MMakingTestBase
{
  StrongMT<mmaking::StubMMaking> mm;
  bool manoeuvresEnabled;

  struct STestReq
  {
    mmaking::TUserId        mmId;
    mmaking::TRequestUId    reqId;
    lobby::ETeam::Enum   team;

    STestReq() :
    mmId( 0 ), reqId( 0 ), team( lobby::ETeam::None ) {}

    STestReq( mmaking::TUserId _mmId, mmaking::TRequestUId _reqId, lobby::ETeam::Enum _team ) :
    mmId( _mmId ), reqId( _reqId ), team( _team )
    {
    }
  };


  typedef vector<STestReq>  TRefGame;


  static bool Equals( const TRefGame & vec, const mmaking::SGame & game )
  {
    int total = 0;
    for ( int j = 0; j < game.humans.size(); ++j )
      total += game.humans[j].members.size();

    if ( vec.size() != total )
      return false;

    for ( int i = 0; i < vec.size(); ++i )
    {
      const mmaking::TUserId mmId = vec[i].mmId;
      const mmaking::TRequestUId reqId = vec[i].reqId;
      const lobby::ETeam::Enum team = vec[i].team;

      bool found = false;
      for ( int j = 0; !found && j < game.humans.size(); ++j )
      {
        const mmaking::SGameParty & memb = game.humans[j];
        if ( ( memb.requestUId == reqId ) && ( memb.common.team == team ) )
          for ( int k = 0; !found && k < memb.members.size(); ++k )
            if ( memb.members[k].mmId == mmId )
              found = true;
      }
      if ( !found )
        return false;
    }
    return true;
  };


  virtual void setUp()
  {
    manoeuvresEnabled = true;
    setUpMmTest();
  }



  virtual void tearDown()
  {
    mm = 0;
    tearDownMmTest();
  }


  void SetupMM( int _teamSize, float mockMinimumUserWait = 1.0, NDb::EMapType _mapType = NDb::MAPTYPE_PVP )
  {
    mmConfig->logLevel = mmaking::ELogLevel::Verbose;
    mmConfig->mockMinimumUserWait = mockMinimumUserWait;
    mm = new mmaking::StubMMaking( settings, mmConfig, heroes, _teamSize, _mapType, "MyMapId", 0 );
    mm->EnableAlgoStartRotation( false );
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


  void AddReqs( TRefGame & _game, mmaking::TUserId _baseUserId, lobby::ETeam::Enum _team, int _count )
  {
    _game.reserve( _game.size() + _count );
    for ( int i = 0; i < _count; ++i )
    {
      string hero = ( i % 2 ) ? MaleHero( i % 5 ) : FemaleHero( i % 5 );

      mmaking::TUserId userId = _baseUserId + i;
      mmaking::TRequestUId reqId = AddSingle( userId, _team, hero.c_str(), lobby::ESex::Male );
      _game.push_back( STestReq( userId, reqId, _team ) );
    }
  }



  mmaking::TRequestUId AddParty( TRefGame & _game, mmaking::TUserId _baseUserId, lobby::ETeam::Enum _team, int _count )
  {
    mmaking::SRequestCommonData common( _team, 101, manoeuvresEnabled );

    vector<mmaking::SRequestMember> members;
    members.reserve( _count );

    mmaking::TRequestUId reqUId = nextReqId++;

    _game.reserve( _game.size() + _count );
    for ( int i = 0; i < _count; ++i )
    {
      mmaking::TUserId mmId = _baseUserId + i;
      members.push_back();
      mmaking::SRequestMember & memb = members.back();
      memb.mmId = mmId;
      memb.sex = ( i % 2 ) ? lobby::ESex::Male : lobby::ESex::Female;
      memb.heroId = ( i % 2 ) ? MaleHero( i % 5 ) : FemaleHero( i % 5 );
      memb.playerRating = 0;

      _game.push_back( STestReq( mmId, reqUId, _team ) );
    }

    mm->AddGroupRequest( reqUId, common, members, 0, logicCallback );

    return reqUId;
  }



  void CheckNoGame()
  {
    mmaking::SGame game;
    TS_ASSERT( !mm->PopGame( game ) );
  }

  void CheckGame( const TRefGame & _refGame, lobby::ETeam::Enum _manoeuvresFaction = lobby::ETeam::None ) {
    mmaking::SGame game;
    bool gameReady = mm->PopGame( game );
    TS_ASSERT( gameReady );
    if ( gameReady ) {
      TS_ASSERT( Equals( _refGame, game ) );
      TS_ASSERT_EQUALS( game.manoeuvresFaction, _manoeuvresFaction );
    }
  }



  void BasicTest( int _teamSize )
  {
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, _teamSize );
    AddReqs( game, 110, lobby::ETeam::Team2, _teamSize );
    Poll( 5.0 );
    CheckGame( game );
    Poll( 10.0 );
    CheckNoGame();
  }


  void test_Basic1() { BasicTest( 1 ); }
  void test_Basic2() { BasicTest( 2 ); }
  void test_Basic5() { BasicTest( 5 ); }


  void OneTeamNoDataTest( int _teamSize, lobby::ETeam::Enum _team )
  {
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, _team, _teamSize * 3 );
    Poll( 5.0 );
    CheckNoGame();
  }

  void test_OneTeamNoDataTest1() { OneTeamNoDataTest( 1, lobby::ETeam::Team1 ); }
  void test_OneTeamNoDataTest2() { OneTeamNoDataTest( 2, lobby::ETeam::Team2 ); }
  void test_OneTeamNoDataTest5() { OneTeamNoDataTest( 5, lobby::ETeam::Team1 ); }


  void TwoTeamsNoDataTest( int _teamSize )
  {
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, _teamSize );
    AddReqs( game, 110, lobby::ETeam::Team2, _teamSize - 1 );
    Poll( 5.0 );
    CheckNoGame();
  }

  void test_TwoTeamsNoDataTest1() { TwoTeamsNoDataTest( 1 ); }
  void test_TwoTeamsNoDataTest2() { TwoTeamsNoDataTest( 2 ); }
  void test_TwoTeamsNoDataTest6() { TwoTeamsNoDataTest( 5 ); }


  void RemoveTest( int _teamSize )
  {
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, _teamSize + 1 );
    Poll( 1.0 );
    CheckNoGame();

    int removeIdx = Max( _teamSize - 1, 1 );
    mm->RemoveRequest( game[removeIdx].reqId, logicCallback );
    game.erase( game.begin() + removeIdx );

    AddReqs( game, 100, lobby::ETeam::Team2, _teamSize );
    Poll( 2.0 );

    CheckGame( game );
    CheckNoGame();
  }


  void test_Remove1() { RemoveTest( 1 ); }
  void test_Remove2() { RemoveTest( 2 ); }
  void test_Remove5() { RemoveTest( 5 ); }


  void NoDataRemoveTest( int _teamSize )
  {
    SetupMM( _teamSize );

    for ( int i = 0; i < 2; ++i )
    {
      TRefGame game;

      AddReqs( game, 100 + i * 100, i ? lobby::ETeam::Team2 : lobby::ETeam::Team1, _teamSize * 3 );
      Poll( 5.0 + i * 5.0 );
      CheckNoGame();

      for ( int j = 0; j < game.size(); ++j )
        mm->RemoveRequest( game[j].reqId, logicCallback );
    }

    BasicTest( _teamSize );
  }

  void test_NoData_Remove1() { NoDataRemoveTest( 1 ); }
  void test_NoData_Remove2() { NoDataRemoveTest( 2 ); }
  void test_NoData_Remove5() { NoDataRemoveTest( 5 ); }


  void test_WaitTime()
  {
    SetupMM( 3, 30.0f );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, 2 );
    AddReqs( game, 110, lobby::ETeam::Team2, 2 );
    Poll( 10.0 );
    CheckNoGame();

    AddReqs( game, 200, lobby::ETeam::Team1, 1 );
    AddReqs( game, 210, lobby::ETeam::Team2, 1 );
    Poll( 15.0 );
    CheckNoGame();

    Poll( 25.0 );
    CheckNoGame();

    Poll( 40.0 );
    CheckGame( game );
  }



  void GroupTest( int _teamSize, int _p1size, int _p2size )
  {
    SetupMM( _teamSize );

    TRefGame game;

    TS_ASSERT( _p1size + _p2size == _teamSize );
    if ( _p1size )
      AddParty( game, 100, lobby::ETeam::Team1, _p1size );
    if ( _p2size )
      AddParty( game, 110, lobby::ETeam::Team1, _p2size );
    
    if ( _p1size )
      AddParty( game, 200, lobby::ETeam::Team2, _p1size );
    if ( _p2size )
      AddParty( game, 210, lobby::ETeam::Team2, _p2size );

    Poll( 5.0 );
    CheckGame( game );
    Poll( 10.0 );
    CheckNoGame();
  }

  void test_GroupsBasic1() { GroupTest( 1, 1, 0 ); }
  void test_GroupsBasic2() { GroupTest( 2, 2, 0 ); }
  void test_GroupsBasic5() { GroupTest( 5, 5, 0 ); }
  void test_GroupsBasic32() { GroupTest( 5, 3, 2 ); }
  void test_GroupsBasic41() { GroupTest( 5, 4, 1 ); }


  void MixedTest( int _teamSize, int _1size, int _p1size, int _2size, int _p2size )
  {
    SetupMM( _teamSize );

    TRefGame game;

    TS_ASSERT( ( _p1size + _1size == _teamSize ) && ( _p2size + _2size == _teamSize ) );
    if ( _1size )
      AddReqs( game, 100, lobby::ETeam::Team1, _1size );
    if ( _p1size )
      AddParty( game, 110, lobby::ETeam::Team1, _p1size );
   
    if ( _2size )
      AddReqs( game, 200, lobby::ETeam::Team2, _2size );
    if ( _p2size )
      AddParty( game, 210, lobby::ETeam::Team2, _p2size );

    Poll( 5.0 );
    CheckGame( game );
    Poll( 10.0 );
    CheckNoGame();
  }

  void test_Mixed_2x11() { MixedTest( 2, 0, 2, 2, 0 ); }
  void test_Mixed_11x2() { MixedTest( 2, 2, 0, 0, 2 ); }

  void test_Mixed_5x2111() { MixedTest( 5, 0, 5, 3, 2 ); }
  void test_Mixed_3111x5() { MixedTest( 5, 3, 2, 0, 5 ); }


  void test_PF_35318()
  {
    SetupMM( 2 );
    mm->EnableAlgoStartRotation( true );

    TRefGame game, nul;

    AddReqs( nul, 100, lobby::ETeam::Team1, 1 );
    AddParty( game, 110, lobby::ETeam::Team1, 2 );
    AddReqs( game, 120, lobby::ETeam::Team2, 2 );

    Poll( 1.0 );

    CheckGame( game );
    Poll( 10.0 );
    CheckNoGame();
  }



  void TestManoeuvres( int _teamSize )
  {
    mmConfig->testManoeuvresWaitThreshold = 20.0f;
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, _teamSize );
    AddReqs( game, 110, lobby::ETeam::Team1, _teamSize );

    for ( int i = _teamSize; i < 2 * _teamSize; ++i )
      game[i].team = lobby::ETeam::Team2;

    Poll( 1.0 );
    CheckNoGame();

    Poll( 21.0 );
    CheckGame( game, lobby::ETeam::Team1 );
    Poll( 1.0 );
    CheckNoGame();
  }


  void test_Manoeuvres1() { TestManoeuvres( 1 ); }
  void test_Manoeuvres2() { TestManoeuvres( 2 ); }
  void test_Manoeuvres5() { TestManoeuvres( 5 ); }


  void test_ManoeuvresParty2x2_I()
  {
    mmConfig->testManoeuvresWaitThreshold = 20.0f;
    SetupMM( 2 );

    TRefGame game;

    AddParty( game, 100, lobby::ETeam::Team1, 2 );
    AddParty( game, 110, lobby::ETeam::Team1, 2 );
    for ( int i = 2; i < 4; ++i )
      game[i].team = lobby::ETeam::Team2;

    Poll( 1.0 );
    CheckNoGame();

    Poll( 21.0 );
    CheckGame( game, lobby::ETeam::Team1 );
    Poll( 1.0 );
    CheckNoGame();
  }


  void TestNoManoeuvres( int _teamSize )
  {
    mmConfig->testManoeuvresWaitThreshold = 20.0f;
    SetupMM( _teamSize );

    TRefGame game;

    AddReqs( game, 100, lobby::ETeam::Team1, _teamSize );

    manoeuvresEnabled = false;
    AddReqs( game, 110, lobby::ETeam::Team1, _teamSize );

    Poll( 1.0 );
    CheckNoGame();
    Poll( 21.0 );
    CheckNoGame();
    Poll( 1.0 );
    CheckNoGame();
  }


  void test_NoManoeuvres1() { TestNoManoeuvres( 1 ); }
  void test_NoManoeuvres2() { TestNoManoeuvres( 2 ); }
  void test_NoManoeuvres5() { TestNoManoeuvres( 5 ); }



  void test_pve()
  {
    SetupMM( 5, 1.0, NDb::MAPTYPE_COOPERATIVE );

    TRefGame game1, game2;

    AddReqs( game1, 100, lobby::ETeam::Team1, 5 );
    AddReqs( game2, 110, lobby::ETeam::Team2, 5 );
    Poll( 5.0 );
    CheckGame( game1 );
    CheckGame( game2 );
    Poll( 10.0 );
    CheckNoGame();
  }
};
