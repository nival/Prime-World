#ifndef LOCALNETDRIVER_H_05F53901_6C84_4
#define LOCALNETDRIVER_H_05F53901_6C84_4
#include "Network.h"
#include "../System/Singleton.h"
#include "../System/Thread.h"

namespace	Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LocalNetConnection;
class LocalNetDriver;

struct LocalNetConnectionData
{
  struct SMsg
  {
    CObj<Stream> pS;
    DWORD sendTime;
    SMsg() : sendTime( 0 ) {}
    SMsg( Stream* _pS, DWORD _sendTime ) : pS(_pS), sendTime(_sendTime) {}
  };
  typedef list<SMsg> TQueue;

  Network::NetAddress address;

  TQueue toServerQueue;
  TQueue fromServerQueue;
  threading::Mutex toServerCritical;
  threading::Mutex fromServerCritical;
  bool serverSecure;
  bool clientSecure;
#if defined( NV_WIN_PLATFORM )
  int serverSslCtx;
#elif defined( NV_LINUX_PLATFORM )
  void * serverSslCtx;
#endif
#if defined( NV_WIN_PLATFORM )
  int clientSslCtx;
#elif defined( NV_LINUX_PLATFORM )
  void * clientSslCtx;
#endif

  int connectDelay;
  int latency;
  bool connectionDisabled;
  IStreamAllocator* pAlloc;

  DWORD connectStartTime;
  Network::ConnectionState::Enum status;

  LocalNetConnectionData( int _connectDelay, int _latencyMs, IStreamAllocator* _pAlloc, bool _connectionDisabled )
    : serverSecure( false ), serverSslCtx( 0 ), clientSecure( false ), clientSslCtx( 0 )
    ,  connectDelay(_connectDelay), latency(_latencyMs), connectionDisabled(_connectionDisabled), pAlloc(_pAlloc)
    , connectStartTime(0), status( Network::ConnectionState::Closed ) {}
  LocalNetConnectionData() 
    : serverSecure( false ), serverSslCtx( 0 ), clientSecure( false ), clientSslCtx( 0 )
    , connectDelay(0), latency(0), connectionDisabled(false), pAlloc(0)
    , connectStartTime(0), status( Network::ConnectionState::Closed ) {}
  Network::ConnectionState::Enum GetStatus();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LocalNetConnectionEnd : public BaseObjectMT, public Network::IConnection
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalNetConnectionEnd, BaseObjectMT, Network::IConnection )

  LocalNetConnectionData* data;
  bool clientSide;

  CObj<Stream> receivedMsg;
  int reservedSpace;

  LocalNetConnectionEnd() : data(0) {}
public:		 	
  LocalNetConnectionEnd( LocalNetConnectionData* _data, bool _clientSide ) 
    : data( _data ), clientSide(_clientSide ), reservedSpace( 0 ) {}
  ~LocalNetConnectionEnd();

  LocalNetConnectionData* GetOwner() const { return data; }
  void Close();
  virtual void AsyncClose();
  Network::ConnectionState::Enum GetStatus() const;
  void SetSystemSendBufferSize( int ) {}
  void SetMessageReservedSpace( int space ) { reservedSpace = space; }

  const Network::NetAddress& GetAddress() const;
  virtual const Address& GetRemoteAddress() const 
  {
    NI_ALWAYS_ASSERT("should be never invoked.");
    return *(new Address());
  }

  virtual CObj<Stream> GetBufferToSend();
  virtual bool Send( const CObj<Stream> & data );
  virtual CObj<Stream> Receive();
  virtual void ReleaseReceived( const CObj<Stream> & stream );

  void StartSSL( SSL_CTX* sslInitCtx, bool asServer );
  void ShutdownSSL();

  bool HasUnsentData() const { return false; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LocalNetConnection: public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( LocalNetConnection, BaseObjectMT )

  StrongMT<LocalNetConnectionEnd> pClientSide;
  StrongMT<LocalNetConnectionEnd> pServerSide;

  LocalNetConnection() {}

  LocalNetConnectionData data;
public:
  LocalNetConnection( int connectDelay, int latencyMs, IStreamAllocator* pAlloc,  bool connectionDisabled = false );
  ~LocalNetConnection();
  Network::ConnectionState::Enum GetStatus();
  void Drop() { data.status = Network::ConnectionState::Closed; }
  void SetLatency( int latencyMs ) { data.latency = latencyMs; }
  StrongMT<Network::IConnection> GetClientEnd( const Network::NetAddress& address );
  StrongMT<Network::IConnection> GetServerEnd( const Network::NetAddress& address );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LocalNetIncomingConnections : public BaseObjectMT, public Network::IConnectionsManager
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalNetIncomingConnections, BaseObjectMT, Network::IConnectionsManager )
  
public:
  LocalNetIncomingConnections( const Network::NetAddress& _serverAddress ) : serverAddress(_serverAddress), disableNewConnections( false ), reservedSpace(0) {}
  ~LocalNetIncomingConnections();

  // IConnectionsManager
  virtual void GetNewConnections( Network::TNewConnections& );
  virtual Network::TConnections GetConnections() const
  {
    return serverSide;
  }
  void SetMessageReservedSpace( int space ) { reservedSpace = space; }

  StrongMT<Network::IConnection> ConnectClient( const Network::NetAddress& clientAddress, IStreamAllocator* pAlloc, int connectDelay, int latency );
  void Update();
  const Network::NetAddress& GetServerAddress() const { return serverAddress; }

  void GetDroppedConnections( Network::TConnections* pConnections );
  bool DropConnection(const Network::NetAddress& address, int id);

  void SetDisableNewConnections( bool disable ) { disableNewConnections = disable; } 
private:
  LocalNetIncomingConnections(){}
  Network::NetAddress serverAddress;
  vector<StrongMT<LocalNetConnection> > connections;
  Network::TConnections serverSide;
  Network::TNewConnections newConnections;
  Network::TConnections deadConnections;
  threading::Mutex connectionsCritical;
  bool disableNewConnections;
  int reservedSpace;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (* TModifyNetworkPacket)( const Network::NetAddress& address, bool toListener, Stream* pStream );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LocalNetDriver : public Network::INetworkDriver, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalNetDriver, BaseObjectMT, Network::INetworkDriver )

public:
  LocalNetDriver();
  ~LocalNetDriver();

  virtual Network::IConnectionsManager* CreateConnectionListener( const Network::NetAddress& onAddress, bool useCompression = false );
  virtual StrongMT<Network::IConnection> Connect( const Network::NetAddress& address, bool useCompression = false );
  virtual void SetTrafficType( EDriverTrafficType::Enum ) {}

  virtual void SetStreamAllocator( IStreamAllocator* alloc ) { pAlloc = alloc; }
  virtual IStreamAllocator* GetStreamAllocator() const { return pAlloc; }

  bool DropConnection(const Network::NetAddress& address, int id);

  void SetNewConnectionsLatency( int latencyMs );
  void SetOpenConnectionsLatency( int latencyMs );
  static void SetConnectionLatency( StrongMT<Network::IConnection>& pConnection, int latencyMs );

  void SetConnectDelay( int delayMs ) { connectDelay = delayMs; }

  void EnableConnectionToListener( const Network::NetAddress& address, bool enable );

  static void ClearStatistics();

  static int messagesSent;
  static int messagesQueued;
  static int bytesSent;
  static int bytesQueued;
  static TModifyNetworkPacket packetsModifier;

private:
  vector<StrongMT<LocalNetIncomingConnections> > listeningConnections;
  vector<StrongMT<LocalNetConnection> > toDrop;
  threading::Mutex connectionsCritical;
  int newConnectionsLatency;
  int connectDelay;
  StrongMT<IStreamAllocator> pAlloc;

  string ExtractPort(const string& address);
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif //#define LOCALNETDRIVER_H_05F53901_6C84_4
