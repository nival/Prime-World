#include "stdafx.h"
#include "RdpTestServer.h"
#include "RdpTestSvClientCtx.h"
#include "RdpTestSvGame.h"
#include "System/InlineProfiler.h"


TestServer::TestServer( ni_udp::IRdp * _rdp, int _avgGameDuration ) :
rdp( _rdp ),
nextInstanceIdx( 1 ),
nextUid( 1 ),
nextGameId( 1 ),
avgGameDuration( _avgGameDuration ),
now( 0 )
{
}



bool TestServer::Init( int _listenMux )
{
  listenCtx = rdp->Listen( _listenMux, this );
  NI_VERIFY( listenCtx, "", return false );

  return true;
}



bool TestServer::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  {
    threading::MutexLock lock( timeMutex );
    now = _now;
  }

  {
    threading::MutexLock lock( newClientsMutex );
    clients.insert( clients.end(), newClients.begin(), newClients.end() );
    newClients.clear();
  }


  Clients newPl;
  {
    threading::MutexLock lock( newPlayersMutex );
    newPlayers.swap( newPl );
  }
  
  for ( Clients::iterator it = newPl.begin(); it != newPl.end(); ++it )
    AddPlayerToGame( *it, _now );

  for ( Games::iterator it = games.begin(); it != games.end(); )
    if ( (*it)->Poll( _now ) )
      ++it;
    else
    {
      MessageTrace( "Removing game. game_id=%d", (*it)->Id() );
      it = games.erase( it );
    }

  for ( Clients::iterator it = clients.begin(); it != clients.end(); )
    if ( (*it)->Poll( _now ) )
      ++it;
    else
    {
      MessageTrace( "Removing client context. inst=%d, uid=%d", (*it)->InstIdx(), (*it)->Uid() );
      it = clients.erase( it );
    }

  return true;
}



void TestServer::NewPlayer( TestClientContext * _ctx )
{
  threading::MutexLock lock( newPlayersMutex );
  newPlayers.push_back( _ctx );
}



timer::Time TestServer::SafeNow()
{
  threading::MutexLock lock( timeMutex );
  return now;
}



ni_udp::IRdpConnectionCallback * TestServer::OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr )
{
  StrongMT<TestClientContext> cl;
  {
    threading::MutexLock lock( newClientsMutex );

    cl = new TestClientContext( this, _conn, SafeNow(), nextInstanceIdx++, nextUid++ );
    newClients.push_back( cl );
  }

  return cl;
}



void TestServer::AddPlayerToGame( TestClientContext * _ctx, timer::Time _now )
{
  StrongMT<TestGame> game = newGame.Lock();
  if ( !game )
  {
    float r = 0.4 * ( (float)rand() / (float)RAND_MAX );
    int gameDur = (int)( avgGameDuration * ( 0.8 + r ) );

    game = new TestGame( nextGameId++, _now, gameDur );
    newGame = game;
    games.push_back( game );
  }

  game->AddPlayer( _ctx );

  if ( game->FullSize() >= 10 )
    newGame = 0;
}
