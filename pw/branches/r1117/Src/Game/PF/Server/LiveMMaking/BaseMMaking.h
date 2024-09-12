#ifndef BASEMMAKING_H_INCLUDED
#define BASEMMAKING_H_INCLUDED

#include "IMMakingLogic.h"
#include "MMakingRequest.h"
#include "LiveMMakingConfigVars.h"
#include <list>
#include <map>


namespace NDb
{
  struct MapMMakingSettings;
  struct MapList;
}


namespace mmaking
{

namespace ELogLevel { enum Enum; }


class BaseMMaking : public IMMakingLogic, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( BaseMMaking, IMMakingLogic, BaseObjectMT )

public:
  typedef std::map<TRequestUId, StrongMT<MmRequest> >  TRequestMap;

  static NDb::Ptr<NDb::MapList> GetMapListResource();

  BaseMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix );

  int TeamSize() const { return m_teamSize; }

  //IMMakingLogic
  virtual void Poll();
  virtual void OnConfigReload( MMConfig * _cfg, IHeroesTable * _heroes );
  virtual void AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData, IMMakingLogicCallback * _callback );
  virtual void RemoveGame( lobby::TGameId _gameId, IMMakingLogicCallback * _callback );
  virtual bool PopReconnectSlot( SReconnectSlot & _slot ) { return false; }
  virtual string GetDebugStatus() { return string(); }
  virtual void GetLineStatistics( unsigned & team1, unsigned & team2 ) { team1=team2=0; }

  virtual const StrongMT<Loger> & GetLoger() const { return m_loger; }

protected:
  typedef std::list<SGame>  TGames;

  NDb::Ptr<NDb::MapMMakingSettings> m_settings;
  StrongMT<MMConfig>    m_config;
  StrongMT<IHeroesTable> m_heroes;
  StrongMT<IRankTable>  m_ranks;
  const int             m_teamSize;
  NDb::EMapType         m_mapType;
  const string          m_mapId;
  const GeoTable        m_locales;
  const GeoTable        m_locations;
  int m_enableRandomQueueIterator;

  StrongMT<Loger>       m_loger;

  threading::Mutex      m_configReloadMutex;
  StrongMT<MMConfig>    m_reloadedConfig;
  StrongMT<IHeroesTable> m_reloadedHeroes;

  bool CheckRequestMmIds( const TRequestMap & _requests, MmRequest * _req ) const;
  void FormatGame( string & _buffer, const SGame & _game );
  void LogGame( ELogLevel::Enum _lvl, const SGame & _game, const char * _prefix );
  void PullReloadedConfig();
};

} //namespace mmaking

#endif //BASEMMAKING_H_INCLUDED
