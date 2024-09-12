#include "stdafx.h"
#include "LobbyServerLoginWrapper.h"
#include "RPC/GateKeeper.h"
#include "Network/RSessionKeyRegisterIface.auto.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "Server/NewLogin/NewLoginTypes.h"
#include "ClientControl/RClientControlInterface.auto.h"
#include "ClientControl/ClientControlTypes.h"
#include "ClientControl/ClientControlRemote.h"
#include "Coordinator/LoginServerNaming.h"
#include "System/NiTimer.h"
#include "LobbyLog.h"


namespace lobby
{

TcpLoginWrapper::TcpLoginWrapper( rpc::GateKeeper * _gateKeeper )
{
  loginSvc = new rpc::IfaceRequester<Login::RISessionKeyRegister>;

  if ( rdp_transport::RdpTransportEnabled() )
    loginSvc->init( _gateKeeper, newLogin::serviceIds::Service, newLogin::serviceIds::SessionKeySvc );
  else
    loginSvc->init( _gateKeeper, Login::serviceId, Login::serviceIface.c_str() );
}



void TcpLoginWrapper::Poll()
{
  loginSvc->step();
}



void TcpLoginWrapper::AddSessionKey( const string & sessionLogin, const Transport::TServiceId & sessionPath, const string & zzLogin, int zzUserId, Cluster::TGameId gameid, Login::IAddSessionKeyCallback * callback )
{
  if ( !loginSvc->isopen() )
  {
    LOBBY_LOG_ERR( "No SessionLogin available for sessionLogin=%s, userid=%d", sessionLogin.c_str(), zzUserId );
    return;
  }

  loginSvc->iface()->AddSessionKey( sessionLogin, sessionPath, zzLogin, zzUserId, gameid, callback );
}













class RdpLoginWrapper::Request : public clientCtl::ILoginSvcAllocationCallback, public Login::IAddSessionKeyCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( Request, clientCtl::ILoginSvcAllocationCallback, Login::IAddSessionKeyCallback, BaseObjectMT );

public:
  enum EState { StInit, StAllocating, StWaitingKey, StDone };

  const string  key;
  const Transport::TServiceId svcPath;
  const string  login;
  const Transport::TClientId uid;
  const Cluster::TGameId gameid;

  EState        state;
  timer::Timer  timeout;
  WeakMT<Login::IAddSessionKeyCallback> callback;

  Request( const string & _key, const Transport::TServiceId & _svcPath, const string & _login, Transport::TClientId _uid, Cluster::TGameId _gameid, Login::IAddSessionKeyCallback * _callback ) :
  key( _key ),
  svcPath( _svcPath ),
  login( _login ),
  uid( _uid ),
  gameid( _gameid ),
  state( StInit ),
  callback( _callback ),
  timeout( 20.0f )
  {}

  //clientCtl::ILoginSvcAllocationCallback
  virtual void LoginSvcAllocated( int _alllocId, const Transport::TServiceId & _svcid, Login::ISessionKeyRegister * _sessionKeyInterface ) {
    LOBBY_LOG_MSG( "Login service allocated. svcid=%s, rptr=%08x", _svcid.c_str(), (void*)_sessionKeyInterface );

    if ( state != StAllocating )
      LOBBY_LOG_ERR( "Wrong login service allocating state. st=%d", (int)state );

    NI_VERIFY( _sessionKeyInterface, "", state = StDone; return );

    _sessionKeyInterface->AddSessionKey( key, svcPath, login, uid, gameid, this );
    state = StWaitingKey;
  }

  //clientCtl::ILoginSvcAllocationCallback
  virtual void LoginSvcAllocationFailed( int _alllocId ) {
    state = StDone;
  }

  virtual void OnAddSessionKey(int _rc, const nstl::string & _loginSvcAddr, Cluster::TUserId _userid)
  {
    LOBBY_LOG_MSG( "Got login key ack. uid=%d, login_addr=%s", _userid, _loginSvcAddr.c_str() );

    if ( state != StWaitingKey )
      LOBBY_LOG_ERR( "Wrong login key allocation state. st=%d", (int)state );

    if ( StrongMT<Login::IAddSessionKeyCallback> locked = callback.Lock() )
      locked->OnAddSessionKey( _rc, _loginSvcAddr, _userid );
    else
      LOBBY_LOG_ERR( "Login key dead callback" );

    state = StDone;
  }

  bool Poll( clientCtl::IInterface * _cctrl )
  {
    if ( state == StDone )
      return false;

    if ( ( state == StInit ) && _cctrl )
    {
      _cctrl->AllocateLoginSvc( uid, this );
      state = StAllocating;
      return true;
    }

    if ( timeout.Running() && timeout.Poll() )
    {
      LOBBY_LOG_ERR( "Login key allocation timed out. uid=%d", uid );
      return false;
    }

    return true;
  }
};




RdpLoginWrapper::RdpLoginWrapper( rpc::GateKeeper * _gateKeeper )
{
  clientControl = new rpc::IfaceRequester<clientCtl::RIInterface>;

  clientControl->init( _gateKeeper, clientCtl::serviceIds::Service, clientCtl::serviceIds::Gate );
}



void RdpLoginWrapper::Poll()
{
  clientControl->step();

  for ( Requests::iterator it = requests.begin(); it != requests.end(); )
  {
    if ( (*it)->Poll( clientControl->isopen() ? clientControl->iface() : 0 ) )
      ++it;
    else
      it = requests.erase( it );
  }
}



void RdpLoginWrapper::AddSessionKey( const string & sessionLogin, const Transport::TServiceId & sessionPath, const string & zzLogin, int zzUserId, Cluster::TGameId gameid, Login::IAddSessionKeyCallback * callback )
{
  StrongMT<Request> req = new Request( sessionLogin, sessionPath, zzLogin, zzUserId, gameid, callback );
  requests.push_back( req );
}

} //namespace lobby
