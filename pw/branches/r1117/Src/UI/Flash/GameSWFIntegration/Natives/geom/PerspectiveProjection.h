#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ScriptObject;
class Matrix3DObject;


class PerspectiveProjectionObject: public ScriptObject
{
public:
  PerspectiveProjectionObject( PerspectiveProjectionClass * classType );
  PerspectiveProjectionObject( VTable* ivtable, ScriptObject* prototype );
  ~PerspectiveProjectionObject() {}

  ScriptObject/*Point*/ * get_projectionCenter()
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "get_projectionCenter" );
    return (ScriptObject/*Point*/ *)0;
  }

  Matrix3DObject* toMatrix3D()
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "toMatrix3D" );
    return (Matrix3DObject*)0;
  }

  double get_fieldOfView()
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "get_fieldOfView" );
    return (double)0;
  }

  AvmBox set_projectionCenter(ScriptObject/*Point*/ * p)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "set_projectionCenter" );
    return (AvmBox)0;
  }

  double get_focalLength()
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "get_focalLength" );
    return (double)0;
  }

  void set_fieldOfView(double fieldOfViewAngleInDegrees)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "set_fieldOfView" );
    return (void)0;
  }

  void set_focalLength(double value)
  {
    //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "PerspectiveProjectionObject", "set_focalLength" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_PerspectiveProjectionObject;
};
  
DECLARE_AS_CLASS_WITH_CACHE( PerspectiveProjectionClass, ClassClosure, PerspectiveProjectionObject )

}