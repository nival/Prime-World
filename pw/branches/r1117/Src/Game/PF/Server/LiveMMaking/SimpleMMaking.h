#ifndef SIMPLEMMAKING_H_INCLUDED
#define SIMPLEMMAKING_H_INCLUDED

#include "BaseMMaking.h"


namespace mmaking
{

class SimpleMMaking : public BaseMMaking
{
  NI_DECLARE_REFCOUNT_CLASS_1( SimpleMMaking, BaseMMaking );

public:
  SimpleMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix );

  //IMMakingLogic
  virtual void SetTime( timer::Time _simulationTime ) { m_now = _simulationTime; }
  virtual void Poll();
  virtual void AddGroupRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime, IMMakingLogicCallback * _callback );
  virtual void RemoveRequest( TRequestUId _requestUId, IMMakingLogicCallback * _callback );
  virtual void GetLineStatistics( unsigned & team1, unsigned & team2 );

  void EnableAlgoStartRotation( bool _enable ) { m_enableAlgoStartRotation = _enable; }

protected:
  TRequestMap           m_requests;
  int                   m_requestsCounter;

  timer::Time           m_now;
  bool                  m_enableAlgoStartRotation;

  TRequestMap::iterator GetRotatedRequestsBegin( int rotation ) {
    TRequestMap::iterator it = m_requests.begin();
    if ( ( rotation >= 0 ) && ( rotation < (int)m_requests.size() ) )
      for ( int i = 0; i < rotation; ++i )
        ++it;
    return it;
  }
};



class SingleplayerMMaking : public SimpleMMaking
{
  NI_DECLARE_REFCOUNT_CLASS_1( SingleplayerMMaking, SimpleMMaking );

public:
  SingleplayerMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
  SimpleMMaking( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
  m_mapType( _mapType ),
  m_manoeuvres( _cfg->trainingManoeuvres )
  {
  }

  virtual bool PopGame( SGame & result );

private:
  const NDb::EMapType m_mapType;
  bool m_manoeuvres;
};



class MMakingDraftGame;

class CompStompMMaking : public SimpleMMaking
{
  NI_DECLARE_REFCOUNT_CLASS_1( CompStompMMaking, SimpleMMaking );

public:
  CompStompMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, timer::Time waitThreshold, const char * _logSuffix ) :
  SimpleMMaking( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
  m_waitThreshold( waitThreshold )
  {
  }

  virtual bool PopGame( SGame & result );

private:
  const timer::Time       m_waitThreshold;

  bool RetrieveGameForTeam( SGame & result, lobby::ETeam::Enum searchTeam );
  bool RetrieveGameForTeam( SGame & result, lobby::ETeam::Enum searchTeam, int algoStartRotation );
  void FinishGame( SGame & result, MMakingDraftGame & draft, const std::vector<TRequestMap::iterator> & toRemove );
};




class StubMMaking : public SimpleMMaking
{
  NI_DECLARE_REFCOUNT_CLASS_1( StubMMaking, SimpleMMaking );

public:
  StubMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
  SimpleMMaking( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
  m_mapType( _mapType ),
  m_manoeuvresWaitThreshold( _cfg->testManoeuvresWaitThreshold )
  {
  }

  virtual bool PopGame( SGame & result );

private:
  const NDb::EMapType m_mapType;
  float m_manoeuvresWaitThreshold;

  bool PopGameImpl( SGame & result, lobby::ETeam::Enum currentFaction );
  bool PopGameImpl( SGame & result, lobby::ETeam::Enum currentFaction, int algoStartRotation );
};

} //namespace mmaking

#endif //SIMPLEMMAKING_H_INCLUDED
