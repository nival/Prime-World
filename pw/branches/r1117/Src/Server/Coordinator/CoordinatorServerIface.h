#pragma once
#include "Coordinator/Interface.h"
#include "Coordinator/CoordinatorClientIface.h"
#include "Coordinator/ServerDef.h"
#include "Coordinator/ServicesStartInfo.h"
#include "Coordinator/CoordinatorTypes.h"

namespace Coordinator
{
  REMOTE class IRegisterClientCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IRegisterClientCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnRegisterClient(int _result, Coordinator::ServerIdT _clientid) = 0;
  };

  REMOTE class ICoordinatorServerRemote : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ICoordinatorServerRemote, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual void RegisterClient(Coordinator::ServerIdT _clientid, NI_LPTR ICoordinatorClientRemote* _rptr, ServerDef const & _serverdef, NI_LPTR IRegisterClientCallback* _cb) = 0;

    REMOTE virtual void ServicesStarted(ServicesStartInfo const & _info) = 0;
    REMOTE virtual void Shutdown() = 0;
    REMOTE virtual void StopService(Transport::TServiceId const & _svcid) = 0;
    REMOTE virtual void ServiceStopped(Transport::TServiceId const & _svcid) = 0;
    REMOTE virtual void SoftStopService(Transport::TServiceId const & _svcid) = 0;
    REMOTE virtual void ReloadConfig(Transport::TServiceId const & _svcid) = 0;
  };
}
