#pragma once

#include "TestSocialTransport.h"
#include "System/JobThread.h"
#include <string>

namespace Json
{
  class Value;
}


namespace GtcSocial
{

class TransportHttpJob;

typedef ni_detail::SInt64 TUid;


class HttpRequestContext : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( HttpRequestContext, BaseObjectMT );
public:
  HttpRequestContext( socialLobby::TUId uid, const char * sessionId ) :
  _uid( uid ),
  _uidStr( NStr::StrFmt( "%lld", uid ) ),
  _sessionId( sessionId )
  {}

  const std::string & Uid() const { return _uidStr; }
  const std::string & SessionId() const { return _sessionId; }

private:
  const socialLobby::TUId   _uid;
  const std::string         _uidStr;
  const std::string         _sessionId;
};




class HttpTransport : public ITransport, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransport, ITransport, BaseObjectMT );

public:
  HttpTransport( const SSocialConfig & socConfig );

  virtual void Poll();
  virtual bool IsReady() const { return true; }
  virtual ITransportClient * CreateClient( ITransportClientCallback * callback, socialLobby::TUId uid, const char * sessionId );
  virtual void RequestServerStatus( ITransportCommonCallback * callback );

  TransportHttpJob * Job() { return _job; }

  StrongMT<HttpRequestContext> AllocateContext( socialLobby::TUId uid, const char * sessionId );

private:
  const SSocialConfig _socConfig;
  StrongMT<TransportHttpJob> _job;
  StrongMT<threading::JobThread> _thread;
};






class HttpTransportClient : public ITransportClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HttpTransportClient, ITransportClient, BaseObjectMT );

public:
  HttpTransportClient( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context );

  virtual void Poll() {}
  virtual bool IsOk() const;

  virtual void AddRequest( const socialLobby::SMatchmakingRequest & data );
  virtual void PingMatchmaking();
  virtual void CancelRequest();
  virtual void AcceptGameSession( const NCore::PlayerInfo & data );
  virtual void ChangeGuardHero( const NCore::PlayerInfo & data );
  virtual void GuardLobbyReady();
  virtual void LeaveGame();

private:
  WeakMT<HttpTransport> _transport;
  WeakMT<ITransportClientCallback> _callback;
  StrongMT<HttpRequestContext> _context;
};

} //namespace GtcSocial
