#ifndef ISOCIALLOBBYPVXACK_H_INCLUDED
#define ISOCIALLOBBYPVXACK_H_INCLUDED

#include "RPC/RPC.h"
#include "SocialLobbyTypes.h"


namespace socialLobby
{

REMOTE class IPvxAcknowledge : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IPvxAcknowledge, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void NewGameAck( lobby::TSocialGameId _gameId ) = 0;
  REMOTE virtual void NewReconnectingUserAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId ) = 0;
  REMOTE virtual void NewSpectatorAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId ) = 0;
  REMOTE virtual void UserLeftTheGameInCastleAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId ) = 0;
};

} //namespace socialLobby

#endif //ISOCIALLOBBYPVXACK_H_INCLUDED
