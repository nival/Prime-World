//!Component('LiveMMakingTool/MMakingLogParser')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "MMakingLogParser.h"

struct MMakingLogParserTest : public CxxTest::TestSuite
{
  struct SReq {
    mm_test::Timestamp ts;
    mmaking::TRequestUId reqId;
    mmaking::SRequestCommonData cmn;
    timer::Time wait;
    vector<mmaking::SRequestMember> members;

    //SReq() : {}

    SReq( const mm_test::Timestamp & _t, mmaking::TRequestUId _reqid, const mmaking::SRequestCommonData & _cmn, timer::Time _wait ) :
    ts( _t ), reqId( _reqid ), cmn( _cmn ), wait( _wait )
    {}

    SReq( const mm_test::Timestamp & _t, mmaking::TRequestUId _reqid, const mmaking::SRequestCommonData & _cmn, timer::Time _wait, const vector<mmaking::SRequestMember> & _members ) :
    ts( _t ), reqId( _reqid ), cmn( _cmn ), wait( _wait ),
    members( _members )
    {}

    SReq( const mm_test::Timestamp & _t, mmaking::TRequestUId _reqid, const mmaking::SRequestCommonData & _cmn, timer::Time _wait, const mmaking::SRequestMember & memb1 ) :
    ts( _t ), reqId( _reqid ), cmn( _cmn ), wait( _wait )
    {
      members.push_back( memb1 );
    }

    bool operator == ( const SReq & other ) const { return 
      ts == other.ts;
    }
  };

  class ParserCb : public mm_test::ILogParserCb, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ParserCb, mm_test::ILogParserCb, BaseObjectST );

  public:
    ParserCb() : games( 0 ) {}
    virtual void OnAddRequest( const mm_test::Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait) {
      requests.push_back( SReq( ts, reqId, commonData, wait, members ) );
    }
    virtual void OnRemoveRequest( const mm_test::Timestamp & ts, mmaking::TRequestUId reqId ) {
      removed.push_back( reqId );
    }
    virtual void OnGame( const mm_test::Timestamp & ts, const mmaking::SGame & game ) {
      ++games; //TODO
    }

    virtual void OnProgress( int progress ) {}
    virtual void Finish(){}
    virtual void Output(){}

    vector<SReq> requests;
    vector<mmaking::TRequestUId> removed;
    int games;
  };


  void try_test( mm_test::LogParser & p, const char * text )
  {
    try {
      p.AddText( text, "test.txt" );
    }
    catch ( const mm_test::LogParser::Excep & ex ) {
      ErrorTrace( "%s: %s (%s)", ex.File(), ex.Reason(), ex.TextSample() );
      TS_FAIL( ex.Reason() );
    }
  }


  void test_smoke()
  {
    Strong<ParserCb> cb = new ParserCb;
    mm_test::LogParser p( cb, mm_test::ELogVersion::v902 );
    try_test( p,
      "24/01 12:29:09.64 Matchmaking thread started...\r\n"
      "24/01 12:29:23.09 Request queued: id 1 (wait 505.0), Team Team1, rev 101, (mmId 101500, sex 'Male', hero 'healer' (1), rating 1445, loc 'ru')\r\n"
      "24/01 12:40:03.45 Pushing game: Type PvP, map 'Maps/Multiplayer/PFmap/pf.ADMP.xdb'\r\n"
      "Team1: Rating 7984 (-0)               | Team2: Rating 7841 (-100)            \r\n"
      "101504 Male   firefox     1573 ru 0.9 | 101505 Male   prince     1789 ru 0.9 \r\n"
      "101506 Male   ratcatcher  1754 ru 0.9 | 101507 Male   rockman    1424 ru 0.9 \r\n"
      "101508 Male   faceless    1555 ru 0.9 | 101509 Male   faceless   1337 ru 0.9 \r\n"
      "101510 Male   witchdoctor 1738 ru 0.9 | 101511 Male   firefox    1675 ru 0.9 \r\n"
      "101520 Female prince      1364 ru 0.1 | 101517 Female ratcatcher 1616 ru 0.4 \r\n"
      "\r\n"
      "12/01 00:40:00.94 Request removed: 18\r\n"
      "24/01 12:59:30.00 Request queued: id 3 (wait 505.0), Team Team1, rev 101, (mmId 101500, sex 'Male', hero 'rockman' (1), rating 3333, loc 'ru')\r\n"
      );

    TS_ASSERT_EQUALS( cb->games, 1 );

    TS_ASSERT_EQUALS( cb->requests.size(), 2 );
    SReq req0(
      mm_test::Timestamp( mm_test::Date( 2012, 1, 24 ), mm_test::Time( 12, 29, 23, 90 ) ), 1, mmaking::SRequestCommonData( lobby::ETeam::Team1, 101, false ), 505.0,
      mmaking::SRequestMember( 101500, "healer", lobby::ESex::Male, 1445, 0, "ru" ) );
    TS_ASSERT_EQUALS( cb->requests[0], req0 );

    SReq req1(
      mm_test::Timestamp( mm_test::Date( 2012, 1, 24 ), mm_test::Time( 12, 59, 30, 00 ) ), 3, mmaking::SRequestCommonData( lobby::ETeam::Team1, 101, false ), 505.0,
      mmaking::SRequestMember( 101500, "rockman", lobby::ESex::Male, 3333, 0, "ru" ) );
    TS_ASSERT_EQUALS( cb->requests[1], req1 );

    TS_ASSERT_EQUALS( cb->removed.size(), 1 );
    TS_ASSERT_EQUALS( cb->removed[0], 18 );
  }
};
