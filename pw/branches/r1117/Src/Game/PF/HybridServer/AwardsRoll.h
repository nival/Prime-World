#pragma once

#include "Server/Roll/RRollBalancer.auto.h"
#include "RPC/IfaceRequester.h"
#include "Server/Statistic/StatisticsCommonTypes.h"


namespace Peered
{

typedef vector<roll::SUserAward> TUserAwards;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IAwardsRequester : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IAwardsRequester, IBaseInterfaceMT);

public:

  virtual void FillPreGameData(const nstl::vector<ClientInfo> &_clientsInfo, const SAuxData & _auxData) = 0;
  virtual void FillPostGameData(lobby::EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _gameFinishInfo, const nstl::vector<SClientStatistics> & _clientsStatistics, uint _totalSeconds) = 0;
  virtual void Step() = 0;
  virtual bool IsAwardsReceived() const = 0;
  virtual void GetResults(TUserAwards * _awards) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AwardsRequester : public IAwardsRequester, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( AwardsRequester, IAwardsRequester, BaseObjectMT );

public:

  AwardsRequester(
    rpc::IfaceRequester<roll::RIBalancer> * _rollBalancer,
    NLogg::CChannelLogger * _logStream,
    TSessionId _serverId,
    int _retryTimer);

  virtual void FillPreGameData(const nstl::vector<ClientInfo> & _clientsInfo, const SAuxData & _auxData);
  virtual void FillPostGameData(lobby::EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _gameFinishInfo, const nstl::vector<SClientStatistics> & _clientsStatistics, uint _totalSeconds);
  virtual void Step();
  virtual bool IsAwardsReceived() const { return isAwardsReceived; }
  virtual void GetResults(TUserAwards * _awards) { *_awards = awards; }

private:

  struct RollClientCb;

  void OnInstanceAllocation( roll::RIInstance * inst );
  void OnRollResults( const TUserAwards & _awards );
  void OnRollFailed();
  void FillExtraData(StatisticService::SessionPlayerExtra& extra, const vector<roll::SPreGamePerUserData>& _preData, roll::UserId _clientId );

  WeakMT<rpc::IfaceRequester<roll::RIBalancer> > rollBalancer;
  TUserAwards awards;
  bool isInterfaceRequested;
  bool isAwardsReceived;
  StrongMT<roll::RIInstance>  rollInstance;
  StrongMT<RollClientCb>  clientCb;
  threading::Mutex awardsLock;
  NLogg::CChannelLogger * logStream;
  TSessionId serverId;
  roll::SPreGameData preGameData;
  roll::SPostGameData postGameData;
  int retryTimer;
  int currentTimer;
};

} // namespace Peered

