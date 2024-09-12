#include "stdafx.h"
#include "Application.h"
#include "log.h"
#include "UsersInfo.h"
#include "Convert.h"
#include "FbNetInfo.h"
#include "OkNetInfo.h"
#include "ZZNetInfo.h"
#include "PWCNetInfo.h"


UsersInfo::UsersInfo()
{
  char buf[32];
  sprintf_s(buf,"dummy host %d%d", rand()%RAND_MAX, rand()%RAND_MAX);
  m_hostId = Convert::MD5Hash(buf);
}

UsersInfo::~UsersInfo()
{
}

SocialNetInfoPtr UsersInfo::CreateSocialNet(const std::string& name, const std::string& snuid) const
{
  if(name == "fb")
    return new FbNetInfo(snuid);
  if(name == "ok")
    return new OkNetInfo(snuid);
  if(name == "zzma")
    return new ZZNetInfo(snuid);
  if(name == "pwc")
    return new PWCNetInfo(snuid);
  return NULL;
}

SocialNetInfoPtr UsersInfo::CreateSocialNet(const std::string& name) const
{
  return CreateSocialNet(name, "");
}

void UsersInfo::StoreSocialNet(SocialNetInfoPtr sn)
{
  SocialNetInfoPtr oldSn = Find(sn->GetSnID(), sn->GetUID());
  if(oldSn)
    oldSn->Assign(sn);
  else
    m_socNets.push_back(sn);
}

SocialNetInfoPtr UsersInfo::Find(const std::string& snid, const std::string& snuid)
{
  for(size_t idx = 0; idx < m_socNets.size(); idx++)
    if(m_socNets[idx]->IsSimilar(snid, snuid))
      return m_socNets[idx];
  return NULL;
}

SocialNetInfoPtr UsersInfo::FindByName(const std::string& snid, const std::string& name)
{
  for(size_t idx = 0; idx < m_socNets.size(); idx++)
    if(m_socNets[idx]->IsSimilarByName(snid, name))
      return m_socNets[idx];
  return NULL;
}

void UsersInfo::Clear()
{
  m_socNets.clear();
}


bool UsersInfo::LoadCache()
{
  HANDLE file = CreateFile(g_App->GetVars().GetUsersCacheFile().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  if (file == INVALID_HANDLE_VALUE)
  {
    LOG_WARNING("Can't load cached info %s",
      Convert::ToUTF8(_com_error(HRESULT_FROM_WIN32(GetLastError())).ErrorMessage()).c_str());
    return false;
  }

  DWORD size = GetFileSize(file, NULL);
  CharsVector fileBuffer(size + 1, 0);

  if(!ReadFile(file, (void*)&fileBuffer[0], size, &size, NULL))
  {
    LOG_WARNING("Can't load cached info %s",
      Convert::ToUTF8(_com_error(HRESULT_FROM_WIN32(GetLastError())).ErrorMessage()).c_str());
    CloseHandle(file);
    return false;
  }
  CloseHandle(file);

  std::strstream buffer(&fileBuffer[0], size);

  Json::Value root;
  Json::Reader reader;
  if(!reader.parse(buffer, root, false))
  {
    std::string err = reader.getFormattedErrorMessages();
    LOG_WARNING("Can't parse user cached info %s", err.c_str());
    return false;
  }

  if(!root.isArray())
  {
    LOG_WARNING("Can't parse user cached info. Root is not array");
    return false;
  }

  m_socNets.clear();
  for(Json::Value::iterator snIter = root.begin(); snIter != root.end(); ++snIter)
  {
    const Json::Value& snInfo = *snIter;
    try
    {
      std::string name = snInfo["snid"].asString();
      SocialNetInfoPtr sn = CreateSocialNet(name);
      if(sn)
      {
        if(sn->Read(snInfo))
          m_socNets.push_back(sn);
      }
    }
    catch(std::exception& ex)
    {
      LOG_WARNING("Exception in read user cached info. %s", ex.what());
    }
  }
  LOG("User cached info successfully parsed. Has %i elements", (int)m_socNets.size());

  return true;
}

bool UsersInfo::SaveCache()
{
  Json::Value root(Json::arrayValue);
  for(size_t idx = 0; idx < m_socNets.size(); idx++)
  {
    Json::Value snValue;
    m_socNets[idx]->Write(snValue);
    snValue["snid"] = m_socNets[idx]->GetSnID();
    root.append(snValue);
  }

  std::strstream stream;
  Json::StyledStreamWriter writer;
  writer.write(stream, root);


  HANDLE file = CreateFile(g_App->GetVars().GetUsersCacheFile().c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file == INVALID_HANDLE_VALUE)
  {
    LOG_WARNING("Can't save cached info %s",
      Convert::ToUTF8(_com_error(HRESULT_FROM_WIN32(GetLastError())).ErrorMessage()).c_str());
    return false;
  }

  std::strstreambuf* buffer = stream.rdbuf();
  DWORD size = stream.pcount();
  if(!WriteFile(file, buffer->str(), size, &size, NULL))
  {
    LOG_WARNING("Can't save cached info %s",
      Convert::ToUTF8(_com_error(HRESULT_FROM_WIN32(GetLastError())).ErrorMessage()).c_str());
    buffer->freeze(false);
    CloseHandle(file);
    return false;
  }

  buffer->freeze(false);
  CloseHandle(file);

  return true;
}

SocialNetInfoPtr UsersInfo::GetFromSns(const std::string& name) const
{
  StringSocialNetsMap::const_iterator snIter = m_sns.find(name);
  if(snIter == m_sns.end())
    return NULL;
  return snIter->second;
}

bool UsersInfo::IsAllLoggedIn() const
{
  for(StringSocialNetsMap::const_iterator snIter = m_sns.begin(); snIter != m_sns.end(); ++snIter)
    if(!snIter->second->IsLoggedIn())
      return false;
  return !m_sns.empty();
}

void UsersInfo::Logout()
{
  m_firstLoggedSnS = 0;
  m_auid.clear();
  m_token.clear();
  m_nickName.clear();
  m_sns.clear();
}

bool UsersInfo::OnAuthorized(SocialNetInfoPtr socNet)
{
  if(socNet->IsLoggedIn())
    StoreSocialNet(socNet);

  if(IsLoggedIn())
  {
    SocialNetInfoPtr sn = GetFromSns(socNet->GetSnID());
    if(!sn || !sn->IsSimilar(socNet))
      return false;
    return sn->Assign(socNet);
  }
  if(AuthOnServer(socNet))
  {
    for(StringSocialNetsMap::iterator snsIter = m_sns.begin(); snsIter != m_sns.end(); ++snsIter)
    {
      if (!snsIter->second)
        continue;

      if(!snsIter->second->IsLoggedIn())
        snsIter->second->RefreshUserData();
      if(snsIter->second->IsLoggedIn())
        StoreSocialNet(snsIter->second);
    }

    SaveCache();

    return true;
  }
  return false;
}

bool UsersInfo::AuthOnServer(SocialNetInfoPtr socNet)
{
  Logout();
  std::wstring url = g_App->GetVars().GetAuthServer() + GetServer();
  HttpRequest::RequestParams prms;

  prms["action"] = "l_who";
  prms["hostid"] = m_hostId;
  prms["ver"] = Convert::ToUTF8(g_App->GetVars().GetProtocolVersion());
  prms["locale"] = Convert::ToUTF8(g_App->GetVars().GetLocale());
  prms["primary"] = IsLoggedIn() ? "0" : "1";
  socNet->PrepareServerParams(prms);

  HttpRequest req;
  if(req.SendRequest(url, prms) == S_OK)
  {
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(req.GetResultUTF8(), root, false))
    {
      if(root.isMember("response"))
      {
        const Json::Value& response = root["response"];
        if(response.isMember("ok") && response["ok"] == 1)
        {
          const Json::Value& info = response["info"];
          if(info.isMember("nick"))
            m_nickName = info["nick"].asString();
          else
            m_nickName.clear();
          if(response.isMember("token"))
            m_token = response["token"].asString();
          else
            m_token.clear();

          m_auid = info["auid"].asString();
          if(response.isMember("server"))
            g_App->GetMainWindow().SetServer(Convert::FromUTF8(response["server"].asCString()));

          if (!m_firstLoggedSnS)
            m_firstLoggedSnS = socNet;

          LOG("l_who success. Trying to authorize sns list");

          g_App->GetConsole().AddText(STYLE_FROM_SERVER, root);

          const Json::Value& sns = response["sns"];
          for(Json::Value::const_iterator snsIter = sns.begin();
            snsIter != sns.end();
            ++snsIter)
          {
            std::string snid = snsIter.key().asString();

            std::string snuid;
            try
            {
              snuid = (*snsIter).asString();
            }
            catch(std::runtime_error&)
            {
              snuid = Convert::ToUTF8(Convert::FormatString(L"%d", (*snsIter).asUInt()));
            }
            //sns[snid].asString();

            SocialNetInfoPtr sn = Find(snid, snuid);
            if(!sn)
            {
              sn = CreateSocialNet(snid, snuid);
            }

            if(sn)
              m_sns[snid] = sn;
          }
          return true;
        }
        else
        {
          int ec = 0;
          if(response.isMember("ec"))
            ec = response["ec"].asInt();
          std::wstring errorString = L"Error l_who: server returns error. ec = %i.";
          if(response.isMember("error"))
            errorString += L"\r\n" + Convert::FromUTF8(response["error"].asCString());
          ShowError(errorString.c_str(), ec);
          g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, root);
          return false;
        }
      }
    }
    ShowError(L"Error l_who: wrong server answer");
    g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, req.GetResult());
  }
  else
  {
    ShowError(L"Error l_who: %s", req.GetLastError().c_str());
  }

  return false;
}

bool UsersInfo::LoginOnServer()
{
  return true;
  /*
  if(!IsLoggedIn())
    return false;

  HttpRequest::RequestParams reqPrms;
  reqPrms["action"] = "l_login";
  reqPrms["ver"] = Convert::ToUTF8(g_App->GetVars().GetProtocolVersion());
  reqPrms["auid"] = m_auid;
  long idx = 0;
  for(StringSocialNetsMap::const_iterator snIter = m_sns.begin(); snIter != m_sns.end(); ++snIter)
  {
    SocialNetInfoPtr sn = snIter->second;
    if(sn && sn->IsLoggedIn())
      sn->PrepareServerParams(reqPrms, Convert::VarToString(idx));
  }

  std::wstring url = g_App->GetVars().GetAuthServer() + GetServer() + L"?";
  HttpRequest httpReq;
  if( httpReq.SendRequest(url, reqPrms) != S_OK )
  {
    ShowError(L"Error l_login: %s", httpReq.GetLastError().c_str());
    return false;
  }
  Json::Reader reader;
  Json::Value respData;
  if(reader.parse(httpReq.GetResultUTF8(), respData, false))
  {
    if(respData.isMember("response"))
    {
      const Json::Value& response = respData["response"];
      int ec = 0;
      if(response.isMember("ec"))
        ec = response["ec"].asInt();
      if(ec > 0)
      {
        std::wstring errorString = L"Error l_login: server returns error. ec = %i.";
        if(response.isMember("error"))
          errorString += L"\r\n" + Convert::FromUTF8(response["error"].asCString());
        ShowError(errorString.c_str(), ec);
        g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, respData);
        return false;
      }

      if(response.isMember("ok") && response["ok"].asInt() == 1)
      {
        if(response.isMember("token"))
          m_token = response["token"].asString();
        g_App->GetConsole().AddText(STYLE_FROM_SERVER, respData);
        return true;
      }
    }
  }
  ShowError(L"Error l_login: wrong server answer");
  g_App->GetConsole().AddText(STYLE_FROM_SERVER, httpReq.GetResult());
  return false;*/
}

std::string UsersInfo::MakeCmdLine() const
{
  std::string prms;
  if(IsLoggedIn())
  {
    for(StringSocialNetsMap::const_iterator snsIter = m_sns.begin(); snsIter != m_sns.end(); ++snsIter)
    {
      const SocialNetInfo* sn = snsIter->second;
      if( sn && sn->IsLoggedIn())
      {
        if(!prms.empty())
          prms += " ";
        prms += std::string("--uid ") + sn->GetSnID() + ":" + sn->GetUID();
      }
    }
  }
  return prms;
}

std::wstring UsersInfo::GetServer() const
{
  return g_App->GetMainWindow().GetServer();
}
