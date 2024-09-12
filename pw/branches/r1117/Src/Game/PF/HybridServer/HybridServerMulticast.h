#ifndef HYBRIDSERVERMULTICAST_H_6F36D4BB
#define HYBRIDSERVERMULTICAST_H_6F36D4BB


#include "HybridServerMulticastIface.h"
#include "Network/Transport.h"
#include "PeeredTypes.h"


namespace Peered
{
  struct IGameClient;
}


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class McChannelsWrapper : public IMcChannelsWrapper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(McChannelsWrapper, IMcChannelsWrapper, BaseObjectMT);

public:
  McChannelsWrapper(
    Transport::ITransportSystem * _transport, 
    NLogg::CChannelLogger * _logStream,
    Peered::TSessionId _serverId);

  virtual bool AddClient(const Peered::IGameClient * client, uint clientId, int clientIndex);
  virtual bool RemoveClient(uint clientId);
  virtual bool FindClient(uint clientId);
  virtual int GetClientsCount();
  virtual bool SendData(const byte * data, int size);
  virtual void Close();

private:
  typedef map<Transport::TServiceId, StrongMT<Transport::IMulticastChannel> >  TMulticastChannels;

  StrongMT<Transport::ITransportSystem> transport;
  NLogg::CChannelLogger * logStream;
  Peered::TSessionId serverId;
  TMulticastChannels mcChannels;
};


} // namespace HybridServer


#endif //#define HYBRIDSERVERMULTICAST_H_6F36D4BB
