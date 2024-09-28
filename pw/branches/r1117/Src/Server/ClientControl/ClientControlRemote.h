#ifndef CLIENTCONTROLREMOTE_H_INCLUDED
#define CLIENTCONTROLREMOTE_H_INCLUDED

#include "ClientControlTypes.h"

namespace Login
{
  class ISessionKeyRegister;
}

namespace clientCtl
{

REMOTE class IUserPresenceCallback : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( IUserPresenceCallback, rpc::IRemoteEntity );

public:
  REMOTE virtual void LetUserIn() = 0;
  REMOTE virtual void DenyUser() = 0;
  REMOTE virtual void KickUser() = 0;
};


REMOTE class ILoginSvcAllocationCallback : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( ILoginSvcAllocationCallback, rpc::IRemoteEntity );

public:
  REMOTE virtual void LoginSvcAllocated( int _alllocId, const Transport::TServiceId & _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface ) = 0;
  REMOTE virtual void LoginSvcAllocationFailed( int _alllocId ) = 0;
};

}; //namespace clientCtl

#endif //CLIENTCONTROLREMOTE_H_INCLUDED
