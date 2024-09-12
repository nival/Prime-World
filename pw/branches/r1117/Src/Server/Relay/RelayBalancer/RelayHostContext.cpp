#include "stdafx.h"
#include "RelayBalancer/RelayHostContext.h"

NI_DEFINE_REFCOUNT(Relay::HostContext);

namespace Relay
{
  HostContext::HostContext(Network::NetAddress const & host, Coordinator::TServiceRole const & _role, Balancer::Settings const & _settings)
    :host_(host),
    onlineSvcCount_(0),
    prevOnlineSvcCount_(0),
    settings_(_settings),
    role_(_role)
  {
    //  update local members from settings
    Balancer::UserLimits ul = settings_.relayHostUserLimit(host_);
    softuserlimit_ = ul.softlimit();
    harduserlimit_ = ul.hardlimit();
  }

  HostContext::~HostContext()
  {
  }

  int HostContext::registerSvcContext(StrongMT<SvcContext> const & svctx)
  {
    for(SvcContextListT::const_iterator cit = svcLoadList_.begin(); cit != svcLoadList_.end(); ++cit)
    {
      StrongMT<SvcContext> const & ctx = *cit;
      if (ctx->svcid() == svctx->svcid())
      {
        LOG_C(RBLOG).Trace("Service already registered in load set on the host(host=%s svcid=%s svcrole=%s)", 
          host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str());
        return -1;
      }
    }

    for(SvcContextListT::const_iterator cit = svcReserveList_.begin(); cit != svcReserveList_.end(); ++cit)
    {
      StrongMT<SvcContext> const & ctx = *cit;
      if (ctx->svcid() == svctx->svcid())
      {
        LOG_C(RBLOG).Trace("Service already registered in reserve set on the host(host=%s svcid=%s svcrole=%s)", 
          host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str());
        return -1;
      }
    }

    if (!settings_.loadSetSize() || (uint)svcLoadList_.size() < settings_.loadSetSize())
    {
      svcLoadList_.push_back(svctx);
      LOG_M(RBLOG).Trace("Service registered in load set(host=%s svcid=%s svcrole=%s setsize=%d)", 
        host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str(), svcLoadList_.size());
    }
    else
    {
      svcReserveList_.push_back(svctx);
      LOG_M(RBLOG).Trace("Service registered in reserve set(host=%s svcid=%s svcrole=%s setsize=%d)", 
        host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str(), svcReserveList_.size());
    }

    return 0;
  }

  StrongMT<SvcContext> HostContext::findSvcSoftLimit(Coordinator::TServiceRole const & role, unsigned int limit, Transport::TServiceId const & except)
  {
    for(SvcContextListT::const_iterator lit = svcLoadList_.begin(); lit != svcLoadList_.end(); ++lit)
    {
      StrongMT<SvcContext> const & ctx = *lit;
      if (ctx->isopen())
      {
        if (ctx->svcrole() == role && ctx->ccu() < limit)
        {
          if (except == Transport::EmptySvcId || 
              except != Transport::EmptySvcId && except != ctx->svcid())
            return ctx;
        }
      }
    }

    return StrongMT<SvcContext>();
  }

  StrongMT<SvcContext> HostContext::findSvcHardLimit(Coordinator::TServiceRole const & role, unsigned int limit, Transport::TServiceId const & except)
  {
    StrongMT<SvcContext> resctx;
    for(SvcContextListT::const_iterator lit = svcLoadList_.begin(); lit != svcLoadList_.end(); ++lit)
    {
      StrongMT<SvcContext> const & ctx = *lit;
      if (ctx->isopen())
      {
        if (ctx->svcrole() == role && ctx->ccu() < limit)
        {
          if (resctx)
          {
            if (ctx->ccu() < resctx->ccu())
              if (except == Transport::EmptySvcId || 
                  except != Transport::EmptySvcId && except != ctx->svcid())
                resctx = ctx;
          }
          else
          {
            if (except == Transport::EmptySvcId || 
                except != Transport::EmptySvcId && except != ctx->svcid())
              resctx = ctx;
          }
        }
      }
    }

    return resctx;
  }

  StrongMT<SvcContext> HostContext::unregisterSvcContext(Transport::TServiceId const & svcid)
  {
    for(SvcContextListT::iterator lit = svcLoadList_.begin(); lit != svcLoadList_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svcLoadList_.erase(lit);
        return ctx;
      }
    }

    for(SvcContextListT::iterator lit = svcReserveList_.begin(); lit != svcReserveList_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svcReserveList_.erase(lit);
        return ctx;
      }
    }

    for(SvcContextListT::iterator lit = svcExcludedFromLoad_.begin(); lit != svcExcludedFromLoad_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svcExcludedFromLoad_.erase(lit);
        return ctx;
      }
    }

    return 0;
  }

  void HostContext::step()
  {
    //  update local members from settings
    Balancer::UserLimits ul = settings_.relayHostUserLimit(host_);
    softuserlimit_ = ul.softlimit();
    harduserlimit_ = ul.hardlimit();

    SvcContextListT tmplist;
    onlineSvcCount_ = 0;

    for(SvcContextListT::iterator lit = svcLoadList_.begin(); lit != svcLoadList_.end(); )
    {
      bool elemErased = false;
      SvcContextPtr const & svctx = *lit;
      svctx->step();

      if (settings_.usersConnectTimeoutExpiredThreshold() && 
        svctx->usersConnectTimeoutExpiredCount() >= settings_.usersConnectTimeoutExpiredThreshold())
      {
        SvcContextPtr lsvctx = svctx;
        tmplist.push_back(svctx);
        lit = svcLoadList_.erase(lit);

        LOG_W(RBLOG).Trace("Service removed from load set due to too many users don't reach this relay(host=%s svcid=%s svcrole=%s connectTimeoutCount=%d loadSetSize=%d reserveSetSize=%d)", 
          host_.c_str(), lsvctx->svcid().c_str(), lsvctx->svcrole().c_str(), lsvctx->usersConnectTimeoutExpiredCount(), svcLoadList_.size(), svcReserveList_.size());

        elemErased = true;
      }
      else
      {
        if (svctx->isopen())
          ++onlineSvcCount_;
        else
        if (svctx->offlineTimeStart() && settings_.offlineRelayInLoadSetTimeout() && 
            svctx->offlineTimeStart() + settings_.offlineRelayInLoadSetTimeout() < NHPTimer::GetScalarTime())
        {
          SvcContextPtr lsvctx = svctx;
          tmplist.push_back(svctx);
          lit = svcLoadList_.erase(lit);

          LOG_W(RBLOG).Trace("Service removed from load set due to offline timeout expired(host=%s svcid=%s svcrole=%s connectTimeoutCount=%d offlineTimeout=%d loadSetSize=%d reserveSetSize=%d)", 
            host_.c_str(), lsvctx->svcid().c_str(), lsvctx->svcrole().c_str(), lsvctx->usersConnectTimeoutExpiredCount(), 
            settings_.offlineRelayInLoadSetTimeout(), svcLoadList_.size(), svcReserveList_.size());

          elemErased = true;
        }
      }

      if (!elemErased)
        ++lit;
    }

    //  при необходимости переносим сервисы из резервного набора в нагружаемый
    for(SvcContextListT::iterator lit = svcReserveList_.begin(); lit != svcReserveList_.end(); )
    {
      bool elemErased = false;
      StrongMT<SvcContext> const & svctx = *lit;
      svctx->step();
      if (svctx->isopen())
      {
        if (!settings_.loadSetSize() || (uint)svcLoadList_.size() < settings_.loadSetSize())
        {
          SvcContextPtr lsvctx = svctx;
          svcLoadList_.push_back(svctx);
          lit = svcReserveList_.erase(lit);

          LOG_W(RBLOG).Trace("Service added to load set from reserve set(host=%s svcid=%s svcrole=%s connectTimeoutCount=%d loadSetSize=%d reserveSetSize=%d)", 
            host_.c_str(), lsvctx->svcid().c_str(), lsvctx->svcrole().c_str(), lsvctx->usersConnectTimeoutExpiredCount(), svcLoadList_.size(), svcReserveList_.size());

          lsvctx->resetUsersConnectTimeoutExpiredCount();
          elemErased = true;
          ++onlineSvcCount_;
        }
      }

      if (!elemErased)
        ++lit;
    }

    //  решаем в какой набор класть сервисы изъятые из нагрузочного набора
    for(SvcContextListT::iterator lit = tmplist.begin(); lit != tmplist.end(); ++lit)
    {
      SvcContextPtr const & svctx = *lit;
      if (!settings_.loadSetSize() || (uint)svcLoadList_.size() < settings_.loadSetSize())
      {
        svcLoadList_.push_back(svctx);

        LOG_W(RBLOG).Trace("Service added to load set(host=%s svcid=%s svcrole=%s connectTimeoutCount=%d loadSetSize=%d)", 
          host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str(), svctx->usersConnectTimeoutExpiredCount(), svcLoadList_.size());

        svctx->resetUsersConnectTimeoutExpiredCount();
        if (svctx->isopen())
        {
          ++onlineSvcCount_;
          svctx->resetOfflineTimeStart();
        }
        else
          svctx->initOfflineTimeStart();
      }
      else
      {
        svcReserveList_.push_back(svctx);

        LOG_W(RBLOG).Trace("Service added to reserve set(host=%s svcid=%s svcrole=%s connectTimeoutCount=%d reserveSetSize=%d)", 
          host_.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str(), svctx->usersConnectTimeoutExpiredCount(), svcReserveList_.size());
      }
    }

    if (prevOnlineSvcCount_ != onlineSvcCount_)
    {
      LOG_W(RBLOG).Trace("Online service count is changed(host=%s role=%s prevOnlineSvcCount=%d onlineSvcCount=%d)", 
        host_.c_str(), role_.c_str(), prevOnlineSvcCount_, onlineSvcCount_);

      prevOnlineSvcCount_ = onlineSvcCount_;
    }
  }

  uint HostContext::ccu() const
  {
    uint userCount = 0;
    for(SvcContextListT::const_iterator cit = svcLoadList_.begin(); cit != svcLoadList_.end(); ++cit)
    {
      StrongMT<SvcContext> const & svctx = *cit;
      userCount += svctx->ccu();
    }

    for(SvcContextListT::const_iterator cit = svcReserveList_.begin(); cit != svcReserveList_.end(); ++cit)
    {
      StrongMT<SvcContext> const & svctx = *cit;
      userCount += svctx->ccu();
    }

    for(SvcContextListT::const_iterator cit = svcExcludedFromLoad_.begin(); cit != svcExcludedFromLoad_.end(); ++cit)
    {
      StrongMT<SvcContext> const & svctx = *cit;
      userCount += svctx->ccu();
    }

    return userCount;
  }

  StrongMT<SvcContext> HostContext::excludeFromLoad(Transport::TServiceId const & svcid)
  {
    StrongMT<SvcContext> svctx;
    for(SvcContextListT::iterator lit = svcLoadList_.begin(); lit != svcLoadList_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svcLoadList_.erase(lit);
        svctx = ctx;
        break;
      }
    }

    for(SvcContextListT::iterator lit = svcReserveList_.begin(); !svctx && lit != svcReserveList_.end(); ++lit)
    {
      StrongMT<SvcContext> ctx = *lit;
      if (ctx->svcid() == svcid)
      {
        svcReserveList_.erase(lit);
        svctx = ctx;
        break;
      }
    }

    if (svctx)
      svcExcludedFromLoad_.push_back(svctx);

    return svctx;
  }
}
