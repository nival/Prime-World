#include "stdafx.h"
#include "BillingProcessor.h"
#include "SimpleBillingProcessor.h"

namespace Billing
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SimpleBillingProcessor::SimpleBillingProcessor(): IBillingProcessor(NULL) 
  {}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SimpleBillingProcessor::ErrorCode SimpleBillingProcessor::GetUserMoney(int userAccountId, int &nUserGold) 
  {
    InitUser(userAccountId);
    nUserGold = money.find(userAccountId)->second;
    return ERROR_OK;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SimpleBillingProcessor::ErrorCode SimpleBillingProcessor::AddUserMoney     (int userAccountId, int nServiceID, int nAmount)
  {
    InitUser(userAccountId);
    if(nAmount <= 0)
    {
      return INVALID_PARAMETERS;
    }
    money.find(userAccountId)->second += nAmount;
    return ERROR_OK;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SimpleBillingProcessor::ErrorCode SimpleBillingProcessor::RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount)
  {
    InitUser(userAccountId);
    if(nAmount <= 0)
    {
      return INVALID_PARAMETERS;
    }
    if((money.find(userAccountId)->second - nAmount) < 0)
    {
      return NOT_ENOUGH_MONEY;
    }
    money.find(userAccountId)->second -= nAmount;
    return ERROR_OK;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SimpleBillingProcessor::ErrorCode SimpleBillingProcessor::TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID)
  {
    InitUser(userAccountId);
    InitUser(recipientAccountId);
    if(nAmountToTransfer <= 0)
    {
      return INVALID_PARAMETERS;
    }
    if((money.find(userAccountId)->second - nAmountToTransfer) < 0)
    {
      return NOT_ENOUGH_MONEY;
    }
    money.find(userAccountId)->second      -= nAmountToTransfer;
    money.find(recipientAccountId)->second += nAmountToTransfer;
    return ERROR_OK;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SimpleBillingProcessor::InitUser(int userAccountId)
  {
    if(money.end() == money.find(userAccountId))
    {
      money.insert(MoneyPair(userAccountId, nInitialGold));
    }
  }
}


BASIC_REGISTER_CLASS( Billing::SimpleBillingProcessor )
