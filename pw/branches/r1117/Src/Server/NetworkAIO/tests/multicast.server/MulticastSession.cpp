#include "stdafx.h"
#include "MulticastSession.h"
#include <NetworkAIO/tests/multicast.client/RMulticastClientIface.auto.h>
#include "MulticastTestNaming.h"
#include <sstream>

NI_DEFINE_REFCOUNT(MulticastTest::MulticastSession)

namespace MulticastTest
{
  MulticastSession::MulticastSession(StrongMT<Transport::ITransportSystem> const & _ts, unsigned int _userlimit, NHPTimer::FTime _stepFrequency)
    :ts_(_ts),
    step_(0),
    userlimit_(_userlimit),
    lastStepTime_(NHPTimer::GetScalarTime()),
    stepFrequency_(_stepFrequency)
  {
  }

  MulticastSession::~MulticastSession()
  {
  }

  int MulticastSession::RegisterClient(const char* name, uint clientId, StrongMT<IMulticastClient> const & _client)
  {
    int rc = -1;
    StrongMT<ClientContext> cctx(new ClientContext(clientId, name, _client));
    clients_[clientId] = cctx;

    rpc::INode* node = ((RIMulticastSession*)_client.Get())->GetNode(0);
    Transport::TServiceId svcid;
    if (node)
      svcid = node->GetConnectedPipe().GetPipeChannel()->GetAddress().source;

    if (!svcid.empty())
    {
      MulticastChannelsT::iterator it = channels_.find(svcid);
      if (channels_.end() == it)
      {
        StrongMT<Transport::IMulticastChannel> chnl = ts_->OpenMulticastChannel(Transport::Address(MulticastTest::ServiceClass, svcid, Transport::autoAssignClientId));
        if (chnl)
        {
          channels_[svcid] = chnl;
          rc = cctx->joinMulticastChannel(chnl);
        }
      }
      else
      {
        rc = cctx->joinMulticastChannel(it->second);
      }
    }

    if (rc >= 0)
      _client->OnRegisterClient(RemotePtr<RIMulticastSession>(this));

    return rc;
  }

  void MulticastSession::Step()
  {
    NHPTimer::FTime now = NHPTimer::GetScalarTime();
    if (now - lastStepTime_ > stepFrequency_)
    {
      ++step_;

      std::stringstream ss;
      ss << step_;
      std::string s(ss.str());
      sendRawStep(step_, (byte*)s.c_str(), s.length());

      for(ClientContextsT::iterator it = clients_.begin(); it != clients_.end();)
      {
        StrongMT<IMulticastClient> client = it->second->clientiface();
        RIMulticastClient* rclient = (RIMulticastClient*)client.Get();
        if (rclient->GetStatus() == rpc::Connected)
        {
          client->Step(step_);
          ++it;
        }
        else
          it = clients_.erase(it);
      }

      //if (100 == step_)
      //  closeMulticastChannels();

      if (!clients_.size())
        channels_.clear();

      lastStepTime_ = now;
    }
  }

  void MulticastSession::ConfirmStep(Transport::TClientId _cid, unsigned int _step)
  {
    ClientContextsT::iterator it = clients_.find(_cid);
    if (it != clients_.end())
    {
      it->second->confirmedStep(_step);
    }
  }

  void MulticastSession::sendRawStep(int _step, byte* _data, unsigned int _size)
  {
    for(MulticastChannelsT::iterator it = channels_.begin(); it != channels_.end(); ++it)
    {
      StrongMT<Transport::IMulticastChannel> chnl = it->second;
      if (Network::ConnectionState::Connected == chnl->GetStatus())
      {
        if (chnl->Recipients())
          chnl->SendRaw(_data, _size);
      }
    }
  }

  void MulticastSession::removeRecipients()
  {
    for(ClientContextsT::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
      StrongMT<Transport::IMulticastChannel> chnl = it->second->multicastChannel();
      if (chnl->GetStatus() == Network::ConnectionState::Connected)
        chnl->RemoveRecipient(it->first);
    }
  }

  void MulticastSession::closeMulticastChannels()
  {
    for(ClientContextsT::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
      StrongMT<Transport::IMulticastChannel> chnl = it->second->multicastChannel();
      if (chnl->GetStatus() == Network::ConnectionState::Connected)
        chnl->Close();
    }
  }
}
