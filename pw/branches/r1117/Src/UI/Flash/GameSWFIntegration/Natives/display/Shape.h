#pragma once

#include "../PlayerGlobalIncludes.h"

#include "System/SystemLog.h"
#include "Graphics.h"
#include "DisplayObject.h"

namespace flash
{
  class SwfStreamReader;
  class SWFParser;
}

namespace avmplus
{

class ShapeObject: public DisplayObjectObject
{
public:

  ShapeObject( ShapeClass * classType ) : DisplayObjectObject((DisplayObjectClass*)classType) { Initialize(); }
  ShapeObject( VTable* ivtable, ScriptObject* prototype ) : DisplayObjectObject(ivtable, prototype) { Initialize(); }
  ~ShapeObject();

  // AS methods

  GraphicsObject* get_graphics() { return graphics; }

  // own methods

  virtual void OnSetCharacterID( int id );

  virtual const char* GetDumpName() { return "<Shape>"; }

  virtual bool HitTest( const flash::SWF_POINT & worldPoint );

  void SetShape( const flash::ShapeDefinition& _shapeDesc ); //const-reference это для девочек!!!

private:

  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  void Initialize();

  DRCWB( GraphicsObject* ) graphics;

  DECLARE_SLOTS_ShapeObject;
};

DECLARE_AS_CLASS_WITH_CACHE( ShapeClass, DisplayObjectClass, ShapeObject )

}