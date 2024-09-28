#pragma once

#ifndef INTERNET_COOKIE_HTTPONLY
#define INTERNET_COOKIE_HTTPONLY 0x00002000
#endif

_COM_SMARTPTR_TYPEDEF(IWebBrowser2, __uuidof(IWebBrowser2));
//_COM_SMARTPTR_TYPEDEF(IXMLHTTPRequest, __uuidof(IXMLHTTPRequest));

typedef std::map<std::wstring, std::wstring> WStringsMap;
typedef std::vector<std::wstring> WStringsVector;
typedef std::vector<char> CharsVector;
typedef std::map<std::string, std::string> StringsMap;
typedef std::vector<std::string> StringsVector;

#include "RefCountObject.h"
