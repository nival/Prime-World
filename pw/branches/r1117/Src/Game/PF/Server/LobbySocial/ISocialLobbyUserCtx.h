#ifndef ISOCIALLOBBYUSERCTX_H_INCLUDED
#define ISOCIALLOBBYUSERCTX_H_INCLUDED

#include "RPC/RPC.h"
#include "SocialLobbyTypes.h"


namespace socialLobby
{

REMOTE class IUserContext : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IUserContext, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void AcceptGameSession( const SPlayerData& _playerData ) = 0;
  REMOTE virtual void ChangeGuardHero( const SPlayerData& _playerData ) = 0;
  REMOTE virtual void GuardReady() = 0;
  REMOTE virtual void ReconnectToGame() = 0;
  REMOTE virtual void LeaveGame() = 0;
  REMOTE virtual void CancelRequest() = 0;
  REMOTE virtual void CancelPartyRequest() = 0;
  REMOTE virtual void EmergencyCancel() = 0;
};

} //namespace socialLobby

#endif //ISOCIALLOBBYUSERCTX_H_INCLUDED
