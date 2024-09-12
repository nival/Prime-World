#pragma once
#include <Network/LoginData.h>
namespace Billing
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct IBillingProcessor: public IObjectBase
    {
    enum ErrorCode
    {
      ERROR_OK,
      NO_SUCH_USER,
      NOT_ENOUGH_MONEY,
      INVALID_PARAMETERS,
      ERROR_UNSPECIFIED,
      INVALID_RECIPIENT
    };
    virtual ErrorCode GetUserMoney     (int userAccountId, int &nUserGold) = 0;                                                 //amount of gold user have can be negative
    virtual ErrorCode AddUserMoney     (int userAccountId, int nServiceID, int nAmount) = 0;  //return error code
    virtual ErrorCode RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount) = 0;  //return error code
    virtual ErrorCode TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID) = 0;         //return error code
    
    IBillingProcessor(Login::IUserDatabase* _database): database(_database) {}
    IBillingProcessor(): database(0) {}
    virtual ~IBillingProcessor() {}
  protected:
    Login::IUserDatabase*            database;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
