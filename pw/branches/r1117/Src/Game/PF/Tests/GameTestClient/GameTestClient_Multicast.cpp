#include "stdafx.h"
#include "transport/TLTransportModule.h"
#include "GameTestClient_Multicast.h"

namespace GameTestClient2
{
  MulticastTestClient::MulticastTestClient(unsigned int sessionDurationInSteps,
                int localid, 
                StrongMT<Network::INetworkDriver> const & driver,
                StrongMT<TL::TransportModule> const & sptm, 
                unsigned int stepInMs,
                nstl::string const & loginaddr,
                nstl::string const & user, nstl::string const & pswd,
                nstl::string const & sessionKey)
    :ClientBase(localid, driver, sptm, stepInMs, loginaddr, user, pswd, sessionKey)
  {
  }

  MulticastTestClient::~MulticastTestClient()
  {
  }

  int MulticastTestClient::Step()
  {
    int rc = ClientBase::Step();
    if (Result::NO_SUCH_STAGE != rc)
      return rc;

    switch(stage())
    {
    case MTCStage::INITIAL:
      break;

    default:
      break;
    }

    setLastResult(rc);
    return rc;
  }
}
