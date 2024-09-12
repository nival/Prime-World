#include "StdAfx.h"
#include "FlashWindow.h"
#include "MainFrame.h"
#include <limits.h>

namespace NMainFrame
{

bool FlashCurrentWindow()
{
	HWND hwnd = NMainFrame::GetWnd();
	if ( !IsWindow(hwnd) )
		return false;
	FLASHWINFO info;
	info.cbSize = sizeof(info);
	info.hwnd = hwnd;
	info.dwFlags = FLASHW_CAPTION | FLASHW_TRAY | FLASHW_TIMERNOFG;
	info.uCount = INT_MAX;
	info.dwTimeout = 0;//1 * 1000;
	FlashWindowEx( &info );
	return true;
}

}
