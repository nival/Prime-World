#pragma once

#include "SocialNetInfo.h"

class OkNetInfo : public SocialNetInfo
{
public:
  OkNetInfo();
  OkNetInfo(const std::string& snuid);
  virtual ~OkNetInfo();

  static const char* GetNameStatic()
  {
    return "ok";
  }

  virtual const char* GetSnID() const
  {
    return OkNetInfo::GetNameStatic();
  }

  virtual int GetFirstControlID() const;

  virtual bool Assign(const SocialNetInfo* newSn);

  virtual bool Read(const Json::Value& info);
  virtual void Write(Json::Value& info);
  virtual bool Authorize();
  virtual bool RefreshToken(const std::string& oldToken);
  virtual bool GetUserData();
  virtual bool RefreshUserData();

  virtual void PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr = "") const;
protected:
  bool GetFirstToken(const std::string& code);
  std::string m_refreshToken;
};

typedef RefCountPtr<OkNetInfo> OkNetInfoPtr;
