#include "stdafx.h"
#include "DebugVarsRender.h"
#include "../System/LogFileName.h"
#include "../Render/Renderer.h"
#include "../Render/UIRenderer.h"
#include "../Render/debugrenderer.h"

#include "FontRender.h"
#include "Resolution.h"
#include "SkinStyles.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::Color debugVarNormal( 0, 255, 0, 255 );
const Render::Color debugVarWarning( 255, 64, 64, 255 );
const Render::Color debugVarScreenName( 255, 255, 255, 255 );
const Render::Color debugVarGraphColor( 255, 255, 255, 255 );
const Render::Color debugVarTickColor( 120, 120, 120, 255 );
const int DEBUG_VAR_NAME_MAX_LENGTH = 24;
const int SCREEN_NAME_MAX_LENGTH = 16;
static const string debugVarFontStyle = "DebugVar";
static bool initialized = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::UIRenderMaterial& GetDebugVarBackgroundMaterial()
{
  static Render::UIRenderMaterial renderMaterial( NDb::Get<NDb::BaseUIMaterial>( NDb::DBID( "/UI/Debug/debugVars.MTRL" ) ) );
  return renderMaterial;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetFontSize()
{
  Weak<UI::IFontStyle> debugVarStyle = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( debugVarFontStyle ) );
  int fontSize = 22;
  if ( debugVarStyle )
    fontSize = debugVarStyle->GetStyle() ? debugVarStyle->GetStyle()->fontSize + 3 : fontSize;
  return fontSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDebug
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DebugVarDrawer : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( DebugVarDrawer, BaseObjectST );
  const IDebugVar& var;

  DebugVarDrawer& operator=( const DebugVarDrawer& ) {}

protected:
  const wchar_t* GetName() const { return var.GetName(); }
  const IDebugVar& GetVar() const { return var; }

public:
  DebugVarDrawer() : var( (const IDebugVar&)(*(const IDebugVar*)0) ) { }
	DebugVarDrawer( const IDebugVar& _var ) : var( _var ) { }

  virtual ~DebugVarDrawer() {}

  virtual void Draw( int offset ) {}
  virtual int GetHeight() const { return 0; }

	bool IsMatch( IDebugVar* pVar ) const
	{
		return pVar == &var;
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextDrawer : public DebugVarDrawer
{
  NI_DECLARE_REFCOUNT_CLASS_1( TextDrawer, DebugVarDrawer );

  TextDrawer() : DebugVarDrawer() { }
public:

  TextDrawer( const IDebugVar& _var ) : DebugVarDrawer(_var) { }
  ~TextDrawer() {}

  virtual void Draw( int extoffset )
  {
    static wchar_t value[128];
    GetVar().FormatValue( value, sizeof( value ) / sizeof( wchar_t ) );
    static wchar_t buffer[128];
    int length  = swprintf_s( buffer, L"%s: %s", GetName(), value );
    UI::IFontStyle * style = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( debugVarFontStyle ) );
    if ( style )
      style->DrawString( buffer, length, 2, extoffset, GetVar().IsWarning() ? debugVarWarning : debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );
  }

  virtual int GetHeight() const
  {
    return GetFontSize();
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GraphPlotter : public DebugVarDrawer
{
  NI_DECLARE_REFCOUNT_CLASS_1( GraphPlotter, DebugVarDrawer );

  bool isTime;
  const Plotter* plotter;
	int height;
  nstl::vector<float> vals;
  nstl::vector<float> times;

  GraphPlotter() { }
public:
  GraphPlotter( const IDebugVar& _var, const Plotter* _plotter, int _height )
    : DebugVarDrawer( _var ), plotter( _plotter ), height( _height )
  {
		isTime = plotter->TimeLimit() > 0.0f;
  }

  ~GraphPlotter() {}

  virtual void Draw( int extoffset )
  {
    UI::IFontStyle * style = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( debugVarFontStyle ) );
    float textScale = style->GetAlphabet()->GetHeightScale();
    CTPoint<int> screenRes = UI::GetUIScreenResolution();

    static wchar_t buffer[128];
    vals.clear();
    times.clear();
    plotter->FillInfo( vals, times );

    int graphHeight = height - GetFontSize();

    float minx = vals.size() == 0 ? -10000.0f : vals[0];
    float maxx = vals.size() == 0 ? 10000.0f : vals[0];
    for ( int i = 1; i < plotter->Count(); i++ )
    {
      if ( vals[i] < minx )
      {
        minx = vals[i];
      }
      if ( vals[i] > maxx )
      {
        maxx = vals[i];
      }
    }

    int curX = 2;
    int curY = (extoffset+graphHeight) / textScale;

    int length = swprintf_s( buffer, L"Max: %f", maxx );
    if ( style )
      style->DrawString( buffer, length, curX, extoffset, debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );
    length = swprintf_s( buffer, L"Min: %f", minx );
    if ( style )
		  style->DrawString( buffer, length, curX, extoffset+(height-GetFontSize()), debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );

    if ( maxx == minx )
      maxx = minx + 1.0f;
    float valHeight = maxx - minx;

    if ( isTime )
    {
      length = swprintf_s( buffer, L"%f", plotter->TimeLimit()/4 );
    }
    else
    {
      length = swprintf_s( buffer, L"%d", plotter->Count()/4 );
    }
    if ( style )
      style->DrawString( buffer, length, curX + (screenRes.x-100)/4, extoffset + (height-GetFontSize()), debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );
    if ( isTime )
    {
      length = swprintf_s( buffer, L"%f", plotter->TimeLimit()/2 );
    }
    else
    {
      length = swprintf_s( buffer, L"%d", plotter->Count()/2 );
    }
    if ( style )
      style->DrawString( buffer, length, curX + (screenRes.x-100)/2, extoffset+(height-GetFontSize()), debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );
    if ( isTime )
    {
      length = swprintf_s( buffer, L"%f", 3*plotter->TimeLimit()/4 );
    }
    else
    {
      length = swprintf_s( buffer, L"%d", 3*plotter->Count()/4 );
    }
    if ( style )
      style->DrawString( buffer, length, curX + 3*(screenRes.x-100)/4, extoffset+(height-GetFontSize()), debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );
    if ( isTime )
    {
      length = swprintf_s( buffer, L"%f", plotter->TimeLimit() );
    }
    else
    {
      length = swprintf_s( buffer, L"%d", plotter->Count() );
    }
    if ( style )
      style->DrawString( buffer, length, curX + (screenRes.x-100), extoffset+(height-GetFontSize()), debugVarNormal, UI::GetFontRenderer()->GetNoCropRect() );

    bool isNeedDrawLine = false;

    float curTime = 0.0f;

    for ( int i = 1; i < plotter->Count(); i++ )
    {
      float deltax;
      if ( isTime )
        deltax = times[i]/plotter->TimeLimit()*(screenRes.x)/textScale;
      else
        deltax = (screenRes.x)/(float)plotter->Count()/textScale;
      float lastdelta = -(vals[i-1]-minx)/valHeight*graphHeight/2.0f;
      float deltay = -(vals[i]-minx)/valHeight*graphHeight/2.0f;

      if ( deltax > 5.0f )
      {
        isNeedDrawLine = true;
      }

      curTime += times[i];
      if( isTime && curTime > plotter->TimeLimit() )
      {
        break;
      }

      if ( isNeedDrawLine )
        Render::DebugRenderer::DrawLine2D( curX, curY, curX, extoffset/textScale+GetFontSize(), debugVarTickColor, debugVarTickColor );
      Render::DebugRenderer::DrawLine2D( curX, curY+lastdelta, curX+deltax, curY+deltay, debugVarGraphColor, debugVarGraphColor );
      curX += deltax;
      lastdelta = deltay;
    }

    if ( isNeedDrawLine )
      Render::DebugRenderer::DrawLine2D( curX, curY, curX, extoffset/textScale+GetFontSize(), debugVarTickColor, debugVarTickColor );
  }

  virtual int GetHeight() const
  {
    return height;
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DebugVarScreen
{
	wchar_t name[SCREEN_NAME_MAX_LENGTH];
	vector<Strong<DebugVarDrawer>> drawers;

  bool IsDebugVarExists( IDebugVar* pVar ) const 
  {
		for( vector<Strong<DebugVarDrawer>>::const_iterator it = drawers.begin(); it != drawers.end(); ++it )
		{
			if ( (*it)->IsMatch( pVar ) )
      {
        systemLog( NLogg::LEVEL_MESSAGE ) << "Cannot add debug variable " << wstring( pVar->GetName() ) << " to screen " << wstring( name ) << ". Debug variable already exists at this screen" << endl;
				return false;
      }
		}

    return true;
  }

	IDebugVar* FindUniqueDebugVar( const wchar_t* _name ) const
	{
		IDebugVar* pVar = FindDebugVar( _name );
		if ( !pVar )
    {
		  systemLog( NLogg::LEVEL_MESSAGE ) << "Cannot add debug variable " << wstring( _name ) << " to screen " << wstring( name ) << ". Debug variable not found" << endl;
			return 0;
    }

    return IsDebugVarExists( pVar ) ? pVar : 0;
	}

  // Add debug var to screen. If height == 0 add only text representation of debug var
  void AddDebugVar( IDebugVar* pVar, const int height )
  {
    drawers.push_back( new TextDrawer( *pVar ) );
    if ( height > 0 )
    {
		  if ( pVar->GetPlotter() )
		  {
		    drawers.push_back( new GraphPlotter( *pVar, pVar->GetPlotter(), height ) );
		    if ( pVar->GetSecondPlotter() )
		    {
			    drawers.push_back( new GraphPlotter( *pVar, pVar->GetSecondPlotter(), height ) );
		    }
      }
    }
  }

public:
	DebugVarScreen()
	{
	}

	DebugVarScreen( const wchar_t* _name )
	{
	  NStr::WCopy( _name, name, SCREEN_NAME_MAX_LENGTH );
	}

	DebugVarScreen( const DebugVarScreen& screen ) : drawers( screen.drawers )
	{
		NStr::WCopy( screen.name, name, SCREEN_NAME_MAX_LENGTH );
	}

	bool AddDebugVar( const wchar_t* name, const int height )
	{
		bool result = false;
		vector<IDebugVar*> vars = FindDebugVars( name );
		for ( int i = 0; i < vars.size(); i++ )
		{
			IDebugVar *pVar = vars[i];
      if ( IsDebugVarExists( pVar ) )
      {
        AddDebugVar( pVar, height );
        result = true;
      }
		}
		return result;
	}

	bool RemoveDebugVar( const wchar_t* name )
	{
		IDebugVar* pVar = FindDebugVar( name );
		for( vector<Strong<DebugVarDrawer>>::iterator it = drawers.begin(); it != drawers.end(); ++it )
		{
			if ( (*it)->IsMatch( pVar ) )
			{
				drawers.erase( it );
				return true;
			}
		}

		return false;
	}

	void Draw() const
	{
		int varsHeight = 0;

		for ( int i = 0; i < drawers.size(); i++ )
		{
			varsHeight += drawers[i]->GetHeight();
		}
		if ( varsHeight < 1 )
			return;

		// Draw style quad
		const CTPoint<int> screenRes = UI::GetUIScreenResolution();
    static Render::UIQuad background( UI::Point( 0, 0 ), UI::Point( 0, 0 ), VNULL2, VNULL2, VNULL2, VNULL2 );
		UI::IFontStyle * debugVarStyle = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( debugVarFontStyle ) );

		background.tl.x = 0;
		background.tl.y = 0;
		background.br.x = screenRes.x;
		background.br.y = varsHeight + GetFontSize() + 4;
		Render::GetUIRenderer()->AddQuad( background, GetDebugVarBackgroundMaterial().GetRenderMaterial(), Render::SMaterialParams() );

    if ( debugVarStyle )
		  debugVarStyle->DrawString( name, wcslen( name ), 2, 1, debugVarScreenName, UI::GetFontRenderer()->GetNoCropRect() );

		const wchar_t* versionLabel = NDebug::GetProductNameW();
		const int versionLabelLength = wcslen( versionLabel );
    const int versionLabelPosition = ( screenRes.x - ( debugVarStyle ? debugVarStyle->GetStringLength( versionLabel, versionLabelLength ) : 0 ) );

    if ( debugVarStyle )
		  debugVarStyle->DrawString( versionLabel, versionLabelLength, versionLabelPosition - 2, 1, debugVarScreenName, UI::GetFontRenderer()->GetNoCropRect() );

		int offset = GetFontSize();
		for ( int i = 0; i < drawers.size(); i++ )
		{
			drawers[i]->Draw(offset);
			offset += drawers[i]->GetHeight();
		}
	}

	const wchar_t* GetName() const
	{
		return name;
	}

	bool IsEmpty() const
	{
		return drawers.empty();
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int activeScreen = -1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<DebugVarScreen>& GetScreens()
{
	static vector<DebugVarScreen> screens;
	return screens;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<IDebugVar*>& GetWatchedVars()
{
	static vector<IDebugVar*> watched;
	return watched;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Initialize()
{
  initialized = true;
	GetDebugVarBackgroundMaterial().SetDBMaterial( NDb::Get<NDb::BaseUIMaterial>( NDb::DBID( "/UI/Debug/debugVars.MTRL" ) ), 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Release()
{
  if ( initialized )
    GetDebugVarBackgroundMaterial().Release();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawDebugVars()
{
  if ( Render::GetRenderer()->DeviceIsLost() )
    return;

  if ( activeScreen < 0 || activeScreen >= GetScreens().size() )
		return;

	GetScreens()[activeScreen].Draw();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckWatchedVars()
{
  for( vector<IDebugVar*>::const_iterator it = GetWatchedVars().begin(); it != GetWatchedVars().end(); ++it )
  {
    if ( *it && (*it)->IsWarning() )
    {
      static wchar_t buffer[128];
	    (*it)->FormatValue( buffer, 128 );

      systemLog( NLogg::LEVEL_DEBUG ) << "DebugVar Warning: " << wstring( (*it)->GetName() ) << ": " << wstring( buffer ) << endl;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddDebugVar( const char *name, const vector<wstring> &params )
{
	if ( params.size() < 2 || params.size() > 4 )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <debug_var> <screen> [g <height>]" << endl;
		return true;
	}

	DebugVarScreen* pScreen = 0;
	for( vector<DebugVarScreen>::iterator it = GetScreens().begin(); it != GetScreens().end(); ++it )
	{
		if ( NStr::WCmp( it->GetName(), params[1].c_str() ) == 0 )
		{
			pScreen = it;
			break;
		}
	}

	if ( !pScreen )
	{
		pScreen = &(GetScreens().push_back( DebugVarScreen( params[1].c_str() ) ));
	}

  bool graph = params.size() > 2 && NStr::WCmp( params[2].c_str(), L"g" ) == 0;
  int height = 0;
  if ( params.size() == 4 )
    height = NStr::ToInt( params[3] );

  if ( graph )
    pScreen->AddDebugVar( params[0].c_str(), Max( 25, height ) );
  else
    pScreen->AddDebugVar( params[0].c_str(), 0 );

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool RemoveDebugVar( const char *name, const vector<wstring> &params )
{
	if ( params.size() < 1 || params.size() > 2 )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <debug_var>|* [<screen>]" << endl;
		return true;
	}

	if ( NStr::WCmp( params[0].c_str(), L"*" ) == 0 )
	{
		if ( params.size() == 1 )
		{
			activeScreen = -1;
			GetScreens().clear();
		}
		else
		{
			for( vector<DebugVarScreen>::iterator it = GetScreens().begin(); it != GetScreens().end(); ++it )
			{
				if ( NStr::WCmp( it->GetName(), params[1].c_str() ) == 0 )
				{
					GetScreens().erase( it );
					if ( activeScreen >= GetScreens().size() )
						--activeScreen;

					return true;
				}
			}
		}
	}
	else
	{
		for( vector<DebugVarScreen>::iterator it = GetScreens().begin(); it != GetScreens().end();  )
		{
			if ( params.size() == 1 || NStr::WCmp( it->GetName(), params[1].c_str() ) == 0 )
			{
				it->RemoveDebugVar( params[0].c_str() );
			}

			if ( it->IsEmpty() )
			{
				it = GetScreens().erase( it );
			}
			else
				++it;
		}
		if ( activeScreen >= GetScreens().size() )
			--activeScreen;
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SetDebugVarPage( const char *name, const vector<wstring> &params )
{
	int screen = -1;

	if ( params.size() > 0 )
	{
		const string p = NStr::ToMBCS( params[0] );
		int i = 0;
		for ( vector<DebugVarScreen>::iterator it = GetScreens().begin(); it != GetScreens().end(); ++it, i++ )
		{
			if ( !NStr::WCmp( params[0].c_str(), it->GetName() ) )
			{
				// found
				screen = i;
				break;
			}
		}
		if ( screen < 0 )
		{
			MessageTrace( "set screen: \"%s\" is not found", p.c_str() );
		}
		else if ( GetScreens()[screen].IsEmpty() )
		{
			MessageTrace( "set screen: \"%s\" is empty", p.c_str() );
			screen = -1;
		}
	}

	activeScreen = screen;
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool WatchDebugVar( const char *name, const vector<wstring> &params )
{
	if ( params.size() != 1 )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <debug_var>" << endl;
		return true;
	}

  IDebugVar* pVar = FindDebugVar( params[0].c_str() );
  if ( !pVar )
  {
		systemLog( NLogg::LEVEL_MESSAGE ) << "DebugVar " << params[0] << " not found" << endl;
    return true;
  }

  for( vector<IDebugVar*>::iterator it = GetWatchedVars().begin(); it != GetWatchedVars().end(); ++it )
  {
    if ( *it == pVar )
    {
      GetWatchedVars().erase( it );
	    systemLog( NLogg::LEVEL_MESSAGE ) << "DebugVar " << params[0] << " remove from watch-list" << endl;
      return true;
    }
  }

  GetWatchedVars().push_back( pVar );
  systemLog( NLogg::LEVEL_MESSAGE ) << "DebugVar " << params[0] << " added to watch-list" << endl;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __stdcall LogEnabler( const wchar_t* screen, const wchar_t* _varName, const NDebug::IDebugVar* pDebugVar, void* pData )
{
  FILE* file = (FILE*)pData;

  wstring varName = _varName;

  if ( file == 0 )
    systemLog( NLogg::LEVEL_MESSAGE ) << "\"" << varName << "\"" << endl;
  else
    fprintf_s( file, "\"%ls\"\n", varName.c_str() );
}

static bool ListAllDebugVars( const char *name, const vector<wstring> &params )
{
  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <file_name>|con" << endl;
    systemLog( NLogg::LEVEL_MESSAGE ) << "  if con specified instead of file_name - list to console" << endl;
    return true;
  }
  FILE* file = 0;
  if ( params[0] != L"con" )
    fopen_s( &file, NStr::ToMBCS( params[0]).c_str(), "w" );

  ProcessAllDebugVars( LogEnabler, (void*)file );

  if ( file )
  {
    fclose( file );
    systemLog( NLogg::LEVEL_MESSAGE ) << "List dump complete" << endl;
  }
  return true;
}

bool ToggleVarsCommand( const char *name, const vector<wstring> &params )
{
  bool forward = true;
  if ( !params.empty() && !_wcsicmp( params[0].c_str(), L"back" ) )
    forward = false;

  if ( forward )
  {
    do
		{
			++activeScreen;
			if ( activeScreen >= GetScreens().size() )
				activeScreen = -1;
		} while ( activeScreen > 0 && GetScreens()[activeScreen].IsEmpty() );
  }
  else
  {
    do
		{
			--activeScreen;
			if ( activeScreen < -1 )
        activeScreen = GetScreens().size() - 1;
		} while ( activeScreen > 0 && GetScreens()[activeScreen].IsEmpty() );
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDebug
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_CMD( add_debug_var, NDebug::AddDebugVar );
REGISTER_DEV_CMD( remove_debug_var, NDebug::RemoveDebugVar );
REGISTER_DEV_CMD( debug_var_page, NDebug::SetDebugVarPage );
REGISTER_DEV_CMD( watch_debug_var, NDebug::WatchDebugVar );
REGISTER_DEV_CMD( list_debug_vars, NDebug::ListAllDebugVars );
REGISTER_DEV_CMD( toggle_debug_var, NDebug::ToggleVarsCommand );
