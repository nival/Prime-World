#ifndef AISERVER_H_97C2627D_74FD_4CC
#define AISERVER_H_97C2627D_74FD_4CC

#include <RPC/GateKeeper.h>

#define REMOTE 

namespace Location
{
  class RLocationServer;
}

namespace AI 
{

static const Transport::TServiceId aiServerId = "aiserver";
static const char* AI_SERVER_RPC_NAME = "ai_server";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AIServer : 
  public rpc::IGateKeeperCallback, 
  public CObjectBase
{
  OBJECT_BASIC_METHODS( AIServer );

public:
  AIServer( Transport::ITransportSystem* _transport, const Transport::TServiceId& serviceId );
  ~AIServer();

  // from CObjectBase
  virtual void OnDestroyContents();

  void Step( float delta, NHPTimer::STime serverTime );

  void OnLocationServerReceived( Location::RLocationServer* _locationServer );
  void OnGetNPC( const nstl::vector<int>& result );

  // from IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnCorruptData( Transport::IChannel* channel, rpc::Node* node );

private:
  AIServer() {}

  StrongMT<rpc::GateKeeper> gateKeeper;

  typedef nstl::vector<int> NPCVector;
  NPCVector npñ;
};

} // namespace AI

#endif //#define AISERVER_H_97C2627D_74FD_4CC