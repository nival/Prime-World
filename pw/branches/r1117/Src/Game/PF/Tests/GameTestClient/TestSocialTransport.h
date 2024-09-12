#pragma once

#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "Core/GameTypes.h"

namespace GtcSocial
{

struct SSocialConfig
{
  string                map;
  float                 spawnRate;
  int                   minPartySize, maxPartySize;
  float                 partyFrequency;
  vector<string>        botLocales, botLocations;
  bool                  dumpJson;
  bool                  prettyJson;
  int                   jsonItemsPerRequest;
  string                gatewayUrl;
  float                 defaultTimeout;
  float                 pingInterval;
  bool                  uidReUse; //TODO

  SSocialConfig() :
  map(),
  spawnRate( 10.0f ),
  minPartySize( 2 ), maxPartySize( 5 ),
  partyFrequency( 0.0f ),
  dumpJson( false ),
  prettyJson( false ),
  jsonItemsPerRequest( 0 ),
  gatewayUrl(),
  defaultTimeout( 30.0f ),
  pingInterval( 1.5f ),
  uidReUse( false )
  {
    botLocales.push_back( "ru" );
    botLocations.push_back( "ru0" );
  }
};



class ITransportClient;
class ITransportCommonCallback;
class ITransportClientCallback;



class ITransport : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITransport, IBaseInterfaceMT );

public:
  virtual void Poll() = 0;
  virtual bool IsReady() const = 0;
  virtual ITransportClient * CreateClient( ITransportClientCallback * callback, socialLobby::TUId uid, const char * sessionId ) = 0;
  virtual void RequestServerStatus( ITransportCommonCallback * callback ) = 0;
};



class ITransportClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITransportClient, IBaseInterfaceMT );

public:
  virtual void Poll() = 0;
  virtual bool IsOk() const = 0;

  virtual void AddRequest( const socialLobby::SMatchmakingRequest & data ) = 0;
  virtual void PingMatchmaking() = 0;
  virtual void CancelRequest() = 0;
  virtual void AcceptGameSession( const NCore::PlayerInfo & data ) = 0;
  virtual void ChangeGuardHero( const NCore::PlayerInfo & data ) = 0;
  virtual void GuardLobbyReady() = 0;
  virtual void LeaveGame() = 0;
};



class ITransportCommonCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITransportCommonCallback, IBaseInterfaceMT );

public:
  virtual void OnServerStatus( const socialLobby::SServerStatus & status ) = 0;
};



class ITransportClientCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITransportClientCallback, IBaseInterfaceMT );

public:
  virtual void OnAddRequest() = 0;
  virtual void OnPing( const socialLobby::SMatchmakingStatus & result ) = 0;
};

} //namespace GtcSocial
