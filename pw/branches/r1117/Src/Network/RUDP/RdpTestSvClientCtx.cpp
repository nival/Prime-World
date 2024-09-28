#include "stdafx.h"
#include "RdpTestSvClientCtx.h"
#include "RdpTestServer.h"
#include "RdpTestSvGame.h"
#include "System/InlineProfiler.h"

NI_DEFINE_REFCOUNT( TestClientContext );


TestClientContext::TestClientContext( TestServer * _srv, ni_udp::IRdpConnection * _conn, timer::Time _now, int _instanceIdx, int _uid ) :
RdpTestObject( _now, _instanceIdx, _uid ),
server( _srv ),
conn( _conn )
{
  StartTimer( 10.0, "handshake" );
  Switch( ETestObjectState::Handshake );
}



void TestClientContext::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( mutex );
  if ( State() == ETestObjectState::Closing )
    Fail();
  else
    Switch( ETestObjectState::Finished );
}



void TestClientContext::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( mutex );
  Fail();
}



void TestClientContext::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( State() == ETestObjectState::Handshake )
  {
    ProcessHandshake( _data, _size );
    return;
  }
  else if ( State() == ETestObjectState::Active )
  {
    ProcessClientStep( _data, _size );
    return;
  }
  else
  {
    Fail();
  }
}



void TestClientContext::ProcessHandshake( const void * _data, size_t _size )
{
  int clVer = 0;
  if ( ParseCmd( _data, _size, "hello", clVer ) )
  {
    MessageTrace( "Got hello handshake. uid=%d", Uid() );
    StopTimer();

    string reply = NI_STRFMT( "welcome %d", Uid() );
    conn->SendDatagram( reply.c_str(), reply.size() + 1 );

    Switch( ETestObjectState::Active );
    if ( StrongMT<TestServer> locked = server.Lock() )
      locked->NewPlayer( this );
    return;
  }

  ErrorTrace( "Wrong hello ack. uid=%d", Uid() );
  Fail();
}



void TestClientContext::ProcessClientStep( const void * _data, size_t _size )
{
  int step = 0;
  if ( ParseCmd( _data, _size, "client_step", step ) )
  {
    StrongMT<TestGame> lockedGame = game.Lock();
    if ( !lockedGame )
    {
      ErrorTrace( "Got client step but got no game. uid=%d, step=%d", Uid(), step );
      Fail();
      return;
    }

    lockedGame->OnClientStep( Uid(), step );
    return;
  }

  ErrorTrace( "Wrong step packet. uid=%d", Uid() );
  Fail();
}



void TestClientContext::AddToGame( TestGame * _game )
{
  threading::MutexLock lock( mutex );

  NI_ASSERT( !game.Lock(), "" );

  game = _game;
}



void TestClientContext::SendStartGame( int _gameId )
{
  string msg = NI_STRFMT( "start %d", _gameId );
  conn->SendDatagram( msg.c_str(), msg.size() + 1 );
}



bool TestClientContext::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( !RdpTestObject::Poll( _now ) )
    return false;

  return true;
}



void TestClientContext::GameStep( int _stepIndex )
{
  MessageTrace( "Sending server step. uid=%d, step=%d", Uid(), _stepIndex );

  string msg = NI_STRFMT( "step %d", _stepIndex );
  conn->SendDatagram( msg.c_str(), msg.size() + 1 );
}



void TestClientContext::FinishGame( int _stepIndex )
{
  string msg = NI_STRFMT( "finish %d", _stepIndex );
  conn->SendDatagram( msg.c_str(), msg.size() + 1 );

  conn->Close();

  Switch( ETestObjectState::Finished );
}
