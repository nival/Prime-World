//!Component("System/DebugVar")
//!Component('System/EventFileLogger')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/Events.h"
#include "System/HPTimer.h"
#include "System/EventFileLogger.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TestLogEvent : public Events::EventBase
{
  static bool isEnabled;
  FixedString<64> msg;
  enum { eventTypeId = 0x9A6BF440 };
  enum { skipCallstackFrames = 0 };
  static void Log( const FixedString<64>& _msg ) 
  {
    TestLogEvent event;
    event.typeId = (Events::TEventId)TestLogEvent::eventTypeId;
    event.InitEvent( skipCallstackFrames );
    event.msg = _msg;
    PostEvent( event );
  }
  static const Events::EventType& GetEventType()
  {
    static Events::EventType eventType;
    if ( eventType.params.size() == 0 )
      FillEventType( &eventType );

    return eventType; 
  }
  static void FillEventType( Events::EventType* eventType )
  {
    eventType->name = "TestLogEvent";
    eventType->eventId = TestLogEvent::eventTypeId;
    eventType->params.push_back( Events::EventType::ParamInfo( "msg", Events::GetEventValueType<FixedString<64> >( sizeof(FixedString<64>) ) ) );
  }
};
bool TestLogEvent::isEnabled = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TestEvent : public Events::EventBase
{
  static bool isEnabled;
  bool boolVal;
  int intVal;
  float floatVal;
  FixedString<16> strVal;
  enum { eventTypeId = 0x9A6BF441 };
  enum { skipCallstackFrames = 1 };
  static void Log( const bool& _boolVal, const int& _intVal, const float& _floatVal, const FixedString<16>& _strVal ) 
  {
    TestEvent event;
    event.typeId = (Events::TEventId)eventTypeId;
    event.InitEvent( skipCallstackFrames );
    event.boolVal = _boolVal;
    event.intVal = _intVal;
    event.floatVal = _floatVal;
    event.strVal = _strVal;
    PostEvent( event );
  }
  static const Events::EventType& GetEventType()
  {
    static Events::EventType eventType;
    if ( eventType.params.size() == 0 )
      FillEventType( &eventType );

    return eventType;
  }
  static void FillEventType( Events::EventType* eventType )
  {
    eventType->name = "TestEvent";
    eventType->eventId = TestEvent::eventTypeId;
    eventType->params.push_back( Events::EventType::ParamInfo( "boolVal", Events::GetEventValueType<bool>(sizeof(bool)) ) );
    eventType->params.push_back( Events::EventType::ParamInfo( "intVal", Events::GetEventValueType<int>(sizeof(int)) ) );
    eventType->params.push_back( Events::EventType::ParamInfo( "floatVal", Events::GetEventValueType<float>(sizeof(float)) ) );
    eventType->params.push_back( Events::EventType::ParamInfo( "strVal", Events::GetEventValueType<FixedString<16> >(sizeof(FixedString<16>)) ) );
  }
};
bool TestEvent::isEnabled = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EventsTest : public CxxTest::TestSuite 
{
public:
  struct TestEventLogger : public Events::IEventLogger 
  {
    Events::EventBase lastEvent;
    char buf[256];

    virtual void LogEventName( Events::TEventId, const char* str )
    {
    }

    virtual void Log( const Events::EventBase& event, int eventSize )
    {
      memcpy( &lastEvent, &event, eventSize );
    }
  };

  void TestEvents()
  {
    TestEvent testEvent;
    TestLogEvent logEvent;

    TestEventLogger logger;
    Events::RegisterLogger( &logger );

    TestEvent::isEnabled = true;
    TestEvent::Log( true, 10, 20.f, "abcd" );

    TS_ASSERT_EQUALS( logger.lastEvent.typeId, TestEvent::eventTypeId );
    TestEvent& e = *( (TestEvent*) &logger.lastEvent );

    TS_ASSERT_EQUALS( e.boolVal, true );
    TS_ASSERT( e.strVal == "abcd" );

    Events::UnregisterLogger( &logger );
  }

  void TestEventTypes()
  {
    TestEvent testEvent;

    const Events::EventType& type = TestEvent::GetEventType();
    TS_ASSERT( type.name == "TestEvent" );
    TS_ASSERT_EQUALS( type.params.size(), 4 );
    TS_ASSERT_EQUALS( type.params[0].GetParamType(), Events::EVT_BOOL );
    TS_ASSERT_EQUALS( type.params[1].GetParamType(), Events::EVT_INT );
    TS_ASSERT_EQUALS( type.params[2].GetParamType(), Events::EVT_FLOAT );
    TS_ASSERT_EQUALS( type.params[3].GetParamType(), Events::EVT_STRING );

    string typeString = type.ToString();
    TS_ASSERT( typeString == "TestEvent bool boolVal int intVal float floatVal string( 16 ) strVal" )
  }

  void TestEventsRegistry()
  {
    Events::SRegisterEvent<TestEvent> sRegisterEvent_TestEvent; 

    const Events::EventType& type = Events::GetEventType( TestEvent::eventTypeId );
    TS_ASSERT( type.name == "TestEvent" );
    TS_ASSERT_EQUALS( type.params.size(), 4 );
  }

#if defined( NV_WIN_PLATFORM )
#pragma warning( disable : 4740 ) //warning C4740: flow in or out of inline asm code suppresses global optimization
  static DWORD dwAddr_LogEvent1;
  static DWORD dwAddr_LogEvent2;
  __declspec(noinline) static void _LogEvent1()
  {
    static FixedString<64> d("aasdd");
    TestLogEvent::Log( d );
    __asm
    {
      call nxt
nxt:
      pop [dwAddr_LogEvent1]
    }
  }

  __declspec(noinline) static void __LogEvent2( int dummy )
  {
    (dummy);
    TestEvent::Log( true, 10, 20.f, "abcd" );
  }
  __declspec(noinline) static void _LogEvent2()
  {
    __LogEvent2( 10 );
    __asm
    {
      call nxt
nxt:
      pop [dwAddr_LogEvent2]
    }
  }
#endif // defined( NV_WIN_PLATFORM )
  void TestSkipCallstackFrames()
  {
#if defined( NV_WIN_PLATFORM )
    TestEvent testEvent;
    TestLogEvent logEvent;

    TS_ASSERT_EQUALS( (int)TestEvent::skipCallstackFrames, 1 )
    TS_ASSERT_EQUALS( (int)TestLogEvent::skipCallstackFrames, 0 )

    TestEventLogger logger;
    Events::RegisterLogger( &logger );

    TestEvent::isEnabled = true;
    TestLogEvent::isEnabled = true;

    _LogEvent1();
    TS_ASSERT_EQUALS( logger.lastEvent.callstack[0], dwAddr_LogEvent1 - 8 );

    _LogEvent2();
    TS_ASSERT_EQUALS( logger.lastEvent.callstack[0], dwAddr_LogEvent2 - 8 );

    Events::UnregisterLogger( &logger );
#endif // defined( NV_WIN_PLATFORM )
  }
  
  void TestParse()
  {
    Events::SRegisterEvent<TestEvent> sRegisterEvent_TestEvent; 
    const Events::EventType& type = Events::GetEventType( TestEvent::eventTypeId );

    TestEventLogger logger;
    Events::RegisterLogger( &logger );

    TestEvent::isEnabled = true;
    TestEvent::Log( true, 10, 20.f, "abcd" );

    void* eventData = (void*) &logger.lastEvent;

    Events::TEventId eventId = Events::EventType::ReadEventId( eventData );
    TS_ASSERT_EQUALS( eventId, TestEvent::eventTypeId );

    bool p1 = type.ParseEventParam<bool>( eventData, 0 );
    TS_ASSERT_EQUALS( p1, true );

    int p2 = type.ParseEventParam<int>( eventData, 1 );
    TS_ASSERT_EQUALS( p2, 10 );

    float p3 = type.ParseEventParam<float>( eventData, 2 );
    TS_ASSERT_EQUALS( p3, 20.f );

    string p4 = type.ParseEventParam<string>( eventData, 3 );
    TS_ASSERT_SAME_DATA( p4.c_str(), "abcd", p4.size() );

    Events::UnregisterLogger( &logger );
  }
  void TestParseToString()
  {
    Events::SRegisterEvent<TestEvent> sRegisterEvent_TestEvent; 
    const Events::EventType& type = Events::GetEventType( TestEvent::eventTypeId );

    TestEventLogger logger;
    Events::RegisterLogger( &logger );

    TestEvent::isEnabled = true;
    TestEvent::Log( true, 10, 20.f, "abcd" );

    void* eventData = (void*) &logger.lastEvent;

    Events::TEventId eventId = Events::EventType::ReadEventId( eventData );
    TS_ASSERT_EQUALS( eventId, TestEvent::eventTypeId );

    string testString;
    type.EventToString( eventData, &testString );

    const char* desiredString = "boolVal: true, intVal: 10, floatVal: 20, strVal: \"abcd\"";
    TS_ASSERT_SAME_DATA( testString.c_str(), desiredString, strlen( desiredString ) );

    Events::UnregisterLogger( &logger );
  }
};

#if defined( NV_WIN_PLATFORM )
DWORD EventsTest::dwAddr_LogEvent1 = 0;
DWORD EventsTest::dwAddr_LogEvent2 = 0;
#endif // defined( NV_WIN_PLATFORM )

class EventMacrosTest : public CxxTest::TestSuite 
{
public:
  DECLARE_EVENT_1_PARAM( 0x9A6BF442, TestMacroEvent1, int, p1 )

  DECLARE_EVENT_4_PARAM( 0x9A6BF443, TestMacroEvent4, bool, p1, FixedString<8>, p2, FixedString<8>, p3, int, p4 )

  void TestMacros()
  {
    TestMacroEvent1::Log( 1 );
    TestMacroEvent4::Log( true, "xxx", "yyy", 10 );
  }

  void TestEventFileLogger()
  {
    CObj<Events::EventFileLogger> logger = new Events::EventFileLogger( "test.txt", 65535, 5000 );
    Events::RegisterLogger( logger );
    logger->EnableEvent( TestMacroEvent4::eventTypeId );

    NHPTimer::STime startTime;
    NHPTimer::GetTime( startTime );

    for ( int i = 0; i < 10000; ++i )
    {
      TestMacroEvent4::Log( true, "testtes", "1234567", i );
    }

    Events::UnregisterLogger( logger );
    logger = 0;

    double timePassed = NHPTimer::GetTimePassedAndUpdateTime( startTime );
    (timePassed);
    //TS_TRACE( timePassed );

    string fullFileName = NFile::GetFullName( "test.txt" );
#if defined( NV_WIN_PLATFORM )
    ::DeleteFile( fullFileName.c_str() );
#elif defined( NV_LINUX_PLATFORM )
    ::unlink( fullFileName.c_str() );
#endif
  }
};

REGISTER_EVENT_NS( EventMacrosTest, TestMacroEvent1 )
REGISTER_EVENT_NS( EventMacrosTest, TestMacroEvent4 )

class DebugVarTest : public CxxTest::TestSuite 
{
public:
 	void TestAverageDebugVar()
	{
		NDebug::AverageDebugVar<float> var3( "var3", "t" );

		var3.AddValue( 10.f );
		TS_ASSERT_DELTA( var3.GetAverage().GetAvg(), 10.f, 0.1f );

		var3.AddValue( 5.f );
		TS_ASSERT_DELTA( var3.GetAverage().GetAvg(), 7.5f, 0.1f );

		var3.AddValue( 5.f );
		TS_ASSERT_DELTA( var3.GetAverage().GetAvg(), 6.67f, 0.1f );
	}

	void MySleep( double seconds )
	{
		NHPTimer::STime startTime, curTime;
		NHPTimer::GetTime( startTime );
		do
		{
			;
			NHPTimer::GetTime( curTime );
		}
		while( NHPTimer::Time2Seconds( curTime - startTime ) < seconds );
	}

  void TestAveragePerSecondDebugVar()
  {
    NDebug::AveragePerSecondDebugVar2<int> var1( "var1", "T" );

    TS_ASSERT( var1.GetAverage().GetAvg() == 0 );

    var1.AddValue( 1000 );
    NDebug::ResetDebugVarsOnFrame( 0.2f );

    TS_ASSERT_DELTA( var1.GetAverage().GetAvg(), 5000, 1 );


    for ( int i = 0; i < 10; ++i )
    {
      var1.AddValue( 1000 );
      NDebug::ResetDebugVarsOnFrame( 0.2f );
    }

    TS_ASSERT_DELTA( var1.GetAverage().GetAvg(), 5000, 1 );
    TS_ASSERT_DELTA( var1.GetTotal(), 11000, 50 );

    for ( int i = 0; i < 10; ++i )
    {
      var1.AddValue( 0 );
      NDebug::ResetDebugVarsOnFrame( 0.2f );
    }
    TS_ASSERT_DELTA( var1.GetAverage().GetAvg(), 2618, 1 );

  }

};
