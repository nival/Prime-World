#include "stdafx.h"
#include "MulticastClient.h"
#include <NetworkAIO/tests/multicast.server/MulticastTestNaming.h>
#include "LMulticastClientIface.auto.h"

namespace MulticastTest
{
  MulticastClient::MulticastClient(StrongMT<Network::INetworkDriver> const & driver, 
    StrongMT<TransportLayer::TransportModule> const & sptm, 
    nstl::string const & loginaddr,
    nstl::string const & user)
    :GameTestClient2::ClientBase(0, driver, sptm, 100, loginaddr, user),
    svciface_(new rpc::IfaceRequester<RIMulticastSvc>),
    isClientRegisteredInLocalFactory_(false)
  {
  }

  MulticastClient::~MulticastClient()
  {
    LOG_M(0).Trace("%s", __FUNCTION__);
  }

  int MulticastClient::Step()
  {
    int rc = ClientBase::Step();
    if (GameTestClient2::Result::NO_SUCH_STAGE != rc)
      return rc;

    if (getLocalEntityFactory() && !isClientRegisteredInLocalFactory_)
    {
      isClientRegisteredInLocalFactory_ = true;
      getLocalEntityFactory()->RegisterAttach<IMulticastClient, LIMulticastClient>();
    }

    if (svciface_)
      svciface_->step();

    switch(stage())
    {
    case MulticastStage::INITIAL:
      {
        rc = svciface_->init(this->getGateKeeper(), MulticastTest::ServiceClass, MulticastTest::ServiceIfaceId, &::GetSystemLog(), 0, this);
        setStage(MulticastStage::OPENING);
      }
      break;

    case MulticastStage::OPEN:
      {
        svciface_->iface()->RegisterClient(getUserName().c_str(), userid(), this, this, &MulticastClient::RegisterClient_return);
        setStage(MulticastStage::CLIENT_REGISTER_IN_PROGRESS);
      }
      break;

    case MulticastStage::CLIENT_REGISTERED:
      {
        if (!inputchnl_)
        {
          Transport::TChannels chnls;
          clientTransport()->GetNewAcceptedChannels(chnls);
          if (chnls.size())
          {
            inputchnl_ = *(chnls.begin());
            setStage(MulticastStage::INPUT_CHANNEL_ESTABLISHED);
          }
        }
      }
      break;

    case MulticastStage::INPUT_CHANNEL_ESTABLISHED:
      {
        if (inputchnl_->GetStatus() == Network::ConnectionState::Connected)
        {
          vector<byte> data;
          if (inputchnl_->ReceiveRaw(&data))
          {
            string stepNum;
            stepNum.assign((char*)data.begin(), data.size());
            LOG_M(0).Trace("Multicast step received(clientid=%d datasize=%d step=%s)", userid(), data.size(), stepNum.c_str());
          }
        }
        else
        {
          LOG_W(0).Trace("Input channel is NOT connected(clientid=%d)", userid());
          setStage(MulticastStage::CLOSE);
        }
      }
      break;

    case MulticastStage::CLOSE:
      rc = -1;
      break;

    default:
      break;
    }

    setLastResult(rc);
    return rc;
  }

  void MulticastClient::Step(int _step)
  {
    LOG_M(0).Trace("RPC step received(clientid=%d step=%d)", userid(), _step);
    session_->ConfirmStep(userid(), _step);
  }

  void MulticastClient::onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<RIMulticastSvc>> const & ifacereq)
  {
    LOG_M(0).Trace("%s(st=%d)", __FUNCTION__, (int)st);

    if (rpc::IfaceRequesterState::OPENED == st)
    {
      ClientBase::setStage(MulticastStage::OPEN);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == st)
    {
      ClientBase::setStage(MulticastStage::CLOSE);
    }
  }

  void MulticastClient::OnRegisterClient(RIMulticastSession* _session)
  {
    LOG_M(0).Trace("%s()", __FUNCTION__);

    session_.Set(_session);
  }

  void MulticastClient::RegisterClient_return(int _rc)
  {
    if (_rc < 0)
    {
      LOG_W(0).Trace("Client registration is FAILED(rc=%d)", _rc);
      ClientBase::setStage(MulticastStage::CLOSE);
    }

    ClientBase::setStage(MulticastStage:: CLIENT_REGISTERED);
  }
}
