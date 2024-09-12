using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EaselLevelEditor
{
  /// <summary>
  /// base editor point class 
  /// </summary>
  public class EditorPoint
  {
    public int PointNumber
    {
      get { return pointNum; }
    }

    public Point Coord
    {
      get { return pointCoord; }
    }

    private EaselScaler scaler;
    private int         pointNum;
    private Point       pointCoord;
    private Rectangle   rectPoint;

    private const int CONTROL_POINT_OFFSET = 10;

    public EditorPoint(EaselScaler _scaler,int _num,Point _coords)
    {
      scaler      = _scaler;
      pointNum    = _num;
      pointCoord  = _coords;

      int logicalOffsetWidth;
      int logicalOffsetHeigth;

      scaler.RecalculateToLogicalWidth(CONTROL_POINT_OFFSET,out logicalOffsetWidth);
      scaler.RecalculateToLogicalHeight(CONTROL_POINT_OFFSET,out logicalOffsetHeigth);

      rectPoint = new Rectangle(pointCoord.X - logicalOffsetWidth,
                                pointCoord.Y - logicalOffsetHeigth,
                                logicalOffsetWidth * 2,
                                logicalOffsetHeigth * 2);
    }

     public void DrawPoint(Graphics _graphics)
    {
      Pen controlPointPen = new Pen(Color.Green, 4);
      Font numberFont = new Font("Arial", 16);

      Point scaledPoint;
      scaler.RecalculateToScaledCoordinate(pointCoord, out scaledPoint);
      _graphics.DrawRectangle(controlPointPen, scaledPoint.X - CONTROL_POINT_OFFSET,
                                               scaledPoint.Y - CONTROL_POINT_OFFSET,
                                               CONTROL_POINT_OFFSET * 2,
                                               CONTROL_POINT_OFFSET * 2); // drawing base point
      _graphics.DrawString(pointNum.ToString(),
                          numberFont, Brushes.Red,
                          (float)(scaledPoint.X - CONTROL_POINT_OFFSET),
                          (float)(scaledPoint.Y - CONTROL_POINT_OFFSET));
    }

    public bool CheckHit(Point _coord)
    {
      if (_coord.X >= rectPoint.Left && _coord.X <= rectPoint.Right &&
        _coord.Y >= rectPoint.Top && _coord.Y <= rectPoint.Bottom)
        return true;
      
      return false;
    }
  }
}
