using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorPlugins.Scene;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using EditorNative.SceneElements;

namespace EditorPlugins.Scene.Editors.Widgets
{
  public class TargetPathPoint : GameSceneObject, IObjectTransformController, IMovingController
  {
    private SceneControl sceneControl = null;
    private Vec2 position = null;

    public TargetPathPoint( SceneControl sceneControl, Vec2 _position )
      : base( DBID.Empty, 0, "" )
    {
      this.sceneControl = sceneControl;
      position = _position;
    }

    public void UpdateLocation()
    {
      Placement pl = GetCurrentPlacement();
      pl.location.x = position.x;
      pl.location.y = position.y;
      pl.location.z = 0.0f;
      SetCurrentPlacement( pl );
    }

    Vector2 IMovingController.TileCoordinates
    {
      get
      {
        Placement pl = GetCurrentPlacement();
        return new Vector2( pl.location.x, pl.location.y );
      }
    }

    void IMovingController.Move( float offsetX, float offsetY, bool nonTile )
    {
      PickResult pickResult = sceneControl.Pick();
      if ( pickResult.HasTerrainIntersection )
      {
        var terrainIntersection = pickResult.TerrainIntersection;
        Vec3 newpos = new Vec3();
        newpos.z = 0;
        newpos.x = terrainIntersection.X + offsetX;
        newpos.y = terrainIntersection.Y + offsetY;

        position.x = newpos.x;
        position.y = newpos.y;

        Placement pl = GetCurrentPlacement();
        pl.location.x = newpos.x;
        pl.location.y = newpos.y;
        pl.location.z = newpos.z;
        SetCurrentPlacement( pl );
      }
    }

    Vector3 IObjectTransformController.Location
    {
      get
      {
        Placement pl = GetCurrentPlacement();
        return new Vector3( pl.location.x, pl.location.y, pl.location.z );
      }
      set
      {
        Placement pl = GetCurrentPlacement();
        pl.location.x = value.X;
        pl.location.y = value.Y;
        pl.location.z = 0.0f;
        SetCurrentPlacement( pl );
      }
    }

    Quaternion IObjectTransformController.Rotation
    {
      get
      {
        return new Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
      }
      set
      {
      }
    }

    Vector3 IObjectTransformController.Scale
    {
      get
      {
        return new Vector3( 1.0f, 1.0f, 1.0f );
      }
      set
      {
      }
    }

    TransformParameters IObjectTransformController.MovingX
    {
      get { return TransformParameters.FullEnabled; }
    }

    TransformParameters IObjectTransformController.MovingY
    {
      get { return TransformParameters.FullEnabled; }
    }

    TransformParameters IObjectTransformController.MovingZ
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationPitch
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationRoll
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationYaw
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingX
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingY
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingZ
    {
      get { return TransformParameters.Disabled; }
    }

    bool IObjectTransformController.IsCommonCenter { get; set; }
  }


  public abstract class TargetPathWidgetBase : EditorControlWidget
  {
    private GameSceneObject gameSceneObject = null;
    private ToolStripButton tsbTargetPathAddPoint = null;
    private ToolStripButton tsbTargetPathDeletePoint = null;
    private ToolStripSeparator tssDelimiter = null;

    private List<TargetPathPoint> points = new List<TargetPathPoint>();

    public TargetPathWidgetBase( EditorControl _control ) : base( _control ) { }

    public override bool IsSelected
    {
      get {
        foreach ( TargetPathPoint item in points )
        {
          if ( item.IsSelected )
            return true;
        }
        return false; 
      }
    }

    public override void Create( GameSceneObject target )
    {
      gameSceneObject = target;

      EditorControl.ToolStrip.SuspendLayout();
      tsbTargetPathAddPoint = new ToolStripButton( EditorPluginResources.FlagCreate );
      tsbTargetPathDeletePoint = new ToolStripButton( EditorPluginResources.FlagDelete );
      tsbTargetPathAddPoint.Name = "AddPoint";
      tsbTargetPathDeletePoint.Name = "DeletePoint";
      tsbTargetPathAddPoint.Enabled = CanAddTarget();
      tsbTargetPathDeletePoint.Enabled = CanDeleteTarget();
      tsbTargetPathAddPoint.Click += new EventHandler( tsbSplineAddControlPoint_Click );
      tsbTargetPathDeletePoint.Click += new EventHandler( tsbSplineDeleteControlPoint_Click );

      tssDelimiter = new ToolStripSeparator();
      EditorControl.ToolStrip.Items.Add( tssDelimiter );
      EditorControl.ToolStrip.Items.Add( tsbTargetPathAddPoint );
      EditorControl.ToolStrip.Items.Add( tsbTargetPathDeletePoint );
      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      CreatePoints();
    }

    private void CreatePoints()
    {
      int n = GetPositionCount();

      for ( int i = 0; i < n; ++i )
      {
        Vec2 pos = GetPosition( i );
        TargetPathPoint newPoint = new TargetPathPoint( EditorControl.SceneControl, pos );
        newPoint.EnumerateSceneObjects().Add( new NativeSceneObject( DBID.FromString( "Tech/Default/Flag.SOBJ" ) ) );
        newPoint.IsSelectable = true;
        points.Add( newPoint );
        newPoint.Location = new Vector3( pos.x, pos.y, 0 );
        EditorControl.Scene.Add( newPoint );
        newPoint.UpdateLocation();
      }
    }

    public override void Destroy()
    {
      EditorControl.ToolStrip.SuspendLayout();
      EditorControl.ToolStrip.Items.Remove( tssDelimiter );
      EditorControl.ToolStrip.Items.Remove( tsbTargetPathAddPoint );
      EditorControl.ToolStrip.Items.Remove( tsbTargetPathDeletePoint );
      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      foreach ( TargetPathPoint item in points )
        EditorControl.Scene.Remove( item );

      points.Clear();
    }

    public override void Update()
    {
      bool isSelected = this.IsSelected;
      tsbTargetPathAddPoint.Enabled = CanAddTarget() && ( isSelected || gameSceneObject.IsSelected && GetPositionCount() == 0 );
      tsbTargetPathDeletePoint.Enabled = CanDeleteTarget() && isSelected;

      Placement from = gameSceneObject.GetCurrentPlacement();
      Vector3 point1 = new Vector3( from.location.x, from.location.y, from.location.z );

      for ( int i = 0; i < points.Count; i++ )
      {
        Placement to = points[i].GetCurrentPlacement();
        Vector3 point2 = new Vector3( to.location.x, to.location.y, to.location.z );
        EditorRender.DrawLine3D( point1, point2, System.Drawing.Color.Red, false );
        point1 = point2;
      }
    }

    private void tsbSplineAddControlPoint_Click( object sender, EventArgs e )
    {
      int index = -1;
      IList<SceneElement> selected = EditorControl.Scene.SelectedObjects;
      foreach ( SceneElement item in selected )
      {
        if ( item is TargetPathPoint )
        {
          index = points.IndexOf( item as TargetPathPoint );
          break;
        }
      }

      Vec2 pos = AddTarget( index );
      TargetPathPoint newPoint = new TargetPathPoint( EditorControl.SceneControl, pos );
      newPoint.EnumerateSceneObjects().Add( new NativeSceneObject( DBID.FromString( "Tech/Default/Flag.SOBJ" ) ) );
      newPoint.IsSelectable = true;
      if ( index >= 0 )
        points.Insert( index, newPoint );
      else
        points.Add( newPoint );
      newPoint.Location = new Vector3( pos.x, pos.y, 0 );
      EditorControl.Scene.Add( newPoint );
      newPoint.UpdateLocation();
    }

    private void tsbSplineDeleteControlPoint_Click( object sender, EventArgs e )
    {
      IList<SceneElement> selected = EditorControl.Scene.SelectedObjects;
      List<TargetPathPoint> toDelete = new List<TargetPathPoint>();
      foreach ( SceneElement item in selected )
      {
        if ( item is TargetPathPoint )
          toDelete.Add( item as TargetPathPoint );
      }

      if ( toDelete.Count == 0 )
      {
        TargetPathPoint item = points[points.Count - 1];
        DeleteTarget( points.IndexOf( item ) );
        points.Remove( item );
        EditorControl.Scene.Remove( item );
      }
      else
      {
        foreach ( TargetPathPoint item in toDelete )
        {
          DeleteTarget( points.IndexOf( item ) );
          points.Remove( item );
          EditorControl.Scene.Remove( item );
        }
      }

      gameSceneObject.IsSelected = true;
    }

    protected abstract Vec2 GetPosition( int index );
    protected abstract int GetPositionCount();
    protected abstract bool CanAddTarget();
    protected abstract Vec2 AddTarget( int index );
    protected abstract bool CanDeleteTarget();
    protected abstract void DeleteTarget( int index );
  }
}
