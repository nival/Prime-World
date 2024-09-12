#pragma once
#include "Network/TransportAddress.h"
#include "Network/Address.h"
#include "Coordinator/RCoordinatorClientIface.auto.h"


namespace Coordinator
{

class CoordinatorRouteMap
{
public:
  typedef map<Transport::TServiceId, SvcNetAddresses> TServicesMap;

private:
  typedef TServicesMap::iterator TIter;
  typedef map<Transport::TServiceId, vector<Transport::TServiceId> > TServicesByClass;
  typedef vector<StrongMT<RICoordinatorClientRemote> > CoordinatorClientsT;

  TServicesMap routeMap;
  CoordinatorClientsT slaves;

public:

  CoordinatorRouteMap(){}
  ~CoordinatorRouteMap(){};

  void AddRoute( const Transport::TServiceId& service, SvcNetAddresses const & addrs);
  void RemoveRoute( const Transport::TServiceId& service );

  bool FindRoute( SvcNetAddresses & _result, const Transport::TServiceId & _serviceId ) const;

  void AddSlave( RICoordinatorClientRemote * cli );
  void InitSlave( RICoordinatorClientRemote * cli );

  void RemoveSlaveCorpses();
};

} //namespace Coordinator
