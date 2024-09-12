#ifndef NETWORK_H_CEC44C37_7742_4919_81B
#define NETWORK_H_CEC44C37_7742_4919_81B
#include "System/ChunklessSaver.h"
#include "Address.h"
#include "Network/ConnectionState.h"

class Stream;

struct ssl_ctx_st;
typedef struct ssl_ctx_st SSL_CTX;

namespace Network
{
  const unsigned int HEADER_SIZE = sizeof(ushort);
  const unsigned int MAX_MESSAGE_SIZE = 0xFFFF - HEADER_SIZE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EDriverTrafficType
{
  enum Enum
  {
    // for simulator
    ExtraLight,
    // client-client or client-relay: many connections, light traffic on each
    Light,
    // server-server: small number of connections, high traffic
    Heavy,
  };
}		



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IStreamAllocator : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IStreamAllocator, IBaseInterfaceMT )

  virtual CObj<Stream> Allocate() = 0;
  virtual void Release( const CObj<Stream> & pS ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IConnection: public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IConnection, IBaseInterfaceMT )

  virtual ConnectionState::Enum GetStatus() const = 0;

  virtual void SetSystemSendBufferSize( int newSize ) = 0;

  virtual void AsyncClose() = 0;

  //“ут мы отходим от стандарта и возвращаем из функций CObj<> по значению и передаем его по константной ссылке
  //ѕочему? -ј потому, что мы имеем большие проблемы с временем жизни объектов Stream из-за хранени€ и распространени€ raw-указателей
  virtual CObj<Stream> GetBufferToSend() = 0;
  virtual bool Send( const CObj<Stream> & data ) = 0;

  virtual CObj<Stream> Receive() = 0;
  virtual void ReleaseReceived( const CObj<Stream> & data ) = 0;

  virtual void StartSSL( SSL_CTX* sslInitCtx, bool asServer ) = 0;
  virtual void ShutdownSSL() = 0;

  virtual const Address& GetRemoteAddress() const = 0;

  static void DumpCompressionStatistics();
};

typedef vector<StrongMT<IConnection> > TConnections; // это дл€ хранени€ original connection-ов
typedef vector<StrongMT<IConnection> > TNewConnections; // а это будем использовать дл€ того, что передаетс€ через GetNewConnections

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IConnectionsManager: public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IConnectionsManager, IBaseInterfaceMT )

  virtual void GetNewConnections( TNewConnections& ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface INetworkDriver : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( INetworkDriver, IBaseInterfaceMT )

  virtual IConnectionsManager* CreateConnectionListener( const string& url, bool useCompression = false ) = 0;
  virtual StrongMT<IConnection> Connect( const string& url, bool useCompression = false ) = 0;

  virtual void SetTrafficType( EDriverTrafficType::Enum value ) = 0;

  virtual void SetStreamAllocator( IStreamAllocator* alloc ) = 0;
  virtual IStreamAllocator* GetStreamAllocator() const = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsConnectionClosed( IConnection* pConnection );


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ISSLContextReader : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISSLContextReader, IBaseInterfaceMT )

  virtual bool LoadFromString( const string& str ) = 0;
  virtual bool LoadFromStream( Stream* pStream ) = 0;
  virtual SSL_CTX* GetContext() = 0;
};

}//namespace Network

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void SendMessageHelper( Network::IConnection* pConn, T& msg )
{
  CObj<Stream> pMsg = pConn->GetBufferToSend();
  CObj<IBinSaver> pSaver = CreateChunklessSaver( (MemoryStream*)pMsg.GetPtr(), 0, false );
  msg & (*pSaver);

  pConn->Send( pMsg );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define NETWORK_H_CEC44C37_7742_4919_81B
