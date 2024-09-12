#include "TamarinPCH.h"

#include "MorphShape.h"
#include "FlashMeshCollection.h"

#include "../../MorphData.h"
#include "../../ShapeData.h"
#include "../../FlashMovie.h"

#include "System/InlineProfiler.h"

namespace
{
  static NDebug::DebugVar<unsigned int> totalMorphShapeCount( "TotalMorphShapeCount", "PerfCnt" );

  static bool flashTest2 = true;
  REGISTER_DEV_VAR( "flashTest2", flashTest2, STORAGE_NONE );
}

namespace avmplus
{

MorphShapeObject::MorphShapeObject( MorphShapeClass * classType ) : 
  DisplayObjectObject((DisplayObjectClass*)classType)
{
  Initialize();
}

MorphShapeObject::MorphShapeObject( VTable* ivtable, ScriptObject* prototype ) : 
  DisplayObjectObject(ivtable, prototype)
{
  Initialize();
}

void MorphShapeObject::Initialize()
{
  totalMorphShapeCount.AddValue(1);
  NI_ASSERT(totalMorphShapeCount.GetValue()<2000, "Flash : Morph count > 2000");
}

MorphShapeObject::~MorphShapeObject()
{
   totalMorphShapeCount.DecValue(1);
}

void MorphShapeObject::SetMorphData( flash::MorphData* _morphData ) 
{ 
  morphData = _morphData; 
}

void MorphShapeObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  NI_PROFILE_FUNCTION

  GraphicsObject* currentGraphics = morphData->GetGraphicsAtRatio( GetRatio(), FlashCore() );

  if ( currentGraphics )
  {
    if ( useParentScale9Grid )
    {
      _renderer->SetScale9Grid( scale9ConstX, scale9ConstY, trans9Const );
      currentGraphics->DoRender( _renderer, GetMatrix(), _cxform, _worldMode );
      _renderer->ResetScale9Grid();
    }
    else
    {
      currentGraphics->DoRender( _renderer, _matrix, _cxform, _worldMode );
    }
  }
}

void MorphShapeObject::GetBounds( flash::SWF_RECT& _rect )
{
  GraphicsObject* currentGraphics = morphData->GetGraphicsAtRatio( GetRatio(), FlashCore() );

  if ( currentGraphics )
    currentGraphics->GetBounds( _rect );
}

bool MorphShapeObject::HitTest( const flash::SWF_POINT & worldPoint )
{
  GraphicsObject* currentGraphics = morphData->GetGraphicsAtRatio( GetRatio(), FlashCore() );

  if ( currentGraphics )
  {
    flash::SWF_POINT localPoint;
    GlobalToLocal( localPoint, worldPoint );
    return currentGraphics->HitTest( localPoint );
  }

  return DisplayObjectObject::HitTest( worldPoint );
}


}

