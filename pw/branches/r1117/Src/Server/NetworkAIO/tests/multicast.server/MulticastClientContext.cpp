#include "stdafx.h"
#include "MulticastClientContext.h"

namespace MulticastTest
{
  ClientContext::ClientContext(Transport::TClientId const & _cid,
    nstl::string const & _nickname, StrongMT<IMulticastClient> const & _clientiface)
    :clientid_(_cid),
    nickname_(_nickname),
    clientiface_(_clientiface),
    confirmedStep_(0)
  {
  }

  ClientContext::~ClientContext()
  {
  }

  int ClientContext::joinMulticastChannel(StrongMT<Transport::IMulticastChannel> const & _chnl)
  {
    if (multicastChannel_)
      return -1;

    multicastChannel_.Set(_chnl);
    Transport::EError::Enum rc = multicastChannel_->AddRecipient(clientid());
    return (int)rc;
  }
}
