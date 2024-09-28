#include "stdafx.h"
#include "ZZNetInfo.h"
#include "Convert.h"
#include "BrowserWindow.h"
#include "BrowserController.h"
#include "HttpRequest.h"
#include "Application.h"
#include "resource.h"

const char* zzAuthURL = "SITE";
const char* zzGetTokenURL = "SITE";
const char* zzGetDataURL = "SITE";

int ZZNetInfo::GetFirstControlID() const
{
  return IDC_ZZ_UID;
}

ZZNetInfo::ZZNetInfo(const std::string& snuid)
{
  m_snuid = snuid;
}

ZZNetInfo::ZZNetInfo()
{
}

ZZNetInfo::~ZZNetInfo()
{
}

bool ZZNetInfo::Read(const Json::Value& info)
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

void ZZNetInfo::Write(Json::Value& info)
{
  SocialNetInfo::Write(info);
  info["nickName"] = m_nickName;
}

bool ZZNetInfo::Assign(const SocialNetInfo* newSn)
{
  if(SocialNetInfo::Assign(newSn))
  {
    const ZZNetInfo* zz = static_cast<const ZZNetInfo*>(newSn);
    m_nickName = zz->m_nickName;
    return true;
  }
  return false;
}

bool ZZNetInfo::Authorize()
{
  BrowserController ctrl;
  ctrl.m_url = Convert::ExpandString(zzAuthURL).c_str();
  ctrl.m_stopOnRedir = Convert::FromUTF8(g_App->GetConfig().GetValue("zzma.RedirURI"));

  BrowserWindow wnd(&ctrl);
  if(wnd.Run() == IDOK)
  {
    std::string answer = (LPCSTR)ctrl.m_finalUrl;
    LOG("Get browser answer from ZZima: %s", answer.c_str());

    StringsMap pairs;
    Convert::ParseUrlParams(answer, pairs);

    std::string code = pairs["code"];
    if(!code.empty())
    {
      if(GetToken(code))
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

bool ZZNetInfo::GetToken(const std::string& code)
{
  LOG("Get token for %s:%s. Code=%s", GetSnID(), m_snuid.c_str(), code.c_str());
  if(code.empty())
  {
    m_loggedIn = false;
    return false;
  }

  __time64_t curTime;
  _time64(&curTime);
/*
  if(!m_token.empty() && curTime - m_lastRefreshTime < REFRESH_INTERVAL)
    return true;
*/
  std::wstring url = Convert::FromUTF8(zzGetTokenURL);
  HttpRequest req;
  HttpRequest::RequestParams prms;
  prms["client_id"] = g_App->GetConfig().GetValue("zzma.AppId");
  prms["client_secret"] = g_App->GetConfig().GetValue("zzma.AppSecret");
  prms["redirect_uri"] = g_App->GetConfig().GetValue("zzma.RedirURI");
  prms["code"] = code;

  HttpRequest::RequestHeaders headers;
  headers[L"content-type"] = L"application/x-www-form-urlencoded";
  if(req.SendRequest(url, prms, headers, HttpRequest::REQ_POST) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(!root.isMember("error"))
      {
        m_token = root["access_token"].asString();
        if (root["user_id"].isString())
          m_snuid = root["user_id"].asString();
        else
          m_snuid = Convert::ToUTF8(Convert::FormatString(L"%d", root["user_id"].asUInt()));

        LOG("Get token complete successfully");
        g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);
        return true;
      }
      else
      {
        std::string error = root["error"].asCString();
        if (root.isMember("error_description"))
          error = root["error_description"].asCString();
        LOG_ERROR("Error get token for %s:%s.\r\n\t%s", GetSnID(), m_snuid.c_str(), error.c_str());
        g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, root);
      }
    }
    else
    {
      LOG_ERROR("Can't get token");
      g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
    }
  }
  else
  {
    LOG_ERROR("Can't get token for %s:%s.\r\nNetwork error: %s", GetSnID(), m_snuid.c_str(), Convert::ToUTF8(req.GetLastError()).c_str());
  }
  m_loggedIn = false;
  return false;
}

bool ZZNetInfo::GetUserData()
{
  if(m_token.empty())
    return false;
  LOG("Get user data for %s:%s.", GetSnID(), m_snuid.c_str());
  std::wstring url = Convert::FromUTF8(zzGetDataURL);
  HttpRequest req;
  HttpRequest::RequestParams prms;
  prms["userhash"] = m_token;
  
  HttpRequest::RequestHeaders headers;
  headers[L"content-type"] = L"application/x-www-form-urlencoded";
  if(req.SendRequest(url, prms, headers, HttpRequest::REQ_POST) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(!root.isMember("error"))
      {
        //m_snuid = root["user"]["userid"].asString();
        try
        {
          Json::Value user = root.get("user", Json::nullValue);
          m_name = user["userName"].asString();
          m_nickName = user["userName"].asString();
        }
        catch(...)
        {

        }
        
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
