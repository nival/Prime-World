//!Component("System/Ring")
//!Component('System/Pointers')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestSuite.h"
#include "Ring.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RingTest : public CxxTest::TestSuite 
{
public:
  struct RingObj
  {
    RingObj() : value ( -1 ) { }
    RingObj( int _value ) : value( _value ) { }

    void Set( int _value ) { value = _value; }

	  seDECLARE_RING_CLASS( RingObj, ringPart, Ring );
    Ring::Part ringPart;

    int value;
  };

  void CheckRing( const RingObj::Ring& ring, int first, ... )
  {
	  va_list va;
	  va_start( va, first );

    int index = 0;
    int value = first;
    ring::Range<RingObj::Ring> it( ring );
    while ( value != -1 && it )
    {
      TS_ASSERT_EQUALS( value, it->value );
      value = va_arg( va, int );
      ++index;
      ++it;
    }
    TS_ASSERT_EQUALS( -1, value );
    TS_ASSERT( !it );

    va_end( va );
  }

  void TestAddLastObject()
  {
    RingObj::Ring ring1;
    ring1.addLast( new RingObj( 1 ) );
    ring1.addLast( new RingObj( 2 ) );

    CheckRing( ring1, 1, 2, -1 );

    ring1.clear( ring::DeleteEraser<RingObj>() );
  }

  void TestInsertLinkedObject()
  {
    RingObj::Ring ring1;
    RingObj::Ring ring2;
    RingObj* obj1 = new RingObj( 1 );
    RingObj* obj2 = new RingObj( 2 );
    ring1.addLast( obj1 );
    ring2.addLast( obj2 );

    {
      test::AssertDisabler ad;
      ring1.addLast( obj2 );
    }

    CheckRing( ring1, 1, 2, -1 );
    CheckRing( ring2, -1 );

    ring1.clear( ring::DeleteEraser<RingObj>() );
  }
  
  struct DummyFunctor
  {
    void operator () (const RingObj * ringObj) { /* Dummy */ }
  } dummyFunctor;

  // Tests fail-safe operation of ForAll method on ring with hole.
  // 3 cases are tested: hole in the beginning of the ring, in the middle and in the end.
  void TestBrokenRingAndForAllMethod()
  {
    RingObj::Ring ring;
    RingObj* obj1 = new RingObj( 1 );
    RingObj* obj2 = new RingObj( 2 );
    RingObj* obj3 = new RingObj( 3 );
    ring.addLast( obj1 );
    ring.addLast( obj2 );
    ring.addLast( obj3 );
    CheckRing( ring, 1, 2, 3, -1 );

    // Test hole in the beginning
    memset(obj1, 0, sizeof(RingObj));
    {
      test::AssertDisabler ad;
      ring::ForAll( ring, dummyFunctor );
    }
    CheckRing( ring, 2, 3, -1 );

    obj1->Set( 1 );
    ring.insertBefore( obj1, obj2 );
    CheckRing( ring, 1, 2, 3, -1 );

    // Test hole in the middle
    memset(obj2, 0, sizeof(RingObj));
    {
      test::AssertDisabler ad;
      ring::ForAll( ring, dummyFunctor );
    }
    CheckRing( ring, 1, 3, -1 );

    obj2->Set( 2 );
    ring.insertBefore( obj2, obj3 );
    CheckRing( ring, 1, 2, 3, -1 );

    // Test hole in the end
    memset(obj3, 0, sizeof(RingObj));
    {
      test::AssertDisabler ad;
      ring::ForAll( ring, dummyFunctor );
    }
    CheckRing( ring, 1, 2, -1 );

    obj3->Set( 3 );
    ring.insertAfter( obj3, obj2 );
    CheckRing( ring, 1, 2, 3, -1 );

    ring.clear( ring::DeleteEraser<RingObj>() );
    CheckRing( ring, -1 );
  }

  // Tests fail-safe operation of Clear method on ring with hole.
  // 3 cases are tested: hole in the beginning of the ring, in the middle and in the end.
  void TestBrokenRingAndClearMethod()
  {
    RingObj::Ring ring;

    RingObj* objs[3];
    objs[0] = new RingObj( 1 );
    objs[1] = new RingObj( 2 );
    objs[2] = new RingObj( 3 );

    for (int i = 0; i < 3; ++i)
    {
      ring.addLast( objs[0] );
      ring.addLast( objs[1] );
      ring.addLast( objs[2] );
      CheckRing( ring, 1, 2, 3, -1 );

      memset(objs[i], 0, sizeof(RingObj));
      {
        test::AssertDisabler ad;
        ring::Clear( ring );
      }
      CheckRing( ring, -1 );

      memset(objs[i], 0, sizeof(RingObj));
      objs[i]->Set( i+1 );
    }

    delete objs[0];
    delete objs[1];
    delete objs[2];
  }
};
