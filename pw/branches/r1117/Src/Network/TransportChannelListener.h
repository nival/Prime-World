#pragma once
#include "Transport.h"
#include "TransportAddress.h"
#include "TransportMux.h"
#include "System/Thread.h"

namespace Network
{
	_interface IConnection;
	_interface IConnectionsManager;
}

namespace Transport
{
	struct MessageBase;
	class MessageFactory;
	class Channel;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ChannelListener : public BaseObjectMT, public IChannelListener
	{
    NI_DECLARE_REFCOUNT_CLASS_2( ChannelListener, BaseObjectMT, IChannelListener )

		ChannelListener() {}
		MessageFactory* factory;
		StrongMT<Network::IConnectionsManager> pManager;
    TServiceId serviceId;

		vector<ConnectionMux*> connections;
		vector<StrongMT<IChannel> > newConnections;
    threading::Mutex newConnectionsLock;
    TClientId nextAutoAssignId;
    Network::IStreamAllocator* pAlloc;

	public:

		ChannelListener( const TServiceId& serviceId, MessageFactory* _factory, Network::IConnectionsManager* _pManager, Network::IStreamAllocator* pAlloc );
		~ChannelListener();

    const TServiceId& GetServiceId() const { return serviceId; }
		void GetNewConnections( vector<StrongMT<IChannel> >* pConnections );
		void Step();

    // TFunc( IChannel* _channel )
    template < typename TFunc >
    void ForAllChannels( TFunc& func )
    {
      for ( vector<ConnectionMux*>::iterator it = connections.begin();it != connections.end() ; ++it )
      {
        (*it)->ForAllChannels( func );
      }    
    }
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}