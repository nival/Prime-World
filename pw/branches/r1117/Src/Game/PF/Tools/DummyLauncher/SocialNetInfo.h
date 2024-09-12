#pragma once

#include "HttpRequest.h"

#define REFRESH_INTERVAL 600

class SocialNetInfo : public RefCountObject
{
public:
  SocialNetInfo(); 
  virtual ~SocialNetInfo();

  virtual const char* GetSnID() const = 0;
  virtual int GetFirstControlID() const = 0;
  virtual const char* GetUID() const;
  virtual const char* GetToken() const;
  virtual void Reset();
  virtual bool Assign(const SocialNetInfo* newSn);
  virtual bool IsSimilar(const SocialNetInfo* sn) const;
  virtual bool IsSimilar(const std::string& snid, const std::string& snuid) const;
  virtual bool IsSimilarByName(const std::string& snid, const std::string& name) const;

  template <typename T>
  RefCountPtr<T> Cast()
  {
    return dynamic_cast<T*>(this);
  }

  virtual bool Read(const Json::Value& info);
  virtual void Write(Json::Value& info);
  virtual bool Authorize() = 0;
  virtual bool RefreshToken(const std::string& oldToken) = 0;
  virtual bool GetUserData() = 0;
  virtual bool RefreshUserData();

  virtual bool IsLoggedIn() const { return m_loggedIn; }

  virtual void PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr = "") const;
  virtual std::string GetDisplayName() const;
protected:
  std::string m_name;
  std::string m_snuid;
  std::string m_token;
  __time64_t  m_lastRefreshTime;
  bool m_loggedIn;
};

typedef RefCountPtr<SocialNetInfo> SocialNetInfoPtr;
