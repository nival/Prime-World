#include "stdafx.h"
#include "GatewayJSonHandler.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "Server/Roll/RRollBalancer.auto.h"
#include "Db/DBServer.auto.h"
#include "Core/GameTypes.h" //Need this to serialize talent sets
#include "System/ChunklessSaver.h"
#include "System/SafeTextFormatStl.h"
#include "System/InlineProfiler.h"
#include "ProtoVersion.h"
#include "GatewayPingContext.h"
#include "ForgeRollRequest.h"

#include "HttpGatewayLog.inl"
#include <stdexcept>

#pragma warning( disable : 4996)


namespace HttpGateway
{

static bool s_dumpJson = false;
static bool s_prettyJson = false;
REGISTER_VAR( "http_gateway_dump_json", s_dumpJson, STORAGE_NONE );
REGISTER_VAR( "http_gateway_pretty_json", s_prettyJson, STORAGE_NONE );



GatewayJsonHandler::GatewayJsonHandler( rpc::GateKeeper * _gk ) :
gateKeeper( _gk )
{
  socialLobby = new rpc::IfaceRequester<socialLobby::RISocialInterface>;
  socialLobby->init( gateKeeper, socialLobby::serviceIds::Service, socialLobby::serviceIds::SocialInterface );

  rollBalancer = new rpc::IfaceRequester<roll::RIBalancer>("cMj4tyeV3JCHOnN");
  rollBalancer->init( gateKeeper, roll::serviceIds::BalancerService, roll::serviceIds::BalancerInterface);
}



bool GatewayJsonHandler::Ready()
{
  return socialLobby->isopen();
}



void GatewayJsonHandler::Poll()
{
  NI_PROFILE_FUNCTION;

  socialLobby->step();

  switch ( socialLobby->PopNewState() )
  {
    case rpc::IfaceRequesterState::OPENED:
      SVC_LOG_MSG.Trace( "Got connection to social lobby" );
      break;

    case rpc::IfaceRequesterState::CLOSED:
      SVC_LOG_ERR.Trace( "Lost connection to social lobby!" );
      break;

    default:
      break;
  }

  {
    threading::MutexLock lock( mutex );
    rollBalancer->step();

    switch ( rollBalancer->PopNewState() )
    {
      case rpc::IfaceRequesterState::OPENED:
        SVC_LOG_MSG.Trace( "Got connection to roll service" );
        break;

      case rpc::IfaceRequesterState::CLOSED:
        SVC_LOG_ERR.Trace( "Lost connection to roll service!" );
        break;

      default:
        break;
    }
  }

  PollContexts();
  PollForgeRollrequests();
}



void GatewayJsonHandler::PollContexts()
{
  timer::Time t = timer::Now();

  threading::MutexLock lock( mutex );

  for ( TCacheMap::iterator it = byUids.begin(); it != byUids.end(); )
  {
    StrongMT<PingContext> & ctx = it->second;

    if ( ctx->Poll( t ) ) {
      ++it;
      continue;
    }

    SVC_LOG_WRN.Trace( "Removing failed context: uid=%d", ctx->Uid() );

    TCacheMap::iterator next = it;
    ++next;
    byUids.erase( it );
    it = next;
  }
}



void GatewayJsonHandler::PollForgeRollrequests()
{
  timer::Time t = timer::Now();

  threading::MutexLock lock( mutex );

  for ( ForgeRollRequests::iterator it = forgeRollRequests.begin(); it != forgeRollRequests.end(); )
  {
    ForgeRollRequest * req = *it;

    if ( req->Poll( t ) )
    {
      ++it;
      continue;
    }

    it = forgeRollRequests.erase( it );
  }
}



static void DumpJson( const Json::Value & value, const char * title )
{
  NI_PROFILE_FUNCTION;


  std::string json_request;
  if ( s_prettyJson )
    json_request = (Json::StyledWriter()).write( value );
  else
    json_request = (Json::FastWriter()).write( value );

  if( json_request.length() > 2000 )
    SVC_LOG_DBG << title << "x";
  else
    SVC_LOG_DBG << title << json_request.c_str();
}



bool GatewayJsonHandler::CheckVersion( const Json::Value & request )
{
  NI_PROFILE_FUNCTION;

  Json::Value ver = request.get( "ver", 0 );
  if ( !ver.isString() ) {
    SVC_LOG_ERR.Trace( "No version string in JSON data!" );
    return false;
  }

  std::string verStr = ver.asString();

  int major = 0, minor = 0, patch = 0;
  if ( sscanf( verStr.c_str(), "%d%.%d%.%d", &major, &minor, &patch ) != 3 ) {
    SVC_LOG_ERR.Trace( "Wrong version string '%s' in JSON data!", verStr.c_str() );
    return false;
  }

  if ( ( major != Version::Major ) || ( minor != Version::Minor ) || ( patch != Version::Patch ) )
  {
    SVC_LOG_ERR.Trace( "Wrong version '%s' in JSON data! Server version is %d.%d.%d", verStr.c_str(), Version::Major, Version::Minor, Version::Patch );
    return false;
  }

  return true;
}



void GatewayJsonHandler::HandleJson( std::string & json_reply, const std::string & json_data )
{
  try {
    HandleJsonThrow( json_reply, json_data );
  }
  catch ( const std::runtime_error & err ) { //JSON lib can throw this crap
    SVC_LOG_ERR.Trace( "Catched runtime error exception: %s", err.what());
  }
}



void GatewayJsonHandler::HandleJsonThrow( std::string & json_reply, const std::string & json_data )
{
  NI_PROFILE_FUNCTION_MEM;

  Json::Value reply;
  Json::Value pvxReply(Json::objectValue);
  Json::Value forgeRollReply(Json::objectValue);

  Json::Value request;
  Json::Reader reader;
  bool parsingSuccessful = false;
  {
    NI_PROFILE_BLOCK( "Deserialize JSON" );
    parsingSuccessful = reader.parse( json_data, request );
  }
  if ( parsingSuccessful )
  {
    if ( CheckVersion( request ) )
    {
      reply["response"]["ok"] = 1;

      if ( s_dumpJson )
        DumpJson( request, "----\nParsed  JSON data:\n" );

      HandleGenericRequest( pvxReply, request, "party_cancel",  &GatewayJsonHandler::HandleCancelPartyReq );
      HandleGenericRequest( pvxReply, request, "cancel",        &GatewayJsonHandler::HandleCancelReq );
      HandleGenericRequest( pvxReply, request, "close",         &GatewayJsonHandler::HandleCancelReq ); //"close" is just explicit gracefull "cancel"
      HandleGenericRequest( pvxReply, request, "leave",         &GatewayJsonHandler::HandleLeaveReq );
      HandleGenericRequest( pvxReply, request, "reconnect",     &GatewayJsonHandler::HandleReconnectReq );
      HandleAddRequests( pvxReply, request );
      HandleSpectateRequests( pvxReply, request );
      HandleGenericRequest( pvxReply, request, "ping",          &GatewayJsonHandler::HandlePingReq );
      HandleGenericRequest( pvxReply, request, "accept",        &GatewayJsonHandler::HandleAcceptReq );
      HandleGenericRequest( pvxReply, request, "change_hero",   &GatewayJsonHandler::HandleGuardChangeHeroReq );
      HandleGenericRequest( pvxReply, request, "ready",         &GatewayJsonHandler::HandleGuardReadyReq );

      HandleServerStatus( pvxReply, request );

      HandleForgeRoll( forgeRollReply, request );
    }
    else
    {
      reply["response"]["ok"] = 0;
      reply["response"]["error"] = NI_STRFMT( "Version mismatch. Server version: %d.%d.%d", Version::Major, Version::Minor, Version::Patch );
    }
  }
  else
  {
    reply["response"]["ok"] = 0;

    SVC_LOG_DBG << "Failed to parse json data\n" << reader.getFormatedErrorMessages().c_str();
    reply["response"]["error"] = "Failed to parse json data\n" + reader.getFormatedErrorMessages();
  }

  {
    NI_PROFILE_BLOCK( "Set reply" );
    reply["response"]["pvx"] = pvxReply;
    reply["response"]["forge_roll_ok"] = forgeRollReply;
  }

  json_reply.clear();

  NI_PROFILE_BLOCK( "Serialize JSON" );

  if ( s_prettyJson )
    json_reply = (Json::StyledWriter()).write( reply );
  else
    json_reply = (Json::FastWriter()).write( reply );

  if ( s_dumpJson )
    SVC_LOG_DBG << "\nReturned JSON reply: " << json_reply.c_str();
}




StrongMT<socialLobby::RISocialInterface> GatewayJsonHandler::SocLobbyThreadSafe()
{
  threading::MutexLock lock( mutex );
  NI_VERIFY( socialLobby->isopen(), "", return 0 );
  return socialLobby->iface();
}



StrongMT<PingContext> GatewayJsonHandler::GetCtxByUid( socialLobby::TUId uid )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock guard( mutex );
  TCacheMap::iterator it = byUids.find( uid );
  if ( it == byUids.end() )
    return 0;
  return it->second;
}



StrongMT<PingContext> GatewayJsonHandler::GetCtxSafe( socialLobby::TUId uid, const char * dbgText )
{
  StrongMT<PingContext> ctx = GetCtxByUid( uid );

  if ( !ctx ) {
    SVC_LOG_WRN.Trace( "Unknown uid! Reason: %s, uid=%d", dbgText, uid );
    return 0;
  }

  if ( uid != ctx->Uid() )
    SVC_LOG_ERR.Trace( "Wrong uid in context! Reason: %s, uid=%d, expected uid=%d", dbgText, uid, ctx->Uid() );

  return ctx;
}



StrongMT<PingContext> GatewayJsonHandler::CreateContext( socialLobby::TUId uid, const char * sessionId, EContextState::Enum ctxState, socialLobby::ERequestStatus::Enum status )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  StrongMT<PingContext> & slot = byUids[uid];
  if ( !slot.Valid() ) {
    slot = new PingContext( timer::Now(), uid, sessionId, ctxState, status );
    return slot;
  }

  if ( ctxState != EContextState::New ) {
    SVC_LOG_ERR.Trace( "Duplicate context restoration. uid=%d", uid );
    return 0;
  }

  if ( slot->ResetRestored( timer::Now(), sessionId, ctxState, status ) ) {
    SVC_LOG_WRN.Trace( "Restored existing session context for uid=%d, mmid=%s", uid, sessionId );
    return slot;
  }

  SVC_LOG_ERR.Trace( "Duplicate session for uid=%d, mmid=%s, ctxState=%d", uid, sessionId, (int)slot->CtxState() );
  return 0;
}



void GatewayJsonHandler::HandleAddRequests( Json::Value & pvxReply, const Json::Value & request )
{
  NI_PROFILE_FUNCTION;

  Json::Value dict = request.get("add", 0);
  if ( !dict.isObject() )
    return;

  Json::Value::Members uids = dict.getMemberNames();
  for ( Json::Value::Members::iterator it = uids.begin(); it != uids.end(); ++it )  
  {
    std::string uid = *it;
    Json::Value value = dict[uid];

    if ( !value.isObject() ) {
      SVC_LOG_ERR.Trace( "Wrong add record. uid=%s", uid.c_str() );
      continue;
    }

    SVC_LOG_MSG.Trace( "Processing 'add' request: uid=%s, type=%d", uid, (int)value.type() );
    HandleSingleAddRequest( pvxReply, uid, value );
  }
}



inline void ParseGeoInfo( mmaking::SGeoInfo & result, const Json::Value & requestData )
{
  result.locale = requestData["locale"].asString().c_str();
  NStr::ToLower( &result.locale );

  const Json::Value pings = requestData["pings"];
  if ( pings.isObject() )
  {
    for ( Json::Value::const_iterator it = pings.begin(); it != pings.end(); ++it ) {
      string loc = it.memberName();
      int ping = (*it).isNumeric() ? (*it).asInt() : 0;

      NStr::ToLower( &loc );
      result.pings.push_back( mmaking::SLocationPing( loc.c_str(), ping ) );
    }
  }

  result.location = requestData.get( "geolocation", 0 ).asString().c_str();
}



inline void ParsePartyLineup( vector<socialLobby::TUId> & lineup, const Json::Value & requestData, const char * fldName )
{
  lineup.clear();

  nstl::string strPartyAuids( requestData.get( fldName, 0 ).asString().c_str() );
  if ( strPartyAuids.empty() )
    return;

  vector<nstl::string> partyLineup;
  NStr::SplitString( strPartyAuids, &partyLineup, ',' );

  for( int i = 0; i < partyLineup.size(); ++i )
    if ( !partyLineup[i].empty() )
    {
      socialLobby::TUId partyuid = PingContext::StrToUid( partyLineup[i].c_str() );
      lineup.push_back( partyuid );
    }
}



void GatewayJsonHandler::HandleSingleAddRequest( Json::Value & pvxReply, const std::string & uidString, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isObject() )
    return;

  socialLobby::SMatchmakingRequest mmReq;

  socialLobby::TUId uid = PingContext::StrToUid( uidString.c_str() );

  mmReq.uid = uid;
  mmReq.userIdPvx = requestData.get("zz_uid", 0).asInt();

  int faction = requestData.get("fraction", 0).asInt();
  NI_VERIFY( faction == lobby::ETeam::None || faction == lobby::ETeam::Team1 || faction == lobby::ETeam::Team2,
              NI_STRFMT( "Wrong faction value %d", faction ), return );

  int original_fraction = requestData.get("original_fraction", 0).asInt();
  NI_VERIFY( original_fraction == lobby::ETeam::None || original_fraction == lobby::ETeam::Team1 || original_fraction == lobby::ETeam::Team2,
    NI_STRFMT( "Wrong original_fraction value %d", original_fraction ), original_fraction = faction );

  mmReq.sessionContextId = requestData.get( "mmid", "" ).asString().c_str();

  std::string map = requestData.get("game_type", "").asString();
  mmReq.map = map.c_str();

  mmReq.faction = (lobby::ETeam::Enum)faction;
  mmReq.original_faction = (lobby::ETeam::Enum)original_fraction;

  mmReq.heroId = requestData.get("hero", 0).asString().c_str();
  mmReq.zzimaSex = (lobby::ESex::Enum)requestData.get("sex", lobby::ESex::Male).asInt();
  if ( ( mmReq.zzimaSex != lobby::ESex::Male ) && ( mmReq.zzimaSex != lobby::ESex::Female ) ) {
    mmReq.zzimaSex = lobby::ESex::Male;
    SVC_LOG_ERR.Trace( "Undefined sex %d in add request %s, using 'male' instead", (int)mmReq.zzimaSex, uidString );
  }
  mmReq.clientRevision = requestData.get("client_revn", 0).asInt();
  

  mmReq.basket = (mmaking::EBasket::Enum)( requestData.get("lord_status", 0).asInt() );
  if ( ( mmReq.basket != mmaking::EBasket::Newbie ) && ( mmReq.basket != mmaking::EBasket::Normal ) && ( mmReq.basket != mmaking::EBasket::Leaver )  ) {
    SVC_LOG_ERR.Trace( "Wrong player basket %d in add request %s, using 'Normal' instead", (int)mmReq.basket, uidString );
    mmReq.basket = mmaking::EBasket::Normal;
  }

  mmReq.guardRating = requestData.get("guard_rating", 0).asInt();
  mmReq.playerRating = requestData.get("lord_rating", 0).asInt();
  mmReq.heroRating = (int)requestData.get("hero_rating", 0).asDouble();
  mmReq.force = (float)requestData.get("force", 0).asDouble();
  mmReq.totalWins = requestData.get("lord_wins", 0).asInt();
  ParseGeoInfo( mmReq.geoInfo, requestData );
  mmReq.login = requestData.get("zz_login", "").asString().c_str();

  mmReq.partyId = _atoi64( requestData.get("party_id", 0).asString().c_str() );
  ParsePartyLineup( mmReq.partyLineup, requestData, "party_auids" );
  ParsePartyLineup( mmReq.enemyPartyLineup, requestData, "enemy_auids" );

  mmReq.winLoseHistory = requestData.get("win_lose_hist", 0).asString().c_str();

  mmReq.fameLevel = requestData.get("avatarLevel", 0).asInt(); 

  std::string nickname = requestData.get("nick", 0).asString();

  string decodedNickname;
  NStr::UrlDecode( decodedNickname, nickname.c_str(), true );
  NStr::UTF8ToUnicode( &mmReq.nickname, decodedNickname );

  SVC_LOG_MSG.Trace( "Performing AddRequest. Data: uid=%s, mmid=%s, pvx_uid=%d, login='%s', nick='%s', partyId=%d, party=%i, enemy_party=%i", 
    uidString, mmReq.sessionContextId, mmReq.userIdPvx, mmReq.login, mmReq.nickname, mmReq.partyId, mmReq.partyLineup, mmReq.enemyPartyLineup );
  SVC_LOG_MSG.Trace( "AddRequest data: uid=%s, mmid=%s, faction=%d, original_faction=%d, sex=%d, map='%s', hero='%s', basket=%d, rev=%d", 
    uidString, mmReq.sessionContextId, (int)mmReq.faction, (int)mmReq.original_faction, (int)mmReq.zzimaSex, map, mmReq.heroId, (int)mmReq.basket, mmReq.clientRevision );
  SVC_LOG_MSG.Trace( "AddRequest data: uid=%s, mmid=%s, guardRating=%d, playerRating=%d, force=%.1f, fame=%d, winLose=%s, totalWins=%d", 
    uidString, mmReq.sessionContextId, mmReq.guardRating, mmReq.playerRating, mmReq.force, mmReq.fameLevel, mmReq.winLoseHistory, mmReq.totalWins );

  socialLobby::ERequestStatus::Enum status = socialLobby::ERequestStatus::JustAddedToHttpGateway;
  StrongMT<PingContext> ctx = CreateContext( uid, mmReq.sessionContextId.c_str(), EContextState::New, status );
  if ( !ctx ) {
    pvxReply["add"][uidString] = 0;
    return;
  }
  try
  {
    if ( StrongMT<socialLobby::RISocialInterface> soclobby = SocLobbyThreadSafe() )
      soclobby->AddRequest( mmReq, ctx.Get() );
  }
  catch ( const std::runtime_error & err ) { //JSON lib can throw this crap
    SVC_LOG_ERR.Trace( "Fail of building the request for socialLobby: %s", err.what() );
    pvxReply["add"][uidString] = 0;
    return;
  }
  catch(...)
  {
      
    SVC_LOG_ERR.Trace("Fail of building the request for socialLobby ");
    pvxReply["add"][uidString] = 0;
    return;
  }

  
  pvxReply["add"][uidString] = (int)status;
}



void GatewayJsonHandler::HandleSpectateRequests( Json::Value & pvxReply, const Json::Value & request )
{
  NI_PROFILE_FUNCTION;

  Json::Value dict = request.get("spectate", 0);
  if ( !dict.isObject() )
    return;

  Json::Value::Members uids = dict.getMemberNames();
  for ( Json::Value::Members::iterator it = uids.begin(); it != uids.end(); ++it )  
  {
    std::string uid = *it;
    Json::Value value = dict[uid];

    if ( !value.isObject() ) {
      SVC_LOG_ERR.Trace( "Wrong spectate record. uid=%s", uid.c_str() );
      continue;
    }

    SVC_LOG_MSG.Trace( "Processing 'spectate' request: uid=%s, type=%d", uid, (int)value.type() );
    HandleSingleSpectateRequest( pvxReply, uid, value );
  }
}



void GatewayJsonHandler::HandleSingleSpectateRequest( Json::Value & pvxReply, const std::string & uidString, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isObject() )
    return;

  socialLobby::SMatchmakingRequestCore spectReq;

  socialLobby::TUId uid = PingContext::StrToUid( uidString.c_str() );

  spectReq.uid = uid;
  spectReq.userIdPvx = requestData.get("zz_uid", 0).asInt();
  spectReq.sessionContextId = requestData.get( "mmid", "" ).asString().c_str();
  spectReq.login = requestData.get("zz_login", "").asString().c_str();

  std::string targetStr = requestData.get( "target_uid", "" ).asString();
  socialLobby::TUId target = PingContext::StrToUid( targetStr.c_str() );

  std::string nickname = requestData.get("nick", 0).asString();
  string decodedNickname;
  NStr::UrlDecode( decodedNickname, nickname.c_str(), true );
  NStr::UTF8ToUnicode( &spectReq.nickname, decodedNickname );

  SVC_LOG_MSG.Trace( "Performing Spectate. Data: uid=%s, mmid=%s, pvx_uid=%d, target_uid=%d, login='%s', nick='%s'", 
    uidString, spectReq.sessionContextId, spectReq.userIdPvx, target, spectReq.login, spectReq.nickname );

  socialLobby::ERequestStatus::Enum status = socialLobby::ERequestStatus::JustAddedToHttpGateway;
  StrongMT<PingContext> ctx = CreateContext( uid, spectReq.sessionContextId.c_str(), EContextState::New, status );
  if ( !ctx ) {
    pvxReply["spectate"][uidString] = 0;
    return;
  }

  if ( StrongMT<socialLobby::RISocialInterface> soclobby = SocLobbyThreadSafe() )
    soclobby->Spectate( spectReq, target, ctx.Get() );
  pvxReply["spectate"][uidString] = (int)status;
}



void GatewayJsonHandler::HandleGenericRequest( Json::Value & pvxReply, const Json::Value & request, const char * key, TGenericRequestHandler handler )
{
  NI_PROFILE_FUNCTION;

  Json::Value dict = request.get( key, 0 );
  if ( !dict.isObject() )
    return;
 
  Json::Value::Members uids = dict.getMemberNames();
  for ( Json::Value::Members::iterator it = uids.begin(); it != uids.end(); ++it )  
  {
    std::string uidString = *it;
    Json::Value value = dict[uidString];

    socialLobby::TUId uid = PingContext::StrToUid( uidString.c_str() );
    StrongMT<PingContext> ctx = GetCtxSafe( uid, key );

    int ctxSt = ctx.Valid() ? (int)ctx->CtxState() : 0;
    SVC_LOG_MSG.Trace( "Processing '%s' request: uid=%s, type=%d, ctxState=%d", key, uidString, (int)value.type(), ctxSt );

    EGenericReqReply::Enum answer = (this->*handler)( pvxReply, uidString, ctx, value );

    switch ( answer )
    {
      case EGenericReqReply::ReplyZero:
        pvxReply[key][uidString] = 0;
        break;

      case EGenericReqReply::ReplyMmid:
        if ( ctx.Valid() )
          pvxReply[key][uidString] = ctx->SessionId();
        else
          SVC_LOG_WRN.Trace( "No context to reply with session id: uid=%s, reason='%s'", uidString, key );
        break;

      case EGenericReqReply::DoNothing:
      default:
        break;

      case EGenericReqReply::BadRequest:
        SVC_LOG_WRN.Trace( "Bad '%s' request: uid=%s, type=%d", key, uidString, (int)value.type() );
        break;
    }
  }
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandlePingReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( !ctx )
  {
    SVC_LOG_MSG.Trace( "Trying to acquire new ping context from lobby. uid=%s", uidStr );
    socialLobby::TUId uid = PingContext::StrToUid( uidStr.c_str() );
    StrongMT<PingContext> newCtx = CreateContext( uid, "", EContextState::Restored, socialLobby::ERequestStatus::Null );
    if ( !newCtx )
      return EGenericReqReply::DoNothing;

    if ( StrongMT<socialLobby::RISocialInterface> soclobby = SocLobbyThreadSafe() )
      soclobby->GetRequest( uid, newCtx.Get() );
    return EGenericReqReply::DoNothing;
  }

  ctx->HandlePingRequest( pvxReply );
  return EGenericReqReply::DoNothing; //We've formatted reply already
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleCancelReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( !ctx )
    return EGenericReqReply::DoNothing;

  ctx->HandleCancelRequest( false );

  return EGenericReqReply::ReplyMmid;
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleCancelPartyReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( !ctx )
    return EGenericReqReply::DoNothing;

  ctx->HandleCancelRequest( true );

  return EGenericReqReply::ReplyMmid;
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleLeaveReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( ctx )
    ctx->HandleLeaveRequest();

  return EGenericReqReply::ReplyMmid; //LEGACY: Always returning 'ok', even if there is not such uid-context
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleReconnectReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( ctx )
    ctx->HandleReconnectRequest();

  return EGenericReqReply::ReplyMmid; //LEGACY: Always returning 'ok', even if there is not such uid-context
}

void Json2RollTableItems( Json::Value& jsonRollItems, vector<NCore::TalentRollItem>& items )
{
  NI_VERIFY( jsonRollItems.isArray(), "Json2RollTableItems json object should be array", return );

  int itemsNumber = jsonRollItems.size();
  items.resize(itemsNumber);
  for ( int i = 0; i < itemsNumber; ++i )  
  {
    Json::Value item = jsonRollItems[i];

    NCore::TalentRollItem & talentRollItem = items[i];

    talentRollItem.probability = item.get("probability", 0).asInt();

    // Fix to handle old dbid as string
    Json::Value dbidValue = item.get("dbid", 0);
    if ( dbidValue.isIntegral() )
      talentRollItem.dbid = dbidValue.asInt();
    else
      talentRollItem.dbid = 0;
  }
}


static void ParseTalentRollData( NCore::TalentRollData & data, const std::string & strData )
{
  if ( strData.empty() )
    return;

  {
    Json::Value sessionRollJson;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( strData, sessionRollJson );
    if ( parsingSuccessful )
    {
      data.generationIndex = sessionRollJson.get("gen_index", 0).asInt();

      Json::Value::Members slots = sessionRollJson.getMemberNames();
      for ( Json::Value::Members::iterator it = slots.begin(); it != slots.end(); ++it )  
      {
        std::string slot_key = *it;

        if ( slot_key == "gen_index" )
          continue;

        Json::Value jsonRollItemsObj = sessionRollJson[slot_key];

        NCore::TalentRollItems& rollItems = data.rollTable[slot_key.c_str()];

        if( jsonRollItemsObj.isObject() )
        {
          rollItems.version = jsonRollItemsObj.get("version", 0).asInt();
          rollItems.dbVersion = jsonRollItemsObj.get("db_version",0).asInt();
          Json::Value jsonDefaultItems = jsonRollItemsObj["default"];
          Json::Value jsonPremiumItems = jsonRollItemsObj["premium"];
          if ( jsonDefaultItems.isObject() )
            Json2RollTableItems( jsonDefaultItems["items"], rollItems.defaultItems );
          if ( jsonPremiumItems.isObject() )
            Json2RollTableItems( jsonPremiumItems["items"], rollItems.premiumItems );
        }
      }

    }
  }
}



static void ParseGuildData( NCore::GuildData & data, const Json::Value & value )
{
  data.id = PingContext::StrToUid( value["guild_auid"].asString().c_str() );
  data.rating = value["guild_rating"].asDouble();
  data.level = value["guild_level"].asInt();
  data.buildingLevel = value["guild_building_level"].asInt();
  data.icon_number = value["guild_icon_number"].asInt();
  data.icon_url = value["guild_icon_url"].asString().c_str();
  data.guidWarEventPass = value.get("guild_war_event_pass", false).asBool();
}



inline void ParsePlayerData( NCore::PlayerInfo & data, const Json::Value & value, socialLobby::TUId uid )
{
  data.auid = uid;
  data.heroId = value.get("hid", 0).asInt(); 
  data.heroEnergy = value.get("energy", 0).asInt(); 
  data.avatarLevel = value.get("avatarLevel", 0).asInt(); 
  data.heroLevel = value.get("heroLevel", 0).asInt(); 
  data.heroExp = value.get("heroExp", 0).asInt(); 
  data.guardRating = value.get("guardRating", 0).asDouble(); 
  data.playerRating = value.get("lordRating", 0).asDouble();
  data.heroRating = value.get("heroRating", 0).asDouble();
  data.hsHealth = value.get("hsHealth", 0).asDouble();
  data.hsMana = value.get("hsMana", 0).asDouble();
  data.hsStrength = value.get("hsStrength", 0).asDouble();;
  data.hsIntellect = value.get("hsIntellect", 0).asDouble();
  data.hsAgility = value.get("hsAgility", 0).asDouble();
  data.hsCunning = value.get("hsCunning", 0).asDouble();
  data.hsFortitude = value.get("hsFortitude", 0).asDouble();
  data.hsWill = value.get("hsWill", 0).asDouble();
  data.dropRate = value.get("dropRate", 0).asDouble();
  data.hsLifeRegen = value.get("hsLifeRegen", 0).asDouble();
  data.hsManaRegen = value.get("hsManaRegen", 0).asDouble();
  data.hasPremium = value.get("hasPremium", false).asBool();
  data.partyLeader = value.get("partyLeader", false).asBool();
  data.heroSkin = value.get("heroSkin", "").asCString();
  data.isAnimatedAvatar = value.get("animAvatar", true).asBool();
  data.leagueIndex = value.get("LeagueIndex", 0).asInt();
  data.ownLeaguePlace = value.get("ownLeaguePlace", 0).asInt();
  data.basket = (NCore::EBasket::Enum)( value.get("lord_status", 0).asInt() );
  if ( ( data.basket != NCore::EBasket::Newbie ) && ( data.basket != NCore::EBasket::Normal ) && ( data.basket != NCore::EBasket::Leaver  ) ){
    SVC_LOG_ERR.Trace( "Wrong player basket %d in accept request, using 'Normal' instead, uid=%d", (int)data.basket, uid );
    data.basket = NCore::EBasket::Normal;
  }
  data.fwod = value.get("firstWin", false).asBool();
  data.goldLampRollContainer = value.get("goldLamp", "").asString().c_str();

  SVC_LOG_DBG.Trace( "Player data: uid=%d, premium=%d, drop=%.3f, hero=%d, nrg=%d, lvl=%d, heroLvl=%d, heroSkin=%s", 
    uid, (int)data.hasPremium, data.dropRate, (int)data.heroId, data.heroEnergy, data.avatarLevel, data.heroLevel, data.heroSkin.c_str() );

  SVC_LOG_DBG.Trace( "Player data: uid=%d, will=%d, fort=%d, cunn=%d, agil=%d, int=%d, str=%d, mana=%d, hp=%d", 
    uid, data.hsWill, data.hsFortitude, data.hsCunning, data.hsAgility,
    data.hsIntellect, data.hsStrength, data.hsMana, data.hsHealth );

  data.locale = value.get("locale", "").asString().c_str();
  
  Json::Value inventory = value["inventory"];
  if( inventory.isArray() )
  {
    data.inventory.reserve( inventory.size() );
    for ( uint i = 0; i < inventory.size(); i++ )
      data.inventory.push_back( inventory[i].asInt() );
  }

  Json::Value friends = value["friends"];
  if( friends.isArray() )
  {
    data.friends.reserve( friends.size() );
    for ( uint i = 0; i < friends.size(); i++ )
      data.friends.push_back( friends[i].asInt() );
  }

  Json::Value leaguePlaces = value["leaguePlaces"];
  if( leaguePlaces.isArray() )
  {
    data.leaguePlaces.reserve( leaguePlaces.size() );
    for ( uint i = 0; i < leaguePlaces.size(); i++ )
      data.leaguePlaces.push_back( int(leaguePlaces[i].asFloat()) );
  }

  Json::Value talents = value["ts"];

  if( talents.isObject() )
  {
    string dbgTalents;
    Json::Value::Members slots = talents.getMemberNames();
    for ( Json::Value::Members::iterator it = slots.begin(); it != slots.end(); ++it )  
    {
      std::string slot_key = *it;
      Json::Value talent_dict = talents[slot_key];

      int slotId = NStr::Convert<int>( slot_key.c_str() );
      NCore::TalentInfo & talent = data.talents[slotId];
      talent.id = (uint)talent_dict.get("id", 0).asInt();
      talent.refineRate = talent_dict.get("rr", 0).asInt();
      talent.actionBarIdx = talent_dict.get("ab", 0).asInt();
      talent.isInstaCast = talent_dict.get("ic", false).asBool();

      dbgTalents += NI_STRFMT( "%s%d:%d", ( it == slots.begin() ) ? "" : ", ", slotId, (int)talent.id );
    }

    SVC_LOG_DBG.Trace( "Player data: uid=%d, talents=%s", uid, dbgTalents );
  }

  data.complaintsToday = value.get("complaints_today", 0).asInt(); 
  data.complaintsMax = value.get("complaints_max", 0).asInt(); 

  Json::Value complaints = value["complaints_info"];
  if( complaints.isObject() )
  {
    string dbgComplaints;
    Json::Value::Members keys = complaints.getMemberNames();
    for ( Json::Value::Members::iterator it = keys.begin(); it != keys.end(); ++it )  
    {
      std::string complaint_key = *it;
      int complaintCategory = NStr::Convert<int>( complaint_key.c_str() );

      Json::Value complaintInfo = complaints[complaint_key];
      if ( complaintInfo.isString() )
      {
        data.complaintsInfo[complaintCategory] = complaintInfo.asString().c_str();
        dbgComplaints += NI_STRFMT( "%s%d:%s", ( it == keys.begin() ) ? "" : ", ", complaintCategory, data.complaintsInfo[complaintCategory] );
      }
      else
      {
        SVC_LOG_ERR.Trace( "Error parse complaints info with key %s", complaint_key.c_str() );
      }
    }
    SVC_LOG_DBG.Trace( "Complaints info: %s", dbgComplaints );
  }

  Json::Value awardsBuffs = value["buffs2roll"];
  if (awardsBuffs.isArray())
  {
    data.aBuffs.reserve( awardsBuffs.size() );
    for ( uint i = 0; i < awardsBuffs.size(); i++ )
      data.aBuffs.push_back( awardsBuffs[i].asString().c_str() );
  }
/*
  Json::Value persistentStatModifiers = value["ps_modifiers"];
  if( persistentStatModifiers.isObject() )
  {
    string dbgPerisistentModifiers;
    Json::Value::Members keys = persistentStatModifiers.getMemberNames();
    for ( Json::Value::Members::iterator it = keys.begin(); it != keys.end(); ++it )  
    {
      std::string stat_id = *it;
      NDb::EStat statId = static_cast<NDb::EStat>(NStr::Convert<int>( stat_id.c_str() ));

      Json::Value modifierValue = persistentStatModifiers[stat_id];
      if ( modifierValue.isNumeric() )
      {
        data.psModifiers[statId].add = modifierValue.asDouble();
        dbgPerisistentModifiers += NI_STRFMT( "%s%s:[add=%5.2f, mul=not present]", ( it == keys.begin() ) ? "" : ", ", 
          stat_id, data.psModifiers[statId].add );
      }
      else if ( modifierValue.isArray() )
      {
        data.psModifiers[statId].add = modifierValue[0].asDouble();
        data.psModifiers[statId].mul = modifierValue[1].asDouble();
        dbgPerisistentModifiers += NI_STRFMT( "%s%s:[add=%5.2f, mul=%5.2f]", ( it == keys.begin() ) ? "" : ", ", 
          stat_id, data.psModifiers[statId].add, data.psModifiers[statId].mul );
      }
      else if ( modifierValue.isObject() )
      {
        data.psModifiers[statId].add = modifierValue.get("add").asDouble();
        data.psModifiers[statId].mul = modifierValue.get("mul").asDouble();
        dbgPerisistentModifiers += NI_STRFMT( "%s%s:[add=%5.2f, mul=%5.2f]", ( it == keys.begin() ) ? "" : ", ", 
          stat_id, data.psModifiers[statId].add, data.psModifiers[statId].mul );
      }
      else
      {
        SVC_LOG_ERR.Trace( "Error parse persistent modifiers with key %s", stat_id.c_str() );
      }
    }
    SVC_LOG_DBG.Trace( "Persistent modifiers info: %s", dbgPerisistentModifiers );
  }
*/
  data.chatMuted = value.get("chat_muted", false).asBool(); 
  SVC_LOG_DBG.Trace( "Chat mute: uid=%d, mute=%d'", uid, (int)data.chatMuted );

  std::string strSessionRollData = value.get("session_roll", "").asString();
  ParseTalentRollData( data.talentRollData, strSessionRollData );
  SVC_LOG_DBG.Trace( "Talent roll data: uid=%d, roll='%s'", uid, strSessionRollData );

  ParseGuildData( data.guildData, value );
  SVC_LOG_DBG.Trace( "Guild data: uid=%d, guild_id=%d, guild_rtg=%.1f, guild_lvl=%d, build_blvl=%d, icon_number=%d, icon_url=%s", 
    uid, data.guildData.id, data.guildData.rating, data.guildData.level, data.guildData.buildingLevel, data.guildData.icon_number, data.guildData.icon_url.c_str() );

  data.flagId = value.get( "flag_id", "" ).asString().c_str();
  data.flagCustomPicture = value.get( "flag_picture", "" ).asString().c_str();

  std::string flagTooltip = value.get("flag_tooltip", "").asString();
  string decodedflagTooltip;
  NStr::UrlDecode( decodedflagTooltip, flagTooltip.c_str(), true );
  NStr::UTF8ToUnicode( &data.flagCustomTooltip, decodedflagTooltip );

  data.hasFullLibrary = value.get("hasFullLibrary", false).asBool();
}



inline void MeasurePlayerData( const socialLobby::SPlayerData & data )
{
#if 0 //DO_COMMIT
  CObj<Stream> stream = new MemoryStream(16384);
  CObj<IBinSaver> saver = CreateChunklessSaver( stream, 0, false );

  socialLobby::SPlayerData & nonConstData = const_cast<socialLobby::SPlayerData & >( data );
  nonConstData & *saver;

  int sz = stream->GetPosition();
  DebugTrace( "Player data size: %d", sz );
#endif
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleAcceptReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isObject() )
    return EGenericReqReply::BadRequest;

  if ( !ctx ) {
    SVC_LOG_ERR.Trace( "Accepting unknown user context. uid=%lld" );
    return EGenericReqReply::DoNothing;
  }

  socialLobby::SPlayerData playerData;
  ParsePlayerData( playerData.data, requestData, ctx->Uid() );

  MeasurePlayerData( playerData );

  if ( !ctx->HandleAcceptRequest( playerData ) )
    return EGenericReqReply::DoNothing;

  return EGenericReqReply::ReplyMmid;
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleGuardChangeHeroReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isObject() )
    return EGenericReqReply::BadRequest;

  if ( !ctx ) {
    SVC_LOG_ERR.Trace( "Guard hero change: unknown user context. uid=%lld" );
    return EGenericReqReply::DoNothing;
  }

  socialLobby::SPlayerData playerData;
  ParsePlayerData( playerData.data, requestData, ctx->Uid() );

  if ( !ctx->HandleHeroChangeRequest( playerData ) )
    return EGenericReqReply::DoNothing;

  return EGenericReqReply::ReplyMmid;
}



GatewayJsonHandler::EGenericReqReply::Enum GatewayJsonHandler::HandleGuardReadyReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData )
{
  NI_PROFILE_FUNCTION;

  if ( !requestData.isNumeric() || ( requestData.asInt() <= 0 ) )
    return EGenericReqReply::BadRequest;

  if ( !ctx ) {
    SVC_LOG_ERR.Trace( "Guard ready: unknown user context. uid=%lld" );
    return EGenericReqReply::DoNothing;
  }

  if ( !ctx->HandleGuardReadyRequest() )
    return EGenericReqReply::DoNothing;

  return EGenericReqReply::ReplyMmid;
}


void AvgRRTimeReplyToJson(const socialLobby::TAvgRRTimes& avgTimes, Json::Value& modeTimes)
{
  socialLobby::TAvgRRTimes::const_iterator it_mode = avgTimes.begin();
  for( ; it_mode != avgTimes.end(); ++it_mode )
    modeTimes[ NI_STRFMT( "%d", it_mode->first ) ] = Json::Value(it_mode->second);
}

void AvgModeTimeReplyToJson(const socialLobby::TModeAvgTimes& avgTimes, Json::Value& jsonAvgTimes)
{
  socialLobby::TModeAvgTimes::const_iterator it_mode = avgTimes.begin();
  for( ; it_mode != avgTimes.end(); ++it_mode )
  {
    Json::Value javgTimes ( Json::objectValue );
    AvgRRTimeReplyToJson((*it_mode).second, javgTimes);
    jsonAvgTimes[NI_STRFMT( "%d", it_mode->first )] = javgTimes;
  }
}

void AvgTimeReplyToJson( const socialLobby::TBasketAvgTimes& avgTimes, Json::Value& jsonAvgTimes )
{
  socialLobby::TBasketAvgTimes::const_iterator it_basket = avgTimes.begin();
  for( ; it_basket != avgTimes.end(); ++it_basket )
  {
    Json::Value javgTimes ( Json::objectValue );
    AvgModeTimeReplyToJson(it_basket->second, javgTimes);
    jsonAvgTimes[(it_basket->first).c_str()] = javgTimes;
  }
}







void GatewayJsonHandler::HandleServerStatus( Json::Value & pvxReply, const Json::Value & request )
{
  NI_PROFILE_FUNCTION;

  Json::Value reqStatus = request.get("server_status", 0);
  if( reqStatus.asInt() )
  { 
    SVC_LOG_MSG.Trace( "Sending server status..." );

    // запрашиваем текущую статистику сервера
    if ( StrongMT<socialLobby::RISocialInterface> soclobby = SocLobbyThreadSafe() )
      soclobby->GetServerStatus( this, &GatewayJsonHandler::OnServerStatus );

    Json::Value status( Json::objectValue );

    {// забираем значения из кэша
      threading::MutexLock lock(mutex); 
      status["accept_timeout"] = lastServerStatus.acceptTimeout;
      status["average_mm_time"] = lastServerStatus.averageMmTime;

      Json::Value avgTimes ( Json::objectValue );
      AvgTimeReplyToJson(lastServerStatus.avgTimesPerMode, avgTimes);

      status["average_mm_time_ext"] = avgTimes;
      status["reconnect_timeout"] = lastServerStatus.reconnectTimeout;
      status["guard_lobby_timeout"] = lastServerStatus.guardLobbyTimeout;
      status["mm_debug_status"] = lastServerStatus.pvpMmDebugStatus.c_str();
    }

    pvxReply["server_status"] = status;

    SVC_LOG_MSG.Trace( "Server status sent" );
  }
}



void GatewayJsonHandler::OnServerStatus( socialLobby::SServerStatus result )
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_MSG.Trace( "Got server status update: accept TO %.1f, avg MM time %.1f, reconnect TO %.1f, guard TO %.1f, MM debug:\n%s", result.acceptTimeout, result.averageMmTime, result.reconnectTimeout, result.guardLobbyTimeout, result.pvpMmDebugStatus );

  threading::MutexLock lock(mutex); 
  lastServerStatus = result;
}



void GatewayJsonHandler::HandleForgeRoll( Json::Value & reply, const Json::Value & request )
{
  NI_PROFILE_FUNCTION;

  Json::Value reqObj = request.get("forge_roll", 0);
  if ( !reqObj.isArray() ) {
    reply = Json::Value( (int)0 );
    return;
  }

  for ( size_t i = 0; i < reqObj.size(); ++i )
  {
    Json::Value item = reqObj[i];
    if ( !item.isObject() ) {
      SVC_LOG_ERR.Trace( "Wrong json item fromat for forge roll" );
      continue;
    }

    std::string strUid = item["uid"].asString();
    std::string strRollId = item["roll_id"].asString();
    std::string strSessionRollData = item.get("session_roll", "").asString();

    roll::SForgeRollData data;

    data.uid = PingContext::StrToUid( strUid.c_str() );
    data.rollId = PingContext::StrToUid( strRollId.c_str() );
    data.count = item["count"].asInt();
    ParseTalentRollData( data.talentRollData, strSessionRollData );
    SVC_LOG_DBG.Trace( "Roll data: uid=%d, roll='%s'", data.uid, strSessionRollData );

    SVC_LOG_MSG.Trace( "Processing forge roll request: uid=%d, roll_id=%016x, count=%d, roll_table_size=%d", data.uid, data.rollId, data.count, data.talentRollData.rollTable.size() );

    threading::MutexLock lock( mutex ); 
    StrongMT<ForgeRollRequest> req = new ForgeRollRequest( data, rollBalancer );
    forgeRollRequests.push_back( req );
  }

  reply = Json::Value( (int)1 );
}

} // namespace HttpGateway
