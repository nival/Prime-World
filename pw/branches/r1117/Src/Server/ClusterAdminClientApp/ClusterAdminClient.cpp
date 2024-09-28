#include "stdafx.h"
#include "ClusterAdminClient.h"
#include "ClusterAdminNaming.h"
#include <Network/FreePortsFinder.h>
#include <Network/TransportInitializer.h>
#include <Network/Initializer.h>
#include <Network/TransportMessages.h>


NI_DEFINE_REFCOUNT(ClusterAdmin::Client);

namespace ClusterAdmin
{
  Client::Client()
    :ca_(0),
    carecv_(false),
    clusterClosed_(false)
  {
  }

  Client::~Client()
  {
  }

  bool Client::Init(ClientConfig const & cfg)
  {
    nd_ = Network::Initialize();
    addressResolver_.SetNetworkAddress(cfg.svcNetAddr_);
    Transport::RegisterMessages(&msgFactory_);
    ts_ = Transport::CreateTransportSystem(nd_, Transport::GetGlobalMessageFactory(), &addressResolver_);
    if (ts_)
    {
      adminSvcChnl_ = ts_->OpenChannel(Transport::Address(ClusterAdmin::ServiceClass, 0), "");
      if (adminSvcChnl_)
      {
        while(Network::ConnectionState::Connecting == adminSvcChnl_->GetStatus())
          ::Sleep(10);

        if (Network::ConnectionState::Connected == adminSvcChnl_->GetStatus())
        {
          gateKeeper_ = new rpc::GateKeeper(ts_, "", Transport::autoAssignClientId, this);
          adminSvcRpcNode_ = new rpc::P2PNode(adminSvcChnl_, &gateKeeper_->GetGate());
          bool res = adminSvcRpcNode_->node->Query<ClusterAdmin::RIClusterAdmin>(ClusterAdmin::ServiceIfaceId, this, &Client::OnGetClusterAdminIntf);
          if (res)
          {
            do 
            {
              gateKeeper_->Poll();
              ::Sleep(10);
            } 
            while (!carecv_);

            if (ca_)
              return true;
          }
        }
      }
    }

    return false;
  }

  void Client::OnGetClusterAdminIntf(ClusterAdmin::RIClusterAdmin* intf)
  {
    ca_ = intf;
    carecv_ = true;
  }

  void Client::OnNewNode( Transport::IChannel* channel,  rpc::Node* node )
  {
  }

  void Client::OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node )
  {
    clusterClosed_ = true;
  }

  void Client::OnCorruptData( Transport::IChannel* channel, rpc::Node* node )
  {
  }

  void Client::Shutdown(unsigned int seconds)
  {
    if (ca_)
    {
      ca_->Shutdown(seconds);
      do 
      {
        gateKeeper_->Poll();
        ::Sleep(10);
      }
      while (!clusterClosed_);
    }
  }

}
