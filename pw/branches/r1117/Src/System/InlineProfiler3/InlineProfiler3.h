#ifndef SYSTEM_INLINEPROFILER3_H_INCLUDED
#define SYSTEM_INLINEPROFILER3_H_INCLUDED

//
// This header contains only declarations needed to sample code
// To control the way profiler works or to read sampling data, use InlineProfiler3Control.h
//

#if !defined( _SHIPPING ) && !defined( NI_FORCE_DISABLE_INLINE_PROFILER )
#define NI_ENABLE_INLINE_PROFILER
#endif //!_SHIPPING



#ifdef NI_ENABLE_INLINE_PROFILER

#define NI_PROFILE_THREAD \
  profiler3::ThreadGuard BOOST_JOIN(profiler3_thread_guard_at_line, __LINE__);

#define NI_PROFILE_THREAD_NAMED( name ) \
  profiler3::ThreadGuard BOOST_JOIN(profiler3_thread_guard_at_line ,__LINE__)( name );

#define NI_PROFILE_THREAD_EX_START( name ) \
  profiler3::SetupThisThread( name );

#define NI_PROFILE_THREAD_EX_STOP \
  profiler3::CleanupThisThread();



#define NII_PROFILE_FUNCTION( guard ) \
  static profiler3::TEventId BOOST_JOIN(profiler_event_id_ , __LINE__) = profiler3::RegisterEvent( __FUNCTION__, __FILE__, __LINE__ ); \
  profiler3::guard BOOST_JOIN(profiler_event_guard_, __LINE__)( BOOST_JOIN(profiler_event_id_, __LINE__) );

#define NII_PROFILE_BLOCK( guard, name ) \
  static profiler3::TEventId BOOST_JOIN(profiler_event_id_, __LINE__) = profiler3::RegisterEvent( name, __FILE__, __LINE__ ); \
  profiler3::guard BOOST_JOIN(profiler_event_guard_ ,__LINE__)( BOOST_JOIN(profiler_event_id_, __LINE__) );

#else //NI_ENABLE_INLINE_PROFILER

#define NI_PROFILE_THREAD 
#define NI_PROFILE_THREAD_NAMED( name ) 
#define NI_PROFILE_THREAD_EX_START 
#define NI_PROFILE_THREAD_EX_STOP 
#define NII_PROFILE_FUNCTION( guard ) 
#define NII_PROFILE_BLOCK( guard, name ) 

#endif //NI_ENABLE_INLINE_PROFILER

#define NI_PROFILE_FUNCTION  NII_PROFILE_FUNCTION( EventGuardClass )
#define NI_PROFILE_BLOCK( name )  NII_PROFILE_BLOCK( EventGuardClass, name )

#define NI_PROFILE_FUNCTION_MEM       NII_PROFILE_FUNCTION( MemoryEventGuardClass )
#define NI_PROFILE_BLOCK_MEM( name )  NII_PROFILE_BLOCK( MemoryEventGuardClass, name )

#define NI_PROFILE_HEAVY_FUNCTION  NII_PROFILE_FUNCTION( HeavyEventGuardClass )
#define NI_PROFILE_HEAVY_BLOCK( name )  NII_PROFILE_BLOCK( HeavyEventGuardClass, name )


namespace profiler3
{

typedef ni_detail::UInt64   TTime;
typedef double              FTime;
typedef unsigned            TEventId;

} //namespace profiler3

#ifdef NI_ENABLE_INLINE_PROFILER

namespace profiler3
{

void SetupThisThread( const char * debugThreadName = 0 );
void CleanupThisThread();

TEventId RegisterEvent( const char * name, const char * file, int line );

void StartEvent( TEventId eventId );
void FinishEvent( TEventId eventId );

void StartEavyEvent( TEventId eventId );
void FinishEavyEvent( TEventId eventId );

void StartMemoryEvent( TEventId eventId );
void FinishMemoryEvent( TEventId eventId );



class ThreadGuard
{
public:
  ThreadGuard() { SetupThisThread(); }
  ThreadGuard( const char * debugThreadName ) { SetupThisThread( debugThreadName ); }
  ~ThreadGuard() { CleanupThisThread(); }
};



class EventGuardClass
{
public:
  EventGuardClass( TEventId _eventId ) : eventId( _eventId ) { StartEvent( eventId ); }
  ~EventGuardClass() { FinishEvent( eventId ); }

private:
  TEventId  eventId;
};



class MemoryEventGuardClass
{
public:
  MemoryEventGuardClass( TEventId _eventId ) : eventId( _eventId ) { StartMemoryEvent( eventId ); }
  ~MemoryEventGuardClass() { FinishMemoryEvent( eventId ); }

private:
  TEventId  eventId;
};



class HeavyEventGuardClass
{
public:
  HeavyEventGuardClass( TEventId _eventId ) : eventId( _eventId ) { StartEavyEvent( eventId ); }
  ~HeavyEventGuardClass() { FinishEavyEvent( eventId ); }

private:
  TEventId  eventId;
};

} //namespace profiler3

#endif //NI_ENABLE_INLINE_PROFILER

#endif //SYSTEM_INLINEPROFILER3_H_INCLUDED
