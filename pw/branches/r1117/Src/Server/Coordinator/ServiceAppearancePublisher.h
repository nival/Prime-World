#pragma once
#include "ServiceAppearanceNotifierIface.h"
#include "RServiceAppearanceNotifierIface.auto.h"
#include "ServiceAppearanceNotifySink.h"

namespace Coordinator
{
  class ServiceAppearancePublisher : public Coordinator::IServiceAppearancePublisher, 
                                     public Coordinator::IServiceAppearanceNotifySink, 
                                     BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3(ServiceAppearancePublisher, IServiceAppearancePublisher, IServiceAppearanceNotifySink, BaseObjectMT);

    struct SubscriberContext
    {
      SubscriberContext()
      {
      }

      SubscriberContext(StrongMT<RIServiceAppearanceSubscriber> const & _iface)
        :iface(_iface)
      {}

      StrongMT<RIServiceAppearanceSubscriber> iface;
    };

    typedef nstl::map<int, SubscriberContext> SubscribersT;

  public:

    ServiceAppearancePublisher(StrongMT<Coordinator::IClusterServicesInfo> const & csi);
   ~ServiceAppearancePublisher();

   // IServiceAppearancePublisher
   virtual void RegisterSubscriber( IServiceAppearanceSubscriber* subscriber );
   virtual void UnregisterSubscriber( SubcriberIdT sid, IServiceAppearanceSubscriber* subscriber);
   virtual int Subscribe(SubcriberIdT sid, Transport::TServiceId const & svcls);
   virtual void Unsubscribe(SubcriberIdT sid, Transport::TServiceId const & svcls);

  protected:
    //  IServiceAppearanceNotifySink
    virtual void OnRegisterService( Transport::TServiceId const & svcid );
    virtual void OnUnregisterService( Transport::TServiceId const & svcid );
    virtual void OnStartService( Coordinator::SvcInfo const & svcinfo );
    virtual void OnStopService( Transport::TServiceId const & svcid );
    virtual void OnChangeServiceStatus( Transport::TServiceId const & _svcid, Coordinator::ServiceStatus::Enum _status );

  private:
    int generateSubscriberId();


  private:
   int genSubscriberId;

   SubscribersT subscribers;
   StrongMT<Coordinator::IClusterServicesInfo> svcInfoGetter;
  };

  inline
  int ServiceAppearancePublisher::generateSubscriberId()
  {
    return ++genSubscriberId;
  }
}
