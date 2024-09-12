#pragma once
#include "../System/Thread.h"
#include "system/nhash_map.h"
#include "BillingProcessor.h"

namespace Billing
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SimpleBillingProcessor: public Billing::IBillingProcessor, public CObjectBase
{
private:
  OBJECT_BASIC_METHODS(SimpleBillingProcessor);
public:
  typedef hash_map<int, int>  UserMoney;
  typedef pair<int, int>      MoneyPair;
	virtual ErrorCode GetUserMoney     (int userAccountId, int &nUserGold);                                                 
  virtual ErrorCode AddUserMoney     (int userAccountId, int nServiceID, int nAmount);  
  virtual ErrorCode RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount);  
  virtual ErrorCode TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID);         
  SimpleBillingProcessor();
protected:
  UserMoney money;
private:
  static int const nInitialGold = 1000;
  void InitUser(int userAccountId);
	};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
