#pragma once

#include "BrowserWindow.h"
#include "Log.h"

struct BrowserController
{
  BrowserController()
  {
    m_stopOnRedir = L"pwlaunch://";
  }

  void OnInitialize(BrowserWindow* window)
  {
    if((LPWSTR)m_url)
      window->Navigate(m_url);
  }

  bool OnBeforeNavigate(BrowserWindow* window, const _bstr_t& url)
  {
    LOG("BrowserBN: %s", (LPCSTR)url);
    const wchar_t* urlChars = url;
    if (urlChars)
    {
      if (_wcsnicmp(urlChars, m_stopOnRedir.c_str(), m_stopOnRedir.length()) == 0)
      {
        m_finalUrl = urlChars  + m_stopOnRedir.length() + 2;
        window->Cleanup(IDOK);
        return true;
      }
    }
    return false;
  }

  bool OnNavigateComplete(BrowserWindow* window, const _bstr_t& url)
  {
    // LOG("BrowserControllerNC: %s", (LPCSTR)url);
    const wchar_t* urlChars = url;
    if (urlChars)
    {
      if (_wcsnicmp(urlChars, m_stopOnRedir.c_str(), m_stopOnRedir.length()) == 0)
      {
        m_finalUrl = urlChars  + m_stopOnRedir.length();
        window->Cleanup(IDOK);
        return true;
      }
    }
    return false;
  }

  std::wstring m_stopOnRedir;

  _bstr_t m_url;
  _bstr_t m_finalUrl;
};
