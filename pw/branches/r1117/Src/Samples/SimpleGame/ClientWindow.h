#ifndef CLIENTWINDOW_H_E72E1888_0560_4D7
#define CLIENTWINDOW_H_E72E1888_0560_4D7

#include "DebugDraw.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

class LocationClient;

class ClientWindow : public IDebugDraw, public CObjectBase
{
  OBJECT_BASIC_METHODS( ClientWindow )

public:

  ClientWindow();
  virtual ~ClientWindow();

  bool InitWindow( HINSTANCE hInstance, int _width, int _height );
  void Run();

  void Paint();
  void OnLButtonDown( int _x, int _y );
  void OnRButtonDown( int _x, int _y );

  void SetLocationClient( LocationClient* _locationClient ) { locationClient = _locationClient; }


  // from IDebugDraw
  virtual bool Clear();
  virtual void Invalidate();
  virtual void DrawLine( int x1, int y1, int x2, int y2, const Color& color );

private:

  bool PumpMessages();

  HWND hWnd;

  int width;
  int height;

  struct Line
  {
    int x1, y1, x2, y2;
    Color color;
    Line() : x1(0), y1(0), x2(0), y2(0) {}
  };

  typedef nstl::vector<Line> LineList;
  LineList lineList;

  threading::Event dataReady;
  threading::Event dataDrawn;

  CPtr<LocationClient> locationClient;
};

} // namespace Location

#endif //#define CLIENTWINDOW_H_E72E1888_0560_4D7