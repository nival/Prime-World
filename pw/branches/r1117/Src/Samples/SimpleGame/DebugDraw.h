#ifndef DEBUGDRAW_H_1DBEE054_8419_484D_A
#define DEBUGDRAW_H_1DBEE054_8419_484D_A

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

struct Color
{
  Color() : r( 0.f ), g( 0.f ), b( 0.f ) {}
  Color( float _r, float _g, float _b ) : r(_r), g(_g), b(_b) {}

  float r;
  float g;
  float b;
};

_interface IDebugDraw : IObjectBase
{
  virtual bool Clear() = 0;
  virtual void Invalidate() = 0;

  virtual void DrawLine( int x1, int y1, int x2, int y2, const Color& color = Color( 0, 0, 0 ) ) = 0;
};

} // namespace Location

#endif //#define DEBUGDRAW_H_1DBEE054_8419_484D_A