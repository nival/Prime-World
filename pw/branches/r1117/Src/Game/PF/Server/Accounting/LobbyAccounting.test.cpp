//!Component("System/NSTL")
//!Component("Game/PF/Server/Accounting/Billing")

#include "cxxtest/TestSuite.h"
#include <System/stdafx.h>
#include <Server/rpc/RPC.h>

#include <ZZima/BillingProcessor.h>
#include "LobbyAccounting.h"

struct MockBillingProcessor : public Billing::IBillingProcessor, CObjectBase
{
  OBJECT_BASIC_METHODS(MockBillingProcessor);
public:
  typedef nstl::map<int, int> AccountMap;

  virtual ErrorCode GetUserMoney     (int userAccountId, int &nUserGold) 
  {
    nUserGold = 0;
    AccountMap::iterator it = userMoney.find(userAccountId);
    if (it != userMoney.end())
    {
      nUserGold = it->second;
      return ERROR_OK;
    }
    return NO_SUCH_USER;
  }      

  virtual ErrorCode AddUserMoney     (int userAccountId, int nServiceID, int nAmount) 
  {
    AccountMap::iterator it = userMoney.find(userAccountId);
    if (it != userMoney.end())
    {
      it->second += nAmount;
      return ERROR_OK;
    }
    return NO_SUCH_USER;
  }

  virtual ErrorCode RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount) 
  {
    AccountMap::iterator it = userMoney.find(userAccountId);
    if (it != userMoney.end())
    {
      if (it->second-nAmount < 0) 
      {
        return NOT_ENOUGH_MONEY;
      }
      it->second -= nAmount;
      return ERROR_OK;
    }
    return NO_SUCH_USER;
  }

  virtual ErrorCode TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID) 
  {
    return ERROR_OK;
  }
  AccountMap userMoney;
};

struct Test_LobbyAccounting : public CxxTest::TestSuite
{
  CObj<MockBillingProcessor> bp;
  void setUp()
  {
    bp = new MockBillingProcessor;
  }

  void test_NullProcessor()
  {
    int userId = 5;
    bp->userMoney.insert(userId)->second = 40;

    Lobby::LobbyAccounting b(0);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    TS_ASSERT_EQUALS(0, b.GetMoney(userId));
    
    int blockId = b.BlockMoney(userId, 3);
    TS_ASSERT_EQUALS(-1, blockId);
    
    Lobby::BuyResult result = b.BuyService( userId, serviceId );  
    TS_ASSERT_EQUALS(false, result.isSuccessful);
  }
  
  void test_GetMoney()
  {
    int userId = 5;
    bp->userMoney.insert(userId)->second = 40;

    Lobby::LobbyAccounting b(bp);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    TS_ASSERT_EQUALS(40, b.GetMoney(userId));
  }

  void test_BuyService()
  {
    int userId = 5;
    bp->userMoney.insert(userId)->second = 40;

    Lobby::LobbyAccounting b(bp);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    Lobby::BuyResult result = b.BuyService(userId, serviceId);
    TS_ASSERT_EQUALS(true, result.isSuccessful);
    TS_ASSERT_EQUALS(35, result.currentAmount);
    TS_ASSERT_EQUALS(35, b.GetMoney(userId));

    int unexistedService = 123213;
    result = b.BuyService(userId, unexistedService);
    TS_ASSERT_EQUALS(false, result.isSuccessful);
    TS_ASSERT_EQUALS(35, result.currentAmount);
    TS_ASSERT_EQUALS(35, b.GetMoney(userId));
  }

  void test_GetServicePrice()
  {
    Lobby::LobbyAccounting b(bp);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    TS_ASSERT_EQUALS(5, b.GetServicePrice(serviceId));
    TS_ASSERT_EQUALS(0, b.GetServicePrice(6778));
  }

  void test_Block()
  {
    Lobby::LobbyAccounting b(bp);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    int userId = 2;
    bp->userMoney.insert(userId)->second = 10;
    int blockId = b.BlockMoney(userId, serviceId);
    TS_ASSERT(blockId != -1);
    TS_ASSERT_EQUALS(5, b.GetMoney(userId));

    bool result = b.BuyBlockedService(userId, blockId, serviceId);
    TS_ASSERT_EQUALS(true, result);
    TS_ASSERT_EQUALS(5, b.GetMoney(userId));

    // block expired
    result = b.BuyBlockedService(userId, blockId, serviceId);
    TS_ASSERT_EQUALS(false, result);
    TS_ASSERT_EQUALS(5, b.GetMoney(userId));
  }

  void test_BuyPriceLessThanBlocked()
  {
    Lobby::LobbyAccounting b(bp);
    int serviceId0 = 3;
    int serviceId1 = 5;
    b.SetPrice(serviceId0, 3);
    b.SetPrice(serviceId1, 5);

    int userId = 2;
    bp->userMoney.insert(userId)->second = 10;
    int blockId = b.BlockMoney(userId, serviceId1);
    TS_ASSERT(blockId != -1);
    TS_ASSERT_EQUALS(5, b.GetMoney(userId));

    bool result = b.BuyBlockedService(userId, blockId, serviceId0);
    TS_ASSERT_EQUALS(true, result);
    TS_ASSERT_EQUALS(7, b.GetMoney(userId));
  }

  void test_BuyPriceMoreThanBlocked()
  {
    Lobby::LobbyAccounting b(bp);
    int serviceId0 = 3;
    int serviceId1 = 5;
    b.SetPrice(serviceId0, 3);
    b.SetPrice(serviceId1, 5);

    int userId = 2;
    bp->userMoney.insert(userId)->second = 10;
    int blockId = b.BlockMoney(userId, serviceId0);
    TS_ASSERT(blockId != -1);
    TS_ASSERT_EQUALS(7, b.GetMoney(userId));

    bool result = b.BuyBlockedService(userId, blockId, serviceId1);
    TS_ASSERT_EQUALS(false, result);
    TS_ASSERT_EQUALS(7, b.GetMoney(userId));
  }

  void test_GetServices()
  {
    Lobby::LobbyAccounting b(bp);

    b.SetPrice(3, 10);
    {
      nstl::vector<Lobby::ServiceInfo> prices = b.GetServices();
      TS_ASSERT_EQUALS(1, prices.size());
      TS_ASSERT_EQUALS(3, prices[0].serviceId);
      TS_ASSERT_EQUALS(10, prices[0].servicePrice);
    }
    b.SetPrice(4, 20);
    {
      nstl::vector<Lobby::ServiceInfo> prices = b.GetServices();
      TS_ASSERT_EQUALS(2, prices.size());
      TS_ASSERT_EQUALS(3, prices[0].serviceId);
      TS_ASSERT_EQUALS(10, prices[0].servicePrice);
      TS_ASSERT_EQUALS(4, prices[1].serviceId);
      TS_ASSERT_EQUALS(20, prices[1].servicePrice);
    }
    b.SetPrice(3, 20);
    {
      nstl::vector<Lobby::ServiceInfo> prices = b.GetServices();
      TS_ASSERT_EQUALS(2, prices.size());
      TS_ASSERT_EQUALS(3, prices[0].serviceId);
      TS_ASSERT_EQUALS(20, prices[0].servicePrice);
      TS_ASSERT_EQUALS(4, prices[1].serviceId);
      TS_ASSERT_EQUALS(20, prices[1].servicePrice);
    }
  }

  void test_Unblock()
  {
    Lobby::LobbyAccounting b(bp);
    int serviceId = 3;
    b.SetPrice(serviceId, 5);

    int userId = 2;
    bp->userMoney.insert(userId)->second = 10;
    int blockId = b.BlockMoney(userId, serviceId);
    TS_ASSERT(blockId != -1);

    b.UnblockMoney(userId, blockId);
    TS_ASSERT_EQUALS(10, b.GetMoney(userId));

    // block expired
    bool result = b.BuyBlockedService(userId, blockId, serviceId);
    TS_ASSERT_EQUALS(false, result);
    TS_ASSERT_EQUALS(10, b.GetMoney(userId));
  }

  // TODO:
  // - return blocked money on exit
};