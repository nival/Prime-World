#include "stdafx.h"
#include "RdpTestSvGame.h"
#include "RdpTestSvClientCtx.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( TestGame );


TestGame::TestGame( int _id, timer::Time _now, int _gameDuration ) :
id( _id ),
now( _now ),
currentStep( 0 ),
gameDuration( _gameDuration ),
nextStepTime( _now )
{
}


void TestGame::AddPlayer( TestClientContext * _ctx )
{
  newPlayers.push_back( _ctx );
}



void TestGame::OnClientStep( int _uid, int _step )
{
  threading::MutexLock lock( mutex );

  Players::iterator it = players.find( _uid );
  NI_VERIFY( it != players.end(), "", return );

  timer::Time rtt = 0;
  if ( _step <= currentStep )
  {
    rtt = ( currentStep - _step ) * 0.1;
    rtt += now - ( nextStepTime - 0.1 );
  }

  if ( _step == currentStep )
  {
    it->second.stepAcked = true;
    DebugTrace( "Got client step. game_id=%d, step=%d, uid=%d, rtt=%.1f", id, currentStep, _uid, 1e3 * rtt );
  }
  else if ( _step < currentStep )
    WarningTrace( "Lost client step. game_id=%d, step=%d, client_step=%d, uid=%d, rtt=%.1f", id, currentStep, _step, _uid, 1e3 * rtt );
  else if ( _step > currentStep )
    ErrorTrace( "Wrong client step. game_id=%d, step=%d, uid=%d, client_step=%d", id, currentStep, _uid, _step );
}



bool TestGame::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  now = _now;

  if ( _now > nextStepTime )
    Step( _now );

  return !players.empty() || !newPlayers.empty();
}



void TestGame::Step( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  ++currentStep;

  if ( currentStep > gameDuration )
  {
    FinishGame();
    return;
  }

  int missed = CountStepMisses();

  if ( missed )
    WarningTrace( "Game step, missing acks. game_id=%d, step=%d, missing=%d", id, currentStep, missed );
  else
    DebugTrace( "Game step. game_id=%d, step=%d, players=%d, new_players=%d", id, currentStep, players.size(), newPlayers.size() );

  for ( PlayerList::iterator it = newPlayers.begin(); it != newPlayers.end(); ++it )
    if ( StrongMT<TestClientContext> ctx = it->Lock() )
    {
      ctx->AddToGame( this );
      ctx->SendStartGame( id );

      Player & slot = players[ctx->Uid()];
      slot.ctx = ctx;
    }
  newPlayers.clear();

  for ( Players::iterator it = players.begin(); it != players.end(); )
    if ( StrongMT<TestClientContext> ctx = it->second.ctx.Lock() )
    {
      it->second.stepAcked = false;
      ctx->GameStep( currentStep );
      ++it;
    }
    else
      it = players.erase( it );

  nextStepTime += 0.1;
}



void TestGame::FinishGame()
{
  MessageTrace( "Game finished. game_id=%d, step=%d", id, currentStep );

  for ( PlayerList::iterator it = newPlayers.begin(); it != newPlayers.end(); ++it )
    if ( StrongMT<TestClientContext> ctx = it->Lock() )
      ctx->FinishGame( currentStep );

  for ( Players::iterator it = players.begin(); it != players.end(); ++it )
    if ( StrongMT<TestClientContext> ctx = it->second.ctx.Lock() )
      ctx->FinishGame( currentStep );

  newPlayers.clear();
  players.clear();
}



int TestGame::CountStepMisses()
{
  int missed = 0;
  for ( Players::iterator it = players.begin(); it != players.end(); ++it )
    if ( !it->second.stepAcked )
      ++missed;
  return missed;
}
