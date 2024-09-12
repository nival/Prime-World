//!Component('System/NSTL')

#include "stdafx.h"
#include "PooledContainer.h"
#include "cxxtest/TestSuite.h"

struct TestElement
{
  int objectID;

  int thisElement;
  int nextElement;
  int prevElement;

  TestElement() : objectID(0), thisElement(-1), nextElement(-1), prevElement(-1) {}
};

const int POOL_SIZE = 10;
typedef PooledContainer<TestElement, POOL_SIZE> Pool;
typedef Pool::TPtr PoolID;

const int testElements[] = {1,2,3,4,7,100};
const int testElementsCount = sizeof( testElements ) / sizeof( int );

class TestPooledContainer : public CxxTest::TestSuite 
{
public:
  void removeElement( int id, Pool& pool )
  {
    Pool::iterator it = pool.Begin();
    Pool::iterator last = pool.End();

    for ( ; it != last; ++it )
    {
      if ( id == it->objectID )
        it = pool.Free( it );
    }
  }

  void convertToSet( const Pool& pool, nstl::set<int>& _set )
  {
    _set.clear();

    Pool::const_iterator it = pool.Begin();
    Pool::const_iterator last = pool.End();

    for ( ; it != last; ++it )
    {
      _set.insert( it->objectID );
    }

  }

  void test_IndexingOnAdd()
  {
    Pool test;    

    PoolID prevID = test.Alloc();

    // Проверяем правильность индексирования при добавлении нового блока внутри контейнера
    for ( int i = 0; i < POOL_SIZE * 2; ++i )
    {
      PoolID nextID = test.Alloc();
      TS_ASSERT_DIFFERS( nextID, prevID );
      prevID = nextID;
    }
  }

  void test_Clear()
  {
    Pool test;    
    test.Alloc();

    // Проверяем Clear()
    TS_ASSERT( !test.Empty() );
    test.Clear();
    TS_ASSERT( test.Empty() );
  }

  void test_Operations( void )
  {
    Pool test;    

    nstl::set<int> checkSet;
    for ( int i = 0; i < testElementsCount; ++i )
    {
      checkSet.insert( testElements[i] );
      test.AllocAndGet().objectID = testElements[i]; 
    }

    Pool::iterator it = test.Begin();
    Pool::iterator last = test.End();

    nstl::set<int> checkSet2;
    convertToSet( test, checkSet2 );
    
    // Проверяем итератор
    TS_ASSERT( nstl::equal( checkSet.begin(), checkSet.end(), checkSet2.begin() ) );

    removeElement( 7, test );
    checkSet.erase( 7 );
    convertToSet( test, checkSet2 );

    // Проверяем удаление N1
    TS_ASSERT( nstl::equal( checkSet.begin(), checkSet.end(), checkSet2.begin() ) );

    removeElement( 1, test );
    checkSet.erase( 1 );
    convertToSet( test, checkSet2 );

    // Проверяем удаление N2
    TS_ASSERT( nstl::equal( checkSet.begin(), checkSet.end(), checkSet2.begin() ) );

    removeElement( 100, test );
    checkSet.erase( 100 );
    convertToSet( test, checkSet2 );

    // Проверяем удаление N3
    TS_ASSERT( nstl::equal( checkSet.begin(), checkSet.end(), checkSet2.begin() ) );

    checkSet.insert( 1000 );
    checkSet.insert( 1023 );
    test.AllocAndGet().objectID = 1000; 
    test.AllocAndGet().objectID = 1023; 
    convertToSet( test, checkSet2 );

    // Проверяем добавление после удаления
    TS_ASSERT( nstl::equal( checkSet.begin(), checkSet.end(), checkSet2.begin() ) );
  }
};
