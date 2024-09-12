//!Component('CyclicBuffer')
//!Component('Commands')

#include "stdafx.h"
#include "CyclicBuffer.h"
#include "cxxtest/TestSuite.h"


class CyclicBufferTest : public CxxTest::TestSuite
{
public:
  void setUp() {}
  void tearDown() {}

  template <class T>
  void PopFromHead( CyclicBuffer<T> & _buf, const T & _reference )
  {
    T v = _buf.PopHeadValue();
    TS_ASSERT_EQUALS( v, _reference );
  }


  template <class T>
  void PopFromTail( CyclicBuffer<T> & _buf, const T & _reference )
  {
    T v = _buf.PopTailValue();
    TS_ASSERT_EQUALS( v, _reference );
  }


  void test_simpliest()
  {
    CyclicBuffer<char> C( 5 );

    TS_ASSERT( C.Capacity() == 5 );
    TS_ASSERT( C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 0 );

    C.PushAtHead( 'A' );
    TS_ASSERT( !C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 1 );
  }


  void test1()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtHead( 'A' );
    PopFromHead( C, 'A' );
    TS_ASSERT( C.Empty() );
  }


  void test11()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtHead( 'A' );
    C.PopHead();
    TS_ASSERT( C.Empty() );
  }


  void test2()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtTail( 'B' );
    PopFromTail( C, 'B' );
    TS_ASSERT( C.Empty() );
  }


  void test22()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtTail( 'B' );
    C.PopTail();
    TS_ASSERT( C.Empty() );
  }


  void test3()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtTail( 'C' );
    PopFromHead( C, 'C' );
    TS_ASSERT( C.Empty() );
  }


  void test4()
  {
    CyclicBuffer<char> C( 10 );
    C.PushAtHead( 'D' );
    PopFromTail( C, 'D' );
    TS_ASSERT( C.Empty() );
  }


  void test_fullness1()
  {
    CyclicBuffer<char> C( 3 );
    C.PushAtHead( 'A' );
    C.PushAtHead( 'B' );
    C.PushAtHead( 'C' );
    TS_ASSERT( !C.Empty() );
    TS_ASSERT( C.Full() );
    TS_ASSERT( C.Size() == 3 );

    PopFromHead( C, 'C' );

    TS_ASSERT( !C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 2 );
  }


  void test_fullness2()
  {
    CyclicBuffer<char> C( 3 );
    C.PushAtTail( 'A' );
    C.PushAtTail( 'B' );
    C.PushAtTail( 'C' );
    TS_ASSERT( !C.Empty() );
    TS_ASSERT( C.Full() );
    TS_ASSERT( C.Size() == 3 );

    PopFromTail( C, 'C' );

    TS_ASSERT( !C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 2 );
  }


  void test_fullness3()
  {
    CyclicBuffer<char> C( 3 );
    C.PushAtTail( 'A' );
    C.PushAtHead( 'B' );
    C.PushAtTail( 'C' );
    TS_ASSERT( !C.Empty() );
    TS_ASSERT( C.Full() );
    TS_ASSERT( C.Size() == 3 );

    PopFromHead( C, 'B' );

    TS_ASSERT( !C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 2 );
  }


  void test_fullness4()
  {
    CyclicBuffer<char> C( 3 );
    C.PushAtTail( 'A' );
    C.PushAtHead( 'B' );
    C.PushAtHead( 'C' );
    TS_ASSERT( !C.Empty() );
    TS_ASSERT( C.Full() );
    TS_ASSERT( C.Size() == 3 );

    PopFromTail( C, 'A' );

    TS_ASSERT( !C.Empty() );
    TS_ASSERT( !C.Full() );
    TS_ASSERT( C.Size() == 2 );
  }


  void test_roll_position1()
  {
    CyclicBuffer<int> C( 3 );
    for ( int i = 0; i < 4; ++i )
    {
      C.PushAtHead( i );
      TS_ASSERT( !C.Empty() );
      TS_ASSERT( C.Size() == 1 );
      PopFromTail( C, i );
      TS_ASSERT( C.Empty() );
    }
  }


  void test_roll_position2()
  {
    CyclicBuffer<int> C( 3 );
    for ( int i = 0; i < 4; ++i )
    {
      C.PushAtTail( i );
      TS_ASSERT( !C.Empty() );
      TS_ASSERT( C.Size() == 1 );
      PopFromHead( C, i );
      TS_ASSERT( C.Empty() );
    }
  }


  void test_at_any_point1()
  {
    CyclicBuffer<int> C( 3 );

    for ( int i = 0; i < 4; ++i )
    {
      for ( int j = 0; j < 3; ++j )
        C.PushAtHead( j );
      TS_ASSERT( C.Full() );
      for ( int j = 0; j < 3; ++j )
        PopFromHead( C, 2 - j );
      TS_ASSERT( C.Empty() );

      C.PushAtHead( 0 );
      PopFromTail( C, 0 );
    }
  }


  void test_at_any_point2()
  {
    CyclicBuffer<int> C( 3 );

    for ( int i = 0; i < 4; ++i )
    {
      for ( int j = 0; j < 3; ++j )
        C.PushAtTail( j );
      TS_ASSERT( C.Full() );
      for ( int j = 0; j < 3; ++j )
        PopFromTail( C, 2 - j );
      TS_ASSERT( C.Empty() );

      C.PushAtHead( 0 );
      PopFromTail( C, 0 );
    }
  }


  void test_at_any_point3()
  {
    CyclicBuffer<int> C( 3 );

    for ( int i = 0; i < 4; ++i )
    {
      for ( int j = 0; j < 3; ++j )
        C.PushAtHead( j );
      TS_ASSERT( C.Full() );
      for ( int j = 0; j < 3; ++j )
        PopFromTail( C, j );
      TS_ASSERT( C.Empty() );

      C.PushAtHead( 0 );
      PopFromTail( C, 0 );
    }
  }


  void test_at_any_point4()
  {
    CyclicBuffer<int> C( 3 );

    for ( int i = 0; i < 4; ++i )
    {
      for ( int j = 0; j < 3; ++j )
        C.PushAtTail( j );
      TS_ASSERT( C.Full() );
      for ( int j = 0; j < 3; ++j )
        PopFromHead( C, j );
      TS_ASSERT( C.Empty() );

      C.PushAtHead( 0 );
      PopFromTail( C, 0 );
    }
  }


  void test_get1()
  {
    help_test_get1( 3 );
    help_test_get1( 4 );
  }

  void help_test_get1( size_t _size )
  {
    CyclicBuffer<char> C( _size );
    C.PushAtHead( 'A' );
    C.PushAtHead( 'B' );
    TS_ASSERT( C.AtTail( 0 ) == 'A' ); //not an abba fan really
    TS_ASSERT( C.AtTail( 1 ) == 'B' );
    TS_ASSERT( C.AtHead( 0 ) == 'B' );
    TS_ASSERT( C.AtHead( 1 ) == 'A' );

    C.PushAtHead( 'C' );
    TS_ASSERT( C.AtTail( 2 ) == 'C' );
    TS_ASSERT( C.AtHead( 2 ) == 'A' );
  }


  void test_get2()
  {
    help_test_get2( 3 );
    help_test_get2( 4 );
  }

  void help_test_get2( size_t _size )
  {
    CyclicBuffer<char> C( _size );
    C.PushAtTail( 'A' );
    C.PushAtTail( 'B' );
    C.PushAtTail( 'C' );
    TS_ASSERT( C.AtTail( 0 ) == 'C' );
    TS_ASSERT( C.AtTail( 1 ) == 'B' );
    TS_ASSERT( C.AtTail( 2 ) == 'A' );
    TS_ASSERT( C.AtHead( 0 ) == 'A' );
    TS_ASSERT( C.AtHead( 1 ) == 'B' );
    TS_ASSERT( C.AtHead( 2 ) == 'C' );
  }


  void test_get3()
  {
    help_test_get3( 3 );
    help_test_get3( 4 );
  }

  void help_test_get3( size_t _size )
  {
    CyclicBuffer<char> C( _size );

    C.PushAtTail( 'B' );
    C.PushAtTail( 'A' );
    C.PushAtHead( 'C' );
    C.PushAtHead( 'D' );

    TS_ASSERT( C.AtTail( 0 ) == 'A' );
    TS_ASSERT( C.AtTail( 1 ) == 'B' );
    TS_ASSERT( C.AtTail( 2 ) == 'C' );
    TS_ASSERT( C.AtTail( 3 ) == 'D' );

    TS_ASSERT( C.AtHead( 0 ) == 'D' );
    TS_ASSERT( C.AtHead( 1 ) == 'C' );
    TS_ASSERT( C.AtHead( 2 ) == 'B' );
    TS_ASSERT( C.AtHead( 3 ) == 'A' );
  }


  void test_enlarge1()
  {
    CyclicBuffer<char> C( 4 );

    C.PushAtTail( 'A' );

    TS_ASSERT( !C.Empty() );
    TS_ASSERT( C.Size() == 1 );

    C.PushAtTail( 'B' );
    C.PushAtTail( 'C' );
    C.PushAtTail( 'D' );
    TS_ASSERT( C.Size() == 4 );
    TS_ASSERT( C.Full() );

    C.PushAtTail( 'E' );
    TS_ASSERT( C.Size() == 5 );
    TS_ASSERT( C.Capacity() == 8 );
    TS_ASSERT( !C.Full() );

    TS_ASSERT( C.AtTail( 0 ) == 'E' );
    TS_ASSERT( C.AtTail( 1 ) == 'D' );
    TS_ASSERT( C.AtTail( 2 ) == 'C' );
    TS_ASSERT( C.AtTail( 3 ) == 'B' );
    TS_ASSERT( C.AtTail( 4 ) == 'A' );
  }


  void test_enlarge2()
  {
    CyclicBuffer<char> C( 4 );

    C.PushAtTail( 'B' );
    C.PushAtTail( 'A' );
    C.PushAtHead( 'C' );
    C.PushAtHead( 'D' );

    TS_ASSERT( C.Size() == 4 );
    TS_ASSERT( C.Full() );

    C.PushAtHead( 'E' );
    TS_ASSERT( C.Size() == 5 );
    TS_ASSERT( C.Capacity() == 8 );
    TS_ASSERT( !C.Full() );

    TS_ASSERT( C.AtTail( 0 ) == 'A' );
    TS_ASSERT( C.AtTail( 1 ) == 'B' );
    TS_ASSERT( C.AtTail( 2 ) == 'C' );
    TS_ASSERT( C.AtTail( 3 ) == 'D' );
    TS_ASSERT( C.AtTail( 4 ) == 'E' );
  }
};
