#pragma once

#include <RPC/RPC.h>
#include "LobbyAccountingStructs.h"

namespace NDb
{
  struct ImpulsiveBuffsContainer;
}


namespace Billing
{
  _interface IBillingProcessor;
}


namespace Lobby
{

REMOTE class LobbyAccounting : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( LobbyAccounting, BaseObjectMT )

  LobbyAccounting() : uniqueId() {}

public: 
  RPC_ID();
  LobbyAccounting(Billing::IBillingProcessor* _processor) :
  processor( _processor ), uniqueId( 0 )
  {}

  ~LobbyAccounting() 
  {
  }

  REMOTE int  BlockMoney( int userId, int serviceId );  // пытается заблокировать количество денег необходимое для покупки указанного сервиса, возвращает идентификатор блокировки
  REMOTE void UnblockMoney( int userId, int blockId ); // разблокирует указанную блокировку
  REMOTE int  GetServicePrice( int serviceId ); // возвращает цену указанного сервиса
  REMOTE bool BuyBlockedService( int userId, int blockId, int serviceId );  // пытается приобрести указанный сервис из заблокированной суммы, возвращает true/false в случае успеха/неуспеха операции
  REMOTE Lobby::BuyResult BuyService( int userId, int serviceId );  // пытается приобрести указанный сервис, возвращает true/false в случае успеха/неуспеха операции
  REMOTE int  GetMoney( int userId ); // возвращает текущее состояние счета 
  
  REMOTE bool GiveMoneyToUser( int userId, int userDstId, int serviceId); // allows to transfer possession of service serviceId between users
  REMOTE const nstl::vector<Lobby::ServiceInfo>& GetServices();

  bool RewardUser( int userId, int rewardId ); // пытается наградить юзера наградой rewardId, возвращает true/false в случае успеха/неуспеха операции

  void SetPrice( int serviceId, int price );
  void SetupReward( int rewardId, int billingRewardId, int size );

private:
  struct SReward
  {
    int   billingId;
    int   size;
    SReward() : billingId(), size() {}
  };

  typedef nstl::map<int, int> ServiceMap;
  typedef nstl::map<nstl::pair<int, int>, int> BlockMap;
  typedef map<int, SReward> RewardsMap;

  int uniqueId;
  ServiceMap servicePrices;
  BlockMap blocks;
  CPtr<Billing::IBillingProcessor> processor;
  nstl::vector<Lobby::ServiceInfo> services;

  RewardsMap rewardSizes;
};

} // Lobby
