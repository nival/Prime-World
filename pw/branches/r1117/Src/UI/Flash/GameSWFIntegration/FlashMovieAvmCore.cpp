#include "TamarinPCH.h"

#include "FlashMovieAvmCore.h"
#include "SwfStreamReader.h"

#include "Natives/events/Event.h"

using namespace avmplus;

namespace flash
{
 
  #pragma warning( disable: 4355 ) //'this' : used in base member initializer list

  FlashMovieAvmCore::FlashMovieAvmCore( MMgc::GC *gc ) : 
    avmplus::AvmCore(gc),
    classesCache(gc),
    eventTypes(this),
    movie(0)
  {
    //TODO remove this garbage
    static const uint32_t _min_version_num = 0;
    static const uint32_t _max_version_num = 0;
    static const uint32_t _versions_count[] = {1, };
    static const uint32_t _versions [][1] = { {0, }, };
    static const uint32_t _uris_count = 0;
    static const char* _uris [] = {"", };
    static const int32_t _api_compat [] = {0x1, };

    setAPIInfo(_min_version_num,
      _max_version_num-_min_version_num+1,
      _uris_count,
      (const char**) _uris,
      (int32_t*) _api_compat);
  }

  FlashMovieAvmCore::~FlashMovieAvmCore()
  {
    eventTypes.Destroy();

    SAFE_DELETE( domainEnv );  
    SAFE_DELETE( domain );
    SAFE_DELETE( topLevel );

    GCRoot::Destroy();
  }

  void FlashMovieAvmCore::Initialize()
  {
    this->setActiveAPI(ApiUtils::toAPI(this, 0));

    setStackLimit();

    CacheSizes cacheSize;
    setCacheSizes(cacheSize);

#ifdef DEBUGGER
    initBuiltinPool(10);
#else
    initBuiltinPool();
#endif
    

    topLevel = initTopLevel();

    domain = new (GetGC())  avmplus::Domain(this, builtinDomain);
    domainEnv = new (GetGC())  avmplus::DomainEnv(this, domain, topLevel->domainEnv());

    InitializePlayerBuiltins();
  }

  PoolObject * FlashMovieAvmCore::ParseBlock(avmplus::ReadOnlyScriptBufferImpl * scriptBuffer)
  {
		ScriptBuffer code(scriptBuffer);
    uint32_t api = getAPI(NULL);
    return parseActionBlock(code, 0, topLevel, domainEnv->domain(), NULL, api);
  }
 
  ScriptEnv * FlashMovieAvmCore::PrepareAndStorePool(PoolObject * pool, PoolType::Type poolType)
  {
    PoolData * poolData = new PoolData(GetGC());

    poolData->pool = pool;
    poolData->scriptEnv = prepareActionPool( poolData->pool , topLevel->domainEnv(), topLevel, NULL ) ;
    pools[poolType] = new PoolDataWrapper(poolData);

    return poolData->scriptEnv;
  }
  

    void FlashMovieAvmCore::InitializePlayerBuiltins()
  { 
    nstl::list<ScriptEnv*> scripts;

    //known stored types
   /* {
      Accessibility,
      Display,
      Events,
      Filters,
      Geom,
      System,
      Text,
      UI,
      Utils,
      XML,
    };*/

    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetXMLPool(this) , PoolType::XML) );
    scripts.push_back( prepareActionPool( BuiltinPools::GetByteArrayPool(this) , topLevel->domainEnv(), topLevel, NULL ) );
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetGeomPool(this) , PoolType::Geom)) ;
    scripts.push_back( prepareActionPool( BuiltinPools::GetNetPool(this) , topLevel->domainEnv(), topLevel, NULL ) );
    scripts.push_back( prepareActionPool( BuiltinPools::GetTestingPool(this) , topLevel->domainEnv(), topLevel, NULL ) );

    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetEventsPool(this) , PoolType::Events));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetSoundPool(this) , PoolType::Sound)) ;
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetDisplayPool(this) , PoolType::Display));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetAccessibilityPool(this) , PoolType::Accessibility));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetUIPool(this) , PoolType::UI));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetUtilsPool(this) , PoolType::Utils));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetSystemPool(this) , PoolType::System));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetTextPool(this) , PoolType::Text));
    scripts.push_back( PrepareAndStorePool( BuiltinPools::GetFiltersPool(this) , PoolType::Filters));

    nstl::list<ScriptEnv*>::iterator it = scripts.begin();
    nstl::list<ScriptEnv*>::iterator last = scripts.end();

    for ( ; it != last; ++it )
    {
      (*it)->initGlobal();
      (*it)->coerceEnter((*it)->global->atom());
    }

//     for ( int i = 0 ; i < PoolType::Last; ++i )
//     {
//       DebugTrace( " NEXT POOL " ); 
// 
//       for (int j = 0; j < int(pools[i].pool->cpool_ns.size()); ++j )
//       {
//         if ( pools[i].pool->cpool_ns[j] )
//         {
//           avmplus::StUTF8String message( pools[i].pool->cpool_ns[j]->format( this ) );
//           DebugTrace( " NAMESPACE: %s ", message.c_str() ); 
//         }
//       }
//     }

//     ClassClosure * eventClass = GetClassByName("flash.events.TextEvent");
// 
//     Atom args[] = 
//     { 0, 
//     internConstantStringLatin1("textInput")->atom(),
//     };
// 
//     ScriptObject* scriptObject = atomToScriptObject( eventClass->construct( 1, args ) );
//     EventObject* eventObject = dynamic_cast<EventObject*>( scriptObject );
// 
//     eventObject->SetPropertyByName( internConstantStringLatin1("bubbles"), trueAtom );
  }


  avmplus::ClassClosure * FlashMovieAvmCore::GetClassByTraits( Traits * traits, ScriptEnv * scriptEnv)
  {
    Multiname qname(traits->ns(), traits->name());
    ScriptObject* container = scriptEnv->global->vtable->init->finddef(&qname);
    Atom classAtom = topLevel->getproperty(container->atom(), &qname, container->vtable);
    return (ClassClosure*)AvmCore::atomToScriptObject(classAtom);
  }

  avmplus::ClassClosure * FlashMovieAvmCore::GetClassInPool( const char * className, PoolType::Type poolType )
  {
    ClassClosure * classClosure = 0;

    PoolData * poolData = pools[poolType]->Get();
    Traits * traits = poolData->pool->getBuiltinTraits(internConstantStringLatin1(className));

    if (traits) 
      classClosure = GetClassByTraits(traits, poolData->scriptEnv);
    
    return classClosure;
  }

  avmplus::PoolObject * FlashMovieAvmCore::GetBuiltinPool(PoolType::Type poolType)
  {
    return pools[poolType]->Get()->pool;
  }

  avmplus::Traits * FlashMovieAvmCore::FindTraitsInPool(avmplus::AvmString name, avmplus::PoolObject * pool)
  {
    AvmString actualName = name;

    //this is really ugly! TODO make it more gentle.
    //mainly this code just removes all parts except just name.
    //may be regexp?

    int lastPointPos = name->lastIndexOf(internConstantStringLatin1("."));
    actualName = (lastPointPos ==-1)? actualName: actualName->intern_substring(lastPointPos+1, actualName->length());

    lastPointPos = actualName->lastIndexOf(internConstantStringLatin1("::"));
    actualName = (lastPointPos ==-1)? actualName: actualName->intern_substring(lastPointPos+1, actualName->length());

    return pool->getBuiltinTraits(actualName);
  }

  avmplus::Atom FlashMovieAvmCore::CallMethod( avmplus::ScriptObject * instanceObject , char * methodName, ... )
  {
    Multiname name(findPublicNamespace(),  internConstantStringLatin1( methodName ));

    static const int maxAtoms = 64;
    Atom args[maxAtoms];
   
    AvmAssert(instanceObject != NULL);

    va_list va;
    va_start (va, methodName); 

    int argc = 1;
    args[0] = NULL;
    Atom arg = va_arg (va, Atom);

    while (arg != (Atom)-1) 
    { 
      args[argc] = arg;
      argc++;
      arg = va_arg (va, Atom);
      AvmAssert(argc<maxAtoms);
    }
    va_end(va);

    args[0] = instanceObject->atom();

		Atom result = topLevel->callproperty( instanceObject->atom(), &name, argc-1, args, instanceObject->vtable );
    return result;
  }

  avmplus::AvmString FlashMovieAvmCore::GenerateUniqueName()
  {
    static int instanceIndex = 0;
    static char name[100];
    sprintf_s(name,"instance%d",instanceIndex);
    instanceIndex++;
    return newStringLatin1(name);
  }

  avmplus::ScriptEnv * FlashMovieAvmCore::PreparePool( avmplus::PoolObject * pool )
  {
    return prepareActionPool(pool, domainEnv, topLevel, 0);
  }

  void FlashMovieAvmCore::RunActionBlock( avmplus::ScriptBuffer & code)
  {
    TRY( this, avmplus::kCatchAction_ReportAsError )
    {
    handleActionBlock(code, 0, domainEnv, topLevel, NULL, NULL /*gameCodeContext*/, getAPI(NULL));
	}
    CATCH ( Exception *exception )
    {
      PrintException(exception);
    }
    END_CATCH
    END_TRY
    
  }

  avmplus::EventObject * FlashMovieAvmCore::CreateSimpleEvent( avmplus::AvmString eventType )
  {
    EventClass * eventClass = GetClassCache().GetClass<EventClass>( EFlashClassID::EventClass );
    Atom args[] = {eventClass->atom(), eventType->atom()};
    return (EventObject *)atomToScriptObject(eventClass->construct(1, args));
  }

  avmplus::EventObject * FlashMovieAvmCore::CreateSimpleEvent( avmplus::Atom eventType )
  {
    EventClass * eventClass = GetClassCache().GetClass<EventClass>( EFlashClassID::EventClass );
    Atom args[] = {eventClass->atom(), eventType};
    return (EventObject *)atomToScriptObject(eventClass->construct(1, args));
  }

  avmplus::ScriptObject* FlashMovieAvmCore::FindDef( const avmplus::Multiname& multiname )
  {
    avmplus::ScriptEnv* script = (ScriptEnv*) domainEnv->getScriptInit(multiname);

    if (!script)
      return 0;

    if (script == (ScriptEnv*)BIND_AMBIGUOUS)
      topLevel->throwReferenceError(kAmbiguousBindingError, multiname);

    if (script == (ScriptEnv*)BIND_NONE)
      topLevel->throwReferenceError(kUndefinedVarError, multiname);

    if (script->global == NULL)
    {
      script->initGlobal();
      script->coerceEnter(script->global->atom());
    }

    return script->global;
  }

  avmplus::ClassClosure * FlashMovieAvmCore::GetClassByName( const char * name )
  {
    avmplus::AvmString _name = internConstantStringLatin1( name );

    return GetClassByNameAVM( _name );
  }

  avmplus::ClassClosure * FlashMovieAvmCore::GetClassByNameAVM( avmplus::AvmString name )
  {
    // Search for a dot from the end.
    int dot = name->lastIndexOf(cachedChars[(int)'.']);

    // If there is a '.', this is a fully-qualified
    // class name in a package.  Must turn it into
    // a namespace-qualified multiname.
    Namespace* ns;

    Stringp className;
    if (dot >= 0) {
      Stringp uri = internString(name->substring(0, dot));
      ns = internNamespace(newNamespace(uri, Namespace::NS_Public, getAPI(NULL)));
      className = internString(name->substring(dot+1, name->length()));
    } else {
      ns = findPublicNamespace();
      className = internString(name);
    }

    Multiname multiname(ns, className);

    ScriptObject *container = FindDef( multiname );

    if (!container)
      return 0;

    Atom atom = topLevel->getproperty( container->atom(), &multiname, container->vtable );

    return dynamic_cast<ClassClosure*>( AvmCore::atomToScriptObject(atom) );
  }

#ifdef DEBUGGER
  class FlashDebugger:public avmplus::Debugger
  {
  public:
    FlashDebugger(AvmCore *core, avmplus::Debugger::TraceLevel tracelevel): avmplus::Debugger(core, tracelevel) {}
    virtual void enterDebugger() {};
    virtual bool filterException(Exception *exception, bool willBeCaught) {return true;}
    virtual bool hitWatchpoint() {return false;}
  };


  avmplus::Debugger* FlashMovieAvmCore::createDebugger( int tracelevel )
  {
    return new(GetGC()) FlashDebugger(this, avmplus::Debugger::TRACE_METHODS_AND_LINES_WITH_ARGS);
  }
#endif


  void FlashMovieAvmCore::PrintException( Exception *exception )
  {
    DebugTrace(NStr::StrFmt("FLASH EXCEPTION: %s", StUTF8String(AvmCore::string(exception->atom)).c_str()));

#ifdef DEBUGGER
    if (!exception)
      return;

    StackTrace* stackTrace = exception->getStackTrace();
    stackTrace = exception->getStackTrace();

    ErrorObject* err = ((ErrorObject*)AvmCore::atomToScriptObject(exception->atom));
    Stringp str = err->getStackTrace();

    StUTF8String message(str);
    SwfDebugLog::CallLog(message.c_str());
#endif
  }

bool FlashMovieAvmCore::ScriptObjectToRect( avmplus::ScriptObject * _rectSource, flash::SWF_RECT& _rectDest )
{
  if ( _rectSource )
  {
    int _c_width = FlashScriptObject::GetSlotID( _rectSource, "width" );
    int _c_height = FlashScriptObject::GetSlotID( _rectSource, "height" );
    int _c_x = FlashScriptObject::GetSlotID( _rectSource, "x" );
    int _c_y = FlashScriptObject::GetSlotID( _rectSource, "y" );

    _rectDest.X1 = flash::TWIP * number_d( _rectSource->getSlotAtom( _c_x ) );
    _rectDest.Y1 = flash::TWIP * number_d( _rectSource->getSlotAtom( _c_y ) );
    _rectDest.X2 = _rectDest.X1 + flash::TWIP * number_d( _rectSource->getSlotAtom( _c_width ) );
    _rectDest.Y2 = _rectDest.Y1 + flash::TWIP * number_d( _rectSource->getSlotAtom( _c_height ) );

    return true;
  }

  return false;
}

bool FlashMovieAvmCore::RectToScriptObject( avmplus::ScriptObject * _rectObject, const flash::SWF_RECT& _rectDest )
{
  if ( _rectObject )
  {
    int _c_width = FlashScriptObject::GetSlotID( _rectObject, "width" );
    int _c_height = FlashScriptObject::GetSlotID( _rectObject, "height" );
    int _c_x = FlashScriptObject::GetSlotID( _rectObject, "x" );
    int _c_y = FlashScriptObject::GetSlotID( _rectObject, "y" );

    _rectObject->coerceAndSetSlotAtom( _c_width, doubleToAtom( ( _rectDest.X2 - _rectDest.X1 ) / flash::TWIP ) );
    _rectObject->coerceAndSetSlotAtom( _c_height, doubleToAtom( ( _rectDest.Y2 - _rectDest.Y1 ) / flash::TWIP ) );
    _rectObject->coerceAndSetSlotAtom( _c_x, doubleToAtom( _rectDest.X1 / flash::TWIP ) );
    _rectObject->coerceAndSetSlotAtom( _c_y, doubleToAtom( _rectDest.Y1 / flash::TWIP ) );

    return true;
  }

  return false;
}

}


NI_DEFINE_REFCOUNT(flash::PoolDataWrapper);