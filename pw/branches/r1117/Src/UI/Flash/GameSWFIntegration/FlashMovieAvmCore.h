#pragma once

#include <Vendor/Tamarin/source/platform/system-selection.h>
#include <Vendor/Tamarin/source/platform/win32/win32-platform.h>
#include <Vendor/Tamarin/source/Core/avmplus.h>
#include <Vendor/Tamarin/source/MMgc/MMgc.h>
#include <Vendor/Tamarin/source/Core/AvmCore.h>

#include "FlashClassesCache.h"
#include "builtins/BuiltinPools.h"

#include "Natives/events/EventTypes.h"
#include "GCRootWrapper.h"

namespace PoolType
{
enum Type;
}

namespace avmplus
{
class FlashScriptObject;
class EventObject;
class EventDispatcherObject;
class TimerObject;
}

namespace flash
{

struct SWF_RECT;

struct PoolData: public flash::SafeGCRoot<PoolData>
{
  PoolData(MMgc::GC * gc) : flash::SafeGCRoot<PoolData>(gc), pool(0), scriptEnv(0) {}

  avmplus::PoolObject* pool;
  avmplus::ScriptEnv* scriptEnv;
};

typedef avmplus::GCRootWrapper<PoolData> PoolDataWrapper;

class Movie;




class FlashMovieAvmCore: public avmplus::AvmCore
{
private:
  
  Strong<PoolDataWrapper> pools[PoolType::Last];

  FlashClassesCashe classesCache;
 
  //which pointers use here?
  avmplus::Toplevel * topLevel;
  avmplus::Domain * domain;
  avmplus::DomainEnv * domainEnv;

  Movie* movie;

  avmplus::EventTypes eventTypes;

public:
  FlashMovieAvmCore(MMgc::GC *gc);
  ~FlashMovieAvmCore();
  
  void Initialize();

  avmplus::Domain * GetDomain() { return domain; }
  avmplus::DomainEnv * GetDomainEnv() { return domainEnv; }

  //timing
  void Advance(float deltaTime);

  //TODO. I think we dont need this. May be remove this back link? SimonK
  void SetMovie( Movie* _movie ) { movie = _movie; }
  Movie* GetMovie() { return movie; }
 
  
  FlashClassesCashe & GetClassCache() { return classesCache; }
  avmplus::EventObject * CreateSimpleEvent( avmplus::AvmString eventType );
  avmplus::EventObject * CreateSimpleEvent( avmplus::Atom eventType );

  avmplus::EventTypes & GetEventTypes() { return eventTypes; }

  avmplus::ScriptEnv * PreparePool(avmplus::PoolObject * pool);
  void RunActionBlock( avmplus::ScriptBuffer & code);
  avmplus::PoolObject * ParseBlock(avmplus::ReadOnlyScriptBufferImpl * scriptBuffer);

  avmplus::ClassClosure * GetClassByTraits(avmplus::Traits * traits, avmplus::ScriptEnv * scriptEnv);
  avmplus::ClassClosure * GetClassInPool(const char * className, PoolType::Type poolType);
  avmplus::PoolObject * GetBuiltinPool(PoolType::Type poolType);
 
  avmplus::Traits * FindTraitsInPool(avmplus::AvmString name, avmplus::PoolObject * pool);

  avmplus::ClassClosure * GetClassByName( const char * name );
  avmplus::ClassClosure * GetClassByNameAVM( avmplus::AvmString name );

  avmplus::AvmString GenerateUniqueName();
  
  //calls method from ScriptObject. NOTE that ags should be ended by (Atom)-1 as the end of args
  avmplus::Atom CallMethod(avmplus::ScriptObject * instanceObject, char * methodName, ...);

  bool ScriptObjectToRect( avmplus::ScriptObject * _rectSource, flash::SWF_RECT& _rectDest );
  bool RectToScriptObject( avmplus::ScriptObject * _rectSource, const flash::SWF_RECT& _rectDest );

  //debug putput
  void PrintException(avmplus::Exception *exception);

#pragma  region AVM Core implementation
  virtual avmplus::String* readFileForEval(avmplus::String* referencingFilename, avmplus::String* filename) 
  {
    return 0;
  }
  virtual int32_t getDefaultAPI() { return 0; }
  virtual void interrupt(avmplus::Toplevel *env, InterruptReason) {}
  virtual void stackOverflow(avmplus::Toplevel *env) {}
#pragma endregion
  
  
private:
  void setStackLimit()
  {
    uintptr_t minstack = 327680;
    AvmCore::setStackLimit(minstack);
  }

  void InitializePlayerBuiltins();
  avmplus::ScriptEnv * PrepareAndStorePool(avmplus::PoolObject * pool, PoolType::Type poolType);
  avmplus::ScriptObject* FindDef( const avmplus::Multiname& multiname );

#ifdef DEBUGGER
  virtual avmplus::Debugger* createDebugger(int tracelevel);
#endif
  
};

}