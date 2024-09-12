#include "stdafx.h"

#include "Resolution.h"
#include "DebugDraw.h"
#include "../Render/DebugRenderer.h"

namespace UI
{

namespace Debug
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool traceMouse = false;
REGISTER_DEV_VAR( "ui_trace_mouse", traceMouse, STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const static float FadeOutTime = 0.3f;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPrimitive
{
  Color   color;
  float   timeleft;
  float   duration;
  SPrimitive() : timeleft( 0 ), duration( 0 ) {}
  SPrimitive( const Color & _color, float _duration ) : color( _color ), timeleft( _duration ), duration( _duration ) {}
};

struct SLine : SPrimitive
{
  Point   p0, p1;
  SLine() {}
  SLine( const Point & _p0, const Point & _p1, const Color & _color, float _duration ) : SPrimitive( _color, _duration ), p0( _p0 ), p1( _p1 ) {}
};

struct SRect : SPrimitive
{
  Rect    rect;
  SRect() {}
  SRect( const Rect & _rect, const Color & _color, float _duration ) : SPrimitive( _color, _duration ), rect( _rect ) {}
};

typedef list<SLine>  TLines;
typedef list<SRect>  TRects;

TLines  lines;
TRects  rects;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Color::operator Render::Color() const
{
  return Render::Color( (Render::Color::TValue)r, (Render::Color::TValue)g, (Render::Color::TValue)b, (Render::Color::TValue)255 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MouseTraceEnabled()
{
  return traceMouse;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoint( const Point & p, float size, const Color & color )
{
	const int x = p.x * GetScreenResolution().x / GetUIScreenResolution().x;
	const int y = p.y * GetScreenResolution().y / GetUIScreenResolution().y;
  Render::DebugRenderer::DrawPoint2D( x, y, size, color );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawLine( const Point & p0, const Point & p1, const Color & color )
{
	const int x1 = p0.x * GetScreenResolution().x / GetUIScreenResolution().x;
	const int y1 = p0.y * GetScreenResolution().y / GetUIScreenResolution().y;
	const int x2 = p1.x * GetScreenResolution().x / GetUIScreenResolution().x;
	const int y2 = p1.y * GetScreenResolution().y / GetUIScreenResolution().y;
	Render::DebugRenderer::DrawLine2D( x1, y1, x2, y2, color, color );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawRect( const Rect & rect, const Color & color )
{
  DrawLine( rect.GetLeftTop(), rect.GetRightTop(),        color );
  DrawLine( rect.GetRightTop(), rect.GetRightBottom(),    color );
  DrawLine( rect.GetRightBottom(), rect.GetLeftBottom(),  color );
  DrawLine( rect.GetLeftBottom(), rect.GetLeftTop(),      color );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddLine( const Point & p0, const Point & p1, const Color & color, float duration )
{
  if ( duration == DurationInstant )
  {
    if ( lines.empty() && rects.empty() )
      DrawLine( p0, p1, color );
  }
  else
    lines.push_back( SLine( p0, p1, color, duration ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddRect( const Rect & rect, const Color & color, float duration )
{
  if ( duration == DurationInstant )
  {
    if ( lines.empty() && rects.empty() )
      DrawRect( rect, color );
  }
  else
    rects.push_back( SRect( rect, color, duration ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point LerpPoint( const Point & from, const Point & to, float t )
{
  return Point( (int)( from.x * ( 1.0f - t ) + to.x * t + 0.5f ), (int)( from.y * ( 1.0f - t ) + to.y * t + 0.5f ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Step( float deltaTime )
{
  for( TLines::iterator l = lines.begin(); l != lines.end(); )
  {
    l->timeleft -= deltaTime;

    if ( l->timeleft > FadeOutTime )
      DrawLine( l->p0, l->p1, l->color );
    else if ( l->timeleft > 0 )
    {
      float t = 0.5f * ( 1.0f - l->timeleft / FadeOutTime );
      DrawLine( LerpPoint( l->p0, l->p1, t ), LerpPoint( l->p1, l->p0, t ), l->color );
    }
    
    TLines::iterator next = l;
    ++next;
    if( l->timeleft <= 0 )
      lines.erase( l );
    l = next;
  }

  for( TRects::iterator r = rects.begin(); r != rects.end(); )
  {
    r->timeleft -= deltaTime;
    
    if ( r->timeleft > FadeOutTime )
      DrawRect( r->rect, r->color );
    else if ( r->timeleft > 0 )
    {
      float t = 0.5f * ( 1.0f - r->timeleft / FadeOutTime );
      Rect rect( LerpPoint( r->rect.GetLeftTop(), r->rect.GetRightBottom(), t ), LerpPoint( r->rect.GetRightBottom(), r->rect.GetLeftTop(), t ) );
      DrawRect( rect, r->color );
    }

    TRects::iterator next = r;
    ++next;
    if( r->timeleft <= 0 )
      rects.erase( r );
    r = next;
  }
}

} //namespace Debug

} //namespace UI
