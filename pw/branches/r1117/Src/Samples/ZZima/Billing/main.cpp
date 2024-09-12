#include <string.h>
#include <System/stdafx.h>
#include <System/CmdLine.h>
#include <Server/ZZima/ZZimaService.h>

const char* GetGenderStr(int gender)
{
  switch (gender)
  {
  case 0: return "undefined";
  case 1: return "male";
  case 2: return "female";
  }
  return "<error>";
}

int main (int argc, char *argv[]) 
{
  NCmdLine::CCmdLine cmd("Sample: ZZima billing");

  nstl::string serviceUrl; 
  nstl::string serviceName;
  nstl::string servicePwd;
  nstl::string userName;
  nstl::string userPassword;
  nstl::string socnetUrl; 
  nstl::string socnetKey; 
  nstl::string socnetPassword; 

  int setAmount = -1;
  int addAmount = 0;
  int removeAmount = 0;
  int showServices = 0;
  int showInfo = 0;
  nstl::string subscribeService;
  nstl::string unsubscribeService;

  cmd.AddOption("--user", &userName, "User name");
  cmd.AddOption("--password", &userPassword, "User password");
  cmd.AddOption("--add", &addAmount, "Add amount");
  cmd.AddOption("--set", &setAmount, "Set amount");
  cmd.AddOption("--remove", &removeAmount, "Remove amount");
  cmd.AddOption("--serviceUrl", &serviceUrl, "Url of billing service");
  cmd.AddOption("--serviceName", &serviceName, "Service name");
  cmd.AddOption("--servicePassword", &servicePwd, "Service password");
  cmd.AddOption("--services", &showServices, "Show subscribed services");
  cmd.AddOption("--subscribe", &subscribeService, "Subscribe to service");
  cmd.AddOption("--unsubscribe", &unsubscribeService, "Unsubscribe to service");
  cmd.AddOption("--info", &showInfo, "Show user info");
  cmd.AddOption("--socnetUrl", &socnetUrl, "Url of social network");
  cmd.AddOption("--socnetKey", &socnetKey, "Key for social network");
  cmd.AddOption("--socnetPassword", &socnetPassword, "Password for social network");

  NCmdLine::CCmdLine::EProcessResult result = cmd.Process( argc, argv );
  if ( result == NCmdLine::CCmdLine::PROC_RESULT_OK )
  {
    ZZima::Invoker invoker(serviceUrl.c_str(), serviceName.c_str());
    ZZima::InvokerOld invokerOld(socnetUrl.c_str(), socnetKey.c_str(), socnetPassword.c_str());
    if (invoker.GetStatus() != ZZima::Invoker::Connected)
    {
      printf("Connection to billing service \"%s\" failed, errors \"%s\"", serviceUrl.c_str(), invoker.GetErrors().c_str());
      return 2;
    }
    ZZima::ErrorCode code;
    ZZima::UserProfile profile;
    code = ZZima::GetUserProfile(invoker, userName.c_str(), profile);
    if (code == ZZima::E_OK)
    {
      printf("Profile access ok for account \"%s\":\n    userId=%d\n    email=%s\n", userName.c_str(), profile.userid, profile.email.c_str());
    } else
    {
      printf("Profile access failed for account \"%s\"\n", userName.c_str());
    }

    if (!userPassword.empty())
    {
      printf("Authorizing on server ...\n");
      int userId = -1;
      code = ZZima::Authorize(invoker, userName.c_str(), userPassword.c_str(), userId);
      if (code == ZZima::E_OK && userId == profile.userid)
      {
        printf("Authorization ok for account (%s.%d)\n", userName.c_str(), userId);
      }
      else
      {
        printf("Authorization fail for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 3;
      }
    }
    if (!subscribeService.empty())
    {
      code = ZZima::SubscribeService(invoker, userName.c_str(), std::string(subscribeService.c_str()));
      if (code == ZZima::E_OK)
      {
        printf("Subscription to service \"%s\" successfull\n", subscribeService.c_str());
      } else
      {
        printf("Subscription to service failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 8;
      }
    }
    if (!unsubscribeService.empty())
    {
      code = ZZima::UnsubscribeService(invoker, userName.c_str(), std::string(unsubscribeService.c_str()));
      if (code == ZZima::E_OK)
      {
        printf("Unsubscription to service \"%s\" successfull\n", subscribeService.c_str());
      } else
      {
        printf("Subscription to service failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 9;
      }
    }

    printf("Requesting amount for account \"%s\"\n",  userName.c_str());
    double initAmount;
    code = ZZima::GetBalance(invoker, userName.c_str(), initAmount);
    if (code == ZZima::E_OK)
    {
      printf("Initial amount for account \"%s\": %f\n", userName.c_str(), initAmount);
    } else
    {
      printf("Balance attempt failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
      return 4;
    }

    bool operationPerformed = false;
    if (addAmount > 0)
    {
      code = ZZima::ReplenishAccount(invoker, userName.c_str(), addAmount, "because");
      if (code == ZZima::E_OK)
      {
        printf("Replenish to account successfull\n");
        operationPerformed = true;
      } else
      {
        printf("Replenish failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 5;
      }
    }

    if (removeAmount > 0)
    {
      code = ZZima::WriteoffAccount(invoker, userName.c_str(), removeAmount, "because");
      if (code == ZZima::E_OK)
      {
        printf("Writeoff to account successfull\n");
        operationPerformed = true;
      } 
      else
      {
        printf("Writeoff failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 6;
      }
    }
    if (setAmount >= 0)
    {
      double delta = setAmount-initAmount;
      if (delta > 0)
      {
        code = ZZima::ReplenishAccount(invoker, userName.c_str(), delta, "because");
      } 
      else if (delta < 0)
      {
        code = ZZima::WriteoffAccount(invoker, userName.c_str(), -delta, "because");
      }
      if (code == ZZima::E_OK)
      {
        printf("Set to account successfull\n");
        operationPerformed = true;
      } 
      else
      {
        printf("Set operation failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 6;
      }
    }

    if (operationPerformed)
    {
      double newAmount;
      code = ZZima::GetBalance(invoker, userName.c_str(), newAmount);
      if (code == ZZima::E_OK)
      {
        printf("New amount for account \"%s\": %f\n", userName.c_str(), newAmount);
      } else
      {
        printf("Balance attemp failed for user \"%s\" error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        return 7;
      }
    }
    if (showServices)
    {
      std::vector<ZZima::ServiceShortInfo> services;
      code = ZZima::GetServicesList(invoker, userName.c_str(), services);
      if (code == ZZima::E_OK)
      {
        printf("Subscribed services:\n");
        for (uint i=0;i<services.size();++i)
        {
          if (services[i].subscribed)
          {
            printf("    %s\n", services[i].serviceName.c_str());
          }
        }
      } else
      {
        return 10;
      }
    }
    if (showInfo)
    {
      ZZima::UserInfo info;
      char buffer[64];
      _itoa(profile.userid, buffer, 10);
      code = ZZima::GetUserInfo(invokerOld, buffer, info);
      if (code == ZZima::E_OK)
      {
        printf("User \"%s\" information:\n", userName.c_str());
        printf("    gender: %s\n", GetGenderStr(info.sex));
      } else
      {
        printf("Information request failed for user \"%s\", error \"%s\"\n", userName.c_str(), ZZima::GetErrorText(code));
        printf("    request: %s\n", invokerOld.GetRequest());
        printf("    result: %s\n", invokerOld.GetResult());
        return 11;
      }
    }
  }
  else
  {
    cmd.PrintUsage("Usage:");
  }
  return 0;
}


//--serviceUrl http://SITE:8082/API/PL/ZZServiceWeb.asmx?WSDL --user redjack  --serviceName pwtst --remove 1000
