#ifndef LOBBYCLIENTINTERFACE_H_INCLUDED
#define LOBBYCLIENTINTERFACE_H_INCLUDED

#include "RPC/RPC.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/Roll/RollTypes.h"


namespace Peered
{
  class RIGameServer;
}


namespace lobby
{

REMOTE class ILobbyUser : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ILobbyUser, IBaseInterfaceMT);

public:
  RPC_ID();

  REMOTE virtual void AddGameInfo( const SDevGameInfo & info ) = 0;

  REMOTE virtual void JoinCustomSession( const SGameParameters & params ) = 0;
  REMOTE virtual void UpdateClientStatus( /*EOperationResult::Enum*/ int status ) = 0;

  REMOTE virtual void AddCustomGameMember( const SGameMember & member ) = 0;
  REMOTE virtual void RemoveCustomGameMember( int userId ) = 0;
  REMOTE virtual void UpdateCustomGameMember( int userId, const SPlayerGameContext & params ) = 0;
  REMOTE virtual void UpdateCustomGameMemberReadiness( int userId, bool ready ) = 0;

  REMOTE virtual void StartSession( TGameId sessionId, const SGameParameters & params, const TGameLineUp & gameLineUp, Peered::RIGameServer * gameServerInstance, const Peered::SInstanceId & _gsInstId, unsigned timestamp32 ) = 0;

  REMOTE virtual void Award( const vector<roll::SAwardInfo> & _awards ) = 0;
};

}; //namespace lobby

#endif //LOBBYCLIENTINTERFACE_H_INCLUDED
