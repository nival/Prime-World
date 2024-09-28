#ifndef CLIENTCONTROLINTERFACE_H_INCLUDED
#define CLIENTCONTROLINTERFACE_H_INCLUDED

#include "ClientControlTypes.h"

namespace Login
{
  class ISessionKeyRegister;
}

namespace clientCtl
{

class IUserPresenceCallback;
class ILoginSvcAllocationCallback;


REMOTE class IInterface : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( IInterface, IBaseInterfaceMT );

public:
  //Login server balancing
  REMOTE virtual void RegisterLoginSvc( const Transport::TServiceId& _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface ) = 0;
  REMOTE virtual void UpdateLoginSvc( const Transport::TServiceId& _svcid, int _state, unsigned _load ) = 0;
  REMOTE virtual void AllocateLoginSvc( int _alllocId, NI_LPTR ILoginSvcAllocationCallback* _callback ) = 0;

  //User presence control
  REMOTE virtual void UserEnters( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid, NI_LPTR IUserPresenceCallback* _callback ) = 0;
  REMOTE virtual void UserLeft( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid ) = 0;
  REMOTE virtual void KickUser( Transport::TClientId _uid ) = 0;
};


//Wrapper for MT access and transparent networking reconnect
class IInterfaceAccessor : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IInterfaceAccessor, IBaseInterfaceMT );

public:
  virtual StrongMT<IInterface> GetClientControl() const = 0;
};

}; //namespace clientCtl

#endif //CLIENTCONTROLINTERFACE_H_INCLUDED
