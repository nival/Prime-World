//!Component("Server/LobbySocial/SocialLobbyGuildFightCalc")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "SocialLobbyGuildFightCalc.h"


struct Test_SocialLobbyGuildFightCalc : public CxxTest::TestSuite
{

  void fill_mm_game( mmaking::SGame & g, bool createParty )
  {
    const mmaking::EBasket::Enum basket = mmaking::EBasket::Normal;
    const lobby::ESex::Enum male = lobby::ESex::Male;
    const mmaking::SGeoInfo geo(" ru" );

    g.humans.resize( 3 );

    g.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( lobby::ETeam::Team1, 0, true ), 0, 1 ) );
    g.humans.back().members.push_back( mmaking::SRequestMember( 101, "H", male, basket, 0, 0, 0, 0.0, geo, 0, 0, 0 ) );

    g.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( lobby::ETeam::Team1, 0, true ), 0, 2 ) );
    g.humans.back().members.push_back( mmaking::SRequestMember( 102, "H", male, basket, 0, 0, 0, 0.0, geo, 0, 0, 0 ) );

    g.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( lobby::ETeam::Team2, 0, true ), 0, 3 ) );
    g.humans.back().members.push_back( mmaking::SRequestMember( 103, "H", male, basket, 0, 0, 0, 0.0, geo, 0, 0, 0 ) );

    if ( !createParty )
      g.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( lobby::ETeam::Team2, 0, true ), 0, 4 ) );

    g.humans.back().members.push_back( mmaking::SRequestMember( 104, "H", male, basket, 0, 0, 0, 0.0, geo, 0, 0, 0 ) );
  }


  void test_smoke()
  {
    mmaking::SGame game;
    fill_mm_game( game, false );

    socialLobby::GuildFightCalculator calc( game );

    calc.Add( 101, 4 );
    calc.Add( 102, 4 );
    calc.Add( 103, 5 );
    calc.Add( 104, 5 );

    TS_ASSERT( calc.IsGuildFight( 2 ) );
  }


  void test_smoke_party()
  {
    mmaking::SGame game;
    fill_mm_game( game, true );

    socialLobby::GuildFightCalculator calc( game );

    calc.Add( 101, 4 );
    calc.Add( 102, 4 );
    calc.Add( 103, 5 );
    calc.Add( 104, 5 );

    TS_ASSERT( calc.IsGuildFight( 2 ) );
  }


  void test_negative1()
  {
    mmaking::SGame game;
    fill_mm_game( game, true );

    socialLobby::GuildFightCalculator calc( game );

    calc.Add( 102, 3 );
    calc.Add( 103, 8 );

    TS_ASSERT( !calc.IsGuildFight( 2 ) );
  }


  void test_negative2()
  {
    mmaking::SGame game;
    fill_mm_game( game, false );

    socialLobby::GuildFightCalculator calc( game );

    calc.Add( 102, 3 );
    calc.Add( 103, 10 );
    calc.Add( 104, 10 );

    TS_ASSERT( !calc.IsGuildFight( 2 ) );
  }

}; //struct Test_SocialLobbyGuildFightCalc
