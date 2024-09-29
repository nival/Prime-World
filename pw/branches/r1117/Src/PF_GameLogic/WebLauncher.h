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
public:
	WebLauncherPostRequest();
	~WebLauncherPostRequest();

	std::vector<int> GetTallentSet(const wchar_t* nickName, const char* heroName);
	std::string ConvertFromClassID(int id);
};