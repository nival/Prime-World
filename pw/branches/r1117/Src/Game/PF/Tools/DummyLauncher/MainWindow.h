#pragma once

#include "resource.h"
#include "BrowserWindow.h"
#include "SocialNetInfo.h"

class MainWindow
: public CDialogImpl<MainWindow>
, public CDialogResize<MainWindow>
  , public CMessageFilter
{

  public:
  enum { IDD = IDD_MAIN_WINDOW };

  BEGIN_MSG_MAP(MainWindow)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnEditColor) // WM_CTLCOLORSTATIC, потому что EDIT-ы в дизабле
    COMMAND_ID_HANDLER(IDC_FB_AUTH_BUTTON, OnFbAuthButton)
    COMMAND_ID_HANDLER(IDC_FB_LOGIN_BUTTON, OnFbLoginButton)
    COMMAND_ID_HANDLER(IDC_ZZ_AUTH_BUTTON, OnZZAuthButton)
    COMMAND_ID_HANDLER(IDC_ZZ_LOGIN_BUTTON, OnZZLoginButton)
    COMMAND_ID_HANDLER(IDC_PWC_AUTH_BUTTON, OnPWCAuthButton)
    COMMAND_ID_HANDLER(IDC_OK_AUTH_BUTTON, OnOkAuthButton)
    COMMAND_ID_HANDLER(IDC_OK_LOGIN_BUTTON, OnOkLoginButton)
    COMMAND_ID_HANDLER(IDC_LOGOUT_BUTTON, OnLogoutButton)
    COMMAND_ID_HANDLER(IDC_START_BUTTON, OnStartClick)
    COMMAND_ID_HANDLER(IDC_CONSOLE_BUTTON, OnConsoleButtonClick)
    COMMAND_HANDLER(IDC_PWC_UID, CBN_SELCHANGE, OnCbnSelchangePwcUid)
    CHAIN_MSG_MAP(CDialogResize<MainWindow>)
  END_MSG_MAP()

  BEGIN_DLGRESIZE_MAP(MainWindow)
    DLGRESIZE_CONTROL(IDC_START_BUTTON, DLSZ_MOVE_X|DLSZ_MOVE_Y)
    DLGRESIZE_CONTROL(IDC_CMD_PRMS, DLSZ_SIZE_X|DLSZ_MOVE_Y)
    DLGRESIZE_CONTROL(IDC_FB_UID, DLSZ_SIZE_X)
    DLGRESIZE_CONTROL(IDC_FB_LOGIN_BUTTON, DLSZ_MOVE_X)
    DLGRESIZE_CONTROL(IDC_ZZ_UID, DLSZ_SIZE_X)
    DLGRESIZE_CONTROL(IDC_ZZ_LOGIN_BUTTON, DLSZ_MOVE_X)
    DLGRESIZE_CONTROL(IDC_PWC_UID, DLSZ_SIZE_X)
    DLGRESIZE_CONTROL(IDC_OK_UID, DLSZ_SIZE_X)
    DLGRESIZE_CONTROL(IDC_OK_LOGIN_BUTTON, DLSZ_MOVE_X)
    DLGRESIZE_CONTROL(IDC_PW_TOKEN, DLSZ_SIZE_X)
  END_DLGRESIZE_MAP()

  virtual BOOL PreTranslateMessage(MSG* pMsg);

  void TryAutoLogin();

  void ShowErrorMessage(const wchar_t* text);

  void CloseConsole();

  void SetServer(const std::wstring& newServer, bool resetModify = false) const;
  std::wstring GetServer() const;
  private:
  LRESULT OnClose(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
  LRESULT OnInitDialog(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);

  LRESULT OnEditColor(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);

  LRESULT OnFbAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);
  LRESULT OnFbLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  LRESULT OnZZAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);
  LRESULT OnZZLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  LRESULT OnPWCAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);
  LRESULT OnPWCLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  LRESULT OnOkAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);
  LRESULT OnOkLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  LRESULT OnLogoutButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  LRESULT OnStartClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
  LRESULT OnConsoleButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

  bool IsServerModified() const;
  bool CheckToken(const std::wstring& snid);

  void Logout();

  void LaunchApp();

  void ShowNewCmdLine();

  void UpdateUsersData();
  void UpdateSocNetData(int firstControl, const SocialNetInfo* socNet);

  enum SocNetStates
  {
    STATE_EMPTY = 0,
    STATE_NOT_AUTH,
    STATE_AUTH,
    STATE_ERROR_REFRESH,
  };

  void UpdateSocNetStatus(CWindow& labelWnd, SocNetStates state);

  int CreateSocNetItem(int cbID, const SocialNetInfo* socNet);
  int FindSocNetItem(int cbID, const SocialNetInfo* socNet);

  void TryLoginSocialNetwork(int controlId);
  void TryLoginSocialNetwork(SocialNetInfo* socNet);

  void FillUIDSCombos();
public:
  LRESULT OnCbnSelchangePwcUid(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
