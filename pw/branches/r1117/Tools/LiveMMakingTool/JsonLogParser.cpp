#include "stdafx.h"
#include "JsonLogParser.h"
#include "Db/DBServer.auto.h"
#include "json/reader.h"
#include <io.h>
#include "System/InlineProfiler.h"

namespace mm_test
{

JsonLogParser::JsonLogParser( ILogParserCb * cb, ELogVersion::Enum logVersion ) :
_logVersion( logVersion ),
_cb( cb )
{
}



bool JsonLogParser::AddFile( const char * name )
{
  FILE * f = fopen( name, "rb" );
  if ( f )
  {
    if ( ReadFile( f ) )
    {
      fclose( f );
      return true;
    }
    fclose( f );
  }
  return false;
}



bool JsonLogParser::ReadFile( FILE * f )
{
  long filelen = _filelength( _fileno( f ) );
  for ( int line = 0; !feof( f ); ++line )
  {
    char buf[65536];
    buf[65535] = 0;
    int result = fscanf( f, "%65535[^\n\r]", buf );
    if ( result != 1 )
      return false;

    char tmp[16];
    result = fscanf( f, "%15[\n\r]", tmp );
    if ( result != 1 )
      return false;

    size_t textLen = strlen( buf );
    if ( ( buf[0] == '{' ) && ( buf[textLen - 1] == '}' ) )
      if ( !ParseJson( buf ) )
        return false;

    //progress
    if ( filelen ) {
      long fpos = ftell( f );
      int pro = (int)( 100ull * fpos / filelen );
      _cb->OnProgress( pro );
    }
  }

  return true;
}



bool JsonLogParser::ParseJson( const char * text )
{
  try
  {
    std::string strText( text );

    Json::Value value;
    Json::Reader reader;
    if ( !reader.parse( strText, value ) )
    {
      ErrorTrace( "JSON parse error: %s", reader.getFormatedErrorMessages().c_str() );
      return false;
    }

    ProcessJsonValue( value );
    return true;
  }
  catch ( const JsonExcep & ex )
  {
    ErrorTrace( "Catched JSON processing error: %s", ex.msg );
    return false;
  }
  catch ( const std::runtime_error & err )
  {
    ErrorTrace( "Catched runtime error: %s", err.what() );
    return false;
  }
}



void JsonLogParser::ProcessJsonValue( const Json::Value & value )
{
  Json::Value add = value["RequestQueued"];
  if ( add.type() == Json::objectValue )
  {
    ProcessAddRequest( add );
    return;
  }

  Json::Value remove = value["RequestRemoved"];
  if ( remove.type() == Json::objectValue )
  {
    ProcessRemoveRequest( remove );
    return;
  }

  Json::Value game = value["PushingGame"];
  if ( game.type() == Json::objectValue )
  {
    ProcessGame( game );
    return;
  }
}



void JsonLogParser::ParseGeoInfo( mmaking::SGeoInfo & geo, const Json::Value & value )
{
  geo.locale = value["loc"].asString().c_str();

  const Json::Value pings = value["pings"];
  if ( pings.type() == Json::arrayValue )
  {
    for ( Json::Value::const_iterator it = pings.begin(); it != pings.end(); ++it )
    {
      Json::Value entry = *it;
      if ( ( entry.type() != Json::objectValue ) || ( entry.size() != 1 ) )
        throw JsonExcep( "Wrong ping item" );
      std::string loc = entry.begin().key().asString();
      int ping = (*entry.begin()).asInt();
      geo.pings.push_back( mmaking::SLocationPing( loc.c_str(), ping ) );
    }
  }
  else
  {
    std::string geoloc = value["geo"].asString();
    geo.pings.push_back( mmaking::SLocationPing( geoloc.c_str(), 30 ) );
  }
}



void JsonLogParser::ProcessAddRequest( const Json::Value & value )
{
  Timestamp ts;
  ParseTimestamp( ts, value );

  mmaking::TRequestUId reqId = value["id"].asInt();
  timer::Time addWait = value["wait"].asDouble();

  mmaking::SRequestCommonData cmn;
  cmn.team = (lobby::ETeam::Enum)value["team"].asInt();
  cmn.clientRevision = value["rev"].asInt();
  //cmn.readyToManoeuvre = value["manvrs"].asInt() == 1;

  Json::Value M = value["members"];
  if ( M.type() != Json::arrayValue )
    throw JsonExcep( "Wrong members value" );

  vector<mmaking::SRequestMember> members;
  for ( Json::Value::iterator i = M.begin(); i != M.end(); ++i )
  {
    Json::Value m = *i;
    if ( m.type() != Json::objectValue )
      throw JsonExcep( "Wrong member value" );

    mmaking::SRequestMember member;
    member.mmId = m["mmId"].asInt();
    member.sex = (lobby::ESex::Enum)(m["sex"].asInt());
    member.heroId = m["heroId"].asString().c_str();
    member.basket = (mmaking::EBasket::Enum)(m["basket"].asInt());
    member.guardRating = m["grating"].asInt();
    member.playerRating = m["prating"].asInt();
    member.heroRating = m["hrating"].asInt();
    member.force = m["force"].asDouble();
    member.loseStreak = m["loses"].asInt();
    member.totalWins = m["wins"].asInt();
    member.totalLeaves = m["leaves"].asInt();
    member.fameLevel = m["fame"].asInt();
    member.original_team = cmn.team;
    ParseGeoInfo( member.geoInfo, m );
    members.push_back( member );
  }

  _cb->OnAddRequest( ts, reqId, cmn, members, addWait );
}



void JsonLogParser::ProcessRemoveRequest( const Json::Value & value )
{
  Timestamp ts;
  ParseTimestamp( ts, value );

  mmaking::TRequestUId reqId = value["id"].asInt();

  _cb->OnRemoveRequest( ts, reqId );
}



void JsonLogParser::ProcessGame( const Json::Value & value )
{
  Timestamp ts;
  ParseTimestamp( ts, value );

  mmaking::SGame game;

  if ( value["map_type"].isInt() )
    game.mapType = (NDb::EMapType)(value["map_type"].asInt());
  else
    game.mapType = NDb::MAPTYPE_PVP;
  game.mapId = value["map"].asString().c_str();
  game.basket =  (mmaking::EBasket::Enum)(value["basket"].asInt());

  Json::Value M = value["members"];
  if ( M.type() != Json::arrayValue )
    throw JsonExcep( "Wrong members value" );

  vector<mmaking::SRequestMember> members;
  for ( Json::Value::iterator i = M.begin(); i != M.end(); ++i )
  {
    Json::Value m = *i;
    if ( m.type() != Json::objectValue )
      throw JsonExcep( "Wrong game member value" );

    mmaking::TRequestUId reqId = m["reqId"].asInt();
    lobby::ETeam::Enum team = (lobby::ETeam::Enum)m["team"].asInt();
    timer::Time wait = m["wait"].asDouble();

    mmaking::SRequestMember member;
    member.mmId = m["userId"].asInt();
    member.sex = (lobby::ESex::Enum)(m["sex"].asInt());
    member.heroId = m["hero"].asString().c_str();
    member.basket = (mmaking::EBasket::Enum)(m["basket"].asInt());
    member.guardRating = m["gRating"].asInt();
    member.playerRating = m["pRating"].asInt();
    member.heroRating = m["hRating"].asInt();
    member.force = m["force"].asDouble();
    member.loseStreak = m["loses"].asInt();
    member.totalWins = m["wins"].asInt();
    member.totalLeaves = m["leaves"].asInt();
    member.fameLevel = m["fame"].asInt();
    ParseGeoInfo( member.geoInfo, m );
    
    mmaking::SGameParty * party = 0;
    if ( reqId )
      for ( int i = 0; i < game.humans.size(); ++i )
        if ( game.humans[i].requestUId == reqId ) {
          party = &game.humans[i];
          break;
        }

    if ( !party ) {
      game.humans.push_back( mmaking::SGameParty( mmaking::SRequestCommonData( team, 0), wait, reqId ) );
      party = &game.humans.back();
    }

    party->members.push_back( member );
  }

  _cb->OnGame( ts, game );
}



void JsonLogParser::ParseTimestamp( Timestamp & ts, const Json::Value & value )
{
  Json::Value q = value["time"];
  if ( q.type() == Json::objectValue )
  {
    ts.date.year = 2013;
    ts.date.mon = q["mon"].asInt();
    ts.date.day = q["day"].asInt();
    ts.time.hour = q["hour"].asInt();
    ts.time.minute = q["min"].asInt();
    ts.time.sec = q["sec"].asInt();
    ts.time.ms = 0;
  }
  else if ( q.isString() )
  {
    std::string s = q.asString();
    float scalar = 0;
    int ms = 0;
    if ( 7 != sscanf( s.c_str(), "%u/%u %u:%u:%u.%u %f",
      &ts.date.mon, &ts.date.day,
      &ts.time.hour, &ts.time.minute, &ts.time.sec, &ms, &scalar ) )
      throw JsonExcep( "Wrong timestamp text" );

    ts.time.ms = 10 * ms;
    ts.date.year = 2012;
  }
  else
    throw JsonExcep( "Wrong timestamp" );
}

} //namespace mm_test
