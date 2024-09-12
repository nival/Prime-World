#ifndef PRODMMLOGICTESTING_H_INCLUDED
#define PRODMMLOGICTESTING_H_INCLUDED

#include "MmTesting.h"
#include "ProdMmLogicBase.h"


template<class TMmLogic>
class ProdMMLogicTesting : public MMakingTestBase
{
public:

protected:
  //
  // Data
  //

  StrongMT<mmaking::IMMakingLogic>    logic;

  timer::Time                         testTime;

  int                                 nextUserIdIndex;

  mmaking::SRequestCommonData         currentPartyHeader;
  vector<mmaking::SRequestMember>     currentParty;

  static const int                    stdClientRevision = 101;
  static const int                    stdSkill = 2000;
  static const int                    stdForce = 100;

  const char *                        stdGeolocation;


  //
  // Helper classes
  //

  struct STestReq
  {
    mmaking::TUserId        mmId;
    mmaking::TRequestUId    reqId;
    lobby::ETeam::Enum      team;

    STestReq() :
    mmId( 0 ), reqId( 0 ), team( lobby::ETeam::None ) {}

    STestReq( mmaking::TUserId _mmId, mmaking::TRequestUId _reqId, lobby::ETeam::Enum _team ) :
    mmId( _mmId ), reqId( _reqId ), team( _team )
    {
    }
  };


  class SRefGame
  {
  public:
    SRefGame() {}

    int size() const { return items.size(); }
    const STestReq & operator [] ( int i ) const { TS_ASSERT( i >= 0 && i < items.size() ); return items[i]; }
    STestReq & operator [] ( int i ) { TS_ASSERT( i >= 0 && i < items.size() ); return items[i]; }

    void add( const STestReq & _req ) { items.push_back( _req ); }
    void erase( int idx ) { TS_ASSERT( idx >= 0 && idx < items.size() ); items.erase( items.begin() + idx ); }

  private:
    vector<STestReq>      items;
  };


  static bool Equals( const SRefGame & vec, const mmaking::SGame & game )
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
      for ( int j = 0; !found && ( j < game.humans.size() ); ++j )
      {
        const mmaking::SGameParty & party = game.humans[j];
        if ( ( party.common.team == team ) && ( party.requestUId == reqId ) )
          for ( int k = 0; !found && ( k < party.members.size() ); ++k )
          {
            const mmaking::SRequestMember & memb = party.members[k];
            if ( memb.mmId == mmId )
              found = true;
          }
      }
      if ( !found )
        return false;
    }
    return true;
  };



  //
  //Methods
  //

  ProdMMLogicTesting() : testTime( 0 ), nextUserIdIndex( 0 ), stdGeolocation( "" ) {}


  void setUpProdMmTest( int heroesCount = 30, int botHeroesCount = 20, int enemyBotsHeroesCount = 10, bool maleHeroes = true, bool femaleHeroes = true )
  {
    setUpMmTest( heroesCount, botHeroesCount, enemyBotsHeroesCount, maleHeroes, femaleHeroes );

    NDb::MapMMakingSettings * hacked = WriteConfig();

    mmConfig->localeTable = "ru us";
    stdGeolocation = "ru";

    hacked->partySkillCompensation.push_back( 0.0f );
    hacked->partySkillCompensation.push_back( 50.0f );
    hacked->partySkillCompensation.push_back( 100.0f );
    hacked->partySkillCompensation.push_back( 150.0f );
    hacked->partySkillCompensation.push_back( 200.0f );


    nextUserIdIndex = 0;
    testTime = 0;
  }

  void tearDownProdMmTest()
  {
    nextUserIdIndex = 0;
    logic = 0;
    testTime = 0;

    tearDownMmTest();
  }
  
  inline const mmaking::TUserId * GetUserIds() {
    const mmaking::TUserId * ptr = 0;
    size_t count = 0;
    GetUserIdsImpl( ptr, count );
    return ptr;
  }

  inline size_t GetUserIdsCount() {
    const mmaking::TUserId * ptr = 0;
    size_t count = 0;
    GetUserIdsImpl( ptr, count );
    return count;
  }


  TMmLogic * GetSpecLogic() {
    TMmLogic * specLogic = dynamic_cast<TMmLogic *>( logic.Get() );
    TS_ASSERT( specLogic );
    return specLogic;
  }


  void PollMM( timer::Time _delta, bool runLastPassTwice = false )
  {
    TMmLogic * specLogic = GetSpecLogic();

    TS_ASSERT( logic );
    specLogic->SetTime( testTime );
    specLogic->TestPoll();

    testTime += _delta;

    specLogic->SetTime( testTime );
    specLogic->TestPoll();

    if ( runLastPassTwice )
      specLogic->TestPoll();
  }


  mmaking::TUserId NextUserId() {
    const int total = GetUserIdsCount();
    TS_ASSERT( nextUserIdIndex < total );
    return GetUserIds()[nextUserIdIndex++];
  }


  void OpenParty( lobby::ETeam::Enum _team, int _revision = stdClientRevision ) {
    TS_ASSERT( currentParty.empty() );
    currentParty.clear();
    currentPartyHeader = mmaking::SRequestCommonData( _team, _revision, true );
  }

  void AddToParty_Full( mmaking::TUserId _mmId, const char * _hero, lobby::ESex::Enum _sex, int _skill, const char * _geo ) {
    TS_ASSERT( currentParty.size() < 5 );
    currentParty.push_back( mmaking::SRequestMember( _mmId, _hero, _sex, mmaking::EBasket::Normal, _skill, _skill, _skill, stdForce, _geo, 0, 0, 1 ) );
  }

  void AddToParty( const char * _hero, lobby::ESex::Enum _sex ) {
    AddToParty_Full( NextUserId(), _hero, _sex, stdSkill, stdGeolocation );
  }

  void AddToParty_R( const char * _hero, lobby::ESex::Enum _sex, int _skill ) {
    TS_ASSERT( currentParty.size() < 5 );
    currentParty.push_back( mmaking::SRequestMember( NextUserId(), _hero, _sex, mmaking::EBasket::Normal, _skill, _skill, _skill, stdForce, stdGeolocation, 0, 0, 1 ) );
  }

  mmaking::TRequestUId CloseParty( SRefGame & _refGame, mmaking::TRequestUId _reqUId, timer::Time _waitTime ) {
    NI_VERIFY( !currentParty.empty(), "", return 0 );

    for ( int i = 0; i < currentParty.size(); ++i )
      _refGame.add( STestReq( currentParty[i].mmId, _reqUId, currentPartyHeader.team ) );

    logic->AddGroupRequest( _reqUId, currentPartyHeader, currentParty, _waitTime, logicCallback );
    currentPartyHeader = mmaking::SRequestCommonData();
    currentParty.clear();
    return _reqUId;
  }

  mmaking::TRequestUId CloseParty( SRefGame & _refGame ) {
    return CloseParty( _refGame, nextReqId++, 0 );
  }



  mmaking::TRequestUId AddSingle_Full( SRefGame & _refGame, mmaking::TRequestUId _reqUId, mmaking::TUserId _mmId, timer::Time _waitTime, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex, int _revision, int _skill, const char * _geo ) {
    OpenParty( _team, _revision );
    AddToParty_Full( _mmId, _hero, _sex, _skill, _geo );
    return CloseParty( _refGame, _reqUId, _waitTime );
  }

  mmaking::TRequestUId AddSingle( SRefGame & _refGame, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex ) {
    return AddSingle_Full( _refGame, nextReqId++, NextUserId(), 0, _team, _hero, _sex, stdClientRevision, stdSkill, stdGeolocation );
  }

  mmaking::TRequestUId AddSingle_Rev( SRefGame & _refGame, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex, int _clRev ) {
    return AddSingle_Full( _refGame, nextReqId++, NextUserId(), 0, _team, _hero, _sex, _clRev, stdSkill, stdGeolocation );
  }

  mmaking::TRequestUId AddSingle_R( SRefGame & _refGame, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex, int _skill ) {
    return AddSingle_Full( _refGame, nextReqId++, NextUserId(), 0, _team, _hero, _sex, stdClientRevision, _skill, stdGeolocation );
  }

  mmaking::TRequestUId AddSingle_Geo( SRefGame & _refGame, lobby::ETeam::Enum _team, const char * _hero, lobby::ESex::Enum _sex, const char * _geo ) {
    return AddSingle_Full( _refGame, nextReqId++, NextUserId(), 0, _team, _hero, _sex, stdClientRevision, stdSkill, _geo );
  }


  void AddStdParty( SRefGame & _refGame, lobby::ETeam::Enum _team, int _males, int _females ) {
    OpenParty( _team );
    for ( int i = 0; i < _males; ++i )
      AddToParty( MaleHero( i ), lobby::ESex::Male );
    for ( int i = 0; i < _females; ++i )
      AddToParty( FemaleHero( i ), lobby::ESex::Female );
    CloseParty( _refGame );
  }

  void AddStdSingles( SRefGame & _refGame, lobby::ETeam::Enum _team, int _males, int _females, int _startHero = 0 ) {
    for ( int i = 0; i < _males; ++i )
      AddSingle( _refGame, _team, MaleHero( _startHero + i ), lobby::ESex::Male );
    for ( int i = 0; i < _females; ++i )
      AddSingle( _refGame, _team, FemaleHero( _startHero + i ), lobby::ESex::Female );
  }


  void CheckGameNotReady() {
    mmaking::SGame game;
    bool gameNotReady = !logic->PopGame( game );
    TS_ASSERT( gameNotReady );
  }

  void CheckGame( const SRefGame & _refGame ) {
    mmaking::SGame game;
    bool gameReady = logic->PopGame( game );
    TS_ASSERT( gameReady );
    if ( gameReady )
      TS_ASSERT( Equals( _refGame, game ) );
  }



  void CodeGenerateUIds() {
    std::set<int> ids;
    while ( ids.size() < 40 )
      ids.insert( rand() % 1000 );

    string out;
    while ( !ids.empty() ) {
      int i = rand() % ids.size();
      std::set<int>::iterator it = ids.begin();
      std::advance( it, i );
      int id = *it;
      ids.erase( it );
      out += NStr::StrFmt( "%d, ", id );
    }
    OutputDebugString( out.c_str() );
  }

private:
  inline void GetUserIdsImpl( const mmaking::TUserId * &ids, size_t &count )
  {
    static mmaking::TUserId uids[] =
    {
      391, 281, 382, 724, 703, 716, 895, 292, 718, 153,
      500, 436, 961, 169, 705, 962, 912, 942, 464, 491,
      827, 902, 421, 995, 604, 667, 726, 869, 334, 41,
      467, 478, 145, 447, 358, 299, 538, 35, 771, 894,
      1391, 1281, 1382, 1724, 1703, 1716, 1895, 1292, 1718, 1153,
      1500, 1436, 1961, 1169, 1705, 1962, 1912, 1942, 1464, 1491,
      1827, 1902, 1421, 1995, 1604, 1667, 1726, 1869, 1334, 141,
      1467, 1478, 1145, 1447, 1358, 1299, 1538, 135, 1771, 1894
    };

    ids = uids;
    count = sizeof ( uids ) / sizeof( mmaking::TUserId );
  }
};

#endif //PRODMMLOGICTESTING_H_INCLUDED
