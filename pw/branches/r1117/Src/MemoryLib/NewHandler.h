namespace ni_detail
{

void SetNewHandler(HWND _hWnd);  // defined in NewHandler.cpp

#ifndef _SHIPPING
#define _DEBUG_TERMINATE
#endif // _SHIPPING

#ifdef _DEBUG_TERMINATE
  void DebugTerminate();
#endif // _DEBUG_TERMINATE

} //namespace ni_detail
