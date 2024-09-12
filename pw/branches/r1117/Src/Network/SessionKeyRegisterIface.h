#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>
#include <ClusterTypes/ClusterTypes.h>

namespace Login
{

REMOTE class IAddSessionKeyCallback : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IAddSessionKeyCallback, IRemoteEntity );
  RPC_ID();

public:
  REMOTE virtual void OnAddSessionKey(int _rc, const nstl::string & _loginSvcAddr, Cluster::TUserId _userid) = 0;
};



REMOTE class ISessionKeyRegister : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ISessionKeyRegister, rpc::IRemoteEntity );
  RPC_ID();

public:
  REMOTE virtual void AddSessionKey( const nstl::string &_sessionKey, const Transport::TServiceId &_sessionPath, 
    const nstl::string &_login, Cluster::TUserId _userid, Cluster::TGameId _gameid, NI_LPTR IAddSessionKeyCallback* _pcb ) = 0;
};

} //namespace Login

