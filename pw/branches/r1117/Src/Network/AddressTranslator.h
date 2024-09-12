#pragma once
#include "Network.h"
#include "TransportAddress.h"

namespace Transport
{

class IAddressTranslator : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IAddressTranslator, IBaseInterfaceMT);

  virtual const Network::NetAddress & GetServerIp() const = 0;

  virtual Network::NetAddress GetSvcAddress( const TServiceId & _serviceId ) = 0;

  virtual void DefineRoute( const TServiceId & _serviceId, const Network::NetAddress & _naddr ) = 0;
  virtual void DefineAliasRoute( const TServiceId & _serviceId, const TServiceId & _alias ) = 0;

  virtual TServiceId GetLastServiceInstance( const TServiceId & _svcClass ) = 0;
};

} //namespace Transport
