#pragma once

#include "ClusterAdminSvcIntf.h"
#include <Coordinator/Interface.h>
#include <Coordinator/ServiceAppearanceNotifierIface.h>
#include <Coordinator/RServiceAppearanceNotifierIface.auto.h>
#include <Coordinator/RCoordinatorServerIface.auto.h>
#include <rpc/IfaceRequester.h>
#include "gen-cpp/ClusterManagementAPI_types.h"

namespace ClusterAdmin
{
  namespace Thrift
  {
    class ServiceInfo;
  }

  class ClusterAdminImpl : public IClusterAdmin, public Coordinator::IServiceAppearanceSubscriber, 
    public rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>, 
    public rpc::IfaceRequesterCallback<Coordinator::RICoordinatorServerRemote>, 
    public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_5( ClusterAdminImpl, 
      IClusterAdmin, 
      Coordinator::IServiceAppearanceSubscriber, 
      rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>,
      rpc::IfaceRequesterCallback<Coordinator::RICoordinatorServerRemote>, 
      BaseObjectMT );

    RPC_REDEFINE_ID();

    struct SvcContext
    {
      Transport::TServiceId svcid;
      Coordinator::ServiceStatus::Enum sts;
      Network::NetAddress netaddr;
      Network::NetAddress frontendaddr;
      unsigned int pid;
      nstl::string machineName;

      SvcContext()
        :sts(Coordinator::ServiceStatus::S_STOPPED), pid(0){}
      SvcContext(Transport::TServiceId const & _svcid, 
        Coordinator::ServiceStatus::Enum st = Coordinator::ServiceStatus::S_STOPPED)
        :svcid(_svcid),
        sts(st),
        pid(0)
      {}

      bool operator ==(SvcContext const & other) const
      {
        return svcid == other.svcid;
      }
    };

    typedef list<SvcContext> SvcContextsT;

  public:
    ClusterAdminImpl( StrongMT<rpc::GateKeeper> const & gk, Coordinator::ICoordinatorClient* cclient );
    ~ClusterAdminImpl();

    //  IClusterAdmin
    virtual void Shutdown(unsigned int timeout);

    //  Coordinator::IServiceAppearanceSubscriber
    virtual void OnRegisterSubscriber(Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster);
    virtual void OnRegisterService( Transport::TServiceId const & svcid );
    virtual void OnUnregisterService( Transport::TServiceId const & svcid );
    virtual void OnStartService( Coordinator::SvcInfo const & ssi );
    virtual void OnStopService( Transport::TServiceId const & svcid );
    virtual void OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status);

    //  ClusterManagementIf (thirf interface)
    void GetServices(std::vector<Thrift::ServiceInfo> & _return);
    void GetServicesByMachine(std::vector<Thrift::ServiceInfo> & _return, const std::string& machine);
    void GetServicesByType(std::vector<Thrift::ServiceInfo> & _return, const std::string& stype);
    void GetServiceById(Thrift::ServiceInfo& _return, const std::string& serviceid);
    int32_t ExecuteCommand(const std::string& serviceid, const Thrift::ServiceCommand::type command, const std::string& arguments);
    int32_t ChangeParameters(const std::string& serviceid, const std::vector<Thrift::ServiceParameter> & parameters, const bool saveinconfig);

    void Step();

  protected:

    SvcContext* findSvcContext_(Transport::TServiceId const & svcid);
    bool removeSvcContext_(Transport::TServiceId const & svcid);

    //  rpc::IfaceRequesterCallback
    virtual void onChangeState(rpc::IfaceRequesterState::Enum st, 
      StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> const & ifacereq);
    virtual void onChangeState(rpc::IfaceRequesterState::Enum st, 
      StrongMT<rpc::IfaceRequester<Coordinator::RICoordinatorServerRemote>> const & ifacereq);

    void getServiceInfo_(SvcContext const & svctx, Thrift::ServiceInfo & si);
    void getServiceType_(SvcContext const & svctx, std::string & svctype);

    void setSvcCtxData_(Coordinator::SvcInfo const & si, SvcContext& svctx);

    Thrift::ServiceStatus::type svcStatus2thift_(Coordinator::ServiceStatus::Enum sts);

  private:
    Coordinator::ICoordinatorClient* coordClient_;

    bool shutdown_;
    unsigned int shutdownTimeout_;
    NHPTimer::FTime shutdownStart_;

    typedef StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> SvcPublisherIfaceReqT;
    SvcPublisherIfaceReqT svcPublisherIfaceReq;
    typedef StrongMT<rpc::IfaceRequester<Coordinator::RICoordinatorServerRemote>> CoordinatorIfaceReqT;
    CoordinatorIfaceReqT coordinatorIfaceReq;

    SvcContextsT contexts;
    Coordinator::SubcriberIdT subscriberId;
  };
}
