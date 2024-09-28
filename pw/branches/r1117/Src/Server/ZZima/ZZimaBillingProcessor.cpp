#include "stdafx.h"

#include "BillingProcessor.h"
#include "ZZimaBillingProcessor.h"
#include <Server/ZZima/ZZimaService.h>

namespace Billing
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ZZimaBillingProcessor::ZZimaBillingProcessor(Login::IUserDatabase *database, const nstl::string& serviceUrl, const nstl::string& serviceName, const nstl::string& servicePassword): 
  IBillingProcessor(database)
  {
    invoker = new ZZima::Invoker(serviceUrl.c_str(), serviceName.c_str(), servicePassword.c_str(), false);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ZZimaBillingProcessor::ErrorCode ZZimaBillingProcessor::GetUserMoney(int userAccountId, int &nUserGold) 
  {
    if (invoker->IsOk())
    {
      //  TODO: если нужно - переделать на использование UserManagerAgent
      return NO_SUCH_USER;

      //const Login::LoginResult* info  = database?database->GetUserLoginInfo(userAccountId):0;
      //if (info)
      //{
      //  double amount;
      //  ZZima::ErrorCode code = ZZima::GetBalance(*invoker, NStr::ToMBCS(info->username).c_str(), amount);
      //  if (code == ZZima::E_OK)
      //  {
      //    nUserGold = int(amount);
      //    return ERROR_OK;
      //  } else
      //  {
      //    return INVALID_RECIPIENT;
      //  }
      //} else
      //{
      //  return NO_SUCH_USER;
      //}
    }
    return ERROR_UNSPECIFIED;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ZZimaBillingProcessor::ErrorCode ZZimaBillingProcessor::AddUserMoney(int userAccountId, int nServiceID, int nAmount)
  {
    if (invoker->IsOk())
    {
      //  TODO: если нужно - переделать на использование UserManagerAgent
      return NO_SUCH_USER;

      //const Login::LoginResult* info = database?database->GetUserLoginInfo(userAccountId):0;
      //if (info)
      //{
      //  char reason[64];
      //  sprintf_s(reason, 64, "service %d", nServiceID);
      //  ZZima::ErrorCode code = ZZima::ReplenishAccount(*invoker, NStr::ToMBCS(info->username).c_str(), nAmount, reason);
      //  if (code == ZZima::E_OK)
      //  {
      //    return ERROR_OK;
      //  } else
      //  {
      //    return INVALID_RECIPIENT;
      //  }
      //} else
      //{
      //  return NO_SUCH_USER;
      //}
    }
    return ERROR_UNSPECIFIED;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ZZimaBillingProcessor::ErrorCode ZZimaBillingProcessor::RemoveUserMoney  (int userAccountId, int nServiceID, int nAmount)
  {
    if (invoker->IsOk())
    {
      //  TODO: если нужно - переделать на использование UserManagerAgent
      return NO_SUCH_USER;

      //const Login::LoginResult* info = database?database->GetUserLoginInfo(userAccountId):0;
      //if (info)
      //{
      //  char reason[64];
      //  sprintf_s(reason, 64, "service %d", nServiceID);
      //  ZZima::ErrorCode code = ZZima::WriteoffAccount(*invoker, NStr::ToMBCS(info->username).c_str(), nAmount, reason);
      //  if (code == ZZima::E_OK)
      //  {
      //    return ERROR_OK;
      //  } else
      //  {
      //    return INVALID_RECIPIENT;
      //  }
      //} else
      //{
      //  return NO_SUCH_USER;
      //}
    }
    return ERROR_UNSPECIFIED;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ZZimaBillingProcessor::ErrorCode ZZimaBillingProcessor::TransferUserMoney(int userAccountId, int recipientAccountId, unsigned int nAmountToTransfer, unsigned int nServiceID)
  {
    return INVALID_RECIPIENT;
  }
}

BASIC_REGISTER_CLASS( Billing::ZZimaBillingProcessor )