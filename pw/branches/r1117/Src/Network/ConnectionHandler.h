#ifndef CONNECTIONHANDLER_H_A457162F_098
#define CONNECTIONHANDLER_H_A457162F_098

#include "Network.h"
#include <list>

namespace Network
{

  struct IConnectionProcessor
  {
    virtual void OnNewConnection(Network::IConnection* connection) {}
    virtual void OnDropConnection(Network::IConnection* connection) {}
    virtual bool ProcessPacket(Stream* stream, Network::IConnection *connection) { return true; } 
  };



  class ConnectionHandler 
  {
  public:
    ConnectionHandler(Network::INetworkDriver* _pDriver, const Network::NetAddress& _loginServerAddress, ::SSL_CTX* _secureContext=0);
    ConnectionHandler() {}
    ~ConnectionHandler();
    void Step(IConnectionProcessor* processor);
  private:
    struct ConnSlot
    {
      StrongMT<IConnection>   conn;
      timer::Time             expires;

      ConnSlot( IConnection * _conn, timer::Time _expires ) :
      conn( _conn ),
      expires( _expires )
      {}
    };

    typedef std::list<ConnSlot> TConnSlots;

    StrongMT<Network::IConnectionsManager> pManager;
    TConnSlots    connSlots;
    timer::Time   lastLeakReport;
    ::SSL_CTX* secureContext;
  };

} // Network

#endif
