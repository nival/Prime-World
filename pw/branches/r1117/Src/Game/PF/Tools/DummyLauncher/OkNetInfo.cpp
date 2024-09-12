#include "stdafx.h"
#include "OkNetInfo.h"
#include "Convert.h"
#include "BrowserWindow.h"
#include "BrowserController.h"
#include "HttpRequest.h"
#include "Application.h"
#include "resource.h"

const char* okAuthURL = "SITE";

const char* okGetDataURL = "SITE";
const char* okGetTokenURL = "SITE";

int OkNetInfo::GetFirstControlID() const
{
  return IDC_OK_UID;
}

OkNetInfo::OkNetInfo(const std::string& snuid)
{
  m_snuid = snuid;
}

OkNetInfo::OkNetInfo()
{
}

OkNetInfo::~OkNetInfo()
{
}

bool OkNetInfo::Read(const Json::Value& info)
{
  if(SocialNetInfo::Read(info))
  {
    if(info.isMember("refreshToken"))
      m_refreshToken = info["refreshToken"].asString();
    else
      m_refreshToken.clear();
    return true;
  }
  return false;
}

void OkNetInfo::Write(Json::Value& info)
{
  SocialNetInfo::Write(info);
  info["refreshToken"] = m_refreshToken;
}

bool OkNetInfo::Assign(const SocialNetInfo* newSn)
{
  if(SocialNetInfo::Assign(newSn))
  {
    const OkNetInfo* ok = static_cast<const OkNetInfo*>(newSn);
    m_refreshToken = ok->m_refreshToken;
    return true;
  }
  return false;
}

bool OkNetInfo::Authorize()
{
  BrowserController ctrl;
//  ctrl.m_stopOnRedir = Convert::FromUTF8(g_App->GetConfig().GetValue("ok.RedirURI"));
  ctrl.m_url = Convert::ExpandString(okAuthURL).c_str();

  BrowserWindow wnd(&ctrl);
  if(wnd.Run() == IDOK)
  {
    std::string answer = (LPCSTR)ctrl.m_finalUrl;
    LOG("Get browser answer from OK: %s", answer.c_str());

    StringsMap pairs;
    Convert::ParseUrlParams(answer, pairs);

    std::string code = pairs["code"];
    if(!code.empty())
    {
      if(GetFirstToken(code) && RefreshToken(m_refreshToken))
        return GetUserData();
    }
    // ошибка
  }
  return false;
}

bool OkNetInfo::GetFirstToken(const std::string& code)
{
  m_lastRefreshTime = 0;
  std::wstring url = Convert::FromUTF8(okGetTokenURL);

  HttpRequest req;
  HttpRequest::RequestParams prms;

  prms["code"] = code;
  prms["grant_type"] = "authorization_code";
  prms["client_id"] = g_App->GetConfig().GetValue("ok.AppId");
  prms["client_secret"] = g_App->GetConfig().GetValue("ok.AppSecret");
  prms["redirect_uri"] = std::string(g_App->GetConfig().GetValue("ok.RedirURI")) + "?state=pwlaunch://";
//  prms[L"redirect_uri"] = Convert::FromUTF8(g_App->GetConfig().GetValue("ok.RedirURI"));

  HttpRequest::RequestHeaders headers;
  headers[L"content-type"] = L"application/x-www-form-urlencoded";

  if(req.SendRequest(url, prms, headers, HttpRequest::REQ_POST) == S_OK)
  {
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(root.isMember("access_token"))
      {
        m_token = root["access_token"].asString();
        m_refreshToken = root["refresh_token"].asString();

        g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);

        return true;
      }
      else
      {
        LOG("No access_token parameter passed from Odnoklassniki");
        g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, root);
      }
    }
    else
    {
      LOG("Can't parse answer from OK token.do: %s", reader.getFormattedErrorMessages().c_str());
      g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
    }
  }

  return false;
}

bool OkNetInfo::RefreshToken(const std::string& oldToken)
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

  std::wstring url = Convert::FromUTF8(okGetTokenURL);
  HttpRequest req;
  HttpRequest::RequestParams prms;
  prms["grant_type"] = "refresh_token";
  prms["client_id"] = g_App->GetConfig().GetValue("ok.AppId");
  prms["client_secret"] = g_App->GetConfig().GetValue("ok.AppSecret");
  prms["refresh_token"] = oldToken;

  HttpRequest::RequestHeaders headers;
  headers[L"content-type"] = L"application/x-www-form-urlencoded";

  if(req.SendRequest(url, prms, headers, HttpRequest::REQ_POST) == S_OK)
  {
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(root.isMember("access_token"))
      {
        m_token = root["access_token"].asString();
        m_lastRefreshTime = curTime;
        return true;
      }
      else
      {
        LOG("No access_token parameter passed from Odnoklassniki");
        g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, root);
      }
    }
    else
    {
      LOG("Can't parse answer from OK token.do: %s", reader.getFormattedErrorMessages().c_str());
      g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
    }
  }
  // ошибка
  m_loggedIn = false;

  return false;
}

bool OkNetInfo::GetUserData()
{
  if(m_token.empty())
    return false;
  std::wstring url = Convert::FromUTF8(okGetDataURL);
  HttpRequest req;
  
  HttpRequest::RequestParams prmsMap;
  prmsMap["method"] = "users.getCurrentUser";
  prmsMap["format"] = "JSON";
  prmsMap["application_key"] = g_App->GetConfig().GetValue("ok.AppPublic");
  
  std::string signature = Convert::MD5Hash( (m_token + g_App->GetConfig().GetValue("ok.AppSecret")).c_str() );
  std::string codeString = "";

  for(StringsMap::const_iterator prmsIter = prmsMap.begin(); prmsIter != prmsMap.end(); ++prmsIter)
    codeString += prmsIter->first + "=" + prmsIter->second;
  
  prmsMap["sig"] = Convert::MD5Hash( (codeString + signature).c_str() );
  prmsMap["access_token"] = m_token;

  if(req.SendRequest(url, prmsMap) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(!root.isMember("error"))
      {
        m_snuid = root["uid"].asString();
        _bstr_t name = root["name"].asCString();
        m_name = Convert::ToUTF8((LPWSTR)name);
        m_loggedIn = true;
        g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);
        return true;
      }
      else
      {
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

bool OkNetInfo::RefreshUserData()
{
  if(RefreshToken(m_refreshToken))
    return GetUserData();
  return false;
}

void OkNetInfo::PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr) const
{
  SocialNetInfo::PrepareServerParams(prms, idxStr);
  prms["snrefresh_token" + idxStr] = m_refreshToken;
}
