#include "stdafx.h"
#include "resource.h"
#include <algorithm>

#include "PWCNetInfo.h"
#include "Convert.h"
#include "HttpRequest.h"
#include "Application.h"
#include "Log.h"

const char* pwcAuthURL = "http://SITE.com:88/login?";

int PWCNetInfo::GetFirstControlID() const
{
  return IDC_PWC_UID;
}

PWCNetInfo::PWCNetInfo(const std::string& snuid)
{
  m_snuid = snuid;
}

PWCNetInfo::PWCNetInfo()
{
}

PWCNetInfo::~PWCNetInfo()
{
}

std::string PWCNetInfo::GetDisplayName() const
{
  return m_email;
}

bool PWCNetInfo::RefreshToken(const std::string& oldToken)
{
  LOG("RefreshToken is not implemented yet");
  return true;
}

bool PWCNetInfo::Read(const Json::Value& info)
{
  if(SocialNetInfo::Read(info))
  {
    if(info.isMember("nickName"))
      m_nickName = info["nickName"].asString();
    else
      m_nickName.clear();

    if(info.isMember("email"))
      m_email = info["email"].asString();
    else
      m_email.clear();

    if(info.isMember("password"))
      m_password = info["password"].asString();
    else
      m_password.clear();
    return true;
  }
  return false;
}

void PWCNetInfo::Write(Json::Value& info)
{
  SocialNetInfo::Write(info);
  info["nickName"] = m_nickName;
  info["email"] = m_email;
  info["password"] = m_password;
}

bool PWCNetInfo::Assign(const SocialNetInfo* newSn)
{
  if(SocialNetInfo::Assign(newSn))
  {
    const PWCNetInfo* pwc = static_cast<const PWCNetInfo*>(newSn);
    m_nickName = pwc->m_nickName;
    m_email = pwc->m_email;
    m_snuid = pwc->m_snuid;
    m_password = pwc->m_password;
    m_loggedIn = true;
    return true;
  }
  return false;
}

bool PWCNetInfo::Authorize(const std::wstring& _email, const std::wstring& password)
{
  std::string email(Convert::ToUTF8(_email));
  std::transform(email.begin(), email.end(), email.begin(), ::tolower);
  m_email = email;
  m_snuid = Convert::MD5Hash(email.c_str());
  m_password = Convert::ToUTF8(password);

  HttpRequest req;
  HttpRequest::RequestParams prms;
  prms["action"] = "l_who";
  prms["snid"] = "pwe";
  prms["snuid"] = Convert::MD5Hash(email.c_str());

  std::string signStr("");
  for (HttpRequest::RequestParams::const_iterator i = prms.begin(); i != prms.end(); ++i )
  {
    std::string name = i->first;
    std::string value = i->second;
    signStr += name + value;
  }
  std::string secret(Convert::MD5Hash(Convert::ToUTF8(password).c_str()));
  signStr += secret;
  LOG("Secret: %s", secret.c_str());
  signStr = Convert::MD5Hash(signStr.c_str());
  LOG("Signature: %s", signStr.c_str());
  prms["sign"] = signStr;

  std::wstring url = Convert::FromUTF8(pwcAuthURL);
  if (!g_App->GetVars().GetAuthServer().empty())
  {
    url = (g_App->GetVars().GetAuthServer() + L"login?").c_str();
  }
  
  if(req.SendRequest(url, prms) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if (root.isMember("response"))
      {
        const Json::Value&response = root["response"];
        if(!response.isMember("error"))
        {
          if(response.isMember("ok") && response["ok"] == 1)
          {
            m_snuid = response["uid"].asString();
            m_name = response["name"].asString();
            m_nickName = response["info"]["nick"].asString();
            m_token = response["token"].asString();
            if(response.isMember("server"))
            {
              g_App->GetMainWindow().SetServer(Convert::FromUTF8(response["server"].asCString()));
            }
            m_loggedIn = true;
            LOG("Get user data completed successfully");
            g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);
            return true;
          }
        }
        else
        {
          std::wstring errorString = L"Error l_login: server returns error. ec = %i.";
          if(response.isMember("error"))
            errorString += L"\r\n" + Convert::FromUTF8(response["error"].asCString());
          g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, response);
        }
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

bool PWCNetInfo::GetUserData()
{
  if(m_token.empty())
    return false;
  LOG("Get user data for %s:%s.", GetSnID(), m_snuid.c_str());
  std::wstring url = Convert::FromUTF8(pwcAuthURL + m_token);
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

void PWCNetInfo::PrepareServerParams(HttpRequest::RequestParams& prms, const std::string& idxStr) const
{
  SocialNetInfo::PrepareServerParams(prms, idxStr);
  prms.erase("sntoken"); // worthless for PWC
  prms["snid"] = "pwe"; // PWC snid is 'pwe' for the l_who queries
  if (prms["locale"].empty())
  {
    prms.erase("locale");
  }
  //prms["snrefresh_token" + idxStr] = m_refreshToken;
  prms["snuid"] = Convert::MD5Hash(m_email.c_str());

  std::string signStr("");
  for (HttpRequest::RequestParams::const_iterator i = prms.begin(); i != prms.end(); ++i )
  {
    std::string name = i->first;
    std::string value = i->second;
    signStr += name + value;
  }
  std::string secret(Convert::MD5Hash(m_password.c_str()));
  signStr += secret;
  LOG("Secret: %s", secret.c_str());
  signStr = Convert::MD5Hash(signStr.c_str());
  LOG("Signature: %s", signStr.c_str());
  prms["sign"] = signStr;
}
