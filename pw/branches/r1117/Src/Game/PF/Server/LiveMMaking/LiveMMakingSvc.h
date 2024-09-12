#ifndef LIVEMMAKINGSVC_H_INCLUDED
#define LIVEMMAKINGSVC_H_INCLUDED

#include "ILiveMMaking.h"
#include "IMMakingLogic.h"


namespace NDb
{
  struct AdvMapDescription;
}


namespace mmaking
{

class IMMakingLogic;

class LiveMMaking : public ILiveMMaking, public IMMakingLogicCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( LiveMMaking, ILiveMMaking, IMMakingLogicCallback, BaseObjectMT );

public:
  LiveMMaking( const Transport::TServiceId & _serviceId );
  ~LiveMMaking();

  void Poll();

  void OnConfigReload();

protected:
  //ILiveMMaking
  virtual void SetupLogic( const string & _mapId, ILiveMMakingClient * _client );
  virtual void AddMmRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime );
  virtual void RemoveMmRequest( TRequestUId _requestUId );
  virtual void AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData );
  virtual void RemoveGame( lobby::TGameId _gameId );

  //IMMakingLogicCallback
  virtual void MmResultAddRequest( TRequestUId _requestUId, bool _ok );
  virtual void MmResultRemoveRequest( TRequestUId _requestUId, bool _ok );
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok );
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok );

private:
  const Transport::TServiceId   serviceId;
  StrongMT<ILiveMMakingClient>  client;

  string                        map;
  StrongMT<IMMakingLogic>       logic;
  bool                          producePvpStatusInfo;
  timer::Time                   nextPvpStatus;

  NDb::Ptr<NDb::AdvMapDescription> FindMap( const string & _mapId );
  StrongMT<IHeroesTable> LoadHeroes( MMConfig * _cfg );
  StrongMT<IMMakingLogic> StartLogic( const NDb::AdvMapDescription * mapDesc );

  void UpdatePvPStat( timer::Time _now );
};

} //namespace mmaking

#endif //LIVEMMAKINGSVC_H_INCLUDED
