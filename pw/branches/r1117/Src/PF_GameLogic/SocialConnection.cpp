#include "stdafx.h"
#include <sstream>
#include "SocialConnection.h"
#include "System/Math/MD4.h"
#include "curl/curl.h"
#include "System/Base64.h"
#include "AdventureScreen.h"
#include "AdventureScreenLogic.h"
#include "../System/FileSystem/FilePath.h"
#include "../System/FileSystem/FileUtils.h"
#include <direct.h>

#include "HttpStuff.h"
#include "SocialBootstrap.h"

namespace
{
namespace EShareState 
{
  enum Enum 
  {
    NONE = 0,
    START,
    WAIT_SCREENSHOT,
    WAIT_URL,
  };
}

EShareState::Enum g_shareState = EShareState::NONE;
string screenshotFileName = "share.png";
char openUrl[1024];

size_t curl_to_string(void *ptr, size_t size, size_t nmemb, void *data)
{
  char *str = (char *) data;
  char *sptr = (char *) ptr;
  size_t len = size * nmemb;

  // \0 is appended while clearing memory with 0's
  strncpy(str, sptr, len);
  return len;
}

void EraseShareFileSafe()
{
  string path = GetFullFolderPath(NProfile::FOLDER_SCREENSHOTS);
  if (NFile::DoesFolderExist(path))
  {
    string screenshotName = NFile::Combine(path, screenshotFileName);
    if (NFile::DoesFileExist(screenshotName))
    {
      NFile::EraseFile(screenshotName);
    }
  }
}

}

namespace NGameX
{

void SocialConnection::SendRequest(const Http::HttpRequest& request, const nstl::string& data)
{
  // Erase old jobs
  for (int i = 0; i < sendRequestJobs.size(); i++)
  {
    if (sendRequestJobs[i])
      if (!sendRequestJobs[i]->Wait(0))
        continue;
    sendRequestJobs[i] = 0;
    sendRequestJobs.erase(sendRequestJobs.begin() + i);
    i--;
  }

  StrongMT<Http::RequestSender> sender;

  sendRequestJobs.push_back(Http::SendRequestAsync(sender, request, data));
}

SocialConnection::SocialConnection(const char* _serverName, const char* _uid, const char* _serverKey, const char* _serverSecret)
  : rid(1000000)
  , serverName(_serverName)
  , uid(_uid)
  , serverKey(_serverKey)
  , serverSecret(_serverSecret)
{
  curl_global_init(CURL_GLOBAL_ALL);
}

SocialConnection::SocialConnection(const SocialBootstrap::Session& ss)
  : rid(1000000)
  , serverName(ss.GetServerLocation())
  , uid(ss.GetUID())
  , serverKey(ss.GetServerKey())
  , serverSecret(ss.GetServerSecret())
{
  curl_global_init(CURL_GLOBAL_ALL);
}

SocialConnection::~SocialConnection()
{
}

void SocialConnection::GenerateRequest(Http::HttpRequest& request)
{
  request.SetRID(rid);
  request.SetUID(uid);
  request.SetKey(serverKey);

  request.Build(serverSecret);

  ++rid;
}

bool SocialConnection::AddFriend(__int64 auid)
{
  Http::HttpRequest request(serverName);

  request.AddQueryParam("action", "invite_friend");
  request.AddQueryParam("friend_uid", auid);

  GenerateRequest(request);
  SendRequest(request);

  return true;
}

bool SocialConnection::CreateComplaint(__int64 toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists, int points, int prime, int leave, int distance, int afks)
{
  nstl::string res;
  NStr::UnicodeToUTF8(&res, text);
  const nstl::string base64str(Base64::base64url_encode(reinterpret_cast<const unsigned char*>(res.c_str()), res.size()));

  nstl::string logs;
  NStr::UnicodeToUTF8(&logs, _logs);
  if (logs.empty())
    logs = "None";
  const nstl::string base64logs(Base64::base64_encode(reinterpret_cast<const unsigned char*>(logs.c_str()), logs.size()));
  
  lobby::TGameId sessionId = 0;

  if (AdventureScreen* pAdvScreen = AdventureScreen::Instance())
  {
    sessionId = pAdvScreen->GetSessionId();
  }

  Http::HttpRequest request(serverName);

  request.AddQueryParam("action", "create_complaint");
  request.AddQueryParam("toauid", toauid);
  request.AddQueryParam("category", category);
  request.AddQueryParam("text", base64str);
  request.AddQueryParam("sessionid", sessionId);
  request.AddQueryParam("source", 1);
  request.AddQueryParam("kills", kills);
  request.AddQueryParam("deaths", deaths);
  request.AddQueryParam("assists", assists);
  request.AddQueryParam("points", points);
  request.AddQueryParam("prime", prime);
  request.AddQueryParam("leave", leave);
  request.AddQueryParam("distance", distance);
  request.AddQueryParam("afks", afks);

  nstl::string data("post_data=");

  {
    data += base64logs;
  }

  GenerateRequest(request);
  SendRequest(request, data);

  return true;
}

bool SocialConnection::ChoosePartyAgain(const nstl::vector<__int64>& auids, const unsigned __int64 sessionId, const unsigned __int64 timeLeft, const bool agreed)
{
  Json::Value allies(Json::arrayValue);

  for (int i = 0, count = auids.size(); i < count; ++i)
  {
    allies.append(auids[i]);
  }

  Json::Value json(Json::objectValue);

  json["agreed"] = (agreed ? 1U : 0U);
  json["allies_keys"] = allies;
  json["lock_end_time"] = timeLeft;

  const std::string json_text(Json::FastWriter().write(json));

  nstl::string data;

  data += "post_data";
  data += "=";
  data += json_text.c_str();

  MessageTrace("choose_party_again:\n%s", data.c_str());

  Http::HttpRequest request(serverName);

  request.AddQueryParam("action", "choose_party_again");
  request.AddQueryParam("session_id", sessionId);

  GenerateRequest(request);
  SendRequest(request, data);

  return true;
}

void SocialConnection::parseAuids(const nstl::vector<__int64>& auids, std::string& res )
{
  std::ostringstream ss;

  ss << "[";
  for (int i = 0, last = auids.size() - 1; i < last; ++i)
  {
    ss << auids[i];
    ss << ",";
  }
  {
    ss << auids.back();
  }
  ss << "]";

  res = ss.str();

}

bool SocialConnection::SendTeam(__int64 auid, const nstl::vector<__int64>& team_auids)
{

  Http::HttpRequest request(serverName);

  request.AddQueryParam("action", "mm_allies");
  request.AddQueryParam("player", auid);
  nstl::string data("post_data=");

  {
    std::string s;
    parseAuids(team_auids, s);
    data += s.c_str();
  }


  GenerateRequest(request);
  SendRequest(request, data);

  return true;

}
void SocialConnection::Step()
{
  if (g_shareState == EShareState::START)
  {
    g_shareState = EShareState::NONE;

    EraseShareFileSafe();
   
    // Grab backbuffer and save as png (remove alpha prior to save)
    string path = GetFullFolderPath(NProfile::FOLDER_SCREENSHOTS);
    if (!NFile::DoesFolderExist(path))
    {
      NFile::CreatePath(path);
    }
    string screenshotName = NFile::Combine(path, screenshotFileName);

    IDirect3DDevice9* pDevice = Render::GetDevice();
    IDirect3DSurface9* pBB, *pDest;
    
    if(SUCCEEDED(pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBB)))
    {
      if(SUCCEEDED(pDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &pDest, NULL)))
      {
        RECT rect = { x, y, x + width, y + height };
        if(SUCCEEDED(D3DXLoadSurfaceFromSurface(pDest, NULL, NULL, pBB, NULL, needCrop ? &rect : NULL, D3DX_FILTER_NONE, 0)))
        {
          if(SUCCEEDED(D3DXSaveSurfaceToFile(screenshotName.c_str(), D3DXIFF_PNG, pDest, NULL, NULL)))
          {
            g_shareState = EShareState::WAIT_SCREENSHOT;
          }
          else
          {
            systemLog(NLogg::LEVEL_ASSERT) << "Creating share.png failed." << endl;
          }
        }
        pDest->Release();
      }
      pBB->Release();
    }
  }
  else if (g_shareState == EShareState::WAIT_SCREENSHOT)
  {
    string path = GetFullFolderPath(NProfile::FOLDER_SCREENSHOTS);
    if (NFile::DoesFolderExist(path))
    {
      string screenshotName = NFile::Combine(path, screenshotFileName);
      if (NFile::DoesFileExist(screenshotName))
      {
        NGameX::AdventureScreenLogic* advLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(NGameX::AdventureScreen::Instance()->GetLogic());
        if (advLogic)
        {
          string shareUrl = NGameX::AdventureScreen::Instance()->GetGSClientSettings().shareUrl;

          if (shareUrl.empty())
          {
            g_shareState = EShareState::NONE;
            return;
          }

          __int64 auidInt = advLogic->GetPlayerAuid();
          char auidBuff[65];
          _i64toa(auidInt, auidBuff, 10);
          string auid(auidBuff);
          string salt = shareUrl;
          string hashStr = auid+salt;
          memset(openUrl, 0, sizeof(openUrl));

      	  math::MD5Generator md5;
          md5.Start();
          md5.Update((const byte *)hashStr.c_str(), hashStr.size());
          md5.Stop();

          CURL *curl = curl_easy_init();
          if (curl)
          {
            struct curl_httppost *formpost=NULL;
            struct curl_httppost *lastptr=NULL;
            struct curl_slist *headers=NULL;
            headers = curl_slist_append(headers, "Content-Type: multipart/form-data");

            curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "auid",
               CURLFORM_COPYCONTENTS, auid.c_str(),
               CURLFORM_END);

            curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "sign",
               CURLFORM_COPYCONTENTS, md5.Get().ToString().c_str(),
               CURLFORM_END);
            
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "content",
	            CURLFORM_FILE, screenshotName.c_str(), CURLFORM_CONTENTTYPE,
	            "image/png", CURLFORM_END);

            curl_easy_setopt(curl, CURLOPT_URL, shareUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, openUrl);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl_formfree(formpost);
            curl_slist_free_all(headers);
          }

          if (strstr(openUrl, "http"))
            g_shareState = EShareState::WAIT_URL;
          else
            g_shareState = EShareState::NONE;
        }
      }
    }
  }
  else if (g_shareState == EShareState::WAIT_URL)
  {
    EraseShareFileSafe();

    // Find and pass the actual http string due a bug returning preceding chars in curl_to_string
    NFile::ExecuteFile(strstr(openUrl, "http"));
    g_shareState = EShareState::NONE;
    needCrop = false;
  }
}

void SocialConnection::Share()
{
  if (g_shareState == EShareState::NONE)
  {
    g_shareState = EShareState::START;
  }
}

void SocialConnection::Share(int _x, int _y, int _width, int _height)
{
  needCrop = true;
  x = _x; y = _y; width = _width; height = _height;
  Share();
}

void SocialConnection::OnProtectionError()
{
  Http::HttpRequest request(serverName);

  request.AddQueryParam("action", "protection_error");

  GenerateRequest(request);
  SendRequest(request);
}

}

NI_DEFINE_REFCOUNT(NGameX::ISocialConnection);
NI_DEFINE_REFCOUNT(NGameX::SocialConnection);

namespace
{
bool CreateComplaintCmd(const char *name, const vector<wstring> &params)
{
  if (params.size() == 4)
  {
    nstl::string param0;
    NStr::ToMBCS(&param0, params[0]);

    unsigned long toauid = NStr::ToULong(param0);
    int category = NStr::ToInt(params[1]);

    if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
    {
      NGameX::ISocialConnection* soc = pAdvScreen->GetSocialConnection();
      if (soc)
      {
        soc->CreateComplaint(toauid, category, params[2], params[3], 1, 2, 3, 4, 5, 6, 7, 8);
      }
    }
    return true;
  }

  systemLog(NLogg::LEVEL_MESSAGE) << "usage: " << name << " toauid category text log" << endl;
  return true;
}



bool ShareCmd(const char *name, const vector<wstring> &params)
{
  if (g_shareState == EShareState::NONE)
  {
    g_shareState = EShareState::START;
  }
  return true;
}
}

REGISTER_DEV_CMD(complaint_create, CreateComplaintCmd);
REGISTER_DEV_CMD(share, ShareCmd);