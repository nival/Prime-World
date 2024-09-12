//!Component("PF_GameLogic/WarFog")
//!Component('System/Dumpers')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "WarFog.h"

#include "System/TestAssertDumper.h"
#include "System/DebugTraceDumper.h"
#include "System/Bresenham.h"

namespace
{
  static const int TEST_MAP_SIDE_SIZE = 30;
};


struct WarFogTest : public CxxTest::TestSuite
{
  CObj<NWorld::FogOfWar> fogOfWar;

  virtual void setUp()
  {
    fogOfWar = new NWorld::FogOfWar(0, 3, TEST_MAP_SIDE_SIZE, TEST_MAP_SIDE_SIZE, 1, 4);
  }
  virtual void tearDown()
  {
    fogOfWar = 0;
  }

  void TestBasicVisability()
  {
    int team = 0;
    SVector objectCenter(10,10);
    int radius = 2;
    
    //should be not visible cause map is empty
    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(objectCenter,team));
    fogOfWar->AddObject(objectCenter,team,radius);
    
    //apply changes
    fogOfWar->StepVisibility(0);
    //center
    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(objectCenter, team));

    //corner
    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(objectCenter + SVector(radius, 0), team));

    //outside bounds
    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(objectCenter + SVector(radius+3, 0), team));
  }

  void TestMoveObject()
  {
    int team = 0;
    SVector start(10,10);
    SVector end(20,10);
    int radius = 1;

    //should be not visible cause map is empty
    
    int objectID = fogOfWar->AddObject(start,team,radius);
    //apply changes
    fogOfWar->StepVisibility(0);

    //visiable start
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(start, team), true);
    //not visiable end
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(end, team), false);


    fogOfWar->MoveObject(objectID, end);
    //apply changes
    fogOfWar->StepVisibility(0);

    //not visiable start
    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(start, team));
    //visiable end
    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(end, team));
  }

  void TestRemoveObject()
  {
    int team = 0;
    SVector pos(10,10);
    int radius = 1;

    //should be not visible cause map is empty

    int objectID = fogOfWar->AddObject(pos,team,radius);
    //apply changes
    fogOfWar->StepVisibility(0);

    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(pos, team));

    fogOfWar->RemoveObject(objectID);

    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(pos, team));
  }

  void TestRemoveObjectALot()
  {
    int team = 0;
    SVector pos(10,10);
    int radius = 1;

    for (int i = 0; i< 10; i++)
    {
      int objectID = fogOfWar->AddObject(pos,team,radius);
      //apply changes
      fogOfWar->StepVisibility(0);

      //should be not visible cause map is empty
      TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(pos, team));

      fogOfWar->RemoveObject(objectID);

      TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(pos, team));
    }
  }

  void TestChangeVisibility()
  {
    int team = 0;
    SVector pos(10,10);
   
    //should be not visible cause map is empty

    int objectID = fogOfWar->AddObject(pos,team,1);
    fogOfWar->StepVisibility(0);

    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(pos+SVector(4,0), team));

    fogOfWar->ChangeVisibility(objectID, 10);
    fogOfWar->StepVisibility(0);

    //visiable now
    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(pos+SVector(4,0), team));
  }

  void TestChangeTeam()
  {
    int team = 0;
    int newTeam = 1;

    SVector pos(10,10);

    //should be not visible cause map is empty

    int objectID = fogOfWar->AddObject(pos,team,1);
    fogOfWar->StepVisibility(0);

    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(pos, team));
    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(pos, newTeam));

    fogOfWar->ChangeTeam(objectID, newTeam);
    fogOfWar->StepVisibility(0);

    TS_ASSERT_EQUALS(false, fogOfWar->IsTileVisible(pos, team));
    TS_ASSERT_EQUALS(true, fogOfWar->IsTileVisible(pos, newTeam));
  }


  void TestObstacle()
  {
    vector<SVector> obtacle(4);

    obtacle[0] = SVector(10,10);
    obtacle[1] = SVector(11,10);
    obtacle[2] = SVector(10,11);
    obtacle[3] = SVector(11,11);

    SVector obtacleStart(10,10);

    int team = 0;

    SVector pos(5,10);
    SVector target(15,11);

    //should be not visible cause map is empty

    fogOfWar->AddObject(pos,team,15);
    fogOfWar->StepVisibility(0);
    //visible initally
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(target, team), true);
    
    fogOfWar->AddObstacle(obtacle);
    fogOfWar->StepVisibility(0);
    fogOfWar->Dump("TestObstacle.tga");
    //not visible after obstacle
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(target, team), false);
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(obtacleStart, team), true);

    fogOfWar->RemoveObstacle(obtacle);
    fogOfWar->StepVisibility(0);
    //after removing obstacle we should see it again
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(target, team), true);
  }

  void TestLineOfSightObstacle()
  {
    vector<SVector> obstacle(1);
    obstacle[0] = SVector( 10, 10 );
    fogOfWar->AddObject( SVector( 9, 10 ), 0, 3 );
    fogOfWar->StepVisibility(0);
    fogOfWar->AddObstacle( obstacle );
    fogOfWar->StepVisibility(0);

    fogOfWar->Dump("TestLineOfSightObstacle.tga");

    TS_ASSERT_EQUALS( false, fogOfWar->IsTileVisible( SVector( 11, 10 ), 0 ) );
  }

  void TestLineOfSight()
  {
    fogOfWar->AddObject( SVector( 10, 10 ), 0, 4 );
    fogOfWar->StepVisibility(0);

    fogOfWar->Dump("TestLineOfSight.tga");

    TS_ASSERT_EQUALS( true, fogOfWar->IsTileVisible( SVector( 11, 11 ), 0 ) );
  }

  void TestVisibilityComm2()
  {
    SVector A(4,4);
    SVector B(5,6);

    SVector C(25,4);
    SVector D(24,6);

    SVector E(4,23);
    SVector F(5,25);

    SVector G(25,23);
    SVector H(24,25);

    SVector I(15,13);
    SVector J(16,17);

    int team1 = 0;
    int team2 = 1;

    int r = 3;
    int r2 = 5;

    vector<SVector> obstacle(7);
    obstacle[0] = SVector(  4,  5 );
    obstacle[1] = SVector( 25,  5 );
    obstacle[2] = SVector(  5, 24 );
    obstacle[3] = SVector( 24, 24 );
    obstacle[4] = SVector( 16, 13 );
    obstacle[5] = SVector( 16, 14 );
    obstacle[6] = SVector( 16, 15 );
    fogOfWar->AddObstacle(obstacle);
    fogOfWar->StepVisibility(0);

    fogOfWar->AddObject(A,team1,r);
    fogOfWar->AddObject(B,team2,r);
    fogOfWar->AddObject(C,team1,r);
    fogOfWar->AddObject(D,team2,r);
    fogOfWar->AddObject(E,team1,r);
    fogOfWar->AddObject(F,team2,r);
    fogOfWar->AddObject(G,team1,r);
    fogOfWar->AddObject(H,team2,r);
    fogOfWar->AddObject(I,team1,r2);
    fogOfWar->AddObject(J,team2,r2);
    fogOfWar->StepVisibility(0);

    fogOfWar->Dump("TestVisibilityComm2.tga");

    TS_ASSERT_EQUALS( fogOfWar->IsTileVisible(A,team2), fogOfWar->IsTileVisible(B,team1) );
    TS_ASSERT_EQUALS( fogOfWar->IsTileVisible(C,team2), fogOfWar->IsTileVisible(D,team1) );
    TS_ASSERT_EQUALS( fogOfWar->IsTileVisible(E,team2), fogOfWar->IsTileVisible(F,team1) );
    TS_ASSERT_EQUALS( fogOfWar->IsTileVisible(G,team2), fogOfWar->IsTileVisible(H,team1) );
    TS_ASSERT_EQUALS( fogOfWar->IsTileVisible(I,team2), fogOfWar->IsTileVisible(J,team1) );
  }

  void TestVisibilityComm3()
  {
    vector<SVector> obstacle(4);
    SVector A(15,15);
    int team1 = 0;
    int team2 = 1;
    int radius = 10;
    int asymetry = 0;

    fogOfWar->AddObject(A, team1, radius);
    fogOfWar->StepVisibility(0);

    for (int i = 0; i < 4; ++i)
    {
      obstacle[0] = SVector( 13 + i, 13 );
      obstacle[1] = SVector( 17, 13 + i );
      obstacle[2] = SVector( 17 - i, 17 );
      obstacle[3] = SVector( 13, 17 - i );
      fogOfWar->AddObstacle(obstacle);
      fogOfWar->StepVisibility(0);

      for (int j = 0; j < TEST_MAP_SIDE_SIZE; ++j)
      {
        for (int k = 0; k < TEST_MAP_SIDE_SIZE; ++k)
        {
          if (j > 12 && j < 18 && k > 12 && k < 18 )
            continue;

          SVector B(j, k);
          int objectID = fogOfWar->AddObject(B, team2, radius);
          fogOfWar->StepVisibility(0);

          if (fogOfWar->IsTileVisible(A, team2) != fogOfWar->IsTileVisible(B, team1))
          {
            ++asymetry;
            fogOfWar->Dump( NStr::StrFmt("TestVisibilityComm3_%03d.tga", asymetry) );
          }

          fogOfWar->RemoveObject(objectID);
          fogOfWar->StepVisibility(0);
        }
      }

      fogOfWar->RemoveObstacle(obstacle);
      fogOfWar->StepVisibility(0);
    }

    TS_ASSERT( asymetry == 0 );
  }

  void TestSectorsMerge()
  {
    vector<SVector> obstacle(16);
    obstacle[ 0] = SVector( 13, 13 );
    obstacle[ 1] = SVector( 14, 13 );
    obstacle[ 2] = SVector( 15, 13 );
    obstacle[ 3] = SVector( 16, 13 );
    obstacle[ 4] = SVector( 17, 13 );
    obstacle[ 5] = SVector( 13, 17 );
    obstacle[ 6] = SVector( 14, 17 );
    obstacle[ 7] = SVector( 15, 17 );
    obstacle[ 8] = SVector( 16, 17 );
    obstacle[ 9] = SVector( 17, 17 );
    obstacle[10] = SVector( 13, 14 );
    obstacle[11] = SVector( 13, 15 );
    obstacle[12] = SVector( 13, 16 );
    obstacle[13] = SVector( 17, 14 );
    obstacle[14] = SVector( 17, 15 );
    obstacle[15] = SVector( 17, 16 );
    fogOfWar->AddObstacle(obstacle);
    fogOfWar->StepVisibility(0);

    int badSectorsMerges = 0;

    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        SVector A(14 + i, 14 + j);
        int objectID = fogOfWar->AddObject(A, 0, 10);
        fogOfWar->StepVisibility(0);

        bool visibleTileFound = false;

        for (int k = 0; k < TEST_MAP_SIDE_SIZE && !visibleTileFound; ++k)
        {
          for (int h = 0; h < TEST_MAP_SIDE_SIZE && !visibleTileFound; ++h)
          {
            if (k > 12 && k < 18 && h > 12 && h < 18 )
              continue;

            SVector Tile( k, h );

            if (fogOfWar->IsTileVisible(Tile, 0))
              visibleTileFound = true;
          }
        }

        if (visibleTileFound)
        {
          ++badSectorsMerges;
          fogOfWar->Dump( NStr::StrFmt("TestSectorsMerge_%02d.tga", badSectorsMerges) );
        }

        fogOfWar->RemoveObject(objectID);
        fogOfWar->StepVisibility(0);
      }
    }

    TS_ASSERT( badSectorsMerges == 0 );
  }

  void TestObstacleVisibility()
  {
    vector<SVector> obstacles(10);

    obstacles[0] = SVector(10, 10);
    obstacles[1] = SVector(11, 10);
    obstacles[2] = SVector(12, 10);
    obstacles[3] = SVector(13, 10);
    obstacles[4] = SVector(14, 10);
    obstacles[5] = SVector( 5, 15);
    obstacles[6] = SVector( 5, 16);
    obstacles[7] = SVector( 5, 17);
    obstacles[8] = SVector( 5, 18);
    obstacles[9] = SVector( 5, 19);

    int team = 0;

    SVector pos(5, 10);
    SVector visObstacle1(13, 10);
    SVector invisObstacle1(14, 10);
    SVector visObstacle2( 5, 18);
    SVector invisObstacle2( 5, 19);

    fogOfWar->AddObstacle(obstacles);
    fogOfWar->AddObject(pos, team, 20);
    fogOfWar->StepVisibility(0);

    fogOfWar->Dump("TestObstacleVisibility.tga");

    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(visObstacle1, team), true);
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(invisObstacle1, team), false);
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(visObstacle2, team), true);
    TS_ASSERT_EQUALS(fogOfWar->IsTileVisible(invisObstacle2, team), false);
  }


  void TestLifeTime()
  {
    fogOfWar->AddTempObject( SVector( 10, 10 ), 0, 4, 1.1f );
    fogOfWar->StepVisibility(0);
    TS_ASSERT_EQUALS( true, fogOfWar->IsTileVisible( SVector( 11, 11 ), 0 ) );

    fogOfWar->StepVisibility(1);
    TS_ASSERT_EQUALS( true, fogOfWar->IsTileVisible( SVector( 11, 11 ), 0 ) );

    fogOfWar->StepVisibility(1);
    //TS_ASSERT_EQUALS( false, fogOfWar->IsTileVisible( SVector( 11, 11 ), 0 ) );
  }

  void TestSectorsSymetry()
  {
    SVector A(15,15);

    fogOfWar->AddObject(A,0,12);

    vector<SVector> obstacle(2);

    obstacle[0] = SVector( 14, 15 );
    obstacle[1] = SVector( 16, 15 );
    fogOfWar->AddObstacle(obstacle);
    fogOfWar->StepVisibility(0);
    fogOfWar->Dump("TestSectorsSymetry1.tga");
    fogOfWar->RemoveObstacle(obstacle);

    obstacle[0] = SVector( 15, 14 );
    obstacle[1] = SVector( 15, 16 );
    fogOfWar->AddObstacle(obstacle);
    fogOfWar->StepVisibility(0);
    fogOfWar->Dump("TestSectorsSymetry2.tga");
    fogOfWar->RemoveObstacle(obstacle);
  }


};
