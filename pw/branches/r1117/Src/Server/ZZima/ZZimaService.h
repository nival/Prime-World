#pragma once

#include <wsdlparser/Wsdlinvoker.h>
#include <string>

namespace ZZima
{

  enum ErrorCode
  {
    E_OK = 0, 
    E_ASYNC_WAIT = -1, // связываемся асинхронно, поэтому сразу из PerformLoginCheck возвращаем error code "ждите ответа"
    E_SETUP_FAILED = -500,
    E_INVOKE_FAILED = -501,
    E_PARSE_FAILED = -502,
    E_INVALID_ARG = -1000,
    E_CRC = -1001,
    E_EMAIL_EXISTS = -1002,
    E_USER_EXISTS = -1003,
    E_INVALID_USER = -1004,
    E_INVALID_PASSWORD = -1005,
    E_UNKNOWN_PAYMENT_SYSTEM = -1006,
    E_INVALID_ACCOUNT = -1007,
    E_OVERDRAFT = -1008,
    E_ALREADY_SUBSCRIBED = -1009,
    E_UNSUBSCRIBED = -1010,
    E_INVALID_SERVICE = -1011,
    E_ACCESS = -1012,
    E_INVALID_PROMO = -1013,
    E_ZUNEXPECTED = -2000,
  };

struct Invoker
{
  enum Status
  {
    NotConnected,
    Connected,
  };

  Invoker(const std::string& url, const std::string& _serviceName, const char* _servicePassword=0, bool verbose=true);

  bool SetParam(const std::string& name, const std::string& value)
  {
    return invoker.setValue(name, value);
  }

  bool SetParam(const std::string& name, double value)
  {
    return invoker.setValue(name, &value);
  }

  bool SetParam(const std::string& name, const void* value, int size);

  bool SetMethod(const char* _methodName, const char* _userName);

  bool Invoke(bool buildXml=false, long timeout = 0,bool processResponse = true)
  {
    invoker.setBuildXmlTree(buildXml);
    return invoker.invoke(timeout, processResponse);
  }

  bool GetResult(const char* name, int& result)
  {
    return _GetResult<XSD_INT, int>(name, result);
  }

  bool GetResult(const char* name, bool& result)
  {
    return _GetResult<XSD_BOOLEAN, bool>(name, result);
  }

  bool GetResult(const char* name, double& result)
  {
    return _GetResult<XSD_DECIMAL, double>(name, result);
  }

  bool GetResult(const char* name, std::string& result)
  {
    return _GetResult<XSD_STRING, std::string>(name, result);
  }

  Status GetStatus() const { return status; }
  bool IsOk() { return invoker.status(); }
  ErrorCode GetResultCode();

  std::string GetErrors() { return invoker.errors(); }
  std::string GetXMLResponse() { return invoker.getXMLResponse(); }
  const std::string& GetUserName() { return userName; }
  const std::string& GetServiceName() { return serviceName; }
  const std::string& GetServicePassword() { return servicePassword; }
private:
  template <typename T>
  bool GetXResult(const char* name, T& result, bool canBeEmpty=false)
  {
    std::string value = invoker.getValue<std::string>(name);
    if (!canBeEmpty && value.empty())
    {
      return false;
    }
    std::istringstream iss(value);
    iss>>result;
    return true;
  }

  template <Schema::Type TYPE, typename T>
  bool _GetResult(const char* name, T& result)
  {
    Schema::Type t;
    void * val = invoker.getValue(name, t);
    if (val && t == TYPE)
    {
      result = *((T*)val);
      return true;
    }
    return false;
  }

  Status status;
  WsdlPull::WsdlInvoker invoker;
  std::string serviceName;
  std::string servicePassword;
  std::string userName;
  std::string methodName;
};

struct XmlBuilder
{
  XmlBuilder(const std::string _api_secret):
  api_secret(_api_secret)
  {
  }
  void AddField(const char* name, const std::string value, bool useBase64=true);
  void Finish();

  const std::string& Get() const { return result; } 
  std::string result;
  std::string signature;
  std::string api_secret;
};

class InvokerOld
{
public:
  InvokerOld(const std::string& _apiUrl, const std::string& _apiKey, std::string _apiSecret):
  apiKey(_apiKey),
  apiSecret(_apiSecret),
  apiUrl(_apiUrl)
  {

  }

  void SetMethod(const std::string& method, const std::string& _userId)
  {
    userId = _userId;
    params.clear();
    params.push_back(method);
  }

  void AddParam(const std::string& param)
  {
    params.push_back(param);
  }

  ErrorCode Invoke();
  bool GetResult(const char* name, int& result)
  {
    char buffer[64];
    if (GetTokenValue(name, buffer, 64))
    {
      result = atoi(buffer);
      return true;
    }
    return false;
  }

  ErrorCode GetResultCode()
  {
    char buffer[64];
    if (GetTokenValue("result", buffer, 64))
    {
      int code = atoi(buffer);
      if (code == 1)
      {
        return E_OK;
      }
    }
    return E_PARSE_FAILED;
  }
  const char* GetResult() const { return result.c_str(); }
  const char* GetRequest() const { return request.c_str(); }
private:
  bool GetTokenValue(const char* _token, char* buffer, int size);

  std::vector<std::string> params;
  std::string userId;
  std::string apiKey;
  std::string apiSecret;
  std::string apiUrl;
  std::string result;
  std::string request;
};


struct ServiceShortInfo
{
  std::string serviceName;
  bool subscribed;
};

struct UserInfo
{
  int sex;
};

struct UserProfile
{
  int userid;
  std::string email;
  std::string referalCode;
  std::string displayName;
  std::string partner;
  bool agreementAccepted;
};

ErrorCode Authorize(Invoker& invoker, const char* userName, const char* userPassword, int& userId);
ErrorCode GetBalance(Invoker& invoker, const char* userName, double& amount);
ErrorCode ReplenishAccount(Invoker& invoker, const char* userName, double amount, const char* reason);
ErrorCode WriteoffAccount(Invoker& invoker, const char* userName, double amount, const char* reason);
ErrorCode GetServicesList(Invoker& invoker, const char* userName, std::vector<ServiceShortInfo>& services);
ErrorCode SubscribeService(Invoker& invoker, const char* userName, const std::string& serviceName);
ErrorCode UnsubscribeService(Invoker& invoker, const char* userName, const std::string& serviceName);
ErrorCode GetUserInfo(InvokerOld& invoker, const std::string& userId, UserInfo& result);
const char* GetErrorText(ErrorCode code);
ErrorCode GetUserProfile(Invoker& invoker, const char* userName, UserProfile& result);

}
