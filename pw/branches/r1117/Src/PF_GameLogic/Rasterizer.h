#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////
#include "../System/2Darray.h"

/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////

#define   ACCURACY_SHIFT        16
#define   ACCURACY_HALF         (1<<(ACCURACY_SHIFT-1))

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////


namespace NWorld
{

typedef CTPoint<int>    Point2DS;

inline void Swap(Point2DS &p0, Point2DS &p1)
{
  int temp;
  temp = p0.x; p0.x = p1.x; p1.x = temp;
  temp = p0.y; p0.y = p1.y; p1.y = temp;
}




class LineIterator
{
public:
  LineIterator(const Point2DS &p0, const Point2DS &p1)
  {
    int dx = p1.x - p0.x, dy = p1.y - p0.y;
    NI_ASSERT(dy >= 0, "Bad vertex order for triangle rasterization");
    if (dy > 0)
      m_xStep = (dx << ACCURACY_SHIFT) / dy;
    else
      m_xStep = 0;
    m_xAcc = (p0.x << ACCURACY_SHIFT) + ACCURACY_HALF;
  }
  inline int GetX() 
  { 
    return (m_xAcc >> ACCURACY_SHIFT);
  }
  inline void Step()
  {
    m_xAcc += m_xStep;
  }
  
private:
  int m_xAcc, m_xStep;
};

class BresenhamIterator
{
public:
  BresenhamIterator(const Point2DS &start, const Point2DS &end)
  {
    int dx = end.x - start.x, dy = end.y - start.y;
    int absDx = (dx > 0)? dx: -dx;
    int absDy = (dy > 0)? dy: -dy;
    m_numSteps = (absDx > absDy)? absDx: absDy;
    if (m_numSteps > 0)
    {
      m_xStep = (dx << ACCURACY_SHIFT) / m_numSteps;
      m_yStep = (dy << ACCURACY_SHIFT) / m_numSteps;
    }
    else
    {
      m_xStep = m_yStep = 0;
    }
    m_xAcc  = (start.x << ACCURACY_SHIFT) + ACCURACY_HALF;
    m_yAcc  = (start.y << ACCURACY_SHIFT) + ACCURACY_HALF;
  }
  inline int  GetNumSteps() { return m_numSteps + 1; }
  inline void Step()
  {
    m_xAcc += m_xStep;
    m_yAcc += m_yStep;
  }
  inline int  GetX()
  {
    return (m_xAcc >> ACCURACY_SHIFT);
  }
  inline int  GetY()
  {
    return (m_yAcc >> ACCURACY_SHIFT);
  }
  
private:
  int m_numSteps;
  int m_xStep;
  int m_yStep;
  int m_xAcc;
  int m_yAcc;
      
};

class Rasterizer
{
public:
  Rasterizer(unsigned char *buf, int sideX, int sideY);
  void  DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char bufValue);
  void  DrawLine(int x0, int y0, int x1, int y1, unsigned char bufValue);

private:
  unsigned  char *m_buffer;
  int             m_bufSideX;
  int             m_bufSideY;
  //int             m_bufSideXDegree;
};


} // namespace