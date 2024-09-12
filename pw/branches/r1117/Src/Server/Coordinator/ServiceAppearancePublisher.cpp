#include "stdafx.h"
#include "ServiceAppearancePublisher.h"

NI_DEFINE_REFCOUNT(Coordinator::ServiceAppearancePublisher);

namespace Coordinator
{
  SERIALIZE_FACTORY(SvcInfo);
  SERIALIZE_FACTORY(ClusterInfo);

  ServiceAppearancePublisher::ServiceAppearancePublisher(StrongMT<Coordinator::IClusterServicesInfo> const & csi)
    :genSubscriberId(0),
    svcInfoGetter(csi)
  {
    NI_ASSERT(svcInfoGetter, "");
  }

  ServiceAppearancePublisher::~ServiceAppearancePublisher()
  {
  }

  void ServiceAppearancePublisher::RegisterSubscriber( IServiceAppearanceSubscriber* ss )
  {
    LOG_D(0).Trace("%s", __FUNCTION__);

    int rc = -1;
    if (!ss)
    {
      LOG_A(0).Trace("Subscriber is NULL!");
      return;
    }

    StrongMT<RIServiceAppearanceSubscriber> subscriber = 
      StrongMT<RIServiceAppearanceSubscriber>(static_cast<RIServiceAppearanceSubscriber*>(ss));

    ClusterInfo csi;

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      StrongMT<RIServiceAppearanceSubscriber> curr = it->second.iface;
      if (curr->GetInfo().entityGUID == ss->GetInfo().entityGUID)
      {
        LOG_W(0).Trace("Subscriber already registered in publisher");
        break;
      }
    }

    if (subscribers.end() == it)
    {
      rc = 0;
    }

    if (rc >= 0)
    {
      rc = generateSubscriberId();

      bool res = subscribers.insert(make_pair(rc, subscriber)).second;
      if (!res)
      {
        rc = -2;
        LOG_E(0).Trace("Can't register subscriber: such id already exist(id=%d)", rc);
      }
    }

    if (rc >= 0)
    {
      //  gather cluster info
      svcInfoGetter->GetClusterSvcInfo(csi);
    }

    subscriber->OnRegisterSubscriber(rc, csi);

  }

  void ServiceAppearancePublisher::UnregisterSubscriber( SubcriberIdT sid, IServiceAppearanceSubscriber* subscriber)
  {
    LOG_D(0).Trace("%s(%d)", __FUNCTION__, sid);
  }

  int ServiceAppearancePublisher::Subscribe(SubcriberIdT sid, Transport::TServiceId const & svcls)
  {
    LOG_D(0).Trace("%s(%d, %s)", __FUNCTION__, sid, svcls.c_str());
    return -1;
  }

  void ServiceAppearancePublisher::Unsubscribe(SubcriberIdT sid, Transport::TServiceId const & svcls)
  {
    LOG_D(0).Trace("%s(%d, %s)", __FUNCTION__, sid, svcls.c_str());
  }

  void ServiceAppearancePublisher::OnRegisterService( Transport::TServiceId const & svcid )
  {
    LOG_D(0).Trace("%s(%s)", __FUNCTION__, svcid.c_str());

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      it->second.iface->OnRegisterService(svcid);
    }
  }

  void ServiceAppearancePublisher::OnUnregisterService( Transport::TServiceId const & svcid )
  {
    LOG_D(0).Trace("%s(%s)", __FUNCTION__, svcid.c_str());

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      it->second.iface->OnUnregisterService(svcid);
    }
  }

  void ServiceAppearancePublisher::OnStartService( Coordinator::SvcInfo const & svcinfo )
  {
    LOG_D(0).Trace("%s(%s, %s)", __FUNCTION__, svcinfo.svcid.c_str(), svcinfo.netaddr.c_str());

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      it->second.iface->OnStartService(svcinfo);
    }
  }

  void ServiceAppearancePublisher::OnStopService( Transport::TServiceId const & svcid )
  {
    LOG_D(0).Trace("%s(%s)", __FUNCTION__, svcid.c_str());

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      it->second.iface->OnStopService(svcid);
    }
  }

  void ServiceAppearancePublisher::OnChangeServiceStatus( Transport::TServiceId const & _svcid, Coordinator::ServiceStatus::Enum _status )
  {
    LOG_D(0).Trace("%s(svcid=%s status=%s)", __FUNCTION__, _svcid.c_str(), Coordinator::ServiceStatus::ToString(_status));

    SubscribersT::iterator it = subscribers.begin();
    for(; it != subscribers.end(); ++it)
    {
      it->second.iface->OnChangeServiceStatus(_svcid, _status);
    }
  }
}
