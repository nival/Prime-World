#include "stdafx.h"
#include "Cursor.h"

#include "../System/Stream.h"
#include "../System/ImageDDS.h"
#include "../System/FileSystem/FileUtils.h"

#include "../System/MainFrame.h"

#include "../Render/texture.h"
#include "../Render/renderer.h"
#include "../Render/renderresourcemanager.h"

#include "ImageComponent.h"
#include "Resolution.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCursor
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool g_cursorHW = true;
string g_cursorSmooth = "auto";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCursor
{
	HCURSOR hCursor32; // 32-bit cursor (with alpha)
	HCURSOR hCursor24; // 24-bit cursor (with mask)
	HCURSOR hCursor16; // 16-bit cursor (with mask)
  HCURSOR hCursor;   // single precompiled cursor
	Render::Texture2DRef pTexture; // texture cursor
	CTPoint<int> hotSpot;
	int version;

	SCursor()
		: hCursor32(0)
		, hCursor24(0)
		, hCursor16(0)
    , hCursor(0)
		, pTexture(0)
		, hotSpot(0,0)
		, version(0)
	{}

  ~SCursor()
  {
    ReleaseResources();
  }

	void ReleaseResources()
	{
		if ( hCursor32 ) { DestroyIcon( hCursor32 ); hCursor32 = 0; }
		if ( hCursor24 ) { DestroyIcon( hCursor24 ); hCursor24 = 0; }
		if ( hCursor16 ) { DestroyIcon( hCursor16 ); hCursor16 = 0; }
    hCursor = 0; // do not destroy because you're not the owner
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CACHE_SHIFT = 5;
const int CACHE_SIZE = 1 << CACHE_SHIFT;
const int CACHE_MASK = CACHE_SIZE - 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool               g_cursorsInit = false;
static vector<SCursor>    g_cursorsCache;
static int                g_cursorsCacheHead = 1;
static UI::Point          g_currentSize, g_currentHotspot;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int MakeCacheRef( int index, int version ) { return index | ((version << CACHE_SHIFT) & ~CACHE_MASK); }
static int GetCacheRefIndex( int cacheRef ) { return cacheRef & CACHE_MASK; }
static int GetCacheRefVersion( int cacheRef ) { return cacheRef >> CACHE_SHIFT; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * FormatLastLastErrorMessage( DWORD errorCode )
{
  static char buffer[512] = "";
  if ( FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, buffer, 512, 0 ) )
    return buffer;
  else
    return "Eror message not found";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Image::~Image()
{
  if (hCursor)
    DestroyCursor(hCursor);
  hCursor = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CreateCursors( SCursor *pCursor, const Image & image )
{
	if ( !pCursor )
		return false;

  if ( pCursor->hCursor || pCursor->hCursor16 || pCursor->hCursor24 || pCursor->hCursor32 )
  {
    NI_ALWAYS_ASSERT("Try REcreate exist cursor");
    pCursor->ReleaseResources();
  }

  PushDXPoolGuard dxPool("UI");

  // separate processing for precompiled cursor
  if (image.GetHandle())
  {
    pCursor->hCursor = image.GetHandle();
    pCursor->hCursor16 = 0;
    pCursor->hCursor24 = 0;
    pCursor->hCursor32 = image.GetCursorPic();
    pCursor->pTexture = 0;
    return true;
  }

	const CArray2D<DWORD> & data = image.GetData();

	const int cw = image.GetWidth();
	const int ch = image.GetHeight();

		// Color map
	BITMAPINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = cw;
	bi.bmiHeader.biHeight = ch;
	bi.bmiHeader.biSizeImage = cw * ch * 4;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrImportant = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;

	VOID *pData = 0;

	HDC mdc = CreateCompatibleDC(NULL);
  if ( !mdc )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "CreateCompatibleDC failed! ( 0x%08x ): %s", err, FormatLastLastErrorMessage( err ) ) );
  }

	HBITMAP hBmp32 = CreateDIBSection( mdc, &bi, DIB_RGB_COLORS, &pData, NULL,0 );
  if ( !hBmp32 || !pData )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create cursor image ( 0x%08x, %dx%d ): %s", err, cw, ch, FormatLastLastErrorMessage( err ) ) );
  }

	for ( int y = 0; y < ch; ++y )
		for ( int x = 0; x < cw; ++x )
			((DWORD *)pData)[ x+y*cw ] = data[ch-1-y][x];

	HDC ddc = CreateCompatibleDC(NULL);
  if ( !ddc )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "CreateCompatibleDC failed! ( 0x%08x ): %s", err, FormatLastLastErrorMessage( err ) ) );
  }

	bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biSizeImage = cw * ch * 3;
	HBITMAP hBmp24 = CreateDIBSection( ddc, &bi, DIB_RGB_COLORS, &pData, NULL,0 );
  if ( !hBmp24 || !pData )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "CreateDIBSection24 failed! ( 0x%08x ): %s", err, FormatLastLastErrorMessage( err ) ) );
  }

	bi.bmiHeader.biBitCount = 16;
	bi.bmiHeader.biSizeImage = cw * ch * 2;
	HBITMAP hBmp16 = CreateDIBSection( ddc, &bi, DIB_RGB_COLORS, &pData, NULL,0 );
  if ( !hBmp16 || !pData )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "CreateDIBSection16 failed! ( 0x%08x ): %s", err, FormatLastLastErrorMessage( err ) ) );
  }

	HGDIOBJ hOrigMDC = SelectObject( mdc, hBmp32 );
	HGDIOBJ hOrigDDC = SelectObject( ddc, hBmp24 );
	BitBlt( ddc,0,0,cw,ch, mdc,0,0, SRCCOPY );
  SelectObject(mdc, hOrigMDC);
  SelectObject(ddc, hOrigDDC);

	hOrigMDC = SelectObject( mdc, hBmp32 );
	hOrigDDC = SelectObject( ddc, hBmp16 );
	BitBlt( ddc,0,0,cw,ch, mdc,0,0, SRCCOPY );
  SelectObject(mdc, hOrigMDC);
  SelectObject(ddc, hOrigDDC);

	// Mask
  unsigned char* mskZero = (unsigned char*)_aligned_malloc(cw * ch * 8, 16);
	unsigned char* mskFill = (unsigned char*)_aligned_malloc(cw * ch * 8, 16);

	ZeroMemory( mskZero, cw * ch * 4 );
	for ( int y = 0; y < ch; ++y )
  {
		for ( int x = 0; x < cw; ++x )
		{
			const bool seen = ( (unsigned char *)&data[y][x] )[3] > 128;
			if ( !seen )
				mskZero[( y * cw + x ) >> 3 ] |= 1 << ( 7 - ( x & 7 ) );
		}
  }

  HBITMAP hBmpMask = CreateBitmap( cw, ch, 1, 1, mskZero );
  if ( !hBmpMask )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create cursor mask (%d %d) (0x%08x): %s data ptr: %p", cw, ch, err, FormatLastLastErrorMessage( err ), mskZero ) );
  }

	FillMemory( mskFill, cw * ch * 4, 0xFF );

	HBITMAP hBmpNoMask = CreateBitmap( cw, ch, 1, 32, mskFill );
  if ( !hBmpNoMask )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create cursor no-mask (%d %d) (0x%08x): %s data ptr: %p", cw, ch, err, FormatLastLastErrorMessage( err ), mskFill ) );
  }

		// Create cursors
	ICONINFO iconInfo32;
	iconInfo32.fIcon = FALSE;
	iconInfo32.xHotspot = image.GetHotSpot().x;
	iconInfo32.yHotspot = image.GetHotSpot().y;

  //hOrigMDC = SelectObject( mdc, hBmp32 );
	iconInfo32.hbmColor = hBmp32;
	iconInfo32.hbmMask = hBmpNoMask;
	pCursor->hCursor32 = (HCURSOR)CreateIconIndirect( &iconInfo32 );
  if ( !pCursor->hCursor32 )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create 32bit cursor icon ( 0x%08x / 0x%08x / 0x%08x ): %s, data ptr: %p, %d, %d ",
                                             err, iconInfo32.hbmColor, iconInfo32.hbmMask, FormatLastLastErrorMessage( err ), mskZero, cw, ch ) );
  }
  //SelectObject(mdc, hOrigMDC);

  //hOrigDDC = SelectObject( ddc, hBmp24 );
  ICONINFO iconInfo24;
  iconInfo24.fIcon = FALSE;
  iconInfo24.xHotspot = image.GetHotSpot().x;
  iconInfo24.yHotspot = image.GetHotSpot().y;
	iconInfo24.hbmColor = hBmp24;
	iconInfo24.hbmMask = hBmpMask;
	pCursor->hCursor24 = (HCURSOR)CreateIconIndirect( &iconInfo24 );
  if ( !pCursor->hCursor24 )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create 24bit cursor icon (0x%08x): %s, data ptr: %p, %d, %d ", err, FormatLastLastErrorMessage( err ), mskZero, cw, ch ) );
  }
  //SelectObject(ddc, hOrigDDC);

  //hOrigDDC = SelectObject( ddc, hBmp16 );
  ICONINFO iconInfo16;
  iconInfo16.fIcon = FALSE;
  iconInfo16.xHotspot = image.GetHotSpot().x;
  iconInfo16.yHotspot = image.GetHotSpot().y;
	iconInfo16.hbmColor = hBmp16;
	iconInfo16.hbmMask = hBmpMask;
	pCursor->hCursor16 = (HCURSOR)CreateIconIndirect( &iconInfo16 );
  if ( !pCursor->hCursor16 )
  {
    DWORD err = GetLastError();
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not create 16bit cursor icon (0x%08x): %s, data ptr: %p, %d, %d ", err, FormatLastLastErrorMessage( err ), mskZero, cw, ch ) );
  }
  //SelectObject(ddc, hOrigDDC);

  _aligned_free(mskZero);
  _aligned_free(mskFill);

		// Cleanup
  DeleteObject( hBmp32 );
  DeleteObject( hBmp24 );
  DeleteObject( hBmp16 );
  DeleteObject( hBmpMask );
  DeleteObject( hBmpNoMask );
	DeleteDC( mdc );
	DeleteDC( ddc );
	GdiFlush();

		// Create software texture
	CArray2D<Render::Color> bits;
	bits.SetSizes( cw,ch );
	for ( int y = 0; y < ch; ++y )
		for ( int x = 0; x < cw; ++x )
		{
			unsigned char *bytes = (unsigned char *)&(data[y][x]);
			bits[y][x] = Render::Color( bytes[2], bytes[1], bytes[0], bytes[3] );
		}

	pCursor->pTexture = Render::Create2DTextureFromArray2D( bits );
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int CacheUp( const Image & image )
{
	const int cacheRef = image.cacheRef;
	const int index = GetCacheRefIndex( cacheRef );
	const int version = GetCacheRefVersion( cacheRef );

	if ( index >= 1 && index < CACHE_SIZE && g_cursorsCache[index].version == version )
		return cacheRef;

	const int newIndex = g_cursorsCacheHead;
	if ( ++g_cursorsCacheHead >= CACHE_SIZE )
		g_cursorsCacheHead = 1;

	const int newVersion = ( g_cursorsCache[ newIndex ].version + 1 ) & ( ( 1 << ( 31 - CACHE_SHIFT ) ) - 1 );

	SCursor & cursor = g_cursorsCache[ newIndex ];

	cursor.ReleaseResources();
	cursor.hotSpot = image.GetHotSpot();
	cursor.version = newVersion;

	if ( !CreateCursors( &cursor, image ) )
		return 0;

	image.cacheRef = MakeCacheRef( newIndex, newVersion );
	return image.cacheRef;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int g_currentCacheRef = 0;
static int g_newCacheRef = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SCursor g_defaultCursorData;
static bool g_useDefaultCursor = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool g_lastHW = g_cursorHW;
static string g_lastSmooth = g_cursorSmooth;
static int g_lastDisplayBits = 0;
static bool g_needUpdate = true;

static DWORD g_lastUpdateTime = 0;
static float g_curCursorTime = 0.0f;
static float g_timeToChangeCursor = 1.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetDefault( const Image *pCursorImage )
{
	if ( !g_cursorsInit )
		return;

	g_newCacheRef = 0;

	if ( !pCursorImage )
	{
		g_needUpdate = g_currentCacheRef || !g_useDefaultCursor;
		g_useDefaultCursor = true;
		return;
	}

	g_defaultCursorData.ReleaseResources();
	CreateCursors( &g_defaultCursorData, *pCursorImage );
	g_defaultCursorData.hotSpot = pCursorImage->GetHotSpot();

	g_needUpdate = g_currentCacheRef || g_useDefaultCursor;
	g_useDefaultCursor = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Set( const Image *pCursorImage )
{
  if ( !g_cursorsInit )
    return;

  if ( !pCursorImage )
  {
    g_needUpdate = ( g_currentCacheRef != 0 );
    g_newCacheRef = 0;
    return;
  }

  const int cacheRef = CacheUp( *pCursorImage );
  if ( ( g_needUpdate && g_newCacheRef != cacheRef ) || g_currentCacheRef != cacheRef )
  {
    g_needUpdate = true;
    g_newCacheRef = cacheRef;
  }

  if( pCursorImage )
  {
    g_currentSize.Set( pCursorImage->GetWidth(), pCursorImage->GetHeight() );
    g_currentHotspot = pCursorImage->GetHotSpot();
  }
  else
  {
    g_currentSize.Set( 0, 0 );
    g_currentHotspot.Set( 0, 0 );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static UI::ImageComponent g_cursorSW;
static UI::Point g_cursorSWSize;
static UI::Point g_cursorSWDelta;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool g_frozen = false;
static bool g_startAutoUnfreeze = false;
static DWORD g_autoUnfreezeTime = 0;
static POINT g_freezePos;
static RECT g_freezeClip;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Freeze( bool freeze )
{
	if ( !freeze )
	{
		g_frozen = false;
		::ClipCursor(0);
		return;
	}

	g_startAutoUnfreeze = true;

	if ( !g_frozen )
	{
		if ( FAILED( ::GetCursorPos( &g_freezePos ) ) )
			return;

		g_freezeClip.left = g_freezePos.x;
		g_freezeClip.right = g_freezePos.x;
		g_freezeClip.top = g_freezePos.y;
		g_freezeClip.bottom = g_freezePos.y;

		g_frozen = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Update( DWORD time )
{
  float deltaTime = (time - g_lastUpdateTime)/1000.0f;
  g_lastUpdateTime = time;

	if ( !g_cursorsInit )
		return;

	if ( g_frozen )
	{
		if ( g_startAutoUnfreeze )
		{
			g_startAutoUnfreeze = false;
			g_autoUnfreezeTime = time + 250;
		}

		if ( time >= g_autoUnfreezeTime )
		{
			g_frozen = false;
			::ClipCursor(0);
		}
		else
		{
			::SetCursorPos( g_freezePos.x, g_freezePos.y );
			::ClipCursor( &g_freezeClip );
		}
	}

	HDC hdc = GetDC( NMainFrame::GetWnd() );
	const int displayBits = GetDeviceCaps( hdc, BITSPIXEL );
	ReleaseDC( NMainFrame::GetWnd(), hdc );

	if ( !g_needUpdate && g_lastHW == g_cursorHW && g_lastSmooth == g_cursorSmooth && g_lastDisplayBits == displayBits )
		return;

	g_currentCacheRef = g_newCacheRef;
	g_lastHW = g_cursorHW;
	g_lastSmooth = g_cursorSmooth;
	g_lastDisplayBits = displayBits;
	g_needUpdate = false;

	SCursor *pCursor = 0;

	if ( g_currentCacheRef != 0 )
	{
		const int index = GetCacheRefIndex( g_currentCacheRef );
		const int version = GetCacheRefVersion( g_currentCacheRef );
		pCursor = &g_cursorsCache[ index ];
		if ( pCursor->version != version )
			pCursor = 0;
	}
	else
	{
		if ( g_useDefaultCursor )
		{
			NMainFrame::SetCursor( LoadCursor( NULL, IDC_ARROW ) );
			g_cursorSW.SetRenderable( false );
			return;
		}

		pCursor = &g_defaultCursorData;
	}

	if ( !pCursor )
	{
		NI_ASSERT( 0, "Cursor lost!" );
		NMainFrame::SetCursor( 0 );
		g_cursorSW.SetRenderable( false );
		return;
	}

	const bool trueColor = (displayBits == 32 || displayBits == 24);

	if ( g_cursorHW )
	{
    if (pCursor->hCursor)
    {
      if ( NMainFrame::GetCurrentCursor() != pCursor->hCursor )
      {
        if ( g_curCursorTime > g_timeToChangeCursor )
        {
          // use precompiled cursor
          NMainFrame::SetCursor( pCursor->hCursor );
          g_curCursorTime = 0.0f;
        }
        else
        {
          NMainFrame::SetCursor( pCursor->hCursor32 );
          g_curCursorTime += deltaTime;
        }
      }
    }
    else
    {
		  if ( g_cursorSmooth == "auto" )
			  NMainFrame::SetCursor( trueColor ? pCursor->hCursor32 : pCursor->hCursor16 );
		  else if ( g_cursorSmooth == "1" || g_cursorSmooth == "on" )
			  NMainFrame::SetCursor( trueColor ? pCursor->hCursor32 : pCursor->hCursor32 );
		  else
			  NMainFrame::SetCursor( trueColor ? pCursor->hCursor24 : pCursor->hCursor16 );
    }
	}
	else
	{
		// NOTE: call Render(x,y) to draw software cursor (will be drawn only if needed)
		NMainFrame::SetCursor(0);
		if ( pCursor->pTexture )
		{
			g_cursorSW.SetImageTexture( pCursor->pTexture );
			g_cursorSWDelta = pCursor->hotSpot;
			g_cursorSWSize.x = pCursor->pTexture->GetWidth();
			g_cursorSWSize.y = pCursor->pTexture->GetHeight();
			g_cursorSW.SetRenderable( true );
		}
		else
		{
			g_cursorSW.SetRenderable( false );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Render()
{
	if ( !g_cursorsInit )
		return;

	if ( g_cursorHW )
		return;

	POINT pt;
	if ( TRUE != GetCursorPos( &pt ) )
		return;

	RECT r;
	if ( TRUE != GetClientRect( NMainFrame::GetWnd(), &r ) )
		return;
	const int sw = Max( 1, int(r.right - r.left) );
	const int sh = Max( 1, int(r.bottom - r.top) );

	POINT leftTop;
	leftTop.x = r.left;
	leftTop.y = r.top;
	if ( TRUE != ClientToScreen( NMainFrame::GetWnd(), &leftTop ) )
		return;

	pt.x -= leftTop.x;
	pt.y -= leftTop.y;

	if ( pt.x < 0 || pt.y < 0 || pt.x >= sw || pt.y >= sh )
		return;

	const int uw = UI::GetUIScreenResolution().x;
	const int uh = UI::GetUIScreenResolution().y;
	const int x = ( pt.x * uw ) / sw;
	const int y = ( pt.y * uh ) / sh;

	const int rx = x - ( g_cursorSWDelta.x * uw + sw/2 ) / sw;
	const int ry = y - ( g_cursorSWDelta.y * uh + sh/2 ) / sh;
	const int rw = (g_cursorSWSize.x * uw + sw/2 ) / sw;
	const int rh = (g_cursorSWSize.y * uh + sh/2 ) / sh;

  UI::Rect rect( rx,ry,rx+rw,ry+rh );
	g_cursorSW.SetDrawRect( rect );
	g_cursorSW.SetCropRect( rect );
	//g_cursorSW.Update();
	g_cursorSW.Render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static HCURSOR LoadPrecompiledCursor( const string& fileName )
{
  CObj<Stream> pIStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pIStream && pIStream->IsOk(), NStr::StrFmt( "Cannot open file to load precompiled cursor: \"%s\"", fileName.c_str() ), return 0; );

  // save data to a temporary file
  string tempName = NFile::GetTempFileName();
  FILE* tempFile = 0;
  fopen_s(&tempFile, tempName.c_str(), "wb");
  NI_VERIFY( tempFile, NStr::StrFmt( "Cannot open temporary file to save precompiled cursor: \"%s\"", tempName.c_str() ), return 0; );
  size_t written = fwrite(pIStream->GetBuffer(), pIStream->GetSize(), 1, tempFile);
  fclose(tempFile);
  tempFile = NULL;
  NI_VERIFY( written == 1, NStr::StrFmt( "Error writing temporary file to save precompiled cursor: \"%s\"", tempName.c_str() ), return 0; );
  pIStream = NULL;

  // load cursor from the temporary file
  HCURSOR hCursor = reinterpret_cast<HCURSOR>(::LoadImage(NULL, tempName.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE));
  DWORD lastError = ::GetLastError();
  NI_VERIFY(hCursor, NStr::StrFmt( "Cannot load precompiled cursor: \"%s\"\n"
    "LoadImage() failed! (0x%08x): %s", fileName.c_str(), lastError, FormatLastLastErrorMessage( lastError ) ), return 0);

  // destroy temporary file
  ::remove(tempName.c_str());

  return hCursor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::Load( const NDb::UICursorBase *pCursorBase )
{
	cacheRef = 0;

  if ( !pCursorBase )
    return false;

  if (const NDb::UICursor* pCursor = dynamic_cast<const NDb::UICursor*>(pCursorBase))
  {
	  if ( !pCursor->texture )
		  return false;

	  string fileName = pCursor->texture->textureFileName;
	  if ( fileName.empty() )
		  return false;

	  CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	  NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open file to load cursor image: \"%s\"", fileName ), return false; );

	  if ( !NImage::RecognizeFormatDDS( pStream ) )
		  return false;

	  NImage::LoadImageDDS( &data, pStream );
    width = data.GetSizeX();
    height = data.GetSizeY();
    if ( width > 61 || height > 61 )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt("Size of bitmap \"%s\" (%i %i) exceed %i %i", fileName.c_str(), width, height, 61, 61 ) );
    }
	  hotSpot.x = pCursor->hotSpotX;
	  hotSpot.y = pCursor->hotSpotY;
  }
  else if (const NDb::UIAnimatedCursor* pCursor = dynamic_cast<const NDb::UIAnimatedCursor*>(pCursorBase))
  {
    data.SetSizes(0, 0);

    string const& fileName = pCursor->dstFileName;
    if ( fileName.empty() )
      return false;

    hCursor = LoadPrecompiledCursor(fileName);
    if ( !hCursor )
    {
      NI_ALWAYS_ASSERT("Can't create PrecompiledCursor");
      return false;
    }

    ICONINFO ie = { sizeof(ICONINFO) };
    ::GetIconInfo(hCursor, &ie);
    NI_DATA_ASSERT((int)ie.xHotspot == pCursor->hotSpotX && (int)ie.yHotspot == pCursor->hotSpotY,
      NStr::StrFmt("Hotspot information in precompiled image (%i,%i) and xdb (%i,%i) don't match for %s",
        ie.xHotspot, ie.yHotspot, pCursor->hotSpotX, pCursor->hotSpotY,
        GetFormattedDbId(pCursorBase->GetDBID()).c_str()));

    hCursorPic = (HCURSOR)CreateIconIndirect( &ie );
    if ( !hCursorPic )
    {
      NI_ALWAYS_ASSERT("Can't create PrecompiledCursor");
      return false;
    }

    BITMAP bm = {0};
    if (ie.hbmColor != 0)
    {
      // get color icon dimensions
      int ok = ::GetObject(ie.hbmColor, sizeof(bm), &bm);
      DWORD lastError = ::GetLastError();
      lastError = ::GetLastError();
      NI_VERIFY(ok, NStr::StrFmt("GetObject() failed! (0x%08x): %s", fileName.c_str(), lastError, FormatLastLastErrorMessage( lastError ) ), return false);
      width = bm.bmWidth;
      height = bm.bmHeight;
      if ( width > 61 || height > 61 )
      {
        NI_ALWAYS_ASSERT( NStr::StrFmt("Size of bitmap \"%s\" (%i %i) exceed %i %i", fileName.c_str(), width, height, 61, 61 ) );
      }

    }
    else
    {
      // black-and-white icon contain two masks
      int ok = ::GetObject(ie.hbmMask, sizeof(bm), &bm);
      DWORD lastError = ::GetLastError();
      lastError = ::GetLastError();
      NI_VERIFY(ok, NStr::StrFmt("GetObject() failed! (0x%08x): %s", fileName.c_str(), lastError, FormatLastLastErrorMessage( lastError ) ), return false);
      NI_DATA_ASSERT((bm.bmHeight & 1) == 0, NStr::StrFmt("Monochrome cursor mask should have even height (two masks) but got %i", bm.bmHeight));
      width = bm.bmWidth;
      height = bm.bmHeight / 2;
    }
    if (ie.hbmMask)
      DeleteObject(ie.hbmMask);
    if (ie.hbmColor)
      DeleteObject(ie.hbmColor);

    hotSpot.x = ie.xHotspot;
    hotSpot.y = ie.yHotspot;
  }
  else
  {
    NI_DATA_ALWAYS_ASSERT(NStr::StrFmt("Unsupported UICursorBase implementation in %s", GetFormattedDbId(pCursorBase->GetDBID()).c_str()));
    return false;
  }

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Image::Blit( int x, int y, Image & src, int sx, int sy, int sw, int sh )
{
  NI_DATA_VERIFY(this->GetHandle() == 0 && src.GetHandle() == 0, "Overlays for precompiled cursors are not supported", return);

	cacheRef = 0;

	const int srcXSize = src.data.GetSizeX();
	const int srcYSize = src.data.GetSizeY();
	const int xSize = data.GetSizeX();
	const int ySize = data.GetSizeY();

	if ( sw <= 0 )
		sw = srcXSize - sx;
	if ( sh <= 0 )
		sh = srcYSize - sh;

	for ( int dy = 0; dy < sh; ++dy )
		for ( int dx = 0; dx < sw; ++dx )
		{
			int fromX = sx + dx;
			int fromY = sy + dy;
			if ( fromX < 0 || fromY < 0 || fromX >= srcXSize || fromY >= srcYSize )
				continue;

			int toX = x + dx;
			int toY = y + dy;
			if ( toX < 0 || toY < 0 || toX >= xSize || toY >= ySize )
				continue;

			unsigned char *destBytes = (unsigned char *)&(data[toY][toX]);
			unsigned char *srcBytes = (unsigned char *)&(src.data[fromY][fromX]);

			const int alpha = srcBytes[3];
			const int invAlpha = 255 - alpha;

			destBytes[0] = (( destBytes[0] * invAlpha + srcBytes[0] * alpha ) >> 8) & 0xFF;
			destBytes[1] = (( destBytes[1] * invAlpha + srcBytes[1] * alpha ) >> 8) & 0xFF;
			destBytes[2] = (( destBytes[2] * invAlpha + srcBytes[2] * alpha ) >> 8) & 0xFF;
			destBytes[3] = (255 - (((255-(int)destBytes[3]) * invAlpha ) >> 8)) & 0xFF;
		}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Release()
{
	if ( !g_cursorsInit )
		return;
	g_defaultCursorData.ReleaseResources();
	for ( int i = 0; i < g_cursorsCache.size(); ++i )
		g_cursorsCache[i].ReleaseResources();
	g_cursorsCache.clear();
	g_cursorsInit = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct SCursorShutdowner
{
	~SCursorShutdowner()
	{
		Release();
	}
} cursorShutdowner;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Init()
{
	if ( g_cursorsInit )
		return;

	g_cursorsCache.clear();
	g_cursorsCache.resize( CACHE_SIZE );
	g_cursorsCacheHead = 1;

	NMainFrame::EnableCursorManagement( true );

	g_cursorsInit = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const UI::Point & GetCurrentSize()
{
  return g_currentSize;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const UI::Point & GetCurrentHotSpot()
{
  return g_currentHotspot;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR( "cursor_hw", g_cursorHW, STORAGE_NONE );
REGISTER_VAR( "cursor_smooth", g_cursorSmooth, STORAGE_NONE );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NCursor




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCursors
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_map<string,NCursor::Image> TCursorsMap;
TCursorsMap g_cursors;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int g_selected = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Register( const string & cursorName, /*const*/ NCursor::Image *pCursorImage )
{
	NI_VERIFY( !cursorName.empty(), "Empty cursor name!", return );
	NI_VERIFY( g_cursors.find( cursorName ) == g_cursors.end(), NStr::StrFmt( "Cursor %d already registered!", cursorName.c_str() ), return );
	NI_VERIFY( pCursorImage, "No cursor image passed!", return );
         
	g_cursors[ cursorName ] = *pCursorImage;
  pCursorImage->ResetHandle(); // release handle ownership (if any) and pass it to g_cursors[] map
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Release()
{
  Reset();
  g_cursors.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsRegistered( const string & cursorName )
{
	return g_cursors.find( cursorName ) != g_cursors.end();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Reset()
{
	g_selected = -1;
	NCursor::Set( 0 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Select( const string & cursorName, int priority )
{
	if ( priority <= g_selected )
		return;
	g_selected = priority;

	TCursorsMap::const_iterator it = g_cursors.find( cursorName );
	if ( it != g_cursors.end() )
		NCursor::Set( &(it->second) );
	else
		NCursor::Set( 0 );
}

} //namespace NCursors
