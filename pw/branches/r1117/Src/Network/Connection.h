#ifndef CONNECTION_H_E7BC5028_F026_48B8
#define CONNECTION_H_E7BC5028_F026_48B8
#include "Network.h"
#include "Socket.h"
#include "Address.h"
#include "NetworkBuffers.h"
#include "../System/Thread.h"
#include "../System/TSList.h"
#include "SSLEncoder.h"
#include "DriverSettings.h"

namespace Network
{
  _interface IStreamAllocator;

  struct ConnectionSettings
  {
    uint receiveBufferSize;
    uint sendBufferSize;
    uint networkThreadSleepInterval;
    uint maxSendsOnStep;
    uint reservedSpaceOnMessageStart;
    IStreamAllocator* pAlloc;

    ConnectionSettings() : pAlloc(0) {}
    ConnectionSettings( uint _receiveBufferSize, uint _sendBufferSize, uint _networkThreadSleepInterval, uint _maxSendsOnStep ) 
      : receiveBufferSize( _receiveBufferSize ), sendBufferSize( _sendBufferSize ), networkThreadSleepInterval( _networkThreadSleepInterval ), maxSendsOnStep( _maxSendsOnStep )
      , reservedSpaceOnMessageStart(0), pAlloc(0)
    {
      sendBufferSize = Max( sendBufferSize, MAX_MESSAGE_SIZE );
      receiveBufferSize = Max( receiveBufferSize, MAX_MESSAGE_SIZE );
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  class Queue
  {
  public:
    Queue() {};
    ~Queue() {};

  public:
    void Enqueue(T const & data)
    {
      threading::MutexLock lock(mx_);
      queue_.push_back(data);
    }

    bool Pick(T & data)
    {
      threading::MutexLock lock(mx_);
      if (queue_.size())
        data = queue_.front();

      return (queue_.size() != 0);
    }

    bool Dequeue(T & data )
    {
      threading::MutexLock lock(mx_);
      size_t sz = queue_.size();
      if (sz)
      {
        data = queue_.front();
        queue_.pop_front();
      }
      return (sz != 0);
    }

    unsigned int Size() const
    {
      threading::MutexLock lock(mx_);
      return (unsigned int)queue_.size();
    }

  private:
    nstl::list<T> queue_;
    threading::Mutex mx_;
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class Connection : public BaseObjectMT, public IConnection
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Connection, BaseObjectMT, IConnection )

  public:
    Connection( const ConnectionSettings& settings );
    /** initialize by existing socket */
    Connection( const ConnectionSettings& settings, socket_type socket, const Address& remote );
    ~Connection();

    void EnableCompression();
    bool Connect( const char* url );

    // IConnection methods

    virtual ConnectionState::Enum GetStatus() const { return state; }
    virtual const Address& GetRemoteAddress() const { return remote; }

    virtual void SetSystemSendBufferSize( int newSize );
    virtual void SetMessageReservedSpace( int space );

    virtual void AsyncClose() { wantToClose = true; }
    bool WantAsyncClose() const { return wantToClose; }
    void Close();

    void AddSelf( fd_set* readSet, fd_set* writeSet, fd_set* exceptSet );
    void DoIO( fd_set* readSet, fd_set* writeSet, fd_set* exceptSet );

    virtual CObj<Stream> GetBufferToSend();
    virtual bool Send( const CObj<Stream> & data );

    virtual CObj<Stream> Receive();
    virtual void ReleaseReceived( const CObj<Stream> & data );

    virtual void StartSSL( SSL_CTX* sslInitCtx, bool asServer );
    virtual void ShutdownSSL();

  private:
    Connection()
      : wantToClose(false), state( ConnectionState::Closed ) , sendBuffer( 0 ) , recvBuffer( 0, 0 ) , useCompression( false ) , useTLS( false )
    {}


    ConnectionSettings settings;
    socket_type socket;
    Address	remote;
    ConnectionState::Enum state;
    bool wantToClose;
    DWORD connectingStartTime;

    bool useTLS;
    SSLEncoder sslEncoder;

    bool useCompression;
    ZlibDecomressor decompressor;
    ZlibComressor compressor;

    GatherMessageBuffer sendBuffer;
    ScatterMessageBuffer recvBuffer;
    CObj<Stream> incompleteMsg;

    struct SMsg
    {
      CObj<Stream> pS;
      DWORD sendTime;
      SMsg() : sendTime( 0 ) {}
      SMsg( Stream* _pS, DWORD _sendTime ) : pS(_pS), sendTime(_sendTime) {}
    };
    typedef Network::Queue<SMsg> TQueue;

    TQueue sendList;
    TQueue recvList;

    threading::Mutex settingsChangeCritical;

    bool HasDataToSend();
    bool HasSpaceToReceive();

    int DoSocketRead( byte* buf, int len );
    int DoSocketWrite( const byte* buf, int len );

    int ProcessWrite( bool socketReady );
    bool ProcessRead( bool socketReady );
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConnectionListener
{
public:
    ConnectionListener( const char* url = 0 );
    ~ConnectionListener();

    bool Listen();
    socket_type Accept( Address* pRemote ) const;

    ConnectionState::Enum GetStatus() const { return state; }
    void Close();
private:

    socket_type socket;
    ConnectionState::Enum state;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif //#define CONNECTION_H_E7BC5028_F026_48B8
