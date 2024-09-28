#include "stdafx.h"
#include "NewLoginService.h"
#include "NewLoginLog.h"
#include "NewLoginLogic.h"
#include "ClientAuth.h"
#include "NewLoginSvcLinkInterface.h"
#include "NewLoginSvcLink.h"
#include "Network/LSessionKeyRegisterIface.auto.h"
#include "Network/ClusterConfiguration.h"
#include "ClientControl/ClientControlTypes.h"
#include "ClientControl/RClientControlInterface.auto.h"
#include "ClientControl/LClientControlRemote.auto.h"
#include "RdpTransport/LRdpFrontendAgentRemote.auto.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "rpc/IfaceRequester.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( Login::ISessionKeyRegister );


namespace newLogin
{

class ClientCtrlAccessor : public clientCtl::IInterfaceAccessor, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ClientCtrlAccessor, clientCtl::IInterfaceAccessor, BaseObjectMT );
public:
  ClientCtrlAccessor( rpc::GateKeeper * _gk )
  {
    remote = new rpc::IfaceRequester<clientCtl::RIInterface>;
    remote->init( _gk, clientCtl::serviceIds::Service, clientCtl::serviceIds::Gate );
  }

  void Poll()
  {
    threading::MutexLock lock( mutex );
    remote->step();

    while ( true )
    {
      rpc::IfaceRequesterState::Enum newSt = remote->PopNewState();
      if ( newSt == rpc::IfaceRequesterState::NONE )
        break;
      if ( newSt == rpc::IfaceRequesterState::OPENED )
        newlyConnected = true;
    }
  }

  bool PopNewlyConnected()
  {
    threading::MutexLock lock( mutex );

    if ( newlyConnected ) {
      newlyConnected = false;
      return true;
    }
    return false;
  }

  virtual StrongMT<clientCtl::IInterface> GetClientControl() const
  {
    threading::MutexLock lock( mutex );

    if ( StrongMT<clientCtl::IInterface> ptr = remote->iface() )
      if ( ptr->GetStatus() == rpc::Connected )
        return ptr;
    return 0;
  }

private:
  threading::Mutex mutex;
  StrongMT<rpc::IfaceRequester<clientCtl::RIInterface>>  remote;
  bool newlyConnected;
};







class SvcLinkDict : public ISvcLinkDict, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SvcLinkDict, ISvcLinkDict, BaseObjectMT );
public:
  SvcLinkDict( rpc::GateKeeper * _gk, Transport::IAddressTranslator * _addrTr ) :
  gateKeeper( _gk ),
  addrTranslator( _addrTr )
  {}

  virtual StrongMT<ISvcLink> GetSvcLink( const Transport::TServiceId & _svcId )
  {
    NI_PROFILE_FUNCTION;

    NEWLOGIN_LOG_MSG( "Link to service requested. svc_id=%s", _svcId.c_str() );

    StrongMT<Transport::IAddressTranslator> at = addrTranslator.Lock();
    NI_VERIFY( at, "", return 0 );
    Network::NetAddress svcAddr = at->GetSvcAddress( _svcId );
    if ( svcAddr.empty() )
    {
      NEWLOGIN_LOG_WRN( "Unknown service requested. svc_id=%s", _svcId.c_str() );
      return 0;
    }

    threading::MutexLock lock( mutex );

    StrongMT<SvcLink> & slot = dict[_svcId];

    if ( slot.Valid() )
    {
      if ( slot->Failed() )
        NEWLOGIN_LOG_WRN( "Found failed link to service. svc_id=%s", _svcId.c_str() );
      else
        return slot.Get();
    }

    NEWLOGIN_LOG_MSG( "Creating new service link. svc_id=%s, addr=%s", _svcId.c_str(), svcAddr );
    slot = new SvcLink( gateKeeper, _svcId, svcAddr );
    return slot.Get();
  }

  void Poll()
  {
    threading::MutexLock lock( mutex );

    for ( Dict::iterator it = dict.begin(); it != dict.end(); )
    {
      SvcLink * link = it->second;
      link->Poll();
      if ( link->Failed() )
      {
        NEWLOGIN_LOG_WRN( "Removing service link. svc_id=%s", link->SvcId().c_str() );
        it = dict.erase( it );
      }
      else
        ++it;
    }
  }

private:
  typedef std::map<Transport::TServiceId, StrongMT<SvcLink> > Dict;

  StrongMT<rpc::GateKeeper> gateKeeper;
  WeakMT<Transport::IAddressTranslator> addrTranslator;
  threading::Mutex mutex;
  Dict dict;
};








InstanceSvc::InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
active( false ),
softStopped( false ),
loadNotifyTimer()
{
  if ( !rdp_transport::RdpTransportEnabled() )
  {
    NEWLOGIN_LOG_WRN( "RDP transport is disabled. 'newlogin' service is suspended" );
    return;
  }

  RegisterBackendAttach<Login::ISessionKeyRegister, Login::LISessionKeyRegister>();
  //RegisterBackendAttach<Login::IAddSessionKeyCallback, Login::LIAddSessionKeyCallback>();
  RegisterBackendAttach<clientCtl::IUserPresenceCallback, clientCtl::LIUserPresenceCallback>();
  RegisterBackendAttach<rdp_transport::IFrontendAgentRemote, rdp_transport::LIFrontendAgentRemote>();

  config = CreateConfigFromStatics();

  auth = new ClientAuth( config, Now() );
  //RegisterBackendObject<Login::ISessionKeyRegister>( auth, serviceIds::SessionKeySvc );

  clientControl = new ClientCtrlAccessor( BackendGk() );

  svcLinkDict = new SvcLinkDict( BackendGk(), CoordClient()->GetFrontendAddressTranslator() );

  ni_udp::NetAddr loginAddr( Network::GetLoginServerAddress().c_str() );
  logic = new Logic( loginAddr, config, auth, clientControl, svcLinkDict, Now(), SvcId() );

  auth->SetLoginAddress( logic->ListenAddress().c_str() );

  loadNotifyTimer.Restart( config->Cfg()->loadUpdatePeriod );

  active = true;
}



InstanceSvc::~InstanceSvc()
{
}



void InstanceSvc::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  if ( !active )
    return;

  auth->Poll( _now );

  clientControl->Poll();

  svcLinkDict->Poll();

  size_t usersNumber = 0;
  if ( logic )
    logic->Poll( _now, usersNumber );

  if ( clientControl->PopNewlyConnected() )
    if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
      cc->RegisterLoginSvc( SvcId(), auth );

  if ( loadNotifyTimer.Poll() )
  {
    loadNotifyTimer.Restart();

    if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
    {
      int svcState = softStopped ? clientCtl::ELoginSvcState::SoftStopped : clientCtl::ELoginSvcState::Online;
      NEWLOGIN_LOG_DBG( "Notifying Client Control about service load. svcid=%s, state=%d, load=%u", SvcId().c_str(), svcState, usersNumber );
      cc->UpdateLoginSvc( SvcId(), svcState, usersNumber );
    }
  }
}



void InstanceSvc::OnSoftStop()
{
  NEWLOGIN_LOG_MSG( "Stopping softly. svcid=%s", SvcId().c_str() );

  softStopped = true;
}



void InstanceSvc::OnConfigReload()
{
  config->ReloadConfig();
}

} //namespace newLogin
