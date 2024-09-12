#ifndef CLIENTCONTROLUSER_H_INCLUDED
#define CLIENTCONTROLUSER_H_INCLUDED

#include "ClientControlTypes.h"
#include "ClientControlConfig.h"
#include "System/NiTimer.h"
#include <list>


namespace clientCtl
{

class IClientAuth;
class IUserPresenceCallback;
class LoginSvc;

struct EUserState
{
  enum Enum
  {
    Active,
    Reentering,
    KickingForGood
  };
};

class UserCtx : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( UserCtx, BaseObjectST );

public:
  UserCtx( IConfigProvider * _config, Transport::TClientId _uid, Transport::TUserSid _userSid, LoginSvc * _svc, IUserPresenceCallback * _callback, timer::Time _now );

  Transport::TClientId Uid() const { return uid; }
  Transport::TUserSid UserSid() const { return userSid; }
  const Transport::TServiceId & LoginSvcId() const { return loginSvcId; }
  EUserState::Enum State() const { return state; }

  bool Poll( timer::Time _now );

  void WaitPreviousUsers( UserCtx * _prevUser );
  void Kick();

private:
  typedef std::list<Weak<UserCtx> >   UserList;

  StrongMT<IConfigProvider>           config;
  const Transport::TClientId          uid;
  const Transport::TUserSid           userSid;
  const Transport::TServiceId         loginSvcId;
  StrongMT<IUserPresenceCallback>     callback;
  EUserState::Enum                    state;
  Weak<LoginSvc>                      loginSvc;
  UserList                            prevInstances;
  timer::Timer                        timeout;
  timer::Timer                        linkCheckTimer;

  void Switch( EUserState::Enum _st );
  bool PollReentering();
};

} //namespace clientCtl

#endif //CLIENTCONTROLUSER_H_INCLUDED
