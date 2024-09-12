#pragma once
#include "RPC/RPC.h"
#include "Network/Address.h"
#include "Network/TransportTypes.h"
#include "Coordinator/CoordinatorTypes.h"

namespace Coordinator
{

struct ServiceStartInfo
{
  ZDATA
  Transport::TServiceId svcid;
  Network::NetAddress backendAddr;
  Network::NetAddress frontendAddr;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&svcid); f.Add(3,&backendAddr); f.Add(4,&frontendAddr); return 0; }
  ServiceStartInfo() {}
  ServiceStartInfo( const Transport::TServiceId& _service, const Network::NetAddress& _backendAddr, Network::NetAddress const & _frontendAddr)
    : svcid(_service), backendAddr(_backendAddr), frontendAddr(_frontendAddr)
  {}
};


struct ServicesStartInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  ServerIdT srvid_;
  vector<ServiceStartInfo> serviceDefs;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&srvid_); f.Add(3,&serviceDefs); return 0; }
  ServicesStartInfo() : srvid_(0) {}
};

} //namespace Coordinator
