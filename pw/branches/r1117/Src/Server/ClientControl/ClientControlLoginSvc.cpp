#include "stdafx.h"
#include "ClientControlLoginSvc.h"
#include "ClientControlRemote.h"
#include "Network/SessionKeyRegisterIface.h"
#include "ClientControlLog.h"


namespace clientCtl
{

LoginSvc::LoginSvc( IConfigProvider * _config, const Transport::TServiceId & _svcid, Login::ISessionKeyRegister * _svc, timer::Time _now ) :
svcId( _svcid ),
config( _config ),
remoteLogin( _svc ),
now( _now ),
updateTimeout( _config->Cfg()->loginSvcUpdTimeout ),
state( ELoginSvcState::Online ),
load( 0 )
{
}



bool LoginSvc::Poll( timer::Time _now )
{
  now = _now;

  if ( remoteLogin->GetStatus() != rpc::Connected )
  {
    CLIENTCTL_LOG_ERR( "Lost connection to login service. svcid=%d", svcId.c_str() );
    return false;
  }

  if ( updateTimeout.Poll() )
  {
    CLIENTCTL_LOG_ERR( "Login service update timed out. svcid=%d", svcId.c_str() );
    return false;
  }

  return true;
}



void LoginSvc::Update( ELoginSvcState::Enum _state, unsigned _load )
{
  CLIENTCTL_LOG_DBG( "Login service load updated. svcid=%d, state=%d, load=%u", svcId.c_str(), (int)_state, _load );

  state = _state;
  load = _load;
  updateTimeout.Restart();
}

} //namespace clientCtl
