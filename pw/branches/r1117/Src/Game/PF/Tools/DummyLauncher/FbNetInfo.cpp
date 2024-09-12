#include "stdafx.h"
#include "FbNetInfo.h"
#include "Convert.h"
#include "BrowserWindow.h"
#include "BrowserController.h"
#include "HttpRequest.h"
#include "Application.h"
#include "resource.h"

const char* fbAuthURL = "SITE";
const char* fbRefreshURL = "SITE";
const char* fbGetDataURL = "SITE";

int FbNetInfo::GetFirstControlID() const
{
  return IDC_FB_UID;
}

FbNetInfo::FbNetInfo(const std::string& snuid)
{
  m_snuid = snuid;
}

FbNetInfo::FbNetInfo()
{
}

FbNetInfo::~FbNetInfo()
{
}

bool FbNetInfo::Read(const Json::Value& info)
{
  if(SocialNetInfo::Read(info))
  {
    if(info.isMember("nickName"))
      m_nickName = info["nickName"].asString();
    else
      m_nickName.clear();
    return true;
  }
  return false;
}

void FbNetInfo::Write(Json::Value& info)
{
  SocialNetInfo::Write(info);
  info["nickName"] = m_nickName;
}

bool FbNetInfo::Assign(const SocialNetInfo* newSn)
{
  if(SocialNetInfo::Assign(newSn))
  {
    const FbNetInfo* fb = static_cast<const FbNetInfo*>(newSn);
    m_nickName = fb->m_nickName;
    return true;
  }
  return false;
}

bool FbNetInfo::Authorize()
{
  BrowserController ctrl;
  ctrl.m_url = Convert::ExpandString(fbAuthURL).c_str();

  BrowserWindow wnd(&ctrl);
  if(wnd.Run() == IDOK)
  {
    std::string answer = (LPCSTR)ctrl.m_finalUrl;
    LOG("Get browser answer from FB: %s", answer.c_str());

    StringsMap pairs;
    Convert::ParseUrlParams(answer, pairs);

    std::string token = pairs["access_token"];
    if(!token.empty())
    {
      if(RefreshToken(token))
        return GetUserData();
    }
    else if(!pairs["error"].empty())
    {
      ShowError(L"Authorize error: %s", Convert::FromUTF8(pairs["error"]).c_str());
    }
    else
    {
      ShowError(L"Authorize error: Unknown");
    }
  }
  return false;
}

bool FbNetInfo::RefreshToken(const std::string& oldToken)
{
  LOG("Refresh token for %s:%s. Old token=%s", GetSnID(), m_snuid.c_str(), oldToken.c_str());
  if(oldToken.empty())
  {
    m_loggedIn = false;
    return false;
  }

  __time64_t curTime;
  _time64(&curTime);

  if(!m_token.empty() && curTime - m_lastRefreshTime < REFRESH_INTERVAL)
    return true;

  std::wstring url = Convert::FromUTF8(fbRefreshURL);
  HttpRequest req;
  HttpRequest::RequestParams prms;
  prms["client_id"] = g_App->GetConfig().GetValue("fb.AppId");
  prms["client_secret"] = g_App->GetConfig().GetValue("fb.AppSecret");
  prms["grant_type"] = "fb_exchange_token";
  prms["fb_exchange_token"] = oldToken;
  if(req.SendRequest(url, prms) == S_OK)
  {
    StringsMap pairs;
    Convert::ParseUrlParams(req.GetResultUTF8(), pairs);

    std::string token = pairs["access_token"];
    if(!token.empty())
    {
      m_lastRefreshTime = curTime;
      m_token = token;
      g_App->GetConsole().AddText(STYLE_FROM_SERVER, req.GetResult());
      return true;
    }
    else if(!pairs["error"].empty())
    {
      LOG_ERROR("Can't refresh token: %s", pairs["error"].c_str());
    }
    else
    {
      LOG_ERROR("Can't refresh token");
    }
    g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
  }
  else
  {
    LOG_ERROR("Can't refresh token for %s:%s.\r\nNetwork error: %s", GetSnID(), m_snuid.c_str(), Convert::ToUTF8(req.GetLastError()).c_str());
  }
  m_loggedIn = false;
  return false;
}

bool FbNetInfo::GetUserData()
{
  if(m_token.empty())
    return false;
  LOG("Get user data for %s:%s.", GetSnID(), m_snuid.c_str());
  std::wstring url = Convert::FromUTF8(fbGetDataURL + m_token);
  HttpRequest req;
  if(req.SendRequest(url) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(!root.isMember("error"))
      {
        m_snuid = root["id"].asString();
        m_name = root["name"].asString();
        m_nickName = root["username"].asString();
        m_loggedIn = true;
        LOG("Get user data complete succesfully");
        g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);
        return true;
      }
      else
      {
        std::string error = root["error"].asCString();
        LOG_ERROR("Error get data for %s:%s.\r\n\t%s", GetSnID(), m_snuid.c_str(), error.c_str());
        g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, root);
      }
    }
    else
    {
      g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
    }
  }
  m_loggedIn = false;
  return false;
}
