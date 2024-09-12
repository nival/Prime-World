#pragma once
#include "transport/TLTypes.h"
#include <map>
#include "transport/TLAddressResolver.h"
#include <ace/Thread_Mutex.h>
#include <Network/Address.h>
#include <naio/Types.h>
#include "naio/AcceptorHandle.h"

namespace naio
{
  class Driver;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelListenerInternal;

  class ConnectionManager : public StrongFromThis<ConnectionManager>
  {
  public:
    ConnectionManager(naio::DriverSP const & spdrv, TL::MessageBlockFactorySP const & mbf);
    ~ConnectionManager();

  public:
    ConnectionSP OpenConnection(Network::NetAddress const & naddr, Transport::TServiceId const & svcid = Transport::EmptySvcId);
    void CloseConnection(TL::ConnectionSP const & spconn, bool active);

    naio::AcceptorHandle OpenAcceptor(Network::NetAddress const & naddr);
    void CloseAcceptor(naio::AcceptorHandle const & handle);

    void OnConnectionEstablished(bool success, bool isactive, 
      naio::ConnectionContextStrongPtr const & spconnctx, TL::MessageBlockFactorySP const & spmbf);

    void Peername2Connection(Transport::TServiceId const & _svcid, ConnectionWP const & _conn);

    StrongMT<ChannelListenerInternal> defaultChannelListener() const { return defaultChannelListener_; }

  private:
    ConnectionManager();
    TL::ConnectionSP FindConnection_(nstl::string const & naddr);
    void CloseConnection_(TL::ConnectionSP const & spconn, bool active);

  private:
    typedef std::map<nstl::string, TL::ConnectionSP>  ConnectionsT;
    ConnectionsT  connections_;
    typedef std::map<unsigned long long, TL::ConnectionSP>  AcceptedConnectionsT;
    AcceptedConnectionsT  acceptedConnections_;
    typedef std::map<Transport::TServiceId, TL::ConnectionWP> Peername2ConnectionT;
    Peername2ConnectionT peername2connection_;
    ACE_Thread_Mutex  connectionsMutex_;

    naio::DriverSP spdrv_;
    TL::MessageBlockFactorySP mbf_;

    TL::ConnectionSP spCurrentConnection_;
    typedef nstl::list<TL::ConnectionSP> Connections2OpenListT;
    Connections2OpenListT conns2open_;

    StrongMT<ChannelListenerInternal> defaultChannelListener_;
  };
}
