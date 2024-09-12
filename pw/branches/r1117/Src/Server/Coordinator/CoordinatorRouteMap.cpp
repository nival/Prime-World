#include "stdafx.h"
#include "CoordinatorRouteMap.h"
#include "RCoordinatorClientIface.auto.h"

namespace Coordinator
{

void CoordinatorRouteMap::AddRoute( const Transport::TServiceId& service, SvcNetAddresses const & addrs )
{
  routeMap[ service ] = addrs;

  // routes апдейтим всему кластеру
  for ( int i = 0; i < slaves.size(); ++i )
    slaves[i]->AddRoute( service, addrs );
}



void CoordinatorRouteMap::RemoveRoute( const Transport::TServiceId& service )
{
  routeMap.erase( service );

  // routes апдейтим всему кластеру
  for ( int i = 0; i < slaves.size(); ++i )
    slaves[i]->RemoveRoute( service );
}



bool CoordinatorRouteMap::FindRoute( SvcNetAddresses & _result, const Transport::TServiceId & _serviceId ) const
{
  TServicesMap::const_iterator it = routeMap.find( _serviceId );
  if ( it != routeMap.end() )
  {
    _result = it->second;
    return true;
  }

  return false;
}



void CoordinatorRouteMap::AddSlave( RICoordinatorClientRemote * _cli )
{
  for ( CoordinatorClientsT::iterator it = slaves.begin(); it != slaves.end(); ++it )
    if ( _cli->GetInfo().entityGUID == (*it)->GetInfo().entityGUID )
    {
      *it = _cli;
      return;
    }

  slaves.push_back( _cli );
}



void CoordinatorRouteMap::InitSlave( RICoordinatorClientRemote * _cli )
{
  for ( CoordinatorClientsT::const_iterator cit = slaves.begin(); cit != slaves.end(); ++cit )
    if ( _cli->GetInfo().entityGUID == (*cit)->GetInfo().entityGUID )
    {
      for( TServicesMap::iterator it = routeMap.begin(); it != routeMap.end(); ++it )
        _cli->AddRoute( it->first, it->second );
      return;
    }

  LOG_A(0) << "CoordinatorRouteMap::InitSlave slave=" << _cli << " NOT FOUND!";
}



void CoordinatorRouteMap::RemoveSlaveCorpses()
{
  for ( CoordinatorClientsT::iterator it = slaves.begin(); it != slaves.end(); )
  {
    if ( (*it)->GetStatus() ==  rpc::Connected)
      ++it;
    else
      it = slaves.erase( it );
  }
}

} //namespace Coordinator
