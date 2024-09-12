#pragma once

#include "MmToolStat.h"
#include "MmToolLog.h"
#include "Server/LiveMMaking/RatingSortMmLogic.h"
#include "Server/LiveMMaking/RankMatchmaking.h"
#include "MmVisualization.h"


namespace mm_test
{

class MmDummyCallback : public mmaking::IMMakingLogicCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MmDummyCallback, IMMakingLogicCallback, BaseObjectMT );

public:
  MmDummyCallback() {}
  virtual void MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
  virtual void MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
};



class LogPlaybackCallback : public BasicLogParser
{
  NI_DECLARE_REFCOUNT_CLASS_1( LogPlaybackCallback, BasicLogParser );

public:
  LogPlaybackCallback( MmData * _mmData, const StatisticsSettings & statSett, const VisualizationSettings & visSett );

  virtual void OnAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait );
  virtual void OnRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId );
  virtual void OnGame( const Timestamp & ts, const mmaking::SGame & game );

  void Finish();
  void Output();

private:
  struct ReqItem : public BaseObjectST {
    NI_DECLARE_REFCOUNT_CLASS_1( ReqItem, BaseObjectST );

    ReqItem( mmaking::TRequestUId _reqid, const vector<mmaking::TUserId> & _mmids, timer::Time _t0 ) :
    reqid( _reqid ), t0( _t0 ), mmids( _mmids )
    {}

    mmaking::TRequestUId      reqid;
    vector<mmaking::TUserId>  mmids;
    timer::Time               t0;
  };

  typedef std::map<mmaking::TRequestUId, Strong<ReqItem>>  TRequests;
  typedef std::map<mmaking::TUserId, Strong<ReqItem>>  TRequestsByMmId;
  typedef std::map<mmaking::TRequestUId, mmaking::TRequestUId>  TRequestAliases;

  Strong<MmData>                    mmData;
  Strong<Statistics>                    stat;
  Strong<Visualization>                 visualizer;
  StrongMT<mmaking::ProdLogicBase>      logic;
  StrongMT<MmDummyCallback>             mmCallback;

  TRequests                             reqById;
  TRequestsByMmId                       reqByMmId;
  TRequestAliases                       reqAliases;

  timer::Time                           visualizerNextStep;

  void Remove( ReqItem * item );
  void Remove( TRequests::iterator it );

  virtual void PlaybackPoll();

  void PollLogic();
  void PollRequests();
  void PollMainVisualization();
};

} //namespace mm_test
