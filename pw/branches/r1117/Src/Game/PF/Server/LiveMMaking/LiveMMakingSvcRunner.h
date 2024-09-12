#ifndef LIVEMMAKINGSVCRUNNER_H_INCLUDED
#define LIVEMMAKINGSVCRUNNER_H_INCLUDED

#include "ServerAppBase/NivalService.h"

namespace socialLobby
{
  class RISocialInterface;
}

namespace mmaking
{

namespace EServiceGameModes { enum Enum; }

class LiveMMaking;


class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

protected:
  virtual void Poll( timer::Time _now );
  virtual void OnConfigReload();

private:
  EServiceGameModes::Enum             gameModes;
  StrongMT<rpc::IfaceRequester<socialLobby::RISocialInterface> > remoteSocLobby;
  StrongMT<LiveMMaking>               svc;

  threading::Mutex                    configReloadMutex;
  bool                                reloadedConfigFlag;
};

} //namespace mmaking

#endif //LIVEMMAKINGSVCRUNNER_H_INCLUDED
