#include "stdafx.h"
#include "FrameTimeRender.h"
#include "System/LogFileName.h"
#include "System/SyncProcessorState.h"
#include "Render/Renderer.h"
#include "Render/UIRenderer.h"
#include "Render/smartrenderer.h"

#include "FontRender.h"
#include "Resolution.h"
#include "SkinStyles.h"
#include "Version.h"


namespace NDebug
{

static NDebug::DebugVar<float> FPSshortPeriod( "FPS", "FPS" );
static NDebug::DebugVar<bool> HasTrancieverData( "HasTrancieverData", "HasTrancieverData" );
static NDebug::DebugVar<int> DataBufferSize( "DataBufferSize", "DataBufferSize" );

static bool showFPS = false;
//static float FPSshortPeriod = 0.f;
static float FPSlongPeriod = 0.f;
static float FPSMAXlongPeriod = 0.f;
static float FPSMINlongPeriod = 0.f;
static float FPSshortPeriod_Inter = 0.f;
static float FPSlongPeriod_Inter = 0.f;
static float FPSMAXlongPeriod_Inter = -FLT_MAX;
static float FPSMINlongPeriod_Inter = FLT_MAX;
static int countShortPeriod = 0;
static int countLongPeriod = 0;
static float shortPeriod = 0.f;
static float longPeriod = 0.f;

static const float AggregationPeriod = 0.5f; //0.3 sec
static float noDataTime = 0;
static int srv2ClientTimeDelta = 0;
static bool showSrvTime = false;

static bool g_showBufferInfo = true; 
REGISTER_DEV_VAR( "show_buffer_info", g_showBufferInfo, STORAGE_NONE );

#ifdef _SHIPPING
static bool g_showInfoGraph = false;
#else
static bool g_showInfoGraph = true;
#endif
REGISTER_VAR( "show_info_graph", g_showInfoGraph, STORAGE_NONE );


static int lastStep = 0;

static void DrawStringLAligned( const wstring& text, int x, int y, const string& style, const Render::Color& color )
{
  UI::IFontStyle* fontStyle = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( style ) );
  if ( !fontStyle )
    return;

  fontStyle->DrawString( text.c_str(), text.size(), x, y, color, UI::GetFontRenderer()->GetNoCropRect() );
}


void ShowTime()
{
  if (!showSrvTime)
    return;

  if ( Render::GetRenderer()->DeviceIsLost() )
    return;

  const Render::Color drawColor( 255, 255, 128, 255 );
  const int screenWidth = UI::GetUIScreenResolution().x;

  __time32_t timeLocal = _time32(0);
  if (timeLocal > 0)
  {
    __time32_t timeToDraw = timeLocal - srv2ClientTimeDelta;
    struct tm serverTime;
    _gmtime32_s(&serverTime, &timeToDraw);

    DrawStringLAligned( NStr::StrFmtW( L"%02d:%02d", serverTime.tm_hour, serverTime.tm_min ), screenWidth/2-20, 5, "herobars", drawColor );
  }
}


void ShowFPS()
{
  if ( Render::GetRenderer()->DeviceIsLost() )
    return;

  if ( !showFPS )
    return;


  if( NGlobal::GetVar( "debug_crc_mode" ).Get<int>() == 2 )
  { 
    NDebug::IDebugVar * dbgVar = NDebug::FindDebugVar( L"calc_crc_time" );
    if ( dbgVar )
    {
      wchar_t buff[64] = L"";
      dbgVar->FormatValue( buff, ARRAY_SIZE(buff) );

      if ( g_showInfoGraph )
      {
        char buf[64];
        _snprintf( buf, 63, "CRC: %S", buff );
        debugDisplay::AddText( "__pos2", debugDisplay::Align( -1, -1 ), buf );
      }
      else
      {
        debugDisplay::Remove("__pos2");
      }
    }
  }
}



void SetFrameTime( float frameTime )
{
  if ( frameTime == 0.0f )
    frameTime = 0.001f;

  const float SHORT_LENGTH = 1.5f; // 3 sec.
  const float LONG_LENGTH = 4.0f; // 3 sec.

  float FPS = 1.0f / frameTime;

  FPSshortPeriod_Inter += frameTime;
  FPSlongPeriod_Inter += frameTime;

  FPSMAXlongPeriod_Inter = max( FPSMAXlongPeriod_Inter, FPS );
  FPSMINlongPeriod_Inter = min( FPSMINlongPeriod_Inter, FPS );

  countShortPeriod++;
  countLongPeriod++;

  shortPeriod += frameTime;
  longPeriod += frameTime;

  if ( shortPeriod > SHORT_LENGTH )
  {
    if ( FPSshortPeriod_Inter > 0.f )
    {
      float value = float( countShortPeriod ) / FPSshortPeriod_Inter;
      FPSshortPeriod.SetValue( value, value < 10.0f );
    }

    FPSshortPeriod_Inter = 0.f;

    shortPeriod = 0.f;
    countShortPeriod = 0;

    char buf[64];
    _snprintf( buf, 63, "FPS: %d", (int)FPSshortPeriod.GetValue(), (int)FPSMINlongPeriod, (int)FPSMAXlongPeriod );

    debugDisplay::AddText( "__pos1", debugDisplay::Align( -1, -1 ), buf, FPSshortPeriod.IsWarning() ? debugDisplay::Color::Red : debugDisplay::Color::White, true );
  }

  if ( longPeriod > LONG_LENGTH )
  {
    FPSMAXlongPeriod = FPSMAXlongPeriod_Inter;
    FPSMAXlongPeriod_Inter = -FLT_MAX;

    FPSMINlongPeriod = FPSMINlongPeriod_Inter;
    FPSMINlongPeriod_Inter = FLT_MAX;

    if ( FPSlongPeriod_Inter > 0 )
      FPSlongPeriod = float( countLongPeriod ) / FPSlongPeriod_Inter; 

    FPSlongPeriod_Inter = 0.f;

    longPeriod = 0.f;
    countLongPeriod = 0;

    debugDisplay::Align align( +1, -1 );

    char buf[64];
    _snprintf( buf, 63, "FPS: %d", (int)FPSlongPeriod, (int)FPSMINlongPeriod, (int)FPSMAXlongPeriod );

    debugDisplay::AddText( "__pos1", debugDisplay::Align( -1, -1 ), buf, FPSshortPeriod.IsWarning() ? debugDisplay::Color::Red : debugDisplay::Color::White, true );
  }

  if ( g_showInfoGraph )
  {
    debugDisplay::AddGraph( "fps graph", debugDisplay::Align( +1, -1 ), (int)FPS, debugDisplay::GraphInfo( 64, 180, true ) );
  }
  else
  {
    debugDisplay::Remove("fps graph");
  }
}


void SetSteps( int _recieveStep, int _nextStep, float  dt, int bufferLimit)
{
  if ( _nextStep >= 0 )
  {
    if (_recieveStep < 0)
      noDataTime += dt;
    else
      noDataTime = 0;

    HasTrancieverData.SetValue( noDataTime < AggregationPeriod );
  }

  if (!g_showBufferInfo)
    return;

  if ( _nextStep >= 0 )
  {
    if ( _recieveStep < 0 )
      DataBufferSize.SetValue( -1, true );
    else
      DataBufferSize.SetValue( _recieveStep - _nextStep, _recieveStep - _nextStep > 5 );

    if ( _nextStep != lastStep )
    {
      lastStep = _nextStep;

      debugDisplay::Align align( -1, -1 );
      debugDisplay::Color::Enum color = DataBufferSize.IsWarning() ? debugDisplay::Color::Red : debugDisplay::Color::White;
      debugDisplay::AddGraph( "buffer", align, DataBufferSize.GetValue(), debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, color, false ) );

      if ( g_showInfoGraph )
      {
        debugDisplay::SetNewGraphInfo( "buffer", debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, color, true ) );
        debugDisplay::AddValue( "buffer limit", align, bufferLimit );
      }
      else
      {
        debugDisplay::Remove("buffer limit");
        debugDisplay::SetNewGraphInfo( "buffer", debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, color, false ) );
      }
    }
  }
}



void DumpSystemStatistics()
{
  const NHPTimer::FTime DumpPeriod = 30.0f;

  static NHPTimer::FTime nextDumpTime = 0;

  NHPTimer::FTime now = NHPTimer::GetScalarTime();
  if ( now < nextDumpTime )
    return;

  nextDumpTime = now + DumpPeriod;

  size_t virtualSize = 0;
  utils::GetMemoryStatus( virtualSize );
  MessageTrace( "Virtual Memory Usage: %u mb", virtualSize / ( 1024 * 1024 ) );
}


void SetSrv2ClientTimeDelta(int timeDelta)
{
  srv2ClientTimeDelta = timeDelta;
}


void ShowSrvTime(bool _showSrvTime)
{
  showSrvTime = _showSrvTime;
}


} //namespace NDebug












namespace debugDisplay
{


int Align::Sign( int i )
{
  if ( i < 0 )
    return -1;
  if ( i > 0 )
    return +1;
  return 0;
}


class Element : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Element, BaseObjectST );
public:
  Element( const char * _id, const Align & _align, Color::Enum _color, bool _bigFont ) :
  id ( _id ),
  align( _align ),
  color( _color ),
  bigFont( _bigFont )
  {
    SetVisual( color, bigFont );
  }

  const string & Id() const { return id; }
  const Align & GetAlign() const { return align; }

  void SetVisual( Color::Enum _color, bool _bigFont )
  {
    color = _color;
    if ( !style || ( bigFont != _bigFont ) ) {
      bigFont = _bigFont;
      style = UI::GetFontRenderer()->GetFontStyle( UI::SkinStyles::GetFontStyle( _bigFont ? "FPSMain" : "FPSAvg" ) );
    }
  }

  virtual int Height() { return style->GetMetric().RowStep(); }
  virtual void Render( int x ) = 0;

protected:
  static const Render::Color & RenderColor( Color::Enum c ) {
    static Render::Color
      white( 255, 255, 255 ),
      red( 255, 0, 0 ),
      green( 0, 255, 0 ),
      blue( 0, 0, 255 ),
      cyan( 0, 255, 255 ),
      yellow( 255, 255, 0 );

    switch ( c ) {
      default:
      case Color::White:    return white;
      case Color::Red:      return red;
      case Color::Green:    return green;
      case Color::Blue:     return blue;
      case Color::Cyan:     return cyan;
      case Color::Yellow:   return yellow;
    }
  }

  const Render::Color & RenderColor() const { return RenderColor( color ); }

  void DrawText( const wstring & text, int y, int horAlign, bool bigFont )
  {
    const int screenWidth = UI::GetUIScreenResolution().x;

	  if ( !style )
		  return;

    const int margin = 10;
    int x = margin;
    if ( horAlign == 0 )
      x = ( screenWidth - (int)style->GetStringLength( text.c_str(), text.size() ) ) / 2;
    else if ( horAlign > 0 )
      x = screenWidth - margin - (int)style->GetStringLength( text.c_str(), text.size() );

	  style->DrawString( text.c_str(), text.size(), x, y, RenderColor(), UI::GetFontRenderer()->GetNoCropRect() );
  }

protected:
  string id;
  Align align;
  Color::Enum color;
  bool bigFont;
  Strong<UI::IFontStyle> style;
};



class TextElement : public Element
{
  NI_DECLARE_REFCOUNT_CLASS_1( TextElement, Element );
public:
  TextElement( const char * _id, const Align & _align, Color::Enum _color, const char * _text, bool _bigFont ) :
  Element( _id, _align, _color, _bigFont ),
  text( _text )
  {
    SetText( _text );
  }

  void SetText( const char * _text ) {
    text = _text;
    cachedText = NStr::StrFmtW( L"%S", text.c_str() );
  }

  virtual void Render( int y ) {
    DrawText( cachedText, y, align.hor, false );
  }

private:
  string text;
  wstring cachedText;
};



class ValueElement : public Element
{
  NI_DECLARE_REFCOUNT_CLASS_1( ValueElement, Element );
public:
  ValueElement( const char * _id, const Align & _align, Color::Enum _color, double _val, bool _bigFont ) :
  Element( _id, _align, _color, _bigFont ),
  value( _val )
  {
    SetValue( _val );
  }

  void SetValue( double _val ) {
    value = _val;
    cachedText = NStr::StrFmtW( L"%S: %g", Id().c_str(), value );
  }

  virtual void Render( int y ) {
    DrawText( cachedText, y, align.hor, false );
  }

private:
  double value;
  wstring cachedText;
};



class GraphElement : public Element
{
  NI_DECLARE_REFCOUNT_CLASS_1( GraphElement, Element );
public:
  GraphElement( const char * _id, const Align & _align, const GraphInfo & _info ) :
    Element( _id, _align, Color::White, false ),
    info( _info ),
    lastVal( 0 ),
    pos( 0 ), len( 0 ),
    data( _info.limit, 0 )
  {
    cachedText = NStr::StrFmtW( L"%S", Id().c_str() );
  }

  void AddValue( int _value ) {
    NI_VERIFY( !data.empty(), "", return );
    data[pos] = Max( 0, _value );
    len = Min( len + 1, data.size() );
    pos = ( pos + 1 ) % data.size();
    lastVal = _value;
  }

  void SetNewGraphInfo( const GraphInfo& _info )
  {
    info = _info;
  }

  virtual int Height() { return info.uiheight; }

  virtual void Render( int y ) {
    NI_VERIFY( !data.empty(), "", return );
    if ( !len )
      return;

    const int uiScreenWidth = UI::GetUIScreenResolution().x, displayScreenWidth = UI::GetScreenResolution().x;
    const int width = len * 2 * uiScreenWidth / displayScreenWidth;

    const int margin = 10;
    int x = margin + width;
    if ( GetAlign().hor == 0 )
      x = ( uiScreenWidth - width ) / 2 + width;
    else if ( GetAlign().hor > 0 )
      x = uiScreenWidth - margin;

    int maxv = data[pos];
    int minv = INT_MAX;
    for ( int i = 0; i < len; ++i ) {
      int idx = ( pos + data.size() - i ) % data.size();
      int v = data[idx];
      minv = Min( minv, v );
      maxv = Max( maxv, v );
    }

    cachedText = NStr::StrFmtW( L"%S: %d (%d, %d)", Id().c_str(), lastVal, minv, maxv );
    DrawText( cachedText, y + info.uiheight - Element::Height(), align.hor, false );

    if ( !info.needRenderGraph )
      return;

    if ( maxv <= 0 )
      return;

    int heightScreen = info.uiheight * displayScreenWidth / uiScreenWidth - 4;
    UI::Point screenPoint = UI::ConvertToScreen( UI::Point( x, y + info.uiheight - 2 ) );

    const Render::Color & clr = RenderColor( info.graphColor );
    const float lineWidth = 1.0f;
    const float lineIncr = lineWidth + 1.0f;

    for ( int i = 0; i < len; ++i ) {
      int idx = ( pos + data.size() - i ) % data.size();
      int v = data[idx];
      int h = v * heightScreen / maxv;
      
      Render::SmartRenderer::AddLine(screenPoint.x, screenPoint.y, screenPoint.x, screenPoint.y - h, clr.R, clr.G, clr.B, lineWidth);
      
      screenPoint.x -= lineIncr;
    }
  }
  
private:
  GraphInfo info;
  vector<int> data;
  int lastVal;
  int pos, len;
  wstring cachedText;
};




inline bool operator < ( const Align & a, const Align & b )
{
  if ( a.hor < b.hor )
    return true;
  if ( a.hor > b.hor )
    return false;
  return a.ver < b.ver;
}


inline bool operator == ( const Align & a, const Align & b )
{
  return ( a.hor == b.hor ) && ( a.ver == b.ver );
}

inline bool operator != ( const Align & a, const Align & b ) { return !operator == ( a, b ); }


typedef map<string, Strong<Element>> Elements;

static int drawMode = 0;
static Elements elements;
static int topMargin = 0;


void UserControlImpulse()
{
  drawMode = !drawMode;
}


void SetTopMargin( int _topMargin )
{
  topMargin = _topMargin;
}


void Render()
{
  if ( Render::GetRenderer()->DeviceIsLost() || !drawMode )
    return;

  const int screenHeight = UI::GetUIScreenResolution().y;

  for ( int ha = -1; ha <= +1; ha += 1 )
    for ( int va = -1; va <= +1; va += 1 )
    {
      if ( !ha && !va )
        continue;

      int height = 0;
      for ( Elements::iterator it = elements.begin(); it != elements.end(); ++it )
      {
        Element * e = it->second;
        if ( ( e->GetAlign().hor != ha ) || ( e->GetAlign().ver != va ) )
          continue;

        height += e->Height();
      }

      int margin = ( ha != 0 && va == -1 ) ? topMargin : 10;
      int y = margin;
      if ( va == 0 )
        y = ( screenHeight - height ) / 2;
      else if ( va > 0 )
        y = screenHeight - margin - height;

      for ( Elements::iterator it = elements.begin(); it != elements.end(); ++it )
      {
        Element * e = it->second;
        if ( ( e->GetAlign().hor != ha ) || ( e->GetAlign().ver != va ) )
          continue;

        e->Render( y );
        y += e->Height();
      }

    }
}



void AddText( const char * id, const Align & align, const char * text, Color::Enum color, bool bigFont )
{
  Strong<Element> & e = elements[id];

  if ( e.Valid() )
    if ( TextElement * te = dynamic_cast<TextElement *>( e.Get() ) )
    {
      te->SetText( text );
      te->SetVisual( color, bigFont );
      return;
    }

  e = new TextElement( id, align, color, text, bigFont );
}



void AddValue( const char * id, const Align & align, double value, Color::Enum color, bool bigFont )
{
  Strong<Element> & e = elements[id];

  if ( e.Valid() )
    if ( ValueElement * ve = dynamic_cast<ValueElement *>( e.Get() ) )
    {
      ve->SetValue( value );
      ve->SetVisual( color, bigFont );
      return;
    }

  e = new ValueElement( id, align, color, value, bigFont );
}



void AddGraph( const char * id, const Align & align, int value, const GraphInfo & info )
{
  Strong<Element> & e = elements[id];

  if ( e.Valid() )
    if ( GraphElement * ge = dynamic_cast<GraphElement *>( e.Get() ) )
    {
      ge->AddValue( value );
      return;
    }

  GraphElement * ge = new GraphElement( id, align, info );
  e = ge;
  ge->AddValue( value );
}


void SetNewGraphInfo( const char * id, const GraphInfo & info )
{
  Strong<Element> & e = elements[id];

  if ( e.Valid() )
  {
    if ( GraphElement * ge = dynamic_cast<GraphElement *>( e.Get() ) )
    {
      ge->SetNewGraphInfo( info );
    }
  }
}


void Remove( const char * id )
{
  elements.erase( id );
}


void Cleanup()
{
  elements.clear();
}

} //namespace debugDisplay



static bool ToggleFPSCommand( const char *name, const vector<wstring> &params )
{
  NDebug::showFPS = NDebug::showFPS ? false : true;

  debugDisplay::SetTopMargin(100);
  debugDisplay::UserControlImpulse();
  return true;
}

REGISTER_CMD( toggle_fps, ToggleFPSCommand );
