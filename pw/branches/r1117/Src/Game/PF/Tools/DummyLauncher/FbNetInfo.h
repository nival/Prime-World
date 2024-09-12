#pragma once

#include "SocialNetInfo.h"

class FbNetInfo : public SocialNetInfo
{
public:
  FbNetInfo();
  FbNetInfo(const std::string& snuid);
  virtual ~FbNetInfo();

  static const char* GetNameStatic()
  {
    return "fb";
  }

  virtual const char* GetSnID() const
  {
    return FbNetInfo::GetNameStatic();
  }

  virtual int GetFirstControlID() const;

  virtual bool Assign(const SocialNetInfo* newSn);

  virtual bool Read(const Json::Value& info);
  virtual void Write(Json::Value& info);
  virtual bool Authorize();
  virtual bool RefreshToken(const std::string& oldToken);
  virtual bool GetUserData();
protected:
  std::string m_nickName;
};

typedef RefCountPtr<FbNetInfo> FbNetInfoPtr;
