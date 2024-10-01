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

	std::vector<int> GetTallentSet(const wchar_t* nickName, const char* heroName);
	std::string ConvertFromClassID(int id);
  WebLoginResponse GetNickName(const char* token);
};