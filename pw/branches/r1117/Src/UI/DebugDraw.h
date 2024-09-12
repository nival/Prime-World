#ifndef DEBUGDRAW_H_INCLUDED
#define DEBUGDRAW_H_INCLUDED

//
// A tool for easy and effective debug drawing in UI coordinate space
//

#include "Defines.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
  class Color;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

namespace Debug
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Local color definition, to not drag render headers along
struct Color
{
  int r, g, b;
  Color() : r( 255 ), g( 255 ), b( 255 ) {}
  Color( int _r, int _g, int _b ) : r( _r ), g( _g ), b( _b ) {}
  operator Render::Color () const;
};

//
bool MouseTraceEnabled();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoint( const Point & p, float size, const Color & color );
void DrawLine( const Point & p0, const Point & p1, const Color & color );
void DrawRect( const Rect & rect, const Color & color );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions to draw long-lasting lines
static const float DurationInstant = 0.0f; //Will be skipped if other primitives are still lasting

void AddLine( const Point & p0, const Point & p1, const Color & color, float duration = DurationInstant );
void AddRect( const Rect & rect, const Color & color, float duration = DurationInstant );

void Step( float deltaTime );

} //namespace Debug

} //namespace UI

#endif //DEBUGDRAW_H_INCLUDED
