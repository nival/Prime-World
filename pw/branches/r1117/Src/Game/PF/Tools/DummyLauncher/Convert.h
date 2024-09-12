#pragma once

struct Convert
{
	static std::wstring FormatString(const wchar_t* fmt, ...);

	static std::wstring EncodeUrl(const std::wstring& url);
	static std::wstring DecodeUrl(const std::wstring& url);
  static std::string ToUTF8(const wchar_t* str, int length = -1);
  static std::string ToUTF8(const std::wstring& str)
  {
    return ToUTF8(str.c_str(), -1);
  }
  static std::wstring FromUTF8(const char* str, int length = -1);
  static std::wstring FromUTF8(const std::string& str)
  {
    return FromUTF8(str.c_str(), -1);
  }
	static bool isCharUrlUnsafe(char ch);
	static wchar_t* Trim(wchar_t* line)
	{
		int len = wcslen(line);
		while(len > 0 && (line[len-1] == L' ' || line[len-1] == L'\t'))
		{
			len--;
			line[len] = 0;
		}
		int pos = 0;
		while(pos < len && (line[pos] == L' ' || line[pos] == L'\t'))
			pos++;
		return line + pos;
	}

  static char* Trim(char* line)
  {
    int len = strlen(line);
    while(len > 0 && (line[len-1] == ' ' || line[len-1] == '\t'))
    {
      len--;
      line[len] = 0;
    }
    int pos = 0;
    while(pos < len && (line[pos] == ' ' || line[pos] == '\t'))
      pos++;
    return line + pos;
  }

  static std::string MD5Hash(const char* data);

	static std::string VarToString(const _variant_t& value);
	static std::wstring VarToWString(const _variant_t& value);

  static std::string ExpandString(const std::string& str);

  static void ParseUrlParams(const std::string& str, StringsMap& result);
};
