using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace EaselLevelEditor.Layers
{
  /// <summary>
  /// spline layer object
  /// responsible for spline drawing
  /// </summary>
  class EaselEditorSplineLayer : EaselEditorLayer
  {
    private EaselSpline spline;
    private EaselScaler scaler;

    public EaselEditorSplineLayer() : base()
    {

    }

    protected override void vDraw(Graphics _graphics)
    {
      if(spline != null)
      {
        Point[] splinePoints = spline.SplineLinearPoints;
        if (splinePoints.Length == 0)
          return;
        
        Pen splineLinePen = new Pen(Color.Red, 4);

        Point basePoint, scaledBasePoint;
        Point currentPoint, scaledCurrentPoint;

        basePoint = splinePoints[0];//(Point)pointEnum.Entry.Value;
        scaler.RecalculateToScaledCoordinate(basePoint, out scaledBasePoint);

        for (int i = 1; i < splinePoints.Length; i++ )
        {
          currentPoint = splinePoints[i];//(Point)pointEnum.Entry.Value;
          scaler.RecalculateToScaledCoordinate(currentPoint, out scaledCurrentPoint);

          // отрисовываю линию сплайна
          _graphics.DrawLine(splineLinePen, scaledBasePoint, scaledCurrentPoint);

          scaledBasePoint = scaledCurrentPoint;
        }
      }
    }

    protected override void vUpdate(EaselSpline _spline, EaselScaler _scaler)
    {
      spline = _spline;
      scaler = _scaler;
    }
  }
}
