#include "stdafx.h"
#include "SocialNetInfo.h"
#include "HttpRequest.h"
#include "Convert.h"
#include "Log.h"

SocialNetInfo::SocialNetInfo() 
  : m_lastRefreshTime(0)
  , m_loggedIn(false)
{
}

SocialNetInfo::~SocialNetInfo()
{
}

const char* SocialNetInfo::GetUID() const
{
  if(m_snuid.empty())
    return NULL;
  return m_snuid.c_str();
}

const char* SocialNetInfo::GetToken() const
{
  if(m_token.empty())
    return NULL;
  return m_token.c_str();
}

void SocialNetInfo::Reset()
{
  m_token.clear();
}

bool SocialNetInfo::Assign(const SocialNetInfo* newSn)
{
  if(GetSnID() == newSn->GetSnID())
  {
    m_snuid = newSn->m_snuid;
    m_token = newSn->m_token;
    m_name = newSn->m_name;
    m_lastRefreshTime = newSn->m_lastRefreshTime;
    m_loggedIn = newSn->m_loggedIn;
    return true;
  }
  return false;
}

bool SocialNetInfo::IsSimilar(const SocialNetInfo* sn) const
{
  return IsSimilar(sn->GetSnID(), sn->GetUID());
}

bool SocialNetInfo::IsSimilar(const std::string& snid, const std::string& snuid) const
{
  return (GetSnID() == snid && m_snuid == snuid);
}

bool SocialNetInfo::IsSimilarByName(const std::string& snid, const std::string& name) const
{
  if(GetSnID() == snid)
  {
    std::wstring ownName = Convert::FromUTF8(m_name);
    std::wstring wideName = Convert::FromUTF8(name);
    if(ownName.length() == wideName.length())
    {
      ownName = _wcslwr_s((wchar_t*)ownName.c_str(), ownName.length() + 1);
      wideName = _wcslwr_s((wchar_t*)wideName.c_str(), wideName.length() + 1);
      return (ownName == wideName);
    }
  }
  return false;
}

bool SocialNetInfo::Read(const Json::Value& info)
{
  if(info.isMember("snuid"))
    m_snuid = info["snuid"].asString();
  else
    m_snuid.clear();
  if(info.isMember("sntoken"))
    m_token = info["sntoken"].asString();
  else
    m_token.clear();

  if(info.isMember("name"))
    m_name = info["name"].asString();
  else
    m_name.clear();

  if(info.isMember("lastRefreshTime"))
    m_lastRefreshTime = (__time64_t)info["lastRefreshTime"].asUInt();
  else
    m_lastRefreshTime = 0;

  return true;
}

void SocialNetInfo::Write(Json::Value& info)
{
  info["snuid"] = m_snuid;
  info["sntoken"] = m_token;
  info["name"] = m_name;
  info["lastRefreshTime"] = (Json::UInt)m_lastRefreshTime;
}

bool SocialNetInfo::RefreshUserData()
{
  LOG("Refresh user data for %s:%s", GetSnID(), m_snuid.c_str());
  if(RefreshToken(m_token))
    return GetUserData();
  return false;
}

void SocialNetInfo::PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr) const
{
  prms["snid" + idxStr] = GetSnID();
  prms["snuid" + idxStr] = m_snuid;
  prms["sntoken" + idxStr] = m_token;
}

std::string SocialNetInfo::GetDisplayName() const
{
  std::string result = m_snuid;
  if(!m_name.empty())
    result += " " + m_name;
  return result;
}
