#include "stdafx.h"
#include "Connection.h"
#include "Address.h"
#include "../System/Stream.h"
#include "Errors.h"
#include "../System/Win32Random.h"
#include "Socket.h"
#include "System/sleep.h"
#include "System/get_tick_count.h"
#include "System/interlocked.h"

namespace Network
{
  bool bLogRecvTime = false;
  REGISTER_VAR( "net_log_recv_time", bLogRecvTime, STORAGE_NONE );

  //ULGY: compression statistics
  volatile LONG g_uncompressedTotal = 0, g_compressedTotal = 0, g_compressedChunks = 0;

  namespace
  {
    bool useNonBlockingSockets = true;
    const bool disableNagleAlgorithm = true;
    DWORD connectTimeoutMs = 20000;

    void SetSocketOptions( socket_type socket )
    {
      NI_VERIFY_NO_RET( SetNonBlockingSocket( socket, useNonBlockingSockets ), "Can't set NON BLOCKED option." );
      NI_VERIFY_NO_RET( SetTCPNoDelay( socket, IPPROTO_TCP, disableNagleAlgorithm ), "Can't set NO DELAY option." );
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SetNonBlockingConnect( bool nonBlocking )
  {
    useNonBlockingSockets = nonBlocking;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SetConnectTimeout( int timeoutMs )
  {
    connectTimeoutMs = timeoutMs;
  }

  DWORD GenerateLatency()
  {
    if ( latencyMax == 0 && latencyMin == 0 )
      return 0;

    DWORD l = ( NWin32Random::Random( latencyMin, latencyMax ) + 
      NWin32Random::Random( latencyMin, latencyMax ) +  
      NWin32Random::Random( latencyMin, latencyMax ) ) / 3;

    return l;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Connection::Connection( const ConnectionSettings& _settings )
    : state( ConnectionState::Closed )
    , settings( _settings )
    , sendBuffer( _settings.sendBufferSize )
    , recvBuffer( _settings.receiveBufferSize, settings.receiveBufferSize )
    , useCompression( false )
    , useTLS( false )
    , wantToClose( false )
  {
    socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
#if defined( NV_WIN_PLATFORM )
    NI_VERIFY( socket != BAD_SOCKET, NI_STRFMT("Can't create socket for url. Error %d", WSAGetLastError()), return; );
#elif defined( NV_LINUX_PLATFORM )
    NI_VERIFY( socket != BAD_SOCKET, NI_STRFMT("Can't create socket for url. Error %d", errno), return; );
#endif
    SetSocketOptions( socket );
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Connection::Connection( const ConnectionSettings& _settings, socket_type _socket, const Address& _remote )
    : state( ConnectionState::Closed )
    , settings( _settings )
    , sendBuffer( _settings.sendBufferSize )
    , recvBuffer( _settings.receiveBufferSize, settings.receiveBufferSize )
    , useCompression( false )
    , useTLS( false )
    , wantToClose( false )
  {
    const bool validated = _socket != BAD_SOCKET;
    NI_ASSERT( validated, "Invalid socket." );

    if( validated )
    {
      socket = _socket;
      state = ConnectionState::Connected;
      remote = _remote;

      SetSocketOptions( socket );
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Connection::~Connection()
  {
    Close();
    SMsg s;
    while( sendList.Dequeue( s ) )
      ReleaseReceived( s.pS );
    while( recvList.Dequeue( s ) )
      ReleaseReceived( s.pS );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::EnableCompression()
  {
    useCompression = true;
    compressor.Init( settings.sendBufferSize, true );
    decompressor.Init( settings.receiveBufferSize );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::Close()
  {
    if( state != ConnectionState::Closed )
    {
      CloseSocket( socket );
      socket = BAD_SOCKET;
      state = ConnectionState::Closed;
      wantToClose = false;
    }
      if ( incompleteMsg )
      {
        ReleaseReceived( incompleteMsg );
        incompleteMsg = 0;
      }
    }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Connection::Connect( const char* url )
  {
    Address address( url );
    if ( !ConnectSocket( socket, address ) )
    {
      const int result = GetSocketError();
#if defined( NV_WIN_PLATFORM )
      NI_VERIFY( result == WSAEWOULDBLOCK, NI_STRFMT( "Can't connect to url %s. Error %d", url, result ), return false; );
#elif defined( NV_LINUX_PLATFORM )
      NI_VERIFY( result == EWOULDBLOCK, NI_STRFMT( "Can't connect to url %s. Error %d", url, result ), return false; );
#endif

      connectingStartTime = nival::get_tick_count();
      state = ConnectionState::Connecting;
    }
    else
    {
      state = ConnectionState::Connected;
    }
    remote = address;
    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CObj<Stream> Connection::GetBufferToSend()
  {
    if ( settings.pAlloc )
      return settings.pAlloc->Allocate();

    return new MemoryStream;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Connection::Send( const CObj<Stream> & data )
  {
    if( state == ConnectionState::Closed )
    {
      ReleaseReceived( data );
      return false;
    }

    NI_VERIFY( data->GetSize() <= MAX_MESSAGE_SIZE, "Packet too large, cannot process", return false );

    if( !IsValid( data ) && !data->IsOk() )
      return false;

    SMsg msg; 
    msg.sendTime = GetTickCount() + GenerateLatency();
    msg.pS = data;
    sendList.Enqueue( msg );

    Instrumentation::sendQueueSize.AddValue( 1 );

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CObj<Stream> Connection::Receive()
  {
    SMsg msg;
    if (!recvList.Pick( msg ))
      return 0;

    if ( msg.sendTime > GetTickCount() )
      return 0;

    recvList.Dequeue( msg );
    Instrumentation::recvQueueSize.DecValue( 1 );
    Instrumentation::messagesReceived.AddValue( 1 );

    if (Network::bLogRecvTime)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << 
        "network: recv.OUT (time = "<< NHPTimer::GetScalarTime() << 
        " msg.size = " << msg.pS->GetSize() << 
        " queue.size = " << recvList.Size() << 
        " tid = " << threading::CurrentThreadID() << 
        ")" << endl;
    }

    return msg.pS;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::ReleaseReceived( const CObj<Stream> & stream )
  {
    if ( settings.pAlloc )
      settings.pAlloc->Release( stream );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Connection::HasDataToSend()
  {
    if ( useTLS )
    {
      return sslEncoder.GetNetBytesOut() > 0; 
    }
    if ( useCompression )
    {
      return compressor.GetOutDataSize() > 0;
    }
    return sendBuffer.HasData();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Connection::HasSpaceToReceive()
  {
    if ( useTLS )
    {
      return sslEncoder.GetNetBytesIn();
    }
    if ( useCompression )
    {
      return decompressor.GetBufferInSize() > 0;
    }
    return recvBuffer.HasSpaceToWrite();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::AddSelf( fd_set *readSet, fd_set *writeSet, fd_set *exceptSet )
  {
    if ( state != ConnectionState::Connected && state != ConnectionState::Connecting )
      return;

    if ( HasSpaceToReceive() )
      FD_SET( socket, readSet );

    if ( state == ConnectionState::Connecting  || HasDataToSend() )
      FD_SET( socket, writeSet );

    if ( state == ConnectionState::Connecting )
      FD_SET( socket, exceptSet );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::DoIO( fd_set *readSet, fd_set *writeSet, fd_set *exceptSet )
  {
    if ( state == ConnectionState::Connecting )
    {
      DWORD now = ::GetTickCount();
 
      if ( now - connectingStartTime > connectTimeoutMs )
      {
        Close();
      }
      else if ( FD_ISSET( socket, writeSet ) )
      {
        state = ConnectionState::Connected;
      }
      else if ( FD_ISSET( socket, exceptSet ) )
      {
        int error_code = 0;
        NI_VERIFY_NO_RET( GetSocketOption( socket, SOL_SOCKET, SO_ERROR, error_code ), "getsockopt() error" );
        LOG_D(0) << "socket " << socket << " error code " << error_code;

        Close();
      }
      return;
    }

    if ( state != ConnectionState::Connected )
      return;

    settingsChangeCritical.Lock();

    uint sendCount = 0;
    while( sendCount++ < settings.maxSendsOnStep )
    {
      if ( ProcessWrite( FD_ISSET( socket, writeSet ) ) <= 0 )
        break;
    }

    if ( useTLS )
      sslEncoder.Step();

    sendCount = 0;
    while( sendCount++ < settings.maxSendsOnStep )
    {
      if ( !ProcessRead( FD_ISSET( socket, readSet ) ) )
        break;
    }

    settingsChangeCritical.Unlock();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::StartSSL( SSL_CTX* sslInitCtx, bool isServer )
  {
    settingsChangeCritical.Lock();
    NI_ASSERT( !HasDataToSend(), "Starting TLS connection while some data has not been sent to peer. Data loss will occur" );
    sslEncoder.Init( sslInitCtx, isServer );
    useTLS = true;
    settingsChangeCritical.Unlock();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::ShutdownSSL()
  {
    settingsChangeCritical.Lock();
    //NI_ASSERT( !HasDataToSend(), "Shutting down TLS connection while some data has not been sent to peer. Data loss will occur" );
    useTLS = false;
    sslEncoder.Close();
    settingsChangeCritical.Unlock();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int Connection::ProcessWrite( bool socketReady )
  {
    DWORD time = GetTickCount();
    while( true )
    {
      SMsg msg;
      if ( !sendList.Pick( msg ) )
        break;

      if ( msg.sendTime > time )
        break;

      bool res = sendBuffer.AddMessage( (byte*)msg.pS->GetBuffer() + settings.reservedSpaceOnMessageStart, msg.pS->GetSize() - settings.reservedSpaceOnMessageStart );
      NI_ASSERT( msg.pS->GetSize() < sendBuffer.GetTotalSize(), "Buffer too small" );

      if ( !res )
        break;

      if ( !sendList.Dequeue( msg ) )
        NI_ALWAYS_ASSERT( "Deque failed!" );

      Instrumentation::messageSizeAvg.SetValue( Instrumentation::messageSizeAvg.GetValue() * 0.99f + msg.pS->GetSize() * (1 - 0.99f) );
      Instrumentation::messageSizeMax.SetValue( Max( Instrumentation::messageSizeMax.GetValue(), msg.pS->GetSize() ) );

      if ( settings.pAlloc ) 
        settings.pAlloc->Release( msg.pS );

      Instrumentation::messagesSent.AddValue( 1 );
      Instrumentation::sendQueueSize.DecValue( 1 );
    }


    // Write: sendBuffer -> [compressor] -> [sslEncoder] ->socket
    byte* data = 0;
    int size = 0;
    enum EDataSource
    {
      SSendBuffer,
      SCompressor,
      SSSLencoder,
    };
    EDataSource src;


    sendBuffer.GetData( &data, &size );
    src = SSendBuffer;

    if ( useCompression )
    {
      if ( size > 0 )
      {
        nival::interlocked_exchange_add< LONG >( g_uncompressedTotal, size );

        compressor.SetDataIn( data, size );
        int sent = compressor.GetDataInProcessed();
        compressor.ProcessedDataIn();

        nival::interlocked_increment( g_compressedChunks );

        sendBuffer.ReleaseData( sent );
      }
      compressor.Flush();
      compressor.GetDataOut( &data, &size );
      src = SCompressor;

      nival::interlocked_exchange_add< LONG >( g_compressedTotal, size );
    }

    if( useTLS )
    {
      if( size > 0 )
      {
        int sent = sslEncoder.WriteAppData( data, size );

        if ( src == SSendBuffer )
          sendBuffer.ReleaseData( sent );
        else if ( src == SCompressor )
        {
          if ( sent > 0 )
            compressor.ProcessedDataOut(); //TODO enable partial processing
        }
      }
      sslEncoder.GetNetDataOut( &data, &size );
      src = SSSLencoder;
    }

    if ( socketReady )
    {
      if ( size > 0 )
      {
        int sizeLeft = size; 
        byte* dataLeft = data;
        while ( sizeLeft > 0 ) 
        {
          int sent = ::send( socket, (const char*)dataLeft, sizeLeft, 0 );

#if defined( NV_WIN_PLATFORM )
          if ( sent == SOCKET_ERROR )
#elif defined( NV_LINUX_PLATFORM )
          if ( sent == -1 )
#endif
          {
            int err = GetSocketError();
#if defined( NV_WIN_PLATFORM )
            if( err != WSAEWOULDBLOCK )
#elif defined( NV_LINUX_PLATFORM )
            if( err != EWOULDBLOCK )
#endif
            {
              systemLog(NLogg::LEVEL_DEBUG) << "Send error on socket " << socket << " ( " << remote.GetIp() << " :" << remote.GetPort() << "): " << err << endl;
              Close();
            }
            sent = 0;
            break;
          }
          else if ( sent == 0 )
            break;

          Instrumentation::bytesSent.AddValue( sent );
          sizeLeft -= sent;
          dataLeft += sent;
        }
        int sent = size - sizeLeft;

        if ( src == SSendBuffer )
          sendBuffer.ReleaseData( sent );
        else if ( src == SCompressor )
        {
          NI_ASSERT( state == ConnectionState::Closed || sent == compressor.GetOutDataSize(), "Ask S.Eliseev about partial processing in Connection class" );
          compressor.ProcessedDataOut(); //TODO enable partial processing
        }
        else 
          sslEncoder.CommitNetBufferOut( sent );

        return sent;
      }
    }
    return 0;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Connection::ProcessRead( bool socketReady )
  {
    // Read: socket -> [sslEncoder] -> [decompressor] -> recvBuffer
    byte* data = 0;
    int size = 0;
    enum EBufferSource
    {
      SSSLencoder,
      SDecompressor,
      SRecvBuffer,
    };
    EBufferSource src;

    bool hasMoreDataInSocket = false;
    if ( socketReady )
    {
      if( useTLS )
      {
        sslEncoder.GetNetBufferIn( &data, &size );
        src = SSSLencoder;
      }
      else if ( useCompression )
      {
        decompressor.GetBufferIn( &data, &size );
        src = SDecompressor;
      }
      else
      {
        recvBuffer.GetWriteBuffer( &data, &size );
        src = SRecvBuffer;
      }

      int res = ::recv( socket, (char*)data, size, 0 );
      if ( res == 0 )
      { // connection was dropped
        int err = GetSocketError();
        if( err != 0 )
        {
          systemLog(NLogg::LEVEL_DEBUG) << "Socket " << socket << " ( " << remote.GetIp() << " :" << remote.GetPort() << ") closed with error " << err << endl;
        }
        Close();
      }
      else if ( res <= 0 )
      { // got error or connection was dropped
        res = 0;
        int err = GetSocketError();
#if defined( NV_WIN_PLATFORM )
        if( err != WSAEWOULDBLOCK )
#elif defined( NV_LINUX_PLATFORM )
        if( err != EWOULDBLOCK )
#endif
        {
          if( err != 0 )
          {
            systemLog(NLogg::LEVEL_DEBUG) << "Socket " << socket << " ( " << remote.GetIp() << " :" << remote.GetPort() << ") closed with error " << err << endl;
          }
          Close();
        }
        else
        {
          // workaround for Windows Sockets bug
        }
      }
      else
      {
        hasMoreDataInSocket = true;//@SE@TODO use ioctlsocket( FIONREAD ... ) ? or rely on recv() error WSAEWOULDBLOCK?

        Instrumentation::bytesReceived.AddValue( res );
        if ( src == SSSLencoder )
          sslEncoder.CommitNetBufferIn( res );
        else if ( src == SDecompressor )
          decompressor.CommitBufferIn( res );
        else 
          recvBuffer.CommitWriteBuffer( res );
      }
    }

    if ( useTLS )
    {
      if ( useCompression )
      {
        decompressor.GetBufferIn( &data, &size );
        src = SDecompressor;
      }
      else
      {
        recvBuffer.GetWriteBuffer( &data, &size );
        src = SRecvBuffer;
      }
      int res = sslEncoder.ReadAppData( data, size );

      if ( src == SDecompressor )
        decompressor.CommitBufferIn( res );
      else 
        recvBuffer.CommitWriteBuffer( res );
    }

    if ( useCompression )
    {
      recvBuffer.GetWriteBuffer( &data, &size );

      decompressor.SetBufferOut( data, size );
      int res = decompressor.GetReadyOutData();

      recvBuffer.CommitWriteBuffer( res );
    }

    int nextMsgSize = 0;
    while ( ( nextMsgSize = recvBuffer.ReadNextMessageSize() ) != 0 )
    {
      if ( !incompleteMsg )
      {
        if ( settings.pAlloc ) 
        {
          incompleteMsg = settings.pAlloc->Allocate();
          incompleteMsg->SetSize( nextMsgSize + settings.reservedSpaceOnMessageStart );
        }
        else
          incompleteMsg = new MemoryStream( nextMsgSize + settings.reservedSpaceOnMessageStart );

        incompleteMsg->Seek( settings.reservedSpaceOnMessageStart, SEEKORIGIN_BEGIN );
      }
      else
        NI_ASSERT( incompleteMsg->GetSize() == nextMsgSize, "Internal error" );

      bool res = recvBuffer.CopyMessage( (byte*)incompleteMsg->GetBuffer() + settings.reservedSpaceOnMessageStart, nextMsgSize );

      if ( !res )
        break;

      SMsg msg;
      msg.sendTime = nival::get_tick_count() + GenerateLatency();
      msg.pS = incompleteMsg;
      incompleteMsg = 0;

      Instrumentation::messageSizeAvg.SetValue( Instrumentation::messageSizeAvg.GetValue() * 0.99f + msg.pS->GetSize() * (1 - 0.99f) );
      Instrumentation::messageSizeMax.SetValue( Max( Instrumentation::messageSizeMax.GetValue(), msg.pS->GetSize() ) );

      recvList.Enqueue( msg );
      Instrumentation::recvQueueSize.AddValue( 1 );

      if (Network::bLogRecvTime)
      {
        systemLog(NLogg::LEVEL_MESSAGE) << 
          "network: recv.IN  (time = "<< NHPTimer::GetScalarTime() << 
          " msg.size = " << msg.pS->GetSize() << 
          " queue.size = " << recvList.Size() << 
          " tid = " << threading::CurrentThreadID() << 
          ")" << endl;
      }
    }
    
    return hasMoreDataInSocket;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::SetSystemSendBufferSize( int newSize )
  {
    NI_VERIFY_NO_RET( SetSocketOption( socket, SOL_SOCKET, SO_SNDBUF, newSize ), "setsockopt() error" );
    int sndBufLen = 0;
    NI_VERIFY_NO_RET( GetSocketOption( socket, SOL_SOCKET, SO_SNDBUF, sndBufLen ), "getsockopt() error" );
    NI_ASSERT( sndBufLen == newSize, NI_STRFMT( "Socket does not support send buffer size of %d", newSize ) );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Connection::SetMessageReservedSpace( int space )
  {
    settings.reservedSpaceOnMessageStart = space;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ConnectionListener::ConnectionListener( const char* url )
    : state( ConnectionState::Closed )
    , socket( BAD_SOCKET )
  {
    if ( !url )
      return;

    socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    NI_ASSERT( socket != BAD_SOCKET, "Can't create socket for url." );
    if( socket != BAD_SOCKET )
    {
      nival::sleep(5); // иначе такое впечатление, что быстрый bind/listen что-то ломает в WinSock при запуске серверных сервисов

      state = ConnectionState::Connecting;
      SetSocketOptions( socket );
      const Address address( url );
      if ( !BindSocket( socket, address ) )
      {
        LOG_W(0) << "Error bind socket: " << GetSocketError() << " on address " << address;
        Close();
      }
      else
      {
        LOG_D(0) << "Success binding socket " << socket << " on address " << address;
      }
    }
    else
    {
      LOG_W(0) << "Error creating socket for url " << url;
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool ConnectionListener::Listen()
  {
    if( socket != BAD_SOCKET )
    {
      if( ::listen( socket, SOMAXCONN ) == 0 )
      {
        state = ConnectionState::Connected;
        return true;
      }
      else
      {
        systemLog( NLogg::LEVEL_WARNING ) << "Error listening for socket: " << GetSocketError();
      }
    }
    return false;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ConnectionListener::~ConnectionListener()
  {
    Close();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  socket_type ConnectionListener::Accept( Address* pRemote ) const
  {
    if ( state == ConnectionState::Closed )
    {
      LOG_W(0) << "Accept on a CLOSED socket " << socket;  
      return BAD_SOCKET;
    }

    // Check and return without waiting
#if defined( NV_WIN_PLATFORM )
    TIMEVAL tm = { 0, 0 };
#elif defined( NV_LINUX_PLATFORM )
    timeval tm = { 0, 0 };
#endif
    fd_set errorSet, readSet;

    // Set up the socket sets we are interested in (just this one)
    FD_ZERO( &errorSet );
    FD_SET( socket, &errorSet );
    FD_ZERO( &readSet );
    FD_SET( socket, &readSet );
    // Check the status of the bits. First check for errors
    int nSelectRes = select( 1, &readSet, 0, &errorSet, &tm );
#if defined( NV_WIN_PLATFORM )
    if ( SOCKET_ERROR == nSelectRes )
#elif defined( NV_LINUX_PLATFORM )
    if ( -1 == nSelectRes )
#endif
    {
      NI_ALWAYS_ASSERT(NI_STRFMT("Select failed with error %d.", GetSocketError()));  
    }

    if ( nSelectRes )
    {
      if ( !FD_ISSET( socket, &errorSet ) && FD_ISSET( socket, &readSet ) )
      {
        Address & remote = *pRemote;
        return AcceptSocket( socket, remote );
      }
      else
      {
        int error_code = 0;
        NI_VERIFY_NO_RET( GetSocketOption( socket, SOL_SOCKET, SO_ERROR, error_code ), "getsockopt() error" );
        LOG_W(0) << "Accept ERROR on socket " << socket << ", error code " << error_code;  
      }
    }

    return BAD_SOCKET;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionListener::Close()
  {
    if( state != ConnectionState::Closed )
    {
      CloseSocket( socket );
      socket = BAD_SOCKET;
      state = ConnectionState::Closed;
    }
  }

  void IConnection::DumpCompressionStatistics()
  {
    DebugTrace( "Traffic compression statistics:" );
    DebugTrace( "Uncomp total %ikb, comp total %ikb in %ik chunks", (long)g_uncompressedTotal / 1024l, (long)g_compressedTotal / 1024l, (long)g_compressedChunks / 1024l );
#if defined( NV_WIN_PLATFORM )
    DebugTrace( "Average compression: %i%%", g_uncompressedTotal ? (int)( 100 * (LONGLONG)g_compressedTotal / (LONGLONG)g_uncompressedTotal ) : 0 );
#elif defined( NV_LINUX_PLATFORM )
    DebugTrace( "Average compression: %i%%", g_uncompressedTotal ? (int)( 100 * (long long)g_compressedTotal / (long long)g_uncompressedTotal ) : 0 );
#endif
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

NI_DEFINE_REFCOUNT( Network::Connection );


