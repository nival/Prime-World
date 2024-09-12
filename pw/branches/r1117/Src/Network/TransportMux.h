#pragma once
#include "Transport.h"
#include "../System/Thread.h"
#include "Network.h"
#include "../System/nmap.h"
#include "TransportMessages.h"

namespace Network
{
	_interface IConnection;

}

namespace Transport
{
	class Channel;
	class MessageFactory;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct ConnectionMux
	{
	private:
    enum EState
    {
      S_CONNECTING,
      S_CONNECTED,
      S_CLOSED,
    };

		typedef nstl::hash_map<ChannelAddr, StrongMT<Channel>, ChannelAddrHash> TClientMap; 
    typedef nstl::map<Address, Channel*, AddressIsLess> TClientByAddressMap; 
    typedef nstl::hash_map<TClientId, ClientIdGenerator> TClientIDs; 

		StrongMT<Network::IConnection> pConn;
		TClientMap clientConnections; //by remote pipeID 
    TClientByAddressMap clientConnectionsByAddress; 
    TClientIDs clientIdGenerator; //local ID generator

    threading::Mutex clientConnectionsMutex; 
		MessageFactory* factory;
		Network::ConnectionState::Enum prevNetStatus;
		bool canAcceptNewConnections;
    bool packAddress;
    TClientId packedUserId;

    TClientId* nextAutoAssignId;
    TClientId localAutoAssignId;

    EState state;

    StrongMT<Network::IStreamAllocator> pAlloc;

		void CloseConnection( TClientMap::iterator it );

    void SendInt( const ChannelAddr& chAddr, MessageBase* msg ) 
    {
      CObj<Stream> str = GetBufferToSend();
      pConn->Send( PackNetMessage( chAddr, msg, str ) );
    }

		void CheckNetStatus();
		void Receive();
    void ProcessReceivedNetMessage( NetLogicMessage* pNLMsg, ChannelAddr &addr );
    void Send();

    CObj<Stream> GetBufferToSend()
    {
      if ( pAlloc )
        return pAlloc->Allocate();
      return new MemoryStream();
    }
    void ReleaseReceived( const CObj<Stream> & stream )
    {
      if ( pAlloc )
        pAlloc->Release( stream );
    }
	public:
    ConnectionMux() : packAddress(false), packedUserId(autoAssignClientId), state( S_CLOSED ), pAlloc(0) {}
    ~ConnectionMux();
    void SetAddressPacking( bool packAddress, TClientId packedUserId );
		void Init( MessageFactory* _factory, Network::IConnection* _pConn, bool _canAcceptNewConnections, TClientId* _nextAutoAssignId, Network::IStreamAllocator* pAlloc );

		StrongMT<IChannel> OpenChannel( const Address& address, const TLoginData& loginData );

		void Step();
		bool HasNetConnection() const;

    template < typename TFunc >
    void ForAllChannels( TFunc& func )
    {
      for ( TClientMap::iterator it = clientConnections.begin(); it != clientConnections.end(); ++it )
      {
        func( it->second );
      }    
    }
	};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}