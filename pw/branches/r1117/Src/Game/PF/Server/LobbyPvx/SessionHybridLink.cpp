#include "stdafx.h"
#include "SessionHybridLink.h"
#include "LobbyServerNode.h"
#include "Db/DBServer.auto.h"
#include "System/InlineProfiler.h"
#include "LobbyLog.h"


namespace lobby
{

SessionHybridLink::SessionHybridLink( ServerNode * _service ) :
service( _service )
{
}



void SessionHybridLink::OnGameFinish( Peered::TSessionId _sessionId, int _enumGameResult, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics )
{
  NI_PROFILE_FUNCTION;

  EGameResult::Enum result = (EGameResult::Enum)_enumGameResult;
  LOBBY_LOG_MSG( "Session %s ended with code %d (%s)", FmtGameId( _sessionId ), _enumGameResult, EGameResult::ToString( result ) );

  if ( StrongMT<ServerNode> locked = service.Lock() )
    locked->OnGameFinish( _sessionId, result, _finishInfo, _clientsStatistics );
}



void SessionHybridLink::OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, /*ECheatType*/ int _cheatType, const char * _clientIp )
{
  NI_PROFILE_FUNCTION;

  if ( StrongMT<ServerNode> locked = service.Lock() )
    locked->OnGameCheated( _sessionId, _clientId, (ECheatType::Enum)_cheatType, _clientIp );
}



void SessionHybridLink::OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos )
{
  NI_PROFILE_FUNCTION;

  if ( StrongMT<ServerNode> locked = service.Lock() )
    locked->OnChangeClientStatus( _sessionId, _clientInfos );
}

} //namespace lobby
