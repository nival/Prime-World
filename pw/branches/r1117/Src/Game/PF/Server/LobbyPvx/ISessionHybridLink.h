#pragma once
#include <Server/RPC/RPC.h>
#include <Game/PF/HybridServer/Peered.h>

#include "CommonTypes.h"
#include "Server/Roll/RollTypes.h"

namespace lobby
{

namespace ECheatType
{
  enum Enum
  {
    None,
    ProtocolViolation,
    GameLogicHack,
    Async,
    ProtectionAsync, // магические числа не сошлись
    ProtectionViolation, // нарушение работы защиты
  };
}


REMOTE class ISessionHybridLink : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ISessionHybridLink, rpc::IRemoteEntity );
  RPC_ID();

public:
  REMOTE virtual void OnGameFinish( Peered::TSessionId _sessionId, /*EGameResult*/ int _gameResultType, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics ) = 0;
  REMOTE virtual void OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, /*ECheatType*/ int _cheatType, const char * _clientIp ) = 0; 
  REMOTE virtual void OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos ) = 0;
};

} //namespace lobby
