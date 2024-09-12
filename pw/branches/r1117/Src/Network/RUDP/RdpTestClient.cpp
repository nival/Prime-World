#include "stdafx.h"
#include "RdpTestClient.h"
#include "System/InlineProfiler.h"


RdpTestClient::RdpTestClient( ni_udp::IRdp * _rdp, timer::Time _now, int _instanceIdx, timer::Time _spontaneousDisconnectTime ) :
RdpTestObject( _now, _instanceIdx, 0 ),
rdp( _rdp ),
stepTime( 0 ),
gameId( 0 ),
stepIndex( 0 ),
stepNeedsTobeSent( false ),
spontaneousDisconnectTime( ( _spontaneousDisconnectTime >= 0 ) ? ( _now + _spontaneousDisconnectTime ) : -1.0 )
{
}



bool RdpTestClient::Init( const ni_udp::NetAddr & _serverIpAddr, int _serverMuxIdx )
{
  MessageTrace( "Ñlient started. inst=%d", InstIdx() );

  conn = rdp->Connect( _serverIpAddr, _serverMuxIdx, this );
  NI_VERIFY( conn, "", return false );
  StartTimer( 10.0, "connection" );
  return true;
}



void RdpTestClient::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "Ñlient connected to server. inst=%d", InstIdx() );

  threading::MutexLock lock( mutex );

  NI_VERIFY( State() == ETestObjectState::Init, "", Fail(); return );

  StopTimer();

  Switch( ETestObjectState::Handshake );
  StartTimer( 10.0, "handshake" );
  conn->SendDatagram( "hello 0", 8 );
}



void RdpTestClient::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( mutex );
  if ( State() == ETestObjectState::Closing )
    Fail();
  else
    Switch( ETestObjectState::Finished );
}



void RdpTestClient::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( mutex );
  Fail();
}



void RdpTestClient::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( State() == ETestObjectState::Handshake )
    ProcessHandshake( _data, _size );
  else
    ProcessCommand( _data, _size );
}



bool RdpTestClient::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( !RdpTestObject::Poll( _now ) )
    return false;

  if ( spontaneousDisconnectTime >= 0 )
    if ( _now > spontaneousDisconnectTime )
    {
      MessageTrace( "Disconnecting from server. inst=%d, uid=%d, game_id=%d", InstIdx(), Uid(), gameId );
      conn->Close();
      Switch( ETestObjectState::Finished );
      return false;
    }

  if ( stepIndex )
    if ( stepNeedsTobeSent )
    {
      std::string msg = NI_STRFMT( "client_step %d", stepIndex );
      conn->SendDatagram( msg.c_str(), msg.size() + 1 );
      stepNeedsTobeSent = false;

      DebugTrace( "Client step ack sent. inst=%d, uid=%d, game_id=%d, step=%d", InstIdx(), Uid(), gameId, stepIndex );
    }

  return true;
}



void RdpTestClient::ProcessHandshake( const void * _data, size_t _size )
{
  int userid = 0;
  if ( ParseCmd( _data, _size, "welcome", userid ) )
  {
    MessageTrace( "Got server ack. inst=%d, uid=%d", InstIdx(), userid );
    SetUid( userid );
    StopTimer();
    Switch( ETestObjectState::Active );
    return;
  }

  ErrorTrace( "Wrong hello ack" );
  Fail();
}



void RdpTestClient::ProcessCommand( const void * _data, size_t _size )
{
  int arg = 0;
  if ( ParseCmd( _data, _size, "start", arg ) )
    ProcessStart( arg );
  else if ( ParseCmd( _data, _size, "step", arg ) )
    ProcessStep( arg );
  else if ( ParseCmd( _data, _size, "finish", arg ) )
    ProcessFinish( arg );
  else
  {
    ErrorTrace( "Wrong command. inst=%d", InstIdx() );
    Fail();
  }
}



void RdpTestClient::ProcessStart( int _gameid )
{
  if ( gameId || !_gameid )
  {
    ErrorTrace( "Wrong start command. inst=%d, uid=%d", InstIdx(), Uid() );
    Fail();
    return;
  }

  gameId = _gameid;
  MessageTrace( "Starting game. inst=%d, uid=%d, game_id=%d, time=%.3f", InstIdx(), Uid(), gameId, Now() );
  StartTimer( 10.0, "start_game" );
}



void RdpTestClient::ProcessStep( int _step )
{
  if ( !gameId || !_step )
  {
    ErrorTrace( "Wrong step command. inst=%d, uid=%d, game_id=%d", InstIdx(), Uid(), gameId );
    Fail();
    return;
  }

  if ( !stepIndex )
  {
    MessageTrace( "Got first step. inst=%d, uid=%d, game_id=%d, step=%d", InstIdx(), Uid(), gameId, _step );
    StopTimer();
    stepTime = Now();
  }
  else
  {
    if ( _step != stepIndex + 1 )
    {
      ErrorTrace( "Invalid step index. inst=%d, step=%d, expected=%d", InstIdx(), _step, stepIndex + 1 );
      Fail();
      return;
    }

    stepTime += 0.1;
    timer::Time delta = Now() - stepTime;
    if ( fabs( delta ) > 5e-3 )
    {
      timer::Time correction = delta / 33.0;
      correction = Clamp( correction, -0.005, +0.005 );
      WarningTrace( "Step time out of limit. delta=%.1f, correction=%.1f, step=%d, inst=%d, uid=%d", 1e3 * delta, 1e3 * correction, _step, InstIdx(), Uid() );
      stepTime += correction;
    }
    else
      DebugTrace( "Got server step. delta=%.1f, step=%d, inst=%d, uid=%d", 1e3 * delta, _step, InstIdx(), Uid() );
  }

  stepIndex = _step;
  stepNeedsTobeSent = true;
  return;
}



void RdpTestClient::ProcessFinish( int _step )
{
  MessageTrace( "Got finish game. inst=%d, uid=%d, game_id=%d, step=%d, finish_step=%d", InstIdx(), Uid(), gameId, stepIndex, _step );

  conn->Close();
  Switch( ETestObjectState::Finished );
}
