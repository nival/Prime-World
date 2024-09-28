#pragma once

#include "TestSocialTransport.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "rpc/IfaceRequester.h"

namespace rpc
{
  class GateKeeperClient;
}


namespace GtcSocial
{

class TestSocialTransportRpc : public ITransport, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestSocialTransportRpc, ITransport, BaseObjectMT );

public:
  TestSocialTransportRpc( rpc::GateKeeperClient * gk )
  {
    _socLobby = new rpc::IfaceRequester<socialLobby::RISocialInterface>;
    _socLobby->init( gk, socialLobby::serviceIds::Service, socialLobby::serviceIds::SocialInterface );
  }

  virtual void Poll() {
    _socLobby->step();
  }

  virtual bool IsReady() const {
    return _socLobby->isopen();
  }

  virtual ITransportClient * CreateClient( ITransportClientCallback * callback, socialLobby::TUId uid, const char * sessionId );

  virtual void RequestServerStatus( ITransportCommonCallback * callback ) {
    StrongMT<ITransportCommonCallback> cbPtr( callback );
    _socLobby->iface()->GetServerStatus( this, &TestSocialTransportRpc::OnServerStatus, cbPtr );
  }

private:
  StrongMT<rpc::IfaceRequester<socialLobby::RISocialInterface>> _socLobby;

  void OnServerStatus( socialLobby::SServerStatus status, StrongMT<ITransportCommonCallback> callback, rpc::CallStatus rpcStatus ) {
    if ( ( rpcStatus == rpc::CallSuccessful ) && callback )
      callback->OnServerStatus( status );
  }
};



class TestSocialTransportClientRpc : public ITransportClient, public socialLobby::INotify, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( TestSocialTransportClientRpc, ITransportClient, socialLobby::INotify, BaseObjectMT );

public:
  TestSocialTransportClientRpc( ITransportClientCallback * callback, socialLobby::RISocialInterface * socLobby, socialLobby::TUId uid ) :
  _callback( callback ), _socLobby( socLobby ),
  _uid( uid )
  {}

  virtual void Poll() {}
  virtual bool IsOk() const {
    if ( !_socLobby )
      return false;
    return ( _socLobby->GetStatus() == rpc::Connected ) || ( _socLobby->GetStatus() == rpc::Connecting );
  }

  virtual void AddRequest( const socialLobby::SMatchmakingRequest & data ) {
    NI_ASSERT( _uid == data.uid, "" );
    _socLobby->AddRequest( data, this );
  }

  virtual void PingMatchmaking() { /*Do nothing*/ }

  virtual void CancelRequest() {
    NI_VERIFY( _uid, "", return );
    NI_VERIFY( _socUserCtx, "", return );
    _socUserCtx->CancelRequest();
  }

  virtual void AcceptGameSession( const NCore::PlayerInfo & data ) {
    NI_VERIFY( _uid, "", return );
    NI_VERIFY( _socUserCtx, "", return );

    _socUserCtx->AcceptGameSession( socialLobby::SPlayerData( data ) );
  }


  virtual void ChangeGuardHero( const NCore::PlayerInfo & data ) {
    NI_VERIFY( _uid, "", return );
    NI_VERIFY( _socUserCtx, "", return );

    _socUserCtx->ChangeGuardHero( socialLobby::SPlayerData( data ) );
  }


  virtual void GuardLobbyReady() {
    NI_VERIFY( _uid, "", return );
    NI_VERIFY( _socUserCtx, "", return );

    _socUserCtx->GuardReady();
  }


  virtual void LeaveGame() {
    NI_VERIFY( _uid, "", return );
    NI_VERIFY( _socUserCtx, "", return );
    _socUserCtx->LeaveGame();
  }

  //socialLobby::INotify
  virtual void Open( socialLobby::IUserContext * _ctx ) {
    _socUserCtx = _ctx;

    if ( StrongMT<ITransportClientCallback> locked = _callback.Lock() )
      locked->OnAddRequest();
  }

  virtual void Failure() {
    _socUserCtx = 0;
  }

  virtual void UpdateStatus( const socialLobby::SMatchmakingStatus & _status ) {
    if ( StrongMT<ITransportClientCallback> locked = _callback.Lock() )
      locked->OnPing( _status );
  }

  virtual void Close() {
    _socUserCtx = 0;
  }

private:
  StrongMT<socialLobby::RISocialInterface> _socLobby;
  StrongMT<socialLobby::IUserContext> _socUserCtx;
  WeakMT<ITransportClientCallback> _callback;
  socialLobby::TUId _uid;
};


inline ITransportClient * TestSocialTransportRpc::CreateClient( ITransportClientCallback * callback, socialLobby::TUId uid, const char * sessionId )
{
  return new TestSocialTransportClientRpc( callback, _socLobby->iface(), uid );
}

} //namespace GtcSocial
