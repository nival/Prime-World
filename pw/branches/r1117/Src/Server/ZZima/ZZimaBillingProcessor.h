#pragma once
#include "BillingProcessor.h"

namespace ZZima
{
struct Invoker;
}

namespace Billing
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ZZimaBillingProcessor: public Billing::IBillingProcessor, public CObjectBase
  {
  private:
    OBJECT_BASIC_METHODS(ZZimaBillingProcessor);
    ZZimaBillingProcessor() {}
  public:
    virtual ErrorCode GetUserMoney     (int userAccountId, int &nUserGold);                                                 
    virtual ErrorCode AddUserMoney     (int userAccountId, int nServiceID, int nAmount);  
    virtual ErrorCode RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount);  
    virtual ErrorCode TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID);         
    ZZimaBillingProcessor(Login::IUserDatabase *database, const nstl::string& serviceUrl, const nstl::string& serviceName, const nstl::string& servicePassword);
  protected:
    ZZima::Invoker* invoker;
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
