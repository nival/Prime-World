#ifndef SESSIONHYBRIDLINK_H_INCLUDED
#define SESSIONHYBRIDLINK_H_INCLUDED

#include "Server/LobbyPvx/ISessionHybridLink.h"
#include "CommonTypes.h"


namespace lobby
{

class ServerNode;

class SessionHybridLink : public ISessionHybridLink, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SessionHybridLink, ISessionHybridLink, BaseObjectMT );
public:
  SessionHybridLink( ServerNode * _service );

  //ISessionHybridLink
  virtual void OnGameFinish( Peered::TSessionId _sessionId, int _enumGameResult, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics );
  virtual void OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, /*ECheatType*/ int _cheatType, const char * _clientIp );
  virtual void OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos );

private:
  WeakMT<ServerNode> service;
};

} //namespace lobby

#endif //SESSIONHYBRIDLINK_H_INCLUDED
