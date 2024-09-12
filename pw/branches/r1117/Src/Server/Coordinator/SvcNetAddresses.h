#pragma once
#include "RPC/RPC.h"
#include "Network/Address.h"

namespace Coordinator
{

  struct SvcNetAddresses : rpc::Data
  {
    SERIALIZE_ID();

    SvcNetAddresses()
    {}

    SvcNetAddresses( Network::NetAddress const & _backendaddr, Network::NetAddress const & _frontendaddr ) :
    backendaddr(_backendaddr),
    frontendaddr(_frontendaddr)
    {}

    ZDATA
    Network::NetAddress backendaddr;
    Network::NetAddress frontendaddr;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&backendaddr); f.Add(3,&frontendaddr); return 0; }
  };
}
