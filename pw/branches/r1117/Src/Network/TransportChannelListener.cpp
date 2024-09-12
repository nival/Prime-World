#include "stdafx.h"
#include "TransportChannelListener.h"
#include "TransportChannel.h"
#include "Message.h"
#include "Network.h"

namespace Transport
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChannelListener::ChannelListener( const TServiceId& _serviceId, MessageFactory* _factory, Network::IConnectionsManager* _pManager, Network::IStreamAllocator* _pAlloc ) 
: factory(_factory)
, pManager( _pManager )
, serviceId( _serviceId )
, nextAutoAssignId( firstAutoAssignId )
, pAlloc( _pAlloc )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChannelListener::~ChannelListener()
{
  vector<ConnectionMux*>::iterator it = connections.begin(), itEnd = connections.end(); 
  for ( ;it != itEnd ; ++it )
  {
    delete *it;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChannelListener::Step()
{
  Network::TNewConnections newNetConns; 
  pManager->GetNewConnections( newNetConns );

  Network::TNewConnections::iterator it = newNetConns.begin(), itEnd = newNetConns.end(); 
  for ( ;it != itEnd ; ++it )
  {
    ConnectionMux* mux = connections.push_back(new ConnectionMux);
    mux->Init( factory, *it, true, &nextAutoAssignId, pAlloc );
  }

  for ( vector<ConnectionMux*>::iterator it2 = connections.begin(); it2 != connections.end() ; )
  {
    newConnectionsLock.Lock();
    (*it2)->Step();
    newConnectionsLock.Unlock();

    if ( (*it2)->HasNetConnection() )
      ++it2;
    else
    {
      delete *it2;
      it2 = connections.erase( it2 );
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChannelListener::GetNewConnections( vector<StrongMT<IChannel> >* pConnections )
{
  newConnectionsLock.Lock();
  pConnections->swap( newConnections );
  newConnections.clear();																																	 
  newConnectionsLock.Unlock();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
