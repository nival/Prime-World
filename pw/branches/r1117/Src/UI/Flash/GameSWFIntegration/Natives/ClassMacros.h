#pragma once

#define DECLARE_CREATE_MEMBERS(className) \
  virtual Atom construct(int argc, Atom* argv) \
  { \
    className * object = new (core()->GetGC(), ivtable()->getExtraSize()) className(this); \
    return object->atom(); \
  } \
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype) \
  { \
    return new (core()->GetGC(), ivtable->getExtraSize()) className(ivtable, prototype); \
  } 


#define DECLARE_AS_CLASS(className,parentClass,objectName) \
class className : public parentClass \
  { \
  public: \
  className(VTable *vtable): parentClass(vtable){} \
  ~className(){} \
  DECLARE_CREATE_MEMBERS(objectName) \
  private: \
  DECLARE_SLOTS_##className; \
  };

#define DECLARE_AS_CLASS_WITH_CACHE(className,parentClass,objectName) \
class className : public parentClass \
  { \
  public: \
  className(VTable *vtable): parentClass(vtable){ \
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core(); \
    flashCore->GetClassCache().RegisterClass( EFlashClassID::className, this ); \
  } \
  ~className(){} \
  DECLARE_CREATE_MEMBERS(objectName) \
  private: \
  DECLARE_SLOTS_##className; \
  };

#define CONSTRUCT_CACHE_OBJECT(varName, corePointer, className, objectName) { \
  avmplus::className * classInstance = (corePointer)->GetClassCache().GetClass<avmplus::className>( EFlashClassID::className ); \
  avmplus::Atom args[] = {0}; \
  varName =(avmplus::objectName*)corePointer->atomToScriptObject(classInstance->construct(0, args)); }

#define CONSTRUCT_OBJECT_WITH_CLASSINSTANCE(varName, corePointer, classInstance, objectName) \
  Atom args[] = {0}; \
  varName = (objectName *)corePointer->atomToScriptObject(classInstance->construct(0, args));

//TODO should it be in EventTypes.h ?
#define DECLARE_EVENT(eventName) void Fire_##eventName() {DispatchEvent( FlashCore()->GetEventTypes().eventName);}