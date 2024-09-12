#pragma once

#include "../PlayerGlobalIncludes.h"
#include "DisplayObject.h"
#include "Graphics.h"

namespace flash
{
  class MorphData;
}

namespace avmplus
{

class MorphShapeObject: public DisplayObjectObject
{
public:

  MorphShapeObject( MorphShapeClass * classType );
  MorphShapeObject( VTable* ivtable, ScriptObject* prototype );
  ~MorphShapeObject();

  void SetMorphData( flash::MorphData* _morphData );

  virtual const char* GetDumpName() { return "<MorphShape>"; }

  virtual bool HitTest( const flash::SWF_POINT & worldPoint );

private:
  void Initialize();

  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  Weak<flash::MorphData> morphData;

  DECLARE_SLOTS_MorphShapeObject;
};

DECLARE_AS_CLASS_WITH_CACHE( MorphShapeClass, DisplayObjectClass, MorphShapeObject )

}