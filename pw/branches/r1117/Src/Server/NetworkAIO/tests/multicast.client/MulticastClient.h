#pragma once

#include "Game/PF/Tests/GTCBase/GTCBase.h"
#include "MulticastClientIface.h"
#include <NetworkAIO/tests/multicast.server/RMulticastTestSvcIface.auto.h>
#include <RPC/IfaceRequester.h>

namespace MulticastTest
{
  namespace MulticastStage
  {
    enum
    {
      INVALID = -1,
      INITIAL = GameTestClient2::BaseStage::LOGIN_FINISHED_POST_STEP,
      OPENING,
      OPEN,
      CLIENT_REGISTER_IN_PROGRESS,
      CLIENT_REGISTERED,
      INPUT_CHANNEL_ESTABLISHED,
      CLOSE,
      NUMBER_OF_STAGES
    };
  };

  class MulticastClient : public GameTestClient2::ClientBase, public IMulticastClient, rpc::IfaceRequesterCallback<RIMulticastSvc>, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_4( MulticastClient, GameTestClient2::ClientBase, IMulticastClient, rpc::IfaceRequesterCallback<RIMulticastSvc>, BaseObjectMT );

  public:
    MulticastClient(StrongMT<Network::INetworkDriver> const & driver, 
      StrongMT<TransportLayer::TransportModule> const & sptm = 0, 
      nstl::string const & loginaddr = "",
      nstl::string const & user = "");
    ~MulticastClient();

  public:
    //  ClientBase
    virtual int Step();
    //  IMulticastClient
    virtual void Step(int step);

    virtual void OnRegisterClient(RIMulticastSession* _session);
    virtual void RegisterClient_return(int _rc);

  protected:
    void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<RIMulticastSvc>> const & ifacereq);

  private:
    StrongMT<rpc::IfaceRequester<RIMulticastSvc>> svciface_;
    bool isClientRegisteredInLocalFactory_;
    StrongMT<RIMulticastSession> session_;
    StrongMT<Transport::IChannel> inputchnl_;
  };
}
