using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Mathematics
{
  public class CompositeBSpline
  {
    public delegate void SplinePointFunctor( PointF position, PointF normal, int cpIndex );

    public static void SampleSpline( List<PointF> controlPoints, bool isCircle, SplinePointFunctor pointFunctor )
    {
      int n = controlPoints.Count;
      List<PointF> cps = new List<PointF>();
      if ( isCircle )
      {
        cps.Add( new PointF( controlPoints[n - 1].X, controlPoints[n - 1].Y ) );
        for ( int i = 0; i < n; ++i )
          cps.Add( new PointF( controlPoints[i].X, controlPoints[i].Y ) );

        cps.Add( new PointF( controlPoints[0].X, controlPoints[0].Y ) );
        cps.Add( new PointF( controlPoints[1].X, controlPoints[1].Y ) );
      }
      else
      {
        cps.Add( new PointF( controlPoints[0].X - ( controlPoints[1].X - controlPoints[0].X ),
          controlPoints[0].Y - ( controlPoints[1].Y - controlPoints[0].Y ) ) );

        for ( int i = 0; i < n; ++i )
          cps.Add( new PointF( controlPoints[i].X, controlPoints[i].Y ) );

        cps.Add( new PointF( controlPoints[n - 1].X - ( controlPoints[n - 2].X - controlPoints[n - 1].X ),
          controlPoints[n - 1].Y - ( controlPoints[n - 2].Y - controlPoints[n - 1].Y ) ) );
      }

      float sampleStep = 1;
      float restLength = sampleStep - 1e-8f;
      AnalyticBSpline2D splineSegment = new AnalyticBSpline2D();
      PointF lastNormal = new PointF();
      for ( int index = 0; index < cps.Count - 3; ++index )
      {
        splineSegment.Setup( cps[index], cps[index + 1], cps[index + 2], cps[index + 3] );

        float splineLength = splineSegment.GetLengthAdaptive( 0.01f, 100 );
        float dt = sampleStep / ( splineLength * 10.0f );
        float length = restLength + sampleStep;
        float lastT = 0;
        float t = 0;
        PointF pos = splineSegment.Get( t );
        PointF lastPos = pos;

        int storedCPIndex = index;

        while ( true )
        {
          length -= sampleStep;
          while ( length < sampleStep )
          {
            lastPos = pos;
            t += dt;
            pos = splineSegment.Get( t );

            length += (float)Math.Sqrt( ( lastPos.X - pos.X ) * ( lastPos.X - pos.X ) + ( lastPos.Y - pos.Y ) * ( lastPos.Y - pos.Y ) );
            if ( t > 1 )
              break;
          }

          if ( ( t > 1 ) || ( length < sampleStep ) )
            break;

          PointF location = splineSegment.Get( t );
          PointF normal = splineSegment.GetDiff1( t );
          float normalLen = 1.0f / (float)Math.Sqrt( normal.X * normal.X + normal.Y * normal.Y );
          lastNormal.X = normal.Y * normalLen;
          lastNormal.Y = -normal.X * normalLen;

          pointFunctor( location, lastNormal, storedCPIndex );

          lastT = t;
          storedCPIndex = -1;
        }

        restLength = splineSegment.GetLength( lastT, 1.0f, 100 );
      }

      if ( !isCircle )
        pointFunctor( controlPoints[controlPoints.Count - 1], lastNormal, controlPoints.Count - 1 );
    }

    public List<PointF> sampledPoints = new List<PointF>();

    public void SimplestSampleFunctor( PointF position, PointF normal, int cpIndex )
    {
      sampledPoints.Add( position );
    }
  }
}
