#ifndef ISOCIALLOBBY_H_INCLUDED
#define ISOCIALLOBBY_H_INCLUDED

#include "RPC/RPC.h"
#include "SocialLobbyTypes.h"


namespace mmaking
{
  class ILiveMMaking;
}


namespace socialLobby
{

class INotify;
class IPvxSvc;

REMOTE class ISocialInterface : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISocialInterface, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual void RegisterMmLogic( const Transport::TServiceId& _svcId, NI_LPTR mmaking::ILiveMMaking* _logic, int _gameModes ) = 0;
  REMOTE virtual void AddRequest( const SMatchmakingRequest& _reqData, NI_LPTR INotify* _callback ) = 0;
  REMOTE virtual void Spectate( const SMatchmakingRequestCore& _reqData, TUId _targetUid, NI_LPTR INotify* _callback ) = 0;
  REMOTE virtual void GetRequest( TUId _uid, NI_LPTR INotify* _callback ) = 0;
  REMOTE virtual SServerStatus GetServerStatus() = 0;
};



REMOTE class IPvxInterface : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPvxInterface, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual bool PvxInstance( NI_LPTR IPvxSvc* _pvx, const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings ) = 0;
  REMOTE virtual bool UpdatePvxSettings( const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings ) = 0;
  REMOTE virtual void PvxInstanceLoadNotify( const string& _clusterId, const Transport::TServiceId& _svcId, unsigned _load ) = 0;
  REMOTE virtual bool PvXPreparedForUser( TUserIdPvX _userId, const string & _key ) = 0;
  REMOTE virtual bool UserEnteredPvX( TUserIdPvX _userId ) = 0;
  REMOTE virtual bool UserDroppedFromPvX( TUserIdPvX _userId, bool _intentional ) = 0;
  REMOTE virtual bool GameFinished( lobby::TSocialGameId _gameId, /*lobby::ETeam::Enum*/ int _winner ) = 0;
};



REMOTE class IDevSocLobby : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IDevSocLobby, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual SDevUidRange AcquireUIdRange( int count ) = 0;
};

} //namespace socialLobby

#endif //ISOCIALLOBBY_H_INCLUDED
