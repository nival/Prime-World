#include "stdafx.h"
#include "Events.h"

#if defined( NV_WIN_PLATFORM )
	#include "../MemoryLib/SymAccess.h"
#endif


namespace Events
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<> EventValueType GetEventValueType<bool>( int size ) {	return EVT_BOOL; }
  template<> EventValueType GetEventValueType<int>( int size ) {	return EVT_INT; }
  template<> EventValueType GetEventValueType<float>( int size ) {	return EVT_FLOAT; }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  string EventType::ToString() const
  {
    string res = name.c_str(); 
    for ( uint i = 0; i < params.size(); ++i )
    {
      switch( params[i].type & EVT_TYPE_MASK )
      {
      case EVT_BOOL : res += " bool "; break;
      case EVT_INT : res += " int "; break;
      case EVT_FLOAT : res += " float "; break;
      case EVT_STRING : res += " string( " + NStr::IntToStr( ( params[i].type & EVT_STRING_SIZE_MASK ) >> 8 ) + " ) "; break;
      }
      res += params[i].name.c_str();
    }
    return res;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int EventType::GetParamOffset( uint param ) const
  {
    int offset = sizeof( EventBase );

    for ( uint i = 0; i < param ; ++i )
    {
      const ParamInfo& info = params[i];
      offset += info.GetParamSize();
    }
    return offset;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<> bool EventType::ParseEventParam<bool>( const void* eventData, uint param ) const
  {
    NI_VERIFY( param < params.size(), "param number is out of range", return false );
    NI_VERIFY( ( params[param].type & EVT_TYPE_MASK ) == EVT_BOOL, "Parameter type should be EVT_BOOL", return false );
    int offset = GetParamOffset( param );
    bool res = *(bool*)( ((byte*)eventData) + offset );
    return res;
  }
  template<> int EventType::ParseEventParam<int>( const void* eventData, uint param ) const
  {
    NI_VERIFY( param < params.size(), "param number is out of range", return 0 );
    NI_VERIFY( ( params[param].type & EVT_TYPE_MASK ) == EVT_INT, "Parameter type should be EVT_INT", return 0 );
    int offset = GetParamOffset( param );
    int res = *(int*)( ((byte*)eventData) + offset );
    return res;
  }
  template<> float EventType::ParseEventParam<float>( const void* eventData, uint param ) const
  {
    NI_VERIFY( param < params.size(), "param number is out of range", return 0.f );
    NI_VERIFY( ( params[param].type & EVT_TYPE_MASK ) == EVT_FLOAT, "Parameter type should be EVT_FLOAT", return 0.f );
    int offset = GetParamOffset( param );
    float res = *(float*)( ((byte*)eventData) + offset );
    return res;
  }
  template<> string EventType::ParseEventParam<string>( const void* eventData, uint param ) const
  {
    NI_VERIFY( param < params.size(), "param number is out of range", return string() );
    NI_VERIFY( ( params[param].type & EVT_TYPE_MASK ) == EVT_STRING, "Parameter type should be EVT_STRING", return string() );
    int offset = GetParamOffset( param );
    char* res = (char*)( ((byte*)eventData) + offset);
    return string( res );
  }
  template<> const char* EventType::ParseEventParam<const char*>( const void* eventData, uint param ) const
  {
    NI_VERIFY( param < params.size(), "param number is out of range", return 0 );
    NI_VERIFY( ( params[param].type & EVT_TYPE_MASK ) == EVT_STRING, "Parameter type should be EVT_STRING", return 0 );
    int offset = GetParamOffset( param );
    char* res = (char*)( ((byte*)eventData) + offset );
    return res;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Events::TEventId EventType::ReadEventId( const void* eventData )
  {
    EventBase* event = (EventBase*)eventData;
    return event->typeId;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void EventType::EventToString( const void* eventData, string* pResult ) const
  {
    pResult->clear();

    Events::TEventId id = ReadEventId( eventData );
    NI_VERIFY( id == eventId, "Parsing invalid event", return );

    for ( uint i = 0; i < params.size(); ++i )
    {
      const ParamInfo& par = params[i];
      (*pResult) += string(par.name.c_str()) + ": ";
      switch ( par.type & EVT_TYPE_MASK )
      {
      case EVT_BOOL:
        {
          bool val = ParseEventParam<bool>( eventData, i );
          (*pResult) += val ? "true" : "false";
          break;
        }
      case EVT_INT:
        {
          int val = ParseEventParam<int>( eventData, i );
          (*pResult) += NStr::IntToStr( val );
          break;
        }
      case EVT_FLOAT:
        {
          float val = ParseEventParam<float>( eventData, i );
          (*pResult) += NI_STRFMT( "%g", val );
          break;
        }
      case EVT_STRING:
        {
          const char* val = ParseEventParam<const char*>( eventData, i );
          (*pResult) += string("\"") + val + "\"";
          break;
        }
      }
      if ( i != params.size() - 1 )
      {
        (*pResult) += ", ";
      }

    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  typedef hash_map<TEventId, SEventInfo> TEventsRegistry;
  struct SEventsRegistry
  {
    threading::Mutex eventsMutex;
    TEventsRegistry eventsRegistry;
    SEventsRegistry() {}

    static SEventsRegistry& Instance() 
    { 
      static ScopedPtr<SEventsRegistry> eventsRegistryInstance;
      if ( !eventsRegistryInstance ) 
        Reset( eventsRegistryInstance, new SEventsRegistry );
      return *Get( eventsRegistryInstance );
    }
  protected:
  };
  static threading::Mutex loggerMutex;
  static vector<IEventLogger*> loggers;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void RegisterLogger( IEventLogger* logger )
  {
    {
      SEventsRegistry& r = SEventsRegistry::Instance();
      threading::MutexLock lock( r.eventsMutex );
      for ( TEventsRegistry::iterator it = r.eventsRegistry.begin(); it != r.eventsRegistry.end(); ++it )
      {
        SEventInfo& ei = it->second;
        logger->LogEventName( it->first, ei.type.name.c_str() );
      }
    }

    {
      threading::MutexLock lock( loggerMutex );
      loggers.push_back( logger );
    }
  }
  void UnregisterLogger( IEventLogger* logger )
  {
    threading::MutexLock lock( loggerMutex );
    vector<IEventLogger*>::iterator it = find( loggers.begin(), loggers.end(), logger );
    NI_VERIFY( it != loggers.end(), "Cannot unregister not registered logger", return );
    loggers.erase( it );
  }
  void EventBase::PostEventInt( const EventBase& event, int size )
  {
    threading::MutexLock lock( loggerMutex );
    for( int i = 0; i < loggers.size(); ++i )
    {
      loggers[i]->Log( event, size );
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void EventBase::InitEvent( int skipFrames )
  {
#if defined( NV_WIN_PLATFORM )
    LockSymEngine().QuickCollectCallStack( &callstack[0], EVENT_CALLSTACK_SIZE, 3 + skipFrames );
    ReleaseSymEngine();
#endif
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void RegisterEvent( TEventId typeId, SEventInfo* info )
  {
    SEventsRegistry& r = SEventsRegistry::Instance();
    threading::MutexLock lock( r.eventsMutex );

    TEventsRegistry::iterator it = r.eventsRegistry.find( typeId );
    NI_VERIFY( it == r.eventsRegistry.end(), NI_STRFMT( "Event with id 0x%x registered twice", typeId ), return );
    r.eventsRegistry[ typeId ] = *info;
  }
  void UnregisterEvent( TEventId typeId )
  {
    SEventsRegistry& r = SEventsRegistry::Instance();
    threading::MutexLock lock( r.eventsMutex );

    r.eventsRegistry.erase( typeId );
  }
  const EventType& GetEventType( TEventId typeId )
  {
    SEventsRegistry& r = SEventsRegistry::Instance();
    threading::MutexLock lock( r.eventsMutex );

    TEventsRegistry::iterator it = r.eventsRegistry.find( typeId );
    NI_VERIFY( it != r.eventsRegistry.end(), "Cannot get event type of unregistered event", static EventType eventType; return eventType );
    return  it->second.type;
  }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

