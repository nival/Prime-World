#include "StdAfx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainFrame
{
static const char *pszSplashScreenWindowClass = "SplashScreen_WindowClass_DEFAULT";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSplashScreen : public CObjectBase
{
	OBJECT_METHODS( 0x1E4A8B48, CSplashScreen );
	//
	class SBitmap
	{
		CTPoint<int> size;
		BITMAP bitmapInfo;
		HBITMAP hBitmap;
		HPALETTE hPalette;
		//
		void Clear();
	public:
		SBitmap();
		~SBitmap();

		bool Load( const string &rszImageFileName );
		bool Draw( HDC *pHDC );
		int GetSizeX() { return bitmapInfo.bmWidth; }
		int GetSizeY() { return bitmapInfo.bmHeight; }
	};

	string szImageFileName;
	SBitmap bitmap;	
	HWND hWnd;
public:
	CSplashScreen();
	~CSplashScreen();

	bool Create( const string &rszImageFileName, bool bTopMost );
	bool IsWindow();
	bool ShowWindow( int nCmdShow );
	bool UpdateWindow();
	void Destroy();
	//
	bool Draw( HDC *pHDC );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SplashScreenWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CSplashScreen* pSplashScreen = reinterpret_cast<CSplashScreen*>( ::GetWindowLong( hWnd, GWL_USERDATA ) );
	switch ( uMsg ) 
	{
	case WM_SYSCOMMAND:
		return 1;

	case WM_PAINT:
		if ( GetUpdateRect( hWnd, 0, false ) != 0 ) 
		{
			PAINTSTRUCT ps;
			HDC hDC = ::BeginPaint( hWnd, &ps );

			if ( pSplashScreen )
				pSplashScreen->Draw( &hDC );

			::EndPaint( hWnd, &ps );
			::ValidateRect( hWnd, 0 );
		}
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSplashScreen::SBitmap::SBitmap()
: hBitmap( 0 ), hPalette( 0 )
{
	bitmapInfo.bmHeight = 0;
	bitmapInfo.bmWidth = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSplashScreen::SBitmap::~SBitmap()
{
	Clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSplashScreen::SBitmap::Clear()
{
	if ( hBitmap )
	{
		::DeleteObject( hBitmap );
		hBitmap = 0;
	}

	if ( hPalette )
	{
		::DeleteObject( hPalette );
		hPalette = 0;
	}

	bitmapInfo.bmHeight = 0;
	bitmapInfo.bmWidth = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::SBitmap::Load( const string &rszImageFileName )
{
	Clear();
	//Use LoadImage() to get the image loaded into a DIBSection
	hBitmap = (HBITMAP)::LoadImage( 0,
		rszImageFileName.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	if ( hBitmap == 0 )
		return false;

	//Get the color depth of the DIBSection
	::GetObject( hBitmap, sizeof( BITMAP ), &bitmapInfo );

	//If the DIBSection is 256 color or less, it has a color table
	if ( ( bitmapInfo.bmBitsPixel * bitmapInfo.bmPlanes ) <= 8 )
	{
		// Create a memory DC and select the DIBSection into it
		HDC hMemDC = ::CreateCompatibleDC( 0 );
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject( hMemDC, hBitmap );
		//Get the DIBSection's color table
		RGBQUAD rgb[256];
		::GetDIBColorTable( hMemDC, 0, 256, rgb );
		// Create a palette from the color tabl
		LPLOGPALETTE pLogPal = (LOGPALETTE *)malloc( sizeof( LOGPALETTE ) + ( 256 * sizeof( PALETTEENTRY ) ) );
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;
		for ( int i = 0; i < 256 ; ++i )
		{
			pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
			pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
			pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		hPalette = ::CreatePalette( pLogPal );

		free( pLogPal );
		::SelectObject( hMemDC, hOldBitmap );
		::DeleteDC( hMemDC );
	}
	else
	{
		// It has no color table, so use a halftone palette
		HDC hRefDC = ::GetDC( 0 );
		hPalette = ::CreateHalftonePalette( hRefDC );
		::ReleaseDC( 0, hRefDC );
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::SBitmap::Draw( HDC *pHDC )
{
	if ( (hBitmap == 0) || (hPalette == 0) )
		return false;

	HDC hMemDC = ::CreateCompatibleDC( *pHDC );
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject( hMemDC, hBitmap );
	HPALETTE hOldPalette = ::SelectPalette( *pHDC, hPalette, false );
	::RealizePalette( *pHDC );

	::BitBlt( *pHDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, hMemDC, 0, 0, SRCCOPY );

	::SelectObject( hMemDC, hOldBitmap );
	::SelectPalette( *pHDC, hOldPalette, FALSE );

	DeleteDC ( hMemDC );

	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSplashScreen::CSplashScreen() : hWnd( 0 )
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSplashScreen::~CSplashScreen()
{ 
	if ( ::IsWindow(hWnd) )
		Destroy();	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::Draw( HDC *pHDC )
{
	return bitmap.Draw( pHDC );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::Create( const string &_szImageFileName, bool bTopMost )
{
	szImageFileName = _szImageFileName;

	if ( ::IsWindow(hWnd) )
		Destroy();	

	if ( !bitmap.Load( szImageFileName ) )
		return false;

	WNDCLASSEX wcex;

	wcex.cbSize					= sizeof( WNDCLASSEX ); 
	wcex.style					= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc		= (WNDPROC)SplashScreenWndProc;
	wcex.cbClsExtra			= 0;
	wcex.cbWndExtra			= 0;
	wcex.hInstance			= ::GetModuleHandle( 0 );
	wcex.hIcon					= 0;
	wcex.hCursor				= ::LoadCursor( 0, IDC_ARROW );
	wcex.hbrBackground	= 0; //(HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName		= 0;
	wcex.lpszClassName	= pszSplashScreenWindowClass;
	wcex.hIconSm				= 0;
	if ( !::RegisterClassEx( &wcex ) ) 
		return false;

	hWnd = CreateWindowEx( WS_EX_TOOLWINDOW	| ( bTopMost ? WS_EX_TOPMOST :	0 ),
		pszSplashScreenWindowClass,
		"",
		WS_POPUP,
		0,
		0,
		0,
		0,
		0,
		0,
		::GetModuleHandle( 0 ),
		0 );

	if ( ::IsWindow(hWnd) )
	{
		const CTPoint<int> bitmapSize( bitmap.GetSizeX(), bitmap.GetSizeY() );
		const int nScreenSizeX = GetSystemMetrics( SM_CXSCREEN );
		const int nScreenSizeY = GetSystemMetrics( SM_CYSCREEN );
		const int nX = ( nScreenSizeX - bitmapSize.x ) / 2;
		const int nY = ( nScreenSizeY - bitmapSize.y ) / 2;
		::MoveWindow( hWnd, nX, nY, bitmapSize.x, bitmapSize.y, false );
		::SetWindowLong( hWnd, GWL_USERDATA, reinterpret_cast<LONG>( this ) );
		::UpdateWindow( hWnd ); 
	}
	return ::IsWindow( hWnd ) == TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::ShowWindow( int nCmdShow )
{
	if ( ::IsWindow(hWnd) )
	{
		::ShowWindow( hWnd, nCmdShow );
		::UpdateWindow( hWnd );
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::IsWindow()
{
	return ::IsWindow( hWnd ) == TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CSplashScreen::UpdateWindow()
{
	if ( ::IsWindow(hWnd) )
	{
		::UpdateWindow( hWnd );
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSplashScreen::Destroy()
{
	if ( ::IsWindow(hWnd) )
		DestroyWindow( hWnd );
	hWnd = 0;
	UnregisterClass( pszSplashScreenWindowClass, ::GetModuleHandle(0) );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectBase *CreateSplashScreen( const string &_szImageFileName, bool bTopMost )
{
	CSplashScreen *pSplash = new CSplashScreen();
	pSplash->Create( _szImageFileName, bTopMost );
	pSplash->ShowWindow( SW_SHOW );
	if ( !pSplash->IsWindow() )
	{
		delete pSplash;
		pSplash = 0;
	}
	//
	return pSplash;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
