/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CircleRays.h"


/*

// This algorithm is taken from public sources
//
// http://www.cpe.ku.ac.th/~pom/courses/204481/LectureNote/2DLines.ppt
//

Begin  {Circle}
  x := r;	
  y := 0;	
  d := 1 - r;
  Repeat
    Circle_Points(x,y); 
    y := y + 1;
    If d < 0 Then 
      d := d + 2*y + 1
    Else 
      Begin
        x := x - 1;
        d := d + 2*(y-x) + 1
      End
  Until x < y
End;  {Circle}

// Modification idea to mark diagonal points too

Begin  {Circle}
  x := r;	
  y := 0;	
  d := 1 - r;
  Repeat
    Circle_Points(x,y); 
    y := y + 1;
    If d < 0 Then 
      d := d + 2*y + 1
    Else 
      Begin
        y := y - 1;
        x := x - 1;
        Circle_Points(x,y); 
        y := y + 1;
        d := d + 2*(y-x) + 1
      End
  Until x < y
End;  {Circle}

*/

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

namespace NWorld
{

CircleRays::CircleRays()
{
  numRays   = 0;
}

CircleRays *CircleRays::CreateCircleForRadius(int radius)
{
  NI_VERIFY(radius < 4096, "Too long  radius", return  NULL;)
  NI_VERIFY(radius > 2,    "Too small radius", return  NULL;)
  
  CircleRays *rays = new CircleRays();
  int         x, y, d;
    
  // scan for number of rays
  x           = radius;
  y           = 0;
  d           = 1 - radius;
  rays->numRays = 0;
  while (x >= y) 
  {
    // action for (x,y)
    rays->numRays++;
    
    y++;
    if (d < 0) 
    {
      d += 2*y + 1;
    }
    else 
    {
      y--;
      x--;
      // action for (x,y)
      rays->numRays++;

      y++;      
      d += 2*(y - x) + 1;
    }
  }
  rays->numRays <<= 3;  // *= 8

  Reset(rays->pRays, new RayPixels[rays->numRays]);
  //rays->pRays = new RayPixels[rays->numRays];

  x           = radius;
  y           = 0;
  d           = 1 - radius;


  int index   = 0;
  while (x >= y) 
  {
    // action for x,y
    rays->GetRay(index)->CreateRay(0, 0, x, y);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, y, x);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, y, -x);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, x, -y);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, -x, -y);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, -y, -x);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, -y, x);
    index++;
    rays->GetRay(index)->CreateRay(0, 0, -x, y);
    index++;

    y++;
    if (d < 0) 
    {
      d += 2*y + 1;
    }
    else 
    {
      y--;
      x--;
      // action for x,y
      rays->GetRay(index)->CreateRay(0, 0, x, y);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, y, x);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, y, -x);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, x, -y);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, -x, -y);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, -y, -x);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, -y, x);
      index++;
      rays->GetRay(index)->CreateRay(0, 0, -x, y);
      index++;
      
      
      y++;
      d += 2*(y - x) + 1;
    }
  }
  
  return rays;  
}

} // namespace

