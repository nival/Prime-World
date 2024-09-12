#include "stdafx.h"
#include "RelayBalancer/RelayBalancerUserContext.h"

NI_DEFINE_REFCOUNT(Relay::UserContext);

namespace Relay
{
  UserContext::UserContext(Transport::TClientId const & userid)
    :userid_(userid),
    count_(0)
  {
  }

  UserContext::~UserContext()
  {
  }
}
