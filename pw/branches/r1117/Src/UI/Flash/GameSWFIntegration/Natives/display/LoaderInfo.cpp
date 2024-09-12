#include "TamarinPCH.h"

#include "LoaderInfo.h"
#include "../../FlashMovieAvmCore.h"

namespace avmplus
{

LoaderInfoObject::LoaderInfoObject( VTable *ivtable, ScriptObject *delegate ) :EventDispatcherObject(ivtable, delegate)
{
  Initialize();
}

LoaderInfoObject::LoaderInfoObject( LoaderInfoClass * classType ) : EventDispatcherObject(classType->ivtable(), classType->prototype)
{
  Initialize();
}

void LoaderInfoObject::Initialize()
{
  width = height = 0;
  frameRate = 0;
  url = FlashCore()->internConstantStringLatin1("url");
}

LoaderInfoClass::LoaderInfoClass( VTable *vtable ) : EventDispatcherClass(vtable)
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core(); 
  flashCore->GetClassCache().RegisterClass( EFlashClassID::LoaderInfoClass, this );
}
}