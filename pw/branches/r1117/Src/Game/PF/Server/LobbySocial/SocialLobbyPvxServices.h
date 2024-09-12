#ifndef SOCIALLOBBYPVXSERVICES_H_INCLUDED
#define SOCIALLOBBYPVXSERVICES_H_INCLUDED

#include <map>
#include <list>
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "SocialLobbyCtrl.h"


namespace socialLobby
{

class Config;
class IPvxSvc;
struct SConfig;
class PinnedLocations;


class PvxServiceSlot : public IPvxSvcWrapper, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( PvxServiceSlot, IPvxSvcWrapper, BaseObjectST );

public:
  PvxServiceSlot( const Transport::TServiceId & _svcid, IPvxSvc * _svc ) :
  svcId( _svcid ),
  remote( _svc ),
  load( 0 ),
  connectionLostTimeout( -1 )
  {}

  virtual IPvxSvc *                       Remote() const { return remote; }
  virtual const Transport::TServiceId &   SvcId() const { return svcId; }

  void UpdateRemotePtr( IPvxSvc * _ptr ) { remote = _ptr; }

  unsigned Load() const { return load; }
  void UpdateLoad( unsigned _load ) { load = _load; }
  void IncrementLoad( unsigned _add ) { load += _add; }

  bool Poll( timer::Time _now, const SConfig * _cfg, const string & _dbgClusterId );

private:
  const Transport::TServiceId   svcId;
  StrongMT<IPvxSvc>             remote;
  unsigned                      load;
  timer::Time                   connectionLostTimeout;
};



class PvxSubcluster : public BaseObjectST
{
NI_DECLARE_REFCOUNT_CLASS_1( PvxSubcluster, BaseObjectST );

public:
  PvxSubcluster( const string & _clusterId, const PvxClusterSettings & _settings, const Transport::TServiceId & _settingsSrcSvcId );

  const string & Id() const { return id; }

  void UpdateSettings( const PvxClusterSettings & _settings, const Transport::TServiceId & _srcSvcId );

  unsigned Capacity() const { return settings.capacity; }
  EPvxLobbyInstanceMode::Enum SpecialMode() const { return settings.specialMode; }
  bool IsInSpecialList( TUId _uid ) const { return specialSet.find( _uid ) != specialSet.end(); }

  PvxServiceSlot * FindService( const Transport::TServiceId & _svcId ) const;
  void AddService( IPvxSvc * _pvx, const Transport::TServiceId & _svcId );
  PvxServiceSlot * Allocate( unsigned _loadIncrement );

  unsigned CountTotalLoad() const;

  bool Poll( timer::Time _now, const SConfig * _cfg );

private:
  typedef list<Strong<PvxServiceSlot>> TServices;
  typedef set<TUId> TSpecialList;

  const string          id;
  TServices             services;
  PvxClusterSettings    settings;
  TSpecialList          specialSet;
  Transport::TServiceId settingsSrcSvcId;
};



class PvxServices : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( PvxServices, BaseObjectST );

public:
  PvxServices( Config * _cfg );

  void ReloadConfig();

  void Add( IPvxSvc * _pvx, const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings & _settings );
  void UpdateSettings( const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings & _settings );
  void LoadNotify( const string & _clusterId, const Transport::TServiceId & _svcId, unsigned _load );
  Strong<IPvxSvcWrapper> Allocate( const string & _clusterId, unsigned _loadIncrement );
  string DetermineClusterForGame( const mmaking::SGame & _game );
  void Poll( timer::Time _now );

  PvxSubcluster * FindSubcluster( const string & _clusterId ) const; //It's public just for unit-test

private:
  typedef std::list<Strong<PvxSubcluster>>  TClusters;

  Strong<Config>            config;
  StrongMT<PinnedLocations> pinnedLocations;
  TClusters                 clusters;

  struct ClusterPingQuality;
  typedef std::map<string, ClusterPingQuality>  TClusterCounter;

  PvxSubcluster * FindOrAllocSubcluster( const string & _clusterId, const PvxClusterSettings & _settings, const Transport::TServiceId & _settingsSrcSvcId );
  PvxServiceSlot * Find( const string & _clusterId, const Transport::TServiceId & _svcId ) const;
  PvxSubcluster * GetLeastLoaded();
  void CountMmRequestMemberPings( TClusterCounter & counter, const mmaking::SRequestMember & memb );
  string CheckForPinnedCluster( const mmaking::SGame & _game );
  string CheckForForcedDevCluster( const mmaking::SGame & _game );
};

} //namespace socialLobby

#endif //SOCIALLOBBYPVXSERVICES_H_INCLUDED
