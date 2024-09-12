#pragma once

#include "System/SystemLog.h"

#include "../PlayerGlobalIncludes.h"
#include "../../FlashMovieAvmCore.h"

namespace avmplus
{
class Matrix3DObject;
class DoubleVectorObject;
class ScriptObject;
class ObjectVectorObject;


class Matrix3DObject: public ScriptObject
{
public:
  Matrix3DObject( Matrix3DClass * classType );
  Matrix3DObject( VTable* ivtable, ScriptObject* prototype );
  ~Matrix3DObject() {}

  void transpose()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "transpose" );
    return (void)0;
  }

  void prependTranslation(double x, double y, double z)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "prependTranslation" );
    return (void)0;
  }

  void set_rawData(DoubleVectorObject* v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "set_rawData" );
    return (void)0;
  }

  ScriptObject/*Vector3D*/ * deltaTransformVector(ScriptObject/*Vector3D*/ * v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "deltaTransformVector" );
    return (ScriptObject/*Vector3D*/ *)0;
  }

  ScriptObject/*Vector3D*/ * get_position()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "get_position" );
    return (ScriptObject/*Vector3D*/ *)0;
  }

  void pointAt(ScriptObject/*Vector3D*/ * pos, ScriptObject/*Vector3D*/ * at, ScriptObject/*Vector3D*/ * up)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "pointAt" );
    return (void)0;
  }

  void transformVectors(DoubleVectorObject* vin, DoubleVectorObject* vout)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "transformVectors" );
    return (void)0;
  }

  void prependRotation(double degrees, ScriptObject/*Vector3D*/ * axis, ScriptObject/*Vector3D*/ * pivotPoint)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "prependRotation" );
    return (void)0;
  }

  void prepend(Matrix3DObject* rhs)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "prepend" );
    return (void)0;
  }

  ScriptObject/*Vector3D*/ * transformVector(ScriptObject/*Vector3D*/ * v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "transformVector" );
    return (ScriptObject/*Vector3D*/ *)0;
  }

  void appendScale(double xScale, double yScale, double zScale)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "appendScale" );
    return (void)0;
  }

  ObjectVectorObject* decompose(AvmString orientationStyle)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "decompose" );
    return (ObjectVectorObject*)0;
  }

  ObjectVectorObject* get_rawData()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "get_rawData" );
    return (ObjectVectorObject*)0;
  }

  void interpolateTo(Matrix3DObject* toMat, double percent)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "interpolateTo" );
    return (void)0;
  }

  double get_determinant()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "get_determinant" );
    return (double)0;
  }

  bool invert()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "invert" );
    return (bool)0;
  }

  void appendTranslation(double x, double y, double z)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "appendTranslation" );
    return (void)0;
  }

  void appendRotation(double degrees, ScriptObject/*Vector3D*/ * axis, ScriptObject/*Vector3D*/ * pivotPoint)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "appendRotation" );
    return (void)0;
  }

  void set_position(ScriptObject/*Vector3D*/ * pos)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "set_position" );
    return (void)0;
  }

  void append(Matrix3DObject* lhs)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "append" );
    return (void)0;
  }

  void prependScale(double xScale, double yScale, double zScale)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "prependScale" );
    return (void)0;
  }

  void identity()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "identity" );
    return (void)0;
  }

  bool recompose(ObjectVectorObject* components, AvmString orientationStyle)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DObject", "recompose" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_Matrix3DObject;
};
  
class Matrix3DClass : public ClassClosure
{
public:
  Matrix3DClass(VTable *vtable): ClassClosure(vtable)
  {
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
    flashCore->GetClassCache().RegisterClass( EFlashClassID::Matrix3DClass, this );
  } 
  ~Matrix3DClass(){}

  DECLARE_CREATE_MEMBERS(Matrix3DObject)

  Matrix3DObject* interpolate(Matrix3DObject* thisMat, Matrix3DObject* toMat, double percent)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "Matrix3DClass", "interpolate" );
    return (Matrix3DObject*)0;
  }

private:
  DECLARE_SLOTS_Matrix3DClass;
};

}