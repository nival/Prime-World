#pragma once
#include <Network/TransportTypes.h>
#include <Coordinator/CoordinatorServiceStatus.h>

namespace Coordinator
{
  struct ClusterInfo;
  struct SvcInfo;

  class IClusterServicesInfo : public IBaseInterfaceMT
  {
  public:
    virtual void GetClusterSvcInfo(ClusterInfo & csi) = 0;
  };

  class IServiceAppearanceNotifySink : public IBaseInterfaceMT
  {
  public:
    virtual void OnRegisterService( Transport::TServiceId const & svcid ) = 0;
    virtual void OnUnregisterService( Transport::TServiceId const & svcid ) = 0;
    virtual void OnStartService( Coordinator::SvcInfo const & svcinfo ) = 0;
    virtual void OnStopService( Transport::TServiceId const & svcid ) = 0;
    virtual void OnChangeServiceStatus(Transport::TServiceId const & _svcid, Coordinator::ServiceStatus::Enum _status) = 0;
  };
}
