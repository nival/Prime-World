#include "stdafx.h"
#include "AStarPathFinder.h"
#include "TileMap.h"

namespace NWorld
{

namespace
{

 

  enum 
  {
    notfinished = 0,
    notStarted = 0
  };// path-related constants
  
  enum 
  {
    found = 1, 
    nonexistent = 0 
  };
  
  enum
  {
    walkable = 0, 
    unwalkable = 1
  };
}

void AStarPathFinder::SetTileMap( TileMap * _tileMap )
{
  
 static bool firstTime = true;

 if (firstTime)
 {
   tileMap = _tileMap;
   mapWidth = tileMap->GetSizeX();
   mapHeight = tileMap->GetSizeY();
   onClosedList = 10;
   openList.resize(mapWidth*mapHeight+2);
   closedCells.SetSizes(mapWidth+1, mapHeight+1);
   openedCells.resize(mapWidth*mapHeight+2);
   parents.SetSizes(mapWidth+1, mapHeight+1);
   travelCosts.resize(mapWidth*mapHeight+2);
   fromStartCosts.SetSizes(mapWidth+1, mapHeight+1);

   foundPath.reserve(100);

   firstTime = false;
 }

 Clear();

}

void AStarPathFinder::Clear()
{
  
  closedCells.FillZero();
  parents.FillZero();
  fromStartCosts.FillZero();
  //foundPath.clear();
  //openList.clear();
  //travelCosts.clear();
  //openedCells.clear();
  //memset(&foundPath[0], 0, foundPath.size();
}
bool AStarPathFinder::FindPath(int unitSize, int startingX, int startingY, int targetX, int targetY )
{
  if(!IsValid(tileMap))
    return false;

  requiredSize = unitSize;

  int onOpenList=0, parentXval=0, parentYval=0,
    a=0, b=0, m=0, u=0, v=0, temp=0, corner=0, numberOfOpenListItems=0,
    addedGCost=0, tempGcost = 0, path = 0, newOpenListItemID=0;

  //1. Convert location data (in pixels) to coordinates in the walkability array.
  int startX = startingX;
  int startY = startingY;	

  //2.Quick Path Checks: Under the some circumstances no path needs to
  //	be generated ...

 if (startX == targetX && startY == targetY && pathLocation == 0)
    return false;

  //	If target square is unwalkable, return that it's a nonexistent path.
  if (!CanStandHere(targetX, targetY))
    return false;

  //3.Reset some variables that need to be cleared
  if (onClosedList > 1000000) //reset whichList occasionally
  {
    for (int x = 0; x < mapWidth;x++) {
      for (int y = 0; y < mapHeight;y++)
        closedCells [x][y] = 0;
    }
    onClosedList = 10;	
  }
  onClosedList = onClosedList+2; //changing the values of onOpenList and onClosed list is faster than redimming whichList() array
  onOpenList = onClosedList-1;
  pathLength = notStarted;//i.e, = 0
  pathLocation = notStarted;//i.e, = 0
  fromStartCosts[startX][startY] = 0; //reset starting square's G value to 0

  //4.Add the starting location to the open list of squares to be checked.
  numberOfOpenListItems = 1;
  openList[1] = 1;//assign it as the top (and currently only) item in the open list, which is maintained as a binary heap (explained below)
  openedCells[1].x = startX ; openedCells[1].y = startY;

  //5.Do the following until a path is found or deemed nonexistent.
  do
  {

    //6.If the open list is not empty, take the first cell off of the list.
    //	This is the lowest F cost cell on the open list.
    if (numberOfOpenListItems != 0)
    {

      //7. Pop the first item off the open list.
      parentXval = openedCells[openList[1]].x;
      parentYval = openedCells[openList[1]].y; //record cell coordinates of the item
      closedCells[parentXval][parentYval] = onClosedList;//add the item to the closed list

      //	Open List = Binary Heap: Delete this item from the open list, which
      //  is maintained as a binary heap. For more information on binary heaps, see:
      //	http://www.policyalmanac.org/games/binaryHeaps.htm
      numberOfOpenListItems = numberOfOpenListItems - 1;//reduce number of open list items by 1	

      //	Delete the top item in binary heap and reorder the heap, with the lowest F cost item rising to the top.
      openList[1] = openList[numberOfOpenListItems+1];//move the last item in the heap up to slot #1
      v = 1;

      //	Repeat the following until the new item in slot #1 sinks to its proper spot in the heap.
      do
      {
        u = v;		
        if (2*u+1 <= numberOfOpenListItems) //if both children exist
        {
          //Check if the F cost of the parent is greater than each child.
          //Select the lowest of the two children.
          if (travelCosts[openList[u]].total >= travelCosts[openList[2*u]].total) 
            v = 2*u;

          if (travelCosts[openList[v]].total >= travelCosts[openList[2*u+1]].total) 
            v = 2*u+1;		
        }
        else
        {
          if (2*u <= numberOfOpenListItems) //if only child #1 exists
          {
            //Check if the F cost of the parent is greater than child #1
            if (travelCosts[openList[u]].total >= travelCosts[openList[2*u]].total) 
              v = 2*u;
          }
        }

        if (u != v) //if parent's F is > one of its children, swap them
        {
          temp = openList[u];
          openList[u] = openList[v];
          openList[v] = temp;			
        }
        else
          break; //otherwise, exit loop

      }
      while (true);//reorder the binary heap


      //7.Check the adjacent squares. (Its "children" -- these path children
      //	are similar, conceptually, to the binary heap children mentioned
      //	above, but don't confuse them. They are different. Path children
      //	are portrayed in Demo 1 with grey pointers pointing toward
      //	their parents.) Add these adjacent child squares to the open list
      //	for later consideration if appropriate (see various if statements
      //	below).
      for (b = parentYval-1; b <= parentYval+1; b++){
        for (a = parentXval-1; a <= parentXval+1; a++){

          //	If not off the map (do this first to avoid array out-of-bounds errors)
          if (a != -1 && b != -1 && a != mapWidth && b != mapHeight){

            //	If not already on the closed list (items on the closed list have
            //	already been considered and can now be ignored).			
            if (closedCells[a][b] != onClosedList) { 

              //	If not a wall/obstacle square.
              if (CanStandHere(a, b)) { 

                //	Don't cut across corners
                corner = walkable;	
                if (a == parentXval-1) 
                {
                  if (b == parentYval-1)
                  {
                    if (!CanStandHere(parentXval-1, parentYval) || !CanStandHere(parentXval, parentYval-1)) 
                      corner = unwalkable;
                  }
                  else if (b == parentYval+1)
                  {
                    if (!CanStandHere(parentXval,parentYval+1) || !CanStandHere(parentXval-1, parentYval)) 
                      corner = unwalkable; 
                  }
                }
                else if (a == parentXval+1)
                {
                  if (b == parentYval-1)
                  {
                    if (!CanStandHere(parentXval, parentYval-1)
                      || !CanStandHere(parentXval+1, parentYval)) 
                      corner = unwalkable;
                  }
                  else if (b == parentYval+1)
                  {
                    if (!CanStandHere(parentXval+1, parentYval)
                      || !CanStandHere(parentXval, parentYval+1))
                      corner = unwalkable; 
                  }
                }	
                if (corner == walkable) {

                  //	If not already on the open list, add it to the open list.			
                  if (closedCells[a][b] != onOpenList) 
                  {	

                    //Create a new open list item in the binary heap.
                    newOpenListItemID = newOpenListItemID + 1; //each new item has a unique ID #
                    m = numberOfOpenListItems+1;
                    openList[m] = newOpenListItemID;//place the new open list item (actually, its ID#) at the bottom of the heap
                    int openID = newOpenListItemID;
                    openedCells[newOpenListItemID].x = a;
                    openedCells[newOpenListItemID].y = b;//record the x and y coordinates of the new item

                    //Figure out its G cost
                    if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
                      addedGCost = 14;//cost of going to diagonal squares	
                    else	
                      addedGCost = 10;//cost of going to non-diagonal squares				
                    fromStartCosts[a][b] = fromStartCosts[parentXval][parentYval] + addedGCost;

                    //Figure out its H and F costs and parent
                    travelCosts[openID].toFinal = 10*(abs(a - targetX) + abs(b - targetY));
                    travelCosts[openID].total = fromStartCosts[a][b] + travelCosts[openID].toFinal;
                    
                    parents[a][b] = SVector( parentXval, parentYval);

                    NI_ASSERT(parents[a][b] != SVector(a,b), "cant parent itself!");

                    //Move the new open list item to the proper place in the binary heap.
                    //Starting at the bottom, successively compare to parent items,
                    //swapping as needed until the item finds its place in the heap
                    //or bubbles all the way to the top (if it has the lowest F cost).
                    while (m != 1) //While item hasn't bubbled to the top (m=1)	
                    {
                      //Check if child's F cost is < parent's F cost. If so, swap them.	
                      if (travelCosts[openID].total <= travelCosts[openList[m/2]].total)
                      {
                        temp = openList[m/2];
                        openList[m/2] = openList[m];
                        openList[m] = temp;
                        m = m/2;
                      }
                      else
                        break;
                    }
                    numberOfOpenListItems = numberOfOpenListItems+1;//add one to the number of items in the heap

                    //Change whichList to show that the new item is on the open list.
                    closedCells[a][b] = onOpenList;
                  }

                  //8.If adjacent cell is already on the open list, check to see if this 
                  //	path to that cell from the starting location is a better one. 
                  //	If so, change the parent of the cell and its G and F costs.	
                  else //If whichList(a,b) = onOpenList
                  {

                    //Figure out the G cost of this possible new path
                    if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
                      addedGCost = 14;//cost of going to diagonal tiles	
                    else	
                      addedGCost = 10;//cost of going to non-diagonal tiles				
                    tempGcost = fromStartCosts[parentXval][parentYval] + addedGCost;

                    //If this path is shorter (G cost is lower) then change
                    //the parent cell, G cost and F cost. 		
                    if (tempGcost < fromStartCosts[a][b]) //if G cost is less,
                    {
                      //change the square's parent
                      parents[a][b] = SVector( parentXval, parentYval);
                      NI_ASSERT(parents[a][b] != SVector(a,b), "cant parent itself!");

                      fromStartCosts[a][b] = tempGcost;//change the G cost			

                      //Because changing the G cost also changes the F cost, if
                      //the item is on the open list we need to change the item's
                      //recorded F cost and its position on the open list to make
                      //sure that we maintain a properly ordered open list.
                      for (int x = 1; x <= numberOfOpenListItems; x++) //look for the item in the heap
                      {
                        int open = openList[x];
                        if (openedCells[open].x == a && openedCells[open].y == b) //item found
                        {
                          travelCosts[open].total = fromStartCosts[a][b] + travelCosts[open].toFinal;//change the F cost

                          //See if changing the F score bubbles the item up from it's current location in the heap
                          m = x;
                          while (m != 1) //While item hasn't bubbled to the top (m=1)	
                          {
                            //Check if child is < parent. If so, swap them.	
                            if (travelCosts[openList[m]].total  < travelCosts[openList[m/2]].total)
                            {
                              temp = openList[m/2];
                              openList[m/2] = openList[m];
                              openList[m] = temp;
                              m = m/2;
                            }
                            else
                              break;
                          } 
                          break; //exit for x = loop
                        } //If openX(openList(x)) = a
                      } //For x = 1 To numberOfOpenListItems
                    }//If tempGcost < Gcost(a,b)

                  }//else If whichList(a,b) = onOpenList	
                }//If not cutting a corner
              }//If not a wall/obstacle square.
            }//If not already on the closed list 
          }//If not off the map
        }//for (a = parentXval-1; a <= parentXval+1; a++){
      }//for (b = parentYval-1; b <= parentYval+1; b++){

    }//if (numberOfOpenListItems != 0)

    //9.If open list is empty then there is no path.	
    else
    {
      path = nonexistent; break;
    }  

    //If target is added to open list then path has been found.
    if (closedCells[targetX][targetY] == onOpenList)
    {
      path = found; break;
    }

  }
  while (1);//Do until path is found or deemed nonexistent

  if (path == found)
    SavePath(startX, startY, targetX,targetY);

  return path;
}

void AStarPathFinder::SavePath(int startX, int startY, int targetX, int targetY)
{
  //a.Working backwards from the target to the starting location by checking
  //	each cell's parent, figure out the length of the path.

  //make start parenting itself
  parents[startX][startY] = SVector(startX, startY);

  
  SVector currentPos(targetX, targetY); 
  SVector startPos(startX, startY);

  foundPath.clear();
  //NI_ASSERT(!foundPath.size(), "should be empty here");

  //put destination first
  foundPath.push_back (currentPos);

  do
  {
    //Look up the parent of the current cell.	

    SVector newPos = parents[currentPos.x][currentPos.y];
   	NI_ASSERT(abs(newPos.x - currentPos.x) <= 1 && abs(newPos.y - currentPos.y) <= 1, "Too far!");

    currentPos = newPos;
    
    foundPath.push_back(currentPos);
  }
  while (currentPos != startPos );

  nstl::reverse(foundPath.begin(), foundPath.end());
}

bool AStarPathFinder::CanStandHere( int x, int y )
{
  return tileMap->CanUnitGo(requiredSize,requiredSize, SVector(x,y));
}



}
