#ifndef FASTRECONNECTCTX_H_INCLUDED
#define FASTRECONNECTCTX_H_INCLUDED

//Class to persist some client structures during fast reconnect

namespace NWorld
{
  class IMapCollection;
  class IMapLoader;
}


namespace NCore
{
  class ICommandScheduler;
  class ITransceiver;
  class ServerNode;
  class ReplayWriter;
}


namespace lobby
{

class FastReconnectCtx : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( FastReconnectCtx, BaseObjectMT )

public:
  FastReconnectCtx( Transport::TClientId _clientid ) :
  clientId( _clientid )
  {}

  void SetMaps( NWorld::IMapCollection * _maps, NWorld::IMapLoader * _map ) {
    maps = _maps;
    map = _map;
  }

  void SetGameSvcStuff( 
    NCore::ICommandScheduler * _scheduler,
    NCore::ITransceiver * _trans,
    NCore::ServerNode * _servNode,
    NCore::ReplayWriter * _replayWriter)
  {
    scheduler = _scheduler;
    transceiver = _trans;
    serverNode = _servNode;
    replayWriter = _replayWriter;
  }

  Transport::TClientId ClientId() const { return clientId; }
  NWorld::IMapCollection * Maps() const { return maps; }
  NWorld::IMapLoader * Map() const { return map; }
  NCore::ICommandScheduler * Scheduler() const { return scheduler; }
  NCore::ITransceiver * Transceiver() const { return transceiver; }
  NCore::ServerNode * ServerNode() const { return serverNode; }
  NCore::ReplayWriter * ReplayWriter() const { return replayWriter; }

private:
  Transport::TClientId                clientId;
  StrongMT<NWorld::IMapCollection>    maps;
  StrongMT<NWorld::IMapLoader>        map;
  StrongMT<NCore::ICommandScheduler>  scheduler;
  Strong<NCore::ITransceiver>         transceiver;
  StrongMT<NCore::ServerNode>         serverNode;
  StrongMT<NCore::ReplayWriter>       replayWriter;
};

} //namespace Game

#endif //FASTRECONNECTCTX_H_INCLUDED
