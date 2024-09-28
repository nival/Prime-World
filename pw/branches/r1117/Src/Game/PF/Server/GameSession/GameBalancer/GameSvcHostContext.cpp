#include "stdafx.h"
#include "GameBalancer/GameSvcHostContext.h"
#include "GameBalancer/GameBalancerCfg.h"

NI_DEFINE_REFCOUNT(GameBalancer::HostContext);

namespace GameBalancer
{
  HostContext::HostContext(Network::NetAddress const & host)
    :host_(host),
    onlineSvcCount_(0),
    softlimitReached_(false)
  {
  }

  HostContext::~HostContext()
  {
  }

  int HostContext::registerSvcContext( SvcContext * svctx )
  {
    for(SvcContextListT::const_iterator cit = svclist_.begin(); cit != svclist_.end(); ++cit)
    {
      StrongMT<SvcContext> const & ctx = *cit;
      if (ctx->svcid() == svctx->svcid())
      {
        LOG_C(GBALANCER).Trace("Service already registered on host(svcid=%s)", svctx->svcid().c_str());
        return -1;
      }
    }

    svctx->externalCCUCounter(this);
    svclist_.push_back(svctx);
    return 0;
  }

  StrongMT<SvcContext> HostContext::findSvcSoftLimit(unsigned int limit)
  {
    for( SvcContextListT::const_iterator lit = svclist_.begin(); lit != svclist_.end(); ++lit )
    {
      StrongMT<SvcContext> const & ctx = *lit;
      if (ctx->isopen())
      {
        if (ctx->ccu() < limit)
        {
          return ctx;
        }
      }
    }

    return 0;
  }

  StrongMT<SvcContext> HostContext::findSvcHardLimit(unsigned int limit)
  {
    StrongMT<SvcContext> resctx;
    for(SvcContextListT::const_iterator lit = svclist_.begin(); lit != svclist_.end(); ++lit)
    {
      StrongMT<SvcContext> const & ctx = *lit;
      if (ctx->isopen())
      {
        if (ctx->ccu() < limit)
        {
          if (resctx)
          {
            if (ctx->ccu() < resctx->ccu())
              resctx = ctx;
          }
          else
          {
            resctx = ctx;
          }
        }
      }
    }

    return resctx;
  }

  StrongMT<SvcContext> HostContext::unregisterSvcContext(Transport::TServiceId const & svcid)
  {
    for(SvcContextListT::iterator lit = svclist_.begin(); lit != svclist_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svclist_.erase(lit);
        return ctx;
      }
    }

    return 0;
  }

  void HostContext::step()
  {
    onlineSvcCount_ = 0;
    softlimitReached_ = true;
    for(SvcContextListT::iterator lit = svclist_.begin(); lit != svclist_.end(); ++lit)
    {
      StrongMT<SvcContext> const & svctx = *lit;
      svctx->step();

      if (svctx->isopen())
      {
        ++onlineSvcCount_;
        if (svctx->ccu() < Cfg::GetGameSoftLimit())
          softlimitReached_ = false;
      }
    }

    if (!onlineSvcCount_)
      softlimitReached_ = false;
  }
}
