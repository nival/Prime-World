#pragma once

#include <RPC/GateKeeper.h>
#include <Coordinator/ServiceRole.h>
#include "RelayBalancer/RelayBalancerIface.h"
#include "RelayBalancer/RelayAllocationContextFactory.h"
#include "RelayBalancer/RelayAllocationCompletedNotify.h"
#include "RelayBalancer/RelayBalancerClientNotifyIface.h"
#include "RelayBalancer/RelaySvcContextNotity.h"
#include "UserManagerSvc/RUserManagerIface.auto.h"
#include "RelayBalancer/RelayHostContext.h"
#include <Coordinator/ServiceAppearanceNotifierIface.h>
#include <Coordinator/RServiceAppearanceNotifierIface.auto.h>
#include "RelayBalancer/RelayBalancerSettings.h"

namespace Relay
{
  class SvcContext;
  class GameContext;

  class BalancerImpl : public IBalancer, 
                       public Coordinator::IServiceAppearanceSubscriber,
                       public IAllocationCompletedNotify,
                       public ISvcContextNotify,
                       public rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>, 
                       public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_6( BalancerImpl, IBalancer, Coordinator::IServiceAppearanceSubscriber, IAllocationCompletedNotify, 
      ISvcContextNotify, rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>, BaseObjectMT );

    typedef list<StrongMT<SvcContext> > SvcContextListT;
    typedef list<StrongMT<HostContext> > HostContextListT;
    typedef map<Coordinator::TServiceRole, HostContextListT> HostsByRolesT;
    typedef map<Transport::TServiceId, HostsByRolesT> SvcContextsT;

    typedef list<StrongMT<AllocationContext> > AllocCtxListT;
    typedef map<Transport::TClientId, StrongMT<UserContext> > UsersT;
    typedef map<Cluster::TGameId, StrongMT<GameContext> > GameCtxsT;

  public:
    BalancerImpl(Balancer::Settings const & _settings, rpc::GateKeeper * _gk, Transport::IAddressTranslator* _addrResolver);
    ~BalancerImpl();

    //  IBalancer
    virtual int AllocateRelay(Cluster::TGameId gameid, Transport::TClientId clientid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, int userctx, Relay::IBalancerCallback* cb);

    //  IRelaySvcAppearanceNotifier
    virtual void AddService(Transport::TServiceId const & svcid, Coordinator::TServiceRole const & role);
    virtual void RemoveService( Transport::TServiceId const & svcid );

    //  IAllocationCompletedNotify
    virtual void OnAllocationCompleted(bool _res, StrongMT<AllocationContext> const & _ctx);

    //  ISvcContextNotify
    virtual void OnUserLeaveSvc(Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole, StrongMT<UserContext> const & _uctx);

    //  IServiceAppearanceSubscriber
    virtual void OnRegisterSubscriber(Coordinator::SubcriberIdT _id, Coordinator::ClusterInfo const & _cluster);
    virtual void OnRegisterService(Transport::TServiceId const & _svcid);
    virtual void OnUnregisterService(Transport::TServiceId const & _svcid);
    virtual void OnStartService(Coordinator::SvcInfo const & _ssi);
    virtual void OnStopService(Transport::TServiceId const & svcid);
    virtual void OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status);

    //  
    int Step();

  public:
    StrongMT<SvcContext> registerService(Transport::TServiceId const & svcpath, Transport::TServiceId const & svcid, Coordinator::TServiceRole const & role);
    StrongMT<SvcContext> unregisterService(Transport::TServiceId const & svcid);
    StrongMT<SvcContext> excludeServiceFromLoad(Transport::TServiceId const & svcid);

  private:

    int AllocateRelay_(Transport::TClientId clientid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, int userctx, Relay::IBalancerCallback* cb, StrongMT<GameContext> const & _gamectx = 0);
    int AllocateGameSpecificRelay_(Cluster::TGameId _gameid, Transport::TClientId _clientid, Transport::TServiceId const & _svcpath, Coordinator::TServiceRole const & _svcrole, int _userctx, Relay::IBalancerCallback* _cb);

    SvcContextPtr findSvc(Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & role, unsigned int softlimit, unsigned int hardlimit, Transport::TServiceId const & except = Transport::EmptySvcId);
    SvcContextPtr findPrimaryRelay(Transport::TServiceId const & _svcpath, Transport::TServiceId const & _exceptRelay);
    SvcContextPtr findPrimaryRelay(Transport::TServiceId const & _svcpath, GameUserGroupPtr const & _gameusergroup, Transport::TServiceId const & _exceptRelay);
    SvcContextPtr findSecondaryRelay(Transport::TServiceId const & _svcpath, Transport::TServiceId const & _exceptRelay);
    SvcContextPtr findSecondaryRelay(Transport::TServiceId const & _svcpath, GameUserGroupPtr const & _gameusergroup, Transport::TServiceId const & _exceptRelay);
    int startRelayAllocation(Balancer::Settings const & _settings, StrongMT<UserContext> const & _uctx, Transport::TServiceId const & _svcpath, 
      int _userctx, SvcContextPtr const & _svctx, SvcContextPtr const & _secondarysvctx, 
      StrongMT<RIBalancerCallback> const & _cb, GameUserGroupPtr const & _gameusergroup);

    StrongMT<HostContext> findHost2Load(HostContextListT* _hctx);

    void OnReturn_RemoveUser(bool res, Transport::TClientId userid, rpc::CallStatus rpcsts);
    void OnReturn_OnUserLeave(bool res, Transport::TClientId userid, rpc::CallStatus rpcsts);

    int registerOpenedContext(StrongMT<SvcContext> const & svctx);
    StrongMT<HostContext> findHostCtx(HostContextListT const & hostlst, Network::NetAddress const & netaddr);

    //  rpc::IfaceRequesterCallback
    virtual void onChangeState(rpc::IfaceRequesterState::Enum _st, 
      StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher> > const & _ifacereq);

  private:
    StrongMT<rpc::GateKeeper> gk;
    SvcContextsT svcContexts;
    StrongMT<AllocationContextFactory> allocCtxFactory;
    AllocCtxListT allocCtxs4Deletion;
    StrongMT<Transport::IAddressTranslator> addrResolver;
    UsersT users_;
    StrongMT<rpc::IfaceRequester<UserManager::RIUserManager> > userMngrIface_;
    SvcContextListT registeredSvcCtxs;  //  список контекстов которые уже имеем
    SvcContextListT initSvcCtxs;  //  список контекстов находящихся в процессе инициализации, при переходе в OPENED удаляются из списка

    StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher> > svcPublisherIface_;
    Coordinator::SubcriberIdT subscriberId_;

    Balancer::Settings const & settings_;

    GameCtxsT games_;
  };
}
