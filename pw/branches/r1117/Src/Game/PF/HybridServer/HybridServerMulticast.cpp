
#include "HybridServerMulticast.h"
#include "Peered.h"
#include "RPeered.auto.h"


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
McChannelsWrapper::McChannelsWrapper(
  Transport::ITransportSystem * _transport,
  NLogg::CChannelLogger * _logStream,
  Peered::TSessionId _serverId)
  : transport(_transport)
  , logStream(_logStream)
  , serverId(_serverId)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool McChannelsWrapper::AddClient(const Peered::IGameClient * client, uint clientId, int clientIndex)
{
  Transport::TServiceId ssvcid;
  Transport::TServiceId tsvcid;

  if (StrongMT<rpc::INode> node = ((Peered::RIGameClient*)client)->GetNode(0))
  {
    ssvcid = node->GetConnectedPipe()->GetPipeChannel()->GetAddress().source;
    tsvcid = node->GetConnectedPipe()->GetPipeChannel()->GetAddress().target;
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "McChannelsWrapper: AddClient: Failed to get client's node (sid=%016x cid=%d cidx=%d)", 
        serverId, clientId, clientIndex);
    return false;
  }

  if (ssvcid.empty() || tsvcid.empty())
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "McChannelsWrapper: AddClient: Failed due to empty svcid (sid=%016x cid=%d cidx=%d ssvcid=%s tsvcid=%s)", 
        serverId, clientId, clientIndex, ssvcid.c_str(), tsvcid.c_str());
    return false;
  }

  TMulticastChannels::iterator it = mcChannels.find(ssvcid);

  if (mcChannels.end() == it)
  {
    StrongMT<Transport::IMulticastChannel> channel = 
      transport->OpenMulticastChannel(Transport::Address(tsvcid, ssvcid, Transport::autoAssignClientId));

    if (channel)
    {
      mcChannels[ssvcid] = channel;
      Transport::EError::Enum rc = channel->AddRecipient(clientId);

      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "McChannelsWrapper: AddClient: Added to a new channel (sid=%016x cid=%d cidx=%d errCode=%d ssvcid=%s tsvcid=%s)", 
          serverId, clientId, clientIndex, (int)rc, ssvcid.c_str(), tsvcid.c_str());
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "McChannelsWrapper: AddClient: Failed to open multicast channel (sid=%016x cid=%d cidx=%d ssvcid=%s tsvcid=%s)", 
          serverId, clientId, clientIndex, ssvcid.c_str(), tsvcid.c_str());
      return false;
    }
  }
  else
  {
    Transport::EError::Enum rc = it->second->AddRecipient(clientId);

    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "McChannelsWrapper: AddClient: Added to existing channel (sid=%016x cid=%d cidx=%d errCode=%d ssvcid=%s tsvcid=%s)", 
        serverId, clientId, (int)rc, ssvcid.c_str(), tsvcid.c_str());
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool McChannelsWrapper::RemoveClient(uint clientId)
{
  for (TMulticastChannels::iterator it = mcChannels.begin();
        it != mcChannels.end(); ++it)
  {
    if (it->second->RemoveRecipient(clientId) >= Transport::EError::OK)
      return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool McChannelsWrapper::FindClient(uint clientId)
{
  for (TMulticastChannels::iterator it = mcChannels.begin();
        it != mcChannels.end(); ++it)
  {
    if (it->second->FindRecipient(clientId))
      return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int McChannelsWrapper::GetClientsCount()
{
  int count = 0;

  for (TMulticastChannels::iterator it = mcChannels.begin();
        it != mcChannels.end(); ++it)
  {
    count += it->second->Recipients();
  }

  return count;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool McChannelsWrapper::SendData(const byte * data, int size)
{
  bool result = true;

  for (TMulticastChannels::iterator it = mcChannels.begin();
        it != mcChannels.end(); ++it)
  {
    if (it->second->Recipients())
    {
      if (Transport::EError::OK != it->second->SendRaw(data, size))
        result = false;
    }
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void McChannelsWrapper::Close()
{
  for (TMulticastChannels::iterator it = mcChannels.begin();
        it != mcChannels.end(); ++it)
  {
    it->second->Close();
  }

  mcChannels.clear();
}


} // namespace HybridServer


NI_DEFINE_REFCOUNT( HybridServer::McChannelsWrapper );

