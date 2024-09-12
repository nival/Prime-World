#include "stdafx.h"
#include "FreePortsFinder.h"
#include "System/Thread.h"
#include "Address.h"

#include "Socket.h"
namespace Network
{

class NetworkFreePortsFinderImpl : public IFreePortsFinder, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( NetworkFreePortsFinderImpl, IFreePortsFinder, BaseObjectMT );

public:
  NetworkFreePortsFinderImpl( int _iniPort ) :
  nextFreePort( _iniPort )
  {}

  virtual int GetFreePort()
  {
    int result = 0;

    threading::MutexLock lock( mutex );

    socket_type sock = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
#ifdef NV_WIN_PLATFORM
    SetSocketOption( sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, 1 );
#endif // NV_WIN_PLATFORM

    Address addr( static_cast< Address::IP >( INADDR_ANY ), nextFreePort );

    bool res = false;
    do
    {
      addr.SetPort( nextFreePort );
      res = BindSocket( sock, addr );
      result = nextFreePort;
      ++nextFreePort;
    }
    while ( !res );

    CloseSocket( sock );

    return result; 
  }

  unsigned short nextFreePort;
  threading::Mutex mutex;
};



IFreePortsFinder * NewFreePortsFinder( int firstFreePort )
{
  return new NetworkFreePortsFinderImpl( firstFreePort );
}

}
