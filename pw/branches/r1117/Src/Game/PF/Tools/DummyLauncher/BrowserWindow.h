#pragma once
#include "resource.h"

struct BrowserController;

class BrowserWindow : public DWebBrowserEvents2
{
public:
  BrowserWindow(BrowserController* controller = NULL);

  void SetController(BrowserController* controller)
  {
    m_controller = controller;
  }

  virtual ~BrowserWindow();

  int Run();
  void Cleanup(int code);
  void Navigate(const _bstr_t& url);

  virtual BOOL PreTranslateMessage(MSG* pMsg) { return FALSE; }
  // DWebBrowserEvents2
  // IUnknown
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
  virtual ULONG STDMETHODCALLTYPE AddRef() { return 1; }
  virtual ULONG STDMETHODCALLTYPE Release() { return 0; }

  // IDispatch
  virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* pctinfo) { pctinfo = 0; return S_OK; }
  virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) { return E_NOTIMPL; }
  virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) { return E_NOTIMPL; }
  virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

private:
  DWORD m_dwAdvise;
  IWebBrowser2Ptr m_browser;
  BrowserController* m_controller;
};
