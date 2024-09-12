#pragma once
#include "ClusterAdmin/ClusterAdminSvc/ClusterAdminSvcIntf.h"
#include "ClusterAdminClientIntf.h"
#include <rpc/GateKeeper.h>
#include <Network/AddressTranslator.h>
#include <rpc/P2PNode.h>

#include "ClusterAdmin/ClusterAdminSvc/RClusterAdminSvcIntf.auto.h"

namespace ClusterAdmin
{
  class Client : public ClusterAdmin::IClient, public rpc::IGateKeeperCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3( Client, ClusterAdmin::IClient, rpc::IGateKeeperCallback, BaseObjectMT );

  public:
    Client();
    ~Client();

    bool Init(ClientConfig const & cfg);

    //  IClient
    virtual void Shutdown(unsigned int seconds);

  private:

    //  IGateKeeperCallback
    virtual void OnNewNode( Transport::IChannel* channel,  rpc::Node* node );
    virtual void OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node );
    virtual void OnCorruptData( Transport::IChannel* channel, rpc::Node* node );

    virtual void OnGetClusterAdminIntf(ClusterAdmin::RIClusterAdmin* intf);

  private:
    StrongMT<Network::INetworkDriver>     nd_;
    StrongMT<Transport::ITransportSystem> ts_;
    Transport::MessageFactory msgFactory_;
    Transport::DummyAddressResolver addressResolver_;
    StrongMT<rpc::GateKeeper> gateKeeper_;
    StrongMT<Transport::IChannel> adminSvcChnl_;
    rpc::P2PNode * adminSvcRpcNode_;

    StrongMT<RIClusterAdmin> ca_;
    bool carecv_;

    bool clusterClosed_;
  };
}
