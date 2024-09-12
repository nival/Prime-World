#pragma once

#include "Game/PF/Tests/GTCBase/GTCBase.h"
#include "NetworkAIO/tests/multicast.client/MulticastClientIface.h"

namespace MulticastTest
{
  class ClientContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ClientContext, BaseObjectMT );

  public:
    ClientContext(Transport::TClientId const & _cid,
      nstl::string const & _nickname, StrongMT<IMulticastClient> const & _clientiface);
    ~ClientContext();

  public:
    Transport::TClientId const & clientid() const;
    nstl::string const & nickname() const;
    StrongMT<IMulticastClient> const & clientiface() const;

    void confirmedStep(unsigned int _confirmedStep);
    unsigned int confirmedStep() const;

    int joinMulticastChannel(StrongMT<Transport::IMulticastChannel> const & _chnl);
    StrongMT<Transport::IMulticastChannel> multicastChannel() const;

    int close();

  private:
    Transport::TClientId clientid_;
    nstl::string nickname_;
    StrongMT<IMulticastClient> clientiface_;
    unsigned int confirmedStep_;
    StrongMT<Transport::IMulticastChannel> multicastChannel_;
  };

  inline
  Transport::TClientId const & ClientContext::clientid() const
  {
    return clientid_;
  }

  inline
  nstl::string const & ClientContext::nickname() const
  {
    return nickname_;
  }

  inline
  StrongMT<IMulticastClient> const & ClientContext::clientiface() const
  {
    return clientiface_;
  }

  inline
  void ClientContext::confirmedStep(unsigned int _confirmedStep)
  {
    NI_ASSERT(confirmedStep_ < _confirmedStep, "");
    confirmedStep_ = _confirmedStep;
  }

  inline
  unsigned int ClientContext::confirmedStep() const
  {
    return confirmedStep_;
  }

  inline
  StrongMT<Transport::IMulticastChannel> ClientContext::multicastChannel() const
  {
    return multicastChannel_;
  }
}
