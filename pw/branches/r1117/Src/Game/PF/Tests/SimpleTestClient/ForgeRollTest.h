#pragma once

#include <conio.h>

#include "System/CmdLineLite.h"

#include "Version.h"
#include "System/InlineProfiler.h"

#include "HttpGatewayProtoVersion.h"
#include "Server/WebClient/WebJsonClient.h"
#include <json/reader.h>
#include <json/writer.h>

#include "Server/LobbySocial/SocialLobbyTypes.h"


namespace forge_roll_test
{

struct Config
{
  socialLobby::TUId     uid;
  lobby::TSocialGameId  rollId;
  int                   count;
};


inline void FillRequestJson( Json::Value & request, const Config & cfg )
{
  Json::Value items( Json::arrayValue );

  for ( int i = 0; i < cfg.count; ++i )
  {
    socialLobby::TUId uid = cfg.uid + i;
    lobby::TSocialGameId rollId = cfg.rollId + i;

    Json::Value item( Json::objectValue );
    item["uid"] = NI_STRFMT( "%d", uid );
    item["roll_id"] = NI_STRFMT( "%d", rollId );
    item["count"] = 1;
    items.append( item );
  }

  request["forge_roll"] = items;
}



inline bool ParseReplyJson( const Json::Value & reply )
{
  Json::Value tag = reply.get( "forge_roll_ok", Json::Value() );
  if ( !tag.isInt() )
  {
    ErrorTrace( "'forge_roll_ok' tag not found in JSON reply" );
    return false;
  }

  int code = tag.asInt();
  if ( code != 1 )
  {
    ErrorTrace( "Forge roll failed! code=%d", code );
    return false;
  }

  return true;
}



inline void RequestRoll( const char * url, const Config & cfg )
{
  StrongMT<webClient::IJsonClient> webcl = webClient::NewJsonClient( true, true );

  Json::Value request;

  request["ver"] = NStr::StrFmt( "%d.%d.%d.rolltest", GtcSocial::Version::Major, GtcSocial::Version::Minor, GtcSocial::Version::Patch );

  FillRequestJson( request, cfg );

  Json::Value answer;
  if ( !webcl->PerformJsonPOST( url, request, answer ) ) {
    ErrorTrace( "HTTP request failed!" );
    return;
  }

  Json::Value reply = answer.get( "response", Json::Value() );
  if ( !reply.isObject() ) {
    ErrorTrace( "'response' tag not found in JSON reply" );
    return;
  }

  Json::Value ok = reply.get( "ok", Json::Value() );
  if ( !ok.isInt() || ( ok.asInt() != 1 ) ) {
    ErrorTrace( "'ok' tag not found in JSON reply" );
    return;
  }

  if ( !ParseReplyJson( reply ) )
    return;

  MessageTrace( "All ok!" );
}


inline bool Test()
{
  if ( !CmdLineLite::Instance().IsKeyDefined( "-forge" ) )
    return false;

  const char * url = CmdLineLite::Instance().GetStringKey( "-url", "http://localhost:34000/x?action=mm" );

  Config cfg;
  cfg.uid = CmdLineLite::Instance().GetIntKey( "-uid", 1000 );
  cfg.rollId = CmdLineLite::Instance().GetIntKey( "-roll_id", 100500 );
  cfg.count = CmdLineLite::Instance().GetIntKey( "-count", 1 );

  MessageTrace( "Performing Forge Roll Test" );
  MessageTrace( "URL: %s", url );
  MessageTrace( "Uid: %d", cfg.uid );
  MessageTrace( "Roll id: %d", cfg.rollId );
  MessageTrace( "Count: %d", cfg.count );
  
  RequestRoll( url, cfg );

  return true;
}

} //namespace forge_roll_test
