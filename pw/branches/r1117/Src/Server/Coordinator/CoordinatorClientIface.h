#pragma once
#include "RPC/RPC.h"
#include "Network/Address.h"
#include "Network/TransportTypes.h"
#include "Coordinator/SvcNetAddresses.h"

namespace Coordinator
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  REMOTE class ICoordinatorClientRemote : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1(ICoordinatorClientRemote, IBaseInterfaceMT);
    RPC_ID();

  public:
    //REMOTE virtual void InitRouteTable(RouteTable const & _rt) = 0;
    REMOTE virtual void AddRoute( const Transport::TServiceId& service, SvcNetAddresses const & addrs ) = 0;
    REMOTE virtual void RemoveRoute( const Transport::TServiceId& service ) = 0;

    REMOTE virtual void StartService( const Transport::TServiceId& service ) = 0;
    REMOTE virtual void StopService( const Transport::TServiceId& service ) = 0;
    REMOTE virtual void SoftStopService( const Transport::TServiceId& service ) = 0;

    REMOTE virtual void ReloadConfig( const Transport::TServiceId & service ) = 0;

    REMOTE virtual unsigned int Ping(unsigned int _param) = 0;
  };
}
