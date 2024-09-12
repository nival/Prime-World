#ifndef ILIVEMMAKING_H_INCLUDED
#define ILIVEMMAKING_H_INCLUDED

#include "LiveMMakingTypes.h"


namespace mmaking
{

class RILiveMMaking;
class RILiveMMakingClient;



REMOTE class ILiveMMakingNode
{
  NI_DECLARE_CLASS_1( ILiveMMakingNode, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual RILiveMMaking* CreateInstance( RILiveMMakingClient* _client ) = 0;
};



REMOTE class ILiveMMaking : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ILiveMMaking, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void AddMmRequest( int _mmId, const SRemoteRequest& _request ) = 0;
  REMOTE virtual void RemoveMmRequest( int _mmId ) = 0;
  REMOTE virtual void RestoreMmRequest( const SRemoteGameMember & _member ) = 0;
};

} //namespace mmaking

#endif //ILIVEMMAKING_H_INCLUDED