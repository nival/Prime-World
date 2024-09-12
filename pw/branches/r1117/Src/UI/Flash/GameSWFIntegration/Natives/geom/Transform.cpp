#include "TamarinPCH.h"

#include "../../FlashMovieAvmCore.h"
#include "../../builtins/BuiltinPools.h"

#include "Transform.h"

namespace avmplus
{

TransformObject::TransformObject( TransformClass * classType ) : 
  FlashScriptObject(classType->ivtable(), classType->prototype ) 
{ 
  Initialize();
}

TransformObject::TransformObject( VTable* ivtable, ScriptObject* prototype ) : 
  FlashScriptObject(ivtable, prototype) 
{ 
  Initialize();
}

void TransformObject::Initialize()
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
  
  PerspectiveProjectionClass * projectionClass = flashCore->GetClassCache().GetClass<PerspectiveProjectionClass>(EFlashClassID::PerspectiveProjectionClass );
  Matrix3DClass * matrix3DClass = flashCore->GetClassCache().GetClass<Matrix3DClass>(EFlashClassID::Matrix3DClass );

  Atom args[] = {0};

  perspectiveProjection = (PerspectiveProjectionObject *)flashCore->atomToScriptObject(projectionClass->construct(0, args));
  matrix3D = (Matrix3DObject *)flashCore->atomToScriptObject(matrix3DClass->construct(0, args));

  avmplus::ClassClosure * closure1 = flashCore->GetClassInPool("ColorTransform", PoolType::Geom);
  avmplus::ClassClosure * closure2 = flashCore->GetClassInPool("Matrix", PoolType::Geom);

  scriptColorTransform = flashCore->atomToScriptObject(closure1->construct(0, args));
  scriptMatrix = flashCore->atomToScriptObject(closure2->construct(0, args));

  _c_0_0 = GetSlotID( scriptColorTransform, "redMultiplier" );
  _c_1_0 = GetSlotID( scriptColorTransform, "greenMultiplier" );
  _c_2_0 = GetSlotID( scriptColorTransform, "blueMultiplier" );
  _c_3_0 = GetSlotID( scriptColorTransform, "alphaMultiplier" );

  _c_0_1 = GetSlotID( scriptColorTransform, "redOffset" );
  _c_1_1 = GetSlotID( scriptColorTransform, "greenOffset" );
  _c_2_1 = GetSlotID( scriptColorTransform, "blueOffset" );
  _c_3_1 = GetSlotID( scriptColorTransform, "alphaOffset" );

  // matrix slots
  _m_0_0 = GetSlotID( scriptMatrix, "a" );
  _m_1_1 = GetSlotID( scriptMatrix, "d" );
  _m_1_0 = GetSlotID( scriptMatrix, "b" );
  _m_0_1 = GetSlotID( scriptMatrix, "c" );
  _m_0_2 = GetSlotID( scriptMatrix, "tx" );
  _m_1_2 = GetSlotID( scriptMatrix, "ty" );
}

void TransformObject::set_matrix(ScriptObject/*Matrix*/ * value) 
{ 
  NI_VERIFY( value, "matrix should not be null", return );

  scriptMatrix = value;

  matrix.m_[0][0] = core()->number_d( scriptMatrix->getSlotAtom( _m_0_0 ) );
  matrix.m_[0][1] = core()->number_d( scriptMatrix->getSlotAtom( _m_0_1 ) );
  matrix.m_[0][2] = core()->number_d( scriptMatrix->getSlotAtom( _m_0_2 ) );
  matrix.m_[1][0] = core()->number_d( scriptMatrix->getSlotAtom( _m_1_0 ) );
  matrix.m_[1][1] = core()->number_d( scriptMatrix->getSlotAtom( _m_1_1 ) );
  matrix.m_[1][2] = core()->number_d( scriptMatrix->getSlotAtom( _m_1_2 ) );
}

ScriptObject/*Matrix*/ * TransformObject::get_matrix() 
{ 
  scriptMatrix->coerceAndSetSlotAtom( _m_0_0, core()->doubleToAtom( matrix.m_[0][0] ) );
  scriptMatrix->coerceAndSetSlotAtom( _m_0_1, core()->doubleToAtom( matrix.m_[0][1] ) );
  scriptMatrix->coerceAndSetSlotAtom( _m_0_2, core()->doubleToAtom( matrix.m_[0][2] ) );
  scriptMatrix->coerceAndSetSlotAtom( _m_1_0, core()->doubleToAtom( matrix.m_[1][0] ) );
  scriptMatrix->coerceAndSetSlotAtom( _m_1_1, core()->doubleToAtom( matrix.m_[1][1] ) );
  scriptMatrix->coerceAndSetSlotAtom( _m_1_2, core()->doubleToAtom( matrix.m_[1][2] ) );

  return scriptMatrix; 
}

void TransformObject::set_colorTransform(ScriptObject/*ColorTransform*/ * value) 
{ 
  NI_VERIFY( value, "colorTransform should not be null", return );

  scriptColorTransform = value; 

  colorTransform.m_[0][0] = core()->number_d( value->getSlotAtom( _c_0_0 ) );
  colorTransform.m_[1][0] = core()->number_d( value->getSlotAtom( _c_1_0 ) );
  colorTransform.m_[2][0] = core()->number_d( value->getSlotAtom( _c_2_0 ) );
  colorTransform.m_[3][0] = core()->number_d( value->getSlotAtom( _c_3_0 ) );
  colorTransform.m_[0][1] = core()->number_d( value->getSlotAtom( _c_0_1 ) ) / 256.f;
  colorTransform.m_[1][1] = core()->number_d( value->getSlotAtom( _c_1_1 ) ) / 256.f;
  colorTransform.m_[2][1] = core()->number_d( value->getSlotAtom( _c_2_1 ) ) / 256.f;
  colorTransform.m_[3][1] = core()->number_d( value->getSlotAtom( _c_3_1 ) ) / 256.f;
}

ScriptObject/*ColorTransform*/ * TransformObject::get_colorTransform() 
{ 
  scriptColorTransform->coerceAndSetSlotAtom( _c_0_0, core()->doubleToAtom( colorTransform.m_[0][0] ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_1_0, core()->doubleToAtom( colorTransform.m_[1][0] ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_2_0, core()->doubleToAtom( colorTransform.m_[2][0] ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_3_0, core()->doubleToAtom( colorTransform.m_[3][0] ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_0_1, core()->doubleToAtom( colorTransform.m_[0][1] * 256.f ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_1_1, core()->doubleToAtom( colorTransform.m_[1][1] * 256.f ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_2_1, core()->doubleToAtom( colorTransform.m_[2][1] * 256.f ) );
  scriptColorTransform->coerceAndSetSlotAtom( _c_3_1, core()->doubleToAtom( colorTransform.m_[3][1] * 256.f ) );

  return scriptColorTransform; 
}

}