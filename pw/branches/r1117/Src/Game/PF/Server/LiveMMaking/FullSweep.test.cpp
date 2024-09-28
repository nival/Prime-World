//!Component("Server/LiveMMaking/FullSweep")

#include "stdafx.h"
#include "FullSweep.h"
#include <set>
#include "System/SafeTextFormatStl.h"


struct Test_FullSweep : public CxxTest::TestSuite
{
  struct Team {
    std::set<char> C;
    Team() {}
    Team & operator + ( char c ) { C.insert( c ); return *this; }
  };

  struct TestDraft;

  struct Pattern
  {
    std::set<char> team0, team1;

    Pattern( const Team & t1, const Team & t2 ) : team0( t1.C ), team1( t2.C ) {}
    Pattern( const TestDraft & draft ) {
      for ( int i = 0; i < draft.lineup[0].size(); ++i )
        team0.insert( draft.lineup[0][i].name );
      for ( int i = 0; i < draft.lineup[1].size(); ++i )
        team1.insert( draft.lineup[1][i].name );
    }
    bool operator == ( const Pattern & other ) const {
      return ( team0 == other.team0 ) && ( team1 == other.team1 );
    }
    bool operator < ( const Pattern & other ) const {
      if ( team0 < other.team0 ) return true;
      if ( team0 > other.team0 ) return false;
      return team1 < other.team1;
    }
    void Format( text::IBuffer * buffer, const text::SFormatSpecs & specs ) const {
      text::PrintfFormatterBufferPtr fmtr( buffer );
      fmtr.Trace( "%i x %i", team0, team1 );
    }
  };


  struct PatternSet : public std::set<Pattern>
  {
    PatternSet & operator + ( const Pattern & P ) { insert( P ); return *this; }

    void Format( text::IBuffer * buffer, const text::SFormatSpecs & specs ) const {
      text::PrintfFormatterBufferPtr fmtr( buffer );
      fmtr.Trace( "%i", (std::set<Pattern>)*this );
    }
  };


  struct TestSlot {
    char  name;
    int   size;
    bool  tooLong;
    explicit TestSlot( char nm ) : name( nm ), size( 1 ), tooLong(false) {}
    TestSlot( char nm, int sz ) : name( nm ), size( sz ), tooLong(false) {}

    int GetSlotSize() const { 
      return size;
    }
  };


  struct TestDraft {
    TestDraft( PatternSet & rf ) : ref( rf ), tooLong(false) {}

    vector<TestSlot> lineup[2];
    PatternSet & ref;
    bool tooLong;

    void PushBack( int teamIndex, const TestSlot & slot ) {
      lineup[teamIndex].push_back(slot);
    }

    void PopBack( int teamIndex, const TestSlot & slot ) {
      lineup[teamIndex].pop_back();
    }

    void CheckOut() {
      std::pair<std::set<Pattern>::iterator, bool> result =
        ref.insert( *this );
      TS_ASSERT( result.second );
    }
  };


  class TestFullSweep : public mmaking::TFullSweepAlgorithm<TestSlot, TestDraft>
  {
  public:
    TestFullSweep() {}
  };


  virtual void setUp()
  {
  }


  virtual void tearDown()
  {
  }


  static const lobby::ETeam::Enum t1 = lobby::ETeam::Team1, t2 = lobby::ETeam::Team2;
  static const char A='A', B='B', C='C', D='D', E='E';
  static const char F='F', G='G', H='H', I='I', J='J';


  unsigned run( int teamSize, TestFullSweep::Sample & sample, PatternSet & result ) {
    TestFullSweep algo;
    algo.PreprocessSample( sample );

    TestDraft draft( result );
    return algo.FullSweepHetero( sample, draft, teamSize );
  }


  void check( int teamSize, TestFullSweep::Sample & sample, const PatternSet & patterns ) {
    PatternSet tmp;
    run( teamSize, sample, tmp );

    DebugTrace( "Got drafts:\n %i", tmp );
    DebugTrace( "Got patterns:\n %i", patterns );

    TS_ASSERT_EQUALS( patterns, tmp );
  }


  unsigned run_homo( int teamSize, TestFullSweep::Sample & sample, PatternSet & result ) {
    TestFullSweep algo;
    algo.PreprocessSample( sample );

    TestDraft draft( result );
    return algo.FullSweepHomo( sample, draft, teamSize );
  }


  void check_homo( int teamSize, TestFullSweep::Sample & sample, const PatternSet & patterns ) {
    PatternSet tmp;
    run_homo( teamSize, sample, tmp );

    PatternSet homoPatterns = homogenize( patterns );
    PatternSet homoTmp = homogenize( tmp );

    DebugTrace( "Got drafts:\n %i", homoTmp );
    DebugTrace( "Got patterns:\n %i", homoPatterns );

    TS_ASSERT_EQUALS( homoPatterns, homoTmp );
  }


  void homogenize( Pattern & pattern ) {
    char c0 = pattern.team0.empty() ? 0 : *pattern.team0.begin();
    char c1 = pattern.team1.empty() ? 0 : *pattern.team1.begin();
    if ( c0 > c1 )
      std::swap( pattern.team0, pattern.team1 );
  }


  PatternSet homogenize( const PatternSet & pset ) {
    PatternSet result;
    for ( PatternSet::const_iterator it = pset.begin(); it != pset.end(); ++it ) {
      Pattern p = *it;
      homogenize( p );
      result.insert( p );
    }
    return result;
  }


  unsigned run_single_side( int teamSize, TestFullSweep::Sample & sample, PatternSet & result ) {
    TestFullSweep algo;
    algo.PreprocessSample( sample );

    TestDraft draft( result );
    return algo.FullSweepSingleSide( sample, draft, teamSize );
  }


  void check_single_side( int teamSize, TestFullSweep::Sample & sample, const PatternSet & patterns ) {
    PatternSet tmp;
    run_single_side( teamSize, sample, tmp );

    DebugTrace( "Got drafts:\n %i", tmp );
    DebugTrace( "Got patterns:\n %i", patterns );

    TS_ASSERT_EQUALS( patterns, tmp );
  }


  void test_1x1_empty()
  {
    TestFullSweep::Sample sample;
    check( 1, sample, PatternSet() );
  }


  void test_1x1_a()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t2, TestSlot( B ) );

    check( 1, sample, PatternSet()
        + Pattern( Team() + A, Team() + B )
      );
  }


  void test_1x1_b()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t2, TestSlot( C ) );
    sample.Push( t2, TestSlot( D ) );

    check( 1, sample, PatternSet()
        + Pattern( Team() + A, Team() + C )
        + Pattern( Team() + B, Team() + D )
        + Pattern( Team() + A, Team() + D )
        + Pattern( Team() + B, Team() + C )
      );
  }


  void test_2x2_a()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 2 ) );
    sample.Push( t2, TestSlot( B, 2 ) );

    check( 2, sample, PatternSet()
        + Pattern( Team() + A, Team() + B )
      );
  }


  void test_2x2_b()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t2, TestSlot( D ) );
    sample.Push( t2, TestSlot( E ) );

    check( 2, sample, PatternSet()
        + Pattern( Team() + A + C, Team() + D + E )
      );
  }


  void test_2x2_c()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 2 ) );
    sample.Push( t2, TestSlot( B ) );
    sample.Push( t2, TestSlot( C ) );

    check( 2, sample, PatternSet()
        + Pattern( Team() + A, Team() + B + C )
      );
  }


  void test_2x2_d()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t2, TestSlot( D ) );
    sample.Push( t2, TestSlot( E ) );
    sample.Push( t2, TestSlot( F ) );

    check( 2, sample, PatternSet()
        + Pattern( Team() + A + B, Team() + D + E )
        + Pattern( Team() + A + B, Team() + E + F )
        + Pattern( Team() + A + B, Team() + D + F )

        + Pattern( Team() + B + C, Team() + D + E )
        + Pattern( Team() + B + C, Team() + E + F )
        + Pattern( Team() + B + C, Team() + D + F )

        + Pattern( Team() + A + C, Team() + D + E )
        + Pattern( Team() + A + C, Team() + E + F )
        + Pattern( Team() + A + C, Team() + D + F )
      );
  }


  void test_3x3_a_overflow()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B, 2 ) );
    sample.Push( t1, TestSlot( C, 2 ) );
    sample.Push( t2, TestSlot( D, 2 ) );
    sample.Push( t2, TestSlot( E ) );
    sample.Push( t2, TestSlot( F, 2 ) );

    check( 3, sample, PatternSet()
        + Pattern( Team() + A + B, Team() + E + D )
        + Pattern( Team() + A + C, Team() + E + F )
        + Pattern( Team() + A + B, Team() + E + F )
        + Pattern( Team() + A + C, Team() + E + D )
      );
  }


  void test_3x3_b_overflow()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 3 ) );
    sample.Push( t2, TestSlot( C, 1 ) );
    sample.Push( t2, TestSlot( D, 2 ) );
    sample.Push( t2, TestSlot( E, 3 ) );

    check( 3, sample, PatternSet()
        + Pattern( Team() + A, Team() + C + D )
        + Pattern( Team() + A, Team() + E )
      );
  }


  void test_5x5_a()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 5 ) );
    sample.Push( t2, TestSlot( B, 5 ) );

    check( 5, sample, PatternSet()
        + Pattern( Team() + A, Team() + B )
      );
  }


  void test_5x5_b_exclude()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 4 ) );
    sample.Push( t1, TestSlot( B, 3 ) );
    sample.Push( t1, TestSlot( C, 2 ) );
    sample.Push( t2, TestSlot( D, 4 ) );
    sample.Push( t2, TestSlot( E, 3 ) );
    sample.Push( t2, TestSlot( F, 2 ) );

    check( 5, sample, PatternSet()
        + Pattern( Team() + B + C, Team() + E + F )
      );
  }


  void test_5x5_c_empty()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 4 ) );
    sample.Push( t1, TestSlot( B, 3 ) );
    sample.Push( t2, TestSlot( C, 3 ) );
    sample.Push( t2, TestSlot( D, 4 ) );

    check( 5, sample, PatternSet() );
  }


  void test_5x5_d_excess()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 4 ) );
    sample.Push( t1, TestSlot( B, 3 ) );
    sample.Push( t1, TestSlot( C, 1 ) );
    sample.Push( t2, TestSlot( D, 1 ) );
    sample.Push( t2, TestSlot( E, 3 ) );
    sample.Push( t2, TestSlot( F, 4 ) );

    check( 5, sample, PatternSet()
        + Pattern( Team() + A + C, Team() + D + F )
      );
  }


  void test_5x5_d_excess2()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 4 ) );
    sample.Push( t1, TestSlot( B, 3 ) );
    sample.Push( t1, TestSlot( C, 1 ) );

    sample.Push( t2, TestSlot( D, 1 ) );
    sample.Push( t2, TestSlot( E, 1 ) );
    sample.Push( t2, TestSlot( F, 3 ) );
    sample.Push( t2, TestSlot( G, 4 ) );

    check( 5, sample, PatternSet()
        + Pattern( Team() + A + C, Team() + D + G )
        + Pattern( Team() + A + C, Team() + E + G )
        + Pattern( Team() + A + C, Team() + D + E + F )
      );
  }


  void test_homo_empty()
  {
    TestFullSweep::Sample sample;
    check_homo( 2, sample, PatternSet() );
  }


  void test_homo_2x2_a()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t1, TestSlot( D ) );

    check_homo( 2, sample, PatternSet()
        + Pattern( Team() + A + B, Team() + C + D )
        + Pattern( Team() + A + C, Team() + B + D )
        + Pattern( Team() + A + D, Team() + B + C )
      );
  }


  void test_homo_2x2_b()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 2 ) );
    sample.Push( t1, TestSlot( B, 2 ) );

    check_homo( 2, sample, PatternSet()
        + Pattern( Team() + A, Team() + B )
      );
  }


  void test_homo_5x5_stairway()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 1 ) );
    sample.Push( t1, TestSlot( B, 2 ) );
    sample.Push( t1, TestSlot( C, 3 ) );
    sample.Push( t1, TestSlot( D, 4 ) );
    sample.Push( t1, TestSlot( E, 5 ) );

    check_homo( 5, sample, PatternSet()
        + Pattern( Team() + A + D, Team() + E )
        + Pattern( Team() + B + C, Team() + E )
        + Pattern( Team() + B + C, Team() + D + A )
      );
  }


  void test_homo_mixed()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B, 3 ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t1, TestSlot( D ) );
    sample.Push( t1, TestSlot( E, 3 ) );
    sample.Push( t1, TestSlot( F, 2 ) );

    check_homo( 5, sample, PatternSet()
        + Pattern( Team() + A + B + C, Team() + E + F )
        + Pattern( Team() + A + B + D, Team() + E + F )
        + Pattern( Team() + B + C + D, Team() + E + F )
        + Pattern( Team() + A + C + E, Team() + B + F )
        + Pattern( Team() + C + D + E, Team() + B + F )
        + Pattern( Team() + A + D + E, Team() + B + F )
      );
  }


  static unsigned fact( unsigned n ) { return ( n < 2 ) ? 1 : ( n * fact( n - 1 ) ); }


  void test_homo_iterations()
  {
    TestFullSweep::Sample sample;
    for ( char i = 0; i < 10; ++i )
      sample.Push( t1, TestSlot( A + i ) );

    unsigned i = fact( 10 ) / ( 2 * sqr( fact( 5 ) ) );

    PatternSet tmp;
    unsigned iterations = run_homo( 5, sample, tmp );

    TS_ASSERT_EQUALS( iterations, i );
  }


  void test_iterations()
  {
    TestFullSweep::Sample sample;
    for ( char i = 0; i < 9; ++i )
      sample.Push( t1, TestSlot( 'A' + i ) );

    for ( char i = 0; i < 7; ++i )
      sample.Push( t2, TestSlot( 'O' + i ) );


    unsigned i1 = fact( 9 ) / ( fact( 9 - 5 ) * fact( 5 ) );
    unsigned i2 = fact( 7 ) / ( fact( 7 - 5 ) * fact( 5 ) );

    PatternSet tmp;
    unsigned iterations = run( 5, sample, tmp );

    TS_ASSERT_EQUALS( iterations, i1 * i2 );
  }


  void test_single_team_smoke()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t1, TestSlot( D ) );

    check_single_side( 2, sample, PatternSet()
        + Pattern( Team() + A + B, Team() )
        + Pattern( Team() + A + C, Team() )
        + Pattern( Team() + A + D, Team() )
        + Pattern( Team() + B + C, Team() )
        + Pattern( Team() + B + D, Team() )
        + Pattern( Team() + C + D, Team() )
      );
  }


  void test_single_team_party_smoke()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 5 ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t1, TestSlot( D ) );
    sample.Push( t1, TestSlot( E ) );
    sample.Push( t1, TestSlot( F ) );

    check_single_side( 5, sample, PatternSet()
        + Pattern( Team() + A, Team() )
        + Pattern( Team() + B + C + D + E + F, Team() )
      );
  }


  void test_single_team_party1()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 2 ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C ) );
    sample.Push( t1, TestSlot( D, 2 ) );

    check_single_side( 3, sample, PatternSet()
        + Pattern( Team() + A + B, Team() )
        + Pattern( Team() + A + C, Team() )
        + Pattern( Team() + B + D, Team() )
        + Pattern( Team() + C + D, Team() )
      );
  }


  void test_single_team_party2()
  {
    TestFullSweep::Sample sample;
    sample.Push( t1, TestSlot( A, 2 ) );
    sample.Push( t1, TestSlot( B ) );
    sample.Push( t1, TestSlot( C, 3 ) );
    sample.Push( t1, TestSlot( D ) );

    check_single_side( 3, sample, PatternSet()
        + Pattern( Team() + A + B, Team() )
        + Pattern( Team() + A + D, Team() )
        + Pattern( Team() + C, Team() )
      );
  }
};
