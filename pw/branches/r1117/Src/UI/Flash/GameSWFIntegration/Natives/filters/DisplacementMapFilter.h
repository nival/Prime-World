#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{
class ScriptObject;
class BitmapDataObject;


class DisplacementMapFilterObject: public BitmapFilterObject
{
public:
  DisplacementMapFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~DisplacementMapFilterObject(void) {}

  uint get_componentY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_componentY" );
    return (uint)0;
  }

  double get_alpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_alpha" );
    return (double)0;
  }

  void set_mode(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_mode" );
    return (void)0;
  }

  void set_mapPoint(ScriptObject/*Point*/ * value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_mapPoint" );
    return (void)0;
  }

  void set_alpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_alpha" );
    return (void)0;
  }

  AvmString get_mode()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_mode" );
    return (AvmString)0;
  }

  BitmapDataObject* get_mapBitmap()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_mapBitmap" );
    return (BitmapDataObject*)0;
  }

  void set_color(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_color" );
    return (void)0;
  }

  double get_scaleX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_scaleX" );
    return (double)0;
  }

  double get_scaleY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_scaleY" );
    return (double)0;
  }

  uint get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_color" );
    return (uint)0;
  }

  ScriptObject/*Point*/ * get_mapPoint()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_mapPoint" );
    return (ScriptObject/*Point*/ *)0;
  }

  void set_componentX(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_componentX" );
    return (void)0;
  }

  void set_componentY(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_componentY" );
    return (void)0;
  }

  uint get_componentX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "get_componentX" );
    return (uint)0;
  }

  void set_scaleX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_scaleX" );
    return (void)0;
  }

  void set_mapBitmap(BitmapDataObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_mapBitmap" );
    return (void)0;
  }

  void set_scaleY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DisplacementMapFilterObject", "set_scaleY" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_DisplacementMapFilterObject;
};
  
class DisplacementMapFilterClass : public ClassClosure
{
public:
  DisplacementMapFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~DisplacementMapFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) DisplacementMapFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_DisplacementMapFilterClass;
};

}