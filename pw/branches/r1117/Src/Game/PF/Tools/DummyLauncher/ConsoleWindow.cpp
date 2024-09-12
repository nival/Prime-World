#include "stdafx.h"
#include "ConsoleWindow.h"
#include "MainWindow.h"
#include "Application.h"
#include "Convert.h"

LRESULT ConsoleWindow::OnClose(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
  g_App->GetMainWindow().CloseConsole();
  return 0;
}

LRESULT ConsoleWindow::OnInitDialog(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
  DlgResize_Init();
  m_logWnd = GetDlgItem(IDC_LOG_EDIT);

  BOOL h;
  OnExecuteButton(0, 0, 0, h);

  return 0;
}

void ConsoleWindow::AddText(TextStyles style, const char* text)
{
  AddText(style, Convert::FromUTF8(text));
}

void ConsoleWindow::AddText(TextStyles style, const std::wstring& text)
{
  const wchar_t* prefix = L"";
  COLORREF clr = 0;
  switch(style)
  {
  case STYLE_FROM_CLIENT:
    prefix = L">>>\r\n";
    clr = RGB(0x33, 0x77, 0x33);
    break;
  case STYLE_FROM_SERVER:
    prefix = L"<<<\r\n";
    clr = RGB(0, 0, 0xff);
    break;
  case STYLE_FROM_SERVER_ERROR:
    prefix = L"<<<\r\n";
    clr = RGB(0xff, 0, 0);
    break;
  }
  AddTextInternal(0, prefix);
  AddTextInternal(clr, text.c_str());

  CHARRANGE cr;
  m_logWnd.GetSel(cr);

  AddTextInternal(0, L"\r\n");

  long pos = m_logWnd.GetTextLength();
  m_logWnd.SetSel(pos - 1, pos);

  m_logWnd.SendMessage(EM_SCROLLCARET, 0, 0);
}

void ConsoleWindow::AddTextInternal(COLORREF clr, const wchar_t* text)
{
  long pos = m_logWnd.GetTextLength();
  CHARFORMAT cf = { sizeof(CHARFORMAT) };
  cf.dwMask = CFM_COLOR;
  cf.dwEffects = 0;
  cf.crTextColor = clr;
  m_logWnd.SetSel(pos, pos + 1);
  m_logWnd.SetSelectionCharFormat(cf);
  m_logWnd.ReplaceSel(text);
}

void ConsoleWindow::AddText(TextStyles style, const Json::Value& parsedValue)
{
  std::strstream stream;
  Json::StyledStreamWriter writer;
  writer.write(stream, parsedValue);

  stream << (char)0;
  AddText(style, stream.rdbuf()->str());
}

LRESULT ConsoleWindow::OnExecuteButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled)
{
  return 1;
}
