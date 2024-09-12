#include "stdafx.h"
#include "ZzimaService.h"
#include "Base64.h"
#include <System/Math/MD4.h>
#include <Vendor/wsdlpull/win32/w3c.h>

namespace ZZima
{

Invoker::Invoker(const std::string& url, const std::string& _serviceName, const char* _servicePassword, bool verbose):
status(NotConnected),
serviceName(_serviceName)
{
  invoker.setVerbose(verbose);   
  if (invoker.setWSDLUri(url, "schemas/"))   
  {  
    status = Connected;
  }
  if (_servicePassword)
  {
    servicePassword = _servicePassword;
  }
}

bool Invoker::SetParam(const std::string& name, const void* value, int size)
{
  std::string src((const char*)value, size);
  std::string dst = base64_encode((const byte*)src.c_str(), src.length());
  return invoker.setValue(name, dst);
}

math::MD4 CalculateCrc(const std::string& serviceName, const std::string& userName, const std::string& servicePassword)
{
  math::MD4 svc = math::GenerateMD5((const byte*)servicePassword.c_str(), servicePassword.length());
  math::MD5Generator digest;
  digest.Start();
  digest.Update((const byte*)serviceName.c_str(), serviceName.length());
  digest.Update((const byte*)userName.c_str(), userName.length());
  digest.Update(svc.Get(), svc.Length());
  digest.Stop();
  return digest.Get();
}

bool Invoker::SetMethod(const char* _methodName, const char* _userName)
{
  userName = _userName;
  methodName = _methodName;
  if (invoker.setOperation(_methodName))
  {
    if (!SetParam("fromServiceName", serviceName))
    {
      return false;
    }
    math::MD4 crc = CalculateCrc(serviceName, userName, servicePassword);
    if (!SetParam("crc", crc.Get(), crc.Length())) 
    {
      return false;
    }
    return true;
  }
  return false;
}

ErrorCode Invoker::GetResultCode()
{
  int code; 
  std::string xpath = methodName+std::string("Response/")+methodName+std::string("Result/code");
  if (GetXResult<int>(xpath.c_str(), code))
  {
    return ErrorCode(code);
  } 
  return E_PARSE_FAILED;
}

ErrorCode Authorize(Invoker& invoker, const char* userName, const char* userPassword, int& userId)
{
  if(!invoker.SetMethod("AuthorizeUser", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }

    std::string userPassword(userPassword);
    math::MD4 pwd = math::GenerateMD5((const byte*)userPassword.c_str(), userPassword.length());
    if (!invoker.SetParam("userPassword", pwd.Get(), pwd.Length()))
    {
      return E_SETUP_FAILED;
    }

    if (invoker.Invoke())
    {
      ErrorCode code = invoker.GetResultCode(); 
      if (code == E_OK)
      {
        if (invoker.GetResult("userId", userId))
        {
          if (userId >= 0)
          {
            return E_OK;
          }
        }
      }
      return code;
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode GetBalance(Invoker& invoker, const char* userName, double& amount)
{
  if(!invoker.SetMethod("GetUserBalance", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }

    if (invoker.Invoke())
    {
      ErrorCode code = invoker.GetResultCode(); 
      if (code == E_OK)
      {
        if (invoker.GetResult("amount", amount))
        {
          return E_OK;
        }
      } 
      return code;
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode ReplenishAccount(Invoker& invoker, const char* userName, double amount, const char* reason)
{
  if(!invoker.SetMethod("AccountReplenish", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("amount", amount))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("paymentSystem", std::string("CBT")))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("reason", std::string(reason)))
    {
      return E_SETUP_FAILED;
    } 
    if (invoker.Invoke())
    {
      return invoker.GetResultCode(); 
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode WriteoffAccount(Invoker& invoker, const char* userName, double amount, const char* reason)
{
  if(!invoker.SetMethod("AccountWriteOff", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("amount", amount))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("reason", std::string(reason)))
    {
      return E_SETUP_FAILED;
    } 
    if (invoker.Invoke())
    {
      return invoker.GetResultCode(); 
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode GetUserProfile(Invoker& invoker, const char* userName, UserProfile& result)
{
  if(!invoker.SetMethod("GetUserProfile", userName))
  {
    return E_SETUP_FAILED;
  }
  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }                
    if (invoker.Invoke())
    {
      ErrorCode code = invoker.GetResultCode(); 
      if (code == E_OK)
      {
        if (!invoker.GetResult("userid", result.userid))
        {
          return E_PARSE_FAILED;
        }
        invoker.GetResult("email", result.email);
        invoker.GetResult("referalCode", result.referalCode);
        invoker.GetResult("displayName", result.displayName);
        invoker.GetResult("partner", result.partner);
        invoker.GetResult("agreementAccepted", result.agreementAccepted);
        return E_OK; 
      }
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}


ErrorCode GetServicesList(Invoker& invoker, const char* userName, std::vector<ServiceShortInfo>& services)
{
  if(!invoker.SetMethod("GetServicesList", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }
    if (invoker.Invoke())
    {
      ErrorCode code = invoker.GetResultCode(); 
      if (code == E_OK)
      {
        services.clear();
        return E_OK; 
      }
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode SubscribeService(Invoker& invoker, const char* userName, const std::string& serviceName)
{
  if(!invoker.SetMethod("SubscribeService", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("serviceName", serviceName))
    {
      return E_SETUP_FAILED;
    }
    if (invoker.Invoke())
    {
      ErrorCode code = invoker.GetResultCode(); 
      if (code == E_OK)
      {
        std::string accountName;
        if (invoker.GetResult("accauntName", accountName))
        {
          return E_OK; 
        } else
        {
          return E_INVALID_ARG;
        }
      }
      return code;
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode UnsubscribeService(Invoker& invoker, const char* userName, const std::string& serviceName)
{
  if(!invoker.SetMethod("UnsubscribeService", userName))
  {
    return E_SETUP_FAILED;
  }

  if (invoker.IsOk())
  {
    if (!invoker.SetParam("userName", invoker.GetUserName()))
    {
      return E_SETUP_FAILED;
    }
    if (!invoker.SetParam("serviceName", serviceName))
    {
      return E_SETUP_FAILED;
    }
    if (invoker.Invoke())
    {
      return invoker.GetResultCode(); 
    } else
    {
      return E_INVOKE_FAILED;
    }
  }
  return E_SETUP_FAILED;
}

ErrorCode GetUserInfo(InvokerOld& invoker, const std::string& userId, UserInfo& result)
{
  invoker.SetMethod("users.getInfo", userId);
  invoker.AddParam(userId);
  invoker.AddParam("1");
  invoker.AddParam("1");
  ErrorCode code = invoker.Invoke();
  if (code == E_OK)
  {
    code = invoker.GetResultCode();
    if (code == E_OK)
    {
      if (invoker.GetResult("sex", result.sex))
      {
        return E_OK;
      } else
      {
        return E_PARSE_FAILED;
      }
    }
  } 
  return code;
}

const char* GetErrorText(ErrorCode code)
{
  switch(code)
  {
  case E_OK : return "OK";
  case E_SETUP_FAILED : return "Setup failed";
  case E_INVOKE_FAILED : return "Invocation failed";
  case E_PARSE_FAILED : return "Parsing failed";
  case E_ACCESS : return "Access denied";
  case E_ALREADY_SUBSCRIBED : return "Already subscribed";
  case E_CRC : return "Crc error";
  case E_EMAIL_EXISTS : return "Email already exists";
  case E_INVALID_ACCOUNT : return "Invalid account";
  case E_INVALID_ARG : return "Invalid argument";
  case E_INVALID_PASSWORD : return "Invalid password";
  case E_INVALID_PROMO : return "Invalid promo";
  case E_INVALID_SERVICE : return "Invalid service";
  case E_INVALID_USER : return "Invalid user";
  case E_OVERDRAFT : return "Overdraft";
  case E_ZUNEXPECTED : return "Unexpected";
  case E_UNKNOWN_PAYMENT_SYSTEM : return "Unknown payment system";
  case E_UNSUBSCRIBED : return "Unsubscribed";
  case E_USER_EXISTS : return "User exists";
  };
  return "Unspecified";
}

namespace XmlUtils
{

void myPost(const std::string uri,const std::string username,
  const std::string password,const std::string data,
  std::string action,char* &results)
{
  unsigned long nread;
  W3Client w3;
  const char* d = data.c_str()   ;       
  if(w3.Connect(uri.c_str())){
    w3.InitializePostArguments();
    w3.setContentType("Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n");
    w3.setAcceptTypes("Accept: text/xml\r\n");
    w3.AddPostArgument(d,data.length());
    std::string tmp="SOAPAction: ";
    tmp+='"';
    tmp+=action;
    tmp+='"';
    tmp+="\r\n";
    w3.setSoapAction(tmp.c_str());

    if(w3.RequestPost(w3.GetURI()))
    {
      unsigned long nread = 0,tot=0;
      char buf[1024]="\0";

      while((nread=w3.Response(reinterpret_cast<unsigned char *>(buf), 1023))){


        if (results == 0){
          results = (char*)malloc(sizeof(unsigned char) * (nread+1));
        }
        else{
          results = (char*) realloc(results,sizeof(unsigned char) *  (nread + tot+1));
        }
        memcpy (results+tot,buf,nread);
        tot+=nread;
        results[tot]='\0';
      }
    }
    //std::cout<<results;
    w3.Close();
  }
}

}

void Escape(std::string& s, const char& c, bool bNeeedPercent)
{
  const char* hdig = "0123456789abcdef";
  if(bNeeedPercent)
    s += '%';
  s += hdig[(c >> 4) & 15];
  s += hdig[c & 15];
}

std::string Escape(unsigned char const *pBuf, size_t nBufLen, bool bNeeedPercent = true)
{
  std::string result;
  for(size_t i = 0; i < nBufLen; ++i)
  {
    std::string str("");
    Escape(str, pBuf[i], bNeeedPercent);
    result += str;
  }
  return result;
}

std::string Escape(std::string& s, bool bNeeedPercent = true)
{
  std::string result;
  for(size_t i = 0; i < s.length(); ++i)
  {
    std::string str("");
    Escape(str, s.c_str()[i], bNeeedPercent);
    result += str;
  }
  return result;
}

void XmlBuilder::AddField(const char* name, const std::string value, bool useBase64)
{
  signature += std::string(name)+std::string("=")+base64_encode((const byte*)value.c_str(), value.length());
  if (!result.empty())
  {
    result += std::string("&");
  }
  result += std::string(name)+std::string("=");
  if (useBase64)
  {
    result += base64_encode((const byte*)value.c_str(), value.length());
  } else
  {
    result += value;
  }
}

void XmlBuilder::Finish()
{
  signature += api_secret;
  math::MD4 crc = math::GenerateMD5((const byte*)signature.c_str(), signature.length());
  std::string crcStr = Escape((const byte*)crc.Get(), crc.Length(), false);
  AddField("sig", crcStr, false);
}

ErrorCode InvokerOld::Invoke()
{
  static const std::string comma(",");
  std::string method;
  for (uint i=0;i<params.size();++i)
  {
    if (i!=0)
    {
      method+=comma;
    }
    method += params[i];
  }
  XmlBuilder b(apiSecret);
  b.AddField("api_key", apiKey);
  b.AddField("game_user", userId);
  b.AddField("method", method);
  b.AddField("format", "xml");
  b.Finish();
  char* results = (char*)0;
  request = b.Get();
  XmlUtils::myPost(apiUrl, std::string(""), std::string(""), request, std::string("Get"), results);
  if (!results)
  {
    result.clear();
    return E_INVOKE_FAILED;
  }
  result = results;
  return E_OK;
}

bool InvokerOld::GetTokenValue(const char* _token, char* buffer, int size)
{
  std::string stoken = std::string("<")+_token+">";
  std::string etoken = std::string("</")+_token+">";
  int offset = result.find(stoken);
  if (offset >= 0)
  {
    int offset2 = result.find(etoken);
    int length = offset2-offset-stoken.length();
    if (offset2 > offset && length < size)
    {
      length = result.copy(buffer, length, offset+stoken.length());
      buffer[length] = 0;
      return true;
    }
  }
  return false;
}

}



