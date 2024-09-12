#ifndef ISOCIALLOBBYPVXSVC_H_INCLUDED
#define ISOCIALLOBBYPVXSVC_H_INCLUDED

#include "RPC/RPC.h"
#include "SocialLobbyTypes.h"


namespace socialLobby
{

class IPvxAcknowledge;

REMOTE class IPvxSvc : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IPvxSvc, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void NewGame( lobby::TSocialGameId _gameId, const mmaking::SGame & _game, const PvxGameDetails & _gameDetails, NI_LPTR IPvxAcknowledge* _ack ) = 0;
  REMOTE virtual void NewReconnectingUser( lobby::TSocialGameId _gameId, TUserIdPvX _userId, NI_LPTR IPvxAcknowledge* _ack ) = 0;
  REMOTE virtual void NewSpectator( lobby::TSocialGameId _gameId, TUserIdPvX _userId, const string& _login, NI_LPTR IPvxAcknowledge* _ack, const wstring& nickname ) = 0;
  REMOTE virtual void UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, TUserIdPvX _userId, NI_LPTR IPvxAcknowledge* _ack ) = 0;
};

} //namespace socialLobby

#endif //ISOCIALLOBBYPVXSVC_H_INCLUDED
