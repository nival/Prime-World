//!Component('PF_Minigames/LuxBall')
//!Component('PF_Minigames/EaselConst')
//!Component('System/Commands')
//!Component('System/Ptr')
#include <CxxTest.h>

#include "stdafx.h"
#include "LuxBall.h"
#include "EaselNotifications.h"

class NotifierMock : public PF_Minigames::IEaselNotifier, public CObjectBase
{
  OBJECT_BASIC_METHODS( NotifierMock );
public:
  virtual bool Notify( tNotification& _notification ) 
  { 
    CObj<CObjectBase> notification = &_notification;
    return true; 
  }
};

struct TestLuxBallCollision : public CxxTest::TestSuite 
{

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testGetCoords( void )
  {
    CObj<NotifierMock> notifier = new NotifierMock();
    CObj<PF_Minigames::LuxBall> ball1 = new PF_Minigames::LuxBall( 0, notifier, PF_Minigames::EBallType::Simple, SVector(0,0), NDb::COLOR_BLUE );
    CObj<PF_Minigames::LuxBall> ball2 = new PF_Minigames::LuxBall( 0, notifier, PF_Minigames::EBallType::Simple, SVector(0,10), NDb::COLOR_BLUE );

    ball1->SetSize( 2 );
    ball2->SetSize( 2 );

    ball1->SetDirection( SVector(0, 1) );
    ball2->SetDirection( SVector(0, -1) );

    ball1->SetSpeed( 1 );
    ball2->SetSpeed( 1 );

    double time;
    /*TS_ASSERT( ball1->GetCollisionTime( ball2, time ) );
    TS_ASSERT( ball2->GetCollisionTime( ball1, time ) );*/

    ball1->SetPosition( SVector(0,0) );
    ball2->SetPosition( SVector(10,10) );

    ball1->SetDirection( SVector(0, 1) );
    ball2->SetDirection( SVector(-1, 0) );

    /*TS_ASSERT( ball1->GetCollisionTime( ball2, time ) );
    TS_ASSERT( ball2->GetCollisionTime( ball1, time ) );*/

    ball1->SetDirection( SVector(0, 1) );
    ball2->SetDirection( SVector(1, 0) );

    TS_ASSERT( !ball1->GetCollisionTime( ball2, time ) );
    TS_ASSERT( !ball2->GetCollisionTime( ball1, time ) );

    ball1->SetPosition( SVector( 7, 9 ) ); // 71100000, 90899968
    ball2->SetPosition( SVector( 7, 0 ) ); // 72710576, 9252879

    ball1->SetDirection( SVector( 0, -1 ) ); // 0, -10000
    ball2->SetDirection( SVector( 0, 0 ) ); // -837950, -11067


    ball1->SetSize( 1 ); // 5000000
    ball2->SetSize( 1 ); // 5000000

    ball1->SetSpeed( 2 ); // 150000
    ball2->SetSpeed( 0 );   // 	15959


    /*TS_ASSERT( ball1->GetCollisionTime( ball2, time ) );
    TS_ASSERT( ball2->GetCollisionTime( ball1, time ) );*/


    ball1->SetPosition( SVector( 71100000, 90899968 ) ); // 71100000, 90899968
    ball2->SetPosition( SVector( 72710576, 9252879 ) ); // 72710576, 9252879

    ball1->SetDirection( SVector( 0, -10000 ) ); // 0, -10000
    ball2->SetDirection( SVector( -837950, -11067 ) ); // -837950, -11067


    ball1->SetSize( 5000000 ); // 5000000
    ball2->SetSize( 5000000 ); // 5000000

    ball1->SetSpeed( 150000 ); // 150000
    ball2->SetSpeed( 1595 );   // 	15959


    /*TS_ASSERT( ball1->GetCollisionTime( ball2, time ) );
    TS_ASSERT( ball2->GetCollisionTime( ball1, time ) );*/
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testInsertion( void )
  {
    CObj<NotifierMock> notifier = new NotifierMock();
    CObj<PF_Minigames::LuxBall> ball1 = new PF_Minigames::LuxBall( 0, notifier, PF_Minigames::EBallType::Simple, SVector(1,0), NDb::COLOR_BLUE );
    CObj<PF_Minigames::LuxBall> ball2 = new PF_Minigames::LuxBall( 0, notifier, PF_Minigames::EBallType::Simple, SVector(0,10), NDb::COLOR_BLUE );

    ball1->SetSize( 2 );
    ball2->SetSize( 2 );

    ball1->SetDirection( SVector( 0, 1 ) );
    ball2->SetDirection( SVector( -1, 0 ) );

    ball1->SetSpeed( 1 );
    ball2->SetSpeed( 0 );

    /*double time;
    TS_ASSERT( ball1->GetCollisionTime( ball2, time ) );

    double a1 = ball1->GetInsertionShift( ball2, time );
    TS_ASSERT( a1 < 0 );

    ball1->SetPosition( SVector( -1, 0 ) );

    double a2 = ball1->GetInsertionShift( ball2, time );
    TS_ASSERT( 0 < a2 );*/
  }
};
