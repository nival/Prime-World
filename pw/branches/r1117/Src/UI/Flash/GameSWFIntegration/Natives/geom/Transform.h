#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

#include "../../SwfTypes.h"
#include "../../FlashBaseClasses.h"

#include "Matrix3D.h"
#include "PerspectiveProjection.h"

namespace avmplus
{

class ScriptObject;

class TransformObject: public FlashScriptObject
{
public:
  TransformObject( TransformClass * classType );
  TransformObject( VTable* ivtable, ScriptObject* prototype );
  ~TransformObject() {}

  // AS3 methods

  void set_matrix(ScriptObject/*Matrix*/ * value);
  ScriptObject/*Matrix*/ * get_matrix();

  void set_colorTransform(ScriptObject/*ColorTransform*/ * value);
  ScriptObject/*ColorTransform*/ * get_colorTransform();

  ScriptObject/*Matrix*/ * get_concatenatedMatrix() { NI_ALWAYS_ASSERT("Not implemented"); return 0; }
  Matrix3DObject* getRelativeMatrix3D(AvmBox relativeTo) { NI_ALWAYS_ASSERT("Not implemented"); return 0; }
  ScriptObject/*ColorTransform*/ * get_concatenatedColorTransform() { NI_ALWAYS_ASSERT("Not implemented"); return 0; }
  ScriptObject/*Rectangle*/ * get_pixelBounds() { NI_ALWAYS_ASSERT("Not implemented"); return 0; }

  AvmBox set_matrix3D(Matrix3DObject* m) { matrix3D = m; return undefinedAtom; }
  Matrix3DObject* get_matrix3D() { return matrix3D; }

  void set_perspectiveProjection(PerspectiveProjectionObject* pm) { perspectiveProjection = pm; }
  PerspectiveProjectionObject* get_perspectiveProjection() { return perspectiveProjection; }

  // own methods

  // Matrix & Color Transform returns as non const

  void SetMatrix( const flash::SWF_MATRIX& value ) { matrix = value; }
  flash::SWF_MATRIX& GetMatrix() { return matrix; }
  const flash::SWF_MATRIX& GetMatrix() const { return matrix; }

  void SetColorTransform( const flash::SWF_CXFORMWITHALPHA& value ) { colorTransform = value; }
  flash::SWF_CXFORMWITHALPHA& GetColorTransform() { return colorTransform; }
  const flash::SWF_CXFORMWITHALPHA& GetColorTransform() const { return colorTransform; }

private:
  void Initialize();

  DRCWB( PerspectiveProjectionObject* ) perspectiveProjection;
  DRCWB( Matrix3DObject* ) matrix3D;
  DRCWB( ScriptObject* ) scriptColorTransform;
  DRCWB( ScriptObject* ) scriptMatrix;

  // Color transform slots

  int _c_0_0; // _redMultiplier;
  int _c_1_0; // _greenMultiplier;
  int _c_2_0; // _blueMultiplier;
  int _c_3_0; // _alphaMultiplier;
  int _c_0_1; // _redOffset;
  int _c_1_1; // _greenOffset;
  int _c_2_1; // _blueOffset;
  int _c_3_1; // _alphaOffset;

  // matrix slots
  int _m_0_0;// ScaleX <-> a
  int _m_1_1;// ScaleY <-> d
  int _m_1_0;// RotateSkew0 <-> b
  int _m_0_1;// RotateSkew1 <-> c
  int _m_0_2;// TranslateX <-> tx
  int _m_1_2;// TranslateY <-> ty

  flash::SWF_MATRIX matrix;
  flash::SWF_CXFORMWITHALPHA colorTransform;

  DECLARE_SLOTS_TransformObject;
};

DECLARE_AS_CLASS_WITH_CACHE( TransformClass, ClassClosure, TransformObject )

}