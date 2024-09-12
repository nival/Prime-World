#ifndef PRODMMLOGICBASE_H_INCLUDED
#define PRODMMLOGICBASE_H_INCLUDED

#include "BaseMMaking.h"
#include "MMakingDraftGame.h"
#include "System/JobThread.h"
#include <list>
#include <map>


namespace NDb
{
  struct HeroesDB;
}

namespace mmaking
{

_interface IDiscreteMMLogicConstraint;
class GameRequest;
class UniStatLoger;
struct GeolocationConstraints;


class IDbgRequestsEnumerator
{
public:
  virtual void EnumRequest( MmRequest * req ) = 0;
};

_interface IParallelThreadHolder : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IParallelThreadHolder, IBaseInterfaceMT );

  virtual void LaunchParallelThread() = 0;
  virtual void StopParallelThread() = 0;
};

class ProdLogicBase : public BaseMMaking, public IParallelThreadHolder
{
  NI_DECLARE_REFCOUNT_CLASS_2( ProdLogicBase, BaseMMaking, IParallelThreadHolder );

public:
  static StrongMT<mmaking::IHeroesTable> FillHeroesTable( MMConfig * _cfg, const NDb::HeroesDB * dbHeroes );

  ProdLogicBase( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix );
  ~ProdLogicBase();

  void LaunchParallelThread();
  void StopParallelThread();

  //IMMakingLogic
  virtual void SetTime( timer::Time _simulationTime );
  virtual void AddGroupRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime, IMMakingLogicCallback * _callback );
  virtual void RemoveRequest( TRequestUId _requestUId, IMMakingLogicCallback * _callback );
  virtual bool PopGame( SGame & _result );
  virtual void AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData, IMMakingLogicCallback * _callback );
  virtual void RemoveGame( lobby::TGameId _gameId, IMMakingLogicCallback * _callback );
  virtual bool PopReconnectSlot( SReconnectSlot & _slot );
  virtual string GetDebugStatus();
  virtual void GetLineStatistics( unsigned & team1, unsigned & team2 );
  //¬нимание! ¬виду асинхронности процесса даже _после_ вызова RemoveRequest(N) игрок N может быть возвращен из функции PopGame() !

  void TestPoll() { bool isRunning = true; ParallelPoll( isRunning ); }

  void DebugEnumerateRequests( IDbgRequestsEnumerator * enumerator );

protected:
  friend class ProdLogicThreadJob;

  template<typename TREQID, typename TREQ>
  struct SIncomingRequest {
    TREQID reqId;
    StrongMT<TREQ> req; //If this is null, then this is command to remove some request
    WeakMT<IMMakingLogicCallback> cb;
    SIncomingRequest() {}
    SIncomingRequest( TREQID _id, TREQ * _req, IMMakingLogicCallback * _cb ) : reqId( _id ), req( _req ), cb( _cb ) {}
  };

  typedef std::list<SIncomingRequest<TRequestUId, MmRequest>>  TIncomingRequests;
  typedef std::list<SIncomingRequest<lobby::TGameId, GameRequest>>  TIncomingGameRequests;

  typedef std::map<lobby::TGameId, StrongMT<GameRequest>> TGameRequestMap;

  typedef std::list<SReconnectSlot>  TGameReqResults;

  typedef std::map<int,int>  TClientRevisions;

  typedef std::map<THeroShortId, int>  THeroCounter;
  
  StrongMT<threading::JobThread>  m_thread;

  //Incoming section
  threading::Mutex      m_incomingMutex;
  TIncomingRequests     m_incoming;
  TIncomingGameRequests m_icomingGameRequests;
  timer::Time           m_externalTime;
  unsigned              m_requestAdded;

  //Current requests in process, only working thread access!
  timer::Time           m_now;
  TRequestMap           m_requests;
  TGameRequestMap       m_gameRequests;
  unsigned              m_requestServed;

  threading::Mutex      m_outcomeMutex;
  TGames                m_outcome;
  TGameReqResults       m_gameRequestsResults;

  unsigned              m_lineLength1, m_lineLength2; //Used to report MM CCU; Protected by 'm_outcomeMutex'

  bool                  m_dataChanged;
  timer::Time           m_lastSmartDump;
  timer::Time           m_lastFullDump;
  unsigned              m_lastRequestsAdded, m_lastRequestsServed;

  //Used to test and debug info
  threading::Mutex      m_debugStatusMutex;
  string                m_debugStatus;

  StrongMT<Loger>       m_queueCsvDumper;
  StrongMT<Loger>       m_jsonLogger;

  StrongMT<UniStatLoger> m_uniStats;

  //These are called from working thread
  void PickUpNewRequests();
  virtual void PickUpNewRequest( MmRequest * newReq, IMMakingLogicCallback * callback );
  void RemoveRemovedRequest( TRequestUId requestId, IMMakingLogicCallback * callback );
  void PickUpNewGameRequests();
  void PickUpNewGameRequest( GameRequest * newReq, IMMakingLogicCallback * callback );
  void RemoveRemovedGameRequest( lobby::TGameId gameId, IMMakingLogicCallback * callback );

  int GatherRevisionsInfo( TClientRevisions & revisions );
  void GatherCcuInfo();
  void ClearInUse();

  bool CheckAndSetupLocalePair( GeolocationConstraints & geo, TGeoIndex locale1, TGeoIndex locale2 );
  bool CheckHeroesLimit( const THeroCounter & heroCounter, const MmRequest * req, EBasket::Enum basket ) const;
  static void CountHeroes( THeroCounter & heroCounter, const MmRequest * req, const IHeroesTable* heroes );

  void PushResultingGame( const MMakingDraftGame & draft, EDebugGameType::Enum debugGameType );
  virtual bool DeleteRequest( TRequestUId requestId );
  void ParallelPoll( volatile bool & isRunning );

  //overridable
  virtual void OnRequestAdded( MmRequest * req ) {}
  virtual void OnRequestDeletion( MmRequest * req ) {}
  virtual void RunIteration( int mostPopularRevision, volatile bool & isRunning ) = 0;
  virtual void OnSmartDump() {}

  void WriteFullDumpHat();
  void WriteFullDumpRequest( MmRequest * req );
  void FullDump( unsigned debugGameId = 0 );
  void SmartDump( unsigned requestAdded, const TClientRevisions & clientRevisions );

  void FormatGameJson( string & _buffer, const SGame & _game );
  void LogGameJson( ELogLevel::Enum _lvl, const SGame & _game );
  void FormatTimeToJson( string & buffer );
};

} //namespace mmaking

#endif //PRODMMLOGICBASE_H_INCLUDED
