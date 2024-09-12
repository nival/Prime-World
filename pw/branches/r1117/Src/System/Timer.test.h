//!Component("System/Timer")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "NiTimer.h"
#include "sleep.h"


class ThreadTestSuite2 : public CxxTest::TestSuite 
{

public:
  //Not unit-test actually...
  void test_stopwatch_smoke()
  {
    timer::Stopwatch sw;

    timer::Time t0 = sw.ElapsedTime();
    TS_ASSERT_LESS_THAN( t0, 0.1 );

    nival::sleep( 500 );

    timer::Time t1 = sw.ElapsedTime();
    TS_ASSERT_LESS_THAN( 0.4, t1 );
    TS_ASSERT_LESS_THAN( t1, 0.6 );
  }


  void test_stopwatch_restart()
  {
    timer::Stopwatch sw;
    TS_ASSERT_LESS_THAN( sw.ElapsedTime(), 0.1 );
    nival::sleep( 500 );
    TS_ASSERT_LESS_THAN( 0.4, sw.ElapsedTime() );
    sw.Restart();
    TS_ASSERT_LESS_THAN( sw.ElapsedTime(), 0.6 );
  }


  void test_timer_smoke()
  {
    timer::Timer tmr( 0.5 );

    tmr.Poll();
    TS_ASSERT( !tmr.Elapsed() );
    TS_ASSERT_LESS_THAN( 0.4, tmr.TimeLeft() );
    nival::sleep( 600 );
    tmr.Poll();
    TS_ASSERT( tmr.Elapsed() );
    TS_ASSERT_EQUALS( tmr.TimeLeft(), 0.0 );

    tmr.Restart( 1.0 );
    TS_ASSERT( !tmr.Elapsed() );
    TS_ASSERT_LESS_THAN( 0.9, tmr.TimeLeft() );
    nival::sleep( 1100 );
    tmr.Poll();
    TS_ASSERT( tmr.Elapsed() );
    TS_ASSERT_EQUALS( tmr.TimeLeft(), 0.0 );
  }



  void test_stop()
  {
    timer::Timer tmr( 1.0 );

    TS_ASSERT( !tmr.Poll() );
    TS_ASSERT( !tmr.Elapsed() );

    timer::Time tl = tmr.TimeLeft();
    TS_ASSERT( ( 0.9 <= tl ) && ( tl <= 1.1 ) );
    nival::sleep( 150 );

    TS_ASSERT( !tmr.Poll() );
    TS_ASSERT( !tmr.Elapsed() );
    tl = tmr.TimeLeft();
    TS_ASSERT( ( 0.8 <= tl ) && ( tl <= 0.9 ) );
    
    tmr.Stop();

    TS_ASSERT( tmr.Poll() );
    TS_ASSERT( tmr.Elapsed() );
    TS_ASSERT( tmr.TimeLeft() == 0 );

    tmr.Restart();
    tl = tmr.TimeLeft();
    TS_ASSERT( ( 0.9 <= tl ) && ( tl <= 1.1 ) );
  }



  struct C : public timer::ICallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( C, timer::ICallback, BaseObjectMT );
    virtual void OnTimeout( timer::Timer * _timer ) { hit = true; }
    bool hit;
    C() : hit( false ) {}
  };

  void test_timer_callback()
  {
    StrongMT<C> c = new C;
    timer::CallbackTimer tmr( 0.5, c );
    tmr.Poll();
    TS_ASSERT( !c->hit );
    nival::sleep( 600 );
    tmr.Poll();
    TS_ASSERT( c->hit );
  }



  struct C2
  {
    C2() : hit( false ) {}
    void OnHit() { hit = true; }
    bool hit;
  };

  void test_timer_memb_ptr()
  {
    C2 c;
    timer::MemberPtrTimer<C2> tmr( 0.5, &c, &C2::OnHit );
    tmr.Poll();
    TS_ASSERT( !c.hit );
    nival::sleep( 600 );
    tmr.Poll();
    TS_ASSERT( c.hit );
  }
};
