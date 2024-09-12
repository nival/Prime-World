#ifndef CLIENTCONTROLLOGIC_H_INCLUDED
#define CLIENTCONTROLLOGIC_H_INCLUDED

#include "ClientControlTypes.h"
#include "ClientControlInterface.h"
#include "ClientControlConfig.h"
#include "System/NiTimer.h"
#include <list>
#include <map>


namespace clientCtl
{

class UserCtx;
class LoginSvc;

class Logic : public IInterface, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Logic, IInterface, BaseObjectMT );

public:
  Logic( IConfigProvider * _config, timer::Time _now );

  void Poll( timer::Time _now, unsigned & _ccu );

protected:
  //IInterface
  virtual void RegisterLoginSvc( const Transport::TServiceId & _svcid, Login::ISessionKeyRegister * _sessionKeyInterface );
  virtual void UpdateLoginSvc( const Transport::TServiceId & _svcid, int _state, unsigned _load );
  virtual void AllocateLoginSvc( int _alllocId, ILoginSvcAllocationCallback * _callback );
  virtual void UserEnters( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid, IUserPresenceCallback * _callback );
  virtual void UserLeft( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid );
  virtual void KickUser( Transport::TClientId _uid );

private:
  typedef std::map<Transport::TServiceId, Strong<LoginSvc> > TLogins;
  typedef std::map<Transport::TClientId, Strong<UserCtx> > TUsers;
  typedef std::list<Strong<UserCtx> >  TUserList;

  StrongMT<IConfigProvider>     config;
  timer::Time                   now;
  TLogins                       logins;
  TUsers                        users;
  TUserList                     disconnectingUsers;
  timer::Timer                  dbgDumpTimeout;

  void PollLoginSvc();
  void PollUsers();
  void PollDisconnectedUsers();
  void PollDebug();
};

} //namespace clientCtl

#endif //CLIENTCONTROLLOGIC_H_INCLUDED
