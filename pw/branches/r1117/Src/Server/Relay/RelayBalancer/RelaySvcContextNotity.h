#pragma once
#include "RelayBalancer/Types.h"

namespace Relay
{
  class UserContext;

  class ISvcContextNotify : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ISvcContextNotify, IBaseInterfaceMT );

  public:
    virtual void OnUserLeaveSvc(Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole, StrongMT<UserContext> const & uctx) = 0;
  };
}
