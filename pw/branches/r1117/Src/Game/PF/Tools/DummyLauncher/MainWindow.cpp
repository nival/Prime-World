#include "stdafx.h"
#include "MainWindow.h"
#include "Application.h"
#include "log.h"
#include "Convert.h"
#include "HttpRequest.h"
#include "UsersInfo.h"
#include "PWCNetInfo.h"

LRESULT MainWindow::OnClose(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
  DestroyWindow();
  PostQuitMessage(0);
  return 0;
}

LRESULT MainWindow::OnInitDialog(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
  DlgResize_Init();

  CFontHandle font( (HFONT)SendDlgItemMessage(IDC_FB_STATIC, WM_GETFONT) );
  LOGFONT lf;
  font.GetLogFont(&lf);
  lf.lfWeight = FW_BOLD;

  CFontHandle newFont;
  newFont.CreateFontIndirect(&lf);

  SendDlgItemMessage( IDC_FB_STATIC, WM_SETFONT, (WPARAM)(HFONT)newFont );
  SendDlgItemMessage( IDC_OK_STATIC, WM_SETFONT, (WPARAM)(HFONT)newFont );
  SendDlgItemMessage( IDC_PW_STATIC, WM_SETFONT, (WPARAM)(HFONT)newFont );
  SendDlgItemMessage( IDC_ZZ_STATIC, WM_SETFONT, (WPARAM)(HFONT)newFont );
  SendDlgItemMessage( IDC_PWC_STATIC, WM_SETFONT, (WPARAM)(HFONT)newFont );

  CButton btn(GetDlgItem(IDC_CONSOLE_BUTTON));
  btn.SetCheck(1);

  FillUIDSCombos();

  return 0;
}

LRESULT MainWindow::OnEditColor(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
  CWindow edit((HWND)lParam);
  LONG_PTR value = edit.GetWindowLongPtr(GWLP_USERDATA);
  CDCHandle dc((HDC)wParam);
  switch((SocNetStates)value)
  {
    case STATE_EMPTY:
    case STATE_NOT_AUTH:
      dc.SetTextColor(0);
      break;
    case STATE_AUTH:
      dc.SetTextColor(0x00aa00);
      break;
    case STATE_ERROR_REFRESH:
      dc.SetTextColor(0x0000FF);
      break;
  }
  dc.SetBkMode(TRANSPARENT);
  return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
}

LRESULT MainWindow::OnFbAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  wchar_t cookieData[4096];
  DWORD size = 4096;

  BOOL res = InternetGetCookieEx(L"http://facebook.com", NULL, cookieData, &size, INTERNET_COOKIE_HTTPONLY, NULL);
  cookieData[size] = 0;

  wchar_t* nextToken = NULL;
  wchar_t* token = wcstok_s( cookieData, L";", &nextToken );

  while(token)
  {
    token = Convert::Trim(token);

    if ( _wcsnicmp(token, L"locale=", 7) != 0 && _wcsnicmp(token, L"c_user=", 7) != 0 &&
         _wcsnicmp(token, L"lu=", 3) != 0 && _wcsnicmp(token, L"sct=", 4) != 0 )
    {
      wchar_t* pos = wcschr( token, L'=' );
      if (pos)
      {
        *pos = 0;
        res = InternetSetCookieEx(L"http://facebook.com", token, L"", INTERNET_COOKIE_HTTPONLY, NULL);
      }
    }
    token = wcstok_s( NULL, L";", &nextToken );
  }

  SocialNetInfoPtr sn = g_App->GetUsersInfo().GetFromSns("fb");
  if(!sn)
    sn = g_App->GetUsersInfo().CreateSocialNet("fb");

  if(sn->Authorize() )
  {
    g_App->GetUsersInfo().OnAuthorized(sn);
  }

  UpdateUsersData();

  return 1;
}

LRESULT MainWindow::OnZZAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  SocialNetInfoPtr sn = g_App->GetUsersInfo().GetFromSns("zzma");
  if(!sn)
    sn = g_App->GetUsersInfo().CreateSocialNet("zzma");

  if(sn->Authorize() )
  {
    g_App->GetUsersInfo().OnAuthorized(sn);
  }

  UpdateUsersData();

  return 1;
}

BOOL MainWindow::PreTranslateMessage(MSG* pMsg)
{
  if(!IsWindow())
    return FALSE;
  if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
     (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
    return FALSE;
  return IsDialogMessage(pMsg);
}

LRESULT MainWindow::OnOkAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  InternetSetCookieEx(L"http://www.odnoklassniki.ru", L"AUTHCODE", L"", INTERNET_COOKIE_HTTPONLY, 0);
  InternetSetCookieEx(L"http://odnoklassniki.ru", L"AUTHCODE", L"", INTERNET_COOKIE_HTTPONLY, 0);
  InternetSetCookieEx(L"http://www.odnoklassniki.ru", L"JSESSIONID", L"", INTERNET_COOKIE_HTTPONLY, 0);
  InternetSetCookieEx(L"http://odnoklassniki.ru", L"JSESSIONID", L"", INTERNET_COOKIE_HTTPONLY, 0);

  SocialNetInfoPtr sn = g_App->GetUsersInfo().GetFromSns("ok");
  if(!sn)
    sn = g_App->GetUsersInfo().CreateSocialNet("ok");

  if(sn->Authorize())
  {
    g_App->GetUsersInfo().OnAuthorized(sn);
  }

  UpdateUsersData();

  return 1;
}

LRESULT MainWindow::OnPWCAuthButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  SocialNetInfoPtr sn = g_App->GetUsersInfo().GetFromSns("pwc");
  if(!sn)
    sn = g_App->GetUsersInfo().CreateSocialNet("pwc");

  CEdit pwcLogin(GetDlgItem(IDC_PWC_UID));
  std::wstring login(L"");
  login.resize(pwcLogin.GetWindowTextLength() + 1);
  pwcLogin.GetWindowText(LPTSTR(&login[0]), login.size());

  CEdit pwcPassword(GetDlgItem(IDC_PWC_PASSWORD));
  std::wstring password(L"");
  password.resize(pwcPassword.GetWindowTextLength() + 1);
  pwcPassword.GetWindowText(LPTSTR(&password[0]), password.size());

  PWCNetInfo *p = static_cast<PWCNetInfo*>(&(*sn));
  if(p->Authorize(login, password))
  {
    g_App->GetUsersInfo().OnAuthorized(sn);
  }

  UpdateUsersData();

  return 1;
}

LRESULT MainWindow::OnLogoutButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  Logout();
  return 1;
}

void MainWindow::Logout()
{
  if(!IsServerModified() || GetServer().empty())
    SetServer(L"", true);
  g_App->GetUsersInfo().Logout();
  UpdateUsersData();
}

void MainWindow::ShowErrorMessage(const wchar_t* text)
{
  if(!IsWindowVisible())
  {
    g_App->GetConsole().ShowWindow(SW_SHOW);
    ShowWindow(SW_SHOW);
  }
  MessageBox(text, L"Ошибка", MB_OK | MB_ICONERROR);
}

LRESULT MainWindow::OnStartClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  LaunchApp();
  return 1;
}

void MainWindow::LaunchApp()
{
  UsersInfo& userData = g_App->GetUsersInfo();
  if(userData.IsLoggedIn())
  {

    /*

      Arguments: {
      {
      --snid | pw |
      --snuid | 298 |
      --server | login0 |
      --sntoken | 71fe9e0358e0ebfe802ff31162450b0b |
      --secret | 613c18c2339b2caa70b1d2f4dbb43777 |
      --needqueue |
      ver | 0.0.0 |
      }

    */
    
    std::string strArgs = "--snid pw --snuid " + userData.GetAUID();
    if(!userData.GetToken().empty())
    {
      strArgs += " --sntoken " + userData.GetToken();
      strArgs += " --secret " + Convert::MD5Hash(userData.GetFirstLoggedSNS()->GetToken());
    }
    if(!userData.GetServer().empty())
      strArgs += " --server " + Convert::ToUTF8(GetServer());

    std::string loggedInSN = userData.GetFirstLoggedSNS()->GetSnID();
    if (loggedInSN == "pwc")
    {
      strArgs += " --needqueue ";
    }
    //reqPrms["ver"] = Convert::ToUTF8(g_App->GetVars().GetProtocolVersion());
    strArgs += " ver " + Convert::ToUTF8(g_App->GetVars().GetProtocolVersion());

    std::wstring args = Convert::FromUTF8(strArgs) + L" " + g_App->GetVars().GetExeArguments();
    std::wstring workDir = g_App->GetVars().GetWorkDir();
    std::wstring exeName = g_App->GetConfig().GetExeName();

    LOG("Executing: exeName=%s\r\n\tworkDir=%s\r\n\targs=%s", Convert::ToUTF8(exeName).c_str(), Convert::ToUTF8(workDir).c_str(), Convert::ToUTF8(args).c_str());

    HINSTANCE result = ShellExecute(m_hWnd, L"open",
                                    (workDir + L"\\" + exeName).c_str(),
                                    args.c_str(),
                                    workDir.c_str(),
                                    SW_SHOWNORMAL);

    std::string workDirUtf8 = Convert::ToUTF8(workDir);
    std::string exeNameUtf8 = Convert::ToUTF8(exeName);
    if((int)result <= 32)
    {
      switch((int)result)
      {
        case 0:
        case SE_ERR_OOM:
          ShowError(L"Exec: Not enough memory: %s", Convert::FromUTF8(exeNameUtf8).c_str());
          break;
        case ERROR_FILE_NOT_FOUND:
          ShowError(L"Exec: File not found: %s\\%s", Convert::FromUTF8(workDirUtf8).c_str(), Convert::FromUTF8(exeNameUtf8).c_str());
          break;
        case ERROR_PATH_NOT_FOUND:
          ShowError(L"Exec: Path not found: %s", Convert::FromUTF8(workDirUtf8).c_str());
          break;
        case ERROR_BAD_FORMAT:
          ShowError(L"Exec: Wrong file format: %s\\%s", Convert::FromUTF8(workDirUtf8).c_str(), Convert::FromUTF8(exeNameUtf8).c_str());
          break;
        case SE_ERR_ACCESSDENIED:
          ShowError(L"Exec: Access denied: %s", Convert::FromUTF8(exeNameUtf8).c_str());
          break;
        case SE_ERR_SHARE:
          ShowError(L"Exec: Sharing violation occurred: %s", Convert::FromUTF8(exeNameUtf8).c_str());
          break;
        default:
          ShowError(L"Exec: Unknown error (0x08x): %s\\%s", (unsigned int)result, Convert::FromUTF8(workDirUtf8).c_str(), Convert::FromUTF8(exeNameUtf8).c_str());
          break;
      }
    }
    else
    {
      LOG("Exec: Process started: %s\\%s", workDirUtf8.c_str(), exeNameUtf8.c_str());
    }

    if(!IsWindowVisible())
      PostMessage(WM_CLOSE);
  }
}

void MainWindow::TryAutoLogin()
{
  const CommandLine::SnUserIDsVector& cmdLineUids = g_App->GetCommandLine().GetUIDs();
  SocialNetInfoPtr firstSn;
  for(size_t i = 0; i < cmdLineUids.size(); i++)
  {
    const CommandLine::SnUserID& curUID = cmdLineUids[i];
    SocialNetInfoPtr sn = g_App->GetUsersInfo().Find(curUID.snid, curUID.snuid);
    if(sn == NULL)
      sn = g_App->GetUsersInfo().FindByName(curUID.snid, curUID.snuid);

    if(sn)
    {
      firstSn = sn;
      if(sn->RefreshUserData())
      {
        g_App->GetUsersInfo().OnAuthorized(sn);
        break;
      }
    }
  }

  if(!g_App->GetUsersInfo().IsLoggedIn() && firstSn)
  {
    UpdateSocNetData(firstSn->GetFirstControlID(), firstSn);
  }
  else
  {
    UpdateUsersData();
  }

  if(g_App->GetCommandLine().GetForceShowUI())
  {
    g_App->GetConsole().ShowWindow(SW_SHOW);
    ShowWindow(SW_SHOW);
  }
  else
  {
    if(g_App->GetUsersInfo().IsAllLoggedIn() || (g_App->GetUsersInfo().IsLoggedIn() && g_App->GetCommandLine().GetSilent()))
    {
      LaunchApp();
    }
    else
    {
      g_App->GetConsole().ShowWindow(SW_SHOW);
      ShowWindow(SW_SHOW);
    }
  }
}

void MainWindow::ShowNewCmdLine()
{
  std::wstring prms = Convert::FromUTF8(g_App->GetUsersInfo().MakeCmdLine());
  GetDlgItem(IDC_CMD_PRMS).SetWindowText(prms.c_str());
}

void MainWindow::UpdateUsersData()
{
  UsersInfo& info = g_App->GetUsersInfo();
  if(info.IsLoggedIn())
  {
    SocialNetInfoPtr sn = info.GetFromSns("fb");
    UpdateSocNetData(IDC_FB_UID, sn);
    sn = info.GetFromSns("ok");
    UpdateSocNetData(IDC_OK_UID, sn);
    sn = info.GetFromSns("zzma");
    UpdateSocNetData(IDC_ZZ_UID, sn);
    sn = info.GetFromSns("pwc");
    UpdateSocNetData(IDC_PWC_UID, sn);
  }
  else
  {
    UpdateSocNetData(IDC_FB_UID, NULL);
    UpdateSocNetData(IDC_OK_UID, NULL);
    UpdateSocNetData(IDC_ZZ_UID, NULL);
    UpdateSocNetData(IDC_PWC_UID, NULL);
  }

  ShowNewCmdLine();

  CEdit edit = GetDlgItem(IDC_AUID);
  edit.SetWindowText(Convert::FromUTF8(info.GetAUID()).c_str());
  edit = GetDlgItem(IDC_PW_TOKEN);
  edit.SetWindowText(Convert::FromUTF8(info.GetToken()).c_str());
}

void MainWindow::UpdateSocNetData(int firstControl, const SocialNetInfo* socNet)
{
  CComboBox cb = GetDlgItem(firstControl);
  CWindow infoLabel = GetDlgItem(firstControl + 3);
  int enableWindows = 0;
  if(g_App->GetUsersInfo().IsLoggedIn() || socNet)
  {
    enableWindows = g_App->GetUsersInfo().IsLoggedIn() ? 0 : 1;
    if(socNet)
    {
      int i = FindSocNetItem(firstControl, socNet);
      if(i < 0)
        i = CreateSocNetItem(firstControl, socNet);

      if(socNet->IsLoggedIn())
      {
        if(g_App->GetUsersInfo().IsLoggedIn())
          UpdateSocNetStatus(infoLabel, STATE_AUTH);
        else
          UpdateSocNetStatus(infoLabel, STATE_NOT_AUTH);
      }
      else
      {
        UpdateSocNetStatus(infoLabel, STATE_ERROR_REFRESH);
        enableWindows = 1;
      }

      int size = cb.GetLBTextLen(i);
      std::string text;
      if(size > 0)
      {
        std::vector<wchar_t> textBuffer(size + 1);
        size = cb.GetLBText(i, &textBuffer[0]);
        textBuffer[size] = 0;
        text = Convert::ToUTF8(&textBuffer[0]);
      }
      if(text != socNet->GetDisplayName())
      {
        cb.DeleteString(i);
        i = CreateSocNetItem(firstControl, socNet);
      }
      cb.SetCurSel(i);
    }
    else
    {
      UpdateSocNetStatus(infoLabel, STATE_EMPTY);
      cb.SetCurSel(-1);
    }
  }
  else
  {
    UpdateSocNetStatus(infoLabel, STATE_NOT_AUTH);
//    cb.SetCurSel(-1);
    enableWindows = 1;
  }
  for(int i = 0; i < 3; i++)
    GetDlgItem(firstControl + i).EnableWindow(enableWindows);
  infoLabel.RedrawWindow();
}

void MainWindow::UpdateSocNetStatus(CWindow& labelWnd, SocNetStates state)
{
  const wchar_t* txt = L"";
  switch(state)
  {
    case STATE_AUTH:
      txt = L"Авторизован";
      break;
    case STATE_NOT_AUTH:
      txt = L"Не авторизован";
      break;
    case STATE_ERROR_REFRESH:
      txt = L"Не удалось получить токен";
      break;
  }
  labelWnd.SetWindowLongPtr(GWLP_USERDATA, state);
  labelWnd.SetWindowText(txt);
}

int MainWindow::CreateSocNetItem(int cbID, const SocialNetInfo* socNet)
{
  CComboBox cb = GetDlgItem(cbID);
  std::wstring name = Convert::FromUTF8(socNet->GetDisplayName());
  int idx = cb.InsertString(cb.GetCount(), name.c_str());
  cb.SetItemDataPtr(idx, (void*)socNet);

  return idx;
}

int MainWindow::FindSocNetItem(int cbID, const SocialNetInfo* socNet)
{
  CComboBox cb = GetDlgItem(cbID);
  int count = cb.GetCount();
  for(int i = 0; i < count; i++)
  {
    const SocialNetInfo* sn = (const SocialNetInfo*)cb.GetItemDataPtr(i);
    if(sn == socNet)
      return i;
  }
  return -1;
}

void MainWindow::FillUIDSCombos()
{
  const UsersInfo::SocialNetInfosVector& uids = g_App->GetUsersInfo().GetUsersCache();
  for(size_t i = 0; i < uids.size(); i++)
  {
    const SocialNetInfo* sn = uids[i];
    std::string name = sn->GetSnID();
    if(name == "fb")
      CreateSocNetItem(IDC_FB_UID, sn);
    else if(name == "ok")
      CreateSocNetItem(IDC_OK_UID, sn);
    else if(name == "zzma")
      CreateSocNetItem(IDC_ZZ_UID, sn);
    else if(name == "pwc")
      CreateSocNetItem(IDC_PWC_UID, sn);
  }
}

LRESULT MainWindow::OnZZLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  TryLoginSocialNetwork(IDC_ZZ_UID);
  return 1;
}

LRESULT MainWindow::OnFbLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  TryLoginSocialNetwork(IDC_FB_UID);
  return 1;
}

LRESULT MainWindow::OnOkLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  TryLoginSocialNetwork(IDC_OK_UID);
  return 1;
}

LRESULT MainWindow::OnPWCLoginButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  TryLoginSocialNetwork(IDC_PWC_UID);
  return 1;
}

void MainWindow::TryLoginSocialNetwork(int controlId)
{
  CComboBox cb = GetDlgItem(controlId);
  int idx = cb.GetCurSel();
  if(idx >= 0)
  {
    SocialNetInfo* sn = static_cast<SocialNetInfo*>(cb.GetItemDataPtr(idx));
    TryLoginSocialNetwork(sn);
  }
}

void MainWindow::TryLoginSocialNetwork(SocialNetInfo* socNet)
{
  if (!socNet)
    return;

  if(socNet->RefreshUserData())
  {
    g_App->GetUsersInfo().OnAuthorized(socNet);
    UpdateUsersData();
  }
  else
  {
    UpdateSocNetData(socNet->GetFirstControlID(), socNet);
  }
}

LRESULT MainWindow::OnConsoleButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  CButton consoleBtn(GetDlgItem(IDC_CONSOLE_BUTTON));
  g_App->GetConsole().ShowWindow(consoleBtn.GetCheck() ? SW_SHOW : SW_HIDE);
  return 1;
}

void MainWindow::CloseConsole()
{
  CButton consoleBtn(GetDlgItem(IDC_CONSOLE_BUTTON));
  consoleBtn.SetCheck(0);
  BOOL tmpB = false;
  OnConsoleButtonClick(0, 0, 0, tmpB);
}

void MainWindow::SetServer(const std::wstring& newServer, bool resetModify) const
{
  CEdit srvEdit(GetDlgItem(IDC_SERVER_EDIT));
  BOOL modified = srvEdit.GetModify();
  srvEdit.SetWindowText(newServer.c_str());
  if(resetModify)
    srvEdit.SetModify(0);
  else
    srvEdit.SetModify(modified);
}

std::wstring MainWindow::GetServer() const
{
  CEdit srvEdit(GetDlgItem(IDC_SERVER_EDIT));

  std::vector<wchar_t> srvText(srvEdit.GetWindowTextLength() + 1);
  srvEdit.GetWindowText(&srvText[0], srvText.size());
  return &srvText[0];
}

bool MainWindow::IsServerModified() const
{
  CEdit srvEdit(GetDlgItem(IDC_SERVER_EDIT));
  return srvEdit.GetModify() != 0;
}

LRESULT MainWindow::OnCbnSelchangePwcUid(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  CComboBox cb = GetDlgItem(IDC_PWC_UID);
  int idx = cb.GetCurSel();
  if(idx >= 0)
  {
    SocialNetInfo* sn = static_cast<SocialNetInfo*>(cb.GetItemDataPtr(idx));
    CEdit passBox = GetDlgItem(IDC_PWC_PASSWORD);
    passBox.SetWindowText(LPCTSTR(Convert::FromUTF8(static_cast<PWCNetInfo*>(sn)->GetPass()).c_str()));
  }
  return 0;
}
