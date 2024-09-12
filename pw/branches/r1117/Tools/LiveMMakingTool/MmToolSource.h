#pragma once

#include "System/RandomGenerator.h"
#include "Server/LiveMMaking/RatingSortMmLogic.h"
#include "SimpleParser.h"

namespace simple_parser
{

bool ParseSingleValue( lobby::ETeam::Enum & _val, const char * _text )
{
  if ( !_stricmp( _text, "a" ) )
    _val = lobby::ETeam::Team1;
  else if ( !_stricmp( _text, "b" ) )
    _val = lobby::ETeam::Team2;
  else
    return false;

  return true;
}


bool ParseSingleValue( lobby::ESex::Enum & _val, const char * _text )
{
  if ( !_stricmp( _text, "m" ) )
    _val = lobby::ESex::Male;
  else if ( !_stricmp( _text, "f" ) )
    _val = lobby::ESex::Female;
  else
    return false;

  return true;
}


bool ParseSingleValue( mmaking::EBasket::Enum & _val, const char * _text )
{
  if ( !_stricmp( _text, "normal" ) )
    _val = mmaking::EBasket::Normal;
  else if ( !_stricmp( _text, "noob" ) )
    _val = mmaking::EBasket::Newbie;
  else if ( !_stricmp( _text, "leaver" ) )
    _val = mmaking::EBasket::Leaver;

  else
    return false;

  return true;
}

} //namespace simple_parser


namespace mm_test
{


struct StoredRequest : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( StoredRequest, BaseObjectST );

  StoredRequest() : recycleMoment( 0 ) {}

  mmaking::SRequestCommonData       common;
  vector<mmaking::SRequestMember>   members;
  timer::Time                       recycleMoment;
};

typedef map<mmaking::TRequestUId, Strong<StoredRequest>>  TRequestMap;
typedef list<Strong<StoredRequest>>  TRequestList;



class MmCallback : public mmaking::IMMakingLogicCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MmCallback, IMMakingLogicCallback, BaseObjectMT );

public:
  MmCallback() {}
  //IMMakingLogicCallback
  virtual void MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
  virtual void MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
};



struct Context
{
  const static int                  BASE_UID = 1000;

  StrongMT<mmaking::IMMakingLogic>    logic;
  StrongMT<MmCallback>                callback;
  NRandom::RandomGenerator            random;
  mmaking::TRequestUId                nextReqUId;
  mmaking::TUserId                    nextUserId;
  TRequestMap                         requestsInMmaking;

  Context() : nextReqUId( 1 ), nextUserId( BASE_UID ) {}
};



class Source : public BaseObjectST, public simple_parser::Parser
{
  NI_DECLARE_REFCOUNT_CLASS_1( Source, BaseObjectST );

public:
  Source( timer::Time _startTime ) :
  startTime( _startTime ),
  count( 0 ),
  nextSpawn( 0 ), requestsSpawned( 0 ),
  readyToManoeuvre( true )
  {
  }


  timer::Time StartTime() const { return startTime; }

  bool Parse( simple_parser::Context & _ctx )
  {
    while ( true )
    {
      string key;
      if ( !ForceWord( key, _ctx ) )
        return false;

      if ( key == "member" )
      {
        SMember memb;
        if ( !ParseMember( memb, _ctx ) )
          return false;
        members.push_back( memb );
      }
      else if ( key == "uids" )
      {
        if ( !userIds.Parse( _ctx ) )
          return false;
        if ( userIds.from >= Context::BASE_UID || userIds.to >= Context::BASE_UID )
          return HandleError( _ctx, "Wrong uid" );
      }
      else if ( key == "count" )
      {
        if ( !ForceValue( count, _ctx ) )
          return false;
      }
      else if ( key == "faction" )
      {
        if ( !teams.Parse( _ctx ) )
          return false;
      }
      else if ( key == "duration" )
      {
        if ( !duration.Parse( _ctx ) )
          return false;
      }
      else if ( key == "no_manoeuvres" )
      {
        readyToManoeuvre = false;
      }
      else if ( key == "rev" )
      {
        if ( !clientRev.Parse( _ctx ) )
          return false;
      }
      else
        return HandleErrorf( _ctx, "Unknown keyword '%s'", key.c_str() );

      if ( PeekSymbol( _ctx, ";" ) )
        break;

      if ( !ForceSymbol( _ctx, "," ) )
        return false;
    }

    if ( members.empty() )
      return HandleError( _ctx, "No request members" );

    if ( teams.empty() ) {
      teams.AddValue( lobby::ETeam::Team1 );
      teams.AddValue( lobby::ETeam::Team2 );
    }

    if ( count < 1 )
      count = 1;

    return true;
  }


  bool Play( timer::Time _now, Context & _ctx )
  {
    requestsSpawned = 0;
    nextSpawn = _now;

    return SpawnMultiple( _now, _ctx );
  }


  bool Poll( timer::Time _now, Context & _ctx )
  {
    return SpawnMultiple( _now, _ctx );
  }


private:
  struct SMember
  {
    struct SPing
    {
      simple_parser::ValuesVector<string>         clusters;
      simple_parser::ValuesRange<int>             ping;
      SPing() {}
      SPing( const char * _cluster, int _pingMin, int _pingMax ) {
        clusters.push_back( _cluster );
        ping.AddValue( _pingMin );
        ping.AddValue( _pingMax );
      }
    };

    simple_parser::ValuesVector<lobby::ESex::Enum> sex;
    simple_parser::ValuesVector<string>           heroes;
    simple_parser::ValuesVector<mmaking::EBasket::Enum> basket;
    simple_parser::ValuesRange<int>               guardRating;
    simple_parser::ValuesRange<int>               playerRating;
    simple_parser::ValuesRange<int>               heroRating;
    simple_parser::ValuesRange<float>             force;
    simple_parser::ValuesRange<int>               loseStreak;
    simple_parser::ValuesRange<int>               totalWins;
    simple_parser::ValuesRange<int>               totalLeaves;
    simple_parser::ValuesVector<string>           locales;
    std::vector<SPing>                            pings;
  };

  timer::Time                                   startTime;
  simple_parser::ValuesRange<int>               userIds;
  int                                           count;
  simple_parser::ValuesVector<lobby::ETeam::Enum> teams;
  simple_parser::ValuesRange<timer::Time>       duration;
  simple_parser::ValuesVector<int>              clientRev;
  vector<SMember>                               members;
  bool                                          readyToManoeuvre;

  timer::Time                                   nextSpawn;
  int                                           requestsSpawned;


  // member { sex M, hero {rockman, mowgly}, rating 1000 }
  bool ParseMember( SMember & _memb, simple_parser::Context & _ctx )
  {
    if ( !ForceSymbol( _ctx, "{" ) )
      return false;

    bool first = true;
    while ( true )
    {
      if ( PopSymbol( _ctx, "}" ) )
        break;

      if ( !first )
        if ( !ForceSymbol( _ctx, "," ) )
          return false;

      string key;
      if ( !ForceWord( key, _ctx ) )
        return false;

      if ( key == "sex" )
      {
        if ( !_memb.sex.Parse( _ctx ) )
          return false;
      }
      else if ( key == "hero" )
      {
        if ( !_memb.heroes.Parse( _ctx ) )
          return false;
      }
      else if ( key == "basket" )
      {
        if ( !_memb.basket.Parse( _ctx ) )
          return false;
      }
      else if ( key == "g_rating" )
      {
        if ( !_memb.guardRating.Parse( _ctx ) )
          return false;
      }
      else if ( key == "p_rating" )
      {
        if ( !_memb.playerRating.Parse( _ctx ) )
          return false;
      }
      else if ( key == "h_rating" )
      {
        if ( !_memb.heroRating.Parse( _ctx ) )
          return false;
      }
      else if ( key == "force" )
      {
        if ( !_memb.force.Parse( _ctx ) )
          return false;
      }
      else if ( key == "lose_streak" )
      {
        if ( !_memb.loseStreak.Parse( _ctx ) )
          return false;
      }
      else if ( key == "wins" )
      {
        if ( !_memb.totalWins.Parse( _ctx ) )
          return false;
      }
      else if ( key == "leaves" )
      {
        if ( !_memb.totalLeaves.Parse( _ctx ) )
          return false;
      }

      else if ( key == "loc" )
      {
        if ( !_memb.locales.Parse( _ctx ) )
          return false;
      }
      else if ( key == "ping" )
      {
        if ( !ForceSymbol( _ctx, "(" ) )
          return false;

        SMember::SPing p;
        if ( !p.clusters.Parse( _ctx ) )
          return false;
        if ( !ForceSymbol( _ctx, "," ) )
          return false;
        if ( !p.ping.Parse( _ctx ) )
          return false;
        if ( !ForceSymbol( _ctx, ")" ) )
          return false;
        _memb.pings.push_back( p );
      }
      else
        return HandleErrorf( _ctx, "Unknown keyword '%s'", key.c_str() );

      first = false;
    }

    if ( _memb.sex.empty() ) {
      _memb.sex.AddValue( lobby::ESex::Male );
      _memb.sex.AddValue( lobby::ESex::Male );
      _memb.sex.AddValue( lobby::ESex::Female );
    }

    if ( _memb.heroes.empty() ) {
      _memb.heroes.AddValue( "M1" );
      _memb.heroes.AddValue( "F1" );
    }

    if ( _memb.basket.empty() )
      _memb.basket.AddValue( mmaking::EBasket::Normal );

    if ( !_memb.guardRating.valuesSet )
      _memb.guardRating.SetValue( 1500 );

    if ( !_memb.playerRating.valuesSet )
      _memb.playerRating.SetValue( 1500 );

    if ( !_memb.heroRating.valuesSet )
      _memb.heroRating.SetValue( 1500 );

    if ( !_memb.force.valuesSet )
      _memb.force.SetValue( 110.0 );

    if ( !_memb.totalWins.valuesSet )
      _memb.totalWins.SetValue( 30 );

    if ( _memb.locales.empty() )
      _memb.locales.SetValue( "ru" );

    if ( _memb.pings.empty() )
      _memb.pings.push_back( SMember::SPing( "ru0", 10, 70 ) );

    return true;
  }


  bool SpawnMultiple( timer::Time _now, Context & _ctx )
  {
    while ( ( requestsSpawned < count ) && ( _now >= nextSpawn ) )
      Spawn( _ctx );

    return requestsSpawned < count;
  }


  void Spawn( Context & _ctx )
  {
    Strong<StoredRequest> req = new StoredRequest;

    lobby::ETeam::Enum team = _ctx.random.RollFromContainer( teams, lobby::ETeam::None );
    int rev = _ctx.random.RollFromContainer( clientRev, 101 );
    req->common = mmaking::SRequestCommonData( team, rev );

    req->members.resize( members.size() );
    for ( int i = 0; i < members.size(); ++i )
    {
      const SMember & src = members[i];
      mmaking::SRequestMember & dest = req->members[i];

      int usersSpawned = requestsSpawned * members.size() + i;
      dest.mmId = ( usersSpawned < userIds.Delta() ) ? ( userIds.from + usersSpawned ) : ( _ctx.nextUserId++ );

      dest.sex            = _ctx.random.RollFromContainer( src.sex );
      dest.heroId         = _ctx.random.RollFromContainer( src.heroes );
      dest.basket         = _ctx.random.RollFromContainer( src.basket );
      dest.guardRating    = _ctx.random.Next( src.guardRating.from, src.guardRating.to );
      dest.playerRating   = _ctx.random.Next( src.playerRating.from, src.playerRating.to );
      dest.heroRating     = _ctx.random.Next( src.heroRating.from, src.heroRating.to );
      dest.force          = _ctx.random.NextF( src.force.from, src.force.to );
      dest.loseStreak     = _ctx.random.Next( src.loseStreak.from, src.loseStreak.to );
      dest.totalWins      = _ctx.random.Next( src.totalWins.from, src.totalWins.to );
      dest.totalLeaves    = _ctx.random.Next( src.totalLeaves.from, src.totalLeaves.to );
      dest.original_team  = team;

      dest.geoInfo.locale = _ctx.random.RollFromContainer( src.locales );
      dest.geoInfo.pings.reserve( src.pings.size() );
      for ( size_t k = 0; k < src.pings.size(); ++k )
        for ( int n = 0; n < src.pings[k].clusters.size(); ++n )
          dest.geoInfo.pings.push_back( mmaking::SLocationPing( src.pings[k].clusters[n].c_str(), _ctx.random.Next( src.pings[k].ping.from, src.pings[k].ping.to ) ) );
    }

    mmaking::TRequestUId reqId = _ctx.nextReqUId++;
    _ctx.logic->AddGroupRequest( reqId, req->common, req->members, 0.0, _ctx.callback );

    Strong<StoredRequest> & slot = _ctx.requestsInMmaking[reqId];
    NI_ASSERT( !slot, "" );
    slot = req;

    nextSpawn = nextSpawn + _ctx.random.NextF( duration.from, duration.to ) / count;
    ++requestsSpawned;
  }
};

} //namespace mm_test
