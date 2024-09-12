#include "TamarinPCH.h"

#include "../../FlashMovieAvmCore.h"

#include "PerspectiveProjection.h"

namespace avmplus
{

PerspectiveProjectionObject::PerspectiveProjectionObject( PerspectiveProjectionClass * classType ) : 
  ScriptObject(classType->ivtable(), classType->prototype ) 
{ 

}

PerspectiveProjectionObject::PerspectiveProjectionObject( VTable* ivtable, ScriptObject* prototype ) : 
  ScriptObject(ivtable, prototype) 
{ 

}

}