#include "stdafx.h"
#include "LocalNetDriver.h"
#include "System/get_tick_count.h"

namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Network::NetAddress& LocalNetConnectionEnd::GetAddress() const
{
  return data->address;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::ConnectionState::Enum LocalNetConnectionEnd::GetStatus() const
{
  return data->GetStatus();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetConnectionEnd::Close()
{
  data->status = Network::ConnectionState::Closed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  LocalNetConnectionEnd::AsyncClose()
{
  data->status = Network::ConnectionState::Closed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> LocalNetConnectionEnd::GetBufferToSend()
{
  if ( data->pAlloc )
    return data->pAlloc->Allocate();
  return new MemoryStream();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LocalNetConnectionEnd::Send( const CObj<Stream> & pS )
{
  if ( GetStatus() == Network::ConnectionState::Closed )
  {
    ReleaseReceived( pS );
    return false;
  }

  threading::MutexLock lock( clientSide ? data->toServerCritical : data->fromServerCritical );

  LocalNetConnectionData::TQueue& q = clientSide ? data->toServerQueue : data->fromServerQueue;
  pS->Seek( reservedSpace, SEEKORIGIN_BEGIN );

  DWORD time = nival::get_tick_count();
  q.push_back( LocalNetConnectionData::SMsg( pS, time ) );

  LocalNetDriver::messagesQueued += 1;
  LocalNetDriver::bytesQueued += pS->GetSize();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> LocalNetConnectionEnd::Receive()
{
  if ( GetStatus() != Network::ConnectionState::Connected )
    return 0;

  if ( data->clientSecure != data->serverSecure ) // wait for "ssl handshake"
    return 0;

  if( data->clientSecure && data->serverSecure )
  {
    NI_VERIFY( data->clientSslCtx == data->serverSslCtx, "Security error: SSL contexts must be equal!"
      , data->status = Network::ConnectionState::Closed; return 0 );
  }

  threading::MutexLock lock( clientSide ? data->fromServerCritical : data->toServerCritical );
  LocalNetConnectionData::TQueue& q = clientSide ? data->fromServerQueue : data->toServerQueue;

  if ( q.empty() )
    return 0;

  DWORD time = GetTickCount();

  if ( q.front().sendTime > time - data->latency )
    return 0;

  CObj<Stream> pHold = q.front().pS;
  q.pop_front();
  CObj<Stream> pS = GetBufferToSend();
  pS->SetSize( pHold->GetSize() - pHold->GetPosition() + reservedSpace );
  pS->Seek( reservedSpace, SEEKORIGIN_BEGIN );
  pS->CopyFrom( pHold );
  pS->Seek( reservedSpace, SEEKORIGIN_BEGIN );

  if ( LocalNetDriver::packetsModifier )
  {
    (*LocalNetDriver::packetsModifier)( data->address, !clientSide, pS );
  }

  receivedMsg = pS;

  if ( data->pAlloc )
    data->pAlloc->Release( pHold );

  LocalNetDriver::messagesQueued -= 1;
  LocalNetDriver::bytesQueued -= pHold->GetSize();
  LocalNetDriver::messagesSent += 1;
  LocalNetDriver::bytesSent += pHold->GetSize();

  return pS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetConnectionEnd::ReleaseReceived( const CObj<Stream> & stream )
{
  if ( data->pAlloc )
    data->pAlloc->Release( stream );
  receivedMsg = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetConnectionEnd::~LocalNetConnectionEnd()
{
  // NI_ASSERT( !receivedMsg, "Call ReleaseReceived first" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetConnectionEnd::StartSSL( SSL_CTX* sslInitCtx, bool asServer )
{
  if ( clientSide )
  {
    data->clientSecure = !!sslInitCtx;
#if defined( NV_WIN_PLATFORM )
    data->clientSslCtx = (int)sslInitCtx;
#elif defined( NV_LINUX_PLATFORM )
    data->clientSslCtx = sslInitCtx;
#endif
  }
  else
  {
    data->serverSecure = !!sslInitCtx;
#if defined( NV_WIN_PLATFORM )
    data->serverSslCtx = (int)sslInitCtx;
#elif defined( NV_LINUX_PLATFORM )
    data->serverSslCtx = sslInitCtx;
#endif
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetConnectionEnd::ShutdownSSL()
{
  if ( clientSide )
  {
    data->clientSecure = false;
    data->clientSslCtx = 0;
  }
  else
  {
    data->serverSecure = false;
    data->serverSslCtx = 0;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetConnection::LocalNetConnection( int _connectDelay, int _latencyMs, IStreamAllocator* _pAlloc, bool _connectionDisabled )
: data( _connectDelay, _latencyMs, _pAlloc, _connectionDisabled )
{
  pClientSide = new LocalNetConnectionEnd( &data, true );
  pServerSide = new LocalNetConnectionEnd( &data, false );
  if ( _connectDelay <= 0)
    data.status = _connectionDisabled ? Network::ConnectionState::Closed : Network::ConnectionState::Connected;
  else
  {
    data.status = Network::ConnectionState::Connecting;
    data.connectStartTime = GetTickCount();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetConnection::~LocalNetConnection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::ConnectionState::Enum LocalNetConnection::GetStatus() 
{
  return data.GetStatus();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::ConnectionState::Enum LocalNetConnectionData::GetStatus()
{
  if ( status == Network::ConnectionState::Connecting )
  {
    DWORD curTime = GetTickCount();
    if ( ( (int)curTime - (int)connectStartTime ) > connectDelay )
      status = connectionDisabled ? Network::ConnectionState::Closed : Network::ConnectionState::Connected;
  }
  return status;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<Network::IConnection> LocalNetConnection::GetClientEnd( const Network::NetAddress& _address )
{
  data.address = _address;
  return StrongMT<Network::IConnection>(pClientSide);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<Network::IConnection> LocalNetConnection::GetServerEnd( const Network::NetAddress& _address )
{
  data.address = _address;
  return StrongMT<Network::IConnection>(pServerSide);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetIncomingConnections::~LocalNetIncomingConnections()
{
  serverSide.clear();
  newConnections.clear();
  deadConnections.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<Network::IConnection> LocalNetIncomingConnections::ConnectClient( const Network::NetAddress& clientAddress, IStreamAllocator* pAlloc, int connectDelay, int latency )
{
  threading::MutexLock lock( connectionsCritical );
  LocalNetConnection* pConn = new LocalNetConnection( connectDelay, latency, pAlloc, disableNewConnections );
  connections.push_back( pConn );
  Network::IConnection* pServerEnd = pConn->GetServerEnd( serverAddress );
  ((LocalNetConnectionEnd*)pServerEnd)->SetMessageReservedSpace( reservedSpace );
  newConnections.push_back( pServerEnd );
  serverSide.push_back( pServerEnd );
  return pConn->GetClientEnd( serverAddress );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LocalNetIncomingConnections::DropConnection(const Network::NetAddress& address, int id)
{
  threading::MutexLock lock( connectionsCritical );
  connections[id]->Drop();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetIncomingConnections::Update()
{
  threading::MutexLock lock( connectionsCritical );
  for ( Network::TConnections::iterator it = serverSide.begin(); it != serverSide.end(); )
  {
    if( (*it)->GetStatus() == Network::ConnectionState::Closed )
    {
      deadConnections.push_back( *it );
      it = serverSide.erase( it );
    }
    else
      ++it;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetIncomingConnections::GetNewConnections( Network::TNewConnections& _newConnections )
{
  threading::MutexLock lock( connectionsCritical );

  for ( Network::TNewConnections::iterator it = newConnections.begin(); it < newConnections.end(); )
  {
    if ( (*it)->GetStatus() == Network::ConnectionState::Connected )
    {
      _newConnections.push_back( *it );
      it = newConnections.erase( it );
    }
    else
    {
      ++it;
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetIncomingConnections::GetDroppedConnections( Network::TConnections* pConnections )
{
  threading::MutexLock lock( connectionsCritical );
  pConnections->clear();
  swap( *pConnections, deadConnections );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetDriver::LocalNetDriver()
: newConnectionsLatency(0)
, connectDelay(0)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocalNetDriver::~LocalNetDriver()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::IConnectionsManager* LocalNetDriver::CreateConnectionListener( const Network::NetAddress& onAddress, bool  )
{
  string local_address = ExtractPort(onAddress);
  StrongMT<LocalNetIncomingConnections> pIncoming = new LocalNetIncomingConnections( local_address );
  threading::MutexLock lock( connectionsCritical );
  listeningConnections.push_back( pIncoming );
  return listeningConnections.back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LocalNetDriver::DropConnection(const Network::NetAddress& address, int id)
{
  string local_address = ExtractPort(address);
  for( int i = 0; i < listeningConnections.size(); ++i )
  {
    LocalNetIncomingConnections* pConn = listeningConnections[i];
    if ( pConn->GetServerAddress() == local_address )
    {
      return pConn->DropConnection(local_address, id);
    }
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string LocalNetDriver::ExtractPort(const string& address)
{
  int index = address.find(":");
  if (index >= 0)
  {
    return address.substr(index+1, address.length());
  } else
  {
    return address;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<Network::IConnection> LocalNetDriver::Connect( const Network::NetAddress& address, bool  )
{
  Network::NetAddress local_address = ExtractPort(address);
  threading::MutexLock lock( connectionsCritical );

  for( int i = 0; i < listeningConnections.size(); ++i )
  {
    LocalNetIncomingConnections* pConn = listeningConnections[i];
    if ( pConn->GetServerAddress() == local_address )
    {
      StrongMT<Network::IConnection> pC = pConn->ConnectClient( local_address, pAlloc, connectDelay, newConnectionsLatency );
      return pC;
    }
  }

  toDrop.push_back( new LocalNetConnection( 0, 0, false ) );
  StrongMT<Network::IConnection> pC(toDrop.back()->GetClientEnd( address ));
  pC->AsyncClose();
  return pC;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetDriver::SetConnectionLatency( StrongMT<Network::IConnection>& pConnection, int latencyMs )
{
  LocalNetConnectionEnd* pEnd = dynamic_cast<LocalNetConnectionEnd*>( pConnection.Get() ); //CDynamicCast<LocalNetConnectionEnd> pEnd(pConnection);

  if ( !pEnd )
    return;

  pEnd->GetOwner()->latency = latencyMs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetDriver::SetNewConnectionsLatency( int latencyMs )
{
  newConnectionsLatency = latencyMs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetDriver::SetOpenConnectionsLatency( int latencyMs )
{
  threading::MutexLock lock( connectionsCritical );

  for( int i = 0; i < listeningConnections.size(); ++i )
  {
    LocalNetIncomingConnections* pConn = listeningConnections[i];

    Network::TConnections connections = pConn->GetConnections();
    Network::TConnections::iterator it = connections.begin(), itEnd = connections.end(); 
    for ( ;it != itEnd ; ++it )
    {
      SetConnectionLatency( *it, latencyMs );
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocalNetDriver::EnableConnectionToListener( const Network::NetAddress& address, bool enable )
{
  Network::NetAddress local_address = ExtractPort( address );
  threading::MutexLock lock( connectionsCritical );

  for( int i = 0; i < listeningConnections.size(); ++i )
  {
    LocalNetIncomingConnections* pConn = listeningConnections[i];
    if ( pConn->GetServerAddress() == local_address )
    {
      pConn->SetDisableNewConnections( !enable );
      break;
    }
  }
}

int LocalNetDriver::messagesSent = 0;
int LocalNetDriver::messagesQueued = 0;
int LocalNetDriver::bytesSent = 0;
int LocalNetDriver::bytesQueued = 0;
TModifyNetworkPacket LocalNetDriver::packetsModifier = 0;

void LocalNetDriver::ClearStatistics()
{
  messagesSent = 0;
  messagesQueued = 0;
  bytesSent = 0;
  bytesQueued = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
