#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "NewClientVerifier.h"
#include "ClientContext.h"
#include "BackendContext.h"
#include "RelayServer2Cfg.h"
#include "RelayChannelManager.h"

using namespace Terabit;
using namespace Transport;

namespace Relay
{

RelayChannelManager::RelayChannelManager(const ACE_TCHAR *       name,
                                         IOThreadPool &          task,
                                         AsynchChannelFactory &  channelFactory,
                                         Transport::IAddressTranslator* pAddressTranslator,
                                         Transport::MessageFactory* msgFactory,
                                         bool packClientAddress,
                                         NewClientVerifier* newClientVerifier,
                                         Transport::TServiceId const & svcid,
                                         Transport::TServiceId const & backendSvcid)
  :ChannelManager(name, task, channelFactory),
  addressTranslator_(pAddressTranslator),
  messageFactory_(msgFactory),
  packClientAddress_(packClientAddress),
  newClientVerifier_(newClientVerifier),
  svcid_(svcid),
  backendSvcid_(backendSvcid)
{
}

RelayChannelManager::~RelayChannelManager()
{
}

bool RelayChannelManager::RegisterConnection(int connid, Terabit::AsynchChannelPtr const & pchannel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (newConnectionsMutex_);
  return newConnections_.insert(nstl::pair<int, Terabit::AsynchChannelPtr>(connid, pchannel)).second;
}

Terabit::AsynchChannelPtr RelayChannelManager::UnregisterConnection(int connid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  AsynchChannelPtr pchannel;

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (newConnectionsMutex_);
  ConnectionsT::iterator it = newConnections_.find(connid);
  if (newConnections_.end() != it)
  {
    pchannel = it->second;
    newConnections_.erase(it);
  }

  return pchannel;
}

ClientContextSP RelayChannelManager::RegisterClient(int connid, Transport::TClientId const & userid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  AsynchChannelPtr pchannel = UnregisterConnection(connid);
  if (!pchannel)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. No connection registered to register client(c=%d ch=%d)"),
      __FUNCTION__, userid, connid));
    return ClientContextSP();
  }

  //  create context
  ClientContextSP spcc(new ClientContext);
  Transport::TServiceId trackSvcId(RelayServer2Cfg::GetClientTrackedSvc().c_str());
  spcc->setWeakPtr(spcc);

  spcc->open(userid, pchannel, RelayServer2Cfg::GetClientTrackInput() != 0, 
    trackSvcId, (unsigned int)RelayServer2Cfg::GetClientInputNotificationThreshold());

  //  insert to clients
  if (!InsertClient(userid, pchannel->get_id(), spcc))
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't insert client(c=%d ch=%d)"),
      __FUNCTION__, userid, pchannel->get_id()));
    return ClientContextSP();
  }

  return spcc;
}

BackendContextSP RelayChannelManager::RegisterService(Transport::TServiceId const & svcid, 
                                                               Terabit::AsynchChannelPtr const & pchannel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  //  generate service context id
  ServiceId sid = generateBackendId();
  if (INVALID_SERVICE_ID == sid)
    return BackendContextSP();

  //  create context
  BackendContextSP spbc(new BackendContext);
  spbc->setWeakPtr(spbc);
  spbc->open(svcid, sid, pchannel, this->CreateTrafficTrackerFactory(svcid));

  //  insert to clients
  if (!InsertService(sid, spbc))
    return BackendContextSP();

  return spbc;
}

bool RelayChannelManager::InsertClient(TClientId const & userid, unsigned int connid, ClientContextSP const & pctx)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (clientContextsMutex_);
  bool res = clientContexts_.insert(nstl::make_pair(userid, pctx)).second;
  if (res)
  {
    res = conn2ClientContext_.insert(nstl::make_pair(connid, pctx)).second;
    if (!res)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("Client already registered by connection id(c=%d connid=%d)"), userid, connid));
      clientContexts_.erase(userid);
    }

    ACE_ERROR((LM_INFO, ACE_TEXT("Client registered(c=%d count=%d)"), userid, clientContexts_.size()));
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Client already registered by userid(c=%d)"), userid));
  }

  return res;
}

ClientContextSP RelayChannelManager::FindClient(TClientId const & userid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Read_Guard<ACE_RW_Thread_Mutex> lock (clientContextsMutex_);
  ClientContextsT::iterator it = clientContexts_.find(userid);
  if (clientContexts_.end() == it)
    return ClientContextSP();

  return it->second;
}

ClientContextSP RelayChannelManager::FindClientByConn(unsigned int connid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Read_Guard<ACE_RW_Thread_Mutex> lock (clientContextsMutex_);
  Coonnection2ClientContextT::iterator it = conn2ClientContext_.find(connid);
  if (conn2ClientContext_.end() == it)
    return ClientContextSP();

  return it->second;
}

void RelayChannelManager::RemoveClient(Transport::TClientId const & userid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (clientContextsMutex_);
  ClientContextsT::iterator it = clientContexts_.find(userid);
  if (it != clientContexts_.end())
  {
    int connid = it->second->channelId();
    conn2ClientContext_.erase(connid);
    clientContexts_.erase(it);

    ACE_ERROR((LM_INFO, ACE_TEXT("Client unregistered(c=%d count=%d)"), userid, clientContexts_.size()));
  }
}

bool RelayChannelManager::InsertService(ServiceId const & srvid, BackendContextSP const & pctx)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (backendContextsMutex_);
  return backendContexts_.insert(nstl::make_pair(srvid, pctx)).second;
}

BackendContextSP RelayChannelManager::FindService(ServiceId const & srvid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Read_Guard<ACE_RW_Thread_Mutex> lock (backendContextsMutex_);
  BackendContextsT::iterator it = backendContexts_.find(srvid);
  if (backendContexts_.end() == it)
    return BackendContextSP();

  return it->second;
}

void RelayChannelManager::RemoveService(ServiceId const & srvid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Write_Guard<ACE_RW_Thread_Mutex> lock (backendContextsMutex_);
  backendContexts_.erase(srvid);
}

bool RelayChannelManager::ResolveSvcAddress(Transport::TServiceId const & serviceid, TRB_Sock_Addr & netaddr)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  TServiceId svcid = addressTranslator_->GetLastServiceInstance( serviceid );
  Network::NetAddress naddr = addressTranslator_->GetSvcAddress( svcid );
  netaddr = TRB_Sock_Addr(ACE_INET_Addr(naddr.c_str()));
  return !naddr.empty();
}

int RelayChannelManager::RegisterTrafficTrackerFactory(Transport::TServiceId const & svcls, StrongMT<ITrafficTrackerFactory> const & spttf)
{
  if (!trackerFactories_.insert(std::make_pair<Transport::TServiceId, StrongMT<ITrafficTrackerFactory> >(svcls, spttf)).second)
    return -1;

  return 0;
}

void RelayChannelManager::UnregisterTrafficTrackerFactory(Transport::TServiceId const & svcls)
{
  TrackerFactoriesT::iterator it = trackerFactories_.find(svcls);
  if (it != trackerFactories_.end())
  {
    trackerFactories_.erase(it);
  }
}

StrongMT<ITrafficTrackerFactory> RelayChannelManager::CreateTrafficTrackerFactory(Transport::TServiceId const & svcid)
{
  Transport::TServiceId svcls;
  Transport::GetServiceClass(svcid, svcls);

  TrackerFactoriesT::iterator it = trackerFactories_.find(svcls);
  if (it != trackerFactories_.end())
  {
    return it->second->CloneFactory(svcid);
  }

  return StrongMT<ITrafficTrackerFactory>();
}



ClientId RelayChannelManager::generateClientId()
{
  if (INVALID_CLIENT_ID == generatedClientId.value())
    return INVALID_CLIENT_ID;

  return ++generatedClientId;
}



ServiceId RelayChannelManager::generateBackendId()
{
  if (INVALID_SERVICE_ID == generatedBackendId.value())
    return INVALID_SERVICE_ID;

  return ++generatedBackendId;
}

} //namespace Relay
