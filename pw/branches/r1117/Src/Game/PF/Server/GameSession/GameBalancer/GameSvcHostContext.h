#pragma once
#include <Network/Address.h>
#include "GameBalancer/IGameCCUCounter.h"
#include "GameBalancer/SvcContext.h"

namespace GameBalancer
{

class HostContext : public ICCUCounter, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HostContext, ICCUCounter, BaseObjectMT );

  typedef nstl::list<StrongMT<SvcContext> > SvcContextListT;

public:
  HostContext(Network::NetAddress const & host);
  ~HostContext();

public:
  int registerSvcContext( SvcContext * svctx );
  StrongMT<SvcContext> unregisterSvcContext(Transport::TServiceId const & svcid);

  Network::NetAddress const & host() const { return host_; }

  StrongMT<SvcContext> findSvcSoftLimit(unsigned int limit);
  StrongMT<SvcContext> findSvcHardLimit(unsigned int limit);

  void step();

  uint svcCount() const { return svclist_.size(); }
  uint onlineSvcCount() const { return onlineSvcCount_; }

  bool softlimitReached() const { return softlimitReached_; }
  void softlimitReached(bool _flag) { softlimitReached_ = _flag; }

private:
  Network::NetAddress host_;
  SvcContextListT svclist_;
  uint onlineSvcCount_;
  bool softlimitReached_;
};

}
