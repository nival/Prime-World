#include "stdafx.h"
#include "TestSocialTransportHttp.h"
#include "TestSocialTransportHttpJob.h"
#include "TestSocialTransportHttpJson.h"


namespace GtcSocial
{

HttpTransport::HttpTransport( const SSocialConfig & socConfig ) :
_socConfig( socConfig )
{
  _job = new TransportHttpJob( socConfig );
  _thread = new threading::JobThread( _job, "HttpTransport" );
}



void HttpTransport::Poll()
{
  _job->Apply();
}



ITransportClient * HttpTransport::CreateClient( ITransportClientCallback * callback, socialLobby::TUId uid, const char * sessionId )
{
  StrongMT<HttpRequestContext> ctx = AllocateContext( uid, sessionId );
  return new HttpTransportClient( this, callback, ctx );
}



void HttpTransport::RequestServerStatus( ITransportCommonCallback * callback )
{
  _job->AddRequest( new HttpTransportServerStatusRequest( callback ) );
}



StrongMT<HttpRequestContext> HttpTransport::AllocateContext( socialLobby::TUId uid, const char * sessionId )
{
  StrongMT<HttpRequestContext> ctx = new HttpRequestContext( uid, sessionId );
  return ctx;
}










HttpTransportClient::HttpTransportClient( HttpTransport * transport, ITransportClientCallback * callback, HttpRequestContext * context ) :
_transport( transport ), _callback( callback ), _context( context )
{
}



bool HttpTransportClient::IsOk() const
{
  WeakMT<HttpTransport> transpCopy = _transport; //trick to pass by 'const'
  return transpCopy.Lock().Valid();
}



void HttpTransportClient::AddRequest( const socialLobby::SMatchmakingRequest & data )
{
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportAddRequest( lockedTr, lockedCb, _context, data ) );
}



void HttpTransportClient::PingMatchmaking() {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportPingRequest( lockedTr, lockedCb, _context ) );
}



void HttpTransportClient::CancelRequest() {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportCancelRequest( lockedTr, lockedCb, _context ) );
}



void HttpTransportClient::AcceptGameSession( const NCore::PlayerInfo & data ) {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportAcceptAndHeroChngRequests( lockedTr, lockedCb, _context, data, true ) );
}



void HttpTransportClient::ChangeGuardHero( const NCore::PlayerInfo & data ) {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportAcceptAndHeroChngRequests( lockedTr, lockedCb, _context, data, false ) );
}



void HttpTransportClient::GuardLobbyReady() {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportGuardReadyRequest( lockedTr, lockedCb, _context ) );
}



void HttpTransportClient::LeaveGame() {
  StrongMT<HttpTransport> lockedTr = _transport.Lock();
  StrongMT<ITransportClientCallback> lockedCb = _callback.Lock();
  NI_VERIFY( lockedTr.Valid() && lockedCb.Valid(), "", return );

  lockedTr->Job()->AddRequest( new HttpTransportLeaveRequest( lockedTr, lockedCb, _context ) );
}

} //namespace GtcSocial
