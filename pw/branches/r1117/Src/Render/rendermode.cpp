#include "stdafx.h"

#include "rendermode.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Render
{
static RenderMode g_renderMode;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned int RenderMode::WIDTH_DEFAULT = 1024;
const unsigned int RenderMode::HEIGHT_DEFAULT = 768;
const unsigned int RenderMode::REFRESH_RATE_DEFAULT = D3DPRESENT_RATE_DEFAULT;

static NDebug::StringDebugVar s_ScreenResolution( "ScreenResolution", "" );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderMode::RenderMode()
	: multiSampleType( MULTISAMPLE_NONE )
	, multiSampleQuality( 0 )
	, isFullScreen( true )
	, width( WIDTH_DEFAULT )
	, height( HEIGHT_DEFAULT )
  , width3D( WIDTH_DEFAULT )
  , height3D( HEIGHT_DEFAULT )
	, refreshRate( REFRESH_RATE_DEFAULT )
	, vsyncCount( 0 )
{}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ResolutionVariable: public NGlobal::IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( ResolutionVariable );
public:
  ResolutionVariable() {}

  virtual NGlobal::VariantValue Get() 
  {  
    return NGlobal::VariantValue(NStr::StrFmtW(L"%dx%d", g_renderMode.width, g_renderMode.height)); 
  }

  virtual void Set( const NGlobal::VariantValue &val )
  {  
    wstring str( val.Get<wstring>() );
    vector<wstring> res;
    NStr::ToLower( &str );
    NStr::SplitString( str, &res, 'x' );

    if ( res.size() != 2 )
    {
      DebugTrace( "Could not parse screen resolution settings, using defaults" );
      
      //http://msdn.microsoft.com/en-us/library/ee417691.aspx#_1.5
      //The game uses the desktop resolution of the display device by 
      //default if it is a supported resolution. 
      GetDesktopResolution( g_renderMode.width, g_renderMode.height );
      return;
    }
    
    g_renderMode.width = NStr::ToInt( res[0] );
    g_renderMode.height = NStr::ToInt( res[1] );

    s_ScreenResolution.SetValue( "%dx%d", g_renderMode.width, g_renderMode.height );
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class InverseVariable: public NGlobal::IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( InverseVariable );
  
public:
  InverseVariable(): pVar(0) {}
  InverseVariable(T *pVar): pVar(pVar) {}
  virtual NGlobal::VariantValue Get() {  NI_ASSERT(pVar != 0, ""); return NGlobal::VariantValue(!*pVar); }
  virtual void Set( const NGlobal::VariantValue &val ){  NI_ASSERT(pVar != 0, ""); *pVar = !val.Get<T>(); }

private:
  T *pVar;            
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetDesktopResolution( unsigned int &width, unsigned int &height )
{
  //http://msdn.microsoft.com/en-us/library/ee417691.aspx#_1.5
  //The desktop resolution can be obtained by calling 
  //EnumDisplaySettings with ENUM_REGISTRY_SETTINGS.
  DEVMODE devMode;
  
  devMode.dmSize = sizeof(devMode);
  devMode.dmDriverExtra = 0;
  
  if( EnumDisplaySettings(0, ENUM_REGISTRY_SETTINGS, &devMode) )
  {
    width = devMode.dmPelsWidth;
    height = devMode.dmPelsHeight;
    
    if( Compatibility::IsRunnedUnderWine() )
    { 
      //Под Wine методы: EnumDisplaySettings, IDirect3D9::GetAdapterDisplayMode, GetDeviceCaps, 
      //GetMonitorInfo, GetWindowRect(GetDesktopWindow()) возвращают высоту монитора меньше
      //реальной на высоту стандартной полоски меню. 
      //Полноэкранный режим с такими настройками выглядит плохо: видно полоску меню и 
      //панель Dock. Поскольку найти функцию, которая вернёт настоящий размер мне не удалось,
      //я решил просто увеличивать высоту на размер полоски меню. Поскольку перед тем, как применить
      //разрешение осуществляется поиск максимально близкого из тех, которые поддерживает монитор, 
      //такой подход не должен ничего сломать.
      height += 22; 
    }
  }
  else
  {
    width = RenderMode::WIDTH_DEFAULT;
    height = RenderMode::HEIGHT_DEFAULT;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


REGISTER_VAR( "gfx_fullscreen", g_renderMode.isFullScreen, STORAGE_USER )
REGISTER_VAR_INTERFACE( "gfx_resolution", new ResolutionVariable(), STORAGE_USER )
REGISTER_VAR_INTERFACE( "gfx_windowed_mode", new InverseVariable<bool>(&g_renderMode.isFullScreen), STORAGE_NONE )
REGISTER_VAR( "gfx_vsync", g_renderMode.vsyncCount, STORAGE_USER )
REGISTER_VAR( "gfx_refreshrate", g_renderMode.refreshRate, STORAGE_USER )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetResolution( unsigned int &width, unsigned int &height )
{
  width = g_renderMode.width;
  height = g_renderMode.height;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetResolution( unsigned int width, unsigned int height )
{
  g_renderMode.width = width;
  g_renderMode.height = height;
  g_renderMode.refreshRate = RenderMode::REFRESH_RATE_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetRenderModeFromConfig(RenderMode &renderMode)
{	
	renderMode = g_renderMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
