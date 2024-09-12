//!Component('Server/Roll/EloRating')

#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include <System/TestSuite.h>

#include <Game/PF/Server/LobbyPvx/CommonTypes.h>

#include "EloRating.h"

struct Test_EloRating : public CxxTest::TestSuite
{
  void test_Simple()
  {
    EloRating::Calculator rating;
    rating.AddPlayer(lobby::ETeam::Team1, 0, 100, 0);
    rating.AddPlayer(lobby::ETeam::Team2, 1, 100, 0);
    {
      float ratingChange = 0;
      TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
      TS_ASSERT_EQUALS(0, ratingChange);

      TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
      TS_ASSERT_EQUALS(0, ratingChange);
    }

    rating.Calculate(lobby::ETeam::None, 0, 0);

    {
      float ratingChange = 0;
      TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
      TS_ASSERT_EQUALS(-16, ratingChange);

      TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
      TS_ASSERT_EQUALS(-16, ratingChange);
    }
  }

  void test_TeamAWin()
  {
    EloRating::Calculator rating;
    {
      rating.AddPlayer(lobby::ETeam::Team1, 0, 100, 0);
      rating.AddPlayer(lobby::ETeam::Team2, 1, 100, 0);
      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);
      }

      rating.Calculate(lobby::ETeam::Team1, 0,0);

      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(16, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(-16, ratingChange);
      }
    }
    rating.Clear();
    {
      rating.AddPlayer(lobby::ETeam::Team1, 0, 116, 0);
      rating.AddPlayer(lobby::ETeam::Team2, 1, 84, 0);
      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);
      }

      rating.Calculate(lobby::ETeam::Team1, 0, 0);

      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT( ( 14.0f < ratingChange ) && ( ratingChange < 15.0f ) );

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT( ( -15.0f < ratingChange ) && ( ratingChange < -14.0f ) );
      }
    }

    rating.Clear();
    {
      rating.AddPlayer(lobby::ETeam::Team1, 0, 133, 0);
      rating.AddPlayer(lobby::ETeam::Team2, 1, 70, 0);
      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);
      }

      rating.Calculate(lobby::ETeam::Team1, 0, 0);

      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT( ( 13 < ratingChange ) && ( ratingChange < 14 ));

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT( ( -14 < ratingChange ) && ( ratingChange < -13 ) );
      }
    }
  }

  void test_TeamAWinMultiple()
  {
    EloRating::Calculator rating;
    {
      rating.AddPlayer(lobby::ETeam::Team1, 0, 1500, 0);
      rating.AddPlayer(lobby::ETeam::Team1, 1, 1500, 0);
      rating.AddPlayer(lobby::ETeam::Team2, 2, 1500, 0);
      rating.AddPlayer(lobby::ETeam::Team2, 3, 1500, 0);
      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(2, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(3, ratingChange));
        TS_ASSERT_EQUALS(0, ratingChange);
      }

      rating.Calculate(lobby::ETeam::Team2, 0, 0);

      {
        float ratingChange = 0;
        TS_ASSERT_EQUALS(true, rating.GetChange(0, ratingChange));
        TS_ASSERT_EQUALS(-16, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(1, ratingChange));
        TS_ASSERT_EQUALS(-16, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(2, ratingChange));
        TS_ASSERT_EQUALS(16, ratingChange);

        TS_ASSERT_EQUALS(true, rating.GetChange(3, ratingChange));
        TS_ASSERT_EQUALS(16, ratingChange);
      }
    }
  }

  void test_Kamz_Roumor()
  {
    EloRating::Calculator r;

    r.AddPlayer(lobby::ETeam::Team1, 0, 1400, 0);
    r.AddPlayer(lobby::ETeam::Team1, 1, 2100, 0);
    r.AddPlayer(lobby::ETeam::Team1, 2, 2100, 0);
    r.AddPlayer(lobby::ETeam::Team1, 3, 2100, 0);
    r.AddPlayer(lobby::ETeam::Team1, 4, 2100, 0);

    r.AddPlayer(lobby::ETeam::Team2, 5, 1950, 0);
    r.AddPlayer(lobby::ETeam::Team2, 6, 1950, 0);
    r.AddPlayer(lobby::ETeam::Team2, 7, 1950, 0);
    r.AddPlayer(lobby::ETeam::Team2, 8, 1950, 0);
    r.AddPlayer(lobby::ETeam::Team2, 9, 1950, 0);

    r.Calculate( lobby::ETeam::Team1, 0, 0 );

    float kapral = 0, palkan1 = 0, palkan2 = 0;
    r.GetChange( 0, kapral );
    r.GetChange( 1, palkan1 );
    r.GetChange( 2, palkan2 );

    float podpol = 0;
    r.GetChange( 7, podpol );
  }

  void test_PartyRatings()
  {
    EloRating::Calculator rcalc;

    rcalc.AddPlayer(lobby::ETeam::Team1, 0, 1400, 2);
    rcalc.AddPlayer(lobby::ETeam::Team1, 1, 2000, 2);
    rcalc.AddPlayer(lobby::ETeam::Team1, 2, 1700, 1);
    rcalc.AddPlayer(lobby::ETeam::Team1, 3, 1600, 1);
    rcalc.AddPlayer(lobby::ETeam::Team1, 4, 1900, 1);

    rcalc.AddPlayer(lobby::ETeam::Team2, 5, 1800, 0);
    rcalc.AddPlayer(lobby::ETeam::Team2, 6, 1500, 0);
    rcalc.AddPlayer(lobby::ETeam::Team2, 7, 1800, 3);
    rcalc.AddPlayer(lobby::ETeam::Team2, 8, 2000, 3);
    rcalc.AddPlayer(lobby::ETeam::Team2, 9, 1500, 0);

    rcalc.Calculate( lobby::ETeam::Team1, 0, 0);

    float ratingChange = 0;

    TS_ASSERT( rcalc.GetChange( 0, ratingChange ));
    TS_ASSERT_DELTA( 26.033f, ratingChange, 0.005f );

    TS_ASSERT( rcalc.GetChange( 2, ratingChange ));
    TS_ASSERT_DELTA( 16.701f, ratingChange, 0.005f );

    TS_ASSERT( rcalc.GetChange( 5, ratingChange ) );
    TS_ASSERT_DELTA( -18.61f, ratingChange, 0.05f );

    TS_ASSERT( rcalc.GetChange( 7, ratingChange ) );
    TS_ASSERT_DELTA( -18.61f, ratingChange, 0.05f );
  }



  struct PartyRatingBonusCallback : public EloRating::IPartyRatingBonusCallback
  {
    virtual int PartyRatingBonus( float partyRating, int partySize )
    {
      NI_VERIFY( fabs( partyRating - 1700 ) < 1e-3, "", return 0 );
      NI_VERIFY( partySize == 2, "", return 0 );
      if ( partySize >= 2 )
        return 300;
      return 0;
    }
  };


  void test_PartyRatings_Cb()
  {
    EloRating::Calculator rcalc;

    rcalc.AddPlayer(lobby::ETeam::Team1, 0, 1400, 0); //1400
    rcalc.AddPlayer(lobby::ETeam::Team1, 1, 1500, 1); //1500
    rcalc.AddPlayer(lobby::ETeam::Team1, 2, 1700, 1); //1700

    rcalc.AddPlayer(lobby::ETeam::Team2, 23, 1800, 0);
    rcalc.AddPlayer(lobby::ETeam::Team2, 24, 1500, 0);
    rcalc.AddPlayer(lobby::ETeam::Team2, 25, 1800, 0);

    PartyRatingBonusCallback callback;
    rcalc.Calculate( lobby::ETeam::Team1, &callback, 0 );

    float ratingChange = 0;

    TS_ASSERT( rcalc.GetChange( 0, ratingChange ));
    TS_ASSERT_DELTA( 26.22f, ratingChange, 0.01f );

    TS_ASSERT( rcalc.GetChange( 1, ratingChange ));
    TS_ASSERT_DELTA( 23.44f, ratingChange, 0.01f );

    TS_ASSERT( rcalc.GetChange( 2, ratingChange ) );
    TS_ASSERT_DELTA( 16.21f, ratingChange, 0.01f );

    TS_ASSERT( rcalc.GetChange( 23, ratingChange ) );
    TS_ASSERT_DELTA( -17.59f, ratingChange, 0.01f );
  }
};
