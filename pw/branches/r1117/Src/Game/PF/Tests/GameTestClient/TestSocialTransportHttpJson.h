#pragma once

#include "TestSocialTransportHttpJob.h"
#include <json/reader.h>
#include <json/writer.h>


namespace GtcSocial
{

class JsonRequestBaseClientItem : public IJsonRequestItem, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( JsonRequestBaseClientItem, IJsonRequestItem, BaseObjectMT );

public:
  JsonRequestBaseClientItem( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
  _callback( callback ), _transport( transport ), _context( context )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) = 0;
  virtual bool ParseJsonBack( const Json::Value & answerRoot ) { return true; }
  virtual void Apply() {}
  virtual void Failed() {}

protected:
  WeakMT<ITransportClientCallback>  _callback;
  WeakMT<HttpTransport>             _transport;
  StrongMT<HttpRequestContext>      _context;

  string StringFromJsonArr( const Json::Value & arr, unsigned idx, const string & defaultStr = string() ) {
    if ( !arr.isArray() )
      return defaultStr;
    Json::Value val = arr.get( (Json::UInt)idx, Json::Value() );
    if ( !val.isString() )
      return defaultStr;
    return val.asString().c_str();
  }

  int IntFromJsonArr( const Json::Value & arr, unsigned idx, int defaultInt = 0 ) {
    if ( !arr.isArray() )
      return defaultInt;
    Json::Value val = arr.get( (Json::UInt)idx, Json::Value() );
    if ( !val.isNumeric() )
      return defaultInt;
    return val.asInt();
  }
};





class HttpTransportAddRequest : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportAddRequest, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportAddRequest( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context, const socialLobby::SMatchmakingRequest & data ) :
  JsonRequestBaseClientItem( transport, callback, context ), _data( data )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    //Do some data pre-conversion
    string utf8nick;
    NStr::UnicodeToUTF8( &utf8nick, _data.nickname );

    std::string partyLineup;
    partyLineup.reserve( _data.partyLineup.size() * 8 );
    for ( int i = 0; i < _data.partyLineup.size(); ++i )
      partyLineup += NStr::StrFmt( "%s%u", i ? "," : "", _data.partyLineup[i] );

    const char * winLoseHist[] = { "", "00", "11", "10", "01", "0000", "000000" };
    const size_t winLoseHistLen = sizeof(winLoseHist) / sizeof(const char*);

    //Format json
    Json::Value item;
    item["mmid"]            = _data.sessionContextId.c_str();
    item["fraction"]        = (int)_data.faction;
    item["game_type"]       = _data.map.c_str();
    item["hero"]            = _data.heroId.c_str();
    item["sex"]             = (int)_data.zzimaSex;
    item["client_revn"]     = _data.clientRevision;
    item["lord_status"]     = _data.basket;
    item["guard_rating"]    = _data.guardRating;
    item["lord_rating"]     = _data.playerRating;
    item["hero_rating"]     = _data.heroRating;
    item["lord_wins"]       = _data.totalWins;
    item["force"]           = _data.force;
    item["avatarLevel"]     = _data.fameLevel;
    item["locale"]          = _data.geoInfo.locale.c_str();

    Json::Value pings;
    for ( int i = 0; i < _data.geoInfo.pings.size(); ++i ) {
      string cluster = _data.geoInfo.pings[i].clusterId;
      int ping = _data.geoInfo.pings[i].ping;
      pings[cluster.c_str()] = ping;
    }
    item["geolocation"]     = _data.geoInfo.location.c_str();
    item["pings"]           = pings;

    item["zz_login"]        = _data.login.c_str();
    item["zz_uid"]          = (int)_data.userIdPvx;
    item["party_id"]        = NI_STRFMT( "%lld", _data.partyId );
    item["party_auids"]     = partyLineup;
    item["enemy_auids"]     = "";
    item["nick"]            = utf8nick.c_str();
    item["win_lose_hist"]   = winLoseHist[_data.uid % winLoseHistLen];

    //put record in request
    requestRoot["add"][_context->Uid()] = item;
  }

  virtual void Apply() {
    if ( StrongMT<ITransportClientCallback> locked = _callback.Lock() )
      locked->OnAddRequest();
  }

private:
  socialLobby::SMatchmakingRequest _data;
};



inline socialLobby::TUId StrToUid( const char * str )
{
  return _atoi64( str );
}



class HttpTransportPingRequest : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportPingRequest, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportPingRequest( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
  JsonRequestBaseClientItem( transport, callback, context ),
  _gotPing( false )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    requestRoot["ping"][_context->Uid()] = (int)1;
  }

  virtual bool ParseJsonBack( const Json::Value & answerRoot )
  {
    Json::Value ping = answerRoot["ping"][_context->Uid()];

    if ( ping.isNumeric() && ( ping.asInt() == 0 ) )  {
      _ping.progress = socialLobby::ERequestStatus::Null;
      _gotPing = true;
      return true;
    }

    if ( ping.type() != Json::arrayValue ) //NEVER ever use 'isArray()' here!!
      return false;

    _ping.progress          = (socialLobby::ERequestStatus::Enum)IntFromJsonArr( ping, 0 );
    _ping.pvxSessionKey     = StringFromJsonArr( ping, 1 );
    _ping.requestsAccepted  = IntFromJsonArr( ping, 2 );
    _ping.totalPlayers      = IntFromJsonArr( ping, 3 );
    _ping.debugInfo         = StringFromJsonArr( ping, 4 );
    ParseGameResults( ping.get( (Json::UInt)5, Json::Value() ) );
    _ping.gameId = _atoi64( StringFromJsonArr( ping, 6 ).c_str() );
    _ping.sessionContextId = StringFromJsonArr( ping, 7 );
    ParseGuardLobby( ping.get( (Json::UInt)9, Json::Value() ) );
    _gotPing = true;
    return true;
  }

  virtual void Apply() {
    if ( _gotPing )
    if ( StrongMT<ITransportClientCallback> locked = _callback.Lock() )
      locked->OnPing( _ping );
  }

private:
  bool _gotPing;
  socialLobby::SMatchmakingStatus _ping;

  inline void ParseGameResults( const Json::Value & value ) {
    if ( !value.isObject() )
      return;
    _ping.gameResults.winner = (lobby::ETeam::Enum)value["victoriousFaction"].asInt();
    _ping.gameResults.playerIsLeaver = value["playerIsLeaver"].asInt();
  }

  inline void ParseGuardLobby( const Json::Value & value ) {
    _ping.gameBasket = mmaking::EBasket::Normal;

    if ( !value.isObject() )
      return;

    _ping.preGameLobbyInfo.foesReady = (int)value["foes_rdy"].asInt();

    Json::Value allies = value["allies"];
    if ( allies.type() == Json::arrayValue )
      for ( Json::UInt i = 0; i < allies.size(); ++i ) {
        Json::Value item = allies.get( (Json::UInt)i, Json::Value() );
        if ( !item.isObject() )
          continue;

        socialLobby::SAllyStatus ally;
        ally.uid = StrToUid( item["uid"].asString().c_str() );
        ally.ready = item["rdy"].asInt() ? true : false;
        _ping.preGameLobbyInfo.allies.push_back( ally );
      }
  }
};


static Json::Value RollItems2Json( const vector<NCore::TalentRollItem>& rollItems )
{
  Json::Value jsonRollList( Json::arrayValue );
  for ( int i = 0; i < rollItems.size(); ++i )
  {
    Json::Value item( Json::objectValue );
    const NCore::TalentRollItem& talentRollItem = rollItems[i];
    item["dbid"] = talentRollItem.dbid;
    item["probability"] = talentRollItem.probability;
    jsonRollList.append( item );
  }
  return jsonRollList;
}


static Json::Value RollTable2JsonConverter( const NCore::TalentRollData & rollData )
{
  Json::Value jsonRollData( Json::objectValue );

  jsonRollData["gen_index"] = (int)rollData.generationIndex;

  const NCore::TTalentRollTable& rollTable = rollData.rollTable;

  for ( NCore::TTalentRollTable::const_iterator it = rollTable.begin(); it != rollTable.end(); ++it )
  {
    const NCore::TalentRollItems & talentRollItems = it->second;

    Json::Value jsonRollTableObj( Json::objectValue );
    jsonRollTableObj["version"] = talentRollItems.version;
    jsonRollTableObj["db_version"] = talentRollItems.dbVersion;

    Json::Value itemsListObj( Json::objectValue );
    itemsListObj["items"] = RollItems2Json( talentRollItems.defaultItems );
    jsonRollTableObj["default"] = itemsListObj;
    itemsListObj["items"] = RollItems2Json( talentRollItems.premiumItems );
    jsonRollTableObj["premium"] = itemsListObj;

    jsonRollData[(it->first).c_str()] = jsonRollTableObj;
  }
  return jsonRollData;
}



inline void PlayerDataToJson( Json::Value & value, const NCore::PlayerInfo & data )
{
  value["hid"] =            (int)data.heroId; //IMPORTANT! It just HAVE TO be signed value
  value["energy"] =         data.heroEnergy;
  value["avatarLevel"] =    data.avatarLevel;
  value["heroLevel"] =      data.heroLevel;
  value["guardRating"] =    data.guardRating;
  value["lordRating"] =     data.playerRating;
  value["heroRating"] =     data.heroRating;
  value["heroExp"] =        data.heroExp;
  value["hsHealth"] =       data.hsHealth;
  value["hsMana"] =         data.hsMana;
  value["hsStrength"] =     data.hsStrength;
  value["hsIntellect"] =    data.hsIntellect;
  value["hsAgility"] =      data.hsAgility;
  value["hsCunning"] =      data.hsCunning;
  value["hsFortitude"] =    data.hsFortitude;
  value["hsWill"] =         data.hsWill;
  value["dropRate"] =       data.dropRate;
  value["hasPremium"] =     data.hasPremium ? 1 : 0;
  value["lord_status"] =    (int)data.basket;
  value["firstWin"] =       data.fwod;
  value["flag_id"] =        data.flagId.c_str();

  Json::Value talents;
  for ( NCore::PlayerTalentSet::const_iterator it = data.talents.begin(); it != data.talents.end(); ++it ) {
    int slotId = it->first;
    const NCore::TalentInfo & srcTalent = it->second;

    std::string key = NStr::StrFmt( "%d", slotId );
    Json::Value talent;
    talent["id"] = (Json::Int)srcTalent.id;
    talent["rr"] = (Json::Int)srcTalent.refineRate;
    talent["ab"] = (Json::Int)srcTalent.actionBarIdx;
    talents[key] = talent;
  }

  value["ts"] = talents;

  // Roll data stuff
  Json::Value talentRollData;
  talentRollData["rollTable"] = RollTable2JsonConverter( data.talentRollData );

  std::string strTalentRollData = (Json::FastWriter()).write( talentRollData );
  // End of roll stat stuff

  value["session_roll"] = strTalentRollData;

  Json::Value inventory( Json::arrayValue );
  for ( int i = 0; i < data.inventory.size(); ++i )
    inventory.append( data.inventory[i] );
  value["inventory"] = inventory;

  Json::Value friends( Json::arrayValue );
  for ( int i = 0; i < data.friends.size(); ++i )
    friends.append( data.friends[i] );
  value["friends"] = friends;
}



class HttpTransportAcceptAndHeroChngRequests : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportAcceptAndHeroChngRequests, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportAcceptAndHeroChngRequests( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context, const NCore::PlayerInfo & data, bool acceptMode ) :
  JsonRequestBaseClientItem( transport, callback, context ),
  _data( data ),
  _acceptMode( acceptMode )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    Json::Value value;
    PlayerDataToJson( value, _data );
    const char * reqName = _acceptMode ? "accept" : "change_hero";
    requestRoot[reqName][_context->Uid()] = value;
  }

  virtual bool ParseJsonBack( const Json::Value & answerRoot ) {
    const char * reqName = _acceptMode ? "accept" : "change_hero";
    Json::Value answer = answerRoot[reqName][_context->Uid()];
    return answer.isString() && ( answer.asString() == _context->SessionId() );
  }

  virtual void Apply() {
  }

private:
  const NCore::PlayerInfo _data;
  const bool _acceptMode;
};



class HttpTransportGuardReadyRequest : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportGuardReadyRequest, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportGuardReadyRequest( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
  JsonRequestBaseClientItem( transport, callback, context )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    requestRoot["ready"][_context->Uid()] = (int)1;
  }
};




class HttpTransportCancelRequest : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportCancelRequest, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportCancelRequest( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
  JsonRequestBaseClientItem( transport, callback, context )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    requestRoot["cancel"][_context->Uid()] = (int)1;
  }
};




class HttpTransportLeaveRequest : public JsonRequestBaseClientItem
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportLeaveRequest, JsonRequestBaseClientItem, BaseObjectMT );
public:
  HttpTransportLeaveRequest( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
  JsonRequestBaseClientItem( transport, callback, context )
  {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    requestRoot["leave"][_context->Uid()] = (int)1;
  }
};




class HttpTransportServerStatusRequest : public IJsonRequestItem, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportServerStatusRequest, IJsonRequestItem, BaseObjectMT );

public:
  HttpTransportServerStatusRequest( ITransportCommonCallback * callback ) : _callback( callback ) {}

  virtual void DoIntoJson( Json::Value & requestRoot ) {
    requestRoot["server_status"] = 1;
  }

  virtual bool ParseJsonBack( const Json::Value & answerRoot ) {
    const Json::Value & st = answerRoot["server_status"];
    _data.acceptTimeout = st["accept_timeout"].asDouble();
    _data.averageMmTime = st["average_mm_time"].asDouble();
    _data.reconnectTimeout = st["reconnect_timeout"].asDouble();
    _data.reconnectTimeout = st["guard_lobby_timeout"].asDouble();
    _data.pvpMmDebugStatus = st["mm_debug_status"].asString().c_str();
    return true;
  }

  virtual void Apply() {
    if ( StrongMT<ITransportCommonCallback> locked = _callback.Lock() )
      locked->OnServerStatus( _data );
  }

  virtual void Failed() {}

private:
  WeakMT<ITransportCommonCallback> _callback;
  socialLobby::SServerStatus _data;
};

} //namespace GtcSocial
