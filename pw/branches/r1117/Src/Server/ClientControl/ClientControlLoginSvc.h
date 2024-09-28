#ifndef CLIENTCONTROLLOGINSVC_H_INCLUDED
#define CLIENTCONTROLLOGINSVC_H_INCLUDED

#include "ClientControlTypes.h"
#include "ClientControlConfig.h"
#include "System/NiTimer.h"
#include <map>


namespace Login
{
  class ISessionKeyRegister;
}


namespace clientCtl
{

class UserCtx;
class IUserPresenceCallback;

class LoginSvc : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoginSvc, BaseObjectST );

public:
  LoginSvc( IConfigProvider * _config, const Transport::TServiceId & _svcid, Login::ISessionKeyRegister * _svc, timer::Time _now );

  bool Poll( timer::Time _now );
  void Update( ELoginSvcState::Enum _state, unsigned _load );

  Login::ISessionKeyRegister * Remote() const { return remoteLogin; }
  const Transport::TServiceId & SvcId() const { return svcId; }
  ELoginSvcState::Enum State() const { return state; }
  unsigned Load() const { return load; }
  void IncLoad( unsigned _inc ) { load += _inc; }

private:
  const Transport::TServiceId           svcId;
  StrongMT<IConfigProvider>             config;
  StrongMT<Login::ISessionKeyRegister>  remoteLogin;
  timer::Time                           now;
  timer::Timer                          updateTimeout;
  ELoginSvcState::Enum                  state;
  unsigned                              load;
};

} //namespace clientCtl

#endif //CLIENTCONTROLLOGINSVC_H_INCLUDED
