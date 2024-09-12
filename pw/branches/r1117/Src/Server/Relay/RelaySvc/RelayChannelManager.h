#pragma once

#include <IOTerabit/ChannelManager.h>
#include <TProactor/Sock_Addr.h>
#include <ace/RW_Thread_Mutex.h>
#include <map>
#include <ace/Atomic_Op.h>
#include <Network/AddressTranslator.h>
#include "ClientContext.h"
#include "SvcConnectionManager.h"
#include "ITrafficTrackerFactory.h"

typedef ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> AtomicId;

namespace Terabit
{
  class ChannelConnector;
}

namespace Transport
{
  class MessageFactory;
  //class IAddressTranslator;
}

namespace Relay
{

class ClientContext;
class BackendContext;
class NewClientVerifier;

class RelayChannelManager : public Terabit::ChannelManager, public ISvcAddressResolver
{
public:
  RelayChannelManager(const ACE_TCHAR *       name,
    Terabit::IOThreadPool &          task,
    Terabit::AsynchChannelFactory &  channelFactory,
    Transport::IAddressTranslator* pAddressTranslator,
    Transport::MessageFactory* msgFactory,
    bool packClientAddress,
    NewClientVerifier* newClientVerifier,
    Transport::TServiceId const & svcid,
    Transport::TServiceId const & backendSvcid);

  ~RelayChannelManager();

public:
  bool RegisterConnection(int connid, Terabit::AsynchChannelPtr const & pchannel);
  Terabit::AsynchChannelPtr UnregisterConnection(int connid);

  //  register client for new connection
  ClientContextSP RegisterClient(int connid, Transport::TClientId const & userid);

  bool InsertClient(Transport::TClientId const & userid, unsigned int connid, ClientContextSP const & pctx);
  ClientContextSP FindClient(Transport::TClientId const & userid);
  ClientContextSP FindClientByConn(unsigned int connid);
  void RemoveClient(Transport::TClientId const & userid);

  BackendContextSP RegisterService(Transport::TServiceId const & svcid, Terabit::AsynchChannelPtr const & pchannel);

  bool InsertService(ServiceId const & srvid, BackendContextSP const & pctx);
  BackendContextSP FindService(ServiceId const & srvid);
  void RemoveService(ServiceId const & srvid);

  int RegisterTrafficTrackerFactory(Transport::TServiceId const & svcls, StrongMT<ITrafficTrackerFactory> const & ttf);
  void UnregisterTrafficTrackerFactory(Transport::TServiceId const & svcls);
  StrongMT<ITrafficTrackerFactory> CreateTrafficTrackerFactory(Transport::TServiceId const & svcid);

public:
  //  settings
  Transport::MessageFactory* messageFactory() const { return messageFactory_; }
  bool packClientAddress() const { return packClientAddress_; }

  ClientId generateClientId();
  ServiceId generateBackendId();

  NewClientVerifier* newClientVerifier() const { return newClientVerifier_; }

  bool ResolveSvcAddress(Transport::TServiceId const & serviceid, TRB_Sock_Addr & netaddr);

  void setSvcConnectionManager(SvcConnectionManager* scm) { svcConnectionMngr_ = scm; }
  SvcConnectionManager* getSvcConnectionManager() { return svcConnectionMngr_; }

  Transport::TServiceId const & svcid() const { return svcid_; }
  Transport::TServiceId const & backendSvcid() const { return backendSvcid_; }

private:

  typedef nstl::hash_map<int, Terabit::AsynchChannelPtr> ConnectionsT;
  typedef nstl::hash_map<Transport::TClientId, ClientContextSP> ClientContextsT;
  typedef nstl::hash_map<unsigned int, ClientContextSP>  Coonnection2ClientContextT;
  typedef nstl::hash_map<ServiceId, BackendContextSP> BackendContextsT;
  typedef std::map<Transport::TServiceId, StrongMT<ITrafficTrackerFactory> > TrackerFactoriesT;

  ConnectionsT        newConnections_;
  ACE_RW_Thread_Mutex newConnectionsMutex_;

  ClientContextsT     clientContexts_;
  Coonnection2ClientContextT conn2ClientContext_;

  ACE_RW_Thread_Mutex clientContextsMutex_;

  BackendContextsT    backendContexts_;
  ACE_RW_Thread_Mutex backendContextsMutex_;

  AtomicId  generatedClientId;
  AtomicId  generatedBackendId;

  Terabit::ChannelConnector* backendConnector_;

  //  from old relay server
  StrongMT<Transport::IAddressTranslator> addressTranslator_;
  Transport::MessageFactory* messageFactory_;
  bool  packClientAddress_;
  NewClientVerifier* newClientVerifier_;
  SvcConnectionManager* svcConnectionMngr_;

  TrackerFactoriesT trackerFactories_;

  Transport::TServiceId svcid_;
  Transport::TServiceId backendSvcid_;
};

}
