#pragma once

#include "resource.h"

enum TextStyles
{
  STYLE_FROM_CLIENT,
  STYLE_FROM_SERVER,
  STYLE_FROM_SERVER_ERROR,
};

class ConsoleWindow
  : public CDialogImpl<ConsoleWindow>
  , public CDialogResize<ConsoleWindow>
//  , public CMessageFilter
{

public:
  enum { IDD = IDD_CONSOLE };

  BEGIN_MSG_MAP(ConsoleWindow)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_ID_HANDLER(IDC_EXECUTE_BUTTON, OnExecuteButton)
    CHAIN_MSG_MAP(CDialogResize<ConsoleWindow>)
  END_MSG_MAP()

  BEGIN_DLGRESIZE_MAP(ConsoleWindow)
    DLGRESIZE_CONTROL(IDC_LOG_EDIT, DLSZ_SIZE_X|DLSZ_SIZE_Y)
    DLGRESIZE_CONTROL(IDC_COMMAND_EDIT, DLSZ_SIZE_X|DLSZ_MOVE_Y)
    DLGRESIZE_CONTROL(IDC_EXECUTE_BUTTON, DLSZ_MOVE_X|DLSZ_MOVE_Y)
  END_DLGRESIZE_MAP()

  void AddText(TextStyles style, const std::wstring& text);
  void AddText(TextStyles style, const char* text);
  void AddText(TextStyles style, const Json::Value& parsedValue);
private:
  void AddTextInternal(COLORREF clr, const wchar_t* text);
  LRESULT OnClose(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
  LRESULT OnInitDialog(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);

  LRESULT OnExecuteButton(WORD code, WORD wId, HWND hCtrl, BOOL& handled);

  CRichEditCtrl m_logWnd;
};