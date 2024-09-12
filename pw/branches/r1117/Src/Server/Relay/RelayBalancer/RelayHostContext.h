#pragma once
#include <Network/Address.h>
#include "RelayBalancer/IRelayCCUCounter.h"
#include "RelayBalancer/RelaySvcContext.h"
#include "RelayBalancer/RelayBalancerSettings.h"
#include "Coordinator/ServiceRole.h"

namespace Relay
{
  class HostContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( HostContext, BaseObjectMT );

    typedef nstl::list<SvcContextPtr> SvcContextListT;

  public:
    HostContext(Network::NetAddress const & _host, Coordinator::TServiceRole const & _role, Balancer::Settings const & _settings);
    ~HostContext();

  public:
    int registerSvcContext(StrongMT<SvcContext> const & svctx);
    StrongMT<SvcContext> unregisterSvcContext(Transport::TServiceId const & svcid);
    StrongMT<SvcContext> excludeFromLoad(Transport::TServiceId const & svcid);

    Network::NetAddress const & host() const;

    StrongMT<SvcContext> findSvcSoftLimit(Coordinator::TServiceRole const & role, unsigned int limit, Transport::TServiceId const & except = Transport::EmptySvcId);
    StrongMT<SvcContext> findSvcHardLimit(Coordinator::TServiceRole const & role, unsigned int limit, Transport::TServiceId const & except = Transport::EmptySvcId);

    void step();

    uint svcCount() const;
    uint onlineSvcCount() const;
    uint softUserLimit() const;
    uint hardUserLimit() const;

    bool load() const;

    uint ccu() const;
    Coordinator::TServiceRole const & role() const;

  private:
    Network::NetAddress host_;
    SvcContextListT svcLoadList_;
    SvcContextListT svcReserveList_;
    SvcContextListT svcExcludedFromLoad_;

    Coordinator::TServiceRole role_;
    uint onlineSvcCount_;
    uint prevOnlineSvcCount_;
    uint softuserlimit_;
    uint harduserlimit_;
    Balancer::Settings const & settings_;
  };

  inline
  Network::NetAddress const & HostContext::host() const
  {
    return host_;
  }

  inline
  uint HostContext::svcCount() const
  {
    return svcLoadList_.size() + svcReserveList_.size();
  }

  inline
  uint HostContext::onlineSvcCount() const
  {
    return onlineSvcCount_;
  }

  inline
  uint HostContext::softUserLimit() const
  {
    return softuserlimit_;
  }

  inline
  uint HostContext::hardUserLimit() const
  {
    return harduserlimit_;
  }

  inline
  bool HostContext::load() const
  {
    Balancer::UserLimits ul = settings_.relayRoleUserLimit(role_.c_str());
    return (onlineSvcCount() && (!hardUserLimit() || ccu() < hardUserLimit()) && (ccu() < onlineSvcCount()*ul.hardlimit()));
  }

  inline
  Coordinator::TServiceRole const & HostContext::role() const
  {
    return role_;
  }
}
