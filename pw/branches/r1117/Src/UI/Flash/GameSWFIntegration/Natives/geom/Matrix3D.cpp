#include "TamarinPCH.h"

#include "../../FlashMovieAvmCore.h"

#include "Matrix3D.h"

namespace avmplus
{

Matrix3DObject::Matrix3DObject( Matrix3DClass * classType ) : 
  ScriptObject(classType->ivtable(), classType->prototype ) 
{ 

}

Matrix3DObject::Matrix3DObject( VTable* ivtable, ScriptObject* prototype ) : 
  ScriptObject(ivtable, prototype) 
{ 

}

}