#ifndef CONNECTIONMANAGER_H_A457162F_098
#define CONNECTIONMANAGER_H_A457162F_098
#include "Network.h"
#include "ConnectionsContainer.h"
#include "Connection.h"
#include "System/Thread.h"

namespace Network
{
  class Connection;

  class IncomingConnectionManager : public IConnectionsManager, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( IncomingConnectionManager, IConnectionsManager, BaseObjectMT )
    
    IncomingConnectionManager() {}		

    ConnectionListener listener; 
    ConnectionsContainer container;
    bool useCompressionForNewConnections;
    ConnectionSettings settings;

    TNewConnections newConnections;

    nstl::string myURL;
    Address remote;

    threading::Mutex newConnectionsMutex;

  public:
    IncomingConnectionManager( const char* url, bool useCompressionForNewConnections, const ConnectionSettings& settings );
    virtual ~IncomingConnectionManager();

    // _newConnections может содержать уже закрытые соединения - надо проверять на IsValid
    virtual void GetNewConnections( TNewConnections& _newConnections );

    void Step();

    ConnectionState::Enum GetListenerStatus();
    virtual void SetMessageReservedSpace( int space );
  };

}
#endif //#define CONNECTIONMANAGER_H_A457162F_098
