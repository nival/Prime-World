//!Component('System/NSTL')
//!Component('Samples/SimpleGame/VoxelGrid')
#include <CxxTest.h>

#include "stdafx.h"
#include "VoxelGrid.h"

struct TestSampleVoxelGrid : public CxxTest::TestSuite 
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testGetCoords( void )
  {
    Location::VoxelGrid testGrid;

    testGrid.Setup(-500.f, 300.f, 100.f, 600.f, 3, 2 );

    Location::VoxelCoords coords;

    TS_ASSERT( testGrid.GetCoords( -430.f, 250.f, coords ) );
    TS_ASSERT_EQUALS( coords.x, 0 );
    TS_ASSERT_EQUALS( coords.y, 0 );

    TS_ASSERT( testGrid.GetCoords( 290.f, 430.f, coords ) );
    TS_ASSERT_EQUALS( coords.x, 2 );
    TS_ASSERT_EQUALS( coords.y, 1 );

    TS_ASSERT( !testGrid.GetCoords( -700.f, 430.f, coords ) );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testNeighbours( void )
  {
    Location::VoxelGrid testGrid;

    testGrid.Setup(0.f, 1000.f, 0.f, 1000.f, 10, 10 );

    testGrid.AddObject( 150.f, 350.f, 0 ); 
    testGrid.AddObject( 250.f, 350.f, 1 ); // + neighbour of (3,3) with radis 1
    Location::PoolElement& removeIt = testGrid.AddObject( 350.f, 350.f, 2 ); // + neighbour of (3,3) with radis 1
    testGrid.AddObject( 450.f, 350.f, 3 ); // + neighbour of (3,3) with radis 1
    testGrid.AddObject( 550.f, 350.f, 4 );
    testGrid.AddObject( 450.f, 450.f, 5 ); // + neighbour of (3,3) with radis 1
    testGrid.AddObject( 350.f, 520.f, 6 );

    struct NeighbourTest
    {
      nstl::set<int> collection;
      void operator()( int objectID ) {  collection.insert( objectID ); }
    };

    NeighbourTest neighbourTest;

    testGrid.ForAllNeighbours( 3, 3, 1, neighbourTest );

    nstl::set<int> checkCollection;
    checkCollection.insert( 1 );
    checkCollection.insert( 2 );
    checkCollection.insert( 3 );
    checkCollection.insert( 5 );

    // test 'for all neighbours'
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 3, 3, 2, neighbourTest );

    TS_ASSERT( ! nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.insert( 0 );
    checkCollection.insert( 4 );
    checkCollection.insert( 6 );

    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    testGrid.RemoveObject( removeIt );

    // test 'for all neighbours' with radius
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 3, 3, 2, neighbourTest );

    checkCollection.erase( 2 );

    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    // test clear
    testGrid.Clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 3, 3, 2, neighbourTest );

    TS_ASSERT( neighbourTest.collection.empty() );

    // test 'for all' on coreners

    testGrid.AddObject(  50.f, 50.f, 0 ); 
    testGrid.AddObject( 150.f, 50.f, 1 ); 

    testGrid.AddObject( 950.f, 50.f, 2 ); 
    testGrid.AddObject( 950.f, 50.f, 3 ); 

    testGrid.AddObject(  50.f, 950.f, 4 ); 
    testGrid.AddObject( 150.f, 950.f, 5 ); 

    testGrid.AddObject( 950.f, 950.f, 6 ); 
    testGrid.AddObject( 950.f, 850.f, 7 ); 

    // corner [0,0]
    checkCollection.clear();
    checkCollection.insert( 0 );
    checkCollection.insert( 1 );
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 0, 0, 1, neighbourTest );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    // corner [0,9]
    checkCollection.clear();
    checkCollection.insert( 4 );
    checkCollection.insert( 5 );
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 0, 9, 1, neighbourTest );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    // corner [9,0]
    checkCollection.clear();
    checkCollection.insert( 2 );
    checkCollection.insert( 3 );
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 9, 0, 1, neighbourTest );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    // corner [9,9]
    checkCollection.clear();
    checkCollection.insert( 6 );
    checkCollection.insert( 7 );
    neighbourTest.collection.clear();
    testGrid.ForAllNeighbours( 9, 9, 1, neighbourTest );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testMove( void )
  {
    Location::VoxelGrid testGrid;
    testGrid.Setup( -500.f, 500.f, -500.f, 500.f, 10, 10 );

    int nextID = 0;

    for ( int j = 0; j < 10; ++j )
    {
      for ( int i = 0; i < 10; ++i )
      {
        testGrid.AddObject( -450.f + 100.f * float(i), -450.f + 100.f * float(j), nextID );
        nextID++;
      }
    }

    struct NeighbourTest
    {
      nstl::set<int> collection;
      void operator()( int objectID ) {  collection.insert( objectID ); }
    };

    // Тест сдвигов с радиусом 1 во все стороны
    nstl::set<int> checkCollection;
    NeighbourTest neighbourTest;
    testGrid.ForAllNeighboursDelta( 3, 3, -1, -1, 1, neighbourTest );
    checkCollection.insert( 11 ); checkCollection.insert( 12 ); checkCollection.insert( 13 );
    checkCollection.insert( 21 ); checkCollection.insert( 31 ); 
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, 0, -1, 1, neighbourTest );
    checkCollection.insert( 12 ); checkCollection.insert( 13 ); checkCollection.insert( 14 );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, +1, -1, 1, neighbourTest );
    checkCollection.insert( 13 ); checkCollection.insert( 14 ); checkCollection.insert( 15 );
    checkCollection.insert( 25 ); checkCollection.insert( 35 ); 
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, +1, 0, 1, neighbourTest );
    checkCollection.insert( 25 ); checkCollection.insert( 35 ); checkCollection.insert( 45 );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, +1, +1, 1, neighbourTest );
    checkCollection.insert( 35 ); checkCollection.insert( 45 ); checkCollection.insert( 55 );
    checkCollection.insert( 53 ); checkCollection.insert( 54 ); 
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, 0, +1, 1, neighbourTest );
    checkCollection.insert( 52 ); checkCollection.insert( 53 ); checkCollection.insert( 54 );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, -1, +1, 1, neighbourTest );
    checkCollection.insert( 51 ); checkCollection.insert( 52 ); checkCollection.insert( 53 );
    checkCollection.insert( 31 ); checkCollection.insert( 41 ); 
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, -1, 0, 1, neighbourTest );
    checkCollection.insert( 21 ); checkCollection.insert( 31 ); checkCollection.insert( 41 );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );

    // Тест сдвигов на краях 
    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 1, 1, -1, -1, 1, neighbourTest );
    TS_ASSERT( neighbourTest.collection.empty() );

    testGrid.ForAllNeighboursDelta( 8, 1, +1, -1, 1, neighbourTest );
    TS_ASSERT( neighbourTest.collection.empty() );

    testGrid.ForAllNeighboursDelta( 1, 8, -1, +1, 1, neighbourTest );
    TS_ASSERT( neighbourTest.collection.empty() );

    testGrid.ForAllNeighboursDelta( 8, 8, +1, +1, 1, neighbourTest );
    TS_ASSERT( neighbourTest.collection.empty() );

    // Тест с радиусом 2
    checkCollection.clear();
    neighbourTest.collection.clear();
    testGrid.ForAllNeighboursDelta( 3, 3, -1, -1, 2, neighbourTest );
    checkCollection.insert( 0 ); checkCollection.insert( 1 ); checkCollection.insert( 2 ); checkCollection.insert( 3 );
    checkCollection.insert( 4 ); checkCollection.insert( 10 ); checkCollection.insert( 20 ); checkCollection.insert( 30 );
    checkCollection.insert( 40 );
    TS_ASSERT( nstl::equal( checkCollection.begin(), checkCollection.end(), neighbourTest.collection.begin() ) );
  }
};
