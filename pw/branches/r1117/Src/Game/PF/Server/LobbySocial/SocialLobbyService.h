#ifndef SOCIALLOBBYSERVICE_H_INCLUDED
#define SOCIALLOBBYSERVICE_H_INCLUDED

#include "ServerAppBase/NivalService.h"
#include "ISocialLobbyPvxAck.h"
#include "RPC/IfaceRequester.h"

namespace rpc
{
  class GateKeeper;
  struct LocalEntityFactory;
}

namespace StatisticService
{
  class GameStatClient;
}

namespace Coordinator
{
  _interface ICoordinatorClient;
}

namespace socialLobby
{

class SocialLobby;
class IDevSocLobby;

class Service : public Transport::BaseService, public socialLobby::IPvxAcknowledge
{
  NI_DECLARE_REFCOUNT_CLASS_2( Service, Transport::BaseService, socialLobby::IPvxAcknowledge );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );

  ~Service();

  virtual void OnConfigReload();

private:
  StrongMT<rpc::GateKeeper>           extClusterGateKeeper;
  ScopedPtr<rpc::LocalEntityFactory>  extClusterRpcFactory;

  StrongMT<SocialLobby>               logic;
  StrongMT<socialLobby::IDevSocLobby> devSocLobby;
  StrongMT<StatisticService::GameStatClient> statistics;

  virtual void Poll( timer::Time _now );

  //socialLobby::IPvxAcknowledge
  virtual void NewGameAck( lobby::TSocialGameId _gameId );
  virtual void NewReconnectingUserAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId );
  virtual void NewSpectatorAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId );
  virtual void UserLeftTheGameInCastleAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId );
};

} //namespace socialLobby

#endif //SOCIALLOBBYSERVICE_H_INCLUDED
