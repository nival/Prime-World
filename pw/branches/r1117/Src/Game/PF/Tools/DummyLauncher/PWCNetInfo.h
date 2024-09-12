#pragma once

#include "SocialNetInfo.h"

class PWCNetInfo : public SocialNetInfo
{
public:
  PWCNetInfo();
  PWCNetInfo(const std::string& login);
  virtual ~PWCNetInfo();
  static const char* GetNameStatic()
  {
    return "pwc";
  }

  virtual const char* GetSnID() const
  {
    return PWCNetInfo::GetNameStatic();
  }
  virtual int GetFirstControlID() const;

  virtual bool Assign(const SocialNetInfo* newSn);

  virtual bool Read(const Json::Value& info);
  virtual void Write(Json::Value& info);
  virtual bool Authorize(const std::wstring& email, const std::wstring& password);
  virtual bool Authorize() {return false;}
  virtual bool RefreshToken(const std::string& oldToken);
  virtual bool GetUserData();

  virtual void PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr = "") const;
  virtual std::string GetDisplayName() const;
  std::string GetPass() const { return m_password;}
protected:
  std::string m_nickName;
  std::string m_email;
  std::string m_password;
};

typedef RefCountPtr<PWCNetInfo> PWCNetInfoPtr;
