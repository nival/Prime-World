#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "Server/Statistic/StatisticsClientTypes.h"
#include "System/RandomGenerator.h"
#include "System/NiTimer.h"
#include "PF_GameLogic/SessionEventType.h"
#include <list>

namespace gstat_test
{


class TestSession : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestSession, BaseObjectMT );

public:
  TestSession( lobby::TGameId _gameId, int _firstUid, int _size, int _sessDuration, bool _sendStartSess ) :
  sessDuration( _sessDuration ),
  sendStartSess( _sendStartSess ),
  clientStat( new StatisticService::GameStatClient( new StatisticService::ClientHttpDispatcher, 1 ) ),
  serverStat( new StatisticService::GameStatClient( new StatisticService::ClientHttpDispatcher, 0 ) ),
  rnd( GetTickCount() ),
  state( StConnecting ),
  timeout( 15.0 )
  {
    sessionEvents.push_back( SessionEventType::HeroKill );
    sessionEvents.push_back( SessionEventType::HeroDeath );
    sessionEvents.push_back( SessionEventType::KillAssist );

    heroIds.push_back( 1617033593 );
    heroIds.push_back( -1150316378 );
    heroIds.push_back( 1160508680 );
    heroIds.push_back( -834226607 );
    heroIds.push_back( 571020430 );\

    SetupMmSessionStart( _gameId, _firstUid, _size );

    if ( mmSession.status == StatisticService::ELobbyGameStatus::Launched )
      SetupPvxSessionStart();
  }

  lobby::TGameId Id() const { return mmSession.persistentId; }

  bool Poll()
  {
    switch ( state )
    {
      case StConnecting:
      {
        if ( timeout.Poll() )
        {
          ErrorTrace( "Cannot connect to host!" );
          return false;
        }

        if ( clientStat->Ready() && serverStat->Ready() )
        {
          MessageTrace( "Connected to GameStat host. sess=%016x", mmSession.persistentId );

          DebugTrace( "Sending MMakingGame. sess=%016x", mmSession.persistentId );
          serverStat->Message( mmSession );
          state = StBeforeStart;
          timeout.Restart( 1.0 );

          if ( !pvxSession.sessionid )
          {
            MessageTrace( "This is 'dismissed' session. Closing context. sess=%016x", mmSession.persistentId );
            return false;
          }
        }
        return true;
      }

      case StBeforeStart:
      {
        if ( !timeout.Poll() )
          return true;

        if ( sendStartSess )
        {
          DebugTrace( "Sending SessionStartEvent. sess=%016x", pvxSession.sessionid );
          serverStat->Message( pvxSession );
        }
        else
          DebugTrace( "Sending SessionStartEvent SKIPPED! sess=%016x", pvxSession.sessionid );

        state = StPlaying;
        
        timeout.Restart( sessDuration );

        sessEvtCooldown.Restart( 0.5 );
        disconnectEvtCooldown.Restart( rnd.NextF( sessDuration * 0.1, sessDuration * 0.5 ) );
        mmCancelCooldown.Restart( rnd.NextF( 30.0, 180.0 ) );

        return true;
      }

      case StPlaying:
      {
        if ( !clientStat->Ready() || !serverStat->Ready() )
          ErrorTrace( "Connection lost! sess=%016x", mmSession.persistentId );

        if ( timeout.Poll() )
        {
          MessageTrace( "Sessiong finished. sess=%016x", pvxSession.sessionid );

          SendPvxSessionResult();
          return false;
        }

        if ( sessEvtCooldown.Poll() )
        {
          StatisticService::RPC::SessionStartPlayer plr = rnd.RollFromContainer( pvxSession.players );

          StatisticService::RPC::ClientCommonSessionEvent evt;
          evt.common = StatisticService::RPC::CommonSessionEventInfo( pvxSession.sessionid, plr.userid, rnd.Next( 1, 1000 ) );
          evt.x = rnd.Next( -1000, +1000 );
          evt.y = rnd.Next( -1000, +1000 );
          evt.eventType = rnd.RollFromContainer( sessionEvents, SessionEventType::HeroKill );
          evt.info.intParam1 = 1;
          evt.info.intParam2 = 2;
          evt.info.intParam3 = 3;
          evt.info.intParam4 = 4;
          evt.info.intParam5 = 5;
          evt.info.strParam1 = L"A";
          evt.info.strParam2 = L"B";
          
          //DebugTrace( "Sending ClientCommonSessionEvent. sess=%016x, uid=%d", pvxSession.sessionid, evt.common.playerId );
          clientStat->Message( evt );

          sessEvtCooldown.Restart( rnd.NextF( 0.1f, 1.0f ) );
        }

        if ( disconnectEvtCooldown.Poll() )
        {
          NI_VERIFY( pvxSession.sessionid, "", return false );

          StatisticService::RPC::UserDisconnectEvent evt;
          evt.ctx = StatisticService::RPC::SessionUserContext( pvxSession.sessionid, rnd.RollFromContainer( pvxSession.players ).userid );
          evt.reason = rnd.Roll( 90.0f ) ? Peered::DisconnectedByClient : Peered::DisconnectedByServer;

          DebugTrace( "Sending UserDisconnectEvent. sess=%016x, uid=%d", mmSession.persistentId, evt.ctx.userid );
          serverStat->Message( evt );

          disconnectEvtCooldown.Restart( rnd.NextF( sessDuration * 0.1, sessDuration * 0.5 ) );
        }


        if ( mmCancelCooldown.Poll() )
        {
          StatisticService::RPC::MMakingCanceled evt;
          evt.map = L"TestMap";
          RandomizeMmMember( evt.member, rnd.Next( 0, 9 ), 10, rnd.Next( 1, 100500 ) );

          DebugTrace( "Sending MMakingCanceled. sess=%016x, uid=%d", mmSession.persistentId, evt.member.userid );
          serverStat->Message( evt );

          mmCancelCooldown.Restart( rnd.NextF( 30.0, 180.0 ) );
        }
        return true;
      }

      default:
        NI_ALWAYS_ASSERT( "unknown state" );
        return false;
    }
  }

private:
  enum EState { StConnecting, StBeforeStart, StPlaying };

  const int                                   sessDuration;
  const bool                                  sendStartSess;
  std::vector<int>                            sessionEvents;
  std::vector<int>                            heroIds;
  StrongMT<StatisticService::GameStatClient>  clientStat, serverStat;
  NRandom::RandomGenerator                    rnd;

  StatisticService::RPC::MMakingGame          mmSession;
  StatisticService::RPC::SessionStartEvent    pvxSession;

  EState                                      state;
  timer::Timer                                timeout, sessEvtCooldown, disconnectEvtCooldown, mmCancelCooldown;


  void RandomizeMmMember( StatisticService::RPC::MMakingMember & m, int _idx, int _size, int _uid )
  {
    m.userid = _uid;
    m.faction = ( _idx < ( _size / 2 ) ) ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
    m.sex = rnd.Roll( 85.0f ) ? lobby::ESex::Male : lobby::ESex::Female;
    m.heroid = rnd.RollFromContainer( heroIds );
    m.heroRating = rnd.Next( 1000, 2000 );
    m.playerRating = rnd.Next( 1000, 2000 );
    m.guardRating = m.playerRating;
    m.force = rnd.NextF( 100.0f, 170.0f );
    m.partyId = 0;
    m.waitTime = rnd.NextF( 0.0f, 300.0f );
    m.loseStreak = rnd.Next( 5 );
    m.fameLevel = rnd.Next( 1, 31 );
    m.basket = rnd.Roll( 90.0f ) ? mmaking::EBasket::Normal : mmaking::EBasket::Newbie;
    m.lobbyReaction = StatisticService::ELobbyReaction::Accept;
  }



  void SetupMmSessionStart( lobby::TGameId _gameId, int _firstUid, int _size )
  {
    DebugTrace( "Sending MMakingGame" );

    mmSession.persistentId = _gameId;
    mmSession.status = rnd.Roll( 90.0f ) ? StatisticService::ELobbyGameStatus::Launched : StatisticService::ELobbyGameStatus::Dismissed;
    mmSession.manoeuvresFaction = lobby::ETeam::None;
    mmSession.basket = mmaking::EBasket::Normal;
    mmSession.map = L"Maps/Multiplayer/DefaultTestMap.MAPDESC";
    mmSession.members.resize( _size );
    for ( int i = 0; i < _size; ++i )
      RandomizeMmMember( mmSession.members[i], i, _size, _firstUid + i );
  }



  void SetupPvxSessionStart()
  {
    pvxSession.sessionid = mmSession.persistentId;
    pvxSession.persistentId = mmSession.persistentId;
    pvxSession.map = L"TestMap";
    pvxSession.server = L"gamesvc/test";
    pvxSession.sessionType = StatisticService::EGameType::Soc_Matchmaking;
    
    pvxSession.players.resize( mmSession.members.size() );
    for ( int i = 0; i < mmSession.members.size(); ++i )
    {
      const StatisticService::RPC::MMakingMember & memb = mmSession.members[i];

      StatisticService::RPC::SessionStartPlayer & plr = pvxSession.players[i];

      plr.userid = memb.userid;
      plr.faction = memb.faction;
      plr.sex = memb.sex;
      plr.heroid = memb.heroid;
      plr.nickname = NStr::StrFmtW( L"User%i", memb.userid );
    }
  }


  void SendPvxSessionResult()
  {
    DebugTrace( "Sending SessionResultEvent. sess=%016x", pvxSession.sessionid );

    StatisticService::RPC::SessionResultEvent evt;

    evt.result = 0;
    evt.sessionid = mmSession.persistentId;
    evt.clientData.players.resize( mmSession.members.size() );
    evt.serverPlayersInfo.resize( mmSession.members.size() );

    for ( int i = 0; i < mmSession.members.size(); ++i )
    {
      evt.clientData.players[i].userid = mmSession.members[i].userid;
      evt.serverPlayersInfo[i].userid = mmSession.members[i].userid;
    }

    serverStat->Message( evt );
  }
};






typedef std::list<StrongMT<TestSession> > TSessions;

inline bool Test()
{
  const char * url = CmdLineLite::Instance().GetStringKey( "-gstat" );
  if ( !url )
    return false;

  lobby::TGameId nextSessId = ( ((lobby::TGameId)GetTickCount()) << 32 ) + 1;
  int nextUid = 1;

  const int count = CmdLineLite::Instance().GetIntKey( "-count", 100 );
  const int gameDuration = CmdLineLite::Instance().GetIntKey( "-gamedur", 300 );
  const bool sendStartSess = !CmdLineLite::Instance().IsKeyDefined( "-skipstart" );

  MessageTrace( "Starting GameStat test. url=%s, count=%d, duration=%d", url, count, gameDuration );

  NGlobal::SetVar( "stat_client_url", url, STORAGE_NONE );

  TSessions sessions;

  NRandom::RandomGenerator rnd( GetTickCount() );
  timer::Timer addCd;
  while ( true )
  {
    if ( sessions.size() < (size_t)count )
      if ( addCd.Poll() )
      {
        lobby::TGameId sessId = nextSessId++;
        MessageTrace( "New session. sess=%016x", sessId );

        StrongMT<TestSession> test = new TestSession( sessId, nextUid, 10, gameDuration + rnd.Next( 0, gameDuration / 5 ), sendStartSess );
        nextUid += 10;

        sessions.push_back( test );
        addCd.Restart( 0.1 );
      }

    for ( TSessions::iterator it = sessions.begin(); it != sessions.end(); )
      if ( (*it)->Poll() )
        ++it;
      else
      {
        MessageTrace( "Removing session. sess=%016x", (*it)->Id() );
        it = sessions.erase( it );
      }

    Sleep( 10 );
  }

  return true;
}

}
