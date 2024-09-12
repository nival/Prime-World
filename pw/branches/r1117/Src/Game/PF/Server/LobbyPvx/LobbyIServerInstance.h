#ifndef LOBBYISERVERINSTANCE_H_INCLUDED
#define LOBBYISERVERINSTANCE_H_INCLUDED


#include "CommonTypes.h"


namespace Peered
{
  class RIGameServer;
}


namespace lobby
{

REMOTE class IServerInstance : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IServerInstance, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual void SetDeveloperSex( int /*ESex::Enum*/ _sex ) = 0;
  REMOTE virtual void RequestGamesList() = 0;
  REMOTE virtual EOperationResult::Enum JoinGame( int gameId ) = 0;
  REMOTE virtual EOperationResult::Enum ReconnectToCustomGame( int gameId, /*ETeam::Enum*/ int team, const string & heroId ) = 0;
  REMOTE virtual EOperationResult::Enum CreateCustomGame( int maxPlayers, int maxPlayersPerTeam, const string & mapId, int autostartPlayers ) = 0;
  REMOTE virtual EOperationResult::Enum SpectateCustomGame( int gameId ) = 0;
  REMOTE virtual void ChangeCustomGameSettings( /*ETeam::Enum*/ int team,/*ETeam::Enum*/ int faction, const string & heroId ) = 0;
  REMOTE virtual void SetReady( /*ECustomGamePlayerReadiness::Enum*/ int readiness ) = 0;
  REMOTE virtual void SetDeveloperParty( int party ) = 0;

  REMOTE virtual EOperationResult::Enum JoinSocialGame() = 0;
};

}; //namespace lobby

#endif //LOBBYISERVERINSTANCE_H_INCLUDED
