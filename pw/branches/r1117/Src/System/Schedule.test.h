//!Component("System/Schedule")
//!Component("System/Commands")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "Schedule.h"
#include "System/sleep.h"
#include "System/DarkSide.h"


class Test_Schedule : public CxxTest::TestSuite
{
public:
  struct Cb : public IScheduleCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Cb, IScheduleCallback, BaseObjectMT );
  public:
    virtual void AsyncEvent( TScheduleAuxParam _aux )
    {
      hist.push_back( DarkSide::ptr2int< int >( _aux ) );
    }

    std::vector<int> hist;
  };

  void setUp()
  {
  }

  void tearDown()
  {
  }


  void test_sync()
  {
    StrongMT<Schedule> s = new Schedule( true );
    StrongMT<Cb> cb1 = new Cb, cb2 = new Cb;

    s->SyncPoll( 0.0 );
    TS_ASSERT( cb1->hist.empty() && cb2->hist.empty() );

    s->Add( cb1, (TScheduleAuxParam)5 );
    s->Add( cb1, (TScheduleAuxParam)6 );
    s->Add( cb2, (TScheduleAuxParam)10 );

    s->SyncPoll( 0.0 );

    TS_ASSERT( cb1->hist.size() == 2 );
    TS_ASSERT( cb1->hist[0] == 5 );
    TS_ASSERT( cb1->hist[1] == 6 );
    TS_ASSERT( cb2->hist.size() == 1 );
    TS_ASSERT( cb2->hist[0] == 10 );
  }



  void test_async()
  {
    StrongMT<Schedule> s = new Schedule( false );
    StrongMT<Cb> cb1 = new Cb, cb2 = new Cb;

    s->Add( cb1, (TScheduleAuxParam)3 );
    s->Add( cb2, (TScheduleAuxParam)4 );
    s->Add( cb2, (TScheduleAuxParam)-1 );

    nival::sleep( 100 );

    TS_ASSERT( cb1->hist.size() == 1 );
    TS_ASSERT( cb1->hist[0] == 3 );
    TS_ASSERT( cb2->hist.size() == 2 );
    TS_ASSERT( cb2->hist[0] == 4 );
    TS_ASSERT( cb2->hist[1] == -1 );
  }

  void test_timed()
  {
    StrongMT<Schedule> s = new Schedule( true );
    StrongMT<Cb> cb1 = new Cb, cb2 = new Cb;

    s->Add( cb1, 10.0, (TScheduleAuxParam)-10 );
    s->Add( cb1, 2.0, (TScheduleAuxParam)5 );
    s->Add( cb2, 1.0, (TScheduleAuxParam)100500 );

    s->SyncPoll( 0.0 );
    TS_ASSERT( cb1->hist.empty() && cb2->hist.empty() );

    s->SyncPoll( 1.5 );
    TS_ASSERT( cb1->hist.empty() );
    TS_ASSERT( cb2->hist.size() == 1 );
    TS_ASSERT( cb2->hist[0] == 100500 );

    s->SyncPoll( 3.0 );
    TS_ASSERT( cb1->hist.size() == 1 );
    TS_ASSERT( cb2->hist.size() == 1 );
    TS_ASSERT( cb1->hist[0] == 5 );

    s->Add( cb1, 9.0, (TScheduleAuxParam)-11 );
    s->Add( cb1, 15.0, (TScheduleAuxParam)-15 );

    s->SyncPoll( 20.0 );
    TS_ASSERT( cb1->hist.size() == 4 );
    TS_ASSERT( cb2->hist.size() == 1 );
    TS_ASSERT( cb1->hist[1] == -11 );
    TS_ASSERT( cb1->hist[2] == -10 );
    TS_ASSERT( cb1->hist[3] == -15 );
  }
};
