
/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Rasterizer.h"


/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////


namespace NWorld
{

/////////////////////////////////////////////////////////////////////////////////
// Methods
/////////////////////////////////////////////////////////////////////////////////

Rasterizer::Rasterizer(unsigned char *buf, int sideX, int sideY)
{
  m_buffer    = buf;
  m_bufSideX  = sideX;
  m_bufSideY  = sideY;
  //m_bufSideXDegree = -1;
  //while (sideX > 0)
  //{
  //  m_bufSideXDegree ++;
  //  sideX >>= 1;
  //}
}

void  Rasterizer::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char bufValue)
{
  int             y, xS, xE, i;
  unsigned char   *dest;
  
  NI_VERIFY(x0 < m_bufSideX, "x0 in triangle out of image", return; )
  NI_VERIFY(x1 < m_bufSideX, "x1 in triangle out of image", return; )
  NI_VERIFY(x2 < m_bufSideX, "x2 in triangle out of image", return; )
  NI_VERIFY(y0 < m_bufSideY, "y0 in triangle out of image", return; )
  NI_VERIFY(y1 < m_bufSideY, "y1 in triangle out of image", return; )
  NI_VERIFY(y2 < m_bufSideY, "y2 in triangle out of image", return; )
  
  Point2DS p0(x0, y0), p1(x1, y1), p2(x2, y2);
  if (p0.y  > p1.y)
    Swap(p0, p1);
  if (p0.y  > p2.y)
    Swap(p0, p2);
  Point2DS p01 = p1 - p0, p12 = p2 - p1;
  int dotProd = p01.y * p12.x - p01.x * p12.y;
  if (dotProd == 0)
    return; // degenerated triangle
  if (dotProd < 0)
    Swap(p1, p2);
  if (p1.y > p2.y)
  {
    //
    //        * p0
    //         \ -
    //          \  -
    //           \   -
    //            \    -
    //             \     -
    //              \      * p2
    //               \    -
    //                \  -
    //                 * p1
    //
    //
    LineIterator line01(p0, p1), line02(p0, p2), line21(p2, p1);
    for (y = p0.y; y < p2.y; y++)
    {
      xS = line01.GetX();
      xE = line02.GetX();
      
      // draw line
      //dest = m_buffer + (y << m_bufSideXDegree) + xS;
      dest = m_buffer + (y * m_bufSideX) + xS;
      for (i = (xE - xS + 1); i > 0; i--)
      {
        *dest = bufValue;
        dest++;
      }
      
      // go to next line
      line01.Step(); 
      line02.Step();
    }
    for (; y < p1.y; y++)
    {
      xS = line01.GetX();
      xE = line21.GetX();

      // draw line
      //dest = m_buffer + (y << m_bufSideXDegree) + xS;
      dest = m_buffer + (y * m_bufSideX) + xS;
      for (i = (xE - xS + 1); i > 0; i--)
      {
        *dest = bufValue;
        dest++;
      }
      
      // go to next line
      line01.Step(); 
      line21.Step();
    }
  
  }
  else
  {
    //
    //             * p0
    //            /| 
    //           / |
    //          /   |
    //         /    |
    //        /      |
    //       * p1    |
    //        \       |
    //          \     |
    //            \    |
    //              \  |
    //                 * p2
    LineIterator line01(p0, p1), line12(p1, p2), line02(p0, p2);
    for (y = p0.y; y < p1.y; y++)
    {
      xS = line01.GetX();
      xE = line02.GetX();

      // draw line
      //dest = m_buffer + (y << m_bufSideXDegree) + xS;
      dest = m_buffer + (y * m_bufSideX) + xS;
      for (i = (xE - xS + 1); i > 0; i--)
      {
        *dest = bufValue;
        dest++;
      }
      
      // go to next line
      line01.Step(); 
      line02.Step();
    }
    for (; y < p2.y; y++)
    {
      xS = line12.GetX();
      xE = line02.GetX();

      // draw line
      //dest = m_buffer + (y << m_bufSideXDegree) + xS;
      dest = m_buffer + (y * m_bufSideX) + xS;
      for (i = (xE - xS + 1); i > 0; i--)
      {
        *dest = bufValue;
        dest++;
      }

      // go to next line
      line12.Step(); 
      line02.Step();
    }
  }
}

void  Rasterizer::DrawLine(int x0, int y0, int x1, int y1, unsigned char bufValue)
{
  int             i, len;
  int             x, y;
  unsigned  char  *dest;
  
  Point2DS start(x0, y0), end(x1, y1);
  BresenhamIterator iter(start, end);
  
  len = iter.GetNumSteps();
  for (i = 0; i < len; i++)
  {
    x = iter.GetX();
    y = iter.GetY();
    //dest = m_buffer + (y << m_bufSideXDegree) + x;
    dest = m_buffer + (y * m_bufSideX) + x;
    *dest = bufValue;
    iter.Step();
  }
}

} // namespace

