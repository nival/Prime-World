#ifndef WINDOWPOINTJOB_H_INCLUDED
#define WINDOWPOINTJOB_H_INCLUDED

#include "Window.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сумасшедшая конструкция для перебора окон, расположенных под заданной точкой,
// с поддержкой конвертации координат 2D <-> 3D и захвата мышки
class WindowPointJob : public IWindowJob
{
public:
  WindowPointJob();
  WindowPointJob( const Point & _point );
  void SetPoint( const Point & _point ) { unconverted = _point; point = _point; }
  void SetCaptureTarget( Window * capture, bool _ignoreCapturedRect ) { captureTarget = capture; ignoreCapturedRect = _ignoreCapturedRect; }
  void SetIgnoreWindow( Window * ignore ) { ignoreWindow = ignore; }

protected:
  //Конвертация координат для 3D-окон
  Point   unconverted, point;

  //Будет игнорится это окно и все его чилды
  Window * ignoreWindow;
  //
  bool    ignoreCapturedRect;

  //Для обработки только captureTarget и окон ниже
  Window * captureTarget;
  bool    processingCaptured;

  virtual EWindowJobCode::Enum BeforeChildren( Window * target );
  virtual EWindowJobCode::Enum AfterChildren( Window * target );
  virtual bool Act( Window * target ) = 0;
};

} //namespace UI

#endif //WINDOWPOINTJOB_H_INCLUDED
