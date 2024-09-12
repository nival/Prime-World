#ifndef EVENTS_H_C004691C_0AA7_441A_BF20
#define EVENTS_H_C004691C_0AA7_441A_BF20

#include "fixedString.h"
#include "fixedvector.h"
#include "MetaProg.h"
#include "CompileTimeAssert.h"

namespace Events
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EVENT_CALLSTACK_SIZE 8

enum EventValueType
{
  EVT_BOOL    = 0,
  EVT_INT     = 1,
  EVT_FLOAT   = 2,
  EVT_STRING  = 3,
  EVT_STRING_SIZE_MASK = 0xffffff00,
  EVT_TYPE_MASK = 0xff,
};
typedef unsigned short TEventLength;
typedef int TEventId;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T> EventValueType GetEventValueType( int size ) { COMPILE_TIME_ASSERT( SUPERSUBCLASS( _BaseFixedString, T ), invalid_event_param_type );  return EventValueType( EVT_STRING | ( ( size << 8 ) & EVT_STRING_SIZE_MASK ) ); }
template<> EventValueType GetEventValueType<bool>( int size );
template<> EventValueType GetEventValueType<int>( int size );
template<> EventValueType GetEventValueType<float>( int size );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct EventType
{
  struct ParamInfo
  {
    FixedString<32> name;
    EventValueType type;
    bool operator == ( const ParamInfo& right ) const { return name == right.name && type == right.type; }
    ParamInfo() : type( EVT_BOOL ) {}
    ParamInfo( const char* _name, EventValueType _type )
      : name(_name), type(_type) 
    {
    }

    EventValueType GetParamType() const
    {
      return EventValueType( type & EVT_TYPE_MASK );
    }
    int GetParamSize() const 
    {
      switch( type & EVT_TYPE_MASK )
      {
      case EVT_BOOL : return sizeof(int); //due to event packing
      case EVT_INT : return sizeof(int);
      case EVT_FLOAT : return sizeof(float);
      case EVT_STRING : return ( ( type & EVT_STRING_SIZE_MASK ) >> 8 ) * sizeof(char);
      }
      NI_ALWAYS_ASSERT( "Unknown event param type" );
      return 0;
    }
  };

  Events::TEventId eventId;
  FixedString<32> name;
  FixedVector<ParamInfo, 8> params;

  string ToString() const;

  template<class T> T ParseEventParam( const void* eventData, uint param ) const;
  static TEventId ReadEventId( const void* eventData );
  void EventToString( const void* eventData, string* pResult ) const;
private:
  int GetParamOffset( uint param ) const;
};
template<> bool EventType::ParseEventParam<bool>( const void* eventData, uint param ) const;
template<> int EventType::ParseEventParam<int>( const void* eventData, uint param ) const;
template<> float EventType::ParseEventParam<float>( const void* eventData, uint param ) const;
template<> string EventType::ParseEventParam<string>( const void* eventData, uint param ) const;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack( push, 1)
struct EventBase
{
  TEventId typeId;
  DWORD callstack[EVENT_CALLSTACK_SIZE];

  EventBase()
  {
    typeId  = 0;
    callstack[0] = 0;
  }
protected:
  static EventType eventType;
  template<class T>
  static void PostEvent( const T& event )
  {
    PostEventInt( event, sizeof( T ) );
  }

  static void PostEventInt( const EventBase& event, int size );

  void InitEvent( int skipFrames );
};
#pragma pack( pop )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// event logging and control
_interface IEventLogger 
{
  virtual void LogEventName( TEventId eventId, const char* str ) = 0;
  virtual void Log( const EventBase& event, int eventSize ) = 0;

  virtual void EnableEvent( TEventId eventId ) {}
  virtual void DisableEvent( TEventId eventId ) {}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterLogger( IEventLogger* logger );
void UnregisterLogger( IEventLogger* logger );

const EventType& GetEventType( TEventId typeId );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// internals
struct SEventInfo
{
  EventType type;
  SEventInfo() {}
};
void RegisterEvent( TEventId typeId, SEventInfo* info );
void UnregisterEvent( TEventId typeId );

template<typename T>
struct SRegisterEvent
{
  SRegisterEvent()
  {
    SEventInfo info;
    T::FillEventType( &info.type );
    RegisterEvent( T::eventTypeId, &info );
  }
  ~SRegisterEvent()
  {
    UnregisterEvent( T::eventTypeId );
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_EVENT_1_PARAM_CSSKIP( _typeId, eventName, callStackSkipFrames, type1, name1 ) \
struct eventName : public Events::EventBase                         \
{                                                                   \
  static bool isEnabled;                                            \
  type1 name1;                                                      \
  enum { eventTypeId = _typeId };                                   \
  enum { skipCallstackFrames = callStackSkipFrames };               \
  static void Log( const type1& _##name1 )                          \
  { if  ( !isEnabled ) return;                                      \
    eventName event;                                                \
    event.typeId = eventTypeId;                                     \
    event.InitEvent( skipCallstackFrames );                         \
    event.name1 = _##name1;                                         \
    EventBase::PostEvent( event );                                  \
  }                                                                 \
  static const Events::EventType& GetEventType()                    \
  { static Events::EventType eventType;                             \
    if ( eventType.params.size() == 0 )                             \
      FillEventType( &eventType );                                  \
    return eventType;                                               \
  }                                                                 \
  static void FillEventType( Events::EventType* eventType )         \
  {                                                                 \
    eventType->name = #eventName;                                   \
    eventType->eventId = _typeId;                                   \
    eventType->params.push_back( Events::EventType::ParamInfo( #name1, Events::GetEventValueType<type1>( sizeof(type1) ) ) );  \
  }                                                                 \
};

#define DECLARE_EVENT_2_PARAM_CSSKIP( _typeId, eventName, callStackSkipFrames, type1, name1, type2, name2 )            \
struct eventName : public Events::EventBase                         \
{                                                                   \
  static bool isEnabled;                                            \
  type1 name1;                                                      \
  type2 name2;                                                      \
  enum { eventTypeId = _typeId };                                   \
  enum { skipCallstackFrames = callStackSkipFrames };               \
  static void Log( const type1& _##name1, const type2& _##name2 )   \
  { if  ( !isEnabled ) return;                                      \
    eventName event;                                                \
    event.typeId = eventTypeId;                                     \
    event.InitEvent( skipCallstackFrames );                         \
    event.name1 = _##name1;                                         \
    event.name2 = _##name2;                                         \
    EventBase::PostEvent( event );                                  \
  }                                                                 \
  static const Events::EventType& GetEventType()                    \
  { static Events::EventType eventType;                             \
    if ( eventType.params.size() == 0 )                             \
      FillEventType( &eventType );                                  \
    return eventType;                                               \
  }                                                                 \
  static void FillEventType( Events::EventType* eventType )         \
  {                                                                 \
    eventType->name = #eventName;                                   \
    eventType->eventId = _typeId;                                   \
    eventType->params.push_back( Events::EventType::ParamInfo( #name1, Events::GetEventValueType<type1>( sizeof(type1) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name2, Events::GetEventValueType<type2>( sizeof(type2) ) ) );  \
  }                                                                 \
};

#define DECLARE_EVENT_3_PARAM_CSSKIP( _typeId, eventName, callStackSkipFrames, type1, name1, type2, name2, type3, name3 )            \
struct eventName : public Events::EventBase                         \
{                                                                   \
  static bool isEnabled;                                            \
  type1 name1;                                                      \
  type2 name2;                                                      \
  type3 name3;                                                      \
  enum { eventTypeId = _typeId };                                   \
  enum { skipCallstackFrames = callStackSkipFrames };               \
  static void Log( const type1& _##name1, const type2& _##name2, const type3& _##name3 )  \
  { if  ( !isEnabled ) return;                                      \
    eventName event;                                                \
    event.typeId = eventTypeId;                                     \
    event.InitEvent( skipCallstackFrames );                         \
    event.name1 = _##name1;                                         \
    event.name2 = _##name2;                                         \
    event.name3 = _##name3;                                         \
    EventBase::PostEvent( event );                                  \
  }                                                                 \
  static const Events::EventType& GetEventType()                    \
  { static Events::EventType eventType;                             \
    if ( eventType.params.size() == 0 )                             \
      FillEventType( &eventType );                                  \
    return eventType;                                               \
  }                                                                 \
  static void FillEventType( Events::EventType* eventType )         \
  {                                                                 \
    eventType->name = #eventName;                                   \
    eventType->eventId = _typeId;                                   \
    eventType->params.push_back( Events::EventType::ParamInfo( #name1, Events::GetEventValueType<type1>( sizeof(type1) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name2, Events::GetEventValueType<type2>( sizeof(type2) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name3, Events::GetEventValueType<type3>( sizeof(type3) ) ) );  \
  }                                                                 \
};


#define DECLARE_EVENT_4_PARAM_CSSKIP( _typeId, eventName, callStackSkipFrames, type1, name1, type2, name2, type3, name3, type4, name4 )            \
struct eventName : public Events::EventBase                         \
{                                                                   \
  static bool isEnabled;                                            \
  type1 name1;                                                      \
  type2 name2;                                                      \
  type3 name3;                                                      \
  type4 name4;                                                      \
  enum { eventTypeId = _typeId };                                   \
  enum { skipCallstackFrames = callStackSkipFrames };               \
  static void Log( const type1& _##name1, const type2& _##name2, const type3& _##name3, const type4& _##name4 )  \
  { if  ( !isEnabled ) return;                                      \
    eventName event;                                                \
    event.typeId = eventTypeId;                                     \
    event.InitEvent( skipCallstackFrames );                         \
    event.name1 = _##name1;                                         \
    event.name2 = _##name2;                                         \
    event.name3 = _##name3;                                         \
    event.name4 = _##name4;                                         \
    EventBase::PostEvent( event );                                  \
  }                                                                 \
  static const Events::EventType& GetEventType()                    \
  { static Events::EventType eventType;                             \
    if ( eventType.params.size() == 0 )                             \
      FillEventType( &eventType );                                  \
    return eventType;                                               \
  }                                                                 \
  static void FillEventType( Events::EventType* eventType )         \
  {                                                                 \
    eventType->name = #eventName;                                   \
    eventType->eventId = _typeId;                                   \
    eventType->params.push_back( Events::EventType::ParamInfo( #name1, Events::GetEventValueType<type1>( sizeof(type1) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name2, Events::GetEventValueType<type2>( sizeof(type2) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name3, Events::GetEventValueType<type3>( sizeof(type3) ) ) );  \
    eventType->params.push_back( Events::EventType::ParamInfo( #name4, Events::GetEventValueType<type4>( sizeof(type4) ) ) );  \
  }                                                                 \
};

#define DECLARE_EVENT_1_PARAM( typeId, eventName, type1, name1 ) DECLARE_EVENT_1_PARAM_CSSKIP( typeId, eventName, 0, type1, name1 )
#define DECLARE_EVENT_2_PARAM( typeId, eventName, type1, name1, type2, name2 ) DECLARE_EVENT_2_PARAM_CSSKIP( typeId, eventName, 0, type1, name1, type2, name2 )
#define DECLARE_EVENT_3_PARAM( typeId, eventName, type1, name1, type2, name2, type3, name3 ) DECLARE_EVENT_3_PARAM_CSSKIP( typeId, eventName, 0, type1, name1, type2, name2, type3, name3 )
#define DECLARE_EVENT_4_PARAM( typeId, eventName, type1, name1, type2, name2, type3, name3, type4, name4 ) DECLARE_EVENT_4_PARAM_CSSKIP( typeId, eventName, 0, type1, name1, type2, name2, type3, name3, type4, name4 )

#define REGISTER_EVENT_NS( ns, name )                     \
bool ns::name::isEnabled = true;                          \
Events::SRegisterEvent<ns::name> sRegisterEvent_##name;

#define REGISTER_EVENT_NS_DISABLED( ns, name )            \
bool ns::name::isEnabled = false;                         \
Events::SRegisterEvent<ns::name> sRegisterEvent_##name;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //#define EVENTS_H_C004691C_0AA7_441A_BF20
