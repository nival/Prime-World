#pragma once

#include "SocialNetInfo.h"


class ZZNetInfo : public SocialNetInfo
{
public:
  ZZNetInfo();
  ZZNetInfo(const std::string& snuid);
  virtual ~ZZNetInfo();

  static const char* GetNameStatic()
  {
    return "zzma";
  }

  virtual const char* GetSnID() const
  {
    return ZZNetInfo::GetNameStatic();
  }

  virtual int GetFirstControlID() const;

  virtual bool Assign(const SocialNetInfo* newSn);

  virtual bool Read(const Json::Value& info);
  virtual void Write(Json::Value& info);
  virtual bool Authorize();
  virtual bool GetToken(const std::string& code);
  virtual bool RefreshToken(const std::string& oldToken) { return false; }
  virtual bool GetUserData();
protected:
  std::string m_nickName;
};

typedef RefCountPtr<ZZNetInfo> ZZNetInfoPtr;
