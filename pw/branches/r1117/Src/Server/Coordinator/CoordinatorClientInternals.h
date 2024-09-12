#pragma once

#include "Network/Transport.h"
#include "Network/AddressTranslator.h"
#include <map>

namespace Coordinator
{

class ClassRoutes : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClassRoutes, BaseObjectMT );
public:
  ClassRoutes() {}
  void AddClassRoute( const Transport::TServiceId & _svcId );
  Transport::TServiceId FindClassLastService( const Transport::TServiceId & _svcClass ) const;

protected:
  typedef std::map<Transport::TServiceId, Transport::TServiceId> TMap;

  threading::Mutex mutex;
  TMap  routes;
};










class AddressTranslator : public Transport::IAddressTranslator, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( AddressTranslator, Transport::IAddressTranslator, BaseObjectMT );
public:
  typedef std::map<Transport::TServiceId, Network::NetAddress> TRouteMap;

  AddressTranslator( const char * _tag, ClassRoutes * _classRoutes );

  void SetServerIp( const Network::NetAddress & _ip ) { serverIp = _ip; }
  void AddRoute( const Transport::TServiceId & _svcId, Network::NetAddress const & _addr );
  void RemoveRoute( const Transport::TServiceId & _svcId );

  virtual const Network::NetAddress & GetServerIp() const { return serverIp; }
  virtual Network::NetAddress GetSvcAddress( const Transport::TServiceId & _serviceId );
  virtual void DefineRoute( const Transport::TServiceId & _service, const Network::NetAddress & _naddr );
  virtual void DefineAliasRoute( const Transport::TServiceId & _service, const Transport::TServiceId & _alias );
  virtual Transport::TServiceId GetLastServiceInstance( const Transport::TServiceId & _svcClass );

  void PopFreshRoutes( TRouteMap & _result );

protected:
  const string            tag;
  Network::NetAddress     serverIp;
  StrongMT<ClassRoutes>   classRoutes;
  threading::Mutex        mutex;
  TRouteMap               freshRoutes, permanentRoutes;
};

} //namespace Coordinator
