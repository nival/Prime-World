#include "transport/stdafx.h"
#include "transport/TLChannelListener.h"
#include <Network/TransportChannelType.h>
#include "transport/TLChannelInt.h"
#include "transport/TLChannelWrapper.h"
#include "transport/TLConnectionManager.h"

namespace TransportLayer
{
ChannelListener::ChannelListener(Transport::TServiceId const & serviceId, ACE_INET_Addr const & listenAddr)
: serviceId_(serviceId)
, listenAddr_(listenAddr)
{
}

ChannelListener::~ChannelListener()
{
  //  FIXME: delete our usercontext in acceptorHandle
}

void ChannelListener::onOpenChannel(TL::IChannelInternalSP const & spchnl)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  threading::MutexLock lock(newConnectionsMutex);
  StrongMT<Transport::IChannel> extchnl = 0;
  if (Transport::EChannelType::Unicast == spchnl->channeltype())
    extchnl.Set(new ChannelWrapper(spchnl));
  else
    NI_ALWAYS_ASSERT("Inappropriate channel type");

  if (extchnl)
    newConnections.push_back(extchnl);
}

void ChannelListener::close()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>* acp = 
    reinterpret_cast<AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>*>(acceptorHandle().userContext());
  if (acp)
    delete acp;
}

void ChannelListener::GetNewConnections(vector<StrongMT<Transport::IChannel> >* pConnections)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  threading::MutexLock lock(newConnectionsMutex);
  pConnections->swap( newConnections );
  newConnections.clear();
}



Transport::TServiceId const & ChannelListener::GetServiceId() const
{
  return serviceId_;
}

}
