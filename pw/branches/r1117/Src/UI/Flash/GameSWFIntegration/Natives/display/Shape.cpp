#include "TamarinPCH.h"

#include "Shape.h"
#include "../../FlashMovieAvmCore.h"

#include "System/InlineProfiler.h"

namespace
{
  static NDebug::DebugVar<unsigned int> totalShapeCount( "TotalShapeCount", "PerfCnt" );
}

namespace avmplus
{

void ShapeObject::Initialize()
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();

  Atom args[] = {0};

  GraphicsClass * graphicsClass = flashCore->GetClassCache().GetClass<GraphicsClass>( EFlashClassID::GraphicsClass );
  graphics = (GraphicsObject *)flashCore->atomToScriptObject(graphicsClass->construct(0, args));

  totalShapeCount.AddValue(1);
  NI_ASSERT(totalShapeCount.GetValue()<9000, "Flash : Shape count > 9000");
}

ShapeObject::~ShapeObject()
{
  totalShapeCount.DecValue(1);
}

void ShapeObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  NI_PROFILE_HEAVY_FUNCTION

  if ( graphics )
  {
    if ( useParentScale9Grid )
    {
      _renderer->SetScale9Grid( scale9ConstX, scale9ConstY, trans9Const );
      graphics->DoRender( _renderer, GetMatrix(), _cxform, _worldMode );
      _renderer->ResetScale9Grid();
    }
    else
    {
      graphics->DoRender( _renderer, _matrix, _cxform, _worldMode );
    }
  }
}

void ShapeObject::GetBounds( flash::SWF_RECT& _rect )
{
  if ( graphics )
    graphics->GetBounds( _rect );
}

void ShapeObject::OnSetCharacterID( int id )
{
  if ( graphics )
    graphics->SetCharacterID( id, 0 );
}

void ShapeObject::SetShape( const flash::ShapeDefinition& _shapeDesc )
{
  if ( graphics )
    graphics->SetShape( _shapeDesc );
}

bool ShapeObject::HitTest( const flash::SWF_POINT & worldPoint )
{
  if ( graphics )
  {
    flash::SWF_POINT localPoint;
    GlobalToLocal( localPoint, worldPoint );
    return graphics->HitTest( localPoint );
  }

  return DisplayObjectObject::HitTest( worldPoint );
}


}