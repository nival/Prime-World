#include "stdafx.h"

#include "FontRender.hpp"
#include "Resolution.h"

#include "../Render/MaterialSpec.h"
#include "../Render/UIRenderer.h"
#include "FontStyle.h"

#include <shlobj.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFontRenderer* GetFontRenderer()
{
  static Strong<FontRenderer> fontRenderer = new FontRenderer();
  return fontRenderer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FontRenderer::FontRenderer() :
  ftLibrary(0),
  freeX(1),
  freeY(1),
  maxY(1)
{
  InitDefaultFontCache();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FontRenderer::~FontRenderer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontRenderer::Initialize()
{
  fontTexture = Render::CreateTexture2D( FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 1, Render::RENDER_POOL_MANAGED, Render::FORMAT_L8 );
  Render::GetUIRenderer()->SetFontTextureSize( FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE );

  if ( FT_Init_FreeType( &ftLibrary ) )
  {
    NI_ALWAYS_ASSERT_TRACE( "Can't initialize FreeType library" );
    return;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontRenderer::Release()
{
  alphabetCache.clear();
  fontStyles.clear();

  debugFontStyles.clear();

  if ( ftLibrary )
  {
    FT_Done_FreeType( ftLibrary );
    ftLibrary = 0;
  }

  fontTexture = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontRenderer::AllocatePlace( Glyph& glyph, int _width, int _height )
{
  const int FONT_TXT_GAP = 3;

  maxY = Max( maxY, freeY + _height );
  if ( freeX + _width + FONT_TXT_GAP >= FONT_TEXTURE_SIZE )
  {
    freeX = 1;
    freeY = maxY + FONT_TXT_GAP;

    maxY = Max( maxY, freeY + _height );

    if ( freeY + _height + FONT_TXT_GAP >= FONT_TEXTURE_SIZE )
    {
      NI_ALWAYS_ASSERT_TRACE( "No more place for letters" ); // remake

      glyph.u1 = 0;
      glyph.v1 = 0;
      glyph.u2 = ( _width ) / (float)FONT_TEXTURE_SIZE;
      glyph.v2 = ( _height ) / (float)FONT_TEXTURE_SIZE;

      return;
    }
  }

  glyph.u1 = freeX / (float)FONT_TEXTURE_SIZE;
  glyph.v1 = freeY / (float)FONT_TEXTURE_SIZE;
  glyph.u2 = ( freeX + _width ) / (float)FONT_TEXTURE_SIZE;
  glyph.v2 = ( freeY + _height ) / (float)FONT_TEXTURE_SIZE;

  freeX += _width + FONT_TXT_GAP;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Rect & FontRenderer::GetNoCropRect()
{
  static Rect noCrop( 0, 0, 0, 0 );
  return noCrop;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IAlphabet * FontRenderer::FindNearestAlphabet( const char * ttfFileName, int size, bool systemFont, bool bold, bool italic, bool forFlash )
{
  if ( !ttfFileName )
    ttfFileName = "UI/Fonts/DejaVu_book/DejaVuLGCSans.ttf";

  float K = UI::GetScreenResolution().y > 0 ? ( float( UI::GetUIScreenResolution().y ) / float( UI::GetScreenResolution().y ) ) : 1.0f;

  int needFontSize = (int)floorf( size / K );

  AlphabetCache::iterator it = alphabetCache.find( FontKey( FontKey::PszKeyType, ttfFileName, needFontSize, bold, italic, forFlash ) );

  if ( it != alphabetCache.end() )
    return it->second;

  nstl::pair<AlphabetCache::iterator, bool> insert = alphabetCache.insert( nstl::make_pair( FontKey( FontKey::StringKeyType, ttfFileName, needFontSize, bold, italic, forFlash ), new Alphabet( this ) ) );

  insert.first->second->LoadAlphabet( ftLibrary, ttfFileName, needFontSize, bold, italic, systemFont, forFlash );

  return insert.first->second;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFontStyle * FontRenderer::GetFontStyle( const NDb::UIFontStyle* _style )
{
  if ( !_style )
    return GetDebugFontStyle( 20 );

  FontStyles::iterator it = fontStyles.find( _style->GetDBID() );

  IFontStyle* fontStyle = ( it != fontStyles.end() ) ? fontStyle = it->second : new FontStyle( _style );
  fontStyles[ _style->GetDBID() ] = fontStyle;

  return fontStyle;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFontStyle * FontRenderer::GetDebugFontStyle( int size )
{
  Strong<IFontStyle> & style = debugFontStyles[size];

  if ( !style )
  {
    FontStyle * st = new FontStyle;
    st->SetDefaultSize( size );
    st->GetMaterial()->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
    st->GetMaterial()->GetDiffuseMap()->SetTexture( fontTexture );
    style = st;
  }

  return style;
}


static string GetFontPath( const string& fontName )
{
  if ( fontName.empty() )
    return "";

  string fullFontName = fontName + " (TrueType)";

  HKEY hKey;
  if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &hKey ) != ERROR_SUCCESS )
    if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Fonts", 0, KEY_READ, &hKey ) != ERROR_SUCCESS )
      return "";

  TCHAR fontsDir[MAX_PATH];
  if ( S_OK != SHGetFolderPath( 0, CSIDL_FONTS, 0, SHGFP_TYPE_CURRENT, fontsDir ) )
    return "";

  DWORD count;
  RegQueryInfoKey( hKey, NULL, NULL, NULL, NULL, NULL, NULL, &count, NULL, NULL, NULL, NULL );

  string res;
  for ( int i = 0; i < (int)count; i++ ) 
  { 
    TCHAR valueName[MAX_PATH]; 
    DWORD valueNameSize = MAX_PATH;

    BYTE  valueData[MAX_PATH];
    DWORD valueDataSize = MAX_PATH;

    if ( RegEnumValueA( hKey, i, valueName, &valueNameSize, NULL, NULL, valueData, &valueDataSize ) == ERROR_SUCCESS ) 
    { 
      if ( fullFontName == (char*)valueName )
      {
        if( !Compatibility::IsRunnedUnderWine() ) 
          res = NFile::Combine( (char*)fontsDir, (char*)valueData );
        else
          res = (char*)valueData;

        break;
      }
    } 
  }

  RegCloseKey( hKey );
  return res;
}


FontFileCache* FontRenderer::GetFontFileCache( const char * ttfFileName, EFontLocation::Enum fontLocation )
{
  FontFileCaches::iterator it = fontFileCaches[ fontLocation ].find( ttfFileName );

  if ( it != fontFileCaches[ fontLocation ].end() )
    return it->second;

  CObj<Stream> newStream;

  if ( fontLocation == EFontLocation::SystemFont )
    newStream = new FileStream( GetFontPath( ttfFileName ), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  else
    newStream = RootFileSystem::OpenFile( ttfFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

  if ( !(newStream && newStream->GetSize() ) )
  {
    DebugTrace( "Cannot load ttf font: %s", ttfFileName );
    fontFileCaches[ fontLocation ][ ttfFileName ] = defualtFontCache;
    return defualtFontCache;
  }

  Strong<FontFileCache> cache = new FontFileCache();

  fontFileCaches[ fontLocation ][ ttfFileName ] = cache;

  CopyFileToCache( newStream, cache, ttfFileName );

  return cache;
}

void FontRenderer::InitDefaultFontCache()
{
  defualtFontCache = new FontFileCache();

  CObj<Stream> fontStream = RootFileSystem::OpenFile( "UI/Fonts/DejaVu_book/DejaVuLGCSans.ttf", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

  NI_VERIFY( fontStream && fontStream->GetSize(), "Cannot load base ttf font: DejaVuLGCSans.ttf", return);

  CopyFileToCache( fontStream, defualtFontCache, "UI/Fonts/DejaVu_book/DejaVuLGCSans.ttf" );
}

void FontRenderer::CopyFileToCache( Stream* _stream, FontFileCache* _cache, const char* _fileName )
{
  if ( !IsValid( _stream ) || !IsValid( _cache ) )
    return;

  _cache->alphaBytes.clear();
  _cache->alphaBytes.resize( _stream->GetSize(), 0 );
  copy( _stream->GetBuffer(), _stream->GetBuffer() + _stream->GetSize(), _cache->alphaBytes.begin() );

  if ( NFile::GetFileExt( _fileName ) == ".pfb" )
  {
    {
      _cache->kerningBytes.clear();
      const string kerningFileName = NFile::CutFileExt( _fileName, 0 ) + ".afm";
      CObj<Stream> kerningStream = RootFileSystem::OpenFile( kerningFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

      if ( kerningStream && kerningStream->IsOk() && kerningStream->GetSize() )
      {
        _cache->kerningBytes.resize( kerningStream->GetSize(), 0 );
        copy( kerningStream->GetBuffer(), kerningStream->GetBuffer() + kerningStream->GetSize(), _cache->kerningBytes.begin() );
      }
      else
        NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't read kerning and additional metrics for font from file: %s", _fileName ) );
    }
  }
}



} //namespace UI

NI_DEFINE_REFCOUNT(UI::IAlphabet)
NI_DEFINE_REFCOUNT(UI::IFontStyle)
NI_DEFINE_REFCOUNT(UI::FontFileCache)