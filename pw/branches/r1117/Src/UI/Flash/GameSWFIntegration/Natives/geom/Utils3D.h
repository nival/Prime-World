#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class Matrix3DObject;
class ScriptObject;
class DoubleVectorObject;


class Utils3DObject: public ScriptObject
{
public:
  Utils3DObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~Utils3DObject(void) {}


private:
  DECLARE_SLOTS_Utils3DObject;
};
  
class Utils3DClass : public ClassClosure
{
public:
  Utils3DClass(VTable *vtable): ClassClosure(vtable){}
  ~Utils3DClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) Utils3DObject(ivtable, prototype);
  }  
  
  Matrix3DObject* pointTowards(double percent, Matrix3DObject* mat, ScriptObject/*Vector3D*/ * pos, ScriptObject/*Vector3D*/ * at, ScriptObject/*Vector3D*/ * up)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Utils3DClass", "pointTowards" );
    return (Matrix3DObject*)0;
  }

  ScriptObject/*Vector3D*/ * projectVector(Matrix3DObject* m, ScriptObject/*Vector3D*/ * v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Utils3DClass", "projectVector" );
    return (ScriptObject/*Vector3D*/ *)0;
  }

  void projectVectors(Matrix3DObject* m, DoubleVectorObject* verts, DoubleVectorObject* projectedVerts, DoubleVectorObject* uvts)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Utils3DClass", "projectVectors" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_Utils3DClass;
};

}