#include "stdafx.h"
#include "Convert.h"
#include "md5.h"
#include "Application.h"

std::wstring Convert::FormatString(const wchar_t* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	wchar_t buffer[2048];
	vswprintf(buffer, 2048, fmt, args);
	va_end(args);
	return buffer;
}

std::wstring Convert::EncodeUrl(const std::wstring& url)
{
	std::string utf8Str = ToUTF8(url.c_str());
	size_t len = utf8Str.length();
	std::vector<char> resultData;
	resultData.reserve(len);
	char buff[10] = {'%'};
	for(size_t i = 0; i < len; i++)
	{
		const char& ch = utf8Str[i];
		if(isCharUrlUnsafe(ch))
		{
			sprintf_s(buff + 1, 9, "%02X", (int)(unsigned char)ch);
			resultData.insert(resultData.end(), buff, buff + 3);
		}
		else
		{
			resultData.push_back(ch);
		}
	}
	resultData.push_back(0);

	return FromUTF8(&resultData[0]);
}

std::wstring Convert::DecodeUrl(const std::wstring& url)
{
	std::string utf8Str = ToUTF8(url.c_str());
	size_t len = utf8Str.length();
	std::vector<char> resultData;
	resultData.reserve(len);
	char buff[3] = {0};
	for(size_t i = 0; i < len; i++)
	{
		const char& ch = utf8Str[i];
		if(ch == '%')
		{
			buff[0] = utf8Str[++i];
			buff[1] = utf8Str[++i];
			int v = 0;
			sscanf_s(buff, "%x", &v);
			resultData.push_back((char)(unsigned char)v);
		}
		else
		{
			resultData.push_back(ch);
		}
	}
	resultData.push_back(0);

	return FromUTF8(&resultData[0]);
}

std::string Convert::ToUTF8(const wchar_t* str, int length)
{
	if (!str)
		return "";
	size_t size = (size_t)::WideCharToMultiByte( CP_UTF8, 0, str, length, NULL, 0, NULL, NULL );
	std::vector<char> result(size + 1, 0);
	::WideCharToMultiByte( CP_UTF8, 0, str, length, &result[0], size + 1, NULL, NULL );
	return &result[0];
}

std::wstring Convert::FromUTF8(const char* str, int length)
{
	if (!str)
		return L"";
	int size = ::MultiByteToWideChar(CP_UTF8, 0, str, length, NULL, 0);
	std::vector<wchar_t> result(size + 1, 0);
	::MultiByteToWideChar(CP_UTF8, 0, str, length, &result[0], size + 1);
	return &result[0];
}

bool Convert::isCharUrlUnsafe(char ch)
{
	static const char* unsafeChars = "\"<>%\\^[]`+$,@:;/!#?=&";

	if( strchr(unsafeChars, ch) )
		return true;

	return (ch < 32 || ch > 123);
}

std::string Convert::MD5Hash(const char* data)
{
	MD5 md5;
	return md5.digestString(data);
}

std::string Convert::VarToString(const _variant_t& value)
{
	switch( value.vt )
	{
	case VT_NULL:
		return "VT_NULL";
	case VT_EMPTY:
		return "VT_EMPTY";
	default:
		return (LPCSTR)_bstr_t(value);
	}
}

std::wstring Convert::VarToWString(const _variant_t& value)
{
	switch( value.vt )
	{
	case VT_NULL:
		return L"VT_NULL";
	case VT_EMPTY:
		return L"VT_EMPTY";
	default:
		return (LPCWSTR)_bstr_t(value);
	}
}

std::string Convert::ExpandString(const std::string& str)
{
  std::string result;
  size_t pos = 0;
  while(str[pos])
  {
    size_t nextPos = str.find('{', pos);
    if(nextPos == std::string::npos)
      break;
    size_t endPos = str.find('}', nextPos + 1);
    if(endPos == std::string::npos)
      break;
    result += str.substr(pos, nextPos - pos);
    std::string valueName = str.substr(nextPos + 1, endPos - nextPos - 1);
    const char* value = g_App->GetConfig().GetValue(valueName);
    if(value)
      result += value;
    else
      result += str.substr(nextPos, endPos - nextPos + 1);
    pos = endPos + 1;
  }
  result += str.substr(pos);
  return result;
}

void Convert::ParseUrlParams(const std::string& paramsStr, StringsMap& result)
{
  std::string str = paramsStr;
  size_t pos = str.find_first_of("?#&", 0);
  size_t eqPos = str.find('=', 0);
  if(eqPos < pos)
  {
    str = "#" + paramsStr;
    pos = 0;
  }
  while(pos != std::string::npos)
  {
    while (!isalpha(str[pos]) && pos < str.length())
      pos++;

    eqPos = str.find('=', pos);
    if(eqPos == std::string::npos)
      break;
    std::string name = str.substr(pos, eqPos - pos);
    pos = str.find_first_of("?#&", eqPos + 1);
    std::string value = (pos == std::string::npos) ? str.substr(eqPos + 1) : str.substr(eqPos + 1, pos - eqPos - 1);
    result[name] = value;
  }
}
