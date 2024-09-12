#pragma once

namespace NWorld
{

class TileMap;


class AStarPathFinder
{
  struct TravelCost
  {
    TravelCost() : total(0), toFinal(0) {}
    int total;
    int toFinal;
  };


  CPtr<TileMap> tileMap;

  static const int tileSize = 10;

  int mapWidth , mapHeight;
  int onClosedList;

  //Create needed arrays
  vector<int> openList; //1 dimensional array holding ID# of open list items
  CArray2D<int> closedCells;  //2 dimensional array used to record 

  vector<SVector> openedCells; //1d array stores the (x,y) location of an item on the open list

  CArray2D<SVector> parents; //2d array to store parent of each cell


  //1d array to store F&G cost of a cell on the open list
  vector<TravelCost> travelCosts;

  //2d array to store G cost for each cell.
  CArray2D<int> fromStartCosts; 	

  int pathLength;     //stores length of the found path for critter
  int pathLocation;   //stores current position along the chosen path for critter		
  
  vector<SVector> foundPath;
  int requiredSize; // required unit size

public:

  void SetTileMap(TileMap * _tileMap); 

  //-----------------------------------------------------------------------------
  // Name: FindPath
  // Desc: Finds a path using A*
  //-----------------------------------------------------------------------------
  bool FindPath (int unitSize,int startingX, int startingY, int targetX, int targetY);
  vector<SVector> & GetFoundPath() {return foundPath;}

private:
  void Clear();
  void SavePath(int startX, int startY, int targetX, int targetY);
  bool CanStandHere(int x, int y);
};

}