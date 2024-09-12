#include "stdafx.h"

#include "LocationClient.h"
#include "ClientWindow.h"

namespace Location 
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientWindow::ClientWindow() :
  hWnd(0),
  width(100),
  height(100),
  dataReady(false, true),
  dataDrawn(false, true)
{
  lineList.reserve( 1000 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientWindow::~ClientWindow()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  ClientWindow* clientWindow = reinterpret_cast<ClientWindow*>( ::GetWindowLongPtr( hWnd, GWL_USERDATA ) );  

  switch ( uMsg )
  {
  case WM_ERASEBKGND:
    return 0;
  case WM_PAINT:
    clientWindow->Paint();
    return 0;
  case WM_CLOSE:
    PostQuitMessage( 0 );
    return 0;
  case WM_MOUSEMOVE:
    break;
  case WM_RBUTTONDOWN:
    clientWindow->OnRButtonDown( LOWORD(lParam), HIWORD(lParam) );
    break;
  case WM_LBUTTONDOWN:
    clientWindow->OnLButtonDown( LOWORD(lParam), HIWORD(lParam) );
    break;
  }

  return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::OnLButtonDown( int _x, int _y )
{
  if ( !IsValid( locationClient ) )
    return;
  
  locationClient->MovePlayerTo( CVec3( _x, _y, 0.f ), Protocol::invalidObjectId );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::OnRButtonDown( int _x, int _y )
{
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClientWindow::Clear()
{
  if ( !dataDrawn.Wait( 100 ) )
    return false;

  lineList.clear();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::Invalidate()
{
  dataReady.Set();

  ::InvalidateRect( hWnd, 0, TRUE );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::DrawLine( int x1, int y1, int x2, int y2, const Color& color )
{
  Line& line = lineList.push_back();

  line.x1 = x1;
  line.y1 = y1;
  line.x2 = x2;
  line.y2 = y2;
  line.color = color; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::Paint()
{
  HDC hOriginalDC = ::GetDC( hWnd );
  HDC hDC = ::CreateCompatibleDC( hOriginalDC );
  HBITMAP hBitmap = ::CreateCompatibleBitmap( hDC, width, height );
  HBITMAP hBmpOld = (HBITMAP)::SelectObject( hDC, hBitmap );

  {
    dataReady.Wait();

    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    COLORREF clrOld = ::SetBkColor( hDC, RGB( 255, 255, 255 ) );
    ::ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
    ::SetBkColor( hDC, clrOld );

    {
      LineList::iterator it = lineList.begin();
      LineList::iterator last = lineList.end();

      for ( ; it != last; ++it )
      {
        HPEN pen = ::CreatePen( PS_SOLID, 1, RGB( it->color.r * 256, it->color.g * 256, it->color.b * 256 ) );
        HPEN oldPen = (HPEN)::SelectObject( hDC, pen );  

        ::MoveToEx( hDC, it->x1, it->y1, NULL );
        ::LineTo( hDC, it->x2, it->y2 );

        (HPEN)::SelectObject( hDC, oldPen );  
        ::DeleteObject( pen );
      }
    }

    dataDrawn.Set();
  }

  ::BitBlt( hOriginalDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
  ::SelectObject( hDC, hBmpOld );

  ::DeleteObject( hBitmap );
  ::DeleteDC( hDC );
  ::ReleaseDC( hWnd, hOriginalDC );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClientWindow::InitWindow( HINSTANCE hInstance, int _width, int _height )
{
  width = _width;
  height = _height;

  const char applicationTitle[] = "SimpleGameClient";

  WNDCLASS wndClass = { 0, WndProc, 0, 0, hInstance, 0, 0, 
    (HBRUSH)::GetStockObject( WHITE_BRUSH ),
    NULL, applicationTitle };

  wndClass.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

  ::RegisterClass( &wndClass );

  // Create the render window
  hWnd = ::CreateWindow( applicationTitle, "Simple Client", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
    0, 0, width, height,
    0, 0, hInstance, 0 );

  if ( !hWnd )
    return false;

  ::SetWindowLongPtr( hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>( this ) );  

  ::ShowWindow( hWnd, SW_SHOW );
  ::UpdateWindow( hWnd );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClientWindow::PumpMessages()
{
  static MSG msg;

  while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
  {
    if ( msg.message == WM_QUIT )
    {
      return false;
    }
    else
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientWindow::Run()
{
  while ( PumpMessages() )   
  {

  }
}

} // namespace Location
