#pragma once
#include <vector>
#include <Windows.h>
#include <Wininet.h>
#include <map>
#include <string>

class WebLauncherPostRequest
{
	HINTERNET hInternet;
	HINTERNET hConnect;
	HINTERNET hRequest;

	std::map<std::string, int> characterMap;
	std::map<int, std::string> classTalentMap;

	std::vector<int> keysClassTalent;
public:
	WebLauncherPostRequest();
	~WebLauncherPostRequest();

  enum LoginResponse {
    LoginResponse_OK,
    LoginResponse_FAIL,
    LoginResponse_OFFLINE, // Not safe
  };

  struct WebLoginResponse {
    std::string response;
    LoginResponse retCode;
  };

  struct TalentWebData {
    int webTalentId;
    int activeSlot; // negative = smart cast
    bool isSmartCast;
  };

  struct WebUserData {
    std::vector<TalentWebData> talents;
  };

	std::vector<TalentWebData> GetTallentSet(const wchar_t* nickName, const char* heroName);
  std::map<std::wstring, WebUserData> WebLauncherPostRequest::GetUsersData(const std::vector<std::wstring>& nickNames, const std::vector<std::string>& heroNames);
	std::string ConvertFromClassID(int id);
  WebLoginResponse GetNickName(const char* token);
  std::string WebLauncherPostRequest::SendPostRequest(const std::string& jsonData);

};

extern std::string GetSkinByHeroPersistentId(const std::string& heroId, int someValue);