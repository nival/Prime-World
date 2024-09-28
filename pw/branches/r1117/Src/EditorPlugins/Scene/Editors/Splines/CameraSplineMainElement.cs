using System.Collections.Generic;
using System.Drawing;
using DBTypes;
using EditorPlugins.Scene;
using EditorNative;
using EditorNative.SceneElements;
using EditorPlugins.Mathematics;

namespace EditorPlugins.Scene.Editors.Splines
{
  internal class CameraSplineMainElement : SplineMainElementBase<Spline3DControlPointDesc, CameraSplineControlElement>
  {
    private readonly List<Vector3> sampledPoints = new List<Vector3>();

    private readonly List<Quaternion> sampledQuat = new List<Quaternion>();

    private const int frequency = 300;

    private int hight;

    public override Quaternion BaseRotation
    {
      get { return base.BaseRotation; }
      set
      {
        //if ( base.BaseRotation == null )
        {
          base.BaseRotation = value;
        }
        //else if ( base.BaseRotation != value )
        //{
        //  for( int i = 0; i < splinePoints.Count; ++i )
        //  {
        //    Vector3 lastPos = new Vector3( splinePoints[i].position.x, splinePoints[i].position.y,
        //                                   splinePoints[i].position.z );
        //    lastPos = base.BaseRotation.Inverted.Rotate( lastPos );

        //    Vector3 newPos = value.Rotate( lastPos );
        //    splinePoints[i].position.x = newPos.X;
        //    splinePoints[i].position.y = newPos.Y;
        //    splinePoints[i].position.z = newPos.Z;

        //  }
        //  base.BaseRotation = value;
        //}
      }
    }

    public override Vector3 BaseScale
    {
      get { return base.BaseScale; }
      set
      {
        if ( base.BaseScale == null )
        {
          base.BaseScale = value;
        }
        else if ( base.BaseScale != value )
        {
          if ( value.X < 0.0001f || value.Y < 0.0001f || value.Z < 0.0001f )
          {
            return;
          }

          for ( int i = 0; i < splinePoints.Count; ++i )
          {
            Vector3 lastPos = new Vector3( splinePoints[i].position.x, splinePoints[i].position.y,
                                           splinePoints[i].position.z );
            lastPos.X /= base.BaseScale.X;
            lastPos.Y /= base.BaseScale.Y;
            lastPos.Z /= base.BaseScale.Z;

            Vector3 newPos = new Vector3( lastPos.X * value.X, lastPos.Y * value.Y, lastPos.Z * value.Z );
            splinePoints[i].position.x = newPos.X;
            splinePoints[i].position.y = newPos.Y;
            splinePoints[i].position.z = newPos.Z;
          }
          base.BaseScale = value;
        }
      }
    }

    public override void CorrectPosition( Vector3 point )
    {
      if ( !IsAbsolutePosition )
      {
        Vector3 newPos = BaseRotation.Rotate( point );
        point.X = newPos.X;
        point.Y = newPos.Y;
        point.Z = newPos.Z;

        point.X += BaseLocation.X;
        point.Y += BaseLocation.Y;
        point.Z += BaseLocation.Z;
      }
    }

    public override void Draw()
    {
      if ( null == splinePoints || splinePoints.Count < 2 )
        return;

      Vector3 prevPoint = new Vector3( splinePoints[0].position.x, splinePoints[0].position.y, splinePoints[0].position.z );
      CorrectPosition( prevPoint );

      Vector3 startPoint = prevPoint;

      for ( int i = 1; i < splinePoints.Count; ++i )
      {
        Vector3 curPoint = new Vector3( splinePoints[i].position.x, splinePoints[i].position.y, splinePoints[i].position.z );
        CorrectPosition( curPoint );

        EditorRender.DrawLine3D( prevPoint, curPoint, System.Drawing.Color.Red, false );
        prevPoint = curPoint;
      }

      if ( IsCircle )
        EditorRender.DrawLine3D( prevPoint, startPoint, System.Drawing.Color.Red, false );


      if ( needResample )
        ResampleSpline();

      if ( sampledPoints.Count == 0 )
        return;

      prevPoint = new Vector3( sampledPoints[0].X, sampledPoints[0].Y, sampledPoints[0].Z );
      CorrectPosition( prevPoint );

      for ( int i = 1; i < sampledPoints.Count; ++i )
      {
        Vector3 curPoint = new Vector3( sampledPoints[i].X, sampledPoints[i].Y, sampledPoints[i].Z );
        CorrectPosition( curPoint );

        EditorRender.DrawLine3D( prevPoint, curPoint, System.Drawing.Color.Yellow, false );

        Vector3 dir = sampledQuat[i].GetYAxis();
        EditorRender.DrawLine3D( curPoint, curPoint + dir.Normalized * hight, System.Drawing.Color.White, false );

        prevPoint = curPoint;
      }

      if ( IsCircle )
        EditorRender.DrawLine3D( prevPoint, startPoint, System.Drawing.Color.Yellow, false );
    }

    internal override void AddToSceneInternal( EditorScene scene )
    {
      for ( int i = 0; i < splinePoints.Count; ++i )
      {
        CameraSplineControlElement newCP = new CameraSplineControlElement( this, splinePoints[i], hight );
        controlPoints.Add( newCP );
        newCP.AddToScene( scene );
      }
    }

    private void ResampleSpline()
    {
      if ( splinePoints.Count < 2 )
        return;

      sampledPoints.Clear();
      sampledQuat.Clear();

      PlacementSpline spline = new PlacementSpline();

      List<Vector3> points = new List<Vector3>();
      List<Vector3> angles = new List<Vector3>();

      for ( int i = 0; i < splinePoints.Count; ++i )
      {
        Quaternion quat =
          Quaternion.FromEulerAngles( new Vector3( splinePoints[i].rotation.y, splinePoints[i].rotation.x,
                                                   splinePoints[i].rotation.z ) );
        Quaternion newQuat = BaseRotation*quat;
        Vector3 euler = newQuat.EulerAngles;

        points.Add( new Vector3( splinePoints[i].position.x, splinePoints[i].position.y, splinePoints[i].position.z ) );
        angles.Add( new Vector3( euler.Y, euler.X, euler.Z ) );
      }

      spline.Setup( points, angles, 0.9f, frequency );

      for ( int i = 0; i < frequency; i++ )
      {
        Quaternion tempQuat = new Quaternion( 0, 0, 0, 1 );
        Vector3 tempVec = new Vector3( 0, 0, 0 );
        spline.GetValue( (float)i / (float)frequency, tempVec, tempQuat );

        sampledPoints.Add( tempVec );
        sampledQuat.Add( tempQuat );
      }

      needResample = false;
    }

    internal override void RemoveFromSceneInternal()
    {
      for ( int i = 0; i < controlPoints.Count; ++i )
        controlPoints[i].RemoveFromScene();
    }

    public CameraSplineMainElement( SceneControl control, IList<Spline3DControlPointDesc> splinePoints, Vector3 baseLocation, Quaternion baseRotation, Vector3 baseScale, bool hasWidth, bool isCircle, bool isAbsolutePosition, int _hight )
      : base( control, splinePoints, baseLocation, baseRotation, baseScale, hasWidth, isCircle, isAbsolutePosition )
    {
      hight = _hight;
    }

    internal override void InsertControlPoint( int position )
    {
      if ( position < 0 || position >= controlPoints.Count )
        return;

      int i = ( position == 0 ) ? 1 : position;

      Spline3DControlPointDesc point = new Spline3DControlPointDesc();
      point.position.x = ( splinePoints[i].position.x + splinePoints[i - 1].position.x ) * 0.5f;
      point.position.y = ( splinePoints[i].position.y + splinePoints[i - 1].position.y ) * 0.5f;
      point.position.z = ( splinePoints[i].position.z + splinePoints[i - 1].position.z ) * 0.5f;
      splinePoints.Insert( i, point );

      CameraSplineControlElement newCP = new CameraSplineControlElement( this, splinePoints[i], hight );
      controlPoints.Insert( i, newCP );
      newCP.AddToScene( Scene );

      UpdateToolbarItems();
      Invalidate();
    }

    internal void AddControlPoint( Spline3DControlPointDesc point )
    {
      splinePoints.Add( point );
      int i = splinePoints.Count - 1;

      CameraSplineControlElement newCP = new CameraSplineControlElement( this, splinePoints[i], hight );
      controlPoints.Insert( i, newCP );
      newCP.AddToScene( Scene );

      UpdateToolbarItems();
      Invalidate();
    }

    internal override void DeleteControlPoint( int position )
    {
      if ( position < 0 || position >= controlPoints.Count || controlPoints.Count <= 2 )
        return;

      CameraSplineControlElement cp = controlPoints[position];
      controlPoints.RemoveAt( position );
      splinePoints.RemoveAt( position );
      cp.RemoveFromScene();

      UpdateToolbarItems();
      Invalidate();
    }
  }
}

