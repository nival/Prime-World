#pragma once

#include "../PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{
class ArrayObject;


class ColorMatrixFilterObject: public BitmapFilterObject
{
public:
  ColorMatrixFilterObject(VTable *ivtable, ScriptObject *delegate);
  ~ColorMatrixFilterObject(void) {}

  ArrayObject* get_matrix();
  void set_matrix(ArrayObject* value);

  virtual void RealtimeBegin( Render::IFlashRenderer* _renderer );
  virtual void RealtimeEnd( Render::IFlashRenderer* _renderer );

private:

  void CopyInternalToExternal();
  void CopyExternalToInternal();

  SHMatrix colorMatrix;
  CVec4 addColor;
  
  DRCWB( ArrayObject* ) externalColorMatrix;

  DECLARE_SLOTS_ColorMatrixFilterObject;
};
  
class ColorMatrixFilterClass : public ClassClosure
{
public:
  ColorMatrixFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~ColorMatrixFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ColorMatrixFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ColorMatrixFilterClass;
};

}