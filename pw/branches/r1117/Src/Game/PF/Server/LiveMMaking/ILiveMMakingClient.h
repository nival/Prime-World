#ifndef ILIVEMMAKINGCLIENT_H_INCLUDED
#define ILIVEMMAKINGCLIENT_H_INCLUDED

#include "LiveMMakingTypes.h"

namespace mmaking
{

REMOTE class ILiveMMakingClient : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ILiveMMakingClient, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void MmLogicSetupResult( const Transport::TServiceId & _svcId, bool _result ) = 0;

  REMOTE virtual void GameMatchmaked( const SGame & _game ) = 0;
  REMOTE virtual void GameMatchmakedForReconnect( const SReconnectSlot & _slot ) = 0;

  REMOTE virtual void MmResultAddRequest( TRequestUId _requestUId, bool _ok ) = 0;
  REMOTE virtual void MmResultRemoveRequest( TRequestUId _requestUId, bool _ok ) = 0;
  REMOTE virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) = 0;
  REMOTE virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) = 0;

  REMOTE virtual void MmDebugStatus( const char * _status ) = 0;
};

} //namespace mmaking

#endif //ILIVEMMAKINGCLIENT_H_INCLUDED
