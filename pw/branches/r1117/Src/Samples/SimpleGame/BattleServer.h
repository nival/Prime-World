#ifndef BATTLESERVER_H_97C2627D_74FD_4CC
#define BATTLESERVER_H_97C2627D_74FD_4CC

#include <RPC/GateKeeper.h>

#define REMOTE 

namespace Battle 
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REMOTE class BattleServer : public rpc::IGateKeeperCallback, public CObjectBase
{
  OBJECT_BASIC_METHODS( BattleServer );

public:
  RPC_ID();

  BattleServer( Transport::ITransportSystem* _transport, const Transport::TServiceId& serviceId );
  ~BattleServer();

  void Step( float delta, NHPTimer::STime serverTime );

  REMOTE void TestFunction( int _a ); 

  // from IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnCorruptData( Transport::IChannel* channel, rpc::Node* node );

private:
  BattleServer() {}

  StrongMT<rpc::GateKeeper> gateKeeper;
};

} // namespace Battle

#endif //#define BATTLESERVER_H_97C2627D_74FD_4CC