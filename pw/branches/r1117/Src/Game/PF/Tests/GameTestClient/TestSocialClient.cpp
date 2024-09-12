#include "stdafx.h"
#include "TestSocialClient.h"
#include "System/Crc32Checksum.h"
#include "System/InlineProfiler.h"


namespace GtcSocial
{

template <typename TENUM, TENUM DFLT>
class StaticSet {
  const static int maxSz = 8;
  TENUM states[maxSz];
  int count;
public:
  StaticSet() : count( 0 ) { std::fill( states, states + maxSz, DFLT ); }

  void Add( const TENUM _st ) { NI_VERIFY( count < maxSz, "", return ); states[count++] = _st; }

  string Str() const {
    string tmp;
    tmp.reserve( 128 );
    if ( count > 1 ) tmp += "( ";
    for ( int i = 0; i < count; ++i ) {
      if ( i ) tmp += ", ";
      tmp += ToString( states[i] ); }
    if ( count > 1 ) tmp += " )";
    return tmp;
  }

  bool In( TENUM _st ) const { return std::find( states, states + count, _st ) != states + count; }
};


class SocialClient::States : public StaticSet<ESocClSt::Enum, ESocClSt::None> {
public:
  States & operator << ( ESocClSt::Enum _st ) { Add( _st ); return *this; }
};

class SocialClient::Pings : public StaticSet<EReqSt::Enum, EReqSt::Null> {
public:
  Pings & operator << ( EReqSt::Enum _st ) { Add( _st ); return *this; }
};









inline int CastlePersId( const char * str ) { return Crc32Checksum().AddString( str ).Get(); }

SocialClient::SocialClient( const SSocialConfig & socConfig, ITransport * testSocialTransport, const socialLobby::SMatchmakingRequest & reqData ) :
_socConfig( socConfig ),
req( reqData ),
added( false ),
state( ESocClSt::Start ),
stateTimeoutMoment( 0 ), timedOutState( ESocClSt::None ),
stateStartTime( timer::Now() ),
nextPingTime( 0 ),
_acceptedGameId( 0 ),
_guardReadyGameId( 0 )
{
  for ( int i = 0, index = 1; i < 6; ++i )
    for ( int j = 0; j < 6; ++j, ++index )
    {
      const char * talents[] = { "G132", "G134", "G040", "G217" };
      const size_t talNum = sizeof(talents) / sizeof(talents[0]);
      const char * talId = talents[index % talNum];
      playerData.talents[index] = NCore::TalentInfo( CastlePersId( talId ), 1, 0, false );
    }
  /*
  playerData.talents[1] = NCore::TalentInfo( CastlePersId( "G132" ), 1, 0 );
  playerData.talents[2] = NCore::TalentInfo( CastlePersId( "G134" ), 1, 0 );
  playerData.talents[3] = NCore::TalentInfo( CastlePersId( "G040" ), 1, 1 );
  playerData.talents[4] = NCore::TalentInfo( CastlePersId( "G217" ), 1, 2 );
  */
  playerData.talentRollData.rollTable["pvp"].defaultItems.push_back( NCore::TalentRollItem( 500, CastlePersId( "Server/PvP_Roll.xdb:770D7C0C-D2F0-4247-AB86-DA9D049036BE" ) ) );
  playerData.talentRollData.rollTable["pvp"].defaultItems.push_back( NCore::TalentRollItem( 1000, CastlePersId( "Server/PvP_Roll.xdb:0E2B7BCA-837B-420A-89C5-D5D5CC987DBD" ) ) );
  playerData.talentRollData.rollTable["training"].defaultItems.push_back( NCore::TalentRollItem( 1000, CastlePersId( "Server/Training_Roll.xdb:34D0E774-BF86-4E75-993C-70230E250331" ) ) );

  /*
  playerData.inventory.resize( 5 );
  for ( int i = 0; i < playerData.inventory.size(); ++i )
    playerData.inventory[i] = i + 1;
  */

  /*
  playerData.friends.resize( 500 + req.uid % 200 ); //TODO: раздуем данные; В жизни за раздувание данных отвечает поле .talentRollData
  for ( int i = 0; i < playerData.friends.size(); ++i )
    playerData.friends[i] = ( i * 3571 ) % 2797;
  */

  playerData.guardRating = req.guardRating;
  playerData.playerRating = req.playerRating;
  playerData.heroRating = req.heroRating;
  playerData.dropRate = 1.0f;

  playerData.heroId = CastlePersId( req.heroId.c_str() );
  playerData.heroEnergy = 100;
  playerData.basket = (NCore::EBasket::Enum)req.basket;
  playerData.flagId = "ru";

  _socTransportClient = testSocialTransport->CreateClient( this, reqData.uid, reqData.sessionContextId.c_str() ); 
}



SocialClient::~SocialClient()
{
  TerminatePvx();
}



void SocialClient::Poll()
{
  timer::Time t = timer::Now();

  if ( stateTimeoutMoment ) {
    if ( t > stateTimeoutMoment ) {
      Error( "Timed out!" );
      timedOutState = state;
      ChangeState( ESocClSt::TimedOut );
    }
  }

  if ( state == ESocClSt::Start )
    AddRequest();

  Ping( t );
}



void SocialClient::PoppedToPvX( gtc::IGameTestClient * _cl )
{
  NI_VERIFY( state == ESocClSt::PreparedToGame, "", return );
  pvxClient = _cl;
  ChangeState( ESocClSt::PreparedToGameAndPopped );
}



void SocialClient::PvXClientTerminated()
{
  pvxClient = 0;
}



void SocialClient::ChangeState( ESocClSt::Enum _st, timer::Time _timeout )
{
  timer::Time t = timer::Now();

  statesTimingLog.push_back( StateTiming( state, t - stateStartTime ) );
  stateStartTime = t;

  state = _st;

  if ( _timeout )
    stateTimeoutMoment = t + _timeout;
  else
    stateTimeoutMoment = 0;
}



void SocialClient::AddRequest()
{
  Msg( "Adding request..." );

  _socTransportClient->AddRequest( req );
  ChangeState( ESocClSt::WaitingAddAck, _socConfig.defaultTimeout );
}



void SocialClient::OnAddRequest()
{
  Msg( "Got AddRequest ack" );

  if ( !EnsureState( "AddRequest ack", States() << ESocClSt::WaitingAddAck ) )
    return;

  added = true;
  ChangeState( ESocClSt::WaitingGame );
}



void SocialClient::Ping( timer::Time t )
{
  if ( !added )
    return;

  if ( t < nextPingTime )
    return;

  Msg( "Pinging..." );

  nextPingTime = t + _socConfig.pingInterval;
  _socTransportClient->PingMatchmaking();
}



void SocialClient::OnPing( const socialLobby::SMatchmakingStatus & ping )
{
  Msg( "Got ping %s(%d)", EReqSt::ToString( ping.progress ), ping.progress );

  if ( ping.progress != EReqSt::Null )
    if ( ping.sessionContextId != req.sessionContextId ) {
      Fail( "Got wrong session id '%s' ('%s' expected)", ping.sessionContextId.c_str(), req.sessionContextId.c_str() );
      return;
    }

  switch ( state )
  {
    case ESocClSt::None:
    case ESocClSt::Start:
    case ESocClSt::WaitingAddAck:
      Fail( "Unexpected Ping" );
      break;

    case ESocClSt::WaitingGame:
      EnsurePing( ping, Pings() << 
            EReqSt::JustAddedToSocialServer <<
            EReqSt::JustAddedToHttpGateway <<
            EReqSt::JustAddedToLobby <<
            EReqSt::WaitingPartyMembers <<
            EReqSt::InLine <<
            EReqSt::WaitingAccept );
      if ( ping.progress == EReqSt::WaitingAccept )
        Accept( ping.gameId );
      break;

    case ESocClSt::WaitingGameAccept:
      EnsurePing( ping, Pings() <<
        EReqSt::PreGameLobby <<
        EReqSt::WaitingInPvX <<
        EReqSt::InLine <<
        EReqSt::WaitingAccept <<
        EReqSt::Accepted <<
        EReqSt::PreparingPvX );

      if ( ping.progress == EReqSt::PreGameLobby ) {
        Msg( "We are in a guard lobby" );
        ChangeState( ESocClSt::GuardLobby );
      }
      else if ( ping.progress == EReqSt::WaitingInPvX ) {
        sessionKey = ping.pvxSessionKey;
        ChangeState( ESocClSt::PreparedToGame, _socConfig.defaultTimeout );
      }
      else if ( ping.progress == EReqSt::InLine ) {
        Msg( "Game was not accepted by other members! Returned to MM-queue..." );
        ChangeState( ESocClSt::WaitingGame );
      }
      else if ( ping.progress == EReqSt::WaitingAccept ) {
        if ( ping.gameId != _acceptedGameId ) {
          Msg( "Game was not accepted by other members! Returned to MM-queue and immidiately matchmaked!" );
          ChangeState( ESocClSt::WaitingGame );
          Accept( ping.gameId );
        }
      }
      break;

    case ESocClSt::GuardLobby:
      EnsurePing( ping, Pings() << EReqSt::PreGameLobby );
      GuardReady( ping.gameId );
      break;

    case ESocClSt::GuardLobbyReady:
      EnsurePing( ping, Pings() << EReqSt::PreGameLobby << EReqSt::PreparingPvX << EReqSt::WaitingInPvX << EReqSt::InLine );

      if ( ping.progress == EReqSt::WaitingInPvX ) {
        sessionKey = ping.pvxSessionKey;
        ChangeState( ESocClSt::PreparedToGame, _socConfig.defaultTimeout );
      }
      else if ( ping.progress == EReqSt::InLine ) {
        Msg( "Guard game was not confirmed by other members! Returned to MM-queue..." );
        ChangeState( ESocClSt::WaitingGame );
      }
      else if ( ping.progress == EReqSt::WaitingAccept ) {
        if ( ping.gameId != _acceptedGameId ) {
          Msg( "Guard game was not confirmed by other members! Returned to MM-queue and immidiately matchmaked!" );
          ChangeState( ESocClSt::WaitingGame );
          Accept( ping.gameId );
        }
      }
      break;

    case ESocClSt::PreparedToGame:
      EnsurePing( ping, Pings() << EReqSt::WaitingInPvX );
      break;

    case ESocClSt::PreparedToGameAndPopped:
      EnsurePing( ping, Pings() << EReqSt::WaitingInPvX << EReqSt::InGame << EReqSt::ClientDropped );

      if ( ping.progress == EReqSt::InGame )
        ChangeState( ESocClSt::InGame );
      else if ( ping.progress == EReqSt::ClientDropped )
        Leave();
      break;

    case ESocClSt::InGame:
      EnsurePing( ping, Pings() << EReqSt::InGame << EReqSt::GameFinished << EReqSt::ClientDropped );

      if ( ping.progress == EReqSt::GameFinished )
        GameFinished( ping.gameResults );
      else if ( ping.progress == EReqSt::ClientDropped )
        Leave();
      break;

    case ESocClSt::LeavingGame:
      if ( ping.progress == EReqSt::WaitingGameFinish ) {
        Msg( "Leaver is waiting game to finish..." );
        ChangeState( ESocClSt::WaitingGameFinish );
      }
      else if ( ping.progress == EReqSt::GameFinished ) {
        Msg( "Left the game" );
        Cancel();
      }
      else
        EnsurePing( ping, Pings() << EReqSt::ClientDropped << EReqSt::WaitingGameFinish );
      break;

    case ESocClSt::WaitingGameFinish:
      EnsurePing( ping, Pings() << EReqSt::WaitingGameFinish << EReqSt::GameFinished );
      if ( ping.progress == EReqSt::GameFinished )
        GameFinished( ping.gameResults );
      break;

    case ESocClSt::Cancelling:
      if ( ping.progress == EReqSt::Null ) {
        Msg( "Closed" );
        ChangeState( ESocClSt::Finished );
      }
      break;

    case ESocClSt::Finished:
    case ESocClSt::Failed:
    case ESocClSt::TimedOut:
      break;
  }
}



void SocialClient::GameFinished( const socialLobby::SGameResults & results )
{
  Msg( "Game finished, cancelling" );

  TerminatePvx();

  gameResults = results;
  Cancel();
}



void SocialClient::Cancel()
{
  Msg( "Cancelling..." );

  NI_VERIFY( !ESocClSt::Terminal( state ), "", return );
  NI_VERIFY( state != ESocClSt::Cancelling, "", return );

  _socTransportClient->CancelRequest();

  ChangeState( ESocClSt::Cancelling, _socConfig.defaultTimeout );
}



void SocialClient::Accept( lobby::TSocialGameId gameId )
{
  Msg( "Accepting game g%016llx...", gameId );
  if ( _acceptedGameId == gameId ) {
    Msg( "This game already has been accepted!" );
    return;
  }

  NI_VERIFY( state == ESocClSt::WaitingGame, "", return );

  _socTransportClient->AcceptGameSession( playerData );

  _acceptedGameId = gameId;
  ChangeState( ESocClSt::WaitingGameAccept );
}



void SocialClient::GuardReady( lobby::TSocialGameId gameId )
{
  Msg( "Confirming guard readiness of game g%016llx...", gameId );
  if ( _guardReadyGameId == gameId ) {
    Msg( "This guard game readiness already has been confirmed!" );
    return;
  }

  NI_VERIFY( state == ESocClSt::GuardLobby, "", return );

  //Send the same hero, just for test
  //TODO: make option to really send new hero data here
  _socTransportClient->ChangeGuardHero( playerData );

  _socTransportClient->GuardLobbyReady();

  _guardReadyGameId = gameId;
  ChangeState( ESocClSt::GuardLobbyReady );
}



void SocialClient::Leave()
{
  Msg( "Leaving game..." );

  TerminatePvx();

  _socTransportClient->LeaveGame();

  ChangeState( ESocClSt::LeavingGame, _socConfig.defaultTimeout );
}



void SocialClient::TerminatePvx()
{
  if ( StrongMT<gtc::IGameTestClient> pvx = pvxClient.Lock() )
    pvx->TerminatePvx();
  pvxClient = 0;
}



bool SocialClient::EnsurePing( const socialLobby::SMatchmakingStatus & ping, const Pings & pings )
{
  if ( pings.In( ping.progress ) )
    return true;
  Fail( "Wrong client ping %s(%d), %s expected", EReqSt::ToString( ping.progress ), ping.progress, pings.Str().c_str() );
  return false;
}



bool SocialClient::EnsureState( const char * _msg, const States & states )
{
  if ( states.In( state ) )
    return true;
  Fail( "Wrong client state for %s, %s expected", _msg, states.Str().c_str() );
  return false;
}



void SocialClient::Msg( const char * _fmt, ... )
{
  char buf[256];
  va_list args;
  va_start( args, _fmt );
  NStr::VPrintf( buf, 256, _fmt, args);
  va_end( args );

  MessageTrace( "Social req u%lld (%s): %s", req.uid, ESocClSt::ToString( state ), buf );
}



void SocialClient::Error( const char * _fmt, ... )
{
  char buf[256];
  va_list args;
  va_start( args, _fmt );
  NStr::VPrintf( buf, 256, _fmt, args);
  va_end( args );

  ErrorTrace( "Social req u%lld (%s): %s", req.uid, ESocClSt::ToString( state ), buf );
}



void SocialClient::Fail( const char * _fmt, ... )
{
  char buf[256];
  va_list args;
  va_start( args, _fmt );
  NStr::VPrintf( buf, 256, _fmt, args);
  va_end( args );

  ErrorTrace( "Social req u%lld (%s): %s", req.uid, ESocClSt::ToString( state ), buf );

  ChangeState( ESocClSt::Failed );
}



NI_ENUM_BEGIN_STD( ESocClSt );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Start );
  NI_ENUM_ITEM( WaitingAddAck );
  NI_ENUM_ITEM( WaitingGame );
  NI_ENUM_ITEM( WaitingGameAccept );
  NI_ENUM_ITEM( GuardLobby );
  NI_ENUM_ITEM( GuardLobbyReady );
  NI_ENUM_ITEM( PreparedToGame );
  NI_ENUM_ITEM( PreparedToGameAndPopped );
  NI_ENUM_ITEM( InGame );
  NI_ENUM_ITEM( LeavingGame );
  NI_ENUM_ITEM( WaitingGameFinish );
  NI_ENUM_ITEM( Cancelling );
  NI_ENUM_ITEM( Finished );
  NI_ENUM_ITEM( Failed );
  NI_ENUM_ITEM( TimedOut );
NI_ENUM_END_STD;

} // namespace GtcSocial

NI_DEFINE_REFCOUNT( GtcSocial::SocialClient );
