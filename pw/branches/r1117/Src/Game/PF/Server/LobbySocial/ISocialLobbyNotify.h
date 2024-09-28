#ifndef ISOCIALLOBBYNOTIFY_H_INCLUDED
#define ISOCIALLOBBYNOTIFY_H_INCLUDED

#include "RPC/RPC.h"
#include "SocialLobbyTypes.h"


namespace socialLobby
{

class IUserContext;

REMOTE class INotify : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( INotify, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void Open( NI_LPTR IUserContext* _ctx ) = 0;
  REMOTE virtual void Failure() = 0; //AddRequest() or GetRequest() failed
  REMOTE virtual void UpdateStatus( const SMatchmakingStatus& _status ) = 0;
  REMOTE virtual void Close() = 0;
};

} //namespace socialLobby

#endif //ISOCIALLOBBYNOTIFY_H_INCLUDED
