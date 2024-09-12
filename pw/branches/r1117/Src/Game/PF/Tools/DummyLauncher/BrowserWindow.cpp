#include "stdafx.h"
#include "BrowserWindow.h"
#include "Application.h"
#include "BrowserController.h"

BrowserWindow::BrowserWindow(BrowserController* controller)
  : m_controller(controller)
{
}

BrowserWindow::~BrowserWindow()
{
  if (m_browser) {
    AtlUnadvise(m_browser, DIID_DWebBrowserEvents2, m_dwAdvise);
    m_browser->Quit();
  }
}

int BrowserWindow::Run()
{
  HRESULT hr = 0;

  hr = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER,
                        IID_IWebBrowser2, (void**)&m_browser);
  if (hr != S_OK) {
    return IDABORT;
  }

  AtlAdvise(m_browser, (DWebBrowserEvents2*)this, DIID_DWebBrowserEvents2, &m_dwAdvise);
  // basic setup to get a pristine browser window
  m_browser->put_Silent(VARIANT_TRUE);
  m_browser->put_AddressBar(VARIANT_FALSE);
  m_browser->put_MenuBar(VARIANT_FALSE);
  m_browser->put_StatusBar(VARIANT_FALSE);
  m_browser->put_ToolBar(FALSE);

  // ready to navigate to the initial URL
  if(m_controller)
    m_controller->OnInitialize(this);
  else {
    return IDABORT;
  }

  // if everything is ok, set the window title
  // and show it
  HWND IEWindow = 0;
  m_browser->get_HWND((SHANDLE_PTR*)&IEWindow);
  SetWindowTextW(IEWindow, L"Авторизация");
  m_browser->put_Visible(VARIANT_TRUE);
  BringWindowToTop(IEWindow);

  CMessageLoop* loop = g_App->GetMainMessageLoop();
  return loop->Run();
}

void BrowserWindow::Navigate(const _bstr_t& url)
{
  _variant_t urlPrm(url);
  _variant_t vtEmpty;
  m_browser->Navigate2(&urlPrm, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
}

HRESULT STDMETHODCALLTYPE BrowserWindow::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = (IUnknown*)(DWebBrowserEvents2*)this;
  else if (riid == IID_IDispatch)
    *ppvObject = (IDispatch*)(DWebBrowserEvents2*)this;
  else if (riid == DIID_DWebBrowserEvents)
    *ppvObject = (DWebBrowserEvents*)this;
  else if (riid == DIID_DWebBrowserEvents2)
    *ppvObject = (DWebBrowserEvents2*)this;
  else
    *ppvObject = NULL;
  if (*ppvObject)
  {
    AddRef();
    return S_OK;
  }
  return E_NOINTERFACE;
}

HRESULT STDMETHODCALLTYPE BrowserWindow::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
  switch(dispIdMember)
  {
    case DISPID_BEFORENAVIGATE2:
    {
      _bstr_t url = pDispParams->rgvarg[pDispParams->cArgs - 2];
      if(m_controller)
        pDispParams->rgvarg[0].boolVal = m_controller->OnBeforeNavigate(this, url) ? VARIANT_TRUE : VARIANT_FALSE;
      else
        pDispParams->rgvarg[0].boolVal = VARIANT_FALSE;
    }
    return S_OK;
    case DISPID_ONQUIT:
    {
      Cleanup(IDCANCEL);
    }
    return S_OK;
    case DISPID_TITLECHANGE:
    {
      // Make the windows title fake-constant, instead of updating it to the current URL
      HWND IEWindow = 0;
      m_browser->get_HWND((SHANDLE_PTR*)&IEWindow);
      SetWindowTextW(IEWindow, L"Авторизация");
    }
    return S_OK;
    case DISPID_NAVIGATECOMPLETE2:
    {
      _bstr_t url = pDispParams->rgvarg[pDispParams->cArgs - 2];
      LOG("BrowserNC: %s", (LPCSTR)url);

      if(m_controller)
        pDispParams->rgvarg[0].boolVal = m_controller->OnNavigateComplete(this, url) ? VARIANT_TRUE : VARIANT_FALSE;
      else
        pDispParams->rgvarg[0].boolVal = VARIANT_FALSE;
    }
    return S_OK;
    default:
      return S_FALSE;
  }
  return S_FALSE;
}

void BrowserWindow::Cleanup(int code)
{
  m_browser->Stop();
  m_browser->put_Visible(VARIANT_FALSE);
  ::PostQuitMessage(code);
}
