//!Component('Server/LiveMMaking/GameEstimFunction')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "GameEstimFunction.h"
#include "Db/DbServer.auto.h"

struct GameEstimFunctionTest : public CxxTest::TestSuite
{
  NDb::Ptr<NDb::MapMMakingSettings> Data() {
    NDb::Ptr<NDb::MapMMakingSettings> db = new NDb::MapMMakingSettings;

    NDb::MapMMakingSettings * hacked = const_cast<NDb::MapMMakingSettings *>( db.GetPtr() );
    hacked; //TODO

    //hacked->forceScale.low = 100;
    //hacked->forceScale.high = 200;

    return db;
  }

  struct SData
  {
    lobby::ETeam::Enum      team;
    lobby::ESex::Enum       sex;
    mmaking::THeroShortId   hero;
    mmaking::EBasket::Enum  basket;
    int                     rating;
    int                     force;
  };

  const static int stdR = 1000;
  const static int stdF = 101;
  const static int stdW = 30;

  mmaking::SHeroClassEfficiency  stdHeroEff;

  virtual void setUp()
  {
    for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
      stdHeroEff.classes[i] = 100 / 5;
  }


  virtual void tearDown()
  {
  }


  struct Defaults
  {
    int   rating;
    float force;
    mmaking::EBasket::Enum basket;
    float wait;

    Defaults() : 
    rating( stdR ),
    force( stdF ),
    wait( stdW ),
    basket( mmaking::EBasket::Normal )
    {}
  };


  void add_std_data( mmaking::GameEstimFun & e, const Defaults & defaults, int skip = -1, ... )
  {
    SData data[] = {
      { lobby::ETeam::Team1, lobby::ESex::Male,    1,  defaults.basket,  defaults.rating, defaults.force }, //0
      { lobby::ETeam::Team1, lobby::ESex::Male,    2,  defaults.basket,  defaults.rating, defaults.force }, //1
      { lobby::ETeam::Team1, lobby::ESex::Male,    3,  defaults.basket,  defaults.rating, defaults.force }, //2
      { lobby::ETeam::Team1, lobby::ESex::Male,    4,  defaults.basket,  defaults.rating, defaults.force }, //3
      { lobby::ETeam::Team1, lobby::ESex::Female,  5,  defaults.basket,  defaults.rating, defaults.force }, //4

      { lobby::ETeam::Team2, lobby::ESex::Male,    1,  defaults.basket,  defaults.rating, defaults.force }, //5
      { lobby::ETeam::Team2, lobby::ESex::Male,    2,  defaults.basket,  defaults.rating, defaults.force }, //6
      { lobby::ETeam::Team2, lobby::ESex::Male,    3,  defaults.basket,  defaults.rating, defaults.force }, //7
      { lobby::ETeam::Team2, lobby::ESex::Male,    4,  defaults.basket,  defaults.rating, defaults.force }, //8
      { lobby::ETeam::Team2, lobby::ESex::Female,  5,  defaults.basket,  defaults.rating, defaults.force }  //9
    };

    va_list args;

    int N = sizeof(data) / sizeof(SData);
    for ( int i = 0; i < N; ++i ) {
      bool use = true;
      va_start( args, skip );
      for ( int s = skip; s >= 0; s = va_arg( args, int ) )
        if ( i == s )
          use = false;
      if ( use )
        e.Count( data[i].team, data[i].sex, data[i].hero, data[i].basket, data[i].rating, data[i].force, stdHeroEff, defaults.wait, 0, false );
    }

    va_end( args );
  }

  void test_smoke()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults() );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.0f, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, 0.0f, 1e-6f );
    TS_ASSERT_DELTA( details.sexTerm, 0.0f, 1e-6f );
    TS_ASSERT_DELTA( details.heroesTerm, 0.0f, 1e-6f );
    TS_ASSERT_EQUALS( details.waitTimeAvg, stdW );
  }


  void test_uncount1()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults() );

    estim.Uncount ( lobby::ETeam::Team2, lobby::ESex::Female, 4, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, stdW, 0, false );
    estim.Count   ( lobby::ETeam::Team2, lobby::ESex::Female, 4, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, 60, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.0f, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, 0.0f, 1e-6f );
  }


  void test_uncount2()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 3, -1 );

    estim.Count   ( lobby::ETeam::Team1, lobby::ESex::Male,    3,  mmaking::EBasket::Normal, 500, stdF, stdHeroEff, 60, 0, false );

    estim.Uncount ( lobby::ETeam::Team1, lobby::ESex::Male,    3,  mmaking::EBasket::Normal, 500, stdF, stdHeroEff, 60, 0, false );
    estim.Count   ( lobby::ETeam::Team1, lobby::ESex::Male,    4,  mmaking::EBasket::Normal, 1000, stdF, stdHeroEff, 6, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.0f, 1e-6f );
  }


  //TODO: write a test for case sex=Undefined
  void test_sex()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 3, 9, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Female,  4, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male,  5, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, stdW, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 1.0f, 1e-6f );
    TS_ASSERT_DELTA( details.sexTerm, 0.25f, 1e-6f );
    TS_ASSERT_DELTA( details.genderPairsDeltaTerm, 1.0f, 1e-6f );
    TS_ASSERT_EQUALS( details.genderPairsDelta, 2 );
  }


  void test_heroes()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 1, 2, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  1, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  1, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, stdW, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.25f, 1e-6f );
    TS_ASSERT_DELTA( details.heroesTerm, 0.25f, 1e-6f );
  }


  void test_rating()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 2, 3, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  3, mmaking::EBasket::Normal, 2000, stdF, stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  4, mmaking::EBasket::Normal, 2000, stdF, stdHeroEff, stdW, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    float avgR = 0.5f * ( 5000.0f + 7000.0f ) / 5.0;
    float rspan = 1000.0f / avgR;

    TS_ASSERT_EQUALS( details.teamRating[0], 1400 );
    TS_ASSERT_EQUALS( details.teamRating[1], stdR );
    TS_ASSERT_DELTA( details.ratingSpanTerm, rspan, 1e-6f );
    TS_ASSERT_DELTA( details.maxValue, rspan, 1e-6f );

    TS_ASSERT_EQUALS( details.ratingSpan, 1000 );
  }


  void xtest_force()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, true );

    add_std_data( estim, Defaults(), 2, 3, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  3, mmaking::EBasket::Normal, stdR, 95, stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  4, mmaking::EBasket::Normal, stdR, 158, stdHeroEff, stdW, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    int f0 = ( 303 + 95 + 158 ) / 5;
    int avgF = (int)( ( 808.0f + 95.0f + 158.0f ) / 10.0f );
    int fspan = 158 - 95;

    TS_ASSERT_EQUALS( details.avgForce, ( f0 + stdF ) / 2 );

    TS_ASSERT_EQUALS( details.forceSpan, fspan );

    TS_ASSERT_DELTA( details.forceSpanTerm, fspan / (float)avgF, 1e-6f );
    TS_ASSERT_DELTA( details.maxValue, fspan / (float)avgF, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, fspan / (float)avgF, 1e-6f );
  }


  float EfDecreaseFactor( const NDb::MapMMakingSettings * db, float w ) {
    float t = ( w - db->estimFunDecreaseTimeBegin );
    t /= ( db->estimFunDecreaseTimeEnd - db->estimFunDecreaseTimeBegin );
    t = Clamp( t, 0.0f, 1.0f );
    return Lerp( 1.0f, db->estimFunDecreaseFactor, t );
  }


  void test_wait_time()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 3, 4, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male, 4, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, 400, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male, 5, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, 400, 0, false );

    int avgWait = ( stdW * 8 + 400 * 2 ) / 10;
    int avgWaitTewaked = ( avgWait + 400 ) / 2;

    float decrease_factor = EfDecreaseFactor( Data(), avgWaitTewaked );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.5f * decrease_factor, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, ( 0.125f + 0.5f ) * decrease_factor, 1e-6f );
    TS_ASSERT_DELTA( details.sexTerm, 0.125f, 1e-6f );
    TS_ASSERT_DELTA( details.genderPairsDeltaTerm, 0.5f, 1e-6f );

    TS_ASSERT_EQUALS( details.waitTimeAvg, avgWaitTewaked );
  }


  void test_low_wait_time()
  {
    NDb::Ptr<NDb::MapMMakingSettings> db = Data();

    mmaking::GameEstimFun estim( 5, db, mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 8, 9, -1 );

    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male, 4, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, 5, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male, 5, mmaking::EBasket::Normal, stdR, stdF, stdHeroEff, 85, 0, false );

    int avgWait = ( stdW * 8 + 5 + 85 ) / 10;
    int avgWaitTewaked = ( avgWait + 85 ) / 2;

    float lowtime = ( db->lowWaitTimeThreshold - 5.0 );
    lowtime /= (float)db->lowWaitTimeThreshold;
    float increase_factor = Lerp( 1.0f, db->lowWaitTimeFactor, lowtime );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    TS_ASSERT_DELTA( details.maxValue, 0.5f * increase_factor, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, ( 0.125f + 0.5f ) * increase_factor, 1e-6f );
    TS_ASSERT_DELTA( details.sexTerm, 0.125f, 1e-6f );
    TS_ASSERT_DELTA( details.genderPairsDeltaTerm, 0.5f, 1e-6f );

    TS_ASSERT_EQUALS( details.waitTimeAvg, avgWaitTewaked );
  }


  /*
  void lose_streak_helper( int streak, int expectedLevel, float expectedPenalty )
  {
    NDb::Ptr<NDb::MapMMakingSettings> db = Data();

    mmaking::GameEstimFun estim( 5, Data(), db, mmaking::EBasket::Normal, lobby::ETeam::None, false );

    add_std_data( estim, Defaults(), 3, -1 );

    const float forceBias = 10.0f;
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male, 4, mmaking::EBasket::Normal, stdR, stdF - forceBias, stdHeroEff, stdW, streak, false );

    float decrease_factor = EfDecreaseFactor( db, stdW );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    const float avgF = stdF - forceBias / 10;

    TS_ASSERT_DELTA( details.forceSpan, forceBias, 1e-6f );
    TS_ASSERT_DELTA( details.forceSpanTerm, forceBias / avgF, 1e-6f );
    TS_ASSERT_DELTA( details.forcePatternDelta, forceBias / 5, 1e-6f );
    TS_ASSERT_DELTA( details.forcePatternDeltaTerm, forceBias / 5 / avgF, 1e-6f );
    TS_ASSERT_EQUALS( details.loseStreakCorrectionLevel, expectedLevel );
    TS_ASSERT_DELTA( details.loseStreakCorrectionTerm, expectedPenalty, 1e-6f );
    TS_ASSERT_DELTA( details.maxValue, expectedPenalty * decrease_factor, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, 0, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, ( details.forceSpanTerm + details.forcePatternDeltaTerm + details.loseStreakCorrectionTerm ) * decrease_factor, 1e-6f );
  }
  */

  /*
  void xtest_lose_streak_1()
  {
    lose_streak_helper( Data()->loseStreakCorrection.firstCaseThreshold, 1, Data()->loseStreakCorrection.firstCasePenalty );
  }


  void xtest_lose_streak_2()
  {
    lose_streak_helper( Data()->loseStreakCorrection.secondCaseThreshold, 2, Data()->loseStreakCorrection.secondCasePenalty );
  }


  void xtest_lose_streak_3()
  {
    lose_streak_helper( Data()->loseStreakCorrection.thirdCaseThreshold + 1, 3, Data()->loseStreakCorrection.thirdCasePenalty );
  }
  */


  void test_big_smoke()
  {
    mmaking::GameEstimFun estim( 5, Data(), mmaking::EBasket::Normal, lobby::ETeam::None, false );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,    1, mmaking::EBasket::Normal, 500,   125,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,    2, mmaking::EBasket::Normal, stdR,  125,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,    3, mmaking::EBasket::Normal, stdR,  140,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Female,  4, mmaking::EBasket::Normal, stdR,  140,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Female,  5, mmaking::EBasket::Normal, 1500,  190,  stdHeroEff, stdW, 0, false );

    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male,    1, mmaking::EBasket::Normal, stdR,  140,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male,    2, mmaking::EBasket::Normal, stdR,  125,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male,    3, mmaking::EBasket::Normal, stdR,  125,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Male,    3, mmaking::EBasket::Normal, stdR,  125,  stdHeroEff, stdW, 0, false );
    estim.Count( lobby::ETeam::Team2, lobby::ESex::Female,  5, mmaking::EBasket::Normal, 500,   125,  stdHeroEff, stdW, 0, false );

    mmaking::SGameEstimDetails details;
    estim.Get( details, 0 );

    int ratingSpan = 1500 - 500;
    int ratingPtrnDelta = ( 1500 - stdR ) / 5;
    int ratingAvg = ( stdR * 7 + 500 * 2 + 1500 ) / 10;
    int ratingAvgDelta = 1000 - 900;

    TS_ASSERT_EQUALS( details.ratingSpan, ratingSpan );
    TS_ASSERT_EQUALS( details.ratingPatternDelta, ratingPtrnDelta );
    TS_ASSERT_EQUALS( details.ratingTeamAvgDelta, ratingAvgDelta );

    TS_ASSERT_DELTA( details.ratingSpanTerm, ratingSpan / (float)ratingAvg, 1e-6f );
    TS_ASSERT_DELTA( details.ratingPatternDeltaTerm, ratingPtrnDelta / (float)ratingAvg, 1e-6f );
    TS_ASSERT_DELTA( details.ratingTeamAvgDeltaTerm, ratingAvgDelta / (float)ratingAvg, 1e-6f );

    //int forceSpan = 190 - 125;
    //int forcePtrnDelta = ( ( 190 - 140 ) + ( 140 - 125 ) * 2 ) / 5;
    //int forceAvg = ( 125 * 6 + 140 * 3 + 190 ) / 10;

    //TS_ASSERT_EQUALS( details.forceSpan, forceSpan );
    //TS_ASSERT_EQUALS( details.forcePatternDelta, forcePtrnDelta );

    //TS_ASSERT_DELTA( details.forceSpanTerm, forceSpan / (float)forceAvg, 1e-6f );
    //TS_ASSERT_DELTA( details.forcePatternDeltaTerm, forcePtrnDelta / (float)forceAvg, 1e-6f );

    TS_ASSERT_DELTA( details.sexTerm, 0.125f, 1e-6f );
    TS_ASSERT_EQUALS( details.genderPairsDelta, 1 );
    TS_ASSERT_DELTA( details.genderPairsDeltaTerm, 0.5, 1e-6f );

    TS_ASSERT_DELTA( details.heroesTerm, 0.125f, 1e-6f );

    TS_ASSERT_DELTA( details.maxValue, details.ratingSpanTerm, 1e-6f );
    float sum = details.ratingSpanTerm + details.ratingPatternDeltaTerm + details.ratingTeamAvgDeltaTerm +
                                            /*details.forceSpanTerm + details.forcePatternDeltaTerm + */
                                            details.sexTerm + details.genderPairsDeltaTerm + details.heroesTerm;
    TS_ASSERT_DELTA( details.sumValue, sum, 1e-6f );
  }


  struct TestDetails
  {
    int   team1force, avgForce, forcePatternDelta, forceSpan;
    int   team1rating, avgRating, ratingPatternDelta, ratingTeamAvgDelta, ratingSpan;
    TestDetails() :
    team1force( 0 ), avgForce( 0 ), forcePatternDelta( 0 ), forceSpan( 0 ),
    team1rating( 0 ), avgRating( 0 ), ratingPatternDelta( 0 ), ratingTeamAvgDelta( 0 ), ratingSpan( 0 )
    {}
  };

  void prepare_basket_test( mmaking::SGameEstimDetails & details, const mmaking::EBasket::Enum basket, TestDetails & testDetails )
  {
    mmaking::GameEstimFun estim( 5, Data(), basket, lobby::ETeam::None, false );

    Defaults defaults;
    defaults.basket = basket;
    defaults.wait = 60;
    add_std_data( estim, defaults, 2, 3, -1 );

    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  3, mmaking::EBasket::Normal, 1100, 95, stdHeroEff, 60, 0, false );
    estim.Count( lobby::ETeam::Team1, lobby::ESex::Male,  4, mmaking::EBasket::Normal, 1500, 158, stdHeroEff, 60, 0, false );

    estim.Get( details, 0 );

    testDetails.team1force = ( stdF * 3 + 95 + 158 ) / 5;
    testDetails.avgForce = (int)( ( 808.0f + 95.0f + 158.0f ) / 10.0f );
    testDetails.forcePatternDelta = ( ( 158 - stdF ) + ( stdF - 95 ) ) / 5;
    testDetails.forceSpan = 158 - 95;

    testDetails.team1rating = ( stdR * 3 + 1100 + 1500 ) / 5;
    testDetails.avgRating = (int)( ( testDetails.team1rating + stdR ) / 2.0f );
    testDetails.ratingPatternDelta = ( ( 1500 - stdR ) + ( 1100 - stdR ) ) / 5;
    testDetails.ratingTeamAvgDelta = testDetails.team1rating - stdR;
    testDetails.ratingSpan = 1500 - stdR;
  }


  void test_newbies()
  {
    mmaking::SGameEstimDetails details;

    TestDetails testDet;
    prepare_basket_test( details, mmaking::EBasket::Newbie, testDet );

    TS_ASSERT( details.valid );

    //TS_ASSERT_EQUALS( details.teamForce[0], testDet.team1force );
    //TS_ASSERT_EQUALS( details.teamForce[1], stdF );
    //TS_ASSERT_EQUALS( details.forceSpan, testDet.forceSpan );
    //TS_ASSERT_EQUALS( details.forcePatternDelta, testDet.forcePatternDelta );
    //TS_ASSERT_DELTA( details.forceSpanTerm, testDet.forceSpan / (float)testDet.avgForce, 1e-6f );
    //TS_ASSERT_DELTA( details.forcePatternDeltaTerm, testDet.forcePatternDelta / (float)testDet.avgForce, 1e-6f );

    TS_ASSERT_EQUALS( details.teamRating[0], 0 );
    TS_ASSERT_EQUALS( details.teamRating[1], 0 );
    TS_ASSERT_EQUALS( details.ratingSpan, 0 );
    TS_ASSERT_EQUALS( details.ratingPatternDelta, 0 );
    TS_ASSERT_DELTA( details.ratingSpanTerm, 0.0f, 1e-6f );
    TS_ASSERT_DELTA( details.ratingPatternDeltaTerm, 0.0f, 1e-6f );

    //TS_ASSERT_DELTA( details.maxValue, Max( testDet.forcePatternDelta, testDet.forceSpan ) / (float)testDet.avgForce, 1e-6f );
    //TS_ASSERT_DELTA( details.sumValue, ( testDet.forcePatternDelta + testDet.forceSpan ) / (float)testDet.avgForce, 1e-6f );
    TS_ASSERT_DELTA( details.maxValue, 0, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, 0, 1e-6f );
  }



  void test_normals()
  {
    mmaking::SGameEstimDetails details;

    TestDetails testDet;
    prepare_basket_test( details, mmaking::EBasket::Normal, testDet );

    TS_ASSERT( details.valid );

    //TS_ASSERT_EQUALS( details.teamForce[0], testDet.team1force );
    //TS_ASSERT_EQUALS( details.teamForce[1], stdF );
    //TS_ASSERT_EQUALS( details.forceSpan, testDet.forceSpan );
    //TS_ASSERT_EQUALS( details.forcePatternDelta, testDet.forcePatternDelta );
    //TS_ASSERT_DELTA( details.forceSpanTerm, testDet.forceSpan / (float)testDet.avgForce, 1e-6f );
    //TS_ASSERT_DELTA( details.forcePatternDeltaTerm, testDet.forcePatternDelta / (float)testDet.avgForce, 1e-6f );
    //const float maxForceTerm = Max( testDet.forcePatternDelta, testDet.forceSpan ) / (float)testDet.avgForce;
    //const float sumForceTerm = ( testDet.forcePatternDelta + testDet.forceSpan ) / (float)testDet.avgForce;

    TS_ASSERT_EQUALS( details.teamRating[0], testDet.team1rating );
    TS_ASSERT_EQUALS( details.teamRating[1], stdR );
    TS_ASSERT_EQUALS( details.ratingSpan, testDet.ratingSpan );
    TS_ASSERT_EQUALS( details.ratingPatternDelta, testDet.ratingPatternDelta );
    TS_ASSERT_DELTA( details.ratingSpanTerm, testDet.ratingSpan / (float)testDet.avgRating, 1e-6f );
    TS_ASSERT_DELTA( details.ratingPatternDeltaTerm, testDet.ratingPatternDelta / (float)testDet.avgRating, 1e-6f );
    const float maxRatingTerm = Max( testDet.ratingPatternDelta, testDet.ratingSpan ) / (float)testDet.avgRating;
    const float sumRatingTerm = ( testDet.ratingPatternDelta + testDet.ratingSpan + testDet.ratingTeamAvgDelta ) / (float)testDet.avgRating;

    //TS_ASSERT_DELTA( details.maxValue, Max( maxForceTerm, maxRatingTerm ), 1e-6f );
    //TS_ASSERT_DELTA( details.sumValue, sumForceTerm + sumRatingTerm, 1e-6f );
    TS_ASSERT_DELTA( details.maxValue, maxRatingTerm, 1e-6f );
    TS_ASSERT_DELTA( details.sumValue, sumRatingTerm, 1e-6f );
  }
};
