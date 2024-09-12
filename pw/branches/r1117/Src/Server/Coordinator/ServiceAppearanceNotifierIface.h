#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>
#include <Network/Address.h>
#include "Coordinator/CoordinatorServiceStatus.h"
#include "Coordinator/ServiceRole.h"

namespace Coordinator
{
  struct SvcInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    Transport::TServiceId svcid;
    TServiceRole svcrole;
    ServiceStatus::Enum st;
    Network::NetAddress netaddr;
    unsigned int pid; //  process id
    nstl::string machineName;
    Network::NetAddress frontendnetaddr;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&svcid); f.Add(3,&svcrole); f.Add(4,&st); f.Add(5,&netaddr); f.Add(6,&pid); f.Add(7,&machineName); f.Add(8,&frontendnetaddr); return 0; }
    SvcInfo() : st(ServiceStatus::S_INIT), pid(0) {}
    SvcInfo( const Transport::TServiceId& _svcid, TServiceRole const & _svcrole, const Network::NetAddress& _netaddr, ServiceStatus::Enum _st, const Network::NetAddress& _frontendnetaddr = "", 
      unsigned int _pid = 0, nstl::string const & _machineName = "")
      : svcid(_svcid), svcrole(_svcrole), netaddr(_netaddr), st(_st), frontendnetaddr(_frontendnetaddr), pid(_pid), machineName(_machineName) {}
  };

  struct ClusterInfo : public rpc::Data
  {
    SERIALIZE_ID();

    typedef vector<SvcInfo> SvcInfosT;

    ZDATA
    ZNOPARENT(rpc::Data)
    SvcInfosT svcinfos;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&svcinfos); return 0; }
    ClusterInfo() {}
  };

  typedef int SubcriberIdT;
  const SubcriberIdT INVALID_SUBSCRIBER_ID = -1;

  REMOTE class IServiceAppearanceSubscriber : public rpc::IRemoteEntity
  {
    RPC_ID();

  public:
    REMOTE virtual void OnRegisterSubscriber(Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster) = 0;
    REMOTE virtual void OnRegisterService( Transport::TServiceId const & svcid ) = 0;
    REMOTE virtual void OnUnregisterService( Transport::TServiceId const & svcid ) = 0;
    REMOTE virtual void OnStartService( SvcInfo const & ssi ) = 0;
    REMOTE virtual void OnStopService( Transport::TServiceId const & svcid ) = 0;
    REMOTE virtual void OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/int _status) = 0;
  };

  REMOTE class IServiceAppearancePublisher : public IBaseInterfaceMT
  {
    RPC_ID();

  public:
    REMOTE virtual void RegisterSubscriber( NI_LPTR IServiceAppearanceSubscriber* subscriber ) = 0;
    REMOTE virtual void UnregisterSubscriber( SubcriberIdT sid, NI_LPTR IServiceAppearanceSubscriber* subscriber) = 0;
    REMOTE virtual int Subscribe(SubcriberIdT sid, Transport::TServiceId const & svcls) = 0;
    REMOTE virtual void Unsubscribe(SubcriberIdT sid, Transport::TServiceId const & svcls) = 0;
  };
}
