#include "stdafx.h"

#include "WindowPointJob.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowPointJob::WindowPointJob() :
ignoreWindow( 0 ),
ignoreCapturedRect( false ),
captureTarget( 0 ),
processingCaptured( false )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowPointJob::WindowPointJob( const Point & _point ) :
unconverted( _point ), point( _point ),
ignoreCapturedRect( false ),
captureTarget( 0 ),
processingCaptured( false )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EWindowJobCode::Enum WindowPointJob::BeforeChildren( Window * target )
{
  if( target == ignoreWindow )
    return EWindowJobCode::ReturnNull;

  if( !target->IsVisible() )
    return EWindowJobCode::ReturnNull;

  if( target->Is3D() )
  {
    point = unconverted;
    target->ConvertCoordinates( &point );
  }

  if ( captureTarget )
    if ( !processingCaptured )
      if( target == captureTarget )
        processingCaptured = true;

  return EWindowJobCode::Ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EWindowJobCode::Enum WindowPointJob::AfterChildren( Window * target )
{
  bool useRect = !( captureTarget && ( target == captureTarget ) && ignoreCapturedRect );
  bool check = !useRect || target->IsInsideWindow( point );

  if( target->Is3D() )
    point = unconverted;

  if ( captureTarget )
  {
    if ( processingCaptured )
    {
      if ( target == captureTarget )
        processingCaptured = false;
    }
    else
    {
      if ( target != captureTarget )
        return EWindowJobCode::ReturnNull;
    }
  }

  if ( !check )
    return EWindowJobCode::ReturnNull;

  EWindowJobCode::Enum result = Act( target ) ? EWindowJobCode::ReturnThis : EWindowJobCode::ReturnNull;
  return result;
}

} //namespace UI
