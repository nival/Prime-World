#include "stdafx.h"
#include <Server/ZZima/BillingProcessor.h>
#include "LobbyAccounting.h"

namespace Lobby
{

int LobbyAccounting::BlockMoney( int userId, int serviceId )  // пытается заблокировать количество денег необходимое для покупки указанного сервиса, возвращает идентификатор блокировки
{
  if ( !IsValid( processor ) )
    return -1;

  ServiceMap::iterator price = servicePrices.find(serviceId);
  if (price != servicePrices.end())
  {
    Billing::IBillingProcessor::ErrorCode error = processor->RemoveUserMoney(userId, serviceId, price->second);
    if (error == Billing::IBillingProcessor::ERROR_OK)
    {
      nstl::pair<int, int> key(userId, uniqueId);
      uniqueId ++;
      blocks.insert(key)->second = price->second;
      return key.second;
    }
  }
  return -1;
}



void LobbyAccounting::UnblockMoney( int userId, int blockId ) // разблокирует указанную блокировку
{
  if ( !IsValid( processor ) )
    return;

  nstl::pair<int, int> key(userId, blockId);
  BlockMap::iterator block = blocks.find(key);
  if (block != blocks.end())
  {
    Billing::IBillingProcessor::ErrorCode error = processor->AddUserMoney(userId, 0, block->second);
    if (error == Billing::IBillingProcessor::ERROR_OK)
    {
      blocks.erase(block);
    } 
  }
}



int LobbyAccounting::GetServicePrice( int serviceId ) // возвращает цену указанного сервиса
{
  ServiceMap::iterator it = servicePrices.find(serviceId);
  if (it != servicePrices.end())
  {
    return it->second;
  }
  return 0;
}



bool LobbyAccounting::BuyBlockedService( int userId, int blockId, int serviceId )  // пытается приобрести указанный сервис из заблокированной суммы, возвращает true/false в случае успеха/неуспеха операции
{
  if ( !IsValid( processor ) )
    return false;

  ServiceMap::iterator price = servicePrices.find(serviceId);
  if (price != servicePrices.end())
  {
    nstl::pair<int, int> key(userId, blockId);
    BlockMap::iterator block = blocks.find(key);
    if (block != blocks.end())
    {
      if (price->second > block->second)
      {
        return false;
      }
      block->second -= price->second;
      if (block->second > 0)
      {
        Billing::IBillingProcessor::ErrorCode error = processor->AddUserMoney(userId, serviceId, block->second);
        if (error == Billing::IBillingProcessor::ERROR_OK)
        {
          blocks.erase(block);
          return true;
        } 
      } else
      {
        blocks.erase(block);
        return true;
      }
    }
  }
  return false;
}



BuyResult LobbyAccounting::BuyService( int userId, int serviceId )  // пытается приобрести указанный сервис, возвращает true/false в случае успеха/неуспеха операции
{
  BuyResult result;
  result.isSuccessful = false;
  result.currentAmount = 0;
  if (processor)
  {
    ServiceMap::iterator it = servicePrices.find(serviceId);
    if (it != servicePrices.end())
    { 
      Billing::IBillingProcessor::ErrorCode error = processor->RemoveUserMoney(userId, serviceId, it->second);
      if (error == Billing::IBillingProcessor::ERROR_OK)
      {
        result.isSuccessful = true;
      } 
    }
    result.currentAmount = GetMoney(userId);
  }
  return result;
}



bool LobbyAccounting::RewardUser( int userId, int rewardId )  // пытается наградить юзера наградой serviceId, возвращает true/false в случае успеха/неуспеха операции
{
  if ( !IsValid( processor ) )
    return false;

  RewardsMap::iterator it = rewardSizes.find( rewardId );
  if ( it != rewardSizes.end() )
  { 
    Billing::IBillingProcessor::ErrorCode error = processor->AddUserMoney( userId, it->second.billingId, it->second.size );
    if ( error == Billing::IBillingProcessor::ERROR_OK )
      return true;
  }

  return false;
}



bool LobbyAccounting::GiveMoneyToUser( int userId, int userDstId, int serviceId )  // allows to transfer possession of service serviceId between users
{
  if ( !IsValid( processor ) )
    return false;

  ServiceMap::iterator it = servicePrices.find(serviceId);
  if (it != servicePrices.end())
  { 
    Billing::IBillingProcessor::ErrorCode error = processor->TransferUserMoney(userId, userDstId, it->second, serviceId);
    if (error == Billing::IBillingProcessor::ERROR_OK)
    {
      return true;
    } 
  }
  return false;
}



int LobbyAccounting::GetMoney( int userId ) // возвращает текущее состояние счета
{
  if ( !IsValid( processor ) )
    return 0;

  int amount;
  Billing::IBillingProcessor::ErrorCode error = processor->GetUserMoney(userId, amount);
  if (error == Billing::IBillingProcessor::ERROR_OK)
  {
    return amount;
  } 
  return 0;
}



const nstl::vector<Lobby::ServiceInfo>& LobbyAccounting::GetServices()
{
  return services;
}



void LobbyAccounting::SetPrice(int serviceId, int price)
{
  ServiceMap::iterator it = servicePrices.find(serviceId);
  if (it != servicePrices.end())
  {
    it->second = price;
    for (nstl::vector<ServiceInfo>::iterator it = services.begin(); it!= services.end(); ++it)
    {
      if (it->serviceId == serviceId)
      {
        it->servicePrice = price;
        break;
      }
    }
  }
  else
  {
    servicePrices.insert(serviceId)->second = price;
    ServiceInfo info = {serviceId, price};
    services.push_back(info);
  }
}



void LobbyAccounting::SetupReward( int rewardId, int billingRewardId, int size )
{
  SReward & reward = rewardSizes[rewardId];
  reward.billingId = billingRewardId;
  reward.size = size;
}

} // Lobby

NI_DEFINE_REFCOUNT( Lobby::LobbyAccounting );
