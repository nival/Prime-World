#ifndef ILIVEMMAKING_H_INCLUDED
#define ILIVEMMAKING_H_INCLUDED

#include "LiveMMakingTypes.h"


namespace mmaking
{

class RILiveMMaking;
class ILiveMMakingClient;
class RILiveMMakingClient;



REMOTE class ILiveMMaking : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ILiveMMaking, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void SetupLogic( const string & _mapId, NI_LPTR ILiveMMakingClient* _client ) = 0;

  REMOTE virtual void AddMmRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime ) = 0;
  REMOTE virtual void RemoveMmRequest( TRequestUId _requestUId ) = 0;

  REMOTE virtual void AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData ) = 0;
  REMOTE virtual void RemoveGame( lobby::TGameId _gameId ) = 0;
};

} //namespace mmaking

#endif //ILIVEMMAKING_H_INCLUDED
