//!Component("Server/LiveMMaking/RatingSortMmLogic")
//!Component('Server/LiveMMaking/ProdMMLogicTesting')

#include "stdafx.h"
#include "ProdMMLogicTesting.h"
#include "RatingSortMmLogic.h"
#include "System/RandomGenerator.h"


struct Test_RatingSortMatchmakin : public CxxTest::TestSuite, public ProdMMLogicTesting<mmaking::RatingSortMmLogic>
{
  NRandom::RandomGenerator random;

  virtual void setUp()
  {
    setUpProdMmTest();

    NDb::MapMMakingSettings * hacked = WriteConfig();
    hacked->ratingScale.low = 1200;
    hacked->ratingScale.high = 2500;
    hacked->ratingScale.step = 100;
    hacked->ratingScale.diffLow.push_back();
    hacked->ratingScale.diffLow[0].x = 1500;
    hacked->ratingScale.diffLow[0].y = 200;
    hacked->ratingScale.diffHigh.push_back();
    hacked->ratingScale.diffHigh[0].x = 1500;
    hacked->ratingScale.diffHigh[0].y = 500;

    hacked->forceScale.low = 90;
    hacked->forceScale.high = 180;
    hacked->forceScale.step = 10;
    hacked->forceScale.diffLow.push_back();
    hacked->forceScale.diffLow[0].x = 130;
    hacked->forceScale.diffLow[0].y = 30;
    hacked->forceScale.diffHigh.push_back();
    hacked->forceScale.diffHigh[0].x = 130;
    hacked->forceScale.diffHigh[0].y = 30;

    StrongMT<mmaking::RatingSortMmLogic> specLogic = new mmaking::RatingSortMmLogic( settings, mmConfig, heroes, 5, NDb::MAPTYPE_PVP, "MyMapId", 0 );
    logic = specLogic;
  }



  virtual void tearDown()
  {
    tearDownProdMmTest();
  }


  void add_XbyX( SRefGame & game, int n, int ratingBase, int ratingInc, bool randomize )
  {
    struct SPattern { lobby::ESex::Enum sex; const char * hero; } pattern[] = {
      { lobby::ESex::Male, "M1" },
      { lobby::ESex::Male, "M2" },
      { lobby::ESex::Male, "M3" },
      { lobby::ESex::Female, "M1" },
      { lobby::ESex::Female, "M2" }
    };
    size_t patternSize = sizeof( pattern ) / sizeof( pattern[0] );

    for ( int i = 0; i < n; ++i ) {
      int idx0 = randomize ? random.Next( patternSize ) : ( i % patternSize );
      lobby::ESex::Enum s0 = pattern[idx0].sex;
      const char * h0 = pattern[ i % patternSize ].hero;
      int r0 = ( randomize && ratingInc ) ? ( ratingBase + random.Next( ratingInc ) ) : ( ratingBase + i * ratingInc );

      int idx1 = randomize ? random.Next( patternSize ) : ( i % patternSize );
      lobby::ESex::Enum s1 = pattern[idx1].sex;
      const char * h1 = pattern[ i % patternSize].hero;
      int r1 = ( randomize && ratingInc ) ? ( ratingBase + random.Next( ratingInc ) ) : ( ratingBase + i * ratingInc );

      AddSingle_R( game, lobby::ETeam::Team1, h0, s0, r0 );
      AddSingle_R( game, lobby::ETeam::Team2, h1, s1, r1 );
    }
  }

  //
  // Tests itself
  //
  void test_smoke()
  {
    SRefGame g;

    AddSingle( g, lobby::ETeam::Team1, "M1", lobby::ESex::Male );
    AddSingle( g, lobby::ETeam::Team1, "M2", lobby::ESex::Male );

    AddSingle( g, lobby::ETeam::Team2, "F1", lobby::ESex::Female );
    AddSingle( g, lobby::ETeam::Team2, "M4", lobby::ESex::Male );

    AddSingle( g, lobby::ETeam::Team1, "M3", lobby::ESex::Male );
    AddSingle( g, lobby::ETeam::Team1, "M4", lobby::ESex::Male );
    AddSingle( g, lobby::ETeam::Team1, "F1", lobby::ESex::Female );

    AddSingle( g, lobby::ETeam::Team2, "M1", lobby::ESex::Male );
    AddSingle( g, lobby::ETeam::Team2, "M2", lobby::ESex::Male );
    AddSingle( g, lobby::ETeam::Team2, "M3", lobby::ESex::Male );

    PollMM( 1.0 );
    //CheckGame( g );
  }



  void test_bad_but_acceptable_rating()
  {
    SRefGame g;

    AddSingle_R( g, lobby::ETeam::Team1, "M1", lobby::ESex::Male, 1200 );
    AddSingle_R( g, lobby::ETeam::Team1, "M2", lobby::ESex::Male, 1200 );
    AddSingle_R( g, lobby::ETeam::Team1, "M3", lobby::ESex::Male, 1500 );
    AddSingle_R( g, lobby::ETeam::Team1, "M4", lobby::ESex::Male, 1500 );
    AddSingle_R( g, lobby::ETeam::Team1, "F2", lobby::ESex::Female, 1800 );

    AddSingle_R( g, lobby::ETeam::Team2, "F1", lobby::ESex::Male, 1000 );
    AddSingle_R( g, lobby::ETeam::Team2, "M1", lobby::ESex::Male, 1500 );
    AddSingle_R( g, lobby::ETeam::Team2, "M2", lobby::ESex::Male, 1500 );
    AddSingle_R( g, lobby::ETeam::Team2, "M3", lobby::ESex::Male, 1800 );
    AddSingle_R( g, lobby::ETeam::Team2, "M4", lobby::ESex::Female, 1200 );

    PollMM( 1.0 );
    CheckGameNotReady();
    PollMM( 1200.0 );
    CheckGame( g );
  }


  void xtest_10x10()
  {
    SRefGame g;
    add_XbyX( g, 10, 1000, 100, false );
    PollMM( 1.0 );
    CheckGame( g );
  }

  void test_10x10_rand()
  {
    random.SetSeed( 100 );

    SRefGame g;
    add_XbyX( g, 10, 1000, 2000, true );
    PollMM( 1.0 );
    CheckGameNotReady();
    PollMM( 180.0 );
    //CheckGame( g );
  }

  void xtest_15x15()
  {
    SRefGame g;
    add_XbyX( g, 15, 1000, 100, false );
    PollMM( 1.0 );
    CheckGame( g );
  }
};
